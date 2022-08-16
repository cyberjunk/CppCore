#pragma once

#include <CppCore/Root.h>
#include <CppCore/Memory.h>

namespace CppCore
{
   /// <summary>
   /// Fixed size memory buffer with 16-byte alignment.
   /// Keep SIZE a multiple of 16.
   /// </summary>
   template<size_t SIZE = 8192U, bool ZEROMEM = false>
   class CPPCORE_ALIGN16 Buffer
   {
   protected:
      const static size_t N128 = SIZE >> 4U;
      const static size_t N64  = SIZE >> 5U;
      const static size_t N32  = SIZE >> 6U;
      union {
         struct {
            union {
               struct {
                  CPPCORE_ALIGN8 size_t mLength;         // length in 32/64 bit but aligned to 64
                  CPPCORE_ALIGN8 size_t mLengthRead;     // length read in 32/64 bit but aligned to 64
               };
            #if defined(CPPCORE_CPUFEAT_SSE2)
               CPPCORE_ALIGN16 __m128i mLengthSSE;       // both length as single SSE word
            #endif
            };
            union {
               CPPCORE_ALIGN16 char     mData[SIZE];     // data in 8-bit words
               CPPCORE_ALIGN16 uint32_t mData32[N32];    // data in 32-bit words
               CPPCORE_ALIGN16 uint64_t mData64[N64];    // data in 64-bit words
            #if defined(CPPCORE_CPUFEAT_SSE2)
               CPPCORE_ALIGN16 __m128i  mDataSSE[N128];  // data in 128-bit words
            #endif
            };
         };
      #if defined(CPPCORE_CPUFEAT_SSE2)
         CPPCORE_ALIGN16 __m128i mSSE[N128+1];           // both length + data in SSE words
      #endif
      };

   public:

      /// <summary>
      /// Total number of bytes that can be stored in this Buffer class.
      /// </summary>
      static INLINE size_t getSize() { return SIZE; }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE size_t getLength()        const           { return mLength;                                       }
      INLINE size_t getLengthRead()    const           { return mLengthRead;                                   }
      INLINE size_t getRemaining()     const           { return SIZE - mLength;                                }
      INLINE size_t getRemainingRead() const           { return mLength - mLengthRead;                         }
      INLINE char*  getPtr()                           { return &mData[0];                                     }
      INLINE char*  getPtrRead()                       { return &mData[mLengthRead];                           }
      INLINE char*  getPtrRemaining()                  { return &mData[mLength];                               }
      INLINE void   setLength(const size_t length)     { mLength = (length <= SIZE) ? length : SIZE;           }
      INLINE void   setLengthRead(const size_t length) { mLengthRead = (length <= mLength) ? length : mLength; }
      INLINE void*  operator new   (const size_t size) { return CPPCORE_ALIGNED_ALLOC(size, 16U);              }
      INLINE void*  operator new[] (const size_t size) { return CPPCORE_ALIGNED_ALLOC(size, 16U);              }
      INLINE void   operator delete   (void* ptr)      { return CPPCORE_ALIGNED_FREE(ptr);                     }
      INLINE void   operator delete[] (void* ptr)      { return CPPCORE_ALIGNED_FREE(ptr);                     }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Default Constructor
      /// </summary>
      INLINE Buffer()
      {
      #if defined(CPPCORE_CPUFEAT_SSE2)
         if (ZEROMEM) Memory::streamclear128x1(&mSSE, 16U + SIZE);
         else         Memory::streamclear128x1(&mLengthSSE, 16U);
      #else
         mLength     = 0U;
         mLengthRead = 0U;
       #if defined(CPPCORE_CPU_64BIT)
         if (ZEROMEM) Memory::clear64(mData64, N64);
       #else
         if (ZEROMEM) Memory::clear32(mData32, N32);
       #endif
      #endif
      }

      /// <summary>
      /// Copy Constructor
      /// </summary>
      INLINE Buffer(const Buffer& other)
      {
         CPPCORE_ASSERT_MULTIPLE16(SIZE);
      #if defined(CPPCORE_CPUFEAT_SSE2)
         Memory::streamcopy128x1(mSSE, other.mSSE, 16U + other.mLength);
      #else
         mLength     = other.mLength;
         mLengthRead = other.mLengthRead;
         Memory::copy(mData, other.mData, other.mLength);
      #endif
      }

