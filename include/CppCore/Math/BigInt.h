#pragma once
#pragma warning(disable:26495)

#include <CppCore/Root.h>
#include <CppCore/Memory.h>
#include <CppCore/Math/Util.h>
#include <CppCore/Math/Primes.h>
#include <CppCore/Encoding.h>
#include <CppCore/Random.h>

namespace CppCore
{
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // FORWARD DECLARATIONS
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   // GENERIC
   class uint128_tg;
   class uint256_tg;
   class uint512_tg;
   class uint1024_tg;
   class uint2048_tg;

   // SIMD/OPTIMIZED
   class uint128_ts;
   class uint256_ts;
   class uint512_ts;
   class uint1024_ts;
   class uint2048_ts;

   // SET DEFAULT BASED ON CONFIGURATION
#if defined(CPPCORE_OPTIMIZED_BIGINT)
   typedef uint128_ts  uint128_t;
   typedef uint256_ts  uint256_t;
   typedef uint512_ts  uint512_t;
   typedef uint1024_ts uint1024_t;
   typedef uint2048_ts uint2048_t;
#else
   typedef uint128_tg  uint128_t;
   typedef uint256_tg  uint256_t;
   typedef uint512_tg  uint512_t;
   typedef uint1024_tg uint1024_t;
   typedef uint2048_tg uint2048_t;
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Default Data Unions
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Default Data for uint128_t
   /// </summary>
   union uint128_d
   {
   public:
      static constexpr size_t N512 = 0;
      static constexpr size_t N256 = 0;
      static constexpr size_t N128 = 1;
      static constexpr size_t N64  = 2;
      static constexpr size_t N32  = 4;
      static constexpr size_t N16  = 8;
      static constexpr size_t N8   = 16;
      struct { uint64_t l;  uint64_t h; };
      struct { uint32_t ll; uint32_t lh; uint32_t hl; uint32_t hh; };
      struct { uint64_t v0; uint64_t v1; };
      uint64_t i64[N64];
      uint32_t i32[N32];
      uint16_t i16[N16];
      uint8_t  i8 [N8];
   #if defined(CPPCORE_CPUFEAT_SSE2)
      __m128i sse[N128];
      struct { __m128i sse0;};
      INLINE uint128_d(const uint128_d& oth) : sse0(oth.sse0) { }
      INLINE uint128_d(const __m128i& sse0) : sse0(sse0) { }
      #if defined(CPPCORE_CPU_X86) && defined(CPPCORE_COMPILER_MSVC)
      // _mm_set_epi64x is broken in MSVC X86 with optimizations
      INLINE uint128_d(const uint64_t& l, const uint64_t& h = 0ULL) : 
         sse0(_mm_castpd_si128(_mm_set_pd(*(double*)&h, *(double*)&l))) { }
      #else
      INLINE uint128_d(const uint64_t& l, const uint64_t& h = 0ULL) : 
         sse0(_mm_set_epi64x(h, l)) { }
      #endif
      INLINE uint128_d(
         const uint32_t& ll,
         const uint32_t& lh = 0U,
         const uint32_t& hl = 0U,
         const uint32_t& hh = 0U) :
         sse0(_mm_set_epi32(hh, hl, lh, ll)) { }
      INLINE operator const __m128i&() const { return sse0; }
   #else
      INLINE uint128_d(const uint128_d& oth) : l(oth.l), h(oth.h) { }
      INLINE uint128_d(const uint64_t& l, const uint64_t& h = 0ULL) : l(l), h(h) { }
      INLINE uint128_d(
         const uint32_t& ll,
         const uint32_t& lh = 0U,
         const uint32_t& hl = 0U,
         const uint32_t& hh = 0U) :
         ll(ll), lh(lh), hl(hl), hh(hh) { }
   #endif
      INLINE uint128_d() { }
   };

