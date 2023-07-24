#pragma once

#include <CppCore/Root.h>
#include <CppCore/Hash/Hash.h>

namespace CppCore
{
   /// <summary>
   /// MD5 Hash
   /// </summary>
   class MD5 : public Hash<MD5, Block128>
   {
   public:
      CPPCORE_ALIGN64 static constexpr const uint8_t PADDING[64] = {
         0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      };
      static constexpr const uint32_t SEED1 = 0x67452301;
      static constexpr const uint32_t SEED2 = 0xefcdab89;
      static constexpr const uint32_t SEED3 = 0x98badcfe;
      static constexpr const uint32_t SEED4 = 0x10325476;

   public:
      using Block = Block512;
      using State = Block128;
      using Hash::step;
      using Hash::hash;

   protected:
      INLINE static uint32_t MD5_F(const uint32_t x, const uint32_t y, const uint32_t z) {
         return (x & y) | CppCore::andn32(x, z);
      }
      INLINE static uint32_t MD5_G(const uint32_t x, const uint32_t y, const uint32_t z) {
         return (x & z) | CppCore::andn32(z, y);
      }
      INLINE static uint32_t MD5_H(const uint32_t x, const uint32_t y, const uint32_t z) {
         return x ^ y ^ z;
      }
      INLINE static uint32_t MD5_I(const uint32_t x, const uint32_t y, const uint32_t z) {
         return y ^ (x | (~z));
      }
      INLINE static void MD5_XX(uint32_t& a, 
         const uint32_t b, const uint32_t c, const uint32_t d, 
         const uint32_t x, const uint32_t s, const uint32_t ac, const uint32_t z) {
         a = CppCore::rotl32(a + z + x + ac, s) + b;
      }
      INLINE static void MD5_FF(uint32_t& a, 
         const uint32_t b, const uint32_t c, const uint32_t d, 
         const uint32_t x, const uint32_t s, const uint32_t ac) {
         MD5_XX(a, b, c, d, x, s, ac, MD5_F(b, c, d));
      }
      INLINE static void MD5_GG(uint32_t& a, 
         const uint32_t b, const uint32_t c, const uint32_t d, 
         const uint32_t x, const uint32_t s, const uint32_t ac) {
         MD5_XX(a, b, c, d, x, s, ac, MD5_G(b, c, d));
      }
      INLINE static void MD5_HH(uint32_t& a, 
         const uint32_t b, const uint32_t c, const uint32_t d, 
         const uint32_t x, const uint32_t s, const uint32_t ac) {
         MD5_XX(a, b, c, d, x, s, ac, MD5_H(b, c, d));
      }
      INLINE static void MD5_II(uint32_t& a, 
         const uint32_t b, const uint32_t c, const uint32_t d, 
         const uint32_t x, const uint32_t s, const uint32_t ac) {
         MD5_XX(a, b, c, d, x, s, ac, MD5_I(b, c, d));
      }

   protected:
      CPPCORE_ALIGN16 State    mState;    // current state
      CPPCORE_ALIGN16 Block    mBlock;    // current block
      CPPCORE_ALIGN8  size_t   blockSize; // byte size used in current block
      CPPCORE_ALIGN8  uint64_t totalSize; // byte size totally hashed

