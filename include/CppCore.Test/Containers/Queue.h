#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Containers
{
   /// <summary>
   /// Tests for Queue.h in CppCore::Containers
   /// </summary>
   class Queue
   {
   public:
      template<typename T, size_t SIZE>
      INLINE static bool fillmaxthenempty()
      {
         CppCore::Queue::ST<T, SIZE> container;
         T items[SIZE];
         T item;

         // pushFront
         for (size_t i = 0; i < SIZE; i++)
         {
            if (i != container.length()) return false;
            if (!container.pushFront(items[i])) return false;
         }

         if (container.pushFront(items[0])) return false;

         // popBack
         for (size_t i = SIZE; i > 0; i--)
         {
            if (i != container.length()) return false;
            if (!container.popBack(item)) return false;
         }

         if (container.popBack(item)) return false;

         // pushBack
         for (size_t i = 0; i < SIZE; i++)
         {
            if (i != container.length()) return false;
            if (!container.pushBack(items[i])) return false;
         }

         if (container.pushBack(items[0])) return false;

         // popFront
         for (size_t i = SIZE; i > 0; i--)
         {
            if (i != container.length()) return false;
            if (!container.popFront(item)) return false;
         }

         if (container.popFront(item)) return false;

         return true;
      }
      INLINE static bool fillmaxthenempty1() { return fillmaxthenempty<int32_t,   1>(); }
      INLINE static bool fillmaxthenempty2() { return fillmaxthenempty<uint64_t, 10>(); }
      INLINE static bool fillmaxthenempty3() { return fillmaxthenempty<Model,    12>(); }
      INLINE static bool fillmaxthenempty4() { return fillmaxthenempty<Model,   256>(); }
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Containers
{
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(Queue)
   {
   public:
      TEST_METHOD(FILLMAXTHENEMPTY1) { Assert::AreEqual(true, CppCore::Test::Containers::Queue::fillmaxthenempty1()); }
      TEST_METHOD(FILLMAXTHENEMPTY2) { Assert::AreEqual(true, CppCore::Test::Containers::Queue::fillmaxthenempty2()); }
      TEST_METHOD(FILLMAXTHENEMPTY3) { Assert::AreEqual(true, CppCore::Test::Containers::Queue::fillmaxthenempty3()); }
      TEST_METHOD(FILLMAXTHENEMPTY4) { Assert::AreEqual(true, CppCore::Test::Containers::Queue::fillmaxthenempty4()); }
   };
}}}}
#endif
