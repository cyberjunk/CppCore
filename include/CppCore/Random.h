#pragma once

#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>

namespace CppCore
{
   /// <summary>
   /// Random Value Generation
   /// </summary>
   class Random
   {
   public:
      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SEEDING
      /////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns a 16-bit seed for a random number generator.
      /// Quality and performance ranges from good to poor depending on available options.
      /// By default (LOWBITONE=true) only 15-bit are random and lowbit is always 1 to avoid return of 0.
      /// </summary>
      template <bool LOWBITONE = true>
      INLINE static uint16_t seed16()
      {
         uint16_t v;
      #if defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_CPUFEAT_RDSEED)
         while (0 == _rdseed16_step(&v)) CPPCORE_UNLIKELY _mm_pause();
      #elif defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_CPUFEAT_RDRAND)
         while (0 == _rdrand16_step(&v)) CPPCORE_UNLIKELY _mm_pause();
      #elif defined(CPPCORE_CPU_X86ORX64)
         v = (uint16_t)__rdtsc();
      #else
         v = (uint16_t)::std::chrono::high_resolution_clock::now().time_since_epoch().count();
      #endif
         return v | (uint16_t)LOWBITONE;
      }

      /// <summary>
      /// Returns a 32-bit seed for a random number generator.
      /// Quality and performance ranges from good to poor depending on available options.
      /// By default (LOWBITONE=true) only 31-bit are random and lowbit is always 1 to avoid return of 0.
      /// </summary>
      template <bool LOWBITONE = true>
      INLINE static uint32_t seed32()
      {
         uint32_t v;
      #if defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_CPUFEAT_RDSEED)
         while (0 == _rdseed32_step(&v)) CPPCORE_UNLIKELY _mm_pause();
      #elif defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_CPUFEAT_RDRAND)
         while (0 == _rdrand32_step(&v)) CPPCORE_UNLIKELY _mm_pause();
      #elif defined(CPPCORE_CPU_X86ORX64)
         v = (uint32_t)__rdtsc();
      #else
         v = (uint32_t)::std::chrono::high_resolution_clock::now().time_since_epoch().count();
      #endif
         return v | (uint32_t)LOWBITONE;
      }

      /// <summary>
      /// Returns a 64-bit seed for a random number generator.
      /// Quality and performance ranges from good to poor depending on available options.
      /// By default (LOWBITONE=true) only 63-bit are random and lowbit is always 1 to avoid return of 0.
      /// </summary>
      template <bool LOWBITONE = true>
      INLINE static uint64_t seed64()
      {
         uint64_t v;
      #if defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_CPUFEAT_RDSEED)
         while (0 == _rdseed64_step((unsigned long long*)&v)) CPPCORE_UNLIKELY _mm_pause();
      #elif defined(CPPCORE_CPU_X64) && defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_CPUFEAT_RDRAND)
         while (0 == _rdrand64_step((unsigned long long*)&v)) CPPCORE_UNLIKELY _mm_pause();
      #elif defined(CPPCORE_CPU_X86) && defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_CPUFEAT_RDSEED)
         while (0 == _rdseed32_step( (uint32_t*)&v))    CPPCORE_UNLIKELY _mm_pause();
         while (0 == _rdseed32_step(((uint32_t*)&v)+1)) CPPCORE_UNLIKELY _mm_pause();
      #elif defined(CPPCORE_CPU_X86) && defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_CPUFEAT_RDRAND)
         while (0 == _rdrand32_step( (uint32_t*)&v))    CPPCORE_UNLIKELY _mm_pause();
         while (0 == _rdrand32_step(((uint32_t*)&v)+1)) CPPCORE_UNLIKELY _mm_pause();
      #elif defined(CPPCORE_CPU_X86ORX64)
         v = (uint64_t)__rdtsc();
      #else
         v = (uint64_t)::std::chrono::high_resolution_clock::now().time_since_epoch().count();
      #endif
         return v | (uint64_t)LOWBITONE;
      }

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Returns four 32-bit seeds for a packed random number generator.
      /// Quality and performance ranges from good to poor depending on available options.
      /// By default (LOWBITONE=true) only each 31-bit are random and lowbits are always 1 to avoid return of 0.
      /// </summary>
      template <bool LOWBITONE = true>
      INLINE static __m128i seed32x4()
      {
         const __m128i t = _mm_set_epi32(
            Random::seed32<false>(),
            Random::seed32<false>(),
            Random::seed32<false>(),
            Random::seed32<false>());
         return _mm_or_si128(t, _mm_set1_epi32(LOWBITONE));
      }

