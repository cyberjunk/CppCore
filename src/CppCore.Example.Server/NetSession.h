#pragma once

#include <CppCore/Network/NetSession.h> // the base class
#include <CppCore/Example/Network.h>    // the example protocol
#include <CppCore/Hash/CRC32.h>         // CRC32

namespace CppCore { namespace Example 
{
   /// <summary>
   /// Shared Data between all sessions and server.
   /// </summary>
   class NetSessionSharedData : public CppCore::NetSessionSharedData<Message::Tcp, Message::Udp>
   {
   public:
      INLINE NetSessionSharedData() : mEpoch(0) { }
      uint8_t mEpoch;
   };

   /// <summary>
   /// Example NetSession
   /// </summary>
   class NetSession : public CppCore::NetSession<Message::Tcp, Message::Udp, NetSessionSharedData>
   {
   public:
      /// <summary>
      /// Base Class
      /// </summary>
      using Base = CppCore::NetSession<Message::Tcp, Message::Udp, NetSessionSharedData>;

   protected:
      size_t   mSeqNumUdp;

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CONNECTION
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Executed on ThreadPool during clear of session. Last chance to do custom clearing before
      /// session might get assigned to another client.
      /// </summary>
      INLINE void onSessionClear() override
      {
         Base::onSessionClear();
         mSeqNumUdp = 0;
      }

