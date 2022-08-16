#pragma once

#include <CppCore/Root.h>
#include <CppCore/Network/Message.h>
#include <CppCore/Example/Model.h>

namespace CppCore { namespace Example 
{
   /// <summary>
   /// Example Messages
   /// </summary>
   class Message 
   {
   public:
      /// <summary>
      /// Example Message Types
      /// </summary>
      class Type
      {
      public:
         /// <summary>
         /// 
         /// </summary>
         enum uint8_t
         {
            PING_TCP  = 1,
            PONG_TCP  = 2,
            PING_UDP  = 3,
            PONG_UDP  = 4,
            EPOCH     = 5,
            SESSIONID = 6,
            PAYLOAD   = 7
         };
      };

      /// <summary>
      /// Example Headers
      /// </summary>
      class Header
      {
      public:
#pragma pack (push, 1)
         /// <summary>
         /// Example Tcp Header
         /// </summary>
         struct Tcp
         {
            uint16_t len1;
            uint16_t crc;
            uint16_t len2;
            uint8_t  epoch;

            /// <summary>
            /// Mandatory: Length of body from header
            /// </summary>
            INLINE size_t length() const { return len1; }

            /// <summary>
            /// Mandatory: True if length is ok.
            /// </summary>
            INLINE bool lengthok() const { return len1 == len2; }
         };

         /// <summary>
         /// Example Udp Header
         /// </summary>
         struct Udp
         {
            uint32_t sessionid;
            uint32_t seqno;
            uint16_t crc;
            uint8_t  epoch;
         };
#pragma pack(pop)
      };

      /// <summary>
      /// Example Base Message
      /// </summary>
      template<typename THEADER, size_t TSIZE>
      class Base : public CppCore::Message<THEADER, TSIZE>
      {
      public:
         INLINE bool writeString(const StdString& str)
         {
            const uint16_t LEN = (uint16_t)str.length();
            return 
               this->write(LEN) &&
               this->writeData(str.c_str(), LEN);
         }
         INLINE bool readString(StdString& str)
         {
            uint16_t len; 
            if (this->read(len) && this->mLengthRead + len <= TSIZE)
            {
               str.assign(&this->mData[this->mLengthRead], len);
               this->mLengthRead += len;
               return true;
            }
            else
               return false;
         }
         ////////////////////////////////////////////////////////////////////////////////////////////////
         INLINE bool writeModel(const Model& data)
         {
            return
               this->write(data.getId()) &&
               this->writeString(data.getName());
         }
         INLINE bool writeModels(const Model* data, const uint16_t len)
         {
            if (this->write(len))
            {
               for (uint16_t i = 0; i < len; i++)
               {
                  if (!writeModel(data[i]))
                     return false;
               }
               return true;
            }
            else 
               return false;
         }
         INLINE bool readModel(Model& data)
         {
            return
               this->read(data.refId()) &&
               this->readString(data.refName());
         }
         ////////////////////////////////////////////////////////////////////////////////////////////////
         INLINE void createPingTcp()
         {
            this->prepareWrite();
            this->setType(Type::PING_TCP);
         }
         INLINE void createPongTcp()
         {
            this->prepareWrite();
            this->setType(Type::PONG_TCP);
         }
         INLINE void createPingUdp()
         {
            this->prepareWrite();
            this->setType(Type::PING_UDP);
         }
         INLINE void createPongUdp()
         {
            this->prepareWrite();
            this->setType(Type::PONG_UDP);
         }
         INLINE void createEpoch()
         {
            this->prepareWrite();
            this->setType(Type::EPOCH);
         }
         INLINE void createSessionId(const uint32_t sessionId)
         {
            this->prepareWrite();
            this->setType(Type::SESSIONID);
            this->write(sessionId);
         }
         INLINE void createPayload(const uint8_t val1, const uint16_t val2, const uint32_t val3, const StdString& val4, const Model* val5, const uint16_t val5len)
         {
            this->prepareWrite();
            this->setType(Type::PAYLOAD);
            this->write(val1);
            this->write(val2);
            this->write(val3);
            this->writeString(val4);
            this->writeModels(val5, val5len);
         }
         INLINE void createPayloadBroken()
         {
            // for testing purposes, creates parse error
            this->prepareWrite();
            this->setType(Type::PAYLOAD);
            this->write((uint32_t)457457456);
            this->write((uint32_t)377645746);
            this->write((uint32_t)265345346);
            this->write((uint32_t)156456543);
            this->write((uint32_t)346346456);
         }
      };

      /// <summary>
      /// Example Tcp Message
      /// </summary>
      class Tcp : public Base<Header::Tcp, CPPCORE_BUFFERSIZE_TCP>
      {
      public:
      };

      /// <summary>
      /// Example Udp Message
      /// </summary>
      class Udp : public Base<Header::Udp, CPPCORE_BUFFERSIZE_UDP>
      {
      public:
         /// <summary>
         /// 
         /// </summary>
         INLINE uint32_t getHeaderSessionIndex() const { return getHeader().sessionid; }

         /// <summary>
         /// 
         /// </summary>
         INLINE uint32_t getHeaderSequenceNumber() const { return getHeader().seqno; }
      };
   };
}}
