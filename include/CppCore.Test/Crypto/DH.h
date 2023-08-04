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
      INLINE static bool test1()
      {
         DH alice;
         DH bob;

         // alices generates and shares prime and constant
         // both generate a private key

         alice.reset();
         bob.reset(alice.p, alice.g);
         bob.genkey(alice.V);
         alice.genkey(bob.V);

         if (::memcmp(&alice.k, &bob.k, DH::SIZE) != 0)
            return false;

         return true;
      }
      template<typename DH>
      INLINE static bool test2()
      {
         DH alice;
         DH bob;

         // both already know prime (7) and constant (4)
         // both use their predefined key (alice=2, bob=6)

         alice.reset(7U, 4U, 2U);
         bob.reset(7U, 4U, 6U);
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
      TEST_METHOD(TEST1DH128)   { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test1<CppCore::DH128>()); }
      TEST_METHOD(TEST1DH256)   { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test1<CppCore::DH256>()); }
      TEST_METHOD(TEST1DH512)   { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test1<CppCore::DH512>()); }
      //TEST_METHOD(TEST1DH1024)  { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test1<CppCore::DH1024>()); }
      //TEST_METHOD(TEST1DH2048)  { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test1<CppCore::DH2048>()); }
      TEST_METHOD(TEST2DH128)   { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test2<CppCore::DH128>()); }
      TEST_METHOD(TEST2DH256)   { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test2<CppCore::DH256>()); }
      TEST_METHOD(TEST2DH512)   { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test2<CppCore::DH512>()); }
      //TEST_METHOD(TEST2DH1024)  { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test2<CppCore::DH1024>()); }
      //TEST_METHOD(TEST2DH2048)  { Assert::AreEqual(true, CppCore::Test::Crypto::DH::test2<CppCore::DH2048>()); }

   };
}}}}
#endif
