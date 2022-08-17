#pragma once

#include <CppCore/Network/NetClient.h> // the base class
#include <CppCore/Example/Network.h>   // the example protocol
#include <CppCore/Hash/CRC32.h>        // CRC32

namespace CppCore { namespace Example 
{
   /// <summary>
   /// Example NetClient
   /// </summary>
   class NetClient : public CppCore::NetClient<Message::Tcp, Message::Udp>
   {
   public:
      /// <summary>
      /// Easy access to Base class
      /// </summary>
      using Base = CppCore::NetClient<Message::Tcp, Message::Udp>;

      /// <summary>
      /// Ping Timer Interval
      /// </summary>
      static constexpr milliseconds PINGINTERVAL = milliseconds(1000);

   protected:
      uint32_t     mSessionId;    // custom session id sent by server
      uint32_t     mSeqNumUdp;    // raised by one for each sent udp
      uint8_t      mEpoch;        // epoch sent by server
      TimePointHR  mPingSentTcp;  // last time we sent a tcp ping
      TimePointHR  mPingSentUdp;  // last time we sent a udp ping
      DurationHR   mRTT;          // last measures ping rtt
      Runnable     mRunnablePing; // ping timer

      ////////////////////////////////////////////////////////////////////////////////////
      // OVERRIDES ON BASE CLASS
      ////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Executed on workload handler after connection has been terminated.
      /// </summary>
      INLINE void onDisconnected() override
      {
         Base::onDisconnected();

         // cancel ping timer
         this->mHandlerWorkload.cancel(mRunnablePing);

         // reset values
         mSessionId = 0;
         mSeqNumUdp = 0;
         mEpoch = 0;
      }

      /// <summary>
      /// Executed on workload handler after connection has been established.
      /// </summary>
      INLINE void onConnected() override
      {
         Base::onConnected();

         // start ping timer
         this->mHandlerWorkload.schedule(
            mRunnablePing, 
            ClockHR::now() + mRunnablePing.getInterval());
      }

      /// <summary>
      /// Executed on workload handler and last chance to modify outgoing tcp message.
      /// </summary>
      INLINE void onSendFinalizeTcp(Message::Tcp& msg) override
      {
         Base::onSendFinalizeTcp(msg);

         // get body length
         const uint16_t BLEN = (uint16_t)msg.getLengthBody();

         // calculate crc on message body
         uint32_t crc32;
         CRC32::hashMem(msg.getPtrBody(), BLEN, &crc32);

         // get reference to message header
         Message::Header::Tcp& header = msg.getHeader();

         // set header values
         header.len1  = BLEN;
         header.crc   = (uint16_t)crc32;
         header.len2  = BLEN;
         header.epoch = mEpoch;
      }

      /// <summary>
      /// Executed on workload handler and last chance to modify outgoing udp message.
      /// </summary>
      INLINE void onSendFinalizeUdp(Message::Udp& msg) override
      {
         Base::onSendFinalizeUdp(msg);

         // calculate crc on message body
         uint32_t crc32;
         CRC32::hashMem(msg.getPtrBody(), msg.getLengthBody(), &crc32);

         // get reference to message header
         Message::Header::Udp& header = msg.getHeader();

         // set header values
         header.sessionid = mSessionId;
         header.seqno     = mSeqNumUdp++;
         header.crc       = (uint16_t)crc32;
         header.epoch     = mEpoch;
      }

      /// <summary>
      /// Executed on workload handler and first chance to check incoming message.
      /// Returning false will discard the message and disconnect from server.
      /// </summary>
      INLINE bool onRecvCheckTcp(Message::Tcp& msg) override
      {
         if (!Base::onRecvCheckTcp(msg))
            return false;

         // calculate crc
         uint32_t crc32;
         CRC32::hashMem(msg.getPtrBody(), (uint32_t)msg.getLengthBody(), &crc32);

         // check crc
         return msg.getHeader().crc == (uint16_t)crc32;
      }

