#pragma once

#include <CppCore/Root.h>
#include <CppCore/Hash/Hash.h>

namespace CppCore
{
   /////////////////////////////////////////////////////////////////////////////////////////////////
   // BASE CLASSES
   /////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// SHA2 Base Class
   /// </summary>
   template<typename TSTATE, typename TBLOCK, typename TSHA>
   class SHA2b : public Hash<TSHA, TSTATE>
   {
   public:
      using Base  = Hash<TSHA, TSTATE>;
      using Block = TBLOCK;
      using State = TSTATE;
      using Base::step;
      using Base::hash;
      using Base::thiss;

   private:
      friend Base;

   protected:
      CPPCORE_ALIGN32 State    mState;     // current state/hash
      CPPCORE_ALIGN32 Block    mBlock;     // current block
      CPPCORE_ALIGN8  size_t   mBlockSize; // byte size used in current block
      CPPCORE_ALIGN8  uint64_t mTotalSize; // byte size totally hashed

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE SHA2b() { }

      /// <summary>
      /// Digest/Hash Output Size in Bytes
      /// </summary>
      static constexpr const size_t DIGESTSIZE = sizeof(TSTATE);

      /// <summary>
      /// Size of the internal Work Block in Bytes
      /// </summary>
      static constexpr const size_t BLOCKSIZE  = sizeof(TBLOCK);

      /// <summary>
      /// Compute length bytes of data into the current hash.
      /// </summary>
      INLINE void step(const void* data, size_t length)
      {
         this->step(data, length, 
            this->mBlock, 
            this->mBlockSize, 
            this->mTotalSize);
      }
   };

   /// <summary>
   /// SHA2 256-Bit Base Class
   /// </summary>
   template<typename TSHA>
   class SHA256b : public SHA2b<Block256, Block512, TSHA>
   {
   public:
      using Base = SHA2b<Block256, Block512, TSHA>;
      using typename Base::Digest;
      using typename Base::Block;
      using typename Base::State;
      using Base::blockstep;

   public:
      CPPCORE_ALIGN64 static constexpr const uint32_t K[] = {
         0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
         0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
         0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
         0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
         0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
         0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
         0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
         0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
         0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
         0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
         0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
         0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
         0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
         0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
         0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
         0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
      };
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
      static constexpr const uint32_t SEED1 = 0x6a09e667;
      static constexpr const uint32_t SEED2 = 0xbb67ae85;
      static constexpr const uint32_t SEED3 = 0x3c6ef372;
      static constexpr const uint32_t SEED4 = 0xa54ff53a;
      static constexpr const uint32_t SEED5 = 0x510e527f;
      static constexpr const uint32_t SEED6 = 0x9b05688c;
      static constexpr const uint32_t SEED7 = 0x1f83d9ab;
      static constexpr const uint32_t SEED8 = 0x5be0cd19;

   protected:
      /// <summary>
      /// Flips Endianess on Block
      /// </summary>
      INLINE void flipEndianBlock() { this->mBlock.flipEndian32(); }

      /// <summary>
      /// Flips Endianess on State
      /// </summary>
      INLINE void flipEndianState() { this->mState.flipEndian32(); }

      /// <summary>
      /// Calculates amount of padding bytes for current block
      /// </summary>
      INLINE size_t padSize() const
      {
         return Base::padSize(sizeof(this->mBlock), this->mBlockSize, 8U);
      }

