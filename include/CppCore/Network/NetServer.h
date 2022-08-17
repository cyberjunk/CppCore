#pragma once

#include <CppCore/Root.h>
#include <CppCore/Network/TcpServer.h>
#include <CppCore/Network/NetSession.h>

namespace CppCore
{
   /// <summary>
   /// NetServer
   /// </summary>
   template<
      typename TMSGTCP, 
      typename TMSGUDP, 
      typename TSHAREDDATA  = NetSessionSharedData<TMSGTCP, TMSGUDP>,
      typename TSESSION     = NetSession<TMSGTCP, TMSGUDP, TSHAREDDATA>,
      typename TPOOLSESSION = TcpSessionPool<TSESSION, CPPCORE_NETSERVER_MAXCLIENTS>,
      typename TPOLLSESSION = Array::Fix::ST<TSESSION*, CPPCORE_NETSERVER_MAXCLIENTS>,
      typename TPOOLUDP     = Pool::Fix::MT<TMSGUDP, CPPCORE_NETSERVER_BUFFERCOUNT_UDP>>
   class NetServer : public TcpServer<TMSGTCP, TSHAREDDATA, TSESSION, TPOOLSESSION, TPOLLSESSION>
   {
   public:
      /// <summary>
      /// Base Class
      /// </summary>
      using Base = TcpServer<TMSGTCP, TSHAREDDATA, TSESSION, TPOOLSESSION, TPOLLSESSION>;

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
         INLINE virtual void onSessionMessageUdp(TSESSION& session, TMSGUDP& msg) { }
      };

   protected:
      Socket   mSocketUdp;
      Runnable mRunnablePollUdp;

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////
      // RUNNABLES
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Polls the shared UDP socket and reads pending data if any.
      /// </summary>
      INLINE void runPollUdp(const int timeout = 16)
      {
         // < 0 error || = 0 timeout || > 0 new udp datagram
         const int r = mSocketUdp.poll(POLLIN, timeout);
         
         if (r <= 0)
         {
            if (r < 0)
               this->logDebug("Error polling UDP socket");

            return;
         }

         // size of message header
         const size_t LENHEAD = TMSGUDP::getHeaderSize();

         // current udp message
         TMSGUDP* msg = NULL;

         // looper on pending udp datagrams
         while (true)
         {
            sockaddr_in6 senderaddr;
            socklen_t lplen = sizeof(senderaddr);
 
            // continue OR try to get a new udp messagebuffer
            // if none is available just return (TODO: kick random client?)
            if (!msg && !this->mSharedData.mPoolMessageUdp.popBack(msg))
               return;

            // try to read next udp datagram
            // unlike tcp, udp is 1 udp = 1 message
            // so it's always written to data start
            const int rc = mSocketUdp.recvfrom(
               msg->getPtr(), (int)msg->getSize(), 0, (sockaddr*)&senderaddr, &lplen);

            // a new datagram was read
            if (rc > 0)
            {
               // too short, not even a header
               if ((size_t)rc < LENHEAD)
               {
                  this->logDebug("UDP with less than header length");
                  continue; // reuse msg next loop
               }

               // set new length of messagebuffer
               msg->setLength((size_t)rc);

               // invalid session id
               const size_t SESSIONIDX = msg->getHeaderSessionIndex();
               if (SESSIONIDX >= CPPCORE_NETSERVER_MAXCLIENTS)
               {
                  this->logDebug("UDP Invalid SessionIndex");
                  continue; // reuse msg next loop
               }

               // receive udp into session (if true reset msg, otherwise reuse)
               if (this->mSessions[SESSIONIDX].recvUdp(*msg, senderaddr))
                  msg = NULL;
            }

            // no more udp datagram was read
            else
            {
               // due to an error
               if (rc < 0)
               {
                  if (!Socket::Op::isLastErrorBlock())
                     this->logDebug("UDP read socket error");
               }

               // add unused buffer to free ones again
               this->mSharedData.mPoolMessageUdp.pushBack(msg);

               // break out of udp read loop
               break;
            }
         }
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////
      // NETSESSION CALLBACK
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Executed on message handler on udp message from client.
      /// </summary>
      INLINE virtual void onSessionMessageUdp(typename TSESSION::NETSESSION& session, TMSGUDP& msg) override
      {
         dynamic_cast<Callback&>(this->mCallback).onSessionMessageUdp(dynamic_cast<TSESSION&>(session), msg);
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE NetServer(
         uint16_t  port,
         Handler&  handler,
         Handler&  threadPool,
         Handler&  messageHandler,
         Logger&   logger,
         Callback& callBack,
         const DurationHR& timeoutReceive = seconds(5)) :
         Base(port, handler, threadPool, messageHandler, logger, callBack, timeoutReceive),
         mSocketUdp(),
         mRunnablePollUdp([this]() { runPollUdp(); }, true, milliseconds(0))
      {
         // create udp socket
         this->log("Creating UDP socket and binding to port " + std::to_string(this->mPort));
         mSocketUdp.setSocket(Socket::Op::socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP));
         if (mSocketUdp.getSocket() == INVALID_SOCKET)
            this->logError("Failed to create udp socket.");

         // set udp socket options
         if (!mSocketUdp.setNoBlock(true))
             this->logError("Failed to enable FIONBIO (noblock) on udp socket.");

         if (!mSocketUdp.setOptionIPv6Only(false))
             this->logError("Failed to disable IPV6_V6ONLY on udp socket.");

         // bind udp socket
         if (SOCKET_ERROR == mSocketUdp.bind((sockaddr*)&this->mSocketTcp.getAddress(), sizeof(this->mSocketTcp.getAddress())))
             this->logError("Failed to bind udp socket.");

         // schedule udp polling
         this->mThreadPool.schedule(mRunnablePollUdp);
      }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~NetServer()
      {
         // disable udp poll and cancel it
         mRunnablePollUdp.setRepeat(false);
         this->mThreadPool.cancel(mRunnablePollUdp);
      }
   };
}
