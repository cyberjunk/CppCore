#pragma once

#include <CppCore/Root.h>
#include <CppCore/Hash/Murmur3.h>

namespace CppCore
{
   /// <summary>
   /// Hasher
   /// </summary>
   class Hasher
   {
   private:
      INLINE Hasher() { }
   public:
      /// <summary>
      /// Murmur3
      /// </summary>
      class Murmur3
      {
      private:
         INLINE Murmur3() { }
      public:
         template<typename KEY>
         class Generic
         {
         private:
            INLINE Generic() { }
         public:
            INLINE static bool hash(const KEY& a, uint32_t& b)
            {
               b = 0;
               return CppCore::Murmur3::hashMem(&a, sizeof(KEY), b);
            }
         };
         class UInt32
         {
         private:
            INLINE UInt32() { }
         public:
            INLINE static bool hash(const uint32_t& a, uint32_t& b)
            {
               b = 0;
               CppCore::Murmur3::hashUInt32(a, b);
               return true;
            }
         };
         class UInt64
         {
         private:
            INLINE UInt64() { }
         public:
            INLINE static bool hash(const uint64_t& a, uint32_t& b)
            {
               b = 0;
               return CppCore::Murmur3::hashMem(&a, sizeof(uint64_t), b);
            }
         };
         class String
         {
         private:
            INLINE String() { }
         public:
            INLINE static bool hash(const StdString& a, uint32_t& b)
            {
               b = 0;
               return CppCore::Murmur3::hashMem(a.data(), (uint32_t)a.length(), b);
            }
         };
      };
   };
}
