#pragma once

#include <CppCore/Root.h>
#include <CppCore/Buffer.h>
#include <CppCore/Network/TcpSocket.h>
#include <CppCore/Containers/Pool.h>
#include <CppCore/Containers/Queue.h>

#ifndef CPPCORE_TCPLINK_DEFAULT_BUFFERCOUNT_TCP
#define CPPCORE_TCPLINK_DEFAULT_BUFFERCOUNT_TCP 1024
#endif

#ifndef CPPCORE_TCPLINK_DEFAULT_QUEUESIZE_TCP_IN
#define CPPCORE_TCPLINK_DEFAULT_QUEUESIZE_TCP_IN 64
#endif

#ifndef CPPCORE_TCPLINK_DEFAULT_QUEUESIZE_TCP_OUT
#define CPPCORE_TCPLINK_DEFAULT_QUEUESIZE_TCP_OUT 64
#endif

namespace CppCore
{
   /// <summary>
   /// Default Message Type if not specified. 
   /// This is just a plain TCP segment buffer.
   /// </summary>
   template<size_t SIZE = CPPCORE_BUFFERSIZE_TCP>
   using TcpLinkMessage = Buffer<SIZE, false>;

   /// <summary>
   /// Default Pool Type if not specified.
   /// </summary>
   template<
      typename TMSGTCP = TcpLinkMessage<>,
      size_t   SIZE    = CPPCORE_TCPLINK_DEFAULT_BUFFERCOUNT_TCP>
   using TcpLinkPool = Pool::Fix::MT<TMSGTCP, SIZE>;

   /// <summary>
   /// Default Queue-In Type if not specified.
   /// </summary>
   template<
      typename TMSGTCP = TcpLinkMessage<>,
      size_t   SIZE    = CPPCORE_TCPLINK_DEFAULT_QUEUESIZE_TCP_IN>
   using TcpLinkQueueIn = Queue::MT<TMSGTCP*, SIZE>;

   /// <summary>
   /// Default Queue-Out Type if not specified.
   /// </summary>
   template<
      typename TMSGTCP = TcpLinkMessage<>,
      size_t    SIZE   = CPPCORE_TCPLINK_DEFAULT_QUEUESIZE_TCP_OUT>
   using TcpLinkQueueOut = Queue::MT<TMSGTCP*, SIZE>;

   //////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// TcpLink
   /// </summary>
   template<
      typename TMSGTCP     = TcpLinkMessage<>,
      typename TPOOL       = TcpLinkPool<TMSGTCP>,
      typename TQUEUEREAD  = TcpLinkQueueIn<TMSGTCP>,
      typename TQUEUEWRITE = TcpLinkQueueOut<TMSGTCP>>
   class TcpLink
   {
   public:
      using MSGTCP     = TMSGTCP;
      using POOL       = TPOOL;
      using QUEUEREAD  = TQUEUEREAD;
      using QUEUEWRITE = TQUEUEWRITE;

      /// <summary>
      /// TcpLink Callback
      /// </summary>
      class Callback
      {
      public:
         INLINE virtual void onSendCheckTcpFailed(TMSGTCP& msg) { }
         INLINE virtual void onSendFinalizeTcp(TMSGTCP& msg) { }
         INLINE virtual void onSendDataTransmitted(uint32_t bytes) { }
         INLINE virtual void onSendBlocked() { }
         INLINE virtual void onSendError() { }

         INLINE virtual bool onRecvCheckTcp(TMSGTCP& msg) { return true; }
         INLINE virtual bool onRecvHandleTcp(TMSGTCP& msg) { return true; }
         INLINE virtual void onRecvNewMessage() { }
         INLINE virtual void onRecvRegularDisconnect() { }
         INLINE virtual void onRecvErrorNoFreeTcpBuffer() { }
         INLINE virtual void onRecvErrorLengthMismatch() { }
         INLINE virtual void onRecvErrorTcpMsgOversized() { }
         INLINE virtual void onRecvErrorSocket() { }
         INLINE virtual void onRecvErrorTcpInQueueFull() { }
         INLINE virtual void onRecvErrorCrc() { }
         INLINE virtual void onRecvErrorLength() { }
      };

