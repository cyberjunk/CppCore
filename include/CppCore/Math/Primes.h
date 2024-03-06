#pragma once

#include <CppCore/Root.h>
#include <CppCore/BitOps.h>
#include <CppCore/Math/Util.h>

namespace CppCore
{
   /// <summary>
   /// Prime Constants and Tests
   /// </summary>
   class Primes
   {
   public:
      /// <summary>
      /// Prime Check Result
      /// </summary>
      enum Result { NotPrime = 0, Prime = 1, LikelyPrime = 2 };

      /// <summary>
      /// Maximum 32-Bit Signed Prime (0x7FFFFFFF=2147483647)
      /// </summary>
      static constexpr uint32_t MAX32S = 0x7FFFFFFFU;

      /// <summary>
      /// Maximum 32-Bit Unsigned Prime (0xFFFFFFFB=4294967291)
      /// </summary>
      static constexpr uint32_t MAX32U = 0xFFFFFFFBU;

      /// <summary>
      /// Maximum 64-Bit Signed Prime (0x7FFFFFFFFFFFFFE7=9223372036854775783)
      /// </summary>
      static constexpr uint64_t MAX64S = 0x7FFFFFFFFFFFFFE7ULL;
      
      /// <summary>
      /// Maximum 64-Bit Unsigned Prime (0xFFFFFFFFFFFFFFC5=18446744073709551557)
      /// </summary>
      static constexpr uint64_t MAX64U = 0xFFFFFFFFFFFFFFC5ULL;

      /// <summary>
      /// Large 128-Bit Prime (0x0397ffffffffffffffffffffffffffff=4776913109852041418248056622882488319) from OEIS A050918.
      /// </summary>
      static constexpr char LARGE128[] = "4776913109852041418248056622882488319";

      /// <summary>
      /// Small 128-Bit Prime (00000000000257FFFFFFFFFFFFFFFFFF=2833419889721787128217599) from OEIS A050918.
      /// </summary>
      static constexpr char SMALL128[] = "2833419889721787128217599";

      /// <summary>
      /// Largest 128-Bit Mersenne Prime (7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF=170141183460469231731687303715884105727)
      /// </summary>
      static constexpr char MERSENNE128[] = "170141183460469231731687303715884105727";

      /// <summary>
      /// Number of odd primes in the ODDPRIMES array.
      /// </summary>
      static constexpr uint32_t NUMODDPRIMES = 512;

