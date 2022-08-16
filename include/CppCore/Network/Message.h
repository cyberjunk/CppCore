#pragma once

#include <CppCore/Root.h>
#include <CppCore/Buffer.h>
#include <CppCore/Network/Essential.h>

namespace CppCore
{
   /// <summary>
   /// Message Base Classes for TCP and UDP with a fixed size header THEADER and a fixed max message size of TSIZE bytes.
   /// You must derive from this class, see CppCore/Example/Network.h
   /// </summary>
   template<typename THEADER, size_t TSIZE>
   class Message : public Buffer<TSIZE, false>
   {
   protected:
      /// <summary>
      /// Constructor.
      /// </summary>
      INLINE Message() { }

   public:
      static INLINE size_t getHeaderSize() { return sizeof(THEADER);                   }
      static INLINE size_t getIndexType()  { return sizeof(THEADER);                   }
      static INLINE size_t getIndexBody()  { return sizeof(THEADER);                   }
      static INLINE size_t getIndexData()  { return sizeof(THEADER) + sizeof(uint8_t); }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // Message Type

      /// <summary>
      /// Gets a refernce to the message type stored at fixed index.
      /// </summary>
      INLINE uint8_t& getType() 
      { 
         return this->template Buffer<TSIZE, false>::template ref<uint8_t>(getIndexType());
      }

      /// <summary>
      /// Gets a const reference to the message type stored at fixed index.
      /// </summary>
      INLINE const uint8_t& getType() const
      { 
         return this->template Buffer<TSIZE, false>::template ref<uint8_t>(getIndexType());
      }

      /// <summary>
      /// Sets the message type stored at fixed index.
      /// </summary>
      INLINE void setType(const uint8_t type) { getType() = type; }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // Header Related

      /// <summary>
      /// Returns modifyable reference to the fixed size header in the message.
      /// </summary>
      INLINE THEADER& getHeader() { return this->template Buffer<TSIZE, false>::template ref<THEADER>(0); }

      /// <summary>
      /// Returns const reference to the fixed size header in the message.
      /// </summary>
      INLINE const THEADER& getHeader() const { return this->template Buffer<TSIZE, false>::template ref<THEADER>(0); }

      /// <summary>
      /// True if all of the fixed size header is available
      /// </summary>
      INLINE bool hasCompleteHeader() const { return this->getLength() >= getHeaderSize(); }

      /// <summary>
      /// The number of bytes still missing to complete the fixed size header or 0 if the header is complete.
      /// </summary>
      INLINE size_t getMissingHeaderLength() const { return hasCompleteHeader() ? 0 : getHeaderSize() - this->getLength(); }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // Body Related

      /// <summary>
      /// True if the fixed size header is available and proposed body length in it exactly matches length in buffer.
      /// The message is complete and can be processed now.
      /// </summary>
      INLINE bool isComplete() const 
      { 
         return hasCompleteHeader() && this->getLength() == getHeaderSize() + getHeader().length();
      }

      /// <summary>
      /// True if the fixed size header is available and current message body is already
      /// larger than proposed length in it. This should not happen with a proper parser...
      /// </summary>
      INLINE bool isOverComplete() const
      {
         return hasCompleteHeader() && this->getLength() > getHeaderSize() + getHeader().length();
      }

      /// <summary>
      /// Returns bytes still
      /// </summary>
      INLINE size_t getMissingBodyLength() const
      {
         const size_t s = getHeaderSize() + getHeader().length();
         return (!hasCompleteHeader() || this->getLength() >= s) ? 
            0 : s - this->getLength();
      }

      /// <summary>
      /// Returns the current length of the message body (includes type and data)
      /// </summary>
      INLINE size_t getLengthBody() const { return this->getLength() > getIndexBody() ? this->getLength() - getIndexBody() : 0; }

      /// <summary>
      /// Returns the current length of the message data (includes only data, no type)
      /// </summary>
      INLINE size_t getLengthData() const { return this->getLength() > getIndexData() ? this->getLength() - getIndexData() : 0; }