      /// <summary>
      /// Finish hash calculations.
      /// </summary>
      INLINE void finish()
      {
         // length of the overall hashed data in bits
         const uint64_t bitlength = this->mTotalSize * 8ULL;

         // append padding
         this->thiss().step(PADDING, padSize());

         // write the 64-bit length of the original message
         // as big endian to the end of the block
         CppCore::storer64(&this->mBlock.u64[Block::N64-1], bitlength);

         // calculate the message digest
         this->thiss().transform();

         // convert integers to big-endian
         this->thiss().flipEndianState();
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE SHA256b() { }

      /// <summary>
      /// Resets to new seeds.
      /// </summary>
      INLINE void reset(
         const uint32_t s0 = SEED1, const uint32_t s1 = SEED2,
         const uint32_t s2 = SEED3, const uint32_t s3 = SEED4,
         const uint32_t s4 = SEED5, const uint32_t s5 = SEED6,
         const uint32_t s6 = SEED7, const uint32_t s7 = SEED8)
      {
         this->mState.u32[0] = s0; this->mState.u32[1] = s1;
         this->mState.u32[2] = s2; this->mState.u32[3] = s3;
         this->mState.u32[4] = s4; this->mState.u32[5] = s5;
         this->mState.u32[6] = s6; this->mState.u32[7] = s7;
         this->mBlockSize = 0;
         this->mTotalSize = 0;
      }

      /// <summary>
      /// Computes exactly a multiple of 64 bytes into the current hash.
      /// Do not use this if you have already called step() with a non-multiple of 64 bytes!
      /// </summary>
      INLINE void blockstep(const void* data, size_t length)
      {
         this->blockstep(data, length, this->mBlock, this->mBlockSize, this->mTotalSize);
      }

      /// <summary>
      /// Finish hash calculations.
      /// </summary>
      INLINE void finish(Digest& digest)
      {
         this->thiss().finish();
         CppCore::clone(digest, this->mState);
      }

      /// <summary>
      /// Finish hash calculations.
      /// Writes 32 bytes to digest!
      /// </summary>
      INLINE void finish(void* digest)
      {
         this->thiss().finish();
         Memory::singlecopy256<1,16>(digest, &this->mState);
      }
   };

   /// <summary>
   /// SHA2 512-Bit Base Class
   /// </summary>
   template<typename TSHA>
   class SHA512b : public SHA2b<Block512, Block1024, TSHA>
   {
   public:
      using Base = SHA2b<Block512, Block1024, TSHA>;
      using typename Base::Digest;
      using typename Base::Block;
      using typename Base::State;
      using Base::blockstep;

   public:
      CPPCORE_ALIGN64 static constexpr const uint64_t K[] = {
         0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
         0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
         0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
         0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
         0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
         0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
         0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
         0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
         0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
         0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
         0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
         0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
         0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
         0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
         0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
         0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
         0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
         0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
         0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
         0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
      };
      CPPCORE_ALIGN64 static constexpr const uint8_t PADDING[128] = {
         0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      };
      static constexpr const uint64_t SEED1 = 0x6A09E667F3BCC908;
      static constexpr const uint64_t SEED2 = 0xBB67AE8584CAA73B;
      static constexpr const uint64_t SEED3 = 0x3C6EF372FE94F82B;
      static constexpr const uint64_t SEED4 = 0xA54FF53A5F1D36F1;
      static constexpr const uint64_t SEED5 = 0x510E527FADE682D1;
      static constexpr const uint64_t SEED6 = 0x9B05688C2B3E6C1F;
      static constexpr const uint64_t SEED7 = 0x1F83D9ABFB41BD6B;
      static constexpr const uint64_t SEED8 = 0x5BE0CD19137E2179;

   protected:
      /// <summary>
      /// Flip Endianess on Block
      /// </summary>
      INLINE void flipEndianBlock() { this->mBlock.flipEndian64(); }

      /// <summary>
      /// Flip Endianess on State
      /// </summary>
      INLINE void flipEndianState() { this->mState.flipEndian64(); }

      /// <summary>
      /// Calculates amount of padding bytes for current block
      /// </summary>
      INLINE size_t padSize() const
      {
         return Base::padSize(sizeof(this->mBlock), this->mBlockSize, 16U);
      }

