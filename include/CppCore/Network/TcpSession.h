#pragma once

#include <CppCore/Root.h>
#include <CppCore/Threading/Handler.h>
#include <CppCore/Network/Essential.h>
#include <CppCore/Network/TcpLink.h>
#include <CppCore/Logger.h>

namespace CppCore
{
   /// <summary>
   /// Default Pool Type if not specified.
   /// </summary>
   template<typename TSESSION, size_t SIZE = CPPCORE_NETSERVER_MAXCLIENTS>
   using TcpSessionPool = Array::Fix::MT<TSESSION*, SIZE>;

   /// <summary>
   /// Shared data between all sessions and server.
   /// </summary>
   template<
      typename TMSGTCP  = TcpLinkMessage<>, 
      typename TPOOLTCP = TcpLinkPool<TMSGTCP, CPPCORE_NETSERVER_BUFFERCOUNT_TCP>>
   class TcpSessionSharedData
   {
   public:
      using MSGTCP  = TMSGTCP;
      using POOLTCP = TPOOLTCP;
      TPOOLTCP mPoolMessageTcp;
      INLINE TcpSessionSharedData() { }
   };

   /// <summary>
   /// TcpSession
   /// </summary>
   template<
      typename TMSGTCP      = TcpLinkMessage<>, 
      typename TSHAREDDATA  = TcpSessionSharedData<TMSGTCP, TcpLinkPool<TMSGTCP, CPPCORE_NETSERVER_BUFFERCOUNT_TCP>>,
      typename TQUEUETCPIN  = TcpLinkQueueIn<TMSGTCP, CPPCORE_NETSERVER_QUEUESIZE_TCP_IN>,
      typename TQUEUETCPOUT = TcpLinkQueueIn<TMSGTCP, CPPCORE_NETSERVER_QUEUESIZE_TCP_OUT>,
      typename TNETLINK     = TcpLink<TMSGTCP, typename TSHAREDDATA::POOLTCP, TQUEUETCPIN, TQUEUETCPOUT>>
   class CPPCORE_ALIGN16 TcpSession :
      public TNETLINK::Callback
   {
   public:
      using MSGTCP      = TMSGTCP;
      using SHAREDDATA  = TSHAREDDATA;
      using QUEUETCPIN  = TQUEUETCPIN;
      using QUEUETCPOUT = TQUEUETCPOUT;
      using NETLINK     = TNETLINK;
      using TCPSESSION  = TcpSession;

      /// <summary>
      /// TcpSession Callback
      /// </summary>
      class Callback
      {
      public:
         /// <summary>
         /// Raised if new tcp message is available on a session.
         /// Executed on message handler.
         /// </summary>
         INLINE virtual void onSessionMessageTcp(TcpSession& session, TMSGTCP& msg) { }

         /// <summary>
         /// Raised after client connection was accepted.
         /// Executed on connection handler.
         /// </summary>
         INLINE virtual void onSessionAccepted(TcpSession& session) { }

         /// <summary>
         /// Raised after disconnect of client or in case of connection error.
         /// Executed on connection handler.
         /// </summary>
         INLINE virtual void onSessionDisconnected(TcpSession& session) { }
      };

   protected:
      uint32_t           mID;
      CPPCORE_MUTEX_TYPE mMutexClose;
      CPPCORE_MUTEX_TYPE mMutexClearRead;
      CPPCORE_MUTEX_TYPE mMutexClearSend;
      Handler&           mApplication;
      Handler&           mThreadPool;
      Handler&           mMessageHandler;
      Logger&            mLogger;
      Callback&          mCallback;
      TSHAREDDATA&       mSharedData;
      TNETLINK           mTcpLink;
      Runnable           mRunnableOnRead;
      Runnable           mRunnableOnDisconnected;
      Runnable           mRunnableOnAccepted;
      Runnable           mRunnableWrite;
      Runnable           mRunnableDisconnectBlocked;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE TcpSession(
         uint32_t     id,
         Handler&     handlerMain,
         Handler&     handlerThreadPool,
         Handler&     handlerNewMessage,
         Logger&      logger,
         Callback&    callBack,
         TSHAREDDATA& sharedData) :
         mID(id),
         mApplication(handlerMain),
         mThreadPool(handlerThreadPool),
         mMessageHandler(handlerNewMessage),
         mLogger(logger),
         mCallback(callBack),
         mSharedData(sharedData),
         mTcpLink(sharedData.mPoolMessageTcp),
         mRunnableOnRead([this]() { runOnRead(); }),
         mRunnableOnDisconnected([this]() { runOnDisconnected(); }),
         mRunnableOnAccepted([this]() { runOnAccepted(); }),
         mRunnableWrite([this]() { runSendTcp(); }),
         mRunnableDisconnectBlocked([this]() { runDisconnectBlocked(); })
      {
         CPPCORE_MUTEX_INIT(mMutexClose);
         CPPCORE_MUTEX_INIT(mMutexClearRead);
         CPPCORE_MUTEX_INIT(mMutexClearSend);
      }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~TcpSession()
      {
         CPPCORE_MUTEX_DELETE(mMutexClose);
         CPPCORE_MUTEX_DELETE(mMutexClearRead);
         CPPCORE_MUTEX_DELETE(mMutexClearSend);
      }

   protected:
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////
      // RUNNABLES
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Runnable Code
      /// </summary>
      INLINE virtual void runOnRead()
      {
         while (TMSGTCP * msgtcp = mTcpLink.dequeue())
         {
            mCallback.onSessionMessageTcp(*this, *msgtcp);
            pushFreeTcp(msgtcp);
         }
      }

      /// <summary>
      /// Runnable Code
      /// </summary>
      INLINE void runOnDisconnected()
      {
         mCallback.onSessionDisconnected(*this); 
         this->clear();
      }

      /// <summary>
      /// Runnable Code
      /// </summary>
      INLINE void runOnAccepted()
      {
         mCallback.onSessionAccepted(*this);
      }

      /// <summary>
      /// Sends pending tcp messages from the according queue.
      /// </summary>
      INLINE void runSendTcp()
      {
         // lock
         CPPCORE_MUTEX_LOCK(mMutexClearSend);

         // only if session is active
         if (isActive())
            mTcpLink.send(*this);

         // unlock
         CPPCORE_MUTEX_UNLOCK(mMutexClearSend);
      }

      /// <summary>
      /// Runnable Code
      /// </summary>
      INLINE void runDisconnectBlocked()
      {
         logWarn("Disconnect (TCP OUT BLOCKED)"); 
         close();
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////
      // FOR HANDLING IN SUBCLASS
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// 
      /// </summary>
      INLINE virtual void onSessionClear() { }

      /// <summary>
      /// Raised when new session was accepted.
      /// </summary>
      INLINE virtual void onSessionAccepted() { }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TCPLINK SEND CALLBACKS
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////

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
         // log it
         logDebug("Sending blocked, starting disconnect timer");

         // schedule the disconnect of this session in case it does not recover
         mThreadPool.schedule(mRunnableDisconnectBlocked,
            ClockHR::now() + milliseconds(CPPCORE_NETSERVER_SENDSTUCKDISCTIME));
      }

      /// <summary>
      /// Raised by TcpLink in case of socket error.
      /// </summary>
      INLINE virtual void onSendError() override
      {
         logWarn("Disconnect (SOCKET ERROR SEND)");
         close();
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

      INLINE virtual bool onRecvCheckTcp(TMSGTCP& msg) override { return true; }

      INLINE virtual bool onRecvHandleTcp(TMSGTCP& msg) override { return true; }

      INLINE virtual void onRecvNewMessage() override
      { 
         mMessageHandler.schedule(mRunnableOnRead);
      }
      
      INLINE virtual void onRecvRegularDisconnect() override
      { 
         logDebug("Disconnect (REGULAR)");
         close();
      }
      
      INLINE virtual void onRecvErrorNoFreeTcpBuffer() override
      {
         logError("Disconnect (NO TCP BUFFER)");
         close();
      }
      
      INLINE virtual void onRecvErrorLengthMismatch()  override
      {
         logWarn("Disconnect (LEN MISMATCH)");
         close();
      }

      INLINE virtual void onRecvErrorTcpMsgOversized() override
      {
         logWarn("Disconnect (TCP-MSG OVERSIZED)");
         close();
      }

      INLINE virtual void onRecvErrorSocket() override
      {
         logWarn("Disconnect (SOCKET ERROR RECV)");
         close();
      }

      INLINE virtual void onRecvErrorTcpInQueueFull() override
      {
         logWarn("Disconnect (TCP-IN QUEUE FULL)");
         close();
      }

      INLINE virtual void onRecvErrorCrc() override
      {
         logWarn("Disconnect (CRC ERROR)");
         close();
      }

      INLINE virtual void onRecvErrorLength() override
      {
         logWarn("Disconnect (LEN ERROR)");
         close();
      }

   public:
      /// <summary>
      /// Get unique ID of this TCP session
      /// </summary>
      INLINE uint32_t getId() const { return mID; }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TCPLINK
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// The TcpSocket of this TcpSession
      /// </summary>
      INLINE TcpSocket& getSocket() { return mTcpLink.getSocket(); }

      /// <summary>
      /// The OS socket handle
      /// </summary>
      INLINE SOCKET getSocketOS() { return mTcpLink.getSocketOS(); }

      /// <summary>
      /// IPv6 address of the connected client.
      /// </summary>
      INLINE const sockaddr_in6& getAddress() const { return mTcpLink.getAddress(); }

      /// <summary>
      /// IPv6 address of connected client as string.
      /// </summary>
      INLINE const char* getAddressString() const { return mTcpLink.getAddressString(); }

      /// <summary>
      /// Received bytes on the TcpLink since session was accepted.
      /// </summary>
      INLINE const uint64_t& getBytesReceived() const { return mTcpLink.getBytesReceived(); }

      /// <summary>
      /// Sent bytes on the the TcpLink since the session was accepted.
      /// </summary>
      INLINE const uint64_t& getBytesSent() const { return mTcpLink.getBytesSent(); }

      /// <summary>
      /// When this session was accepted.
      /// </summary>
      INLINE const TimePoint& getStartTime() const { return mTcpLink.getStartTime(); }

      /// <summary>
      /// Elapsed time since this session was accepted.
      /// </summary>
      INLINE const Duration& getDuration() const { return mTcpLink.getDuration(); }

      /// <summary>
      /// Last time some tcp data was received for this session
      /// </summary>
      INLINE const TimePointHR& getLastReceiveTcp() const { return mTcpLink.getLastReceive(); }

      /// <summary>
      /// Last time some tcp data was sent for this session
      /// </summary>
      INLINE const TimePointHR& getLastSendTcp() const { return mTcpLink.getLastSend(); }

      /// <summary>
      /// True if the session is in use (socket is not closed).
      /// </summary>
      INLINE bool isUsed() const { return mTcpLink.isUsed(); }

      /// <summary>
      /// True if the socket is shutting down but still in use.
      /// </summary>
      INLINE bool isClosing() const { return mTcpLink.isClosing(); }

      /// <summary>
      /// True if the session is active (= used and not closing).
      /// </summary>
      INLINE bool isActive() const { return isUsed() && !isClosing(); }

      /// <summary>
      /// True if TcpLink is in blocked send state.
      /// </summary>
      INLINE bool isBlockedSend() const { return mTcpLink.isSendBlocked(); }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TCP POOL
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Pushes a free tcp message back to the pool.
      /// </summary>
      INLINE bool pushFreeTcp(TMSGTCP* buffer) { return mSharedData.mPoolMessageTcp.pushBack(buffer); }

      /// <summary>
      /// Pops a free tcp message from the pool.
      /// </summary>
      INLINE TMSGTCP* popFreeTcp() { TMSGTCP* msg; return mSharedData.mPoolMessageTcp.popBack(msg) ? msg : 0; }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // LOG HELPERS
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Helper function to create a session related log entry
      /// </summary>
      INLINE void log(const string& msg, const Logger::Type type = Logger::Type::Info)
      {
         stringstream s;
         s <<
            "SSN:" << ::std::setw(3) << ::std::setfill('0') << ::std::to_string(this->getId()) <<
            "|SOCK:" << ::std::setw(4) << ::std::setfill('0') << ::std::to_string(mTcpLink.getSocketOS()) <<
            "||" << msg;

         mLogger.log(s.str(), Logger::Channel::Network, type);
      }

      /// <summary>
      /// Create error log for this session
      /// </summary>
      INLINE void logError(const string& message) { this->log(message, Logger::Type::Error); }

      /// <summary>
      /// Create warning log for this session
      /// </summary>
      INLINE void logWarn(const string& message)  { this->log(message, Logger::Type::Warning); }

      /// <summary>
      /// Create debug log for this session
      /// </summary>
      INLINE void logDebug(const string& message) { this->log(message, Logger::Type::Debug); }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Calls accept on the provided Socket and stores the returned
      /// client socket in this session. Activates the session.
      /// The pendant is clear()
      /// </summary>
      INLINE bool acceptFrom(TcpSocket &s)
      {
         if (mTcpLink.acceptFrom(s))
         {
            this->onSessionAccepted();                    // raise callback in subclass (same workthread)
            mApplication.schedule(mRunnableOnAccepted); // raise callback on connection handler
            return true;
         }
         else
            return false;
      }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Finally clears a session which was closed before. The pendant is acceptFrom().
      /// Will be automatically triggered when calling close().
      /// </summary>
      INLINE virtual void clear()
      {
         // use a separated lock for sender and reader
         // so they don't block each other but only with this
         CPPCORE_MUTEX_LOCK(mMutexClearRead);
         CPPCORE_MUTEX_LOCK(mMutexClearSend);

         // reset parser of session
         mTcpLink.close();

         // let subclass do some clear
         this->onSessionClear();

         // unlock
         CPPCORE_MUTEX_UNLOCK(mMutexClearRead);
         CPPCORE_MUTEX_UNLOCK(mMutexClearSend);
      }

      /// <summary>
      /// If not yet set as closing, will set session as closing.
      /// Closes the socket and triggers a disconnect event.
      /// Can be called from any thread (Reader/Sender/Main)
      /// </summary>
      INLINE void close()
      {
         // lock
         CPPCORE_MUTEX_LOCK(mMutexClose);

         // cancel possible pending stalled disconnect runnable
         mThreadPool.cancel(mRunnableDisconnectBlocked);

         // only if not yet set to closing
         if (!mTcpLink.isClosing())
         {
            // make log
            logDebug("Closing socket/session");

            // close link immediately but clear/reset in runnable
            // or session may be reused immediately
            mTcpLink.shutdown();

            // raise callback in mainthread
            mApplication.schedule(mRunnableOnDisconnected);
         }
         else 
            logDebug("Tried to close an already closing session");

         // unlock
         CPPCORE_MUTEX_UNLOCK(mMutexClose);
      }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SEND/RECV | ENQUEUE/DEQUEUE
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Processes this session based on pollfd info
      /// </summary>
      INLINE void recvPendingTcp(pollfd& pollfd)
      {
         // lock
         CPPCORE_MUTEX_LOCK(mMutexClearRead);

         // only if session is active
         if (isActive())
         {
            // receive available tcp data from winsock
            if ((pollfd.revents & POLLIN) || (pollfd.revents & POLLHUP) || (pollfd.revents & POLLERR))
            {
               mTcpLink.receive(*this);
            }

            // schedule sending of outgoing tcpdata after block
            if (pollfd.revents & POLLOUT)
            {
               if (mTcpLink.isSendBlocked())
               {
                  logDebug("Sending unblocked, stopping disconnect timer");
                  mThreadPool.cancel(mRunnableDisconnectBlocked);
                  mThreadPool.schedule(mRunnableWrite);
               }
            }
         }

         // unlock
         CPPCORE_MUTEX_UNLOCK(mMutexClearRead);
      }

      /// <summary>
      /// Call this to send TCP messages to the client.
      /// Can be called from any thread.
      /// Don't touch message anymore once called.
      /// </summary>
      INLINE bool sendTcp(TMSGTCP* message)
      {
         // send msg to active session only
         if (isActive())
         {
            // try to enqueue it to the TCP link
            if (mTcpLink.enqueue(message))
               return mThreadPool.schedule(mRunnableWrite);

            // queue is full, disconnect client
            else
            {
               logWarn("Disconnect (TCP-OUT QUEUE FULL)");
               close();
               pushFreeTcp(message);
               return false;
            }
         }

         // tried to send a msg to non active session
         else
         {
            logDebug("Tried to send tcp message to inactive session");
            pushFreeTcp(message);
            return false;
         }
      }
   };
}
