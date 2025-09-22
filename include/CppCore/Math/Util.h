#pragma once

#include <CppCore/Root.h>
#include <CppCore/BitOps.h>

namespace CppCore
{
   /// <summary>
   /// Returns how many bits are required to store the unsigned integer i.
   /// </summary>
   template<typename T = uint64_t>
   static INLINE T bitsRequiredForInt(const T i)
   {
      return (T)::log2(i) + (T)1U;
   }

   /// <summary>
   /// Returns the maximum unsigned integer for n symbols of base b.
   /// </summary>
   template<typename T = uint64_t>
   static INLINE T maxIntForBase(const T n, const T b)
   {
      return (T)::pow(b, n) - (T)1U;
   }

   /// <summary>
   /// Returns the maximum unsigned integer for n symbols of base 2.
   /// This is faster than calling maxIntForBase() with base=2
   /// </summary>
   template<typename T = uint64_t>
   static INLINE T maxIntForBase2(const T n)
   {
      return ((T)1U << n) - (T)1U;
   }

   /// <summary>
   /// Returns bounded value of v in interval min/max.
   /// </summary>
   template<typename T>
   static INLINE T bound(T v, T min, T max)
   {
      return v < min ? min : v > max ? max : v;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // RANGE CHECKS WITH BINARY AND
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// True if v is greater(equal) min and smaller(equal) max.
   /// Uses binary AND instead of logical to reduce branching.
   /// </summary>
   template<typename T, bool INCLUSIVE = true>
   INLINE static bool isinrange(const T v, const T min, const T max)
   {
      return INCLUSIVE ?
         ((v >= min) & (v <= max)) :
         ((v >  min) & (v <  max));
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BIT OPERATIONS
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Sets bit at index i in 32-bit integer v to b.
   /// </summary>
   static INLINE uint32_t setbit32(uint32_t v, uint32_t i, bool b)
   {
      return (v & ~(1U << i)) | ((uint32_t)b << i);
   }

   /// <summary>
   /// Sets bit at index i in 64-bit integer v to b.
   /// </summary>
   static INLINE uint64_t setbit64(uint64_t v, uint64_t i, bool b)
   {
      return (v & ~(1ULL << i)) | ((uint64_t)b << i);
   }

   /// <summary>
   /// Returns in lowbits the n bits starting at index i from 32-bit integer v.
   /// Undefined return for i >= 32 (use i AND 0x1F to map cyclic).
   /// Uses BMI1 if enabled.
   /// </summary>
   static INLINE uint32_t getbits32(const uint32_t v, const uint32_t i, const uint32_t n)
   {
   #if defined(CPPCORE_CPUFEAT_BMI1)
      return _bextr_u32(v, i, n);
   #else
      return (v >> i) & ((1U << n)-1U);
   #endif
   }

   /// <summary>
   /// Returns in lowbits the bits specified by mask from 32-bit integer v.
   /// Uses BMI2 if enabled.
   /// </summary>
   static INLINE uint32_t getbits32(const uint32_t v, const uint32_t mask)
   {
   #if defined(CPPCORE_CPUFEAT_BMI2)
      return _pext_u32(v, mask);
   #else
      return (v & mask) >> CppCore::tzcnt32(mask);
   #endif
   }

   /// <summary>
   /// Returns in lowbits the n bits starting at index i from 64-bit integer v.
   /// Undefined return for i >= 64 (use i AND 0x3F to map cyclic).
   /// Uses BMI1 if enabled.
   /// </summary>
   static INLINE uint64_t getbits64(const uint64_t v, const uint32_t i, const uint32_t n)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_BMI1)
      return _bextr_u64(v, i, n);
   #else
      return (v >> i) & ((1ULL << n)-1ULL);
   #endif
   }

   /// <summary>
   /// Returns in lowbits the bits specified by mask from 64-bit integer v.
   /// Uses BMI2 if enabled.
   /// </summary>
   static INLINE uint64_t getbits64(const uint64_t v, const uint64_t mask)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_BMI2)
      return _pext_u64(v, mask);
   #else
      return (v & mask) >> CppCore::tzcnt64(mask);
   #endif
   }

   /// <summary>
   /// Sets bits that are 1 in mask to 0 in 32-bit integer v and returns it.
   /// Uses BMI1 if enabled.
   /// </summary>
   static INLINE uint32_t unsetbits32(const uint32_t v, const uint32_t mask)
   {
   #if defined(CPPCORE_CPUFEAT_BMI1)
      return _andn_u32(mask, v);
   #else
      return ~mask & v;
   #endif
   }

   /// <summary>
   /// Sets n bits starting at index i in 32-bit integer v to zero.
   /// Uses BMI1 if enabled.
   /// </summary>
   static INLINE uint32_t unsetbits32(const uint32_t v, const uint32_t i, const uint32_t n)
   {
      return CppCore::unsetbits32(v, ((1U<<n)-1U)<<i);
   }

   /// <summary>
   /// Sets bits that are 1 in mask to 0 in 64-bit integer v and returns it.
   /// Uses BMI1 if enabled.
   /// </summary>
   static INLINE uint64_t unsetbits64(const uint64_t v, const uint64_t mask)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_BMI1)
      return _andn_u64(mask, v);
   #else
      return ~mask & v;
   #endif
   }

   /// <summary>
   /// Sets n bits starting at index i in 64-bit integer v to zero.
   /// Uses BMI1 if enabled.
   /// </summary>
   static INLINE uint64_t unsetbits64(const uint64_t v, const uint64_t i, const uint64_t n)
   {
      return CppCore::unsetbits64(v, ((1ULL<<n)-1ULL)<<i);
   }

   /// <summary>
   /// First unsets bits that are 1 in mask to 0 in 32-bit integer v (if UNSET=true).
   /// Then sets contiguous low bits from x into v at position specified by first lowbit in mask.
   /// Uses BMI1 and BMI2 if enabled. Zero Mask not allowed.
   /// </summary>
   template<bool UNSET = true>
   static INLINE uint32_t setbits32(const uint32_t v, const uint32_t x, const uint32_t mask)
   {
       assert(mask != 0);
   #if defined(CPPCORE_CPUFEAT_BMI2)
      return UNSET ? 
         CppCore::unsetbits32(v, mask) | _pdep_u32(x, mask) : 
         v | _pdep_u32(x, mask);
   #else
      return UNSET ? 
         CppCore::unsetbits32(v, mask) | (x << CppCore::tzcnt32(mask)) : 
         v | (x << CppCore::tzcnt32(mask));
   #endif
   }

   /// <summary>
   /// First unsets bits that are 1 in mask to 0 in 64-bit integer v (if UNSET=true).
   /// Then sets contiguous low bits from x into v at position specified by first lowbit in mask.
   /// Uses BMI1 and BMI2 if enabled. Zero Mask not allowed.
   /// </summary>
   template<bool UNSET = true>
   static INLINE uint64_t setbits64(const uint64_t v, const uint64_t x, const uint64_t mask)
   {
       assert(mask != 0);
    #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_BMI2)
      return UNSET ? 
         CppCore::unsetbits64(v, mask) | _pdep_u64(x, mask) : 
         v | _pdep_u64(x, mask);
   #else
      return UNSET ? 
         CppCore::unsetbits64(v, mask) | (x << CppCore::tzcnt64(mask)) : 
         v | (x << CppCore::tzcnt64(mask));
   #endif
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // 96-BIT LOAD/STORE
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE)
   /// <summary>
   /// Loads 96-bit (three floats) from unaligned m into SSE register.
   /// </summary>
   INLINE __m128 load96(const float* m)
   {
   #if defined(CPPCORE_CPUFEAT_AVX)
      return _mm_permute_ps(_mm_loadh_pi(_mm_load_ss(&m[2]), (const __m64*)m), _MM_SHUFFLE(1, 0, 3, 2));
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      return _mm_movelh_ps(_mm_castpd_ps(_mm_load_sd((const double*)m)), _mm_load_ss(&m[2]));
   #else
      return _mm_movelh_ps(_mm_loadl_pi(_mm_setzero_ps(), (const __m64*)m), _mm_load_ss(&m[2]));
   #endif
   }

   /// <summary>
   /// Stores 96-bit (three floats) from SSE register to unaligned m
   /// </summary>
   INLINE void store96(float* m, __m128 v)
   {
   #if defined(CPPCORE_CPUFEAT_SSE41)
      _mm_store_sd((double*)m, _mm_castps_pd(v)); 
      ((int*)m)[2] = _mm_extract_ps(v, 0x02);
   #elif defined(CPPCORE_CPUFEAT_SSE2)
      _mm_store_sd((double*)m, _mm_castps_pd(v));
      _mm_store_ss(&m[2], _mm_movehl_ps(v, v));
   #else
      _mm_storel_pi((__m64*)m, v); 
      _mm_store_ss(&m[2], _mm_movehl_ps(v, v));
   #endif
   }
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MODERN SSE/AVX INTRINSICS WITH OLDER FALLBACKS
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE)
   /// <summary>
   /// Uses _mm_permute_ps if AVX is available, else falls back to old _mm_shuffle_ps (SSE).
   /// </summary>
   template<int MASK>
   INLINE __m128 permute128f(const __m128& v)
   {
   #if defined(CPPCORE_CPUFEAT_AVX)
      return _mm_permute_ps(v, MASK);
   #else
      return _mm_shuffle_ps(v, v, MASK);
   #endif
   }

   /// <summary>
   /// Uses _mm_broadcast_ss if AVX is available, else falls back to old _mm_load_ps1 (SSE).
   /// </summary>
   INLINE __m128 broadcast128f(const float* v)
   {
   #if defined(CPPCORE_CPUFEAT_AVX)
      return _mm_broadcast_ss(v);
   #else
      return _mm_load_ps1(v);
   #endif
   }

   /// <summary>
   /// Returns (v*m)+a for float vectors. Requires SSE, uses newer FMA3 if enabled.
   /// </summary>
   INLINE __m128 madd128f(const __m128& v, const __m128& m, const __m128& a)
   {
   #if defined(CPPCORE_CPUFEAT_FMA3)
      return _mm_fmadd_ps(v, m, a);
   #else
      return _mm_add_ps(_mm_mul_ps(v, m), a);
   #endif
   }

   /// <summary>
   /// Returns (v*m)-s for float vectors. Requires SSE, uses newer FMA3 if enabled.
   /// </summary>
   INLINE __m128 msub128f(const __m128& v, const __m128& m, const __m128& s)
   {
   #if defined(CPPCORE_CPUFEAT_FMA3)
      return _mm_fmsub_ps(v, m, s);
   #else
      return _mm_sub_ps(_mm_mul_ps(v, m), s);
   #endif
   }
#endif

