#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Hash
{
   /// <summary>
   /// Tests for MD5.h in CppCore::Hash
   /// </summary>
   class MD5
   {
   public:
      INLINE static bool test1()
      {
         uint8_t hash[16];
         const static uint8_t r[16] = { 0xE1,0x0A,0xDC,0x39,0x49,0xBA,0x59,0xAB,0xBE,0x56,0xE0,0x57,0xF2,0x0F,0x88,0x3E };
         bool ok = CppCore::MD5::hashMem("123456", 6, &hash[0]);
         return ok && memcmp(r, hash, 16) == 0;
      }
      INLINE static bool test2()
      {
         uint8_t hash[16];
         const static uint8_t r[16] = { 0xD4,0x9D,0xEA,0x3B,0x30,0x03,0xB5,0xF7,0x9B,0xAD,0xDD,0xA3,0x9E,0x02,0x99,0xA6 };
         bool ok = CppCore::MD5::hashMem("DgjsDheManfJH=asy;D-hF1Sj4H24kjad853kdhAdgj3lkams>weq", 53, &hash[0]);
         return ok && memcmp(r, &hash[0], 16) == 0;
      }
      INLINE static bool test3()
      {
         uint8_t hash[16];
         const static uint8_t r[16] = { 0x02,0x12,0x9b,0xb8,0x61,0x06,0x1d,0x1a,0x05,0x2c,0x59,0x2e,0x2d,0xc6,0xb3,0x83 };
         bool ok = CppCore::MD5::hashMem("X", 1, &hash[0]);
         return ok && memcmp(r, &hash[0], 16) == 0;
      }
      INLINE static bool test4()
      {
         uint8_t hash[16];
         const static uint8_t r[16] = { 0x4b,0x2e,0xf4,0x95,0xf7,0xda,0x4a,0x41,0xc4,0x27,0x69,0xfd,0xdd,0x84,0xb5,0x32 };
         bool ok = CppCore::MD5::hashMem("DgjsDheManfJH=asy;D-hF1Sj4H24kjad853kdhAdgj3lkams>weqDgjsDheManfJH=asy;D-hF1Sj4H24kjad853kdhAdgj3lkams>weq", 106, &hash[0]);
         return ok && memcmp(r, hash, 16) == 0;
      }
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Hash
{
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(MD5)
   {
   public:
      TEST_METHOD(test1) { Assert::AreEqual(true, CppCore::Test::Hash::MD5::test1()); }
      TEST_METHOD(test2) { Assert::AreEqual(true, CppCore::Test::Hash::MD5::test2()); }
      TEST_METHOD(test3) { Assert::AreEqual(true, CppCore::Test::Hash::MD5::test3()); }
      TEST_METHOD(test4) { Assert::AreEqual(true, CppCore::Test::Hash::MD5::test4()); }
   };
}}}}
#endif
