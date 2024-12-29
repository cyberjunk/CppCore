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
         CppCore::Uuid uuid;
         CppCore::Uuid::Generator gen;

         // test static create constructor with on the fly prng
         uuid = CppCore::Uuid::create();
         if (uuid.getVersion() != CppCore::Uuid::VERSION || uuid.getVariant() != CppCore::Uuid::VARIANT)
            return false;

         // test generate
         gen.generate(uuid);
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
         if (!CppCore::Uuid::isUuidString("826224c83ccb4d109721167a007d90d5"    )) return false;
         return true;
      }
      INLINE static bool touuidstring()
      {
         if (CppCore::Uuid(0x0000000000000000ULL, 0x0000000000000000ULL, false).toUuidString(true,  false) != "00000000-0000-0000-0000-000000000000") return false;
         if (CppCore::Uuid(0x0000000000000000ULL, 0x0000000000000000ULL, true ).toUuidString(true,  false) != "00000000-0000-4000-8000-000000000000") return false;
         if (CppCore::Uuid(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, false).toUuidString(true,  false) != "ffffffff-ffff-ffff-ffff-ffffffffffff") return false;
         if (CppCore::Uuid(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, false).toUuidString(false, false) != "ffffffffffffffffffffffffffffffff")     return false;
         if (CppCore::Uuid(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, false).toUuidString(false, true)  != "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")     return false;
         return true;
      }
      INLINE static bool fromuuidstring()
      {
         CppCore::Uuid uuid;
         if ( uuid.fromUuidString(""                                    )) return false;
         if ( uuid.fromUuidString("0"                                   )) return false;
         if ( uuid.fromUuidString("------------------------------------")) return false;
         if ( uuid.fromUuidString("xxx224c8-3ccb-4d10-9721-167a007d90d5")) return false;
         if (!uuid.fromUuidString("826224c8-3ccb-4d10-9721-167a007d90d5")) return false;
         if (!uuid.fromUuidString("826224c83ccb4d109721167a007d90d5"    )) return false;
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
      TEST_METHOD(CONSTRUCTOR)    { Assert::AreEqual(true, CppCore::Test::Uuid::constructor()); }
      TEST_METHOD(SIZEOF)         { Assert::AreEqual(true, CppCore::Test::Uuid::sizeOf()); }
      TEST_METHOD(ISUUIDSTRING)   { Assert::AreEqual(true, CppCore::Test::Uuid::isuuidstring()); }
      TEST_METHOD(TOUUIDSTRING)   { Assert::AreEqual(true, CppCore::Test::Uuid::touuidstring()); }
      TEST_METHOD(FROMUUIDSTRING) { Assert::AreEqual(true, CppCore::Test::Uuid::fromuuidstring()); }
   };
}}}
#endif