   protected:
      TcpSocket   mSocket;
      TPOOL&      mPoolMessageTcp;
      TQUEUEREAD  mMessagesRecv;
      TQUEUEWRITE mMessagesSend;
      TMSGTCP*    mCurrentMessageIn;
      TMSGTCP*    mCurrentMessageOut;
      uint64_t    mBytesReceived;
      uint64_t    mBytesSent;
      TimePoint   mStartTime;
      TimePointHR mLastReceive;
      TimePointHR mLastSend;
      bool        mIsClosing;
      bool        mSendBlocked;

      /// <summary>
      /// Allow subclasses to check outgoing msg before it is actually sent.
      /// Returning false will prevent the msg from being sent and instead
      /// raises an onSendCheckTcpFailed() on the callback.
      /// </summary>
      INLINE virtual bool onSendCheckTcp(TMSGTCP& msg) const { return true; }

      /// <summary>
      /// Overwrite with a check whether a message is complete or still has to be finished.
      /// Since this base class operates on raw tcp segments, they are alway finished if not empty.
      /// </summary>
      INLINE virtual bool isMessageComplete(TMSGTCP& msg) const { return msg.getLength() != 0; }

      /// <summary>
      /// TCP segments have no header. It is complete if the segment isn't empty.
      /// </summary>
      INLINE virtual bool isHeaderComplete(TMSGTCP& msg) const { return msg.getLength() != 0; }

      /// <summary>
      /// TCP segments have no header. Return is always true.
      /// </summary>
      INLINE virtual bool isHeaderOK(TMSGTCP& msg) const { return true; }

      /// <summary>
      /// Return how many more bytes must be read before msg is finished.
      /// Since this base class operates on raw tcp segments, 
      /// it just returns the remaining size in buffer.
      /// </summary>
      INLINE virtual size_t getMissingLength(TMSGTCP& msg) const { return msg.getRemaining(); }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE TcpLink(TPOOL& poolMessageTcp) :
         mSocket(),
         mPoolMessageTcp(poolMessageTcp),
         mMessagesRecv(),
         mMessagesSend(),
         mCurrentMessageIn(NULL),
         mCurrentMessageOut(NULL),
         mBytesReceived(0),
         mBytesSent(0),
         mStartTime(Duration::zero()),
         mLastReceive(DurationHR::zero()),
         mLastSend(DurationHR::zero()),
         mIsClosing(false),
         mSendBlocked(false) { }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~TcpLink()
      {
         if (mCurrentMessageIn)
            mPoolMessageTcp.pushBack(mCurrentMessageIn);

         if (mCurrentMessageOut)
            mPoolMessageTcp.pushBack(mCurrentMessageOut);
      }

      /// <summary>
      /// TcpSocket used in this TcpLink
      /// </summary>
      INLINE TcpSocket& getSocket() { return mSocket; }

      /// <summary>
      /// Operating System Socket Handle
      /// </summary>
      INLINE SOCKET getSocketOS() { return mSocket.getSocket(); }

      /// <summary>
      /// Bytes received on TcpSocket
      /// </summary>
      INLINE const uint64_t&  getBytesReceived() const { return mBytesReceived; }

      /// <summary>
      /// Bytes sent on TcpSocket
      /// </summary>
      INLINE const uint64_t&  getBytesSent() const { return mBytesSent; }

      /// <summary>
      /// When the TcpLink was connected (client) or accepted (server).
      /// </summary>
      INLINE const TimePoint& getStartTime() const { return mStartTime; }

      /// <summary>
      /// Elapsed time since successfully connected (client) or accepted (server).
      /// </summary>
      INLINE const Duration& getDuration() const { return Clock::now() - mStartTime; }

      /// <summary>
      /// Last time when data was succesfully read from the socket.
      /// </summary>
      INLINE const TimePointHR& getLastReceive() const { return mLastReceive; }

      /// <summary>
      /// Elapsed time since some data was successfully read from the socket.
      /// </summary>
      INLINE const DurationHR& getLastReceiveDuration() const { return ClockHR::now() - mLastReceive; }

      /// <summary>
      /// Last time when data was sucessfully written to the socket.
      /// </summary>
      INLINE const TimePointHR& getLastSend() const { return mLastSend; }

      /// <summary>
      /// Elapsed time since some data was successfully written to the socket.
      /// </summary>
      INLINE const DurationHR& getLastSendDuration() const { return ClockHR::now() - mLastSend; }

