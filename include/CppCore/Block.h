#pragma once

#include <CppCore/Root.h>
#include <CppCore/BitOps.h>
#include <CppCore/Math/Util.h>
#include <CppCore/Memory.h>

namespace CppCore
{
   /// <summary>
   /// Block of Bytes of any fixed SIZE
   /// </summary>
   template<typename T, size_t SIZE>
   class Block
   {
   public:
      static constexpr const size_t N8   = SIZE;
      static constexpr const size_t N16  = SIZE >> 1;
      static constexpr const size_t N32  = SIZE >> 2;
      static constexpr const size_t N64  = SIZE >> 3;
      static constexpr const size_t N128 = SIZE >> 4;
      static constexpr const size_t N256 = SIZE >> 5;
      static constexpr const size_t N512 = SIZE >> 6;

      union {
         uint8_t  u8 [N8];
         uint16_t u16[N16];
         uint32_t u32[N32];
         uint64_t u64[N64];
         int8_t   i8 [N8];
         int16_t  i16[N16];
         int32_t  i32[N32];
         int64_t  i64[N64];
      };

      /// <summary>
      /// Sets all bytes in the block to given byte.
      /// </summary>
      INLINE void set(const uint8_t v) 
      {
         CppCore::bytedup(v, *(T*)this);
      }

      /// <summary>
      /// Xors this Block with arbitrary sized memory v.
      /// Processes only min(len, blocksize) data.
      /// </summary>
      INLINE void xor_(const void* v, size_t len)
      {
         len = MIN(len, N8);
         uint8_t* p  = (uint8_t*)v;
         uint8_t* pe = p + len;
         uint8_t* b = u8;
      #if defined(CPPCORE_CPU_64BIT)
         for (; p+8 <= pe; p+=8, b+=8)
            *((uint64_t*)b) ^= *((uint64_t*)p);
         if (p+4 <= pe) {
      #else
         while (p+4 <= pe) {
      #endif
            *((uint32_t*)b) ^= *((uint32_t*)p);
            p+=4; b+=4;
         }
         if (p+2 <= pe) {
            *((uint16_t*)b) ^= *((uint16_t*)p);
            p+=2; b+=2;
         }
         if (p < pe) {
            *b ^= *p;
         }
      }

   public:
      INLINE T operator ^ (const T& v) const
      {
         T r;
         CppCore::xor_(v, *(T*)this, r);
         return r;
      }
      INLINE void operator ^= (const T& v)
      {
         CppCore::xor_(v, *(T*)this, *(T*)this);
      }
   };

   /// <summary>
   /// Blocks with SIZE being multiples of 16 Bit
   /// </summary>
   template<typename T, size_t SIZE>
   class Block16x : public Block<T, SIZE>
   {
      static_assert(SIZE % 2 == 0);
   };

   /// <summary>
   /// Blocks with SIZE being multiples of 32 Bit
   /// </summary>
   template<typename T, size_t SIZE>
   class Block32x : public Block16x<T, SIZE>
   {
      static_assert(SIZE % 4 == 0);

   public:
      /// <summary>
      /// Flips endianess of all 32-Bit chunks.
      /// </summary>
      INLINE void flipEndian32()
      {
         CPPCORE_UNROLL
         for (size_t i = 0; i < this->N32; i++)
            this->u32[i] = CppCore::loadr32(&this->u32[i]);
      }
   };

   /// <summary>
   /// Blocks with SIZE being multiples of 64 Bit
   /// </summary>
   template<typename T, size_t SIZE>
   class Block64x : public Block32x<T, SIZE>
   {
      static_assert(SIZE % 8 == 0);

   public:
      /// <summary>
      /// Flips endianess of all 64-Bit chunks.
      /// </summary>
      INLINE void flipEndian64()
      {
         CPPCORE_UNROLL
         for (size_t i = 0; i < this->N64; i++)
            this->u64[i] = CppCore::loadr64(&this->u64[i]);
      }
   };

   /// <summary>
   /// Blocks with SIZE being multiples of 128 Bit
   /// </summary>
   template<typename T, size_t SIZE>
   class Block128x : public Block64x<T, SIZE>
   {
      static_assert(SIZE % 16 == 0);
   };

   /// <summary>
   /// Blocks with SIZE being multiples of 256 Bit
   /// </summary>
   template<typename T, size_t SIZE>
   class Block256x : public Block128x<T, SIZE>
   {
      static_assert(SIZE % 32 == 0);
   };

   /// <summary>
   /// Blocks with SIZE being multiples of 512 Bit
   /// </summary>
   template<typename T, size_t SIZE>
   class Block512x : public Block256x<T, SIZE>
   {
      static_assert(SIZE % 64 == 0);
   };

   //////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////

   class Block64   : public Block64x <Block64,   8>    { };
   class Block96   : public Block32x <Block96,   12>   { };
   class Block128  : public Block128x<Block128,  16>   { };
   class Block160  : public Block32x <Block160,  20>   { };
   class Block192  : public Block64x <Block192,  24>   { };
   class Block224  : public Block32x <Block224,  28>   { };
   class Block256  : public Block256x<Block256,  32>   { };
   class Block288  : public Block32x <Block288,  36>   { };
   class Block320  : public Block64x <Block320,  40>   { };
   class Block352  : public Block32x <Block352,  44>   { };

   class Block512  : public Block512x<Block512,  64>   { };
   class Block1024 : public Block512x<Block1024, 128>  { };
   class Block2048 : public Block512x<Block2048, 256>  { };
   class Block4096 : public Block512x<Block4096, 512>  { };
   class Block8192 : public Block512x<Block8192, 1024> { };
}
