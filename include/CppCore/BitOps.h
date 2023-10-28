#pragma once

#include <CppCore/Root.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Count of 512-Bit chunks and a possible 256/128/64/32/16/8 tail
#define CPPCORE_CHUNK_COUNT512(x)                \
   constexpr size_t N512 = (sizeof(x) / 64);     \
   constexpr size_t N256 = (sizeof(x) % 64) / 32;\
   constexpr size_t N128 = (sizeof(x) % 32) / 16;\
   constexpr size_t N64  = (sizeof(x) % 16) / 8; \
   constexpr size_t N32  = (sizeof(x) % 8 ) / 4; \
   constexpr size_t N16  = (sizeof(x) % 4 ) / 2; \
   constexpr size_t N8   = (sizeof(x) % 2 );

// Count of 256-Bit chunks and a possible 128/64/32/16/8 tail
#define CPPCORE_CHUNK_COUNT256(x)                \
   constexpr size_t N512 = 0;                    \
   constexpr size_t N256 = (sizeof(x) / 32);     \
   constexpr size_t N128 = (sizeof(x) % 32) / 16;\
   constexpr size_t N64  = (sizeof(x) % 16) / 8; \
   constexpr size_t N32  = (sizeof(x) % 8 ) / 4; \
   constexpr size_t N16  = (sizeof(x) % 4 ) / 2; \
   constexpr size_t N8   = (sizeof(x) % 2 );

// Count of 128-Bit chunks and a possible 64/32/16/8 tail
#define CPPCORE_CHUNK_COUNT128(x)               \
   constexpr size_t N512 = 0;                   \
   constexpr size_t N256 = 0;                   \
   constexpr size_t N128 = (sizeof(x) / 16);    \
   constexpr size_t N64  = (sizeof(x) % 16) / 8;\
   constexpr size_t N32  = (sizeof(x) % 8 ) / 4;\
   constexpr size_t N16  = (sizeof(x) % 4 ) / 2;\
   constexpr size_t N8   = (sizeof(x) % 2 );

// Count of 64-Bit chunks and a possible 32/16/8 tail
#define CPPCORE_CHUNK_COUNT64(x)                \
   constexpr size_t N512 = 0;                   \
   constexpr size_t N256 = 0;                   \
   constexpr size_t N128 = 0;                   \
   constexpr size_t N64  = (sizeof(x) / 8);     \
   constexpr size_t N32  = (sizeof(x) % 8) / 4; \
   constexpr size_t N16  = (sizeof(x) % 4) / 2; \
   constexpr size_t N8   = (sizeof(x) % 2);

// Count of 32-Bit chunks and a possible 16/8 tail
#define CPPCORE_CHUNK_COUNT32(x)                \
   constexpr size_t N512 = 0;                   \
   constexpr size_t N256 = 0;                   \
   constexpr size_t N128 = 0;                   \
   constexpr size_t N64  = 0;                   \
   constexpr size_t N32  = (sizeof(x) / 4);     \
   constexpr size_t N16  = (sizeof(x) % 4) / 2; \
   constexpr size_t N8   = (sizeof(x) % 2);

// Select which one to use based on CPU
#if defined(CPPCORE_CPU_64BIT)
#define CPPCORE_CHUNK_COUNT(x) CPPCORE_CHUNK_COUNT64(x)
#else
#define CPPCORE_CHUNK_COUNT(x) CPPCORE_CHUNK_COUNT32(x)
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE)
#define CPPCORE_CHUNK_LOAD128(t,p)    (alignof(t)%16==0) ? _mm_load_si128 ((__m128i*)p)    : _mm_loadu_si128 ((__m128i*)p)
#define CPPCORE_CHUNK_STORE128(t,p,v) (alignof(t)%16==0) ? _mm_store_si128((__m128i*)p, v) : _mm_storeu_si128((__m128i*)p, v)
#define CPPCORE_CHUNK_STEP128_X(forward, p128)          \
   CPPCORE_UNROLL                                       \
   for (size_t i = 0; i < N128; i++) {                  \
      if constexpr (!forward) { px -= 16U; }            \
      __m128i* px128 = (__m128i*)px;                    \
      p128;                                             \
      if constexpr (forward) { px += 16U; }             \
   }
#define CPPCORE_CHUNK_STEP128_XY(forward, p128)         \
   CPPCORE_UNROLL                                       \
   for (size_t i = 0; i < N128; i++) {                  \
      if constexpr (!forward) { px -= 16U; py -= 16U; } \
      __m128i* px128 = (__m128i*)px;                    \
      __m128i* py128 = (__m128i*)py;                    \
      p128;                                             \
      if constexpr (forward) { px += 16U; py += 16U; }  \
   }
#define CPPCORE_CHUNK_STEP128_XYZ(forward, p128)        \
   CPPCORE_UNROLL                                       \
   for (size_t i = 0; i < N128; i++) {                  \
      if constexpr (!forward) {                         \
         px -= 16U; py -= 16U; pz -= 16U;               \
      }                                                 \
      __m128i* px128 = (__m128i*)px;                    \
      __m128i* py128 = (__m128i*)py;                    \
      __m128i* pz128 = (__m128i*)pz;                    \
      p128;                                             \
      if constexpr (forward) {                          \
         px += 16U; py += 16U; pz += 16U;               \
      }                                                 \
   }
#elif defined(CPPCORE_CPUFEAT_ARM_NEON)
#define CPPCORE_CHUNK_LOAD128(t,p)    vld1q_u32 ((uint32_t*)p)
#define CPPCORE_CHUNK_STORE128(t,p,v) vst1q_u32((uint32_t*)p, v)
#define CPPCORE_CHUNK_STEP128_X(forward, p128)          \
   CPPCORE_UNROLL                                       \
   for (size_t i = 0; i < N128; i++) {                  \
      if constexpr (!forward) { px -= 16U; }            \
      uint32x4_t* px128 = (uint32x4_t*)px;              \
      p128;                                             \
      if constexpr (forward) { px += 16U; }             \
   }
#define CPPCORE_CHUNK_STEP128_XY(forward, p128)         \
   CPPCORE_UNROLL                                       \
   for (size_t i = 0; i < N128; i++) {                  \
      if constexpr (!forward) { px -= 16U; py -= 16U; } \
      uint32x4_t* px128 = (uint32x4_t*)px;              \
      uint32x4_t* py128 = (uint32x4_t*)py;              \
      p128;                                             \
      if constexpr (forward) { px += 16U; py += 16U; }  \
   }
#define CPPCORE_CHUNK_STEP128_XYZ(forward, p128)        \
   CPPCORE_UNROLL                                       \
   for (size_t i = 0; i < N128; i++) {                  \
      if constexpr (!forward) {                         \
         px -= 16U; py -= 16U; pz -= 16U;               \
      }                                                 \
      uint32x4_t* px128 = (uint32x4_t*)px;              \
      uint32x4_t* py128 = (uint32x4_t*)py;              \
      uint32x4_t* pz128 = (uint32x4_t*)pz;              \
      p128;                                             \
      if constexpr (forward) {                          \
         px += 16U; py += 16U; pz += 16U;               \
      }                                                 \
   }
#else
#define CPPCORE_CHUNK_STEP128_X(forward, p128)
#define CPPCORE_CHUNK_STEP128_XY(forward, p128)
#define CPPCORE_CHUNK_STEP128_XYZ(forward, p128)
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
#define CPPCORE_CHUNK_LOAD256(t, p)   (alignof(t)%32==0) ? _mm256_load_si256((__m256i*)p)     : _mm256_loadu_si256((__m256i*)p)
#define CPPCORE_CHUNK_STORE256(t,p,v) (alignof(t)%32==0) ? _mm256_store_si256((__m256i*)p, v) : _mm256_storeu_si256((__m256i*)p, v)
#define CPPCORE_CHUNK_STEP256_X(forward, p256)       \
   CPPCORE_UNROLL                                    \
   for (size_t i = 0; i < N256; i++) {               \
      if constexpr (!forward) { px -= 32U; }         \
      __m256i* px256 = (__m256i*)px;                 \
      p256;                                          \
      if constexpr (forward) { px += 32U; }          \
   }
#define CPPCORE_CHUNK_STEP256_XY(forward, p256)         \
   CPPCORE_UNROLL                                       \
   for (size_t i = 0; i < N256; i++) {                  \
      if constexpr (!forward) { px -= 32U; py -= 32U; } \
      __m256i* px256 = (__m256i*)px;                    \
      __m256i* py256 = (__m256i*)py;                    \
      p256;                                             \
      if constexpr (forward) { px += 32U; py += 32U; }  \
   }
#define CPPCORE_CHUNK_STEP256_XYZ(forward, p256)        \
   CPPCORE_UNROLL                                       \
   for (size_t i = 0; i < N256; i++) {                  \
      if constexpr (!forward) {                         \
         px -= 32U; py -= 32U; pz -= 32U;               \
      }                                                 \
      __m256i* px256 = (__m256i*)px;                    \
      __m256i* py256 = (__m256i*)py;                    \
      __m256i* pz256 = (__m256i*)pz;                    \
      p256;                                             \
      if constexpr (forward) {                          \
         px += 32U; py += 32U; pz += 32U;               \
      }                                                 \
   }
#else
#define CPPCORE_CHUNK_STEP256_X(forward, p256)
#define CPPCORE_CHUNK_STEP256_XY(forward, p256)
#define CPPCORE_CHUNK_STEP256_XYZ(forward, p256)
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
#define CPPCORE_CHUNK_LOAD512(t, p)   (alignof(t)%64==0) ? _mm512_load_si512((__m512i*)p)     : _mm512_loadu_si512((__m512i*)p)
#define CPPCORE_CHUNK_STORE512(t,p,v) (alignof(t)%64==0) ? _mm512_store_si512((__m512i*)p, v) : _mm512_storeu_si512((__m512i*)p, v)
#define CPPCORE_CHUNK_STEP512_X(forward, p512) \
   CPPCORE_UNROLL                              \
   for (size_t i = 0; i < N512; i++) {         \
      if constexpr (!forward) { px -= 64U; }   \
      __m512i* px512 = (__m512i*)px;           \
      p512;                                    \
      if constexpr (forward) { px += 64U; }    \
   }
#define CPPCORE_CHUNK_STEP512_XY(forward, p512)          \
   CPPCORE_UNROLL                                        \
   for (size_t i = 0; i < N512; i++) {                   \
      if constexpr (!forward) { px -= 64U; py -= 64U; }  \
      __m512i* px512 = (__m512i*)px;                     \
      __m512i* py512 = (__m512i*)py;                     \
      p512;                                              \
      if constexpr (forward) { px += 64U; py += 64U; }   \
   }
#define CPPCORE_CHUNK_STEP512_XYZ(forward, p512)         \
   CPPCORE_UNROLL                                        \
   for (size_t i = 0; i < N512; i++) {                   \
      if constexpr (!forward) {                          \
         px -= 64U; py -= 64U; pz -= 64U;                \
      }                                                  \
      __m512i* px512 = (__m512i*)px;                     \
      __m512i* py512 = (__m512i*)py;                     \
      __m512i* pz512 = (__m512i*)pz;                     \
      p512;                                              \
      if constexpr (forward) {                           \
         px += 64U; py += 64U; pz += 64U;                \
      }                                                  \
   }
#else
#define CPPCORE_CHUNK_STEP512_X(forward, p512)
#define CPPCORE_CHUNK_STEP512_XY(forward, p512)
#define CPPCORE_CHUNK_STEP512_XYZ(forward, p512)
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Base Macro for op(x).
#define CPPCORE_CHUNK_PROCESS_BASE_X(x, type, forward, p512, p256, p128, p64, p32, p16, p8) \
   uint8_t* px = (uint8_t*)&(x);                   \
   if constexpr (!forward) {                       \
      px += sizeof(type);                          \
   }                                               \
   CPPCORE_CHUNK_STEP512_X(forward, p512)          \
   CPPCORE_CHUNK_STEP256_X(forward, p256)          \
   CPPCORE_CHUNK_STEP128_X(forward, p128)          \
   CPPCORE_UNROLL                                  \
   for (size_t i = 0; i < N64; i++) {              \
      if constexpr (!forward) { px -= 8U; }        \
      uint64_t* px64 = (uint64_t*)px;              \
      p64;                                         \
      if constexpr (forward) { px += 8U; }         \
   }                                               \
   CPPCORE_UNROLL                                  \
   for (size_t i = 0; i < N32; i++) {              \
      if constexpr (!forward) { px -= 4U; }        \
      uint32_t* px32 = (uint32_t*)px;              \
      p32;                                         \
      if constexpr (forward) { px += 4U; }         \
   }                                               \
   if (N16) {                                      \
      if constexpr (!forward) { px -= 2U; }        \
      uint16_t* px16 = (uint16_t*)px;              \
      p16;                                         \
      if constexpr (forward && N8) { px += 2U; }   \
   }                                               \
   if (N8) {                                       \
      if constexpr (!forward) { px -= 1U; }        \
      uint8_t* px8  = (uint8_t*)px;                \
      p8;                                          \
   }

// Process chunks of type. For op(x). 
// Requires 64-Bit and 32-Bit Op and will select based on CPU
#define CPPCORE_CHUNK_PROCESS_X(x, type, forward, p64, p32, p16, p8)     \
   CPPCORE_CHUNK_COUNT(type)                                             \
   CPPCORE_CHUNK_PROCESS_BASE_X(x, type, forward, , , , p64, p32, p16, p8)

// Process chunks of type. For op(x). 
// Requires 128-Bit Op additionally
#define CPPCORE_CHUNK_PROCESS128_X(x, type, forward, p128, p64, p32, p16, p8) \
   CPPCORE_CHUNK_COUNT128(type)                                               \
   CPPCORE_CHUNK_PROCESS_BASE_X(x, type, forward, , , p128, p64, p32, p16, p8)

// Process chunks of type. For op(x). 
// Requires 256-Bit Op additionally
#define CPPCORE_CHUNK_PROCESS256_X(x, type, forward, p256, p128, p64, p32, p16, p8) \
   CPPCORE_CHUNK_COUNT256(type)                                                     \
   CPPCORE_CHUNK_PROCESS_BASE_X(x, type, forward, , p256, p128, p64, p32, p16, p8)