      /// <summary>
      /// Executed on workload handler and last chance to handle incoming message.
      /// Afterwards the msg is in the queue for the real message handler 
      /// and must not be touched anymore in NetClient.
      /// </summary>
      INLINE bool onRecvHandleTcp(Message::Tcp& msg) override
      {
         if (!Base::onRecvHandleTcp(msg))
            return false;

         const uint8_t epochNew = msg.getHeader().epoch;
         const uint8_t epochOld = mEpoch;

         // update epoch
         if (epochNew != epochOld)
         {
            mEpoch = epochNew;
            this->logDebug("Received new server epoch");
         }

         // internally handle some messages
         switch (msg.getType())
         {
         case Message::Type::PONG_TCP:  return handlePongTcp(msg);
         case Message::Type::PONG_UDP:  return handlePongUdp(msg);
         case Message::Type::SESSIONID: return handleSessionId(msg);
         default: return true;
         }
      }

      ////////////////////////////////////////////////////////////////////////////////////
      // INTERNAL MESSAGE HANDLERS
      ////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Handle Message from Server internally.
      /// </summary>
      INLINE bool handlePongTcp(Message::Tcp& msg)
      {
         mRTT = ClockHR::now() - mPingSentTcp;
         this->logDebug("Received PONG_TCP from server: " + 
            ::std::to_string(mRTT.count()) + "ns");
         return true;
      }

      /// <summary>
      /// Handle Message from Server internally.
      /// </summary>
      INLINE bool handlePongUdp(Message::Tcp& msg)
      {
         this->logDebug("Received PONG_UDP from server");
         return true;
      }

      /// <summary>
      /// Handle Message from Server internally.
      /// </summary>
      INLINE bool handleSessionId(Message::Tcp& msg)
      {
         const uint32_t& ID = msg.ref<uint32_t>(0);
         mSessionId = ID;
         this->logDebug("Received SESSIONID from server: " + 
            ::std::to_string(ID));
         return true;
      }

      ////////////////////////////////////////////////////////////////////////////////////
      // RUNNABLES
      ////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Ping Runnable Timer
      /// </summary>
      INLINE void runPing()
      {
         sendPingUdp(); 
         sendPingTcp();
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE NetClient(
         Handler&  handlerMain,
         Handler&  handlerThreadPool,
         Handler&  handlerMessage,
         Logger&   logger,
         Callback& callBack) :
         Base(handlerMain, handlerThreadPool, handlerMessage, logger, callBack),
         mSessionId(0),
         mSeqNumUdp(0),
         mEpoch(0),
         mPingSentTcp(nanoseconds(0)),
         mPingSentUdp(nanoseconds(0)),
         mRTT(nanoseconds(0)),
         mRunnablePing([this]() { runPing(); }, true, PINGINTERVAL)
      {
      }

      /// <summary>
      /// Send Message to Server
      /// </summary>
      INLINE void sendPingTcp()
      {
         if (Message::Tcp* msg = this->popFreeTcp())
         {
            msg->createPingTcp();
            this->logDebug("Sending PING_TCP to server...");
            mPingSentTcp = ClockHR::now();
            this->sendTcp(msg);
         }

         // test
         //sendPayload();
      }

      /// <summary>
      /// Send Message to Server
      /// </summary>
      INLINE void sendPingUdp()
      {
         if (Message::Udp* msg = this->popFreeUdp())
         {
            msg->createPingUdp();
            this->logDebug("Sending PING_UDP to server... seq:" + 
               std::to_string(mSeqNumUdp));
            mPingSentUdp = ClockHR::now();
            this->sendUdp(msg);
         }
      }

      /// <summary>
      /// Send Message to Server
      /// </summary>
      INLINE void sendPayload()
      {
         Model model[2] { {1, "model1"}, {2, "model2"} };

         if (Message::Tcp* msg = this->popFreeTcp())
         {
            // testing real payload
            msg->createPayload(53, 5832, 35721324, 
               string("hello"), &model[0], 2);
            
            // testing broken payload
            //msg->createPayloadBroken();

            this->logDebug("Sending PAYLOAD to server...");
            this->sendTcp(msg);
         }
      }
   };
}}