      /// <summary>
      /// Returns two 64-bit seeds for a packed random number generator.
      /// Quality and performance ranges from good to poor depending on available options.
      /// By default (LOWBITONE=true) only each 63-bit are random and lowbits are always 1 to avoid return of 0.
      /// </summary>
      template <bool LOWBITONE = true>
      INLINE static __m128i seed64x2()
      {
         const __m128i t = _mm_set_epi64x(
            Random::seed64<false>(),
            Random::seed64<false>());
         return _mm_or_si128(t, _mm_set1_epi64x(LOWBITONE));
      }
#endif

      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CUSTOM PSEUDO RANDOM NUMBER GENERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Base Class for Pseudo Random Number Generators
      /// </summary>
      template<typename T, typename INT, typename SINT, typename REAL>
      class PRNG
      {
      protected:
         INLINE T* thiss() const { return (T*)this; }
      public:
         /// <summary>
         /// Size of Generated Values in Bytes
         /// </summary>
         static constexpr size_t GENSIZE = sizeof(INT);

         /// <summary>
         /// Empty Constructor
         /// </summary>
         INLINE PRNG() { }

         ///////////////////////////////////////////////////////////////////////////////////////////////////
         // RANDOMS WITHIN SPECIFIED TYPE AND RANGE
         ///////////////////////////////////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Returns next unsigned pseudo random number in range [min, max] (inclusive).
         /// Min must be smaller than max and range (max-min) must be smaller than unsigned MAXINT (e.g. 0xFFFFFFFF for 32-Bit).
         /// Uniform=true makes distribution more uniform at cost of indeterminstic and higher runtime.
         /// </summary>
         INLINE INT next(const INT min, const INT max, const bool uniform = false)
         {
            assert(min < max);
            assert(max - min < std::numeric_limits<INT>::max());
            if (uniform)
            {
               const INT range = (INT)1U + max - min;
               const INT bins  = std::numeric_limits<INT>::max() / range;
               const INT limit = bins * range;

               INT r;
               do { r = thiss()->next(); } 
               while (r >= limit);

               return min + (r / bins);
            }
            else
               return (thiss()->next() % ((max - min) + 1U)) + min;
         }

         /// <summary>
         /// Returns next signed pseudo random number in range [min, max] (inclusive).
         /// Min must be smaller than max and range (max-min) must be smaller than or equal to signed MAXINT (e.g. 0x7FFFFFFF for 32-Bit).
         /// Uniform=true makes distribution more uniform at cost of indeterminstic and higher runtime.
         /// </summary>
         INLINE SINT next(const SINT min, const SINT max, const bool uniform = false)
         {
            assert(min < max);
            const INT d = (INT)(max - min);
            assert(d <= (INT)std::numeric_limits<SINT>::max());
            const INT r = thiss()->next(0U, d, uniform);
            return (SINT)r + min;
         }

         /// <summary>
         /// Returns next pseudo random floating point number in range [min, max] (inclusive).
         /// Min must be smaller than max and there are more limitations due to floating point precision.
         /// </summary>
         INLINE REAL next(const REAL min, const REAL max)
         {
            assert(min < max);
            const REAL r = (REAL)thiss()->next() / (REAL)std::numeric_limits<INT>::max();
            return (r * (max - min)) + min;
         }

         ///////////////////////////////////////////////////////////////////////////////////////////////////
         // ARRAY FILLING
         ///////////////////////////////////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Fills memory m with n unsigned and unbound random integer values.
         /// </summary>
         INLINE void fill(INT* m, const size_t n)
         {
            CPPCORE_UNROLL
            for (size_t i = 0; i < n; i++)
               m[i] = thiss()->next();
         }

         /// <summary>
         /// Fills memory m with n unsigned random integer values in range [min, max] (inclusive).
         /// </summary>
         INLINE void fill(INT* m, const size_t n, const INT min, const INT max, const bool uniform = false)
         {
            CPPCORE_UNROLL
            for (size_t i = 0; i < n; i++)
               m[i] = thiss()->next(min, max, uniform);
         }

         /// <summary>
         /// Fills memory m with n signed random integer values in range [min, max] (inclusive).
         /// </summary>
         INLINE void fill(SINT* m, const size_t n, const SINT min, const SINT max, const bool uniform = false)
         {
            CPPCORE_UNROLL
            for (size_t i = 0; i < n; i++)
               m[i] = thiss()->next(min, max, uniform);
         }

         /// <summary>
         /// Fills memory m with n random floating point values in range [min, max] (inclusive).
         /// </summary>
         INLINE void fill(REAL* m, const size_t n, const REAL min, const REAL max)
         {
            CPPCORE_UNROLL
            for (size_t i = 0; i < n; i++)
               m[i] = thiss()->next(min, max);
         }

