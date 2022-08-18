#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Hash
{
   /// <summary>
   /// Tests for Murmur3.h in CppCore::Hash
   /// </summary>
   class Murmur3
   {
   public:
      INLINE static bool test1()
      {
         uint32_t hash = 0;
         bool ok = CppCore::Murmur3::hashMem("DgjsDheManfJH=asy;D-hF1Sj4H24kjad853kdhAdgj3lkams>weq", 53, &hash);
         return ok && hash == 0x7C800BB4;
      }
      INLINE static bool test2()
      {
         uint32_t hash = 0;
         bool ok = CppCore::Murmur3::hashMem("X", 1, &hash);
         return ok && hash == 0x2814D70C;
      }
      INLINE static bool test3()
      {
         uint32_t hash = 0;
         bool ok = CppCore::Murmur3::hashMem("123456", 6, &hash);
         return ok && hash == 0xBF60EAB8;
      }
      INLINE static bool test4()
      {
         uint32_t hash = 0;
         bool ok = CppCore::Murmur3::hashMem("12345", 5, &hash);
         return ok && hash == 0x13a51193;
      }
      INLINE static bool test5()
      {
         uint32_t hash = 0;
         bool ok = CppCore::Murmur3::hashMem("1234", 4, &hash);
         return ok && hash == 0x721c5dc3;
      }
      INLINE static bool test6()
      {
         uint32_t hash = 0;
         bool ok = CppCore::Murmur3::hashMem("123", 3, &hash);
         return ok && hash == 0x9eb471eb;
      }
      
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Hash
{
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(Murmur3)
   {
   public:
      TEST_METHOD(TEST1) { Assert::AreEqual(true, CppCore::Test::Hash::Murmur3::test1()); }
      TEST_METHOD(TEST2) { Assert::AreEqual(true, CppCore::Test::Hash::Murmur3::test2()); }
      TEST_METHOD(TEST3) { Assert::AreEqual(true, CppCore::Test::Hash::Murmur3::test3()); }
      TEST_METHOD(TEST4) { Assert::AreEqual(true, CppCore::Test::Hash::Murmur3::test4()); }
      TEST_METHOD(TEST5) { Assert::AreEqual(true, CppCore::Test::Hash::Murmur3::test5()); }
      TEST_METHOD(TEST6) { Assert::AreEqual(true, CppCore::Test::Hash::Murmur3::test6()); }
   };
}}}}
#endif