      /// <summary>
      /// First 512 ODD Primes (2 not included)
      /// </summary>
      CPPCORE_ALIGN64 static constexpr uint16_t ODDPRIMES[NUMODDPRIMES] =
      {
         0x0003,0x0005,0x0007,0x000B,0x000D,0x0011,0x0013,0x0017,0x001D,0x001F,0x0025,0x0029,0x002B,0x002F,0x0035,0x003B,
         0x003D,0x0043,0x0047,0x0049,0x004F,0x0053,0x0059,0x0061,0x0065,0x0067,0x006B,0x006D,0x0071,0x007F,0x0083,0x0089,
         0x008B,0x0095,0x0097,0x009D,0x00A3,0x00A7,0x00AD,0x00B3,0x00B5,0x00BF,0x00C1,0x00C5,0x00C7,0x00D3,0x00DF,0x00E3,
         0x00E5,0x00E9,0x00EF,0x00F1,0x00FB,0x0101,0x0107,0x010D,0x010F,0x0115,0x0119,0x011B,0x0125,0x0133,0x0137,0x0139,
         0x013D,0x014B,0x0151,0x015B,0x015D,0x0161,0x0167,0x016F,0x0175,0x017B,0x017F,0x0185,0x018D,0x0191,0x0199,0x01A3,
         0x01A5,0x01AF,0x01B1,0x01B7,0x01BB,0x01C1,0x01C9,0x01CD,0x01CF,0x01D3,0x01DF,0x01E7,0x01EB,0x01F3,0x01F7,0x01FD,
         0x0209,0x020B,0x021D,0x0223,0x022D,0x0233,0x0239,0x023B,0x0241,0x024B,0x0251,0x0257,0x0259,0x025F,0x0265,0x0269,
         0x026B,0x0277,0x0281,0x0283,0x0287,0x028D,0x0293,0x0295,0x02A1,0x02A5,0x02AB,0x02B3,0x02BD,0x02C5,0x02CF,0x02D7,
         0x02DD,0x02E3,0x02E7,0x02EF,0x02F5,0x02F9,0x0301,0x0305,0x0313,0x031D,0x0329,0x032B,0x0335,0x0337,0x033B,0x033D,
         0x0347,0x0355,0x0359,0x035B,0x035F,0x036D,0x0371,0x0373,0x0377,0x038B,0x038F,0x0397,0x03A1,0x03A9,0x03AD,0x03B3,
         0x03B9,0x03C7,0x03CB,0x03D1,0x03D7,0x03DF,0x03E5,0x03F1,0x03F5,0x03FB,0x03FD,0x0407,0x0409,0x040F,0x0419,0x041B,
         0x0425,0x0427,0x042D,0x043F,0x0443,0x0445,0x0449,0x044F,0x0455,0x045D,0x0463,0x0469,0x047F,0x0481,0x048B,0x0493,
         0x049D,0x04A3,0x04A9,0x04B1,0x04BD,0x04C1,0x04C7,0x04CD,0x04CF,0x04D5,0x04E1,0x04EB,0x04FD,0x04FF,0x0503,0x0509,
         0x050B,0x0511,0x0515,0x0517,0x051B,0x0527,0x0529,0x052F,0x0551,0x0557,0x055D,0x0565,0x0577,0x0581,0x058F,0x0593,
         0x0595,0x0599,0x059F,0x05A7,0x05AB,0x05AD,0x05B3,0x05BF,0x05C9,0x05CB,0x05CF,0x05D1,0x05D5,0x05DB,0x05E7,0x05F3,
         0x05FB,0x0607,0x060D,0x0611,0x0617,0x061F,0x0623,0x062B,0x062F,0x063D,0x0641,0x0647,0x0649,0x064D,0x0653,0x0655,
         0x065B,0x0665,0x0679,0x067F,0x0683,0x0685,0x069D,0x06A1,0x06A3,0x06AD,0x06B9,0x06BB,0x06C5,0x06CD,0x06D3,0x06D9,
         0x06DF,0x06F1,0x06F7,0x06FB,0x06FD,0x0709,0x0713,0x071F,0x0727,0x0737,0x0745,0x074B,0x074F,0x0751,0x0755,0x0757,
         0x0761,0x076D,0x0773,0x0779,0x078B,0x078D,0x079D,0x079F,0x07B5,0x07BB,0x07C3,0x07C9,0x07CD,0x07CF,0x07D3,0x07DB,
         0x07E1,0x07EB,0x07ED,0x07F7,0x0805,0x080F,0x0815,0x0821,0x0823,0x0827,0x0829,0x0833,0x083F,0x0841,0x0851,0x0853,
         0x0859,0x085D,0x085F,0x0869,0x0871,0x0883,0x089B,0x089F,0x08A5,0x08AD,0x08BD,0x08BF,0x08C3,0x08CB,0x08DB,0x08DD,
         0x08E1,0x08E9,0x08EF,0x08F5,0x08F9,0x0905,0x0907,0x091D,0x0923,0x0925,0x092B,0x092F,0x0935,0x0943,0x0949,0x094D,
         0x094F,0x0955,0x0959,0x095F,0x096B,0x0971,0x0977,0x0985,0x0989,0x098F,0x099B,0x09A3,0x09A9,0x09AD,0x09C7,0x09D9,
         0x09E3,0x09EB,0x09EF,0x09F5,0x09F7,0x09FD,0x0A13,0x0A1F,0x0A21,0x0A31,0x0A39,0x0A3D,0x0A49,0x0A57,0x0A61,0x0A63,
         0x0A67,0x0A6F,0x0A75,0x0A7B,0x0A7F,0x0A81,0x0A85,0x0A8B,0x0A93,0x0A97,0x0A99,0x0A9F,0x0AA9,0x0AAB,0x0AB5,0x0ABD,
         0x0AC1,0x0ACF,0x0AD9,0x0AE5,0x0AE7,0x0AED,0x0AF1,0x0AF3,0x0B03,0x0B11,0x0B15,0x0B1B,0x0B23,0x0B29,0x0B2D,0x0B3F,
         0x0B47,0x0B51,0x0B57,0x0B5D,0x0B65,0x0B6F,0x0B7B,0x0B89,0x0B8D,0x0B93,0x0B99,0x0B9B,0x0BB7,0x0BB9,0x0BC3,0x0BCB,
         0x0BCF,0x0BDD,0x0BE1,0x0BE9,0x0BF5,0x0BFB,0x0C07,0x0C0B,0x0C11,0x0C25,0x0C2F,0x0C31,0x0C41,0x0C5B,0x0C5F,0x0C61,
         0x0C6D,0x0C73,0x0C77,0x0C83,0x0C89,0x0C91,0x0C95,0x0C9D,0x0CB3,0x0CB5,0x0CB9,0x0CBB,0x0CC7,0x0CE3,0x0CE5,0x0CEB,
         0x0CF1,0x0CF7,0x0CFB,0x0D01,0x0D03,0x0D0F,0x0D13,0x0D1F,0x0D21,0x0D2B,0x0D2D,0x0D3D,0x0D3F,0x0D4F,0x0D55,0x0D69,
         0x0D79,0x0D81,0x0D85,0x0D87,0x0D8B,0x0D8D,0x0DA3,0x0DAB,0x0DB7,0x0DBD,0x0DC7,0x0DC9,0x0DCD,0x0DD3,0x0DD5,0x0DDB,
         0x0DE5,0x0DE7,0x0DF3,0x0DFD,0x0DFF,0x0E09,0x0E17,0x0E1D,0x0E21,0x0E27,0x0E2F,0x0E35,0x0E3B,0x0E4B,0x0E57,0x0E59
      };