         ///////////////////////////////////////////////////////////////////////////////////////////////////
         // STD C++ PRNG COMPATIBILITY
         ///////////////////////////////////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Same as INT. For some compatibility with std C++ generators.
         /// </summary>
         using result_type = INT;

         /// <summary>
         /// Same as next(). For some compatibility with std C++ generators.
         /// </summary>
         INLINE INT operator()() { return thiss()->next(); }

         /// <summary>
         /// Maximum value returned from next(). For some compatibility with std C++ generators.
         /// </summary>
         INLINE static INT max() { return std::numeric_limits<INT>::max(); }

         /// <summary>
         /// Minimum value returned from next(). For some compatibility with std C++ generators.
         /// </summary>
         INLINE static INT min() { return (INT)0; }
      };

      /// <summary>
      /// Xorshift32 PRNG by George Marsaglia creating 32-Bit pseudo randoms.
      /// Must not be seeded with zero.
      /// </summary>
      /// <remarks>
      /// https://en.wikipedia.org/wiki/Xorshift
      /// </remarks>
      class Xorshift32 : public PRNG<Xorshift32, uint32_t, int32_t, float>
      {
         typedef PRNG<Xorshift32, uint32_t, int32_t, float> Xorshift32b;
      protected:
         uint32_t s;
      public:
         using Xorshift32b::next;
         INLINE Xorshift32(): s(Random::seed32()) { assert(s != 0U); }
         INLINE Xorshift32(const uint32_t seed) : s(seed) { assert(s != 0U); }
         INLINE uint32_t next()
         {
            s ^= s << 13;
            s ^= s >> 17;
            s ^= s << 5;
            return s;
         }
      };

      /// <summary>
      /// Xorshift64 PRNG by George Marsaglia creating 64-Bit pseudo randoms.
      /// Must not be seeded with zero.
      /// </summary>
      /// <remarks>
      /// https://en.wikipedia.org/wiki/Xorshift
      /// </remarks>
      class Xorshift64 : public PRNG<Xorshift64, uint64_t, int64_t, double>
      {
         typedef PRNG<Xorshift64, uint64_t, int64_t, double> Xorshift64b;
      protected:
         uint64_t s;
      public:
         using Xorshift64b::next;
         INLINE Xorshift64() : s(Random::seed64()) { assert(s != 0ULL); }
         INLINE Xorshift64(const uint64_t seed) : s(seed) { assert(s != 0ULL); }
         INLINE uint64_t next()
         {
            s ^= s << 13;
            s ^= s >> 7;
            s ^= s << 17;
            return s;
         }
      };

      /// <summary>
      /// xoshiro128++ 1.0 PRNG by David Blackman and Sebastiano Vigna creating 32-Bit pseudo randoms.
      /// Must not be seeded with zero.
      /// </summary>
      /// <remarks>
      /// https://prng.di.unimi.it/xoshiro128plusplus.c
      /// </remarks>
      class Xoshiro32 : public PRNG<Xoshiro32, uint32_t, int32_t, float>
      {
         typedef PRNG<Xoshiro32, uint32_t, int32_t, float> Xoshiro32b;
      protected:
         uint32_t s[4];
      public:
         using Xoshiro32b::next;
         INLINE Xoshiro32()
         {
            s[0] = Random::seed32();
            s[1] = Random::seed32();
            s[2] = Random::seed32();
            s[3] = Random::seed32();
            assert(s[0] != 0U || s[1] != 0U || s[2] != 0U || s[3] != 0U);
         }
         INLINE Xoshiro32(const uint32_t seed1, const uint32_t seed2, const uint32_t seed3, const uint32_t seed4)
         { 
            s[0] = seed1;
            s[1] = seed2;
            s[2] = seed3;
            s[3] = seed4;
            assert(s[0] != 0U || s[1] != 0U || s[2] != 0U || s[3] != 0U);
         }
         INLINE uint32_t next()
         {
            const uint32_t r = CppCore::rotl32(s[0] + s[3], 7U) + s[0];
            const uint32_t t = s[1] << 9;
            s[2] ^= s[0];
            s[3] ^= s[1];
            s[1] ^= s[2];
            s[0] ^= s[3];
            s[2] ^= t;
            s[3] = CppCore::rotl32(s[3], 11U);
            return r;
         }
      };

