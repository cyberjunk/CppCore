#pragma once

#include <CppCore.Test/Root.h>

#define CPPCORE_TEST_RANDOM_ITERATIONS 4096

namespace CppCore { namespace Test
{
   /// <summary>
   /// Tests for Random.h in CppCore
   /// </summary>
   class Random
   {
   public:
      template<typename PRNG32>
      INLINE static bool next32()
      {
         PRNG32 rnd;
         // unsigned
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            uint32_t r = rnd.next(0U, 16U);
            if (r > 16U)
               return false;
         }
         // signed
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            int32_t r = rnd.next(-10, 10);
            if (r < -10 || r > 10)
               return false;
         }
         // float
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            float r = rnd.next(-10.0f, 10.0f);
            if (r < -10.0f || r > 10.0f)
               return false;
         }
         return true;
      }

      template<typename PRNG64>
      INLINE static bool next64()
      {
         PRNG64 rnd;
         // unsigned
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            uint64_t r = rnd.next((uint64_t)0ULL, (uint64_t)16ULL);
            if (r > 16U)
               return false;
         }
         // signed
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            int64_t r = rnd.next((int64_t)-10LL, (int64_t)10LL);
            if (r < -10 || r > 10)
               return false;
         }
         // float
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            double r = rnd.next(-10.0, 10.0);
            if (r < -10.0 || r > 10.0)
               return false;
         }
         return true;
      }

      template<typename PRNG32>
      INLINE static bool fill32()
      {
         PRNG32 rnd;
         uint32_t m_uint32[CPPCORE_TEST_RANDOM_ITERATIONS];
         int32_t  m_int32[CPPCORE_TEST_RANDOM_ITERATIONS];
         float    m_float[CPPCORE_TEST_RANDOM_ITERATIONS];

         // unsigned
         rnd.fill(m_uint32, CPPCORE_TEST_RANDOM_ITERATIONS, 0U, 16U);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
            if (m_uint32[i] > 16U)
               return false;

         // signed
         rnd.fill(m_int32, CPPCORE_TEST_RANDOM_ITERATIONS, -10, 10);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
            if (m_int32[i] < -10 || m_int32[i] > 10)
               return false;

         // float
         rnd.fill(m_float, CPPCORE_TEST_RANDOM_ITERATIONS, -10.0f, 10.0f);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
            if (m_float[i] < -10.0f || m_float[i] > 10.0f)
               return false;

         return true;
      }

      template<typename PRNG64>
      INLINE static bool fill64()
      {
         PRNG64 rnd;
         uint64_t m_uint64[CPPCORE_TEST_RANDOM_ITERATIONS];
         int64_t  m_int64[CPPCORE_TEST_RANDOM_ITERATIONS];
         double   m_double[CPPCORE_TEST_RANDOM_ITERATIONS];

         // unsigned
         rnd.fill(m_uint64, CPPCORE_TEST_RANDOM_ITERATIONS, 0ULL, 16ULL);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
            if (m_uint64[i] > 16ULL)
               return false;

         // signed
         rnd.fill(m_int64, CPPCORE_TEST_RANDOM_ITERATIONS, -10LL, 10LL);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
            if (m_int64[i] < -10LL || m_int64[i] > 10LL)
               return false;

         // float
         rnd.fill(m_double, CPPCORE_TEST_RANDOM_ITERATIONS, -10.0, 10.0);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
            if (m_double[i] < -10.0 || m_double[i] > 10.0)
               return false;

         return true;
      }