      ///////////////////////////////////////////////////////////////////////////////////////////
      // UTIL
      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// SPRP Helper. Calculates t=n-1, s=tzcnt(t) and d=t>>s.
      /// </summary>
      template<typename UINT>
      INLINE static void sprp_tsd(const UINT& n, UINT& t, uint32_t& s, UINT& d)
      {
         t = n - 1U;
         s = CppCore::tzcnt(t);
         d = t;
         if (s) d >>= s;
      }

      /// <summary>
      /// SPRP with precalculated t, s and d and work memory m
      /// </summary>
      template<typename UINT>
      INLINE static bool sprp(const UINT& n, UINT& a, const UINT& t, const uint32_t& s, const UINT& d, UINT& r, UINT m[3])
      {
         assert(a != 1U);
         CppCore::upowmod(a, d, n, r, m);
         if ((r == 1U) | (r == t)) 
            return true;
         for (uint32_t i = 1U; i < s; i++)
         {
            //TODO: usquaremod
            CppCore::umulmod(r, r, n, r, m);
            if (r <= 1U) return false;
            if (r == t)  return true;
         }
         return false;
      }

      /// <summary>
      /// SPRP
      /// </summary>
      template<typename UINT>
      INLINE static bool sprp(const UINT& n, UINT a)
      {
         UINT t, d, r;
         UINT m[3];
         uint32_t s;
         sprp_tsd(n, t, s, d);
         return sprp(n, a, t, s, d, r, m);
      }

      /// <summary>
      /// Testing n % p for all odd numbers in [p, m] in O((m-p)/2).
      /// Requires p to be odd and largerequal 3..
      /// Returns true if odd number in range [p, m] factorized n, else false.
      /// Returns last tested odd number in p.
      /// </summary>
      template<typename UINT>
      INLINE static bool hasoddfactor(const UINT& n, UINT& p, const UINT& m)
      {
         assert(p >= 3U);        // p must be larger or equal 3
         assert((p & 1U) == 1U); // p must be odd number
         //assert(p <= m);         // p must be smaller or equal m
         for (; p <= m; p += 2U) // test odd numbers
            if (n % p == 0U)     // p is factor of n
               return true;      // n has odd factor in [p, m]
         return false;           // n has odd no factor in [p, m]
      }

