#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test
{
   /// <summary>
   /// Tests for Encoding.h in CppCore
   /// </summary>
   class Encoding
   {
   public:
      INLINE static bool isdigit()
      {
         char c = 0;
         while (true)
         {
            bool d = CppCore::isdigit(c);
            bool a = d && (
               c == '0' || c == '1' || c == '2' || c == '3' || c == '4' ||
               c == '5' || c == '6' || c == '7' || c == '8' || c == '9');
            bool b = !d && (
               c != '0' && c != '1' && c != '2' && c != '3' && c != '4' &&
               c != '5' && c != '6' && c != '7' && c != '8' && c != '9');
            if (!a && !b)
               return false;
            else
            {
               if (c == (char)0xFF)
                  return true;
               else 
                  c++;
            }
         }
      }
      INLINE static bool isxdigit()
      {
         char c = 0;
         while (true)
         {
            bool d = CppCore::isxdigit(c);
            bool a = d && (
               c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' ||
               c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' ||
               c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F');
            bool b = !d && (
               c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9' &&
               c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e' && c != 'f' && 
               c != 'A' && c != 'B' && c != 'C' && c != 'D' && c != 'E' && c != 'F');
            if (!a && !b)
               return false;
            else
            {
               if (c == (char)0xFF)
                  return true;
               else 
                  c++;
            }
         }
      }
      class BaseX
      {
      public:
         INLINE static bool estimatebits()
         {
            return
               CppCore::BaseX::estimateBits( 0,  2) ==  0 &&
               CppCore::BaseX::estimateBits( 1,  2) ==  1 &&
               CppCore::BaseX::estimateBits( 2,  2) ==  2 &&
               CppCore::BaseX::estimateBits( 1,  3) ==  2 &&
               CppCore::BaseX::estimateBits( 1, 12) ==  4 &&
               CppCore::BaseX::estimateBits( 1, 16) ==  4 &&
               CppCore::BaseX::estimateBits( 8, 16) == 32 &&
               CppCore::BaseX::estimateBits(16, 16) == 64 &&
               CppCore::BaseX::estimateBits( 6, 62) == 36 &&
               CppCore::BaseX::estimateBits( 6, 64) == 36;
         }
         INLINE static bool estimatesymbols()
         {
            bool ok =
               CppCore::BaseX::estimateSymbols( 0,  2) ==  0 &&
               CppCore::BaseX::estimateSymbols( 1,  2) ==  1 &&
               CppCore::BaseX::estimateSymbols(32, 16) ==  8 &&
               CppCore::BaseX::estimateSymbols(64, 16) == 16 &&
               CppCore::BaseX::estimateSymbols(64, 32) == 13 &&
               CppCore::BaseX::estimateSymbols(64, 62) == 13 &&
               CppCore::BaseX::estimateSymbols(32, 64) ==  6;
            if (!ok) 
               return false;
            std::string alphabet;
            for (uint32_t b = 2; b < 256; b++)
            {
               alphabet.resize(b, '0');
               uint32_t e = CppCore::BaseX::estimateSymbols(64, b);
               std::string s = CppCore::BaseX::tostring(UINT64_MAX, alphabet.c_str());
               if (s.length() > e)
                  return false;
            }
            return true;
         }
         INLINE static bool tostring8()
         {
            std::string ss;
            ss.clear(); CppCore::BaseX::tostring(uint8_t(0x00), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("0"    ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint8_t(0x01), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("1"    ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint8_t(0xFF), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("255"  ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint8_t(0x0F), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("15"   ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint8_t(0xBC), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("188"  ) != ss) return false;
            char s[64]; constexpr size_t S = sizeof(s);
            if (S-1  != CppCore::BaseX::tostring(uint8_t(0x00), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "0",   1)) return false;
            if (S-1  != CppCore::BaseX::tostring(uint8_t(0x01), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "1",   1)) return false;
            if (S-3  != CppCore::BaseX::tostring(uint8_t(0xFF), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "255", 3)) return false;
            if (S-2  != CppCore::BaseX::tostring(uint8_t(0x0F), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "15",  2)) return false;
            if (S-3  != CppCore::BaseX::tostring(uint8_t(0xBC), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "188", 3)) return false;
            if (0    != CppCore::BaseX::tostring(uint8_t(0xBC), s, 3,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "188", 3)) return false;
            if (-1   != CppCore::BaseX::tostring(uint8_t(0xFF), s, 2,  10U, CPPCORE_ALPHABET_B10, true)) return false;
            if (-3   != CppCore::BaseX::tostring(uint8_t(0xFF), s, 0,  10U, CPPCORE_ALPHABET_B10, true)) return false;
            // TODO: More than Base10
            return true;
         }
         INLINE static bool tostring16()
         {
            std::string ss;
            ss.clear(); CppCore::BaseX::tostring(uint16_t(0x0000), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("0"    ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint16_t(0x0001), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("1"    ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint16_t(0xFFFF), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("65535") != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint16_t(0x0FFF), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("4095" ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint16_t(0xBC3A), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("48186") != ss) return false;
            char s[64]; constexpr size_t S = sizeof(s);
            if (S-1  != CppCore::BaseX::tostring(uint16_t(0x0000), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "0",     1)) return false;
            if (S-1  != CppCore::BaseX::tostring(uint16_t(0x0001), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "1",     1)) return false;
            if (S-5  != CppCore::BaseX::tostring(uint16_t(0xFFFF), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "65535", 5)) return false;
            if (S-4  != CppCore::BaseX::tostring(uint16_t(0x0FFF), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "4095",  4)) return false;
            if (S-5  != CppCore::BaseX::tostring(uint16_t(0xBC3A), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "48186", 5)) return false;
            if (0    != CppCore::BaseX::tostring(uint16_t(0xBC3A), s, 5,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "48186", 5)) return false;
            if (-1   != CppCore::BaseX::tostring(uint16_t(0xFFFF), s, 4,  10U, CPPCORE_ALPHABET_B10, true)) return false;
            if (-5   != CppCore::BaseX::tostring(uint16_t(0xFFFF), s, 0,  10U, CPPCORE_ALPHABET_B10, true)) return false;
            // TODO: More than Base10
            return true;
         }
         INLINE static bool tostring32()
         {
            std::string ss;
            ss.clear(); CppCore::BaseX::tostring(0x00000000U, ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("0"         ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(0x00000001U, ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("1"         ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(0xFFFFFFFFU, ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("4294967295") != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(0x0FFFFFFFU, ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("268435455" ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(0xBC3A19FAU, ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("3157924346") != ss) return false;
            char s[64]; constexpr size_t S = sizeof(s);
            if (S-1  != CppCore::BaseX::tostring(uint32_t(0x00000000U), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "0",           1)) return false;
            if (S-1  != CppCore::BaseX::tostring(uint32_t(0x00000001U), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "1",           1)) return false;
            if (S-10 != CppCore::BaseX::tostring(uint32_t(0xFFFFFFFFU), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "4294967295", 10)) return false;
            if (S-9  != CppCore::BaseX::tostring(uint32_t(0x0FFFFFFFU), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "268435455",   9)) return false;
            if (S-10 != CppCore::BaseX::tostring(uint32_t(0xBC3A19FAU), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "3157924346", 10)) return false;
            if (0    != CppCore::BaseX::tostring(uint32_t(0xBC3A19FAU), s, 10, 10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "3157924346", 10)) return false;
            if (-1   != CppCore::BaseX::tostring(uint32_t(0xFFFFFFFFU), s, 9,  10U, CPPCORE_ALPHABET_B10, true)) return false;
            if (-10  != CppCore::BaseX::tostring(uint32_t(0xFFFFFFFFU), s, 0,  10U, CPPCORE_ALPHABET_B10, true)) return false;
            // TODO: More than Base10
            return true;
         }
         INLINE static bool tostring64()
         {
            std::string ss;
            ss.clear(); CppCore::BaseX::tostring(uint64_t(0x0000000000000000), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("0"                   ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint64_t(0x0000000000000001), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("1"                   ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint64_t(0xFFFFFFFFFFFFFFFF), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("18446744073709551615") != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint64_t(0x0FFFFFFFFFFFFFFF), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("1152921504606846975" ) != ss) return false;
            ss.clear(); CppCore::BaseX::tostring(uint64_t(0xBC3A19FABC3A19FA), ss, 10U, CPPCORE_ALPHABET_B10); if (std::string("13563181792470112762") != ss) return false;
            char s[64]; constexpr size_t S = sizeof(s);
            if (S-1  != CppCore::BaseX::tostring(uint64_t(0x0000000000000000), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "0",                     1)) return false;
            if (S-1  != CppCore::BaseX::tostring(uint64_t(0x0000000000000001), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "1",                     1)) return false;
            if (S-20 != CppCore::BaseX::tostring(uint64_t(0xFFFFFFFFFFFFFFFF), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "18446744073709551615", 20)) return false;
            if (S-19 != CppCore::BaseX::tostring(uint64_t(0x0FFFFFFFFFFFFFFF), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "1152921504606846975",  19)) return false;
            if (S-20 != CppCore::BaseX::tostring(uint64_t(0xBC3A19FABC3A19FA), s, S,  10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "13563181792470112762", 20)) return false;
            if (0    != CppCore::BaseX::tostring(uint64_t(0xBC3A19FABC3A19FA), s, 20, 10U, CPPCORE_ALPHABET_B10, true) || 0 != ::memcmp(s, "13563181792470112762", 20)) return false;
            if (-1   != CppCore::BaseX::tostring(uint64_t(0xFFFFFFFFFFFFFFFF), s, 19, 10U, CPPCORE_ALPHABET_B10, true)) return false;
            if (-20  != CppCore::BaseX::tostring(uint64_t(0xFFFFFFFFFFFFFFFF), s, 0,  10U, CPPCORE_ALPHABET_B10, true)) return false;
            // TODO: More than Base10
            return true;
         }
         INLINE static bool parse8()
         {
            uint8_t r;
            CppCore::BaseX::parse("",    r, CPPCORE_ALPHABET_B10); if (r != 0) return false;
            CppCore::BaseX::parse("0",   r, CPPCORE_ALPHABET_B10); if (r != 0) return false;
            CppCore::BaseX::parse("1",   r, CPPCORE_ALPHABET_B10); if (r != 1) return false;
            CppCore::BaseX::parse("143", r, CPPCORE_ALPHABET_B10); if (r != 143) return false;
            CppCore::BaseX::parse("255", r, CPPCORE_ALPHABET_B10); if (r != 255) return false;
            CppCore::BaseX::parse("256", r, CPPCORE_ALPHABET_B10); if (r != 0) return false;
            return true;
         }
         INLINE static bool parse16()
         {
            uint16_t r;
            CppCore::BaseX::parse("",      r, CPPCORE_ALPHABET_B10); if (r != 0) return false;
            CppCore::BaseX::parse("0",     r, CPPCORE_ALPHABET_B10); if (r != 0) return false;
            CppCore::BaseX::parse("1",     r, CPPCORE_ALPHABET_B10); if (r != 1) return false;
            CppCore::BaseX::parse("143",   r, CPPCORE_ALPHABET_B10); if (r != 143) return false;
            CppCore::BaseX::parse("255",   r, CPPCORE_ALPHABET_B10); if (r != 255) return false;
            CppCore::BaseX::parse("65535", r, CPPCORE_ALPHABET_B10); if (r != 65535) return false;
            CppCore::BaseX::parse("65536", r, CPPCORE_ALPHABET_B10); if (r != 0) return false;
            return true;
         }
         INLINE static bool parse32()
         {
            uint32_t r;
            CppCore::BaseX::parse("",           r, CPPCORE_ALPHABET_B10); if (r != 0U) return false;
            CppCore::BaseX::parse("0",          r, CPPCORE_ALPHABET_B10); if (r != 0U) return false;
            CppCore::BaseX::parse("1",          r, CPPCORE_ALPHABET_B10); if (r != 1U) return false;
            CppCore::BaseX::parse("143",        r, CPPCORE_ALPHABET_B10); if (r != 143U) return false;
            CppCore::BaseX::parse("255",        r, CPPCORE_ALPHABET_B10); if (r != 255U) return false;
            CppCore::BaseX::parse("65535",      r, CPPCORE_ALPHABET_B10); if (r != 65535U) return false;
            CppCore::BaseX::parse("4294967295", r, CPPCORE_ALPHABET_B10); if (r != 4294967295U) return false;
            CppCore::BaseX::parse("4294967296", r, CPPCORE_ALPHABET_B10); if (r != 0) return false;
            return true;
         }
         INLINE static bool parse64()
         {
            uint64_t r;
            CppCore::BaseX::parse("",           r, CPPCORE_ALPHABET_B10); if (r != 0U) return false;
            CppCore::BaseX::parse("0",          r, CPPCORE_ALPHABET_B10); if (r != 0U) return false;
            CppCore::BaseX::parse("1",          r, CPPCORE_ALPHABET_B10); if (r != 1U) return false;
            CppCore::BaseX::parse("143",        r, CPPCORE_ALPHABET_B10); if (r != 143U) return false;
            CppCore::BaseX::parse("255",        r, CPPCORE_ALPHABET_B10); if (r != 255U) return false;
            CppCore::BaseX::parse("65535",      r, CPPCORE_ALPHABET_B10); if (r != 65535U) return false;
            CppCore::BaseX::parse("4294967295", r, CPPCORE_ALPHABET_B10); if (r != 4294967295U) return false;
            CppCore::BaseX::parse("18446744073709551615", r, CPPCORE_ALPHABET_B10); if (r != 18446744073709551615ULL) return false;
            CppCore::BaseX::parse("18446744073709551616", r, CPPCORE_ALPHABET_B10); if (r != 0) return false;
            return true;
         }
         INLINE static bool parse128()
         {
            uint64_t r[2];
            CppCore::BaseX::parse("",           r, CPPCORE_ALPHABET_B10); if (r[1] != 0U || r[0] != 0U) return false;
            CppCore::BaseX::parse("0",          r, CPPCORE_ALPHABET_B10); if (r[1] != 0U || r[0] != 0U) return false;
            CppCore::BaseX::parse("1",          r, CPPCORE_ALPHABET_B10); if (r[1] != 0U || r[0] != 1U) return false;
            CppCore::BaseX::parse("143",        r, CPPCORE_ALPHABET_B10); if (r[1] != 0U || r[0] != 143U) return false;
            CppCore::BaseX::parse("255",        r, CPPCORE_ALPHABET_B10); if (r[1] != 0U || r[0] != 255U) return false;
            CppCore::BaseX::parse("65535",      r, CPPCORE_ALPHABET_B10); if (r[1] != 0U || r[0] != 65535U) return false;
            CppCore::BaseX::parse("4294967295", r, CPPCORE_ALPHABET_B10); if (r[1] != 0U || r[0] != 4294967295U) return false;
            CppCore::BaseX::parse("18446744073709551615", r, CPPCORE_ALPHABET_B10); if (r[1] != 0U || r[0] != 18446744073709551615ULL) return false;
            CppCore::BaseX::parse("340282366920938463463374607431768211455", r, CPPCORE_ALPHABET_B10); if (r[1] != 0xFFFFFFFFFFFFFFFFULL || r[0] != 0xFFFFFFFFFFFFFFFFULL) return false;
            CppCore::BaseX::parse("340282366920938463463374607431768211456", r, CPPCORE_ALPHABET_B10); if (r[1] != 0U || r[0] != 0U) return false;
            return true;
         }
         INLINE static bool tryparse8()
         {
            uint8_t r;
            if (!CppCore::BaseX::tryparse("0",   r, CPPCORE_ALPHABET_B10) || r != 0) return false;
            if (!CppCore::BaseX::tryparse("1",   r, CPPCORE_ALPHABET_B10) || r != 1) return false;
            if (!CppCore::BaseX::tryparse("143", r, CPPCORE_ALPHABET_B10) || r != 143) return false;
            if (!CppCore::BaseX::tryparse("255", r, CPPCORE_ALPHABET_B10) || r != 255) return false;
            if ( CppCore::BaseX::tryparse("256", r, CPPCORE_ALPHABET_B10)) return false; // add overflow
            if ( CppCore::BaseX::tryparse("2550",r, CPPCORE_ALPHABET_B10)) return false; // mul overflow
            if ( CppCore::BaseX::tryparse("",    r, CPPCORE_ALPHABET_B10)) return false;
            if ( CppCore::BaseX::tryparse("x",   r, CPPCORE_ALPHABET_B10)) return false;
            return true;
         }
         INLINE static bool tryparse16()
         {
            uint16_t r;
            if (!CppCore::BaseX::tryparse("0",     r, CPPCORE_ALPHABET_B10) || r != 0) return false;
            if (!CppCore::BaseX::tryparse("1",     r, CPPCORE_ALPHABET_B10) || r != 1) return false;
            if (!CppCore::BaseX::tryparse("143",   r, CPPCORE_ALPHABET_B10) || r != 143) return false;
            if (!CppCore::BaseX::tryparse("255",   r, CPPCORE_ALPHABET_B10) || r != 255) return false;
            if (!CppCore::BaseX::tryparse("65535", r, CPPCORE_ALPHABET_B10) || r != 65535) return false;
            if ( CppCore::BaseX::tryparse("65536", r, CPPCORE_ALPHABET_B10)) return false; // add overflow
            if ( CppCore::BaseX::tryparse("655350",r, CPPCORE_ALPHABET_B10)) return false; // mul overflow
            if ( CppCore::BaseX::tryparse("",      r, CPPCORE_ALPHABET_B10)) return false;
            if ( CppCore::BaseX::tryparse("x",     r, CPPCORE_ALPHABET_B10)) return false;
            return true;
         }
         INLINE static bool tryparse32()
         {
            uint32_t r;
            if (!CppCore::BaseX::tryparse("0",     r, CPPCORE_ALPHABET_B10) || r != 0) return false;
            if (!CppCore::BaseX::tryparse("1",     r, CPPCORE_ALPHABET_B10) || r != 1) return false;
            if (!CppCore::BaseX::tryparse("143",   r, CPPCORE_ALPHABET_B10) || r != 143) return false;
            if (!CppCore::BaseX::tryparse("255",   r, CPPCORE_ALPHABET_B10) || r != 255) return false;
            if (!CppCore::BaseX::tryparse("65535", r, CPPCORE_ALPHABET_B10) || r != 65535) return false;
            if (!CppCore::BaseX::tryparse("4294967295", r, CPPCORE_ALPHABET_B10) || r != 4294967295U) return false;
            if ( CppCore::BaseX::tryparse("4294967296", r, CPPCORE_ALPHABET_B10)) return false; // add overflow
            if ( CppCore::BaseX::tryparse("42949672950",r, CPPCORE_ALPHABET_B10)) return false; // mul overflow
            if ( CppCore::BaseX::tryparse("",      r, CPPCORE_ALPHABET_B10)) return false;
            if ( CppCore::BaseX::tryparse("x",     r, CPPCORE_ALPHABET_B10)) return false;
            return true;
         }
         INLINE static bool tryparse64()
         {
            uint64_t r;
            if (!CppCore::BaseX::tryparse("0",     r, CPPCORE_ALPHABET_B10) || r != 0) return false;
            if (!CppCore::BaseX::tryparse("1",     r, CPPCORE_ALPHABET_B10) || r != 1) return false;
            if (!CppCore::BaseX::tryparse("143",   r, CPPCORE_ALPHABET_B10) || r != 143) return false;
            if (!CppCore::BaseX::tryparse("255",   r, CPPCORE_ALPHABET_B10) || r != 255) return false;
            if (!CppCore::BaseX::tryparse("65535", r, CPPCORE_ALPHABET_B10) || r != 65535) return false;
            if (!CppCore::BaseX::tryparse("4294967295", r, CPPCORE_ALPHABET_B10) || r != 4294967295U) return false;
            if (!CppCore::BaseX::tryparse("18446744073709551615", r, CPPCORE_ALPHABET_B10) || r != 18446744073709551615ULL) return false;
            if ( CppCore::BaseX::tryparse("18446744073709551616", r, CPPCORE_ALPHABET_B10)) return false; // add overflow
            if ( CppCore::BaseX::tryparse("184467440737095516150",r, CPPCORE_ALPHABET_B10)) return false; // mul overflow
            if ( CppCore::BaseX::tryparse("",      r, CPPCORE_ALPHABET_B10)) return false;
            if ( CppCore::BaseX::tryparse("x",     r, CPPCORE_ALPHABET_B10)) return false;
            return true;
         }
         INLINE static bool tryparse128()
         {
            uint64_t r[2];
            if (!CppCore::BaseX::tryparse("0",          r, CPPCORE_ALPHABET_B10) || r[1] != 0U || r[0] != 0U) return false;
            if (!CppCore::BaseX::tryparse("1",          r, CPPCORE_ALPHABET_B10) || r[1] != 0U || r[0] != 1U) return false;
            if (!CppCore::BaseX::tryparse("143",        r, CPPCORE_ALPHABET_B10) || r[1] != 0U || r[0] != 143U) return false;
            if (!CppCore::BaseX::tryparse("255",        r, CPPCORE_ALPHABET_B10) || r[1] != 0U || r[0] != 255U) return false;
            if (!CppCore::BaseX::tryparse("65535",      r, CPPCORE_ALPHABET_B10) || r[1] != 0U || r[0] != 65535U) return false;
            if (!CppCore::BaseX::tryparse("4294967295", r, CPPCORE_ALPHABET_B10) || r[1] != 0U || r[0] != 4294967295U) return false;
            if (!CppCore::BaseX::tryparse("18446744073709551615", r, CPPCORE_ALPHABET_B10) || r[1] != 0U || r[0] != 18446744073709551615ULL) return false;
            if (!CppCore::BaseX::tryparse("340282366920938463463374607431768211455", r, CPPCORE_ALPHABET_B10) || r[1] != 0xFFFFFFFFFFFFFFFFULL || r[0] != 0xFFFFFFFFFFFFFFFFULL) return false;
            if ( CppCore::BaseX::tryparse("340282366920938463463374607431768211456", r, CPPCORE_ALPHABET_B10)) return false; // add overflow
            if ( CppCore::BaseX::tryparse("3402823669209384634633746074317682114550",r, CPPCORE_ALPHABET_B10)) return false; // mul overflow
            if ( CppCore::BaseX::tryparse("",      r, CPPCORE_ALPHABET_B10)) return false;
            if ( CppCore::BaseX::tryparse("x",     r, CPPCORE_ALPHABET_B10)) return false;
            return true;
         }
      };
      class Hex
      {
      public:
         INLINE static bool encode()
         {
            char s[9 * 2 + 1];
            ::std::string ss;
            
            uint8_t rr0[1] = { 0x00 };
            uint8_t rr1[1] = { 0xA5 };
            uint8_t rr2[2] = { 0xA5,0xFF };
            uint8_t rr3[3] = { 0xA5,0xFF,0x3C };
            uint8_t rr4[4] = { 0xA5,0xFF,0x3C,0x74 };
            uint8_t rr5[5] = { 0xA5,0xFF,0x3C,0x74,0xE9 };
            uint8_t rr6[9] = { 0xA5,0xFF,0x3C,0x74,0xE9,0xA5,0xFF,0x3C,0x04 };

            CppCore::Hex::encode(rr0, s, 1, false, true, true); CppCore::Hex::encode(rr0, ss, 1, false, true, true); if (s != ss || s != std::string("00")) return false;
            CppCore::Hex::encode(rr1, s, 1, false, true, true); CppCore::Hex::encode(rr1, ss, 1, false, true, true); if (s != ss || s != std::string("A5")) return false;
            CppCore::Hex::encode(rr2, s, 2, false, true, true); CppCore::Hex::encode(rr2, ss, 2, false, true, true); if (s != ss || s != std::string("A5FF")) return false;
            CppCore::Hex::encode(rr3, s, 3, false, true, true); CppCore::Hex::encode(rr3, ss, 3, false, true, true); if (s != ss || s != std::string("A5FF3C")) return false;
            CppCore::Hex::encode(rr4, s, 4, false, true, true); CppCore::Hex::encode(rr4, ss, 4, false, true, true); if (s != ss || s != std::string("A5FF3C74")) return false;
            CppCore::Hex::encode(rr5, s, 5, false, true, true); CppCore::Hex::encode(rr5, ss, 5, false, true, true); if (s != ss || s != std::string("A5FF3C74E9")) return false;
            CppCore::Hex::encode(rr6, s, 9, false, true, true); CppCore::Hex::encode(rr6, ss, 9, false, true, true); if (s != ss || s != std::string("A5FF3C74E9A5FF3C04")) return false;

            CppCore::Hex::encode(rr0, s, 1, false, true, false); CppCore::Hex::encode(rr0, ss, 1, false, true, false); if (s != ss || s != std::string("00")) return false;
            CppCore::Hex::encode(rr1, s, 1, false, true, false); CppCore::Hex::encode(rr1, ss, 1, false, true, false); if (s != ss || s != std::string("a5")) return false;
            CppCore::Hex::encode(rr2, s, 2, false, true, false); CppCore::Hex::encode(rr2, ss, 2, false, true, false); if (s != ss || s != std::string("a5ff")) return false;
            CppCore::Hex::encode(rr3, s, 3, false, true, false); CppCore::Hex::encode(rr3, ss, 3, false, true, false); if (s != ss || s != std::string("a5ff3c")) return false;
            CppCore::Hex::encode(rr4, s, 4, false, true, false); CppCore::Hex::encode(rr4, ss, 4, false, true, false); if (s != ss || s != std::string("a5ff3c74")) return false;
            CppCore::Hex::encode(rr5, s, 5, false, true, false); CppCore::Hex::encode(rr5, ss, 5, false, true, false); if (s != ss || s != std::string("a5ff3c74e9")) return false;
            CppCore::Hex::encode(rr6, s, 9, false, true, false); CppCore::Hex::encode(rr6, ss, 9, false, true, false); if (s != ss || s != std::string("a5ff3c74e9a5ff3c04")) return false;

            CppCore::Hex::encode(rr0, s, 1, true, true, true); CppCore::Hex::encode(rr0, ss, 1, true, true, true); if (s != ss || s != std::string("00")) return false;
            CppCore::Hex::encode(rr1, s, 1, true, true, true); CppCore::Hex::encode(rr1, ss, 1, true, true, true); if (s != ss || s != std::string("A5")) return false;
            CppCore::Hex::encode(rr2, s, 2, true, true, true); CppCore::Hex::encode(rr2, ss, 2, true, true, true); if (s != ss || s != std::string("FFA5")) return false;
            CppCore::Hex::encode(rr3, s, 3, true, true, true); CppCore::Hex::encode(rr3, ss, 3, true, true, true); if (s != ss || s != std::string("3CFFA5")) return false;
            CppCore::Hex::encode(rr4, s, 4, true, true, true); CppCore::Hex::encode(rr4, ss, 4, true, true, true); if (s != ss || s != std::string("743CFFA5")) return false;
            CppCore::Hex::encode(rr5, s, 5, true, true, true); CppCore::Hex::encode(rr5, ss, 5, true, true, true); if (s != ss || s != std::string("E9743CFFA5")) return false;
            CppCore::Hex::encode(rr6, s, 9, true, true, true); CppCore::Hex::encode(rr6, ss, 9, true, true, true); if (s != ss || s != std::string("043CFFA5E9743CFFA5")) return false;

            CppCore::Hex::encode(rr0, s, 1, true, true, false); CppCore::Hex::encode(rr0, ss, 1, true, true, false); if (s != ss || s != std::string("00")) return false;
            CppCore::Hex::encode(rr1, s, 1, true, true, false); CppCore::Hex::encode(rr1, ss, 1, true, true, false); if (s != ss || s != std::string("a5")) return false;
            CppCore::Hex::encode(rr2, s, 2, true, true, false); CppCore::Hex::encode(rr2, ss, 2, true, true, false); if (s != ss || s != std::string("ffa5")) return false;
            CppCore::Hex::encode(rr3, s, 3, true, true, false); CppCore::Hex::encode(rr3, ss, 3, true, true, false); if (s != ss || s != std::string("3cffa5")) return false;
            CppCore::Hex::encode(rr4, s, 4, true, true, false); CppCore::Hex::encode(rr4, ss, 4, true, true, false); if (s != ss || s != std::string("743cffa5")) return false;
            CppCore::Hex::encode(rr5, s, 5, true, true, false); CppCore::Hex::encode(rr5, ss, 5, true, true, false); if (s != ss || s != std::string("e9743cffa5")) return false;
            CppCore::Hex::encode(rr6, s, 9, true, true, false); CppCore::Hex::encode(rr6, ss, 9, true, true, false); if (s != ss || s != std::string("043cffa5e9743cffa5")) return false;
            
            return true;
         }
         INLINE static bool decode()
         {
            uint8_t out[9];

            uint8_t rr0[1] = { 0x00 };
            uint8_t rr1[1] = { 0xA5 };
            uint8_t rr2[2] = { 0xA5,0xFF };
            uint8_t rr3[3] = { 0xA5,0xFF,0x3C };
            uint8_t rr4[4] = { 0xA5,0xFF,0x3C,0x74 };
            uint8_t rr5[5] = { 0xA5,0xFF,0x3C,0x74,0xE9 };
            uint8_t rr6[9] = { 0xA5,0xFF,0x3C,0x74,0xE9,0xA5,0xFF,0x3C,0x04 };

            CppCore::Hex::decode("00",         out, 2, false); if (::memcmp(out, rr0, 1) != 0) return false;
            CppCore::Hex::decode("A5",         out, 2, false); if (::memcmp(out, rr1, 1) != 0) return false;
            CppCore::Hex::decode("A5FF",       out, 4, false); if (::memcmp(out, rr2, 2) != 0) return false;
            CppCore::Hex::decode("A5FF3C",     out, 6, false); if (::memcmp(out, rr3, 3) != 0) return false;
            CppCore::Hex::decode("A5FF3C74",   out, 8, false); if (::memcmp(out, rr4, 4) != 0) return false;
            CppCore::Hex::decode("A5FF3C74E9", out, 10, false); if (::memcmp(out, rr5, 5) != 0) return false;
            CppCore::Hex::decode("A5FF3C74E9A5FF3C04", out, 18, false); if (::memcmp(out, rr6, 9) != 0) return false;

            CppCore::Hex::decode("00",                 out, 2, true); if (::memcmp(out, rr0, 1) != 0) return false;
            CppCore::Hex::decode("A5",                 out, 2, true); if (::memcmp(out, rr1, 1) != 0) return false;
            CppCore::Hex::decode("FFA5",               out, 4, true); if (::memcmp(out, rr2, 2) != 0) return false;
            CppCore::Hex::decode("3CFFA5",             out, 6, true); if (::memcmp(out, rr3, 3) != 0) return false;
            CppCore::Hex::decode("743CFFA5",           out, 8, true); if (::memcmp(out, rr4, 4) != 0) return false;
            CppCore::Hex::decode("E9743CFFA5",         out, 10, true); if (::memcmp(out, rr5, 5) != 0) return false;
            CppCore::Hex::decode("043CFFA5E9743CFFA5", out, 18, true); if (::memcmp(out, rr6, 9) != 0) return false;

            return true;
         }
         INLINE static bool tostring16()
         {
            char s[5];
            char l[9];

            CppCore::Hex::tostring(uint16_t(0x0000), s, true); if (std::string("0000") != s) return false;
            CppCore::Hex::tostring(uint16_t(0x0001), s, true); if (std::string("0001") != s) return false;
            CppCore::Hex::tostring(uint16_t(0xFFFF), s, true); if (std::string("FFFF") != s) return false;
            CppCore::Hex::tostring(uint16_t(0x0FFF), s, true); if (std::string("0FFF") != s) return false;
            CppCore::Hex::tostring(uint16_t(0xBC3A), s, true); if (std::string("BC3A") != s) return false;

            CppCore::Hex::tostring(uint16_t(0x0000), s, false); if (std::string("0000") != s) return false;
            CppCore::Hex::tostring(uint16_t(0x0100), s, false); if (std::string("0001") != s) return false;
            CppCore::Hex::tostring(uint16_t(0xFFFF), s, false); if (std::string("FFFF") != s) return false;
            CppCore::Hex::tostring(uint16_t(0xFF0F), s, false); if (std::string("0FFF") != s) return false;
            CppCore::Hex::tostring(uint16_t(0x3ABC), s, false); if (std::string("BC3A") != s) return false;

            return true;
         }
         INLINE static bool tostring32()
         {
            char s[9];
            char l[17];

            CppCore::Hex::tostring(0x00000000U, s, true); if (std::string("00000000") != s) return false;
            CppCore::Hex::tostring(0x00000001U, s, true); if (std::string("00000001") != s) return false;
            CppCore::Hex::tostring(0xFFFFFFFFU, s, true); if (std::string("FFFFFFFF") != s) return false;
            CppCore::Hex::tostring(0x0FFFFFFFU, s, true); if (std::string("0FFFFFFF") != s) return false;
            CppCore::Hex::tostring(0xBC3A19FAU, s, true); if (std::string("BC3A19FA") != s) return false;

            CppCore::Hex::tostring(0x00000000U, s, false); if (std::string("00000000") != s) return false;
            CppCore::Hex::tostring(0x01000000U, s, false); if (std::string("00000001") != s) return false;
            CppCore::Hex::tostring(0xFFFFFFFFU, s, false); if (std::string("FFFFFFFF") != s) return false;
            CppCore::Hex::tostring(0xFFFFFF0FU, s, false); if (std::string("0FFFFFFF") != s) return false;
            CppCore::Hex::tostring(0xFA193ABCU, s, false); if (std::string("BC3A19FA") != s) return false;

            return true;
         }
         INLINE static bool tostring64()
         {
            char s[17];
            char l[33];

            CppCore::Hex::tostring(uint64_t(0x0000000000000000), s, true); if (std::string("0000000000000000") != s) return false;
            CppCore::Hex::tostring(uint64_t(0x0000000000000001), s, true); if (std::string("0000000000000001") != s) return false;
            CppCore::Hex::tostring(uint64_t(0xFFFFFFFFFFFFFFFF), s, true); if (std::string("FFFFFFFFFFFFFFFF") != s) return false;
            CppCore::Hex::tostring(uint64_t(0x0FFFFFFFFFFFFFFF), s, true); if (std::string("0FFFFFFFFFFFFFFF") != s) return false;
            CppCore::Hex::tostring(uint64_t(0xBC3A19FABC3A19FA), s, true); if (std::string("BC3A19FABC3A19FA") != s) return false;

            CppCore::Hex::tostring(uint64_t(0x0000000000000000), s, false); if (std::string("0000000000000000") != s) return false;
            CppCore::Hex::tostring(uint64_t(0x0100000000000000), s, false); if (std::string("0000000000000001") != s) return false;
            CppCore::Hex::tostring(uint64_t(0xFFFFFFFFFFFFFFFF), s, false); if (std::string("FFFFFFFFFFFFFFFF") != s) return false;
            CppCore::Hex::tostring(uint64_t(0xFFFFFFFFFFFFFF0F), s, false); if (std::string("0FFFFFFFFFFFFFFF") != s) return false;
            CppCore::Hex::tostring(uint64_t(0xFA193ABCFA193ABC), s, false); if (std::string("BC3A19FABC3A19FA") != s) return false;

            return true;
         }
         INLINE static bool parse16()
         {
            uint16_t r;

            if (!CppCore::Hex::tryparse("0",    r, true) || r != 0x0000U) return false;
            if (!CppCore::Hex::tryparse("0000", r, true) || r != 0x0000U) return false;
            if (!CppCore::Hex::tryparse("1",    r, true) || r != 0x0001U) return false;
            if (!CppCore::Hex::tryparse("0001", r, true) || r != 0x0001U) return false;
            if (!CppCore::Hex::tryparse("FFFF", r, true) || r != 0xFFFFU) return false;
            if (!CppCore::Hex::tryparse("0FFF", r, true) || r != 0x0FFFU) return false;
            if (!CppCore::Hex::tryparse("BC3A", r, true) || r != 0xBC3AU) return false;
            if (!CppCore::Hex::tryparse("1FF",  r, true) || r != 0x01FFU) return false;

            if (!CppCore::Hex::tryparse("0",    r, false) || r != 0x0000U) return false;
            if (!CppCore::Hex::tryparse("0000", r, false) || r != 0x0000U) return false;
            if (!CppCore::Hex::tryparse("1",    r, false) || r != 0x0001U) return false;
            if (!CppCore::Hex::tryparse("0001", r, false) || r != 0x0100U) return false;
            if (!CppCore::Hex::tryparse("FFFF", r, false) || r != 0xFFFFU) return false;
            if (!CppCore::Hex::tryparse("0FFF", r, false) || r != 0xFF0FU) return false;
            if (!CppCore::Hex::tryparse("BC3A", r, false) || r != 0x3ABCU) return false;
            if (!CppCore::Hex::tryparse("1FF",  r, false) || r != 0x0F1FU) return false;

            if (CppCore::Hex::tryparse("10000", r, true)) return false; // overflow
            if (CppCore::Hex::tryparse("12X3",  r, true)) return false; // invalid symbol
            if (CppCore::Hex::tryparse("-1",    r, true)) return false; // invalid symbol
            if (CppCore::Hex::tryparse("+1",    r, true)) return false; // invalid symbol
            if (CppCore::Hex::tryparse("FFFFX", r, true)) return false; // invalid symbol after valid max
            if (CppCore::Hex::tryparse("00001", r, true)) return false; // too many leading zeros
            if (CppCore::Hex::tryparse("",      r, true)) return false; // empty input
            if (CppCore::Hex::tryparse((const char*)0,r, true)) return false; // null pointer

            return true;
         }
         INLINE static bool parse32()
         {
            uint32_t r;

            if (!CppCore::Hex::tryparse("0",        r, true) || r != 0x00000000U) return false;
            if (!CppCore::Hex::tryparse("00000000", r, true) || r != 0x00000000U) return false;
            if (!CppCore::Hex::tryparse("1",        r, true) || r != 0x00000001U) return false;
            if (!CppCore::Hex::tryparse("00000001", r, true) || r != 0x00000001U) return false;
            if (!CppCore::Hex::tryparse("FFFFFFFF", r, true) || r != 0xFFFFFFFFU) return false;
            if (!CppCore::Hex::tryparse("0FFFFFFF", r, true) || r != 0x0FFFFFFFU) return false;
            if (!CppCore::Hex::tryparse("BC3A19FA", r, true) || r != 0xBC3A19FAU) return false;

            if (!CppCore::Hex::tryparse("0",        r, false) || r != 0x00000000U) return false;
            if (!CppCore::Hex::tryparse("00000000", r, false) || r != 0x00000000U) return false;
            if (!CppCore::Hex::tryparse("1",        r, false) || r != 0x00000001U) return false;
            if (!CppCore::Hex::tryparse("00000001", r, false) || r != 0x01000000U) return false;
            if (!CppCore::Hex::tryparse("FFFFFFFF", r, false) || r != 0xFFFFFFFFU) return false;
            if (!CppCore::Hex::tryparse("0FFFFFFF", r, false) || r != 0xFFFFFF0FU) return false;
            if (!CppCore::Hex::tryparse("BC3A19FA", r, false) || r != 0xFA193ABCU) return false;

            if (CppCore::Hex::tryparse("100000000",   r, true)) return false; // overflow
            if (CppCore::Hex::tryparse("12X345",      r, true)) return false; // invalid symbol
            if (CppCore::Hex::tryparse("-1",          r, true)) return false; // invalid symbol
            if (CppCore::Hex::tryparse("+1",          r, true)) return false; // invalid symbol
            if (CppCore::Hex::tryparse("FFFFFFFFX",   r, true)) return false; // invalid symbol after valid max
            if (CppCore::Hex::tryparse("000000001",   r, true)) return false; // too many leading zeros
            if (CppCore::Hex::tryparse("",            r, true)) return false; // empty input
            if (CppCore::Hex::tryparse((const char*)0,r, true)) return false; // null pointer

            return true;
         }
         INLINE static bool parse64()
         {
            uint64_t r;

            if (!CppCore::Hex::tryparse("0",                r, true) || r != 0x0000000000000000ULL) return false;
            if (!CppCore::Hex::tryparse("0000000000000000", r, true) || r != 0x0000000000000000ULL) return false;
            if (!CppCore::Hex::tryparse("1",                r, true) || r != 0x0000000000000001ULL) return false;
            if (!CppCore::Hex::tryparse("0000000000000001", r, true) || r != 0x0000000000000001ULL) return false;
            if (!CppCore::Hex::tryparse("FFFFFFFFFFFFFFFF", r, true) || r != 0xFFFFFFFFFFFFFFFFULL) return false;
            if (!CppCore::Hex::tryparse("0FFFFFFFFFFFFFFF", r, true) || r != 0x0FFFFFFFFFFFFFFFULL) return false;
            if (!CppCore::Hex::tryparse("BC3A19FABC3A19FA", r, true) || r != 0xBC3A19FABC3A19FAULL) return false;

            if (!CppCore::Hex::tryparse("0",                r, false) || r != 0x0000000000000000ULL) return false;
            if (!CppCore::Hex::tryparse("0000000000000000", r, false) || r != 0x0000000000000000ULL) return false;
            if (!CppCore::Hex::tryparse("1",                r, false) || r != 0x0000000000000001ULL) return false;
            if (!CppCore::Hex::tryparse("0000000000000001", r, false) || r != 0x0100000000000000ULL) return false;
            if (!CppCore::Hex::tryparse("FFFFFFFFFFFFFFFF", r, false) || r != 0xFFFFFFFFFFFFFFFFULL) return false;
            if (!CppCore::Hex::tryparse("0FFFFFFFFFFFFFFF", r, false) || r != 0xFFFFFFFFFFFFFF0FULL) return false;
            if (!CppCore::Hex::tryparse("BC3A19FABC3A19FA", r, false) || r != 0xFA193ABCFA193ABCULL) return false;

            if (CppCore::Hex::tryparse("10000000000000000", r, true)) return false; // overflow
            if (CppCore::Hex::tryparse("12X345",            r, true)) return false; // invalid symbol
            if (CppCore::Hex::tryparse("-1",                r, true)) return false; // invalid symbol
            if (CppCore::Hex::tryparse("+1",                r, true)) return false; // invalid symbol
            if (CppCore::Hex::tryparse("FFFFFFFFFFFFFFFFX", r, true)) return false; // invalid symbol after valid max
            if (CppCore::Hex::tryparse("00000000000000001", r, true)) return false; // too many leading zeros
            if (CppCore::Hex::tryparse("",                  r, true)) return false; // empty input
            if (CppCore::Hex::tryparse((const char*)0,      r, true)) return false; // null pointer

            return true;
         }
      };
      class Base64
      {
      public:
         INLINE static bool bytelength()
         {
            // STD
            if (CppCore::Base64::bytelength("",         0) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("=",        1) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("==",       2) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("a",        1) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("aa",       2) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("aa=",      3) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("aa==",     4) != 1) return false; // ok
            if (CppCore::Base64::bytelength("aaa=",     4) != 2) return false; // ok
            if (CppCore::Base64::bytelength("aaaa",     4) != 3) return false; // ok
            if (CppCore::Base64::bytelength("aa=a",     4) != 3) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("(aaa",     4) != 3) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("aaaaa",    5) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("aaaaaa",   6) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("aaaaaa=",  7) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("aaaaaa==", 8) != 4) return false; // ok
            if (CppCore::Base64::bytelength("aaaaaaa=", 8) != 5) return false; // ok
            if (CppCore::Base64::bytelength("aaaaaaaa", 8) != 6) return false; // ok
            // URL
            if (CppCore::Base64::bytelength("",         0, true) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("=",        1, true) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("==",       2, true) != 1) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("a",        1, true) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("aa",       2, true) != 1) return false; // ok
            if (CppCore::Base64::bytelength("aa=",      3, true) != 2) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("aa==",     4, true) != 3) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("aaa=",     4, true) != 3) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("aaaa",     4, true) != 3) return false; // ok
            if (CppCore::Base64::bytelength("aa=a",     4, true) != 3) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("(aaa",     4, true) != 3) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("aaaaa",    5, true) != 0) return false; // invalid length
            if (CppCore::Base64::bytelength("aaaaaa",   6, true) != 4) return false; // ok
            if (CppCore::Base64::bytelength("aaaaaa=",  7, true) != 5) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("aaaaaa==", 8, true) != 6) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("aaaaaaa=", 8, true) != 6) return false; // ok (invalid symbol)
            if (CppCore::Base64::bytelength("aaaaaaaa", 8, true) != 6) return false; // ok
            return true;
         }
         INLINE static bool symbollength()
         {
            // STD
            if (CppCore::Base64::symbollength(0, false) != 0) return false;
            if (CppCore::Base64::symbollength(1, false) != 4) return false;
            if (CppCore::Base64::symbollength(2, false) != 4) return false;
            if (CppCore::Base64::symbollength(3, false) != 4) return false;
            if (CppCore::Base64::symbollength(4, false) != 8) return false;
            if (CppCore::Base64::symbollength(5, false) != 8) return false;
            if (CppCore::Base64::symbollength(6, false) != 8) return false;
            // URL
            if (CppCore::Base64::symbollength(0, true) != 0) return false;
            if (CppCore::Base64::symbollength(1, true) != 2) return false;
            if (CppCore::Base64::symbollength(2, true) != 3) return false;
            if (CppCore::Base64::symbollength(3, true) != 4) return false;
            if (CppCore::Base64::symbollength(4, true) != 6) return false;
            if (CppCore::Base64::symbollength(5, true) != 7) return false;
            if (CppCore::Base64::symbollength(6, true) != 8) return false;
            return true;
         }
         INLINE static bool encode_std()
         {
            std::string s;
            CppCore::Base64::encode("1",                s); if (s != "MQ==")                      return false;
            CppCore::Base64::encode("12",               s); if (s != "MTI=")                      return false;
            CppCore::Base64::encode("123",              s); if (s != "MTIz")                      return false;
            CppCore::Base64::encode("1234",             s); if (s != "MTIzNA==")                  return false;
            CppCore::Base64::encode("12345",            s); if (s != "MTIzNDU=")                  return false;
            CppCore::Base64::encode("123456",           s); if (s != "MTIzNDU2")                  return false;
            CppCore::Base64::encode("1234567",          s); if (s != "MTIzNDU2Nw==")              return false;
            CppCore::Base64::encode("12345678",         s); if (s != "MTIzNDU2Nzg=")              return false;
            CppCore::Base64::encode("123456789",        s); if (s != "MTIzNDU2Nzg5")              return false;
            CppCore::Base64::encode("1234567890abcdef", s); if (s != "MTIzNDU2Nzg5MGFiY2RlZg==")  return false;
            CppCore::Base64::encode("",                 s); if (s != "")                          return false;
            uint8_t d1[] = { 0x01, 0x02, 0x03 }; CppCore::Base64::encode(d1, s); if (s != "AQID") return false;
            uint8_t d2[] = { 0xFF, 0xEE };       CppCore::Base64::encode(d2, s); if (s != "/+4=") return false;
            uint8_t d3[] = { 0xFF };             CppCore::Base64::encode(d3, s); if (s != "/w==") return false;
            uint8_t d4[] = {
               0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff,
               0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff,
               0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff,
               0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff
            };
            CppCore::Base64::encode(d4, s);
            if (s != "/+7//+7//+7//+7//+7////u///u///u///u///u////7v//7v//7v//7v//7v///+7//+7//+7//+7//+7//w==")
               return false;
            return true;
         }
         INLINE static bool encode_url()
         {
            std::string s;
            CppCore::Base64::encode("1",                s, true); if (s != "MQ")                      return false;
            CppCore::Base64::encode("12",               s, true); if (s != "MTI")                     return false;
            CppCore::Base64::encode("123",              s, true); if (s != "MTIz")                    return false;
            CppCore::Base64::encode("1234",             s, true); if (s != "MTIzNA")                  return false;
            CppCore::Base64::encode("12345",            s, true); if (s != "MTIzNDU")                 return false;
            CppCore::Base64::encode("123456",           s, true); if (s != "MTIzNDU2")                return false;
            CppCore::Base64::encode("1234567",          s, true); if (s != "MTIzNDU2Nw")              return false;
            CppCore::Base64::encode("12345678",         s, true); if (s != "MTIzNDU2Nzg")             return false;
            CppCore::Base64::encode("123456789",        s, true); if (s != "MTIzNDU2Nzg5")            return false;
            CppCore::Base64::encode("1234567890abcdef", s, true); if (s != "MTIzNDU2Nzg5MGFiY2RlZg")  return false;
            CppCore::Base64::encode("",                 s, true); if (s != "")                        return false;
            uint8_t d1[] = { 0x01, 0x02, 0x03 }; CppCore::Base64::encode(d1, s, true); if (s != "AQID") return false;
            uint8_t d2[] = { 0xFF, 0xEE };       CppCore::Base64::encode(d2, s, true); if (s != "_-4")  return false;
            uint8_t d3[] = { 0xFF };             CppCore::Base64::encode(d3, s, true); if (s != "_w")   return false;
            uint8_t d4[] = {
               0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff,
               0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff,
               0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff,
               0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff, 0xee, 0xff, 0xff
            };
            CppCore::Base64::encode(d4, s, true);
            if (s != "_-7__-7__-7__-7__-7____u___u___u___u___u____7v__7v__7v__7v__7v___-7__-7__-7__-7__-7__w")
               return false;
            return true;
         }
         INLINE static bool decode_std()
         {
            std::string s;
            if (!CppCore::Base64::decode("MQ==",     s) || s != "1")    return false;
            if (!CppCore::Base64::decode("MTI=",     s) || s != "12")   return false;
            if (!CppCore::Base64::decode("MTIz",     s) || s != "123")  return false;
            if (!CppCore::Base64::decode("MTIzNA==", s) || s != "1234") return false;
            if ( CppCore::Base64::decode("",     s)) return false; // empty string
            if ( CppCore::Base64::decode("Z",    s)) return false; // invalid length
            if ( CppCore::Base64::decode("AB",   s)) return false; // invalid length
            if ( CppCore::Base64::decode("M=",   s)) return false; // invalid length
            if ( CppCore::Base64::decode("M==",  s)) return false; // invalid length
            if ( CppCore::Base64::decode("(aaa", s)) return false; // invalid symbol
            if ( CppCore::Base64::decode("aa=a", s)) return false; // invalid symbol
            uint8_t d1[3];
            uint8_t d2[1];
            if (!CppCore::Base64::decode("AQID", d1) || d1[0] != 0x01 || d1[1] != 0x02 || d1[2] != 0x03) return false;
            if (!CppCore::Base64::decode("/w==", d1) || d1[0] != 0xFF || d1[1] != 0x00 || d1[2] != 0x00) return false;
            if (!CppCore::Base64::decode("/w==", d2) || d2[0] != 0xFF)                                   return false;
            if ( CppCore::Base64::decode("AQID", d2)) return false; // too large
            uint8_t d3_gen[48];
            uint8_t d3_exp[48] = {
               0x00, 0x10, 0x83, 0x10, 0x51, 0x87, 0x20, 0x92, 0x8b, 0x30, 0xd3, 0x8f,
               0x41, 0x14, 0x93, 0x51, 0x55, 0x97, 0x61, 0x96, 0x9b, 0x71, 0xd7, 0x9f,
               0x82, 0x18, 0xa3, 0x92, 0x59, 0xa7, 0xa2, 0x9a, 0xab, 0xb2, 0xdb, 0xaf,
               0xc3, 0x1c, 0xb3, 0xd3, 0x5d, 0xb7, 0xe3, 0x9e, 0xbb, 0xf3, 0xdf, 0xbf
            };
            if (!CppCore::Base64::decode("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", d3_gen))
               return false;
            if (::memcmp(d3_gen, d3_exp, 48) != 0)
               return false;
            if (CppCore::Base64::decode("#BCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", d3_gen))
               return false; // invalid symbol '#' at index 0
            if (CppCore::Base64::decode("ABCDEFGHIJKLMNOPQRSTUVWXY!abcdefghijklmnopqrstuvwxyz0123456789+/", d3_gen))
               return false; // invalid symbol '!' at index 25
            return true;
         }
         INLINE static bool decode_url()
         {
            std::string s;
            if (!CppCore::Base64::decode("MQ",     s, true) || s != "1")    return false;
            if (!CppCore::Base64::decode("MTI",    s, true) || s != "12")   return false;
            if (!CppCore::Base64::decode("MTIz",   s, true) || s != "123")  return false;
            if (!CppCore::Base64::decode("MTIzNA", s, true) || s != "1234") return false;
            if ( CppCore::Base64::decode("",       s, true)) return false; // empty string
            if ( CppCore::Base64::decode("Z",      s, true)) return false; // invalid length
            if ( CppCore::Base64::decode("M=",     s, true)) return false; // invalid symbol
            if ( CppCore::Base64::decode("M==",    s, true)) return false; // invalid symbol
            if ( CppCore::Base64::decode("(aaa",   s, true)) return false; // invalid symbol
            if ( CppCore::Base64::decode("aa=a",   s, true)) return false; // invalid symbol
            if ( CppCore::Base64::decode("MQ==",   s, true)) return false; // invalid symbol
            if ( CppCore::Base64::decode("MTI=",   s, true)) return false; // invalid symbol
            if ( CppCore::Base64::decode("MTIaa",  s, true)) return false; // invalid length
            uint8_t d1[3];
            uint8_t d2[1];
            if (!CppCore::Base64::decode("AQID", d1, true) || d1[0] != 0x01 || d1[1] != 0x02 || d1[2] != 0x03) return false;
            if (!CppCore::Base64::decode("_w",   d1, true) || d1[0] != 0xFF || d1[1] != 0x00 || d1[2] != 0x00) return false;
            if (!CppCore::Base64::decode("_w",   d2, true) || d2[0] != 0xFF)                                   return false;
            if ( CppCore::Base64::decode("AQID", d2, true)) return false; // too large
            uint8_t d3_gen[48];
            uint8_t d3_exp[48] = {
               0x00, 0x10, 0x83, 0x10, 0x51, 0x87, 0x20, 0x92, 0x8b, 0x30, 0xd3, 0x8f,
               0x41, 0x14, 0x93, 0x51, 0x55, 0x97, 0x61, 0x96, 0x9b, 0x71, 0xd7, 0x9f,
               0x82, 0x18, 0xa3, 0x92, 0x59, 0xa7, 0xa2, 0x9a, 0xab, 0xb2, 0xdb, 0xaf,
               0xc3, 0x1c, 0xb3, 0xd3, 0x5d, 0xb7, 0xe3, 0x9e, 0xbb, 0xf3, 0xdf, 0xbf
            };
            if (!CppCore::Base64::decode("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_", d3_gen, true))
               return false;
            if (::memcmp(d3_gen, d3_exp, 48) != 0)
               return false;
            if (CppCore::Base64::decode("#BCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_", d3_gen, true))
               return false; // invalid symbol '#' at index 0
            if (CppCore::Base64::decode("ABCDEFGHIJKLMNOPQRSTUVWXY!abcdefghijklmnopqrstuvwxyz0123456789-_", d3_gen, true))
               return false; // invalid symbol '!' at index 25
            return true;
         }
      };
      class Decimal
      {
      public:
         INLINE static bool tostring8u()
         {
            char s[CPPCORE_MAXLENGTH_B10_8U+1];
            CppCore::Decimal::tostring(uint8_t(0x00), s); if (std::string("0"  ) != s) return false;
            CppCore::Decimal::tostring(uint8_t(0x01), s); if (std::string("1"  ) != s) return false;
            CppCore::Decimal::tostring(uint8_t(0xFF), s); if (std::string("255") != s) return false;
            CppCore::Decimal::tostring(uint8_t(0x0F), s); if (std::string("15" ) != s) return false;
            CppCore::Decimal::tostring(uint8_t(0xBC), s); if (std::string("188") != s) return false;
            std::string ss;
            ss.clear(); CppCore::Decimal::tostring(uint8_t(0x00), ss); if (std::string("0"  ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint8_t(0x01), ss); if (std::string("1"  ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint8_t(0xFF), ss); if (std::string("255") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint8_t(0x0F), ss); if (std::string("15" ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint8_t(0xBC), ss); if (std::string("188") != ss) return false;
            return true;
         }
         INLINE static bool tostring8s()
         {
            char s[CPPCORE_MAXLENGTH_B10_8S+1];
            CppCore::Decimal::tostring(int8_t(0x00), s); if (std::string( "0"  ) != s) return false;
            CppCore::Decimal::tostring(int8_t(0x01), s); if (std::string( "1"  ) != s) return false;
            CppCore::Decimal::tostring(int8_t(0x7F), s); if (std::string( "127") != s) return false;
            CppCore::Decimal::tostring(int8_t(0x80), s); if (std::string("-128") != s) return false;
            CppCore::Decimal::tostring(int8_t(0xFF), s); if (std::string("-1"  ) != s) return false;
            CppCore::Decimal::tostring(int8_t(0x0F), s); if (std::string( "15" ) != s) return false;
            //CppCore::Decimal::tostring(int8_t(0xBC), s); if (std::string("-17350") != s) return false;
            std::string ss;
            ss.clear(); CppCore::Decimal::tostring(int8_t(0x00), ss); if (std::string( "0"  ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int8_t(0x01), ss); if (std::string( "1"  ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int8_t(0x7F), ss); if (std::string( "127") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int8_t(0x80), ss); if (std::string("-128") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int8_t(0xFF), ss); if (std::string("-1"  ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int8_t(0x0F), ss); if (std::string( "15" ) != ss) return false;
            //ss.clear(); CppCore::Decimal::tostring(int8_t(0xBC), ss); if (std::string("-17350") != ss) return false;
            return true;
         }
         INLINE static bool tostring16u()
         {
            char s[CPPCORE_MAXLENGTH_B10_16U+1];
            CppCore::Decimal::tostring(uint16_t(0x0000), s); if (std::string("0"    ) != s) return false;
            CppCore::Decimal::tostring(uint16_t(0x0001), s); if (std::string("1"    ) != s) return false;
            CppCore::Decimal::tostring(uint16_t(0xFFFF), s); if (std::string("65535") != s) return false;
            CppCore::Decimal::tostring(uint16_t(0x0FFF), s); if (std::string("4095" ) != s) return false;
            CppCore::Decimal::tostring(uint16_t(0xBC3A), s); if (std::string("48186") != s) return false;
            std::string ss;
            ss.clear(); CppCore::Decimal::tostring(uint16_t(0x0000), ss); if (std::string("0"    ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint16_t(0x0001), ss); if (std::string("1"    ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint16_t(0xFFFF), ss); if (std::string("65535") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint16_t(0x0FFF), ss); if (std::string("4095" ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint16_t(0xBC3A), ss); if (std::string("48186") != ss) return false;
            return true;
         }
         INLINE static bool tostring16s()
         {
            char s[CPPCORE_MAXLENGTH_B10_16S+1];
            CppCore::Decimal::tostring(int16_t(0x0000), s); if (std::string( "0"    ) != s) return false;
            CppCore::Decimal::tostring(int16_t(0x0001), s); if (std::string( "1"    ) != s) return false;
            CppCore::Decimal::tostring(int16_t(0x7FFF), s); if (std::string( "32767") != s) return false;
            CppCore::Decimal::tostring(int16_t(0x8000), s); if (std::string("-32768") != s) return false;
            CppCore::Decimal::tostring(int16_t(0xFFFF), s); if (std::string("-1"    ) != s) return false;
            CppCore::Decimal::tostring(int16_t(0x0FFF), s); if (std::string( "4095" ) != s) return false;
            CppCore::Decimal::tostring(int16_t(0xBC3A), s); if (std::string("-17350") != s) return false;
            std::string ss;
            ss.clear(); CppCore::Decimal::tostring(int16_t(0x0000), ss); if (std::string( "0"    ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int16_t(0x0001), ss); if (std::string( "1"    ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int16_t(0x7FFF), ss); if (std::string( "32767") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int16_t(0x8000), ss); if (std::string("-32768") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int16_t(0xFFFF), ss); if (std::string("-1"    ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int16_t(0x0FFF), ss); if (std::string( "4095" ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int16_t(0xBC3A), ss); if (std::string("-17350") != ss) return false;
            return true;
         }
         INLINE static bool tostring32u()
         {
            char s[CPPCORE_MAXLENGTH_B10_32U+1];
            CppCore::Decimal::tostring(0x00000000U, s); if (std::string("0"         ) != s) return false;
            CppCore::Decimal::tostring(0x00000001U, s); if (std::string("1"         ) != s) return false;
            CppCore::Decimal::tostring(0xFFFFFFFFU, s); if (std::string("4294967295") != s) return false;
            CppCore::Decimal::tostring(0x0FFFFFFFU, s); if (std::string("268435455" ) != s) return false;
            CppCore::Decimal::tostring(0xBC3A19FAU, s); if (std::string("3157924346") != s) return false;
            std::string ss;
            ss.clear(); CppCore::Decimal::tostring(0x00000000U, ss); if (std::string("0"         ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(0x00000001U, ss); if (std::string("1"         ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(0xFFFFFFFFU, ss); if (std::string("4294967295") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(0x0FFFFFFFU, ss); if (std::string("268435455" ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(0xBC3A19FAU, ss); if (std::string("3157924346") != ss) return false;
            return true;
         }
         INLINE static bool tostring32s()
         {
            char s[CPPCORE_MAXLENGTH_B10_32S+1];
            CppCore::Decimal::tostring(int32_t(0x00000000), s); if (std::string( "0"         ) != s) return false;
            CppCore::Decimal::tostring(int32_t(0x00000001), s); if (std::string( "1"         ) != s) return false;
            CppCore::Decimal::tostring(int32_t(0x7FFFFFFF), s); if (std::string( "2147483647") != s) return false;
            CppCore::Decimal::tostring(int32_t(0x80000000), s); if (std::string("-2147483648") != s) return false;
            CppCore::Decimal::tostring(int32_t(0xFFFFFFFF), s); if (std::string("-1"         ) != s) return false;
            CppCore::Decimal::tostring(int32_t(0x0FFFFFFF), s); if (std::string( "268435455" ) != s) return false;
            CppCore::Decimal::tostring(int32_t(0xBC3A19FA), s); if (std::string("-1137042950") != s) return false;
            std::string ss;
            ss.clear(); CppCore::Decimal::tostring(int32_t(0x00000000), ss); if (std::string( "0"         ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int32_t(0x00000001), ss); if (std::string( "1"         ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int32_t(0x7FFFFFFF), ss); if (std::string( "2147483647") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int32_t(0x80000000), ss); if (std::string("-2147483648") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int32_t(0xFFFFFFFF), ss); if (std::string("-1"         ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int32_t(0x0FFFFFFF), ss); if (std::string( "268435455" ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int32_t(0xBC3A19FA), ss); if (std::string("-1137042950") != ss) return false;
            return true;
         }
         INLINE static bool tostring64u()
         {
            char s[CPPCORE_MAXLENGTH_B10_64U+1];
            CppCore::Decimal::tostring(uint64_t(0x0000000000000000), s); if (std::string("0"                   ) != s) return false;
            CppCore::Decimal::tostring(uint64_t(0x0000000000000001), s); if (std::string("1"                   ) != s) return false;
            CppCore::Decimal::tostring(uint64_t(0xFFFFFFFFFFFFFFFF), s); if (std::string("18446744073709551615") != s) return false;
            CppCore::Decimal::tostring(uint64_t(0x0FFFFFFFFFFFFFFF), s); if (std::string("1152921504606846975" ) != s) return false;
            CppCore::Decimal::tostring(uint64_t(0xBC3A19FABC3A19FA), s); if (std::string("13563181792470112762") != s) return false;
            std::string ss;
            ss.clear(); CppCore::Decimal::tostring(uint64_t(0x0000000000000000), ss); if (std::string("0"                   ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint64_t(0x0000000000000001), ss); if (std::string("1"                   ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint64_t(0xFFFFFFFFFFFFFFFF), ss); if (std::string("18446744073709551615") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint64_t(0x0FFFFFFFFFFFFFFF), ss); if (std::string("1152921504606846975" ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(uint64_t(0xBC3A19FABC3A19FA), ss); if (std::string("13563181792470112762") != ss) return false;
            return true;
         }
         INLINE static bool tostring64s()
         {
            char s[CPPCORE_MAXLENGTH_B10_64S+1];
            CppCore::Decimal::tostring(int64_t(0x0000000000000000), s); if (std::string( "0"                  ) != s) return false;
            CppCore::Decimal::tostring(int64_t(0x0000000000000001), s); if (std::string( "1"                  ) != s) return false;
            CppCore::Decimal::tostring(int64_t(0x7FFFFFFFFFFFFFFF), s); if (std::string( "9223372036854775807") != s) return false;
            CppCore::Decimal::tostring(int64_t(0x8000000000000000), s); if (std::string("-9223372036854775808") != s) return false;
            CppCore::Decimal::tostring(int64_t(0xFFFFFFFFFFFFFFFF), s); if (std::string("-1"                  ) != s) return false;
            CppCore::Decimal::tostring(int64_t(0x0FFFFFFFFFFFFFFF), s); if (std::string( "1152921504606846975") != s) return false;
            CppCore::Decimal::tostring(int64_t(0xBC3A19FABC3A19FA), s); if (std::string("-4883562281239438854") != s) return false;
            std::string ss;
            ss.clear(); CppCore::Decimal::tostring(int64_t(0x0000000000000000), ss); if (std::string( "0"                  ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int64_t(0x0000000000000001), ss); if (std::string( "1"                  ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int64_t(0x7FFFFFFFFFFFFFFF), ss); if (std::string( "9223372036854775807") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int64_t(0x8000000000000000), ss); if (std::string("-9223372036854775808") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int64_t(0xFFFFFFFFFFFFFFFF), ss); if (std::string("-1"                  ) != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int64_t(0x0FFFFFFFFFFFFFFF), ss); if (std::string( "1152921504606846975") != ss) return false;
            ss.clear(); CppCore::Decimal::tostring(int64_t(0xBC3A19FABC3A19FA), ss); if (std::string("-4883562281239438854") != ss) return false;
            return true;
         }
         INLINE static bool parse8u()
         {
            uint8_t r;
            if (CppCore::Decimal::parse8u("00" ) != uint8_t(0x00)) return false;
            if (CppCore::Decimal::parse8u("01" ) != uint8_t(0x01)) return false;
            if (CppCore::Decimal::parse8u("99" ) != uint8_t(0x63)) return false;
            if (CppCore::Decimal::parse8u("16" ) != uint8_t(0x10)) return false;
            if (CppCore::Decimal::parse8u("0"  ) != uint8_t(0x00)) return false;
            if (CppCore::Decimal::parse8u("255") != uint8_t(0xFF)) return false;

            if (!CppCore::Decimal::tryparse("00" ,r) || r != uint8_t(0x00)) return false;
            if (!CppCore::Decimal::tryparse("01" ,r) || r != uint8_t(0x01)) return false;
            if (!CppCore::Decimal::tryparse("99" ,r) || r != uint8_t(0x63)) return false;
            if (!CppCore::Decimal::tryparse("16" ,r) || r != uint8_t(0x10)) return false;
            if (!CppCore::Decimal::tryparse("0"  ,r) || r != uint8_t(0x00)) return false;
            if (!CppCore::Decimal::tryparse("255",r) || r != uint8_t(0xFF)) return false;

            if (CppCore::Decimal::tryparse("256",  r)) return false; // add overflow
            if (CppCore::Decimal::tryparse("999",  r)) return false; // mul overflow ?
            if (CppCore::Decimal::tryparse("2X3",  r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("-1",   r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("+1",   r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("255X", r)) return false; // invalid symbol after valid max
            //if (CppCore::Decimal::tryparse("0001",      r)) return false; // too many leading zeros
            if (CppCore::Decimal::tryparse("",            r)) return false; // empty input
            if (CppCore::Decimal::tryparse((const char*)0,r)) return false; // null pointer

            return true;
         }
         INLINE static bool parse8s()
         {
            int8_t r;

            if (CppCore::Decimal::parse16s( "00" ) != int8_t(0x00)) return false;
            if (CppCore::Decimal::parse16s( "01" ) != int8_t(0x01)) return false;
            if (CppCore::Decimal::parse16s("-01" ) != int8_t(0xFF)) return false;
            if (CppCore::Decimal::parse16s( "99" ) != int8_t(0x63)) return false;
            if (CppCore::Decimal::parse16s("-99" ) != int8_t(0x9D)) return false;
            if (CppCore::Decimal::parse16s("+16" ) != int8_t(0x10)) return false;
            if (CppCore::Decimal::parse16s("-16" ) != int8_t(0xF0)) return false;
            if (CppCore::Decimal::parse16s( "0"  ) != int8_t(0x00)) return false;
            if (CppCore::Decimal::parse16s( "127") != int8_t(0x7F)) return false;
            if (CppCore::Decimal::parse16s("-128") != int8_t(0x80)) return false;

            if (!CppCore::Decimal::tryparse( "00" ,r) || r != int8_t(0x00)) return false;
            if (!CppCore::Decimal::tryparse( "01" ,r) || r != int8_t(0x01)) return false;
            if (!CppCore::Decimal::tryparse("-01" ,r) || r != int8_t(0xFF)) return false;
            if (!CppCore::Decimal::tryparse( "99" ,r) || r != int8_t(0x63)) return false;
            if (!CppCore::Decimal::tryparse("-99" ,r) || r != int8_t(0x9D)) return false;
            if (!CppCore::Decimal::tryparse("+16" ,r) || r != int8_t(0x10)) return false;
            if (!CppCore::Decimal::tryparse("-16" ,r) || r != int8_t(0xF0)) return false;
            if (!CppCore::Decimal::tryparse( "0"  ,r) || r != int8_t(0x00)) return false;
            if (!CppCore::Decimal::tryparse("+0"  ,r) || r != int8_t(0x00)) return false;
            if (!CppCore::Decimal::tryparse("-0"  ,r) || r != int8_t(0x00)) return false;
            if (!CppCore::Decimal::tryparse( "127",r) || r != int8_t(0x7F)) return false;
            if (!CppCore::Decimal::tryparse("-128",r) || r != int8_t(0x80)) return false;

            if (CppCore::Decimal::tryparse( "128",         r)) return false; // add overflow
            if (CppCore::Decimal::tryparse("-129",         r)) return false; // sub underflow
            if (CppCore::Decimal::tryparse( "999",         r)) return false; // mul overflow?
            if (CppCore::Decimal::tryparse("-999",         r)) return false; // mul underflow?
            if (CppCore::Decimal::tryparse( "X23",         r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "1X3",         r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "12X",         r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "127X",        r)) return false; // invalid symbol after valid max
            if (CppCore::Decimal::tryparse("-128X",        r)) return false; // invalid symbol after valid min
            //if (CppCore::Decimal::tryparse( "000001",      r)) return false; // too many leading zeros
            //if (CppCore::Decimal::tryparse("-000001",      r)) return false; // too many leading zeros
            if (CppCore::Decimal::tryparse( "-",           r)) return false; // single minus
            if (CppCore::Decimal::tryparse( "+",           r)) return false; // single plus
            if (CppCore::Decimal::tryparse( "-x",          r)) return false; // minus with invalid symbol
            if (CppCore::Decimal::tryparse( "+x",          r)) return false; // plus with invalid symbol
            if (CppCore::Decimal::tryparse( "",            r)) return false; // empty input
            if (CppCore::Decimal::tryparse((const char*)0, r)) return false; // null pointer

            return true;
         }
         INLINE static bool parse16u()
         {
            uint16_t r;
            if (CppCore::Decimal::parse16u("0000" ) != uint16_t(0x0000)) return false;
            if (CppCore::Decimal::parse16u("0001" ) != uint16_t(0x0001)) return false;
            if (CppCore::Decimal::parse16u("9999" ) != uint16_t(0x270F)) return false;
            if (CppCore::Decimal::parse16u("16"   ) != uint16_t(0x0010)) return false;
            if (CppCore::Decimal::parse16u("0"    ) != uint16_t(0x0000)) return false;
            if (CppCore::Decimal::parse16u("65535") != uint16_t(0xFFFF)) return false;

            if (!CppCore::Decimal::tryparse("0000" ,r) || r != uint16_t(0x0000)) return false;
            if (!CppCore::Decimal::tryparse("0001" ,r) || r != uint16_t(0x0001)) return false;
            if (!CppCore::Decimal::tryparse("9999" ,r) || r != uint16_t(0x270F)) return false;
            if (!CppCore::Decimal::tryparse("16"   ,r) || r != uint16_t(0x0010)) return false;
            if (!CppCore::Decimal::tryparse("0"    ,r) || r != uint16_t(0x0000)) return false;
            if (!CppCore::Decimal::tryparse("65535",r) || r != uint16_t(0xFFFF)) return false;

            if (CppCore::Decimal::tryparse("65536",       r)) return false; // add overflow
            if (CppCore::Decimal::tryparse("99999",       r)) return false; // mul overflow ?
            if (CppCore::Decimal::tryparse("12X34",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("-1",          r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("+1",          r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("65535X",      r)) return false; // invalid symbol after valid max
            //if (CppCore::Decimal::tryparse("000001",      r)) return false; // too many leading zeros
            if (CppCore::Decimal::tryparse("",            r)) return false; // empty input
            if (CppCore::Decimal::tryparse((const char*)0,r)) return false; // null pointer

            return true;
         }
         INLINE static bool parse16s()
         {
            int16_t r;

            if (CppCore::Decimal::parse16s( "0000" ) != int16_t(0x0000)) return false;
            if (CppCore::Decimal::parse16s( "0001" ) != int16_t(0x0001)) return false;
            if (CppCore::Decimal::parse16s("-0001" ) != int16_t(0xFFFF)) return false;
            if (CppCore::Decimal::parse16s( "9999" ) != int16_t(0x270F)) return false;
            if (CppCore::Decimal::parse16s("-9999" ) != int16_t(0xD8F1)) return false;
            if (CppCore::Decimal::parse16s("+16"   ) != int16_t(0x0010)) return false;
            if (CppCore::Decimal::parse16s("-16"   ) != int16_t(0xFFF0)) return false;
            if (CppCore::Decimal::parse16s( "0"    ) != int16_t(0x0000)) return false;
            if (CppCore::Decimal::parse16s( "32767") != int16_t(0x7FFF)) return false;
            if (CppCore::Decimal::parse16s("-32768") != int16_t(0x8000)) return false;

            if (!CppCore::Decimal::tryparse( "0000" ,r) || r != int16_t(0x0000)) return false;
            if (!CppCore::Decimal::tryparse( "0001" ,r) || r != int16_t(0x0001)) return false;
            if (!CppCore::Decimal::tryparse("-0001" ,r) || r != int16_t(0xFFFF)) return false;
            if (!CppCore::Decimal::tryparse( "9999" ,r) || r != int16_t(0x270F)) return false;
            if (!CppCore::Decimal::tryparse("-9999" ,r) || r != int16_t(0xD8F1)) return false;
            if (!CppCore::Decimal::tryparse("+16"   ,r) || r != int16_t(0x0010)) return false;
            if (!CppCore::Decimal::tryparse("-16"   ,r) || r != int16_t(0xFFF0)) return false;
            if (!CppCore::Decimal::tryparse( "0"    ,r) || r != int16_t(0x0000)) return false;
            if (!CppCore::Decimal::tryparse("+0"    ,r) || r != int16_t(0x0000)) return false;
            if (!CppCore::Decimal::tryparse("-0"    ,r) || r != int16_t(0x0000)) return false;
            if (!CppCore::Decimal::tryparse( "32767",r) || r != int16_t(0x7FFF)) return false;
            if (!CppCore::Decimal::tryparse("-32768",r) || r != int16_t(0x8000)) return false;

            if (CppCore::Decimal::tryparse( "32768",       r)) return false; // add overflow
            if (CppCore::Decimal::tryparse("-32769",       r)) return false; // sub underflow
            if (CppCore::Decimal::tryparse( "99999",       r)) return false; // mul overflow?
            if (CppCore::Decimal::tryparse("-99999",       r)) return false; // mul underflow?
            if (CppCore::Decimal::tryparse( "X2345",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "1X345",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "12X45",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "123X5",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "1234X",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "32767X",      r)) return false; // invalid symbol after valid max
            if (CppCore::Decimal::tryparse("-32768X",      r)) return false; // invalid symbol after valid min
            //if (CppCore::Decimal::tryparse( "000001",      r)) return false; // too many leading zeros
            //if (CppCore::Decimal::tryparse("-000001",      r)) return false; // too many leading zeros
            if (CppCore::Decimal::tryparse( "-",           r)) return false; // single minus
            if (CppCore::Decimal::tryparse( "+",           r)) return false; // single plus
            if (CppCore::Decimal::tryparse( "-x",          r)) return false; // minus with invalid symbol
            if (CppCore::Decimal::tryparse( "+x",          r)) return false; // plus with invalid symbol
            if (CppCore::Decimal::tryparse( "",            r)) return false; // empty input
            if (CppCore::Decimal::tryparse((const char*)0, r)) return false; // null pointer

            return true;
         }
         INLINE static bool parse32u()
         {
            uint32_t r;
            if (CppCore::Decimal::parse32u("00000000"  ) != 0x00000000U) return false;
            if (CppCore::Decimal::parse32u("00000001"  ) != 0x00000001U) return false;
            if (CppCore::Decimal::parse32u("99999999"  ) != 0x05F5E0FFU) return false;
            if (CppCore::Decimal::parse32u("16"        ) != 0x00000010U) return false;
            if (CppCore::Decimal::parse32u("0"         ) != 0x00000000U) return false;
            if (CppCore::Decimal::parse32u("4294967295") != 0xFFFFFFFFU) return false;

            if (!CppCore::Decimal::tryparse("00000000"  ,r) || r != 0x00000000U) return false;
            if (!CppCore::Decimal::tryparse("00000001"  ,r) || r != 0x00000001U) return false;
            if (!CppCore::Decimal::tryparse("99999999"  ,r) || r != 0x05F5E0FFU) return false;
            if (!CppCore::Decimal::tryparse("16"        ,r) || r != 0x00000010U) return false;
            if (!CppCore::Decimal::tryparse("0"         ,r) || r != 0x00000000U) return false;
            if (!CppCore::Decimal::tryparse("4294967295",r) || r != 0xFFFFFFFFU) return false;

            if (CppCore::Decimal::tryparse("4294967296",  r)) return false; // add overflow
            if (CppCore::Decimal::tryparse("5555555555",  r)) return false; // mul overflow
            if (CppCore::Decimal::tryparse("12X345",      r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("-1",          r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("+1",          r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("4294967295X", r)) return false; // invalid symbol after valid max
            //if (CppCore::Decimal::tryparse("00000000001", r)) return false; // too many leading zeros
            if (CppCore::Decimal::tryparse("",            r)) return false; // empty input
            if (CppCore::Decimal::tryparse((const char*)0,r)) return false; // null pointer

            return true;
         }
         INLINE static bool parse32s()
         {
            int32_t r;

            if (CppCore::Decimal::parse32s( "00000000"  ) != int32_t(0x00000000)) return false;
            if (CppCore::Decimal::parse32s( "00000001"  ) != int32_t(0x00000001)) return false;
            if (CppCore::Decimal::parse32s("-00000001"  ) != int32_t(0xFFFFFFFF)) return false;
            if (CppCore::Decimal::parse32s( "99999999"  ) != int32_t(0x05F5E0FF)) return false;
            if (CppCore::Decimal::parse32s("-99999999"  ) != int32_t(0xFA0A1F01)) return false;
            if (CppCore::Decimal::parse32s("+16"        ) != int32_t(0x00000010)) return false;
            if (CppCore::Decimal::parse32s("-16"        ) != int32_t(0xFFFFFFF0)) return false;
            if (CppCore::Decimal::parse32s( "0"         ) != int32_t(0x00000000)) return false;
            if (CppCore::Decimal::parse32s( "2147483647") != int32_t(0x7FFFFFFF)) return false;
            if (CppCore::Decimal::parse32s("-2147483648") != int32_t(0x80000000)) return false;

            if (!CppCore::Decimal::tryparse( "00000000"  ,r) || r != int32_t(0x00000000)) return false;
            if (!CppCore::Decimal::tryparse( "00000001"  ,r) || r != int32_t(0x00000001)) return false;
            if (!CppCore::Decimal::tryparse("-00000001"  ,r) || r != int32_t(0xFFFFFFFF)) return false;
            if (!CppCore::Decimal::tryparse( "99999999"  ,r) || r != int32_t(0x05F5E0FF)) return false;
            if (!CppCore::Decimal::tryparse("-99999999"  ,r) || r != int32_t(0xFA0A1F01)) return false;
            if (!CppCore::Decimal::tryparse("+16"        ,r) || r != int32_t(0x00000010)) return false;
            if (!CppCore::Decimal::tryparse("-16"        ,r) || r != int32_t(0xFFFFFFF0)) return false;
            if (!CppCore::Decimal::tryparse( "0"         ,r) || r != int32_t(0x00000000)) return false;
            if (!CppCore::Decimal::tryparse("+0"         ,r) || r != int32_t(0x00000000)) return false;
            if (!CppCore::Decimal::tryparse("-0"         ,r) || r != int32_t(0x00000000)) return false;
            if (!CppCore::Decimal::tryparse( "2147483647",r) || r != int32_t(0x7FFFFFFF)) return false;
            if (!CppCore::Decimal::tryparse("-2147483648",r) || r != int32_t(0x80000000)) return false;

            if (CppCore::Decimal::tryparse( "2147483648",  r)) return false; // add overflow
            if (CppCore::Decimal::tryparse("-2147483649",  r)) return false; // sub underflow
            if (CppCore::Decimal::tryparse( "5555555555",  r)) return false; // mul overflow?
            if (CppCore::Decimal::tryparse("-5555555555",  r)) return false; // mul underflow?
            if (CppCore::Decimal::tryparse( "X2345",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "1X345",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "12X45",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "123X5",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "1234X",       r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "2147483647X", r)) return false; // invalid symbol after valid max
            if (CppCore::Decimal::tryparse("-2147483648X", r)) return false; // invalid symbol after valid min
            //if (CppCore::Decimal::tryparse( "00000000001", r)) return false; // too many leading zeros
            //if (CppCore::Decimal::tryparse("-00000000001", r)) return false; // too many leading zeros
            if (CppCore::Decimal::tryparse( "-",           r)) return false; // single minus
            if (CppCore::Decimal::tryparse( "+",           r)) return false; // single plus
            if (CppCore::Decimal::tryparse( "-x",          r)) return false; // minus with invalid symbol
            if (CppCore::Decimal::tryparse( "+x",          r)) return false; // plus with invalid symbol
            if (CppCore::Decimal::tryparse( "",            r)) return false; // empty input
            if (CppCore::Decimal::tryparse((const char*)0, r)) return false; // null pointer

            return true;
         }
         INLINE static bool parse64u()
         {
            uint64_t r;
            if (CppCore::Decimal::parse64u("0000000000000000")     != 0x0000000000000000ULL) return false;
            if (CppCore::Decimal::parse64u("0000000000000001")     != 0x0000000000000001ULL) return false;
            if (CppCore::Decimal::parse64u("9999999999999999")     != 0x002386F26FC0FFFFULL) return false;
            if (CppCore::Decimal::parse64u("16")                   != 0x0000000000000010ULL) return false;
            if (CppCore::Decimal::parse64u("0")                    != 0x0000000000000000ULL) return false;
            if (CppCore::Decimal::parse64u("18446744073709551615") != 0xFFFFFFFFFFFFFFFFULL) return false;

            if (!CppCore::Decimal::tryparse("0000000000000000"    ,r) || r != 0x0000000000000000ULL) return false;
            if (!CppCore::Decimal::tryparse("0000000000000001"    ,r) || r != 0x0000000000000001ULL) return false;
            if (!CppCore::Decimal::tryparse("9999999999999999"    ,r) || r != 0x002386F26FC0FFFFULL) return false;
            if (!CppCore::Decimal::tryparse("16"                  ,r) || r != 0x0000000000000010ULL) return false;
            if (!CppCore::Decimal::tryparse("0"                   ,r) || r != 0x0000000000000000ULL) return false;
            if (!CppCore::Decimal::tryparse("18446744073709551615",r) || r != 0xFFFFFFFFFFFFFFFFULL) return false;

            if (CppCore::Decimal::tryparse("18446744073709551616", r)) return false; // add overflow
            if (CppCore::Decimal::tryparse("55555555555555555555", r)) return false; // mul overflow
            if (CppCore::Decimal::tryparse("12X345",               r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("-1",                   r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("+1",                   r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse("18446744073709551615X",r)) return false; // invalid symbol after valid max
            //if (CppCore::Decimal::tryparse("000000000000000000001",r)) return false; // too many leading zeros
            if (CppCore::Decimal::tryparse("",                     r)) return false; // empty input
            if (CppCore::Decimal::tryparse((const char*)0,         r)) return false; // null pointer

            return true;
         }
         INLINE static bool parse64s()
         {
            int64_t r;

            if (CppCore::Decimal::parse64s( "0000000000000000"   ) != int64_t(0x0000000000000000)) return false;
            if (CppCore::Decimal::parse64s( "0000000000000001"   ) != int64_t(0x0000000000000001)) return false;
            if (CppCore::Decimal::parse64s("-0000000000000001"   ) != int64_t(0xFFFFFFFFFFFFFFFF)) return false;
            if (CppCore::Decimal::parse64s( "9999999999999999"   ) != int64_t(0x002386F26FC0FFFF)) return false;
            if (CppCore::Decimal::parse64s("-9999999999999999"   ) != int64_t(0xFFDC790D903F0001)) return false;
            if (CppCore::Decimal::parse64s("+16"                 ) != int64_t(0x0000000000000010)) return false;
            if (CppCore::Decimal::parse64s("-16"                 ) != int64_t(0xFFFFFFFFFFFFFFF0)) return false;
            if (CppCore::Decimal::parse64s( "0"                  ) != int64_t(0x0000000000000000)) return false;
            if (CppCore::Decimal::parse64s( "9223372036854775807") != int64_t(0x7FFFFFFFFFFFFFFF)) return false;
            if (CppCore::Decimal::parse64s("-9223372036854775808") != int64_t(0x8000000000000000)) return false;

            if (!CppCore::Decimal::tryparse( "0000000000000000"   ,r) || r != int64_t(0x0000000000000000)) return false;
            if (!CppCore::Decimal::tryparse( "0000000000000001"   ,r) || r != int64_t(0x0000000000000001)) return false;
            if (!CppCore::Decimal::tryparse("-0000000000000001"   ,r) || r != int64_t(0xFFFFFFFFFFFFFFFF)) return false;
            if (!CppCore::Decimal::tryparse( "9999999999999999"   ,r) || r != int64_t(0x002386F26FC0FFFF)) return false;
            if (!CppCore::Decimal::tryparse("-9999999999999999"   ,r) || r != int64_t(0xFFDC790D903F0001)) return false;
            if (!CppCore::Decimal::tryparse("+16"                 ,r) || r != int64_t(0x0000000000000010)) return false;
            if (!CppCore::Decimal::tryparse("-16"                 ,r) || r != int64_t(0xFFFFFFFFFFFFFFF0)) return false;
            if (!CppCore::Decimal::tryparse( "0"                  ,r) || r != int64_t(0x0000000000000000)) return false;
            if (!CppCore::Decimal::tryparse("+0"                  ,r) || r != int64_t(0x0000000000000000)) return false;
            if (!CppCore::Decimal::tryparse("-0"                  ,r) || r != int64_t(0x0000000000000000)) return false;
            if (!CppCore::Decimal::tryparse( "9223372036854775807",r) || r != int64_t(0x7FFFFFFFFFFFFFFF)) return false;
            if (!CppCore::Decimal::tryparse("-9223372036854775808",r) || r != int64_t(0x8000000000000000)) return false;

            if (CppCore::Decimal::tryparse( "9223372036854775808", r)) return false; // add overflow
            if (CppCore::Decimal::tryparse("-9223372036854775809", r)) return false; // sub underflow
            if (CppCore::Decimal::tryparse( "9999999999999999999", r)) return false; // mul overflow?
            if (CppCore::Decimal::tryparse("-9999999999999999999", r)) return false; // mul underflow?
            if (CppCore::Decimal::tryparse( "X2345",               r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "1X345",               r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "12X45",               r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "123X5",               r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "1234X",               r)) return false; // invalid symbol
            if (CppCore::Decimal::tryparse( "9223372036854775807X",r)) return false; // invalid symbol after valid max
            if (CppCore::Decimal::tryparse("-9223372036854775808X",r)) return false; // invalid symbol after valid min
            //if (CppCore::Decimal::tryparse( "00000000000000000001",r)) return false; // too many leading zeros
            //if (CppCore::Decimal::tryparse("-00000000000000000001",r)) return false; // too many leading zeros
            if (CppCore::Decimal::tryparse( "-",                   r)) return false; // single minus
            if (CppCore::Decimal::tryparse( "+",                   r)) return false; // single plus
            if (CppCore::Decimal::tryparse( "-x",                  r)) return false; // minus with invalid symbol
            if (CppCore::Decimal::tryparse( "+x",                  r)) return false; // plus with invalid symbol
            if (CppCore::Decimal::tryparse( "",                    r)) return false; // empty input
            if (CppCore::Decimal::tryparse((const char*)0,         r)) return false; // null pointer

            return true;
         }
      };
   };
}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS
{
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(Encoding)
   {
   public:
      TEST_METHOD(ISDIGIT)          { Assert::AreEqual(true, CppCore::Test::Encoding::isdigit()); }
      TEST_METHOD(ISXDIGIT)         { Assert::AreEqual(true, CppCore::Test::Encoding::isxdigit()); }
      TEST_METHOD(BASEX_ESTIMATEBITS)    { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::estimatebits()); }
      TEST_METHOD(BASEX_ESTIMATESYMBOLS) { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::estimatesymbols()); }
      TEST_METHOD(BASEX_TOSTRING8)  { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::tostring8()); }
      TEST_METHOD(BASEX_TOSTRING16) { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::tostring16()); }
      TEST_METHOD(BASEX_TOSTRING32) { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::tostring32()); }
      TEST_METHOD(BASEX_TOSTRING64) { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::tostring64()); }
      TEST_METHOD(BASEX_PARSE8)     { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::parse8()); }
      TEST_METHOD(BASEX_PARSE16)    { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::parse16()); }
      TEST_METHOD(BASEX_PARSE32)    { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::parse32()); }
      TEST_METHOD(BASEX_PARSE64)    { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::parse64()); }
      TEST_METHOD(BASEX_PARSE128)   { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::parse128()); }
      TEST_METHOD(BASEX_TRYPARSE8)  { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::tryparse8()); }
      TEST_METHOD(BASEX_TRYPARSE16) { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::tryparse16()); }
      TEST_METHOD(BASEX_TRYPARSE32) { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::tryparse32()); }
      TEST_METHOD(BASEX_TRYPARSE64) { Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::tryparse64()); }
      TEST_METHOD(BASEX_TRYPARSE128){ Assert::AreEqual(true, CppCore::Test::Encoding::BaseX::tryparse128()); }
      TEST_METHOD(HEX_ENCODE)       { Assert::AreEqual(true, CppCore::Test::Encoding::Hex::encode()); }
      TEST_METHOD(HEX_DECODE)       { Assert::AreEqual(true, CppCore::Test::Encoding::Hex::decode()); }
      TEST_METHOD(HEX_TOSTRING16)   { Assert::AreEqual(true, CppCore::Test::Encoding::Hex::tostring16()); }
      TEST_METHOD(HEX_TOSTRING32)   { Assert::AreEqual(true, CppCore::Test::Encoding::Hex::tostring32()); }
      TEST_METHOD(HEX_TOSTRING64)   { Assert::AreEqual(true, CppCore::Test::Encoding::Hex::tostring64()); }
      TEST_METHOD(HEX_PARSE16)      { Assert::AreEqual(true, CppCore::Test::Encoding::Hex::parse16()); }
      TEST_METHOD(HEX_PARSE32)      { Assert::AreEqual(true, CppCore::Test::Encoding::Hex::parse32()); }
      TEST_METHOD(HEX_PARSE64)      { Assert::AreEqual(true, CppCore::Test::Encoding::Hex::parse64()); }
      TEST_METHOD(BASE64_BYTELENGTH)   { Assert::AreEqual(true, CppCore::Test::Encoding::Base64::bytelength()); }
      TEST_METHOD(BASE64_SYMBOLLENGTH) { Assert::AreEqual(true, CppCore::Test::Encoding::Base64::symbollength()); }
      TEST_METHOD(BASE64_ENCODE_STD)   { Assert::AreEqual(true, CppCore::Test::Encoding::Base64::encode_std()); }
      TEST_METHOD(BASE64_ENCODE_URL)   { Assert::AreEqual(true, CppCore::Test::Encoding::Base64::encode_url()); }
      TEST_METHOD(BASE64_DECODE_STD)   { Assert::AreEqual(true, CppCore::Test::Encoding::Base64::decode_std()); }
      TEST_METHOD(BASE64_DECODE_URL)   { Assert::AreEqual(true, CppCore::Test::Encoding::Base64::decode_url()); }
      TEST_METHOD(DEC_TOSTRING8U)   { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::tostring8u()); }
      TEST_METHOD(DEC_TOSTRING8S)   { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::tostring8s()); }
      TEST_METHOD(DEC_TOSTRING16U)  { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::tostring16u()); }
      TEST_METHOD(DEC_TOSTRING16S)  { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::tostring16s()); }
      TEST_METHOD(DEC_TOSTRING32U)  { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::tostring32u()); }
      TEST_METHOD(DEC_TOSTRING32S)  { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::tostring32s()); }
      TEST_METHOD(DEC_TOSTRING64U)  { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::tostring64u()); }
      TEST_METHOD(DEC_TOSTRING64S)  { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::tostring64s()); }
      TEST_METHOD(DEC_PARSE8U)      { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::parse8u()); }
      TEST_METHOD(DEC_PARSE8S)      { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::parse8s()); }
      TEST_METHOD(DEC_PARSE16U)     { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::parse16u()); }
      TEST_METHOD(DEC_PARSE16S)     { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::parse16s()); }
      TEST_METHOD(DEC_PARSE32U)     { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::parse32u()); }
      TEST_METHOD(DEC_PARSE32S)     { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::parse32s()); }
      TEST_METHOD(DEC_PARSE64U)     { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::parse64u()); }
      TEST_METHOD(DEC_PARSE64S)     { Assert::AreEqual(true, CppCore::Test::Encoding::Decimal::parse64s()); }
   };
}}}
#endif
