#pragma once

#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>

#define CPPCORE_MEMORY_SWITCH_LEN15(len, op64, op32, op16, op8) \
  switch ((len)) {                                           \
  case 15: { { op64; } { op32; } { op16; } { op8; } } break; \
  case 14: { { op64; } { op32; } { op16; }          } break; \
  case 13: { { op64; } { op32; }           { op8; } } break; \
  case 12: { { op64; } { op32; }                    } break; \
  case 11: { { op64; }           { op16; } { op8; } } break; \
  case 10: { { op64; }           { op16; }          } break; \
  case 9:  { { op64; }                     { op8; } } break; \
  case 8:  { { op64; }                              } break; \
  case 7:  {           { op32; } { op16; } { op8; } } break; \
  case 6:  {           { op32; } { op16; }          } break; \
  case 5:  {           { op32; }           { op8; } } break; \
  case 4:  {           { op32; }                    } break; \
  case 3:  {                     { op16; } { op8; } } break; \
  case 2:  {                     { op16; }          } break; \
  case 1:  {                               { op8; } } break; \
  default:                                            break; \
  };

#define CPPCORE_MEMORY_PROCESS_512(len, op512, op256, op128, op64, op32, op16, op8) \
  while (len >= 64U) { \
    len -= 64U;        \
    op512;             \
  }                    \
  if (len >= 32U) {    \
    len -= 32U;        \
    op256;             \
  }                    \
  if (len >= 16U) {    \
    len -= 16U;        \
    op128;             \
  }                    \
  CPPCORE_MEMORY_SWITCH_LEN15(len, op64, op32, op16, op8)

#define CPPCORE_MEMORY_PROCESS_256(len,                                           op256,                op128,      op64, op32, op16, op8) \
        CPPCORE_MEMORY_PROCESS_512(len, op256;op256;,                             op256,                op128,      op64, op32, op16, op8)
#define CPPCORE_MEMORY_PROCESS_128(len,                                                                 op128,      op64, op32, op16, op8) \
        CPPCORE_MEMORY_PROCESS_512(len, op128;op128;op128;op128;,                 op128;op128;,         op128,      op64, op32, op16, op8)
#define CPPCORE_MEMORY_PROCESS_64( len,                                                                             op64, op32, op16, op8) \
        CPPCORE_MEMORY_PROCESS_512(len, op64;op64;op64;op64;op64;op64;op64;op64;, op64;op64;op64;op64;, op64;op64;, op64, op32, op16, op8)


namespace CppCore
{
   /// <summary>
   /// Memory
   /// </summary>
   class Memory
   {
   private:
      INLINE Memory() { }

   public:
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ALLOCATION
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Allocates size*sizeof(T) unaligned memory.
      /// </summary>
      template<typename T = char>
      INLINE static T* alloc(const size_t size)
      {
         return (T*)::malloc(size * sizeof(T));
      }

      /// <summary>
      /// Frees unaligned memory.
      /// </summary>
      INLINE static void free(void* mem)
      {
         ::free(mem);
      }

      /// <summary>
      /// Allocates aligned memory on the heap with a size of:
      /// size*sizeof(T) rounded up to next multiple of alignment which must be a power of 2.
      /// </summary>
      template<typename T = char>
      INLINE static T* alignedalloc(const size_t size, const size_t alignment = 16)
      {
         assert(CppCore::popcnt(alignment) == 1U);
         return (T*)CPPCORE_ALIGNED_ALLOC(
            CppCore::rupptwo(size * sizeof(T), alignment), 
            alignment);
      }