      /// <summary>
      /// Trivial Prime Check testing all odd numbers from 3 to sqrt(n)/2.
      /// O(1) for n in range [0-3] and even numbers, else up to O(sqrt(n)/2).
      /// On modern CPU less than 1ms for 32-Bit worst case (0xFFFFFFFB),
      /// ~10s for 64-Bit worst case (0xFFFFFFFFFFFFFFC5) and may "never" 
      /// finish for high 128-Bit Primes!
      /// </summary>
      template<typename UINT>
      INLINE static bool isprime_trivial(const UINT& n)
      {
         if ( n < 2U)                  return false; // 0 and 1 not prime
         if ( n < 4U)                  return true;  // 2 and 3 are prime
         if (((uint32_t)n & 1U) == 0U) return false; // even never prime
         if ( n < 9U)                  return true;  // 5,7 are prime
         if ( n % 3U  == 0U)           return false; // test 3 (const div replaced by compiler)
         if ( n % 5U  == 0U)           return false; // test 5 (const div replaced by compiler)
         if ( n % 7U  == 0U)           return false; // test 7 (const div replaced by compiler)
         UINT p(11U);                      // min. divisor (prime) to test
         const UINT& m = CppCore::isqrt(n);// max. divisor to test
         return !hasoddfactor(n, p, m);    // test odd numbers in range
      }

      /// <summary>
      /// Trial Prime Check testing first 512 precomputed odd primes up to 3673. 
      /// Constant complexity up to O(512).
      /// Returns 1 (true) or 0 (false) for range [0-3] and all even numbers.
      /// Returns 1 (true) or 0 (false) for odd numbers in range [5-13490929].
      /// Returns 3673 (last tested prime) for odd numbers larger than 13490929,
      /// if the first 512 odd primes don't factorize them, else returns 0 (false).
      /// </summary>
      template<typename UINT>
      INLINE static uint16_t isprime_trial(const UINT& n)
      {
         uint16_t x;
         if ( n < 2U)                  return 0U;  // 0 and 1 not prime
         if ( n < 4U)                  return 1U;  // 2 and 3 are prime
         if (((uint32_t)n & 1U) == 0U) return 0U;  // even never prime
         if ( n < 9U)                  return 1U;  // 5,7 are prime
         if (n % 3U == 0U)             return 0U;  // test 3 (const div replaced by compiler)
         if (n % 5U == 0U)             return 0U;  // test 5 (const div replaced by compiler)
         if (n % 7U == 0U)             return 0U;  // test 7 (const div replaced by compiler)
         for (size_t i = 3; i < NUMODDPRIMES; i++) // test precomputed primes up to 3673
         {
            x = ODDPRIMES[i];            // get precomputed prime to test
            if (n == x)      return 1U;  // n is a precomuted prime
            if (n % x == 0U) return 0U;  // precomputed prime is factor of n
         }
         return (n < 13490929U) ? 1U : x; // covered by trial above (3673*3673=13490929)
      }

      ///////////////////////////////////////////////////////////////////////////////////////////
      // 32/64 BIT PRIME TESTS
      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Fast Prime Test for 32-Bit using Trial Test first and then
      /// SPRP (Determinstic Miller-Rabin Test).
      /// </summary>
      INLINE static bool isprime32(const uint32_t n)
      {
         const uint16_t X = isprime_trial(n);
         if (X == 0)       return false;
         if (X == 1)       return true;
         if (!sprp(n,2U))  return false;
         if (!sprp(n,7U))  return false;
         if (!sprp(n,61U)) return false;
         return true;
      }