      /// <summary>
      /// xoshiro256++ 1.0 PRNG by David Blackman and Sebastiano Vigna creating 64-Bit pseudo randoms.
      /// Must not be seeded with zero.
      /// </summary>
      /// <remarks>
      /// https://prng.di.unimi.it/xoshiro256plusplus.c
      /// </remarks>
      class Xoshiro64 : public PRNG<Xoshiro64, uint64_t, int64_t, double>
      {
         typedef PRNG<Xoshiro64, uint64_t, int64_t, double> Xoshiro64b;
      protected:
         uint64_t s[4];
      public:
         using Xoshiro64b::next;
         INLINE Xoshiro64()
         {
            s[0] = Random::seed64();
            s[1] = Random::seed64();
            s[2] = Random::seed64();
            s[3] = Random::seed64();
            assert(s[0] != 0ULL || s[1] != 0ULL || s[2] != 0ULL || s[3] != 0ULL);
         }
         INLINE Xoshiro64(const uint64_t seed1, const uint64_t seed2, const uint64_t seed3, const uint64_t seed4)
         { 
            s[0] = seed1;
            s[1] = seed2;
            s[2] = seed3;
            s[3] = seed4;
            assert(s[0] != 0ULL || s[1] != 0ULL || s[2] != 0ULL || s[3] != 0ULL);
         }
         INLINE uint64_t next()
         {
            const uint64_t r = CppCore::rotl64(s[0] + s[3], 23U) + s[0];
            const uint64_t t = s[1] << 17;
            s[2] ^= s[0];
            s[3] ^= s[1];
            s[1] ^= s[2];
            s[0] ^= s[3];
            s[2] ^= t;
            s[3] = CppCore::rotl64(s[3], 45U);
            return r;
         }
      };

      /// <summary>
      /// Mulberry32 PRNG by Tommy Ettinger creating 32-Bit pseudo randoms.
      /// </summary>
      /// <remarks>
      /// https://gist.github.com/tommyettinger/46a874533244883189143505d203312c
      /// </remarks>
      class Mulberry32 : public PRNG<Mulberry32, uint32_t, int32_t, float>
      {
         typedef PRNG<Mulberry32, uint32_t, int32_t, float> Mulberry32b;
      protected:
         uint32_t s;
      public:
         using Mulberry32b::next;
         INLINE Mulberry32() : s(Random::seed32()) { }
         INLINE Mulberry32(const uint32_t seed) : s(seed) { }
         INLINE uint32_t next()
         {
            uint32_t r;
            r = s + 0x6D2B79F5U;
            s = r;
            r = (r ^ (r >> 15)) * (r | 1U);
            r = r ^ (r + ((r ^ (r >> 7)) * (r | 61U)));
            return r ^ (r >> 14);
         }
      };

      /// <summary>
      /// Splitmix64 PRNG by Sebastiano Vigna creating 64-Bit pseudo randoms.
      /// </summary>
      /// <remarks>
      /// https://prng.di.unimi.it/splitmix64.c
      /// </remarks>
      class Splitmix64 : public PRNG<Splitmix64, uint64_t, int64_t, double>
      {
         typedef PRNG<Splitmix64, uint64_t, int64_t, double> Splitmix64b;
      protected:
         uint64_t s;
      public:
         using Splitmix64b::next;
         INLINE Splitmix64() : s(Random::seed64()) { }
         INLINE Splitmix64(const uint64_t seed) : s(seed) { }
         INLINE uint64_t next()
         {
            uint64_t r = (s += 0x9E3779B97F4A7C15ULL);
            r = (r ^ (r >> 30)) * 0xBF58476D1CE4E5B9ULL;
            r = (r ^ (r >> 27)) * 0x94D049BB133111EBULL;
            return r ^ (r >> 31);
         }
      };

#if defined(CPPCORE_CPUFEAT_RDRAND) && defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// CPU PRNG creating 32-Bit pseudo random. Uses RDRAND instruction.
      /// Beware: This instruction is known to be buggy, consider testing with validate()
      /// </summary>
      class Cpu32 : public PRNG<Cpu32, uint32_t, int32_t, float>
      {
         typedef PRNG<Cpu32, uint32_t, int32_t, float> Cpu32b;
      public:
         using Cpu32b::next;
         INLINE Cpu32() { }
         INLINE static bool validate(const size_t loops = 512U)
         {
            uint32_t v;
            for (size_t i = 0; i < loops; i++)
               if (_rdrand32_step(&v)) return true;
               else  _mm_pause();
            return false;
         }
         INLINE uint32_t next()
         {
            uint32_t v;
            while (0 == _rdrand32_step(&v))
               _mm_pause();
            return v;
         }
      };

