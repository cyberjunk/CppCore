#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test
{
   /// <summary>
   /// Tests for Uuid.h in CppCore
   /// </summary>
   class Uuid
   {
   public:
      INLINE static bool sizeOf()
      {
         return sizeof(CppCore::Uuid) == 16U;
      }
      INLINE static bool constructor()
      {
         CppCore::Random::Default64 g1;
         CppCore::Uuid uuid;
         
         // test static create constructor
         uuid = CppCore::Uuid::create();
         if (uuid.getVersion() != CppCore::Uuid::VERSION || uuid.getVariant() != CppCore::Uuid::VARIANT)
            return false;

         // test generate
         uuid.generate(g1);
         if (uuid.getVersion() != CppCore::Uuid::VERSION || uuid.getVariant() != CppCore::Uuid::VARIANT)
            return false;

         // test generate with on the fly prng
         uuid.generate();
         if (uuid.getVersion() != CppCore::Uuid::VERSION || uuid.getVariant() != CppCore::Uuid::VARIANT)
            return false;

         return true;
      }
      INLINE static bool isuuidstring()
      {
         if ( CppCore::Uuid::isUuidString(""                                    )) return false;
         if ( CppCore::Uuid::isUuidString("0"                                   )) return false;
         if ( CppCore::Uuid::isUuidString("------------------------------------")) return false;
         if ( CppCore::Uuid::isUuidString("xxx224c8-3ccb-4d10-9721-167a007d90d5")) return false;
         if (!CppCore::Uuid::isUuidString("826224c8-3ccb-4d10-9721-167a007d90d5")) return false;
         if (!CppCore::Uuid::isUuidString("00000000-0000-0000-0000-000000000000")) return false;
         return true;
      }
      INLINE static bool touuidstring()
      {
         if (CppCore::Uuid(0x0000000000000000ULL, 0x0000000000000000ULL, false).toUuidString() != "00000000-0000-0000-0000-000000000000") return false;
         if (CppCore::Uuid(0x0000000000000000ULL, 0x0000000000000000ULL, true ).toUuidString() != "00000000-0000-4000-8000-000000000000") return false;
         if (CppCore::Uuid(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, false).toUuidString() != "ffffffff-ffff-ffff-ffff-ffffffffffff") return false;
         return true;
      }
   };
}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { 
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(Uuid)
   {
   public:
      TEST_METHOD(CONSTRUCTOR) { Assert::AreEqual(true, CppCore::Test::Uuid::constructor()); }
      TEST_METHOD(SIZEOF)      { Assert::AreEqual(true, CppCore::Test::Uuid::sizeOf()); }
      TEST_METHOD(ISUUIDSTRING){ Assert::AreEqual(true, CppCore::Test::Uuid::isuuidstring()); }
      TEST_METHOD(TOUUIDSTRING){ Assert::AreEqual(true, CppCore::Test::Uuid::touuidstring()); }
   };
}}}
#endif
