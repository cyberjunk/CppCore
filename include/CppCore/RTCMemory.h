#pragma once

#include <CppCore/Root.h>
#include <CppCore/Memory.h>

namespace CppCore
{
   /// <summary>
   /// A piece of (R)un-(T)ime (C)onstant Memory.
   /// SIZE must be a multiple of 64.
   /// </summary>
   template<size_t SIZE>
   class RTCMemory
   {
   private:
      static_assert(SIZE % 64 == 0);

   protected:
      CPPCORE_ALIGN64 char   mData[SIZE];
      CPPCORE_ALIGN16 size_t mLength;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE RTCMemory() : mLength(0)
      {
      #if defined(CPPCORE_CPUFEAT_SSE2)
         Memory::streamclear128x4(mData, SIZE);
      #else
         Memory::clear(mData, SIZE);
      #endif
      }

      /// <summary>
      /// Push some data to the run-time constant memory.
      /// Returns pointer to permanently stored data on success or null on fail.
      /// </summary>
      INLINE const void* push(const void* d, const size_t len)
      {
         const size_t free  = SIZE - mLength;
         const size_t len1  = len + 1U;
         const size_t len16 = CppCore::rupptwo(len1, (size_t)16U);
         if (free >= len16)
         {
            char* p = &mData[mLength];
            mLength += len16;
            Memory::copy(p, d, len);
            return p;
         }
         return 0;
      }

      /// <summary>
      /// Push a string with zero termination to the run-time constant memory.
      /// Returns pointer to permanently stored string on success or null on fail.
      /// </summary>
      INLINE const char* push(const char* s)
      {
         return (const char*)push(s, ::strlen(s));
      }

      /// <summary>
      /// Push any type T to the run-time constant memory.
      /// </summary>
      template<typename T>
      INLINE const T* push(const T& d)
      {
         return (const T*)push(&d, sizeof(T));
      }
   };
}
