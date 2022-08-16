#pragma once

#include <CppCore/Root.h>
#include <CppCore/Network/TcpSession.h>
#include <CppCore/Network/NetLink.h>

namespace CppCore
{
   /// <summary>
   /// Shared Data between all sessions and server.
   /// </summary>
   template<
      typename TMSGTCP  = TcpLinkMessage<>, 
      typename TMSGUDP  = Buffer<CPPCORE_BUFFERSIZE_UDP, false>,
      typename TPOOLTCP = TcpLinkPool<TMSGTCP, CPPCORE_NETSERVER_BUFFERCOUNT_TCP>,
      typename TPOOLUDP = Pool::Fix::MT<TMSGUDP, CPPCORE_NETSERVER_BUFFERCOUNT_UDP>>
   class NetSessionSharedData : public TcpSessionSharedData<TMSGTCP, TPOOLTCP>
   {
   public:
      TPOOLUDP mPoolMessageUdp;

      INLINE NetSessionSharedData() : TcpSessionSharedData<TMSGTCP, TPOOLTCP>() { }
   };

   /// <summary>
   /// NetSession
   /// </summary>
   template<
      typename TMSGTCP      = TcpLinkMessage<>, 
      typename TMSGUDP      = Buffer<CPPCORE_BUFFERSIZE_UDP, false>,
      typename TSHAREDDATA  = NetSessionSharedData<TMSGTCP, TMSGUDP, 
         TcpLinkPool<TMSGTCP, CPPCORE_NETSERVER_BUFFERCOUNT_TCP>, 
         Pool::Fix::MT<TMSGUDP, CPPCORE_NETSERVER_BUFFERCOUNT_UDP>>,
      typename TQUEUETCPIN  = TcpLinkQueueIn<TMSGTCP, CPPCORE_NETSERVER_QUEUESIZE_TCP_IN>,
      typename TQUEUETCPOUT = TcpLinkQueueIn<TMSGTCP, CPPCORE_NETSERVER_QUEUESIZE_TCP_OUT>,
      typename TQUEUEUDPIN  = Queue::MT<TMSGUDP*, CPPCORE_NETSERVER_QUEUESIZE_UDP_IN>>
   class NetSession : public TcpSession<
      TMSGTCP,
      TSHAREDDATA,
      TQUEUETCPIN,
      TQUEUETCPOUT,
      NetLink<TMSGTCP, typename TSHAREDDATA::POOLTCP, TQUEUETCPIN, TQUEUETCPOUT>>
   {
   public:
      /// <summary>
      /// TcpSession Base Class
      /// </summary>
      using Base = TcpSession<
         TMSGTCP, 
         TSHAREDDATA,
         TQUEUETCPIN, 
         TQUEUETCPOUT, 
         NetLink<TMSGTCP, typename TSHAREDDATA::POOLTCP, TQUEUETCPIN, TQUEUETCPOUT>>;

   public:
      using QUEUEUDPIN = TQUEUEUDPIN;
      using NETSESSION = NetSession;

      /// <summary>
      /// NetSession Callback
      /// </summary>
      class Callback : public Base::Callback
      {
      public:
         /// <summary>
         /// Raised if new udp message is available on a session.
         /// Executed on message handler.
         /// </summary>
         INLINE virtual void onSessionMessageUdp(NetSession& session, TMSGUDP& msg) { }
      };

   protected:
      TQUEUEUDPIN  mMessagesUdpToRead;
      StdTimePoint mLastReceiveUdp;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE NetSession(
         uint32_t     id,
         Handler&     handlerMain,
         Handler&     handlerThreadPool,
         Handler&     handlerMessage,
         Logger&      logger,
         Callback&    callBack,
         TSHAREDDATA& sharedData) :
         Base(id, 
            handlerMain, handlerThreadPool, 
            handlerMessage, logger, callBack, sharedData),
         mMessagesUdpToRead(),
         mLastReceiveUdp(StdSeconds(0)) { }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~NetSession() { }

   protected:
      /// <summary>
      /// For deriving classes to check Udp datagram.
      /// </summary>
      INLINE virtual bool onRecvCheckUdp(TMSGUDP& msg) { return true; }

      /// <summary>
      /// For deriving classes to handle Udp datagram.
      /// </summary>
      INLINE virtual bool onRecvHandleUdp(TMSGUDP& msg) { return true; }

      /// <summary>
      /// Raised when session should be cleared.
      /// </summary>
      INLINE virtual void onSessionClear() override
      {
         Base::onSessionClear();
         TMSGUDP* udp;
         while (mMessagesUdpToRead.popFront(udp))
            this->mSharedData.mPoolMessageUdp.pushBack(udp);
      }

      /// <summary>
      /// 
      /// </summary>
      INLINE virtual void runOnRead() override
      {
         // read tcp in base class
         Base::runOnRead();

         // our derived callback type
         Callback& cb = dynamic_cast<Callback&>(this->mCallback);

         // read all pending UDP messages
         TMSGUDP* msgudp;
         while (mMessagesUdpToRead.popFront(msgudp))
         {
            cb.onSessionMessageUdp(*this, *msgudp);
            this->mSharedData.mPoolMessageUdp.pushBack(msgudp);
         }
      }

   public:
      /// <summary>
      /// Returns last time a valid UDP datagram was receveid for this session
      /// </summary>
      INLINE const StdTimePoint& getLastReceiveUdp() const { return mLastReceiveUdp; }

      /// <summary>
      /// Receives a potential UDP datagram into this session.
      /// </summary>
      INLINE bool recvUdp(TMSGUDP& msg, sockaddr_in6& senderaddr)
      {
         // lock
         CPPCORE_MUTEX_LOCK(this->mMutexClearRead);

         // 1) session not active
         if (!this->isActive())
         {
            this->logDebug("UDP for inactive session");
            CPPCORE_MUTEX_UNLOCK(this->mMutexClearRead);
            return false;
         }

         // 2) not same IP as session belongs to
         if (!this->mTcpLink.isEndpoint(senderaddr))
         {
            this->logWarn("UDP with Session from other IP");
            CPPCORE_MUTEX_UNLOCK(this->mMutexClearRead);
            return false;
         }

         // 3) let subclass do its check
         if (!this->onRecvCheckUdp(msg))
         {
            CPPCORE_MUTEX_UNLOCK(this->mMutexClearRead);
            return false;
         }

         // 4) let subclass do its handling
         if (!this->onRecvHandleUdp(msg))
         {
            CPPCORE_MUTEX_UNLOCK(this->mMutexClearRead);
            return false;
         }

         // all good, enqueue it for processing
         if (mMessagesUdpToRead.pushBack(&msg))
         {
            mLastReceiveUdp = StdClock::now();
            CPPCORE_MUTEX_UNLOCK(this->mMutexClearRead);
            this->onRecvNewMessage();
            return true;
         }
         // queue overfilled, disconnect client
         else
         {
            CPPCORE_MUTEX_UNLOCK(this->mMutexClearRead);
            this->logWarn("Disconnect. UDP queue overfilled.");
            this->close();
            return false;
         }
      }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // UDP POOL
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Pushes a free udp message back to the pool.
      /// </summary>
      INLINE bool pushFreeUdp(TMSGUDP* msg) { return this->mSharedData.mPoolMessageUdp.pushBack(msg); }

      /// <summary>
      /// Pops a free udp message from the pool.
      /// </summary>
      INLINE TMSGUDP* popFreeUdp() { TMSGUDP* msg; return this->mSharedData.mPoolMessageUdp.popBack(msg) ? msg : 0; }
   };
}
