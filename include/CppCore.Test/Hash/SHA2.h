#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Hash
{
   /// <summary>
   /// Tests for SHA2.h in CppCore::Hash
   /// </summary>
   class SHA2
   {
   public:
      template<typename SHA>
      INLINE static bool sha256()
      {
         typename SHA::Digest digest;
         uint8_t expect[32] = { 
            0xa9,0xe8,0x91,0x3b,0x13,0x86,0x40,0x96,
            0xb9,0xea,0x59,0x2f,0x95,0x48,0xc8,0x76,
            0x54,0xaa,0xf8,0xdf,0x24,0xe3,0x43,0x76,
            0x45,0xfa,0xc1,0x74,0xd1,0x03,0x6e,0x1c
         };

         SHA sha;
         sha.step(SHA::PADDING, sizeof(SHA::PADDING));
         sha.finish(digest);
         if (memcmp(&digest, expect, sizeof(expect)) != 0)
            return false;

         SHA::hashMem(SHA::PADDING, sizeof(SHA::PADDING), digest);
         if (memcmp(&digest, expect, sizeof(expect)) != 0)
            return false;

         return true;
      }

      template<typename SHA>
      INLINE static bool sha512()
      {
         typename SHA::Digest digest;
         uint8_t expect[64] = { 
            0x0c,0x3b,0x48,0x09,0x6d,0x8f,0x5e,0x8c,
            0x52,0xe4,0x23,0xb8,0x3f,0x11,0x9e,0x5b,
            0x1e,0xe7,0x2d,0x61,0xa4,0x7a,0x50,0x88,
            0x35,0xcd,0x53,0x09,0xb2,0x4b,0xec,0x3e,
            0x6c,0x15,0xf3,0x1e,0x33,0x7a,0x16,0x2e,
            0xb1,0x1e,0x6e,0x53,0xa0,0xb6,0x77,0x4b,
            0x3c,0x72,0x61,0x2c,0x8c,0x77,0x88,0xf2,
            0x45,0x81,0x55,0x2e,0xd4,0xa5,0xed,0x6a
         };

         SHA sha;
         sha.step(SHA::PADDING, sizeof(SHA::PADDING));
         sha.finish(digest);
         if (memcmp(&digest, expect, sizeof(expect)) != 0)
            return false;

         SHA::hashMem(SHA::PADDING, sizeof(SHA::PADDING), digest);
         if (memcmp(&digest, expect, sizeof(expect)) != 0)
            return false;

         return true;
      }
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Hash
{
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(SHA2)
   {
   public:
      TEST_METHOD(SHA256G) { Assert::AreEqual(true, CppCore::Test::Hash::SHA2::sha256<CppCore::SHA256g>()); }
      TEST_METHOD(SHA512G) { Assert::AreEqual(true, CppCore::Test::Hash::SHA2::sha512<CppCore::SHA512g>()); }

      TEST_METHOD(SHA256S) { Assert::AreEqual(true, CppCore::Test::Hash::SHA2::sha256<CppCore::SHA256s>()); }
      TEST_METHOD(SHA512S) { Assert::AreEqual(true, CppCore::Test::Hash::SHA2::sha512<CppCore::SHA512s>()); }
   };
}}}}
#endif
