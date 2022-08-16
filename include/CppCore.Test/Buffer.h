#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test
{
   /// <summary>
   /// Tests for Buffer.h in CppCore
   /// </summary>
   class Buffer
   {
   public:
      template<size_t SIZE>
      INLINE static bool sizeOf()
      {
         return sizeof(CppCore::Buffer<SIZE, false>) == SIZE + 16U;
      }
      template<size_t SIZE>
      INLINE static bool alignment()
      {
         for (size_t i = 0; i < 16; i++)
         {
            CppCore::Buffer<SIZE, false>  b1;
            CppCore::Buffer<SIZE, false>* b2 = new CppCore::Buffer<SIZE, false>();
            CppCore::Buffer<SIZE, false>* b3 = new CppCore::Buffer<SIZE, false>[2];

            const size_t sb2  = (size_t)b2;
            const size_t sb31 = (size_t)&b3[0];
            const size_t sb32 = (size_t)&b3[1];

            delete   b2;
            delete[] b3;

            if ((((size_t)(&b1) & 0x0FU) != 0) || ((sb2 & 0x0FU) != 0) || ((sb31 & 0x0FU) != 0) || ((sb32 & 0x0FU) != 0))
               return false;
         }
         return true;
      }
      template<size_t SIZE>
      INLINE static bool constructor()
      {
         // empty constructor
         CppCore::Buffer<SIZE, false> buf1;
         if (buf1.getSize()       != SIZE || 
             buf1.getRemaining()  != SIZE || 
             buf1.getLength()     != 0U   ||
             buf1.getLengthRead() != 0U)
            return false;

         // empty constructor with clear
         CppCore::Buffer<SIZE, true> buf1c;
         if (buf1c.getSize()       != SIZE || 
             buf1c.getRemaining()  != SIZE || 
             buf1c.getLength()     != 0U   ||
             buf1c.getLengthRead() != 0U)
            return false;

         // copy constructor
         CppCore::Buffer<SIZE, false> buf2(buf1);
         if (buf2.getSize()       != SIZE || 
             buf2.getRemaining()  != SIZE || 
             buf2.getLength()     != 0U   ||
             buf2.getLengthRead() != 0U)
            return false;

         // copy constructor with clear
         CppCore::Buffer<SIZE, true> buf2c(buf1c);
         if (buf2c.getSize()       != SIZE || 
             buf2c.getRemaining()  != SIZE || 
             buf2c.getLength()     != 0U   ||
             buf2c.getLengthRead() != 0U)
            return false;

         return true;
      }
   };
}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { 
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(Buffer)
   {
   public:
      TEST_METHOD(SIZEOF)      { Assert::AreEqual(true, CppCore::Test::Buffer::sizeOf<8192U>()); }
      TEST_METHOD(ALIGNMENT)   { Assert::AreEqual(true, CppCore::Test::Buffer::alignment<8192U>()); }
      TEST_METHOD(CONSTRUCTOR) { Assert::AreEqual(true, CppCore::Test::Buffer::constructor<8192U>()); }
   };
}}}
#endif