      /// <summary>
      /// Transform current block
      /// </summary>
      INLINE void transform()
      {
         // Constants
         const uint32_t 
            S11 = 7, S12 = 12, S13 = 17, S14 = 22,
            S21 = 5, S22 =  9, S23 = 14, S24 = 20,
            S31 = 4, S32 = 11, S33 = 16, S34 = 23,
            S41 = 6, S42 = 10, S43 = 15, S44 = 21;

         // Variables
         uint32_t 
            a = mState.u32[0], b = mState.u32[1],
            c = mState.u32[2], d = mState.u32[3];

         // Round 1
         MD5_FF(a, b, c, d, mBlock.u32[0],  S11, 0xd76aa478); // 1
         MD5_FF(d, a, b, c, mBlock.u32[1],  S12, 0xe8c7b756); // 2
         MD5_FF(c, d, a, b, mBlock.u32[2],  S13, 0x242070db); // 3
         MD5_FF(b, c, d, a, mBlock.u32[3],  S14, 0xc1bdceee); // 4
         MD5_FF(a, b, c, d, mBlock.u32[4],  S11, 0xf57c0faf); // 5
         MD5_FF(d, a, b, c, mBlock.u32[5],  S12, 0x4787c62a); // 6
         MD5_FF(c, d, a, b, mBlock.u32[6],  S13, 0xa8304613); // 7
         MD5_FF(b, c, d, a, mBlock.u32[7],  S14, 0xfd469501); // 8
         MD5_FF(a, b, c, d, mBlock.u32[8],  S11, 0x698098d8); // 9
         MD5_FF(d, a, b, c, mBlock.u32[9],  S12, 0x8b44f7af); // 10
         MD5_FF(c, d, a, b, mBlock.u32[10], S13, 0xffff5bb1); // 11
         MD5_FF(b, c, d, a, mBlock.u32[11], S14, 0x895cd7be); // 12
         MD5_FF(a, b, c, d, mBlock.u32[12], S11, 0x6b901122); // 13
         MD5_FF(d, a, b, c, mBlock.u32[13], S12, 0xfd987193); // 14
         MD5_FF(c, d, a, b, mBlock.u32[14], S13, 0xa679438e); // 15
         MD5_FF(b, c, d, a, mBlock.u32[15], S14, 0x49b40821); // 16

         // Round 2
         MD5_GG(a, b, c, d, mBlock.u32[1],  S21, 0xf61e2562); // 17
         MD5_GG(d, a, b, c, mBlock.u32[6],  S22, 0xc040b340); // 18
         MD5_GG(c, d, a, b, mBlock.u32[11], S23, 0x265e5a51); // 19
         MD5_GG(b, c, d, a, mBlock.u32[0],  S24, 0xe9b6c7aa); // 20
         MD5_GG(a, b, c, d, mBlock.u32[5],  S21, 0xd62f105d); // 21
         MD5_GG(d, a, b, c, mBlock.u32[10], S22, 0x02441453); // 22
         MD5_GG(c, d, a, b, mBlock.u32[15], S23, 0xd8a1e681); // 23
         MD5_GG(b, c, d, a, mBlock.u32[4],  S24, 0xe7d3fbc8); // 24
         MD5_GG(a, b, c, d, mBlock.u32[9],  S21, 0x21e1cde6); // 25
         MD5_GG(d, a, b, c, mBlock.u32[14], S22, 0xc33707d6); // 26
         MD5_GG(c, d, a, b, mBlock.u32[3],  S23, 0xf4d50d87); // 27
         MD5_GG(b, c, d, a, mBlock.u32[8],  S24, 0x455a14ed); // 28
         MD5_GG(a, b, c, d, mBlock.u32[13], S21, 0xa9e3e905); // 29
         MD5_GG(d, a, b, c, mBlock.u32[2],  S22, 0xfcefa3f8); // 30
         MD5_GG(c, d, a, b, mBlock.u32[7],  S23, 0x676f02d9); // 31
         MD5_GG(b, c, d, a, mBlock.u32[12], S24, 0x8d2a4c8a); // 32

         // Round 3
         MD5_HH(a, b, c, d, mBlock.u32[5],  S31, 0xfffa3942); // 33
         MD5_HH(d, a, b, c, mBlock.u32[8],  S32, 0x8771f681); // 34
         MD5_HH(c, d, a, b, mBlock.u32[11], S33, 0x6d9d6122); // 35
         MD5_HH(b, c, d, a, mBlock.u32[14], S34, 0xfde5380c); // 36
         MD5_HH(a, b, c, d, mBlock.u32[1],  S31, 0xa4beea44); // 37
         MD5_HH(d, a, b, c, mBlock.u32[4],  S32, 0x4bdecfa9); // 38
         MD5_HH(c, d, a, b, mBlock.u32[7],  S33, 0xf6bb4b60); // 39
         MD5_HH(b, c, d, a, mBlock.u32[10], S34, 0xbebfbc70); // 40
         MD5_HH(a, b, c, d, mBlock.u32[13], S31, 0x289b7ec6); // 41
         MD5_HH(d, a, b, c, mBlock.u32[0],  S32, 0xeaa127fa); // 42
         MD5_HH(c, d, a, b, mBlock.u32[3],  S33, 0xd4ef3085); // 43
         MD5_HH(b, c, d, a, mBlock.u32[6],  S34, 0x04881d05); // 44
         MD5_HH(a, b, c, d, mBlock.u32[9],  S31, 0xd9d4d039); // 45
         MD5_HH(d, a, b, c, mBlock.u32[12], S32, 0xe6db99e5); // 46
         MD5_HH(c, d, a, b, mBlock.u32[15], S33, 0x1fa27cf8); // 47
         MD5_HH(b, c, d, a, mBlock.u32[2],  S34, 0xc4ac5665); // 48

         // Round 4
         MD5_II(a, b, c, d, mBlock.u32[0],  S41, 0xf4292244); // 49
         MD5_II(d, a, b, c, mBlock.u32[7],  S42, 0x432aff97); // 50
         MD5_II(c, d, a, b, mBlock.u32[14], S43, 0xab9423a7); // 51
         MD5_II(b, c, d, a, mBlock.u32[5],  S44, 0xfc93a039); // 52
         MD5_II(a, b, c, d, mBlock.u32[12], S41, 0x655b59c3); // 53
         MD5_II(d, a, b, c, mBlock.u32[3],  S42, 0x8f0ccc92); // 54
         MD5_II(c, d, a, b, mBlock.u32[10], S43, 0xffeff47d); // 55
         MD5_II(b, c, d, a, mBlock.u32[1],  S44, 0x85845dd1); // 56
         MD5_II(a, b, c, d, mBlock.u32[8],  S41, 0x6fa87e4f); // 57
         MD5_II(d, a, b, c, mBlock.u32[15], S42, 0xfe2ce6e0); // 58
         MD5_II(c, d, a, b, mBlock.u32[6],  S43, 0xa3014314); // 59
         MD5_II(b, c, d, a, mBlock.u32[13], S44, 0x4e0811a1); // 60
         MD5_II(a, b, c, d, mBlock.u32[4],  S41, 0xf7537e82); // 61
         MD5_II(d, a, b, c, mBlock.u32[11], S42, 0xbd3af235); // 62
         MD5_II(c, d, a, b, mBlock.u32[2],  S43, 0x2ad7d2bb); // 63
         MD5_II(b, c, d, a, mBlock.u32[9],  S44, 0xeb86d391); // 64

         mState.u32[0] += a;
         mState.u32[1] += b;
         mState.u32[2] += c;
         mState.u32[3] += d;
      }