   /// <summary>
   /// Default Data for uint256_t
   /// </summary>
   template<typename T128 = uint128_t>
   union uint256_d
   {
   public:
      static constexpr size_t N512 = 0;
      static constexpr size_t N256 = 1;
      static constexpr size_t N128 = 2;
      static constexpr size_t N64  = 4;
      static constexpr size_t N32  = 8;
      static constexpr size_t N16  = 16;
      static constexpr size_t N8   = 32;
      struct { T128 l; T128 h; };
      struct { uint64_t ll; uint64_t lh; uint64_t hl; uint64_t hh; };
      struct { uint64_t v0; uint64_t v1; uint64_t v2; uint64_t v3; };
      T128     i128[N128];
      uint64_t i64 [N64];
      uint32_t i32 [N32];
      uint16_t i16 [N16];
      uint8_t  i8  [N8];
   #if defined(CPPCORE_CPUFEAT_SSE2)
      __m128i  sse[N128];
      struct { __m128i sse0; __m128i sse1; };
      INLINE uint256_d(const __m128i& sse0, const __m128i& sse1) : sse0(sse0), sse1(sse1) { }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX)
      __m256i avx[N256];
      struct { __m256i avx0; };
      INLINE uint256_d(const __m256i& avx0) : avx0(avx0) { }
      INLINE operator const __m256i& () const { return avx0; }
   #endif
      INLINE uint256_d() { }
      INLINE uint256_d(const T128& l, const T128& h = 0ULL) : l(l), h(h) { }
   #if defined(CPPCORE_CPUFEAT_AVX)
      INLINE uint256_d(const uint256_d& oth) : avx0(oth.avx0) { }
      INLINE uint256_d(
         const uint64_t& ll,
         const uint64_t& lh = 0ULL,
         const uint64_t& hl = 0ULL,
         const uint64_t& hh = 0ULL) :
         avx0(_mm256_set_epi64x(hh,hl,lh,ll)) { }
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      INLINE uint256_d(const uint256_d& oth) : sse0(oth.sse0), sse1(oth.sse1) { }
      #if defined(CPPCORE_CPU_X86) && defined(CPPCORE_COMPILER_MSVC)
      // _mm_set_epi64x is broken in MSVC X86 with optimizations
      INLINE uint256_d(
         const uint64_t& ll,
         const uint64_t& lh = 0ULL,
         const uint64_t& hl = 0ULL,
         const uint64_t& hh = 0ULL) :
         sse0(_mm_castpd_si128(_mm_set_pd(*(double*)&lh, *(double*)&ll))),
         sse1(_mm_castpd_si128(_mm_set_pd(*(double*)&hh, *(double*)&hl))) { }
      #else
      INLINE uint256_d(
         const uint64_t& ll,
         const uint64_t& lh = 0ULL,
         const uint64_t& hl = 0ULL,
         const uint64_t& hh = 0ULL) :
         sse0(_mm_set_epi64x(lh,ll)),
         sse1(_mm_set_epi64x(hh,hl)) { }
      #endif
   #else
      INLINE uint256_d(const uint256_d& oth) : l(oth.l), h(oth.h) { }
      INLINE uint256_d(
         const uint64_t& ll, 
         const uint64_t& lh = 0ULL, 
         const uint64_t& hl = 0ULL, 
         const uint64_t& hh = 0ULL) : 
         ll(ll), lh(lh), hl(hl), hh(hh) { }
   #endif
   };

   /// <summary>
   /// Default Data for uint512_t
   /// </summary>
   template<typename T128 = uint128_t, typename T256 = uint256_t>
   union uint512_d
   {
   public:
      static constexpr size_t N512 = 1;
      static constexpr size_t N256 = 2;
      static constexpr size_t N128 = 4;
      static constexpr size_t N64  = 8;
      static constexpr size_t N32  = 16;
      static constexpr size_t N16  = 32;
      static constexpr size_t N8   = 64;
      struct { T256 l;  T256 h; };
      struct { T128 ll; T128 lh; T128 hl; T128 hh; };
      struct { 
         uint64_t v0; uint64_t v1; uint64_t v2; uint64_t v3;
         uint64_t v4; uint64_t v5; uint64_t v6; uint64_t v7;
      };
      T256      i256[N256];
      T128      i128[N128];
      uint64_t  i64 [N64];
      uint32_t  i32 [N32];
      uint16_t  i16 [N16];
      uint8_t   i8  [N8];
   #if defined(CPPCORE_CPUFEAT_SSE2)
      __m128i   sse [N128];
      struct { __m128i sse0; __m128i sse1; __m128i sse2; __m128i sse3; };
      INLINE uint512_d(
         const __m128i& sse0, 
         const __m128i& sse1, 
         const __m128i& sse2, 
         const __m128i& sse3) : 
         sse0(sse0), sse1(sse1), sse2(sse2), sse3(sse3) { }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX)
      __m256i avx[N256];
      struct { __m256i avx0; __m256i avx1;};
      INLINE uint512_d(const __m256i& avx0, const __m256i& avx1) : avx0(avx0), avx1(avx1) { }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX512)
      __m512i   avx512[N512];
      struct { __m512i avx5120; };
      INLINE uint512_d(const __m512i& avx5120) : avx5120(avx5120) { }
      INLINE operator const __m512i& () const { return avx5120; }
   #endif
      INLINE uint512_d() { }
      INLINE uint512_d(const T256& l, const T256& h = 0ULL) : l(l), h(h) { }
      INLINE uint512_d(
         const T128& ll,
         const T128& lh = 0ULL,
         const T128& hl = 0ULL,
         const T128& hh = 0ULL) :
         ll(ll), lh(lh), hl(hl), hh(hh) { }
   #if defined(CPPCORE_CPUFEAT_AVX512)
      INLINE uint512_d(const uint512_d& oth) :
         avx5120(oth.avx5120) { }
      INLINE uint512_d(
         const uint64_t& v0,
         const uint64_t& v1 = 0ULL, 
         const uint64_t& v2 = 0ULL, 
         const uint64_t& v3 = 0ULL,
         const uint64_t& v4 = 0ULL, 
         const uint64_t& v5 = 0ULL, 
         const uint64_t& v6 = 0ULL, 
         const uint64_t& v7 = 0ULL) :
         avx5120(_mm512_set_epi64(v7,v6,v5,v4,v3,v2,v1,v0)) { }
   #elif defined(CPPCORE_CPUFEAT_AVX)
      INLINE uint512_d(const uint512_d& oth) :
         avx0(oth.avx0), avx1(oth.avx1) { }
      INLINE uint512_d(
         const uint64_t& v0,
         const uint64_t& v1 = 0ULL,
         const uint64_t& v2 = 0ULL,
         const uint64_t& v3 = 0ULL,
         const uint64_t& v4 = 0ULL,
         const uint64_t& v5 = 0ULL,
         const uint64_t& v6 = 0ULL,
         const uint64_t& v7 = 0ULL) :
         avx0(_mm256_set_epi64x(v3,v2,v1,v0)),
         avx1(_mm256_set_epi64x(v7,v6,v5,v4)) { }
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      INLINE uint512_d(const uint512_d& oth) :
         sse0(oth.sse0), sse1(oth.sse1), sse2(oth.sse2), sse3(oth.sse3) { }
      #if defined(CPPCORE_CPU_X86) && defined(CPPCORE_COMPILER_MSVC)
      // _mm_set_epi64x is broken in MSVC X86 with optimizations
      INLINE uint512_d(
         const uint64_t& v0,
         const uint64_t& v1 = 0ULL,
         const uint64_t& v2 = 0ULL,
         const uint64_t& v3 = 0ULL,
         const uint64_t& v4 = 0ULL,
         const uint64_t& v5 = 0ULL,
         const uint64_t& v6 = 0ULL,
         const uint64_t& v7 = 0ULL) :
         sse0(_mm_castpd_si128(_mm_set_pd(*(double*)&v1, *(double*)&v0))),
         sse1(_mm_castpd_si128(_mm_set_pd(*(double*)&v3, *(double*)&v2))),
         sse2(_mm_castpd_si128(_mm_set_pd(*(double*)&v5, *(double*)&v4))),
         sse3(_mm_castpd_si128(_mm_set_pd(*(double*)&v7, *(double*)&v6))) { }
      #else
      INLINE uint512_d(
         const uint64_t& v0,
         const uint64_t& v1 = 0ULL,
         const uint64_t& v2 = 0ULL,
         const uint64_t& v3 = 0ULL,
         const uint64_t& v4 = 0ULL,
         const uint64_t& v5 = 0ULL,
         const uint64_t& v6 = 0ULL,
         const uint64_t& v7 = 0ULL) :
         sse0(_mm_set_epi64x(v1,v0)),
         sse1(_mm_set_epi64x(v3,v2)),
         sse2(_mm_set_epi64x(v5,v4)),
         sse3(_mm_set_epi64x(v7,v6)) { }
      #endif
   #else
      INLINE uint512_d(const uint512_d& oth) :
         l(oth.l), h(oth.h) { }
      INLINE uint512_d(
         const uint64_t& v0, 
         const uint64_t& v1 = 0ULL, 
         const uint64_t& v2 = 0ULL, 
         const uint64_t& v3 = 0ULL,
         const uint64_t& v4 = 0ULL,
         const uint64_t& v5 = 0ULL,
         const uint64_t& v6 = 0ULL,
         const uint64_t& v7 = 0ULL) : 
         v0(v0), v1(v1), v2(v2), v3(v3),
         v4(v4), v5(v5), v6(v6), v7(v7) { }
   #endif
   };

   /// <summary>
   /// Default Data for uint1024_t
   /// </summary>
   template<typename T128 = uint128_t, typename T256 = uint256_t, typename T512 = uint512_t>
   union uint1024_d
   {
   public:
      static constexpr size_t N512 = 2;
      static constexpr size_t N256 = 4;
      static constexpr size_t N128 = 8;
      static constexpr size_t N64  = 16;
      static constexpr size_t N32  = 32;
      static constexpr size_t N16  = 64;
      static constexpr size_t N8   = 128;
      struct { T512 l;  T512 h; };
      struct { T256 ll; T256 lh; T256 hl; T256 hh; };
      struct { 
         uint64_t v0;  uint64_t v1;  uint64_t v2;  uint64_t v3;
         uint64_t v4;  uint64_t v5;  uint64_t v6;  uint64_t v7;
         uint64_t v8;  uint64_t v9;  uint64_t v10; uint64_t v11;
         uint64_t v12; uint64_t v13; uint64_t v14; uint64_t v15;
      };
      T512      i512[N512];
      T256      i256[N256];
      T128      i128[N128];
      uint64_t  i64 [N64];
      uint32_t  i32 [N32];
      uint16_t  i16 [N16];
      uint8_t   i8  [N8];
   #if defined(CPPCORE_CPUFEAT_SSE2)
      __m128i   sse [N128];
      struct { 
         __m128i sse0; __m128i sse1; __m128i sse2; __m128i sse3;
         __m128i sse4; __m128i sse5; __m128i sse6; __m128i sse7;
      };
      INLINE uint1024_d(
         const __m128i& sse0, 
         const __m128i& sse1, 
         const __m128i& sse2, 
         const __m128i& sse3,
         const __m128i& sse4,
         const __m128i& sse5,
         const __m128i& sse6,
         const __m128i& sse7) :
         sse0(sse0), sse1(sse1), sse2(sse2), sse3(sse3),
         sse4(sse4), sse5(sse5), sse6(sse6), sse7(sse7) { }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX)
      __m256i avx[N256];
      struct { __m256i avx0; __m256i avx1; __m256i avx2; __m256i avx3; };
      INLINE uint1024_d(
         const __m256i& avx0, const __m256i& avx1, 
         const __m256i& avx2, const __m256i& avx3) : 
         avx0(avx0), avx1(avx1), avx2(avx2), avx3(avx3) { }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX512)
      __m512i   avx512[N512];
      struct { __m512i avx5120; __m512i avx5121;};
      INLINE uint1024_d(
         const __m512i& avx5120, const __m512i& avx5121) : 
         avx5120(avx5120), avx5121(avx5121) { }
   #endif
      INLINE uint1024_d() { }
      INLINE uint1024_d(const T512& l, const T512& h = 0ULL) : l(l), h(h) { }
      INLINE uint1024_d(
         const T256& ll,
         const T256& lh = 0ULL,
         const T256& hl = 0ULL,
         const T256& hh = 0ULL) :
         ll(ll), lh(lh), hl(hl), hh(hh) { }
   #if defined(CPPCORE_CPUFEAT_AVX512)
      INLINE uint1024_d(const uint1024_d& oth) :
         avx5120(oth.avx5120), 
         avx5121(oth.avx5121) { }
      INLINE uint1024_d(
         const uint64_t& v0,         const uint64_t& v1  = 0ULL, const uint64_t& v2  = 0ULL, const uint64_t& v3  = 0ULL,
         const uint64_t& v4  = 0ULL, const uint64_t& v5  = 0ULL, const uint64_t& v6  = 0ULL, const uint64_t& v7  = 0ULL,
         const uint64_t& v8  = 0ULL, const uint64_t& v9  = 0ULL, const uint64_t& v10 = 0ULL, const uint64_t& v11 = 0ULL,
         const uint64_t& v12 = 0ULL, const uint64_t& v13 = 0ULL, const uint64_t& v14 = 0ULL, const uint64_t& v15 = 0ULL) :
         avx5120(_mm512_set_epi64(v7,v6,v5,v4,v3,v2,v1,v0)),
         avx5121(_mm512_set_epi64(v15,v14,v13,v12,v11,v10,v9,v8)) { }
   #elif defined(CPPCORE_CPUFEAT_AVX)
      INLINE uint1024_d(const uint1024_d& oth) :
         avx0(oth.avx0), avx1(oth.avx1), avx2(oth.avx2), avx3(oth.avx3) { }
      INLINE uint1024_d(
         const uint64_t& v0,         const uint64_t& v1  = 0ULL, const uint64_t& v2  = 0ULL, const uint64_t& v3  = 0ULL,
         const uint64_t& v4  = 0ULL, const uint64_t& v5  = 0ULL, const uint64_t& v6  = 0ULL, const uint64_t& v7  = 0ULL,
         const uint64_t& v8  = 0ULL, const uint64_t& v9  = 0ULL, const uint64_t& v10 = 0ULL, const uint64_t& v11 = 0ULL,
         const uint64_t& v12 = 0ULL, const uint64_t& v13 = 0ULL, const uint64_t& v14 = 0ULL, const uint64_t& v15 = 0ULL) :
         avx0(_mm256_set_epi64x(v3,v2,v1,v0)),   avx1(_mm256_set_epi64x(v7,v6,v5,v4)),
         avx2(_mm256_set_epi64x(v11,v10,v9,v8)), avx3(_mm256_set_epi64x(v15,v14,v13,v12)) { }
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      INLINE uint1024_d(const uint1024_d& oth) :
         sse0(oth.sse0), sse1(oth.sse1), sse2(oth.sse2), sse3(oth.sse3),
         sse4(oth.sse4), sse5(oth.sse5), sse6(oth.sse6), sse7(oth.sse7) { }
      #if defined(CPPCORE_CPU_X86) && defined(CPPCORE_COMPILER_MSVC)
      // _mm_set_epi64x is broken in MSVC X86 with optimizations
      INLINE uint1024_d(
         const uint64_t& v0,         const uint64_t& v1  = 0ULL, const uint64_t& v2  = 0ULL, const uint64_t& v3  = 0ULL,
         const uint64_t& v4  = 0ULL, const uint64_t& v5  = 0ULL, const uint64_t& v6  = 0ULL, const uint64_t& v7  = 0ULL,
         const uint64_t& v8  = 0ULL, const uint64_t& v9  = 0ULL, const uint64_t& v10 = 0ULL, const uint64_t& v11 = 0ULL,
         const uint64_t& v12 = 0ULL, const uint64_t& v13 = 0ULL, const uint64_t& v14 = 0ULL, const uint64_t& v15 = 0ULL) :
         sse0(_mm_castpd_si128(_mm_set_pd(*(double*)&v1,  *(double*)&v0))),
         sse1(_mm_castpd_si128(_mm_set_pd(*(double*)&v3,  *(double*)&v2))),
         sse2(_mm_castpd_si128(_mm_set_pd(*(double*)&v5,  *(double*)&v4))),
         sse3(_mm_castpd_si128(_mm_set_pd(*(double*)&v7,  *(double*)&v6))),
         sse4(_mm_castpd_si128(_mm_set_pd(*(double*)&v9,  *(double*)&v8))),
         sse5(_mm_castpd_si128(_mm_set_pd(*(double*)&v11, *(double*)&v10))),
         sse6(_mm_castpd_si128(_mm_set_pd(*(double*)&v13, *(double*)&v12))),
         sse7(_mm_castpd_si128(_mm_set_pd(*(double*)&v15, *(double*)&v14))) { }
      #else
      INLINE uint1024_d(
         const uint64_t& v0,         const uint64_t& v1  = 0ULL, const uint64_t& v2  = 0ULL, const uint64_t& v3  = 0ULL,
         const uint64_t& v4  = 0ULL, const uint64_t& v5  = 0ULL, const uint64_t& v6  = 0ULL, const uint64_t& v7  = 0ULL,
         const uint64_t& v8  = 0ULL, const uint64_t& v9  = 0ULL, const uint64_t& v10 = 0ULL, const uint64_t& v11 = 0ULL,
         const uint64_t& v12 = 0ULL, const uint64_t& v13 = 0ULL, const uint64_t& v14 = 0ULL, const uint64_t& v15 = 0ULL) :
         sse0(_mm_set_epi64x(v1,v0)), sse1(_mm_set_epi64x(v3,v2)),   sse2(_mm_set_epi64x(v5,v4)),   sse3(_mm_set_epi64x(v7,v6)),
         sse4(_mm_set_epi64x(v9,v8)), sse5(_mm_set_epi64x(v11,v10)), sse6(_mm_set_epi64x(v13,v12)), sse7(_mm_set_epi64x(v15,v14)) { }
      #endif
   #else
      INLINE uint1024_d(const uint1024_d& oth) :
         l(oth.l), h(oth.h) { }
      INLINE uint1024_d(
         const uint64_t& v0,         const uint64_t& v1  = 0ULL, const uint64_t& v2  = 0ULL, const uint64_t& v3  = 0ULL,
         const uint64_t& v4  = 0ULL, const uint64_t& v5  = 0ULL, const uint64_t& v6  = 0ULL, const uint64_t& v7  = 0ULL,
         const uint64_t& v8  = 0ULL, const uint64_t& v9  = 0ULL, const uint64_t& v10 = 0ULL, const uint64_t& v11 = 0ULL,
         const uint64_t& v12 = 0ULL, const uint64_t& v13 = 0ULL, const uint64_t& v14 = 0ULL, const uint64_t& v15 = 0ULL) :
         v0(v0),   v1(v1),   v2(v2),   v3(v3),
         v4(v4),   v5(v5),   v6(v6),   v7(v7),
         v8(v8),   v9(v9),   v10(v10), v11(v11),
         v12(v12), v13(v13), v14(v14), v15(v15) { }
   #endif
   };

   /// <summary>
   /// Default Data for uint2048_t
   /// </summary>
   template<typename T128 = uint128_t, typename T256 = uint256_t, typename T512 = uint512_t, typename T1024 = uint1024_t>
   union uint2048_d
   {
   public:
      static constexpr size_t N1024 = 2;
      static constexpr size_t N512  = 4;
      static constexpr size_t N256  = 8;
      static constexpr size_t N128  = 16;
      static constexpr size_t N64   = 32;
      static constexpr size_t N32   = 64;
      static constexpr size_t N16   = 128;
      static constexpr size_t N8    = 256;
      struct { T1024 l; T1024 h; };
      struct { T512 ll; T512 lh; T512 hl; T512 hh; };
      struct { 
         uint64_t v0;  uint64_t v1;  uint64_t v2;  uint64_t v3;
         uint64_t v4;  uint64_t v5;  uint64_t v6;  uint64_t v7;
         uint64_t v8;  uint64_t v9;  uint64_t v10; uint64_t v11;
         uint64_t v12; uint64_t v13; uint64_t v14; uint64_t v15;
         uint64_t v16; uint64_t v17; uint64_t v18; uint64_t v19;
         uint64_t v20; uint64_t v21; uint64_t v22; uint64_t v23;
         uint64_t v24; uint64_t v25; uint64_t v26; uint64_t v27;
         uint64_t v28; uint64_t v29; uint64_t v30; uint64_t v31;
      };
      T1024    i1024 [N1024];
      T512     i512  [N512];
      T256     i256  [N256];
      T128     i128  [N128];
      uint64_t i64   [N64];
      uint32_t i32   [N32];
      uint16_t i16   [N16];
      uint8_t  i8    [N8];
   #if defined(CPPCORE_CPUFEAT_SSE2)
      __m128i  sse   [N128];
      struct { 
         __m128i sse0;  __m128i sse1;  __m128i sse2;  __m128i sse3;
         __m128i sse4;  __m128i sse5;  __m128i sse6;  __m128i sse7;
         __m128i sse8;  __m128i sse9;  __m128i sse10; __m128i sse11;
         __m128i sse12; __m128i sse13; __m128i sse14; __m128i sse15;
      };
      INLINE uint2048_d(
         const __m128i& sse0,  const __m128i& sse1, 
         const __m128i& sse2,  const __m128i& sse3, 
         const __m128i& sse4,  const __m128i& sse5,
         const __m128i& sse6,  const __m128i& sse7,
         const __m128i& sse8,  const __m128i& sse9, 
         const __m128i& sse10, const __m128i& sse11, 
         const __m128i& sse12, const __m128i& sse13,
         const __m128i& sse14, const __m128i& sse15
         ) :
         sse0(sse0),   sse1(sse1),   sse2(sse2),   sse3(sse3),
         sse4(sse4),   sse5(sse5),   sse6(sse6),   sse7(sse7),
         sse8(sse8),   sse9(sse9),   sse10(sse10), sse11(sse11),
         sse12(sse12), sse13(sse13), sse14(sse14), sse15(sse15) { }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX)
      __m256i avx[N256];
      struct { 
         __m256i avx0; __m256i avx1; __m256i avx2; __m256i avx3;
         __m256i avx4; __m256i avx5; __m256i avx6; __m256i avx7;
      };
      INLINE uint2048_d(
         const __m256i& avx0, const __m256i& avx1, 
         const __m256i& avx2, const __m256i& avx3,
         const __m256i& avx4, const __m256i& avx5,
         const __m256i& avx6, const __m256i& avx7) :
         avx0(avx0), avx1(avx1), avx2(avx2), avx3(avx3),
         avx4(avx4), avx5(avx5), avx6(avx6), avx7(avx7) { }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX512)
      __m512i  avx512[N512];
      struct { __m512i avx5120; __m512i avx5121; __m512i avx5122; __m512i avx5123; };
      INLINE uint2048_d(
         const __m512i& avx5120, const __m512i& avx5121,
         const __m512i& avx5122, const __m512i& avx5123) :
         avx5120(avx5120), avx5121(avx5121),
         avx5122(avx5122), avx5123(avx5123) { }
   #endif
      INLINE uint2048_d() { }
      INLINE uint2048_d(const T1024& l, const T1024& h = 0ULL) : l(l), h(h) { }
      INLINE uint2048_d(
         const T512& ll,
         const T512& lh = 0ULL,
         const T512& hl = 0ULL,
         const T512& hh = 0ULL) :
         ll(ll), lh(lh), hl(hl), hh(hh) { }
   #if defined(CPPCORE_CPUFEAT_AVX512)
      INLINE uint2048_d(const uint2048_d& oth) :
         avx5120(oth.avx5120), avx5121(oth.avx5121), 
         avx5122(oth.avx5122), avx5123(oth.avx5123) { }
      INLINE uint2048_d(
         const uint64_t& v0,         const uint64_t& v1  = 0ULL, const uint64_t& v2  = 0ULL, const uint64_t& v3  = 0ULL,
         const uint64_t& v4  = 0ULL, const uint64_t& v5  = 0ULL, const uint64_t& v6  = 0ULL, const uint64_t& v7  = 0ULL,
         const uint64_t& v8  = 0ULL, const uint64_t& v9  = 0ULL, const uint64_t& v10 = 0ULL, const uint64_t& v11 = 0ULL,
         const uint64_t& v12 = 0ULL, const uint64_t& v13 = 0ULL, const uint64_t& v14 = 0ULL, const uint64_t& v15 = 0ULL,
         const uint64_t& v16 = 0ULL, const uint64_t& v17 = 0ULL, const uint64_t& v18 = 0ULL, const uint64_t& v19 = 0ULL,
         const uint64_t& v20 = 0ULL, const uint64_t& v21 = 0ULL, const uint64_t& v22 = 0ULL, const uint64_t& v23 = 0ULL,
         const uint64_t& v24 = 0ULL, const uint64_t& v25 = 0ULL, const uint64_t& v26 = 0ULL, const uint64_t& v27 = 0ULL,
         const uint64_t& v28 = 0ULL, const uint64_t& v29 = 0ULL, const uint64_t& v30 = 0ULL, const uint64_t& v31 = 0ULL) :
         avx5120(_mm512_set_epi64(v7,v6,v5,v4,v3,v2,v1,v0)),
         avx5121(_mm512_set_epi64(v15,v14,v13,v12,v11,v10,v9,v8)),
         avx5122(_mm512_set_epi64(v23,v22,v21,v20,v19,v18,v17,v16)),
         avx5123(_mm512_set_epi64(v31,v30,v29,v28,v27,v26,v25,v24)) { }
   #elif defined(CPPCORE_CPUFEAT_AVX)
      INLINE uint2048_d(const uint2048_d& oth) :
         avx0(oth.avx0), avx1(oth.avx1), avx2(oth.avx2), avx3(oth.avx3),
         avx4(oth.avx4), avx5(oth.avx5), avx6(oth.avx6), avx7(oth.avx7) { }
      INLINE uint2048_d(
         const uint64_t& v0,         const uint64_t& v1  = 0ULL, const uint64_t& v2  = 0ULL, const uint64_t& v3  = 0ULL,
         const uint64_t& v4  = 0ULL, const uint64_t& v5  = 0ULL, const uint64_t& v6  = 0ULL, const uint64_t& v7  = 0ULL,
         const uint64_t& v8  = 0ULL, const uint64_t& v9  = 0ULL, const uint64_t& v10 = 0ULL, const uint64_t& v11 = 0ULL,
         const uint64_t& v12 = 0ULL, const uint64_t& v13 = 0ULL, const uint64_t& v14 = 0ULL, const uint64_t& v15 = 0ULL,
         const uint64_t& v16 = 0ULL, const uint64_t& v17 = 0ULL, const uint64_t& v18 = 0ULL, const uint64_t& v19 = 0ULL,
         const uint64_t& v20 = 0ULL, const uint64_t& v21 = 0ULL, const uint64_t& v22 = 0ULL, const uint64_t& v23 = 0ULL,
         const uint64_t& v24 = 0ULL, const uint64_t& v25 = 0ULL, const uint64_t& v26 = 0ULL, const uint64_t& v27 = 0ULL,
         const uint64_t& v28 = 0ULL, const uint64_t& v29 = 0ULL, const uint64_t& v30 = 0ULL, const uint64_t& v31 = 0ULL) :
         avx0(_mm256_set_epi64x(v3,v2,v1,v0)),     avx1(_mm256_set_epi64x(v7,v6,v5,v4)),
         avx2(_mm256_set_epi64x(v11,v10,v9,v8)),   avx3(_mm256_set_epi64x(v15,v14,v13,v12)),
         avx4(_mm256_set_epi64x(v19,v18,v17,v16)), avx5(_mm256_set_epi64x(v23,v22,v21,v20)),
         avx6(_mm256_set_epi64x(v27,v26,v25,v24)), avx7(_mm256_set_epi64x(v31,v30,v29,v28)) { }
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      INLINE uint2048_d(const uint2048_d& oth) :
         sse0(oth.sse0),   sse1(oth.sse1),   sse2(oth.sse2),   sse3(oth.sse3),
         sse4(oth.sse4),   sse5(oth.sse5),   sse6(oth.sse6),   sse7(oth.sse7),
         sse8(oth.sse8),   sse9(oth.sse9),   sse10(oth.sse10), sse11(oth.sse11),
         sse12(oth.sse12), sse13(oth.sse13), sse14(oth.sse14), sse15(oth.sse15) { }
      #if defined(CPPCORE_CPU_X86) && defined(CPPCORE_COMPILER_MSVC)
      // _mm_set_epi64x is broken in MSVC X86 with optimizations
      INLINE uint2048_d(
         const uint64_t& v0,         const uint64_t& v1  = 0ULL, const uint64_t& v2  = 0ULL, const uint64_t& v3  = 0ULL,
         const uint64_t& v4  = 0ULL, const uint64_t& v5  = 0ULL, const uint64_t& v6  = 0ULL, const uint64_t& v7  = 0ULL,
         const uint64_t& v8  = 0ULL, const uint64_t& v9  = 0ULL, const uint64_t& v10 = 0ULL, const uint64_t& v11 = 0ULL,
         const uint64_t& v12 = 0ULL, const uint64_t& v13 = 0ULL, const uint64_t& v14 = 0ULL, const uint64_t& v15 = 0ULL,
         const uint64_t& v16 = 0ULL, const uint64_t& v17 = 0ULL, const uint64_t& v18 = 0ULL, const uint64_t& v19 = 0ULL,
         const uint64_t& v20 = 0ULL, const uint64_t& v21 = 0ULL, const uint64_t& v22 = 0ULL, const uint64_t& v23 = 0ULL,
         const uint64_t& v24 = 0ULL, const uint64_t& v25 = 0ULL, const uint64_t& v26 = 0ULL, const uint64_t& v27 = 0ULL,
         const uint64_t& v28 = 0ULL, const uint64_t& v29 = 0ULL, const uint64_t& v30 = 0ULL, const uint64_t& v31 = 0ULL) :
         sse0 (_mm_castpd_si128(_mm_set_pd(*(double*)&v1,  *(double*)&v0))),
         sse1 (_mm_castpd_si128(_mm_set_pd(*(double*)&v3,  *(double*)&v2))),
         sse2 (_mm_castpd_si128(_mm_set_pd(*(double*)&v5,  *(double*)&v4))),
         sse3 (_mm_castpd_si128(_mm_set_pd(*(double*)&v7,  *(double*)&v6))),
         sse4 (_mm_castpd_si128(_mm_set_pd(*(double*)&v9,  *(double*)&v8))),
         sse5 (_mm_castpd_si128(_mm_set_pd(*(double*)&v11, *(double*)&v10))),
         sse6 (_mm_castpd_si128(_mm_set_pd(*(double*)&v13, *(double*)&v12))),
         sse7 (_mm_castpd_si128(_mm_set_pd(*(double*)&v15, *(double*)&v14))),
         sse8 (_mm_castpd_si128(_mm_set_pd(*(double*)&v17, *(double*)&v16))),
         sse9 (_mm_castpd_si128(_mm_set_pd(*(double*)&v19, *(double*)&v18))),
         sse10(_mm_castpd_si128(_mm_set_pd(*(double*)&v21, *(double*)&v20))),
         sse11(_mm_castpd_si128(_mm_set_pd(*(double*)&v23, *(double*)&v22))),
         sse12(_mm_castpd_si128(_mm_set_pd(*(double*)&v25, *(double*)&v24))),
         sse13(_mm_castpd_si128(_mm_set_pd(*(double*)&v27, *(double*)&v26))),
         sse14(_mm_castpd_si128(_mm_set_pd(*(double*)&v29, *(double*)&v28))),
         sse15(_mm_castpd_si128(_mm_set_pd(*(double*)&v31, *(double*)&v30))) { }
      #else
      INLINE uint2048_d(
         const uint64_t& v0,         const uint64_t& v1  = 0ULL, const uint64_t& v2  = 0ULL, const uint64_t& v3  = 0ULL,
         const uint64_t& v4  = 0ULL, const uint64_t& v5  = 0ULL, const uint64_t& v6  = 0ULL, const uint64_t& v7  = 0ULL,
         const uint64_t& v8  = 0ULL, const uint64_t& v9  = 0ULL, const uint64_t& v10 = 0ULL, const uint64_t& v11 = 0ULL,
         const uint64_t& v12 = 0ULL, const uint64_t& v13 = 0ULL, const uint64_t& v14 = 0ULL, const uint64_t& v15 = 0ULL,
         const uint64_t& v16 = 0ULL, const uint64_t& v17 = 0ULL, const uint64_t& v18 = 0ULL, const uint64_t& v19 = 0ULL,
         const uint64_t& v20 = 0ULL, const uint64_t& v21 = 0ULL, const uint64_t& v22 = 0ULL, const uint64_t& v23 = 0ULL,
         const uint64_t& v24 = 0ULL, const uint64_t& v25 = 0ULL, const uint64_t& v26 = 0ULL, const uint64_t& v27 = 0ULL,
         const uint64_t& v28 = 0ULL, const uint64_t& v29 = 0ULL, const uint64_t& v30 = 0ULL, const uint64_t& v31 = 0ULL) :
         sse0(_mm_set_epi64x(v1,v0)),    sse1(_mm_set_epi64x(v3,v2)),    sse2(_mm_set_epi64x(v5,v4)),    sse3(_mm_set_epi64x(v7,v6)),
         sse4(_mm_set_epi64x(v9,v8)),    sse5(_mm_set_epi64x(v11,v10)),  sse6(_mm_set_epi64x(v13,v12)),  sse7(_mm_set_epi64x(v15,v14)),
         sse8(_mm_set_epi64x(v17,v16)),  sse9(_mm_set_epi64x(v19,v18)),  sse10(_mm_set_epi64x(v21,v20)), sse11(_mm_set_epi64x(v23,v22)),
         sse12(_mm_set_epi64x(v25,v24)), sse13(_mm_set_epi64x(v27,v26)), sse14(_mm_set_epi64x(v29,v28)), sse15(_mm_set_epi64x(v31,v30)) { }
      #endif
   #else
      INLINE uint2048_d(const uint2048_d& oth) :
         l(oth.l), h(oth.h) { }
      INLINE uint2048_d(
         const uint64_t& v0,         const uint64_t& v1  = 0ULL, const uint64_t& v2  = 0ULL, const uint64_t& v3  = 0ULL,
         const uint64_t& v4  = 0ULL, const uint64_t& v5  = 0ULL, const uint64_t& v6  = 0ULL, const uint64_t& v7  = 0ULL,
         const uint64_t& v8  = 0ULL, const uint64_t& v9  = 0ULL, const uint64_t& v10 = 0ULL, const uint64_t& v11 = 0ULL,
         const uint64_t& v12 = 0ULL, const uint64_t& v13 = 0ULL, const uint64_t& v14 = 0ULL, const uint64_t& v15 = 0ULL,
         const uint64_t& v16 = 0ULL, const uint64_t& v17 = 0ULL, const uint64_t& v18 = 0ULL, const uint64_t& v19 = 0ULL,
         const uint64_t& v20 = 0ULL, const uint64_t& v21 = 0ULL, const uint64_t& v22 = 0ULL, const uint64_t& v23 = 0ULL,
         const uint64_t& v24 = 0ULL, const uint64_t& v25 = 0ULL, const uint64_t& v26 = 0ULL, const uint64_t& v27 = 0ULL,
         const uint64_t& v28 = 0ULL, const uint64_t& v29 = 0ULL, const uint64_t& v30 = 0ULL, const uint64_t& v31 = 0ULL) :
         v0(v0),   v1(v1),   v2(v2),   v3(v3),
         v4(v4),   v5(v5),   v6(v6),   v7(v7),
         v8(v8),   v9(v9),   v10(v10), v11(v11),
         v12(v12), v13(v13), v14(v14), v15(v15),
         v16(v16), v17(v17), v18(v18), v19(v19),
         v20(v20), v21(v21), v22(v22), v23(v23),
         v24(v24), v25(v25), v26(v26), v27(v27),
         v28(v28), v29(v29), v30(v30), v31(v31) { }
   #endif
   };

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // 
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   using uint128_tgd  = uint128_d;
   using uint256_tgd  = uint256_d <uint128_tg>;
   using uint512_tgd  = uint512_d <uint128_tg, uint256_tg>;
   using uint1024_tgd = uint1024_d<uint128_tg, uint256_tg, uint512_tg>;
   using uint2048_tgd = uint2048_d<uint128_tg, uint256_tg, uint512_tg, uint1024_tg>;

   using uint128_tsd  = uint128_d;
   using uint256_tsd  = uint256_d <uint128_ts>;
   using uint512_tsd  = uint512_d <uint128_ts, uint256_ts>;
   using uint1024_tsd = uint1024_d<uint128_ts, uint256_ts, uint512_ts>;
   using uint2048_tsd = uint2048_d<uint128_ts, uint256_ts, uint512_ts, uint1024_ts>;

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Base uintx_t Implementation
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Base class for integers built from smaller integer chunks.
   /// </summary>
   template<class TC, typename D>
   class uintx_t
   {
   private:
      typedef uintx_t<TC, D> TB;

   protected:
      /// <summary>
      /// Casts this to TC
      /// </summary>
      INLINE TC* thiss() const { return (TC*)this; }

   public:
      constexpr static size_t N1024 = sizeof(D) / 128;
      constexpr static size_t N512  = sizeof(D) / 64;
      constexpr static size_t N256  = sizeof(D) / 32;
      constexpr static size_t N128  = sizeof(D) / 16;
      constexpr static size_t N64   = sizeof(D) / 8;
      constexpr static size_t N32   = sizeof(D) / 4;
      constexpr static size_t N16   = sizeof(D) / 2;
      constexpr static size_t N8    = sizeof(D);
      constexpr static size_t NBITS = sizeof(D) * 8;

      /// <summary>
      /// Data
      /// </summary>
      D d;

      /////////////////////////////////////////////////////////////////////////////////////////////
      // CONSTRUCTORS
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Empty Constructor
      /// </summary>
      INLINE uintx_t() { }

      /// <summary>
      /// Constructor from Data
      /// </summary>
      constexpr INLINE uintx_t(const D& v) : d(v) { }

      /// <summary>
      /// Constructor from 64 Bit Unsigned Integer
      /// </summary>
      constexpr INLINE uintx_t(const uint64_t v) : d(v) { }

      /// <summary>
      /// Constructor from 32 Bit Unsigned Integer
      /// </summary>
      constexpr INLINE uintx_t(const uint32_t v) : uintx_t((uint64_t)v) { }

      /// <summary>
      /// Constructor from 64 Bit Integer
      /// </summary>
      constexpr INLINE uintx_t(const int64_t v) : uintx_t((uint64_t)v) { }

      /// <summary>
      /// Constructor from 32 Bit Integer
      /// </summary>
      constexpr INLINE uintx_t(const int32_t v) : uintx_t((uint32_t)v) { }

      /// <summary>
      /// Constructor from Decimal string
      /// </summary>
      INLINE uintx_t(const ::std::string& input)
      {
         *thiss() = TC::parseDecimal(input.c_str());
      }

      /// <summary>
      /// Constructor from any alphabet string
      /// </summary>
      INLINE uintx_t(const ::std::string& input, const ::std::string& alphabet)
      {
         TC::tryParse(input, *thiss(), alphabet);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // HELPERS
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns the minimum value (all bits zero)
      /// </summary>
      INLINE static TC min()
      {
         return TC(0ULL);
      }

      /// <summary>
      /// Returns the maximum value (all bits one)
      /// </summary>
      INLINE static TC max()
      {
         TC r;
         for (size_t i = 0U; i < N64; i++)
            r.d.i64[i] = UINT64_MAX;
         return r;
      }

      /// <summary>
      /// Sets all bits to zero.
      /// </summary>
      INLINE void clear()
      {
         CppCore::clear(*thiss());
      }

      /// <summary>
      /// Loads into CPU cache if available on platform.
      /// </summary>
      template<int HINT = 1>
      INLINE void prefetch() const
      {
      #if defined(CPPCORE_CPUFEAT_SSE)
         // it's cpu model based how many bytes this loads...
         // expected range is 32 on older cpu to 64 bytes on newer cpu (maybe even above).
         // use only for 512-bit integers and above with their first ~512 bits.
         if (N512 > 0U) 
            _mm_prefetch((const char*)d.sse, HINT);
      #endif
      }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // STD::NUMERIC_LIMITS
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// For std::numeric_limits template specialization
      /// </summary>
      class numeric_limits
      {
      public:
         INLINE static TC min() { return TC::min(); };
         INLINE static TC max() { return TC::max(); };
      };

      /////////////////////////////////////////////////////////////////////////////////////////////
      // STATIC OPS
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Static Operations
      /// </summary>
      class Op
      {
      private:
         INLINE Op() { }
      public:
         /////////////////////////////////////////////////////////////////////////////////////////////
         // COMPARISON
         /////////////////////////////////////////////////////////////////////////////////////////////

         /// <summary>
         /// a == b (same type)
         /// </summary>
         INLINE static bool eq(const TC& a, const TC& b)
         {
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = 0; i < N64; i++)
               if (a.d.i64[i] != b.d.i64[i])
                  return false;
         #else
            for (size_t i = 0; i < N32; i++)
               if (a.d.i32[i] != b.d.i32[i])
                  return false;
         #endif
            return true;
         }

         /// <summary>
         /// a == b (uint64)
         /// </summary>
         INLINE static bool eq(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] != b)
               return false;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return false;
            return true;
         }

         /// <summary>
         /// a == b (uint32)
         /// </summary>
         INLINE static bool eq(const TC& a, const uint32_t& b)
         {
            if (a.d.i32[0] != b)
               return false;
            if (a.d.i32[1] != 0)
               return false;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return false;
            return true;
         }

         /// <summary>
         /// a != b (same type)
         /// </summary>
         INLINE static bool neq(const TC& a, const TC& b)
         {
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = 0; i < N64; i++)
               if (a.d.i64[i] != b.d.i64[i])
                  return true;
         #else
            for (size_t i = 0; i < N32; i++)
               if (a.d.i32[i] != b.d.i32[i])
                  return true;
         #endif
            return false;
         }

         /// <summary>
         /// a != b (uint64)
         /// </summary>
         INLINE static bool neq(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] != b)
               return true;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return true;
            return false;
         }
         
         /// <summary>
         /// a != b (uint32)
         /// </summary>
         INLINE static bool neq(const TC& a, const uint32_t& b)
         {
            if (a.d.i32[0] != b)
               return true;
            if (a.d.i32[1] != 0)
               return true;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return true;
            return false;
         }

         /// <summary>
         /// a < b (same type)
         /// </summary>
         INLINE static bool lt(const TC& a, const TC& b)
         {
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = N64 - 1; i != std::numeric_limits<size_t>::max(); i--)
               if      (a.d.i64[i] < b.d.i64[i]) return true;  // smaller
               else if (a.d.i64[i] > b.d.i64[i]) return false; // larger
         #else
            for (size_t i = N32 - 1; i != std::numeric_limits<size_t>::max(); i--)
               if      (a.d.i32[i] < b.d.i32[i]) return true;  // smaller
               else if (a.d.i32[i] > b.d.i32[i]) return false; // larger
         #endif
            return false;                                      // equal
         }

         /// <summary>
         /// a < b (uint64)
         /// </summary>
         INLINE static bool lt(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] >= b)
               return false;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return false;
            return true;
         }

         /// <summary>
         /// a < b (uint32)
         /// </summary>
         INLINE static bool lt(const TC& a, const uint32_t& b)
         {
            if (a.d.i32[0] >= b)
               return false;
            if (a.d.i32[1] != 0)
               return false;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return false;
            return true;
         }

         /// <summary>
         /// a <= b (same type)
         /// </summary>
         INLINE static bool lte(const TC& a, const TC& b)
         {
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = N64 - 1; i != std::numeric_limits<size_t>::max(); i--)
               if      (a.d.i64[i] < b.d.i64[i]) return true;  // smaller
               else if (a.d.i64[i] > b.d.i64[i]) return false; // larger
         #else
            for (size_t i = N32 - 1; i != std::numeric_limits<size_t>::max(); i--)
               if      (a.d.i32[i] < b.d.i32[i]) return true;  // smaller
               else if (a.d.i32[i] > b.d.i32[i]) return false; // larger
         #endif
            return true;                                       // equal
         }

         /// <summary>
         /// a <= b (uint64)
         /// </summary>
         INLINE static bool lte(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] > b)
               return false;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return false;
            return true;
         }

         /// <summary>
         /// a <= b (uint32)
         /// </summary>
         INLINE static bool lte(const TC& a, const uint32_t& b)
         {
            if (a.d.i32[0] > b)
               return false;
            if (a.d.i32[1] != 0)
               return false;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return false;
            return true;
         }

         /// <summary>
         /// a > b (same type)
         /// </summary>
         INLINE static bool gt(const TC& a, const TC& b)
         {
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = N64 - 1; i != std::numeric_limits<size_t>::max(); i--)
               if      (a.d.i64[i] < b.d.i64[i]) return false; // smaller
               else if (a.d.i64[i] > b.d.i64[i]) return true;  // larger
         #else
            for (size_t i = N32 - 1; i != std::numeric_limits<size_t>::max(); i--)
               if      (a.d.i32[i] < b.d.i32[i]) return false; // smaller
               else if (a.d.i32[i] > b.d.i32[i]) return true;  // larger
         #endif
            return false;                                      // equal
         }

         /// <summary>
         /// a > b (uint64)
         /// </summary>
         INLINE static bool gt(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] > b)
               return true;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return true;
            return false;
         }

         /// <summary>
         /// a > b (uint32)
         /// </summary>
         INLINE static bool gt(const TC& a, const uint32_t& b)
         {
            if (a.d.i32[0] > b)
               return true;
            if (a.d.i32[1] != 0)
               return true;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return true;
            return false;
         }

         /// <summary>
         /// a >= b (same type)
         /// </summary>
         INLINE static bool gte (const TC& a, const TC& b)
         {
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = N64 - 1; i != std::numeric_limits<size_t>::max(); i--)
               if      (a.d.i64[i] < b.d.i64[i]) return false; // smaller
               else if (a.d.i64[i] > b.d.i64[i]) return true;  // larger
         #else
            for (size_t i = N32 - 1; i != std::numeric_limits<size_t>::max(); i--)
               if      (a.d.i32[i] < b.d.i32[i]) return false; // smaller
               else if (a.d.i32[i] > b.d.i32[i]) return true;  // larger
         #endif
            return true;                                       // equal
         }

         /// <summary>
         /// a >= b (uint64)
         /// </summary>
         INLINE static bool gte(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] >= b)
               return true;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return true;
            return false;
         }

         /// <summary>
         /// a >= b (uint32)
         /// </summary>
         INLINE static bool gte(const TC& a, const uint32_t& b)
         {
            if (a.d.i32[0] >= b)
               return true;
            if (a.d.i32[1] != 0)
               return true;
            for (size_t i = 1; i < N64; i++)
               if (a.d.i64[i] != 0)
                  return true;
            return false;
         }

         /////////////////////////////////////////////////////////////////////////////////////////////
         // BIT OPERATIONS
         /////////////////////////////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Binary OR (a OR b = r) with same type.
         /// </summary>
         INLINE static void _or(const TC& a, const TC& b, TC& r)
         {
            CppCore::or_(a, b, r);
         }

         /// <summary>
         /// Binary OR (a OR b = r) with 64-Bit integer.
         /// </summary>
         INLINE static void _or(const TC& a, const uint64_t& b, TC& r)
         {
            r.d.i64[0] = a.d.i64[0] | b;
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = 1; i < N64; i++)
               r.d.i64[i] = a.d.i64[i];
         #else
            for (size_t i = 2; i < N32; i++)
               r.d.i32[i] = a.d.i32[i];
         #endif
         }

         /// <summary>
         /// Binary OR (a OR b = r) with 32-Bit integer.
         /// </summary>
         INLINE static void _or(const TC& a, const uint32_t& b, TC& r)
         {
            r.d.i32[0] = a.d.i32[0] | b;
            r.d.i32[1] = a.d.i32[1];
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = 1; i < N64; i++)
               r.d.i64[i] = a.d.i64[i];
         #else
            for (size_t i = 2; i < N32; i++)
               r.d.i32[i] = a.d.i32[i];
         #endif
         }

         /// <summary>
         /// Binary AND (a AND b = r) with same type.
         /// </summary>
         INLINE static void _and(const TC & a, const TC & b, TC & r)
         {
            CppCore::and_(a, b, r);
         }

         /// <summary>
         /// Binary AND (a AND b = r)  with 64-Bit integer.
         /// </summary>
         INLINE static void _and(const TC& a, const uint64_t& b, TC& r)
         {
            r.d.i64[0] = a.d.i64[0] & b;
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = 1; i < N64; i++)
               r.d.i64[i] = 0;
         #else
            for (size_t i = 2; i < N32; i++)
               r.d.i32[i] = 0;
         #endif
         }

         /// <summary>
         /// Binary AND (a AND b = r) with 32-Bit integer.
         /// </summary>
         INLINE static void _and(const TC& a, const uint32_t& b, TC& r)
         {
            r.d.i32[0] = a.d.i32[0] & b;
            r.d.i32[1] = 0;
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = 1; i < N64; i++)
               r.d.i64[i] = 0;
         #else
            for (size_t i = 2; i < N32; i++)
               r.d.i32[i] = 0;
         #endif
         }

         /// <summary>
         /// Binary XOR (a XOR b = r) with same type.
         /// </summary>
         INLINE static void _xor(const TC& a, const TC& b, TC& r)
         {
            CppCore::xor_(a, b, r);
         }

         /// <summary>
         /// Binary XOR (a XOR b = r)  with 64-Bit integer.
         /// </summary>
         INLINE static void _xor(const TC& a, const uint64_t& b, TC& r)
         {
            r.d.i64[0] = a.d.i64[0] ^ b;
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = 1; i < N64; i++)
               r.d.i64[i] = a.d.i64[i];
         #else
            for (size_t i = 2; i < N32; i++)
               r.d.i32[i] = a.d.i32[i];
         #endif
         }

         /// <summary>
         /// Binary XOR (a XOR b = r) with 32-Bit integer.
         /// </summary>
         INLINE static void _xor(const TC& a, const uint32_t& b, TC& r)
         {
            r.d.i32[0] = a.d.i32[0] ^ b;
            r.d.i32[1] = a.d.i32[1];
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = 1; i < N64; i++)
               r.d.i64[i] = a.d.i64[i];
         #else
            for (size_t i = 2; i < N32; i++)
               r.d.i32[i] = a.d.i32[i];
         #endif
         }

         /// <summary>
         /// Binary NOT (~a = r) with same type.
         /// </summary>
         INLINE static void _not(const TC& a, TC& r)
         {
            CppCore::not_(a, r);
         }

         /// <summary>
         /// Large Left Shift
         /// </summary>
         INLINE static void shl64x(TC& a, const uint8_t s)
         {
            CppCore::shl64x(a.d.i64, a.d.i64, N64, s);
         }

         /// <summary>
         /// Binary Left Shift (a << b = a)
         /// </summary>
         INLINE static void shl(TC& a, const size_t b)
         {
            CppCore::shl(a, a, b);
         }

         /// <summary>
         /// Large Right Shift
         /// </summary>
         INLINE static void shr64x(TC& a, const uint8_t s)
         {
            CppCore::shr64x(a.d.i64, a.d.i64, N64, s);
         }

         /// <summary>
         /// Binary Right Shift (a >> b = a)
         /// </summary>
         INLINE static void shr(TC& a, const size_t b)
         {
            CppCore::shr(a, a, b);
         }

         /// <summary>
         /// Binary Left Roll (a rotl b = a). TODO: Needs optimization.
         /// </summary>
         INLINE static void rotl(TC& a, size_t b)
         {
            b &= ((sizeof(TC) << 3) - 1U);
            while (b >= 64U)
            {
               uint64_t t = a.d.i64[N64-1];
               for (size_t i = N64-1; i > 0; i--)
                  a.d.i64[i] = a.d.i64[i-1];

               a.d.i64[0] = t;
               b -= 64U;
            }
            if (b)
            {
               uint64_t t = a.d.i64[N64-1];
               for (size_t i = N64-1; i > 0; i--)
                  a.d.i64[i] = CppCore::shld64(a.d.i64[i], a.d.i64[i-1], (uint8_t)b);
               a.d.i64[0] = CppCore::shld64(a.d.i64[0], t, (uint8_t)b);
            }
         }

         /// <summary>
         /// Binary Right Roll (a rotr b = a). TODO: Needs optimization.
         /// </summary>
         INLINE static void rotr(TC& a, size_t b)
         {
            b &= ((sizeof(TC) << 3) - 1U);
            while (b >= 64U)
            {
               uint64_t t = a.d.i64[0];
               for (size_t i = 0; i < N64-1; i++)
                  a.d.i64[i] = a.d.i64[i+1];

               a.d.i64[N64-1] = t;
               b -= 64U;
            }
            if (b)
            {
               uint64_t t = a.d.i64[0];
               for (size_t i = 0; i < N64-1; i++)
                  a.d.i64[i] = CppCore::shrd64(a.d.i64[i], a.d.i64[i+1], (uint8_t)b);
               a.d.i64[N64-1] = CppCore::shrd64(a.d.i64[N64-1], t, (uint8_t)b);
            }
         }

         /// <summary>
         /// Population Count (counts the number of 1 bits)
         /// </summary>
         INLINE static void popcnt(const TC& a, uint32_t& r)
         {
            r = CppCore::popcnt(a);
         }

         /// <summary>
         /// Trailing Zeros Count
         /// </summary>
         INLINE static void tzcnt(const TC& a, uint32_t& r)
         {
            r = CppCore::tzcnt(a);
         }

         /// <summary>
         /// Leading Zeros Count
         /// </summary>
         INLINE static void lzcnt(const TC& a, uint32_t& r)
         {
            r = CppCore::lzcnt(a);
         }

         /// <summary>
         /// Gets the bit at index i
         /// </summary>
         INLINE static void getbitat(const TC& a, uint32_t i, bool& r)
         {
            const uint32_t num = (i >> 6) & (N64-1U);
            const uint32_t idx = (i & (uint32_t)0x3F);
            r = (bool)CppCore::bitextract64(a.d.i64[num], idx);
         }

         /// <summary>
         /// Sets the bit at index i
         /// </summary>
         INLINE static void setbitat(TC& a, size_t i, bool v)
         {
            const size_t num = (i >> 6) & (N64-1U);
            const size_t idx = (i & (size_t)0x3F);
            a.d.i64[num] = CppCore::setbit64(a.d.i64[num], idx, v);
         }

         /// <summary>
         /// Swaps byte order
         /// </summary>
         INLINE static void byteswap(TC& a)
         {
         #if defined(CPPCORE_CPU_64BIT)
            for (size_t i = 0; i < N64/2U; i++)
            {
               uint64_t t = CppCore::byteswap64(a.d.i64[i]);
               a.d.i64[i] = CppCore::byteswap64(a.d.i64[N64-i-1U]);
               a.d.i64[N64-i-1U] = t;
            }
         #else
            for (size_t i = 0; i < N32/2U; i++)
            {
               uint32_t t = CppCore::byteswap32(a.d.i32[i]);
               a.d.i32[i] = CppCore::byteswap32(a.d.i32[N32-i-1U]);
               a.d.i32[N32-i-1U] = t;
            }
         #endif
         }

         /////////////////////////////////////////////////////////////////////////////////////////////
         // ARITHMETIC
         /////////////////////////////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Addition (a+b=r)(same type)
         /// </summary>
         INLINE static void add(const TC& a, const TC& b, TC& r)
         {
            CppCore::uadd(a, b, r);
         }

         /// <summary>
         /// Addition (a+b=r)(uint64)
         /// </summary>
         INLINE static void add(const TC& a, const uint64_t& b, TC& r)
         {
            uint8_t c = 0;
         #if defined(CPPCORE_CPU_64BIT)
            CppCore::addcarry64(a.d.i64[0], b, r.d.i64[0], c);
            for (size_t i = 1; i < N64; i++)
               CppCore::addcarry64(a.d.i64[i], 0ULL, r.d.i64[i], c);
         #else
            CppCore::addcarry32(a.d.i32[0], (uint32_t)b,       r.d.i32[0], c);
            CppCore::addcarry32(a.d.i32[1], (uint32_t)(b>>32), r.d.i32[1], c);
            for (size_t i = 2; i < N32; i++)
               CppCore::addcarry32(a.d.i32[i], 0U, r.d.i32[i], c);
         #endif
         }

         /// <summary>
         /// Addition (a+b=r)(uint32)
         /// </summary>
         INLINE static void add(const TC& a, const uint32_t& b, TC& r)
         {
            uint8_t c = 0;
         #if defined(CPPCORE_CPU_64BIT)
            CppCore::addcarry64(a.d.i64[0], (uint64_t)b, r.d.i64[0], c);
            for (size_t i = 1; i < N64; i++)
               CppCore::addcarry64(a.d.i64[i], 0ULL, r.d.i64[i], c);
         #else
            CppCore::addcarry32(a.d.i32[0], b, r.d.i32[0], c);
            for (size_t i = 1; i < N32; i++)
               CppCore::addcarry32(a.d.i32[i], 0U, r.d.i32[i], c);
         #endif
         }

         /// <summary>
         /// Addition with Carry (a+b+c=r+c)(same type)
         /// </summary>
         INLINE static void addc(const TC& a, const TC& b, TC& r, uint8_t& c)
         {
            CppCore::addcarry(a, b, r, c);
         }

         /// <summary>
         /// Addition with Carry (a+b+c=r+c)(uint64_t)
         /// </summary>
         INLINE static void addc(const TC& a, const uint64_t& b, TC& r, uint8_t& c)
         {
            CppCore::addcarry(a, b, r, c);
         }

         /// <summary>
         /// Addition with Carry (a+b+c=r+c)(uint32_t)
         /// </summary>
         INLINE static void addc(const TC& a, const uint32_t& b, TC& r, uint8_t& c)
         {
            CppCore::addcarry(a, b, r, c);
         }

         /// <summary>
         /// Subtraction (a-b=r)(same type)
         /// </summary>
         INLINE static void sub(const TC& a, const TC& b, TC& r)
         {
            CppCore::usub(a, b, r);
         }

         /// <summary>
         /// Subtraction (a-b=r)(uint64)
         /// </summary>
         INLINE static void sub(const TC& a, const uint64_t& b, TC& r)
         {
            uint8_t c = 0;
         #if defined(CPPCORE_CPU_64BIT)
            CppCore::subborrow64(a.d.i64[0], b, r.d.i64[0], c);
            for (size_t i = 1; i < N64; i++)
               CppCore::subborrow64(a.d.i64[i], 0ULL, r.d.i64[i], c);
         #else
            CppCore::subborrow32(a.d.i32[0], (uint32_t)b,       r.d.i32[0], c);
            CppCore::subborrow32(a.d.i32[1], (uint32_t)(b>>32), r.d.i32[1], c);
            for (size_t i = 2; i < N32; i++)
               CppCore::subborrow32(a.d.i32[i], 0U, r.d.i32[i], c);
         #endif
         }

         /// <summary>
         /// Subtraction (a-b=r)(uint32)
         /// </summary>
         INLINE static void sub(const TC& a, const uint32_t& b, TC& r)
         {
            uint8_t c = 0;
         #if defined(CPPCORE_CPU_64BIT)
            CppCore::subborrow64(a.d.i64[0], (uint64_t)b, r.d.i64[0], c);
            for (size_t i = 1; i < N64; i++)
               CppCore::subborrow64(a.d.i64[i], 0ULL, r.d.i64[i], c);
         #else
            CppCore::subborrow32(a.d.i32[0], b, r.d.i32[0], c);
            for (size_t i = 1; i < N32; i++)
               CppCore::subborrow32(a.d.i32[i], 0U, r.d.i32[i], c);
         #endif
         }

         /// <summary>
         /// Subtraction with Borrow (a-b-c=r-c)(same type)
         /// </summary>
         INLINE static void subb(const TC& a, const TC& b, TC& r, uint8_t& c)
         {
            CppCore::subborrow(a, b, r, c);
         }

         /// <summary>
         /// Subtraction with Borrow (a-b-c=r-c)(uint64_t)
         /// </summary>
         INLINE static void subb(const TC& a, const uint64_t& b, TC& r, uint8_t& c)
         {
            CppCore::subborrow(a, b, r, c);
         }

         /// <summary>
         /// Subtraction with Borrow (a-b-c=r-c)(uint32_t)
         /// </summary>
         INLINE static void subb(const TC& a, const uint32_t& b, TC& r, uint8_t& c)
         {
            CppCore::subborrow(a, b, r, c);
         }

         /// <summary>
         /// Multiplication (a*b=r)(same type)
         /// </summary>
         INLINE static void mul(const TC& a, const TC& b, TC& r)
         {
            CppCore::umul(a, b, r);
         }

         /// <summary>
         /// Multiplication (a*b=r)(uint64)
         /// </summary>
         INLINE static void mul(const TC& a, const uint64_t& b, TC& r)
         {
            CppCore::umul(a, b, r);
         }

         /// <summary>
         /// Multiplication (a*b=r)(uint32)
         /// </summary>
         INLINE static void mul(const TC& a, const uint32_t& b, TC& r)
         {
         #if defined(CPPCORE_CPU_64BIT)
            CppCore::umul(a, (uint64_t)b, r);
         #else
            CppCore::umul(a, b, r);
         #endif
         }

         /// <summary>
         /// Wide Multiplication (a*b=r)(same type)
         /// </summary>
         INLINE static void mulw(const TC& a, const TC& b, uint64_t r[N64+N64])
         {
            struct TCX2 { uint64_t x[N64+N64]; };
            CppCore::umul(a, b, *(TCX2*)r);
         }

         /// <summary>
         /// Wide Multiplication (a*b=r)(uint64_t)
         /// </summary>
         INLINE static void mulw(const TC& a, const uint64_t& b, uint64_t r[N64+1])
         {
            struct TCX { uint64_t x[N64+1]; };
            CppCore::umul(a, b, *(TCX*)r);
         }

         /// <summary>
         /// Wide Multiplication (a*b=r)(uint32_t)
         /// </summary>
         INLINE static void mulw(const TC& a, const uint32_t& b, uint64_t r[N64+1])
         {
            const uint64_t b64 = b;
            TC::Op::mulw(a, b64, r);
         }

         /// <summary>
         /// Division+Modulo (a/b=q,r)(same type).
         /// </summary>
         INLINE static void divmod(const TC& n, const TC& d, TC&q, TC& r)
         {
            TC un[2];
            CppCore::udivmod<TC, TC>(q, r, n, d, un);
         }

         /// <summary>
         /// Division+Modulo (a/b=q,r)(uint32).
         /// </summary>
         INLINE static void divmod(const TC& n, const uint32_t& d, TC& q, uint32_t& r)
         {
         #if defined(CPPCORE_CPU_X64)
            uint64_t r64;
            CppCore::udivmod128_64x(n.d.i64, (uint64_t)d, q.d.i64, r64, N64);
            r = (uint32_t)r64;
         #else
            CppCore::udivmod64_32x(n.d.i32, d, q.d.i32, r, N32);
         #endif
         }

         /// <summary>
         /// Division (a/b=r)(same type)
         /// </summary>
         INLINE static void div(const TC& a, const TC& b, TC& q)
         {
            TC r;
            TC::Op::divmod(a, b, q, r);
         }

         /// <summary>
         /// Division (a/b=r)(uint32)
         /// </summary>
         INLINE static void div(const TC& a, const uint32_t& b, TC& q)
         {
            uint32_t r;
            TC::Op::divmod(a, b, q, r);
         }

         /// <summary>
         /// Modulo (a%b=r)(same type)
         /// </summary>
         INLINE static void mod(const TC& a, const TC& b, TC& r)
         {
            TC mem[2];
            CppCore::umod(r, a, b, mem);
         }

      #if defined(CPPCORE_CPU_X64)
         /// <summary>
         /// Modulo (a%b=r)(uint64)
         /// </summary>
         INLINE static void mod(const TC& a, const uint64_t& b, uint64_t& r)
         {
            r = CppCore::umod128_64x(a.d.i64, b, N64);
         }
      #endif

         /// <summary>
         /// Modulo (a%b=r)(uint32)
         /// </summary>
         INLINE static void mod(const TC& a, const uint32_t& b, uint32_t& r)
         {
         #if defined(CPPCORE_CPU_X64)
            r = (uint32_t)CppCore::umod128_64x(a.d.i64, (uint64_t)b, N64);
         #else
            r = CppCore::umod64_32x(a.d.i32, b, N32);
         #endif
         }

         /// <summary>
         /// Square root (sqrt(a)=r)
         /// </summary>
         INLINE static void sqrt(const TC& a, TC& r)
         {
            r = CppCore::isqrt(a);
         }

         /// <summary>
         /// Power (a^b=r)
         /// </summary>
         template<typename UINT>
         INLINE static void pow(const TC& a, const UINT& b, TC& r)
         {
            r = CppCore::upow(a, b);
         }
      };

      /////////////////////////////////////////////////////////////////////////////////////////////
      // INCREMENT/DECREMENT OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Increment Operator Prefix (++i)
      /// </summary>
      constexpr INLINE TC& operator ++ ()
      {
         for (size_t i = 0; i < N64; i++)
         {
            // increment
            d.i64[i]++;

            // done if no overflow
            if (d.i64[i] != 0)
               break;
         }
         return *thiss();
      }

      /// <summary>
      /// Increment Operator Postfix (i++)
      /// </summary>
      constexpr INLINE TC operator ++ (int)
      {
         TC r(*thiss());
         ++(*thiss());
         return r;
      }

      /// <summary>
      /// Decrement Operator Prefix (--i)
      /// </summary>
      constexpr INLINE TC& operator -- ()
      {
         for (size_t i = 0; i < N64; i++)
         {
            // decrement
            d.i64[i]--;

            // done if no underflow
            if (d.i64[i] != UINT64_MAX)
               break;
         }
         return *thiss();
      }

      /// <summary>
      /// Decrement Operator Postfix (i--)
      /// </summary>
      constexpr INLINE TC operator -- (int)
      {
         TC r(*thiss());
         --(*thiss());
         return r;
      }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // RELATIONAL OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////

      constexpr INLINE bool operator == (const TC& v) const { return TC::Op::eq (*thiss(), v); }
      constexpr INLINE bool operator != (const TC& v) const { return TC::Op::neq(*thiss(), v); }
      constexpr INLINE bool operator <  (const TC& v) const { return TC::Op::lt (*thiss(), v); }
      constexpr INLINE bool operator <= (const TC& v) const { return TC::Op::lte(*thiss(), v); }
      constexpr INLINE bool operator >  (const TC& v) const { return TC::Op::gt (*thiss(), v); }
      constexpr INLINE bool operator >= (const TC& v) const { return TC::Op::gte(*thiss(), v); }

      constexpr INLINE bool operator == (const uint64_t& v) const { return TC::Op::eq (*thiss(), v); }
      constexpr INLINE bool operator != (const uint64_t& v) const { return TC::Op::neq(*thiss(), v); }
      constexpr INLINE bool operator <  (const uint64_t& v) const { return TC::Op::lt (*thiss(), v); }
      constexpr INLINE bool operator <= (const uint64_t& v) const { return TC::Op::lte(*thiss(), v); }
      constexpr INLINE bool operator >  (const uint64_t& v) const { return TC::Op::gt (*thiss(), v); }
      constexpr INLINE bool operator >= (const uint64_t& v) const { return TC::Op::gte(*thiss(), v); }

      constexpr INLINE bool operator == (const uint32_t& v) const { return TC::Op::eq (*thiss(), v); }
      constexpr INLINE bool operator != (const uint32_t& v) const { return TC::Op::neq(*thiss(), v); }
      constexpr INLINE bool operator <  (const uint32_t& v) const { return TC::Op::lt (*thiss(), v); }
      constexpr INLINE bool operator <= (const uint32_t& v) const { return TC::Op::lte(*thiss(), v); }
      constexpr INLINE bool operator >  (const uint32_t& v) const { return TC::Op::gt (*thiss(), v); }
      constexpr INLINE bool operator >= (const uint32_t& v) const { return TC::Op::gte(*thiss(), v); }

      constexpr INLINE bool operator == (const uint16_t& v) const { return TC::Op::eq (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator != (const uint16_t& v) const { return TC::Op::neq(*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator <  (const uint16_t& v) const { return TC::Op::lt (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator <= (const uint16_t& v) const { return TC::Op::lte(*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator >  (const uint16_t& v) const { return TC::Op::gt (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator >= (const uint16_t& v) const { return TC::Op::gte(*thiss(), (uint32_t)v); }

      constexpr INLINE bool operator == (const uint8_t& v) const { return TC::Op::eq (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator != (const uint8_t& v) const { return TC::Op::neq(*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator <  (const uint8_t& v) const { return TC::Op::lt (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator <= (const uint8_t& v) const { return TC::Op::lte(*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator >  (const uint8_t& v) const { return TC::Op::gt (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator >= (const uint8_t& v) const { return TC::Op::gte(*thiss(), (uint32_t)v); }

      constexpr INLINE bool operator == (const int64_t& v) const { return TC::Op::eq (*thiss(), (uint64_t)v); }
      constexpr INLINE bool operator != (const int64_t& v) const { return TC::Op::neq(*thiss(), (uint64_t)v); }
      constexpr INLINE bool operator <  (const int64_t& v) const { return TC::Op::lt (*thiss(), (uint64_t)v); }
      constexpr INLINE bool operator <= (const int64_t& v) const { return TC::Op::lte(*thiss(), (uint64_t)v); }
      constexpr INLINE bool operator >  (const int64_t& v) const { return TC::Op::gt (*thiss(), (uint64_t)v); }
      constexpr INLINE bool operator >= (const int64_t& v) const { return TC::Op::gte(*thiss(), (uint64_t)v); }

      constexpr INLINE bool operator == (const int32_t& v) const { return TC::Op::eq (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator != (const int32_t& v) const { return TC::Op::neq(*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator <  (const int32_t& v) const { return TC::Op::lt (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator <= (const int32_t& v) const { return TC::Op::lte(*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator >  (const int32_t& v) const { return TC::Op::gt (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator >= (const int32_t& v) const { return TC::Op::gte(*thiss(), (uint32_t)v); }

      constexpr INLINE bool operator == (const int16_t& v) const { return TC::Op::eq (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator != (const int16_t& v) const { return TC::Op::neq(*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator <  (const int16_t& v) const { return TC::Op::lt (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator <= (const int16_t& v) const { return TC::Op::lte(*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator >  (const int16_t& v) const { return TC::Op::gt (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator >= (const int16_t& v) const { return TC::Op::gte(*thiss(), (uint32_t)v); }

      constexpr INLINE bool operator == (const int8_t& v) const { return TC::Op::eq (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator != (const int8_t& v) const { return TC::Op::neq(*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator <  (const int8_t& v) const { return TC::Op::lt (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator <= (const int8_t& v) const { return TC::Op::lte(*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator >  (const int8_t& v) const { return TC::Op::gt (*thiss(), (uint32_t)v); }
      constexpr INLINE bool operator >= (const int8_t& v) const { return TC::Op::gte(*thiss(), (uint32_t)v); }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // BINARY OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////

      template<typename UINT>
      constexpr INLINE TC operator | (const UINT& v) const
      {
         TC r;
         TC::Op::_or(*thiss(), v, r);
         return r;
      }

      template<typename UINT>
      constexpr INLINE TC& operator |= (const UINT& v)
      {
         TC::Op::_or(*thiss(), v, *thiss());
         return *thiss();
      }

      template<typename UINT>
      constexpr INLINE TC operator & (const UINT& v) const
      {
         TC r;
         TC::Op::_and(*thiss(), v, r);
         return r;
      }

      template<typename UINT>
      constexpr INLINE TC& operator &= (const UINT& v)
      {
         TC::Op::_and(*thiss(), v, *thiss());
         return *thiss();
      }

      template<typename UINT>
      constexpr INLINE TC operator ^ (const UINT& v) const
      {
         TC r;
         TC::Op::_xor(*thiss(), v, r);
         return r;
      }

      template<typename UINT>
      constexpr INLINE TC& operator ^= (const UINT& v)
      {
         TC::Op::_xor(*thiss(), v, *thiss());
         return *thiss();
      }

      constexpr INLINE TC operator ~ () const
      {
         TC r;
         TC::Op::_not(*thiss(), r);
         return r;
      }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // SHIFT OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////

      constexpr INLINE TC operator << (size_t v) const
      {
         TC r = *thiss();
         TC::Op::shl(r, v);
         return r;
      }

      constexpr INLINE TC& operator <<= (size_t v)
      {
         TC::Op::shl(*thiss(), v);
         return *thiss();
      }

      constexpr INLINE TC operator >> (size_t v) const
      {
         TC r = *thiss();
         TC::Op::shr(r, v);
         return r;
      }

      constexpr INLINE TC& operator >>= (size_t v)
      {
         TC::Op::shr(*thiss(), v);
         return *thiss();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // ARITHMETIC OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Addition Operator (same type)
      /// </summary>
      constexpr INLINE TC operator + (const TC& v) const
      {
         TC r;
         TC::Op::add(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Addition Operator (uint64)
      /// </summary>
      constexpr INLINE TC operator + (const uint64_t& v) const
      {
         TC r;
         TC::Op::add(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Addition Operator (uint32)
      /// </summary>
      constexpr INLINE TC operator + (const uint32_t& v) const
      {
         TC r;
         TC::Op::add(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Addition Operator (int64)
      /// </summary>
      constexpr INLINE TC operator + (const int64_t& v) const { return *thiss() + (const uint64_t&)v; }

      /// <summary>
      /// Addition Operator (int32)
      /// </summary>
      constexpr INLINE TC operator + (const int32_t& v) const { return *thiss() + (const uint32_t&)v; }

      /// <summary>
      /// Addition Compound Assignment Operator (same type)
      /// </summary>
      constexpr INLINE TC& operator += (const TC& v)
      {
         TC::Op::add(*thiss(), v, *thiss());
         return *thiss();
      }

      /// <summary>
      /// Addition Compound Assignment Operator (uint64)
      /// </summary>
      constexpr INLINE TC& operator += (const uint64_t& v)
      {
         TC::Op::add(*thiss(), v, *thiss());
         return *thiss();
      }

      /// <summary>
      /// Addition Compound Assignment Operator (uint32)
      /// </summary>
      constexpr INLINE TC& operator += (const uint32_t& v)
      {
         TC::Op::add(*thiss(), v, *thiss());
         return *thiss();
      }

      /// <summary>
      /// Addition Compound Assignment Operator (int64)
      /// </summary>
      constexpr INLINE TC& operator += (const int64_t& v) { return *thiss() += (const uint64_t&)v; }

      /// <summary>
      /// Addition Compound Assignment Operator (int32)
      /// </summary>
      constexpr INLINE TC& operator += (const int32_t& v) { return *thiss() += (const uint32_t&)v; }

      /// <summary>
      /// Subtraction Operator (same type)
      /// </summary>
      constexpr INLINE TC operator - (const TC& v) const
      {
         TC r;
         TC::Op::sub(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Subtraction Operator (uint64)
      /// </summary>
      constexpr INLINE TC operator - (const uint64_t& v) const
      {
         TC r;
         TC::Op::sub(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Subtraction Operator (uint32)
      /// </summary>
      constexpr INLINE TC operator - (const uint32_t& v) const
      {
         TC r;
         TC::Op::sub(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Subtraction Operator (int64)
      /// </summary>
      constexpr INLINE TC operator - (const int64_t& v) const { return *thiss() - (const uint64_t&)v; }

      /// <Subtraction>
      /// Subtraction Operator (int32)
      /// </summary>
      constexpr INLINE TC operator - (const int32_t& v) const { return *thiss() - (const uint32_t&)v; }

      /// <summary>
      /// Subtraction Compound Assignment Operator (same type)
      /// </summary>
      constexpr INLINE TC& operator -=  (const TC& v)
      {
         TC::Op::sub(*thiss(), v, *thiss());
         return *thiss();
      }

      /// <summary>
      /// Subtraction Compound Assignment Operator (uint64)
      /// </summary>
      constexpr INLINE TC& operator -=  (const uint64_t& v)
      {
         TC::Op::sub(*thiss(), v, *thiss());
         return *thiss();
      }

      /// <summary>
      /// Subtraction Compound Assignment Operator (uint32)
      /// </summary>
      constexpr INLINE TC& operator -=  (const uint32_t& v)
      {
         TC::Op::sub(*thiss(), v, *thiss());
         return *thiss();
      }

      /// <summary>
      /// Subtraction Compound Assignment Operator (int64)
      /// </summary>
      constexpr INLINE TC& operator -= (const int64_t& v) { return *thiss() -= (const uint64_t&)v; }

      /// <summary>
      /// Subtraction Compound Assignment Operator (int32)
      /// </summary>
      constexpr INLINE TC& operator -= (const int32_t& v) { return *thiss() -= (const uint32_t&)v; }

      /// <summary>
      /// Multiplication Operator (same type)
      /// </summary>
      constexpr INLINE TC operator * (const TC& v) const
      {
         TC r;
         TC::Op::mul(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Multiplication Operator (uint64)
      /// </summary>
      constexpr INLINE TC operator * (const uint64_t& v) const
      {
         TC r;
         TC::Op::mul(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Multiplication Operator (uint32)
      /// </summary>
      constexpr INLINE TC operator * (const uint32_t& v) const
      {
         TC r;
         TC::Op::mul(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Multiplication Operator (int64)
      /// </summary>
      constexpr INLINE TC operator * (const int64_t& v) const { return *thiss() * (const uint64_t&)v; }

      /// <Subtraction>
      /// Multiplication Operator (int32)
      /// </summary>
      constexpr INLINE TC operator * (const int32_t& v) const { return *thiss() * (const uint32_t&)v; }

      /// <summary>
      /// Multiplication Compound Assignment Operator (same type)
      /// </summary>
      constexpr INLINE TC& operator *=  (const TC& v)
      {
         // default multiword multiplication requires
         // r to be different than a and b
         TC t(*thiss());
         TC::Op::mul(t, v, *thiss());
         return *thiss();
      }

      /// <summary>
      /// Multiplication Compound Assignment Operator (uint64)
      /// </summary>
      constexpr INLINE TC& operator *=  (const uint64_t& v)
      {
         TC::Op::mul(*thiss(), v, *thiss());
         return *thiss();
      }

      /// <summary>
      /// Multiplication Compound Assignment Operator (uint32)
      /// </summary>
      constexpr INLINE TC& operator *=  (const uint32_t& v)
      {
         TC::Op::mul(*thiss(), v, *thiss());
         return *thiss();
      }

      /// <summary>
      /// Multiplication Compound Assignment Operator (int64)
      /// </summary>
      constexpr INLINE TC& operator *= (const int64_t& v) { return *thiss() *= (const uint64_t&)v; }

      /// <summary>
      /// Multiplication Compound Assignment Operator (int32)
      /// </summary>
      constexpr INLINE TC& operator *= (const int32_t& v) { return *thiss() *= (const uint32_t&)v; }

      /// <summary>
      /// Division Operator (same type)
      /// </summary>
      constexpr INLINE TC operator / (const TC& v) const
      {
         TC r;
         TC::Op::div(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Division Operator (uint32)
      /// </summary>
      constexpr INLINE TC operator / (const uint32_t& v) const
      {
         TC r;
         TC::Op::div(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Division Compound Assignment Operator (same type)
      /// </summary>
      constexpr INLINE TC& operator /=  (const TC& v)
      {
         TC r;
         TC::Op::div(*thiss(), v, r);
         *thiss() = r;
         return *thiss();
      }

      /// <summary>
      /// Division Compound Assignment Operator (uint32)
      /// </summary>
      constexpr INLINE TC& operator /=  (const uint32_t& v)
      {
         TC::Op::div(*thiss(), v, *thiss());
         return *thiss();
      }

      /// <summary>
      /// Modulo Operator (same type)
      /// </summary>
      constexpr INLINE TC operator % (const TC& v) const
      {
         TC r;
         TC::Op::mod(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Modulo Operator (uint32)
      /// </summary>
      constexpr INLINE uint32_t operator % (const uint32_t& v) const
      {
         uint32_t r = 0;
         TC::Op::mod(*thiss(), v, r);
         return r;
      }

      /// <summary>
      /// Modulo Compound Assignment Operator (same type)
      /// </summary>
      constexpr INLINE TC& operator %=  (const TC& v)
      {
         TC r;
         TC::Op::mod(*thiss(), v, r);
         *thiss() = r;
         return *thiss();
      }

      /// <summary>
      /// Modulo Compound Assignment Operator (uint32)
      /// </summary>
      constexpr INLINE TC& operator %=  (const uint32_t& v)
      {
         uint32_t r = 0;
         TC::Op::mod(*thiss(), v, r);
         *thiss() = r;
         return *thiss();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // CAST OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Get low 64 bits
      /// </summary>
      constexpr INLINE explicit operator uint64_t () const { return d.i64[0]; }

      /// <summary>
      /// Get low 32 bits
      /// </summary>
      constexpr INLINE explicit operator uint32_t () const { return d.i32[0]; }

      /// <summary>
      /// Get low 16 bits
      /// </summary>
      constexpr INLINE explicit operator uint16_t () const { return d.i16[0]; }

      /// <summary>
      /// Get low 8 bits
      /// </summary>
      constexpr INLINE explicit operator uint8_t () const { return d.i8[0]; }

      /// <summary>
      /// Convert to IEEE-754 Double Precision
      /// </summary>
      constexpr INLINE explicit operator double () const
      {
         constexpr uint32_t BITS = N8 * 8U;
         constexpr uint32_t LOSS = BITS - 52U;
         const TC LMSK((TC(1U) << LOSS) - 1U);
         const TC LCMP((TC(1U) << (LOSS - 1U)));

         const TC& x = *thiss();
         uint32_t clz = 0U;
         TC man, los;

         if (x == 0) CPPCORE_UNLIKELY
            return 0.0;

         TC::Op::lzcnt(x, clz);
         uint32_t idh = BITS - clz - 1U;

         if (BITS > 1024U && idh > 1024U)
            return std::numeric_limits<double>::infinity();

         uint64_t exp = (uint64_t)(idh + 1023U) << 52;

         man = (x << (clz + 1U));
         los = man & LMSK;
         man >>= LOSS;
         man += ((los > LCMP) || ((los == LCMP) && ((uint32_t)man & 1U)));
         exp |= (uint64_t)man;

         return reinterpret_cast<double&>(exp);
      }

      /// <summary>
      /// Convert to Decimal String
      /// </summary>
      INLINE explicit operator string() const
      {
         return thiss()->toString();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // STRING SERIALIZATION
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns string representation using any alphabet. By default decimal.
      /// Returns empty string if alphabet is invalid (e.g. less than 2 symbols).
      /// </summary>
      INLINE string toString(const string& alphabet = CPPCORE_ALPHABET_B10) const
      {
         const uint32_t b = (uint32_t)alphabet.length();
         string s;
         if (b > 1U)
         {
            TC t(*thiss());
            if (!CppCore::testzero(t))
            {
               uint32_t r;
               while (!CppCore::testzero(t))
               {
                  TC::Op::divmod(t, b, t, r);
                  s += (char)alphabet[r];
               }
            }
            else s = '0';
            std::reverse(std::begin(s), std::end(s));
         }
         return s;
      }

      /// <summary>
      /// Returns a fixed-length, leading zero padded string representation in Hex (Base16). Optimized.
      /// </summary>
      INLINE string toHexString() const
      {
         string s;
         s.resize(N64 * 16U);
      #if defined(CPPCORE_CPU_64BIT)
         CppCore::Hex::tostring(d.i64, s.data(), N64, false);
      #else
         CppCore::Hex::tostring(d.i32, s.data(), N32, false);
      #endif
         return s;
      }

      /// <summary>
      /// Appends the value to a stream based on active base encoding.
      /// </summary>
      INLINE std::ostream& appendToStream(std::ostream& os) const
      {
         const auto& flags = os.flags();
         const auto& v = *thiss();
         os <<
            ((flags & std::ios_base::dec) ? v.toString(CPPCORE_ALPHABET_B10) :
            ( flags & std::ios_base::hex) ? v.toHexString() :
            ( flags & std::ios_base::oct) ? v.toString(CPPCORE_ALPHABET_B08) :
            "UNKNOWN_BASE");
         return os;
      }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // STRING DESERIALIZATION
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Tries to parse integer from string input using any alphabet.
      /// Returns false if (a) empty input (b) invalid symbol or (c) overflow.
      /// </summary>
      constexpr INLINE static bool tryParse(const string& input, TC& r, const string& alphabet = CPPCORE_ALPHABET_B10)
      {
         r = 0ULL;
         const size_t b = alphabet.length();
         const size_t l = input.length();
         if ((b > 1U) && (l > 0))
         {
            struct { TC v; uint64_t of; } t;
            for (size_t i = 0; i < l; i++)
            {
               const char c = input[i];
               const size_t idx = alphabet.find(c, 0);
               if (idx != string::npos)
               {
                  CppCore::umul(r, b, t);
                  if (t.of != 0U) // mul overflow
                     return false;
                  r = t.v;
                  uint8_t carry = 0;
                  CppCore::addcarry(r, idx, r, carry);
                  if (carry != 0) // add overflow
                     return false;
               }
               else // invalid symbol in input
                  return false;
            }
            // success
            return true;
         }
         else // invalid alphabet or empty input
            return false;
      }

      /// <summary>
      /// Parses integer from decimal string.
      /// Unlike tryParse(), it does not support any alphabet and it does not detect 
      /// errors like invalid symbols or overflows. But it's faster!
      /// </summary>
      constexpr INLINE static TC parseDecimal(const char* input)
      {
         TC r(0ULL);
         while(const char c = *input++)
         {
            r *= 10U;
            r += (c - '0');
         }
         return r;
      }

      /// <summary>
      /// Parses integer from hex string.
      /// Unlike tryParse(), it does not support any alphabet and it does not detect 
      /// errors like invalid symbols or overflows. But it's faster!
      /// </summary>
      constexpr INLINE static TC parseHex(const char* input)
      {
         TC r(0ULL);
         while(const char c = *input++)
         {
            r <<= 4;
            r.d.i32[0] |= Hex::Util::valueofhexchar(c);
         }
         return r;
      }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // RANDOM
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Sets all bits to random ones using 
      /// provided pseudo random number generator.
      /// </summary>
      template<typename PRNG = Random::Default64>
      INLINE void randomize(PRNG& prng)
      {
         static_assert(PRNG::GENSIZE == 8U || PRNG::GENSIZE == 4U);
         if constexpr (PRNG::GENSIZE == 8U)
            for (size_t i = 0; i < N64; i++)
               d.i64[i] = (uint64_t)prng.next();
         else
            for (size_t i = 0; i < N32; i++)
               d.i32[i] = (uint32_t)prng.next();
      }

      /// <summary>
      /// Sets all bits to random ones using an on-the-fly 
      /// created default pseudo random number generator.
      /// </summary>
      INLINE void randomize()
      {
      #if defined(CPPCORE_CPU_64BIT)
         Random::Default64 prng;
         thiss()->randomize(prng);
      #else
         Random::Default32 prng;
         thiss()->randomize(prng);
      #endif
      }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // PRIMES
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Like other variant, but with temporary work memory.
      /// </summary>
      INLINE Primes::Result isprime(uint32_t maxidx = 64) const
      {
         Primes::Memory<TC> mem;
         return Primes::isprime(*thiss(), mem, maxidx);
      }

      /// <summary>
      /// Turn into a strong probable prime
      /// </summary>
      template<typename PRNG>
      INLINE void genprime(PRNG& prng, Primes::Memory<TC>& mem, uint32_t maxidx = 64)
      {
         do {
            thiss()->randomize(prng);
            d.i32[0]     |= 0x00000001U;
            d.i32[N32-1] |= 0x80000000U;
         } while (Primes::isprime(*thiss(), mem, maxidx) == Primes::Composite);
      }

      /// <summary>
      /// Turn into a strong probable prime
      /// </summary>
      INLINE void genprime(uint32_t maxidx = 64)
      {
         Primes::Memory<TC> mem;
      #if defined(CPPCORE_CPU_64BIT)
         Random::Default64 prng;
      #else
         Random::Default32 prng;
      #endif
         thiss()->genprime(prng, mem, maxidx);
      }
   };

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Fast uintx_t Implementations
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// uintx_t with SSE
   /// </summary>
   template<typename TC, typename D>
   class uintx_t_sse2 : public uintx_t<TC, D>
   {

   private:
      typedef uintx_t<TC, D> TB;
      using TB::uintx_t;

      static_assert(TB::N64 >= 2U);
      static_assert(TB::N64 % 2U == 0U);

   public:
      using TB::d;
      /*INLINE uintx_t_sse2(const uintx_t_sse2& o)
      {
         Memory::copy128<true>(d.sse, o.d.sse, TC::N128);
      }
      INLINE uintx_t_sse2(const uint64_t v)
      {
         d.sse[0] = _mm_set_epi64x(0ULL, v);
         Memory::clear128<true>(&d.sse[1], TC::N128-1U);
      }
      INLINE uintx_t_sse2(const uint32_t v) : uintx_t_sse2((uint64_t)v) { }
      INLINE uintx_t_sse2(const int64_t  v) : uintx_t_sse2((uint64_t)v) { }
      INLINE uintx_t_sse2(const int32_t  v) : uintx_t_sse2((uint64_t)v) { }
      */
      INLINE void clear()
      {
         Memory::clear128<true>(d.sse, TC::N128);
      }

      class Op : public TB::Op
      {
      private:
         INLINE Op() { }
      public:
         using TB::Op::eq;
         using TB::Op::neq;
         using TB::Op::lt;
         using TB::Op::lte;
         using TB::Op::gt;
         using TB::Op::gte;

         INLINE static bool eq(const TC& a, const TC& b)
         {
            if (!CppCore::equal128(a.d.sse[0], b.d.sse[0]))
               return false;
            return TC::N128 < 2 ? true :
               Memory::equal128o<true>(&a.d.sse[1], &b.d.sse[1], TC::N128-1U);
         }

         INLINE static bool eq(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] != b)
               return false;
            if (a.d.i64[1] != 0ULL)
               return false;
            return TC::N128 < 2 ? true : 
               Memory::testzero128o<true>(&a.d.sse[1], TC::N128-1U);
         }

         INLINE static bool eq(const TC& a, const uint32_t& b)
         {
            return TC::Op::eq(a, (uint64_t)b);
         }

         INLINE static bool neq(const TC& a, const TC& b)
         {
            if (!CppCore::equal128(a.d.sse[0], b.d.sse[0]))
               return true;
            return TC::N128 < 2 ? false :
               !Memory::equal128o(&a.d.sse[1], &b.d.sse[1], TC::N128-1U);
         }

         INLINE static bool neq(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] != b)
               return true;
            if (a.d.i64[1] != 0ULL)
               return true;
            return TC::N128 < 2 ? false : 
               !Memory::testzero128o<true>(&a.d.sse[1], TC::N128-1U);
         }

         INLINE static bool neq(const TC& a, const uint32_t& b)
         {
            return TC::Op::neq(a, (uint64_t)b);
         }

         INLINE static bool lt(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] >= b)
               return false;
            if (a.d.i64[1] != 0ULL)
               return false;
            return TC::N128 < 2 ? true : 
               Memory::testzero128o<true>(&a.d.sse[1], TC::N128-1U);
         }

         INLINE static bool lt(const TC& a, const uint32_t& b)
         {
            return TC::Op::lt(a, (uint64_t)b);
         }

         INLINE static bool lte(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] > b)
               return false;
            if (a.d.i64[1] != 0ULL)
               return false;
            return TC::N128 < 2 ? true : 
               Memory::testzero128o<true>(&a.d.sse[1], TC::N128-1U);
         }

         INLINE static bool lte(const TC& a, const uint32_t& b)
         {
            return TC::Op::lte(a, (uint64_t)b);
         }

         INLINE static bool gt(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] > b)
               return true;
            if (a.d.i64[1] != 0ULL)
               return true;
            return TC::N128 < 2 ? false : 
               !Memory::testzero128o<true>(&a.d.sse[1], TC::N128-1U);
         }

         INLINE static bool gt(const TC& a, const uint32_t& b)
         {
            return TC::Op::gt(a, (uint64_t)b);
         }

         INLINE static bool gte(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] >= b)
               return true;
            if (a.d.i64[1] != 0ULL)
               return true;
            return TC::N128 < 2 ? false : 
               !Memory::testzero128o<true>(&a.d.sse[1], TC::N128-1U);
         }

         INLINE static bool gte(const TC& a, const uint32_t& b)
         {
            return TC::Op::gte(a, (uint64_t)b);
         }

         INLINE static void _or(const TC& a, const TC& b, TC& r)
         {
            for (size_t i = 0; i < TC::N128; i++)
               r.d.sse[i] = _mm_or_si128(a.d.sse[i], b.d.sse[i]);
         }

         INLINE static void _and(const TC & a, const TC & b, TC & r)
         {
            for (size_t i = 0; i < TC::N128; i++)
               r.d.sse[i] = _mm_and_si128(a.d.sse[i], b.d.sse[i]);
         }

         INLINE static void _xor(const TC& a, const TC& b, TC& r)
         {
            for (size_t i = 0; i < TC::N128; i++)
               r.d.sse[i] = _mm_xor_si128(a.d.sse[i], b.d.sse[i]);
         }

         /*INLINE static void shl64x(TC& a, const uint8_t s)
         {
            CppCore::shl64x<true>(a.d.sse, a.d.sse, TC::N128, s);
         }

         INLINE static void shr64x(TC& a, const uint8_t s)
         {
            CppCore::shr64x<true>(a.d.sse, a.d.sse, TC::N128, s);
         }*/
      };
   };
#endif

#if defined(CPPCORE_CPUFEAT_AVX)
   /// <summary>
   /// uintx_t with AVX
   /// </summary>
   template<typename TC, typename D>
   class uintx_t_avx : public uintx_t_sse2<TC, D>
   {
   private:
      typedef uintx_t_sse2<TC, D> TB;
      using TB::uintx_t_sse2;

      static_assert(TB::N64 >= 4U);
      static_assert(TB::N64 % 4U == 0U);

   public:
      using TB::d;

      /*INLINE uintx_t_avx(const uintx_t_avx& o)
      {
         Memory::copy256<true>(d.avx, o.d.avx, TC::N256);
      }
      INLINE uintx_t_avx(const uint64_t v)
      {
         d.avx[0] = _mm256_set_epi64x(0ULL, 0ULL, 0ULL, v);
         Memory::clear256<true>(&d.avx[1], TC::N256-1U);
      }
      INLINE uintx_t_avx(const uint32_t v) : uintx_t_avx((uint64_t)v) { }
      INLINE uintx_t_avx(const int64_t  v) : uintx_t_avx((uint64_t)v) { }
      INLINE uintx_t_avx(const int32_t  v) : uintx_t_avx((uint64_t)v) { }
      */
      INLINE void clear()
      {
         Memory::clear256<true>(d.avx, TC::N256);
      }

      class Op : public TB::Op
      {
      private:
         INLINE Op() { }
      public:
         using TB::Op::eq;
         using TB::Op::neq;
         using TB::Op::lt;
         using TB::Op::lte;
         using TB::Op::gt;
         using TB::Op::gte;

      #if defined(CPPCORE_CPUFEAT_AVX2)
         INLINE static bool eq(const TC& a, const TC& b)
         {
            if (!CppCore::equal256(a.d.avx[0], b.d.avx[0]))
               return false;
            return TC::N256 < 2 ? true :
               Memory::equal256o<true>(&a.d.avx[1], &b.d.avx[1], TC::N256-1U);
         }
      #endif
         INLINE static bool eq(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] != b)
               return false;
            if (a.d.i64[1] != 0ULL)
               return false;
            if (!CppCore::testzero128(a.d.sse[1]))
               return false;
            return TC::N256 < 2 ? true :
               Memory::testzero256o<true>(&a.d.avx[1], TC::N256-1U);
         }

         INLINE static bool neq(const TC& a, const TC& b)
         {
            if (!CppCore::equal256(a.d.avx[0], b.d.avx[0]))
               return true;
            return TC::N256 < 2 ? false :
               !Memory::equal256o<true>(&a.d.avx[1], &b.d.avx[1], TC::N256-1U);
         }

         INLINE static bool neq(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] != b)
               return true;
            if (a.d.i64[1] != 0ULL)
               return true;
            if (!CppCore::testzero128(a.d.sse[1]))
               return true;
            return TC::N256 < 2 ? false : 
               !Memory::testzero256o<true>(&a.d.avx[1], TC::N256-1U);
         }

         INLINE static bool lt(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] >= b)
               return false;
            if (a.d.i64[1] != 0ULL)
               return false;
            if (!Memory::testzero128<true>(&a.d.sse[1], 1U))
               return false;
            return TC::N256 < 2 ? true :
               Memory::testzero256o<true>(&a.d.avx[1], TC::N256-1U);
         }

         INLINE static bool lte(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] > b)
               return false;
            if (a.d.i64[1] != 0ULL)
               return false;
            if (!Memory::testzero128<true>(&a.d.sse[1], 1U))
               return false;
            return TC::N256 < 2 ? true :
               Memory::testzero256o<true>(&a.d.avx[1], TC::N256-1U);
         }

         INLINE static bool gt(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] > b)
               return true;
            if (a.d.i64[1] != 0ULL)
               return true;
            if (!Memory::testzero128<true>(&a.d.sse[1], 1U))
               return true;
            return TC::N256 < 2 ? false :
               !Memory::testzero256o<true>(&a.d.avx[1], TC::N256-1U);
         }

         INLINE static bool gte(const TC& a, const uint64_t& b)
         {
            if (a.d.i64[0] >= b)
               return true;
            if (a.d.i64[1] != 0ULL)
               return true;
            if (!Memory::testzero128<true>(&a.d.sse[1], 1U))
               return true;
            return TC::N256 < 2 ? false :
               !Memory::testzero256o<true>(&a.d.avx[1], TC::N256-1U);
         }

         INLINE static void _or(const TC& a, const TC& b, TC& r)
         {
            for (size_t i = 0; i < TC::N256; i++)
               r.d.avx[i] = _mm256_or_si256(a.d.avx[i], b.d.avx[i]);
         }

         INLINE static void _and(const TC & a, const TC & b, TC & r)
         {
            for (size_t i = 0; i < TC::N256; i++)
               r.d.avx[i] = _mm256_and_si256(a.d.avx[i], b.d.avx[i]);
         }

         INLINE static void _xor(const TC& a, const TC& b, TC& r)
         {
            for (size_t i = 0; i < TC::N256; i++)
               r.d.avx[i] = _mm256_xor_si256(a.d.avx[i], b.d.avx[i]);
         }

         /*INLINE static void shl64x(TC& a, const uint8_t s)
         {
            CppCore::shl64x<true>(a.d.avx, a.d.avx, TC::N256, s);
         }

         INLINE static void shr64x(TC& a, const uint8_t s)
         {
            CppCore::shr64x<true>(a.d.avx, a.d.avx, TC::N256, s);
         }*/
      };
   };
#endif

#if defined(CPPCORE_CPUFEAT_AVX512)
   /// <summary>
   /// uintx_t with AVX512
   /// </summary>
   template<typename TC, typename D>
   class uintx_t_avx512 : public uintx_t_avx<TC, D>
   {
   private:
      typedef uintx_t_avx<TC, D> TB;
      using TB::uintx_t_avx;

      static_assert(TB::N64 >= 8U);
      static_assert(TB::N64 % 8U == 0U);

   public:
      using TB::d;

      /*INLINE uintx_t_avx512(const uintx_t_avx512& o)
      {
         Memory::copy512<true>(d.avx512, o.d.avx512, TC::N512);
      }
      INLINE uintx_t_avx512(const uint64_t v)
      {
         d.avx512[0] = _mm512_set_epi64(0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, v);
         Memory::clear512<true>(&d.avx512[1], TC::N512-1U);
      }
      INLINE uintx_t_avx512(const uint32_t v) : uintx_t_avx512((uint64_t)v) { }
      INLINE uintx_t_avx512(const int64_t  v) : uintx_t_avx512((uint64_t)v) { }
      INLINE uintx_t_avx512(const int32_t  v) : uintx_t_avx512((uint64_t)v) { }
      */
      INLINE void clear()
      {
         Memory::clear512<true>(d.avx512, TC::N512);
      }

      class Op : public TB::Op
      {
      private:
         INLINE Op() { }
      public:
         /*INLINE static bool eq(const TC& a, const TC& b)
         {
            return Memory::equal512(a.d.avx512, b.d.avx512, TC::N512);
         }*/
         INLINE static void _or(const TC& a, const TC& b, TC& r)
         {
            for (size_t i = 0; i < TC::N512; i++)
               r.d.avx512[i] = _mm512_or_si512(a.d.avx512[i], b.d.avx512[i]);
         }
         INLINE static void _and(const TC & a, const TC & b, TC & r)
         {
            for (size_t i = 0; i < TC::N512; i++)
               r.d.avx512[i] = _mm512_and_si512(a.d.avx512[i], b.d.avx512[i]);
         }
         INLINE static void _xor(const TC& a, const TC& b, TC& r)
         {
            for (size_t i = 0; i < TC::N512; i++)
               r.d.avx512[i] = _mm512_xor_si512(a.d.avx512[i], b.d.avx512[i]);
         }
      };
   };
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // FIXED LENGTH BASE CLASSES
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   // GENERIC
   using uint128_bg  = uintx_t<uint128_tg,  uint128_tgd>;
   using uint256_bg  = uintx_t<uint256_tg,  uint256_tgd>;
   using uint512_bg  = uintx_t<uint512_tg,  uint512_tgd>;
   using uint1024_bg = uintx_t<uint1024_tg, uint1024_tgd>;
   using uint2048_bg = uintx_t<uint2048_tg, uint2048_tgd>;

   // OPTIMIZED
#if defined(CPPCORE_CPUFEAT_AVX512) && defined(CPPCORE_CPUFEAT_AVX) && defined(CPPCORE_CPUFEAT_SSE2)
   using uint128_bs  = uintx_t_sse2  <uint128_ts,  uint128_tsd>;
   using uint256_bs  = uintx_t_avx   <uint256_ts,  uint256_tsd>;
   using uint512_bs  = uintx_t_avx512<uint512_ts,  uint512_tsd>;
   using uint1024_bs = uintx_t_avx512<uint1024_ts, uint1024_tsd>;
   using uint2048_bs = uintx_t_avx512<uint2048_ts, uint2048_tsd>;
#elif defined(CPPCORE_CPUFEAT_AVX) && defined(CPPCORE_CPUFEAT_SSE2)
   using uint128_bs  = uintx_t_sse2<uint128_ts,  uint128_tsd>;
   using uint256_bs  = uintx_t_avx <uint256_ts,  uint256_tsd>;
   using uint512_bs  = uintx_t_avx <uint512_ts,  uint512_tsd>;
   using uint1024_bs = uintx_t_avx <uint1024_ts, uint1024_tsd>;
   using uint2048_bs = uintx_t_avx <uint2048_ts, uint2048_tsd>;
#elif defined(CPPCORE_CPUFEAT_SSE2)
   using uint128_bs  = uintx_t_sse2<uint128_ts,  uint128_tsd>;
   using uint256_bs  = uintx_t_sse2<uint256_ts,  uint256_tsd>;
   using uint512_bs  = uintx_t_sse2<uint512_ts,  uint512_tsd>;
   using uint1024_bs = uintx_t_sse2<uint1024_ts, uint1024_tsd>;
   using uint2048_bs = uintx_t_sse2<uint2048_ts, uint2048_tsd>;
#else
   using uint128_bs  = uintx_t<uint128_ts,  uint128_tsd>;
   using uint256_bs  = uintx_t<uint256_ts,  uint256_tsd>;
   using uint512_bs  = uintx_t<uint512_ts,  uint512_tsd>;
   using uint1024_bs = uintx_t<uint1024_ts, uint1024_tsd>;
   using uint2048_bs = uintx_t<uint2048_ts, uint2048_tsd>;
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // UINT128
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Unsigned 128-Bit Integer (Generic)
   /// </summary>
   class CPPCORE_ALIGN16 uint128_tg : public uint128_bg
   {
   public:
      using uint128_bg::uint128_bg;
      INLINE uint128_tg(const uint64_t l, const uint64_t h = 0ULL) : uint128_bg(uint128_tgd(l, h)) { }
   };

   INLINE bool operator == (const uint64_t a, const uint128_tg& b) { return b == a; }
   INLINE bool operator != (const uint64_t a, const uint128_tg& b) { return b != a; }
   INLINE bool operator <  (const uint64_t a, const uint128_tg& b) { return uint128_tg(a).operator< (b); }
   INLINE bool operator <= (const uint64_t a, const uint128_tg& b) { return uint128_tg(a).operator<=(b); }
   INLINE bool operator >  (const uint64_t a, const uint128_tg& b) { return uint128_tg(a).operator> (b); }
   INLINE bool operator >= (const uint64_t a, const uint128_tg& b) { return uint128_tg(a).operator>=(b); }

   INLINE uint128_tg    operator |  (const uint64_t a, const uint128_tg& b) { return b | a; }
   INLINE uint128_tg    operator &  (const uint64_t a, const uint128_tg& b) { return b & a; }
   INLINE uint128_tg    operator ^  (const uint64_t a, const uint128_tg& b) { return b ^ a; }
   INLINE uint128_tg    operator +  (const uint64_t a, const uint128_tg& b) { return b + a; }
   INLINE uint128_tg    operator -  (const uint64_t a, const uint128_tg& b) { return uint128_tg(a) - b; }
   INLINE uint128_tg    operator *  (const uint64_t a, const uint128_tg& b) { return b * a; }
   INLINE uint128_tg    operator /  (const uint64_t a, const uint128_tg& b) { return uint128_tg(a) / b; }
   INLINE uint128_tg    operator %  (const uint64_t a, const uint128_tg& b) { return uint128_tg(a) % b; }
   INLINE std::ostream& operator << (std::ostream& os, const uint128_tg& v) { return v.appendToStream(os); }

   template<> INLINE void umul(const uint64_t& a, const uint64_t& b, uint128_tg& r)
   {
      CppCore::umul128(a, b, r.d.l, r.d.h);
   }
   template<> INLINE void umul(const uint128_tg& a, const uint128_tg& b, uint128_tg& r)
   {
      CppCore::umul128(a.d.l, a.d.h, b.d.l, b.d.h, r.d.l, r.d.h);
   }

#if defined(CPPCORE_CPU_X64)
   template<> INLINE void umod(uint64_t& r, const uint128_tg& u, const uint64_t& v, uint128_tg mem[3])
   {
      r = CppCore::umod128_64x(u.d.i64, v, uint128_tg::N64);
   }
#endif

   template<> INLINE void umod(uint32_t& r, const uint128_tg& u, const uint32_t& v, uint128_tg mem[3])
   {
   #if defined(CPPCORE_CPU_X64)
      r = (uint32_t)CppCore::umod128_64x(u.d.i64, (uint64_t)v, uint128_tg::N64);
   #else
      r = CppCore::umod64_32x(u.d.i32, v, uint128_tg::N32);
   #endif
   }

   /// <summary>
   /// Unsigned 128-Bit Integer (SIMD/Optimized)
   /// </summary>
   class CPPCORE_ALIGN16 uint128_ts : public uint128_bs
   {
   public:
      using uint128_bs::uint128_bs;
      INLINE uint128_ts(const uint64_t l, const uint64_t h = 0ULL) : uint128_bs(uint128_tsd(l, h)) { }
   #if defined(CPPCORE_CPUFEAT_SSE2)
      INLINE uint128_ts(const __m128i& other) : uint128_bs(uint128_tsd(other)) { }
      INLINE operator const __m128i&() const { return d.sse0; }
   #endif
   };

   INLINE bool operator == (const uint64_t a, const uint128_ts& b) { return b == a; }
   INLINE bool operator != (const uint64_t a, const uint128_ts& b) { return b != a; }
   INLINE bool operator <  (const uint64_t a, const uint128_ts& b) { return uint128_ts(a).operator< (b); }
   INLINE bool operator <= (const uint64_t a, const uint128_ts& b) { return uint128_ts(a).operator<=(b); }
   INLINE bool operator >  (const uint64_t a, const uint128_ts& b) { return uint128_ts(a).operator> (b); }
   INLINE bool operator >= (const uint64_t a, const uint128_ts& b) { return uint128_ts(a).operator>=(b); }

   INLINE uint128_ts    operator |  (const uint64_t a, const uint128_ts& b) { return b | a; }
   INLINE uint128_ts    operator &  (const uint64_t a, const uint128_ts& b) { return b & a; }
   INLINE uint128_ts    operator ^  (const uint64_t a, const uint128_ts& b) { return b ^ a; }
   INLINE uint128_ts    operator +  (const uint64_t a, const uint128_ts& b) { return b + a; }
   INLINE uint128_ts    operator -  (const uint64_t a, const uint128_ts& b) { return uint128_ts(a) - b; }
   INLINE uint128_ts    operator *  (const uint64_t a, const uint128_ts& b) { return b * a; }
   INLINE uint128_ts    operator /  (const uint64_t a, const uint128_ts& b) { return uint128_ts(a) / b; }
   INLINE uint128_ts    operator %  (const uint64_t a, const uint128_ts& b) { return uint128_ts(a) % b; }
   INLINE std::ostream& operator << (std::ostream& os, const uint128_ts& v) { return v.appendToStream(os); }

   template<> INLINE void umul(const uint64_t& a, const uint64_t& b, uint128_ts& r)
   {
      CppCore::umul128(a, b, r.d.l, r.d.h);
   }
   template<> INLINE void umul(const uint128_ts& a, const uint128_ts& b, uint128_ts& r)
   {
      CppCore::umul128(a.d.l, a.d.h, b.d.l, b.d.h, r.d.l, r.d.h);
   }

#if defined(CPPCORE_CPU_X64)
   template<> INLINE void umod(uint64_t& r, const uint128_ts& u, const uint64_t& v, uint128_ts mem[3])
   {
      r = CppCore::umod128_64x(u.d.i64, v, uint128_ts::N64);
   }
#endif

   template<> INLINE void umod(uint32_t& r, const uint128_ts& u, const uint32_t& v, uint128_ts mem[3])
   {
   #if defined(CPPCORE_CPU_X64)
      r = (uint32_t)CppCore::umod128_64x(u.d.i64, (uint64_t)v, uint128_ts::N64);
   #else
      r = CppCore::umod64_32x(u.d.i32, v, uint128_ts::N32);
   #endif
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // UINT256
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Unsigned 256-Bit Integer (Generic)
   /// </summary>
   class CPPCORE_ALIGN32 uint256_tg : public uint256_bg
   {
   public:
      using uint256_bg::uint256_bg;
      INLINE uint256_tg(const uint128_tg& l, const uint128_tg& h = 0ULL) : uint256_bg(uint256_tgd(l, h)) { }
      INLINE uint256_tg(const uint64_t v1, const uint64_t v2 = 0, const uint64_t v3 = 0, const uint64_t v4 = 0) : uint256_bg(uint256_tgd(v1, v2, v3, v4)) { }
      INLINE explicit operator const uint128_tg& () const { return d.i128[0]; }
   };

   INLINE bool operator == (const uint64_t a, const uint256_tg& b) { return b == a; }
   INLINE bool operator != (const uint64_t a, const uint256_tg& b) { return b != a; }
   INLINE bool operator <  (const uint64_t a, const uint256_tg& b) { return uint256_tg(a).operator< (b); }
   INLINE bool operator <= (const uint64_t a, const uint256_tg& b) { return uint256_tg(a).operator<=(b); }
   INLINE bool operator >  (const uint64_t a, const uint256_tg& b) { return uint256_tg(a).operator> (b); }
   INLINE bool operator >= (const uint64_t a, const uint256_tg& b) { return uint256_tg(a).operator>=(b); }

   INLINE uint256_tg    operator |  (const uint64_t a, const uint256_tg& b) { return b | a; }
   INLINE uint256_tg    operator &  (const uint64_t a, const uint256_tg& b) { return b & a; }
   INLINE uint256_tg    operator ^  (const uint64_t a, const uint256_tg& b) { return b ^ a; }
   INLINE uint256_tg    operator +  (const uint64_t a, const uint256_tg& b) { return b + a; }
   INLINE uint256_tg    operator -  (const uint64_t a, const uint256_tg& b) { return uint256_tg(a) - b; }
   INLINE uint256_tg    operator *  (const uint64_t a, const uint256_tg& b) { return b * a; }
   INLINE uint256_tg    operator /  (const uint64_t a, const uint256_tg& b) { return uint256_tg(a) / b; }
   INLINE uint256_tg    operator %  (const uint64_t a, const uint256_tg& b) { return uint256_tg(a) % b; }
   INLINE std::ostream& operator << (std::ostream& os, const uint256_tg& v) { return v.appendToStream(os); }

   /// <summary>
   /// Unsigned 256-Bit Integer (SIMD/Optimized)
   /// </summary>
   class CPPCORE_ALIGN32 uint256_ts : public uint256_bs
   {
   public:
      using uint256_bs::uint256_bs;
      INLINE uint256_ts(const uint128_ts& l, const uint128_ts& h = 0ULL) : uint256_bs(uint256_tsd(l, h)) { }
      INLINE uint256_ts(const uint64_t v1, const uint64_t v2 = 0, const uint64_t v3 = 0, const uint64_t v4 = 0) :
         uint256_bs(uint256_tsd(v1, v2, v3, v4)) { }
   #if defined(CPPCORE_CPUFEAT_AVX)
      INLINE uint256_ts(const __m256i& other) : uint256_bs(uint256_tsd(other)) { }
      INLINE operator const __m256i&() const { return d.avx0; }
   #endif
      INLINE explicit operator const uint128_ts& () const { return d.i128[0]; }
   };

   INLINE bool operator == (const uint64_t a, const uint256_ts& b) { return b == a; }
   INLINE bool operator != (const uint64_t a, const uint256_ts& b) { return b != a; }
   INLINE bool operator <  (const uint64_t a, const uint256_ts& b) { return uint256_ts(a).operator< (b); }
   INLINE bool operator <= (const uint64_t a, const uint256_ts& b) { return uint256_ts(a).operator<=(b); }
   INLINE bool operator >  (const uint64_t a, const uint256_ts& b) { return uint256_ts(a).operator> (b); }
   INLINE bool operator >= (const uint64_t a, const uint256_ts& b) { return uint256_ts(a).operator>=(b); }

   INLINE uint256_ts    operator |  (const uint64_t a, const uint256_ts& b) { return b | a; }
   INLINE uint256_ts    operator &  (const uint64_t a, const uint256_ts& b) { return b & a; }
   INLINE uint256_ts    operator ^  (const uint64_t a, const uint256_ts& b) { return b ^ a; }
   INLINE uint256_ts    operator +  (const uint64_t a, const uint256_ts& b) { return b + a; }
   INLINE uint256_ts    operator -  (const uint64_t a, const uint256_ts& b) { return uint256_ts(a) - b; }
   INLINE uint256_ts    operator *  (const uint64_t a, const uint256_ts& b) { return b * a; }
   INLINE uint256_ts    operator /  (const uint64_t a, const uint256_ts& b) { return uint256_ts(a) / b; }
   INLINE uint256_ts    operator %  (const uint64_t a, const uint256_ts& b) { return uint256_ts(a) % b; }
   INLINE std::ostream& operator << (std::ostream& os, const uint256_ts& v) { return v.appendToStream(os); }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // UINT512
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Unsigned 512-Bit Integer (Generic)
   /// </summary>
   class CPPCORE_ALIGN64 uint512_tg : public uint512_bg
   {
   public:
      using uint512_bg::uint512_bg;
      INLINE uint512_tg(const uint256_tg& l, const uint256_tg& h = 0ULL) : uint512_bg(uint512_tgd(l, h)) { }
      INLINE uint512_tg(
         const uint64_t v1,     const uint64_t v2 = 0, const uint64_t v3 = 0, const uint64_t v4 = 0, 
         const uint64_t v5 = 0, const uint64_t v6 = 0, const uint64_t v7 = 0, const uint64_t v8 = 0) : 
         uint512_bg(uint512_tgd(v1, v2, v3, v4, v5, v6, v7, v8)) { }
      INLINE explicit operator const uint128_tg& () const { return d.i128[0]; }
      INLINE explicit operator const uint256_tg& () const { return d.i256[0]; }
   };

   INLINE bool operator == (const uint64_t a, const uint512_tg& b) { return b == a; }
   INLINE bool operator != (const uint64_t a, const uint512_tg& b) { return b != a; }
   INLINE bool operator <  (const uint64_t a, const uint512_tg& b) { return uint512_tg(a).operator< (b); }
   INLINE bool operator <= (const uint64_t a, const uint512_tg& b) { return uint512_tg(a).operator<=(b); }
   INLINE bool operator >  (const uint64_t a, const uint512_tg& b) { return uint512_tg(a).operator> (b); }
   INLINE bool operator >= (const uint64_t a, const uint512_tg& b) { return uint512_tg(a).operator>=(b); }

   INLINE uint512_tg    operator |  (const uint64_t a, const uint512_tg& b) { return b | a; }
   INLINE uint512_tg    operator &  (const uint64_t a, const uint512_tg& b) { return b & a; }
   INLINE uint512_tg    operator ^  (const uint64_t a, const uint512_tg& b) { return b ^ a; }
   INLINE uint512_tg    operator +  (const uint64_t a, const uint512_tg& b) { return b + a; }
   INLINE uint512_tg    operator -  (const uint64_t a, const uint512_tg& b) { return uint512_tg(a) - b; }
   INLINE uint512_tg    operator *  (const uint64_t a, const uint512_tg& b) { return b * a; }
   INLINE uint512_tg    operator /  (const uint64_t a, const uint512_tg& b) { return uint512_tg(a) / b; }
   INLINE uint512_tg    operator %  (const uint64_t a, const uint512_tg& b) { return uint512_tg(a) % b; }
   INLINE std::ostream& operator << (std::ostream& os, const uint512_tg& v) { return v.appendToStream(os); }

   /// <summary>
   /// Unsigned 512-Bit Integer (SIMD/Optimized)
   /// </summary>
   class CPPCORE_ALIGN64 uint512_ts : public uint512_bs
   {
   public:
      using uint512_bs::uint512_bs;
      INLINE uint512_ts(const uint256_ts& l, const uint256_ts& h = 0ULL) : uint512_bs(uint512_tsd(l, h)) { }
      INLINE uint512_ts(
         const uint64_t v1,     const uint64_t v2 = 0, const uint64_t v3 = 0, const uint64_t v4 = 0, 
         const uint64_t v5 = 0, const uint64_t v6 = 0, const uint64_t v7 = 0, const uint64_t v8 = 0) :
         uint512_bs(uint512_tsd(v1, v2, v3, v4, v5, v6, v7, v8)) { }
   #if defined(CPPCORE_CPUFEAT_AVX512)
      INLINE uint512_ts(const __m512i& other) : uint512_bs(uint512_tsd(other)) { }
      INLINE operator const __m512i&() const { return d.avx5120; }
   #endif
      INLINE explicit operator const uint128_ts& () const { return d.i128[0]; }
      INLINE explicit operator const uint256_ts& () const { return d.i256[0]; }
   };

   INLINE bool operator == (const uint64_t a, const uint512_ts& b) { return b == a; }
   INLINE bool operator != (const uint64_t a, const uint512_ts& b) { return b != a; }
   INLINE bool operator <  (const uint64_t a, const uint512_ts& b) { return uint512_ts(a).operator< (b); }
   INLINE bool operator <= (const uint64_t a, const uint512_ts& b) { return uint512_ts(a).operator<=(b); }
   INLINE bool operator >  (const uint64_t a, const uint512_ts& b) { return uint512_ts(a).operator> (b); }
   INLINE bool operator >= (const uint64_t a, const uint512_ts& b) { return uint512_ts(a).operator>=(b); }

   INLINE uint512_ts    operator |  (const uint64_t a, const uint512_ts& b) { return b | a; }
   INLINE uint512_ts    operator &  (const uint64_t a, const uint512_ts& b) { return b & a; }
   INLINE uint512_ts    operator ^  (const uint64_t a, const uint512_ts& b) { return b ^ a; }
   INLINE uint512_ts    operator +  (const uint64_t a, const uint512_ts& b) { return b + a; }
   INLINE uint512_ts    operator -  (const uint64_t a, const uint512_ts& b) { return uint512_ts(a) - b; }
   INLINE uint512_ts    operator *  (const uint64_t a, const uint512_ts& b) { return b * a; }
   INLINE uint512_ts    operator /  (const uint64_t a, const uint512_ts& b) { return uint512_ts(a) / b; }
   INLINE uint512_ts    operator %  (const uint64_t a, const uint512_ts& b) { return uint512_ts(a) % b; }
   INLINE std::ostream& operator << (std::ostream& os, const uint512_ts& v) { return v.appendToStream(os); }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // UINT1024
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Unsigned 1024-Bit Integer (Generic)
   /// </summary>
   class CPPCORE_ALIGN64 uint1024_tg : public uint1024_bg
   {
   public:
      using uint1024_bg::uint1024_bg;
      INLINE uint1024_tg(const uint512_tg& l, const uint512_tg& h = 0ULL) : uint1024_bg(uint1024_tgd(l, h)) { }
      INLINE uint1024_tg(
         const uint64_t v1,      const uint64_t v2  = 0, const uint64_t v3  = 0, const uint64_t v4  = 0, 
         const uint64_t v5  = 0, const uint64_t v6  = 0, const uint64_t v7  = 0, const uint64_t v8  = 0,
         const uint64_t v9  = 0, const uint64_t v10 = 0, const uint64_t v11 = 0, const uint64_t v12 = 0, 
         const uint64_t v13 = 0, const uint64_t v14 = 0, const uint64_t v15 = 0, const uint64_t v16 = 0) : 
         uint1024_bg(uint1024_tgd(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16)) { }
      INLINE explicit operator const uint128_tg& () const { return d.i128[0]; }
      INLINE explicit operator const uint256_tg& () const { return d.i256[0]; }
      INLINE explicit operator const uint512_tg& () const { return d.i512[0]; }
   };

   INLINE bool operator == (const uint64_t a, const uint1024_tg& b) { return b == a; }
   INLINE bool operator != (const uint64_t a, const uint1024_tg& b) { return b != a; }
   INLINE bool operator <  (const uint64_t a, const uint1024_tg& b) { return uint1024_tg(a).operator< (b); }
   INLINE bool operator <= (const uint64_t a, const uint1024_tg& b) { return uint1024_tg(a).operator<=(b); }
   INLINE bool operator >  (const uint64_t a, const uint1024_tg& b) { return uint1024_tg(a).operator> (b); }
   INLINE bool operator >= (const uint64_t a, const uint1024_tg& b) { return uint1024_tg(a).operator>=(b); }

   INLINE uint1024_tg    operator |  (const uint64_t a, const uint1024_tg& b) { return b | a; }
   INLINE uint1024_tg    operator &  (const uint64_t a, const uint1024_tg& b) { return b & a; }
   INLINE uint1024_tg    operator ^  (const uint64_t a, const uint1024_tg& b) { return b ^ a; }
   INLINE uint1024_tg    operator +  (const uint64_t a, const uint1024_tg& b) { return b + a; }
   INLINE uint1024_tg    operator -  (const uint64_t a, const uint1024_tg& b) { return uint1024_tg(a) - b; }
   INLINE uint1024_tg    operator *  (const uint64_t a, const uint1024_tg& b) { return b * a; }
   INLINE uint1024_tg    operator /  (const uint64_t a, const uint1024_tg& b) { return uint1024_tg(a) / b; }
   INLINE uint1024_tg    operator %  (const uint64_t a, const uint1024_tg& b) { return uint1024_tg(a) % b; }
   INLINE std::ostream& operator << (std::ostream& os, const uint1024_tg& v) { return v.appendToStream(os); }

   /// <summary>
   /// Unsigned 1024-Bit Integer (SIMD/Optimized)
   /// </summary>
   class CPPCORE_ALIGN64 uint1024_ts : public uint1024_bs
   {
   public:
      using uint1024_bs::uint1024_bs;
      INLINE uint1024_ts(const uint512_ts& l, const uint512_ts& h = 0ULL) : uint1024_bs(uint1024_tsd(l, h)) { }
      INLINE uint1024_ts(
         const uint64_t v1,      const uint64_t v2  = 0, const uint64_t v3  = 0, const uint64_t v4  = 0, 
         const uint64_t v5  = 0, const uint64_t v6  = 0, const uint64_t v7  = 0, const uint64_t v8  = 0,
         const uint64_t v9  = 0, const uint64_t v10 = 0, const uint64_t v11 = 0, const uint64_t v12 = 0, 
         const uint64_t v13 = 0, const uint64_t v14 = 0, const uint64_t v15 = 0, const uint64_t v16 = 0) :
         uint1024_bs(uint1024_tsd(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16)) { }
      INLINE explicit operator const uint128_ts& () const { return d.i128[0]; }
      INLINE explicit operator const uint256_ts& () const { return d.i256[0]; }
      INLINE explicit operator const uint512_ts& () const { return d.i512[0]; }
   };

   INLINE bool operator == (const uint64_t a, const uint1024_ts& b) { return b == a; }
   INLINE bool operator != (const uint64_t a, const uint1024_ts& b) { return b != a; }
   INLINE bool operator <  (const uint64_t a, const uint1024_ts& b) { return uint1024_ts(a).operator< (b); }
   INLINE bool operator <= (const uint64_t a, const uint1024_ts& b) { return uint1024_ts(a).operator<=(b); }
   INLINE bool operator >  (const uint64_t a, const uint1024_ts& b) { return uint1024_ts(a).operator> (b); }
   INLINE bool operator >= (const uint64_t a, const uint1024_ts& b) { return uint1024_ts(a).operator>=(b); }

   INLINE uint1024_ts    operator |  (const uint64_t a, const uint1024_ts& b) { return b | a; }
   INLINE uint1024_ts    operator &  (const uint64_t a, const uint1024_ts& b) { return b & a; }
   INLINE uint1024_ts    operator ^  (const uint64_t a, const uint1024_ts& b) { return b ^ a; }
   INLINE uint1024_ts    operator +  (const uint64_t a, const uint1024_ts& b) { return b + a; }
   INLINE uint1024_ts    operator -  (const uint64_t a, const uint1024_ts& b) { return uint1024_ts(a) - b; }
   INLINE uint1024_ts    operator *  (const uint64_t a, const uint1024_ts& b) { return b * a; }
   INLINE uint1024_ts    operator /  (const uint64_t a, const uint1024_ts& b) { return uint1024_ts(a) / b; }
   INLINE uint1024_ts    operator %  (const uint64_t a, const uint1024_ts& b) { return uint1024_ts(a) % b; }
   INLINE std::ostream& operator << (std::ostream& os, const uint1024_ts& v) { return v.appendToStream(os); }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // UINT2048
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Unsigned 2048-Bit Integer (Generic)
   /// </summary>
   class CPPCORE_ALIGN64 uint2048_tg : public uint2048_bg
   {
   public:
      using uint2048_bg::uint2048_bg;
      INLINE uint2048_tg(const uint1024_tg& l, const uint1024_tg& h = 0ULL) : uint2048_bg(uint2048_tgd(l, h)) { }
      INLINE uint2048_tg(
         const uint64_t v1,      const uint64_t v2  = 0, const uint64_t v3  = 0, const uint64_t v4  = 0, 
         const uint64_t v5  = 0, const uint64_t v6  = 0, const uint64_t v7  = 0, const uint64_t v8  = 0,
         const uint64_t v9  = 0, const uint64_t v10 = 0, const uint64_t v11 = 0, const uint64_t v12 = 0, 
         const uint64_t v13 = 0, const uint64_t v14 = 0, const uint64_t v15 = 0, const uint64_t v16 = 0,
         const uint64_t v17 = 0, const uint64_t v18 = 0, const uint64_t v19 = 0, const uint64_t v20 = 0,
         const uint64_t v21 = 0, const uint64_t v22 = 0, const uint64_t v23 = 0, const uint64_t v24 = 0,
         const uint64_t v25 = 0, const uint64_t v26 = 0, const uint64_t v27 = 0, const uint64_t v28 = 0,
         const uint64_t v29 = 0, const uint64_t v30 = 0, const uint64_t v31 = 0, const uint64_t v32 = 0) :
         uint2048_bg(uint2048_tgd(
            v1, v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16,
            v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32)) { }
      INLINE explicit operator const uint128_tg& () const { return d.i128[0]; }
      INLINE explicit operator const uint256_tg& () const { return d.i256[0]; }
      INLINE explicit operator const uint512_tg& () const { return d.i512[0]; }
      INLINE explicit operator const uint1024_tg& () const { return d.i1024[0]; }
   };

   INLINE bool operator == (const uint64_t a, const uint2048_tg& b) { return b == a; }
   INLINE bool operator != (const uint64_t a, const uint2048_tg& b) { return b != a; }
   INLINE bool operator <  (const uint64_t a, const uint2048_tg& b) { return uint2048_tg(a).operator< (b); }
   INLINE bool operator <= (const uint64_t a, const uint2048_tg& b) { return uint2048_tg(a).operator<=(b); }
   INLINE bool operator >  (const uint64_t a, const uint2048_tg& b) { return uint2048_tg(a).operator> (b); }
   INLINE bool operator >= (const uint64_t a, const uint2048_tg& b) { return uint2048_tg(a).operator>=(b); }

   INLINE uint2048_tg    operator |  (const uint64_t a, const uint2048_tg& b) { return b | a; }
   INLINE uint2048_tg    operator &  (const uint64_t a, const uint2048_tg& b) { return b & a; }
   INLINE uint2048_tg    operator ^  (const uint64_t a, const uint2048_tg& b) { return b ^ a; }
   INLINE uint2048_tg    operator +  (const uint64_t a, const uint2048_tg& b) { return b + a; }
   INLINE uint2048_tg    operator -  (const uint64_t a, const uint2048_tg& b) { return uint2048_tg(a) - b; }
   INLINE uint2048_tg    operator *  (const uint64_t a, const uint2048_tg& b) { return b * a; }
   INLINE uint2048_tg    operator /  (const uint64_t a, const uint2048_tg& b) { return uint2048_tg(a) / b; }
   INLINE uint2048_tg    operator %  (const uint64_t a, const uint2048_tg& b) { return uint2048_tg(a) % b; }
   INLINE std::ostream& operator << (std::ostream& os, const uint2048_tg& v) { return v.appendToStream(os); }

   /// <summary>
   /// Unsigned 2048-Bit Integer (SIMD/Optimized)
   /// </summary>
   class CPPCORE_ALIGN64 uint2048_ts : public uint2048_bs
   {
   public:
      using uint2048_bs::uint2048_bs;
      INLINE uint2048_ts(const uint1024_ts& l, const uint1024_ts& h = 0ULL) : uint2048_bs(uint2048_tsd(l, h)) { }
      INLINE uint2048_ts(
         const uint64_t v1,      const uint64_t v2  = 0, const uint64_t v3  = 0, const uint64_t v4  = 0, 
         const uint64_t v5  = 0, const uint64_t v6  = 0, const uint64_t v7  = 0, const uint64_t v8  = 0,
         const uint64_t v9  = 0, const uint64_t v10 = 0, const uint64_t v11 = 0, const uint64_t v12 = 0, 
         const uint64_t v13 = 0, const uint64_t v14 = 0, const uint64_t v15 = 0, const uint64_t v16 = 0,
         const uint64_t v17 = 0, const uint64_t v18 = 0, const uint64_t v19 = 0, const uint64_t v20 = 0,
         const uint64_t v21 = 0, const uint64_t v22 = 0, const uint64_t v23 = 0, const uint64_t v24 = 0,
         const uint64_t v25 = 0, const uint64_t v26 = 0, const uint64_t v27 = 0, const uint64_t v28 = 0,
         const uint64_t v29 = 0, const uint64_t v30 = 0, const uint64_t v31 = 0, const uint64_t v32 = 0) : 
         uint2048_bs(uint2048_tsd(
            v1, v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16,
            v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32)) { }
      INLINE explicit operator const uint128_ts& () const { return d.i128[0]; }
      INLINE explicit operator const uint256_ts& () const { return d.i256[0]; }
      INLINE explicit operator const uint512_ts& () const { return d.i512[0]; }
      INLINE explicit operator const uint1024_ts& () const { return d.i1024[0]; }
   };

   INLINE bool operator == (const uint64_t a, const uint2048_ts& b) { return b == a; }
   INLINE bool operator != (const uint64_t a, const uint2048_ts& b) { return b != a; }
   INLINE bool operator <  (const uint64_t a, const uint2048_ts& b) { return uint2048_ts(a).operator< (b); }
   INLINE bool operator <= (const uint64_t a, const uint2048_ts& b) { return uint2048_ts(a).operator<=(b); }
   INLINE bool operator >  (const uint64_t a, const uint2048_ts& b) { return uint2048_ts(a).operator> (b); }
   INLINE bool operator >= (const uint64_t a, const uint2048_ts& b) { return uint2048_ts(a).operator>=(b); }

   INLINE uint2048_ts    operator |  (const uint64_t a, const uint2048_ts& b) { return b | a; }
   INLINE uint2048_ts    operator &  (const uint64_t a, const uint2048_ts& b) { return b & a; }
   INLINE uint2048_ts    operator ^  (const uint64_t a, const uint2048_ts& b) { return b ^ a; }
   INLINE uint2048_ts    operator +  (const uint64_t a, const uint2048_ts& b) { return b + a; }
   INLINE uint2048_ts    operator -  (const uint64_t a, const uint2048_ts& b) { return uint2048_ts(a) - b; }
   INLINE uint2048_ts    operator *  (const uint64_t a, const uint2048_ts& b) { return b * a; }
   INLINE uint2048_ts    operator /  (const uint64_t a, const uint2048_ts& b) { return uint2048_ts(a) / b; }
   INLINE uint2048_ts    operator %  (const uint64_t a, const uint2048_ts& b) { return uint2048_ts(a) % b; }
   INLINE std::ostream& operator << (std::ostream& os, const uint2048_ts& v) { return v.appendToStream(os); }
};
#pragma warning(default:26495)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPATIBILITY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ::sqrt()

INLINE CppCore::uint128_tg  sqrt(const CppCore::uint128_tg&  a) { CppCore::uint128_tg  r; CppCore::uint128_tg::Op::sqrt (a, r); return r; }
INLINE CppCore::uint256_tg  sqrt(const CppCore::uint256_tg&  a) { CppCore::uint256_tg  r; CppCore::uint256_tg::Op::sqrt (a, r); return r; }
INLINE CppCore::uint512_tg  sqrt(const CppCore::uint512_tg&  a) { CppCore::uint512_tg  r; CppCore::uint512_tg::Op::sqrt (a, r); return r; }
INLINE CppCore::uint1024_tg sqrt(const CppCore::uint1024_tg& a) { CppCore::uint1024_tg r; CppCore::uint1024_tg::Op::sqrt(a, r); return r; }
INLINE CppCore::uint2048_tg sqrt(const CppCore::uint2048_tg& a) { CppCore::uint2048_tg r; CppCore::uint2048_tg::Op::sqrt(a, r); return r; }

INLINE CppCore::uint128_ts  sqrt(const CppCore::uint128_ts&  a) { CppCore::uint128_ts  r; CppCore::uint128_ts::Op::sqrt (a, r); return r; }
INLINE CppCore::uint256_ts  sqrt(const CppCore::uint256_ts&  a) { CppCore::uint256_ts  r; CppCore::uint256_ts::Op::sqrt (a, r); return r; }
INLINE CppCore::uint512_ts  sqrt(const CppCore::uint512_ts&  a) { CppCore::uint512_ts  r; CppCore::uint512_ts::Op::sqrt (a, r); return r; }
INLINE CppCore::uint1024_ts sqrt(const CppCore::uint1024_ts& a) { CppCore::uint1024_ts r; CppCore::uint1024_ts::Op::sqrt(a, r); return r; }
INLINE CppCore::uint2048_ts sqrt(const CppCore::uint2048_ts& a) { CppCore::uint2048_ts r; CppCore::uint2048_ts::Op::sqrt(a, r); return r; }

// ::std::numeric_limits

namespace std 
{
   template<> class numeric_limits<CppCore::uint128_tg>  : public CppCore::uint128_tg::numeric_limits { };
   template<> class numeric_limits<CppCore::uint256_tg>  : public CppCore::uint256_tg::numeric_limits { };
   template<> class numeric_limits<CppCore::uint512_tg>  : public CppCore::uint512_tg::numeric_limits { };
   template<> class numeric_limits<CppCore::uint1024_tg> : public CppCore::uint1024_tg::numeric_limits { };
   template<> class numeric_limits<CppCore::uint2048_tg> : public CppCore::uint2048_tg::numeric_limits { };

   template<> class numeric_limits<CppCore::uint128_ts>  : public CppCore::uint128_ts::numeric_limits { };
   template<> class numeric_limits<CppCore::uint256_ts>  : public CppCore::uint256_ts::numeric_limits { };
   template<> class numeric_limits<CppCore::uint512_ts>  : public CppCore::uint512_ts::numeric_limits { };
   template<> class numeric_limits<CppCore::uint1024_ts> : public CppCore::uint1024_ts::numeric_limits { };
   template<> class numeric_limits<CppCore::uint2048_ts> : public CppCore::uint2048_ts::numeric_limits { };
}