      /// <summary>
      /// Frees aligned memory.
      /// </summary>
      INLINE static void alignedfree(void* mem)
      {
         CPPCORE_ALIGNED_FREE(mem);
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SET
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Set memory that's multiple of 8-bit from 8-bit integer.
      /// </summary>
      INLINE static void set8(uint8_t* mem, const size_t n8, const uint8_t v)
      {
         for (size_t i = 0; i < n8; i++)
            mem[i] = v;
      }

      /// <summary>
      /// Set memory that's multiple of 16-bit from 16-bit integer.
      /// </summary>
      INLINE static void set16(uint16_t* mem, const size_t n16, const uint16_t v)
      {
         for (size_t i = 0; i < n16; i++)
            mem[i] = v;
      }

      /// <summary>
      /// Set memory that's multiple of 32-bit from 32-bit integer.
      /// </summary>
      INLINE static void set32(uint32_t* mem, const size_t n32, const uint32_t v)
      {
         for (size_t i = 0; i < n32; i++)
            mem[i] = v;
      }

      /// <summary>
      /// Set memory that's multiple of 64-bit from 64-bit integer.
      /// </summary>
      INLINE static void set64(uint64_t* mem, const size_t n64, const uint64_t v)
      {
         for (size_t i = 0; i < n64; i++)
            mem[i] = v;
      }

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Set memory that's multiple of 128-bit from 128-bit integer.
      /// Requires SSE2.
      /// </summary>
      template<bool ALIGNED=false>
      INLINE static void set128(__m128i* mem, const size_t n128, const __m128i v)
      {
         if (ALIGNED) for (size_t i = 0; i < n128; i++) _mm_store_si128 (&mem[i], v);
         else         for (size_t i = 0; i < n128; i++) _mm_storeu_si128(&mem[i], v);
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Set memory that's multiple of 256-bit from 256-bit integer.
      /// Requirers AVX.
      /// </summary>
      template<bool ALIGNED=false>
      INLINE static void set256(__m256i* mem, const size_t n256, const __m256i v)
      {
         if (ALIGNED) for (size_t i = 0; i < n256; i++) _mm256_store_si256 (&mem[i], v);
         else         for (size_t i = 0; i < n256; i++) _mm256_storeu_si256(&mem[i], v);
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
      /// <summary>
      /// Set memory that's multiple of 512-bit from 512-bit integer.
      /// Requires AVX512.
      /// </summary>
      template<bool ALIGNED=false>
      INLINE static void set512(__m512i* mem, const size_t n512, const __m512i v)
      {
         if (ALIGNED) for (size_t i = 0; i < n512; i++) _mm512_store_si512 (&mem[i], v);
         else         for (size_t i = 0; i < n512; i++) _mm512_storeu_si512(&mem[i], v);
      }
#endif

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STREAMSET
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Stream-Set aligned memory that's multiple of 128-bit from 128-bit integer.
      /// Requires SSE2 and memory aligned to 16 bytes.
      /// </summary>
      INLINE static void streamset128(__m128i* mem, const size_t n128, const __m128i v)
      {
         CPPCORE_ASSERT_MULTIPLE16(mem);
         for (size_t i = 0; i < n128; i++) 
            _mm_stream_si128 (&mem[i], v);
      }

      /// <summary>
      /// Stream-Set aligned memory that's multiple of 128-bit from 128-bit integer.
      /// Requires SSE2 and memory aligned to 16 bytes.
      /// </summary>
      INLINE static void streamset128x1(void* mem, const size_t len, const __m128i v)
      {
         CPPCORE_ASSERT_MULTIPLE16(mem);
         //CPPCORE_ASSERT_MULTIPLE16(len);
         __m128i* m = (__m128i*)mem;
         __m128i* e = (__m128i*)((char*)mem + len);
         for (; m < e; m++)
            _mm_stream_si128(m, v);
      }

      /// <summary>
      /// Stream-Set aligned memory that's multiple of 256-bit from 128-bit integer.
      /// Requires SSE2 and memory aligned to 16 bytes.
      /// </summary>
      INLINE static void streamset128x2(void* mem, const size_t len, const __m128i v)
      {
         CPPCORE_ASSERT_MULTIPLE16(mem);
         //CPPCORE_ASSERT_MULTIPLE32(len);
         __m128i* m = (__m128i*)mem;
         __m128i* e = (__m128i*)((char*)mem + len);
         while (m < e)
         {
            _mm_stream_si128(m, v); m++;
            _mm_stream_si128(m, v); m++;
         }
      }

      /// <summary>
      /// Stream-Set aligned memory that's multiple of 512-bit from 128-bit integer.
      /// Requires SSE2 and memory aligned to 16 bytes.
      /// </summary>
      INLINE static void streamset128x4(void* mem, const size_t len, const __m128i v)
      {
         CPPCORE_ASSERT_MULTIPLE16(mem);
         //CPPCORE_ASSERT_MULTIPLE64(len);
         __m128i* m = (__m128i*)mem;
         __m128i* e = (__m128i*)((char*)mem + len);
         while (m < e)
         {
            _mm_stream_si128(m, v); m++;
            _mm_stream_si128(m, v); m++;
            _mm_stream_si128(m, v); m++;
            _mm_stream_si128(m, v); m++;
         }
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Stream-Set aligned memory that's multiple of 256-bit from 256-bit integer.
      /// Requires AVX and memory aligned to 32 bytes.
      /// </summary>
      INLINE static void streamset256(__m256i* mem, const size_t n256, const __m256i v)
      {
         CPPCORE_ASSERT_MULTIPLE32(mem);
         for (size_t i = 0; i < n256; i++)
            _mm256_stream_si256(&mem[i], v);
      }

      /// <summary>
      /// Stream-Set aligned memory that's multiple of 256-bit from 256-bit integer.
      /// Requires AVX and memory aligned to 32 bytes.
      /// </summary>
      INLINE static void streamset256x1(void* mem, const size_t len, const __m256i v)
      {
         CPPCORE_ASSERT_MULTIPLE32(mem);
         //CPPCORE_ASSERT_MULTIPLE32(len);
         __m256i* m = (__m256i*)mem;
         __m256i* e = (__m256i*)((char*)mem + len);
         for (; m < e; m++)
            _mm256_stream_si256(m, v);
      }

      /// <summary>
      /// Stream-Set aligned memory that's multiple of 512-bit from 256-bit integer.
      /// Requires AVX and memory aligned to 32 bytes.
      /// </summary>
      INLINE static void streamset256x2(void* mem, const size_t len, const __m256i v)
      {
         CPPCORE_ASSERT_MULTIPLE32(mem);
         //CPPCORE_ASSERT_MULTIPLE64(len);
         __m256i* m = (__m256i*)mem;
         __m256i* e = (__m256i*)((char*)mem + len);
         while (m < e)
         {
            _mm256_stream_si256(m, v); m++;
            _mm256_stream_si256(m, v); m++;
         }
      }

      /// <summary>
      /// Stream-Set aligned memory that's multiple of 1024-bit from 256-bit integer.
      /// Requires AVX and memory aligned to 32 bytes.
      /// </summary>
      INLINE static void streamset256x4(void* mem, const size_t len, const __m256i v)
      {
         CPPCORE_ASSERT_MULTIPLE32(mem);
         //CPPCORE_ASSERT_MULTIPLE128(len);
         __m256i* m = (__m256i*)mem;
         __m256i* e = (__m256i*)((char*)mem + len);
         while (m < e)
         {
            _mm256_stream_si256(m, v); m++;
            _mm256_stream_si256(m, v); m++;
            _mm256_stream_si256(m, v); m++;
            _mm256_stream_si256(m, v); m++;
         }
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
      /// <summary>
      /// Stream-Set aligned memory that's multiple of 512-bit from 512-bit integer.
      /// Requires AVX512 and memory aligned to 64 bytes.
      /// </summary>
      INLINE static void streamset512(__m512i* mem, const size_t n512, const __m512i v)
      {
         CPPCORE_ASSERT_MULTIPLE64(mem);
         for (size_t i = 0; i < n512; i++)
            _mm512_stream_si512(&mem[i], v);
      }

      /// <summary>
      /// Stream-Set aligned memory that's multiple of 512-bit from 512-bit integer.
      /// Requires AVX512 and memory aligned to 64 bytes.
      /// </summary>
      INLINE static void streamset512x1(void* mem, const size_t len, const __m512i v)
      {
         CPPCORE_ASSERT_MULTIPLE64(mem);
         //CPPCORE_ASSERT_MULTIPLE64(len);
         __m512i* m = (__m512i*)mem;
         __m512i* e = (__m512i*)((char*)mem + len);
         for (; m < e; m++)
            _mm512_stream_si512(m, v);
      }

      /// <summary>
      /// Stream-Set aligned memory that's multiple of 1024-bit from 512-bit integer.
      /// Requires AVX512 and memory aligned to 64 bytes.
      /// </summary>
      INLINE static void streamset512x2(void* mem, const size_t len, const __m512i v)
      {
         CPPCORE_ASSERT_MULTIPLE64(mem);
         //CPPCORE_ASSERT_MULTIPLE128(len);
         __m512i* m = (__m512i*)mem;
         __m512i* e = (__m512i*)((char*)mem + len);
         while (m < e)
         {
            _mm512_stream_si512(m, v); m++;
            _mm512_stream_si512(m, v); m++;
         }
      }

      /// <summary>
      /// Stream-Set aligned memory that's multiple of 2048-bit from 512-bit integer.
      /// Requires AVX512 and memory aligned to 64 bytes.
      /// </summary>
      INLINE static void streamset512x4(void* mem, const size_t len, const __m512i v)
      {
         CPPCORE_ASSERT_MULTIPLE64(mem);
         //CPPCORE_ASSERT_MULTIPLE256(len);
         __m512i* m = (__m512i*)mem;
         __m512i* e = (__m512i*)((char*)mem + len);
         while (m < e)
         {
            _mm512_stream_si512(m, v); m++;
            _mm512_stream_si512(m, v); m++;
            _mm512_stream_si512(m, v); m++;
            _mm512_stream_si512(m, v); m++;
         }
      }
#endif

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CLEAR
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// Shortcut for calling set8() with zero value.
      /// </summary>
      INLINE static void clear8(uint8_t* mem, const size_t n8)
      {
         Memory::set8(mem, n8, (uint8_t)0U);
      }

      /// <summary>
      /// Shortcut for calling set16() with zero value.
      /// </summary>
      INLINE static void clear16(uint16_t* mem, const size_t n16)
      {
         Memory::set16(mem, n16, (uint16_t)0U);
      }

      /// <summary>
      /// Shortcut for calling set32() with zero value.
      /// </summary>
      INLINE static void clear32(uint32_t* mem, const size_t n32)
      {
         Memory::set32(mem, n32, 0U);
      }

      /// <summary>
      /// Shortcut for calling set64() with zero value.
      /// </summary>
      INLINE static void clear64(uint64_t* mem, const size_t n64)
      {
         Memory::set64(mem, n64, 0ULL);
      }

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Shortcut for calling set128() with zero value.
      /// Requires SSE2.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static void clear128(__m128i* mem, const size_t n128)
      {
         Memory::set128<ALIGNED>(mem, n128, _mm_setzero_si128());
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Shortcut for calling set256() with zero value.
      /// Requires AVX.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static void clear256(__m256i* mem, const size_t n256)
      {
         Memory::set256<ALIGNED>(mem, n256, _mm256_setzero_si256());
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
      /// <summary>
      /// Shortcut for calling set512() with zero value.
      /// Requires AVX512.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static void clear512(__m512i* mem, const size_t n512)
      {
         Memory::set512<ALIGNED>(mem, n512, _mm512_setzero_si512());
      }
#endif

      /// <summary>
      /// Clears any sized memory with any alignment.
      /// Consider using optimized clearXY() or streamclearXY() for special cases instead.
      /// </summary>
      INLINE static void clear(void* m, const size_t len)
      {
         char*       mem = (char*)m;
         const char* end = mem + len;
      #if defined(CPPCORE_CPUFEAT_AVX512F)
         const __m512i z512 = _mm512_setzero_si512();
      #endif
      #if defined(CPPCORE_CPUFEAT_AVX)
         const __m256i z256 = _mm256_setzero_si256();
      #endif
      #if defined(CPPCORE_CPUFEAT_SSE2)
         const __m128i z128 = _mm_setzero_si128();
      #endif
         while (mem + 64U <= end)
         {
         #if defined(CPPCORE_CPUFEAT_AVX512F)
            _mm512_storeu_si512((__m512i*)mem, z512); mem += 64U;
         #elif defined(CPPCORE_CPUFEAT_AVX)
            _mm256_storeu_si256((__m256i*)mem, z256); mem += 32U;
            _mm256_storeu_si256((__m256i*)mem, z256); mem += 32U;
         #elif defined(CPPCORE_CPUFEAT_SSE2)
            _mm_storeu_si128((__m128i*)mem, z128); mem += 16U;
            _mm_storeu_si128((__m128i*)mem, z128); mem += 16U;
            _mm_storeu_si128((__m128i*)mem, z128); mem += 16U;
            _mm_storeu_si128((__m128i*)mem, z128); mem += 16U;
         #elif defined(CPPCORE_CPU_64BIT)
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
         #else
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
         #endif
         }
         if (mem + 32U <= end)
         {
         #if defined(CPPCORE_CPUFEAT_AVX)
            _mm256_storeu_si256((__m256i*)mem, z256); mem += 32U;
         #elif defined(CPPCORE_CPUFEAT_SSE2)
            _mm_storeu_si128((__m128i*)mem, z128); mem += 16U;
            _mm_storeu_si128((__m128i*)mem, z128); mem += 16U;
         #elif defined(CPPCORE_CPU_64BIT)
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
         #else
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
         #endif
         }
         if (mem + 16U <= end)
         {
         #if defined(CPPCORE_CPUFEAT_SSE2)
            _mm_storeu_si128((__m128i*)mem, z128); mem += 16U;
         #elif defined(CPPCORE_CPU_64BIT)
            *((uint64_t*)mem) = 0ULL; mem += 8U;
            *((uint64_t*)mem) = 0ULL; mem += 8U;
         #else
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
         #endif
         }
         if (mem + 8U <= end)
         {
         #if defined(CPPCORE_CPU_64BIT)
            *((uint64_t*)mem) = 0ULL; mem += 8U;
         #else
            *((uint32_t*)mem) = 0U; mem += 4U;
            *((uint32_t*)mem) = 0U; mem += 4U;
         #endif
         }
         if (mem + 4U <= end)
         {
            *((uint32_t*)mem) = (uint32_t)0U;
            mem += 4U;
         }
         if (mem + 2U <= end)
         {
            *((uint16_t*)mem) = (uint16_t)0U;
            mem += 2U;
         }
         if (mem < end)
            *((uint8_t*)mem) = (uint8_t)0U;
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STREAMCLEAR
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Shortcut for calling streamset128() with zero value.
      /// Requires SSE2.
      /// </summary>
      INLINE static void streamclear128(__m128i* mem, const size_t n128)
      {
         Memory::streamset128(mem, n128, _mm_setzero_si128());
      }

      /// <summary>
      /// Shortcut for calling streamset128x1() with zero value.
      /// Requires SSE2.
      /// </summary>
      INLINE static void streamclear128x1(void* mem, const size_t len)
      {
         Memory::streamset128x1(mem, len, _mm_setzero_si128());
      }

      /// <summary>
      /// Shortcut for calling streamset128x2() with zero value.
      /// Requires SSE2.
      /// </summary>
      INLINE static void streamclear128x2(void* mem, const size_t len)
      {
         Memory::streamset128x2(mem, len, _mm_setzero_si128());
      }

      /// <summary>
      /// Shortcut for calling streamset128x4() with zero value.
      /// Requires SSE2.
      /// </summary>
      INLINE static void streamclear128x4(void* mem, const size_t len)
      {
         Memory::streamset128x4(mem, len, _mm_setzero_si128());
      }
#else
      /// <summary>
      /// Fallback Version without Intrinsics.
      /// len must be multiple of 16 bytes.
      /// </summary>
      INLINE static void streamclear128x1(void* mem, const size_t len)
      {
         Memory::clear(mem, len);
      }

      /// <summary>
      /// Fallback Version without Intrinsics.
      /// len must be multiple of 32 bytes.
      /// </summary>
      INLINE static void streamclear128x2(void* mem, const size_t len)
      {
         Memory::clear(mem, len);
      }

      /// <summary>
      /// Fallback Version without Intrinsics.
      /// len must be multiple of 64 bytes.
      /// </summary>
      INLINE static void streamclear128x4(void* mem, const size_t len)
      {
         Memory::clear(mem, len);
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Shortcut for calling streamset256() with zero value.
      /// Requires AVX.
      /// </summary>
      INLINE static void streamclear256(__m256i* mem, const size_t n256)
      {
         Memory::streamset256(mem, n256, _mm256_setzero_si256());
      }

      /// <summary>
      /// Shortcut for calling streamset256x1() with zero value.
      /// len must be multiple of 32 bytes. Requires AVX.
      /// </summary>
      INLINE static void streamclear256x1(void* mem, const size_t len)
      {
         Memory::streamset256x1(mem, len, _mm256_setzero_si256());
      }

      /// <summary>
      /// Shortcut for calling streamset256x2() with zero value.
      /// len must be multiple of 64 bytes. Requires AVX.
      /// </summary>
      INLINE static void streamclear256x2(void* mem, const size_t len)
      {
         Memory::streamset256x2(mem, len, _mm256_setzero_si256());
      }

      /// <summary>
      /// Shortcut for calling streamset256x4() with zero value.
      /// len must be multiple of 128 bytes. Requires AVX.
      /// </summary>
      INLINE static void streamclear256x4(void* mem, const size_t len)
      {
         Memory::streamset256x4(mem, len, _mm256_setzero_si256());
      }
#else
      /// <summary>
      /// Fallback Version without Intrinsics.
      /// len must be multiple of 32 bytes.
      /// </summary>
      INLINE static void streamclear256x1(void* mem, const size_t len)
      {
         Memory::clear(mem, len);
      }

      /// <summary>
      /// Fallback Version without Intrinsics.
      /// len must be multiple of 64 bytes.
      /// </summary>
      INLINE static void streamclear256x2(void* mem, const size_t len)
      {
         Memory::clear(mem, len);
      }

      /// <summary>
      /// Fallback Version without Intrinsics.
      /// len must be multiple of 128 bytes.
      /// </summary>
      INLINE static void streamclear256x4(void* mem, const size_t len)
      {
         Memory::clear(mem, len);
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
      /// <summary>
      /// Shortcut for calling streamset512() with zero value.
      /// Requires AVX512.
      /// </summary>
      INLINE static void streamclear512(__m512i* mem, const size_t n512)
      {
         Memory::streamset512(mem, n512, _mm512_setzero_si512());
      }

      /// <summary>
      /// Shortcut for calling streamset512x1() with zero value.
      /// len must be multiple of 64 bytes. Requires AVX512.
      /// </summary>
      INLINE static void streamclear512x1(void* mem, const size_t len)
      {
         Memory::streamset512x1(mem, len, _mm512_setzero_si512());
      }

      /// <summary>
      /// Shortcut for calling streamset512x2() with zero value.
      /// len must be multiple of 128 bytes. Requires AVX512.
      /// </summary>
      INLINE static void streamclear512x2(void* mem, const size_t len)
      {
         Memory::streamset512x2(mem, len, _mm512_setzero_si512());
      }

      /// <summary>
      /// Shortcut for calling streamset512x4() with zero value.
      /// len must be multiple of 256 bytes. Requires AVX512.
      /// </summary>
      INLINE static void streamclear512x4(void* mem, const size_t len)
      {
         Memory::streamset512x4(mem, len, _mm512_setzero_si512());
      }
#else
      /// <summary>
      /// Fallback Version without Intrinsics.
      /// len must be multiple of 64 bytes.
      /// </summary>
      INLINE static void streamclear512x1(void* mem, const size_t len)
      {
         Memory::clear(mem, len);
      }

      /// <summary>
      /// Fallback Version without Intrinsics.
      /// len must be multiple of 128 bytes.
      /// </summary>
      INLINE static void streamclear512x2(void* mem, const size_t len)
      {
         Memory::clear(mem, len);
      }

      /// <summary>
      /// Fallback Version without Intrinsics. 
      /// len must be multiple of 256 bytes.
      /// </summary>
      INLINE static void streamclear512x4(void* mem, const size_t len)
      {
         Memory::clear(mem, len);
      }
#endif

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // EQUAL
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns true if m1 and m2 have n8 identical 8-Bit chunks.
      /// </summary>
      INLINE static bool equal8(const uint8_t* m1, const uint8_t* m2, const size_t n8)
      {
         for (size_t i = 0; i < n8; i++)
            if (m1[i] != m2[i])
               return false;
         return true;
      }

      /// <summary>
      /// Returns true if m1 and m2 have n16 identical 16-Bit chunks.
      /// </summary>
      INLINE static bool equal16(const uint16_t* m1, const uint16_t* m2, const size_t n16)
      {
         for (size_t i = 0; i < n16; i++)
            if (m1[i] != m2[i])
               return false;
         return true;
      }

      /// <summary>
      /// Returns true if m1 and m2 have n32 identical 32-Bit chunks.
      /// </summary>
      INLINE static bool equal32(const uint32_t* m1, const uint32_t* m2, const size_t n32)
      {
         for (size_t i = 0; i < n32; i++)
            if (m1[i] != m2[i])
               return false;
         return true;
      }

      /// <summary>
      /// Returns true if m1 and m2 have n64 identical 64-Bit chunks.
      /// </summary>
      INLINE static bool equal64(const uint64_t* m1, const uint64_t* m2, const size_t n64)
      {
         for (size_t i = 0; i < n64; i++)
            if (m1[i] != m2[i])
               return false;
         return true;
      }

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Returns true if m1 and m2 have n128 identical 128-Bit chunks. 
      /// Requires SSE2.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static bool equal128(const __m128i* m1, const __m128i* m2, const size_t n128)
      {
         for (size_t i = 0; i < n128; i++)
            if (!CppCore::equal128(
               ALIGNED ? _mm_load_si128(&m1[i]) : _mm_loadu_si128(&m1[i]), 
               ALIGNED ? _mm_load_si128(&m2[i]) : _mm_loadu_si128(&m2[i])))
               return false;
         return true;
      }

      /// <summary>
      /// Returns true if m1 and m2 have n128 identical 128-Bit chunks.
      /// Requires SSE2.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static bool equal128o(const __m128i* m1, const __m128i* m2, const size_t n128)
      {
         __m128i v(_mm_cmpeq_epi32(
            ALIGNED ? _mm_load_si128(&m1[0]) : _mm_loadu_si128(&m1[0]),
            ALIGNED ? _mm_load_si128(&m2[0]) : _mm_loadu_si128(&m2[0])));
         for (size_t i = 1; i < n128; i++)
            v = CppCore::and128(v, _mm_cmpeq_epi32(
               ALIGNED ? _mm_load_si128(&m1[i]) : _mm_loadu_si128(&m1[i]),
               ALIGNED ? _mm_load_si128(&m2[i]) : _mm_loadu_si128(&m2[i])));
      #if defined(CPPCORE_CPUFEAT_SSE41)
         return _mm_testc_si128(v, _mm_set1_epi32(0xFFFFFFFFU));
      #else
         return _mm_movemask_epi8(v) == 0xFFFFU;
      #endif
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
      /// <summary>
      /// Returns true if m1 and m2 have n256 identical 256-Bit chunks.
      /// Requires AVX2.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static bool equal256(const __m256i* m1, const __m256i* m2, const size_t n256)
      {
         for (size_t i = 0; i < n256; i++)
            if (!CppCore::equal256(
               ALIGNED ? _mm256_load_si256(&m1[i]) : _mm256_loadu_si256(&m1[i]),
               ALIGNED ? _mm256_load_si256(&m2[i]) : _mm256_loadu_si256(&m2[i])))
               return false;
         return true;
      }

      /// <summary>
      /// Returns true if m1 and m2 have n256 identical 256-Bit chunks.
      /// Requires AVX2.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static bool equal256o(const __m256i* m1, const __m256i* m2, const size_t n256)
      {
         __m256i v(_mm256_cmpeq_epi64(
            ALIGNED ? _mm256_load_si256(&m1[0]) : _mm256_loadu_si256(&m1[0]), 
            ALIGNED ? _mm256_load_si256(&m2[0]) : _mm256_loadu_si256(&m2[0])));
         for (size_t i = 1; i < n256; i++)
            v = CppCore::and256(v, _mm256_cmpeq_epi64(
               ALIGNED ? _mm256_load_si256(&m1[i]) : _mm256_loadu_si256(&m1[i]),
               ALIGNED ? _mm256_load_si256(&m2[i]) : _mm256_loadu_si256(&m2[i])));
         return _mm256_testc_si256(v, _mm256_set1_epi64x(0xFFFFFFFFFFFFFFFFULL));
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512BW)
      /// <summary>
      /// Returns true if m1 and m2 have n512 identical 512-Bit chunks.
      /// Requires AVX512.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static bool equal512(const __m512i* m1, const __m512i* m2, const size_t n512)
      {
         for (size_t i = 0; i < n512; i++)
            if (!CppCore::equal512(
               ALIGNED ? _mm512_load_si512(&m1[i]) : _mm512_loadu_si512(&m1[i]),
               ALIGNED ? _mm512_load_si512(&m2[i]) : _mm512_loadu_si512(&m2[i])))
               return false;
         return true;
      }
#endif

      /// <summary>
      /// Compares any sized memory with any alignment.
      /// Consider using optimized equalXY() or streamequalXY() for special cases instead.
      /// </summary>
      INLINE static bool equal(const void* mem1, const void* mem2, const size_t len)
      {
         char* m1 = (char*)mem1;
         char* m2 = (char*)mem2;
         const char* end = m1 + len;
      #if false && defined(CPPCORE_CPUFEAT_AVX512BW)
         while (m1 + 64U <= end)
         {
            if (!equal512<false>((__m512i*)m1, (__m512i*)m2, 1))
               return false;
            m1 += 64U; m2 += 64U;
         }
      #endif
      #if false && defined(CPPCORE_CPUFEAT_AVX)
         while (m1 + 32U <= end)
         {
            if (!equal256<false>((__m256i*)m1, (__m256i*)m2, 1))
               return false;
            m1 += 32U; m2 += 32U;
         }
      #endif
      #if defined(CPPCORE_CPUFEAT_SSE2)
         while (m1 + 16U <= end)
         {
            if (!equal128<false>((__m128i*)m1, (__m128i*)m2, 1))
               return false;
            m1 += 16U; m2 += 16U;
         }
      #endif
      #if defined(CPPCORE_CPU_64BIT)
      #if defined(CPPCORE_CPUFEAT_SSE2)
         if (m1 + 8U <= end)
      #else
         while (m1 + 8U <= end)
      #endif
         {
            if (!equal64((uint64_t*)m1, (uint64_t*)m2, 1))
               return false;
            m1 += 8U; m2 += 8U;
         }
         if (m1 + 4U <= end)
      #else
         while (m1 + 4U <= end)
      #endif
         {
            if (!equal32((uint32_t*)m1, (uint32_t*)m2, 1))
               return false;
            m1 += 4U; m2 += 4U;
         }
         if (m1 + 2U <= end)
         {
            if (!equal16((uint16_t*)m1, (uint16_t*)m2, 1))
               return false;
            m1 += 2U; m2 += 2U;
         }
         if (m1 < end)
         {
            if (!equal8((uint8_t*)m1, (uint8_t*)m2, 1))
               return false;
         }
         return true;
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STREAMEQUAL
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Returns true if m1 and m2 have n128 identical 128-Bit chunks.
      /// Requires SSE2 (SSE41 to be different from aligned equal128) and memory aligned to 16 bytes.
      /// </summary>
      INLINE static bool streamequal128(const __m128i* m1, const __m128i* m2, const size_t n128)
      {
         CPPCORE_ASSERT_MULTIPLE16(m1);
         CPPCORE_ASSERT_MULTIPLE16(m2);
         for (size_t i = 0; i < n128; i++)
            if (!CppCore::equal128(Memory::streamload128(&m1[i]), Memory::streamload128(&m2[i])))
               return false;
         return true;
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
      /// <summary>
      /// Returns true if m1 and m2 have n256 identical 256-Bit chunks. 
      /// Requires AVX (AVX2 to be different from aligned equal256) and memory aligned to 32 bytes.
      /// </summary>
      INLINE static bool streamequal256(const __m256i* m1, const __m256i* m2, const size_t n256)
      {
         CPPCORE_ASSERT_MULTIPLE32(m1);
         CPPCORE_ASSERT_MULTIPLE32(m2);
         for (size_t i = 0; i < n256; i++)
            if (!CppCore::equal256(Memory::streamload256(&m1[i]), Memory::streamload256(&m2[i])))
               return false;
         return true;
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512BW)
      /// <summary>
      /// Returns true if m1 and m2 have n512 identical 512-Bit chunks. 
      /// Requires AVX512 and memory aligned to 64 bytes.
      /// </summary>
      INLINE static bool streamequal512(const __m512i* m1, const __m512i* m2, const size_t n512)
      {
         CPPCORE_ASSERT_MULTIPLE64(m1);
         CPPCORE_ASSERT_MULTIPLE64(m2);
         for (size_t i = 0; i < n512; i++)
            if (!CppCore::equal512(Memory::streamload512(&m1[i]), Memory::streamload512(&m2[i])))
               return false;
         return true;
      }
#endif

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TESTZERO
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns true if m has n8 zero 8-Bit chunks.
      /// </summary>
      INLINE static bool testzero8(const uint8_t* m, const size_t n8)
      {
         for (size_t i = 0; i < n8; i++)
            if (m[i] != 0U)
               return false;
         return true;
      }

      /// <summary>
      /// Returns true if m has n16 zero 16-Bit chunks.
      /// </summary>
      INLINE static bool testzero16(const uint16_t* m, const size_t n16)
      {
         for (size_t i = 0; i < n16; i++)
            if (m[i] != 0U)
               return false;
         return true;
      }

      /// <summary>
      /// Returns true if m has n32 zero 32-Bit chunks.
      /// </summary>
      INLINE static bool testzero32(const uint32_t* m, const size_t n32)
      {
         for (size_t i = 0; i < n32; i++)
            if (m[i] != 0U)
               return false;
         return true;
      }

      /// <summary>
      /// Returns true if m has n64 zero 64-Bit chunks.
      /// </summary>
      INLINE static bool testzero64(const uint64_t* m, const size_t n64)
      {
         for (size_t i = 0; i < n64; i++)
            if (m[i] != 0ULL)
               return false;
         return true;
      }

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Returns true if m has n128 zero 128-Bit chunks.
      /// Requires SSE2. Uses SSE41 if enabled.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static bool testzero128(const __m128i* m, const size_t n128)
      {
      #if defined(CPPCORE_CPUFEAT_SSE41)
         for (size_t i = 0; i < n128; i++)
         {
            const __m128i& v = ALIGNED ? 
               _mm_load_si128 (&m[i]) : 
               _mm_loadu_si128(&m[i]);
            if (!_mm_testz_si128(v, v))
               return false;
         }
      #else
         const __m128i ZERO(_mm_setzero_si128());
         for (size_t i = 0; i < n128; i++)
         {
            const __m128i& v = ALIGNED ? 
               _mm_load_si128 (&m[i]) : 
               _mm_loadu_si128(&m[i]);
            if (0xFFFF != _mm_movemask_epi8(_mm_cmpeq_epi8(v, ZERO)))
               return false;
         }
      #endif
         return true;
      }

      /// <summary>
      /// Returns true if m has n128 zero 128-Bit chunks.
      /// Requires SSE2. Uses SSE41 if enabled. 
      /// OR all values and perform single test only.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static bool testzero128o(const __m128i* m, const size_t n128)
      {
      #if defined(CPPCORE_CPUFEAT_SSE41)
         __m128i v = ALIGNED ?
            _mm_load_si128 (&m[0]) : 
            _mm_loadu_si128(&m[0]);
         for (size_t i = 1; i < n128; i++)
            v = _mm_or_si128(v, ALIGNED ? 
               _mm_load_si128 (&m[i]) : 
               _mm_loadu_si128(&m[i]));
         if (!_mm_testz_si128(v, v))
            return false;
         return true;
      #else
         return Memory::testzero128<ALIGNED>(m, n128);
      #endif
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Returns true if m has n256 zero 256-Bit chunks.
      /// Requires AVX.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static bool testzero256(const __m256i* m, const size_t n256)
      {
         for (size_t i = 0; i < n256; i++)
         {
            const __m256i& v = ALIGNED ? 
               _mm256_load_si256 (&m[i]) : 
               _mm256_loadu_si256(&m[i]);
            if (!_mm256_testz_si256(v, v))
               return false;
         }
         return true;
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
      /// <summary>
      /// Returns true if m has n256 zero 256-Bit chunks.
      /// Requires AVX2. OR all values and perform single test only.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static bool testzero256o(const __m256i* m, const size_t n256)
      {
         __m256i v = ALIGNED ? 
            _mm256_load_si256 (&m[0]) : 
            _mm256_loadu_si256(&m[0]);
         for (size_t i = 1; i < n256; i++)
            v = _mm256_or_si256(v, ALIGNED ? 
               _mm256_load_si256 (&m[i]) : 
               _mm256_loadu_si256(&m[i]));
         if (!_mm256_testz_si256(v, v))
            return false;
         return true;
      }
#elif defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Returns true if m has n256 zero 256-Bit chunks.
      /// Fallback version to testzero256() if AVX2 is not available.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static bool testzero256o(const __m256i* m, const size_t n256)
      {
         return testzero256<ALIGNED>(m, n256);
      }
#endif

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // COPY
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Copies memory that's multiple of 8-bit using 8-bit chunks.
      /// </summary>
      INLINE static void copy8(uint8_t* dst, const uint8_t* src, const size_t n8)
      {
         for (size_t i = 0; i < n8; i++)
            dst[i] = src[i];
      }

      /// <summary>
      /// Copies memory that's multiple of 16-bit using 16-bit chunks.
      /// </summary>
      INLINE static void copy16(uint16_t* dst, const uint16_t* src, const size_t n16)
      {
         for (size_t i = 0; i < n16; i++)
            dst[i] = src[i];
      }

      /// <summary>
      /// Copies memory that's multiple of 32-bit using 32-bit chunks.
      /// </summary>
      INLINE static void copy32(uint32_t* dst, const uint32_t* src, const size_t n32)
      {
         for (size_t i = 0; i < n32; i++)
            dst[i] = src[i];
      }

      /// <summary>
      /// Copies memory that's multiple of 64-bit using 64-bit chunks.
      /// </summary>
      INLINE static void copy64(uint64_t* dst, const uint64_t* src, const size_t n64)
      {
         for (size_t i = 0; i < n64; i++)
            dst[i] = src[i];
      }

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Copies memory that's multiple of 128-bit using 128-bit chunks.
      /// Requires SSE2.
      /// </summary>
      template<bool ALIGNED=false>
      INLINE static void copy128(__m128i* dst, const __m128i* src, const size_t n128)
      {
         for (size_t i = 0; i < n128; i++)
            if (ALIGNED) _mm_store_si128 (&dst[i], _mm_load_si128 (&src[i]));
            else         _mm_storeu_si128(&dst[i], _mm_loadu_si128(&src[i]));
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Copies memory that's multiple of 256-bit using 256-bit chunks.
      /// Requires AVX.
      /// </summary>
      template<bool ALIGNED=false>
      INLINE static void copy256(__m256i* dst, const __m256i* src, const size_t n256)
      {
         for (size_t i = 0; i < n256; i++)
            if (ALIGNED) _mm256_store_si256 (&dst[i], _mm256_load_si256 (&src[i]));
            else         _mm256_storeu_si256(&dst[i], _mm256_loadu_si256(&src[i]));
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
      /// <summary>
      /// Copies memory that's multiple of 512-bit using 512-bit chunks.
      /// Requires AVX512.
      /// </summary>
      template<bool ALIGNED=false>
      INLINE static void copy512(__m512i* dst, const __m512i* src, const size_t n512)
      {
         for (size_t i = 0; i < n512; i++)
            if (ALIGNED) _mm512_store_si512 (&dst[i], _mm512_load_si512 (&src[i]));
            else         _mm512_storeu_si512(&dst[i], _mm512_loadu_si512(&src[i]));
      }
#endif

      /// <summary>
      /// Copies any sized memory with any alignment.
      /// Consider using optimized copyXY() or streamcopyXY() for special cases instead.
      /// </summary>
      INLINE static void copy(void* dstmem, const void* srcmem, size_t len)
      {
         char* memd = (char*)dstmem;
         char* mems = (char*)srcmem;
      #if defined(CPPCORE_CPUFEAT_AVX512F)
         CPPCORE_MEMORY_PROCESS_512(len,
            _mm512_storeu_si512((__m512i*)memd, _mm512_loadu_si512((__m512i*)mems)); memd += 64U; mems += 64U;,
            _mm256_storeu_si256((__m256i*)memd, _mm256_loadu_si256((__m256i*)mems)); memd += 32U; mems += 32U;, 
            _mm_storeu_si128((__m128i*)memd, _mm_loadu_si128((__m128i*)mems)); memd += 16U; mems += 16U;, 
            *((uint64_t*)memd) = *((uint64_t*)mems); memd += 8U; mems += 8U;, 
            *((uint32_t*)memd) = *((uint32_t*)mems); memd += 4U; mems += 4U;, 
            *((uint16_t*)memd) = *((uint16_t*)mems); memd += 2U; mems += 2U;, 
            *((uint8_t*) memd) = *((uint8_t*) mems); memd += 1U; mems += 1U;);
      #elif defined(CPPCORE_CPUFEAT_AVX)
         CPPCORE_MEMORY_PROCESS_256(len, 
            _mm256_storeu_si256((__m256i*)memd, _mm256_loadu_si256((__m256i*)mems)); memd += 32U; mems += 32U; , 
            _mm_storeu_si128((__m128i*)memd, _mm_loadu_si128((__m128i*)mems)); memd += 16U; mems += 16U;, 
            *((uint64_t*)memd) = *((uint64_t*)mems); memd += 8U; mems += 8U;, 
            *((uint32_t*)memd) = *((uint32_t*)mems); memd += 4U; mems += 4U;, 
            *((uint16_t*)memd) = *((uint16_t*)mems); memd += 2U; mems += 2U;, 
            *((uint8_t*) memd) = *((uint8_t*) mems); memd += 1U; mems += 1U;);
      #elif defined(CPPCORE_CPUFEAT_SSE2)
         CPPCORE_MEMORY_PROCESS_128(len, 
            _mm_storeu_si128((__m128i*)memd, _mm_loadu_si128((__m128i*)mems)); memd += 16U; mems += 16U;, 
            *((uint64_t*)memd) = *((uint64_t*)mems); memd += 8U; mems += 8U;, 
            *((uint32_t*)memd) = *((uint32_t*)mems); memd += 4U; mems += 4U;, 
            *((uint16_t*)memd) = *((uint16_t*)mems); memd += 2U; mems += 2U;, 
            *((uint8_t*) memd) = *((uint8_t*) mems); memd += 1U; mems += 1U;);
      #else
         CPPCORE_MEMORY_PROCESS_64(len, 
            *((uint64_t*)memd) = *((uint64_t*)mems); memd += 8U; mems += 8U;, 
            *((uint32_t*)memd) = *((uint32_t*)mems); memd += 4U; mems += 4U;, 
            *((uint16_t*)memd) = *((uint16_t*)mems); memd += 2U; mems += 2U;, 
            *((uint8_t*) memd) = *((uint8_t*) mems); memd += 1U; mems += 1U;);
      #endif
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STREAMLOAD
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Stream-Loads a single 128-bit value if SSE41 is enabled else uses normal SSE2 aligned load.
      /// Requires at least SSE2 and memory aligned to 16 bytes. 
      /// </summary>
      INLINE static __m128i streamload128(const __m128i* mem)
      {
      #if defined(CPPCORE_CPUFEAT_SSE41)
         return _mm_stream_load_si128(mem);
      #else
         return _mm_load_si128(mem);
      #endif
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Stream-Loads a single 256-bit value if AVX2 is enabled else uses normal AVX aligned load.
      /// Requires at least AVX and memory aligned to 32 bytes. 
      /// </summary>
      INLINE static __m256i streamload256(const __m256i* mem)
      {
      #if defined(CPPCORE_CPUFEAT_AVX2)
         return _mm256_stream_load_si256(mem);
      #else
         return _mm256_load_si256(mem);
      #endif
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
      /// <summary>
      /// Stream-Loads a single 512-bit value.
      /// Requires AVX512 and memory aligned to 64 bytes. 
      /// </summary>
      INLINE static __m512i streamload512(const __m512i* mem)
      {
         return _mm512_stream_load_si512(mem);
      }
#endif

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STREAMCOPY
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Stream-Copies memory that's multiple of 128-bit using 128-bit chunks.
      /// Requires SSE2 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamcopy128(__m128i* dst, const __m128i* src, const size_t n128)
      {
         CPPCORE_ASSERT_MULTIPLE16(dst);
         CPPCORE_ASSERT_MULTIPLE16(src);
         for (size_t i = 0; i < n128; i++)
            _mm_stream_si128(&dst[i], Memory::streamload128(&src[i]));
      }

      /// <summary>
      /// Stream-Copies memory that's multiple of 128-bit using 128-bit chunks.
      /// Requires SSE2 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamcopy128x1(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE16(dst);
         CPPCORE_ASSERT_MULTIPLE16(src);
         //CPPCORE_ASSERT_MULTIPLE16(len);
         __m128i* d = (__m128i*)dst;
         __m128i* s = (__m128i*)src;
         __m128i* e = (__m128i*)((char*)dst + len);
         while (d < e)
         {
            _mm_stream_si128(d, Memory::streamload128(s)); d++; s++;
         }
      }

      /// <summary>
      /// Stream-Copies memory that's multiple of 256-bit using 128-bit chunks.
      /// Requires SSE2 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamcopy128x2(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE16(dst);
         CPPCORE_ASSERT_MULTIPLE16(src);
         //CPPCORE_ASSERT_MULTIPLE32(len);
         __m128i* d = (__m128i*)dst;
         __m128i* s = (__m128i*)src;
         __m128i* e = (__m128i*)((char*)dst + len);
         while (d < e)
         {
            _mm_stream_si128(d, Memory::streamload128(s)); d++; s++;
            _mm_stream_si128(d, Memory::streamload128(s)); d++; s++;
         }
      }

      /// <summary>
      /// Stream-Copies memory that's multiple of 512-bit using 128-bit chunks.
      /// Requires SSE2 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamcopy128x4(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE16(dst);
         CPPCORE_ASSERT_MULTIPLE16(src);
         //CPPCORE_ASSERT_MULTIPLE64(len);
         __m128i* d = (__m128i*)dst;
         __m128i* s = (__m128i*)src;
         __m128i* e = (__m128i*)((char*)dst + len);
         while (d < e)
         {
            _mm_stream_si128(d, Memory::streamload128(s)); d++; s++;
            _mm_stream_si128(d, Memory::streamload128(s)); d++; s++;
            _mm_stream_si128(d, Memory::streamload128(s)); d++; s++;
            _mm_stream_si128(d, Memory::streamload128(s)); d++; s++;
         }
      }
#else
       /// <summary>
      /// Fallback Version using Memory::copy() if no 128-Bit operations are available.
      /// </summary>
      INLINE static void streamcopy128x1(void* dst, const void* src, const size_t len)
      {
         Memory::copy(dst, src, len);
      }

      /// <summary>
      /// Fallback Version using Memory::copy() if no 128-Bit operations are available.
      /// </summary>
      INLINE static void streamcopy128x2(void* dst, const void* src, const size_t len)
      {
         Memory::copy(dst, src, len);
      }

      /// <summary>
      /// Fallback Version using Memory::copy() if no 128-Bit operations are available.
      /// </summary>
      INLINE static void streamcopy128x4(void* dst, const void* src, const size_t len)
      {
         Memory::copy(dst, src, len);
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Stream-Copies memory that's multiple of 256-bit using 256-bit chunks.
      /// Requires AVX and memory aligned to 32 bytes. Improves if AVX2 is also enabled.
      /// </summary>
      INLINE static void streamcopy256(__m256i* dst, const __m256i* src, const size_t n256)
      {
         CPPCORE_ASSERT_MULTIPLE32(dst);
         CPPCORE_ASSERT_MULTIPLE32(src);
         for (size_t i = 0; i < n256; i++)
            _mm256_stream_si256(&dst[i], Memory::streamload256(&src[i]));
      }

      /// <summary>
      /// Stream-Copies memory that's multiple of 256-bit using 256-bit chunks.
      /// Requires AVX and memory aligned to 32 bytes. Improves if AVX2 is also enabled.
      /// </summary>
      INLINE static void streamcopy256x1(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE32(dst);
         CPPCORE_ASSERT_MULTIPLE32(src);
         //CPPCORE_ASSERT_MULTIPLE32(len);
         __m256i* d = (__m256i*)dst;
         __m256i* s = (__m256i*)src;
         __m256i* e = (__m256i*)((char*)dst + len);
         while (d < e)
         {
            _mm256_stream_si256(d, Memory::streamload256(s)); d++; s++;
         }
      }

      /// <summary>
      /// Stream-Copies memory that's multiple of 512-bit using 256-bit chunks.
      /// Requires AVX and memory aligned to 32 bytes. Improves if AVX2 is also enabled.
      /// </summary>
      INLINE static void streamcopy256x2(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE32(dst);
         CPPCORE_ASSERT_MULTIPLE32(src);
         //CPPCORE_ASSERT_MULTIPLE64(len);
         __m256i* d = (__m256i*)dst;
         __m256i* s = (__m256i*)src;
         __m256i* e = (__m256i*)((char*)dst + len);
         while (d < e)
         {
            _mm256_stream_si256(d, Memory::streamload256(s)); d++; s++;
            _mm256_stream_si256(d, Memory::streamload256(s)); d++; s++;
         }
      }

      /// <summary>
      /// Stream-Copies memory that's multiple of 1024-bit using 256-bit chunks.
      /// Requires AVX and memory aligned to 32 bytes. Improves if AVX2 is also enabled.
      /// </summary>
      INLINE static void streamcopy256x4(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE32(dst);
         CPPCORE_ASSERT_MULTIPLE32(src);
         //CPPCORE_ASSERT_MULTIPLE128(len);
         __m256i* d = (__m256i*)dst;
         __m256i* s = (__m256i*)src;
         __m256i* e = (__m256i*)((char*)dst + len);
         while (d < e)
         {
            _mm256_stream_si256(d, Memory::streamload256(s)); d++; s++;
            _mm256_stream_si256(d, Memory::streamload256(s)); d++; s++;
            _mm256_stream_si256(d, Memory::streamload256(s)); d++; s++;
            _mm256_stream_si256(d, Memory::streamload256(s)); d++; s++;
         }
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
      /// <summary>
      /// Stream-Copies memory that's multiple of 512-bit using 512-bit chunks.
      /// Requires AVX512 and memory aligned to 64 bytes.
      /// </summary>
      INLINE static void streamcopy512(__m512i* dst, const __m512i* src, const size_t n512)
      {
         CPPCORE_ASSERT_MULTIPLE64(dst);
         CPPCORE_ASSERT_MULTIPLE64(src);
         for (size_t i = 0; i < n512; i++)
            _mm512_stream_si512(&dst[i], Memory::streamload512(&src[i]));
      }

      /// <summary>
      /// Stream-Copies memory that's multiple of 512-bit using 512-bit chunks.
      /// Requires AVX512 and memory aligned to 64 bytes.
      /// </summary>
      INLINE static void streamcopy512x1(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE64(dst);
         CPPCORE_ASSERT_MULTIPLE64(src);
         //CPPCORE_ASSERT_MULTIPLE64(len);
         __m512i* d = (__m512i*)dst;
         __m512i* s = (__m512i*)src;
         __m512i* e = (__m512i*)((char*)dst + len);
         while (d < e)
         {
            _mm512_stream_si512(d, Memory::streamload512(s)); d++; s++;
         }
      }

      /// <summary>
      /// Stream-Copies memory that's multiple of 1024-bit using 512-bit chunks.
      /// Requires AVX512 and memory aligned to 64 bytes.
      /// </summary>
      INLINE static void streamcopy512x2(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE64(dst);
         CPPCORE_ASSERT_MULTIPLE64(src);
         //CPPCORE_ASSERT_MULTIPLE128(len);
         __m512i* d = (__m512i*)dst;
         __m512i* s = (__m512i*)src;
         __m512i* e = (__m512i*)((char*)dst + len);
         while (d < e)
         {
            _mm512_stream_si512(d, Memory::streamload512(s)); d++; s++;
            _mm512_stream_si512(d, Memory::streamload512(s)); d++; s++;
         }
      }

      /// <summary>
      /// Stream-Copies memory that's multiple of 2048-bit using 512-bit chunks.
      /// Requires AVX512 and memory aligned to 64 bytes.
      /// </summary>
      INLINE static void streamcopy512x4(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE64(dst);
         CPPCORE_ASSERT_MULTIPLE64(src);
         //CPPCORE_ASSERT_MULTIPLE256(len);
         __m512i* d = (__m512i*)dst;
         __m512i* s = (__m512i*)src;
         __m512i* e = (__m512i*)((char*)dst + len);
         while (d < e)
         {
            _mm512_stream_si512(d, Memory::streamload512(s)); d++; s++;
            _mm512_stream_si512(d, Memory::streamload512(s)); d++; s++;
            _mm512_stream_si512(d, Memory::streamload512(s)); d++; s++;
            _mm512_stream_si512(d, Memory::streamload512(s)); d++; s++;
         }
      }
#endif

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // COPY REVERSE
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Copies (in reverse byte order) memory that's multiple of 8-bit using 8-bit chunks.
      /// </summary>
      INLINE static void copyreverse8(uint8_t* dst, const uint8_t* src, const size_t n8)
      {
         const size_t LST = n8-1U;
         for (size_t i = 0; i < n8; i++)
            dst[i] = src[LST-i];
      }

      /// <summary>
      /// Copies (in reverse byte order) memory that's multiple of 16-bit using 16-bit chunks.
      /// </summary>
      INLINE static void copyreverse16(uint16_t* dst, const uint16_t* src, const size_t n16)
      {
         const size_t LST = n16-1U;
         for (size_t i = 0; i < n16; i++)
            dst[i] = CppCore::loadr16(&src[LST-i]);
      }

      /// <summary>
      /// Copies (in reverse byte order) memory that's multiple of 32-bit using 32-bit chunks.
      /// </summary>
      INLINE static void copyreverse32(uint32_t* dst, const uint32_t* src, const size_t n32)
      {
         const size_t LST = n32-1U;
         for (size_t i = 0; i < n32; i++)
            dst[i] = CppCore::loadr32(&src[LST-i]);
      }

      /// <summary>
      /// Copies (in reverse byte order) memory that's multiple of 64-bit using 64-bit chunks.
      /// </summary>
      INLINE static void copyreverse64(uint64_t* dst, const uint64_t* src, const size_t n64)
      {
         const size_t LST = n64-1U;
         for (size_t i = 0; i < n64; i++)
            dst[i] = CppCore::loadr64(&src[LST-i]);
      }

      /// <summary>
      /// Copies (in reverse byte order) memory that's multiple of 128-bit using 128-bit chunks.
      /// Requires SSSE3.
      /// </summary>
#if defined(CPPCORE_CPUFEAT_SSSE3)
      template<bool ALIGNED = false>
      INLINE static void copyreverse128(__m128i* dst, const __m128i* src, const size_t n128)
      {
         const size_t  LST = n128-1U;
         const __m128i MASK(_mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
         if (ALIGNED)
            for (size_t i = 0; i < n128; i++)
               _mm_store_si128(&dst[i], _mm_shuffle_epi8(_mm_load_si128(&src[LST-i]), MASK));
         else
            for (size_t i = 0; i < n128; i++)
               _mm_storeu_si128(&dst[i], _mm_shuffle_epi8(_mm_loadu_si128(&src[LST-i]), MASK));
      }
#endif

      /// <summary>
      /// Copies (in reverse byte order) any sized memory with any alignment.
      /// Consider using optimized copyreverseXY() or streamcopyreverseXY() for special cases instead.
      /// </summary>
      INLINE static void copyreverse(void* dstmem, const void* srcmem, const size_t len)
      {
         char* dst = (char*)dstmem;
         char* src = (char*)srcmem + len;
         const char* end = dst + len;
      #if defined(CPPCORE_CPUFEAT_SSSE3)
         const __m128i MASK(_mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
         while (dst + 16U <= end)
         {
            src -= 16U;
            _mm_storeu_si128((__m128i*)dst, _mm_shuffle_epi8(_mm_loadu_si128((__m128i*)src), MASK));
            dst += 16U;
         }
      #endif
      #if defined(CPPCORE_CPU_64BIT)
      #if defined(CPPCORE_CPUFEAT_SSSE3)
         if (dst + 8U <= end)
      #else
         while (dst + 8U <= end)
      #endif
         {
            src -= 8U;
            *((uint64_t*)dst) = CppCore::loadr64((uint64_t*)src);
            dst += 8U;
         }
         if (dst + 4U <= end)
      #else
         while (dst + 4U <= end)
      #endif
         {
            src -= 4U;
            *((uint32_t*)dst) = CppCore::loadr32((uint32_t*)src);
            dst += 4U;
         }
         if (dst + 2U <= end)
         {
            src -= 2U;
            *((uint16_t*)dst) = CppCore::loadr16((uint16_t*)src);
            dst += 2U;
         }
         if (dst < end)
         {
            src--;
            *dst = *src;
         }
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STREAMCOPY REVERSE
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSSE3)
      /// <summary>
      /// Stream-Copies (in reverse byte order) memory that's multiple of 128-bit using 128-bit chunks.
      /// Requires SSSE3 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamcopyreverse128(__m128i* dst, const __m128i* src, const size_t n128)
      {
         CPPCORE_ASSERT_MULTIPLE16(dst);
         CPPCORE_ASSERT_MULTIPLE16(src);
         const size_t  LST = n128-1U;
         const __m128i MASK(_mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
         for (size_t i = 0; i < n128; i++)
            _mm_stream_si128(&dst[i], _mm_shuffle_epi8(Memory::streamload128(&src[LST-i]), MASK));
      }

      /// <summary>
      /// Stream-Copies (in reverse byte order) memory that's multiple of 128-bit using 128-bit chunks.
      /// Requires SSSE3 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamcopyreverse128x1(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE16(dst);
         CPPCORE_ASSERT_MULTIPLE16(src);
         //CPPCORE_ASSERT_MULTIPLE16(len);
         const __m128i MASK(_mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
         __m128i* d = (__m128i*)dst;
         __m128i* s = (__m128i*)((char*)src + len) - 1U;
         __m128i* e = (__m128i*)((char*)dst + len);
         while (d < e)
         {
            _mm_stream_si128(d, _mm_shuffle_epi8(Memory::streamload128(s), MASK)); d++; s--;
         }
      }

      /// <summary>
      /// Stream-Copies (in reverse byte order) memory that's multiple of 256-bit using 128-bit chunks.
      /// Requires SSSE3 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamcopyreverse128x2(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE16(dst);
         CPPCORE_ASSERT_MULTIPLE16(src);
         //CPPCORE_ASSERT_MULTIPLE32(len);
         const __m128i MASK(_mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
         __m128i* d = (__m128i*)dst;
         __m128i* s = (__m128i*)((char*)src + len) - 1U;
         __m128i* e = (__m128i*)((char*)dst + len);
         while (d < e)
         {
            _mm_stream_si128(d, _mm_shuffle_epi8(Memory::streamload128(s), MASK)); d++; s--;
            _mm_stream_si128(d, _mm_shuffle_epi8(Memory::streamload128(s), MASK)); d++; s--;
         }
      }

      /// <summary>
      /// Stream-Copies (in reverse byte order) memory that's multiple of 512-bit using 128-bit chunks.
      /// Requires SSSE3 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamcopyreverse128x4(void* dst, const void* src, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE16(dst);
         CPPCORE_ASSERT_MULTIPLE16(src);
         //CPPCORE_ASSERT_MULTIPLE64(len);
         const __m128i MASK(_mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
         __m128i* d = (__m128i*)dst;
         __m128i* s = (__m128i*)((char*)src + len) - 1U;
         __m128i* e = (__m128i*)((char*)dst + len);
         while (d < e)
         {
            _mm_stream_si128(d, _mm_shuffle_epi8(Memory::streamload128(s), MASK)); d++; s--;
            _mm_stream_si128(d, _mm_shuffle_epi8(Memory::streamload128(s), MASK)); d++; s--;
            _mm_stream_si128(d, _mm_shuffle_epi8(Memory::streamload128(s), MASK)); d++; s--;
            _mm_stream_si128(d, _mm_shuffle_epi8(Memory::streamload128(s), MASK)); d++; s--;
         }
      }
#endif

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SWAP
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Swaps memory that's multiple of 8-bit using 8-bit chunks.
      /// </summary>
      INLINE static void swap8(uint8_t* mem1, uint8_t* mem2, const size_t n8)
      {
         uint8_t t;
         for (size_t i = 0; i < n8; i++)
         {
            t = mem1[i];
            mem1[i] = mem2[i];
            mem2[i] = t;
         }
      }

      /// <summary>
      /// Swaps memory that's multiple of 16-bit using 16-bit chunks.
      /// </summary>
      INLINE static void swap16(uint16_t* mem1, uint16_t* mem2, const size_t n16)
      {
         uint16_t t;
         for (size_t i = 0; i < n16; i++)
         {
            t = mem1[i];
            mem1[i] = mem2[i];
            mem2[i] = t;
         }
      }

      /// <summary>
      /// Swaps memory that's multiple of 32-bit using 32-bit chunks.
      /// </summary>
      INLINE static void swap32(uint32_t* mem1, uint32_t* mem2, const size_t n32)
      {
         uint32_t t;
         for (size_t i = 0; i < n32; i++)
         {
            t = mem1[i];
            mem1[i] = mem2[i];
            mem2[i] = t;
         }
      }

      /// <summary>
      /// Swaps memory that's multiple of 64-bit using 64-bit chunks.
      /// </summary>
      INLINE static void swap64(uint64_t* mem1, uint64_t* mem2, const size_t n64)
      {
         uint64_t t;
         for (size_t i = 0; i < n64; i++)
         {
            t = mem1[i];
            mem1[i] = mem2[i];
            mem2[i] = t;
         }
      }

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Swaps memory that's multiple of 128-bit using 128-bit chunks. Requires SSE2.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static void swap128(__m128i* mem1, __m128i* mem2, const size_t n128)
      {
         __m128i t;
         if (ALIGNED)
         {
            for (size_t i = 0; i < n128; i++)
            {
               t = _mm_load_si128(&mem1[i]);
               _mm_store_si128(&mem1[i], _mm_load_si128(&mem2[i]));
               _mm_store_si128(&mem2[i], t);
            }
         }
         else
         {
            for (size_t i = 0; i < n128; i++)
            {
               t = _mm_loadu_si128(&mem1[i]);
               _mm_storeu_si128(&mem1[i], _mm_loadu_si128(&mem2[i]));
               _mm_storeu_si128(&mem2[i], t);
            }
         }
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Swaps memory that's multiple of 256-bit using 256-bit chunks. Requires AVX.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static void swap256(__m256i* mem1, __m256i* mem2, const size_t n256)
      {
         __m256i t;
         if (ALIGNED)
         {
            for (size_t i = 0; i < n256; i++)
            {
               t = _mm256_load_si256(&mem1[i]);
               _mm256_store_si256(&mem1[i], _mm256_load_si256(&mem2[i]));
               _mm256_store_si256(&mem2[i], t);
            }
         }
         else
         {
            for (size_t i = 0; i < n256; i++)
            {
               t = _mm256_loadu_si256(&mem1[i]);
               _mm256_storeu_si256(&mem1[i], _mm256_loadu_si256(&mem2[i]));
               _mm256_storeu_si256(&mem2[i], t);
            }
         }
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
      /// <summary>
      /// Swaps memory that's multiple of 512-bit using 512-bit chunks. Requires AVX512.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static void swap512(__m512i* mem1, __m512i* mem2, const size_t n512)
      {
         __m512i t;
         if (ALIGNED)
         {
            for (size_t i = 0; i < n512; i++)
            {
               t = _mm512_load_si512(&mem1[i]);
               _mm512_store_si512(&mem1[i], _mm512_load_si512(&mem2[i]));
               _mm512_store_si512(&mem2[i], t);
            }
         }
         else
         {
            for (size_t i = 0; i < n512; i++)
            {
               t = _mm512_loadu_si512(&mem1[i]);
               _mm512_storeu_si512(&mem1[i], _mm512_loadu_si512(&mem2[i]));
               _mm512_storeu_si512(&mem2[i], t);
            }
         }
      }
#endif

      /// <summary>
      /// Swaps any sized memory with any alignment.
      /// Consider using optimized swapXY() or streamswapXY() for special cases instead.
      /// </summary>
      INLINE static void swap(void* mem1, const void* mem2, const size_t len)
      {
         char* dst = (char*)mem1;
         char* src = (char*)mem2;
         const char* end = dst + len;
      #if false && defined(CPPCORE_CPUFEAT_AVX512F)
         while (dst + 64U <= end)
         {
            swap512<false>((__m512i*)dst, (__m512i*)src, 1);
            dst += 64U; src += 64U;
         }
      #endif
      #if false && defined(CPPCORE_CPUFEAT_AVX)
         while (dst + 32U <= end)
         {
            swap256<false>((__m256i*)dst, (__m256i*)src, 1);
            dst += 32U; src += 32U;
         }
      #endif
      #if defined(CPPCORE_CPUFEAT_SSE2)
         while (dst + 16U <= end)
         {
            swap128<false>((__m128i*)dst, (__m128i*)src, 1);
            dst += 16U; src += 16U;
         }
      #endif
      #if defined(CPPCORE_CPU_64BIT)
      #if defined(CPPCORE_CPUFEAT_SSE2)
         if (dst + 8U <= end)
      #else
         while (dst + 8U <= end)
      #endif
         {
            swap64((uint64_t*)dst, (uint64_t*)src, 1);
            dst += 8U; src += 8U;
         }
         if (dst + 4U <= end)
      #else
         while (dst + 4U <= end)
      #endif
         {
            swap32((uint32_t*)dst, (uint32_t*)src, 1);
            dst += 4U; src += 4U;
         }
         if (dst + 2U <= end)
         {
            swap16((uint16_t*)dst, (uint16_t*)src, 1);
            dst += 2U; src += 2U;
         }
         if (dst < end)
            swap8((uint8_t*)dst, (uint8_t*)src, 1);
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STREAM-SWAP
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Stream-Swaps memory that's multiple of 128-bit using 128-bit chunks.
      /// Requires SSE2 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamswap128(__m128i* mem1, __m128i* mem2, const size_t n128)
      {
         CPPCORE_ASSERT_MULTIPLE16(mem1);
         CPPCORE_ASSERT_MULTIPLE16(mem2);
         for (size_t i = 0; i < n128; i++)
         {
            __m128i t = Memory::streamload128(&mem1[i]);
            _mm_stream_si128(&mem1[i], Memory::streamload128(&mem2[i]));
            _mm_stream_si128(&mem2[i], t);
         }
      }

      /// <summary>
      /// Stream-Swaps memory that's multiple of 128-bit using 128-bit chunks.
      /// Requires SSE2 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamswap128x1(void* mem1, void* mem2, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE16(mem1);
         CPPCORE_ASSERT_MULTIPLE16(mem2);
         //CPPCORE_ASSERT_MULTIPLE16(len);
         __m128i* m1 = (__m128i*)mem1;
         __m128i* m2 = (__m128i*)mem2;
         __m128i* e1 = (__m128i*)((char*)mem1 + len);
         while (m1 < e1)
         {
            __m128i t = Memory::streamload128(m1);
            _mm_stream_si128(m1, Memory::streamload128(m2));
            _mm_stream_si128(m2, t);
            m1++;
            m2++;
         }
      }

      /// <summary>
      /// Stream-Swaps memory that's multiple of 256-bit using 128-bit chunks.
      /// Requires SSE2 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamswap128x2(void* mem1, void* mem2, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE16(mem1);
         CPPCORE_ASSERT_MULTIPLE16(mem2);
         //CPPCORE_ASSERT_MULTIPLE32(len);
         __m128i* m1 = (__m128i*)mem1;
         __m128i* m2 = (__m128i*)mem2;
         __m128i* e1 = (__m128i*)((char*)mem1 + len);
         while (m1 < e1)
         {
            __m128i t;
            t = Memory::streamload128(m1);
            _mm_stream_si128(m1, Memory::streamload128(m2));
            _mm_stream_si128(m2, t);
            m1++;
            m2++;
            t = Memory::streamload128(m1);
            _mm_stream_si128(m1, Memory::streamload128(m2));
            _mm_stream_si128(m2, t);
            m1++;
            m2++;
         }
      }

      /// <summary>
      /// Stream-Swaps memory that's multiple of 512-bit using 128-bit chunks.
      /// Requires SSE2 and memory aligned to 16 bytes. Improves if SSE41 is also enabled.
      /// </summary>
      INLINE static void streamswap128x4(void* mem1, void* mem2, const size_t len)
      {
         CPPCORE_ASSERT_MULTIPLE16(mem1);
         CPPCORE_ASSERT_MULTIPLE16(mem2);
         //CPPCORE_ASSERT_MULTIPLE64(len);
         __m128i* m1 = (__m128i*)mem1;
         __m128i* m2 = (__m128i*)mem2;
         __m128i* e1 = (__m128i*)((char*)mem1 + len);
         while (m1 < e1)
         {
            __m128i t;
            t = Memory::streamload128(m1);
            _mm_stream_si128(m1, Memory::streamload128(m2));
            _mm_stream_si128(m2, t);
            m1++;
            m2++;
            t = Memory::streamload128(m1);
            _mm_stream_si128(m1, Memory::streamload128(m2));
            _mm_stream_si128(m2, t);
            m1++;
            m2++;
            t = Memory::streamload128(m1);
            _mm_stream_si128(m1, Memory::streamload128(m2));
            _mm_stream_si128(m2, t);
            m1++;
            m2++;
            t = Memory::streamload128(m1);
            _mm_stream_si128(m1, Memory::streamload128(m2));
            _mm_stream_si128(m2, t);
            m1++;
            m2++;
         }
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
      /// <summary>
      /// Stream-Swaps memory that's multiple of 256-bit using 256-bit chunks.
      /// Requires AVX and memory aligned to 32 bytes. Improves if AVX2 is also enabled.
      /// </summary>
      INLINE static void streamswap256(__m256i* mem1, __m256i* mem2, const size_t n256)
      {
         CPPCORE_ASSERT_MULTIPLE32(mem1);
         CPPCORE_ASSERT_MULTIPLE32(mem2);
         for (size_t i = 0; i < n256; i++)
         {
            __m256i t = Memory::streamload256(&mem1[i]);
            _mm256_stream_si256(&mem1[i], Memory::streamload256(&mem2[i]));
            _mm256_stream_si256(&mem2[i], t);
         }
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512F)
      /// <summary>
      /// Stream-Swaps memory that's multiple of 512-bit using 512-bit chunks.
      /// Requires AVX512 and memory aligned to 64 bytes.
      /// </summary>
      INLINE static void streamswap512(__m512i* mem1, __m512i* mem2, const size_t n512)
      {
         CPPCORE_ASSERT_MULTIPLE64(mem1);
         CPPCORE_ASSERT_MULTIPLE64(mem2);
         for (size_t i = 0; i < n512; i++)
         {
            __m512i t = Memory::streamload512(&mem1[i]);
            _mm512_stream_si512(&mem1[i], Memory::streamload512(&mem2[i]));
            _mm512_stream_si512(&mem2[i], t);
         }
      }
#endif

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // REVERSE
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Reverses byte order of memory that's multiple of 8-bit using 8-bit chunks.
      /// </summary>
      INLINE static void reverse8(uint8_t* mem, const size_t n8)
      {
         const size_t LST = n8-1U;
         const size_t MID = n8>>1;
         for (size_t i = 0; i < MID; i++)
         {
            const uint8_t t = mem[i];
            mem[i] = mem[LST-i];
            mem[LST-i] = t;
         }
      }

      /// <summary>
      /// Reverses byte order of memory that's multiple of 16-bit using 16-bit chunks.
      /// </summary>
      INLINE static void reverse16(uint16_t* mem, const size_t n16)
      {
         if (n16 > 1U)
         {
            const size_t LST = n16-1U;
            const size_t MID = n16>>1;
            for (size_t i = 0; i < MID; i++)
            {
               const uint16_t t = CppCore::loadr16(&mem[i]);
               mem[i] = CppCore::loadr16(&mem[LST-i]);
               mem[LST-i] = t;
            }
         }
         else if (n16 == 1U)
            *mem = CppCore::loadr16(mem);
      }

      /// <summary>
      /// Reverses byte order of memory that's multiple of 32-bit using 32-bit chunks.
      /// </summary>
      INLINE static void reverse32(uint32_t* mem, const size_t n32)
      {
         if (n32 > 1U)
         {
            const size_t LST = n32-1U;
            const size_t MID = n32>>1;
            for (size_t i = 0; i < MID; i++)
            {
               const uint32_t t = CppCore::loadr32(&mem[i]);
               mem[i] = CppCore::loadr32(&mem[LST-i]);
               mem[LST-i] = t;
            }
         }
         else if (n32 == 1U)
            *mem = CppCore::loadr32(mem);
      }

      /// <summary>
      /// Reverses byte order of memory that's multiple of 64-bit using 64-bit chunks.
      /// </summary>
      INLINE static void reverse64(uint64_t* mem, const size_t n64)
      {
         if (n64 > 1U)
         {
            const size_t LST = n64-1U;
            const size_t MID = n64>>1;
            for (size_t i = 0; i < MID; i++)
            {
               const uint64_t t = CppCore::loadr64(&mem[i]);
               mem[i] = CppCore::loadr64(&mem[LST-i]);
               mem[LST-i] = t;
            }
         }
         else if (n64 == 1U)
            *mem = CppCore::loadr64(mem);
      }

#if defined(CPPCORE_CPUFEAT_SSSE3)
      /// <summary>
      /// Reverses byte order of memory that's multiple of 128-bit using 128-bit chunks.
      /// Requires SSSE3.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static void reverse128(__m128i* mem, const size_t n128)
      {
         const __m128i MASK(_mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
         if (n128 > 1U)
         {
            const size_t LST = n128-1U;
            const size_t MID = n128>>1;
            if (ALIGNED)
            {
               for (size_t i = 0; i < MID; i++)
               {
                  const __m128i t = _mm_shuffle_epi8(_mm_load_si128(&mem[i]), MASK);
                  _mm_store_si128(&mem[i], _mm_shuffle_epi8(_mm_load_si128(&mem[LST-i]), MASK));
                  _mm_store_si128(&mem[LST-i], t);
               }
            }
            else
            {
               for (size_t i = 0; i < MID; i++)
               {
                  const __m128i t = _mm_shuffle_epi8(_mm_loadu_si128(&mem[i]), MASK);
                  _mm_storeu_si128(&mem[i], _mm_shuffle_epi8(_mm_loadu_si128(&mem[LST-i]), MASK));
                  _mm_storeu_si128(&mem[LST-i], t);
               }
            }
         }
         else if (n128 == 1U)
         {
            if (ALIGNED) _mm_store_si128(mem, _mm_shuffle_epi8(_mm_load_si128(mem), MASK));
            else         _mm_storeu_si128(mem, _mm_shuffle_epi8(_mm_loadu_si128(mem), MASK));
         }
      }
#endif

      /// <summary>
      /// Reverses byte order of any sized memory with any alignment.
      /// Consider using optimized reverseXY() or streamreverseXY() for special cases instead.
      /// </summary>
      INLINE static void reverse(void* mem, const size_t len)
      {
         char* ptrs = (char*)mem;      // pointer to start
         char* ptre = ptrs + len;      // pointer to end
         char* ptrm = ptrs + (len>>1); // pointer to mid
      #if defined(CPPCORE_CPUFEAT_SSSE3)
         const __m128i MASK(_mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
         while (ptrs + 16U <= ptrm)
         {
            ptre -= 16U;
            const __m128i t = _mm_shuffle_epi8(_mm_loadu_si128((__m128i*)ptrs), MASK);
            _mm_storeu_si128((__m128i*)ptrs, _mm_shuffle_epi8(_mm_loadu_si128((__m128i*)ptre), MASK));
            _mm_storeu_si128((__m128i*)ptre, t);
            ptrs += 16U;
         }
      #endif
      #if defined(CPPCORE_CPU_64BIT)
      #if defined(CPPCORE_CPUFEAT_SSSE3)
         if (ptrs + 8U <= ptrm)
      #else
         while (ptrs + 8U <= ptrm)
      #endif
         {
            ptre -= 8U;
            const uint64_t t = CppCore::loadr64((uint64_t*)ptrs);
            *((uint64_t*)ptrs) = CppCore::loadr64((uint64_t*)ptre);
            *((uint64_t*)ptre) = t;
            ptrs += 8U;
         }
         if (ptrs + 4U <= ptrm)
      #else
         while (ptrs + 4U <= ptrm)
      #endif
         {
            ptre -= 4U;
            const uint32_t t = CppCore::loadr32((uint32_t*)ptrs);
            *((uint32_t*)ptrs) = CppCore::loadr32((uint32_t*)ptre);
            *((uint32_t*)ptre) = t;
            ptrs += 4U;
         }
         if (ptrs + 2U <= ptrm)
         {
            ptre -= 2U;
            const uint16_t t = CppCore::loadr16((uint16_t*)ptrs);
            *((uint16_t*)ptrs) = CppCore::loadr16((uint16_t*)ptre);
            *((uint16_t*)ptre) = t;
            ptrs += 2U;
         }
         if (ptrs + 1U <= ptrm)
         {
            ptre -= 1U;
            const uint8_t t = *ptrs;
            *ptrs = *ptre;
            *ptre = t;
         }
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // BYTE INDEX
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns index of next c char in mem searching in 32-Bit steps.
      /// </summary>
      INLINE static size_t byteidxf32(const char* mem, const char c)
      {
         const uint32_t p = CppCore::bytedup32(c);
         size_t i = 0U;
         while(true)
         {
            const uint32_t v = *((uint32_t*)&mem[i]) ^ p;
            const uint32_t x = (v - 0x01010101U) & ~v & 0x80808080U;
            if (x == 0) i += 4U;
            else return i + (CppCore::tzcnt32(x) >> 3);
         }
      }

      /// <summary>
      /// Returns index of next c char in mem searching up to maxsteps 32-Bit steps.
      /// Returns size_t::max if not found in maxsteps.
      /// </summary>
      INLINE static size_t byteidxf32(const uint32_t* mem, const char c, const size_t n32)
      {
         const uint32_t p = CppCore::bytedup32(c);
         for (size_t i = 0; i < n32; i++)
         {
            const uint32_t v = mem[i] ^ p;
            const uint32_t x = (v - 0x01010101U) & ~v & 0x80808080U;
            if (x != 0)
               return (i << 2) + (CppCore::tzcnt32(x) >> 3);
         }
         return std::numeric_limits<size_t>::max();
      }

      /// <summary>
      /// Returns index of next c char in mem searching in 64-Bit steps.
      /// </summary>
      INLINE static size_t byteidxf64(const char* mem, const char c)
      {
         const uint64_t p = CppCore::bytedup64(c);
         size_t i = 0U;
         while(true)
         {
            const uint64_t v = *((uint64_t*)&mem[i]) ^ p;
            const uint64_t x = (v - 0x0101010101010101ULL) & ~v & 0x8080808080808080ULL;
            if (x == 0) i += 8U;
            else return i + (CppCore::tzcnt64(x) >> 3);
         }
      }

      /// <summary>
      /// Returns index of next c char in mem searching up to maxsteps 64-Bit steps.
      /// Returns size_t::max if not found in maxsteps.
      /// </summary>
      INLINE static size_t byteidxf64(const uint64_t* mem, const char c, const size_t n64)
      {
         const uint64_t p = CppCore::bytedup64(c);
         for (size_t i = 0; i < n64; i++)
         {
            const uint64_t v = mem[i] ^ p;
            const uint64_t x = (v - 0x0101010101010101ULL) & ~v & 0x8080808080808080ULL;
            if (x != 0)
               return (i << 3) + (CppCore::tzcnt64(x) >> 3);
         }
         return std::numeric_limits<size_t>::max();
      }

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Searches mem in steps of 16 bytes for the first occurence of the byte duplicated in v.
      /// For instance, searches for 0xAB if v is 0xABAB..AB.
      /// DOES NOT have any boundary checks, the pattern MUST exist.
      /// </summary>
      template <bool ALIGNED = false>
      INLINE static size_t byteidxf128(const char* mem, const __m128i& v)
      {
         size_t i = 0U;
         while(true)
         {
            const uint32_t c = CppCore::bytemaskequal128(ALIGNED ?
               _mm_load_si128( (__m128i*)&mem[i]) :
               _mm_loadu_si128((__m128i*)&mem[i]), v);
            if (c == 0) i += 16U;
            else return i + CppCore::tzcnt32(c);
         }
      }

      /// <summary>
      /// Searches mem in steps of 16 bytes for the first occurence of the byte duplicated in v.
      /// For instance, searches for 0xAB if v is 0xABAB..AB.
      /// Stops after n128 steps.
      /// </summary>
      template <bool ALIGNED = false>
      INLINE static size_t byteidxf128(const __m128i* mem, const __m128i& v, const size_t n128)
      {
         for (size_t i = 0; i < n128; i++)
         {
            const uint32_t c = CppCore::bytemaskequal128(ALIGNED ?
               _mm_load_si128( &mem[i]) :
               _mm_loadu_si128(&mem[i]), v);
            if (c != 0)
               return (i << 4) + CppCore::tzcnt32(c);
         }
         return std::numeric_limits<size_t>::max();
      }

      /// <summary>
      /// Returns index of next c char in mem searching in 128-Bit steps.
      /// DOES NOT have any boundary checks, the pattern MUST exist.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t byteidxf128(const char* mem, const char c)
      {
         return byteidxf128<ALIGNED>(mem, _mm_set1_epi8(c));
      }

      /// <summary>
      /// Returns index of next c char in mem searching up to maxsteps 128-Bit steps.
      /// Returns size_t::max if not found in n128 ssteps.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t byteidxf128(const char* mem, const char c, const size_t n128)
      {
         return byteidxf128<ALIGNED>((const __m128i*)mem, _mm_set1_epi8(c), n128);
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
      /// <summary>
      /// Searches mem in steps of 32 bytes for the first occurence of the byte duplicated in v.
      /// For instance, searches for 0xAB if v is 0xABAB..AB.
      /// DOES NOT have any boundary checks, the pattern MUST exist.
      /// </summary>
      template <bool ALIGNED = false>
      INLINE static size_t byteidxf256(const char* mem, const __m256i& v)
      {
         size_t i = 0U;
         while (true)
         {
            const uint32_t c = CppCore::bytemaskequal256(ALIGNED ?
               _mm256_load_si256( (__m256i*)&mem[i]) :
               _mm256_loadu_si256((__m256i*)&mem[i]), v);
            if (c == 0) i += 32U;
            else return i + CppCore::tzcnt32(c);
         }
      }

      /// <summary>
      /// Searches mem in steps of 32 bytes for the first occurence of the byte duplicated in v.
      /// For instance, searches for 0xAB if v is 0xABAB..AB.
      /// Stops after n256 steps.
      /// </summary>
      template <bool ALIGNED = false>
      INLINE static size_t byteidxf256(const __m256i* mem, const __m256i& v, const size_t n256)
      {
         for (size_t i = 0; i < n256; i++)
         {
            const uint32_t c = CppCore::bytemaskequal256(ALIGNED ?
               _mm256_load_si256( &mem[i]) :
               _mm256_loadu_si256(&mem[i]), v);
            if (c != 0)
               return (i << 5) + CppCore::tzcnt32(c);
         }
         return std::numeric_limits<size_t>::max();
      }

      /// <summary>
      /// Returns index of next c char in mem searching in 256-Bit steps.
      /// DOES NOT have any boundary checks, the pattern MUST exist.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t byteidxf256(const char* mem, const char c)
      {
         return byteidxf256<ALIGNED>(mem, _mm256_set1_epi8(c));
      }

      /// <summary>
      /// Returns index of next c char in mem searching up to maxsteps 256-Bit steps.
      /// Returns size_t::max if not found in n256 steps.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t byteidxf256(const char* mem, const char c, const size_t n256)
      {
         return byteidxf256<ALIGNED>((const __m256i*)mem, _mm256_set1_epi8(c), n256);
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512BW)
      /// <summary>
      /// Searches mem in steps of 64 bytes for the first occurence of the byte duplicated in v.
      /// For instance, searches for 0xAB if v is 0xABAB..AB.
      /// DOES NOT have any boundary checks, the pattern MUST exist.
      /// </summary>
      template <bool ALIGNED = false>
      INLINE static size_t byteidxf512(const char* mem, const __m512i& v)
      {
         size_t i = 0U;
         while(true)
         {
            const uint64_t c = CppCore::bytemaskequal512(ALIGNED ?
               _mm512_load_si512( (__m512i*)&mem[i]) :
               _mm512_loadu_si512((__m512i*)&mem[i]), v);
            if (c == 0) i += 64U;
            else return i + CppCore::tzcnt64(c);
         }
      }

      /// <summary>
      /// Searches mem in steps of 64 bytes for the first occurence of the byte duplicated in v.
      /// For instance, searches for 0xAB if v is 0xABAB..AB.
      /// Stops after n512 steps.
      /// </summary>
      template <bool ALIGNED = false>
      INLINE static size_t byteidxf512(const __m512i* mem, const __m512i& v, const size_t n512)
      {
         for (size_t i = 0; i < n512; i++)
         {
            const uint64_t c = CppCore::bytemaskequal512(ALIGNED ?
               _mm512_load_si512( &mem[i]) :
               _mm512_loadu_si512(&mem[i]), v);
            if (c != 0)
               return (i << 6) + CppCore::tzcnt64(c);
         }
         return std::numeric_limits<size_t>::max();
      }

      /// <summary>
      /// Returns index of next c char in mem searching in 512-Bit steps.
      /// DOES NOT have any boundary checks, the pattern MUST exist.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t byteidxf512(const char* mem, const char c)
      {
         return byteidxf512<ALIGNED>(mem, _mm512_set1_epi8(c));
      }

      /// <summary>
      /// Returns index of next c char in mem searching up to maxsteps 512-Bit steps.
      /// Returns size_t::max if not found in n512 steps.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t byteidxf512(const char* mem, const char c, const size_t n512)
      {
         return byteidxf512<ALIGNED>((const __m512i*)mem, _mm512_set1_epi8(c), n512);
      }
#endif

      /// <summary>
      /// Returns index of next chr in mem searching up to len bytes.
      /// Returns size_t::max if not found in len bytes.
      /// Consider using aligned and padded memory and faster (e.g. zbyteidxf128) versions.
      /// </summary>
      INLINE static size_t byteidxf(const char* mem, const size_t len, const char chr)
      {
         const char* s = mem;
         const char* e = mem + len;
      #if false && defined(CPPCORE_CPUFEAT_AVX512BW)
         const __m512i z512 = _mm512_set1_epi8(chr);
         while(mem + 64U <= e)
         {
            const uint64_t c = CppCore::bytemaskequal512(_mm512_loadu_si512((__m512i*)mem), z512);
            if (c == 0) mem += 64U;
            else return mem - s + CppCore::tzcnt64(c);
         }
      #endif
      #if false && defined(CPPCORE_CPUFEAT_AVX2)
         const __m256i z256 = _mm256_set1_epi8(chr);
         while(mem + 32U <= e)
         {
            const uint32_t c = CppCore::bytemaskequal256(_mm256_loadu_si256((__m256i*)mem), z256);
            if (c == 0) mem += 32U;
            else return mem - s + CppCore::tzcnt32(c);
         }
      #endif
      #if defined(CPPCORE_CPUFEAT_SSE2)
         const __m128i z128 = _mm_set1_epi8(chr);
         while(mem + 16U <= e)
         {
            const uint32_t c = CppCore::bytemaskequal128(_mm_loadu_si128((__m128i*)mem), z128);
            if (c == 0) mem += 16U;
            else return mem - s + CppCore::tzcnt32(c);
         }
      #endif
      #if defined(CPPCORE_CPU_64BIT)
         const uint64_t chr64 = CppCore::bytedup64(chr);
      #if defined(CPPCORE_CPUFEAT_SSE2)
         if (mem + 8U <= e)
      #else
         while (mem + 8U <= e)
      #endif
         {
            const uint64_t v = *((uint64_t*)mem) ^ chr64;
            const uint64_t c = (v - 0x0101010101010101ULL) & ~v & 0x8080808080808080ULL;
            if (c == 0) mem += 8U;
            else return mem - s + (CppCore::tzcnt64(c) >> 3);
         }
         const uint32_t chr32 = (uint32_t)chr64;
         if (mem + 4U <= e)
      #else
         const uint32_t chr32 = CppCore::bytedup32(chr);
         while (mem + 4U <= e)
      #endif
         {
            const uint32_t v = *((uint32_t*)mem) ^ chr32;
            const uint32_t c = (v - 0x01010101U) & ~v & 0x80808080U;
            if (c == 0) mem += 4U;
            else return mem - s + (CppCore::tzcnt32(c) >> 3);
         }
         if (mem + 2U <= e)
         {
            const uint16_t v = *((uint16_t*)mem);
            if ((char)v == chr) return mem - s;
            else if ((v & 0xFF00) == ((uint16_t)chr << 8)) return mem - s + 1;
            else mem += 2U;
         }
         if (mem < e && *mem == chr)
            return mem - s;
         return std::numeric_limits<size_t>::max();
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ZERO BYTE INDEX
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns index of next 0x00 in mem searching in 32-Bit steps.
      /// </summary>
      INLINE static size_t zbyteidxf32(const char* mem)
      {
         size_t i = 0U;
         while(true)
         {
            const uint32_t v = *((uint32_t*)&mem[i]);
            const uint32_t c = (v - 0x01010101U) & ~v & 0x80808080U;
            if (c == 0) i += 4U;
            else return i + (CppCore::tzcnt32(c) >> 3);
         }
      }

      /// <summary>
      /// Returns index of next 0x00 in mem searching up to maxsteps 32-Bit steps.
      /// Returns size_t::max if not found in n32 steps.
      /// </summary>
      INLINE static size_t zbyteidxf32(const uint32_t* mem, const size_t n32)
      {
         for (size_t i = 0; i < n32; i++)
         {
            const uint32_t v = mem[i];
            const uint32_t c = (v - 0x01010101U) & ~v & 0x80808080U;
            if (c != 0)
               return (i << 2) + (CppCore::tzcnt32(c) >> 3);
         }
         return std::numeric_limits<size_t>::max();
      }

      /// <summary>
      /// Returns index of next 0x00 in mem searching in 64-Bit steps.
      /// </summary>
      INLINE static size_t zbyteidxf64(const char* mem)
      {
         size_t i = 0U;
         while(true)
         {
            const uint64_t v = *((uint64_t*)&mem[i]);
            const uint64_t c = (v - 0x0101010101010101ULL) & ~v & 0x8080808080808080ULL;
            if (c == 0) i += 8U;
            else return i + (CppCore::tzcnt64(c) >> 3);
         }
      }

      /// <summary>
      /// Returns index of next 0x00 in mem searching up to maxsteps 64-Bit steps.
      /// Returns size_t::max if not found in n64 steps.
      /// </summary>
      INLINE static size_t zbyteidxf64(const uint64_t* mem, const size_t n64)
      {
         for (size_t i = 0; i < n64; i++)
         {
            const uint64_t v = mem[i];
            const uint64_t c = (v - 0x0101010101010101ULL) & ~v & 0x8080808080808080ULL;
            if (c != 0)
               return (i << 3) + (CppCore::tzcnt64(c) >> 3);
         }
         return std::numeric_limits<size_t>::max();
      }

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Returns index of next 0x00 in mem searching in 128-Bit steps.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t zbyteidxf128(const char* mem)
      {
         return byteidxf128<ALIGNED>(mem, _mm_setzero_si128());
      }

      /// <summary>
      /// Returns index of next 0x00 in mem searching up to maxsteps 128-Bit steps.
      /// Returns size_t::max if not found in n128 steps.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t zbyteidxf128(const char* mem, const size_t n128)
      {
         return byteidxf128<ALIGNED>((const __m128i*)mem, _mm_setzero_si128(), n128);
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX2)
      /// <summary>
      /// Returns index of next 0x00 in mem searching in 256-Bit steps.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t zbyteidxf256(const char* mem)
      {
         return byteidxf256<ALIGNED>(mem, _mm256_setzero_si256());
      }

      /// <summary>
      /// Returns index of next 0x00 in mem searching up to maxsteps 256-Bit steps.
      /// Returns size_t::max if not found in n256 steps.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t zbyteidxf256(const char* mem, const size_t n256)
      {
         return byteidxf256<ALIGNED>((const __m256i*)mem, _mm256_setzero_si256(), n256);
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512BW)
      /// <summary>
      /// Returns index of next 0x00 in mem searching in 512-Bit steps.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t zbyteidxf512(const char* mem)
      {
         return byteidxf512<ALIGNED>(mem, _mm512_setzero_si512());
      }

      /// <summary>
      /// Returns index of next 0x00 in mem searching up to maxsteps 512-Bit steps.
      /// Returns size_t::max if not found in n512 steps.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE static size_t zbyteidxf512(const char* mem, const size_t n512)
      {
         return byteidxf512<ALIGNED>((const __m512i*)mem, _mm512_setzero_si512(), n512);
      }
#endif

      /// <summary>
      /// Returns index of next 0x00 in mem searching up to len bytes.
      /// Returns size_t::max if not found in len bytes.
      /// Consider using aligned and padded memory and faster (e.g. zbyteidxf128) versions.
      /// </summary>
      INLINE static size_t zbyteidxf(const char* mem, const size_t len)
      {
         const char* s = mem;
         const char* e = mem + len;
      #if false && defined(CPPCORE_CPUFEAT_AVX512BW)
         const __m512i z512 = _mm512_setzero_si512();
         while(mem + 64U <= e)
         {
            const uint64_t c = CppCore::bytemaskequal512(_mm512_loadu_si512((__m512i*)mem), z512);
            if (c == 0) mem += 64U;
            else return mem - s + CppCore::tzcnt64(c);
         }
      #endif
      #if false && defined(CPPCORE_CPUFEAT_AVX2)
         const __m256i z256 = _mm256_setzero_si256();
         while(mem + 32U <= e)
         {
            const uint32_t c = CppCore::bytemaskequal256(_mm256_loadu_si256((__m256i*)mem), z256);
            if (c == 0) mem += 32U;
            else return mem - s + CppCore::tzcnt32(c);
         }
      #endif
      #if defined(CPPCORE_CPUFEAT_SSE2)
         const __m128i z128 = _mm_setzero_si128();
         while(mem + 16U <= e)
         {
            const uint32_t c = CppCore::bytemaskequal128(_mm_loadu_si128((__m128i*)mem), z128);
            if (c == 0) mem += 16U;
            else return mem - s + CppCore::tzcnt32(c);
         }
      #endif
      #if defined(CPPCORE_CPU_64BIT)
      #if defined(CPPCORE_CPUFEAT_SSE2)
         if (mem + 8U <= e)
      #else
         while (mem + 8U <= e)
      #endif
         {
            const uint64_t v = *((uint64_t*)mem);
            const uint64_t c = (v - 0x0101010101010101ULL) & ~v & 0x8080808080808080ULL;
            if (c == 0) mem += 8U;
            else return mem - s + (CppCore::tzcnt64(c) >> 3);
         }
         if (mem + 4U <= e)
      #else
         while (mem + 4U <= e)
      #endif
         {
            const uint32_t v = *((uint32_t*)mem);
            const uint32_t c = (v - 0x01010101U) & ~v & 0x80808080U;
            if (c == 0) mem += 4U;
            else return mem - s + (CppCore::tzcnt32(c) >> 3);
         }
         if (mem + 2U <= e)
         {
            const uint16_t v = *((uint16_t*)mem);
            if ((char)v == 0) return mem - s;
            else if ((v & 0xFF00) == 0) return mem - s + 1;
            else mem += 2U;
         }
         if (mem < e && *mem == 0)
            return mem - s;
         return std::numeric_limits<size_t>::max();
      }
   };
}
