#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Math
{
   /// <summary>
   /// Tests for Primes.h in CppCore::Math
   /// </summary>
   class Primes
   {
   public:
      static constexpr size_t NUMCOMPOSITES32 = 8U;
      static constexpr uint32_t COMPOSITES32[NUMCOMPOSITES32] =
      {
         0x00000004U, // 2²
         0x00000009U, // 3²
         0x0000000FU, // 3*5
         0x00000015U, // 3*7
         0x00281839U, // 1621²
         0x19B72AC9U, // 20771²
         0x61B429F1U, // 40487²
         0xFFFFFFFFU  // 3*0x55555555
      };

      static constexpr size_t NUMCOMPOSITES64  = 7U;
      static constexpr size_t NUMCOMPOSITES64T = 4U; // for trivial
      static constexpr uint64_t COMPOSITES64[NUMCOMPOSITES64] =
      {
         0x000000038F5BDE19ULL, // 123653²
         0x000002C715039331ULL, // 1747591²
         0x0000AAC79D991059ULL, // 13703077²
         0x000A28653DAD63B1ULL, // 53471161²
         0x035D441F423FD219ULL, // 492366587²
         0x6D8E2922B8569A11ULL, // 6692367337²
         0xF935DF089FEE9F41ULL  // 9809862296159²
      };

      template<typename UINT>
      INLINE static bool isprime_trivial()
      {
         // test trivial cases
         const bool t1 =
            CppCore::Primes::isprime_trivial((UINT)0U) == false &&
            CppCore::Primes::isprime_trivial((UINT)1U) == false &&
            CppCore::Primes::isprime_trivial((UINT)2U) == true  &&
            CppCore::Primes::isprime_trivial((UINT)3U) == true;
         if (!t1)
            return false;

         // test precomputed first odd primes
         for (size_t i = 0; i < CppCore::Primes::NUMODDPRIMES; i++)
            if (!CppCore::Primes::isprime_trivial((UINT)CppCore::Primes::ODDPRIMES[i]))
               return false;

         // test some special primes
         // beware of runtime for large ones!
         const bool t2 = 
            CppCore::Primes::isprime_trivial((UINT)20771U)                  &&
            CppCore::Primes::isprime_trivial((UINT)40487U)                  &&
            CppCore::Primes::isprime_trivial((UINT)2481757U)                &&
            CppCore::Primes::isprime_trivial((UINT)CppCore::Primes::MAX32S) &&
            CppCore::Primes::isprime_trivial((UINT)CppCore::Primes::MAX32U);
         if (!t2)
            return false;

         // test some 32-bit composites
         for (size_t i = 0; i < NUMCOMPOSITES32; i++)
            if (CppCore::Primes::isprime_trivial((UINT)COMPOSITES32[i]))
               return false;

         // test some 64-bit composites
         // beware of runtime for large ones!
         if (sizeof(UINT) >= 8U)
            for (size_t i = 0; i < NUMCOMPOSITES64T; i++)
               if (CppCore::Primes::isprime_trivial((UINT)COMPOSITES64[i]))
                  return false;

         return true;
      }

      template<typename UINT>
      INLINE static bool isprime_trial()
      {
         // test trivial cases
         const bool t1 =
            CppCore::Primes::isprime_trial((UINT)0U) == 0U &&
            CppCore::Primes::isprime_trial((UINT)1U) == 0U &&
            CppCore::Primes::isprime_trial((UINT)2U) == 1U &&
            CppCore::Primes::isprime_trial((UINT)3U) == 1U;
         if (!t1)
            return false;

         // test precomputed first odd primes
         for (size_t i = 0; i < CppCore::Primes::NUMODDPRIMES; i++)
            if (1U != CppCore::Primes::isprime_trial((UINT)CppCore::Primes::ODDPRIMES[i]))
               return false;

         // test some primes that are smaller than square of max precomputed prime
         const bool t2 =
            1U == CppCore::Primes::isprime_trial((UINT)20771U) &&
            1U == CppCore::Primes::isprime_trial((UINT)40487U) &&
            1U == CppCore::Primes::isprime_trial((UINT)2481757U);
         if (!t2)
            return false;

         // test some special uncovered primes returning unknown (last tested prime)
         const bool t3 = 
            CppCore::Primes::isprime_trial((UINT)CppCore::Primes::MAX32S) > 1U &&
            CppCore::Primes::isprime_trial((UINT)CppCore::Primes::MAX32U) > 1U;
         if (!t3)
            return false;

         // test some 32-bit composites
         for (size_t i = 0; i < NUMCOMPOSITES32; i++)
            if (1U == CppCore::Primes::isprime_trial((UINT)COMPOSITES32[i]))
               return false;

         return true;
      }

      INLINE static bool isprime32()
      {
         // test trivial cases
         const bool t1 =
            CppCore::Primes::isprime32(0U) == false &&
            CppCore::Primes::isprime32(1U) == false &&
            CppCore::Primes::isprime32(2U) == true  &&
            CppCore::Primes::isprime32(3U) == true;
         if (!t1)
            return false;

         // test precomputed first odd primes
         for (size_t i = 0; i < CppCore::Primes::NUMODDPRIMES; i++)
            if (!CppCore::Primes::isprime32((uint32_t)CppCore::Primes::ODDPRIMES[i]))
               return false;

         // test some special primes
         const bool t2 = 
            CppCore::Primes::isprime32(20771U)                  &&
            CppCore::Primes::isprime32(40487U)                  &&
            CppCore::Primes::isprime32(2481757U)                &&
            CppCore::Primes::isprime32(CppCore::Primes::MAX32S) &&
            CppCore::Primes::isprime32(CppCore::Primes::MAX32U);
         if (!t2)
            return false;

         // test some 32-bit composites
         for (size_t i = 0; i < NUMCOMPOSITES32; i++)
            if (CppCore::Primes::isprime32((uint32_t)COMPOSITES32[i]))
               return false;

         return true;
      }

      INLINE static bool isprime64()
      {
         // test trivial cases
         const bool t1 =
            CppCore::Primes::isprime64(0ULL) == false &&
            CppCore::Primes::isprime64(1ULL) == false &&
            CppCore::Primes::isprime64(2ULL) == true  &&
            CppCore::Primes::isprime64(3ULL) == true;
         if (!t1)
            return false;

         // test precomputed 256 first odd primes
         for (size_t i = 0; i < CppCore::Primes::NUMODDPRIMES; i++)
            if (!CppCore::Primes::isprime64((uint64_t)CppCore::Primes::ODDPRIMES[i]))
               return false;

         // test some special primes
         const bool t2 = 
            CppCore::Primes::isprime64(20771ULL)                          &&
            CppCore::Primes::isprime64(40487ULL)                          &&
            CppCore::Primes::isprime64(2481757ULL)                        &&
            CppCore::Primes::isprime64((uint64_t)CppCore::Primes::MAX32S) &&
            CppCore::Primes::isprime64((uint64_t)CppCore::Primes::MAX32U) &&
            CppCore::Primes::isprime64((uint64_t)CppCore::Primes::MAX64S) &&
            CppCore::Primes::isprime64((uint64_t)CppCore::Primes::MAX64U);
         if (!t2)
            return false;

         // test some 32-bit composites
         for (size_t i = 0; i < NUMCOMPOSITES32; i++)
            if (CppCore::Primes::isprime64((uint64_t)COMPOSITES32[i]))
               return false;

         // test some 64-bit composites
         for (size_t i = 0; i < NUMCOMPOSITES64; i++)
            if (CppCore::Primes::isprime64((uint64_t)COMPOSITES64[i]))
               return false;

         return true;
      }

      INLINE static bool isprime128()
      {
         // test trivial cases
         const bool t1 =
            uint128_t(0ULL).isprime() == CppCore::Primes::Result::Composite &&
            uint128_t(1ULL).isprime() == CppCore::Primes::Result::Composite &&
            uint128_t(2ULL).isprime() == CppCore::Primes::Result::Prime &&
            uint128_t(3ULL).isprime() == CppCore::Primes::Result::Prime;
         if (!t1)
            return false;

         // test precomputed 512 first odd primes
         for (size_t i = 0; i < CppCore::Primes::NUMODDPRIMES; i++)
            if (uint128_t((uint64_t)CppCore::Primes::ODDPRIMES[i]).isprime() != CppCore::Primes::Result::Prime)
               return false;

         // test some covered primes which are guaranteed to be true or false
         const bool t2 =
            uint128_t(20771ULL).isprime()                          == CppCore::Primes::Result::Prime &&
            uint128_t(40487ULL).isprime()                          == CppCore::Primes::Result::Prime &&
            uint128_t(2481757ULL).isprime()                        == CppCore::Primes::Result::Prime &&
            uint128_t((uint64_t)CppCore::Primes::MAX32S).isprime() == CppCore::Primes::Result::Prime &&
            uint128_t((uint64_t)CppCore::Primes::MAX32U).isprime() == CppCore::Primes::Result::Prime &&
            uint128_t((uint64_t)CppCore::Primes::MAX64S).isprime() == CppCore::Primes::Result::Prime &&
            uint128_t((uint64_t)CppCore::Primes::MAX64U).isprime() == CppCore::Primes::Result::Prime &&
            uint128_t(CppCore::Primes::SMALL128).isprime()         == CppCore::Primes::Result::Prime;
         if (!t2)
            return false;

         // test mersenne primes (any size gives true)
         const bool t3 =
            uint128_t(CppCore::Primes::MERSENNE128).isprime() == CppCore::Primes::Result::Prime;
         if (!t3)
            return false;

         // test some uncovered high known primes
         const bool t4 =
            uint128_t(CppCore::Primes::LARGE128).isprime() == CppCore::Primes::Result::LikelyPrime;
         if (!t4)
            return false;

         // test some uncovered perfect squares of high primes
         const bool t5 = 
            (uint128_t(CppCore::Primes::MAX64U) * uint128_t(CppCore::Primes::MAX64U)).isprime() == CppCore::Primes::Result::Composite;
         if (!t5)
            return false;

         return true;
      }

      INLINE static bool ismersenneprime32()
      {
         return
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(0U))   == false && // 0 = no mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(1U))   == false && // 1 = no mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(2U))   == true  && // 2^2-1 = 1st mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(3U))   == true  && // 2^3-1 = 2nd mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(5U))   == true  && // 2^5-1 = 3rd mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(7U))   == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(13U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(17U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(19U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(22U))  == false && // 2^22-1 = no mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(31U))  == true  && // 8th mersenne prime (largest 32)
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint32_t>(32U))  == false;   // 2^32-1 = no mersenne prime
      }

      INLINE static bool ismersenneprime64()
      {
         return
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(0U))   == false && // 0 = no mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(1U))   == false && // 1 = no mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(2U))   == true  && // 2^2-1 = 1st mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(3U))   == true  && // 2^3-1 = 2nd mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(5U))   == true  && // 2^5-1 = 3rd mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(7U))   == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(13U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(17U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(19U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(31U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(40U))  == false && // 2^40-1 = no mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(61U))  == true  && // 9th mersenne prime (largest 64)
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint64_t>(64U))  == false;   // 2^64-1 = no mersenne prime
      }

      INLINE static bool ismersenneprime128()
      {
         return
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(0U))   == false && // 0 = no mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(1U))   == false && // 1 = no mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(2U))   == true  && // 2^2-1 = 1st mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(3U))   == true  && // 2^3-1 = 2nd mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(5U))   == true  && // 2^5-1 = 3rd mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(7U))   == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(13U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(17U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(19U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(31U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(40U))  == false && // 2^40-1 = no mersenne prime
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(61U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(89U))  == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(107U)) == true  && // ..
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(127U)) == true  && // 12th mersenne prime (largest 128)
            CppCore::Primes::ismersenneprime(CppCore::getmersenne<uint128_t>(128U)) == false;   // 2^128-1 = no mersenne prime
      }
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Math {
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(Primes)
   {
   public:
      TEST_METHOD(ISPRIME_TRIVIAL32)  { Assert::AreEqual(true, CppCore::Test::Math::Primes::isprime_trivial<uint32_t>()); }
      TEST_METHOD(ISPRIME_TRIVIAL64)  { Assert::AreEqual(true, CppCore::Test::Math::Primes::isprime_trivial<uint64_t>()); }
      TEST_METHOD(ISPRIME_TRIAL32)    { Assert::AreEqual(true, CppCore::Test::Math::Primes::isprime_trial<uint32_t>()); }
      TEST_METHOD(ISPRIME_TRIAL64)    { Assert::AreEqual(true, CppCore::Test::Math::Primes::isprime_trial<uint64_t>()); }
      TEST_METHOD(ISPRIME32)          { Assert::AreEqual(true, CppCore::Test::Math::Primes::isprime32()); }
      TEST_METHOD(ISPRIME64)          { Assert::AreEqual(true, CppCore::Test::Math::Primes::isprime64()); }
      TEST_METHOD(ISPRIME128)         { Assert::AreEqual(true, CppCore::Test::Math::Primes::isprime128()); }
      TEST_METHOD(ISMERSENNEPRIME32)  { Assert::AreEqual(true, CppCore::Test::Math::Primes::ismersenneprime32()); }
      TEST_METHOD(ISMERSENNEPRIME64)  { Assert::AreEqual(true, CppCore::Test::Math::Primes::ismersenneprime64()); }
      TEST_METHOD(ISMERSENNEPRIME128) { Assert::AreEqual(true, CppCore::Test::Math::Primes::ismersenneprime128()); }
   };
}}}}
#endif