      /// <summary>
      /// CPU PRNG creating 64-Bit pseudo random. Uses RDRAND instruction.
      /// Beware: This instruction is known to be buggy, consider testing with validate()
      /// </summary>
      class Cpu64 : public PRNG<Cpu64, uint64_t, int64_t, double>
      {
         typedef PRNG<Cpu64, uint64_t, int64_t, double> Cpu64b;
      public:
         using Cpu64b::next;
         INLINE Cpu64() { }
         INLINE static bool validate(const size_t loops = 512U)
         {
         #if defined(CPPCORE_CPU_X64)
            uint64_t v;
            for (size_t i = 0; i < loops; i++)
               if (_rdrand64_step((unsigned long long*)&v)) return true;
               else  _mm_pause();
         #elif defined(CPPCORE_CPU_X86)
            uint32_t v;
            for (size_t i = 0; i < loops; i++)
               if (_rdrand32_step(&v)) return true;
               else  _mm_pause();
         #endif
            return false;
         }
         INLINE uint64_t next()
         {
            uint64_t v;
         #if defined(CPPCORE_CPU_X64)
            while (0 == _rdrand64_step((unsigned long long*)&v))
               _mm_pause();
         #elif defined(CPPCORE_CPU_X86)
            while (0 == _rdrand32_step((uint32_t*)&v))
               _mm_pause();
            while (0 == _rdrand32_step(((uint32_t*)&v) + 1))
               _mm_pause();
         #endif
            return v;
         }
      };
#endif

      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STD C++ PRNG
      /////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Pseudo Random Number Generators using std C++
      /// </summary>
      class Std
      {
      protected:
         /// <summary>
         /// Base Class for C++ STD Generators
         /// </summary>
         template <typename T, typename INT, typename SINT, typename REAL, typename GENERATOR>
         class Base : public PRNG<T, INT, SINT, REAL>
         {
         protected:
            GENERATOR mGenerator;
         public:
            using PRNG<T, INT, SINT, REAL>::next;
            INLINE Base(const INT seed) : mGenerator(seed) { }
            INLINE INT next() { return (INT)mGenerator(); }
            INLINE INT next(const INT min, const INT max, const bool uniform = false)
            {
               return uniform ? 
                  std::uniform_int_distribution<INT>(min, max)(mGenerator) :
                  PRNG<T, INT, SINT, REAL>::next(min, max, false);
            }
            INLINE SINT next(const SINT min, const SINT max, const bool uniform = false)
            {
               return uniform ? 
                  std::uniform_int_distribution<SINT>(min, max)(mGenerator) :
                  PRNG<T, INT, SINT, REAL>::next(min, max, false);
            }
            INLINE REAL next(const REAL min, const REAL max)
            {
               return std::uniform_real_distribution<REAL>(min, max)(mGenerator);
            }
         };
      public:
         /// <summary>
         /// Mersenne Twister 19937 PRNG from C++ STD creating 32-Bit pseudo randoms.
         /// </summary>
         class Mt32 : public Base<Mt32, uint32_t, int32_t, float, std::mt19937>
         {
            typedef Base<Mt32, uint32_t, int32_t, float, std::mt19937> Mt32b;
         public:
            INLINE Mt32() : Mt32b(Random::seed32()) { }
            INLINE Mt32(const uint32_t seed) : Mt32b(seed) { assert(seed != 0U); }
         };

         /// <summary>
         /// Mersenne Twister 19937 PRNG from C++ STD creating 64-Bit pseudo randoms.
         /// </summary>
         class Mt64 : public Base<Mt64, uint64_t, int64_t, double, std::mt19937_64>
         {
            typedef Base<Mt64, uint64_t, int64_t, double, std::mt19937_64> Mt64b;
         public:
            INLINE Mt64() : Mt64b(Random::seed64()) { }
            INLINE Mt64(const uint64_t seed) : Mt64b(seed) { assert(seed != 0ULL); }
         };

         using Int32 = Mt32; // for backwards compatibility, todo: remove
         using Int64 = Mt64; // for backwards compatibility, todo: remove
      };

      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // DEFAULT PSEUDO RANDOM NUMBER GENERATOR
      /////////////////////////////////////////////////////////////////////////////////////////////////////////

      #if !defined(CPPCORE_PRNG_DEFAULT32)
      #define CPPCORE_PRNG_DEFAULT32 Random::Mulberry32
      #endif

      #if !defined(CPPCORE_PRNG_DEFAULT64)
      #define CPPCORE_PRNG_DEFAULT64 Random::Splitmix64
      #endif

      using Default32 = CPPCORE_PRNG_DEFAULT32;
      using Default64 = CPPCORE_PRNG_DEFAULT64;

      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CUSTOM PACKED PSEUDO RANDOM NUMBER GENERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Base Class for 32x4 Bits Packed Pseudo Random Number Generators. Requires SSE2.
      /// </summary>
      template<typename T>
      class PPRNG32x4
      {
      protected:
         INLINE T* thiss() const { return (T*)this; }
      public:
         /// <summary>
         /// Empty Constructor
         /// </summary>
         INLINE PPRNG32x4() { }