      /// <summary>
      /// Finish hash calculations.
      /// </summary>
      INLINE void finish()
      {
          // length of the original message (before padding)
          const uint64_t totalSize = this->totalSize * 8ULL;

          // determine padding size
          const size_t padSize = (this->blockSize < 56U) ?
             56U - this->blockSize :
             sizeof(this->mBlock) + 56U - this->blockSize;

          // append padding
          step(PADDING, padSize);

          // add the 64-bit length of the original message
          // to the end of the block
          mBlock.u64[Block::N64-1] = totalSize;

          // calculate the message digest
          transform();
      }

   public:
      /// <summary>
      /// Digest/Hash Output Size in Bytes
      /// </summary>
      static constexpr const size_t DIGESTSIZE = sizeof(Digest);

      /// <summary>
      /// Size of the internal Work Block in Bytes
      /// </summary>
      static constexpr const size_t BLOCKSIZE  = sizeof(Block);

      /// <summary>
      /// Constructor
      /// </summary>
      INLINE MD5(
         const uint32_t s0 = SEED1,
         const uint32_t s1 = SEED2,
         const uint32_t s2 = SEED3,
         const uint32_t s3 = SEED4)
      {
         reset(s0, s1, s2, s3);
      }

      /// <summary>
      /// Resets to new seeds.
      /// </summary>
      INLINE void reset(
         const uint32_t s0 = SEED1,
         const uint32_t s1 = SEED2,
         const uint32_t s2 = SEED3,
         const uint32_t s3 = SEED4)
      {
         totalSize = 0;
         blockSize = 0;
         mState.u32[0] = s0;
         mState.u32[1] = s1;
         mState.u32[2] = s2;
         mState.u32[3] = s3;
      }

      /// <summary>
      /// Compute length bytes of data into the current hash.
      /// </summary>
      INLINE void step(const void* data, size_t length)
      {
         while (length)
         {
            // copy up to max.blocksize
            const size_t n = MIN(length, sizeof(Block) - blockSize);

            // copy data to current block
            Memory::copy(&mBlock.u8[blockSize], data, n);

            // update sizes
            blockSize += n;
            totalSize += n;

            // advance pointer, decrease length
            data = (uint8_t*)data + n;
            length -= n;

            // process block if complete
            if (blockSize == sizeof(Block))
            {
               transform();
               blockSize = 0;
            }
         }
      }

      /// <summary>
      /// Finish hash calculations.
      /// </summary>
      INLINE void finish(Digest& digest)
      {
         finish();

         // copy the final digest
         CppCore::clone(digest, mState);
      }

      /// <summary>
      /// Finish hash calculations.
      /// Writes 16 bytes to digest!
      /// </summary>
      INLINE void finish(void* digest)
      {
         finish();
         Memory::singlecopy128<1,16>(digest, &mState);
      }

      /// <summary>
      /// Finish hash calculations.
      /// </summary>
      INLINE void finish(uint64_t& l, uint64_t& h)
      {
         finish();

         // copy the final digest
         l = mState.u64[0];
         h = mState.u64[1];
      }
   };
}
