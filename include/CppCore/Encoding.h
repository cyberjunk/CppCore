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
      /// Returns an upper bound of decoded bits required for encoded symbols.
      /// </summary>
      INLINE static uint32_t estimateBits(uint32_t symbols, uint32_t base)
      {
         assert(base >= 2);
         uint32_t pow2b = CppCore::ngptwo32(base);
         uint32_t nbits = CppCore::tzcnt32(pow2b);
         return symbols * nbits;
      }

      /// <summary>
      /// Returns an upper bound of encoded symbols required for decoded bits.
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
         CPPCORE_ALIGN_OPTIM(UINT) v;
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
         CPPCORE_ALIGN_OPTIM(UINT) v;
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
         uint8_t n = 0;
         CPPCORE_ALIGN64 uint8_t tbl[256];
         CppCore::clear(tbl);
         CppCore::clear(r);
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
         uint8_t n = 0;
         CPPCORE_ALIGN64 uint8_t tbl[256];
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
      /// Encodes exactly 'len' bytes from 'in' into '2*len' hex characters in 'out'.
      /// </summary>
      INLINE static void encode(const void* in, char* out, size_t len, bool reverse = false, bool writeterm = false)
      {
         uint16_t* out16 = (uint16_t*)out;
         if (reverse)
         {
            uint8_t* in8 = (uint8_t*)in + len;
            while (len--)
               *out16++ = Util::bytetohexint16(*--in8);
         }
         else
         {
            uint8_t* in8 = (uint8_t*)in;
            while (len--)
               *out16++ = Util::bytetohexint16(*in8++);
         }
         if (writeterm)
            *((uint8_t*)out16) = 0x00;
      }

      /// <summary>
      /// Encodes exactly 'len' bytes from 'in' into '2*len' hex characters in 'out'.
      /// </summary>
      template<typename STRING = std::string>
      INLINE static void encode(const void* in, STRING& out, size_t len, bool reverse = false, bool writeterm = false)
      {
         out.resize(len * 2U);
         Hex::encode(in, out.data(), len, reverse, writeterm);
      }

      /// <summary>
      /// Decodes exactly '2*len' characters from 'in' into 'len' bytes in 'out'.
      /// </summary>
      INLINE static void decode(const char* in, void* out, size_t len, bool reverse = false)
      {
         uint8_t* out8 = (uint8_t*)out;
         if (reverse)
         {
            in += len + len;
            while (len--)
            {
               char c2 = *--in;
               char c1 = *--in;
               *out8++ = 
                  (Util::valueofhexchar(c1) << 4) | 
                  (Util::valueofhexchar(c2));
            }
         }
         else
         {
            while (len--)
            {
               char c1 = *in++;
               char c2 = *in++;
               *out8++ = 
                  (Util::valueofhexchar(c1) << 4) | 
                  (Util::valueofhexchar(c2));
            }
         }
      }

      /// <summary>
      /// Parses unsigned integer 'out' from n hex characters in 'in'.
      /// Note that e.g. 0xFF1 is 0xFF01 (and neither 0x0FF1 nor 0xFF10) if 'in_be' is false.
      /// </summary>
      template<typename UINT>
      INLINE static void parse(const char* in, size_t n, UINT& out, const bool in_be = true, const bool out_le = CPPCORE_ENDIANESS_LITTLE)
      {
         CppCore::clear(out);
         uint8_t* p = (uint8_t*)&out;
         if (in_be)
         {
            in += n;
            if (n > sizeof(UINT)*2)
               n = sizeof(UINT)*2;
            if (out_le)
            {
               while (n >= 2)
               {
                  n -= 2;
                  char c2 = *--in;
                  char c1 = *--in;
                  *p++ =
                     (Util::valueofhexchar(c1) << 4) |
                     (Util::valueofhexchar(c2));
               }
               if (n)
                  *p++ = Util::valueofhexchar(*--in);
            }
            else
            {
               p += sizeof(UINT);
               while (n >= 2)
               {
                  n -= 2;
                  char c2 = *--in;
                  char c1 = *--in;
                  *--p =
                     (Util::valueofhexchar(c1) << 4) |
                     (Util::valueofhexchar(c2));
               }
               if (n)
                  *--p = Util::valueofhexchar(*--in);
            }
         }
         else
         {
            if (n > sizeof(UINT)*2)
               n = sizeof(UINT)*2;
            if (out_le)
            {
               while (n >= 2)
               {
                  n -= 2;
                  char c1 = *in++;
                  char c2 = *in++;
                  *p++ =
                     (Util::valueofhexchar(c1) << 4) |
                     (Util::valueofhexchar(c2));
               }
               if (n)
                  *p++ = Util::valueofhexchar(*in);
            }
            else
            {
               p += sizeof(UINT);
               while (n >= 2)
               {
                  n -= 2;
                  char c1 = *in++;
                  char c2 = *in++;
                  *--p =
                     (Util::valueofhexchar(c1) << 4) |
                     (Util::valueofhexchar(c2));
               }
               if (n)
                  *--p = Util::valueofhexchar(*in);
            }
         }
      }

      /// <summary>
      /// Determines C string length on-the-fly
      /// </summary>
      template<typename UINT>
      INLINE static void parse(const char* in, UINT& out, const bool in_be = true, const bool out_le = true)
      {
         CppCore::Hex::parse(in, ::strlen(in), out, in_be, out_le);
      }

      /// <summary>
      /// For C++ strings
      /// </summary>
      template<typename UINT, typename STRING>
      INLINE static void parse(const STRING& in, UINT& out, const bool in_be = true, const bool out_le = true)
      {
         CppCore::Hex::parse(in.data(), in.length(), out, in_be, out_le);
      }

      /// <summary>
      /// Tries to parse unsigned integer 'out' from n hex characters in 'in'.
      /// </summary>
      template<typename UINT>
      INLINE static bool tryparse(const char* in, size_t n, UINT& out, const bool in_be = true)
      {
         static_assert(CPPCORE_ENDIANESS_LITTLE);
         CppCore::clear(out);
         if (!in || *in == 0x00)
            return false;
         if (n > sizeof(UINT)*2)
            return false;
         uint8_t* p = (uint8_t*)&out;
         if (in_be)
         {
            in += n;
            while (n >= 2)
            {
               n -= 2;
               char c2 = *--in;
               char c1 = *--in;
               uint8_t v1 = Util::valueofhexchar(c1);
               uint8_t v2 = Util::valueofhexchar(c2);
               if (v1 > 0x0F || v2 > 0x0F)
                  return false;
               *p++ = (v1 << 4) | (v2);
            }
            if (n) {
               uint8_t v = Util::valueofhexchar(*--in);
               if (v > 0x0F)
                  return false;
               *p++ = v;
            }
         }
         else
         {
            while (n >= 2)
            {
               n -= 2;
               char c1 = *in++;
               char c2 = *in++;
               uint8_t v1 = Util::valueofhexchar(c1);
               uint8_t v2 = Util::valueofhexchar(c2);
               if (v1 > 0x0F || v2 > 0x0F)
                  return false;
               *p++ = (v1 << 4) | (v2);
            }
            if (n) {
               uint8_t v = Util::valueofhexchar(*in);
               if (v > 0x0F)
                  return false;
               *p++ = v;
            }
         }
         return true;
      }

      /// <summary>
      /// Determines C string length on-the-fly
      /// </summary>
      template<typename UINT>
      INLINE static bool tryparse(const char* in, UINT& out, const bool in_be = true)
      {
         return (in == 0) ? false : Hex::tryparse(in, ::strlen(in), out, in_be);
      }

      /// <summary>
      /// For C++ strings
      /// </summary>
      template<typename UINT, typename STRING>
      INLINE static bool tryparse(const STRING& in, UINT& out, const bool in_be = true)
      {
         return Hex::tryparse(in.data(), in.length(), out, in_be);
      }

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
         #if false
            return 9 * (c >> 6) + (c & 0xf);
         #else
            CPPCORE_ALIGN64 static constexpr uint8_t hexcharvalues[] =
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
            return hexcharvalues[c];
         #endif
         }

         /// <summary>
         /// Returns 2 characters encoded in uint16_t with the string representation of the byte argument.
         /// For instance, returns 0x3030 ("00") for 0x00 because '0' is 0x30 in ascii.
         /// </summary>
         INLINE static uint16_t bytetohexint16(const uint8_t byte)
         {
            CPPCORE_ALIGN64 static constexpr uint16_t table[] = 
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
            };
            return table[byte];
         }

         /// <summary>
         /// Template function for parsing unsigned integer from zero terminated hex string.
         /// Returns false if input is a null pointer or empty string or has invalid symbol or overflowed.
         /// For bigendian=true the first character must contain the highest bits.
         /// N must be the number of overflow free symbols for T (e.g. 8 for 32bit and 16 for 64bit).
         /// </summary>
         /*template<typename T, size_t N = sizeof(T) * 2>
         INLINE static bool tryparse(const char* input, T& r, const bool bigendian = true)
         {
            CppCore::clear(r);
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
                        if (!bigendian)
                           CppCore::byteswap(r);
                        return true;
                     }
                     else // invalid symbol
                        return false;
                  }
                  if (*input == 0) CPPCORE_LIKELY
                  {
                     if (!bigendian)
                        CppCore::byteswap(r);
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
         }*/
      };

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Creates hex string with exactly 2*sizeof(v) symbols in s.
      /// Requires 2*sizeof(v) (+1 if writeterm=true) free bytes in s.
      /// </summary>
      template<typename UINT>
      INLINE static void tostring(const UINT& v, char* s, const bool bigendian = true, const bool writeterm = true)
      {
         Hex::encode(&v, s, sizeof(UINT), bigendian == CPPCORE_ENDIANESS_LITTLE, writeterm);
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
               CppCore::udivmod(v, r, v, 10U);
               *s++ = CPPCORE_ALPHABET_B10[r];
               CPPCORE_UNROLL
               for (n = 1U; n != N; n++)
               {
                  if (!CppCore::testzero(v))
                  {
                     CppCore::udivmod(v, r, v, 10U);
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
               CppCore::udivmod(u, r, u, 10U);
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
                  CppCore::udivmod(u, r, u, 10U);
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