         /// <summary>
         /// 
         /// </summary>
         INLINE __m128i next(const uint32_t min, const uint32_t max)
         {
            assert(min < max);
            assert(max - min < std::numeric_limits<uint32_t>::max());
            const uint32_t d = (max - min) + 1U;
            union {
               __m128i  n;
               uint32_t n32[4];
            };
            n = thiss()->next();
            n32[0] %= d; n32[1] %= d;
            n32[2] %= d; n32[3] %= d;
            return _mm_add_epi32(n, _mm_set1_epi32(min));
         }

         /// <summary>
         /// 
         /// </summary>
         INLINE __m128i next(const int32_t min, const int32_t max)
         {
            assert(min < max);
            const uint32_t d = (uint32_t)(max - min);
            assert(d <= (uint32_t)std::numeric_limits<int32_t>::max());
            const __m128i r = thiss()->next(0U, d);
            return _mm_add_epi32(r, _mm_set1_epi32(min));
         }

         /// <summary>
         /// 
         /// </summary>
         INLINE __m128 next(const float min, const float max)
         {
            assert(min < max);
            const __m128i v = thiss()->next();
            const __m128  n = CppCore::cvtepu32f(v);
            const __m128  d = _mm_set1_ps((float)std::numeric_limits<uint32_t>::max());
            const __m128  r = _mm_div_ps(n, d);
            return _mm_add_ps(_mm_mul_ps(r, _mm_set1_ps(max - min)), _mm_set1_ps(min));
         }

         /// <summary>
         /// 
         /// </summary>
         INLINE void fill(__m128i* m, const size_t n, const uint32_t min, const uint32_t max)
         {
            assert(min < max);
            assert(max - min < std::numeric_limits<uint32_t>::max());
            const uint32_t d = (max - min) + 1U;
            const __m128i  u = _mm_set1_epi32(min);
            CPPCORE_UNROLL
            for (size_t i = 0; i < n; i++)
            {
               union {
                  __m128i  n;
                  uint32_t n32[4];
               };
               n = thiss()->next();
               n32[0] %= d; n32[1] %= d;
               n32[2] %= d; n32[3] %= d;
               m[i] = _mm_add_epi32(n, u);
            }
         }

         /// <summary>
         /// 
         /// </summary>
         INLINE void fill(__m128i* m, const size_t n, const int32_t min, const int32_t max)
         {
            assert(min < max);
            const uint32_t d = (uint32_t)(max - min);
            assert(d <= (uint32_t)std::numeric_limits<int32_t>::max());
            const __m128i u = _mm_set1_epi32(min);
            CPPCORE_UNROLL
            for (size_t i = 0; i < n; i++)
               m[i] = _mm_add_epi32(thiss()->next(0U, d), u);
         }

         /// <summary>
         /// 
         /// </summary>
         INLINE void fill(__m128* m, const size_t n, const float min, const float max)
         {
            assert(min < max);
            const __m128 c1 = _mm_set1_ps((float)std::numeric_limits<uint32_t>::max());
            const __m128 c2 = _mm_set1_ps(max - min);
            const __m128 c3 = _mm_set1_ps(min);
            CPPCORE_UNROLL
            for (size_t i = 0; i < n; i++)
            {
               const __m128i v = thiss()->next();
               const __m128  n = CppCore::cvtepu32f(v);
               m[i] = _mm_add_ps(_mm_mul_ps(_mm_div_ps(n, c1), c2), c3);
            }
         }
      };
#endif

#if defined(CPPCORE_CPUFEAT_AVX512) && defined(CPPCORE_OS_WINDOWS)
      /// <summary>
      /// Base Class for 64x2 Bits Packed Pseudo Random Number Generators. Requires AVX512.
      /// </summary>
      template<typename T>
      class PPRNG64x2
      {
      protected:
         INLINE T* thiss() const { return (T*)this; }
      public:
         /// <summary>
         /// Empty Constructor
         /// </summary>
         INLINE PPRNG64x2() { }

         /// <summary>
         /// 
         /// </summary>
         INLINE __m128i next(const uint64_t min, const uint64_t max)
         {
            // _mm_mullo_epi64 is avx-512
            assert(min < max);
            assert(max - min < std::numeric_limits<uint64_t>::max());
            const __m128i n = thiss()->next();
            const __m128i d = _mm_set1_epi64x(((max - min) + 1U));
            const __m128i div = _mm_div_epu64(n, d);
            const __m128i rem = _mm_sub_epi64(n, _mm_mullo_epi64(div, d));
            return _mm_add_epi64(rem, _mm_set1_epi64x(min));
         }