      /// <summary>
      /// Fast Prime Test for 64-Bit using Trial Test first and then
      /// SPRP (Determinstic Miller-Rabin Test).
      /// </summary>
      INLINE static bool isprime64(const uint64_t n)
      {
         constexpr uint64_t C1 =            25326001ULL;
         constexpr uint64_t C2 =          3215031751ULL;
         constexpr uint64_t C3 =       2152302898747ULL;
         constexpr uint64_t C4 =       3474749660383ULL;
         constexpr uint64_t C5 =     341550071728321ULL;
         constexpr uint64_t C6 = 3825123056546413051ULL;
         const uint16_t X  = isprime_trial(n);
         if (X == 0U)                return false;
         if (X == 1U)                return true;
         if (!sprp(n,(uint64_t)2U))  return false;
         if (!sprp(n,(uint64_t)3U))  return false;
         if (!sprp(n,(uint64_t)5U))  return false;
         if (n < C1)                 return true;
         if (!sprp(n,(uint64_t)7U))  return false;
         if (n < C2)                 return true;
         if (!sprp(n,(uint64_t)11U)) return false;
         if (n< C3)                  return true;
         if (!sprp(n,(uint64_t)13U)) return false;
         if (n< C4)                  return true;
         if (!sprp(n,(uint64_t)17U)) return false;
         if (n < C5)                 return true;
         if (!sprp(n,(uint64_t)19U)) return false;
         if (!sprp(n,(uint64_t)23U)) return false;
         if (n < C6)                 return true;
         if (!sprp(n,(uint64_t)29U)) return false;
         if (!sprp(n,(uint64_t)31U)) return false;
         if (!sprp(n,(uint64_t)37U)) return false;
         return true;
      }

      ///////////////////////////////////////////////////////////////////////////////////////////
      // MERSENNE PRIME TESTS
      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns true if n is a Mersenne Prime Number (a.k.a. Lucas-Lehmer Test). 
      /// </summary>
      template<typename UINT>
      INLINE static bool ismersenneprime(const UINT& n)
      {
         if (n <  3U) return false;
         if (n == 3U) return true;
         const uint32_t ith = CppCore::ismersenne(n);
         if (!Primes::isprime32(ith))
            return false;
         struct UINTX2 { UINT x[2]; };
         UINT   s(4U);
         UINTX2 r;
         UINTX2 mem[2];
         for (uint32_t i = 2U; i < ith; i++)
         {
            CppCore::umul(s, s, r);
            CppCore::usub(r, (size_t)2U, r);
            CppCore::umod(s, r, n, mem);
         }
         return CppCore::testzero(s);
      }

      ///////////////////////////////////////////////////////////////////////////////////////////
      // PRIME TEST
      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Memory used by Prime Check algorithm.
      /// </summary>
      template<typename UINT>
      struct Memory
      {
         union {
            struct {
               UINT t;
               UINT d;
               UINT a;
               UINT r;
               UINT m[3];
            };
            UINT mem[7];
         };
         uint32_t s;
      public:
         INLINE Memory() { }
      };

      /// <summary>
      /// Prime Check using Trial Test and Miller-Rabin Test with up to the first 513 primes for a.
      /// Returns 'Prime' or 'NotPrime' rather fast if less than 3317044064679887385961981.
      /// May return 'LikelyPrime' for odd numbers above that (strong pseudo-primes).
      /// Detects Mersenne Primes ('Prime') and simple square root products ('NotPrime') at any size.
      /// Adjust maxidx between 12 and 512 to balance MR-Test certainty vs. runtime
      /// </summary>
      template<typename UINT>
      INLINE static Primes::Result isprime(const UINT& n, Memory<UINT>& mem, uint32_t maxidx = 64)
      {
         // trial test
         const uint16_t x = Primes::isprime_trial(n);
         if (x == 0) return Primes::NotPrime;
         if (x == 1) return Primes::Prime;

         uint32_t& s = mem.s; // s constant, see below 
         UINT&     t = mem.t; // t constant, see below
         UINT&     d = mem.d; // d constant, see below
         UINT&     a = mem.a; // base a to test
         UINT&     r = mem.r; // temporary result
         UINT*     m = mem.m; // work memory

         // calculate constants
         // t = n-1
         // s = tzcnt(t)
         // d = t>>s
         Primes::sprp_tsd(n, t, s, d);

         // miller-rabin test on 2 and first 12 odd primes for base a
         a = 2U;  if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime;
         a = 3U;  if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 0
         a = 5U;  if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 1
                  if (n < 25326001U)                        return Primes::Prime;
         a = 7U;  if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 2
                  if (n < (uint64_t)3215031751ULL)          return Primes::Prime;
         a = 11U; if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 3
                  if (n < (uint64_t)2152302898747ULL)       return Primes::Prime;
         a = 13U; if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 4
                  if (n < (uint64_t)3474749660383ULL)       return Primes::Prime;
         a = 17U; if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 5
                  if (n < (uint64_t)341550071728321ULL)     return Primes::Prime;
         a = 19U; if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 6
         a = 23U; if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 7
                  if (n < (uint64_t)3825123056546413051ULL) return Primes::Prime;
         a = 29U; if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 8
         a = 31U; if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 9
         a = 37U; if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 10
         const UINT C1(0xE92817F9FC85B7E5ULL, 0x000000000000437AULL);  // DEC: 318665857834031151167461
                  if (n < C1)                               return Primes::Prime;
         a = 41U; if (!Primes::sprp(n,a,t,s,d,r,m))         return Primes::NotPrime; // 11
         const UINT C2(0x51ADC5B22410A5FDULL, 0x000000000002BE69ULL);  // DEC:3317044064679887385961981
                  if (n < C2)                               return Primes::Prime;

         // miller-rabin test on up to remaining 500 odd primes for base a
         assert(Primes::ODDPRIMES[11] == 41U);
         maxidx = MIN(maxidx, Primes::NUMODDPRIMES);
         for (uint32_t i = 12U; i < maxidx; i++)
         {
            a = (uint32_t)Primes::ODDPRIMES[i];
            if (!Primes::sprp(n, a, t, s, d, r, m))
               return Primes::NotPrime;
         }

         // perfect square root test
         t = CppCore::isqrt(n);
         if (n == t*t)
            return Primes::NotPrime;

         // lucas-lehmer mersenne prime check
         if (Primes::ismersenneprime(n))
            return Primes::Prime;

         // likely prime, but not certain...
         return Primes::LikelyPrime;
      }