      /// <summary>
      /// Set length to 0 (and maybe clear data).
      /// </summary>
      INLINE void clear()
      {
      #if defined(CPPCORE_CPUFEAT_SSE2)
         if (ZEROMEM) Memory::streamclear128x1(&mSSE, 16U + mLength);
         else         Memory::streamclear128x1(&mLengthSSE, 16U);
      #else
         mLength     = 0U;
         mLengthRead = 0U;
       #if defined(CPPCORE_CPU_64BIT)
         if (ZEROMEM) Memory::clear64(mData64, N64);
       #else
         if (ZEROMEM) Memory::clear32(mData32, N32);
       #endif
      #endif
      }

      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// References a specific typed value from custom index.
      /// This is a reference, hence changing the reference
      /// changes the underlying bytes in the buffer.
      /// </summary>
      template<typename T>
      INLINE T& ref(const size_t index)
      {
         return *((T*)&mData[index]);
      }

      /// <summary>
      /// Like other variant, but constant.
      /// </summary>
      template<typename T>
      INLINE const T& ref(const size_t index) const
      {
         return *((T*)&mData[index]);
      }

      /// <summary>
      /// References a specific typed value at current read index.
      /// This is a reference, hence changing the reference
      /// changes the underlying bytes in the buffer.
      /// </summary>
      template<typename T>
      INLINE T& refRead()
      {
         return *((T*)&mData[mLengthRead]);
      }

      /// <summary>
      /// Like other variant, but constant.
      /// </summary>
      template<typename T>
      INLINE const T& refRead() const
      {
         return *((T*)&mData[mLengthRead]);
      }

      /// <summary>
      /// References a specific typed value at current write index.
      /// This is a reference, hence changing the reference
      /// changes the underlying bytes in the buffer.
      /// </summary>
      template<typename T>
      INLINE T& refWrite()
      {
         return *((T*)&mData[mLength]);
      }

      /// <summary>
      /// Like other variant, but constant.
      /// </summary>
      template<typename T>
      INLINE const T& refWrite() const
      {
         return *((T*)&mData[mLength]);
      }

      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Writes generic data to custom index.
      /// Does not touch current length. Uses memcpy().
      /// </summary>
      template<bool CHECK = true>
      INLINE bool writeData(const char* data, const size_t length, const size_t index)
      {
         const bool OK = !CHECK || index + length <= SIZE;
         if (OK) memcpy(&mData[index], data, length);
         return OK;
      }

      /// <summary>
      /// Writes generic data to next free index.
      /// Increments length by length param.
      /// </summary>
      template<bool CHECK = true>
      INLINE bool writeData(const char* data, const size_t length)
      {
         const bool OK = writeData<CHECK>(data, length, mLength);
         if (OK) mLength += length;
         return OK;
      }

      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Reads generic data from custom index.
      /// Does not touch current length. Uses memcpy().
      /// </summary>
      template<bool CHECK = true>
      INLINE bool readData(char* data, const size_t length, const size_t index) const
      {
         const bool OK = !CHECK || index + length <= SIZE;
         if (OK) memcpy(data, &mData[index], length);
         return OK;
      }

      /// <summary>
      /// Reads generic data from current read index.
      /// Increments read index by length param.
      /// </summary>
      template<bool CHECK = true>
      INLINE bool readData(char* data, const size_t length)
      {
         const bool OK = readData<CHECK>(data, length, mLengthRead);
         if (OK) mLengthRead += length;
         return OK;
      }

      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Write a specific typed value to custom index.
      /// Does not touch current length.
      /// </summary>
      template<typename T, bool CHECK = true> 
      INLINE bool write(const T& data, const size_t index)
      {
         const bool OK = !CHECK || index + sizeof(T) <= SIZE;
         if (OK) *((T*)&mData[index]) = data;
         return OK;
      }

      /// <summary>
      /// Writes a specific typed value to next free index.
      /// Increments length by sizeof(T)
      /// </summary>
      template<typename T, bool CHECK = true>
      INLINE bool write(const T& data)
      {
         const bool OK = write<T, CHECK>(data, mLength);
         if (OK) mLength += sizeof(T);
         return OK;
      }

      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Read a specific typed value from custom index.
      /// Does not touch current read index.
      /// </summary>
      template<typename T, bool CHECK = true>
      INLINE bool read(T& data, const size_t index) const
      {
         const bool OK = !CHECK || index + sizeof(T) <= SIZE;
         if (OK) data = *((T*)&mData[index]);
         return OK;
      }

      /// <summary>
      /// Reads a specific typed value from current read index.
      /// Increments read index by sizeof(T)
      /// </summary>
      template<typename T, bool CHECK = true>
      INLINE bool read(T& data)
      {
         const bool OK = read<T, CHECK>(data, mLengthRead);
         if (OK) mLengthRead += sizeof(T);
         return OK;
      }
   };
}