      /// <summary>
      /// True if shutdown() has been called, but not yet reset().
      /// </summary>
      INLINE bool isClosing() const { return mIsClosing; }

      /// <summary>
      /// True if TcpLink is in send blocked state.
      /// </summary>
      INLINE bool isSendBlocked() const { return mSendBlocked; }

      /////////////////////////////////////////////////////////////////////////////////////////////////
      // TCPSOCKET
      /////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns currently linked IPv6 address of this TcpLink
      /// </summary>
      INLINE const sockaddr_in6& getAddress() const { return mSocket.getAddress(); }

      /// <summary>
      /// Returns currently linked IPv6 address of this TcpLink as string.
      /// </summary>
      INLINE const char* getAddressString() const { return mSocket.getAddressString(); }

      /// <summary>
      /// Returns true if the parameter address matches the endpoint of this tcp link.
      /// </summary>
      INLINE bool isEndpoint(const sockaddr_in6& address) const
      {
         return mSocket.isEndpoint(address);
      }

      /// <summary>
      /// True if socket is in use
      /// </summary>
      INLINE bool isUsed() const { return mSocket.isUsed(); }

      /// <summary>
      /// Accepts a pending incoming TCP connection from a listenerSocket
      /// and assigns the accepted socket to this instance.
      /// </summary>
      INLINE bool acceptFrom(TcpSocket& listenerSocket)
      {
         if (mSocket.acceptFrom(listenerSocket))
         {
            mStartTime = Clock::now();
            mLastReceive = mLastSend = ClockHR::now();
            return true;
         }
         else
            return false;
      }

      /// <summary>
      /// Tries to connect the TcpLink to the specitifed host and TCP port.
      /// Blocks until successfully connected, error occured or specified timeout reached.
      /// </summary>
      INLINE TcpSocket::ConnectReturn connect(
         const char* host, 
         const char* port, 
         const int   timeout   = TcpSocket::ConnectDefaults::TIMEOUT,
         const bool  nodelay   = TcpSocket::ConnectDefaults::NODELAY,
         const bool  reuseaddr = TcpSocket::ConnectDefaults::REUSEADDR,
         const bool  linger    = TcpSocket::ConnectDefaults::LINGER,
         const int   ltime     = TcpSocket::ConnectDefaults::LTIME,
         const bool  keepalive = TcpSocket::ConnectDefaults::KEEPALIVE)
      {
         const TcpSocket::ConnectReturn CR = 
            mSocket.connect(host, port, timeout, nodelay, reuseaddr, linger, keepalive);

         if (CR == TcpSocket::ConnectReturn::OK)
         {
            mStartTime = Clock::now();
            mLastReceive = mLastSend = ClockHR::now();
         }

         return CR;
      }

      /// <summary>
      /// Starts graceful FIN/FIN-ACK end of TCP connection.
      /// You must still call close() afterwards.
      /// </summary>
      INLINE void shutdown()
      {
         mIsClosing = true;
         mSocket.shutdown();
      }

      /// <summary>
      /// Closes the socket.
      /// </summary>
      INLINE void close()
      {
         TMSGTCP* buftcp;

         if (!mIsClosing)
            shutdown();

         // todo: do final recv/send here for FIN/FIN-ACK ?
         mSocket.close();

         while (mMessagesRecv.popFront(buftcp))
            mPoolMessageTcp.pushBack(buftcp);

         while (mMessagesSend.popFront(buftcp))
            mPoolMessageTcp.pushBack(buftcp);

         if (mCurrentMessageIn)
         {
            mPoolMessageTcp.pushBack(mCurrentMessageIn);
            mCurrentMessageIn = NULL;
         }
         
         if (mCurrentMessageOut)
         {
            mPoolMessageTcp.pushBack(mCurrentMessageOut);
            mCurrentMessageOut = NULL;
         }

         mBytesReceived = 0;
         mBytesSent = 0;
         mStartTime = TimePoint(Duration::zero());
         mLastReceive = TimePointHR(DurationHR::zero());
         mLastSend = TimePointHR(DurationHR::zero());
         mIsClosing = false;
         mSendBlocked = false;
      }