#if defined(CPPCORE_CPUFEAT_SSE2)
      template<typename PPRNG32x4, typename PRNG32>
      INLINE static bool next32x4()
      {
         const uint32_t s1 = CppCore::Random::seed32();
         const uint32_t s2 = CppCore::Random::seed32();
         const uint32_t s3 = CppCore::Random::seed32();
         const uint32_t s4 = CppCore::Random::seed32();

         PPRNG32x4 rnd(s1, s2, s3, s4);
         PRNG32 rnd1(s1);
         PRNG32 rnd2(s2);
         PRNG32 rnd3(s3);
         PRNG32 rnd4(s4);

         // unsigned
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            union { __m128i r; uint32_t r32[4]; } v;
            v.r = rnd.next(0U, 16U);
            uint32_t v1 = rnd1.next(0U, 16U);
            uint32_t v2 = rnd2.next(0U, 16U);
            uint32_t v3 = rnd3.next(0U, 16U);
            uint32_t v4 = rnd4.next(0U, 16U);
            if (v.r32[0] != v1 || v.r32[1] != v2 || v.r32[2] != v3 || v.r32[3] != v4)
                return false;
            if (v.r32[0] > 16U || v.r32[1] > 16U || v.r32[2] > 16U || v.r32[3] > 16U)
                return false;
         }

         // signed
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            union { __m128i r; int32_t r32[4]; } v;
            v.r = rnd.next(-10, 10);
            int32_t v1 = rnd1.next(-10, 10);
            int32_t v2 = rnd2.next(-10, 10);
            int32_t v3 = rnd3.next(-10, 10);
            int32_t v4 = rnd4.next(-10, 10);
            if (v.r32[0] != v1 || v.r32[1] != v2 || v.r32[2] != v3 || v.r32[3] != v4)
                return false;
            if (v.r32[0] < -10 || v.r32[0] > 10 ||
                v.r32[1] < -10 || v.r32[1] > 10 ||
                v.r32[2] < -10 || v.r32[2] > 10 ||
                v.r32[3] < -10 || v.r32[3] > 10)
                return false;
         }

         // float
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            union { __m128 r; float r32[4]; } v;
            v.r = rnd.next(-10.0f, 10.0f);
            float v1 = rnd1.next(-10.0f, 10.0f);
            float v2 = rnd2.next(-10.0f, 10.0f);
            float v3 = rnd3.next(-10.0f, 10.0f);
            float v4 = rnd4.next(-10.0f, 10.0f);
            // if FMA is enabled, the values can slightly differ
            const float eps = CPPCORE_CPUFEAT_FMA3_ENABLED ? 0.000001f : 0.0f;
            if (::std::abs(v.r32[0]-v1) > eps || 
                ::std::abs(v.r32[1]-v2) > eps || 
                ::std::abs(v.r32[2]-v3) > eps || 
                ::std::abs(v.r32[3]-v4) > eps)
                return false;
            if (v.r32[0] < -10.0f || v.r32[0] > 10.0f ||
                v.r32[1] < -10.0f || v.r32[1] > 10.0f ||
                v.r32[2] < -10.0f || v.r32[2] > 10.0f ||
                v.r32[3] < -10.0f || v.r32[3] > 10.0f)
                return false;
         }

         return true;
      }

      template<typename PPRNG32x4>
      INLINE static bool fill32x4()
      {
         PPRNG32x4 rnd;
         CPPCORE_ALIGN16 uint32_t du32[CPPCORE_TEST_RANDOM_ITERATIONS * 4];
         
         int32_t* di32 = (int32_t*)du32;
         float*   df32 = (float*)du32;

         // unsigned
         rnd.fill((__m128i*)du32, CPPCORE_TEST_RANDOM_ITERATIONS, 0U, 16U);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
            if (du32[i*4+0] > 16U || du32[i*4+1] > 16U ||
                du32[i*4+2] > 16U || du32[i*4+3] > 16U)
                return false;

         // signed
         rnd.fill((__m128i*)du32, CPPCORE_TEST_RANDOM_ITERATIONS, -10, 10);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
            if (di32[i*4+0] < -10 || di32[i*4+0] > 10 ||
                di32[i*4+1] < -10 || di32[i*4+1] > 10 ||
                di32[i*4+2] < -10 || di32[i*4+2] > 10 ||
                di32[i*4+3] < -10 || di32[i*4+3] > 10)
                return false;

         // float
         rnd.fill((__m128*)du32, CPPCORE_TEST_RANDOM_ITERATIONS, -10.0f, 10.0f);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
            if (df32[i*4+0] < -10.0f || df32[i*4+0] > 10.0f ||
                df32[i*4+1] < -10.0f || df32[i*4+1] > 10.0f ||
                df32[i*4+2] < -10.0f || df32[i*4+2] > 10.0f ||
                df32[i*4+3] < -10.0f || df32[i*4+3] > 10.0f)
                return false;

         //todo: test for equal with non-packed versions

         return true;
      }
