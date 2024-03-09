#pragma once

#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>
#include <CppCore/Memory.h>

// Alphabets

#define CPPCORE_ALPHABET_B02            "01"
#define CPPCORE_ALPHABET_B03            "012"
#define CPPCORE_ALPHABET_B04            "0123"
#define CPPCORE_ALPHABET_B05            "01234"
#define CPPCORE_ALPHABET_B06            "012345"
#define CPPCORE_ALPHABET_B07            "0123456"
#define CPPCORE_ALPHABET_B08            "01234567"
#define CPPCORE_ALPHABET_B09            "012345678"
#define CPPCORE_ALPHABET_B10            "0123456789"
#define CPPCORE_ALPHABET_B16_UPPERCASE  "0123456789ABCDEF"
#define CPPCORE_ALPHABET_B16_LOWERCASE  "0123456789abcdef"
#define CPPCORE_ALPHABET_B62_UPPERFIRST "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define CPPCORE_ALPHABET_B62_LOWERFIRST "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define CPPCORE_ALPHABET_B64_STD        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define CPPCORE_ALPHABET_B64_URL        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"

// Defaults

#if !defined(CPPCORE_ALPHABET_B16)
#define CPPCORE_ALPHABET_B16 CPPCORE_ALPHABET_B16_UPPERCASE
#endif

#if !defined(CPPCORE_ALPHABET_B62)
#define CPPCORE_ALPHABET_B62 CPPCORE_ALPHABET_B62_UPPERFIRST
#endif

#if !defined(CPPCORE_ALPHABET_B64)
#define CPPCORE_ALPHABET_B64 CPPCORE_ALPHABET_B64_STD
#endif

// Maximal Symbols For Integers

#define CPPCORE_MAXSYMBOLS_B10_8U   3U //  3 decimal symbols for uint8_t  (255)
#define CPPCORE_MAXSYMBOLS_B10_8S   3U //  3 decimal symbols for int8_t   (127)
#define CPPCORE_MAXSYMBOLS_B10_16U  5U //  5 decimal symbols for uint16_t (65535)
#define CPPCORE_MAXSYMBOLS_B10_16S  5U //  5 decimal symbols for int16_t  (32767)
#define CPPCORE_MAXSYMBOLS_B10_32U 10U // 10 decimal symbols for uint32_t (4294967295)
#define CPPCORE_MAXSYMBOLS_B10_32S 10U // 10 decimal symbols for int32_t  (2147483647)
#define CPPCORE_MAXSYMBOLS_B10_64U 20U // 20 decimal symbols for uint64_t (18446744073709551615)
#define CPPCORE_MAXSYMBOLS_B10_64S 19U // 19 decimal symbols for int64_t  (9223372036854775807)

#define CPPCORE_MAXSYMBOLS_B16_8    2U //  2 hex symbols for uint8_t/int8_t   (FF)
#define CPPCORE_MAXSYMBOLS_B16_16   4U //  4 hex symbols for uint16_t/int16_t (FFFF)
#define CPPCORE_MAXSYMBOLS_B16_32   8U //  8 hex symbols for uint32_t/int32_t (FFFFFFFF)
#define CPPCORE_MAXSYMBOLS_B16_64  16U // 16 hex symbols for uint64_t/int64_t (FFFFFFFFFFFFFFFF)

// Maximal Length

#define CPPCORE_MAXLENGTH_B10_8U  (CPPCORE_MAXSYMBOLS_B10_8U)     //  3
#define CPPCORE_MAXLENGTH_B10_8S  (CPPCORE_MAXSYMBOLS_B10_8S+1U)  //  3 + 1 for sign
#define CPPCORE_MAXLENGTH_B10_16U (CPPCORE_MAXSYMBOLS_B10_16U)    //  5
#define CPPCORE_MAXLENGTH_B10_16S (CPPCORE_MAXSYMBOLS_B10_16S+1U) //  5 + 1 for sign
#define CPPCORE_MAXLENGTH_B10_32U (CPPCORE_MAXSYMBOLS_B10_32U)    // 10 
#define CPPCORE_MAXLENGTH_B10_32S (CPPCORE_MAXSYMBOLS_B10_32S+1U) // 10 + 1 for sign
#define CPPCORE_MAXLENGTH_B10_64U (CPPCORE_MAXSYMBOLS_B10_64U)    // 20
#define CPPCORE_MAXLENGTH_B10_64S (CPPCORE_MAXSYMBOLS_B10_64S+1U) // 19 + 1 for sign 

#define CPPCORE_MAXLENGTH_B16_8  CPPCORE_MAXSYMBOLS_B16_8
#define CPPCORE_MAXLENGTH_B16_16 CPPCORE_MAXSYMBOLS_B16_16
#define CPPCORE_MAXLENGTH_B16_32 CPPCORE_MAXSYMBOLS_B16_32
#define CPPCORE_MAXLENGTH_B16_64 CPPCORE_MAXSYMBOLS_B16_64

namespace CppCore
{
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BASICS
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// True if c is a decimal digit (0-9)
   /// </summary>
   template<typename T = char>
   INLINE static bool isdigit(const T c)
   {
      // TODO: This could be also done with table lookup
      return CppCore::isinrange<T, true>(c, (T)'0', (T)'9');
   }

   /// <summary>
   /// Lookup Table for HEX. 
   /// Contains 0x01 for every hex char else 0x00.
   /// </summary>
   CPPCORE_ALIGN64 static constexpr uint8_t LOOKUP_XDIGIT[] =
   {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //  !"#$%&'
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ()*+,-./
      0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, // 01234567
      0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89:;<=>?
      0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, // @ABCDEFG
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // HIJKLMNO
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // PQRSTUVW
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // XYZ[\]^_
      0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, // `abcdefg
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // hijklmno
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // pqrstuvw
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // xyz{|}~.
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // ........
   };

