#pragma once

#include <CppCore/Root.h>
#include <CppCore/Network/TcpClient.h>
#include <CppCore/Network/NetLink.h>

#ifndef CPPCORE_NETCLIENT_BUFFERCOUNT_UDP
#define CPPCORE_NETCLIENT_BUFFERCOUNT_UDP    128
#endif
#ifndef CPPCORE_NETCLIENT_QUEUESIZE_UDP_OUT
#define CPPCORE_NETCLIENT_QUEUESIZE_UDP_OUT  128
#endif

namespace CppCore
{
   /// <summary>
   /// NetClient
   /// </summary>
   template<
      typename TMSGTCP, 
      typename TMSGUDP, 
      typename TPOOLTCP     = TcpLinkPool<TMSGTCP, CPPCORE_TCPCLIENT_BUFFERCOUNT_TCP>,
      typename TQUEUETCPIN  = TcpLinkQueueIn<TMSGTCP, CPPCORE_TCPCLIENT_QUEUESIZE_TCP_IN>,
      typename TQUEUETCPOUT = TcpLinkQueueOut<TMSGTCP, CPPCORE_TCPCLIENT_QUEUESIZE_TCP_OUT>,
      typename TPOOLUDP     = Pool::Fix::MT<TMSGUDP, CPPCORE_NETCLIENT_BUFFERCOUNT_UDP>,
      typename TQUEUEUDPOUT = Queue::MT<TMSGUDP*, CPPCORE_NETCLIENT_QUEUESIZE_UDP_OUT>>
   class NetClient : public TcpClient<
      TMSGTCP, 
      TPOOLTCP, 
      TQUEUETCPIN, 
      TQUEUETCPOUT, 
      NetLink<TMSGTCP, TPOOLTCP, TQUEUETCPIN, TQUEUETCPOUT>>
   {
   public:
      typedef NetLink<TMSGTCP, TPOOLTCP, TQUEUETCPIN, TQUEUETCPOUT> ClientNetLink;
      typedef TcpClient<TMSGTCP, TPOOLTCP, TQUEUETCPIN, TQUEUETCPOUT, ClientNetLink> Base;

      friend ClientNetLink;
      using Callback =  typename Base::Callback;

   protected:
      Socket       mSocketUdp;
      TPOOLUDP     mPoolMessageUdp;
      TQUEUEUDPOUT mMessagesUdp;

      /// <summary>
      /// 
      /// </summary>
      INLINE void sendSub() override
      {
         // UDP
         TMSGUDP* msg;
         while (mMessagesUdp.popFront(msg))
         {
            msg->setLengthRead(0);
            onSendFinalizeUdp(*msg);

            // check minimal length
            const size_t LENHEAD = TMSGUDP::getHeaderSize();
            const size_t LENMSG = msg->getLength();

            // only send if at least header length
            if (LENMSG >= LENHEAD)
            {
               // send the whole udp datagram
               const int rc = mSocketUdp.sendto(
                  msg->getPtr(), (int)LENMSG, 0, 
                  (sockaddr*)&this->mNetLink.getAddress(),
                  sizeof(this->mNetLink.getAddress()));

               // something went wrong
               if (rc != (int)LENMSG)
                  this->logWarn("Failed to send udp message");
            }
            else
               this->logWarn("Discarded udp message below headersize");

            // push msg back to free ones
            mPoolMessageUdp.pushBack(msg);
         }
      }

      /// <summary>
      /// 
      /// </summary>
      INLINE virtual void onSendFinalizeUdp(TMSGUDP& msg) { }

      /// <summary>
      /// Raised in TcpClient Base Class if connect() was successful.
      /// Runs on the worker thread that executed the connect().
      /// </summary>
      INLINE virtual void onConnected() override 
      {
         Base::onConnected();

         // create udp socket
         mSocketUdp.setSocket(Socket::Op::socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP));
         if (mSocketUdp.getSocket() == INVALID_SOCKET)
            this->logError("Failed to create udp socket.");

         // set udp socket options
         if (!mSocketUdp.setNoBlock(true))
            this->logError("Failed to enable FIONBIO (noblock) on udp socket.");

         if (!mSocketUdp.setOptionIPv6Only(false))
            this->logError("Failed to enable to IPv6 DS on udp socket.");
      }

      /// <summary>
      /// Raised in TcpClient Base Class in case of a disconnect.
      /// Runs on the worker thread that executed the connect().
      /// </summary>
      INLINE virtual void onDisconnected() override 
      {
         Base::onDisconnected();

         // close udp socket
         mSocketUdp.close();

         // push pending udp messages back to free ones
         TMSGUDP* msg;
         while (mMessagesUdp.popFront(msg))
            mPoolMessageUdp.pushBack(msg);
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE NetClient(
         Handler&  connectionHandler,
         Handler&  workloadHandler,
         Handler&  messageHandler,
         Logger&   logger,
         Callback& callBack) :
         Base(connectionHandler, workloadHandler, messageHandler, logger, callBack),
         mSocketUdp()
      {
      }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~NetClient()
      {
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // UDP POOL
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Pushes a free udp message back to the pool
      /// </summary>
      INLINE bool pushFreeUdp(TMSGUDP* msg) { return mPoolMessageUdp.pushBack(msg); }

      /// <summary>
      /// Pops a free udp message from the pool
      /// </summary>
      INLINE TMSGUDP* popFreeUdp() { TMSGUDP* msg; return mPoolMessageUdp.popBack(msg) ? msg : 0; }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SEND UDP
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Enqueues a UDP message for transmission to the server.
      /// Do not access the message afterwards.
      /// </summary>
      INLINE bool sendUdp(TMSGUDP* message)
      {
         // can only send in connected state
         if (this->mConnectionState != Base::ConnectionState::Connected)
         {
            mPoolMessageUdp.pushBack(message);
            return false;
         }

         // try to enqueue the udp message for sending
         if (!mMessagesUdp.pushBack(message))
         {
            this->logWarn("Disconnect (UDP-OUT QUEUE FULL)");
            this->disconnect();
            mPoolMessageUdp.pushBack(message);
            return false;
         }

         // try schedule the send task on the threadpool
         // false just means it's scheduled already...
         const bool OK = this->mHandlerWorkload.schedule(this->mRunnableSend);

         // success
         return true;
      }
   };
}