#endif

#if defined(CPPCORE_CPUFEAT_AVX512)
      template<typename PPRNG64x2, typename PRNG64>
      INLINE static bool next64x2()
      {
         const uint64_t s1 = CppCore::Random::seed64();
         const uint64_t s2 = CppCore::Random::seed64();

         PPRNG64x2 rnd(s1, s2);
         PRNG64 rnd1(s1);
         PRNG64 rnd2(s2);

         // unsigned
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            __m128i r = rnd.next(0ULL, 16ULL);
            uint64_t v[2]{ rnd1.next(0ULL, 16ULL), rnd2.next(0ULL, 16ULL) };

            if (0 != memcmp(&r, &v, 16))
               return false;

            if (v[0] > 16ULL || 
                v[1] > 16ULL)
                return false;
         }

         // signed
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            __m128i r = rnd.next(-10LL, 10LL);
            int64_t v[2]{ rnd1.next(-10LL, 10LL), rnd2.next(-10LL, 10LL) };

            if (0 != memcmp(&r, &v, 16))
               return false;

            if (v[0] < -10LL || v[0] > 10LL ||
                v[1] < -10LL || v[1] > 10LL)
               return false;
         }

         // double
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            __m128d r = rnd.next(-10.0, 10.0);
            double v[2]{ rnd1.next(-10.0, 10.0), rnd2.next(-10.0, 10.0) };

            if (0 != memcmp(&r, &v, 16))
               return false;

            if (v[0] < -10.0 || v[0] > 10.0 ||
                v[1] < -10.0 || v[1] > 10.0)
               return false;
         }

         return true;
      }

      template<typename PPRNG64x2>
      INLINE static bool fill64x2()
      {
         PPRNG64x2 rnd;
         __m128i m_uint64[CPPCORE_TEST_RANDOM_ITERATIONS];
         __m128i m_int64[CPPCORE_TEST_RANDOM_ITERATIONS];
         __m128d m_double[CPPCORE_TEST_RANDOM_ITERATIONS];

         // unsigned
         rnd.fill(m_uint64, CPPCORE_TEST_RANDOM_ITERATIONS, 0ULL, 16ULL);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            uint64_t v[2];
            _mm_storeu_epi64(v, m_uint64[i]);
            if (v[0] > 16ULL || v[1] > 16ULL)
               return false;
         }

         // signed
         rnd.fill(m_int64, CPPCORE_TEST_RANDOM_ITERATIONS, -10LL, 10LL);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            int64_t v[2];
            _mm_storeu_epi64(v, m_int64[i]);
            if (v[0] < -10LL || v[0] > 10LL ||
                v[1] < -10LL || v[1] > 10LL)
                return false;
         }

         // double
         rnd.fill(m_double, CPPCORE_TEST_RANDOM_ITERATIONS, -10.0, 10.0);
         for (size_t i = 0; i < CPPCORE_TEST_RANDOM_ITERATIONS; i++)
         {
            double v[2];
            _mm_storeu_pd(v, m_double[i]);
            if (v[0] < -10.0 || v[0] > 10.0 ||
                v[1] < -10.0 || v[1] > 10.0)
                return false;
         }

         //todo: test for equal with non-packed versions

         return true;
      }