#if defined(CPPCORE_CPUFEAT_SSE2)  
   /// <summary>
   /// Uses _mm_cvtepu32_ps if AVX512F is available, else falls back to SSE2 code.
   /// </summary>
   /// SSE2 Solution From:
   /// https://stackoverflow.com/questions/34066228/how-to-perform-uint32-float-conversion-with-sse
   /// </remarks>
   INLINE __m128 cvtepu32f(const __m128i& v)
   {
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      return _mm_cvtepu32_ps(v);
   #else
      __m128i msk_lo     = _mm_set1_epi32(0xFFFF);
      __m128  cnst65536f = _mm_set1_ps(65536.0f);
      __m128i v_lo       = _mm_and_si128(v, msk_lo);
      __m128i v_hi       = _mm_srli_epi32(v, 16);
      __m128  v_lo_flt   = _mm_cvtepi32_ps(v_lo);
      __m128  v_hi_flt   = _mm_cvtepi32_ps(v_hi);
      return _mm_add_ps(_mm_mul_ps(cnst65536f, v_hi_flt), v_lo_flt);
   #endif
   }
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ROUNDING TO POW2 MULTIPLES
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Rounds v to the next lower multiple of m with m being a power of 2
   /// </summary>
   constexpr static INLINE uint32_t rdownptwo32(uint32_t v, uint32_t m)
   {
      // From Hacker's Delight
      return v & -(int32_t)m;
   }

   /// <summary>
   /// Rounds v to the next lower multiple of m with m being a power of 2
   /// </summary>
   constexpr static INLINE uint64_t rdownptwo64(uint64_t v, uint64_t m)
   {
      // From Hacker's Delight
      return v & -(int64_t)m;
   }

   /// <summary>
   /// Rounds v to the next higher multiple of m with m being a power of 2
   /// </summary>
   constexpr static INLINE uint32_t rupptwo32(uint32_t v, uint32_t m)
   {
      // From Hacker's Delight
      return rdownptwo32(v+(m-1), m);
   }

   /// <summary>
   /// Rounds v to the next higher multiple of m with m being a power of 2
   /// </summary>
   constexpr static INLINE uint64_t rupptwo64(uint64_t v, uint64_t m)
   {
      // From Hacker's Delight
      return rdownptwo64(v+(m-1), m);
   }

   /// <summary>
   /// Rounds v to the next higher multiple of m with m being a power of 2
   /// </summary>
   template<typename T>
   constexpr static INLINE T rupptwo(T v, T m)
   {
      assert(sizeof(T) == 4U || sizeof(T) == 8U);
      return sizeof(T) == 4U ?
         (T)rupptwo32((uint32_t)v, (uint32_t)m) :
         (T)rupptwo64((uint64_t)v, (uint64_t)m);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ROUNDING TO ANY MULTIPLES
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Rounds v to the next lower multiple of m.
   /// If m is a multiple of pow2, use faster rdownptwo32() instead.
   /// </summary>
   constexpr static INLINE uint32_t rdown32(uint32_t v, uint32_t m)
   {
      return (v / m) * m;
   }

   /// <summary>
   /// Rounds v to the next lower multiple of m.
   /// If m is a multiple of pow2, use faster rdownptwo64() instead.
   /// </summary>
   constexpr static INLINE uint64_t rdown64(uint64_t v, uint64_t m)
   {
      return (v / m) * m;
   }

   /// <summary>
   /// Rounds v to the next greater multiple of m.
   /// If m is a multiple of pow2, use faster rupptwo32() instead.
   /// </summary>
   constexpr static INLINE uint32_t rup32(uint32_t v, uint32_t m)
   {
      uint32_t r = rdown32(v, m);
      return r != v ? r + m : r;
   }

   /// <summary>
   /// Rounds v to the next greater multiple of m.
   /// If m is a multiple of pow2, use faster rupptwo64() instead.
   /// </summary>
   constexpr static INLINE uint64_t rup64(uint64_t v, uint64_t m)
   {
      uint64_t r = rdown64(v, m);
      return r != v ? r + m : r;
   }

   /// <summary>
   /// Rounds v to the next closest multiple of m.
   /// If same distance, picks lower one, except if lower would one be 0.
   /// </summary>
   constexpr static INLINE uint32_t round32(uint32_t v, uint32_t m)
   {
      uint32_t a = rdown32(v, m);
      uint32_t b = a + m;
      return ((a == 0) | (v-a > b-v)) ? b : a;
   }

   /// <summary>
   /// Rounds v to the next closest multiple of m.
   /// If same distance, picks lower one, except if lower would one be 0.
   /// </summary>
   constexpr static INLINE uint64_t round64(uint64_t v, uint64_t m)
   {
      uint64_t a = rdown64(v, m);
      uint64_t b = a + m;
      return ((a == 0) | (v-a > b-v)) ? b : a;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ROUNDING TO NEXT POWER OF TWO
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns next greater power of 2 for 32-bit integer
   /// </summary>
   constexpr static INLINE uint32_t ngptwo32(uint32_t n)
   {
      n--;
      n |= n >> 1;
      n |= n >> 2;
      n |= n >> 4;
      n |= n >> 8;
      n |= n >> 16;
      n++;
      return n;
   }

   /// <summary>
   /// Returns next greater power of 2 for 64-bit integer
   /// </summary>
   constexpr static INLINE uint64_t ngptwo64(uint64_t n)
   {
      n--;
      n |= n >> 1;
      n |= n >> 2;
      n |= n >> 4;
      n |= n >> 8;
      n |= n >> 16;
      n |= n >> 32;
      n++;
      return n;
   }

   /// <summary>
   /// Returns next lower power of 2 for 32-bit integer
   /// </summary>
   constexpr static INLINE uint32_t nlptwo32(uint32_t n)
   {
      n |= n >> 1;
      n |= n >> 2;
      n |= n >> 4;
      n |= n >> 8;
      n |= n >> 16;
      return n - (n>>1);
   }

   /// <summary>
   /// Returns next lower power of 2 for 64-bit integer
   /// </summary>
   constexpr static INLINE uint64_t nlptwo64(uint64_t n)
   {
      n |= n >> 1;
      n |= n >> 2;
      n |= n >> 4;
      n |= n >> 8;
      n |= n >> 16;
      n |= n >> 32;
      return n - (n>>1);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // PADDED STRUCT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack (push, 1)
   /// <summary>
   /// Pads T to next higher multiple of N. 
   /// Extends by N if sizeof(T) is multiple of N already.
   /// </summary>
   template<typename T, size_t N=sizeof(size_t)>
   struct Padded
   {
      static constexpr size_t DELTA = CppCore::rup32(sizeof(T),N)-sizeof(T);
      static constexpr size_t PADSIZE = DELTA ? DELTA : N;
      T v;
      uint8_t t[PADSIZE];
      INLINE Padded() { }
      INLINE Padded(const T& v)
      {
         CppCore::clone(this->v, v);
         CppCore::clear(t);
      }
   };
#pragma pack(pop)

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // TEMPLATE UNIONS
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Union of two types
   /// </summary>
   template<typename T1, typename T2>
   union U2
   {
   public:
      T1 t1;
      T2 t2;
      INLINE U2() {}
   };

   /// <summary>
   /// Union of three types
   /// </summary>
   template<typename T1, typename T2, typename T3>
   union U3
   {
   public:
      T1 t1;
      T2 t2;
      T3 t3;
      INLINE U3() {}
   };

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ADDITION OPERATIONS WITH OVERFLOW BIT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Addition with carry bit for 8-bit integer.
   /// </summary>
   INLINE static void addcarry8(uint8_t a, uint8_t b, uint8_t& r, uint8_t& c)
   {
   #if defined(CPPCORE_COMPILER_MSVC) && defined(CPPCORE_CPU_X86ORX64)
      c = _addcarry_u8(c, a, b, &r);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_addcb)
      unsigned char t;
      r = __builtin_addcb(a, b, c, &t);
      c = (uint8_t)t;
   #else
      // from Hacker's Delight
      r = a + b + c;
      c = ((a & b) | ((a | b) & ~r)) >> 7;
   #endif
   }

   /// <summary>
   /// Addition with carry bit for 16-bit integer.
   /// </summary>
   INLINE static void addcarry16(uint16_t a, uint16_t b, uint16_t& r, uint8_t& c)
   {
   #if defined(CPPCORE_COMPILER_MSVC) && defined(CPPCORE_CPU_X86ORX64)
      c = _addcarry_u16(c, a, b, &r);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_addcs)
      unsigned short t;
      r = __builtin_addcs(a, b, c, &t);
      c = (uint8_t)t;
   #else
      // from Hacker's Delight
      r = a + b + c;
      c = ((a & b) | ((a | b) & ~r)) >> 15;
   #endif
   }

   /// <summary>
   /// Addition with carry bit for 32-bit integer.
   /// </summary>
   INLINE static void addcarry32(uint32_t a, uint32_t b, uint32_t& r, uint8_t& c)
   {
   #if defined(CPPCORE_CPUFEAT_ADX)
      c = _addcarryx_u32(c, a, b, &r);
   #elif defined(CPPCORE_CPU_X86ORX64)
      c = _addcarry_u32(c, a, b, &r);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_addc)
      unsigned int t;
      r = __builtin_addc(a, b, c, &t);
      c = (uint8_t)t;
   #else
      // from Hacker's Delight
      r = a + b + c;
      c = ((a & b) | ((a | b) & ~r)) >> 31;
   #endif
   }

   /// <summary>
   /// Addition with carry bit for 64-bit integer.
   /// Using 2x 32-Bit addcarry32.
   /// </summary>
   INLINE static void addcarry64(
      uint32_t  al, uint32_t  ah, 
      uint32_t  bl, uint32_t  bh, 
      uint32_t& rl, uint32_t& rh,
      uint8_t&  c)
   {
      CppCore::addcarry32(al, bl, rl, c);
      CppCore::addcarry32(ah, bh, rh, c);
   }

   /// <summary>
   /// Addition with carry bit for 64-bit integer.
   /// </summary>
   INLINE static void addcarry64(uint64_t a, uint64_t b, uint64_t& r, uint8_t& c)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_ADX)
      c = _addcarryx_u64(c, a, b, (unsigned long long*)&r);
   #elif defined(CPPCORE_CPU_X64)
      c = _addcarry_u64(c, a, b, (unsigned long long*)&r);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_addcll)
      unsigned long long t;
      r = __builtin_addcll(a, b, c, &t);
      c = (uint8_t)t;
   #else
      // from Hacker's Delight
      r = a + b + c;
      c = ((a & b) | ((a | b) & ~r)) >> 63;
   #endif
   }

   /// <summary>
   /// Addition with carry bit for 128-bit integer.
   /// Using 4x addcarry32 operations.
   /// </summary>
   INLINE static void addcarry128(
      uint32_t  all, uint32_t  alh, uint32_t  ahl, uint32_t  ahh,
      uint32_t  bll, uint32_t  blh, uint32_t  bhl, uint32_t  bhh,
      uint32_t& rll, uint32_t& rlh, uint32_t& rhl, uint32_t& rhh,
      uint8_t&  c)
   {
      CppCore::addcarry32(all, bll, rll, c);
      CppCore::addcarry32(alh, blh, rlh, c);
      CppCore::addcarry32(ahl, bhl, rhl, c);
      CppCore::addcarry32(ahh, bhh, rhh, c);
   }

   /// <summary>
   /// Addition with carry bit for 128-bit integer.
   /// Using 2x addcarry64 operations.
   /// </summary>
   INLINE static void addcarry128(
      uint64_t  al, uint64_t  ah, 
      uint64_t  bl, uint64_t  bh, 
      uint64_t& rl, uint64_t& rh, 
      uint8_t&  c)
   {
      CppCore::addcarry64(al, bl, rl, c);
      CppCore::addcarry64(ah, bh, rh, c);
   }

   /// <summary>
   /// Addition with carry bit for any sized integers that are multiples of 32-bit.
   /// </summary>
   template<typename UINT1, typename UINT2, typename UINT3>
   INLINE static void addcarry(const UINT1& x, const UINT2& y, UINT3& z, uint8_t& c)
   {
      static_assert(sizeof(UINT1) % 4 == 0 || sizeof(UINT1) < sizeof(size_t));
      static_assert(sizeof(UINT2) % 4 == 0 || sizeof(UINT2) < sizeof(size_t));
      static_assert(sizeof(UINT3) % 4 == 0);
      constexpr size_t MAXSIZE = MAX(sizeof(UINT1), sizeof(UINT2));
      constexpr size_t MINSIZE = MIN(sizeof(UINT1), sizeof(UINT2));
      static_assert(sizeof(UINT3) == MAXSIZE);
   #if defined(CPPCORE_CPU_64BIT)
      if constexpr (sizeof(UINT1) % 8 == 0 && sizeof(UINT2) % 8 == 0 && sizeof(UINT3) % 8 == 0)
      {
         constexpr size_t NUINT1 = sizeof(UINT1) / 8;
         constexpr size_t NUINT2 = sizeof(UINT2) / 8;
         constexpr size_t NMIN = MINSIZE / 8;
         uint64_t* px = (uint64_t*)&x;
         uint64_t* py = (uint64_t*)&y;
         uint64_t* pz = (uint64_t*)&z;
         for (size_t i = 0; i < NMIN; i++)
            CppCore::addcarry64(px[i], py[i], pz[i], c);
         if constexpr (sizeof(UINT1) > sizeof(UINT2))
            for (size_t i = NMIN; i < NUINT1; i++)
               CppCore::addcarry64(px[i], 0ULL, pz[i], c);
         if constexpr (sizeof(UINT1) < sizeof(UINT2))
            for (size_t i = NMIN; i < NUINT2; i++)
               CppCore::addcarry64(0ULL, py[i], pz[i], c);
      }
      else if
   #else
      if
   #endif
         constexpr (sizeof(UINT1) % 4 == 0 && sizeof(UINT2) % 4 == 0 && sizeof(UINT3) % 4 == 0)
      {
         constexpr size_t NUINT1 = sizeof(UINT1) / 4;
         constexpr size_t NUINT2 = sizeof(UINT2) / 4;
         constexpr size_t NMIN = MINSIZE / 4;
         uint32_t* px = (uint32_t*)&x;
         uint32_t* py = (uint32_t*)&y;
         uint32_t* pz = (uint32_t*)&z;
         for (size_t i = 0; i < NMIN; i++)
            CppCore::addcarry32(px[i], py[i], pz[i], c);
         if constexpr (sizeof(UINT1) > sizeof(UINT2))
            for (size_t i = NMIN; i < NUINT1; i++)
               CppCore::addcarry32(px[i], 0U, pz[i], c);
         if constexpr (sizeof(UINT1) < sizeof(UINT2))
            for (size_t i = NMIN; i < NUINT2; i++)
               CppCore::addcarry32(0U, py[i], pz[i], c);
      }
      else if constexpr (sizeof(UINT1) < sizeof(size_t)) { CppCore::addcarry<size_t, UINT2, UINT3>((size_t)x, y, z, c); }
      else if constexpr (sizeof(UINT2) < sizeof(size_t)) { CppCore::addcarry<UINT1, size_t, UINT3>(x, (size_t)y, z, c); }
   }

   /// <summary>
   /// Template Specialization for 8+8=8
   /// </summary>
   template<> INLINE void addcarry(const uint8_t& x, const uint8_t& y, uint8_t& r, uint8_t& c)
   {
      CppCore::addcarry8(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 16+8=16
   /// </summary>
   template<> INLINE void addcarry(const uint16_t& x, const uint8_t& y, uint16_t& r, uint8_t& c)
   {
      CppCore::addcarry16(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 16+16=16
   /// </summary>
   template<> INLINE void addcarry(const uint16_t& x, const uint16_t& y, uint16_t& r, uint8_t& c)
   {
      CppCore::addcarry16(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 32+8=32
   /// </summary>
   template<> INLINE void addcarry(const uint32_t& x, const uint8_t& y, uint32_t& r, uint8_t& c)
   {
      CppCore::addcarry32(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 32+16=32
   /// </summary>
   template<> INLINE void addcarry(const uint32_t& x, const uint16_t& y, uint32_t& r, uint8_t& c)
   {
      CppCore::addcarry32(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 32+32=32
   /// </summary>
   template<> INLINE void addcarry(const uint32_t& x, const uint32_t& y, uint32_t& r, uint8_t& c)
   {
      CppCore::addcarry32(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 64+8=64
   /// </summary>
   template<> INLINE void addcarry(const uint64_t& x, const uint8_t& y, uint64_t& r, uint8_t& c)
   {
      CppCore::addcarry64(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 64+16=64
   /// </summary>
   template<> INLINE void addcarry(const uint64_t& x, const uint16_t& y, uint64_t& r, uint8_t& c)
   {
      CppCore::addcarry64(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 64+32=64
   /// </summary>
   template<> INLINE void addcarry(const uint64_t& x, const uint32_t& y, uint64_t& r, uint8_t& c)
   {
      CppCore::addcarry64(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 64+64=64
   /// </summary>
   template<> INLINE void addcarry(const uint64_t& x, const uint64_t& y, uint64_t& r, uint8_t& c)
   {
      CppCore::addcarry64(x, y, r, c);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ADDITION
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Addition for 64-Bit Unsigned integer.
   /// Using addcarry64 with 32-Bit and discarding the overflow
   /// </summary>
   INLINE static void uadd64(
      uint32_t  al, uint32_t  ah, 
      uint32_t  bl, uint32_t  bh, 
      uint32_t& rl, uint32_t& rh)
   {
      uint8_t c = 0;
      CppCore::addcarry64(al, ah, bl, bh, rl, rh, c);
   }

   /// <summary>
   /// Addition for 128-bit Unsigned integer.
   /// Using addcarry128 with 32-Bits and discarding the overflow.
   /// </summary>
   INLINE static void uadd128(
      uint32_t  all, uint32_t  alh, uint32_t  ahl, uint32_t  ahh,
      uint32_t  bll, uint32_t  blh, uint32_t  bhl, uint32_t  bhh,
      uint32_t& rll, uint32_t& rlh, uint32_t& rhl, uint32_t& rhh)
   {
      uint8_t c = 0;
      CppCore::addcarry128(
         all, alh, ahl, ahh,
         bll, blh, bhl, bhh,
         rll, rlh, rhl, rhh,
         c);
   }

   /// <summary>
   /// Addition for 128-bit Unsigned integer.
   /// Using addcarry128 with 64-Bits and discarding the overflow.
   /// </summary>
   INLINE static void uadd128(
      uint64_t  al, uint64_t  ah, 
      uint64_t  bl, uint64_t  bh, 
      uint64_t& rl, uint64_t& rh)
   {
      uint8_t c = 0;
      CppCore::addcarry128(al, ah, bl, bh, rl, rh, c);
   }

   /// <summary>
   /// Addition for any sized integers that are multiples of 32-bit.
   /// </summary>
   template<typename UINT1, typename UINT2, typename UINT3>
   INLINE static void uadd(const UINT1& x, const UINT2& y, UINT3& r)
   {
      if      constexpr (sizeof(UINT1) < sizeof(size_t)) { CppCore::uadd((size_t)x, y, r); }
      else if constexpr (sizeof(UINT2) < sizeof(size_t)) { CppCore::uadd(x, (size_t)y, r); }
      else if constexpr (sizeof(UINT3) < sizeof(size_t)) { size_t t; CppCore::uadd(x, y, t); r = (UINT3)t; }
      else { uint8_t c = 0; CppCore::addcarry(x, y, r, c); }
   }

   /// <summary>
   /// Template Specialization for 8+8=8
   /// </summary>
   template<> INLINE void uadd(const uint8_t& x, const uint8_t& y, uint8_t& r)
   {
      r = x + y;
   }

   /// <summary>
   /// Template Specialization for 8+8=16
   /// </summary>
   template<> INLINE void uadd(const uint8_t& x, const uint8_t& y, uint16_t& r)
   {
      r = (uint16_t)x + (uint16_t)y;
   }

   /// <summary>
   /// Template Specialization for 16+16=16
   /// </summary>
   template<> INLINE void uadd(const uint16_t& x, const uint16_t& y, uint16_t& r)
   {
      r = x + y;
   }

   /// <summary>
   /// Template Specialization for 16+16=32
   /// </summary>
   template<> INLINE void uadd(const uint16_t& x, const uint16_t& y, uint32_t& r)
   {
      r = (uint32_t)x + (uint32_t)y;
   }

   /// <summary>
   /// Template Specialization for 32+32=32
   /// </summary>
   template<> INLINE void uadd(const uint32_t& x, const uint32_t& y, uint32_t& r)
   {
      r = x + y;
   }

   /// <summary>
   /// Template Specialization for 32+32=64
   /// </summary>
   template<> INLINE void uadd(const uint32_t& x, const uint32_t& y, uint64_t& r)
   {
      r = (uint64_t)x + (uint64_t)y;
   }

   /// <summary>
   /// Template Specialization for 64+64=64
   /// </summary>
   template<> INLINE void uadd(const uint64_t& x, const uint64_t& y, uint64_t& r)
   {
      r = x + y;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SUBTRACTIION OPERATIONS WITH UNDERFLOW BIT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Subtraction with carry bit for 8-bit integer.
   /// </summary>
   INLINE static void subborrow8(uint8_t a, uint8_t b, uint8_t& r, uint8_t& c)
   {
   #if defined(CPPCORE_COMPILER_MSVC) && defined(CPPCORE_CPU_X86ORX64)
      c = _subborrow_u8(c, a, b, &r);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_subcb)
      unsigned char t;
      r = __builtin_subcb(a, b, c, &t);
      c = (uint8_t)t;
   #else
      // from Hacker's Delight
      r = a - b - c;
      c = ((~a & b) | ((~a | b) & r)) >> 7;
   #endif
   }

   /// <summary>
   /// Subtraction with carry bit for 16-bit integer.
   /// </summary>
   INLINE static void subborrow16(uint16_t a, uint16_t b, uint16_t& r, uint8_t& c)
   {
   #if defined(CPPCORE_COMPILER_MSVC) && defined(CPPCORE_CPU_X86ORX64)
      c = _subborrow_u16(c, a, b, &r);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_subcs)
      unsigned short t;
      r = __builtin_subcs(a, b, c, &t);
      c = (uint8_t)t;
   #else
      // from Hacker's Delight
      r = a - b - c;
      c = ((~a & b) | ((~a | b) & r)) >> 15;
   #endif
   }

   /// <summary>
   /// Subtraction with carry bit for 32-bit integer.
   /// </summary>
   INLINE static void subborrow32(uint32_t a, uint32_t b, uint32_t& r, uint8_t& c)
   {
   #if defined(CPPCORE_CPU_X86ORX64)
      c = _subborrow_u32(c, a, b, &r);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_subc)
      unsigned int t;
      r = __builtin_subc(a, b, c, &t);
      c = (uint8_t)t;
   #else
      // from Hacker's Delight
      r = a - b - c;
      c = ((~a & b) | ((~a | b) & r)) >> 31;
   #endif
   }

   /// <summary>
   /// Subtraction with carry bit for 2x32-bit integer.
   /// Using 2x subborrow32.
   /// </summary>
   INLINE static void subborrow64(
      uint32_t  al, uint32_t  ah, 
      uint32_t  bl, uint32_t  bh, 
      uint32_t& rl, uint32_t& rh,
      uint8_t&  c)
   {
      CppCore::subborrow32(al, bl, rl, c);
      CppCore::subborrow32(ah, bh, rh, c);
   }

   /// <summary>
   /// Subtraction with carry bit for 64-bit integer.
   /// </summary>
   INLINE static void subborrow64(uint64_t a, uint64_t b, uint64_t& r, uint8_t& c)
   {
   #if defined(CPPCORE_CPU_X64)
      c = _subborrow_u64(c, a, b, (unsigned long long*)&r);
   #elif defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_subcll)
      unsigned long long t;
      r = __builtin_subcll(a, b, c, &t);
      c = (uint8_t)t;
   #else
      // from Hacker's Delight
      r = a - b - c;
      c = ((~a & b) | ((~a | b) & r)) >> 63;
   #endif
   }

   /// <summary>
   /// Subtraction with carry bit for 128-bit integer.
   /// Using 4x subborrow32.
   /// </summary>
   INLINE static void subborrow128(
      uint32_t  all, uint32_t  alh, uint32_t  ahl, uint32_t  ahh,
      uint32_t  bll, uint32_t  blh, uint32_t  bhl, uint32_t  bhh,
      uint32_t& rll, uint32_t& rlh, uint32_t& rhl, uint32_t& rhh,
      uint8_t&  c)
   {
      CppCore::subborrow32(all, bll, rll, c);
      CppCore::subborrow32(alh, blh, rlh, c);
      CppCore::subborrow32(ahl, bhl, rhl, c);
      CppCore::subborrow32(ahh, bhh, rhh, c);
   }

   /// <summary>
   /// Subtraction with carry bit for 128-bit integer.
   /// Using 2x subborrow64.
   /// </summary>
   INLINE static void subborrow128(
      uint64_t  al, uint64_t  ah,
      uint64_t  bl, uint64_t  bh,
      uint64_t& rl, uint64_t& rh,
      uint8_t&  c)
   {
      CppCore::subborrow64(al, bl, rl, c);
      CppCore::subborrow64(ah, bh, rh, c);
   }

   /// <summary>
   /// Subtraction with carry bit for any sized integer that is multiple of 32-bit.
   /// </summary>
   template<typename UINT1, typename UINT2, typename UINT3>
   INLINE static void subborrow(const UINT1& x, const UINT2& y, UINT3& z, uint8_t& c)
   {
      static_assert(sizeof(UINT1) % 4 == 0 || sizeof(UINT1) < sizeof(size_t));
      static_assert(sizeof(UINT2) % 4 == 0 || sizeof(UINT2) < sizeof(size_t));
      static_assert(sizeof(UINT3) % 4 == 0);
      constexpr size_t MAXSIZE = MAX(sizeof(UINT1), sizeof(UINT2));
      constexpr size_t MINSIZE = MIN(sizeof(UINT1), sizeof(UINT2));
      static_assert(sizeof(UINT3) == MAXSIZE);
   #if defined(CPPCORE_CPU_64BIT)
      if constexpr (sizeof(UINT1) % 8 == 0 && sizeof(UINT2) % 8 == 0 && sizeof(UINT3) % 8 == 0)
      {
         constexpr size_t NUINT1 = sizeof(UINT1) / 8;
         constexpr size_t NUINT2 = sizeof(UINT2) / 8;
         constexpr size_t NMIN = MINSIZE / 8;
         constexpr size_t NMAX = MAXSIZE / 8;
         uint64_t* px = (uint64_t*)&x;
         uint64_t* py = (uint64_t*)&y;
         uint64_t* pz = (uint64_t*)&z;
         for (size_t i = 0; i < NMIN; i++)
            CppCore::subborrow64(px[i], py[i], pz[i], c);
         if constexpr (sizeof(UINT1) > sizeof(UINT2))
            for (size_t i = NMIN; i < NUINT1; i++)
               CppCore::subborrow64(px[i], 0ULL, pz[i], c);
         if constexpr (sizeof(UINT1) < sizeof(UINT2))
            for (size_t i = NMIN; i < NUINT2; i++)
               CppCore::subborrow64(0ULL, py[i], pz[i], c);
      }
      else if
   #else
      if
   #endif
         constexpr (sizeof(UINT1) % 4 == 0 && sizeof(UINT2) % 4 == 0 && sizeof(UINT3) % 4 == 0)
      {
         constexpr size_t NUINT1 = sizeof(UINT1) / 4;
         constexpr size_t NUINT2 = sizeof(UINT2) / 4;
         constexpr size_t NMIN = MINSIZE / 4;
         constexpr size_t NMAX = MAXSIZE / 4;
         uint32_t* px = (uint32_t*)&x;
         uint32_t* py = (uint32_t*)&y;
         uint32_t* pz = (uint32_t*)&z;
         for (size_t i = 0; i < NMIN; i++)
            CppCore::subborrow32(px[i], py[i], pz[i], c);
         if constexpr (sizeof(UINT1) > sizeof(UINT2))
            for (size_t i = NMIN; i < NUINT1; i++)
               CppCore::subborrow32(px[i], 0U, pz[i], c);
         if constexpr (sizeof(UINT1) < sizeof(UINT2))
            for (size_t i = NMIN; i < NUINT2; i++)
               CppCore::subborrow32(0U, py[i], pz[i], c);
      }
      else if constexpr (sizeof(UINT1) < sizeof(size_t)) { CppCore::subborrow<size_t, UINT2, UINT3>((size_t)x, y, z, c); }
      else if constexpr (sizeof(UINT2) < sizeof(size_t)) { CppCore::subborrow<UINT1, size_t, UINT3>(x, (size_t)y, z, c); }
   }

   /// <summary>
   /// Template Specialization for 8-8=8
   /// </summary>
   template<> INLINE void subborrow(const uint8_t& x, const uint8_t& y, uint8_t& r, uint8_t& c)
   {
      CppCore::subborrow8(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 16-16=16
   /// </summary>
   template<> INLINE void subborrow(const uint16_t& x, const uint16_t& y, uint16_t& r, uint8_t& c)
   {
      CppCore::subborrow16(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 32-32=32
   /// </summary>
   template<> INLINE void subborrow(const uint32_t& x, const uint32_t& y, uint32_t& r, uint8_t& c)
   {
      CppCore::subborrow32(x, y, r, c);
   }

   /// <summary>
   /// Template Specialization for 64-64=64
   /// </summary>
   template<> INLINE void subborrow(const uint64_t& x, const uint64_t& y, uint64_t& r, uint8_t& c)
   {
      CppCore::subborrow64(x, y, r, c);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SUBTRACTIION
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Subtraction for 32-bit Unsigned Integer.
   /// Using subborrow64 with 32-Bits and discarding the underflow.
   /// </summary>
   INLINE static void usub64(
      uint32_t  al, uint32_t  ah, 
      uint32_t  bl, uint32_t  bh, 
      uint32_t& rl, uint32_t& rh)
   {
      uint8_t c = 0;
      CppCore::subborrow64(al, ah, bl, bh, rl, rh, c);
   }

   /// <summary>
   /// Subtraction for 128-bit Unsigned Integer.
   /// Using subborrow128 with 32-Bits and discarding the underflow.
   /// </summary>
   INLINE static void usub128(
      uint32_t  all, uint32_t  alh, uint32_t  ahl, uint32_t  ahh,
      uint32_t  bll, uint32_t  blh, uint32_t  bhl, uint32_t  bhh,
      uint32_t& rll, uint32_t& rlh, uint32_t& rhl, uint32_t& rhh)
   {
      uint8_t c = 0;
      CppCore::subborrow128(
         all, alh, ahl, ahh,
         bll, blh, bhl, bhh,
         rll, rlh, rhl, rhh,
         c);
   }

   /// <summary>
   /// Subtraction for 128-bit Unsigned Integer.
   /// Using subborrow128 with 64-Bits and discarding the underflow.
   /// </summary>
   INLINE static void usub128(
      uint64_t  al, uint64_t  ah,
      uint64_t  bl, uint64_t  bh,
      uint64_t& rl, uint64_t& rh)
   {
      uint8_t c = 0;
      CppCore::subborrow128(al, ah, bl, bh, rl, rh, c);
   }

   /// <summary>
   /// Subtraction for any sized integer that is multiple of 32-bit.
   /// </summary>
   template<typename UINT1, typename UINT2, typename UINT3>
   INLINE static void usub(const UINT1& x, const UINT2& y, UINT3& r)
   {
      if      constexpr (sizeof(UINT1) < sizeof(size_t)) { CppCore::usub((size_t)x, y, r); }
      else if constexpr (sizeof(UINT2) < sizeof(size_t)) { CppCore::usub(x, (size_t)y, r); }
      else if constexpr (sizeof(UINT3) < sizeof(size_t)) { size_t t; CppCore::usub(x, y, t); r = (UINT3)t; }
      else { uint8_t c = 0; CppCore::subborrow(x, y, r, c); }
   }

   /// <summary>
   /// Template Specialization for 8-8=8
   /// </summary>
   template<> INLINE void usub(const uint8_t& x, const uint8_t& y, uint8_t& r)
   {
      r = x - y;
   }

   /// <summary>
   /// Template Specialization for 16-8=16
   /// </summary>
   template<> INLINE void usub(const uint16_t& x, const uint8_t& y, uint16_t& r)
   {
      r = x - y;
   }

   /// <summary>
   /// Template Specialization for 16-16=16
   /// </summary>
   template<> INLINE void usub(const uint16_t& x, const uint16_t& y, uint16_t& r)
   {
      r = x - y;
   }

   /// <summary>
   /// Template Specialization for 32-8=32
   /// </summary>
   template<> INLINE void usub(const uint32_t& x, const uint8_t& y, uint32_t& r)
   {
      r = x - y;
   }

   /// <summary>
   /// Template Specialization for 32-16=32
   /// </summary>
   template<> INLINE void usub(const uint32_t& x, const uint16_t& y, uint32_t& r)
   {
      r = x - y;
   }

   /// <summary>
   /// Template Specialization for 32-32=32
   /// </summary>
   template<> INLINE void usub(const uint32_t& x, const uint32_t& y, uint32_t& r)
   {
      r = x - y;
   }

   /// <summary>
   /// Template Specialization for 64-8=64
   /// </summary>
   template<> INLINE void usub(const uint64_t& x, const uint8_t& y, uint64_t& r)
   {
      r = x - y;
   }

   /// <summary>
   /// Template Specialization for 64-16=64
   /// </summary>
   template<> INLINE void usub(const uint64_t& x, const uint16_t& y, uint64_t& r)
   {
      r = x - y;
   }

   /// <summary>
   /// Template Specialization for 64-32=64
   /// </summary>
   template<> INLINE void usub(const uint64_t& x, const uint32_t& y, uint64_t& r)
   {
      r = x - y;
   }

   /// <summary>
   /// Template Specialization for 64-64=64
   /// </summary>
   template<> INLINE void usub(const uint64_t& x, const uint64_t& y, uint64_t& r)
   {
      r = x - y;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // UNSIGNED INTEGER MULTIPLICATION
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Unsigned 32-Bit * Unsigned 32-Bit = Unsigned 64 Bit.
   /// </summary>
   INLINE static void umul64(const uint32_t& a, const uint32_t& b, uint32_t& l, uint32_t& h)
   {
   #if defined(CPPCORE_CPU_X86ORX64) && defined(CPPCORE_CPUFEAT_BMI2) && defined(CPPCORE_COMPILER_MSVC)
      l = _mulx_u32(a, b, &h);
   #else
      const uint64_t t = (uint64_t)a * (uint64_t)b;
      l = (uint32_t)t;
      h = (uint32_t)(t >> 32);
   #endif
   }

   /// <summary>
   /// Unsigned 64-Bit * Unsigned 64-Bit = Unsigned 128 Bit. 
   /// Uses single MULX or MUL instruction on Intel 64-Bit.
   /// </summary>
   INLINE static void umul128(uint64_t a, uint64_t b, uint64_t& l, uint64_t& h)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_BMI2)
      l = _mulx_u64(a, b, (unsigned long long*)&h);
   #elif defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_MSVC)
      l = _umul128(a, b, &h);
   #elif defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_CLANG)
      __asm("MULQ %3" : "=a" (l), "=d" (h) : "0" (a), "r" (b));
   #elif defined(CPPCORE_COMPILER_CLANG) && defined(__SIZEOF_INT128__)
      __uint128_t t = (__uint128_t)a * b;
      l = (uint64_t)t;
      h = (uint64_t)(t >> 64);
   #else
      uint32_t al = (uint32_t)a;
      uint32_t ah = (uint32_t)(a >> 32);
      uint32_t bl = (uint32_t)b;
      uint32_t bh = (uint32_t)(b >> 32);

      uint64_t p1 = (uint64_t)al * bl;
      uint64_t p2 = (uint64_t)al * bh;
      uint64_t p3 = (uint64_t)ah * bl;
      uint64_t p4 = (uint64_t)ah * bh;
      uint64_t t;

      l = (uint32_t)p1;
      h = p4;
      
      t = p2 + (p1 >> 32);
      h += (t >> 32);
      t = p3 + (uint32_t)t;

      l |= (t << 32);
      h += (t >> 32);
   #endif
   }

   /// <summary>
   /// Unsigned 128-Bit * Unsigned 128-Bit = Unsigned 128 Bit.
   /// </summary>
   INLINE static void umul128(uint64_t al, uint64_t ah, uint64_t bl, uint64_t bh, uint64_t& l, uint64_t& h)
   {
      CppCore::umul128(al, bl, l, h);
      h += (ah*bl) + (al*bh);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SIGNED INTEGER MULTIPLICATION
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Signed 64-Bit * Signed 64-Bit = Signed 128 Bit.
   /// </summary>
   INLINE static void mul128(int64_t a, int64_t b, int64_t& l, int64_t& h)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_MSVC)
      l = _mul128(a, b, &h);
   #else
      CppCore::umul128((uint64_t)a, (uint64_t)b, (uint64_t&)l, (uint64_t&)h);
      if (a < 0) h -= b;
      if (b < 0) h -= a;
   #endif
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MADD AND MSUB TEMPLATE OPERATIONS
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Template Version. Returns (v*m)+a.
   /// </summary>
   template<typename T>
   INLINE static T madd(const T v, const T m, const T a)
   {
      return (v * m) + a;
   }

   /// <summary>
   /// Template Version. Returns (v*m)-s.
   /// </summary>
   template<typename T>
   INLINE static T msub(const T v, const T m, const T s)
   {
      return (v * m) - s;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // INTEGER SQUARE ROOT
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Generic Square Root for unsigned integer types
   /// that support shift, or, sub and comparison ops.
   /// </summary>
   template<typename T, size_t NBITS = sizeof(T) * 8U>
   INLINE static void isqrt(const T& a, T& r)
   {
      // From Hacker's Delight
      T m, x, b;
      CppCore::clone(x, a);
      CppCore::clear(r);
      m = 1;
      m <<= (NBITS - 2U);
      while (m != 0) {
         CppCore::or_(r, m, b);
         r >>= 1;
         if (x >= b) {
            x -= b;
            r |= m;
         }
         m >>= 2;
      }
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // CLMUL
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Carry-less Multiplication (Generic Version).
   /// Accepts any integer sizes that are multiples of four.
   /// </summary>
   template<typename UINT1, typename UINT2, typename UINT3>
   INLINE static void clmul_generic(const UINT1& a, const UINT2& b, UINT3& r)
   {
      static_assert(sizeof(UINT1) % 4 == 0);
      static_assert(sizeof(UINT2) % 4 == 0);
      static_assert(sizeof(UINT3) % 4 == 0);
      UINT3 ta;
      UINT2 tb;
      if constexpr (sizeof(a) < sizeof(ta)) {
         CppCore::clear(ta);
         CppCore::clone(*(UINT1*)&ta, a);
      }
      else CppCore::clone(ta, *(UINT3*)&a);
      CppCore::clone(tb, b);
      CppCore::clear(r);
      while (!CppCore::testzero(tb))
      {
         if (CppCore::bittest(tb, 0))
            CppCore::xor_(r, ta, r);
         CppCore::shr(tb, tb, 1);
         CppCore::shl(ta, ta, 1);
      }
   }

   /// <summary>
   /// Carry-less Multiplication (Optimized Version).
   /// Uses CLMUL instruction if available and applicable else uses generic version.
   /// </summary>
   template<typename UINT1, typename UINT2, typename UINT3>
   INLINE static void clmul(const UINT1& a, const UINT2& b, UINT3& r)
   {
   #if defined(CPPCORE_CPUFEAT_PCLMUL)
      if constexpr (sizeof(UINT1) == 16 && sizeof(UINT2) == 16 && sizeof(UINT3) == 32)
      {
         __m128i xmma = _mm_loadu_si128((__m128i*)&a);
         __m128i xmmb = _mm_loadu_si128((__m128i*)&b);
         __m128i xmm0 = _mm_clmulepi64_si128(xmma, xmmb, 0x00); // l x l
         __m128i xmm1 = _mm_clmulepi64_si128(xmma, xmmb, 0x10); // h x l
         __m128i xmm2 = _mm_clmulepi64_si128(xmma, xmmb, 0x01); // l x h
         __m128i xmm3 = _mm_clmulepi64_si128(xmma, xmmb, 0x11); // h x h
         xmm0 = _mm_xor_si128(xmm0, _mm_slli_si128(xmm1, 8));
         xmm0 = _mm_xor_si128(xmm0, _mm_slli_si128(xmm2, 8));
         _mm_storeu_si128((__m128i*)&r, xmm0);
         xmm3 = _mm_xor_si128(xmm3, _mm_srli_si128(xmm1, 8));
         xmm3 = _mm_xor_si128(xmm3, _mm_srli_si128(xmm2, 8));
         _mm_storeu_si128(((__m128i*)&r)+1, xmm3);
      }
      else if constexpr (sizeof(UINT1) == 16 && sizeof(UINT2) == 16 && sizeof(UINT3) == 16)
      {
         __m128i xmma = _mm_loadu_si128((__m128i*)&a);
         __m128i xmmb = _mm_loadu_si128((__m128i*)&b);
         __m128i xmm0 = _mm_clmulepi64_si128(xmma, xmmb, 0x00); // l x l
         __m128i xmm1 = _mm_clmulepi64_si128(xmma, xmmb, 0x10); // h x l
         __m128i xmm2 = _mm_clmulepi64_si128(xmma, xmmb, 0x01); // l x h
         xmm0 = _mm_xor_si128(xmm0, _mm_slli_si128(xmm1, 8));
         xmm0 = _mm_xor_si128(xmm0, _mm_slli_si128(xmm2, 8));
         _mm_storeu_si128((__m128i*)&r, xmm0);
      }
      else if constexpr (sizeof(UINT1) == 8 && sizeof(UINT2) == 8 && sizeof(UINT3) == 16)
         _mm_storeu_si128((__m128i*)&r, _mm_clmulepi64_si128(
            _mm_loadl_epi64((__m128i*)&a),
            _mm_loadl_epi64((__m128i*)&b), 0x00));
      else if constexpr (sizeof(UINT1) == 8 && sizeof(UINT2) == 8 && sizeof(UINT3) == 8)
         _mm_storel_epi64((__m128i*)&r, _mm_clmulepi64_si128(
            _mm_loadl_epi64((__m128i*)&a), 
            _mm_loadl_epi64((__m128i*)&b), 0x00));
      else if constexpr (sizeof(UINT1) == 4 && sizeof(UINT2) == 4 && sizeof(UINT3) == 8)
         _mm_storel_epi64((__m128i*)&r, _mm_clmulepi64_si128(
            _mm_cvtsi32_si128(*(uint32_t*)&a),
            _mm_cvtsi32_si128(*(uint32_t*)&b), 0x00));
      else if constexpr (sizeof(UINT1) == 4 && sizeof(UINT2) == 4 && sizeof(UINT3) == 4)
         *(uint32_t*)&r = _mm_cvtsi128_si32(_mm_clmulepi64_si128(
            _mm_cvtsi32_si128(*(uint32_t*)&a),
            _mm_cvtsi32_si128(*(uint32_t*)&b), 0x00));
      else
   #endif
         CppCore::clmul_generic(a, b, r);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // INTEGER TO FLOAT CONVERSION
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Manually converts unsigned 64-bit integer to double precision (IEEE-754)
   /// </summary>
   INLINE double todouble(const uint64_t x, const uint32_t rounding = FE_TONEAREST)
   {
      const uint64_t MASKSIG = 0x8000000000000000ULL; // mask for 1 sign bit
      const uint64_t MASKEXP = 0x7FF0000000000000ULL; // mask for 11 exponent bits
      const uint64_t MASKMAN = 0x000FFFFFFFFFFFFFULL; // mask for 52 mantissa bits
      const uint64_t MASKHHI = 0x0010000000000000ULL; // mask for hidden high bit

   #if defined(CPPCORE_OS_WINDOWS) && defined(CPPCORE_CPU_64BIT)
      uint32_t IH;
      if (!_BitScanReverse64((unsigned long*)&IH, x)) CPPCORE_UNLIKELY
         return 0.0;
      uint32_t LZ = 64U - IH - 1U;
   #else
      if (x == 0) CPPCORE_UNLIKELY
         return 0.0;
      uint32_t LZ = (uint32_t)CppCore::lzcnt64(x); // count of leading zeros in x (1-based)
      uint32_t IH = 64U - LZ - 1U;                 // idx of high bit in x (0-based)
   #endif

      // build the zero (positive) sign bit and the exponent bits
      // exp is neg for 0-1022, zero for 1023 and pos above.
      // shift the exponent in place (52 bits mantissa)
      const uint64_t exp = (uint64_t)(IH + 1023U) << 52;
      
      // start mantissa building by left-shifting the high bit out of x.
      // this removes it and creates a fixed offset to the hidden highbit position in IEEE-754.
      uint64_t man = (x << (LZ + 1U));

      // save 12 lowbits we may lose when shifting mantissa in place in next step
      // the lowbit here is always 0 since it was always shifted in above
      // the other 11 lowbits may be set depending on how large x is (LZ)
      const uint32_t lost = man & 0xFFFU;

      // shift mantissa in final place in order to make space for 11 bits of exp and one for sign.
      // this is the step where data loss due to limited precision may happen.
      // this also moves the lost highbit to its actual position (lowbit of exp)
      man >>= (11U + 1U);

      // apply rounding based on selected mode
      switch (rounding)
      {
   #if defined(FE_DOWNWARD)
      case FE_DOWNWARD:
         break; // nothing to do
   #endif
   #if defined(FE_TOWARDZERO)
      case FE_TOWARDZERO:
         break; // nothing to do
   #endif
   #if defined(FE_UPWARD)
      case FE_UPWARD:
         // round up if we lost anything
         if (lost) man++;
         break;
   #endif
      case FE_TONEAREST:
         // round up for upper range (break tie by only rounding odd up)
         man += ((lost > 2048U) | ((lost == 2048U) & man & 1U));

         //if (_bittest((long*)&lost, 11))
         //   man += ((lost & 2047) | (man & 1)) != 0;

         // if rounding overflowed into exp bits, increment exponent and remove overflow bit.
         // disabled because just ORing the overflow into exp below gives same result here.
         //if (man & MASKEXP) { exp++; man &= MASKMAN; }
         break;
      }

      // combine the exponent bits with the mantissa bits
      // OR a possible overflow bit of mantissa into exponent
      const uint64_t ri = exp | man;
      return reinterpret_cast<const double&>(ri);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // OVERFLOW CHECKED ADDITION
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Calculates a+b=r for unsigned 8-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowadd(uint8_t a, uint8_t b, uint8_t& r)
   {
      const uint32_t t = (uint32_t)a + (uint32_t)b;
      if (t <= (uint32_t)UINT8_MAX) 
      {
         r = (uint8_t)t;
         return false;
      }
      return true;
   }

      /// <summary>
   /// Calculates a+b=r for signed 8-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowadd(int8_t a, int8_t b, int8_t& r)
   {
      const int32_t t = (int32_t)a + (int32_t)b;
      if (CppCore::isinrange(t, (int32_t)INT8_MIN, (int32_t)INT8_MAX))
      {
         r = (int8_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a+b=r for unsigned 16-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowadd(uint16_t a, uint16_t b, uint16_t& r)
   {
      const uint32_t t = (uint32_t)a + (uint32_t)b;
      if (t <= (uint32_t)UINT16_MAX) 
      {
         r = (uint16_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a+b=r for signed 16-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowadd(int16_t a, int16_t b, int16_t& r)
   {
      const int32_t t = (int32_t)a + (int32_t)b;
      if (CppCore::isinrange(t, (int32_t)INT16_MIN, (int32_t)INT16_MAX))
      {
         r = (int16_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a+b=r for unsigned 32-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowadd(uint32_t a, uint32_t b, uint32_t& r)
   {
   #if defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_uadd_overflow)
      return __builtin_uadd_overflow(a, b, &r);
   #else
      uint8_t c = 0;
      CppCore::addcarry32(a, b, r, c);
      return c;
   #endif
   }

   /// <summary>
   /// Calculates a+b=r for signed 32-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowadd(int32_t a, int32_t b, int32_t& r)
   {
   #if defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_sadd_overflow)
      return __builtin_sadd_overflow(a, b, &r);
   #elif false // likely slower
      if (((a <= 0) | (b <= INT32_MAX-a)) & ((a >= 0) | (b >= INT32_MIN-a)))
      {
         r = a + b;
         return false;
      }
      return true;
   #else // likely faster (even on 32-Bit with SSE2 64-Bit Integer)
      const int64_t t = (int64_t)a + (int64_t)b;
      if (CppCore::isinrange(t, (int64_t)INT32_MIN, (int64_t)INT32_MAX))
      {
         r = (int32_t)t;
         return false;
      }
      return true;
   #endif
   }

   /// <summary>
   /// Calculates a+b=r for unsigned 64-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowadd(uint64_t a, uint64_t b, uint64_t& r)
   {
   #if defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_uaddll_overflow)
      return __builtin_uaddll_overflow(a, b, (unsigned long long*)&r);
   #else
      uint8_t c = 0;
      CppCore::addcarry64(a, b, r, c);
      return c;
   #endif
   }

   /// <summary>
   /// Calculates a+b=r for signed 64-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowadd(int64_t a, int64_t b, int64_t& r)
   {
   #if defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_saddll_overflow)
      return __builtin_saddll_overflow(a, b, (long long*)&r);
   #else
      if (((a <= 0) | (b <= INT64_MAX-a)) & ((a >= 0) | (b >= INT64_MIN-a)))
      {
         r = a + b;
         return false;
      }
      return true;
   #endif
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // OVERFLOW CHECKED SUBTRACTION
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Calculates a-b=r for unsigned 8-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowsub(uint8_t a, uint8_t b, uint8_t& r)
   {
      const uint32_t t = (uint32_t)a - (uint32_t)b;
      if (t <= (uint32_t)UINT8_MAX) 
      {
         r = (uint8_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a-b=r for signed 8-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowsub(int8_t a, int8_t b, int8_t& r)
   {
      const int32_t t = (int32_t)a - (int32_t)b;
      if (CppCore::isinrange(t, (int32_t)INT8_MIN, (int32_t)INT8_MAX))
      {
         r = (int8_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a-b=r for unsigned 16-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowsub(uint16_t a, uint16_t b, uint16_t& r)
   {
      const uint32_t t = (uint32_t)a - (uint32_t)b;
      if (t <= (uint32_t)UINT16_MAX) 
      {
         r = (uint16_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a-b=r for signed 16-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowsub(int16_t a, int16_t b, int16_t& r)
   {
      const int32_t t = (int32_t)a - (int32_t)b;
      if (CppCore::isinrange(t, (int32_t)INT16_MIN, (int32_t)INT16_MAX))
      {
         r = (int16_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a-b=r for unsigned 32-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowsub(uint32_t a, uint32_t b, uint32_t& r)
   {
   #if defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_usub_overflow)
      return __builtin_usub_overflow(a, b, &r);
   #else
      uint8_t c = 0;
      CppCore::subborrow32(a, b, r, c);
      return c;
   #endif
   }

   /// <summary>
   /// Calculates a-b=r for signed 32-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowsub(int32_t a, int32_t b, int32_t& r)
   {
   #if defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_ssub_overflow)
      return __builtin_ssub_overflow(a, b, &r);
   #elif false // likely slower
      if (((a < 0) | (b >= -(INT32_MAX-a))) & ((a >= 0) | (b <= -(INT32_MIN-a))))
      {
         r = a - b;
         return false;
      }
      return true;
   #else // likely faster (even on 32-Bit with SSE2 64-Bit Integer)
      const int64_t t = (int64_t)a - (int64_t)b;
      if (CppCore::isinrange(t, (int64_t)INT32_MIN, (int64_t)INT32_MAX))
      {
         r = (int32_t)t;
         return false;
      }
      return true;
   #endif
   }

   /// <summary>
   /// Calculates a-b=r for unsigned 64-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowsub(uint64_t a, uint64_t b, uint64_t& r)
   {
   #if defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_usubll_overflow)
      return __builtin_usubll_overflow(a, b, (unsigned long long*)&r);
   #else
      uint8_t c = 0;
      CppCore::subborrow64(a, b, r, c);
      return c;
   #endif
   }

   /// <summary>
   /// Calculates a-b=r for signed 64-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowsub(int64_t a, int64_t b, int64_t& r)
   {
   #if defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_ssubll_overflow)
      return __builtin_ssubll_overflow(a, b, (long long*)&r);
   #else
      if (((a < 0) | (b >= -(INT64_MAX-a))) & ((a >= 0) | (b <= -(INT64_MIN-a))))
      {
         r = a - b;
         return false;
      }
      return true;
   #endif
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // OVERFLOW CHECKED MULTIPLICATION
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Calculates a*b=r for unsigned 8-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowmul(uint8_t a, uint8_t b, uint8_t& r)
   {
      const uint32_t t = (uint32_t)a * (uint32_t)b;
      if (t <= (uint32_t)UINT8_MAX) 
      {
         r = (uint8_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a*b=r for signed 8-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowmul(int8_t a, int8_t b, int8_t& r)
   {
      const int32_t t = (int32_t)a * (int32_t)b;
      if (CppCore::isinrange(t, (int32_t)INT8_MIN, (int32_t)INT8_MAX))
      {
         r = (int8_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a*b=r for unsigned 16-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowmul(uint16_t a, uint16_t b, uint16_t& r)
   {
      const uint32_t t = (uint32_t)a * (uint32_t)b;
      if (t <= (uint32_t)UINT16_MAX) 
      {
         r = (uint16_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a*b=r for signed 16-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowmul(int16_t a, int16_t b, int16_t& r)
   {
      const int32_t t = (int32_t)a * (int32_t)b;
      if (CppCore::isinrange(t, (int32_t)INT16_MIN, (int32_t)INT16_MAX))
      {
         r = (int16_t)t;
         return false;
      }
      return true;
   }

   /// <summary>
   /// Calculates a*b=r for unsigned 32-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowmul(uint32_t a, uint32_t b, uint32_t& r)
   {
   #if defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_umul_overflow)
      return __builtin_umul_overflow(a, b, &r);
   #else
      const uint64_t t = (uint64_t)a * (uint64_t)b;
      if (t <= (uint64_t)UINT32_MAX)
      {
         r = (uint32_t)t;
         return false;
      }
      else
         return true;
   #endif
   }

   /// <summary>
   /// Calculates r=a*b for signed 32-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowmul(int32_t a, int32_t b, int32_t& r)
   {
   #if defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_smul_overflow)
      return __builtin_smul_overflow(a, b, &r);
   #else
      const int64_t t = (int64_t)a * (int64_t)b;
      if (CppCore::isinrange(t, (int64_t)INT32_MIN, (int64_t)INT32_MAX))
      {
         r = (int32_t)t;
         return false;
      }
      else
         return true;
   #endif
   }

   /// <summary>
   /// Calculates a*b=r for unsigned 64-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowmul(uint64_t a, uint64_t b, uint64_t& r)
   {
   #if defined(CPPCORE_CPU_64BIT) && defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_umulll_overflow)
      return __builtin_umulll_overflow(a, b, (unsigned long long*)&r);
   #else
      uint64_t t;
      CppCore::umul128(a, b, r, t);
      return t != 0ULL;
   #endif
   }

   /// <summary>
   /// Calculates a*b=r for signed 64-Bit. Returns true if operation overflowed.
   /// </summary>
   INLINE static bool overflowmul(int64_t a, int64_t b, int64_t& r)
   {
   #if defined(CPPCORE_CPU_64BIT) && defined(CPPCORE_COMPILER_CLANG) && __has_builtin(__builtin_smulll_overflow)
      return __builtin_smulll_overflow(a, b, (long long*)&r);
   #else
      int64_t t;
      CppCore::mul128(a, b, r, t);
      return (((t != 0LL) | (r < 0LL)) & ((t != -1LL) | (r >= 0LL)));
   #endif
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // OVERFLOW CHECKED MADD+MSUB
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Template. Returns true if (v*m)+a overflowed else false and valid response in r.
   /// </summary>
   template<typename T>
   INLINE static bool overflowmadd(T& r, const T v, const T m, const T a)
   {
      return CppCore::overflowmul(v, m, r) || CppCore::overflowadd(r, a, r);
   }

   /// <summary>
   /// Template. Returns true if (v*m)-s overflowed else false and valid response in r.
   /// </summary>
   template<typename T>
   INLINE static bool overflowmsub(T& r, const T v, const T m, const T a)
   {
      return CppCore::overflowmul(v, m, r) || CppCore::overflowsub(r, a, r);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // UNSIGNED DIVISION+MODULO OPERATIONS
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Safe Division+Modulo (a/b=q,r) for 32-Bit integer. Works for any 32-Bit integers a and b, except b=0.
   /// </summary>
   INLINE static void udivmod32(uint32_t a, uint32_t b, uint32_t& q, uint32_t& r)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_MSVC)
      q = _udiv64(a, b, &r); // exists also on x86, but is buggy
   #else
      q = a / b;
      r = a % b;
   #endif
   }

   /// <summary>
   /// Safe Division+Modulo (a/b=q,r) for 64-Bit integer. Works for any 64-Bit integers a and b, except b=0.
   /// </summary>
   INLINE static void udivmod64(uint64_t a, uint64_t b, uint64_t& q, uint64_t& r)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_MSVC)
      q = _udiv128(0, a, b, &r);
   #else
      q = a / b;
      r = a % b;
   #endif
   }

   /// <summary>
   /// Safe Division+Modulo (a/b=q,r) for 16-Bit integer. Works for any 16-Bit integers a and b, except b=0.
   /// Uses the 32-Bit version internally.
   /// </summary>
   INLINE static void udivmod16(uint16_t a, uint16_t b, uint16_t& q, uint16_t& r)
   {
      uint32_t q32, r32;
      CppCore::udivmod32(a, b, q32, r32);
      q = (uint16_t)q32;
      r = (uint16_t)r32;
   }

   /// <summary>
   /// Safe Division+Modulo (a/b=q,r) for 8-Bit integer. Works for any 8-Bit integers a and b, except b=0.
   /// Uses the 32-Bit version internally.
   /// </summary>
   INLINE static void udivmod8(uint8_t a, uint8_t b, uint8_t& q, uint8_t& r)
   {
      uint32_t q32, r32;
      CppCore::udivmod32(a, b, q32, r32);
      q = (uint8_t)q32;
      r = (uint8_t)r32;
   }

   /// <summary>
   /// Unsafe Division+Modulo (a/b=q,r) for 64-bit dividend and 32-bit divisor if available on CPU.
   /// May cause integer overflow exception on q or r based on a and b (e.g. 0xFFFFFFFFFFFFFFFF / 1).
   /// Falls back to compiler provided 64/32 (usually 64/64) otherwise.
   /// </summary>
   INLINE static void udivmod64_32(uint64_t a, uint32_t b, uint32_t& q, uint32_t& r)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_MSVC)
      q = _udiv64(a, b, &r); // exists also on x86, but is buggy
   #elif defined(CPPCORE_CPU_X86ORX64) && defined(CPPCORE_COMPILER_CLANG)
      __asm("DIVL %4" : "=a" (q), "=d" (r) : "0" ((uint32_t)a), "1" ((uint32_t)(a >> 32)), "r" (b));
   #else
      q = (uint32_t)(a / b);
      r = (uint32_t)(a % b);
   #endif
   }

   /// <summary>
   /// Unsafe Division+Modulo (a/b=q,r) for 64-bit dividend and 32-bit divisor if available on CPU.
   /// May cause integer overflow exception on q or r based on a and b (e.g. 0xFFFFFFFFFFFFFFFF / 1).
   /// Falls back to compiler provided 64/32 (usually 64/64) otherwise.
   /// </summary>
   INLINE static void udivmod64_32(uint32_t ah, uint32_t al, uint32_t b, uint32_t& q, uint32_t& r)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_MSVC)
      uint64_t a = (uint64_t)al | ((uint64_t)ah << 32);
      q = _udiv64(a, b, &r); // exists also on x86, but is buggy
   #elif defined(CPPCORE_CPU_X86ORX64) && defined(CPPCORE_COMPILER_CLANG)
      __asm("DIVL %4" : "=a" (q), "=d" (r) : "0" (al), "1" (ah), "r" (b));
   #else
      uint64_t a = (uint64_t)al | ((uint64_t)ah << 32);
      q = (uint32_t)(a / b);
      r = (uint32_t)(a % b);
   #endif
   }

   /// <summary>
   /// Division+Modulo (a/b=q,r) with a and q being multiple of 32-Bit and b and r exactly 32-Bit.
   /// </summary>
   INLINE static void udivmod64_32x(const uint32_t* a, uint32_t b, uint32_t* q, uint32_t& r, const uint32_t n32)
   {
      r = 0U;
      assert(b != 0U);
      assert(n32 != 0U);
      for (uint32_t i = n32-1U; i != 0xFFFFFFFFU; i--)
         CppCore::udivmod64_32(r, a[i], b, q[i], r);
   }

   /// <summary>
   /// Division+Modulo (a/b=q,r) with a and q being multiple of 32-Bit and b and r exactly 32-Bit.
   /// Returns true if the q is zero else false.
   /// </summary>
   INLINE static bool udivmod64_32x_testzero(const uint32_t* a, uint32_t b, uint32_t* q, uint32_t& r, const uint32_t n32)
   {
      r = 0U;
      assert(b != 0U);
      assert(n32 != 0U);
      uint32_t t;
      uint32_t n = 0U;
      for (uint32_t i = n32-1U; i != 0xFFFFFFFFU; i--)
      {
         CppCore::udivmod64_32(r, a[i], b, t, r);
         n |= t;
         q[i] = t;
      }
      return n == 0U;
   }

#if defined(CPPCORE_CPU_X64)
   /// <summary>
   /// Unsafe Division+Modulo (a/b=q,r) for 128-bit dividend and 64-bit divisor if available on CPU.
   /// May cause integer overflow exception on q or r based on a and b (e.g. 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF / 1).
   /// TODO: Only available on x64
   /// </summary>
   INLINE static void udivmod128_64(uint64_t ah, uint64_t al, uint64_t b, uint64_t& q, uint64_t& r)
   {
   #if defined(CPPCORE_COMPILER_MSVC)
      q = _udiv128(ah, al, b, &r);
   #else
      __asm("DIVQ %4" : "=a" (q), "=d" (r) : "0" (al), "1" (ah), "r" (b));
   #endif
   }

   /// <summary>
   /// Division+Modulo (a/b=q,r) with a and q being multiple of 64-Bit and b and r exactly 64-Bit.
   /// </summary>
   INLINE static void udivmod128_64x(const uint64_t* a, uint64_t b, uint64_t* q, uint64_t& r, const uint32_t n64)
   {
      r = 0ULL;
      assert(b != 0U);
      assert(n64 != 0U);
      for (uint32_t i = n64-1U; i != 0xFFFFFFFFU; i--)
         CppCore::udivmod128_64(r, a[i], b, q[i], r);
   }

   /// <summary>
   /// Division+Modulo (a/b=q,r) with a and q being multiple of 64-Bit and b and r exactly 64-Bit.
   /// Returns true if the q is zero else false.
   /// </summary>
   INLINE static bool udivmod128_64x_testzero(const uint64_t* a, uint64_t b, uint64_t* q, uint64_t& r, const uint32_t n64)
   {
      r = 0ULL;
      assert(b != 0U);
      assert(n64 != 0U);
      uint64_t t;
      uint64_t n = 0ULL;
      for (uint32_t i = n64-1U; i != 0xFFFFFFFFU; i--)
      {
         CppCore::udivmod128_64(r, a[i], b, t, r);
         n |= t;
         q[i] = t;
      }
      return n == 0ULL;
   }

   /// <summary>
   /// Division+Modulo (a/b=q,r) for 128-bit dividend, divisor, quotient and remainer if available on CPU.
   /// Uses udivmod128_64(). TODO: Only available on x64
   /// </summary>
   INLINE static void udivmod128_128(
      uint64_t  ah, uint64_t  al, 
      uint64_t  bh, uint64_t  bl, 
      uint64_t& qh, uint64_t& ql, 
      uint64_t& rh, uint64_t& rl)
   {
      assert((bh | bl) != 0);
      uint8_t c;

      const bool b0 = (bh == 0);
      const bool b1 = (bh - ah == 0);

      // 64/64 only
      if ((ah | bh) == 0)
      {
         qh = rh = 0;
         ql = al / bl;
         rl = al % bl;
         return;
      }
      
      // div by 1
      //if ((bh == 0) & (bl == 1))
      if ((bh | (bl - 1U)) == 0)
      {
         qh = ah;
         ql = al;
         rh = rl = 0;
         return;
      }

      // divisor larger dividend (q=0,r=dividend)
      if (((bh > ah) | (b1 & (bl > al))) != 0)
      {
         qh = ql = 0;
         rh = ah;
         rl = al;
         return;
      }

      // div by pow2 (single bit set)
      if (CppCore::popcnt64(bh) + CppCore::popcnt64(bl) - 1U == 0U)
      {
         uint32_t ntz = CppCore::tzcnt64(bl);
         if (ntz == 64U)
            ntz += CppCore::tzcnt64(bh);
         // quotient by rightshift
         if (ntz <= 64)
         {
            ql = CppCore::shrd64(al, ah, ntz);
            qh = ah >> ntz;
         }
         else
         {
            ql = ah >> (ntz - 64);
            qh = 0;
         }
         // remainder by and
         c = 0;
         CppCore::subborrow64(bl, 1, bl, c);
         bh -= c;
         rh = ah & bh;
         rl = al & bl;
         return;
      }

      // x/x=1
      if ((b1 & (al-bl == 0)) != 0)
      {
         qh = rh = rl = 0;
         ql = 1;
         return;
      }

      // 128/64
      if (b0)
      {
         // 128/64=64
         if (ah < bl)
         {
            CppCore::udivmod128_64(ah, al, bl, ql, rl);
            qh = 0;
            rh = 0;
            return;
         }
         // 128/64=128
         else
         {
            qh = ah / bl;
            rh = ah % bl;
            CppCore::udivmod128_64(rh, al, bl, ql, rl);
            rh = 0;
         }
      }

      // 128/128
      else
      {
         uint64_t dummy;
         const uint32_t n = (uint32_t)CppCore::lzcnt64(bh);
         const uint64_t v1h = n ? CppCore::shld64(bh, bl, n) : bh;
         const uint64_t u1h = ah >> 1;
         const uint64_t u1l = CppCore::shrd64(al, ah, 1);
         udivmod128_64(u1h, u1l, v1h, ql, dummy);
         qh = 0;
         ql >>= (63U - n);
         if (ql)
         {
            c = 0;
            CppCore::subborrow64(ql, 1, ql, c);
            qh -= c;
         }
         CppCore::umul128(ql, qh, bl, bh, rl, rh);
         c = 0;
         CppCore::subborrow64(al, rl, rl, c);
         CppCore::subborrow64(ah, rh, rh, c);
         if ((rh > bh) | ((rh == bh) & (rl >= bl)))
         {
            c = 0;
            CppCore::addcarry64(ql, 1U, ql, c);
            qh += c;
            c = 0;
            CppCore::subborrow64(rl, bl, rl, c);
            CppCore::subborrow64(rh, bh, rh, c);
         }
      }
   }
#endif

   /// <summary>
   /// a/b=q,r with 8/8=8,8
   /// </summary>
   INLINE static void udivmod(uint8_t& q, uint8_t& r, uint8_t a, uint8_t b)
   {
      CppCore::udivmod8(a, b, q, r);
   }

   /// <summary>
   /// a/b=q,r with 8/16=8,16
   /// </summary>
   INLINE static void udivmod(uint8_t& q, uint16_t& r, uint8_t a, uint16_t b)
   {
      uint16_t t;
      CppCore::udivmod16(a, b, t, r);
      q = (uint8_t)t;
   }

   /// <summary>
   /// a/b=q,r with 8/32=8,32
   /// </summary>
   INLINE static void udivmod(uint8_t& q, uint32_t& r, uint8_t a, uint32_t b)
   {
      uint32_t t;
      CppCore::udivmod32(a, b, t, r);
      q = (uint8_t)t;
   }

   /// <summary>
   /// a/b=q,r with 8/64=8,64
   /// </summary>
   INLINE static void udivmod(uint8_t& q, uint64_t& r, uint8_t a, uint64_t b)
   {
      uint64_t t;
      CppCore::udivmod64(a, b, t, r);
      q = (uint8_t)t;
   }

   /// <summary>
   /// a/b=q,r with 16/16=16,16
   /// </summary>
   INLINE static void udivmod(uint16_t& q, uint16_t& r, uint16_t a, uint16_t b)
   {
      CppCore::udivmod16(a, b, q, r);
   }

   /// <summary>
   /// a/b=q,r with 16/32=16,32
   /// </summary>
   INLINE static void udivmod(uint16_t& q, uint32_t& r, uint16_t a, uint32_t b)
   {
      uint32_t t;
      CppCore::udivmod32(a, b, t, r);
      q = (uint16_t)t;
   }

   /// <summary>
   /// a/b=q,r with 16/64=16,64
   /// </summary>
   INLINE static void udivmod(uint16_t& q, uint64_t& r, uint16_t a, uint64_t b)
   {
      uint64_t t;
      CppCore::udivmod64(a, b, t, r);
      q = (uint16_t)t;
   }

   /// <summary>
   /// a/b=q,r with 32/32=32,32
   /// </summary>
   INLINE static void udivmod(uint32_t& q, uint32_t& r, uint32_t a, uint32_t b)
   {
      CppCore::udivmod32(a, b, q, r);
   }

   /// <summary>
   /// a/b=q,r with 32/64=32,64
   /// </summary>
   INLINE static void udivmod(uint32_t& q, uint64_t& r, uint32_t a, uint64_t b)
   {
      uint64_t t;
      CppCore::udivmod64(a, b, t, r);
      q = (uint32_t)t;
   }

   /// <summary>
   /// a/b=q,r with 64/64=64,64
   /// </summary>
   INLINE static void udivmod(uint64_t& q, uint64_t& r, uint64_t a, uint64_t b)
   {
      CppCore::udivmod64(a, b, q, r);
   }

   /// <summary>
   /// a/b=q,r with N32/32=N32,32
   /// </summary>
   template<typename UINT>
   INLINE static void udivmod(UINT& q, uint32_t& r, const UINT& a, uint32_t b)
   {
      static_assert(sizeof(UINT) % 4 == 0);
   #if defined(CPPCORE_CPU_X64)
      if constexpr (sizeof(UINT) % 8 == 0)
      {
         uint64_t r64;
         CppCore::udivmod128_64x((const uint64_t*)&a, b, (uint64_t*)&q, r64, sizeof(UINT)/8);
         r = (uint32_t)r64;
      }
      else
   #endif
      {
         CppCore::udivmod64_32x((const uint32_t*)&a, b, (uint32_t*)&q, r, sizeof(UINT)/4);
      }
   }

#if defined(CPPCORE_CPU_X64)
   /// <summary>
   /// a/b=q,r with N64/64=N64,64
   /// </summary>
   template<typename UINT>
   INLINE static void udivmod(UINT& q, uint64_t& r, const UINT& a, uint64_t b)
   {
      static_assert(sizeof(UINT) % 8 == 0);
      CppCore::udivmod128_64x((const uint64_t*)&a, b, (uint64_t*)&q, r, sizeof(UINT)/8);
   }
#endif

   /// <summary>
   /// a/b=q,r with 8/8=8,8
   /// </summary>
   INLINE static bool udivmod_testzero(uint8_t a, uint8_t b, uint8_t& q, uint8_t& r)
   {
      CppCore::udivmod8(a, b, q, r);
      return q == 0U;
   }

   /// <summary>
   /// a/b=q,r with 8/16=8,16
   /// </summary>
   INLINE static bool udivmod_testzero(uint8_t a, uint16_t b, uint8_t& q, uint16_t& r)
   {
      uint16_t t;
      CppCore::udivmod16(a, b, t, r);
      q = (uint8_t)t;
      return q == 0U;
   }

   /// <summary>
   /// a/b=q,r with 8/32=8,32
   /// </summary>
   INLINE static bool udivmod_testzero(uint8_t a, uint32_t b, uint8_t& q, uint32_t& r)
   {
      uint32_t t;
      CppCore::udivmod32(a, b, t, r);
      q = (uint8_t)t;
      return q == 0U;
   }

   /// <summary>
   /// a/b=q,r with 8/64=8,64
   /// </summary>
   INLINE static bool udivmod_testzero(uint8_t a, uint64_t b, uint8_t& q, uint64_t& r)
   {
      uint64_t t;
      CppCore::udivmod64(a, b, t, r);
      q = (uint8_t)t;
      return q == 0U;
   }

   /// <summary>
   /// a/b=q,r with 16/16=16,16
   /// </summary>
   INLINE static bool udivmod_testzero(uint16_t a, uint16_t b, uint16_t& q, uint16_t& r)
   {
      CppCore::udivmod16(a, b, q, r);
      return q == 0U;
   }

   /// <summary>
   /// a/b=q,r with 16/32=16,32
   /// </summary>
   INLINE static bool udivmod_testzero(uint16_t a, uint32_t b, uint16_t& q, uint32_t& r)
   {
      uint32_t t;
      CppCore::udivmod32(a, b, t, r);
      q = (uint16_t)t;
      return q == 0U;
   }

   /// <summary>
   /// a/b=q,r with 16/64=16,64
   /// </summary>
   INLINE static bool udivmod_testzero(uint16_t a, uint64_t b, uint16_t& q, uint64_t& r)
   {
      uint64_t t;
      CppCore::udivmod64(a, b, t, r);
      q = (uint16_t)t;
      return q == 0U;
   }

   /// <summary>
   /// a/b=q,r with 32/32=32,32
   /// </summary>
   INLINE static bool udivmod_testzero(uint32_t a, uint32_t b, uint32_t& q, uint32_t& r)
   {
      CppCore::udivmod32(a, b, q, r);
      return q == 0U;
   }

   /// <summary>
   /// a/b=q,r with 32/64=32,64
   /// </summary>
   INLINE static bool udivmod_testzero(uint32_t a, uint64_t b, uint32_t& q, uint64_t& r)
   {
      uint64_t t;
      CppCore::udivmod64(a, b, t, r);
      q = (uint32_t)t;
      return q == 0U;
   }

   /// <summary>
   /// a/b=q,r with 64/64=64,64
   /// </summary>
   INLINE static bool udivmod_testzero(uint64_t a, uint64_t b, uint64_t& q, uint64_t& r)
   {
      CppCore::udivmod64(a, b, q, r);
      return q == 0U;
   }

   /// <summary>
   /// a/b=q,r with N32/32=N32,32
   /// </summary>
   template<typename UINT>
   INLINE static bool udivmod_testzero(const UINT& a, uint32_t b, UINT& q, uint32_t& r)
   {
      static_assert(sizeof(UINT) % 4 == 0);
   #if defined(CPPCORE_CPU_X64)
      if constexpr (sizeof(UINT) % 8 == 0)
      {
         uint64_t r64;
         bool iszero = CppCore::udivmod128_64x_testzero((const uint64_t*)&a, b, (uint64_t*)&q, r64, sizeof(UINT)/8);
         r = (uint32_t)r64;
         return iszero;
      }
      else
   #endif
      {
         return CppCore::udivmod64_32x_testzero((const uint32_t*)&a, b, (uint32_t*)&q, r, sizeof(UINT)/4);
      }
   }

#if defined(CPPCORE_CPU_X64)
   /// <summary>
   /// a/b=q,r with N64/64=N64,64
   /// </summary>
   template<typename UINT>
   INLINE static bool udivmod_testzero(const UINT& a, uint64_t b, UINT& q, uint64_t& r)
   {
      static_assert(sizeof(UINT) % 8 == 0);
      return CppCore::udivmod128_64x_testzero((const uint64_t*)&a, b, (uint64_t*)&q, r, sizeof(UINT)/8);
   }
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SIGNED DIVISION+MODULO OPERATIONS
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Safe Division+Modulo (a/b=q,r) for 32-Bit signed Integer. Works for any 32-Bit integers a and b, except b=0.
   /// </summary>
   INLINE static void divmod32(int32_t a, int32_t b, int32_t& q, int32_t& r)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_MSVC)
      q = _div64(a, b, &r); // exists also on x86, but is buggy
   #elif false && defined(CPPCORE_CPU_X86ORX64) && defined(CPPCORE_COMPILER_CLANG)
      // TODO: Use Assembly like in udivmod32
   #else
      q = a / b;
      r = a % b;
   #endif
   }

   /// <summary>
   /// Safe Division+Modulo (a/b=q,r) for 64-Bit signed Integer. Works for any 64-Bit integers a and b, except b=0.
   /// </summary>
   INLINE static void divmod64(int64_t a, int64_t b, int64_t& q, int64_t& r)
   {
   #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_MSVC)
      q = _div128(a < 0 ? -1 : 0, a, b, &r);
   #elif false && defined(CPPCORE_CPU_X64) && defined(CPPCORE_COMPILER_CLANG)
      // TODO: Use Assembly like in udivmod64
   #else
      q = a / b;
      r = a % b;
   #endif
   }

   /// <summary>
   /// Safe Division+Modulo (a/b=q,r) for 16-Bit signed Integer. Works for any 16-Bit integers a and b, except b=0.
   /// Uses 32-Bit version internally.
   /// </summary>
   INLINE static void divmod16(int16_t a, int16_t b, int16_t& q, int16_t& r)
   {
      int32_t q32, r32;
      CppCore::divmod32(a, b, q32, r32);
      q = (int16_t)q32;
      r = (int16_t)r32;
   }

   /// <summary>
   /// Safe Division+Modulo (a/b=q,r) for 8-Bit signed Integer. Works for any 8-Bit integers a and b, except b=0.
   /// Uses 32-Bit version internally.
   /// </summary>
   INLINE static void divmod8(int8_t a, int8_t b, int8_t& q, int8_t& r)
   {
      int32_t q32, r32;
      CppCore::divmod32(a, b, q32, r32);
      q = (int8_t)q32;
      r = (int8_t)r32;
   }

   /// <summary>
   /// Same as divmod8()
   /// </summary>
   INLINE static void divmod(int8_t a, int8_t b, int8_t& q, int8_t& r)
   {
      CppCore::divmod8(a, b, q, r);
   }

   /// <summary>
   /// Same as divmod16()
   /// </summary>
   INLINE static void divmod(int16_t a, int16_t b, int16_t& q, int16_t& r)
   {
      CppCore::divmod16(a, b, q, r);
   }

   /// <summary>
   /// Same as divmod32()
   /// </summary>
   INLINE static void divmod(int32_t a, int32_t b, int32_t& q, int32_t& r)
   {
      CppCore::divmod32(a, b, q, r);
   }

   /// <summary>
   /// Same as divmod64()
   /// </summary>
   INLINE static void divmod(int64_t a, int64_t b, int64_t& q, int64_t& r)
   {
      CppCore::divmod64(a, b, q, r);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MULTIPLICATION
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Simple Multiplication (a*b=r) in up to O(n*n) automatically selecting 64-Bit or 32-Bit operations and chunks.
   /// Calculates all bits of r, performing a full wide multiplication if sizeof(r) larger-equal sizeof(a)+sizeof(b).
   /// </summary>
   template<typename UINT1, typename UINT2, typename UINT3>
   INLINE static void umul(const UINT1& a, const UINT2& b, UINT3& r)
   {
      if      constexpr (sizeof(UINT1) < sizeof(size_t)) { CppCore::umul((size_t)a, b, r); }
      else if constexpr (sizeof(UINT2) < sizeof(size_t)) { CppCore::umul(a, (size_t)b, r); }
      else if constexpr (sizeof(UINT3) < sizeof(size_t)) 
      { 
         size_t t; 
         CppCore::umul(a, b, t); 
         CppCore::clone(r, *(UINT3*)&t); 
      }
      else if constexpr (sizeof(UINT1) % sizeof(size_t) != 0)
      {
         Padded<UINT1> t(a);
         CppCore::umul(t, b, r);
      }
      else if constexpr (sizeof(UINT2) % sizeof(size_t) != 0)
      {
         Padded<UINT2> t(b);
         CppCore::umul(a, t, r);
      }
      else if constexpr (sizeof(UINT3) % sizeof(size_t) != 0)
      {
         Padded<UINT3> t;
         CppCore::umul(a, b, t);
         CppCore::clone(r, t.v);
      }
   #if defined(CPPCORE_CPU_64BIT)
      else if constexpr (sizeof(UINT1) == 16 && sizeof(UINT2) == 16 && sizeof(UINT3) == 16)
      {
         uint64_t* ap = (uint64_t*)&a;
         uint64_t* bp = (uint64_t*)&b;
         uint64_t* rp = (uint64_t*)&r;
         CppCore::umul128(ap[0], ap[1], bp[0], bp[1], rp[0], rp[1]);
      }
      else if constexpr (sizeof(UINT1) % 8 == 0 && sizeof(UINT2) % 8 == 0 && sizeof(UINT3) % 8 == 0)
      {
         // 64-Bit CPU and Multiples of 64-Bit
         constexpr size_t NA = sizeof(UINT1) / 8;
         constexpr size_t NB = sizeof(UINT2) / 8;
         constexpr size_t NR = sizeof(UINT3) / 8;
         assert(NB == 1 || (((void*)&a != (void*)&r) && ((void*)&b != (void*)&r)));
         uint64_t* ap = (uint64_t*)&a;
         uint64_t* bp = (uint64_t*)&b;
         uint64_t* rp = (uint64_t*)&r;
         uint64_t  tl, th, bj, k;
         uint8_t   c;
         for (size_t i = NA+NB; i < NR; i++)
            rp[i] = 0ULL;
         bj = *bp++;
         CppCore::umul128(*ap++, bj, *rp++, k);  // mulx
         for (size_t i = 1; i < MIN(NA,NR); i++, ap++, rp++)
         {
            CppCore::umul128(*ap, bj, tl, th);   // mulx
            c = 0;
            CppCore::addcarry64(tl, k, *rp, c);  // add
            CppCore::addcarry64(th, 0ULL, k, c); // adc
         }
         if constexpr (NA < NR)
            *rp = k;
         for (size_t j = 1; j < NB; j++)
         {
            k  = 0ULL;
            bj = *bp++;
            ap = (uint64_t*)&a;
            rp = &((uint64_t*)&r)[j];
            for (size_t i = 0; i < NA && i+j < NR; i++, ap++, rp++)
            {
               CppCore::umul128(*ap, bj, tl, th);    // mulx
               c = 0;
               CppCore::addcarry64(tl, *rp, tl, c);  // add
               CppCore::addcarry64(th, 0ULL, th, c); // adc
               c = 0;
               CppCore::addcarry64(tl, k, *rp, c);   // add
               CppCore::addcarry64(th, 0ULL, k, c);  // adc
            }
            if (j+NA < NR)
               *rp = k;
         }
      }
   #endif
      else if constexpr (sizeof(UINT1) % 4 == 0 && sizeof(UINT2) % 4 == 0 && sizeof(UINT3) % 4 == 0)
      {
         // 32/64-Bit CPU and Multiples of 32-Bit
         constexpr size_t NA = sizeof(UINT1) / 4;
         constexpr size_t NB = sizeof(UINT2) / 4;
         constexpr size_t NR = sizeof(UINT3) / 4;
         assert(NB == 1 || (((void*)&a != (void*)&r) && ((void*)&b != (void*)&r)));
         uint32_t* ap = (uint32_t*)&a;
         uint32_t* bp = (uint32_t*)&b;
         uint32_t* rp = (uint32_t*)&r;
         uint32_t tl, th, bj, k;
         uint8_t  c;
         for (size_t i = NA+NB; i < NR; i++)
            rp[i] = 0U;
         bj = *bp++;
         CppCore::umul64(*ap++, bj, *rp++, k);
         for (size_t i = 1; i < MIN(NA,NR); i++, ap++, rp++)
         {
            CppCore::umul64(*ap, bj, tl, th);
            c = 0;
            CppCore::addcarry32(tl, k, *rp, c);
            CppCore::addcarry32(th, 0U, k, c);
         }
         if constexpr (NA < NR)
            *rp = k;
         for (size_t j = 1; j < NB; j++)
         {
            k  = 0U;
            bj = *bp++;
            ap = (uint32_t*)&a;
            rp = &((uint32_t*)&r)[j];
            CPPCORE_UNROLL
            for (size_t i = 0; i < NA && i+j < NR; i++, ap++, rp++)
            {
               CppCore::umul64(*ap, bj, tl, th);
               c = 0;
               CppCore::addcarry32(tl, *rp, tl, c);
               CppCore::addcarry32(th, 0U, th, c);
               c = 0;
               CppCore::addcarry32(tl, k, *rp, c);
               CppCore::addcarry32(th, 0U, k, c);
            }
            if (j+NA < NR)
               *rp = k;
         }
      }
   }

   /// <summary>
   /// Template Specialization for 8x8=8
   /// </summary>
   template<> INLINE void umul(const uint8_t& a, const uint8_t& b, uint8_t& r)
   {
      r = a * b;
   }

   /// <summary>
   /// Template Specialization for 8x8=16
   /// </summary>
   template<> INLINE void umul(const uint8_t& a, const uint8_t& b, uint16_t& r)
   {
      r = (uint16_t)a * b;
   }

   /// <summary>
   /// Template Specialization for 16x16=16
   /// </summary>
   template<> INLINE void umul(const uint16_t& a, const uint16_t& b, uint16_t& r)
   {
      r = a * b;
   }

   /// <summary>
   /// Template Specialization for 16x16=32
   /// </summary>
   template<> INLINE void umul(const uint16_t& a, const uint16_t& b, uint32_t& r)
   {
      r = (uint32_t)a * b;
   }

   /// <summary>
   /// Template Specialization for 32x32=32
   /// </summary>
   template<> INLINE void umul(const uint32_t& a, const uint32_t& b, uint32_t& r)
   {
      r = a * b;
   }

   /// <summary>
   /// Template Specialization for 32x32=64
   /// </summary>
   template<> INLINE void umul(const uint32_t& a, const uint32_t& b, uint64_t& r)
   {
      r = (uint64_t)a * b;
   }

   /// <summary>
   /// Template Specialization for 64x64=64
   /// </summary>
   template<> INLINE void umul(const uint64_t& a, const uint64_t& b, uint64_t& r)
   {
      r = a * b;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // UNSIGNED DIVISION+MODULO BY CONSTANTS
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Divides a by 3. Storing quotient in q and remainder in r.
   /// This is for reference. Use only if template specialization exists.
   /// TODO: Write tests.
   /// </summary>
   template<typename UINT1, typename UINT2>
   INLINE static void udivmodby3(const UINT1& a, UINT1& q, UINT2& r)
   {
      static_assert(sizeof(UINT1) % 4 == 0);
      static_assert(sizeof(UINT2) % 4 == 0);
      struct UINTX2 { UINT1 x[2]; };
      UINTX2 prod;
      UINT1  magic;
      if constexpr (sizeof(UINT1) % 8 == 0)
      {
         uint64_t* mp = (uint64_t*)&magic;
         constexpr size_t N64 = sizeof(UINT1) / 8;
         mp[0] = 0xAAAAAAAAAAAAAAABULL;
         for (size_t i = 1; i < N64; i++)
            mp[i] = 0xAAAAAAAAAAAAAAAAULL;
      }
      else
      {
         uint32_t* mp = (uint32_t*)&magic;
         constexpr size_t N32 = sizeof(UINT1) / 4;
         mp[0] = 0xAAAAAAABULL;
         for (size_t i = 1; i < N32; i++)
            mp[i] = 0xAAAAAAAAULL;
      }
      CppCore::umul(a, magic, prod);
      q = prod.x[1] >> 1;
      r = a - q*3U;
   }

   /// <summary>
   /// Template Specialization
   /// </summary>
   template<> INLINE void udivmodby3<uint32_t, uint32_t>(const uint32_t& a, uint32_t& q, uint32_t& r)
   {
      uint32_t l, h;
      CppCore::umul64(a, 0xAAAAAAABU, l, h);
      h >>= 1;
      q = h;
      r = a - h*3U;
   }

   /// <summary>
   /// Template Specialization
   /// </summary>
   template<> INLINE void udivmodby3<uint64_t, uint64_t>(const uint64_t& a, uint64_t& q, uint64_t& r)
   {
      uint64_t l, h;
      CppCore::umul128(a, 0xAAAAAAAAAAAAAAABULL, l, h);
      h >>= 1;
      q = h;
      r = a - h*3U;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // POW
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// a^b
   /// </summary>
   template<typename UINT, typename UINT2>
   INLINE static UINT upow(UINT a, UINT2 b)
   {
      CPPCORE_ALIGN_OPTIM(UINT) r(1U);
      while (b != 0U)
      {
         if (((uint32_t)b & 1U) != 0U)
            r *= a;
         b >>= 1;
         a *= a;
      }
      return r;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MULTI WORD DIVISIONS (u/v=q,r)
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   #pragma warning(disable:6255 6385)
   /// <summary>
   /// Knuth's Multi-Word Divison+Modulo Algorithm from Hacker's Delight.
   /// This is for reference only. See optimized variants.
   /// </summary>
   INLINE static bool udivmod(
            uint16_t q[],  // quotient
            uint16_t r[],  // remainder
      const uint16_t u[],  // divident
      const uint16_t v[],  // divisor
      const uint32_t m,    // num words in u
            uint32_t n,    // num words in v
            uint16_t vn[], // vn mem
      const uint32_t vnl,  // num words in vn (must be >= n)
            uint16_t un[], // un mem
      const uint32_t unl)  // num words in un (must be >= m+1)
   {
      const uint32_t b = 65536U; // Number base (16 bits).
      uint32_t qhat, rhat;       // Estimated quotient and remainder digit.
      uint32_t p;                // Product of two digits.
      int32_t  t, k;             // Intermediate Results

      // ignore leading zero highwords on divisor
      // this is a requirement of the algorithm
      while (n > 0U && v[n-1] == 0)
         n--;

      const uint32_t VNWORDS = n;
      const uint32_t UNWORDS = m + 1U;

      // invalid params (division by zero or..)
      if (((m < n) | (n == 0) | (vnl < VNWORDS) | (unl < UNWORDS)) == 1)
         return false;

      // single digit divison case
      if (n == 1) 
      {
         k = 0;
         for (uint32_t j = m-1; j != UINT32_MAX; j--) 
         {
            q[j] = (k*b + u[j]) / v[0];
            k    = (k*b + u[j]) - q[j]*v[0];
         }
         if (r != NULL)
            r[0] = k;
         return true;
      }

      // Normalize by shifting v left just enough so that
      // its high-order bit is on, and shift u left the
      // same amount. We may have to append a high-order
      // digit on the dividend; we do that unconditionally.
      const uint32_t s = CppCore::lzcnt32(v[n-1]) - 16U; // 0 <= s <= 16.

      // prepare vn
      for (uint32_t i = n-1; i > 0U; i--)
         vn[i] = (v[i] << s) | (v[i-1] >> (16U-s));
      vn[0] = v[0] << s;
      
      // prepare un
      un[m] = u[m-1] >> (16U-s);
      for (uint32_t i = m-1; i > 0U; i--)
         un[i] = (u[i] << s) | (u[i-1] >> (16U-s));
      un[0] = u[0] << s;

      // main loop
      for (uint32_t j = m - n; j != UINT32_MAX; j--)
      {
         // Compute estimate qhat of q[j].
         qhat = (un[j+n] * b + un[j+n-1]) / vn[n-1];
         rhat = (un[j+n] * b + un[j+n-1]) - qhat * vn[n-1];
      again:
         if (qhat >= b || qhat * vn[n-2] > b * rhat + un[j+n-2])
         {
            qhat = qhat - 1;
            rhat = rhat + vn[n-1];
            if (rhat < b) goto again;
         }
         // Multiply and subtract.
         k = 0;
         for (uint32_t i = 0; i < n; i++) {
            p = qhat * vn[i];
            t = un[i+j] - k - (p & 0xFFFF);
            un[i+j] = t;
            k = (p >> 16) - (t >> 16);
         }
         t = un[j+n] - k;
         un[j+n] = t;
         q[j] = qhat;       // Store quotient digit.
         if (t < 0) {       // If we subtracted too
            q[j] = q[j]-1U; // much, add back.
            k = 0;
            for (uint32_t i = 0; i < n; i++) {
               t = un[i + j] + vn[i] + k;
               un[i+j] = t;
               k = t >> 16;
            }
            un[j+n] = un[j+n] + k;
         }
      }

      // If the caller wants the remainder, unnormalize
      // it and pass it back.
      if (r != NULL) {
         for (uint32_t i = 0; i < n; i++)
            r[i] = (un[i] >> s) | (un[i+1] << (16U-s));
      }

      return true;
   }
   #pragma warning(default:6255 6385)

   /// <summary>
   /// Division+Modulo for any sized Integers that are multiples of 32-Bit.
   /// Based on Knuth's Algorithm in Hacker's Delight. (q=u/v, r=u%v)
   /// </summary>
   template<typename UINT1, typename UINT2>
   INLINE static bool udivmod(UINT1& q, UINT2& r, const UINT1& u, const UINT2& v, UINT1 mem[2])
   {
      static_assert(sizeof(UINT1) % 4 == 0);
      static_assert(sizeof(UINT2) % 4 == 0);
      static_assert(sizeof(UINT1) >= sizeof(UINT2));
      assert(&q != &u && &r != &v);
      CppCore::clear(q);
   #if defined(CPPCORE_CPU_X64)
      if constexpr (sizeof(UINT1) % 8 == 0 && sizeof(UINT2) % 8 == 0)
      {
         // using 64-bit chunks
         constexpr uint32_t M = sizeof(UINT1) / 8;
         constexpr uint32_t N = sizeof(UINT2) / 8;
         uint64_t* qp  = (uint64_t*)&q;
         uint64_t* rp  = (uint64_t*)&r;
         uint64_t* up  = (uint64_t*)&u;
         uint64_t* vp  = (uint64_t*)&v;
         uint64_t* unp = (uint64_t*)mem;
         uint64_t* vn;
         uint32_t  n = N;
         while (n != 0U && vp[n-1] == 0U)
            n--;
         if (n == 0U)
            return false;
         if (n == 1U) {
            uint64_t k;
            CppCore::clear(r);
            CppCore::udivmod128_64x(up, vp[0], qp, k, M);
            rp[0] = k;
            return true;
         }
         const auto S((uint8_t)CppCore::lzcnt(vp[n-1]));
         if (S) {
            CppCore::clear(r);
            CppCore::shl64x(vp, rp, n, S);
            vn = rp;
            unp[M] = up[M-1] >> (64U-S);
            CppCore::shl64x(up, unp, M, S);
         }
         else {
            vn = vp;
            CppCore::clone(mem[0], u);
            unp[M] = 0U;
         }
         const auto VNN1 = vn[n-1];
         const auto VNN2 = vn[n-2];
         for (uint32_t j = M-n; j != UINT32_MAX; j--)
         {
            auto* unpj = &unp[j];
            const auto UNJN  = unpj[n];
            const auto UNJN2 = unpj[n-2];
            uint64_t kl, kh, ql, qh, pl, ph;
            uint64_t rhat;
            uint8_t  c;
            if (VNN1 <= UNJN) {
               CppCore::udivmod128_64(0ULL, UNJN,  VNN1, qh, rhat);
               CppCore::udivmod128_64(rhat, unpj[n-1], VNN1, ql, rhat);
            }
            else {
               qh = 0ULL;
               CppCore::udivmod128_64(UNJN, unpj[n-1], VNN1, ql, rhat);
            }
            do {
               if (qh == 0ULL) {
                  CppCore::umul128(ql, VNN2, kl, kh);
                  if (((kh > rhat) | ((kh == rhat) & (kl > UNJN2))) == 0)
                     break;
               }
               c = 0;
               CppCore::usub128(ql, qh, 1ULL, 0ULL, ql, qh);
               CppCore::addcarry64(rhat, VNN1, rhat, c);
            } while (c == 0);
            CppCore::umul128(ql, *vn, kl, ph);
            CppCore::usub128(*unpj, 0ULL, kl, 0ULL, *unpj, kh);
            CppCore::usub128(ph, 0ULL, kh, 0ULL-(kh>>63), kl, kh);
            for (uint32_t i = 1; i < n; i++) {
               CppCore::umul128(ql, vn[i], pl, ph);
               CppCore::uadd128(kl, kh, pl, 0ULL, kl, kh);
               CppCore::usub128(unpj[i], 0ULL, kl, kh, unpj[i], kh);
               CppCore::usub128(ph, 0ULL, kh, 0ULL-(kh>>63), kl, kh);
            }
            CppCore::usub128(unpj[n], 0ULL, kl, kh, kl, kh);
            if (kh >> 63) {
               qp[j] = ql - 1ULL;
               c = 0;
               for (uint32_t i = 0; i < n; i++)
                  CppCore::addcarry64(unpj[i], vn[i], unpj[i], c);
               CppCore::addcarry64(kl, 0ULL, unpj[n], c);
            }
            else {
               qp[j] = ql;
               unpj[n] = kl;
            }
         }
         if (S) { CppCore::shr64x(unp, rp, n, S); }
         else   { CppCore::clone(r, *(UINT2*)&mem[0]); }
      }
      else
   #endif
      {
         // using 32-bit chunks
         constexpr uint32_t M = sizeof(UINT1) / 4;
         constexpr uint32_t N = sizeof(UINT2) / 4;
         uint32_t* qp  = (uint32_t*)&q;
         uint32_t* rp  = (uint32_t*)&r;
         uint32_t* up  = (uint32_t*)&u;
         uint32_t* vp  = (uint32_t*)&v;
         uint32_t* unp = (uint32_t*)mem;
         uint32_t* vn;
         uint32_t  n = N;
         while (n != 0U && vp[n-1] == 0U)
            n--;
         if (n == 0U)
            return false;
         if (n == 1U) {
            uint32_t k;
            CppCore::clear(r);
            CppCore::udivmod64_32x(up, vp[0], qp, k, M);
            rp[0] = k;
            return true;
         }
         const auto S((uint8_t)CppCore::lzcnt(vp[n-1]));
         if (S) {
            CppCore::clear(r);
            CppCore::shl32x(vp, rp, n, S);
            vn = rp;
            unp[M] = up[M-1] >> (32U-S);
            CppCore::shl32x(up, unp, M, S);
         }
         else {
            vn = vp;
            CppCore::clone(mem[0], u);
            unp[M] = 0U;
         }
         const auto VNN1 = vn[n-1];
         const auto VNN2 = vn[n-2];
         for (uint32_t j = M-n; j != UINT32_MAX; j--)
         {
            auto* unpj = &unp[j];
            const auto UNJN  = unpj[n];
            const auto UNJN2 = unpj[n-2];
            uint32_t kl, kh, ql, qh, pl, ph;
            uint32_t rhat;
            uint8_t  c;
            if (VNN1 <= UNJN) {
               CppCore::udivmod64_32(0U,   UNJN,  VNN1, qh, rhat);
               CppCore::udivmod64_32(rhat, unpj[n-1], VNN1, ql, rhat);
            }
            else {
               qh = 0U;
               CppCore::udivmod64_32(UNJN, unpj[n-1], VNN1, ql, rhat);
            }
            do {
               if (qh == 0U) {
                  CppCore::umul64(ql, VNN2, kl, kh);
                  if (((kh > rhat) | ((kh == rhat) & (kl > UNJN2))) == 0)
                     break;
               }
               c = 0;
               CppCore::usub64(ql, qh, 1U, 0U, ql, qh);
               CppCore::addcarry32(rhat, VNN1, rhat, c);
            } while (c == 0);
            CppCore::umul64(ql, *vn, kl, ph);
            CppCore::usub64(*unpj, 0U, kl, 0U, *unpj, kh);
            CppCore::usub64(ph, 0U, kh, 0U-(kh>>31), kl, kh);
            for (uint32_t i = 1; i < n; i++) {
               CppCore::umul64(ql, vn[i], pl, ph);
               CppCore::uadd64(kl, kh, pl, 0U, kl, kh);
               CppCore::usub64(unpj[i], 0U, kl, kh, unpj[i], kh);
               CppCore::usub64(ph, 0U, kh, 0U-(kh>>31), kl, kh);
            }
            CppCore::usub64(unpj[n], 0U, kl, kh, kl, kh);
            if (kh >> 31) {
               qp[j] = ql - 1U;
               c = 0;
               for (uint32_t i = 0; i < n; i++)
                  CppCore::addcarry32(unpj[i], vn[i], unpj[i], c);
               CppCore::addcarry32(kl, 0U, unpj[n], c);
            }
            else {
               qp[j] = ql;
               unpj[n] = kl;
            }
         }
         if (S) { CppCore::shr32x(unp, rp, n, S); }
         else   { CppCore::clone(r, *(UINT2*)&mem[0]); }
      }
      return true;
   }

   /// <summary>
   /// Like other variant but using temporary stack memory
   /// </summary>
   template<typename UINT1, typename UINT2>
   INLINE static bool udivmod(UINT1& q, UINT2& r, const UINT1& u, const UINT2& v)
   {
      CPPCORE_ALIGN_OPTIM(UINT1) mem[2];
      return CppCore::udivmod(q, r, u, v, mem);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MULTI WORD MODULO (u%v=r)
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Modulo (a%b=r) with a n32 multiples of 32-Bit and b and r exactly 32-Bit.
   /// </summary>
   INLINE static uint32_t umod64_32x(const uint32_t* a, uint32_t b, const uint32_t n32)
   {
      uint32_t q;
      uint32_t r = 0U;
      assert(b != 0U);
      assert(n32 != 0U);
      for (uint32_t i = n32-1U; i != 0xFFFFFFFFU; i--)
         CppCore::udivmod64_32(r, a[i], b, q, r);
      return r;
   }

#if defined(CPPCORE_CPU_X64)
   /// <summary>
   /// Modulo (a%b=r) with a n64 multiples of 64-Bit and b and r exactly 64-Bit.
   /// </summary>
   INLINE static uint64_t umod128_64x(const uint64_t* a, uint64_t b, const uint32_t n64)
   {
      uint64_t q;
      uint64_t r = 0ULL;
      assert(b != 0U);
      assert(n64 != 0U);
      for (uint32_t i = n64-1U; i != 0xFFFFFFFFU; i--)
         CppCore::udivmod128_64(r, a[i], b, q, r);
      return r;
   }
#endif

   /// <summary>
   /// Modulo for any sized Integers that are multiples of 32-Bit.
   /// Based on Knuth's Algorithm in Hacker's Delight. (r=u%v)
   /// </summary>
   template<typename UINT1, typename UINT2>
   INLINE static void umod(UINT2& r, const UINT1& u, const UINT2& v, UINT1 mem[2])
   {
      assert(&r != &v);
      static_assert(sizeof(UINT1) % 4 == 0);
      static_assert(sizeof(UINT2) % 4 == 0);
      static_assert(sizeof(UINT1) >= sizeof(UINT2));
   #if defined(CPPCORE_CPU_X64)
      if constexpr (sizeof(UINT1) % 8 == 0 && sizeof(UINT2) % 8 == 0)
      {
         // using 64-bit chunks
         constexpr uint32_t M = sizeof(UINT1) / 8;
         constexpr uint32_t N = sizeof(UINT2) / 8;
         uint64_t* rp  = (uint64_t*)&r;
         uint64_t* up  = (uint64_t*)&u;
         uint64_t* vp  = (uint64_t*)&v;
         uint64_t* unp = (uint64_t*)mem;
         uint64_t* vno;
         uint64_t* vne;
         uint32_t  n = N;
         while (n != 0U && vp[n-1] == 0U)
            n--;
         if (n == 0U)
            return;
         if (n == 1U) {
            CppCore::clear(r);
            *rp = CppCore::umod128_64x(up, *vp, M);
            return;
         }
         const auto S((uint8_t)CppCore::lzcnt(vp[n-1]));
         if (S) {
            CppCore::clear(r);
            CppCore::shl64x(vp, rp, n, S);
            vno = rp;
            vne = &rp[n];
            unp[M] = up[M-1] >> (64U-S);
            CppCore::shl64x(up, unp, M, S);
         }
         else {
            vno = vp;
            vne = &vp[n];
            CppCore::clone(mem[0], u);
            unp[M] = 0U;
         }
         const auto VNN1 = vno[n-1];
         const auto VNN2 = vno[n-2];
         for (uint32_t j = M-n; j != UINT32_MAX; j--)
         {
            auto* unpjo = &unp[j];
            auto* unpj = unpjo;
            auto* vn = vno;
            const auto UNJN  = unpj[n];
            const auto UNJN2 = unpj[n-2];
            uint64_t kl, kh, ql, qh, pl, ph;
            uint64_t rhat;
            uint8_t  c;
            if (VNN1 <= UNJN) {
               CppCore::udivmod128_64(0ULL, UNJN, VNN1, qh, rhat);
               CppCore::udivmod128_64(rhat, unpj[n-1], VNN1, ql, rhat);
            }
            else {
               qh = 0ULL;
               CppCore::udivmod128_64(UNJN, unpj[n-1], VNN1, ql, rhat);
            }
            do {
               if (qh == 0ULL) {
                  CppCore::umul128(ql, VNN2, kl, kh);
                  if (((kh > rhat) | ((kh == rhat) & (kl > UNJN2))) == 0)
                     break;
               }
               c = 0;
               CppCore::usub128(ql, qh, 1ULL, 0ULL, ql, qh);
               CppCore::addcarry64(rhat, VNN1, rhat, c);
            } while (c == 0);
            CppCore::umul128(ql, *vn, kl, ph);
            CppCore::usub128(*unpj, 0ULL, kl, 0ULL, *unpj, kh);
            CppCore::usub128(ph, 0ULL, kh, 0ULL-(kh>>63), kl, kh);
            vn++; unpj++;
            do {
               CppCore::umul128(ql, *vn, pl, ph);
               CppCore::uadd128(kl, kh, pl, 0ULL, kl, kh);
               CppCore::usub128(*unpj, 0ULL, kl, kh, *unpj, kh);
               CppCore::usub128(ph, 0ULL, kh, 0ULL-(kh>>63), kl, kh);
               vn++; unpj++;
            } while (vn < vne);
            CppCore::usub128(*unpj, 0ULL, kl, kh, kl, kh);
            if (kh >> 63) {
               vn = vno; 
               unpj = unpjo; 
               c = 0;
               do  {
                  CppCore::addcarry64(*unpj, *vn, *unpj, c);
                  vn++;  unpj++;
               } while (vn < vne);
               CppCore::addcarry64(kl, 0ULL, *unpj, c);
            }
            else
               *unpj = kl;
         }
         if (S) { CppCore::shr64x(unp, rp, n, S); }
         else   { CppCore::clone(r, *(UINT2*)mem); }
      }
      else
   #endif
      {
         // using 32-bit chunks
         constexpr uint32_t M = sizeof(UINT1) / 4;
         constexpr uint32_t N = sizeof(UINT2) / 4;
         uint32_t* rp  = (uint32_t*)&r;
         uint32_t* up  = (uint32_t*)&u;
         uint32_t* vp  = (uint32_t*)&v;
         uint32_t* unp = (uint32_t*)mem;
         uint32_t* vno;
         uint32_t* vne;
         uint32_t  n = N;
         while (n != 0U && vp[n-1] == 0U)
            n--;
         if (n == 0U)
            return;
         if (n == 1U) {
            CppCore::clear(r);
            *rp = CppCore::umod64_32x(up, *vp, M);
            return;
         }
         const auto S((uint8_t)CppCore::lzcnt(vp[n-1]));
         if (S) {
            CppCore::clear(r);
            CppCore::shl32x(vp, rp, n, S);
            vno = rp;
            vne = &rp[n];
            unp[M] = up[M-1] >> (32U-S);
            CppCore::shl32x(up, unp, M, S);
         }
         else {
            vno = vp;
            vne = &vp[n];
            CppCore::clone(mem[0], u);
            unp[M] = 0U;
         }
         const auto VNN1 = vno[n-1];
         const auto VNN2 = vno[n-2];
         for (uint32_t j = M-n; j != UINT32_MAX; j--)
         {
            auto* unpjo = &unp[j];
            auto* unpj = unpjo;
            auto* vn = vno;
            const auto UNJN = unpj[n];
            const auto UNJN2 = unpj[n-2];
            uint32_t kl, kh, ql, qh, pl, ph;
            uint32_t rhat;
            uint8_t  c;
            if (VNN1 <= UNJN) {
               CppCore::udivmod64_32(0U, UNJN,  VNN1, qh, rhat);
               CppCore::udivmod64_32(rhat, unpj[n-1], VNN1, ql, rhat);
            }
            else {
               qh = 0U;
               CppCore::udivmod64_32(UNJN, unpj[n-1], VNN1, ql, rhat);
            }
            do {
               if (qh == 0U) {
                  CppCore::umul64(ql, VNN2, kl, kh);
                  if (((kh > rhat) | ((kh == rhat) & (kl > UNJN2))) == 0)
                     break;
               }
               c = 0;
               CppCore::usub64(ql, qh, 1U, 0U, ql, qh);
               CppCore::addcarry32(rhat, VNN1, rhat, c);
            } while (c == 0);
            CppCore::umul64(ql, *vn, kl, ph);
            CppCore::usub64(*unpj, 0U, kl, 0U, *unpj, kh);
            CppCore::usub64(ph, 0U, kh, 0U-(kh>>31), kl, kh);
            vn++; unpj++;
            do {
               CppCore::umul64(ql, *vn, pl, ph);
               CppCore::uadd64(kl, kh, pl, 0U, kl, kh);
               CppCore::usub64(*unpj, 0U, kl, kh, *unpj, kh);
               CppCore::usub64(ph, 0U, kh, 0U-(kh>>31), kl, kh);
               vn++; unpj++;
            } while (vn < vne);
            CppCore::usub64(*unpj, 0U, kl, kh, kl, kh);
            if (kh >> 31) {
               vn = vno; 
               unpj = unpjo; 
               c = 0;
               do {
                  CppCore::addcarry32(*unpj, *vn, *unpj, c);
                  vn++;  unpj++;
               } while (vn < vne);
               CppCore::addcarry32(kl, 0U, *unpj, c);
            }
            else
               *unpj = kl;
         }
         if (S) { CppCore::shr32x(unp, rp, n, S); }
         else   { CppCore::clone(r, *(UINT2*)mem); }
      }
   }

   /// <summary>
   /// Like other variant but using temporary stack memory
   /// </summary>
   template<typename UINT1, typename UINT2>
   INLINE static void umod(UINT2& r, const UINT1& u, const UINT2& v)
   {
      CPPCORE_ALIGN_OPTIM(UINT1) mem[2];
      CppCore::umod(r, u, v, mem);
   }

   /// <summary>
   /// TODO: Special Version for High Bit on Divisor set.
   /// </summary>
   template<typename UINT1, typename UINT2>
   INLINE static void umod_highdiv(UINT2& r, const UINT1& u, const UINT2& v, UINT1 mem[2])
   {
      assert(&r != &v);
      static_assert(sizeof(UINT1) % 4 == 0);
      static_assert(sizeof(UINT2) % 4 == 0);
   #if defined(CPPCORE_CPU_X64)
      if constexpr (sizeof(UINT1) % 8 == 0 && sizeof(UINT2) % 8 == 0)
      {
         // using 64-bit chunks
         constexpr uint32_t M = sizeof(UINT1) / 8;
         constexpr uint32_t N = sizeof(UINT2) / 8;
         static_assert(M >= N);
         uint64_t* rp  = (uint64_t*)&r;
         uint64_t* up  = (uint64_t*)&u;
         uint64_t* vp  = (uint64_t*)&v;
         uint64_t* unp = (uint64_t*)mem;
         uint64_t* vn  = vp;
         assert(CppCore::lzcnt(vp[N-1]) == 0);
         if (N == 1U) {
            CppCore::clear(r);
            rp[0] = CppCore::umod128_64x(up, vp[0], M);
            return;
         }
         CppCore::clone(mem[0], u);
         unp[M] = 0U;
         const auto VNN1 = vn[N-1];
         const auto VNN2 = vn[N-2];
         for (uint32_t j = M-N; j != UINT32_MAX; j--)
         {
            auto* unpj = &unp[j];
            const auto UNJN  = unpj[N];
            const auto UNJN2 = unpj[N-2];
            uint64_t kl, kh, ql, qh, pl, ph;
            uint64_t rhat;
            uint8_t  c;
            if (VNN1 <= UNJN) {
               CppCore::udivmod128_64(0ULL, UNJN,  VNN1, qh, rhat);
               CppCore::udivmod128_64(rhat, unpj[N-1], VNN1, ql, rhat);
            }
            else {
               qh = 0ULL;
               CppCore::udivmod128_64(UNJN, unpj[N-1], VNN1, ql, rhat);
            }
            do {
               if (qh == 0ULL) {
                  CppCore::umul128(ql, VNN2, kl, kh);
                  if (((kh > rhat) | ((kh == rhat) & (kl > UNJN2))) == 0)
                     break;
               }
               c = 0;
               CppCore::usub128(ql, qh, 1ULL, 0ULL, ql, qh);
               CppCore::addcarry64(rhat, VNN1, rhat, c);
            } while (c == 0);
            CppCore::umul128(ql, *vn, kl, ph);
            CppCore::usub128(*unpj, 0ULL, kl, 0ULL, *unpj, kh);
            CppCore::usub128(ph, 0ULL, kh, 0ULL-(kh>>63), kl, kh);
            for (uint32_t i = 1; i < N; i++) {
               CppCore::umul128(ql, vn[i], pl, ph);
               CppCore::uadd128(kl, kh, pl, 0ULL, kl, kh);
               CppCore::usub128(unpj[i], 0ULL, kl, kh, unpj[i], kh);
               CppCore::usub128(ph, 0ULL, kh, 0ULL-(kh>>63), kl, kh);
            }
            CppCore::usub128(unpj[N], 0ULL, kl, kh, kl, kh);
            if (kh >> 63) {
               c = 0;
               for (uint32_t i = 0; i < N; i++)
                  CppCore::addcarry64(unpj[i], vn[i], unpj[i], c);
               CppCore::addcarry64(kl, 0ULL, unpj[N], c);
            }
            else
               unpj[N] = kl;
         }
         CppCore::clone(r, *(UINT2*)mem);
      }
      else
   #endif
      {
         // using 32-bit chunks
         constexpr uint32_t M = sizeof(UINT1) / 4;
         constexpr uint32_t N = sizeof(UINT2) / 4;
         static_assert(M >= N);
         uint32_t* rp  = (uint32_t*)&r;
         uint32_t* up  = (uint32_t*)&u;
         uint32_t* vp  = (uint32_t*)&v;
         uint32_t* unp = (uint32_t*)mem;
         uint32_t* vn  = vp;
         assert(CppCore::lzcnt(vp[N-1]) == 0);
         if (N == 1U) {
            CppCore::clear(r);
            rp[0] = CppCore::umod64_32x(up, vp[0], M);
            return;
         }
         CppCore::clone(mem[0], u);
         unp[M] = 0U;
         const auto VNN1  = vn[N-1];
         const auto VNN2  = vn[N-2];
         for (uint32_t j = M-N; j != UINT32_MAX; j--)
         {
            auto* unpj = &unp[j];
            const auto UNJN  = unpj[N];
            const auto UNJN2 = unpj[N-2];
            uint32_t kl, kh, ql, qh, pl, ph;
            uint32_t rhat;
            uint8_t  c;
            if (VNN1 <= UNJN) {
               CppCore::udivmod64_32(0U,   UNJN,  VNN1, qh, rhat);
               CppCore::udivmod64_32(rhat, unpj[N-1], VNN1, ql, rhat);
            }
            else {
               qh = 0U;
               CppCore::udivmod64_32(UNJN, unpj[N-1], VNN1, ql, rhat);
            }
            do {
               if (qh == 0U) {
                  CppCore::umul64(ql, VNN2, kl, kh);
                  if (((kh > rhat) | ((kh == rhat) & (kl > UNJN2))) == 0)
                     break;
               }
               c = 0;
               CppCore::usub64(ql, qh, 1U, 0U, ql, qh);
               CppCore::addcarry32(rhat, VNN1, rhat, c);
            } while (c == 0);
            CppCore::umul64(ql, *vn, kl, ph);
            CppCore::usub64(*unpj, 0U, kl, 0U, *unpj, kh);
            CppCore::usub64(ph, 0U, kh, 0U-(kh>>31), kl, kh);
            for (uint32_t i = 1; i < N; i++) {
               CppCore::umul64(ql, vn[i], pl, ph);
               CppCore::uadd64(kl, kh, pl, 0U, kl, kh);
               CppCore::usub64(unpj[i], 0U, kl, kh, unpj[i], kh);
               CppCore::usub64(ph, 0U, kh, 0U-(kh>>31), kl, kh);
            }
            CppCore::usub64(unpj[N], 0U, kl, kh, kl, kh);
            if (kh >> 31) {
               c = 0;
               for (uint32_t i = 0; i < N; i++)
                  CppCore::addcarry32(unpj[i], vn[i], unpj[i], c);
               CppCore::addcarry32(kl, 0U, unpj[N], c);
            }
            else
               unpj[N] = kl;
         }
         CppCore::clone(r, *(UINT2*)mem);
      }
   }

   /// <summary>
   /// 32%32=32
   /// </summary>
   template<> INLINE void umod(uint32_t& r, const uint32_t& u, const uint32_t& v, uint32_t mem[2])
   {
      r = u % v;
   }

   /// <summary>
   /// 64%64=64
   /// </summary>
   template<> INLINE void umod(uint64_t& r, const uint64_t& u, const uint64_t& v, uint64_t mem[2])
   {
      r = u % v;
   }

   /// <summary>
   /// 64%32=32
   /// </summary>
   template<> INLINE void umod(uint32_t& r, const uint64_t& u, const uint32_t& v, uint64_t mem[2])
   {
      r = u % v;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MULMOD
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// a*b mod m. For any sized integers that are multiples of 32-bit.
   /// </summary>
   template<typename UINT>
   INLINE static void umulmod(const UINT& a, const UINT& b, const UINT& m, UINT& r, UINT p[3])
   {
      struct UINTX2 { UINT x[2]; };
      CppCore::umul<UINT, UINT, UINTX2>(a, b, *(UINTX2*)p);
      CppCore::umod<UINTX2, UINT>(r, *(UINTX2*)p, m, (UINTX2*)p);
   }

   /// <summary>
   ///  a*b mod m. For any sized integers that are multiples of 32-bit.
   /// </summary>
   template<typename UINT>
   INLINE static void umulmod(const UINT& a, const UINT& b, const UINT& m, UINT& r)
   {
      CPPCORE_ALIGN_OPTIM(UINT) p[3];
      CppCore::umulmod(a, b, m, r, p);
   }

   /// <summary>
   /// a*b mod m. For 16-Bit Unsigned Integers using 32-Bit product.
   /// </summary>
   INLINE static void umulmod16(const uint16_t& a, const uint16_t& b, const uint16_t& m, uint16_t& r)
   {
      r = ((uint32_t)a * (uint32_t)b) % m;
   }

   /// <summary>
   /// Template Specialization for 16-Bit Unsigned.
   /// </summary>
   template<> INLINE void umulmod(const uint16_t& a, const uint16_t& b, const uint16_t& m, uint16_t& r, uint16_t p[3])
   {
      CppCore::umulmod16(a, b, m, r); 
   }

   /// <summary>
   /// Template Specialization for 16-Bit Unsigned.
   /// </summary>
   template<> INLINE void umulmod(const uint16_t& a, const uint16_t& b, const uint16_t& m, uint16_t& r)
   {
      CppCore::umulmod16(a, b, m, r); 
   }

   /// <summary>
   /// a*b mod m. For 32-Bit Unsigned Integers using 64-Bit product.
   /// </summary>
   INLINE static void umulmod32(const uint32_t& a, const uint32_t& b, const uint32_t& m, uint32_t& r)
   {
      r = ((uint64_t)a * (uint64_t)b) % m;
   }

   /// <summary>
   /// Template Specialization for 32-Bit Unsigned.
   /// </summary>
   template<> INLINE void umulmod(const uint32_t& a, const uint32_t& b, const uint32_t& m, uint32_t& r, uint32_t p[3])
   {
      CppCore::umulmod32(a, b, m, r);
   }

   /// <summary>
   /// Template Specialization for 32-Bit Unsigned.
   /// </summary>
   template<> INLINE void umulmod(const uint32_t& a, const uint32_t& b, const uint32_t& m, uint32_t& r)
   {
      CppCore::umulmod32(a, b, m, r);
   }

#if defined(CPPCORE_CPU_X64)
   /// <summary>
   /// a*b mod m. For 64-Bit Unsigned Integers using 128-Bit intermediate product.
   /// </summary>
   INLINE static void umulmod64(uint64_t a, uint64_t b, const uint64_t& m, uint64_t& r)
   {
      CppCore::umul128(a, b, a, b);
      CppCore::udivmod128_64((b < m) ? b : b % m, a, m, a, r);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Unsigned.
   /// </summary>
   template<> INLINE void umulmod(const uint64_t& a, const uint64_t& b, const uint64_t& m, uint64_t& r, uint64_t p[3])
   {
      CppCore::umulmod64(a, b, m, r);
   }

   /// <summary>
   /// Template Specialization for 64-Bit Unsigned.
   /// </summary>
   template<> INLINE void umulmod(const uint64_t& a, const uint64_t& b, const uint64_t& m, uint64_t& r)
   {
      CppCore::umulmod64(a, b, m, r);
   }
#else
   /// <summary>
   /// a*b mod m. For 64-Bit Unsigned Integers using 128-Bit intermediate product.
   /// </summary>
   INLINE static void umulmod64(uint64_t a, uint64_t b, const uint64_t& m, uint64_t& r)
   {
      CppCore::umulmod(a, b, m, r);
   }
#endif

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // POWMOD
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   /// <summary>
   /// a^b mod m
   /// </summary>
   template<typename UINT>
   INLINE static void upowmod(UINT& a, const UINT& b, const UINT& m, UINT& r, UINT t[3])
   {
      assert((&a != &r) && (&b != &r) && (&m != &r));
      assert(!CppCore::testzero(m));
      CppCore::clear(r);
      constexpr auto NUMBITS = sizeof(UINT)*8U;
      const auto LZB = CppCore::lzcnt(b);
      if (LZB == NUMBITS) CPPCORE_UNLIKELY {
         if (NUMBITS-CppCore::lzcnt(m) != 1U) CPPCORE_LIKELY
            *(uint32_t*)&r = 1U;
         return;
      }
      *(uint32_t*)&r = 1U;
      const uint32_t HIDX = NUMBITS-LZB;
      for (uint32_t i = 0; i < HIDX; i++)
      {
         if (CppCore::bittest(b, i))
            CppCore::umulmod(r, a, m, r, t);
         CppCore::umulmod(a, a, m, a, t); //TODO: usquaremod
      }
   }

   /// <summary>
   /// a^b mod m
   /// </summary>
   template<typename UINT>
   INLINE static void upowmod(UINT& a, const UINT& b, const UINT& m, UINT& r)
   {
      CPPCORE_ALIGN_OPTIM(UINT) t[3];
      CppCore::upowmod(a, b, m, r, t);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MERSENNE NUMBERS (2^i)-1
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Returns the ith Mersenne Number.
   /// Returns 0 for i=0 or i>sizeof(UINT)*8.
   /// </summary>
   template<typename UINT>
   INLINE static UINT getmersenne(uint32_t i)
   {
      return 
         i <  sizeof(UINT)*8U ? (UINT(1U) << i) - 1U :
         i == sizeof(UINT)*8U ? ::std::numeric_limits<UINT>::max() :
         0U;
   }

   /// <summary>
   /// Returns i if n is a (2^i)-1 Mersenne Number else 0.
   /// </summary>
   INLINE static uint32_t ismersenne32(const uint32_t& n)
   {
      if (CppCore::tzcnt32(n) != 0)
         return 0U;
      const uint32_t LZC = CppCore::lzcnt32(n);
      const uint32_t POPC = CppCore::popcnt32(n);
      return (POPC == 32U - LZC) ? POPC : 0U;
   }

   /// <summary>
   /// Returns i if n is a (2^i)-1 Mersenne Number else 0.
   /// </summary>
   INLINE static uint32_t ismersenne64(const uint64_t& n)
   {
      if (CppCore::tzcnt64(n) != 0U)
         return 0U;
      const uint32_t LZC = CppCore::lzcnt64(n);
      const uint32_t POPC = CppCore::popcnt64(n);
      return (POPC == 64U - LZC) ? POPC : 0U;
   }

   /// <summary>
   /// Returns i if this is a (2^i)-1 mersenne number else 0.
   /// </summary>
   template<typename UINT>
   INLINE static uint32_t ismersenne(const UINT& n)
   {
      if (CppCore::tzcnt(n) != 0U)
         return 0U;
      const uint32_t LZC  = CppCore::lzcnt(n);
      const uint32_t POPC = CppCore::popcnt(n);
      return (POPC == (uint32_t)(sizeof(UINT)*8U) - LZC) ? POPC : 0U;
   }

   /// <summary>
   /// Template Specialization for 32-bit integer.
   /// </summary>
   template<> INLINE uint32_t ismersenne<uint32_t>(const uint32_t& x)
   {
      return CppCore::ismersenne32(x);
   }

   /// <summary>
   /// Template Specialization for 64-bit integer.
   /// </summary>
   template<> INLINE uint32_t ismersenne<uint64_t>(const uint64_t& x)
   {
      return CppCore::ismersenne64(x);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // GREATEST COMMON DIVISOR (GCD)
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// GCD for 32-Bit
   /// </summary>
   INLINE static uint32_t gcd32(uint32_t a, uint32_t b)
   {
      uint32_t t;
      if (a == 0U)
         return b;
      while (b != 0U)
      {
         t = a % b;
         a = b;
         b = t;
      }
      return a;
   }

   /// <summary>
   /// GCD for 64-Bit
   /// </summary>
   INLINE static uint64_t gcd64(uint64_t a, uint64_t b)
   {
      uint64_t t;
      if (a == 0ULL)
         return b;
      while (b != 0ULL)
      {
         t = a % b;
         a = b;
         b = t;
      }
      return a;
   }

   /// <summary>
   /// GCD for any size
   /// </summary>
   template<typename UINT>
   INLINE static void gcd(const UINT& x, const UINT& y, UINT& r)
   {
      CPPCORE_ALIGN_OPTIM(UINT) b, t;
      CPPCORE_ALIGN_OPTIM(UINT) un[2];

      if (CppCore::testzero(x))
         CppCore::clone(r, y);

      else
      {
         CppCore::clone(r, x);
         CppCore::clone(b, y);
         while (!CppCore::testzero(b))
         {
            CppCore::umod<UINT, UINT>(t, r, b, un);
            CppCore::clone(r, b);
            CppCore::clone(b, t);
         }
      }
   }

   /// <summary>
   /// Specialization for uint32_t
   /// </summary>
   template<> INLINE void gcd(const uint32_t& x, const uint32_t& y, uint32_t& r)
   {
      r = CppCore::gcd32(x, y);
   }
   /// <summary>
   /// Specialization for uint64_t
   /// </summary>
   template<> INLINE void gcd(const uint64_t& x, const uint64_t& y, uint64_t& r)
   {
      r = CppCore::gcd64(x, y);
   }
}
