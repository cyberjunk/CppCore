#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Hash
{
   /// <summary>
   /// Tests for CRC32.h in CppCore::Hash
   /// </summary>
   class CRC32
   {
   public:
      static constexpr const char STR1[] = "123456";
      static constexpr const char STR2[] = "DgjsDheManfJH=asy;D-hF1Sj4H24kjad853kdhAdgj3lkams>weq";
      static constexpr const char STR3[] = "X";

      INLINE static bool crc32test1()
      {
         CppCore::CRC32::Digest hash;
         bool ok = CppCore::CRC32::hashMem(STR1, ::strlen(STR1), hash);
         if (!ok || hash != 0x0972D361U) return false;
         return true;
      }
      INLINE static bool crc32test2()
      {
         CppCore::CRC32::Digest hash;
         bool ok = CppCore::CRC32::hashMem(STR2, ::strlen(STR2), hash);
         if (!ok || hash != 0x7FCB7808U) return false;
         return true;
      }
      INLINE static bool crc32test3()
      {
         CppCore::CRC32::Digest hash;
         bool ok = CppCore::CRC32::hashMem(STR3, ::strlen(STR3), hash);
         if (!ok || hash != 0xB7B2364BU) return false;
         return true;
      }
      template<typename TCRC>
      INLINE static bool crc32ctest1()
      {
         CppCore::CRC32::Digest hash;
         bool ok = TCRC::hashMem(STR1, ::strlen(STR1), hash);
         if (!ok || hash != 0x41357186U) return false;
         return true;
      }
      template<typename TCRC>
      INLINE static bool crc32ctest2()
      {
         CppCore::CRC32::Digest hash;
         bool ok = TCRC::hashMem(STR2, ::strlen(STR2), hash);
         if (!ok || hash != 0xc4a71611) return false;
         return true;
      }
      template<typename TCRC>
      INLINE static bool crc32ctest3()
      {
         CppCore::CRC32::Digest hash;
         bool ok = TCRC::hashMem(STR3, ::strlen(STR3), hash);
         if (!ok || hash != 0x8981D14D) return false;
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
   TEST_CLASS(CRC32)
   {
   public:
      TEST_METHOD(CRC32TEST1) { Assert::AreEqual(true, CppCore::Test::Hash::CRC32::crc32test1()); }
      TEST_METHOD(CRC32TEST2) { Assert::AreEqual(true, CppCore::Test::Hash::CRC32::crc32test2()); }
      TEST_METHOD(CRC32TEST3) { Assert::AreEqual(true, CppCore::Test::Hash::CRC32::crc32test3()); }
      TEST_METHOD(CRC32CGTEST1) { Assert::AreEqual(true, CppCore::Test::Hash::CRC32::crc32ctest1<CppCore::CRC32Cg>()); }
      TEST_METHOD(CRC32CGTEST2) { Assert::AreEqual(true, CppCore::Test::Hash::CRC32::crc32ctest2<CppCore::CRC32Cg>()); }
      TEST_METHOD(CRC32CGTEST3) { Assert::AreEqual(true, CppCore::Test::Hash::CRC32::crc32ctest3<CppCore::CRC32Cg>()); }
#if defined(CPPCORE_CPUFEAT_SSE42)
      TEST_METHOD(CRC32CSTEST1) { Assert::AreEqual(true, CppCore::Test::Hash::CRC32::crc32ctest1<CppCore::CRC32Cs>()); }
      TEST_METHOD(CRC32CSTEST2) { Assert::AreEqual(true, CppCore::Test::Hash::CRC32::crc32ctest2<CppCore::CRC32Cs>()); }
      TEST_METHOD(CRC32CSTEST3) { Assert::AreEqual(true, CppCore::Test::Hash::CRC32::crc32ctest3<CppCore::CRC32Cs>()); }
#endif
   };
}}}}
#endif