#endif
   };
}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { 
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(Random)
   {
   public:
      TEST_METHOD(XORSHIFT32_NEXT) { Assert::AreEqual(true, CppCore::Test::Random::next32<CppCore::Random::Xorshift32>()); }
      TEST_METHOD(XORSHIFT32_FILL) { Assert::AreEqual(true, CppCore::Test::Random::fill32<CppCore::Random::Xorshift32>()); }
      TEST_METHOD(XORSHIFT64_NEXT) { Assert::AreEqual(true, CppCore::Test::Random::next64<CppCore::Random::Xorshift64>()); }
      TEST_METHOD(XORSHIFT64_FILL) { Assert::AreEqual(true, CppCore::Test::Random::fill64<CppCore::Random::Xorshift64>()); }
      TEST_METHOD(XOSHIRO32_NEXT)  { Assert::AreEqual(true, CppCore::Test::Random::next32<CppCore::Random::Xoshiro32>()); }
      TEST_METHOD(XOSHIRO32_FILL)  { Assert::AreEqual(true, CppCore::Test::Random::fill32<CppCore::Random::Xoshiro32>()); }
      TEST_METHOD(XOSHIRO64_NEXT)  { Assert::AreEqual(true, CppCore::Test::Random::next64<CppCore::Random::Xoshiro64>()); }
      TEST_METHOD(XOSHIRO64_FILL)  { Assert::AreEqual(true, CppCore::Test::Random::fill64<CppCore::Random::Xoshiro64>()); }
      TEST_METHOD(MULBERRY32_NEXT) { Assert::AreEqual(true, CppCore::Test::Random::next32<CppCore::Random::Mulberry32>()); }
      TEST_METHOD(MULBERRY32_FILL) { Assert::AreEqual(true, CppCore::Test::Random::fill32<CppCore::Random::Mulberry32>()); }
      TEST_METHOD(SPLITMIX64_NEXT) { Assert::AreEqual(true, CppCore::Test::Random::next64<CppCore::Random::Splitmix64>()); }
      TEST_METHOD(SPLITMIX64_FILL) { Assert::AreEqual(true, CppCore::Test::Random::fill64<CppCore::Random::Splitmix64>()); }
   #if defined(CPPCORE_CPUFEAT_RDRAND) && defined(CPPCORE_CPUFEAT_SSE2)
      TEST_METHOD(CPU32_NEXT)      { Assert::AreEqual(true, CppCore::Test::Random::next32<CppCore::Random::Cpu32>()); }
      TEST_METHOD(CPU32_FILL)      { Assert::AreEqual(true, CppCore::Test::Random::fill32<CppCore::Random::Cpu32>()); }
      TEST_METHOD(CPU64_NEXT)      { Assert::AreEqual(true, CppCore::Test::Random::next64<CppCore::Random::Cpu64>()); }
      TEST_METHOD(CPU64_FILL)      { Assert::AreEqual(true, CppCore::Test::Random::fill64<CppCore::Random::Cpu64>()); }
   #endif
   #if defined(CPPCORE_CPUFEAT_SSE2)
      TEST_METHOD(XORSHIFT32X4_NEXT) { Assert::AreEqual(true, CppCore::Test::Random::next32x4<CppCore::Random::Xorshift32x4, CppCore::Random::Xorshift32>()); }
      TEST_METHOD(XORSHIFT32X4_FILL) { Assert::AreEqual(true, CppCore::Test::Random::fill32x4<CppCore::Random::Xorshift32x4>()); }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX512) && defined(CPPCORE_OS_WINDOWS)
      TEST_METHOD(XORSHIFT64X2_NEXT) { Assert::AreEqual(true, CppCore::Test::Random::next64x2<CppCore::Random::Xorshift64x2, CppCore::Random::Xorshift64>()); }
      TEST_METHOD(XORSHIFT64X2_FILL) { Assert::AreEqual(true, CppCore::Test::Random::fill64x2<CppCore::Random::Xorshift64x2>()); }
   #endif
   #if defined(CPPCORE_CPUFEAT_SSE41)
      TEST_METHOD(MULBERRY32X4_NEXT) { Assert::AreEqual(true, CppCore::Test::Random::next32x4<CppCore::Random::Mulberry32x4, CppCore::Random::Mulberry32>()); }
      TEST_METHOD(MULBERRY32X4_FILL) { Assert::AreEqual(true, CppCore::Test::Random::fill32x4<CppCore::Random::Mulberry32x4>()); }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX512) && defined(CPPCORE_OS_WINDOWS)
      TEST_METHOD(SPLITMIX64X2_NEXT) { Assert::AreEqual(true, CppCore::Test::Random::next64x2<CppCore::Random::Splitmix64x2, CppCore::Random::Splitmix64>()); }
      TEST_METHOD(SPLITMIX64X2_FILL) { Assert::AreEqual(true, CppCore::Test::Random::fill64x2<CppCore::Random::Splitmix64x2>()); }
   #endif
   };
}}}
#endif
