#pragma once

#include <CppCore/Root.h>
#include <CppCore/Hash/Hash.h>

namespace CppCore 
{
   /// <summary>
   /// Murmur3 Hash (32-Bit)
   /// </summary>
   class Murmur3 : public Hash<Murmur3, uint32_t>
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
      using Hash::step;
      using Hash::hash;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Murmur3(uint32_t seed = 0)
      {
         reset(seed);
      }

      /// <summary>
      /// Resets the hash to the given seed
      /// </summary>
      INLINE void reset(uint32_t seed = 0)
      {
         mHash = seed;
         mLen = 0;
      }

      /// <summary>
      /// Compute another value into hash
      /// </summary>
      INLINE void step(const uint32_t& value)
      {
         mHash = step32_full(mHash, value);
         mLen += sizeof(uint32_t);
      }

      /// <summary>
      /// Compute memory into hash.
      /// Due to tail handling in Murmur3, chunk sizes matter.
      /// Chunks should be multiples of 4 bytes except for the last one.
      /// </summary>
      INLINE void step(const void* data, size_t length)
      {
         uint8_t* mem = (uint8_t*)data;
         uint8_t* end = mem + length;
         uint32_t hsh = mHash;

         // full 32 bit steps
         while(mem + 4U <= end)
         {
            hsh = step32_full(hsh, *(uint32_t*)mem);
            mem += 4U;
         }

         // step on 0-3 remaining bytes
         if (const uint32_t tail = length & 3)
         {
            uint32_t v = *(uint32_t*)mem;
            v &= (1U << ((tail << 3U) + 1U)) - 1U;
            hsh = step32_part(hsh, v);
         }

         mHash = hsh;
         mLen += (uint32_t)length;
      }

      /// <summary>
      /// Just calls step()
      /// </summary>
      INLINE void blockstep(const void* data, size_t len)
      {
         this->step(data, len);
      }

      /// <summary>
      /// Finish hash computation
      /// </summary>
      INLINE Digest finish()
      {
         return mix32(mHash ^ mLen);
      }

      /// <summary>
      /// Finish hash computation
      /// </summary>
      INLINE void finish(Digest& digest)
      {
         digest = finish();
      }

      /// <summary>
      /// Finish hash computation.
      /// Writes 4 bytes to digest!
      /// </summary>
      INLINE void finish(void* digest)
      {
         *(uint32_t*)digest = finish();
      }

      /// <summary>
      /// Hash of uint32_t
      /// </summary>
      INLINE void hash(uint32_t data, Digest& digest, uint32_t seed = 0)
      {
         digest = mix32(step32_full(seed, data) ^ 4);
      }

      /// <summary>
      /// Hash of uint64_t
      /// </summary>
      INLINE void hash(uint64_t data, Digest& digest, uint32_t seed = 0)
      {
         digest = mix32(step32_full(
            step32_full(seed, (uint32_t)data),
            (uint32_t)(data >> 32)) ^ 4);
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
   };
}