      /// <summary>
      /// Finish hash calculations.
      /// </summary>
      INLINE void finish()
      {
         // length of the overall hashed data in bits
         const uint64_t bitlength = this->mTotalSize * 8ULL;

         // append padding
         this->thiss().step(PADDING, padSize());

         // write the 128-bit length of the original message
         // as big endian to the end of the block
         this->mBlock.u64[Block::N64-2] = 0;
         CppCore::storer64(&this->mBlock.u64[Block::N64-1], bitlength);

         // calculate the message digest
         this->thiss().transform();

         // convert integers to big-endian
         flipEndianState();
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE SHA512b() { }

      /// <summary>
      /// Resets to new seeds.
      /// </summary>
      INLINE void reset(
         const uint64_t s0 = SEED1, const uint64_t s1 = SEED2,
         const uint64_t s2 = SEED3, const uint64_t s3 = SEED4,
         const uint64_t s4 = SEED5, const uint64_t s5 = SEED6,
         const uint64_t s6 = SEED7, const uint64_t s7 = SEED8)
      {
         this->mState.u64[0] = s0; this->mState.u64[1] = s1;
         this->mState.u64[2] = s2; this->mState.u64[3] = s3;
         this->mState.u64[4] = s4; this->mState.u64[5] = s5;
         this->mState.u64[6] = s6; this->mState.u64[7] = s7;
         this->mBlockSize = 0; 
         this->mTotalSize = 0;
      }

      /// <summary>
      /// Computes exactly a multiple of 128 bytes into the current hash.
      /// Do not use this if you have already called step() with a non-multiple of 128 bytes!
      /// </summary>
      INLINE void blockstep(const void* data, size_t length)
      {
         this->blockstep(data, length, this->mBlock, this->mBlockSize, this->mTotalSize);
      }

      /// <summary>
      /// Finish hash calculations.
      /// </summary>
      INLINE void finish(Digest& digest)
      {
         this->thiss().finish();
         CppCore::clone(digest, this->mState);
      }

      /// <summary>
      /// Finish hash calculations.
      /// Writes 64 bytes to digest!
      /// </summary>
      INLINE void finish(void* digest)
      {
         this->thiss().finish();
         Memory::singlecopy512<1,16>(digest, &this->mState);
      }
   };

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // GENERIC VERSIONS
   /////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// SHA2 256-Bit Generic
   /// </summary>
   class SHA256g : public SHA256b<SHA256g>
   {
   public:
      using Base = SHA256b<SHA256g>;

   private:
      friend Base;
      friend Base::Base;
      friend Base::Base::Base;

   protected:
      INLINE static uint32_t ch (const uint32_t x, const uint32_t y, const uint32_t z) { return (x & y) | CppCore::andn32(x, z); }
      INLINE static uint32_t maj(const uint32_t x, const uint32_t y, const uint32_t z) { return (x & y) | (x & z) | (y & z); }
      INLINE static uint32_t sigma1(const uint32_t x) { return CppCore::rotr32(x, 2)  ^ CppCore::rotr32(x, 13) ^ CppCore::rotr32(x, 22); }
      INLINE static uint32_t sigma2(const uint32_t x) { return CppCore::rotr32(x, 6)  ^ CppCore::rotr32(x, 11) ^ CppCore::rotr32(x, 25); }
      INLINE static uint32_t sigma3(const uint32_t x) { return CppCore::rotr32(x, 7)  ^ CppCore::rotr32(x, 18) ^ (x >> 3); }
      INLINE static uint32_t sigma4(const uint32_t x) { return CppCore::rotr32(x, 17) ^ CppCore::rotr32(x, 19) ^ (x >> 10); }
      INLINE uint32_t& W(const uint32_t x) { return mBlock.u32[x & 0x0F]; }

      /// <summary>
      /// Transform Block
      /// </summary>
      INLINE void transform()
      {
         // flip 32-bit integers to big endianess
         flipEndianBlock();

         // load state
         uint32_t a = mState.u32[0];
         uint32_t b = mState.u32[1];
         uint32_t c = mState.u32[2];
         uint32_t d = mState.u32[3];
         uint32_t e = mState.u32[4];
         uint32_t f = mState.u32[5];
         uint32_t g = mState.u32[6];
         uint32_t h = mState.u32[7];

         // transform state
         CPPCORE_UNROLL
         for (uint32_t t = 0; t < 64U; t++)
         {
            if (t >= 16)
               W(t) += sigma4(W(t + 14)) + W(t + 9) + sigma3(W(t + 1));
  
            const uint32_t t1 = h + sigma2(e) + ch(e, f, g) + K[t] + W(t);
            const uint32_t t2 = sigma1(a) + maj(a, b, c);
  
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
         }
  
         // save state
         mState.u32[0] += a;
         mState.u32[1] += b;
         mState.u32[2] += c;
         mState.u32[3] += d;
         mState.u32[4] += e;
         mState.u32[5] += f;
         mState.u32[6] += g;
         mState.u32[7] += h;
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE SHA256g(
         const uint32_t s0 = SEED1, const uint32_t s1 = SEED2,
         const uint32_t s2 = SEED3, const uint32_t s3 = SEED4,
         const uint32_t s4 = SEED5, const uint32_t s5 = SEED6,
         const uint32_t s6 = SEED7, const uint32_t s7 = SEED8) : SHA256b() 
      {
         thiss().reset(s0, s1, s2, s3, s4, s5, s6, s7);
      }
   };

