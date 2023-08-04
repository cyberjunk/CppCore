#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Crypto
{
   /// <summary>
   /// 
   /// </summary>
   class DH
   {
   public:
      template<typename DH>
      INLINE static bool test()
      {
         DH alice;
         DH bob;

         alice.reset();
         bob.reset(alice.p, alice.g);
         bob.genkey(alice.V);
         alice.genkey(bob.V);

         if (::memcmp(&alice.k, &bob.k, DH::SIZE) != 0)
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
   TEST_CLASS(DH)
   {
   public:
      TEST_METHOD(DH128)   { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test<CppCore::DH128>()); }
      TEST_METHOD(DH256)   { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test<CppCore::DH256>()); }
      TEST_METHOD(DH512)   { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test<CppCore::DH512>()); }
      //TEST_METHOD(DH1024)  { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test<CppCore::DH1024>()); }
      //TEST_METHOD(DH2048)  { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test<CppCore::DH2048>()); }
   };
}}}}
#endif
