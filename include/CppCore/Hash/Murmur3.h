#pragma once

#include <CppCore/Root.h>
#include <CppCore/Hash/Hash.h>

namespace CppCore 
{
   /// <summary>
   /// Murmur3 Hash (32-Bit)
   /// </summary>
   class Murmur3 : public Hash
   {
   protected:
      uint32_t mLen;
      uint32_t mHash;

      INLINE static uint32_t mix32(uint32_t v)
      {
         v ^= v >> 16;
         v *= 0x85ebca6bU;
         v ^= v >> 13;
         v *= 0xc2b2ae35U;
         v ^= v >> 16;
         return v;
      }
      INLINE static uint32_t step32_part(const uint32_t h, uint32_t v)
      {
         v *= 0xcc9e2d51U;
         v  = CppCore::rotl32(v, 15U);
         v *= 0x1b873593U;
         v ^= h;
         return v;
      }
      INLINE static uint32_t step32_full(const uint32_t h, uint32_t v)
      {
         v = step32_part(h, v);
         v = CppCore::rotl32(v, 13U);
         v = (v * 5U) + 0xe6546b64U;
         return v;
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      /// <param name="seed">A previously hash to continue</param>
      INLINE Murmur3(uint32_t seed = 0)
      {
         reset(seed);
      }

      /// <summary>
      /// Resets the hash to the given seed
      /// </summary>
      /// <param name="seed"></param>
      INLINE void reset(uint32_t seed = 0)
      {
         mHash = seed;
         mLen = 0;
      }

      /// <summary>
      /// Compute another value into hash
      /// </summary>
      /// <param name="value"></param>
      INLINE void step(uint32_t value)
      {
         mHash = step32_full(mHash, value);
         mLen += sizeof(uint32_t);
      }

      /// <summary>
      /// Finish hash computation
      /// </summary>
      /// <returns>Hash value</returns>
      INLINE uint32_t finish()
      {
         return mix32(mHash ^ mLen);
      }

      ///////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Calculates hash of a single UInt32.
      /// 'seed' must be initially set with seed and then returns hash.
      /// </summary>
      INLINE static void hashUInt32(const uint32_t value, uint32_t& seed)
      {
         seed = step32_full(seed, value);
         seed = mix32(seed ^ 4);
      }

      /// <summary>
      /// Calculates hash of arbitrary memory.
      /// 'seed' must be initially set with seed and then returns hash.
      /// </summary>
      INLINE static bool hashMem(const void* buf, const uint32_t len, uint32_t& seed)
      {
         // check ptrs
         if (buf == 0 || len == 0)
            return false;

         uint8_t* mem = (uint8_t*)buf;
         uint8_t* end = mem + len;

         // full 32 bit steps
         while(mem + 4U <= end)
         {
            seed = step32_full(seed, *(uint32_t*)mem);
            mem += 4U;
         }

         // step on 0-3 remaining bytes
         const uint32_t tail = len & 3;
         if (tail)
         {
            uint32_t v = *(uint32_t*)mem;

            // keep only bytes of tail
            // tail=1: v &= 0x000000FF
            // tail=2: v &= 0x0000FFFF
            // tail=3: v &= 0x00FFFFFF
            v &= (1U << ((tail << 3U) + 1U)) - 1U;
            seed = step32_part(seed, v);
         }

         // finish
         seed = mix32(seed ^ len);

         // success
         return true;
      }

      /// <summary>
      /// Calculates 32-Bit Hash of an input stream.
      /// 'seed' must be initially set with 32-Bit seed and then returns 32-Bit hash.
      /// </summary>
      INLINE static bool hashStream(istream& s, const uint64_t len, void* digest)
      {
         // stream with zero size
         if (len == 0)
            return false;

         // first seed then hash
         uint32_t& seed = *(uint32_t*)digest;

         // chunk buffer
         CPPCORE_ALIGN16 uint8_t buf[8192];

         uint32_t* end;
         uint32_t* ptr;
         uint64_t  n64;
         uint32_t  n32;

         // read n64 * 8192 byte chunks
         n64 = len >> 13;
         end = (uint32_t*)(&buf[0] + 8192);
         for (uint64_t i = 0; i < n64; i++)
         {
            s.read((char*)buf, 8192);
            ptr = (uint32_t*)buf;
            while (ptr < end)
               seed = step32_full(seed, *ptr++);
         }

         // read remaining 0-8191 bytes
         n32 = (uint32_t)len & 0x1FFFU;
         s.read((char*)buf, n32);
         ptr = (uint32_t*)&buf[0];

         // 4 byte chunks
         n32 >>= 2;
         for (uint32_t i = 0; i < n32; i++)
            seed = step32_full(seed, *ptr++);

         // 0-3 byte tail
         n32 = len & 0x03;
         if (n32)
         {
            uint32_t v = *(uint32_t*)ptr;

            // keep only bytes of tail
            // tail=1: v &= 0x000000FF
            // tail=2: v &= 0x0000FFFF
            // tail=3: v &= 0x00FFFFFF
            v &= (1U << ((n32 << 3U) + 1U)) - 1U;
            seed = step32_part(seed, v);
         }

         // finish
         seed = mix32(seed ^ (uint32_t)len);

         // success
         return true;
      }

      /// <summary>
      /// 
      /// </summary>
      INLINE static bool hashFile(const string& file, void* digest)
      {
         return Hash::hashFile<Murmur3>(file, digest);
      }
   };
}