   /// <summary>
   /// SHA2 512-Bit Generic
   /// </summary>
   class SHA512g : public SHA512b<SHA512g>
   {
   public:
      using Base = SHA512b<SHA512g>;

   private:
      friend Base;
      friend Base::Base;
      friend Base::Base::Base;

   protected:
      INLINE static uint64_t ch (const uint64_t x, const uint64_t y, const uint64_t z) { return (x & y) | CppCore::andn64(x, z); }
      INLINE static uint64_t maj(const uint64_t x, const uint64_t y, const uint64_t z) { return (x & y) | (x & z) | (y & z); }
      INLINE static uint64_t sigma1(const uint64_t x) { return CppCore::rotr64(x, 28) ^ CppCore::rotr64(x, 34) ^ CppCore::rotr64(x, 39); }
      INLINE static uint64_t sigma2(const uint64_t x) { return CppCore::rotr64(x, 14) ^ CppCore::rotr64(x, 18) ^ CppCore::rotr64(x, 41); }
      INLINE static uint64_t sigma3(const uint64_t x) { return CppCore::rotr64(x, 1)  ^ CppCore::rotr64(x, 8)  ^ (x >> 7); }
      INLINE static uint64_t sigma4(const uint64_t x) { return CppCore::rotr64(x, 19) ^ CppCore::rotr64(x, 61) ^ (x >> 6); }
      INLINE uint64_t& W(const uint64_t x) { return mBlock.u64[x & 0x0F]; }

      /// <summary>
      /// Transform Block
      /// </summary>
      INLINE void transform()
      {
         // flip 64-bit integers to big endianess
         flipEndianBlock();

         // load state
         uint64_t a = mState.u64[0];
         uint64_t b = mState.u64[1];
         uint64_t c = mState.u64[2];
         uint64_t d = mState.u64[3];
         uint64_t e = mState.u64[4];
         uint64_t f = mState.u64[5];
         uint64_t g = mState.u64[6];
         uint64_t h = mState.u64[7];

         // transform state
         CPPCORE_UNROLL
         for (uint32_t t = 0; t < 80U; t++)
         {
            if (t >= 16)
               W(t) += sigma4(W(t + 14)) + W(t + 9) + sigma3(W(t + 1));
  
            const uint64_t t1 = h + sigma2(e) + ch(e, f, g) + K[t] + W(t);
            const uint64_t t2 = sigma1(a) + maj(a, b, c);
  
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
         }
  
         // save state
         mState.u64[0] += a;
         mState.u64[1] += b;
         mState.u64[2] += c;
         mState.u64[3] += d;
         mState.u64[4] += e;
         mState.u64[5] += f;
         mState.u64[6] += g;
         mState.u64[7] += h;
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE SHA512g(
         const uint64_t s0 = SEED1, const uint64_t s1 = SEED2,
         const uint64_t s2 = SEED3, const uint64_t s3 = SEED4,
         const uint64_t s4 = SEED5, const uint64_t s5 = SEED6,
         const uint64_t s6 = SEED7, const uint64_t s7 = SEED8) : SHA512b()
      {
         thiss().reset(s0, s1, s2, s3, s4, s5, s6, s7);
      }
   };

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // OPTIMIZED VERSIONS (INTEL+ARM)
   /////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SHA)
   /// <summary>
   /// SHA2 256-Bit using INTEL-SHA Instructions
   /// </summary>
   class SHA256s : public SHA256b<SHA256s>
   {
   public:
      using Base = SHA256b<SHA256s>;