      /// <summary>
      /// Same as other variant but using stack memory.
      /// </summary>
      template<typename UINT>
      INLINE static Primes::Result isprime(const UINT& n, uint32_t maxidx = 64)
      {
         Primes::Memory<UINT> mem;
         return Primes::isprime<UINT>(n, mem, maxidx);
      }

      /// <summary>
      /// Template Specialization for uint8_t
      /// </summary>
      template<> INLINE static Primes::Result isprime<uint8_t>(const uint8_t& n, uint32_t maxidx)
      {
         return (Primes::Result)Primes::isprime32(n);
      }

      /// <summary>
      /// Template Specialization for uint16_t
      /// </summary>
      template<> INLINE static Primes::Result isprime<uint16_t>(const uint16_t& n, uint32_t maxidx)
      {
         return (Primes::Result)Primes::isprime32(n);
      }

      /// <summary>
      /// Template Specialization for uint32_t
      /// </summary>
      template<> INLINE static Primes::Result isprime<uint32_t>(const uint32_t& n, uint32_t maxidx)
      {
         return (Primes::Result)Primes::isprime32(n);
      }

      /// <summary>
      /// Template Specialization for uint64_t
      /// </summary>
      template<> INLINE static Primes::Result isprime<uint64_t>(const uint64_t& n, uint32_t maxidx)
      {
         return (Primes::Result)Primes::isprime64(n);
      }

      /// <summary>
      /// Template Specialization for int8_t
      /// </summary>
      template<> INLINE static Primes::Result isprime<int8_t>(const int8_t& n, uint32_t maxidx)
      {
         return n < 0 ? Primes::Result::NotPrime : (Primes::Result)Primes::isprime32((uint32_t)n);
      }

      /// <summary>
      /// Template Specialization for int16_t
      /// </summary>
      template<> INLINE static Primes::Result isprime<int16_t>(const int16_t& n, uint32_t maxidx)
      {
         return n < 0 ? Primes::Result::NotPrime : (Primes::Result)Primes::isprime32((uint32_t)n);
      }

      /// <summary>
      /// Template Specialization for int32_t
      /// </summary>
      template<> INLINE static Primes::Result isprime<int32_t>(const int32_t& n, uint32_t maxidx)
      {
         return n < 0 ? Primes::Result::NotPrime : (Primes::Result)Primes::isprime32((uint32_t)n);
      }

      /// <summary>
      /// Template Specialization for int64_t
      /// </summary>
      template<> INLINE static Primes::Result isprime<int64_t>(const int64_t& n, uint32_t maxidx)
      {
         return n < 0 ? Primes::Result::NotPrime : (Primes::Result)Primes::isprime64((uint64_t)n);
      }
   };
}