// Process chunks of type. For op(x). 
// Requires 512-Bit Op additionally
#define CPPCORE_CHUNK_PROCESS512_X(x, type, forward, p512, p256, p128, p64, p32, p16, p8) \
   CPPCORE_CHUNK_COUNT512(type)                                                           \
   CPPCORE_CHUNK_PROCESS_BASE_X(x, type, forward, p512, p256, p128, p64, p32, p16, p8)

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Base Macro for op(x, y).
#define CPPCORE_CHUNK_PROCESS_BASE_XY(x, y, type, forward, p512, p256, p128, p64, p32, p16, p8) \
   uint8_t* px = (uint8_t*)&(x);                      \
   uint8_t* py = (uint8_t*)&(y);                      \
   if (!forward) {                                    \
      px += sizeof(type);                             \
      py += sizeof(type);                             \
   }                                                  \
   CPPCORE_CHUNK_STEP512_XY(forward, p512)            \
   CPPCORE_CHUNK_STEP256_XY(forward, p256)            \
   CPPCORE_CHUNK_STEP128_XY(forward, p128)            \
   CPPCORE_UNROLL                                     \
   for (size_t i = 0; i < N64; i++) {                 \
      if constexpr (!forward) { px -= 8U; py -= 8U; } \
      uint64_t* px64 = (uint64_t*)px;                 \
      uint64_t* py64 = (uint64_t*)py;                 \
      p64;                                            \
      if constexpr (forward) { px += 8U; py += 8U; }  \
   }                                                  \
   CPPCORE_UNROLL                                     \
   for (size_t i = 0; i < N32; i++) {                 \
      if constexpr (!forward) { px -= 4U; py -= 4U; } \
      uint32_t* px32 = (uint32_t*)px;                 \
      uint32_t* py32 = (uint32_t*)py;                 \
      p32;                                            \
      if constexpr (forward) { px += 4U; py += 4U; }  \
   }                                                  \
   if (N16) {                                         \
      if constexpr (!forward) { px -= 2U; py -= 2U; } \
      uint16_t* px16 = (uint16_t*)px;                 \
      uint16_t* py16 = (uint16_t*)py;                 \
      p16;                                            \
      if constexpr (forward && N8) {                  \
         px += 2U; py += 2U;                          \
      }                                               \
   }                                                  \
   if (N8) {                                          \
      if constexpr (!forward) { px -= 1U; py -= 1U; } \
      uint8_t* px8 = (uint8_t*)px;                    \
      uint8_t* py8 = (uint8_t*)py;                    \
      p8;                                             \
   }

// Process chunks of type. For op(x, y). 
// Requires 64-Bit and 32-Bit Op and will select based on CPU
#define CPPCORE_CHUNK_PROCESS_XY(x, y, type, forward, p64, p32, p16, p8)     \
   CPPCORE_CHUNK_COUNT(type)                                                 \
   CPPCORE_CHUNK_PROCESS_BASE_XY(x, y, type, forward, , , , p64, p32, p16, p8)

// Process chunks of type. For op(x, y). 
// Requires 128-Bit Op additionally
#define CPPCORE_CHUNK_PROCESS128_XY(x, y, type, forward, p128, p64, p32, p16, p8) \
   CPPCORE_CHUNK_COUNT128(type)                                                   \
   CPPCORE_CHUNK_PROCESS_BASE_XY(x, y, type, forward, , , p128, p64, p32, p16, p8)

// Process chunks of type. For op(x, y). 
// Requires 256-Bit Op additionally
#define CPPCORE_CHUNK_PROCESS256_XY(x, y, type, forward, p256, p128, p64, p32, p16, p8) \
   CPPCORE_CHUNK_COUNT256(type)                                                         \
   CPPCORE_CHUNK_PROCESS_BASE_XY(x, y, type, forward, , p256, p128, p64, p32, p16, p8)

// Process chunks of type. For op(x, y). 
// Requires 512-Bit Op additionally
#define CPPCORE_CHUNK_PROCESS512_XY(x, y, type, forward, p512, p256, p128, p64, p32, p16, p8) \
   CPPCORE_CHUNK_COUNT512(type)                                                               \
   CPPCORE_CHUNK_PROCESS_BASE_XY(x, y, type, forward, p512, p256, p128, p64, p32, p16, p8)

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Base Macro for op(x, y, z).
#define CPPCORE_CHUNK_PROCESS_BASE_XYZ(x, y, z, type, forward, p512, p256, p128, p64, p32, p16, p8) \
   uint8_t* px = (uint8_t*)&(x);                           \
   uint8_t* py = (uint8_t*)&(y);                           \
   uint8_t* pz = (uint8_t*)&(z);                           \
   if constexpr (!forward) {                               \
      px += sizeof(type);                                  \
      py += sizeof(type);                                  \
      pz += sizeof(type);                                  \
   }                                                       \
   CPPCORE_CHUNK_STEP512_XYZ(forward, p512)                \
   CPPCORE_CHUNK_STEP256_XYZ(forward, p256)                \
   CPPCORE_CHUNK_STEP128_XYZ(forward, p128)                \
   CPPCORE_UNROLL                                          \
   for (size_t i = 0; i < N64; i++) {                      \
      if constexpr (!forward) {                            \
         px -= 8U; py -= 8U; pz -= 8U;                     \
      }                                                    \
      uint64_t* px64 = (uint64_t*)px;                      \
      uint64_t* py64 = (uint64_t*)py;                      \
      uint64_t* pz64 = (uint64_t*)pz;                      \
      p64;                                                 \
      if constexpr (forward) {                             \
         px += 8U; py += 8U; pz += 8U;                     \
      }                                                    \
   }                                                       \
   CPPCORE_UNROLL                                          \
   for (size_t i = 0; i < N32; i++) {                      \
      if constexpr (!forward) {                            \
         px -= 4U; py -= 4U; pz -= 4U;                     \
      }                                                    \
      uint32_t* px32 = (uint32_t*)px;                      \
      uint32_t* py32 = (uint32_t*)py;                      \
      uint32_t* pz32 = (uint32_t*)pz;                      \
      p32;                                                 \
      if constexpr (forward) {                             \
         px += 4U; py += 4U; pz += 4U;                     \
      }                                                    \
   }                                                       \
   if (N16) {                                              \
      if constexpr (!forward) {                            \
         px -= 2U; py -= 2U; pz -= 2U;                     \
      }                                                    \
      uint16_t* px16 = (uint16_t*)px;                      \
      uint16_t* py16 = (uint16_t*)py;                      \
      uint16_t* pz16 = (uint16_t*)pz;                      \
      p16;                                                 \
      if constexpr (forward && N8) {                       \
         px += 2U; py += 2U; pz += 2U;                     \
      }                                                    \
   }                                                       \
   if (N8) {                                               \
      if constexpr (!forward) {                            \
         px -= 1U; py -= 1U; pz -= 1U;                     \
      }                                                    \
      uint8_t* px8 = (uint8_t*)px;                         \
      uint8_t* py8 = (uint8_t*)py;                         \
      uint8_t* pz8 = (uint8_t*)pz;                         \
      p8;                                                  \
   }

// Process chunks of type. For op(x, y, z). 
// Requires 64-Bit and 32-Bit Op and will select based on CPU
#define CPPCORE_CHUNK_PROCESS_XYZ(x, y, z, type, forward, p64, p32, p16, p8)     \
   CPPCORE_CHUNK_COUNT(type)                                                     \
   CPPCORE_CHUNK_PROCESS_BASE_XYZ(x, y, z, type, forward, , , , p64, p32, p16, p8)

// Process chunks of type. For op(x, y, z). 
// Requires 128-Bit Op additionally
#define CPPCORE_CHUNK_PROCESS128_XYZ(x, y, z, type, forward, p128, p64, p32, p16, p8) \
   CPPCORE_CHUNK_COUNT128(type)                                                       \
   CPPCORE_CHUNK_PROCESS_BASE_XYZ(x, y, z, type, forward, , , p128, p64, p32, p16, p8)

// Process chunks of type. For op(x, y, z). 
// Requires 256-Bit Op additionally
#define CPPCORE_CHUNK_PROCESS256_XYZ(x, y, z, type, forward, p256, p128, p64, p32, p16, p8) \
   CPPCORE_CHUNK_COUNT256(type)                                                             \
   CPPCORE_CHUNK_PROCESS_BASE_XYZ(x, y, z, type, forward, , p256, p128, p64, p32, p16, p8)