      /// <summary>
      /// Returns a pointer to the beginning of data
      /// </summary>
      INLINE char* getPtrData() { return &this->mData[getIndexData()]; }

      /// <summary>
      /// Returns a pointer to the beginning of body
      /// </summary>
      INLINE char* getPtrBody() { return &this->mData[getIndexBody()]; }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // Prepare

      INLINE void prepareRecv()  { this->mLength     = 0;              } // before writing to it on socket recv
      INLINE void prepareSend()  { this->mLengthRead = 0;              } // before reading from it on socket send
      INLINE void prepareWrite() { this->mLength     = getIndexData(); } // before writing data values to it
      INLINE void prepareRead()  { this->mLengthRead = getIndexData(); } // before reading data values from it

      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // Buffer Method Overwrites

      /// <summary>
      /// References a specific typed value from custom index in message data.
      /// This is a reference, hence changing the reference
      /// changes the underlying bytes in the buffer.
      /// </summary>
      template<typename T>
      INLINE T& ref(const size_t index = 0)
      {
         return Buffer<TSIZE, false>::template ref<T>(getIndexData() + index);
      }

      /// <summary>
      /// 
      /// </summary>
      template<typename T>
      INLINE const T& ref(const size_t index = 0) const
      {
         return Buffer<TSIZE, false>::template ref<T>(getIndexData() + index);
      }

      /// <summary>
      /// Writes generic data to custom index.
      /// Does not touch current length. Uses memcpy().
      /// </summary>
      template<bool CHECK = true>
      INLINE bool writeData(const char* data, const size_t length, const size_t index)
      {
         return Buffer<TSIZE, false>::template writeData<CHECK>(data, length, getIndexData() + index);
      }

      /// <summary>
      /// Writes generic data to next free index.
      /// Increments length by length param.
      /// </summary>
      template<bool CHECK = true>
      INLINE bool writeData(const char* data, const size_t length)
      {
         return Buffer<TSIZE, false>::template writeData<CHECK>(data, length);
      }

      /// <summary>
      /// Reads generic data from custom index.
      /// Does not touch current length. Uses memcpy().
      /// </summary>
      template<bool CHECK = true>
      INLINE bool readData(const char* data, const size_t length, const size_t index) const
      {
         return Buffer<TSIZE, false>::template readData<CHECK>(data, length, getIndexData() + index);
      }

      /// <summary>
      /// Reads generic data from current read index.
      /// Increments read index by length param.
      /// </summary>
      template<bool CHECK = true>
      INLINE bool readData(const char* data, const size_t length)
      {
         return Buffer<TSIZE, false>::template readData<CHECK>(data, length);
      }

      /// <summary>
      /// Write a specific typed value to custom index.
      /// Does not touch current length.
      /// </summary>
      template<typename T, bool CHECK = true>
      INLINE bool write(const T& data, const size_t index)
      {
         return Buffer<TSIZE, false>::template write<T, CHECK>(data, getIndexData() + index);
      }

      /// <summary>
      /// Writes a specific typed value to next free index.
      /// Increments length by sizeof(T)
      /// </summary>
      template<typename T, bool CHECK = true>
      INLINE bool write(const T& data)
      {
         return Buffer<TSIZE, false>::template write<T, CHECK>(data);
      }

      /// <summary>
      /// Read a specific typed value from custom index.
      /// Does not touch current read index.
      /// </summary>
      template<typename T, bool CHECK = true>
      INLINE bool read(T& data, const size_t index) const
      {
         return Buffer<TSIZE, false>::template read<T, CHECK>(data, getIndexData() + index);
      }

      /// <summary>
      /// Reads a specific typed value from current read index.
      /// Increments read index by sizeof(T)
      /// </summary>
      template<typename T, bool CHECK = true>
      INLINE bool read(T& data)
      {
         return Buffer<TSIZE, false>::template read<T, CHECK>(data);
      }
   };
}
