#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Crypto
{
   /// <summary>
   /// 
   /// </summary>
   class HMAC
   {
   public:
      INLINE static bool md5test1()
      {
         uint8_t digest[16];
         uint8_t expect[] = {
            0xab,0x91,0xfb,0xfb,0x6c,0x6d,0x1e,0x3e,
            0x4a,0x98,0x3c,0xc6,0xf2,0x3f,0x26,0xdc
         };

         HMACMD5 hmac;
         hmac.reset("01234567890123456789012345678901234567890123456789012345678901234", 65);
         hmac.step("Test", 4);
         hmac.finish(&digest);

         if (::memcmp(digest, expect, 16) != 0)
            return false;

         return true;
      }

      INLINE static bool sha256test1()
      {
         uint8_t digest[32];
         uint8_t expect[] = {
           0x14,0x69,0xdd,0x3a,0xe2,0x90,0xb5,0x26,
           0x78,0xc8,0x20,0x83,0xcd,0x20,0x87,0xc9,
           0xef,0xd9,0xaa,0x0e,0x6e,0x24,0xae,0x4a,
           0xcc,0x34,0x0e,0x7a,0x8a,0x84,0xbc,0x8a
         };

         HMACSHA256 hmac;
         hmac.reset("01234567890123456789012345678901234567890123456789012345678901234", 65);
         hmac.step("Test", 4);
         hmac.finish(&digest);

         if (::memcmp(digest, expect, 32) != 0)
            return false;

         return true;
      }

      INLINE static bool sha512test1()
      {
         uint8_t digest[64];
         uint8_t expect[] = {
           0xdd,0xf3,0x13,0xf1,0x64,0x09,0x81,0x29,
           0xb3,0x66,0x70,0x3d,0xed,0xc0,0xb8,0x91,
           0x52,0xd3,0x1d,0xd1,0x32,0x03,0xd3,0x96,
           0x37,0xfd,0x00,0xaf,0x10,0xaa,0xb7,0xe0,
           0xbb,0x02,0xee,0xc0,0x6f,0xdf,0xb8,0x41,
           0xfe,0xc3,0x3e,0xe4,0xae,0x70,0x97,0xde,
           0x31,0x4f,0x29,0x1f,0xae,0x06,0x7d,0x6a,
           0xeb,0xee,0x23,0x25,0x46,0x77,0xbe,0xa3
         };

         HMACSHA512 hmac;
         hmac.reset("01234567890123456789012345678901234567890123456789012345678901234", 65);
         hmac.step("Test", 4);
         hmac.finish(&digest);

         if (::memcmp(digest, expect, 64) != 0)
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
   TEST_CLASS(HMAC)
   {
   public:
      TEST_METHOD(HMACMD5TEST1)    { Assert::AreEqual(true, CppCore::Test::Crypto::HMAC::md5test1()); }
      TEST_METHOD(HMACSHA256TEST1) { Assert::AreEqual(true, CppCore::Test::Crypto::HMAC::sha256test1()); }
      TEST_METHOD(HMACSHA512TEST1) { Assert::AreEqual(true, CppCore::Test::Crypto::HMAC::sha512test1()); }
   };
}}}}
#endif
