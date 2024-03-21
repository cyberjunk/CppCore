#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Crypto
{
   /// <summary>
   /// 
   /// </summary>
   class PBKDF2
   {
   public:
      INLINE static bool md5test1()
      {
         uint8_t digest[16];
         uint8_t expect[16] = {
            0x3b,0x3e,0x22,0xac,0x59,0x98,0x7a,0x43,
            0x9e,0x40,0x19,0xf9,0xda,0x8f,0x45,0x20
         };

         PBKDF2MD5 pbkdf2;
         pbkdf2.create("Test", 4, "Hello", 5, 1000, digest, sizeof(digest));

         if (::memcmp(digest, expect, 16) != 0)
            return false;

         return true;
      }

      INLINE static bool sha256test1()
      {
         uint8_t digest[32];
         uint8_t expect[32] = {
            0x71,0x5d,0xd1,0x12,0x87,0xaf,0x09,0x6f,
            0x13,0x76,0x9b,0xdc,0x6e,0x0d,0x7c,0x4e,
            0xa8,0x23,0x27,0xac,0xb6,0xa7,0x3b,0x8a,
            0xee,0xa3,0x66,0xf4,0x42,0xd3,0xce,0x84
         };

         PBKDF2SHA256 pbkdf2;
         pbkdf2.create("Test", 4, "Hello", 5, 1000, digest, sizeof(digest));

         if (::memcmp(digest, expect, 32) != 0)
            return false;

         return true;
      }

      INLINE static bool sha512test1()
      {
         uint8_t digest[64];
         uint8_t expect[64] = {
            0xbd,0x26,0xf3,0xe5,0xed,0xa0,0x3d,0x97,
            0x36,0x28,0x70,0x5e,0x5e,0x3c,0x8c,0x3c,
            0x5d,0x51,0xa5,0xe1,0x87,0x50,0x0a,0x31,
            0x43,0x62,0xc4,0xf1,0x38,0x9c,0x7f,0x82,
            0xad,0x46,0xa8,0x7a,0xdc,0x69,0xfe,0x46,
            0xcc,0x56,0x67,0x1a,0x40,0xd1,0xa9,0x4e,
            0xd7,0xbb,0x6a,0x35,0xcc,0x00,0x98,0xbf,
            0x4a,0x49,0x3d,0xb5,0x4f,0xd2,0xee,0xc1
         };

         PBKDF2SHA512 pbkdf2;
         pbkdf2.create("Test", 4, "Hello", 5, 1000, digest, sizeof(digest));

         if (::memcmp(digest, expect, 64) != 0)
            return false;

         return true;
      }

      INLINE static bool sha512test2()
      {
         uint8_t digest[67];
         uint8_t expect[67] = {
            0xda,0xa1,0x8c,0x6d,0xf3,0xd8,0x71,0x1e,
            0x1b,0x71,0xca,0x4e,0xcb,0x59,0x59,0xa6,
            0x9a,0xd0,0x4d,0xfa,0xf7,0xfb,0x2a,0x67,
            0x68,0x60,0xd8,0x43,0x5f,0xca,0x64,0x51,
            0x88,0xb3,0x13,0xf0,0xe0,0x24,0x81,0xba,
            0x0b,0xd0,0xf6,0x8b,0xf7,0x49,0xe4,0xc9,
            0x04,0xec,0xe0,0xb9,0x23,0xe8,0x3d,0x4a,
            0x19,0xee,0x39,0x58,0xb9,0x0b,0x72,0xd9,
            0xf5,0xf5,0x8a
         };

         PBKDF2SHA512 pbkdf2;
         pbkdf2.create("EHjwij3ht8zaDhj", 15, "eDjr4hje", 8, 1000, digest, sizeof(digest));

         if (::memcmp(digest, expect, 67) != 0)
            return false;

         return true;
      }

   };
}}}


#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Crypto {
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(PBKDF2)
   {
   public:
      TEST_METHOD(MD5TEST1)    { Assert::AreEqual(true, CppCore::Test::Crypto::PBKDF2::md5test1()); }
      TEST_METHOD(SHA256TEST1) { Assert::AreEqual(true, CppCore::Test::Crypto::PBKDF2::sha256test1()); }
      TEST_METHOD(SHA512TEST1) { Assert::AreEqual(true, CppCore::Test::Crypto::PBKDF2::sha512test1()); }
      TEST_METHOD(SHA512TEST2) { Assert::AreEqual(true, CppCore::Test::Crypto::PBKDF2::sha512test2()); }
   };
}}}}
#endif