         /// <summary>
         /// 
         /// </summary>
         INLINE __m128i next(const int64_t min, const int64_t max)
         {
            assert(min < max);
            const uint64_t d = (uint64_t)(max - min);
            assert(d <= (uint64_t)std::numeric_limits<int64_t>::max());
            const __m128i r = thiss()->next(0ULL, d);
            return _mm_add_epi64(r, _mm_set1_epi64x(min));
         }
         
         /// <summary>
         /// 
         /// </summary>
         INLINE __m128d next(const double min, const double max)
         {
            assert(min < max);
            const __m128i v = thiss()->next();
            const __m128d n = _mm_cvtepu64_pd(v); // this is avx-512
            const __m128d d = _mm_set1_pd((double)std::numeric_limits<uint64_t>::max());
            const __m128d r = _mm_div_pd(n, d);
            return _mm_add_pd(_mm_mul_pd(r, _mm_set1_pd(max - min)), _mm_set1_pd(min));
         }

         /// <summary>
         /// TODO: TEST IT
         /// </summary>
         INLINE void fill(__m128i* m, const size_t n, const uint64_t min, const uint64_t max)
         {
            assert(min < max);
            assert(max - min < std::numeric_limits<uint64_t>::max());
            const __m128i d = _mm_set1_epi64x(((max - min) + 1U));
            const __m128i u = _mm_set1_epi64x(min);
            CPPCORE_UNROLL
            for (size_t i = 0; i < n; i++)
            {
               const __m128i n = thiss()->next();
               const __m128i div = _mm_div_epu64(n, d);
               const __m128i rem = _mm_sub_epi64(n, _mm_mullo_epi64(div, d));
               m[i] = _mm_add_epi64(rem, u);
            }
         }

         /// <summary>
         /// TODO: TEST IT
         /// </summary>
         INLINE void fill(__m128i* m, const size_t n, const int64_t min, const int64_t max)
         {
            assert(min < max);
            const uint64_t d = (uint64_t)(max - min);
            assert(d <= (uint64_t)std::numeric_limits<int64_t>::max());
            const __m128i u = _mm_set1_epi64x(min);
            CPPCORE_UNROLL
            for (size_t i = 0; i < n; i++)
               m[i] = _mm_add_epi64(thiss()->next(0ULL, d), u);
         }