// Process chunks of type. For op(x, y, z). 
// Requires 512-Bit Op additionally
#define CPPCORE_CHUNK_PROCESS512_XYZ(x, y, z, type, forward, p512, p256, p128, p64, p32, p16, p8) \
   CPPCORE_CHUNK_COUNT512(type)                                                                   \
   CPPCORE_CHUNK_PROCESS_BASE_XYZ(x, y, z, type, forward, p512, p256, p128, p64, p32, p16, p8)

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace CppCore
{
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BYTEMASKEQUAL
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns a bit set to 1 for each equal byte in v1 and v2 (16 Bytes input -> 16 Bits return).
   /// For instance, returns 0xFFFF if all equal, 0x0000 if none. Requires SSE2.
   /// </summary>
   INLINE static uint32_t bytemaskequal128(const __m128i& v1, const __m128i& v2)
   {
      return (uint32_t)_mm_movemask_epi8(_mm_cmpeq_epi8(v1, v2));
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Returns a bit set to 1 for each equal byte in v1 and v2 (32 Bytes input -> 32 Bits returned).
   /// For instance, returns 0xFFFFFFFF if all equal, 0x00000000 if none. Requires AVX2.
   /// </summary>
   INLINE static uint32_t bytemaskequal256(const __m256i& v1, const __m256i& v2)
   {
      return (uint32_t)_mm256_movemask_epi8(_mm256_cmpeq_epi8(v1, v2));
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512BW)
   /// <summary>
   /// Returns a bit set to 1 for each equal byte in v1 and v2 (64 Bytes input -> 64 Bits returned).
   /// For instance, returns 0xFFFFFFFFFFFFFFFF if all equal, 0x0000000000000000 if none. Requires AVX512BW.
   /// </summary>
   INLINE static uint64_t bytemaskequal512(const __m512i& v1, const __m512i& v2)
   {
      return _mm512_cmpeq_epi8_mask(v1, v2);
   }
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // EQUAL
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns x == y for 8-bit integer.
   /// </summary>
   static INLINE bool equal8(uint8_t x, uint8_t y)
   {
      return x == y;
   }

   /// <summary>
   /// Returns x == y for 16-bit integer.
   /// </summary>
   static INLINE bool equal16(uint16_t x, uint16_t y)
   {
      return x == y;
   }

   /// <summary>
   /// Returns x == y for 32-bit integer.
   /// </summary>
   static INLINE bool equal32(uint32_t x, uint32_t y)
   {
      return x == y;
   }

   /// <summary>
   /// Returns x == y for 64-bit integer.
   /// </summary>
   static INLINE bool equal64(uint64_t x, uint64_t y)
   {
      return x == y;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns x == y for 128-bit sse2 integer.
   /// </summary>
   static INLINE bool equal128(const __m128i& v1, const __m128i& v2)
   {
   #if defined(CPPCORE_CPUFEAT_SSE41)
      const __m128i t = _mm_sub_epi8(v1, v2);
      return _mm_testz_si128(t, t);
   #else
      return 0xFFFFU == CppCore::bytemaskequal128(v1, v2);
   #endif
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Returns x == y for 256-bit avx2 integer.
   /// </summary>
   static INLINE bool equal256(const __m256i& v1, const __m256i& v2)
   {
      const __m256i t = _mm256_sub_epi8(v1, v2);
      return _mm256_testz_si256(t, t);
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512BW)
   /// <summary>
   /// Returns x == y for 512-bit avx512 integer.
   /// </summary>
   static INLINE bool equal512(const __m512i& v1, const __m512i& v2)
   {
      return 0xFFFFFFFFFFFFFFFFULL == CppCore::bytemaskequal512(v1, v2);
   }
#endif

   /// <summary>
   /// Returns x == y for any sized integer.
   /// </summary>
   template<typename UINT>
   static INLINE bool equal(const UINT& x, const UINT& y)
   {
   #if defined(CPPCORE_CPUFEAT_AVX512BW)
      CPPCORE_CHUNK_PROCESS512_XY(x, y, UINT, true,
         if (!CppCore::equal512(CPPCORE_CHUNK_LOAD512(UINT, px512), CPPCORE_CHUNK_LOAD512(UINT, py512))) return false;,
         if (!CppCore::equal256(CPPCORE_CHUNK_LOAD256(UINT, px256), CPPCORE_CHUNK_LOAD256(UINT, py256))) return false;,
         if (!CppCore::equal128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128))) return false;,
         if (!CppCore::equal64 (*px64,  *py64 )) return false;,
         if (!CppCore::equal32 (*px32,  *py32 )) return false;,
         if (!CppCore::equal16 (*px16,  *py16 )) return false;,
         if (!CppCore::equal8  (*px8,   *py8  )) return false;)
   #elif defined(CPPCORE_CPUFEAT_AVX2)
      CPPCORE_CHUNK_PROCESS256_XY(x, y, UINT, true,
         if (!CppCore::equal256(CPPCORE_CHUNK_LOAD256(UINT, px256), CPPCORE_CHUNK_LOAD256(UINT, py256))) return false;,
         if (!CppCore::equal128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128))) return false;,
         if (!CppCore::equal64 (*px64,  *py64 )) return false;,
         if (!CppCore::equal32 (*px32,  *py32 )) return false;,
         if (!CppCore::equal16 (*px16,  *py16 )) return false;,
         if (!CppCore::equal8  (*px8,   *py8  )) return false;)
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      CPPCORE_CHUNK_PROCESS128_XY(x, y, UINT, true,
         if (!CppCore::equal128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128))) return false;,
         if (!CppCore::equal64 (*px64,  *py64 )) return false;,
         if (!CppCore::equal32 (*px32,  *py32 )) return false;,
         if (!CppCore::equal16 (*px16,  *py16 )) return false;,
         if (!CppCore::equal8  (*px8,   *py8  )) return false;)
   #else
      CPPCORE_CHUNK_PROCESS_XY(x, y, UINT, true,
         if (!CppCore::equal64 (*px64,  *py64 )) return false;,
         if (!CppCore::equal32 (*px32,  *py32 )) return false;,
         if (!CppCore::equal16 (*px16,  *py16 )) return false;,
         if (!CppCore::equal8  (*px8,   *py8  )) return false;)
   #endif
      return true;
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE bool equal<uint8_t>(const uint8_t& x, const uint8_t& y)
   {
      return CppCore::equal8(x, y);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE bool equal<uint16_t>(const uint16_t& x, const uint16_t& y)
   {
      return CppCore::equal16(x, y);
   }

      /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE bool equal<uint32_t>(const uint32_t& x, const uint32_t& y)
   {
      return CppCore::equal32(x, y);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE bool equal<uint64_t>(const uint64_t& x, const uint64_t& y)
   {
      return CppCore::equal64(x, y);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // TESTZERO
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns x == 0 for 8-bit integer.
   /// </summary>
   static INLINE bool testzero8(uint8_t x)
   {
      return x == 0;
   }

   /// <summary>
   /// Returns x == 0 for 16-bit integer.
   /// </summary>
   static INLINE bool testzero16(uint16_t x)
   {
      return x == 0;
   }

   /// <summary>
   /// Returns x == 0 for 32-bit integer.
   /// </summary>
   static INLINE bool testzero32(uint32_t x)
   {
      return x == 0;
   }

   /// <summary>
   /// Returns x == 0 for 64-bit integer.
   /// </summary>
   static INLINE bool testzero64(uint64_t x)
   {
      return x == 0;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns x == 0 for 128-bit sse2 integer.
   /// </summary>
   static INLINE bool testzero128(const __m128i& x)
   {
   #if defined(CPPCORE_CPUFEAT_SSE41)
      return _mm_testz_si128(x, x);
   #else
      return CppCore::equal128(x, _mm_setzero_si128());
   #endif
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
   /// <summary>
   /// Returns x == 0 for 256-bit avx integer.
   /// </summary>
   static INLINE bool testzero256(const __m256i& x)
   {
      return _mm256_testz_si256(x, x);
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512BW)
   /// <summary>
   /// Returns x == 0 for 512-bit avx512 integer.
   /// </summary>
   static INLINE bool testzero512(const __m512i& x)
   {
      return _mm512_test_epi8_mask(x, x) == 0;
      //return CppCore::equal512(x, _mm512_setzero_si512());
   }
#endif

   /// <summary>
   /// Returns x == 0 for any sized integer.
   /// </summary>
   template<typename UINT>
   static INLINE bool testzero(const UINT& x)
   {
   #if defined(CPPCORE_CPUFEAT_AVX512BW)
      CPPCORE_CHUNK_PROCESS512_X(x, UINT, true,
         if (!CppCore::testzero512(CPPCORE_CHUNK_LOAD512(UINT, px512))) return false;,
         if (!CppCore::testzero256(CPPCORE_CHUNK_LOAD256(UINT, px256))) return false;,
         if (!CppCore::testzero128(CPPCORE_CHUNK_LOAD128(UINT, px128))) return false;,
         if (!CppCore::testzero64 (*px64 )) return false;,
         if (!CppCore::testzero32 (*px32 )) return false;,
         if (!CppCore::testzero16 (*px16 )) return false;,
         if (!CppCore::testzero8  (*px8  )) return false;)
   #elif defined(CPPCORE_CPUFEAT_AVX2)
      CPPCORE_CHUNK_PROCESS256_X(x, UINT, true,
         if (!CppCore::testzero256(CPPCORE_CHUNK_LOAD256(UINT, px256))) return false;,
         if (!CppCore::testzero128(CPPCORE_CHUNK_LOAD128(UINT, px128))) return false;,
         if (!CppCore::testzero64 (*px64 )) return false;,
         if (!CppCore::testzero32 (*px32 )) return false;,
         if (!CppCore::testzero16 (*px16 )) return false;,
         if (!CppCore::testzero8  (*px8  )) return false;)
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      CPPCORE_CHUNK_PROCESS128_X(x, UINT, true,
         if (!CppCore::testzero128(CPPCORE_CHUNK_LOAD128(UINT, px128))) return false;,
         if (!CppCore::testzero64 (*px64 )) return false;,
         if (!CppCore::testzero32 (*px32 )) return false;,
         if (!CppCore::testzero16 (*px16 )) return false;,
         if (!CppCore::testzero8  (*px8  )) return false;)
   #else
      CPPCORE_CHUNK_PROCESS_X(x, UINT, true,
         if (!CppCore::testzero64(*px64)) return false;,
         if (!CppCore::testzero32(*px32)) return false;,
         if (!CppCore::testzero16(*px16)) return false;,
         if (!CppCore::testzero8 (*px8 )) return false;)
   #endif
         return true;
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE bool testzero<uint8_t>(const uint8_t& x)
   {
      return CppCore::testzero8(x);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE bool testzero<uint16_t>(const uint16_t& x)
   {
      return CppCore::testzero16(x);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE bool testzero<uint32_t>(const uint32_t& x)
   {
      return CppCore::testzero32(x);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE bool testzero<uint64_t>(const uint64_t& x)
   {
      return CppCore::testzero64(x);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // CLEAR: x = 0
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Sets x = 0
   /// </summary>
   static INLINE void clear8(uint8_t& x)
   {
      x = 0U;
   }

   /// <summary>
   /// Sets x = 0
   /// </summary>
   static INLINE void clear16(uint16_t& x)
   {
      x = 0U;
   }

   /// <summary>
   /// Sets x = 0
   /// </summary>
   static INLINE void clear32(uint32_t& x)
   {
      x = 0U;
   }

   /// <summary>
   /// Sets x = 0
   /// </summary>
   static INLINE void clear64(uint64_t& x)
   {
      x = 0ULL;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Sets x = 0
   /// </summary>
   static INLINE void clear128(__m128i& x)
   {
      x = _mm_setzero_si128();
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
   /// <summary>
   /// Sets x = 0
   /// </summary>
   static INLINE void clear256(__m256i& x)
   {
      x = _mm256_setzero_si256();
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
   /// <summary>
   /// Sets x = 0
   /// </summary>
   static INLINE void clear512(__m512i& x)
   {
      x = _mm512_setzero_si512();
   }
#endif

   /// <summary>
   /// Sets x = 0
   /// </summary>
   template<typename UINT>
   static INLINE void clear(UINT& x)
   {
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      const __m512i ZERO512 = _mm512_setzero_si512();
      const __m256i ZERO256 = _mm256_setzero_si256();
      const __m128i ZERO128 = _mm_setzero_si128();
      CPPCORE_CHUNK_PROCESS512_X(x, UINT, true,
         CPPCORE_CHUNK_STORE512(UINT, px512, ZERO512); ,
         CPPCORE_CHUNK_STORE256(UINT, px256, ZERO256);,
         CPPCORE_CHUNK_STORE128(UINT, px128, ZERO128);,
         CppCore::clear64 (*px64); ,
         CppCore::clear32 (*px32); ,
         CppCore::clear16 (*px16); ,
         CppCore::clear8  (*px8);)
   #elif defined(CPPCORE_CPUFEAT_AVX)
      const __m256i ZERO256 = _mm256_setzero_si256();
      const __m128i ZERO128 = _mm_setzero_si128();
      CPPCORE_CHUNK_PROCESS256_X(x, UINT, true,
         CPPCORE_CHUNK_STORE256(UINT, px256, ZERO256);,
         CPPCORE_CHUNK_STORE128(UINT, px128, ZERO128);,
         CppCore::clear64 (*px64); ,
         CppCore::clear32 (*px32); ,
         CppCore::clear16 (*px16); ,
         CppCore::clear8  (*px8);)
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      const __m128i ZERO128 = _mm_setzero_si128();
      CPPCORE_CHUNK_PROCESS128_X(x, UINT, true,
         CPPCORE_CHUNK_STORE128(UINT, px128, ZERO128);,
         CppCore::clear64 (*px64); ,
         CppCore::clear32 (*px32); ,
         CppCore::clear16 (*px16); ,
         CppCore::clear8  (*px8);)
   #elif defined(CPPCORE_CPUFEAT_ARM_NEON)
      constexpr uint32x4_t ZERO128 = { 0ULL, 0ULL };
      CPPCORE_CHUNK_PROCESS128_X(x, UINT, true,
         CPPCORE_CHUNK_STORE128(UINT, px128, ZERO128);,
         CppCore::clear64 (*px64); ,
         CppCore::clear32 (*px32); ,
         CppCore::clear16 (*px16); ,
         CppCore::clear8  (*px8);)
   #else
      CPPCORE_CHUNK_PROCESS_X(x, UINT, true,
         CppCore::clear64(*px64); ,
         CppCore::clear32(*px32); ,
         CppCore::clear16(*px16); ,
         CppCore::clear8 (*px8);)
   #endif
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE void clear<uint8_t>(uint8_t& x)
   {
      return CppCore::clear8(x);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE void clear<uint16_t>(uint16_t& x)
   {
      return CppCore::clear16(x);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE void clear<uint32_t>(uint32_t& x)
   {
      return CppCore::clear32(x);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE void clear<uint64_t>(uint64_t& x)
   {
      return CppCore::clear64(x);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // CLONE: x = y
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Sets x = y
   /// </summary>
   static INLINE void clone8(uint8_t& x, const uint8_t& y)
   {
      x = y;
   }

   /// <summary>
   /// Sets x = y
   /// </summary>
   static INLINE void clone16(uint16_t& x, const uint16_t& y)
   {
      x = y;
   }

   /// <summary>
   /// Sets x = y
   /// </summary>
   static INLINE void clone32(uint32_t& x, const uint32_t& y)
   {
      x = y;
   }

   /// <summary>
   /// Sets x = y
   /// </summary>
   static INLINE void clone64(uint64_t& x, const uint64_t& y)
   {
      x = y;
   }

   /// <summary>
   /// Sets x = y
   /// </summary>
   template<typename UINT>
   static INLINE void clone(UINT& x, const UINT& y)
   {
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      CPPCORE_CHUNK_PROCESS512_XY(x, y, UINT, true,
         CPPCORE_CHUNK_STORE512(UINT, px512, CPPCORE_CHUNK_LOAD512(UINT, py512));,
         CPPCORE_CHUNK_STORE256(UINT, px256, CPPCORE_CHUNK_LOAD256(UINT, py256));,
         CPPCORE_CHUNK_STORE128(UINT, px128, CPPCORE_CHUNK_LOAD128(UINT, py128));,
         CppCore::clone64 (*px64, *py64);,
         CppCore::clone32 (*px32, *py32);,
         CppCore::clone16 (*px16, *py16);,
         CppCore::clone8  (*px8,  *py8);)
   #elif defined(CPPCORE_CPUFEAT_AVX)
      CPPCORE_CHUNK_PROCESS256_XY(x, y, UINT, true,
         CPPCORE_CHUNK_STORE256(UINT, px256, CPPCORE_CHUNK_LOAD256(UINT, py256));,
         CPPCORE_CHUNK_STORE128(UINT, px128, CPPCORE_CHUNK_LOAD128(UINT, py128));,
         CppCore::clone64 (*px64, *py64);,
         CppCore::clone32 (*px32, *py32);,
         CppCore::clone16 (*px16, *py16);,
         CppCore::clone8  (*px8,  *py8);)
   #elif defined(CPPCORE_CPUFEAT_SSE2) || defined(CPPCORE_CPUFEAT_ARM_NEON)
      CPPCORE_CHUNK_PROCESS128_XY(x, y, UINT, true,
         CPPCORE_CHUNK_STORE128(UINT, px128, CPPCORE_CHUNK_LOAD128(UINT, py128));,
         CppCore::clone64 (*px64, *py64);,
         CppCore::clone32 (*px32, *py32);,
         CppCore::clone16 (*px16, *py16);,
         CppCore::clone8  (*px8,  *py8);)
   #else
      CPPCORE_CHUNK_PROCESS_XY(x, y, UINT, true,
         CppCore::clone64(*px64, *py64); ,
         CppCore::clone32(*px32, *py32); ,
         CppCore::clone16(*px16, *py16); ,
         CppCore::clone8 (*px8,  *py8);)
   #endif
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE void clone<uint8_t>(uint8_t& x, const uint8_t& y)
   {
      CppCore::clone8(x, y);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE void clone<uint16_t>(uint16_t& x, const uint16_t& y)
   {
      CppCore::clone16(x, y);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE void clone<uint32_t>(uint32_t& x, const uint32_t& y)
   {
      CppCore::clone32(x, y);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE void clone<uint64_t>(uint64_t& x, const uint64_t& y)
   {
      CppCore::clone64(x, y);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // OR: x | y
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns x | y for 8-bit integer.
   /// </summary>
   static INLINE uint8_t or8(uint8_t x, uint8_t y)
   {
      return x | y;
   }

   /// <summary>
   /// Returns x | y for 16-bit integer.
   /// </summary>
   static INLINE uint16_t or16(uint16_t x, uint16_t y)
   {
      return x | y;
   }

   /// <summary>
   /// Returns x | y for 32-bit integer.
   /// </summary>
   static INLINE uint32_t or32(uint32_t x, uint32_t y)
   {
      return x | y;
   }

   /// <summary>
   /// Returns x | y for 64-bit integer.
   /// </summary>
   static INLINE uint64_t or64(uint64_t x, uint64_t y)
   {
      return x | y;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns x | y for 128-bit sse2 integer.
   /// </summary>
   static INLINE __m128i or128(const __m128i& x, const __m128i& y)
   {
      return _mm_or_si128(x, y);
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Returns x | y for 256-bit avx2 integer.
   /// </summary>
   static INLINE __m256i or256(const __m256i& x, const __m256i& y)
   {
      return _mm256_or_si256(x, y);
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
   /// <summary>
   /// Returns x | y for 512-bit avx512 integer.
   /// </summary>
   static INLINE __m512i or512(const __m512i& x, const __m512i& y)
   {
      return _mm512_or_si512(x, y);
   }
#endif

   /// <summary>
   /// Returns x | y for any sized integer.
   /// </summary>
   template<typename UINT>
   static INLINE void or_(const UINT& x, const UINT& y, UINT& z)
   {
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      CPPCORE_CHUNK_PROCESS512_XYZ(x, y, z, UINT, true,
         CPPCORE_CHUNK_STORE512(UINT, pz512, CppCore::or512(CPPCORE_CHUNK_LOAD512(UINT, px512), CPPCORE_CHUNK_LOAD512(UINT, py512)));,
         CPPCORE_CHUNK_STORE256(UINT, pz256, CppCore::or256(CPPCORE_CHUNK_LOAD256(UINT, px256), CPPCORE_CHUNK_LOAD256(UINT, py256)));,
         CPPCORE_CHUNK_STORE128(UINT, pz128, CppCore::or128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128)));,
         *pz64  = CppCore::or64 (*px64,  *py64); ,
         *pz32  = CppCore::or32 (*px32,  *py32); ,
         *pz16  = CppCore::or16 (*px16,  *py16); ,
         *pz8   = CppCore::or8  (*px8,   *py8);)
   #elif defined(CPPCORE_CPUFEAT_AVX2)
      CPPCORE_CHUNK_PROCESS256_XYZ(x, y, z, UINT, true,
         CPPCORE_CHUNK_STORE256(UINT, pz256, CppCore::or256(CPPCORE_CHUNK_LOAD256(UINT, px256), CPPCORE_CHUNK_LOAD256(UINT, py256)));,
         CPPCORE_CHUNK_STORE128(UINT, pz128, CppCore::or128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128)));,
         *pz64  = CppCore::or64 (*px64,  *py64); ,
         *pz32  = CppCore::or32 (*px32,  *py32); ,
         *pz16  = CppCore::or16 (*px16,  *py16); ,
         *pz8   = CppCore::or8  (*px8,   *py8);)
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      CPPCORE_CHUNK_PROCESS128_XYZ(x, y, z, UINT, true,
         CPPCORE_CHUNK_STORE128(UINT, pz128, CppCore::or128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128)));,
         *pz64  = CppCore::or64 (*px64,  *py64); ,
         *pz32  = CppCore::or32 (*px32,  *py32); ,
         *pz16  = CppCore::or16 (*px16,  *py16); ,
         *pz8   = CppCore::or8  (*px8,   *py8);)
   #else
      CPPCORE_CHUNK_PROCESS_XYZ(x, y, z, UINT, true,
         *pz64  = CppCore::or64 (*px64,  *py64); ,
         *pz32  = CppCore::or32 (*px32,  *py32); ,
         *pz16  = CppCore::or16 (*px16,  *py16); ,
         *pz8   = CppCore::or8  (*px8,   *py8);)
   #endif
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE void or_<uint8_t>(const uint8_t& x, const uint8_t& y, uint8_t& z)
   {
      z = CppCore::or8(x, y);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE void or_<uint16_t>(const uint16_t& x, const uint16_t& y, uint16_t& z)
   {
      z = CppCore::or16(x, y);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE void or_<uint32_t>(const uint32_t& x, const uint32_t& y, uint32_t& z)
   {
      z = CppCore::or32(x, y);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE void or_<uint64_t>(const uint64_t& x, const uint64_t& y, uint64_t& z)
   {
      z = CppCore::or64(x, y);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // XOR: x ^ y
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns x ^ y for 8-bit integer.
   /// </summary>
   static INLINE uint8_t xor8(uint8_t x, uint8_t y)
   {
      return x ^ y;
   }

   /// <summary>
   /// Returns x ^ y for 16-bit integer.
   /// </summary>
   static INLINE uint16_t xor16(uint16_t x, uint16_t y)
   {
      return x ^ y;
   }

   /// <summary>
   /// Returns x ^ y for 32-bit integer.
   /// </summary>
   static INLINE uint32_t xor32(uint32_t x, uint32_t y)
   {
      return x ^ y;
   }

   /// <summary>
   /// Returns x ^ y for 64-bit integer.
   /// </summary>
   static INLINE uint64_t xor64(uint64_t x, uint64_t y)
   {
      return x ^ y;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns x ^ y for 128-bit sse2 integer.
   /// </summary>
   static INLINE __m128i xor128(const __m128i& x, const __m128i& y)
   {
      return _mm_xor_si128(x, y);
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Returns x ^ y for 256-bit avx2 integer.
   /// </summary>
   static INLINE __m256i xor256(const __m256i& x, const __m256i& y)
   {
      return _mm256_xor_si256(x, y);
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
   /// <summary>
   /// Returns x ^ y for 512-bit avx512 integer.
   /// </summary>
   static INLINE __m512i xor512(const __m512i& x, const __m512i& y)
   {
      return _mm512_xor_si512(x, y);
   }
#endif

   /// <summary>
   /// Returns x ^ y for any sized integer.
   /// </summary>
   template<typename UINT>
   static INLINE void xor_(const UINT& x, const UINT& y, UINT& z)
   {
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      CPPCORE_CHUNK_PROCESS512_XYZ(x, y, z, UINT, true,
         CPPCORE_CHUNK_STORE512(UINT, pz512, CppCore::xor512(CPPCORE_CHUNK_LOAD512(UINT, px512), CPPCORE_CHUNK_LOAD512(UINT, py512)));,
         CPPCORE_CHUNK_STORE256(UINT, pz256, CppCore::xor256(CPPCORE_CHUNK_LOAD256(UINT, px256), CPPCORE_CHUNK_LOAD256(UINT, py256)));,
         CPPCORE_CHUNK_STORE128(UINT, pz128, CppCore::xor128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128)));,
         *pz64  = CppCore::xor64 (*px64,  *py64); ,
         *pz32  = CppCore::xor32 (*px32,  *py32); ,
         *pz16  = CppCore::xor16 (*px16,  *py16); ,
         *pz8   = CppCore::xor8  (*px8,   *py8);)
   #elif defined(CPPCORE_CPUFEAT_AVX2)
      CPPCORE_CHUNK_PROCESS256_XYZ(x, y, z, UINT, true,
         CPPCORE_CHUNK_STORE256(UINT, pz256, CppCore::xor256(CPPCORE_CHUNK_LOAD256(UINT, px256), CPPCORE_CHUNK_LOAD256(UINT, py256)));,
         CPPCORE_CHUNK_STORE128(UINT, pz128, CppCore::xor128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128)));,
         *pz64  = CppCore::xor64 (*px64,  *py64); ,
         *pz32  = CppCore::xor32 (*px32,  *py32); ,
         *pz16  = CppCore::xor16 (*px16,  *py16); ,
         *pz8   = CppCore::xor8  (*px8,   *py8);)
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      CPPCORE_CHUNK_PROCESS128_XYZ(x, y, z, UINT, true,
         CPPCORE_CHUNK_STORE128(UINT, pz128, CppCore::xor128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128)));,
         *pz64  = CppCore::xor64 (*px64,  *py64); ,
         *pz32  = CppCore::xor32 (*px32,  *py32); ,
         *pz16  = CppCore::xor16 (*px16,  *py16); ,
         *pz8   = CppCore::xor8  (*px8,   *py8);)
   #else
      CPPCORE_CHUNK_PROCESS_XYZ(x, y, z, UINT, true,
         *pz64  = CppCore::xor64 (*px64, *py64); ,
         *pz32  = CppCore::xor32 (*px32, *py32); ,
         *pz16  = CppCore::xor16 (*px16, *py16); ,
         *pz8   = CppCore::xor8  (*px8,  *py8);)
   #endif
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE void xor_<uint8_t>(const uint8_t& x, const uint8_t& y, uint8_t& z)
   {
      z = CppCore::xor8(x, y);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE void xor_<uint16_t>(const uint16_t& x, const uint16_t& y, uint16_t& z)
   {
      z = CppCore::xor16(x, y);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE void xor_<uint32_t>(const uint32_t& x, const uint32_t& y, uint32_t& z)
   {
      z = CppCore::xor32(x, y);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE void xor_<uint64_t>(const uint64_t& x, const uint64_t& y, uint64_t& z)
   {
      z = CppCore::xor64(x, y);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // AND: x & y
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns x & y for 8-bit integer.
   /// </summary>
   static INLINE uint8_t and8(uint8_t x, uint8_t y)
   {
      return x & y;
   }

   /// <summary>
   /// Returns x & y for 16-bit integer.
   /// </summary>
   static INLINE uint16_t and16(uint16_t x, uint16_t y)
   {
      return x & y;
   }

   /// <summary>
   /// Returns x & y for 32-bit integer.
   /// </summary>
   static INLINE uint32_t and32(uint32_t x, uint32_t y)
   {
      return x & y;
   }

   /// <summary>
   /// Returns x & y for 64-bit integer.
   /// </summary>
   static INLINE uint64_t and64(uint64_t x, uint64_t y)
   {
      return x & y;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns x & y for 128-bit sse2 integer.
   /// </summary>
   static INLINE __m128i and128(const __m128i& x, const __m128i& y)
   {
      return _mm_and_si128(x, y);
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Returns x & y for 256-bit avx2 integer.
   /// </summary>
   static INLINE __m256i and256(const __m256i& x, const __m256i& y)
   {
      return _mm256_and_si256(x, y);
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
   /// <summary>
   /// Returns x & y for 512-bit avx512 integer.
   /// </summary>
   static INLINE __m512i and512(const __m512i& x, const __m512i& y)
   {
      return _mm512_and_si512(x, y);
   }
#endif

   /// <summary>
   /// Returns x & y for any sized integer.
   /// </summary>
   template<typename UINT>
   static INLINE void and_(const UINT& x, const UINT& y, UINT& z)
   {
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      CPPCORE_CHUNK_PROCESS512_XYZ(x, y, z, UINT, true,
         CPPCORE_CHUNK_STORE512(UINT, pz512, CppCore::and512(CPPCORE_CHUNK_LOAD512(UINT, px512), CPPCORE_CHUNK_LOAD512(UINT, py512)));,
         CPPCORE_CHUNK_STORE256(UINT, pz256, CppCore::and256(CPPCORE_CHUNK_LOAD256(UINT, px256), CPPCORE_CHUNK_LOAD256(UINT, py256)));,
         CPPCORE_CHUNK_STORE128(UINT, pz128, CppCore::and128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128)));,
         *pz64  = CppCore::and64 (*px64,  *py64); ,
         *pz32  = CppCore::and32 (*px32,  *py32); ,
         *pz16  = CppCore::and16 (*px16,  *py16); ,
         *pz8   = CppCore::and8  (*px8,   *py8);)
   #elif defined(CPPCORE_CPUFEAT_AVX2)
      CPPCORE_CHUNK_PROCESS256_XYZ(x, y, z, UINT, true,
         CPPCORE_CHUNK_STORE256(UINT, pz256, CppCore::and256(CPPCORE_CHUNK_LOAD256(UINT, px256), CPPCORE_CHUNK_LOAD256(UINT, py256)));,
         CPPCORE_CHUNK_STORE128(UINT, pz128, CppCore::and128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128)));,
         *pz64  = CppCore::and64 (*px64,  *py64); ,
         *pz32  = CppCore::and32 (*px32,  *py32); ,
         *pz16  = CppCore::and16 (*px16,  *py16); ,
         *pz8   = CppCore::and8  (*px8,   *py8);)
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      CPPCORE_CHUNK_PROCESS128_XYZ(x, y, z, UINT, true,
         CPPCORE_CHUNK_STORE128(UINT, pz128, CppCore::and128(CPPCORE_CHUNK_LOAD128(UINT, px128), CPPCORE_CHUNK_LOAD128(UINT, py128)));,
         *pz64  = CppCore::and64 (*px64,  *py64); ,
         *pz32  = CppCore::and32 (*px32,  *py32); ,
         *pz16  = CppCore::and16 (*px16,  *py16); ,
         *pz8   = CppCore::and8  (*px8,   *py8);)
   #else
      CPPCORE_CHUNK_PROCESS_XYZ(x, y, z, UINT, true,
         *pz64  = CppCore::and64(*px64, *py64); ,
         *pz32  = CppCore::and32(*px32, *py32); ,
         *pz16  = CppCore::and16(*px16, *py16); ,
         *pz8   = CppCore::and8 (*px8,  *py8);)
   #endif
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE void and_<uint8_t>(const uint8_t& x, const uint8_t& y, uint8_t& z)
   {
      z = CppCore::and8(x, y);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE void and_<uint16_t>(const uint16_t& x, const uint16_t& y, uint16_t& z)
   {
      z = CppCore::and16(x, y);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE void and_<uint32_t>(const uint32_t& x, const uint32_t& y, uint32_t& z)
   {
      z = CppCore::and32(x, y);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE void and_<uint64_t>(const uint64_t& x, const uint64_t& y, uint64_t& z)
   {
      z = CppCore::and64(x, y);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // NOT: ~x
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns ~x for 8-bit integer.
   /// </summary>
   static INLINE uint8_t not8(uint8_t x)
   {
      return ~x;
   }

   /// <summary>
   /// Returns ~x for 16-bit integer.
   /// </summary>
   static INLINE uint16_t not16(uint16_t x)
   {
      return ~x;
   }

   /// <summary>
   /// Returns ~x for 32-bit integer.
   /// </summary>
   static INLINE uint32_t not32(uint32_t x)
   {
      return ~x;
   }

   /// <summary>
   /// Returns ~x for 64-bit integer.
   /// </summary>
   static INLINE uint64_t not64(uint64_t x)
   {
      return ~x;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns ~x for 128-bit sse2 integer.
   /// </summary>
   static INLINE __m128i not128(const __m128i& x)
   {
      return _mm_xor_si128(x, _mm_set1_epi64x(-1LL));
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Returns ~x for 256-bit avx2 integer.
   /// </summary>
   static INLINE __m256i not256(const __m256i& x)
   {
      return _mm256_xor_si256(x, _mm256_set1_epi64x(-1LL));
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
   /// <summary>
   /// Returns ~x for 512-bit avx512 integer.
   /// </summary>
   static INLINE __m512i not512(const __m512i& x)
   {
      return _mm512_xor_si512(x, _mm512_set1_epi64(-1LL));
   }
#endif

   /// <summary>
   /// Returns ~x for any sized integer.
   /// </summary>
   template<typename UINT>
   static INLINE void not_(const UINT& x, UINT& y)
   {
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      CPPCORE_CHUNK_PROCESS512_XY(x, y, UINT, true,
         CPPCORE_CHUNK_STORE512(UINT, py512, CppCore::not512(CPPCORE_CHUNK_LOAD512(UINT, px512))); ,
         CPPCORE_CHUNK_STORE256(UINT, py256, CppCore::not256(CPPCORE_CHUNK_LOAD256(UINT, px256)));,
         CPPCORE_CHUNK_STORE128(UINT, py128, CppCore::not128(CPPCORE_CHUNK_LOAD128(UINT, px128)));,
         *py64  = CppCore::not64 (*px64); ,
         *py32  = CppCore::not32 (*px32); ,
         *py16  = CppCore::not16 (*px16); ,
         *py8   = CppCore::not8  (*px8);)
   #elif defined(CPPCORE_CPUFEAT_AVX2)
      CPPCORE_CHUNK_PROCESS256_XY(x, y, UINT, true,
         CPPCORE_CHUNK_STORE256(UINT, py256, CppCore::not256(CPPCORE_CHUNK_LOAD256(UINT, px256)));,
         CPPCORE_CHUNK_STORE128(UINT, py128, CppCore::not128(CPPCORE_CHUNK_LOAD128(UINT, px128)));,
         *py64  = CppCore::not64 (*px64); ,
         *py32  = CppCore::not32 (*px32); ,
         *py16  = CppCore::not16 (*px16); ,
         *py8   = CppCore::not8  (*px8);)
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      CPPCORE_CHUNK_PROCESS128_XY(x, y, UINT, true,
         CPPCORE_CHUNK_STORE128(UINT, py128, CppCore::not128(CPPCORE_CHUNK_LOAD128(UINT, px128)));,
         *py64  = CppCore::not64 (*px64); ,
         *py32  = CppCore::not32 (*px32); ,
         *py16  = CppCore::not16 (*px16); ,
         *py8   = CppCore::not8  (*px8);)
   #else
      CPPCORE_CHUNK_PROCESS_XY(x, y, UINT, true,
         *py64  = CppCore::not64(*px64); ,
         *py32  = CppCore::not32(*px32); ,
         *py16  = CppCore::not16(*px16); ,
         *py8   = CppCore::not8 (*px8);)
   #endif
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE void not_<uint8_t>(const uint8_t& x, uint8_t& y)
   {
      y = CppCore::not8(x);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE void not_<uint16_t>(const uint16_t& x, uint16_t& y)
   {
      y = CppCore::not16(x);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE void not_<uint32_t>(const uint32_t& x, uint32_t& y)
   {
      y = CppCore::not32(x);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE void not_<uint64_t>(const uint64_t& x, uint64_t& y)
   {
      y = CppCore::not64(x);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ANDN: ~a & b
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Computes: (NOT a) AND b for 32-Bit Integer.
   /// Uses BMI1 if enabled.
   /// </summary>
   static INLINE uint32_t andn32(const uint32_t a, const uint32_t b)
   {
   #if defined(CPPCORE_CPUFEAT_BMI1)
      return _andn_u32(a, b);
   #else
      return ~a & b;
   #endif
   }

   /// <summary>
   /// Computes: (NOT a) AND b for 64-Bit Integer.
   /// Uses BMI1 if enabled.
   /// </summary>
   static INLINE uint64_t andn64(const uint64_t a, const uint64_t b)
   {
   #if defined(CPPCORE_CPU_64BIT) && defined(CPPCORE_CPUFEAT_BMI1)
      return _andn_u64(a, b);
   #else
      return ~a & b;
   #endif
   }

   /// <summary>
   /// Computes: (NOT a) AND b for 16-Bit Integer.
   /// </summary>
   static INLINE uint16_t andn16(const uint16_t a, const uint16_t b)
   {
      return (uint16_t)CppCore::andn32(a, b);
   }

   /// <summary>
   /// Computes: (NOT a) AND b for 8-Bit Integer.
   /// </summary>
   static INLINE uint8_t andn8(const uint8_t a, const uint8_t b)
   {
      return (uint8_t)CppCore::andn32(a, b);
   }

   /// <summary>
   /// Computes: (NOT a) AND b for any sized Integer.
   /// </summary>
   template<typename UINT>
   static INLINE void andn(const UINT& x, const UINT& y, UINT& z)
   {
      CPPCORE_CHUNK_PROCESS_XYZ(x, y, z, UINT, true,
         *pz64 = CppCore::andn64(*px64, *py64); ,
         *pz32 = CppCore::andn32(*px32, *py32); ,
         *pz16 = CppCore::andn16(*px16, *py16); ,
         *pz8  = CppCore::andn8 (*px8,  *py8);)
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE void andn<uint8_t>(const uint8_t& x, const uint8_t& y, uint8_t& z)
   {
      z = CppCore::andn8(x, y);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE void andn<uint16_t>(const uint16_t& x, const uint16_t& y, uint16_t& z)
   {
      z = CppCore::andn16(x, y);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE void andn<uint32_t>(const uint32_t& x, const uint32_t& y, uint32_t& z)
   {
      z = CppCore::andn32(x, y);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE void andn<uint64_t>(const uint64_t& x, const uint64_t& y, uint64_t& z)
   {
      z = CppCore::andn64(x, y);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SHLD32/SHLD64: Shift Left And Fill From Other
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Left shifts 32-bit integer a by n and fills right zeros by high bits of b.
   /// Undefined return for n = 0 or n >= 32.
   /// </summary>
   static INLINE uint32_t shld32(uint32_t a, const uint32_t b, const uint8_t n)
   {
   #if defined(CPPCORE_CPU_X86ORX64) && defined(CPPCORE_COMPILER_CLANG)
      __asm("SHLDL %[n], %[b], %[a]" : "=Rm"(a) : [n]"Ic"(n), [b]"r"(b), [a]"0"(a));
      return a;
   #else
      return (a << n) | (b >> (uint8_t)(32U-n));
   #endif
   }

   /// <summary>
   /// Left shifts 64-bit integer a by n and fills right zeros by high bits of b.
   /// Undefined return for n = 0 or n >= 64.
   /// </summary>
   static INLINE uint64_t shld64(uint64_t a, const uint64_t b, const uint8_t n)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_CLANG)
      __asm("SHLDQ %[n], %[b], %[a]" : "=Rm"(a) : [n]"Ic"(n), [b]"r"(b), [a]"0"(a));
      return a;
   #elif defined(CPPCORE_CPU_64BIT) && defined(CPPCORE_COMPILER_MSVC)
      return __shiftleft128(b, a, n);
   #else
      return (a << n) | (b >> (uint8_t)(64U-n));
   #endif
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Left shifts 64x2=128-bit integer a by n and fills right zeros by high bits of b.
   /// Undefined return for n = 0 or n >= 64. Requires SSE2.
   /// </summary>
   /*static INLINE __m128i shld64x2(const __m128i& a, const __m128i& b, const uint8_t n)
   {
      assert(n > 0 && n < 64);
      __m128i al = _mm_slli_epi64(a, n);
      __m128i ah = _mm_srli_epi64(_mm_slli_si128(a, 8), 64U-n);
      __m128i cc = _mm_srli_epi64(_mm_srli_si128(b, 8), 64U-n);
      return _mm_or_si128(_mm_or_si128(al, ah), cc);
   }*/
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Left shifts 64x4=256-bit integer a by n and fills right zeros by high bits of b.
   /// Undefined return for n = 0 or n >= 64. Requires AVX2.
   /// </summary>
   /*static INLINE __m256i shld64x4(const __m256i& a, const __m256i& b, const uint8_t n)
   {
      assert(n > 0 && n < 64);
      __m256i al = _mm256_slli_epi64(a, n);
      __m256i ah = _mm256_srli_epi64(_mm256_slli_si256(a, 8), 64U-n);
      __m256i cc = _mm256_srli_epi64(_mm256_srli_si256(b, 8), 64U-n);
      return _mm256_or_si256(_mm256_or_si256(al, ah), cc);
   }*/
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SHRD32/SHRD64: Shift Right And Fill From Other
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Right shifts 32-bit integer a by n and fills left zeros by low bits b.
   /// Undefined return for n = 0 or n >= 32.
   /// </summary>
   static INLINE uint32_t shrd32(uint32_t a, const uint32_t b, const uint8_t n)
   {
   #if defined(CPPCORE_CPU_X86ORX64) && defined(CPPCORE_COMPILER_CLANG)
      __asm("SHRDL %[n], %[b], %[a]" : "=Rm"(a) : [n]"Ic"(n), [b]"r"(b), [a]"0"(a));
      return a;
   #else
      return (a >> n) | (b << (uint8_t)(32U-n));
   #endif
   }

   /// <summary>
   /// Right shifts 64-bit integer a by n and fills left zeros by low bits of b.
   /// Undefined return for n = 0 or n >= 64.
   /// </summary>
   static INLINE uint64_t shrd64(uint64_t a, const uint64_t b, const uint8_t n)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_CLANG)
      __asm("SHRDQ %[n], %[b], %[a]" : "=Rm"(a) : [n]"Ic"(n), [b]"r"(b), [a]"0"(a));
      return a;
   #elif defined(CPPCORE_CPU_64BIT) && defined(CPPCORE_COMPILER_MSVC)
      return __shiftright128(a, b, n);
   #else
      return (a >> n) | (b << (uint8_t)(64U-n));
   #endif
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Right shifts 64x2=128-bit integer a by n and fills left zeros by high bits of b.
   /// Undefined return for n = 0 or n >= 64. Requires SSE2.
   /// </summary>
   /*static INLINE __m128i shrd64x2(const __m128i& a, const __m128i& b, const uint8_t n)
   {
      assert(n > 0 && n < 64);
      __m128i al = _mm_srli_epi64(a, n);
      __m128i ah = _mm_slli_epi64(_mm_srli_si128(a, 8), 64U-n);
      __m128i cc = _mm_slli_epi64(_mm_slli_si128(b, 8), 64U-n);
      return _mm_or_si128(_mm_or_si128(al, ah), cc);
   }*/
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Right shifts 64x4=256-bit integer a by n and fills left zeros by high bits of b.
   /// Undefined return for n = 0 or n >= 64. Requires AVX2.
   /// </summary>
   /*static INLINE __m256i shrd64x4(const __m256i& a, const __m256i& b, const uint8_t n)
   {
      assert(n > 0 && n < 64);
      __m256i al = _mm256_srli_epi64(a, n);
      __m256i ah = _mm256_slli_epi64(_mm256_srli_si256(a, 8), 64U-n);
      __m256i cc = _mm256_slli_epi64(_mm256_slli_si256(b, 8), 64U-n);
      return _mm256_or_si256(_mm256_or_si256(al, ah), cc);
   }*/
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SHL: LEFT SHIFT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Left shifts 64x2=128-bit integer a by n bits. Requires SSE2.
   /// Undefined return for n = 0 or n >= 64.
   /// </summary>
   /*static INLINE __m128i shl64x2(const __m128i& a, const uint8_t n)
   {
      assert(n > 0 && n < 64U);
      __m128i al = _mm_slli_epi64(a, n);
      __m128i ah = _mm_srli_epi64(_mm_slli_si128(a, 8), 64U - n);
      return _mm_or_si128(al, ah);
   }*/
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Left shifts 64x4=256-bit integer a by n bits. Requires AVX2.
   /// Undefined return for n = 0 or n >= 64.
   /// </summary>
   /*static INLINE __m256i shl64x4(const __m256i& a, const uint8_t n)
   {
      assert(n > 0 && n < 64U);
      __m256i al = _mm256_slli_epi64(a, n);
      __m256i ah = _mm256_srli_epi64(_mm256_slli_si256(a, 8), 64U-n);
      return _mm256_or_si256(al, ah);
   }*/
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SHL32X/SHL64X: SHIFT LEFT MULTIPLE OF 32/64 BIT MEMORY BY UP TO 32/64 BIT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Left shifts a into r (both n32 * 32 bit chunks) by s bits.
   /// Uses shld32 and s must be larger 0 and less than 32.
   /// </summary>
   static INLINE void shl32x(const uint32_t* a, uint32_t* r, const uint32_t n32, const uint8_t s)
   {
      assert(a && r && n32 && s > 0 && s < 32);
      for (uint32_t i = n32-1U; i != 0U; i--)
         r[i] = CppCore::shld32(a[i], a[i-1], s);
      r[0] = a[0] << s;
   }

   /// <summary>
   /// Left shifts a into r (both n64 * 64 bit chunks) by s bits.
   /// Uses shld64 and s must be larger 0 and less than 64.
   /// </summary>
   static INLINE void shl64x(const uint64_t* a, uint64_t* r, const uint32_t n64, const uint8_t s)
   {
      assert(a && r && n64 && s > 0 && s < 64);
      for (uint32_t i = n64-1U; i != 0U; i--)
         r[i] = CppCore::shld64(a[i], a[i-1], s);
      r[0] = a[0] << s;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Left shifts a into r (both n 64x2=128 bit chunks) by s bits.
   /// Uses shld64x2 and s must be larger 0 and less than 64. Requires SSE2.
   /// </summary>
   /*template<bool ALIGNED = false>
   static INLINE void shl64x(const __m128i* a, __m128i* r, const uint32_t n, const uint8_t s)
   {
      if (ALIGNED)
      {
         for (uint32_t i = n-1U; i != 0U; i--)
            r[i] = CppCore::shld64x2(a[i], a[i-1], s);
         r[0] = CppCore::shl64x2(a[0], s);
      }
      else
      {
         for (uint32_t i = n-1U; i != 0U; i--)
            _mm_storeu_si128(&r[i], CppCore::shld64x2(_mm_loadu_si128(&a[i]),_mm_loadu_si128(&a[i-1]), s));
         _mm_storeu_si128(&r[0], CppCore::shl64x2(_mm_loadu_si128(&a[0]), s));
      }
   }*/
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Left shifts a into r (both n 64x4=256 bit chunks) by s bits.
   /// Uses shld64x4 and s must be larger 0 and less than 64. Requires AVX2.
   /// </summary>
   /*template<bool ALIGNED = false>
   static INLINE void shl64x(const __m256i* a, __m256i* r, const uint32_t n, const uint8_t s)
   {
      if (ALIGNED)
      {
         for (uint32_t i = n-1U; i != 0U; i--)
            r[i] = CppCore::shld64x4(a[i], a[i-1], s);
         r[0] = CppCore::shl64x4(a[0], s);
      }
      else
      {
         for (uint32_t i = n-1U; i != 0U; i--)
            _mm256_storeu_si256(&r[i], CppCore::shld64x4(_mm256_loadu_si256(&a[i]),_mm256_loadu_si256(&a[i-1]), s));
         _mm256_storeu_si256(&r[0], CppCore::shl64x4(_mm256_loadu_si256(&a[0]), s));
      }
   }*/
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SHR
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Right shifts 64x2=128-bit integer a by n bits. Requires SSE2.
   /// Undefined return for n = 0 or n >= 64.
   /// </summary>
   /*static INLINE __m128i shr64x2(const __m128i& a, const uint8_t n)
   {
      assert(n > 0 && n < 64U);
      __m128i al = _mm_srli_epi64(a, n);
      __m128i ah = _mm_slli_epi64(_mm_srli_si128(a, 8), 64U-n);
      return _mm_or_si128(al, ah);
   }*/
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Right shifts 64x4=256-bit integer a by n bits. Requires AVX2.
   /// Undefined return for n = 0 or n >= 64.
   /// </summary>
   /*static INLINE __m256i shr64x4(const __m256i& a, const uint8_t n)
   {
      assert(n > 0 && n < 64U);
      __m256i al = _mm256_srli_epi64(a, n);
      __m256i ah = _mm256_slli_epi64(_mm256_srli_si256(a, 8), 64U-n);
      return _mm256_or_si256(al, ah);
   }*/
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SHR32X/SHR64X: SHIFT RIGHT MULTIPLE OF 32/64 BIT MEMORY BY UP TO 32/64 BIT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Right shifts a into r (both n 32 bit chunks) by s bits.
   /// Uses shrd32 and s must be larger 0 and less than 32.
   /// </summary>
   static INLINE void shr32x(const uint32_t* a, uint32_t* r, const uint32_t n32, const uint8_t s)
   {
      assert(a && r && n32 && s > 0 && s < 32);
      for (uint32_t i = 0; i < n32-1U; i++)
         r[i] = CppCore::shrd32(a[i], a[i+1], s);
      r[n32-1] = a[n32-1] >> s;
   }

   /// <summary>
   /// Right shifts a into r (both n 64 bit chunks) by s bits.
   /// Uses shrd64 and s must be larger 0 and less than 64.
   /// </summary>
   static INLINE void shr64x(const uint64_t* a, uint64_t* r, const uint32_t n64, const uint8_t s)
   {
      assert(a && r && n64 && s > 0 && s < 64);
      for (uint32_t i = 0; i < n64-1U; i++)
         r[i] = CppCore::shrd64(a[i], a[i+1], s);
      r[n64-1] = a[n64-1] >> s;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Right shifts a into r (both n 64x2=128 bit chunks) by s bits.
   /// Uses shrd128x2 and s must be larger 0 and less than 64. Requires SSE2.
   /// </summary>
   /*template<bool ALIGNED = false>
   static INLINE void shr64x(const __m128i* a, __m128i* r, const uint32_t n, const uint8_t s)
   {
      if (ALIGNED)
      {
         for (uint32_t i = 0; i < n-1U; i++)
            r[i] = CppCore::shrd64x2(a[i], a[i+1], s);
         r[n-1] = CppCore::shr64x2(a[n-1], s);
      }
      else
      {
         for (uint32_t i = 0; i < n-1U; i++)
            _mm_storeu_si128(&r[i], CppCore::shrd64x2(_mm_loadu_si128(&a[i]), _mm_loadu_si128(&a[i+1]), s));
         _mm_storeu_si128(&r[n-1], CppCore::shr64x2(_mm_loadu_si128(&a[n-1]), s));
      }
   }*/
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Right shifts a into r (both n 64x4=256 bit chunks) by s bits.
   /// Uses shrd64x4 and s must be larger 0 and less than 64. Requires AVX2.
   /// </summary>
   /*template<bool ALIGNED = false>
   static INLINE void shr64x(const __m256i* a, __m256i* r, const uint32_t n, const uint8_t s)
   {
      if (ALIGNED)
      {
         for (uint32_t i = 0; i < n-1U; i++)
            r[i] = CppCore::shrd64x4(a[i], a[i+1], s);
         r[n-1] = CppCore::shr64x4(a[n-1], s);
      }
      else
      {
         for (uint32_t i = 0; i < n-1U; i++)
            _mm256_storeu_si256(&r[i], CppCore::shrd64x4(_mm256_loadu_si256(&a[i]), _mm256_loadu_si256(&a[i+1]), s));
         _mm256_storeu_si256(&r[n-1], CppCore::shr64x4(_mm256_loadu_si256(&a[n-1]), s));
      }
   }*/
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SHL
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Binary Left Shift (r = a << b)
   /// </summary>
   template<typename UINT>
   static INLINE void shl(UINT& r, const UINT& a,const size_t b)
   {
      static_assert(sizeof(UINT) % 4 == 0);
      if (b >= (sizeof(UINT) << 3)) {
         CppCore::clear(r);
         return;
      }
   #if defined(CPPCORE_CPU_64BIT)
      if constexpr (sizeof(UINT) % 8 == 0)
      {
         constexpr size_t N64 = sizeof(UINT) / 8;
         uint64_t* ap = (uint64_t*)&a;
         uint64_t* rp = (uint64_t*)&r;
         if (const size_t t = b >> 6)
         {
            for (size_t i = N64-1; i >= t; i--)
               rp[i] = ap[i-t];
            for (size_t i = 0; i < t; i++)
               rp[i] = 0ULL;
         }
         if (const uint8_t t = b & 0x3F)
            CppCore::shl64x(ap, rp, N64, t);
      }
      else
   #endif
      {
         constexpr size_t N32 = sizeof(UINT) / 4;
         uint32_t* ap = (uint32_t*)&a;
         uint32_t* rp = (uint32_t*)&r;
         if (const size_t t = b >> 5)
         {
            for (size_t i = N32-1; i >= t; i--)
               rp[i] = ap[i-t];
            for (size_t i = 0; i < t; i++)
               rp[i] = 0U;
         }
         if (const uint8_t t = b & 0x1F)
            CppCore::shl32x(ap, rp, N32, t);
      }
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SHR
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Binary Right Shift (r = a >> b)
   /// </summary>
   template<typename UINT>
   static INLINE void shr(UINT& r, const UINT& a,const size_t b)
   {
      static_assert(sizeof(UINT) % 4 == 0);
      if (b >= (sizeof(UINT) << 3)) {
         CppCore::clear(r);
         return;
      }
   #if defined(CPPCORE_CPU_64BIT)
      if constexpr (sizeof(UINT) % 8 == 0)
      {
         constexpr size_t N64 = sizeof(UINT) / 8;
         uint64_t* ap = (uint64_t*)&a;
         uint64_t* rp = (uint64_t*)&r;
         if (const size_t t = b >> 6)
         {
            for (size_t i = 0; i < N64-t; i++)
               rp[i] = ap[i+t];
            for (size_t i = 0; i < t; i++)
               rp[N64-1-i] = 0ULL;
         }
         if (const uint8_t t = b & 0x3F)
            CppCore::shr64x(ap, rp, N64, t);
      }
      else
   #endif
      {
         constexpr size_t N32 = sizeof(UINT) / 4;
         uint32_t* ap = (uint32_t*)&a;
         uint32_t* rp = (uint32_t*)&r;
         if (const size_t t = b >> 5)
         {
            for (size_t i = 0; i < N32-t; i++)
               rp[i] = ap[i+t];
            for (size_t i = 0; i < t; i++)
               rp[N32-1-i] = 0U;
         }
         if (const uint8_t t = b & 0x1F)
            CppCore::shr32x(ap, rp, N32, t);
      }
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ROTL32/ROTL64: Rotate bits left
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Rotates bits of v left by n in 32-bit integer.
   /// Undefined return for n = 0 or n >= 32.
   /// </summary>
   static INLINE uint32_t rotl32(uint32_t v, uint32_t n)
   {
   #if defined(CPPCORE_COMPILER_MSVC)
      return _rotl(v, (int32_t)n);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_rotateleft32)
      return __builtin_rotateleft32(v, n);
   #else
      return CppCore::shld32(v, v, n);
   #endif
   }

   /// <summary>
   /// Rotates bits of v left by n in 64-bit integer.
   /// Undefined return for n = 0 or n >= 64.
   /// </summary>
   static INLINE uint64_t rotl64(uint64_t v, uint32_t n)
   {
   #if defined(CPPCORE_COMPILER_MSVC)
      return _rotl64(v, (int32_t)n);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_rotateleft64)
      return __builtin_rotateleft64(v, n);
   #else
      return CppCore::shld64(v, v, n);
   #endif
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ROTR32/ROTR64: Rotate bits right
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Rotates bits of v right by n in 32-bit integer.
   /// Undefined return for n = 0 or n >= 32.
   /// </summary>
   static INLINE uint32_t rotr32(uint32_t v, uint32_t n)
   {
   #if defined(CPPCORE_COMPILER_MSVC)
      return _rotr(v, (int32_t)n);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_rotateright32)
      return __builtin_rotateright32(v, n);
   #else
      return CppCore::shrd32(v, v, n);
   #endif
   }

   /// <summary>
   /// Rotates bits of v right by n in 64-bit integer.
   /// Undefined return for n = 0 or n >= 64.
   /// </summary>
   static INLINE uint64_t rotr64(uint64_t v, uint32_t n)
   {
   #if defined(CPPCORE_COMPILER_MSVC)
      return _rotr64(v, (int32_t)n);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_rotateright64)
      return __builtin_rotateright64(v, n);
   #else
      return CppCore::shrd64(v, v, n);
   #endif
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // RORX32/RORX64: Rotate bits right
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Uses RORX if available from BMI2, else falls back to rortr32
   /// </summary>
   template<uint32_t n>
   static INLINE uint32_t rorx32(uint32_t v)
   {
   #if defined(CPPCORE_CPUFEAT_BMI2) && defined(CPPCORE_COMPILER_MSVC)
      return _rorx_u32(v, n);
   #else
      return CppCore::rotr32(v, n);
   #endif
   }

   /// <summary>
   /// Uses RORX if available from BMI2, else falls back to rortr64
   /// </summary>
   template<uint32_t n>
   static INLINE uint64_t rorx64(uint64_t v)
   {
   #if defined(CPPCORE_CPUFEAT_BMI2) && defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_MSVC)
      return _rorx_u64(v, n);
   #else
      return CppCore::rotr64(v, n);
   #endif
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // POPCNT: Count One Bits
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Counts the number of bits set to 1 in 32-bit integer.
   /// Slow version with native uint32_t operations only, but constexpr.
   /// </summary>
   constexpr static INLINE uint32_t popcnt32_generic(uint32_t v)
   {
      v -= ((v >> 1) & 0x55555555U);
      v  = (v & 0x33333333U) + ((v >> 2) & 0x33333333U);
      return ((v + (v >> 4) & 0xF0F0F0FU) * 0x1010101U) >> 24;
   }

   /// <summary>
   /// Counts the number of bits set to 1 in 64-bit integer.
   /// Slow version with native uint64_t operations only, but constexpr.
   /// </summary>
   constexpr static INLINE uint32_t popcnt64_generic(uint64_t v)
   {
      v -= ((v >> 1) & 0x5555555555555555ULL);
      v  = (v & 0x3333333333333333ULL) + ((v >> 2) & 0x3333333333333333ULL);
      return ((v + (v >> 4) & 0xF0F0F0F0F0F0F0FULL) * 0x101010101010101ULL) >> 56;
   }

   /// <summary>
   /// Counts the number of bits set to 1 in 32-bit integer.
   /// Uses POPCNT instruction if available.
   /// </summary>
   static INLINE uint32_t popcnt32(uint32_t v)
   {
   #if defined(CPPCORE_CPUFEAT_POPCNT)
      return _mm_popcnt_u32(v);
   #elif defined(CPPCORE_COMPILER_MSVC) && defined(CPPCORE_CPU_X86ORX64)
      return __popcnt(v);
   #elif defined(CPPCORE_COMPILER_MSVC) && defined(CPPCORE_CPU_ARMORARM64)
      return _CountOneBits(v);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_popcountl)
      return __builtin_popcountl(v);
   #else
      return popcnt32_generic(v);
   #endif
   }

   /// <summary>
   /// Counts the number of bits set to 1 in 64-bit integer.
   /// Uses POPCNT instruction if available.
   /// </summary>
   static INLINE uint32_t popcnt64(uint64_t v)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_POPCNT)
      return (uint32_t)_mm_popcnt_u64(v);
   #elif defined(CPPCORE_COMPILER_MSVC) && defined(CPPCORE_CPU_X64)
      return (uint32_t)__popcnt64(v);
   #elif defined(CPPCORE_COMPILER_MSVC) && defined(CPPCORE_CPU_ARM64)
      return _CountOneBits64(v);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_popcountll)
      return (uint32_t)__builtin_popcountll(v);
   #else
      return popcnt64_generic(v);
   #endif
   }

   /// <summary>
   /// Counts the number of bits set to 1 in 16-bit integer.
   /// </summary>
   static INLINE uint32_t popcnt16(uint16_t v)
   {
      return CppCore::popcnt32(v);
   }

   /// <summary>
   /// Counts the number of bits set to 1 in 8-bit integer.
   /// </summary>
   static INLINE uint32_t popcnt8(uint8_t v)
   {
      return CppCore::popcnt32(v);
   }

   /// <summary>
   /// Counts the number of trailing zeros in any sized integer.
   /// </summary>
   template<typename UINT>
   static INLINE uint32_t popcnt(const UINT& x)
   {
      uint32_t r = 0U;
      CPPCORE_CHUNK_PROCESS_X(x, UINT, true,
         r += CppCore::popcnt64(*px64); ,
         r += CppCore::popcnt32(*px32); ,
         r += CppCore::popcnt16(*px16); ,
         r += CppCore::popcnt8 (*px8);
      )
      return r;
   }

   /// <summary>
   /// Template Specialization for 8-bit integer.
   /// </summary>
   template<> INLINE uint32_t popcnt<uint8_t>(const uint8_t& x)
   {
      return CppCore::popcnt8(x);
   }

   /// <summary>
   /// Template Specialization for 16-bit integer.
   /// </summary>
   template<> INLINE uint32_t popcnt<uint16_t>(const uint16_t& x)
   {
      return CppCore::popcnt16(x);
   }

   /// <summary>
   /// Template Specialization for 32-bit integer.
   /// </summary>
   template<> INLINE uint32_t popcnt<uint32_t>(const uint32_t& x)
   {
      return CppCore::popcnt32(x);
   }

   /// <summary>
   /// Template Specialization for 64-bit integer.
   /// </summary>
   template<> INLINE uint32_t popcnt<uint64_t>(const uint64_t& x)
   {
      return CppCore::popcnt64(x);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // LZCNT: Count Leading Zeros
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Counts the number of leading zeros in 32-bit integer.
   /// </summary>
   static INLINE uint32_t lzcnt32(uint32_t v)
   {
   #if defined(CPPCORE_CPUFEAT_LZCNT)
      return _lzcnt_u32(v);
   #elif defined(CPPCORE_COMPILER_MSVC)
      unsigned long r;
      return _BitScanReverse(&r, v) ? 31U - r : 32U;
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_clz)
      return v ? __builtin_clz(v) : 32U;
   #else
      // from: https://stackoverflow.com/questions/23856596/how-to-count-leading-zeros-in-a-32-bit-unsigned-integer
      static constexpr uint32_t table[32] = {
         0, 31, 9, 30, 3, 8, 13, 29, 2, 5, 7, 21, 12, 24, 28, 19,
         1, 10, 4, 14, 6, 22, 25, 20, 11, 15, 23, 26, 16, 27, 17, 18
      };
      if (v)
      {
         v |= v >> 1;
         v |= v >> 2;
         v |= v >> 4;
         v |= v >> 8;
         v |= v >> 16;
         v++;
         return table[(v * 0x076be629) >> 27];
      }
      else
         return 32U;
   #endif
   }

   /// <summary>
   /// Counts the number of leading zeros in 64-bit integer.
   /// </summary>
   static INLINE uint32_t lzcnt64(uint64_t v)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_LZCNT)
      return (uint32_t)_lzcnt_u64(v);
   #elif defined(CPPCORE_CPU_64BIT) && defined(CPPCORE_COMPILER_MSVC)
      unsigned long r;
      return _BitScanReverse64(&r, v) ? 63U - r : 64U;
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_clzll)
      return v ? __builtin_clzll(v) : 64U;
   #else
      const uint32_t hi = (uint32_t)(v >> 32);
      const uint32_t lo = (uint32_t)(v);
      return hi ? lzcnt32(hi) : lzcnt32(lo) + 32U;
   #endif
   }

   /// <summary>
   /// Counts the number of leading zeros in 16-bit integer.
   /// </summary>
   static INLINE uint32_t lzcnt16(uint16_t v)
   {
      return CppCore::lzcnt32((((uint32_t)v) << 16U) | 0x0000FFFFU);
   }

   /// <summary>
   /// Counts the number of leading zeros in 8-bit integer.
   /// </summary>
   static INLINE uint32_t lzcnt8(uint8_t v)
   {
      return CppCore::lzcnt32((((uint32_t)v) << 24U) | 0x00FFFFFFU);
   }

   /// <summary>
   /// Counts the number of leading zeros in any sized integer.
   /// </summary>
   template<typename UINT>
   static INLINE uint32_t lzcnt(const UINT& x)
   {
      uint32_t r = 0U;
      CPPCORE_CHUNK_PROCESS_X(x, UINT, false,
         // 64-Bit
         const auto c = CppCore::lzcnt64(*px64);
         r += c;
         if (c != 64U)
            return r;,
         // 32-Bit
         const auto c = CppCore::lzcnt32(*px32);
         r += c;
         if (c != 32U)
            return r;,
         // 16-Bit
         const auto c = CppCore::lzcnt16(*px16);
         r += c;
         if (c != 16U)
            return r;,
         // 8-Bit
         r += CppCore::lzcnt8(*px8);
      )
      return r;
   }

   /// <summary>
   /// Template Specialization for 8-bit integer.
   /// </summary>
   template<> INLINE uint32_t lzcnt<uint8_t> (const uint8_t& x)
   {
      return CppCore::lzcnt8(x);
   }

   /// <summary>
   /// Template Specialization for 16-bit integer.
   /// </summary>
   template<> INLINE uint32_t lzcnt<uint16_t>(const uint16_t& x)
   {
      return CppCore::lzcnt16(x);
   }

   /// <summary>
   /// Template Specialization for 32-bit integer.
   /// </summary>
   template<> INLINE uint32_t lzcnt<uint32_t>(const uint32_t& x)
   {
      return CppCore::lzcnt32(x);
   }

   /// <summary>
   /// Template Specialization for 64-bit integer.
   /// </summary>
   template<> INLINE uint32_t lzcnt<uint64_t>(const uint64_t& x)
   {
      return CppCore::lzcnt64(x);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // TZCNT: Count Trailing Zeros
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Counts the number of trailing zeros in 32-bit integer.
   /// Uses BMI1 if available.
   /// </summary>
   static INLINE uint32_t tzcnt32(uint32_t v)
   {
   #if defined(CPPCORE_CPUFEAT_BMI1)
      return _tzcnt_u32(v);
   #elif defined(CPPCORE_COMPILER_MSVC)
      unsigned long r;
      return _BitScanForward(&r, v) ? r : 32U;
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_ctzl)
      return v ? __builtin_ctzl(v) : 32U;
   #else
      // from: https://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup
      static constexpr uint32_t table[32] =
      {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
      };
      return v ? table[((v & -(int32_t)v) * 0x077CB531U) >> 27] : 32U;
   #endif
   }

   /// <summary>
   /// Counts the number of trailing zeros in 64-bit integer.
   /// Uses BMI1 if available.
   /// </summary>
   static INLINE uint32_t tzcnt64(uint64_t v)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_BMI1)
      return (uint32_t)_tzcnt_u64(v);
   #elif defined(CPPCORE_CPU_64BIT) && defined(CPPCORE_COMPILER_MSVC)
      unsigned long r;
      return _BitScanForward64(&r, v) ? r : 64U;
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_ctzll)
      return v ? __builtin_ctzll(v) : 64U;
   #else
      const uint32_t r = CppCore::tzcnt32((uint32_t)v);
      return (r != 32U) ? r : 32U + CppCore::tzcnt32((uint32_t)(v >> 32));
   #endif
   }

   /// <summary>
   /// Counts the number of trailing zeros in 16-bit integer.
   /// </summary>
   static INLINE uint32_t tzcnt16(uint16_t v)
   {
      return CppCore::tzcnt32(0xFFFF0000U | v);
   }

   /// <summary>
   /// Counts the number of trailing zeros in 8-bit integer.
   /// </summary>
   static INLINE uint32_t tzcnt8(uint8_t v)
   {
      return CppCore::tzcnt32(0xFFFFFF00U | v);
   }

   /// <summary>
   /// Counts the number of trailing zeros in any sized integer.
   /// </summary>
   template<typename UINT>
   static INLINE uint32_t tzcnt(const UINT& x)
   {
      uint32_t r = 0U;
      CPPCORE_CHUNK_PROCESS_X(x, UINT, true,
         // 64-Bit
         const auto c = CppCore::tzcnt64(*px64);
         r += c;
         if (c != 64U)
            return r;,
         // 32-Bit
         const auto c = CppCore::tzcnt32(*px32);
         r += c;
         if (c != 32U)
            return r;,
         // 16-Bit
         const auto c = CppCore::tzcnt16(*px16);
         r += c;
         if (c != 16U)
            return r;,
         // 8-Bit
         r += CppCore::tzcnt8(*px8);
      )
      return r;
   }

   /// <summary>
   /// Template Specialization for 8-bit integer.
   /// </summary>
   template<> INLINE uint32_t tzcnt<uint8_t>(const uint8_t& x)
   {
      return CppCore::tzcnt8(x);
   }

   /// <summary>
   /// Template Specialization for 16-bit integer.
   /// </summary>
   template<> INLINE uint32_t tzcnt<uint16_t>(const uint16_t& x)
   {
      return CppCore::tzcnt16(x);
   }

   /// <summary>
   /// Template Specialization for 32-bit integer.
   /// </summary>
   template<> INLINE uint32_t tzcnt<uint32_t>(const uint32_t& x)
   {
      return CppCore::tzcnt32(x);
   }

   /// <summary>
   /// Template Specialization for 64-bit integer.
   /// </summary>
   template<> INLINE uint32_t tzcnt<uint64_t>(const uint64_t& x) 
   {
      return CppCore::tzcnt64(x);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BITTEST: Set CF flag for jumping if bit is set
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Tests if bit at index i is set in 32-bit integer v.
   /// </summary>
   static INLINE uint8_t bittest32(const uint32_t v, const uint32_t i)
   {
      assert(i < 32);
   #if defined(CPPCORE_CPU_X86ORX64) && defined(CPPCORE_COMPILER_CLANG)
      uint8_t cf;
      __asm("BTL %[i], %[v]" : "=@ccc"(cf) : [i]"Ir"(i), [v]"r"(v) : );
      return cf;
   #elif defined(CPPCORE_OS_WINDOWS)
      return _bittest((const long*)&v, i);
   #else
      return (v & (1U << i)) != 0U;
   #endif
   }

   /// <summary>
   /// Tests if bit at index i is set in 64-bit integer v.
   /// </summary>
   static INLINE uint8_t bittest64(const uint64_t v, const uint64_t i)
   {
      assert(i < 64);
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_CLANG)
      uint8_t cf;
      __asm("BTQ %[i], %[v]" : "=@ccc"(cf) : [i]"Ir"(i), [v]"r"(v) : );
      return cf;
   #elif defined(CPPCORE_CPU_X64) && defined(CPPCORE_OS_WINDOWS)
      return _bittest64((const long long*)&v, i);
   #else
      return (v & (1ULL << i)) != 0U;
   #endif
   }

   /// <summary>
   /// Tests if bit at index i is set in 16-bit integer v.
   /// </summary>
   static INLINE uint8_t bittest16(const uint16_t v, const uint16_t i)
   {
      assert(i < 16);
      return CppCore::bittest32(v, i);
   }

   /// <summary>
   /// Tests if bit at index i is set in 8-bit integer v.
   /// </summary>
   static INLINE uint8_t bittest8(const uint8_t v, const uint8_t i)
   {
      assert(i < 8);
      return CppCore::bittest32(v, i);
   }

   /// <summary>
   /// Tests if bit at index i is set in any sized integer v.
   /// </summary>
   template<typename UINT>
   static INLINE uint8_t bittest(const UINT& v, const uint32_t i)
   {
      assert(i < sizeof(UINT) * 8);
   #if defined(CPPCORE_CPU_64BIT)
      const uint32_t i64 = i >> 6;   // div 64
      const uint32_t idx = i & 0x3F; // mod 64
      const uint64_t v64 = ((uint64_t*)&v)[i64];
      return CppCore::bittest64(v64, idx);
   #else
      const uint32_t i32 = i >> 5;   // div 32
      const uint32_t idx = i & 0x1F; // mod 32
      const uint32_t v32 = ((uint32_t*)&v)[i32];
      return CppCore::bittest32(v32, idx);
   #endif
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE uint8_t bittest<uint8_t>(const uint8_t& v, const uint32_t i)
   {
      return CppCore::bittest8(v, i);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE uint8_t bittest<uint16_t>(const uint16_t& v, const uint32_t i)
   {
      return CppCore::bittest16(v, i);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE uint8_t bittest<uint32_t>(const uint32_t& v, const uint32_t i)
   {
      return CppCore::bittest32(v, i);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE uint8_t bittest<uint64_t>(const uint64_t& v, const uint32_t i)
   {
      return CppCore::bittest64(v, i);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BITEXTRACT: RETURN ONE BIT FROM GIVEN INDEX IN LOWBIT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns bit from index i in lowbit position and all others 0.
   /// Undefined return for i >= 8.
   /// </summary>
   static INLINE uint8_t bitextract8(const uint8_t v, const uint8_t i)
   {
      assert(i < 8);
      return (v & ((uint8_t)1U << i)) >> i;
   }

   /// <summary>
   /// Returns bit from index i in lowbit position and all others 0.
   /// Undefined return for i >= 16.
   /// </summary>
   static INLINE uint16_t bitextract16(const uint16_t v, const uint16_t i)
   {
      assert(i < 16);
      return (v & ((uint16_t)1U << i)) >> i;
   }

   /// <summary>
   /// Returns bit from index i in lowbit position and all others 0.
   /// Undefined return for i >= 32.
   /// </summary>
   static INLINE uint32_t bitextract32(const uint32_t v, const uint32_t i)
   {
      assert(i < 32);
   #if defined(CPPCORE_CPUFEAT_BMI1)
      return _bextr_u32(v, i, 1);
   #else
      return (v & (1U << i)) >> i;
   #endif
   }

   /// <summary>
   /// Returns bit from index i in lowbit position and all others 0.
   /// Undefined return for i >= 64.
   /// </summary>
   static INLINE uint64_t bitextract64(const uint64_t v, const uint32_t i)
   {
      assert(i < 64);
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_BMI1)
      return _bextr_u64(v, i, 1);
   #else
      return (v & (1ULL << i)) >> i;
   #endif
   }

   /// <summary>
   /// Returns bit from index i in lowbit position and all others 0.
   /// Undefined return for i >= sizeof(UINT)*8.
   /// </summary>
   template<typename UINT>
   static INLINE size_t bitextract(const UINT& v, const uint32_t i)
   {
      assert(i < sizeof(UINT) * 8);
   #if defined(CPPCORE_CPU_64BIT)
      const uint32_t i64 = i >> 6;   // div 64
      const uint32_t idx = i & 0x3F; // mod 64
      const uint64_t v64 = ((uint64_t*)&v)[i64];
      return CppCore::bitextract64(v64, idx);
   #else
      const uint32_t i32 = i >> 5;   // div 32
      const uint32_t idx = i & 0x1F; // mod 32
      const uint32_t v32 = ((uint32_t*)&v)[i32];
      return CppCore::bitextract32(v32, idx);
   #endif
   }

   /// <summary>
   /// Template Specialization for 8-Bit Integer.
   /// </summary>
   template<> INLINE size_t bitextract<uint8_t>(const uint8_t& v, const uint32_t i)
   {
      return (size_t)CppCore::bitextract8(v, (uint8_t)i);
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE size_t bitextract<uint16_t>(const uint16_t& v, const uint32_t i)
   {
      return (size_t)CppCore::bitextract16(v, (uint16_t)i);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE size_t bitextract<uint32_t>(const uint32_t& v, const uint32_t i)
   {
      return (size_t)CppCore::bitextract32(v, (uint32_t)i);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE size_t bitextract<uint64_t>(const uint64_t& v, const uint32_t i)
   {
      return (size_t)CppCore::bitextract64(v, (uint64_t)i);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BSWAP: Reverse Byte Order
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Swaps byte order in 16-bit unsigned integer.
   /// </summary>
   static INLINE uint16_t byteswap16(uint16_t v)
   {
   #if defined(CPPCORE_COMPILER_MSVC)
      return _byteswap_ushort(v);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_bswap16)
      return __builtin_bswap16(v);
   #else
      return
         ((v & 0x00FFUi16) << 8) |
         ((v & 0xFF00Ui16) >> 8);
   #endif
   }

   /// <summary>
   /// Swaps byte order in 32-bit unsigned integer.
   /// </summary>
   static INLINE uint32_t byteswap32(uint32_t v)
   {
   #if defined(CPPCORE_COMPILER_MSVC)
      return _byteswap_ulong(v);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_bswap32)
      return __builtin_bswap32(v);
   #else
      return
         ((v & 0x000000FFU) << 24) |
         ((v & 0x0000FF00U) <<  8) |
         ((v & 0x00FF0000U) >>  8) |
         ((v & 0xFF000000U) >> 24);
   #endif
   }

   /// <summary>
   /// Swaps byte order in 64-bit unsigned integer.
   /// </summary>
   static INLINE uint64_t byteswap64(uint64_t v)
   {
   #if defined(CPPCORE_COMPILER_MSVC)
      return _byteswap_uint64(v);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_bswap64)
      return __builtin_bswap64(v);
   #else
      return
         ((v & 0x00000000000000FFULL) << 56) |
         ((v & 0x000000000000FF00ULL) << 40) |
         ((v & 0x0000000000FF0000ULL) << 24) |
         ((v & 0x00000000FF000000ULL) <<  8) |
         ((v & 0x000000FF00000000ULL) >>  8) |
         ((v & 0x0000FF0000000000ULL) >> 24) |
         ((v & 0x00FF000000000000ULL) >> 40) |
         ((v & 0xFF00000000000000ULL) >> 56);
   #endif
   }

   /// <summary>
   /// Swaps byte order in 16-bit unsigned integer.
   /// </summary>
   static INLINE uint16_t byteswap(uint16_t v)
   {
      return CppCore::byteswap16(v);
   }

   /// <summary>
   /// Swaps byte order in 32-bit unsigned integer.
   /// </summary>
   static INLINE uint32_t byteswap(uint32_t v)
   {
      return CppCore::byteswap32(v);
   }

   /// <summary>
   /// Swaps byte order in 64-bit unsigned integer.
   /// </summary>
   static INLINE uint64_t byteswap(uint64_t v)
   {
      return CppCore::byteswap64(v);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BYTEDUP: Duplicate byte
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Duplicates v into all bytes of 16-Bit Integer
   /// (e.g. 0x0F -> 0x0F0F)
   /// </summary>
   static INLINE uint16_t bytedup16(const uint8_t v)
   {
      return ((uint16_t)v) * (uint16_t)0x0101U;
   }

   /// <summary>
   /// Duplicates v into all bytes of 32-Bit Integer
   /// (e.g. 0x0F -> 0x0F0F0F0F)
   /// </summary>
   static INLINE uint32_t bytedup32(const uint8_t v)
   {
      return ((uint32_t)v) * 0x01010101U;
   }

   /// <summary>
   /// Duplicates v into all bytes of 64-Bit Integer
   /// (e.g. 0x0F -> 0x0F0F0F0F0F0F0F0F)
   /// </summary>
   static INLINE uint64_t bytedup64(const uint8_t v)
   {
      return ((uint64_t)v) * 0x0101010101010101ULL;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Duplicates v into all bytes of 128-Bit Integer
   /// (e.g. 0x0F -> 0x0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F)
   /// </summary>
   static INLINE __m128i bytedup128(const uint8_t v)
   {
      return _mm_set1_epi8(v);
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
   /// <summary>
   /// Duplicates v into all bytes of 256-Bit Integer
   /// </summary>
   static INLINE __m256i bytedup256(const uint8_t v)
   {
      return _mm256_set1_epi8(v);
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
   /// <summary>
   /// Duplicates v into all bytes of 512-Bit Integer
   /// </summary>
   static INLINE __m512i bytedup512(const uint8_t v)
   {
      return _mm512_set1_epi8(v);
   }
#endif

   /// <summary>
   /// Duplicates v into all bytes of any sized Integer
   /// (e.g. 0x0F -> 0x0F0F)
   /// </summary>
   template<typename UINT>
   static INLINE void bytedup(const uint8_t& v, UINT& x)
   {
      const uint16_t dup16 = CppCore::bytedup16(v);
      const uint32_t dup32 = CppCore::bytedup32(v);
      const uint64_t dup64 = CppCore::bytedup64(v);
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      const __m128i dup128 = CppCore::bytedup128(v);
      const __m256i dup256 = CppCore::bytedup256(v);
      const __m512i dup512 = CppCore::bytedup512(v);
      CPPCORE_CHUNK_PROCESS512_X(x, UINT, true,
         CPPCORE_CHUNK_STORE512(UINT, px512, dup512); ,
         CPPCORE_CHUNK_STORE256(UINT, px256, dup256);,
         CPPCORE_CHUNK_STORE128(UINT, px128, dup128);,
         *px64  = dup64; ,
         *px32  = dup32; ,
         *px16  = dup16; ,
         *px8   = v;)
   #elif defined(CPPCORE_CPUFEAT_AVX)
      const __m128i dup128 = CppCore::bytedup128(v);
      const __m256i dup256 = CppCore::bytedup256(v);
      CPPCORE_CHUNK_PROCESS256_X(x, UINT, true,
         CPPCORE_CHUNK_STORE256(UINT, px256, dup256); ,
         CPPCORE_CHUNK_STORE128(UINT, px128, dup128); ,
         *px64  = dup64; ,
         *px32  = dup32; ,
         *px16  = dup16; ,
         *px8   = v;)
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      const __m128i dup128 = CppCore::bytedup128(v);
      CPPCORE_CHUNK_PROCESS128_X(x, UINT, true,
         CPPCORE_CHUNK_STORE128(UINT, px128, dup128); ,
         *px64  = dup64; ,
         *px32  = dup32; ,
         *px16  = dup16; ,
         *px8   = v;)
   #else
      CPPCORE_CHUNK_PROCESS_X(x, UINT, true,
         *px64 = dup64; ,
         *px32 = dup32; ,
         *px16 = dup16; ,
         *px8  = v;)
   #endif
   }

   /// <summary>
   /// Template Specialization for 16-Bit Integer.
   /// </summary>
   template<> INLINE void bytedup<uint16_t>(const uint8_t& v, uint16_t& x)
   {
      x = CppCore::bytedup16(v);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Integer.
   /// </summary>
   template<> INLINE void bytedup<uint32_t>(const uint8_t& v, uint32_t& x)
   {
      x = CppCore::bytedup32(v);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Integer.
   /// </summary>
   template<> INLINE void bytedup<uint64_t>(const uint8_t& v, uint64_t& x)
   {
      x = CppCore::bytedup64(v);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MOVBE: REVERSE LOAD
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Loads 16-bit unsigned integer in reverse byte order.
   /// </summary>
   static INLINE uint16_t loadr16(const uint16_t mem[1])
   {
   #if defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_MSVC)
      return _load_be_u16(mem);
   #elif defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_CLANG)
      return _loadbe_i16(mem);
   #else
      return CppCore::byteswap16(*mem);
   #endif
   }

   /// <summary>
   /// Loads 32-bit unsigned integer in reverse byte order.
   /// </summary>
   static INLINE uint32_t loadr32(const uint32_t mem[1])
   {
   #if defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_MSVC)
      return _load_be_u32(mem);
   #elif defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_CLANG)
      return _loadbe_i32(mem);
   #else
      return CppCore::byteswap32(*mem);
   #endif
   }

   /// <summary>
   /// Loads 64-bit unsigned integer in reverse byte order.
   /// </summary>
   static INLINE uint64_t loadr64(const uint64_t mem[1])
   {
   #if defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_MSVC)
      return _load_be_u64(mem);
   #elif defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_CLANG) && defined(CPPCORE_CPU_X64)
      return _loadbe_i64(mem);
   #else
      return CppCore::byteswap64(*mem);
   #endif
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Loads 128-bit unsigned integer in reverse byte order. 
   /// Requires SSE2. Uses SSSE3 if available.
   /// </summary>
   template<bool ALIGNED = false>
   static INLINE __m128i loadr128(const __m128i mem[1])
   {
   #if defined(CPPCORE_CPUFEAT_SSSE3)
      return _mm_shuffle_epi8(ALIGNED ? _mm_load_si128(mem) : _mm_loadu_si128(mem), 
         _mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
   #elif defined(CPPCORE_CPU_64BIT)
      return _mm_set_epi64x(
         CppCore::loadr64(&(((uint64_t*)mem)[0])),
         CppCore::loadr64(&(((uint64_t*)mem)[1])));
   #else
      return _mm_set_epi32(
         CppCore::loadr32(&(((uint32_t*)mem)[0])), 
         CppCore::loadr32(&(((uint32_t*)mem)[1])),
         CppCore::loadr32(&(((uint32_t*)mem)[2])),
         CppCore::loadr32(&(((uint32_t*)mem)[3])));
   #endif
   }
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MOVBE: REVERSE STORE
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Stores 16-bit unsigned integer in reverse byte order.
   /// </summary>
   static INLINE void storer16(uint16_t mem[1], const uint16_t v)
   {
   #if defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_MSVC)
      _store_be_u16(mem, v);
   #elif defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_CLANG)
      _storebe_i16(mem, v);
   #else
      *mem = CppCore::byteswap16(v);
   #endif
   }

   /// <summary>
   /// Stores 32-bit unsigned integer in reverse byte order.
   /// </summary>
   static INLINE void storer32(uint32_t mem[1], const uint32_t v)
   {
   #if defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_MSVC)
      _store_be_u32(mem, v);
   #elif defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_CLANG)
      _storebe_i32(mem, v);
   #else
      *mem = CppCore::byteswap32(v);
   #endif
   }

   /// <summary>
   /// Stores 64-bit unsigned integer in reverse byte order.
   /// </summary>
   static INLINE void storer64(uint64_t mem[1], const uint64_t v)
   {
   #if defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_MSVC)
      _store_be_u64(mem, v);
   #elif defined(CPPCORE_CPUFEAT_MOVBE) && defined(CPPCORE_COMPILER_CLANG) && defined(CPPCORE_CPU_X64)
      _storebe_i64(mem, v);
   #else
      *mem = CppCore::byteswap64(v);
   #endif
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Stores 128-bit unsigned integer in reverse byte order. 
   /// Requires SSE2. Uses SSSE3 if available.
   /// </summary>
   template<bool ALIGNED = false>
   static INLINE void storer128(__m128i mem[1], const __m128i v)
   {
   #if defined(CPPCORE_CPUFEAT_SSSE3)
      const __m128i t(_mm_shuffle_epi8(v, 
         _mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)));
      if (ALIGNED) _mm_store_si128( mem, t);
      else         _mm_storeu_si128(mem, t);
   #elif defined(CPPCORE_CPU_64BIT)
      CppCore::storer64(&((uint64_t*)mem)[1], ((uint64_t*)&v)[0]);
      CppCore::storer64(&((uint64_t*)mem)[0], ((uint64_t*)&v)[1]);
   #else
      CppCore::storer32(&((uint32_t*)mem)[3], ((uint32_t*)&v)[0]);
      CppCore::storer32(&((uint32_t*)mem)[2], ((uint32_t*)&v)[1]);
      CppCore::storer32(&((uint32_t*)mem)[1], ((uint32_t*)&v)[2]);
      CppCore::storer32(&((uint32_t*)mem)[0], ((uint32_t*)&v)[3]);
   #endif
   }
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ZBYTEIDXL: FIND INDEX OF FIRST ZERO BYTE FROM LEFT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns index (0-3) of first 0x00 byte in 32-Bit integer or 4 if none found (counted from left).
   /// </summary>
   static INLINE uint32_t zbyteidxl32(const uint32_t v)
   {
      // From Hacker's Delight
      return CppCore::lzcnt32(~(((v & 0x7F7F7F7FU) + 0x7F7F7F7FU) | v | 0x7F7F7F7FU)) >> 3;
   }

   /// <summary>
   /// Returns index (0-7) of first 0x00 byte in 64-Bit integer or 8 if none found (counted from left).
   /// </summary>
   static INLINE uint64_t zbyteidxl64(const uint64_t v)
   {
      // From Hacker's Delight
      return CppCore::lzcnt64(~(((v & 0x7F7F7F7F7F7F7F7FULL) + 0x7F7F7F7F7F7F7F7FULL) | v | 0x7F7F7F7F7F7F7F7FULL)) >> 3;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns index (0-15) of first 0x00 byte in 128-Bit integer or 16 if none found (counted from left).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint32_t zbyteidxl128(const __m128i& v)
   {
      return CppCore::lzcnt32(bytemaskequal128(v, _mm_setzero_si128())) - 16U;
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Returns index (0-31) of first 0x00 byte in 256-Bit integer or 32 if none found (counted from left).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint32_t zbyteidxl256(const __m256i& v)
   {
      return CppCore::lzcnt32(bytemaskequal256(v, _mm256_setzero_si256()));
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
   /// <summary>
   /// Returns index (0-63) of first 0x00 byte in 512-Bit integer or 64 if none found (counted from left).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint64_t zbyteidxl512(const __m512i& v)
   {
      return CppCore::lzcnt64(bytemaskequal512(v, _mm512_setzero_si512()));
   }
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ZBYTEIDXR: FIND INDEX OF FIRST ZERO BYTE FROM RIGHT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns index (0-3) of first 0x00 byte in 32-Bit integer or 4 if none found (counted from right).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint32_t zbyteidxr32(const uint32_t v)
   {
      // From Hacker's Delight
      return CppCore::tzcnt32((v - 0x01010101U) & ~v & 0x80808080U) >> 3;
   }

   /// <summary>
   /// Returns index (0-7) of first 0x00 byte in 64-Bit integer or 8 if none found (counted from right).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint64_t zbyteidxr64(const uint64_t v)
   {
      // From Hacker's Delight
      return CppCore::tzcnt64((v - 0x0101010101010101ULL) & ~v & 0x8080808080808080ULL) >> 3;
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns index (0-15) of first 0x00 byte in 128-Bit integer or 32 if none found (counted from right).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint32_t zbyteidxr128(const __m128i& v)
   {
      return CppCore::tzcnt32(CppCore::bytemaskequal128(v, _mm_setzero_si128()));
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Returns index (0-31) of first 0x00 byte in 256-Bit integer or 32 if none found (counted from right).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint32_t zbyteidxr256(const __m256i& v)
   {
      return CppCore::tzcnt32(CppCore::bytemaskequal256(v, _mm256_setzero_si256()));
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
   /// <summary>
   /// Returns index (0-63) of first 0x00 byte in 512-Bit integer or 64 if none found (counted from right).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint64_t zbyteidxr512(const __m512i& v)
   {
      return CppCore::tzcnt64(CppCore::bytemaskequal512(v, _mm512_setzero_si512()));
   }
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BYTEIDXL: FIND INDEX OF FIRST SPECIFIED BYTE FROM LEFT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns index (0-3) of first c byte in 32-Bit integer or 4 if none found (counted from left).
   /// </summary>
   static INLINE uint32_t byteidxl32(const uint32_t v, const char c)
   {
      return CppCore::zbyteidxl32(v ^ CppCore::bytedup32(c));
   }

   /// <summary>
   /// Returns index (0-7) of first c byte in 64-Bit integer or 8 if none found (counted from left).
   /// </summary>
   static INLINE uint64_t byteidxl64(const uint64_t v, const char c)
   {
      return CppCore::zbyteidxl64(v ^ CppCore::bytedup64(c));
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns index (0-15) of first c byte in 128-Bit integer or 16 if none found (counted from left).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint32_t byteidxl128(const __m128i& v, const char c)
   {
      return CppCore::lzcnt32(bytemaskequal128(v, _mm_set1_epi8(c))) - 16U;
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Returns index (0-31) of first c byte in 256-Bit integer or 32 if none found (counted from left).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint32_t byteidxl256(const __m256i& v, const char c)
   {
      return CppCore::lzcnt32(bytemaskequal256(v, _mm256_set1_epi8(c)));
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
   /// <summary>
   /// Returns index (0-63) of first c byte in 512-Bit integer or 64 if none found (counted from left).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint64_t byteidxl512(const __m512i& v, const char c)
   {
      return CppCore::lzcnt64(bytemaskequal512(v, _mm512_set1_epi8(c)));
   }
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BYTEIDXR: FIND INDEX OF FIRST SPECIFIED BYTE FROM RIGHT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns index (0-3) of first c byte in 32-Bit integer or 4 if none found (counted from right).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint32_t byteidxr32(const uint32_t v, const char c)
   {
      return CppCore::zbyteidxr32(v ^ CppCore::bytedup32(c));
   }

   /// <summary>
   /// Returns index (0-7) of first c byte in 64-Bit integer or 8 if none found (counted from right).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint64_t byteidxr64(const uint64_t v, const char c)
   {
      return CppCore::zbyteidxr64(v ^ CppCore::bytedup64(c));
   }

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Returns index (0-15) of first c byte in 128-Bit integer or 32 if none found (counted from right).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint32_t byteidxr128(const __m128i& v, const char c)
   {
      return CppCore::tzcnt32(bytemaskequal128(v, _mm_set1_epi8(c)));
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
   /// <summary>
   /// Returns index (0-31) of first c byte in 256-Bit integer or 32 if none found (counted from right).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint32_t byteidxr256(const __m256i& v, const char c)
   {
      return CppCore::tzcnt32(bytemaskequal256(v, _mm256_set1_epi8(c)));
   }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
   /// <summary>
   /// Returns index (0-63) of first c byte in 512-Bit integer or 64 if none found (counted from right).
   /// Do not use for processing memory/many, see Memory.h for more efficient version for such case.
   /// </summary>
   static INLINE uint64_t byteidxr512(const __m512i& v, const char c)
   {
      return CppCore::tzcnt64(bytemaskequal512(v, _mm512_set1_epi8(c)));
   }
#endif
}
