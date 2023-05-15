#pragma once

#include <CppCore/Root.h>
#include <CppCore/Threading/Runnable.h>
#include <CppCore/Threading/Handler.h>
#include <CppCore/Network/Message.h>
#include <CppCore/Network/TcpLink.h>
#include <CppCore/Logger.h>

#ifndef CPPCORE_TCPCLIENT_BUFFERCOUNT_TCP
#define CPPCORE_TCPCLIENT_BUFFERCOUNT_TCP   768
#endif
#ifndef CPPCORE_TCPCLIENT_QUEUESIZE_TCP_OUT
#define CPPCORE_TCPCLIENT_QUEUESIZE_TCP_OUT 256
#endif
#ifndef CPPCORE_TCPCLIENT_QUEUESIZE_TCP_IN
#define CPPCORE_TCPCLIENT_QUEUESIZE_TCP_IN  512
#endif

namespace CppCore
{
   /// <summary>
   /// TcpClient
   /// </summary>
   template<
      typename TMSGTCP      = TcpLinkMessage<>,
      typename TPOOLTCP     = TcpLinkPool<TMSGTCP, CPPCORE_TCPCLIENT_BUFFERCOUNT_TCP>,
      typename TQUEUETCPIN  = TcpLinkQueueIn<TMSGTCP, CPPCORE_TCPCLIENT_QUEUESIZE_TCP_IN>,
      typename TQUEUETCPOUT = TcpLinkQueueIn<TMSGTCP, CPPCORE_TCPCLIENT_QUEUESIZE_TCP_OUT>,
      typename TNETLINK     = TcpLink<TMSGTCP, TPOOLTCP, TQUEUETCPIN, TQUEUETCPOUT>>
   class TcpClient : 
      public Logger::Producer<Logger, Logger::Channel::Network>,
      public TNETLINK::Callback
   {
   public:
      /// <summary>
      /// TcpClient Callback
      /// </summary>
      class Callback
      {
      public:
         /// <summary>
         /// Raised if new data is available.
         /// Executed on message handler.
         /// Return true if you are done with the message, else false.
         /// But then you must push it back to the pool yourself!
         /// </summary>
         INLINE virtual bool onTcpClientMessage(TMSGTCP& msg) { return true; }

         /// <summary>
         /// Raised after connect() once fully connected.
         /// Executed on connection handler.
         /// </summary>
         INLINE virtual void onTcpClientConnected() { }

         /// <summary>
         /// Raised after connect() in case of error.
         /// Executed on connection handler.
         /// </summary>
         INLINE virtual void onTcpClientConnectionFailed() { }

         /// <summary>
         /// Raised after disconnect() or in case of connection error.
         /// Executed on connection handler.
         /// </summary>
         INLINE virtual void onTcpClientDisconnected() { }
      };

      /// <summary>
      /// Connection State of TcpClient
      /// </summary>
      enum ConnectionState 
      { 
         Disconnected, 
         Connecting, 
         Connected, 
         Disconnecting 
      };

   protected:
      ConnectionState    mConnectionState;
      uint32_t           mConnectionTimeout;
      CPPCORE_MUTEX_TYPE mMutexSend;
      CPPCORE_MUTEX_TYPE mMutexRecv;
      CPPCORE_MUTEX_TYPE mMutexConnecting;
      Handler&           mHandlerConnection;
      Handler&           mHandlerWorkload;
      Handler&           mHandlerMessage;
      Callback&          mCallback;
      TPOOLTCP           mPoolMessageTcp;
      TNETLINK           mNetLink;
      Runnable           mRunnableOnRead;
      Runnable           mRunnableOnConnected;
      Runnable           mRunnableOnConnectionFailed;
      Runnable           mRunnableOnDisconnected;
      Runnable           mRunnableConnect;
      Runnable           mRunnableDisconnect;
      Runnable           mRunnableSend;
      Runnable           mRunnableRecv;
      string             mHost;
      uint16_t           mPort;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE TcpClient(
         Handler&   connectionHandler,
         Handler&   workloadHandler,
         Handler&   messageHandler,
         Logger&    logger,
         Callback&  callBack) :
         Logger::Producer<Logger, Logger::Channel::Network>(logger),
         mConnectionState(ConnectionState::Disconnected),
         mConnectionTimeout(3000),
         mHandlerConnection(connectionHandler),
         mHandlerWorkload(workloadHandler),
         mHandlerMessage(messageHandler),
         mCallback(callBack),
         mPoolMessageTcp(),
         mNetLink(mPoolMessageTcp),
         mRunnableOnRead([this]() { runOnRead(); }),
         mRunnableOnConnected([this]() { mCallback.onTcpClientConnected(); }),
         mRunnableOnConnectionFailed([this]() { mCallback.onTcpClientConnectionFailed(); }),
         mRunnableOnDisconnected([this]() { mCallback.onTcpClientDisconnected(); }),
         mRunnableConnect([this]() { runConnect(); }),
         mRunnableDisconnect([this]() { runDisconnect(); }),
         mRunnableSend([this]() { runSend(); }),
         mRunnableRecv([this]() { runReceive(); }, milliseconds(0)),
         mHost(""),
         mPort(0)
      {
         CPPCORE_MUTEX_INIT(mMutexConnecting);
         CPPCORE_MUTEX_INIT(mMutexRecv);
         CPPCORE_MUTEX_INIT(mMutexSend);
      }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~TcpClient()
      {
         // disable timer runnables
         mRunnableRecv.setRepeat(false);

         // cancel runnables
         mHandlerWorkload.cancel(mRunnableRecv);
         mHandlerWorkload.cancel(mRunnableSend);
         mHandlerWorkload.cancel(mRunnableConnect);
         mHandlerWorkload.cancel(mRunnableDisconnect);

         // delete locks
         CPPCORE_MUTEX_DELETE(mMutexConnecting);
         CPPCORE_MUTEX_DELETE(mMutexRecv);
         CPPCORE_MUTEX_DELETE(mMutexSend);
      }

   private:
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // RUNNABLES
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Dequeues all pending incomgin tcp messages and raises
      /// onTcpCLientMessage() callback with each of them.
      /// Executed on message handler.
      /// </summary>
      INLINE void runOnRead()
      {
         while (TMSGTCP* msg = this->recvTcp())
         {
            if (mCallback.onTcpClientMessage(*msg))
               this->pushFreeTcp(msg);
         }
      }

      /// <summary>
      /// Sends all pending data that is waiting in the queues.
      /// Executed on workload handler.
      /// </summary>
      INLINE void runSend()
      {
         // lock
         CPPCORE_MUTEX_LOCK(mMutexSend);

         // must be in connected state
         if (mConnectionState == ConnectionState::Connected)
         {
            // (1) TCP
            mNetLink.send(*this);

            // (2) OTHER
            sendSub();
         }

         // unlock
         CPPCORE_MUTEX_UNLOCK(mMutexSend);
      }

      /// <summary>
      /// Receives data from socket into the queues.
      /// Waits up to timeout for new data.
      /// Executed on workload handler.
      /// </summary>
      INLINE void runReceive(const int timeout = 16)
      {
         // lock
         CPPCORE_MUTEX_LOCK(mMutexRecv);

         // must be in connected state
         if (mConnectionState == ConnectionState::Connected)
         {
            // remember blocked state before polling
            const bool ISSENDBLOCKED = mNetLink.isSendBlocked();

            // by default do POLLIN, this may recover from sendblock
            const uint16_t revents = mNetLink.poll(
               !ISSENDBLOCKED ? POLLIN : POLLIN | POLLOUT, timeout);

            // read pending tcp data
            if ((revents & POLLIN) || (revents & POLLHUP) || (revents & POLLERR))
               mNetLink.receive(*this);

            // recover from blocked send if no more
            if (ISSENDBLOCKED && !mNetLink.isSendBlocked())
               mHandlerWorkload.schedule(mRunnableSend);
         }

         // unlock
         CPPCORE_MUTEX_UNLOCK(mMutexRecv);
      }

      /// <summary>
      /// Connects to the currently specified endpoint if state is 'Connecting'.
      /// Executed on workload handler after calling 'connect()'.
      /// Changes ConnectionState to 'Connected' or 'Disconnected'.
      /// </summary>
      INLINE void runConnect()
      {
         CPPCORE_MUTEX_LOCK(mMutexSend);       // lock send
         CPPCORE_MUTEX_LOCK(mMutexRecv);       // lock recv
         CPPCORE_MUTEX_LOCK(mMutexConnecting); // lock con/disc

         // must be in state connecting to connect
         if (mConnectionState == ConnectionState::Connecting)
         {
            // connect
            const TcpSocket::ConnectReturn cr = mNetLink.connect(
               mHost.c_str(), 
               std::to_string(mPort).c_str(), 
               mConnectionTimeout);

            // sucessful
            if (cr == TcpSocket::ConnectReturn::OK)
            {
               const std::string CONLOG(
                  std::string("Successfully connected to ") + 
                  mNetLink.getAddressString() + ":" + 
                  std::to_string(mPort)
               );
               log(CONLOG);
               mConnectionState = ConnectionState::Connected;
               onConnected();
               mHandlerConnection.schedule(mRunnableOnConnected);
               mHandlerWorkload.schedule(mRunnableRecv);
            }

            // failed
            else
            {
               const std::string CONLOG(
                  std::string("Failed to connect to ") +
                  mNetLink.getAddressString() + ":" +
                  std::to_string(mPort)
               );
               logError(CONLOG);
               switch (cr)
               {
               case TcpSocket::ConnectReturn::NotClosed:
                  logError("Existing socket not closed.");
                  break;
               case TcpSocket::ConnectReturn::FailOnInit:
                  logError("Failed to create tcp socket.");
                  break;
               case TcpSocket::ConnectReturn::FailOnOptNoBlock:
                  logError("Failed to enable FIONBIO (noblock) on tcp socket.");
                  break;
               case TcpSocket::ConnectReturn::InvalidEndpoint:
                  logError("Invalid or unrecognized endpoint.");
                  break;
               case TcpSocket::ConnectReturn::TimeOut:
                  logError("Timeout on connection attempt.");
                  break;
               case TcpSocket::ConnectReturn::ConnectError:
                  logError("Error on connection attempt.");
                  break;
               default:
                  break;
               }
               mConnectionState = ConnectionState::Disconnected;
               mHandlerConnection.schedule(mRunnableOnConnectionFailed);
            }
         }

         CPPCORE_MUTEX_UNLOCK(mMutexConnecting); // unlock con/disc
         CPPCORE_MUTEX_UNLOCK(mMutexRecv);       // unlock recv
         CPPCORE_MUTEX_UNLOCK(mMutexSend);       // unlock send
      }

      /// <summary>
      /// Disconnects if state is 'Connected'.
      /// Executed on ThreadPool after calling 'disconnect()'.
      /// Changes ConnectionState to 'Disconnected'.
      /// </summary>
      INLINE void runDisconnect()
      {
         CPPCORE_MUTEX_LOCK(mMutexSend);       // lock send
         CPPCORE_MUTEX_LOCK(mMutexRecv);       // lock recv
         CPPCORE_MUTEX_LOCK(mMutexConnecting); // lock con/disc

         // must be in state disconnecting to disconnect
         if (mConnectionState == ConnectionState::Disconnecting)
         {
            // disable runnables
            mHandlerWorkload.cancel(mRunnableRecv);
            mHandlerWorkload.cancel(mRunnableSend);

            // reset tcp link
            mNetLink.close();

            // log
            log("Disconnected from " + 
               mHost + ":" + 
               std::to_string(mPort));

            // set as disconnected
            mConnectionState = ConnectionState::Disconnected;

            // raise internal callback on same thread
            onDisconnected();

            // raise asnyc callback on connection handler
            mHandlerConnection.schedule(mRunnableOnDisconnected);
         }

         CPPCORE_MUTEX_UNLOCK(mMutexConnecting); // unlock con/disc
         CPPCORE_MUTEX_UNLOCK(mMutexRecv);       // unlock recv
         CPPCORE_MUTEX_UNLOCK(mMutexSend);       // unlock send
      }

   protected:
      /// <summary>
      /// Raised from runConnect() in case of success.
      /// </summary>
      INLINE virtual void onConnected() { }

      /// <summary>
      /// Raised from runDisconnect() in case of success.
      /// </summary>
      INLINE virtual void onDisconnected() { }

      /// <summary>
      /// 
      /// </summary>
      INLINE virtual void sendSub() { }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TCPLINK SEND CALLBACKS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Raised by TcpLink before msg is finally written to socket.
      /// </summary>
      INLINE virtual void onSendFinalizeTcp(TMSGTCP& msg) override { }

      /// <summary>
      /// Raised by TcpLink in case some bytes were sent.
      /// </summary>
      INLINE virtual void onSendDataTransmitted(uint32_t bytes) override { }

      /// <summary>
      /// Raised by TcpLink in case the send socket is blocked.
      /// </summary>
      INLINE virtual void onSendBlocked() override 
      {
         logDebug("Tcp Sending Blocked");
      }

      /// <summary>
      /// Raised by TcpLink in case of socket error.
      /// </summary>
      INLINE virtual void onSendError() override 
      {
         logError("Disconnect (SOCKET ERROR SEND)"); 
         disconnect();
      }

      /// <summary>
      /// Raised by TcpLink in case of failed check on outgoing message.
      /// </summary>
      INLINE virtual void onSendCheckTcpFailed(TMSGTCP& msg) override
      {
         logWarn("Outgoing message discarded because of failed check.");
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TCPLINK RECV CALLBACKS
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////

      INLINE virtual bool onRecvCheckTcp(TMSGTCP& msg)  override  { return true; }
      INLINE virtual bool onRecvHandleTcp(TMSGTCP& msg)  override { return true; }
      INLINE virtual void onRecvNewMessage() override
      {
         mHandlerMessage.schedule(mRunnableOnRead);
      }
      INLINE virtual void onRecvRegularDisconnect() override
      {
         log("Disconnect (REGULAR)");
         disconnect();
      }
      INLINE virtual void onRecvErrorNoFreeTcpBuffer() override
      {
         logError("Disconnect (NO TCP BUFFER)");
         disconnect();
      }
      INLINE virtual void onRecvErrorLengthMismatch()  override
      {
         logError("Disconnect (LEN MISMATCH)");
         disconnect();
      }
      INLINE virtual void onRecvErrorTcpMsgOversized() override
      {
         logError("Disconnect (TCP-MSG OVERSIZED)");
         disconnect();
      }
      INLINE virtual void onRecvErrorSocket() override
      {
         logError("Disconnect (SOCKET ERROR RECV)");
         disconnect();
      }
      INLINE virtual void onRecvErrorTcpInQueueFull() override
      {
         logError("Disconnect (TCP-IN QUEUE FULL)");
         disconnect();
      }
      INLINE virtual void onRecvErrorCrc() override
      {
         logError("Disconnect (CRC ERROR)");
         disconnect();
      }
      INLINE virtual void onRecvErrorLength() override
      {
         logError("Disconnect (LEN ERROR)");
         disconnect();
      }

   public:
      /// <summary>
      /// State of connection.
      /// </summary>
      INLINE ConnectionState getConnectionState() const { return mConnectionState; }

      /// <summary>
      /// True if connection state is connected.
      /// </summary>
      INLINE bool isConnected() const { return mConnectionState == ConnectionState::Connected; }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TCPLINK
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Bytes received since connection was established.
      /// </summary>
      INLINE const uint64_t& getBytesReceived() const { return mNetLink.getBytesReceived();  }

      /// <summary>
      /// Bytes sent since connection was established.
      /// </summary>
      INLINE const uint64_t& getBytesSent() const { return mNetLink.getBytesSent(); }

      /// <summary>
      /// When the connection was successfully established
      /// </summary>
      INLINE const TimePoint& getStartTime() const { return mNetLink.getStartTime();  }

      /// <summary>
      /// Elapsed time since the connection was successfully established
      /// </summary>
      INLINE const Duration& getDuration() const { return mNetLink.getDuration();  }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CONNECTION
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Initiates a new connection with specified endpoint, but only if currently disconnected.
      /// Switches ConnectionState from 'Disconnected' to 'Connecting'.
      /// </summary>
      INLINE bool connect(const string& host, const uint16_t port, const uint32_t timeoutms = 3000)
      {
         CPPCORE_MUTEX_LOCK(mMutexConnecting); // lock con

         // new connection can only be established from disconnected state
         const bool DOCONNECT = (mConnectionState == ConnectionState::Disconnected);

         // schedule new connect
         if (DOCONNECT)
         {
            // save new endpoint, timeout and state
            mHost = host;
            mPort = port;
            mConnectionTimeout = timeoutms;
            mConnectionState = ConnectionState::Connecting;
            log("Connecting to " + mHost + ":" + std::to_string(mPort));

            // connect async in threadpool
            mHandlerWorkload.schedule(mRunnableConnect);
         }

         CPPCORE_MUTEX_UNLOCK(mMutexConnecting); // unlock con
         return DOCONNECT;                       // true if now connecting
      }

      /// <summary>
      /// Initiates a disconnect from the current endpoint, but only if currently connected.
      /// Switches ConnectionState from 'Connected' to 'Disconnecting'
      /// </summary>
      INLINE bool disconnect()
      {
         CPPCORE_MUTEX_LOCK(mMutexConnecting); // lock con

         // can only disconnect from connected state
         const bool doDisconnect = (mConnectionState == ConnectionState::Connected);

         if (doDisconnect)
         {
            // set as disconnecting
            mConnectionState = ConnectionState::Disconnecting;
            log("Disconnecting from " + mHost + ":" + std::to_string(mPort));

            // init tcp shutdown immediately, reset later
            mNetLink.shutdown();

            // disconnect async in threadpool
            mHandlerWorkload.schedule(mRunnableDisconnect);
         }

         CPPCORE_MUTEX_UNLOCK(mMutexConnecting); // unlock con
         return doDisconnect;                    // true if now disconnecting
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TCP POOL
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Pushes a free tcp message back to the pool.
      /// </summary>
      INLINE bool pushFreeTcp(TMSGTCP* msg) { return mPoolMessageTcp.pushBack(msg); }

      /// <summary>
      /// Pops a free tcp message from the pool.
      /// Use it to call sendTcp() or pushFreeTcp().
      /// </summary>
      INLINE TMSGTCP* popFreeTcp() { TMSGTCP* msg; return mPoolMessageTcp.popBack(msg) ? msg : 0; }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SEND/RECV | ENQUEUE/DEQUEUE
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Tries to dequeue the next available incoming tcp message.
      /// </summary>
      INLINE TMSGTCP* recvTcp() { TMSGTCP* msg; return mNetLink.dequeue(msg) ? msg : 0; }

      /// <summary>
      /// Enqueues a TCP message for transmission to the server.
      /// Do not access the message afterwards.
      /// </summary>
      INLINE bool sendTcp(TMSGTCP* message)
      {
         // can only send in connected state
         if (mConnectionState != ConnectionState::Connected)
         {
            mPoolMessageTcp.pushBack(message);
            return false;
         }

         // try to enqueue the tcp message for sending
         if (!mNetLink.enqueue(message))
         {
            logWarn("Disconnect (TCP-OUT QUEUE FULL)");
            disconnect();
            mPoolMessageTcp.pushBack(message);
            return false;
         }

         // try schedule the send task on the threadpool
         // false just means it's scheduled already...
         const bool OK = mHandlerWorkload.schedule(mRunnableSend);

         // success
         return true;
      }
   };
}