         /// <summary>
         /// TODO: TEST IT
         /// </summary>
         INLINE void fill(__m128d* m, const size_t n, const double min, const double max)
         {
            assert(min < max);
            const __m128d c1 = _mm_set1_pd((double)std::numeric_limits<uint64_t>::max());
            const __m128d c2 = _mm_set1_pd(max - min);
            const __m128d c3 = _mm_set1_pd(min);
            CPPCORE_UNROLL
            for (size_t i = 0; i < n; i++)
            {
               const __m128i v = thiss()->next();
               const __m128d n = _mm_cvtepu64_pd(v); // this is avx-512
               m[i] = _mm_add_pd(_mm_mul_pd(_mm_div_pd(n, c1), c2), c3);
            }
         }
      };
#endif

#if defined(CPPCORE_CPUFEAT_SSE2)
      /// <summary>
      /// Xorshift32 four times in parallel. Requires SSE2.
      /// </summary>
      class Xorshift32x4 : public PPRNG32x4<Xorshift32x4>
      {
         typedef PPRNG32x4<Xorshift32x4> Xorshift32x4b;
      protected:
         __m128i s;
      public:
         using Xorshift32x4b::next;
         INLINE Xorshift32x4() : s(Random::seed32x4()) { }
         INLINE Xorshift32x4(const __m128i& seed) : s(seed)
         {
            assert(_mm_movemask_epi8(_mm_cmpeq_epi32(seed, _mm_setzero_si128())) == 0);
         }
         INLINE Xorshift32x4(const uint32_t s1, const uint32_t s2, const uint32_t s3, const uint32_t s4) :
            s(_mm_set_epi32(s4, s3, s2, s1)) 
         {
            assert(s1 != 0U);
            assert(s2 != 0U);
            assert(s3 != 0U);
            assert(s4 != 0U);
         }
         INLINE __m128i next()
         {
            s = _mm_xor_si128(s, _mm_slli_epi32(s, 13));
            s = _mm_xor_si128(s, _mm_srli_epi32(s, 17));
            s = _mm_xor_si128(s, _mm_slli_epi32(s, 5));
            return s;
         }
      };
#endif

#if defined(CPPCORE_CPUFEAT_AVX512) && defined(CPPCORE_OS_WINDOWS)
      /// <summary>
      /// Xorshift64 two times in parallel. Requires AVX512.
      /// </summary>
      class Xorshift64x2 : public PPRNG64x2<Xorshift64x2>
      {
         typedef PPRNG64x2<Xorshift64x2> Xorshift64x2b;
      protected:
         __m128i s;
      public:
         using Xorshift64x2b::next;
         INLINE Xorshift64x2() : s(Random::seed64x2()) { }
         INLINE Xorshift64x2(const __m128i& seed) : s(seed)
         {
            assert(_mm_movemask_epi8(_mm_cmpeq_epi64(seed, _mm_setzero_si128())) == 0);
         }
         INLINE Xorshift64x2(const uint64_t s1, const uint64_t s2) :
            s(_mm_set_epi64x(s2, s1)) 
         {
            assert(s1 != 0ULL);
            assert(s2 != 0ULL);
         }
         INLINE __m128i next()
         {
            s = _mm_xor_si128(s, _mm_slli_epi64(s, 13));
            s = _mm_xor_si128(s, _mm_srli_epi64(s, 7));
            s = _mm_xor_si128(s, _mm_slli_epi64(s, 17));
            return s;
         }
      };
#endif

#if defined(CPPCORE_CPUFEAT_SSE41)
      /// <summary>
      /// Mulberry32 four times in parallel. Requires SSE4.1.
      /// </summary>
      class Mulberry32x4 : public PPRNG32x4<Mulberry32x4>
      {
         typedef PPRNG32x4<Mulberry32x4> Mulberry32x4b;
      protected:
         __m128i s;
      public:
         using Mulberry32x4b::next;
         INLINE Mulberry32x4() : s(Random::seed32x4()) { }
         INLINE Mulberry32x4(const __m128i& seed) : s(seed) { }
         INLINE Mulberry32x4(const uint32_t s1, const uint32_t s2, const uint32_t s3, const uint32_t s4) :
            s(_mm_set_epi32(s4, s3, s2, s1)) { }
         INLINE __m128i next()
         {
            // _mm_mullo_epi32 is sse4.1
            __m128i r;
            const __m128i c1 = _mm_set1_epi32(0x6D2B79F5U);
            const __m128i c2 = _mm_set1_epi32(1U);
            const __m128i c3 = _mm_set1_epi32(61U);
            r = _mm_add_epi32(s, c1);
            s = r;
            r = _mm_mullo_epi32(_mm_xor_si128(r, _mm_srli_epi32(r, 15)), _mm_or_si128(r, c2));
            r = _mm_xor_si128(r, _mm_add_epi32(r, _mm_mullo_epi32(_mm_xor_si128(r, _mm_srli_epi32(r, 7)), _mm_or_si128(r, c3))));
            r = _mm_xor_si128(r, _mm_srli_epi32(r, 14));
            return r;
         }
      };
#endif

#if defined(CPPCORE_CPUFEAT_AVX512) && defined(CPPCORE_OS_WINDOWS)
      /// <summary>
      /// Splitmix64 two times in parallel. Requires AVX512.
      /// </summary>
      class Splitmix64x2 : public PPRNG64x2<Splitmix64x2>
      {
         typedef PPRNG64x2<Splitmix64x2> Splitmix64x2b;
      protected:
         __m128i s;
      public:
         using Splitmix64x2b::next;
         INLINE Splitmix64x2() : s(Random::seed64x2()) { }
         INLINE Splitmix64x2(const __m128i& seed) : s(seed) { }
         INLINE Splitmix64x2(const uint64_t s1, const uint64_t s2) :
            s(_mm_set_epi64x(s2, s1)) { }
         INLINE __m128i next()
         {
            // _mm_mullo_epi64 is avx512
            __m128i r;
            const __m128i c1 = _mm_set1_epi64x(0x9E3779B97F4A7C15ULL);
            const __m128i c2 = _mm_set1_epi64x(0xBF58476D1CE4E5B9ULL);
            const __m128i c3 = _mm_set1_epi64x(0x94D049BB133111EBULL);
            r = _mm_add_epi64(s, c1);
            s = r;
            r = _mm_mullo_epi64(_mm_xor_si128(r, _mm_srli_epi64(r, 30)), c2);
            r = _mm_mullo_epi64(_mm_xor_si128(r, _mm_srli_epi64(r, 27)), c3);
            r = _mm_xor_si128(r, _mm_srli_epi64(r, 31));
            return r;
         }
      };
#endif
   };
}