      /// <summary>
      /// Executed on ThreadPool when new session is accepted.
      /// </summary>
      INLINE void onSessionAccepted() override
      {
         Base::onSessionAccepted();
         sendSessionId();
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // UDP
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Executed on ThreadPool. First chance to modify incoming message.
      /// Returning false here will discard the message, but not disconnect the link.
      /// </summary>
      INLINE bool onRecvCheckUdp(Message::Udp& msg) override
      {
         // calculate crc
         uint32_t crc32;
         CRC32::hashMem(msg.getPtrBody(), (uint32_t)msg.getLengthBody(), &crc32);

         // check crc
         if (msg.getHeader().crc != (uint16_t)crc32)
         {
            this->logDebug("Discarding UDP with invalid crc");
            return false;
         }

         // out of sequence check
         const size_t SEQNORECV = msg.getHeader().seqno;
         const size_t SEQNOCUR = mSeqNumUdp;
         const size_t SEQNORECVNEXT = SEQNORECV + 1;

         // (1) < expected: late delivery/out-of-sequence
         // (2) > expected: package loss or forged seq number
         if (SEQNORECV < SEQNOCUR)
         {
            this->logDebug("Discarding out-of-sequence UDP message");
            return false;
         }
         else if (SEQNORECV > SEQNOCUR)
            this->logDebug("UDP loss or forged seq number detected");

         // write back incremented or increased seq number
         mSeqNumUdp = SEQNORECVNEXT;

         // check epoch
         if (msg.getHeader().epoch != mSharedData.mEpoch)
         {
            this->logDebug("Discarding UDP with invalid epoch");
            return false;
         }

         // all good
         return true;
      }

      /// <summary>
      /// Executed on ThreadPool. Last chance to modify or handle incoming message internally.
      /// Afterwards the msg is in the queue for the mainthread and must not be touched anymore in NetClient.
      /// Returning false will suppress the message for the mainthread, but not disconnect the link.
      /// </summary>
      INLINE bool onRecvHandleUdp(Message::Udp& msg) override
      {
         return handleMessage<Message::Udp>(msg);
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TCP
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Executed on ThreadPool. Last chance to modify outgoing message.
      /// </summary>
      INLINE void onSendFinalizeTcp(Message::Tcp& msg) override
      {
         Base::onSendFinalizeTcp(msg);

         // get body length
         const uint16_t BLEN = (uint16_t)msg.getLengthBody();

         // calculate crc
         uint32_t crc32;
         CRC32::hashMem(msg.getPtrBody(), BLEN, &crc32);

         // get reference to header
         Message::Header::Tcp& header = msg.getHeader();

         // set header values
         header.len1 = BLEN;
         header.crc = (uint16_t)crc32;
         header.len2 = BLEN;
         header.epoch = mSharedData.mEpoch;
      }

      /// <summary>
      /// Executed on ThreadPool. First chance to modify incoming message.
      /// Returning false will discard the message and disconnect the link.
      /// </summary>
      INLINE bool onRecvCheckTcp(Message::Tcp& msg) override
      {
         // calculate crc
         uint32_t crc32;
         CRC32::hashMem(msg.getPtrBody(), (uint32_t)msg.getLengthBody(), &crc32);

         // check crc
         if (msg.getHeader().crc != (uint16_t)crc32)
            return false;

         // all good
         return true;
      }

      /// <summary>
      /// Executed on ThreadPool. Last chance to modify or handle incoming message internally.
      /// Afterwards the msg is in the queue for the mainthread and must not be touched anymore in NetClient.
      /// Returning false will suppress the message for the mainthread, but not disconnect the link.
      /// </summary>
      INLINE bool onRecvHandleTcp(Message::Tcp& msg) override
      {
         // discard invalid epoch messages
         if (msg.getHeader().epoch != mSharedData.mEpoch)
         {
            this->logDebug("Discarded tcp message with invalid epoch");
            return false;
         }

         return handleMessage<Message::Tcp>(msg);
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // MESSAGE HANDLERS
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Handle some messages internally before the mainthread does. Executed on ThreadPool.
      /// Executed for every message, regardless whether tcp or udp.
      /// </summary>
      template<typename TMSG>
      INLINE bool handleMessage(TMSG& msg)
      {
         // internally handle some messages
         switch (msg.getType())
         {
         case Message::Type::PING_TCP: return handlePingTcp<TMSG>(msg);
         case Message::Type::PING_UDP: return handlePingUdp<TMSG>(msg);
         case Message::Type::PAYLOAD:  return handlePayload<TMSG>(msg);
         default:                      return true;
         }
      }

      template<typename TMSG>
      INLINE bool handlePingTcp(TMSG& msg)
      {
         sendPongTcp();
         return true;
      }

      template<typename TMSG>
      INLINE bool handlePingUdp(TMSG& msg)
      {
         sendPongUdp();
         return true;
      }

      template<typename TMSG>
      INLINE bool handlePayload(TMSG& msg)
      {
         // parse test

         uint8_t  val1;
         uint16_t val2;
         uint32_t val3;
         string   val4;
         Model    val5[16];
         uint16_t len;

         msg.prepareRead();

         if (!msg.read(val1)  ||
             !msg.read(val2) ||
             !msg.read(val3) ||
             !msg.readString(val4)     ||
             !msg.read(len))
         {
            this->log("Parser Error on PAYLOAD message", Logger::Type::Debug);
            return false;
         }

         for (uint16_t i = 0; i < len; i++)
         {
            if (!msg.readModel(val5[i]))
            {
               this->log("Parser Error on PAYLOAD message", Logger::Type::Debug);
               return false;
            }
         }

         return true;
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE NetSession(
         uint32_t  id,
         Handler&  handlerMain,
         Handler&  handlerThreadPool,
         Handler&  handlerMessage,
         Logger&   logger,
         Callback& callBack,
         NetSessionSharedData& sharedData) :
         mSeqNumUdp(0),
         Base(id, handlerMain, handlerThreadPool, 
            handlerMessage, logger, callBack, sharedData) { }

      /// <summary>
      /// Send Message to Client
      /// </summary>
      INLINE void sendPongTcp()
      {
         if (!this->isActive())
            return;

         if (Message::Tcp* msg = this->popFreeTcp())
         {
            msg->createPongTcp();
            this->sendTcp(msg);
         }
      }

      /// <summary>
      /// Send Message to Client
      /// </summary>
      INLINE void sendPongUdp()
      {
         if (!this->isActive())
            return;

         if (Message::Tcp* msg = this->popFreeTcp())
         {
            msg->createPongUdp();
            this->sendTcp(msg);
         }
      }

      /// <summary>
      /// Send Message to Client
      /// </summary>
      INLINE void sendEpoch()
      {
         if (!this->isActive())
            return;

         if (Message::Tcp* msg = this->popFreeTcp())
         {
            msg->createEpoch();
            this->sendTcp(msg);
         }
      }

      /// <summary>
      /// Send Message to Client
      /// </summary>
      INLINE void sendSessionId()
      {
         if (!this->isActive())
            return;

         if (Message::Tcp* msg = this->popFreeTcp())
         {
            msg->createSessionId(this->mID);
            this->sendTcp(msg);
         }
      }
   };
}}