   /// <summary>
   /// True if c is a hexadecimal digit (0-9, a-f, A-F)
   /// </summary>
   INLINE constexpr static bool isxdigit(const char c)
   {
      return LOOKUP_XDIGIT[(uint8_t)c];
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BASEX
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Any Base Encoding
   /// </summary>
   class BaseX
   {
   private:
      INLINE BaseX() { }
   public:
      /// <summary>
      /// Returns an upper bound of bits required for symbols.
      /// </summary>
      INLINE static uint32_t estimateBits(uint32_t symbols, uint32_t base)
      {
         assert(base >= 2);
         uint32_t pow2b = CppCore::ngptwo32(base);
         uint32_t nbits = CppCore::tzcnt32(pow2b);
         return symbols * nbits;
      }

      /// <summary>
      /// Returns an upper bound of symbols required for bits.
      /// </summary>
      INLINE static uint32_t estimateSymbols(uint32_t bits, uint32_t base)
      {
         assert(base >= 2);
         uint32_t q, r;
         uint32_t pow2b = CppCore::nlptwo32(base);
         uint32_t nbits = CppCore::tzcnt32(pow2b);
         CppCore::udivmod32(bits, nbits, q, r);
         return r ? q + 1 : q;
      }

      /// <summary>
      /// Encodes unsigned integer v into string s using alphabet.
      /// </summary>
      template<typename UINT>
      INLINE static intptr_t tostring(const UINT& val, char* s, intptr_t len, const uint32_t base, const char* alphabet, bool writeterm)
      {
         assert(base >= 2U);
         assert(::strlen(alphabet) == base);
         CPPCORE_ALIGN64 UINT v;
         uint32_t r;
         uint32_t n = 0U;
         bool     z;
         CppCore::clone(v, val);
         do
         {
            z = CppCore::udivmod_testzero(v, base, v, r);
            if (len > 0) *s++ = alphabet[r];
            n++; len--;
         } while (!z);
         if (len >= 0)
            Memory::reverse(s-n, n);
         if (writeterm)
            *s = (char)0x00;
         return len;
      }

      /// <summary>
      /// Encodes unsigned integer v into string s using alphabet.
      /// This appends to the existing string.
      /// </summary>
      template<typename UINT, typename STRING>
      INLINE static void tostring(const UINT& val, STRING& s, const uint32_t base, const char* alphabet)
      {
         assert(base >= 2U);
         assert(::strlen(alphabet) == base);
         CPPCORE_ALIGN64 UINT v;
         uint32_t r;
         uint32_t n = 0U;
         bool     z;
         CppCore::clone(v, val);
         do
         {
            z = CppCore::udivmod_testzero(v, base, v, r);
            s += alphabet[r];
            n++;
         } while (!z);
         Memory::reverse(s.data()+s.length()-n, n);
      }

      /// <summary>
      /// Returns std::string with unsigned integer v encoded using alphabet.
      /// </summary>
      template<typename UINT>
      INLINE static std::string tostring(const UINT& val, const char* alphabet = CPPCORE_ALPHABET_B10)
      {
         std::string s;
         BaseX::tostring(val, s, ::strlen(alphabet), alphabet);
         return s;
      }

      /// <summary>
      /// Template function for parsing unsigned integer from zero terminated string using alphabet.
      /// No overflow or invalid symbol check!
      /// </summary>
      template<typename UINT>
      INLINE static void parse(const char* input, UINT& r, const char* alphabet)
      {
         assert(::strlen(alphabet) >= 2);
         uint8_t tbl[256];
         uint8_t n = 0;
         CppCore::clear(r);
         CppCore::clear(tbl);
         while (const char c = *alphabet++)
            tbl[c] = n++;
         if (const char c = *input++)
         {
            *(uint8_t*)&r = tbl[c];
            while (const char c = *input++)
            {
               CppCore::umul(r, n, r);
               CppCore::uadd(r, tbl[c], r);
            }
         }
      }

      /// <summary>
      /// Template function for parsing unsigned integer from zero terminated string using alphabet.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// </summary>
      template<typename UINT>
      INLINE static bool tryparse(const char* input, UINT& r, const char* alphabet)
      {
         if (!input || !alphabet)
            return false; // null pointer
         uint8_t tbl[256];
         uint8_t n = 0;
         CppCore::bytedup(0xFF, tbl);
         while (const char c = *alphabet++)
            tbl[c] = n++;
         if (n < 2U) CPPCORE_UNLIKELY
            return false; // alphabet too short
         if (const char first = *input++) CPPCORE_LIKELY
         {
            CppCore::clear(r);
            uint8_t idx = tbl[first];
            if (idx == 0xFF) CPPCORE_UNLIKELY
               return false; // invalid first symbol
            *(uint8_t*)&r = idx;
            while (const char c = *input++)
            {
               CppCore::Padded<UINT> t;
               idx = tbl[c];
               if (idx == 0xFFU) CPPCORE_UNLIKELY
                  return false; // invalid symbol
               CppCore::umul(r, n, t);
               if (!CppCore::testzero(t.t)) CPPCORE_UNLIKELY
                  return false; // mul overflow
               uint8_t carry = 0;
               CppCore::addcarry(t.v, idx, r, carry);
               if (carry != 0) CPPCORE_UNLIKELY
                  return false; // add overflow
            }
            return true;
         }
         else CPPCORE_UNLIKELY
            return false; // empty input
      }
   };

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // HEX
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Hexadecimal Encoding
   /// </summary>
   class Hex
   {
   private:
      INLINE Hex() { }
   public:
      /// <summary>
      /// Hexadecimal Helper Functions
      /// </summary>
      class Util
      {
      private:
         INLINE Util() { }
      public:
         /// <summary>
         /// Returns the value represented by the hexadecimal character c.
         /// For instance the characters 'a' and 'A' will both return 10, '0' returns 0.
         /// Returns 0xFF for any non-hexadecimal character and 0xFE for the null char.
         /// </summary>
         INLINE static uint8_t valueofhexchar(const uint8_t c)
         {
            static const uint8_t table[] =
            {
              0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, //  !"#$%&'
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ()*+,-./
              0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // 01234567
              0x08, 0x09, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 89:;<=>?
              0xFF, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0xFF, // @ABCDEFG
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // HIJKLMNO
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // PQRSTUVW
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // XYZ[\]^_
              0xFF, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0xFF, // `abcdefg
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // hijklmno
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // pqrstuvw
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // xyz{|}~.
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ........
              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  // ........
            };
            return table[c];
         }

         /// <summary>
         /// Returns 2 characters with the string representation of the byte argument.
         /// For instance, returns "00" for 0x00 or "FF" for 0xFF.
         /// </summary>
         INLINE static const char* bytetohexstr(const uint8_t byte)
         {
            static const char* table[] = 
            {
               "00", "01", "02", "03", "04", "05", "06", "07", 
               "08", "09", "0A", "0B", "0C", "0D", "0E", "0F",
               "10", "11", "12", "13", "14", "15", "16", "17",
               "18", "19", "1A", "1B", "1C", "1D", "1E", "1F",
               "20", "21", "22", "23", "24", "25", "26", "27",
               "28", "29", "2A", "2B", "2C", "2D", "2E", "2F",
               "30", "31", "32", "33", "34", "35", "36", "37",
               "38", "39", "3A", "3B", "3C", "3D", "3E", "3F",
               "40", "41", "42", "43", "44", "45", "46", "47",
               "48", "49", "4A", "4B", "4C", "4D", "4E", "4F",
               "50", "51", "52", "53", "54", "55", "56", "57",
               "58", "59", "5A", "5B", "5C", "5D", "5E", "5F",
               "60", "61", "62", "63", "64", "65", "66", "67",
               "68", "69", "6A", "6B", "6C", "6D", "6E", "6F",
               "70", "71", "72", "73", "74", "75", "76", "77",
               "78", "79", "7A", "7B", "7C", "7D", "7E", "7F",
               "80", "81", "82", "83", "84", "85", "86", "87",
               "88", "89", "8A", "8B", "8C", "8D", "8E", "8F",
               "90", "91", "92", "93", "94", "95", "96", "97",
               "98", "99", "9A", "9B", "9C", "9D", "9E", "9F",
               "A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7",
               "A8", "A9", "AA", "AB", "AC", "AD", "AE", "AF",
               "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7",
               "B8", "B9", "BA", "BB", "BC", "BD", "BE", "BF",
               "C0", "C1", "C2", "C3", "C4", "C5", "C6", "C7",
               "C8", "C9", "CA", "CB", "CC", "CD", "CE", "CF",
               "D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7",
               "D8", "D9", "DA", "DB", "DC", "DD", "DE", "DF",
               "E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7",
               "E8", "E9", "EA", "EB", "EC", "ED", "EE", "EF",
               "F0", "F1", "F2", "F3", "F4", "F5", "F6", "F7",
               "F8", "F9", "FA", "FB", "FC", "FD", "FE", "FF"
            };
            return table[byte];
         }

         /// <summary>
         /// Returns 2 characters encoded in uint16_t with the string representation of the byte argument.
         /// For instance, returns 0x3030 ("00") for 0x00 because '0' is 0x30 in ascii.
         /// </summary>
         INLINE static uint16_t bytetohexint16(const uint8_t byte)
         {
            static const uint16_t table[] = 
            {
               0x3030, 0x3130, 0x3230, 0x3330, 0x3430, 0x3530, 0x3630, 0x3730,
               0x3830, 0x3930, 0x4130, 0x4230, 0x4330, 0x4430, 0x4530, 0x4630,
               0x3031, 0x3131, 0x3231, 0x3331, 0x3431, 0x3531, 0x3631, 0x3731,
               0x3831, 0x3931, 0x4131, 0x4231, 0x4331, 0x4431, 0x4531, 0x4631,
               0x3032, 0x3132, 0x3232, 0x3332, 0x3432, 0x3532, 0x3632, 0x3732,
               0x3832, 0x3932, 0x4132, 0x4232, 0x4332, 0x4432, 0x4532, 0x4632,
               0x3033, 0x3133, 0x3233, 0x3333, 0x3433, 0x3533, 0x3633, 0x3733,
               0x3833, 0x3933, 0x4133, 0x4233, 0x4333, 0x4433, 0x4533, 0x4633,
               0x3034, 0x3134, 0x3234, 0x3334, 0x3434, 0x3534, 0x3634, 0x3734,
               0x3834, 0x3934, 0x4134, 0x4234, 0x4334, 0x4434, 0x4534, 0x4634,
               0x3035, 0x3135, 0x3235, 0x3335, 0x3435, 0x3535, 0x3635, 0x3735,
               0x3835, 0x3935, 0x4135, 0x4235, 0x4335, 0x4435, 0x4535, 0x4635,
               0x3036, 0x3136, 0x3236, 0x3336, 0x3436, 0x3536, 0x3636, 0x3736,
               0x3836, 0x3936, 0x4136, 0x4236, 0x4336, 0x4436, 0x4536, 0x4636,
               0x3037, 0x3137, 0x3237, 0x3337, 0x3437, 0x3537, 0x3637, 0x3737,
               0x3837, 0x3937, 0x4137, 0x4237, 0x4337, 0x4437, 0x4537, 0x4637,
               0x3038, 0x3138, 0x3238, 0x3338, 0x3438, 0x3538, 0x3638, 0x3738,
               0x3838, 0x3938, 0x4138, 0x4238, 0x4338, 0x4438, 0x4538, 0x4638,
               0x3039, 0x3139, 0x3239, 0x3339, 0x3439, 0x3539, 0x3639, 0x3739,
               0x3839, 0x3939, 0x4139, 0x4239, 0x4339, 0x4439, 0x4539, 0x4639,
               0x3041, 0x3141, 0x3241, 0x3341, 0x3441, 0x3541, 0x3641, 0x3741,
               0x3841, 0x3941, 0x4141, 0x4241, 0x4341, 0x4441, 0x4541, 0x4641,
               0x3042, 0x3142, 0x3242, 0x3342, 0x3442, 0x3542, 0x3642, 0x3742,
               0x3842, 0x3942, 0x4142, 0x4242, 0x4342, 0x4442, 0x4542, 0x4642,
               0x3043, 0x3143, 0x3243, 0x3343, 0x3443, 0x3543, 0x3643, 0x3743,
               0x3843, 0x3943, 0x4143, 0x4243, 0x4343, 0x4443, 0x4543, 0x4643,
               0x3044, 0x3144, 0x3244, 0x3344, 0x3444, 0x3544, 0x3644, 0x3744,
               0x3844, 0x3944, 0x4144, 0x4244, 0x4344, 0x4444, 0x4544, 0x4644,
               0x3045, 0x3145, 0x3245, 0x3345, 0x3445, 0x3545, 0x3645, 0x3745,
               0x3845, 0x3945, 0x4145, 0x4245, 0x4345, 0x4445, 0x4545, 0x4645,
               0x3046, 0x3146, 0x3246, 0x3346, 0x3446, 0x3546, 0x3646, 0x3746,
               0x3846, 0x3946, 0x4146, 0x4246, 0x4346, 0x4446, 0x4546, 0x4646
               /* reverse
               0x3030, 0x3031, 0x3032, 0x3033, 0x3034, 0x3035, 0x3036, 0x3037,
               0x3038, 0x3039, 0x3041, 0x3042, 0x3043, 0x3044, 0x3045, 0x3046,
               0x3130, 0x3131, 0x3132, 0x3133, 0x3134, 0x3135, 0x3136, 0x3137,
               0x3138, 0x3139, 0x3141, 0x3142, 0x3143, 0x3144, 0x3145, 0x3146,
               0x3230, 0x3231, 0x3232, 0x3233, 0x3234, 0x3235, 0x3236, 0x3237,
               0x3238, 0x3239, 0x3241, 0x3242, 0x3243, 0x3244, 0x3245, 0x3246,
               0x3330, 0x3331, 0x3332, 0x3333, 0x3334, 0x3335, 0x3336, 0x3337,
               0x3338, 0x3339, 0x3341, 0x3342, 0x3343, 0x3344, 0x3345, 0x3346,
               0x3430, 0x3431, 0x3432, 0x3433, 0x3434, 0x3435, 0x3436, 0x3437,
               0x3438, 0x3439, 0x3441, 0x3442, 0x3443, 0x3444, 0x3445, 0x3446,
               0x3530, 0x3531, 0x3532, 0x3533, 0x3534, 0x3535, 0x3536, 0x3537,
               0x3538, 0x3539, 0x3541, 0x3542, 0x3543, 0x3544, 0x3545, 0x3546,
               0x3630, 0x3631, 0x3632, 0x3633, 0x3634, 0x3635, 0x3636, 0x3637,
               0x3638, 0x3639, 0x3641, 0x3642, 0x3643, 0x3644, 0x3645, 0x3646,
               0x3730, 0x3731, 0x3732, 0x3733, 0x3734, 0x3735, 0x3736, 0x3737,
               0x3738, 0x3739, 0x3741, 0x3742, 0x3743, 0x3744, 0x3745, 0x3746,
               0x3830, 0x3831, 0x3832, 0x3833, 0x3834, 0x3835, 0x3836, 0x3837,
               0x3838, 0x3839, 0x3841, 0x3842, 0x3843, 0x3844, 0x3845, 0x3846,
               0x3930, 0x3931, 0x3932, 0x3933, 0x3934, 0x3935, 0x3936, 0x3937,
               0x3938, 0x3939, 0x3941, 0x3942, 0x3943, 0x3944, 0x3945, 0x3946,
               0x4130, 0x4131, 0x4132, 0x4133, 0x4134, 0x4135, 0x4136, 0x4137,
               0x4138, 0x4139, 0x4141, 0x4142, 0x4143, 0x4144, 0x4145, 0x4146,
               0x4230, 0x4231, 0x4232, 0x4233, 0x4234, 0x4235, 0x4236, 0x4237,
               0x4238, 0x4239, 0x4241, 0x4242, 0x4243, 0x4244, 0x4245, 0x4246,
               0x4330, 0x4331, 0x4332, 0x4333, 0x4334, 0x4335, 0x4336, 0x4337,
               0x4338, 0x4339, 0x4341, 0x4342, 0x4343, 0x4344, 0x4345, 0x4346,
               0x4430, 0x4431, 0x4432, 0x4433, 0x4434, 0x4435, 0x4436, 0x4437,
               0x4438, 0x4439, 0x4441, 0x4442, 0x4443, 0x4444, 0x4445, 0x4446,
               0x4530, 0x4531, 0x4532, 0x4533, 0x4534, 0x4535, 0x4536, 0x4537,
               0x4538, 0x4539, 0x4541, 0x4542, 0x4543, 0x4544, 0x4545, 0x4546,
               0x4630, 0x4631, 0x4632, 0x4633, 0x4634, 0x4635, 0x4636, 0x4637,
               0x4638, 0x4639, 0x4641, 0x4642, 0x4643, 0x4644, 0x4645, 0x4646*/
            };
            return table[byte];
         }

         /// <summary>
         /// Returns 4 characters encoded in uint32_t with the string representation of parts from v selected by il and ih.
         /// For instance, returns 0x46464646 ("FFFF") for v=0x00FF00FF and il=0 (select first byte) and ih=24 (select third byte).
         /// </summary>
         INLINE static uint32_t valuetohexint32(const uint32_t v, const uint32_t il, const uint32_t ih)
         {
            return
               ((uint32_t)Util::bytetohexint16((uint8_t)CppCore::getbits32(v, il, 8U))) |
               ((uint32_t)Util::bytetohexint16((uint8_t)CppCore::getbits32(v, ih, 8U)) << 16);
         }

         /// <summary>
         /// Returns 4 characters encoded in uint32_t with the string representation of parts from v selected by il and ih.
         /// For instance, returns 0x46464646 ("FFFF") for v=0x00FF0000000000FF and il=0 (select first byte) and ih=48 (select seventh byte).
         /// </summary>
         INLINE static uint32_t valuetohexint32(const uint64_t v, const uint32_t il, const uint32_t ih)
         {
            return
               ((uint32_t)Util::bytetohexint16((uint8_t)CppCore::getbits64(v, il, 8U))) |
               ((uint32_t)Util::bytetohexint16((uint8_t)CppCore::getbits64(v, ih, 8U)) << 16);
         }

         /// <summary>
         /// Template function for parsing unsigned integer from zero terminated hex string.
         /// No overflow or invalid symbol check! No support for '0x' prefix!
         /// For bigendian=true the first character must contain the highest bits.
         /// N must be the number of max symbols for T (e.g. 8 for 32bit and 16 for 64bit).
         /// </summary>
         template<typename T, size_t N>
         INLINE static T parse(const char* input, const bool bigendian = true)
         {
            T r = (T)0U;
            char c;
            CPPCORE_UNROLL
            for (size_t i = 0; i != N && (c = *input++); i++) // pray for unroll
            {
               r <<= 4;
               r |= Util::valueofhexchar(c);
            }
            return bigendian ? r : CppCore::byteswap(r);
         }

         /// <summary>
         /// Template function for parsing unsigned integer from zero terminated hex string.
         /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
         /// For bigendian=true the first character must contain the highest bits.
         /// N must be the number of overflow free symbols for T (e.g. 8 for 32bit and 16 for 64bit).
         /// </summary>
         template<typename T, size_t N>
         INLINE static bool tryparse(const char* input, T& r, const bool bigendian = true)
         {
            r = (T)0U;
            uint8_t v;
            if (input) CPPCORE_LIKELY
            {
               v = Util::valueofhexchar(*input++);
               if (v <= 0x0F) CPPCORE_LIKELY
               {
                  r |= v;
                  CPPCORE_UNROLL
                  for (size_t i = 0; i != N-1; i++)
                  {
                     v = Util::valueofhexchar(*input++);
                     if (v <= 0x0F)
                     {
                        r <<= 4;
                        r |= v;
                     }
                     else if (v == 0xFE) // end of str
                     {
                        r = bigendian ? r : CppCore::byteswap(r);
                        return true;
                     }
                     else // invalid symbol
                        return false;
                  }
                  if (*input == 0) CPPCORE_LIKELY
                  {
                     r = bigendian ? r : CppCore::byteswap(r);
                     return true;
                  }
                  else CPPCORE_UNLIKELY // too many symbols for T
                     return false;
               }
               else CPPCORE_UNLIKELY // empty string or invalid first symbol
                  return false;
            }
            else CPPCORE_UNLIKELY // null pointer
               return false;
         }
      };

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Creates hex string with exactly 4 symbols (leading zeros) for 16-bit unsigned integer v.
      /// Requires 4 (or 5 if writeterm=true) free bytes in parameter s.
      /// </summary>
      INLINE static void tostring(const uint16_t v, char* s, const bool bigendian = true, const bool writeterm = true)
      {
         uint32_t* p = (uint32_t*)s;
         if (bigendian) *p = Util::valuetohexint32((uint32_t)v,  8U,  0U);
         else *p = Util::valuetohexint32((uint32_t)v,  0U,  8U);
         if (writeterm)
            *((char*)&p[1]) = (char)0x00;
      }

      /// <summary>
      /// Creates hex string with exactly 8 symbols (leading zeros) for 32-bit unsigned integer v.
      /// Requires 8 (or 9 if writeterm=true) free bytes in parameter s.
      /// </summary>
      INLINE static void tostring(const uint32_t v, char* s, const bool bigendian = true, const bool writeterm = true)
      {
         uint32_t* p = (uint32_t*)s;
         if (bigendian)
         {
            p[0] = Util::valuetohexint32(v, 24U, 16U);
            p[1] = Util::valuetohexint32(v,  8U,  0U);
         }
         else
         {
            p[0] = Util::valuetohexint32(v,  0U,  8U);
            p[1] = Util::valuetohexint32(v, 16U, 24U);
         }
         if (writeterm)
            *((char*)&p[2]) = (char)0x00;
      }

      /// <summary>
      /// Creates hex string with exactly 16 symbols (leading zeros) for 64-bit unsigned integer v.
      /// Requires 16 (or 17 if writeterm=true) free bytes in parameter s.
      /// </summary>
      INLINE static void tostring(const uint64_t v, char* s, const bool bigendian = true, const bool writeterm = true)
      {
         uint32_t* p = (uint32_t*)s;
         if (bigendian)
         {
            p[0] = Util::valuetohexint32(v, 56ULL, 48ULL);
            p[1] = Util::valuetohexint32(v, 40ULL, 32ULL);
            p[2] = Util::valuetohexint32(v, 24ULL, 16ULL);
            p[3] = Util::valuetohexint32(v,  8ULL,  0ULL);
         }
         else
         {
            p[0] = Util::valuetohexint32(v,  0ULL,  8ULL);
            p[1] = Util::valuetohexint32(v, 16ULL, 24ULL);
            p[2] = Util::valuetohexint32(v, 32ULL, 40ULL);
            p[3] = Util::valuetohexint32(v, 48ULL, 56ULL);
         }
         if (writeterm)
            *((char*)&p[4]) = (char)0x00;
      }

      /// <summary>
      /// Creates hex string with exactly 4*n16 symbols (leading zeros) for memory that's a multiple of 16-bit.
      /// Requires 4*n16 (or 4*n16+1 if writeterm=true) free bytes in parameter s,
      /// </summary>
      INLINE static void tostring(const uint16_t* v, char* s, const size_t n16, const bool bigendian = true, const bool writeterm = true)
      {
         uint32_t* p = (uint32_t*)s;
         if (bigendian)
         {
            for (size_t i = 0; i != n16; i++)
               *p++ = Util::valuetohexint32((uint32_t)v[i],  0U,  8U);
         }
         else
         {
            for (size_t i = n16-1U; i != std::numeric_limits<size_t>::max(); i--)
               *p++ = Util::valuetohexint32((uint32_t)v[i],  8U,  0U);
         }
         if (writeterm)
            *((char*)p) = (char)0x00;
      }

      /// <summary>
      /// Creates hex string with exactly 8*n32 symbols (leading zeros) for memory that's a multiple of 32-bit.
      /// Requires 8*n32 (or 8*n32+1 if writeterm=true) free bytes in parameter s,
      /// </summary>
      INLINE static void tostring(const uint32_t* v, char* s, const size_t n32, const bool bigendian = true, const bool writeterm = true)
      {
         uint32_t* p = (uint32_t*)s;
         if (bigendian)
         {
            for (size_t i = 0; i != n32; i++)
            {
               const uint32_t t = v[i];
               *p++ = Util::valuetohexint32(t,  0U,  8U);
               *p++ = Util::valuetohexint32(t, 16U, 24U);
            }
         }
         else
         {
            for (size_t i = n32-1U; i != std::numeric_limits<size_t>::max(); i--)
            {
               const uint32_t t = v[i];
               *p++ = Util::valuetohexint32(t, 24U, 16U);
               *p++ = Util::valuetohexint32(t,  8U,  0U);
            }
         }
         if (writeterm)
            *((char*)p) = (char)0x00;
      }

      /// <summary>
      /// Creates hex string with exactly 16*n64 symbols (leading zeros) for memory that's a multiple of 64-bit.
      /// Requires 16*n64 (or 16*n64+1 if writeterm=true) free bytes in parameter s,
      /// </summary>
      INLINE static void tostring(const uint64_t* v, char* s, const size_t n64, const bool bigendian = true, const bool writeterm = true)
      {
         uint32_t* p = (uint32_t*)s;
         if (bigendian)
         {
            for (size_t i = 0; i != n64; i++)
            {
               const uint64_t t = v[i];
               *p++ = Util::valuetohexint32(t,  0ULL,  8ULL);
               *p++ = Util::valuetohexint32(t, 16ULL, 24ULL);
               *p++ = Util::valuetohexint32(t, 32ULL, 40ULL);
               *p++ = Util::valuetohexint32(t, 48ULL, 56ULL);
            }

         }
         else
         {
            for (size_t i = n64-1U; i != std::numeric_limits<size_t>::max(); i--)
            {
               const uint64_t t = v[i];
               *p++ = Util::valuetohexint32(t, 56ULL, 48ULL);
               *p++ = Util::valuetohexint32(t, 40ULL, 32ULL);
               *p++ = Util::valuetohexint32(t, 24ULL, 16ULL);
               *p++ = Util::valuetohexint32(t,  8ULL,  0ULL);
            }
         }
         if (writeterm)
            *((char*)p) = (char)0x00;
      }

      /// <summary>
      /// Creates hex string for memory of certain length.
      /// Requires len*2 (or len*2+1 if writeterm=true) free bytes in parameter s.
      /// </summary>
      INLINE static void tostring(const void* m, const size_t len, char* s, const bool bigendian = true, const bool writeterm = true)
      {
         const char* mem = (const char*)m;
         uint32_t* p = (uint32_t*)s;
         if (bigendian)
         {
            const char* end = mem + len;
         #if defined(CPPCORE_CPU_64BIT)
            while (mem + 8U <= end)
            {
               const uint64_t t = *((uint64_t*)mem);
               *p++ = Util::valuetohexint32(t,  0ULL,  8ULL);
               *p++ = Util::valuetohexint32(t, 16ULL, 24ULL);
               *p++ = Util::valuetohexint32(t, 32ULL, 40ULL);
               *p++ = Util::valuetohexint32(t, 48ULL, 56ULL);
               mem += 8U;
            }
            if (mem + 4U <= end)
         #else
            while (mem + 4U <= end)
         #endif
            {
               const uint32_t t = *((uint32_t*)mem);
               *p++ = Util::valuetohexint32(t,  0U,  8U);
               *p++ = Util::valuetohexint32(t, 16U, 24U);
               mem += 4U;
            }
            if (mem + 2U <= end)
            {
               const uint16_t t = *((uint16_t*)mem);
               *p++ = Util::valuetohexint32((uint32_t)t, 0U, 8U);
               mem += 2U;
            }
            if (mem + 1U <= end)
            {
               uint16_t* pt = (uint16_t*)p;
               *pt++ = Util::bytetohexint16(*mem);
               p = (uint32_t*)pt;
            }
         }
         else
         {
            const char* end = mem;
            mem += len;
         #if defined(CPPCORE_CPU_64BIT)
            while (mem - 8U >= end)
            {
               mem -= 8U;
               const uint64_t t = *((uint64_t*)mem);
               *p++ = Util::valuetohexint32(t, 56ULL, 48ULL);
               *p++ = Util::valuetohexint32(t, 40ULL, 32ULL);
               *p++ = Util::valuetohexint32(t, 24ULL, 16ULL);
               *p++ = Util::valuetohexint32(t,  8ULL,  0ULL);
            }
            if (mem - 4U >= end)
         #else
            while (mem - 4U >= end)
         #endif
            {
               mem -= 4U;
               const uint32_t t = *((uint32_t*)mem);
               *p++ = Util::valuetohexint32(t, 24U, 16U);
               *p++ = Util::valuetohexint32(t,  8U,  0U);
            }
            if (mem - 2U >= end)
            {
               mem -= 2U;
               const uint16_t t = *((uint16_t*)mem);
               *p++ = Util::valuetohexint32((uint32_t)t, 8U, 0U);
            }
            if (mem - 1U >= end)
            {
               uint16_t* pt = (uint16_t*)p;
               *pt++ = Util::bytetohexint16(*(mem-1U));
               p = (uint32_t*)pt;
            }
         }
         if (writeterm)
            *((char*)p) = (char)0x00;
      }

      /// <summary>
      /// Creates hex string for memory of certain length.
      /// Will resize s as necessary.
      /// </summary>
      INLINE static void tostring(const void* mem, const size_t len, std::string& s, const bool bigendian = true)
      {
         s.resize(len * 2U);
         Hex::tostring(mem, len, s.data(), bigendian, false);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Parses 16-bit unsigned integer from zero terminated hex string.
      /// No overflow or invalid symbol check! No support for '0x' prefix!
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static uint16_t parse16u(const char* input, const bool bigendian = true)
      {
         return Util::parse<uint16_t, CPPCORE_MAXSYMBOLS_B16_16>(input, bigendian);
      }

      /// <summary>
      /// Parses 32-bit unsigned integer from zero terminated hex string.
      /// No overflow or invalid symbol check! No support for '0x' prefix!
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static uint32_t parse32u(const char* input, const bool bigendian = true)
      {
         return Util::parse<uint32_t, CPPCORE_MAXSYMBOLS_B16_32>(input, bigendian);
      }

      /// <summary>
      /// Parses 64-bit unsigned integer from zero terminated hex string.
      /// No overflow or invalid symbol check! No support for '0x' prefix!
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static uint64_t parse64u(const char* input, const bool bigendian = true)
      {
         return Util::parse<uint64_t, CPPCORE_MAXSYMBOLS_B16_64>(input, bigendian);
      }

      /// <summary>
      /// Parses 16-bit signed integer from zero terminated hex string.
      /// No overflow or invalid symbol check! No support for '0x' prefix!
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static int16_t parse16s(const char* input, const bool bigendian = true)
      {
         return (int16_t)Hex::parse16u(input, bigendian);
      }

      /// <summary>
      /// Parses 32-bit signed integer from zero terminated hex string.
      /// No overflow or invalid symbol check! No support for '0x' prefix!
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static int32_t parse32s(const char* input, const bool bigendian = true)
      {
         return (int32_t)Hex::parse32u(input, bigendian);
      }

      /// <summary>
      /// Parses 64-bit signed integer from zero terminated hex string.
      /// No overflow or invalid symbol check! No support for '0x' prefix!
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static int64_t parse64s(const char* input, const bool bigendian = true)
      {
         return (int64_t)Hex::parse64u(input, bigendian);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Tries to parse 16-bit unsigned integer from zero terminated hex string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static bool tryparse(const char* input, uint16_t& r, const bool bigendian = true)
      {
         return Util::tryparse<uint16_t, CPPCORE_MAXSYMBOLS_B16_16>(input, r, bigendian);
      }

      /// <summary>
      /// Tries to parse 32-bit unsigned integer from zero terminated hex string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static bool tryparse(const char* input, uint32_t& r, const bool bigendian = true)
      {
         return Util::tryparse<uint32_t, CPPCORE_MAXSYMBOLS_B16_32>(input, r, bigendian);
      }

      /// <summary>
      /// Tries to parse 64-bit unsigned integer from zero terminated hex string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static bool tryparse(const char* input, uint64_t& r, const bool bigendian = true)
      {
         return Util::tryparse<uint64_t, CPPCORE_MAXSYMBOLS_B16_64>(input, r, bigendian);
      }

      /// <summary>
      /// Tries to parse 16-bit signed integer from zero terminated hex string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static bool tryparse(const char* input, int16_t& r, const bool bigendian = true)
      {
         return Util::tryparse<uint16_t, CPPCORE_MAXSYMBOLS_B16_16>(input, (uint16_t&)r, bigendian);
      }

      /// <summary>
      /// Tries to parse 32-bit signed integer from zero terminated hex string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static bool tryparse(const char* input, int32_t& r, const bool bigendian = true)
      {
         return Util::tryparse<uint32_t, CPPCORE_MAXSYMBOLS_B16_32>(input, (uint32_t&)r, bigendian);
      }

      /// <summary>
      /// Tries to parse 64-bit signed integer from zero terminated hex string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// For bigendian=true the first character must contain the highest bits.
      /// </summary>
      INLINE static bool tryparse(const char* input, int64_t& r, const bool bigendian = true)
      {
         return Util::tryparse<uint64_t, CPPCORE_MAXSYMBOLS_B16_64>(input, (uint64_t&)r, bigendian);
      }
   };

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // DECIMAL
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Decimal Encoding
   /// </summary>
   class Decimal
   {
   private:
      INLINE Decimal() { }
   public:
      /// <summary>
      /// Decimal Helper Functions
      /// </summary>
      class Util
      {
      private:
         INLINE Util() { }
      public:
         /// <summary>
         /// Creates decimal string with up to N symbols for unsigned integer v.
         /// Requires N (or N+1 if writeterm=true) free bytes in parameter s.
         /// Returns pointer to the position of the new 0x00 termination (written or not).
         /// </summary>
         template<typename UINT, size_t N>
         INLINE static char* tostringu(UINT v, char* s, const bool writeterm)
         {
            if (!CppCore::testzero(v)) CPPCORE_LIKELY
            {
               uint32_t r;
               uint32_t n;
               CppCore::udivmod(v, 10U, v, r);
               *s++ = CPPCORE_ALPHABET_B10[r];
               CPPCORE_UNROLL
               for (n = 1U; n != N; n++)
               {
                  if (!CppCore::testzero(v))
                  {
                     CppCore::udivmod(v, 10U, v, r);
                     *s++ = CPPCORE_ALPHABET_B10[r];
                  }
                  else
                     break;
               }
               Memory::reverse(s-n, n);
            }
            else CPPCORE_UNLIKELY
               *s++ = '0';
            if (writeterm)
               *s = (char)0x00;
            return s;
         }

         /// <summary>
         /// Creates decimal string with up to N symbols for unsigned integer v.
         /// Requires N (or N+1 if writeterm=true) free bytes in parameter s.
         /// </summary>
         template<typename UINT, typename STRING, size_t N>
         INLINE static void tostringu(UINT& v, STRING& s)
         {
            s.resize(N);
            char* start = s.data();
            char* end   = tostringu<UINT, N>(v, start, false);
            s.resize(end-start);
         }

         /// <summary>
         /// Creates decimal string with up to N symbols for signed integer v.
         /// Requires N+1 (for +-) (or N+2 if writeterm=true) free bytes in parameter s.
         /// Returns pointer to the position of the new 0x00 termination (written or not).
         /// </summary>
         template<typename INT, typename UINT, size_t N>
         INLINE static char* tostrings(INT v, char* s, const bool writeterm)
         {
            UINT u;
            uint32_t r;
            uint32_t n;
            if (v > 0)
            {
               u = (UINT)v;
               CppCore::udivmod(u, 10U, u, r);
               *s++ = CPPCORE_ALPHABET_B10[r];
            }
            else if (v < 0)
            {
               *s++ = '-';
               // first one must be signed to deal with MIN (e.g.0x80000000)
               INT rs;
               CppCore::divmod(v, (INT)10U, v, rs);
               *s++ = CPPCORE_ALPHABET_B10[-rs];
               u = (UINT)-v;
            }
            else CPPCORE_UNLIKELY
            {
               *s++ = '0';
               if (writeterm)
                  *s = (char)0x00;
               return s;
            }
            CPPCORE_UNROLL
            for (n = 1U; n != N; n++)
            {
               if (!CppCore::testzero(u))
               {
                  CppCore::udivmod(u, 10U, u, r);
                  *s++ = CPPCORE_ALPHABET_B10[r];
               }
               else
                  break;
            }
            Memory::reverse(s-n, n);
            if (writeterm)
               *s = (char)0x00;
            return s;
         }

         /// <summary>
         /// Creates decimal string with up to N symbols for signed integer v.
         /// </summary>
         template<typename INT, typename UINT, typename STRING, size_t N>
         INLINE static void tostrings(INT& v, STRING& s)
         {
            s.resize(N);
            char* start = s.data();
            char* end   = tostrings<INT, UINT, N>(v, start, false);
            s.resize(end-start);
         }

         /// <summary>
         /// Template function for parsing unsigned integer from zero terminated decimal string.
         /// No overflow or invalid symbol check!
         /// </summary>
         template<typename T>
         INLINE static T parseu(const char* input)
         {
            T r = 0U;
            while (const char c = *input++)
               r = CppCore::madd<T>(r, (T)10U, (T)(c-'0'));
            return r;
         }

         /// <summary>
         /// Template function for parsing signed integer from zero terminated decimal string.
         /// No overflow or invalid symbol check! First symbol can be '-' or '+' to indicate sign.
         /// </summary>
         template<typename T>
         INLINE static T parses(const char* input)
         {
            T r = 0;
            char c;
            if ((c = *input++)) CPPCORE_LIKELY
            {
               T sign = 1;
               if (c == '-') sign = -sign; 
               else if (c == '+') { }
               else r += (T)(c-'0');
               while ((c = *input++))
                  r = CppCore::madd<T>(r, (T)10, (T)(c-'0'));
               r *= sign;
            }
            return r;
         }

         /// <summary>
         /// Template function for parsing unsigned integer from zero terminated decimal string.
         /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
         /// N must be the number of max symbols e.g. 10 for uint32_t or 20 for uint64_t.
         /// </summary>
         template<typename T, size_t N>
         INLINE static bool tryparseu(const char* input, T& r)
         {
            // TODO: The 00-byte check and isdigit() can be
            // done with lookup table like in hex-version
            r = 0U;
            char c;
            if (input) CPPCORE_LIKELY
            {
               // symbol 1 (no mul, no overflow)
               if ((c = *input++) && CppCore::isdigit(c)) CPPCORE_LIKELY
                  r += (T)(c-'0');
               else CPPCORE_UNLIKELY // invalid symbol or empty string
                  return false;
               // n-2 symbols (muladd, no overflow)
               for (size_t i = 0; i != N-2U; i++)
               {
                  if ((c = *input++))
                  {
                     if (CppCore::isdigit(c)) CPPCORE_LIKELY
                        r = CppCore::madd<T>((T)r, (T)10U, (T)(c-'0'));
                     else CPPCORE_UNLIKELY // invalid symbol
                        return false;
                  }
                  else // end of str
                     return true;
               }
               // last symbol (may fit or overflow already)
               if ((c = *input++))
               {
                  if (!CppCore::isdigit(c) || CppCore::overflowmadd((T&)r, (T)r, (T)10U, (T)(c - '0'))) CPPCORE_UNLIKELY
                     return false; // invalid symbol or overflow
               }
               else // end of str
                  return true;
               // ok if end of str else fail (invalid symbol or overflow)
               return (*input == 0);
            }
            else CPPCORE_UNLIKELY // null pointer
               return false;
         }

         /// <summary>
         /// Template function for parsing signed integer from zero terminated decimal string.
         /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
         /// N must be the number of max symbols e.g. 10 for int32_t or 19 for int64_t.
         /// </summary>
         template<typename T, size_t N>
         INLINE static bool tryparses(const char* input, T& r)
         {
            // TODO: The 00-byte check and isdigit() can be 
            // done with lookup table like in hex-version
            r = 0;
            char c;
            if (input && (c = *input++)) CPPCORE_LIKELY
            {
               // POSITIVE INTEGER
               if (CppCore::isdigit(c) || c == '+')
               {
                  // symbol 1 (no mul, no overflow, skip + if there)
                  if (c != '+') CPPCORE_LIKELY
                     r += (T)(c-'0');
                  else CPPCORE_UNLIKELY
                  {
                     if ((c = *input++) && CppCore::isdigit(c)) CPPCORE_LIKELY
                        r += (T)(c-'0');
                     else CPPCORE_UNLIKELY // single + or + with invalid symbol
                        return false;
                  }
                  // n-2 symbols (muladd, no overflow)
                  CPPCORE_UNROLL
                  for (size_t i = 0; i != N-2U; i++)
                  {
                     if ((c = *input++))
                     {
                        if (CppCore::isdigit(c)) CPPCORE_LIKELY
                           r = CppCore::madd<T>((T)r, (T)10, (T)(c-'0'));
                        else CPPCORE_UNLIKELY // invalid symbol
                           return false;
                     }
                     else // end of str
                        return true;
                  }
                  // last symbol (may fit or overflow already)
                  if ((c = *input++))
                  {
                     if (!CppCore::isdigit(c) || CppCore::overflowmadd((T&)r, (T)r, (T)10, (T)(c-'0'))) CPPCORE_UNLIKELY
                        return false; // invalid symbol or overflow
                  }
                  else // end of str
                     return true;
                  // ok if end of str else fail (invalid symbol or overflow)
                  return (*input == 0);
               }
               // NEGATIVE INTEGER
               else if (c == '-' && (c = *input++))
               {
                  // symbol 1 (no mul, no overflow)
                  if (CppCore::isdigit(c)) CPPCORE_LIKELY
                     r -= (T)(c-'0');
                  else CPPCORE_UNLIKELY // - with invalid symbol
                     return false;
                  // n-2 symbols (mulsub, no overflow)
                  CPPCORE_UNROLL
                  for (size_t i = 0; i != N-2U; i++)
                  {
                     if ((c = *input++))
                     {
                        if (CppCore::isdigit(c)) CPPCORE_LIKELY
                           r = CppCore::msub<T>((T)r, (T)10, (T)(c-'0'));
                        else CPPCORE_UNLIKELY // invalid symbol
                           return false;
                     }
                     else // end of str
                        return true;
                  }
                  // last symbol (may fit or overflow already)
                  if ((c = *input++))
                  {
                     if (!CppCore::isdigit(c) || CppCore::overflowmsub((T&)r, (T)r, (T)10, (T)(c-'0'))) CPPCORE_UNLIKELY
                        return false; // invalid symbol or overflow
                  }
                  else // end of str
                     return true;
                  // ok if end of str else fail (invalid symbol or overflow)
                  return (*input == 0);
               }
               else CPPCORE_UNLIKELY // invalid first symbol or single minus
                  return false;
            }
            else CPPCORE_UNLIKELY // null pointer or empty string
               return false;
         }
      };

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Creates decimal string with up to 3 symbols for 8-bit unsigned integer v.
      /// Requires 3 (or 4 if writeterm=true) free bytes in parameter s.
      /// Returns pointer to the position of the new 0x00 termination (written or not).
      /// </summary>
      INLINE static char* tostring(const uint8_t v, char* s, const bool writeterm = true)
      {
         return Util::tostringu<uint8_t, CPPCORE_MAXLENGTH_B10_8U>(v, s, writeterm);
      }

      /// <summary>
      /// Creates decimal string with up to 5 symbols for 16-bit unsigned integer v.
      /// Requires 5 (or 6 if writeterm=true) free bytes in parameter s.
      /// Returns pointer to the position of the new 0x00 termination (written or not).
      /// </summary>
      INLINE static char* tostring(const uint16_t v, char* s, const bool writeterm = true)
      {
         return Util::tostringu<uint16_t, CPPCORE_MAXLENGTH_B10_16U>(v, s, writeterm);
      }

      /// <summary>
      /// Creates decimal string with up to 10 symbols for 32-bit unsigned integer v.
      /// Requires 10 (or 11 if writeterm=true) free bytes in parameter s.
      /// Returns pointer to the position of the new 0x00 termination (written or not).
      /// </summary>
      INLINE static char* tostring(const uint32_t v, char* s, const bool writeterm = true)
      {
         return Util::tostringu<uint32_t, CPPCORE_MAXLENGTH_B10_32U>(v, s, writeterm);
      }

      /// <summary>
      /// Creates decimal string with up to 20 symbols for 64-bit unsigned integer v.
      /// Requires 20 (or 21 if writeterm=true) free bytes in parameter s.
      /// Returns pointer to the position of the new 0x00 termination (written or not).
      /// </summary>
      INLINE static char* tostring(const uint64_t v, char* s, const bool writeterm = true)
      {
         return Util::tostringu<uint64_t, CPPCORE_MAXLENGTH_B10_64U>(v, s, writeterm);
      }

      /// <summary>
      /// Creates decimal string with up to 3 symbols for 8-bit signed integer v.
      /// Requires 4 (or 5 if writeterm=true) free bytes in parameter s.
      /// Returns pointer to the position of the new 0x00 termination (written or not).
      /// </summary>
      INLINE static char* tostring(const int8_t v, char* s, const bool writeterm = true)
      {
         return Util::tostrings<int8_t, uint8_t, CPPCORE_MAXLENGTH_B10_8S>(v, s, writeterm);
      }

      /// <summary>
      /// Creates decimal string with up to 5 symbols for 16-bit signed integer v.
      /// Requires 6 (or 7 if writeterm=true) free bytes in parameter s.
      /// Returns pointer to the position of the new 0x00 termination (written or not).
      /// </summary>
      INLINE static char* tostring(const int16_t v, char* s, const bool writeterm = true)
      {
         return Util::tostrings<int16_t, uint16_t, CPPCORE_MAXLENGTH_B10_16S>(v, s, writeterm);
      }

      /// <summary>
      /// Creates decimal string with up to 10 symbols for 32-bit signed integer v.
      /// Requires 11 (or 12 if writeterm=true) free bytes in parameter s.
      /// Returns pointer to the position of the new 0x00 termination (written or not).
      /// </summary>
      INLINE static char* tostring(const int32_t v, char* s, const bool writeterm = true)
      {
         return Util::tostrings<int32_t, uint32_t, CPPCORE_MAXLENGTH_B10_32S>(v, s, writeterm);
      }

      /// <summary>
      /// Creates decimal string with up to 19 symbols for 64-bit signed integer v.
      /// Requires 20 (or 21 if writeterm=true) free bytes in parameter s.
      /// Returns pointer to the position of the new 0x00 termination (written or not).
      /// </summary>
      INLINE static char* tostring(const int64_t v, char* s, const bool writeterm = true)
      {
         return Util::tostrings<int64_t, uint64_t, CPPCORE_MAXLENGTH_B10_64S>(v, s, writeterm);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Creates decimal string with up to 5 characters for 16-bit unsigned integer v.
      /// STRING must be std::string compatible string type.
      /// </summary>
      template<typename STRING>
      INLINE static void tostring(uint16_t v, STRING& s)
      {
         Util::tostringu<uint16_t, STRING, CPPCORE_MAXLENGTH_B10_16U>(v, s);
      }

      /// <summary>
      /// Creates decimal string with up to 10 characters for 32-bit unsigned integer v.
      /// STRING must be std::string compatible string type.
      /// </summary>
      template<typename STRING>
      INLINE static void tostring(uint32_t v, STRING& s)
      {
         Util::tostringu<uint32_t, STRING, CPPCORE_MAXLENGTH_B10_32U>(v, s);
      }

      /// <summary>
      /// Creates decimal string with up to 20 characters for 64-bit unsigned integer v.
      /// STRING must be std::string compatible string type.
      /// </summary>
      template<typename STRING>
      INLINE static void tostring(uint64_t v, STRING& s)
      {
         Util::tostringu<uint64_t, STRING, CPPCORE_MAXLENGTH_B10_64U>(v, s);
      }

      /// <summary>
      /// Creates decimal string with up to 6 characters for 16-bit signed integer v.
      /// STRING must be std::string compatible string type.
      /// </summary>
      template<typename STRING>
      INLINE static void tostring(int16_t v, STRING& s)
      {
         Util::tostrings<int16_t, uint16_t, STRING, CPPCORE_MAXLENGTH_B10_16S>(v, s);
      }

      /// <summary>
      /// Creates decimal string with up to 11 characters for 32-bit signed integer v.
      /// STRING must be std::string compatible string type.
      /// </summary>
      template<typename STRING>
      INLINE static void tostring(int32_t v, STRING& s)
      {
         Util::tostrings<int32_t, uint32_t, STRING, CPPCORE_MAXLENGTH_B10_32S>(v, s);
      }

      /// <summary>
      /// Creates decimal string with up to 20 characters for 64-bit signed integer v.
      /// STRING must be std::string compatible string type.
      /// </summary>
      template<typename STRING>
      INLINE static void tostring(int64_t v, STRING& s)
      {
         Util::tostrings<int64_t, uint64_t, STRING, CPPCORE_MAXLENGTH_B10_64S>(v, s);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Parses 8-bit unsigned integer from zero terminated decimal string.
      /// No overflow or invalid symbol check!
      /// </summary>
      INLINE static uint8_t parse8u(const char* input)
      {
         return Util::parseu<uint8_t>(input);
      }

      /// <summary>
      /// Parses 16-bit unsigned integer from zero terminated decimal string.
      /// No overflow or invalid symbol check!
      /// </summary>
      INLINE static uint16_t parse16u(const char* input)
      {
         return Util::parseu<uint16_t>(input);
      }

      /// <summary>
      /// Parses 32-bit unsigned integer from zero terminated decimal string.
      /// No overflow or invalid symbol check!
      /// </summary>
      INLINE static uint32_t parse32u(const char* input)
      {
         return Util::parseu<uint32_t>(input);
      }

      /// <summary>
      /// Parses 64-bit unsigned integer from zero terminated decimal string.
      /// No overflow or invalid symbol check!
      /// </summary>
      INLINE static uint64_t parse64u(const char* input)
      {
         return Util::parseu<uint64_t>(input);
      }

      /// <summary>
      /// Parses 8-bit signed integer from zero terminated decimal string.
      /// No overflow or invalid symbol check!
      /// </summary>
      INLINE static int8_t parse8s(const char* input)
      {
         return Util::parses<int8_t>(input);
      }

      /// <summary>
      /// Parses 16-bit signed integer from zero terminated decimal string.
      /// No overflow or invalid symbol check!
      /// </summary>
      INLINE static int16_t parse16s(const char* input)
      {
         return Util::parses<int16_t>(input);
      }

      /// <summary>
      /// Parses 32-bit signed integer from zero terminated decimal string.
      /// No overflow or invalid symbol check!
      /// </summary>
      INLINE static int32_t parse32s(const char* input)
      {
         return Util::parses<int32_t>(input);
      }

      /// <summary>
      /// Parses 64-bit signed integer from zero terminated decimal string.
      /// No overflow or invalid symbol check!
      /// </summary>
      INLINE static int64_t parse64s(const char* input)
      {
         return Util::parses<int64_t>(input);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Tries to parse 8-bit unsigned integer from zero terminated decimal string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// </summary>
      INLINE static bool tryparse(const char* input, uint8_t& r)
      {
         return Util::tryparseu<uint8_t, CPPCORE_MAXSYMBOLS_B10_8U>(input, r);
      }

      /// <summary>
      /// Tries to parse 16-bit unsigned integer from zero terminated decimal string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// </summary>
      INLINE static bool tryparse(const char* input, uint16_t& r)
      {
         return Util::tryparseu<uint16_t, CPPCORE_MAXSYMBOLS_B10_16U>(input, r);
      }

      /// <summary>
      /// Tries to parse 32-bit unsigned integer from zero terminated decimal string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// </summary>
      INLINE static bool tryparse(const char* input, uint32_t& r)
      {
         return Util::tryparseu<uint32_t, CPPCORE_MAXSYMBOLS_B10_32U>(input, r);
      }

      /// <summary>
      /// Tries to parse 64-bit unsigned integer from zero terminated decimal string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
      /// </summary>
      INLINE static bool tryparse(const char* input, uint64_t& r)
      {
         return Util::tryparseu<uint64_t, CPPCORE_MAXSYMBOLS_B10_64U>(input, r);
      }

      /// <summary>
      /// Tries to parse 8-bit signed integer from zero terminated decimal string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or over-/underflowed.
      /// </summary>
      INLINE static bool tryparse(const char* input, int8_t& r)
      {
         return Util::tryparses<int8_t, CPPCORE_MAXSYMBOLS_B10_8S>(input, r);
      }

      /// <summary>
      /// Tries to parse 16-bit signed integer from zero terminated decimal string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or over-/underflowed.
      /// </summary>
      INLINE static bool tryparse(const char* input, int16_t& r)
      {
         return Util::tryparses<int16_t, CPPCORE_MAXSYMBOLS_B10_16S>(input, r);
      }

      /// <summary>
      /// Tries to parse 32-bit signed integer from zero terminated decimal string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or over-/underflowed.
      /// </summary>
      INLINE static bool tryparse(const char* input, int32_t& r)
      {
         return Util::tryparses<int32_t, CPPCORE_MAXSYMBOLS_B10_32S>(input, r);
      }

      /// <summary>
      /// Tries to parse 64-bit signed integer from zero terminated decimal string.
      /// Returns false if input is a null pointer or empty string or has invalid symbol or over-/underflowed.
      /// </summary>
      INLINE static bool tryparse(const char* input, int64_t& r)
      {
         return Util::tryparses<int64_t, CPPCORE_MAXSYMBOLS_B10_64S>(input, r);
      }
   };
}
