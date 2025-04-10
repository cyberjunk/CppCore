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
      /// Lookup Table from BINARY to HEX (uppercase)
      /// </summary>
      CPPCORE_ALIGN64 static constexpr uint16_t BIN2HEX_UPPERCASE[256] = {
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

      /// <summary>
      /// Lookup Table from BINARY to HEX (lowercase)
      /// </summary>
      CPPCORE_ALIGN64 static constexpr uint16_t BIN2HEX_LOWERCASE[256] = {
         0x3030, 0x3130, 0x3230, 0x3330, 0x3430, 0x3530, 0x3630, 0x3730,
         0x3830, 0x3930, 0x6130, 0x6230, 0x6330, 0x6430, 0x6530, 0x6630,
         0x3031, 0x3131, 0x3231, 0x3331, 0x3431, 0x3531, 0x3631, 0x3731,
         0x3831, 0x3931, 0x6131, 0x6231, 0x6331, 0x6431, 0x6531, 0x6631,
         0x3032, 0x3132, 0x3232, 0x3332, 0x3432, 0x3532, 0x3632, 0x3732,
         0x3832, 0x3932, 0x6132, 0x6232, 0x6332, 0x6432, 0x6532, 0x6632,
         0x3033, 0x3133, 0x3233, 0x3333, 0x3433, 0x3533, 0x3633, 0x3733,
         0x3833, 0x3933, 0x6133, 0x6233, 0x6333, 0x6433, 0x6533, 0x6633,
         0x3034, 0x3134, 0x3234, 0x3334, 0x3434, 0x3534, 0x3634, 0x3734,
         0x3834, 0x3934, 0x6134, 0x6234, 0x6334, 0x6434, 0x6534, 0x6634,
         0x3035, 0x3135, 0x3235, 0x3335, 0x3435, 0x3535, 0x3635, 0x3735,
         0x3835, 0x3935, 0x6135, 0x6235, 0x6335, 0x6435, 0x6535, 0x6635,
         0x3036, 0x3136, 0x3236, 0x3336, 0x3436, 0x3536, 0x3636, 0x3736,
         0x3836, 0x3936, 0x6136, 0x6236, 0x6336, 0x6436, 0x6536, 0x6636,
         0x3037, 0x3137, 0x3237, 0x3337, 0x3437, 0x3537, 0x3637, 0x3737,
         0x3837, 0x3937, 0x6137, 0x6237, 0x6337, 0x6437, 0x6537, 0x6637,
         0x3038, 0x3138, 0x3238, 0x3338, 0x3438, 0x3538, 0x3638, 0x3738,
         0x3838, 0x3938, 0x6138, 0x6238, 0x6338, 0x6438, 0x6538, 0x6638,
         0x3039, 0x3139, 0x3239, 0x3339, 0x3439, 0x3539, 0x3639, 0x3739,
         0x3839, 0x3939, 0x6139, 0x6239, 0x6339, 0x6439, 0x6539, 0x6639,
         0x3061, 0x3161, 0x3261, 0x3361, 0x3461, 0x3561, 0x3661, 0x3761,
         0x3861, 0x3961, 0x6161, 0x6261, 0x6361, 0x6461, 0x6561, 0x6661,
         0x3062, 0x3162, 0x3262, 0x3362, 0x3462, 0x3562, 0x3662, 0x3762,
         0x3862, 0x3962, 0x6162, 0x6262, 0x6362, 0x6462, 0x6562, 0x6662,
         0x3063, 0x3163, 0x3263, 0x3363, 0x3463, 0x3563, 0x3663, 0x3763,
         0x3863, 0x3963, 0x6163, 0x6263, 0x6363, 0x6463, 0x6563, 0x6663,
         0x3064, 0x3164, 0x3264, 0x3364, 0x3464, 0x3564, 0x3664, 0x3764,
         0x3864, 0x3964, 0x6164, 0x6264, 0x6364, 0x6464, 0x6564, 0x6664,
         0x3065, 0x3165, 0x3265, 0x3365, 0x3465, 0x3565, 0x3665, 0x3765,
         0x3865, 0x3965, 0x6165, 0x6265, 0x6365, 0x6465, 0x6565, 0x6665,
         0x3066, 0x3166, 0x3266, 0x3366, 0x3466, 0x3566, 0x3666, 0x3766,
         0x3866, 0x3966, 0x6166, 0x6266, 0x6366, 0x6466, 0x6566, 0x6666
      };

      /// <summary>
      /// Lookup Table from HEX to BINARY
      /// </summary>
      CPPCORE_ALIGN64 static constexpr uint8_t HEX2BIN[256] = {
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

      /// <summary>
      /// Encodes exactly 'len' bytes from 'in' into '2*len' hex characters in 'out'.
      /// This contains the actual algorithm and is base function for all the other variants.
      /// </summary>
      FORCEINLINE static void encode(const void* in, char* out, size_t len, bool reverse = false, bool writeterm = false, bool uppercase = true)
      {
         const uint16_t* TABLE = uppercase ?
            Hex::BIN2HEX_UPPERCASE :
            Hex::BIN2HEX_LOWERCASE;
         uint8_t* out8 = (uint8_t*)out;
         uint8_t* in8  = reverse ? (uint8_t*)in+len : (uint8_t*)in;
         size_t   inc, dec;
      #if defined(CPPCORE_CPUFEAT_SSSE3)
         if (len >= 8U)
         {
            dec = reverse ? 8 : 0;
            inc = reverse ? 0 : 8;
            const __m128i SHUF = reverse ?
               _mm_setr_epi8(7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0) :
               _mm_set_epi8 (7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0);
            const __m128i M1 = _mm_set_epi8(
               0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00,
               0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00);
            const __m128i M2 = _mm_srli_si128(M1, 1);
            const __m128i CMP = _mm_set1_epi8(0x0A);
            const __m128i ADD_NUM = _mm_set1_epi8('0');
            const __m128i ADD_ALP = uppercase ?
               _mm_set1_epi8('A'-10) :
               _mm_set1_epi8('a'-10);
            do
            {
               __m128i val;
               in8 -= dec;
               val = _mm_loadu_si64(in8);
               val = _mm_shuffle_epi8(val, SHUF);
               val = _mm_or_si128(
                  _mm_and_si128(val, M1),
                  _mm_and_si128(_mm_srli_epi64(val, 4), M2));
               const __m128i clt = _mm_cmplt_epi8(val, CMP);
               const __m128i add = _mm_or_si128(
                  _mm_and_si128(ADD_NUM, clt),
                  _mm_andnot_si128(clt, ADD_ALP));
               _mm_storeu_si128((__m128i*)out8, _mm_add_epi8(val, add));
               out8 += 16U;
               in8  += inc;
               len  -= 8U;
            } while (len >= 8U);
         }
      #endif
         dec = reverse ? 1 : 0;
         inc = reverse ? 0 : 1;
         while (len--) 
         {
            in8  -= dec;
            *(uint16_t*)out8 = TABLE[*in8];
            in8  += inc;
            out8 += 2U;
         }
         if (writeterm)
            *out8 = 0x00;
      }

      template<typename STRING = std::string>
      INLINE static void encode(const void* in, STRING& out, size_t len, bool reverse = false, bool writeterm = false, bool uppercase = true)
      {
         out.resize(len * 2U);
         Hex::encode(in, out.data(), len, reverse, writeterm, uppercase);
      }

      /// <summary>
      /// Decodes 'len' characters from 'in' into len/2 (+1 if odd) bytes in 'out'.
      /// This contains the actual algorithm and is base function for all the other variants.
      /// </summary>
      FORCEINLINE static bool decode(const char* in, void* out, size_t len, bool reverse = false)
      {
         if (len == 0)
            return false;
         uint8_t* p = (uint8_t*)out;
         size_t inc, dec;
         in  = reverse ? in+len : in;
      #if defined(CPPCORE_CPUFEAT_SSSE3)
         if (len >= 16)
         {
            dec = reverse ? 16 : 0;
            inc = reverse ? 0 : 16;
            const __m128i SHUF1 = reverse ? 
               _mm_setr_epi8(14,12,10,8,6,4,2,0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80) :
               _mm_setr_epi8(0,2,4,6,8,10,12,14,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80);
            const __m128i SHUF2 = reverse ?
               _mm_setr_epi8(15,13,11,9,7,5,3,1,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80) :
               _mm_setr_epi8(1,3,5,7,9,11,13,15,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80);
            const __m128i CMP1_MIN = _mm_set1_epi8('0'-1); // ge 0
            const __m128i CMP1_MAX = _mm_set1_epi8('9'+1); // le 9
            const __m128i CMP1_SUB = _mm_set1_epi8('0');
            const __m128i CMP2_MIN = _mm_set1_epi8('A'-1); // ge A
            const __m128i CMP2_MAX = _mm_set1_epi8('F'+1); // le F
            const __m128i CMP2_SUB = _mm_set1_epi8('A'-10);
            const __m128i CMP3_MIN = _mm_set1_epi8('a'-1); // ge a
            const __m128i CMP3_MAX = _mm_set1_epi8('f'+1); // le f
            const __m128i CMP3_SUB = _mm_set1_epi8('a'-10);
            __m128i err = _mm_setzero_si128();
            __m128i val, sub;
            do
            {
               in -= dec;
               val = _mm_loadu_si128((__m128i*)in);
               sub = _mm_and_si128(CMP1_SUB, _mm_and_si128(
                  _mm_cmpgt_epi8(val, CMP1_MIN),
                  _mm_cmplt_epi8(val, CMP1_MAX)));
               sub = _mm_or_si128(sub, _mm_and_si128(CMP2_SUB, _mm_and_si128(
                  _mm_cmpgt_epi8(val, CMP2_MIN),
                  _mm_cmplt_epi8(val, CMP2_MAX))));
               sub = _mm_or_si128(sub, _mm_and_si128(CMP3_SUB, _mm_and_si128(
                  _mm_cmpgt_epi8(val, CMP3_MIN),
                  _mm_cmplt_epi8(val, CMP3_MAX))));
               err = _mm_or_si128(err, _mm_cmpeq_epi8(sub, _mm_setzero_si128()));
               val = _mm_sub_epi8(val, sub);
               val = _mm_or_si128(
                  _mm_slli_epi64(_mm_shuffle_epi8(val, SHUF1), 4),
                  _mm_shuffle_epi8(val, SHUF2));
               _mm_storeu_si64(p, val);
               p   += 8;
               in  += inc;
               len -= 16;
            } while (len >= 16);
         #if defined(CPPCORE_CPUFEAT_SSE41)
            if (_mm_testz_si128(err, err) == 0)
               return false;
         #else
            if (_mm_movemask_epi8(err) != 0)
               return false;
         #endif
         }
      #endif
         uint8_t  r = 0x00;
         uint8_t v1, v2;
         dec = reverse ? 2 : 0;
         inc = reverse ? 0 : 2;
         while (len >= 2)
         {
            len -= 2;
            in -= dec;
            v1 = Hex::HEX2BIN[(uint8_t)in[0]];
            v2 = Hex::HEX2BIN[(uint8_t)in[1]];
            r |= v1 | v2;
            *p++ = (v1 << 4) | (v2);
            in += inc;
         }
         if (len) {
            v1 = Hex::HEX2BIN[(uint8_t)(reverse ? *--in : *in)];
            r |= v1;
            *p = v1;
         }
         return r <= 0x0F;
      }

      /// <summary>
      /// Tries to parse unsigned integer 'out' from n hex characters in 'in'.
      /// </summary>
      template<typename UINT>
      INLINE static bool tryparse(const char* in, size_t n, UINT& out, const bool in_be = true)
      {
         static_assert(CPPCORE_ENDIANESS_LITTLE);
         CppCore::clear(out);
         if (n > sizeof(UINT)*2) CPPCORE_UNLIKELY
            return false;
         return Hex::decode(in, &out, n, in_be);
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
      /// Creates hex string with exactly 2*sizeof(v) symbols in s.
      /// Requires 2*sizeof(v) (+1 if writeterm=true) free bytes in s.
      /// </summary>
      template<typename UINT>
      INLINE static void tostring(const UINT& v, char* s, const bool bigendian = true, const bool writeterm = true, bool uppercase = true)
      {
         Hex::encode(&v, s, sizeof(UINT), bigendian == CPPCORE_ENDIANESS_LITTLE, writeterm, uppercase);
      }
   };

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // BASE64
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Base64 Encoding
   /// </summary>
   class Base64
   {
   private:
      INLINE Base64() { }
   public:
      /// <summary>
      /// Lookup Table from B64 SYMBOL to BINARY
      /// </summary>
      CPPCORE_ALIGN64 static constexpr uint8_t B64TOBIN_STD[256] = {
         0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3e, 0xFF, 0xFF, 0xFF, 0x3f,
         0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
         0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
         0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
      };

      /// <summary>
      /// Lookup Table from B64 URL SYMBOL to BINARY
      /// </summary>
      CPPCORE_ALIGN64 static constexpr uint8_t B64TOBIN_URL[256] = {
         0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3e, 0xFF, 0xFF,
         0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
         0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0x3f,
         0xFF, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
         0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
      };

      /// <summary>
      /// Lookup Table from BINARY to B64 SYMBOL
      /// </summary>
      CPPCORE_ALIGN64 static constexpr char BINTOB64_STD[64] = {
         'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
         'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
         'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
      };

      /// <summary>
      /// Lookup Table from BINARY to B64 URL SYMBOL
      /// </summary>
      CPPCORE_ALIGN64 static constexpr char BINTOB64_URL[64] = {
         'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
         'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
         'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'
      };

      /// <summary>
      /// Returns the number of bytes needed to store symbols.
      /// Returns 0 if len%4!=0 (url=false) or len%4=1 (url=true).
      /// </summary>
      INLINE static size_t bytelength(const char* s, size_t len, bool url = false)
      {
         size_t full = (len >> 2U) * 3U;
         size_t tail = (len & 0x03U);
         if (url)
         {
            return
               (tail == 0U)  ? (full) : 
               (tail & 0x02U ? (full + (tail-1U)) : 0U);
         }
         else
         {
            if ((len == 0U) | (tail != 0U))
               return 0U;
            size_t t = len;
            if (s[len-1] == '=') len--;
            if (s[len-1] == '=') len--;
            return full - (t-len);
         }
      }

      /// <summary>
      /// Returns the number of symbols needed to store bytes.
      /// </summary>
      INLINE static size_t symbollength(size_t bytes, bool url = false)
      {
         size_t full = (bytes / 3U) * 4U;
         size_t tail = (bytes % 3U);
         return full + (tail ? (url ? tail + 1 : 4U) : 0U);
      }

      /// <summary>
      /// Encodes 'len' bytes from 'in' into 'out'.
      /// Use Base64::symbollength() to pre-calculate the number of symbols written to 'out'.
      /// This contains the actual algorithm and is base function for all the other variants.
      /// </summary>
      FORCEINLINE static void encode(const void* in, size_t len, char* out, bool url = false, bool writeterm = true)
      {
         static_assert(CPPCORE_ENDIANESS_LITTLE);
         const char* tbl = url ?
            Base64::BINTOB64_URL :
            Base64::BINTOB64_STD;
         const uint8_t* p = (const uint8_t*)in;
      #if defined(CPPCORE_CPUFEAT_SSSE3)
         if (len >= 32U)
         {
            // 16 symbols from 12 bytes
            // adapted from: https://github.com/WojciechMula/base64simd
            // only if reasonable large due to overhead for loading masks to sse registers
            const __m128i SHUF1 = _mm_set_epi8(
               10, 11, 9, 10, 7,  8, 6,  7, 4,  5, 3,  4, 1,  2, 0,  1
            );
            const __m128i SHUF2_URL = _mm_setr_epi8(
               'a' - 26, '0' - 52, '0' - 52, '0' - 52, '0' - 52, '0' - 52,
               '0' - 52, '0' - 52, '0' - 52, '0' - 52, '0' - 52, '-' - 62,
               '_' - 63, 'A', 0, 0);
            const __m128i SHUF2_STD = _mm_setr_epi8(
               'a' - 26, '0' - 52, '0' - 52, '0' - 52, '0' - 52, '0' - 52,
               '0' - 52, '0' - 52, '0' - 52, '0' - 52, '0' - 52, '+' - 62,
               '/' - 63, 'A', 0, 0);
            const __m128i SHUF2 = url ? SHUF2_URL : SHUF2_STD;
            const __m128i M1 = _mm_set1_epi32(0x0fc0fc00);
            const __m128i M2 = _mm_set1_epi32(0x04000040);
            const __m128i M3 = _mm_set1_epi32(0x003f03f0);
            const __m128i M4 = _mm_set1_epi32(0x01000010);
            const __m128i M5 = _mm_set1_epi8(51);
            const __m128i M6 = _mm_set1_epi8(26);
            const __m128i M7 = _mm_set1_epi8(13);
            do
            {
               __m128i t, r;
               t = _mm_loadu_si128((const __m128i*)p);
               t = _mm_shuffle_epi8(t, SHUF1);
               t = _mm_or_si128(
                 _mm_mulhi_epu16(_mm_and_si128(t, M1), M2),
                 _mm_mullo_epi16(_mm_and_si128(t, M3), M4));
               r = _mm_subs_epu8(t, M5);
               r = _mm_or_si128(r, _mm_and_si128(_mm_cmpgt_epi8(M6, t), M7));
               r = _mm_shuffle_epi8(SHUF2, r);
               r = _mm_add_epi8(r, t);
               _mm_storeu_si128((__m128i*)out, r);
               p   += 12;
               len -= 12;
               out += 16;
            } while (len >= 16U);
         }
      #endif
         while (len >= 6U)
         {
            // 8 symbols from 6 bytes
            uint32_t v = CppCore::loadr32((uint32_t*)p);
         #if defined(CPPCORE_CPUFEAT_BMI1)
            uint32_t s1 = _bextr_u32(v, 26, 6);
            uint32_t s2 = _bextr_u32(v, 20, 6);
            uint32_t s3 = _bextr_u32(v, 14, 6);
            uint32_t s4 = _bextr_u32(v,  8, 6);
         #else
            uint32_t s1 = (v >> 26);
            uint32_t s2 = (v >> 20) & 0x3F;
            uint32_t s3 = (v >> 14) & 0x3F;
            uint32_t s4 = (v >>  8) & 0x3F;
         #endif
            *out++ = tbl[s1];
            *out++ = tbl[s2];
            *out++ = tbl[s3];
            *out++ = tbl[s4];
            p += 4;
            v = CppCore::shrd32(CppCore::byteswap32(*(uint16_t*)p), v, 8U);
         #if defined(CPPCORE_CPUFEAT_BMI1)
            s1 = _bextr_u32(v, 26, 6);
            s2 = _bextr_u32(v, 20, 6);
            s3 = _bextr_u32(v, 14, 6);
            s4 = _bextr_u32(v,  8, 6);
         #else
            s1 = (v >> 26);
            s2 = (v >> 20) & 0x3F;
            s3 = (v >> 14) & 0x3F;
            s4 = (v >>  8) & 0x3F;
         #endif
            *out++ = tbl[s1];
            *out++ = tbl[s2];
            *out++ = tbl[s3];
            *out++ = tbl[s4];
            p += 2U;
            len -= 6U;
         }
         if (len >= 3U)
         {
            // 4 symbols from 3 bytes
         #if true // others may overread 1 byte
            uint8_t s1 = ((p[0] >> 2));
            uint8_t s2 = ((p[0] & 0x03) << 4) | (p[1] >> 4);
            uint8_t s3 = ((p[1] & 0x0F) << 2) | (p[2] >> 6);
            uint8_t s4 = ((p[2] & 0x3F));
         #elif defined(CPPCORE_CPUFEAT_BMI1)
            uint32_t v  = CppCore::loadr32((uint32_t*)p);
            uint32_t s1 = _bextr_u32(v, 26, 6);
            uint32_t s2 = _bextr_u32(v, 20, 6);
            uint32_t s3 = _bextr_u32(v, 14, 6);
            uint32_t s4 = _bextr_u32(v,  8, 6);
         #else
            uint32_t v  = CppCore::loadr32((uint32_t*)p);
            uint32_t s1 = (v >> 26);
            uint32_t s2 = (v >> 20) & 0x3F;
            uint32_t s3 = (v >> 14) & 0x3F;
            uint32_t s4 = (v >>  8) & 0x3F;
         #endif
            *out++ = tbl[s1];
            *out++ = tbl[s2];
            *out++ = tbl[s3];
            *out++ = tbl[s4];
            len -= 3U;
            p += 3U;
         }
         if (len == 2U)
         {
            // 3 symbols from 2 bytes (+1 padding symbols)
         #if true // other ok but not worth
            uint8_t s1 = ((p[0] >> 2));
            uint8_t s2 = ((p[0] & 0x03) << 4) | (p[1] >> 4);
            uint8_t s3 = ((p[1] & 0x0F) << 2);
         #else
            uint16_t v  = CppCore::loadr16((uint16_t*)p);
            uint16_t s1 = (v >> 10);
            uint16_t s2 = (v >>  4) & 0x3F;
            uint16_t s3 = (v <<  2) & 0x3C;
         #endif
            *out++ = tbl[s1];
            *out++ = tbl[s2];
            *out++ = tbl[s3];
            if (!url)
               *out++ = '=';
         }
         else if (len)
         {
            // 2 symbols from 1 byte (+2 padding symbols)
            uint8_t s1 = (p[0] >> 2);
            uint8_t s2 = (p[0] << 4) & 0x30;
            *out++ = tbl[s1];
            *out++ = tbl[s2];
            if (!url) {
               *out++ = '=';
               *out++ = '=';
            }
         }
         if (writeterm)
            *out = 0x00;
      }

      INLINE static void encode(const char* in, char* out, bool url = false, bool writeterm = true)
      {
         Base64::encode(in, ::strlen(in), out, url, writeterm);
      }

      INLINE static void encode(const std::string& in, char* out, bool url = false, bool writeterm = true)
      {
         Base64::encode(in.c_str(), in.length(), out, url, writeterm);
      }

      INLINE static void encode(const std::string_view& in, char* out, bool url = false, bool writeterm = true)
      {
         Base64::encode(in.data(), in.length(), out, url, writeterm);
      }

      INLINE static void encode(const void* in, size_t len, std::string& out, bool url = false, bool writeterm = true)
      {
         out.resize(Base64::symbollength(len, url));
         Base64::encode(in, len, out.data(), url, writeterm);
      }

      INLINE static void encode(const char* in, std::string& out, bool url = false, bool writeterm = true)
      {
         Base64::encode(in, ::strlen(in), out, url, writeterm);
      }

      INLINE static void encode(const std::string& in, std::string& out, bool url = false, bool writeterm = true)
      {
         Base64::encode(in.c_str(), in.length(), out, url, writeterm);
      }

      INLINE static void encode(const std::string_view& in, std::string& out, bool url = false, bool writeterm = true)
      {
         Base64::encode(in.data(), in.length(), out, url, writeterm);
      }

      template<typename T>
      INLINE static void encode(const T& in, char* out, bool url = false, bool writeterm = true)
      {
         Base64::encode(&in, sizeof(T), out, url, writeterm);
      }

      template<typename T>
      INLINE static void encode(const T& in, std::string& out, bool url = false, bool writeterm = true)
      {
         Base64::encode(&in, sizeof(T), out, url, writeterm);
      }

      INLINE static bool encode(istream& in, ostream& out, bool url = false, bool writeterm = false)
      {
         CPPCORE_ALIGN64 char bin [4096];      // binary
         CPPCORE_ALIGN64 char bout[4096+2048]; // base64 (must be at least 33% larger)
         size_t tail = 0;
         size_t diff;
         size_t read;
         in.clear();
         in.seekg(0, in.beg);
         while (in.good())
         {
            in.read(bin+tail, sizeof(bin)-tail);
            read = in.gcount() + tail;
            tail = read % 3U;
            diff = read - tail;
            CppCore::Base64::encode(bin, diff, bout, url, false);
            out.write(bout, CppCore::Base64::symbollength(diff, url));
            if (tail == 1)
            {
               bin[0] = bin[read-1];
            }
            else if (tail == 2)
            {
               bin[0] = bin[read-2];
               bin[1] = bin[read-1];
            }
         }
         if (tail) {
            CppCore::Base64::encode(bin, tail, bout, url, false);
            out.write(bout, CppCore::Base64::symbollength(tail, url));
         }
         if (writeterm)
            out << '\0';
         return true;
      }

      INLINE static bool encode(const path& in, ostream& out, bool url = false, bool writeterm = false)
      {
         ifstream stream(in, ifstream::binary | ifstream::in);
         if (!stream.is_open())
            return false;
         return Base64::encode(stream, out, url, writeterm);
      }

      INLINE static bool encode(istream& in, const path& out, bool url = false, bool writeterm = false)
      {
         ofstream stream(out, ifstream::binary | ifstream::out);
         if (!stream.is_open())
            return false;
         return Base64::encode(in, stream, url, writeterm);
      }

      INLINE static bool encode(const path& in, const path& out, bool url = false, bool writeterm = false)
      {
         ifstream sin(in, ifstream::binary | ifstream::in);
         if (!sin.is_open())
            return false;
         ofstream sout(out, ofstream::binary | ofstream::out);
         if (!sout.is_open())
            return false;
         return Base64::encode(sin, sout, url, writeterm);
      }

      /// <summary>
      /// Tries to decode 'len' base64 symbols from 'in' into 'out'.
      /// Use Base64::bytelength() to pre-calculate the number of bytes written to 'out'.
      /// This contains the actual algorithm and is base function for all the other variants.
      /// </summary>
      FORCEINLINE static bool decode(const char* in, size_t len, void* out, bool url = false)
      {
         if (len == 0) CPPCORE_UNLIKELY
            return false;
         size_t tail = (len & 0x03);
         if (url)
         {
            if (tail == 1U)
               return false;
         }
         else
         {
            if (tail) return false;
            if (in[len-1] == '=') len--;
            if (in[len-1] == '=') len--;
         }
         uint8_t* p = (uint8_t*)out;
         uint32_t r = 0;
         uint32_t v;
         const uint8_t* tbl = url ? 
            Base64::B64TOBIN_URL : 
            Base64::B64TOBIN_STD;
      #if defined(CPPCORE_CPUFEAT_SSSE3)
         if (len >= 32U)
         {
            // 12 bytes from 16 symbols
            // adapted from: https://github.com/WojciechMula/base64simd
            // only if reasonable large due to overhead for loading masks to sse registers
            const __m128i CMP_GT_A = _mm_set1_epi8('A'-1);
            const __m128i CMP_LT_Z = _mm_set1_epi8('Z'+1);
            const __m128i CMP_GT_a = _mm_set1_epi8('a'-1);
            const __m128i CMP_LT_z = _mm_set1_epi8('z'+1);
            const __m128i CMP_GT_0 = _mm_set1_epi8('0'-1);
            const __m128i CMP_LT_9 = _mm_set1_epi8('9'+1);
            const __m128i CMP_E_C1 = url ? _mm_set1_epi8('-') : _mm_set1_epi8('+');
            const __m128i CMP_E_C2 = url ? _mm_set1_epi8('_') : _mm_set1_epi8('/');
            const __m128i M1 = _mm_set1_epi8(-65);
            const __m128i M2 = _mm_set1_epi8(-71);
            const __m128i M3 = _mm_set1_epi8(4);
            const __m128i M4 = url ? _mm_set1_epi8(17)  : _mm_set1_epi8(19);
            const __m128i M5 = url ? _mm_set1_epi8(-32) : _mm_set1_epi8(16);
            const __m128i M6 = _mm_set1_epi32(0x01400140);
            const __m128i M7 = _mm_set1_epi32(0x00011000);
            const __m128i SHUF = _mm_setr_epi8(
               2,  1,  0,  6,  5,  4,
              10,  9,  8, 14, 13, 12,
              -1, -1, -1, -1);
            __m128i e = _mm_setzero_si128();
            do
            {
               __m128i v = _mm_loadu_si128((__m128i*)in);
               const __m128i ge_A  = _mm_cmpgt_epi8(v, CMP_GT_A);
               const __m128i le_Z  = _mm_cmplt_epi8(v, CMP_LT_Z);
               const __m128i r_AZ  = _mm_and_si128(M1, _mm_and_si128(ge_A, le_Z));
               const __m128i ge_a  = _mm_cmpgt_epi8(v, CMP_GT_a);
               const __m128i le_z  = _mm_cmplt_epi8(v, CMP_LT_z);
               const __m128i r_az  = _mm_and_si128(M2, _mm_and_si128(ge_a, le_z));
               const __m128i ge_0  = _mm_cmpgt_epi8(v, CMP_GT_0);
               const __m128i le_9  = _mm_cmplt_epi8(v, CMP_LT_9);
               const __m128i r_09  = _mm_and_si128(M3, _mm_and_si128(ge_0, le_9));
               const __m128i e_c1  = _mm_cmpeq_epi8(v, CMP_E_C1);
               const __m128i r_c1  = _mm_and_si128(M4, e_c1);
               const __m128i e_c2  = _mm_cmpeq_epi8(v, CMP_E_C2);
               const __m128i r_c2  = _mm_and_si128(M5, e_c2);
               const __m128i shift =
                 _mm_or_si128(r_AZ,
                 _mm_or_si128(r_az,
                 _mm_or_si128(r_09,
                 _mm_or_si128(r_c1, r_c2))));
               e = _mm_or_si128(e, _mm_cmpeq_epi8(shift, _mm_setzero_si128()));
               v = _mm_add_epi8(v, shift);
               v = _mm_maddubs_epi16(v, M6);
               v = _mm_madd_epi16(v, M7);
               v = _mm_shuffle_epi8(v, SHUF);
               _mm_storeu_si64((__m128i*)(p), v);
               _mm_storeu_si32((__m128i*)(p+8U), _mm_castps_si128(_mm_movehl_ps(
                  _mm_castsi128_ps(v), _mm_castsi128_ps(v))));
               p   += 12;
               len -= 16;
               in  += 16;
            } while (len >= 16);
         #if defined(CPPCORE_CPUFEAT_SSE41)
            if (_mm_testz_si128(e, e) == 0)
               return false;
         #else
            if (_mm_movemask_epi8(e) != 0)
               return false;
         #endif
         }
      #endif
         while (len >= 4)
         {
            // 3 bytes from 4 symbols
            uint32_t s1 = tbl[(uint8_t)*in++];
            uint32_t s2 = tbl[(uint8_t)*in++];
            uint32_t s3 = tbl[(uint8_t)*in++];
            uint32_t s4 = tbl[(uint8_t)*in++];
            v = (s1 << 18) | (s2 << 12) | (s3 << 6) | s4;
            r |= s1 | s2 | s3 | s4;
            *p++ = (uint8_t)(v >> 16);
            *p++ = (uint8_t)(v >> 8);
            *p++ = (uint8_t)(v);
            len -= 4;
         }
         if (len == 3)
         {
            // 2 bytes from 3 symbols
            uint32_t s1 = tbl[(uint8_t)*in++];
            uint32_t s2 = tbl[(uint8_t)*in++];
            uint32_t s3 = tbl[(uint8_t)*in++];
            v = (s1 << 18) | (s2 << 12) | (s3 << 6);
            r |= s1 | s2 | s3;
            *p++ = (uint8_t)(v >> 16);
            *p++ = (uint8_t)(v >> 8);
         }
         else if (len == 2)
         {
            // 1 byte from 2 symbols
            uint32_t s1 = tbl[(uint8_t)*in++];
            uint32_t s2 = tbl[(uint8_t)*in++];
            v = (s1 << 18) | (s2 << 12);
            r |= s1 | s2;
            *p++ = (uint8_t)(v >> 16);
         }
         return r <= 0x3F;
      }

      INLINE static bool decode(const char* in, void* out, bool url = false)
      {
         return Base64::decode(in, ::strlen(in), out, url);
      }

      INLINE static bool decode(const std::string& in, void* out, bool url = false)
      {
         return Base64::decode(in.c_str(), in.length(), out, url);
      }

      INLINE static bool decode(const std::string_view& in, void* out, bool url = false)
      {
         return Base64::decode(in.data(), in.length(), out, url);
      }

      INLINE static bool decode(const char* in, size_t len, std::string& out, bool url = false)
      {
         out.resize(Base64::bytelength(in, len, url));
         return Base64::decode(in, len, out.data(), url);
      }
      
      INLINE static bool decode(const char* in, std::string& out, bool url = false)
      {
         return Base64::decode(in, ::strlen(in), out, url);
      }
      
      INLINE static bool decode(const std::string& in, std::string& out, bool url = false)
      {
         return Base64::decode(in.c_str(), in.length(), out, url);
      }
      
      INLINE static bool decode(const std::string_view& in, std::string& out, bool url = false)
      {
         return Base64::decode(in.data(), in.length(), out, url);
      }

      template<typename T>
      INLINE static bool decode(const char* in, size_t len, T& out, bool url = false, bool clear = true)
      {
         const auto BLEN = Base64::bytelength(in, len, url);
         if (BLEN > sizeof(T)) 
            return false;
         if (clear && BLEN < sizeof(T))
            CppCore::clear(out);
         return Base64::decode(in, len, &out, url);
      }

      template<typename T>
      INLINE static bool decode(const char* in, T& out, bool url = false, bool clear = true)
      {
         return Base64::decode<T>(in, ::strlen(in), out, url, clear);
      }

      template<typename T>
      INLINE static bool decode(const std::string& in, T& out, bool url = false, bool clear = true)
      {
         return Base64::decode<T>(in.c_str(), in.length(), out, url, clear);
      }
      
      template<typename T>
      INLINE static bool decode(const std::string_view& in, T& out, bool url = false, bool clear = true)
      {
         return Base64::decode<T>(in.data(), in.length(), out, url, clear);
      }

      INLINE static bool decode(istream& in, ostream& out, bool url = false)
      {
         CPPCORE_ALIGN64 char bin [4096]; // base64
         CPPCORE_ALIGN64 char bout[4096]; // binary
         in.clear();
         in.seekg(0, in.beg);
         while (in.good())
         {
            in.read(bin, sizeof(bin));
            size_t read = in.gcount();
            if (!CppCore::Base64::decode(bin, read, (void*)bout, url))
               return false;
            out.write(bout, CppCore::Base64::bytelength(bin, read, url));
         }
         return true;
      }

      INLINE static bool decode(const path& in, ostream& out, bool url = false)
      {
         ifstream stream(in, ifstream::binary | ifstream::in);
         if (!stream.is_open())
            return false;
         return Base64::decode(stream, out, url);
      }

      INLINE static bool decode(istream& in, const path& out, bool url = false)
      {
         ofstream stream(out, ifstream::binary | ifstream::out);
         if (!stream.is_open())
            return false;
         return Base64::decode(in, stream, url);
      }

      INLINE static bool decode(const path& in, const path& out, bool url = false)
      {
         ifstream sin(in, ifstream::binary | ifstream::in);
         if (!sin.is_open())
            return false;
         ofstream sout(out, ofstream::binary | ofstream::out);
         if (!sout.is_open())
            return false;
         return Base64::decode(sin, sout, url);
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