      /// <summary>
      /// Polls the socket for up to timeout using events and returns revents.
      /// </summary>
      INLINE uint16_t poll(const uint16_t events = POLLIN | POLLOUT, const int timeout = 16)
      {
         // poll
         auto revents = mSocket.poll(events, timeout);

         // recover from send block
         if (revents & POLLOUT)
            mSendBlocked = false;

         // return revents
         return revents;
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////
      // ENQUEUE/DEQUEUE
      /////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Enqueues a TMSGTCP to be sent to the endpoint of this TcpLink.
      /// </summary>
      INLINE bool enqueue(TMSGTCP* buffer) 
      {
         return mMessagesSend.pushBack(buffer);
      }

      /// <summary>
      /// Dequeues a received TMSGTCP from the endpoint of this TcpLink.
      /// </summary>
      INLINE bool dequeue(TMSGTCP*& buffer) 
      { 
         return mMessagesRecv.popFront(buffer);
      }

      /// <summary>
      /// Dequeues a received TMSGTCP from the endpoint of this TcpLink.
      /// Returns NULL if none available.
      /// </summary>
      INLINE TMSGTCP* dequeue()
      {
         TMSGTCP* msg = 0;
         mMessagesRecv.popFront(msg);
         return msg;
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////
      // SEND/RECV
      /////////////////////////////////////////////////////////////////////////////////////////////////

   public:
      /// <summary>
      /// Writes all enqueued message buffers to the tcp socket.
      /// </summary>
      INLINE virtual void send(Callback& cb)
      {
         // sender loop
         while (true)
         {
            // if we're sendindg a new message and don't continue
            if (!mCurrentMessageOut)
            {
               // try to get a new message to send
               if (mMessagesSend.popFront(mCurrentMessageOut))
               {
                  // reset the read length 
                  mCurrentMessageOut->setLengthRead(0);

                  // let subclasses do a final check whether to send or not
                  if (!onSendCheckTcp(*mCurrentMessageOut))
                  {
                     cb.onSendCheckTcpFailed(*mCurrentMessageOut);
                     mPoolMessageTcp.pushBack(mCurrentMessageOut);
                     mCurrentMessageOut = NULL;
                     continue;
                  }

                  // let callback finish (e.g. header/crc) 
                  // this msg before it finally goes out
                  cb.onSendFinalizeTcp(*mCurrentMessageOut);
               }

               // done: nothing to send
               else
                  return;
            }

            //________________________________________________________________//
            // see if done

            const size_t LENLEFT = mCurrentMessageOut->getRemainingRead();
            const size_t LENREAD = mCurrentMessageOut->getLengthRead();

            // nothing more to send for this message
            if (LENLEFT == 0)
            {
               // add current to free buffers again
               mPoolMessageTcp.pushBack(mCurrentMessageOut);
               mCurrentMessageOut = NULL;

               // process possible next pending message
               continue;
            }

            //________________________________________________________________//
            // send

            // try to send what's left to send
            const int rc = mSocket.send(
               mCurrentMessageOut->getPtrRead(), (int)LENLEFT);

            // some data was sent, update read (sent) length and loop again
            if (rc > 0)
            {
               mSendBlocked = false;
               mBytesSent += rc;
               mLastSend = ClockHR::now();
               mCurrentMessageOut->setLengthRead(LENREAD + rc);
               cb.onSendDataTransmitted((uint32_t)rc);
            }

            // nothing was sent (afaik send does not return 0 anyways?)
            else if (rc == 0)
            {
               break;
            }

            // nothing sent due to error
            else
            {
               // because the socket is blocked
               // note: this means the whole winsock buffer (~8kb) has been filled
               // without the client ACKing anything sent from it so far.
               // this should not happen under normal circumstances and likely
               // means the client is either dead, horribly lagged 
               // or not receiving anything on purpose (to attack the server)
               if (Socket::Op::isLastErrorBlock()) {
                  mSendBlocked = true;
                  cb.onSendBlocked();
               }

               // because of other error
               else
               {
                  cb.onSendError();
                  mPoolMessageTcp.pushBack(mCurrentMessageOut);
                  mCurrentMessageOut = NULL;
               }

               // nothing more to do, either dead or notified
               break;
            }
         }
      }

      /// <summary>
      /// Reads all pending bytes from the socket into message buffers 
      /// and enqueues complete ones.
      /// </summary>
      INLINE virtual void receive(Callback& cb)
      {
         // reader loop:
         // usually exits due to EWOULDBLOCK on the recv() call
         // because no more data is available
         while (true)
         {
            // try to get a new tcp messagebuffer
            if (!mCurrentMessageIn)
            {
               if (mPoolMessageTcp.popBack(mCurrentMessageIn))
                  mCurrentMessageIn->setLength(0);
               else
               {
                  cb.onRecvErrorNoFreeTcpBuffer();
                  return;
               }
            }

            // message not complete
            if (!isMessageComplete(*mCurrentMessageIn))
            {
               size_t lenLeft = getMissingLength(*mCurrentMessageIn);
               assert(lenLeft != 0);

               // too large for max message size
               if (lenLeft > mCurrentMessageIn->getRemaining())
               {
                  cb.onRecvErrorTcpMsgOversized();
                  mPoolMessageTcp.pushBack(mCurrentMessageIn);
                  mCurrentMessageIn = NULL;
                  return;
               }

               // more data to read for this message
               else if (lenLeft > 0)
               {
                  const int rc = mSocket.recv(
                     mCurrentMessageIn->getPtrRemaining(),
                     (int)lenLeft);

                  // at least some new data was read
                  if (rc > 0)
                  {
                     mCurrentMessageIn->setLength(
                        mCurrentMessageIn->getLength() + (size_t)rc);

                     // raise received counter and save clock tick
                     mBytesReceived += rc;
                     mLastReceive = ClockHR::now();

                     // check if header is available
                     if (isHeaderComplete(*mCurrentMessageIn))
                     {
                        // and validate it
                        if (!isHeaderOK(*mCurrentMessageIn))
                        {
                           cb.onRecvErrorLengthMismatch();
                           mPoolMessageTcp.pushBack(mCurrentMessageIn);
                           mCurrentMessageIn = NULL;
                           return;
                        }
                     }

                     continue;
                  }

                  // graceful disconnect
                  else if (rc == 0) CPPCORE_UNLIKELY
                  {
                     cb.onRecvRegularDisconnect();
                     mPoolMessageTcp.pushBack(mCurrentMessageIn);
                     mCurrentMessageIn = NULL;
                     return;
                  }

                  // error or EWOULDBLOCK (=nothing more to read)
                  else
                  {
                     // anything but block or shutdown error will be considered an error
                     // e.g. close on WSAECONNRESET, WSAENOBUFS, ..
                     if (!Socket::Op::isLastErrorBlock() && !Socket::Op::isLastErrorShutdown())
                     {
                        cb.onRecvErrorSocket();
                        mPoolMessageTcp.pushBack(mCurrentMessageIn);
                        mCurrentMessageIn = NULL;
                        return;
                     }

                     // break out of reader loop for EWOULDBLOCK
                     // and come back later when more data is available
                     return;
                  }
               }
            }

            // message complete
            else
            {
               // reset read index for checks
               mCurrentMessageIn->setLengthRead(0);

               // allow callback to check some stuff, etc. valid crc
               if (!cb.onRecvCheckTcp(*mCurrentMessageIn)) CPPCORE_UNLIKELY
               {
                  cb.onRecvErrorCrc();
                  mPoolMessageTcp.pushBack(mCurrentMessageIn);
                  mCurrentMessageIn = NULL;
                  return;
               }

               // last chance for callback to do some internal stuff
               if (!cb.onRecvHandleTcp(*mCurrentMessageIn)) CPPCORE_UNLIKELY
               {
                  mPoolMessageTcp.pushBack(mCurrentMessageIn);
                  mCurrentMessageIn = NULL;
                  continue;
               }

               // reset read index once more
               mCurrentMessageIn->setLengthRead(0);

               // try to enqueue it for processing, reset current one and loop again
               if (mMessagesRecv.pushBack(mCurrentMessageIn))
               {
                  cb.onRecvNewMessage();
                  mCurrentMessageIn = NULL;
                  continue;
               }

               // queue full
               else CPPCORE_UNLIKELY
               {
                  cb.onRecvErrorTcpInQueueFull();
                  mPoolMessageTcp.pushBack(mCurrentMessageIn);
                  mCurrentMessageIn = NULL;
                  return;
               }
            }
         }
      }
   };
}
