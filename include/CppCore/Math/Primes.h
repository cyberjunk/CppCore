#pragma once

#include <CppCore/Root.h>
#include <CppCore/BitOps.h>
#include <CppCore/Random.h>
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
      static constexpr uint32_t NUMODDPRIMES = 1024;

      /// <summary>
      /// Default Max Index Argument
      /// </summary>
      static constexpr uint32_t DEFAULTMAXIDX = 64;

      /// <summary>
      /// First 1024 ODD Primes (2 not included)
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
         0x0DE5,0x0DE7,0x0DF3,0x0DFD,0x0DFF,0x0E09,0x0E17,0x0E1D,0x0E21,0x0E27,0x0E2F,0x0E35,0x0E3B,0x0E4B,0x0E57,0x0E59,
         0x0E5D,0x0E6B,0x0E71,0x0E75,0x0E7D,0x0E87,0x0E8F,0x0E95,0x0E9B,0x0EB1,0x0EB7,0x0EB9,0x0EC3,0x0ED1,0x0ED5,0x0EDB,
         0x0EED,0x0EEF,0x0EF9,0x0F07,0x0F0B,0x0F0D,0x0F17,0x0F25,0x0F29,0x0F31,0x0F43,0x0F47,0x0F4D,0x0F4F,0x0F53,0x0F59,
         0x0F5B,0x0F67,0x0F6B,0x0F7F,0x0F95,0x0FA1,0x0FA3,0x0FA7,0x0FAD,0x0FB3,0x0FB5,0x0FBB,0x0FD1,0x0FD3,0x0FD9,0x0FE9,
         0x0FEF,0x0FFB,0x0FFD,0x1003,0x100F,0x101F,0x1021,0x1025,0x102B,0x1039,0x103D,0x103F,0x1051,0x1069,0x1073,0x1079,
         0x107B,0x1085,0x1087,0x1091,0x1093,0x109D,0x10A3,0x10A5,0x10AF,0x10B1,0x10BB,0x10C1,0x10C9,0x10E7,0x10F1,0x10F3,
         0x10FD,0x1105,0x110B,0x1115,0x1127,0x112D,0x1139,0x1145,0x1147,0x1159,0x115F,0x1163,0x1169,0x116F,0x1181,0x1183,
         0x118D,0x119B,0x11A1,0x11A5,0x11A7,0x11AB,0x11C3,0x11C5,0x11D1,0x11D7,0x11E7,0x11EF,0x11F5,0x11FB,0x120D,0x121D,
         0x121F,0x1223,0x1229,0x122B,0x1231,0x1237,0x1241,0x1247,0x1253,0x125F,0x1271,0x1273,0x1279,0x127D,0x128F,0x1297,
         0x12AF,0x12B3,0x12B5,0x12B9,0x12BF,0x12C1,0x12CD,0x12D1,0x12DF,0x12FD,0x1307,0x130D,0x1319,0x1327,0x132D,0x1337,
         0x1343,0x1345,0x1349,0x134F,0x1357,0x135D,0x1367,0x1369,0x136D,0x137B,0x1381,0x1387,0x138B,0x1391,0x1393,0x139D,
         0x139F,0x13AF,0x13BB,0x13C3,0x13D5,0x13D9,0x13DF,0x13EB,0x13ED,0x13F3,0x13F9,0x13FF,0x141B,0x1421,0x142F,0x1433,
         0x143B,0x1445,0x144D,0x1459,0x146B,0x146F,0x1471,0x1475,0x148D,0x1499,0x149F,0x14A1,0x14B1,0x14B7,0x14BD,0x14CB,
         0x14D5,0x14E3,0x14E7,0x1505,0x150B,0x1511,0x1517,0x151F,0x1525,0x1529,0x152B,0x1537,0x153D,0x1541,0x1543,0x1549,
         0x155F,0x1565,0x1567,0x156B,0x157D,0x157F,0x1583,0x158F,0x1591,0x1597,0x159B,0x15B5,0x15BB,0x15C1,0x15C5,0x15CD,
         0x15D7,0x15F7,0x1607,0x1609,0x160F,0x1613,0x1615,0x1619,0x161B,0x1625,0x1633,0x1639,0x163D,0x1645,0x164F,0x1655,
         0x1669,0x166D,0x166F,0x1675,0x1693,0x1697,0x169F,0x16A9,0x16AF,0x16B5,0x16BD,0x16C3,0x16CF,0x16D3,0x16D9,0x16DB,
         0x16E1,0x16E5,0x16EB,0x16ED,0x16F7,0x16F9,0x1709,0x170F,0x1723,0x1727,0x1733,0x1741,0x175D,0x1763,0x1777,0x177B,
         0x178D,0x1795,0x179B,0x179F,0x17A5,0x17B3,0x17B9,0x17BF,0x17C9,0x17CB,0x17D5,0x17E1,0x17E9,0x17F3,0x17F5,0x17FF,
         0x1807,0x1813,0x181D,0x1835,0x1837,0x183B,0x1843,0x1849,0x184D,0x1855,0x1867,0x1871,0x1877,0x187D,0x187F,0x1885,
         0x188F,0x189B,0x189D,0x18A7,0x18AD,0x18B3,0x18B9,0x18C1,0x18C7,0x18D1,0x18D7,0x18D9,0x18DF,0x18E5,0x18EB,0x18F5,
         0x18FD,0x1915,0x191B,0x1931,0x1933,0x1945,0x1949,0x1951,0x195B,0x1979,0x1981,0x1993,0x1997,0x1999,0x19A3,0x19A9,
         0x19AB,0x19B1,0x19B5,0x19C7,0x19CF,0x19DB,0x19ED,0x19FD,0x1A03,0x1A05,0x1A11,0x1A17,0x1A21,0x1A23,0x1A2D,0x1A2F,
         0x1A35,0x1A3F,0x1A4D,0x1A51,0x1A69,0x1A6B,0x1A7B,0x1A7D,0x1A87,0x1A89,0x1A93,0x1AA7,0x1AAB,0x1AAD,0x1AB1,0x1AB9,
         0x1AC9,0x1ACF,0x1AD5,0x1AD7,0x1AE3,0x1AF3,0x1AFB,0x1AFF,0x1B05,0x1B23,0x1B25,0x1B2F,0x1B31,0x1B37,0x1B3B,0x1B41,
         0x1B47,0x1B4F,0x1B55,0x1B59,0x1B65,0x1B6B,0x1B73,0x1B7F,0x1B83,0x1B91,0x1B9D,0x1BA7,0x1BBF,0x1BC5,0x1BD1,0x1BD7,
         0x1BD9,0x1BEF,0x1BF7,0x1C09,0x1C13,0x1C19,0x1C27,0x1C2B,0x1C2D,0x1C33,0x1C3D,0x1C45,0x1C4B,0x1C4F,0x1C55,0x1C73,
         0x1C81,0x1C8B,0x1C8D,0x1C99,0x1CA3,0x1CA5,0x1CB5,0x1CB7,0x1CC9,0x1CE1,0x1CF3,0x1CF9,0x1D09,0x1D1B,0x1D21,0x1D23,
         0x1D35,0x1D39,0x1D3F,0x1D41,0x1D4B,0x1D53,0x1D5D,0x1D63,0x1D69,0x1D71,0x1D75,0x1D7B,0x1D7D,0x1D87,0x1D89,0x1D95,
         0x1D99,0x1D9F,0x1DA5,0x1DA7,0x1DB3,0x1DB7,0x1DC5,0x1DD7,0x1DDB,0x1DE1,0x1DF5,0x1DF9,0x1E01,0x1E07,0x1E0B,0x1E13,
         0x1E17,0x1E25,0x1E2B,0x1E2F,0x1E3D,0x1E49,0x1E4D,0x1E4F,0x1E6D,0x1E71,0x1E89,0x1E8F,0x1E95,0x1EA1,0x1EAD,0x1EBB,
         0x1EC1,0x1EC5,0x1EC7,0x1ECB,0x1EDD,0x1EE3,0x1EEF,0x1EF7,0x1EFD,0x1F01,0x1F0D,0x1F0F,0x1F1B,0x1F39,0x1F49,0x1F4B,
         0x1F51,0x1F67,0x1F75,0x1F7B,0x1F85,0x1F91,0x1F97,0x1F99,0x1F9D,0x1FA5,0x1FAF,0x1FB5,0x1FBB,0x1FD3,0x1FE1,0x1FE7
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
         CppCore::usub(n, (size_t)1U, t);
         s = CppCore::tzcnt(t);
         CppCore::clone(d, t);
         if (s) CppCore::shr(d, d, s);
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
         UINT m;
         if ( n < 2U)                  return false; // 0 and 1 not prime
         if ( n < 4U)                  return true;  // 2 and 3 are prime
         if (((uint32_t)n & 1U) == 0U) return false; // even never prime
         if ( n < 9U)                  return true;  // 5,7 are prime
         if ( n % 3U  == 0U)           return false; // test 3 (const div replaced by compiler)
         if ( n % 5U  == 0U)           return false; // test 5 (const div replaced by compiler)
         if ( n % 7U  == 0U)           return false; // test 7 (const div replaced by compiler)
         UINT p(11U);                   // min. divisor (prime) to test
         CppCore::isqrt(n, m);          // max. divisor to test
         return !hasoddfactor(n, p, m); // test odd numbers in range
      }

      /// <summary>
      /// Trial Prime Check testing first 1024 precomputed odd primes up to 8167. 
      /// Constant complexity up to O(1024).
      /// Returns 1 (true) or 0 (false) for range [0-3] and all even numbers.
      /// Returns 1 (true) or 0 (false) for odd numbers in range [5-66699889].
      /// Returns 8167 (last tested prime) for odd numbers larger than 66699889,
      /// if the first 1024 odd primes don't factorize them, else returns 0 (false).
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
         for (size_t i = 3; i < NUMODDPRIMES; i++) // test precomputed primes up to 8167
         {
            x = ODDPRIMES[i];            // get precomputed prime to test
            if (n == x)      return 1U;  // n is a precomuted prime
            if (n % x == 0U) return 0U;  // precomputed prime is factor of n
         }
         return (n < 66699889U) ? 1U : x; // covered by trial above (8167*8167=66699889)
      }

      ///////////////////////////////////////////////////////////////////////////////////////////
      // 32/64 BIT PRIME TESTS
      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Fast Prime Test for unsigned 32-Bit using Trial Test first and then
      /// SPRP (Determinstic Miller-Rabin Test) with bases 2, 7 and 61
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
      /// Fast Prime Test for signed 32-Bit using Trial Test first and then
      /// SPRP (Determinstic Miller-Rabin Test) with bases 2, 7 and 61
      /// </summary>
      INLINE static bool isprime32(const int32_t n)
      {
         return n < 0 ? false : Primes::isprime32((uint32_t)n);
      }

      /// <summary>
      /// Fast Prime Test for unsigned 64-Bit using Trial Test first and then
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

      /// <summary>
      /// Fast Prime Test for signed 64-Bit using Trial Test first and then
      /// SPRP (Determinstic Miller-Rabin Test).
      /// </summary>
      INLINE static bool isprime64(const int64_t n)
      {
         return n < 0 ? false : Primes::isprime64((uint64_t)n);
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
      struct CPPCORE_ALIGN64 Memory
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
      /// Prime Check for large interes from BigInt.h using Trial Test and Miller-Rabin Test with up to the first 513 primes for a.
      /// Returns 'Prime' or 'NotPrime' rather fast if less than 3317044064679887385961981.
      /// May return 'LikelyPrime' for odd numbers above that (strong pseudo-primes).
      /// Detects Mersenne Primes ('Prime') and simple square root products ('NotPrime') at any size.
      /// Adjust maxidx between 12 and 512 to balance MR-Test certainty vs. runtime.
      /// </summary>
      template<typename UINT>
      INLINE static Primes::Result isprime(const UINT& n, Memory<UINT>& mem, bool sign, uint32_t maxidx = DEFAULTMAXIDX)
      {
         // check for negative number if signed
         if (sign)
         {
            if (CppCore::bittest(n, (uint32_t)(sizeof(UINT) * 8U) - 1U))
               return Primes::NotPrime;
         }

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
         CppCore::isqrt(n, t);
         CppCore::umul(t, t, d);
         if (CppCore::equal(n, d))
            return Primes::NotPrime;

         // lucas-lehmer mersenne prime check
         if (Primes::ismersenneprime(n))
            return Primes::Prime;

         // likely prime, but not certain...
         return Primes::LikelyPrime;
      }

      /// <summary>
      /// Specialization for uint8_t
      /// </summary>
      INLINE static Primes::Result isprime(const uint8_t& n, Memory<uint8_t>& mem, bool sign = false, uint32_t maxidx = 0)
      {
         return (Primes::Result)Primes::isprime32((uint32_t)n);
      }

      /// <summary>
      /// Specialization for uint16_t
      /// </summary>
      INLINE static Primes::Result isprime(const uint16_t& n, Memory<uint16_t>& mem, bool sign = false, uint32_t maxidx = 0)
      {
         return (Primes::Result)Primes::isprime32((uint32_t)n);
      }

      /// <summary>
      /// Specialization for uint32_t
      /// </summary>
      INLINE static Primes::Result isprime(const uint32_t& n, Memory<uint32_t>& mem, bool sign = false, uint32_t maxidx = 0)
      {
         return (Primes::Result)Primes::isprime32(n);
      }

      /// <summary>
      /// Specialization for uint64_t
      /// </summary>
      INLINE static Primes::Result isprime(const uint64_t& n, Memory<uint64_t>& mem, bool sign = false, uint32_t maxidx = 0)
      {
         return (Primes::Result)Primes::isprime64(n);
      }

      /// <summary>
      /// Specialization for int8_t
      /// </summary>
      INLINE static Primes::Result isprime(const int8_t& n, Memory<int8_t>& mem, bool sign = true, uint32_t maxidx = 0)
      {
         return (Primes::Result)Primes::isprime32((int32_t)n);
      }

      /// <summary>
      /// Specialization for int16_t
      /// </summary>
      INLINE static Primes::Result isprime(const int16_t& n, Memory<int16_t>& mem, bool sign = true, uint32_t maxidx = 0)
      {
         return (Primes::Result)Primes::isprime32((int32_t)n);
      }

      /// <summary>
      /// Specialization for int32_t
      /// </summary>
      INLINE static Primes::Result isprime(const int32_t& n, Memory<int32_t>& mem, bool sign = true, uint32_t maxidx = 0)
      {
         return (Primes::Result)Primes::isprime32(n);
      }

      /// <summary>
      /// Specialization for int64_t
      /// </summary>
      INLINE static Primes::Result isprime(const int64_t& n, Memory<int64_t>& mem, bool sign = true, uint32_t maxidx = 0)
      {
         return (Primes::Result)Primes::isprime64(n);
      }

      /// <summary>
      /// Same as other variant but using stack memory.
      /// </summary>
      template<typename INT>
      INLINE static Primes::Result isprime(const INT& n, bool sign, uint32_t maxidx = DEFAULTMAXIDX)
      {
         Primes::Memory<INT> mem;
         return Primes::isprime(n, mem, sign, maxidx);
      }

      /// <summary>
      /// Specialization for uint8_t
      /// </summary>
      INLINE static Primes::Result isprime(const uint8_t& n)
      {
         return (Primes::Result)Primes::isprime32((uint32_t)n);
      }

      /// <summary>
      /// Specialization for uint16_t
      /// </summary>
      INLINE static Primes::Result isprime(const uint16_t& n)
      {
         return (Primes::Result)Primes::isprime32((uint32_t)n);
      }

      /// <summary>
      /// Specialization for uint32_t
      /// </summary>
      INLINE static Primes::Result isprime(const uint32_t& n)
      {
         return (Primes::Result)Primes::isprime32(n);
      }

      /// <summary>
      /// Specialization for uint64_t
      /// </summary>
      INLINE static Primes::Result isprime(const uint64_t& n)
      {
         return (Primes::Result)Primes::isprime64(n);
      }

      /// <summary>
      /// Specialization for int8_t
      /// </summary>
      INLINE static Primes::Result isprime(const int8_t& n)
      {
         return (Primes::Result)Primes::isprime32((int32_t)n);
      }

      /// <summary>
      /// Specialization for int16_t
      /// </summary>
      INLINE static Primes::Result isprime(const int16_t& n)
      {
         return (Primes::Result)Primes::isprime32((int32_t)n);
      }

      /// <summary>
      /// Specialization for int32_t
      /// </summary>
      INLINE static Primes::Result isprime(const int32_t& n)
      {
         return (Primes::Result)Primes::isprime32(n);
      }

      /// <summary>
      /// Specialization for int64_t
      /// </summary>
      INLINE static Primes::Result isprime(const int64_t& n)
      {
         return (Primes::Result)Primes::isprime64(n);
      }

      ///////////////////////////////////////////////////////////////////////////////////////////
      // PRIME GENERATION
      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Generates large prime number in p using provided memory and PRNG
      /// </summary>
      template<typename INT, typename PRNG>
      INLINE static void genprime(INT& p, PRNG& prng, Primes::Memory<INT>& mem, bool sign, uint32_t maxidx = DEFAULTMAXIDX)
      {
         uint8_t* p8 = (uint8_t*)&p;
         do {
            prng.fill(p);
            p8[0] |= 0x01; // make odd
            if (sign) {
               p8[sizeof(INT)-1] &= 0x7F; // make positive
               p8[sizeof(INT)-1] |= 0x40; // make large
            }
            else p8[sizeof(INT)-1] |= 0x80; // make large
         } while (Primes::isprime(p, mem, sign, maxidx) == Primes::NotPrime);
      }

      /// <summary>
      /// Generates large prime number in p using stack memory and temporary default PRNG
      /// </summary>
      template<typename INT>
      INLINE static void genprime(INT& p, bool sign, uint32_t maxidx = DEFAULTMAXIDX)
      {
         Random::Default prng;
         Primes::Memory<INT> mem;
         Primes::genprime(p, prng, mem, sign, maxidx);
      }

      /// <summary>
      /// Generates large uint8_t prime number
      /// </summary>
      INLINE static void genprime(uint8_t& n) { Primes::genprime(n, false, 0); }

      /// <summary>
      /// Generates large uint16_t prime number
      /// </summary>
      INLINE static void genprime(uint16_t& n) { Primes::genprime(n, false, 0); }

      /// <summary>
      /// Generates large uint32_t prime number
      /// </summary>
      INLINE static void genprime(uint32_t& n) { Primes::genprime(n, false, 0); }

      /// <summary>
      /// Generates large uint64_t prime number
      /// </summary>
      INLINE static void genprime(uint64_t& n) { Primes::genprime(n, false, 0); }

      /// <summary>
      /// Generates large int8_t prime number
      /// </summary>
      INLINE static void genprime(int8_t& n)  { Primes::genprime(n, true, 0); }

      /// <summary>
      /// Generates large int16_t prime number
      /// </summary>
      INLINE static void genprime(int16_t& n) { Primes::genprime(n, true, 0); }

      /// <summary>
      /// Generates large int32_t prime number
      /// </summary>
      INLINE static void genprime(int32_t& n) { Primes::genprime(n, true, 0); }

      /// <summary>
      /// Generates large int64_t prime number
      /// </summary>
      INLINE static void genprime(int64_t& n) { Primes::genprime(n, true, 0); }
   };
}