   private:
      friend Base;
      friend Base::Base;
      friend Base::Base::Base;

   protected:
      /// <summary>
      /// Transforms Block
      /// </summary>
      INLINE void transform()
      {
         // adapted from:
         // https://github.com/noloader/SHA-Intrinsics/blob/master/sha256-x86.c

         __m128i STATE0, STATE1;
         __m128i MSG, TMP;
         __m128i MSG0, MSG1, MSG2, MSG3;
         __m128i ABEF_SAVE, CDGH_SAVE;
         const __m128i MASK = _mm_set_epi64x(0x0c0d0e0f08090a0bULL, 0x0405060700010203ULL);

         /* Load initial values */
         TMP = _mm_load_si128((const __m128i*)&mState.u32[0]);
         STATE1 = _mm_load_si128((const __m128i*)&mState.u32[4]);

         TMP = _mm_shuffle_epi32(TMP, 0xB1);          /* CDAB */
         STATE1 = _mm_shuffle_epi32(STATE1, 0x1B);    /* EFGH */
         STATE0 = _mm_alignr_epi8(TMP, STATE1, 8);    /* ABEF */
         STATE1 = _mm_blend_epi16(STATE1, TMP, 0xF0); /* CDGH */

         /* Save current state */
         ABEF_SAVE = STATE0;
         CDGH_SAVE = STATE1;

         /* Rounds 0-3 */
         MSG = _mm_load_si128((const __m128i*) (&mBlock.u32[0]));
         MSG0 = _mm_shuffle_epi8(MSG, MASK);
         MSG = _mm_add_epi32(MSG0, _mm_load_si128((__m128i*)&K[0]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);

         /* Rounds 4-7 */
         MSG1 = _mm_load_si128((const __m128i*) (&mBlock.u32[4]));
         MSG1 = _mm_shuffle_epi8(MSG1, MASK);
         MSG = _mm_add_epi32(MSG1, _mm_load_si128((__m128i*)&K[4]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG0 = _mm_sha256msg1_epu32(MSG0, MSG1);

         /* Rounds 8-11 */
         MSG2 = _mm_load_si128((const __m128i*) (&mBlock.u32[8]));
         MSG2 = _mm_shuffle_epi8(MSG2, MASK);
         MSG = _mm_add_epi32(MSG2, _mm_load_si128((__m128i*)&K[8]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG1 = _mm_sha256msg1_epu32(MSG1, MSG2);

         /* Rounds 12-15 */
         MSG3 = _mm_load_si128((const __m128i*) (&mBlock.u32[12]));
         MSG3 = _mm_shuffle_epi8(MSG3, MASK);
         MSG = _mm_add_epi32(MSG3, _mm_load_si128((__m128i*)&K[12]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG3, MSG2, 4);
         MSG0 = _mm_add_epi32(MSG0, TMP);
         MSG0 = _mm_sha256msg2_epu32(MSG0, MSG3);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG2 = _mm_sha256msg1_epu32(MSG2, MSG3);

         /* Rounds 16-19 */
         MSG = _mm_add_epi32(MSG0, _mm_load_si128((__m128i*)&K[16]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG0, MSG3, 4);
         MSG1 = _mm_add_epi32(MSG1, TMP);
         MSG1 = _mm_sha256msg2_epu32(MSG1, MSG0);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG3 = _mm_sha256msg1_epu32(MSG3, MSG0);

         /* Rounds 20-23 */
         MSG = _mm_add_epi32(MSG1, _mm_load_si128((__m128i*)&K[20]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG1, MSG0, 4);
         MSG2 = _mm_add_epi32(MSG2, TMP);
         MSG2 = _mm_sha256msg2_epu32(MSG2, MSG1);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG0 = _mm_sha256msg1_epu32(MSG0, MSG1);

         /* Rounds 24-27 */
         MSG = _mm_add_epi32(MSG2, _mm_load_si128((__m128i*)&K[24]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG2, MSG1, 4);
         MSG3 = _mm_add_epi32(MSG3, TMP);
         MSG3 = _mm_sha256msg2_epu32(MSG3, MSG2);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG1 = _mm_sha256msg1_epu32(MSG1, MSG2);

         /* Rounds 28-31 */
         MSG = _mm_add_epi32(MSG3, _mm_load_si128((__m128i*)&K[28]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG3, MSG2, 4);
         MSG0 = _mm_add_epi32(MSG0, TMP);
         MSG0 = _mm_sha256msg2_epu32(MSG0, MSG3);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG2 = _mm_sha256msg1_epu32(MSG2, MSG3);

         /* Rounds 32-35 */
         MSG = _mm_add_epi32(MSG0, _mm_load_si128((__m128i*)&K[32]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG0, MSG3, 4);
         MSG1 = _mm_add_epi32(MSG1, TMP);
         MSG1 = _mm_sha256msg2_epu32(MSG1, MSG0);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG3 = _mm_sha256msg1_epu32(MSG3, MSG0);

         /* Rounds 36-39 */
         MSG = _mm_add_epi32(MSG1, _mm_load_si128((__m128i*)&K[36]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG1, MSG0, 4);
         MSG2 = _mm_add_epi32(MSG2, TMP);
         MSG2 = _mm_sha256msg2_epu32(MSG2, MSG1);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG0 = _mm_sha256msg1_epu32(MSG0, MSG1);

         /* Rounds 40-43 */
         MSG = _mm_add_epi32(MSG2, _mm_load_si128((__m128i*)&K[40]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG2, MSG1, 4);
         MSG3 = _mm_add_epi32(MSG3, TMP);
         MSG3 = _mm_sha256msg2_epu32(MSG3, MSG2);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG1 = _mm_sha256msg1_epu32(MSG1, MSG2);

         /* Rounds 44-47 */
         MSG = _mm_add_epi32(MSG3, _mm_load_si128((__m128i*)&K[44]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG3, MSG2, 4);
         MSG0 = _mm_add_epi32(MSG0, TMP);
         MSG0 = _mm_sha256msg2_epu32(MSG0, MSG3);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG2 = _mm_sha256msg1_epu32(MSG2, MSG3);

         /* Rounds 48-51 */
         MSG = _mm_add_epi32(MSG0, _mm_load_si128((__m128i*)&K[48]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG0, MSG3, 4);
         MSG1 = _mm_add_epi32(MSG1, TMP);
         MSG1 = _mm_sha256msg2_epu32(MSG1, MSG0);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
         MSG3 = _mm_sha256msg1_epu32(MSG3, MSG0);

         /* Rounds 52-55 */
         MSG = _mm_add_epi32(MSG1, _mm_load_si128((__m128i*)&K[52]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG1, MSG0, 4);
         MSG2 = _mm_add_epi32(MSG2, TMP);
         MSG2 = _mm_sha256msg2_epu32(MSG2, MSG1);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);

         /* Rounds 56-59 */
         MSG = _mm_add_epi32(MSG2, _mm_load_si128((__m128i*)&K[56]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         TMP = _mm_alignr_epi8(MSG2, MSG1, 4);
         MSG3 = _mm_add_epi32(MSG3, TMP);
         MSG3 = _mm_sha256msg2_epu32(MSG3, MSG2);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);

         /* Rounds 60-63 */
         MSG = _mm_add_epi32(MSG3, _mm_load_si128((__m128i*)&K[60]));
         STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
         MSG = _mm_shuffle_epi32(MSG, 0x0E);
         STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);

         /* Combine state  */
         STATE0 = _mm_add_epi32(STATE0, ABEF_SAVE);
         STATE1 = _mm_add_epi32(STATE1, CDGH_SAVE);

         TMP = _mm_shuffle_epi32(STATE0, 0x1B);       /* FEBA */
         STATE1 = _mm_shuffle_epi32(STATE1, 0xB1);    /* DCHG */
         STATE0 = _mm_blend_epi16(TMP, STATE1, 0xF0); /* DCBA */
         STATE1 = _mm_alignr_epi8(STATE1, TMP, 8);    /* ABEF */

         /* Save state */
         _mm_store_si128((__m128i*)&mState.u32[0], STATE0);
         _mm_store_si128((__m128i*)&mState.u32[4], STATE1);
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE SHA256s(
         const uint32_t s0 = SEED1, const uint32_t s1 = SEED2,
         const uint32_t s2 = SEED3, const uint32_t s3 = SEED4,
         const uint32_t s4 = SEED5, const uint32_t s5 = SEED6,
         const uint32_t s6 = SEED7, const uint32_t s7 = SEED8) : SHA256b() 
      {
         thiss().reset(s0, s1, s2, s3, s4, s5, s6, s7);
      }
   };

   using SHA512s = SHA512g;

#elif defined(CPPCORE_CPUFEAT_ARM_SHA2)
   /// <summary>
   /// SHA2 256-Bit using ARM-SHA Instructions
   /// </summary>
   class SHA256s : public SHA256b<SHA256s>
   {
   public:
      using Base = SHA256b<SHA256s>;

   private:
      friend Base;
      friend Base::Base;
      friend Base::Base::Base;

   protected:
      /// <summary>
      /// Transforms Block
      /// </summary>
      INLINE void transform()
      {
         // adapted from:
         // https://github.com/noloader/SHA-Intrinsics/blob/master/sha256-arm.c

         uint32x4_t STATE0, STATE1, ABEF_SAVE, CDGH_SAVE;
         uint32x4_t MSG0, MSG1, MSG2, MSG3;
         uint32x4_t TMP0, TMP1, TMP2;

         STATE0 = vld1q_u32(&mState.u32[0]);
         STATE1 = vld1q_u32(&mState.u32[4]);

         /* Save state */
         ABEF_SAVE = STATE0;
         CDGH_SAVE = STATE1;

         /* Load message */
         MSG0 = vld1q_u32(&mBlock.u32[0]);
         MSG1 = vld1q_u32(&mBlock.u32[4]);
         MSG2 = vld1q_u32(&mBlock.u32[8]);
         MSG3 = vld1q_u32(&mBlock.u32[12]);

         /* Reverse for little endian */
         MSG0 = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(MSG0)));
         MSG1 = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(MSG1)));
         MSG2 = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(MSG2)));
         MSG3 = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(MSG3)));

         TMP0 = vaddq_u32(MSG0, vld1q_u32(&K[0x00]));

         /* Rounds 0-3 */
         MSG0 = vsha256su0q_u32(MSG0, MSG1);
         TMP2 = STATE0;
         TMP1 = vaddq_u32(MSG1, vld1q_u32(&K[0x04]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP0);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP0);
         MSG0 = vsha256su1q_u32(MSG0, MSG2, MSG3);

         /* Rounds 4-7 */
         MSG1 = vsha256su0q_u32(MSG1, MSG2);
         TMP2 = STATE0;
         TMP0 = vaddq_u32(MSG2, vld1q_u32(&K[0x08]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP1);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP1);
         MSG1 = vsha256su1q_u32(MSG1, MSG3, MSG0);

         /* Rounds 8-11 */
         MSG2 = vsha256su0q_u32(MSG2, MSG3);
         TMP2 = STATE0;
         TMP1 = vaddq_u32(MSG3, vld1q_u32(&K[0x0c]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP0);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP0);
         MSG2 = vsha256su1q_u32(MSG2, MSG0, MSG1);

         /* Rounds 12-15 */
         MSG3 = vsha256su0q_u32(MSG3, MSG0);
         TMP2 = STATE0;
         TMP0 = vaddq_u32(MSG0, vld1q_u32(&K[0x10]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP1);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP1);
         MSG3 = vsha256su1q_u32(MSG3, MSG1, MSG2);

         /* Rounds 16-19 */
         MSG0 = vsha256su0q_u32(MSG0, MSG1);
         TMP2 = STATE0;
         TMP1 = vaddq_u32(MSG1, vld1q_u32(&K[0x14]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP0);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP0);
         MSG0 = vsha256su1q_u32(MSG0, MSG2, MSG3);

         /* Rounds 20-23 */
         MSG1 = vsha256su0q_u32(MSG1, MSG2);
         TMP2 = STATE0;
         TMP0 = vaddq_u32(MSG2, vld1q_u32(&K[0x18]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP1);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP1);
         MSG1 = vsha256su1q_u32(MSG1, MSG3, MSG0);

         /* Rounds 24-27 */
         MSG2 = vsha256su0q_u32(MSG2, MSG3);
         TMP2 = STATE0;
         TMP1 = vaddq_u32(MSG3, vld1q_u32(&K[0x1c]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP0);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP0);
         MSG2 = vsha256su1q_u32(MSG2, MSG0, MSG1);

         /* Rounds 28-31 */
         MSG3 = vsha256su0q_u32(MSG3, MSG0);
         TMP2 = STATE0;
         TMP0 = vaddq_u32(MSG0, vld1q_u32(&K[0x20]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP1);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP1);
         MSG3 = vsha256su1q_u32(MSG3, MSG1, MSG2);

         /* Rounds 32-35 */
         MSG0 = vsha256su0q_u32(MSG0, MSG1);
         TMP2 = STATE0;
         TMP1 = vaddq_u32(MSG1, vld1q_u32(&K[0x24]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP0);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP0);
         MSG0 = vsha256su1q_u32(MSG0, MSG2, MSG3);

         /* Rounds 36-39 */
         MSG1 = vsha256su0q_u32(MSG1, MSG2);
         TMP2 = STATE0;
         TMP0 = vaddq_u32(MSG2, vld1q_u32(&K[0x28]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP1);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP1);
         MSG1 = vsha256su1q_u32(MSG1, MSG3, MSG0);

         /* Rounds 40-43 */
         MSG2 = vsha256su0q_u32(MSG2, MSG3);
         TMP2 = STATE0;
         TMP1 = vaddq_u32(MSG3, vld1q_u32(&K[0x2c]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP0);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP0);
         MSG2 = vsha256su1q_u32(MSG2, MSG0, MSG1);

         /* Rounds 44-47 */
         MSG3 = vsha256su0q_u32(MSG3, MSG0);
         TMP2 = STATE0;
         TMP0 = vaddq_u32(MSG0, vld1q_u32(&K[0x30]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP1);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP1);
         MSG3 = vsha256su1q_u32(MSG3, MSG1, MSG2);

         /* Rounds 48-51 */
         TMP2 = STATE0;
         TMP1 = vaddq_u32(MSG1, vld1q_u32(&K[0x34]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP0);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP0);

         /* Rounds 52-55 */
         TMP2 = STATE0;
         TMP0 = vaddq_u32(MSG2, vld1q_u32(&K[0x38]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP1);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP1);

         /* Rounds 56-59 */
         TMP2 = STATE0;
         TMP1 = vaddq_u32(MSG3, vld1q_u32(&K[0x3c]));
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP0);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP0);

         /* Rounds 60-63 */
         TMP2 = STATE0;
         STATE0 = vsha256hq_u32(STATE0, STATE1, TMP1);
         STATE1 = vsha256h2q_u32(STATE1, TMP2, TMP1);

         /* Combine state */
         STATE0 = vaddq_u32(STATE0, ABEF_SAVE);
         STATE1 = vaddq_u32(STATE1, CDGH_SAVE);

         /* Save state */
         vst1q_u32(&mState.u32[0], STATE0);
         vst1q_u32(&mState.u32[4], STATE1);
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE SHA256s(
         const uint32_t s0 = SEED1, const uint32_t s1 = SEED2,
         const uint32_t s2 = SEED3, const uint32_t s3 = SEED4,
         const uint32_t s4 = SEED5, const uint32_t s5 = SEED6,
         const uint32_t s6 = SEED7, const uint32_t s7 = SEED8) : SHA256b() 
      {
         thiss().reset(s0, s1, s2, s3, s4, s5, s6, s7);
      }
   };

   // TODO: Implement
   using SHA512s = SHA512g;
#else
   using SHA256s = SHA256g;
   using SHA512s = SHA512g;
#endif

   // USE OPTIMIZED BY DEFAULT IF ENABLED
   using SHA256 = SHA256s;
   using SHA512 = SHA512s;
}
