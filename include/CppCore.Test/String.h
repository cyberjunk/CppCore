#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test
{
   /// <summary>
   /// Tests for String.h in CppCore
   /// </summary>
   class String
   {
   public:
      template<typename S> INLINE static bool clear()
      {
         S s1("123");  s1.clear();
         S s2("");     s2.clear();
         S s3("1234"); s3.clear();
         return
            s1 == "" && s1.length() == 0U &&
            s2 == "" && s2.length() == 0U &&
            s3 == "" && s3.length() == 0U;
      }
      template<typename S> INLINE static bool resize()
      {
         S s0;         s0.resize(0);
         S s1("");     s1.resize(15);
         S s2("1234"); s2.resize(3);
         S s3("1234"); s3.resize(15);
         S s4("1234"); s4.resize(30);
         return
            s0 == ""     && s0.length() == 0U && s0.capacity() >= 0  &&
            s1 == ""     && s1.length() == 0U && s1.capacity() >= 15 &&
            s2 == "1234" && s2.length() == 4U && s2.capacity() >= 4  &&
            s3 == "1234" && s3.length() == 4U && s3.capacity() >= 15 &&
            s4 == "1234" && s4.length() == 4U && s4.capacity() >= 30;
      }
      template<typename S> INLINE static bool equals()
      {
         const bool a =
            S("").equals(S(""))            == true  &&
            S("12345").equals(S("12345"))  == true  &&
            S("12345").equals(S("1234"))   == false &&
            S("12345").equals(S("123456")) == false &&
            S("12345").equals(S("1234a"))  == false;
         const bool b =
            S("").equals(std::string(""))            == true  &&
            S("12345").equals(std::string("12345"))  == true  &&
            S("12345").equals(std::string("1234"))   == false &&
            S("12345").equals(std::string("123456")) == false &&
            S("12345").equals(std::string("1234a"))  == false;
         const bool c =
            S("").equals(std::string_view(""))            == true  &&
            S("12345").equals(std::string_view("12345"))  == true  &&
            S("12345").equals(std::string_view("1234"))   == false &&
            S("12345").equals(std::string_view("123456")) == false &&
            S("12345").equals(std::string_view("1234a"))  == false;
         const bool d =
            S("").equals("")            == true  &&
            S("12345").equals("12345")  == true  &&
            S("12345").equals("1234")   == false &&
            S("12345").equals("123456") == false &&
            S("12345").equals("1234a")  == false;
         const bool e =
            S("12345").equals('1') == false  &&
            S("1").equals('1')     == true;
         const bool f =
            S("ABCDEFG").equals("abcdefg", true)  == false &&
            S("ABCDEFG").equals("abcdefg", false) == true  &&
            S("abCdeFg").equals("AbCDefG", false) == true  &&
            S("a").equals('A', false)             == true;
         return a && b && c && d && e && f;
      }
      template<typename S> INLINE static bool append()
      {
         const bool a =
            S(""   ).append(S(""))    == ""    &&
            S(""   ).append(S("123")) == "123" &&
            S("1"  ).append(S("23" )) == "123" &&
            S("123").append(S(""   )) == "123" &&
            S("123").append(S("456")) == "123456";
         const bool b =
            S(""   ).append(std::string(""   )) == ""    &&
            S(""   ).append(std::string("123")) == "123" &&
            S("1"  ).append(std::string("23" )) == "123" &&
            S("123").append(std::string(""   )) == "123" &&
            S("123").append(std::string("456")) == "123456";
         const bool c =
            S(""   ).append(std::string_view(""   )) == ""    &&
            S(""   ).append(std::string_view("123")) == "123" &&
            S("1"  ).append(std::string_view("23" )) == "123" &&
            S("123").append(std::string_view(""   )) == "123" &&
            S("123").append(std::string_view("456")) == "123456";
         const bool d =
            S(""   ).append(""   ) == ""    &&
            S(""   ).append("123") == "123" &&
            S("1"  ).append("23" ) == "123" &&
            S("123").append(""   ) == "123" &&
            S("123").append("456") == "123456";
         const bool e =
            S(""   ).append('1')  == "1"  &&
            S("1"  ).append('2' ) == "12" &&
            S("123").append('4')  == "1234";
         return a && b && c && d && e;
      }
      template<typename S> INLINE static bool insert()
      {
         const bool a = 
            S(""  ).insert('1', 0) == "1"  &&
            S("2" ).insert('1', 0) == "12" &&
            S("1" ).insert('2', 1) == "12" &&
            S("13").insert('2', 1) == "123";
         const bool b =
            S(""  ).insert(S("1" ), 0) == "1"    &&
            S("34").insert(S("12"), 0) == "1234" &&
            S("1" ).insert(S("23"), 1) == "123"  &&
            S("14").insert(S("23"), 1) == "1234";
         const bool c =
            S(""  ).insert(std::string("1" ), 0) == "1"    &&
            S("34").insert(std::string("12"), 0) == "1234" &&
            S("1" ).insert(std::string("23"), 1) == "123"  &&
            S("14").insert(std::string("23"), 1) == "1234";
         const bool d =
            S(""  ).insert(std::string_view("1" ), 0) == "1"    &&
            S("34").insert(std::string_view("12"), 0) == "1234" &&
            S("1" ).insert(std::string_view("23"), 1) == "123"  &&
            S("14").insert(std::string_view("23"), 1) == "1234";
         const bool e =
            S(""  ).insert("1" , 0) == "1"    &&
            S("34").insert("12", 0) == "1234" &&
            S("1" ).insert("23", 1) == "123"  &&
            S("14").insert("23", 1) == "1234";
         return a && b && c && d && e;
      }
      template<typename S> INLINE static bool remove()
      {
         return
            S(""   ).remove(0, 0) == ""   &&
            S("123").remove(0, 1) == "23" &&
            S("123").remove(1, 1) == "13" &&
            S("123").remove(2, 1) == "12" &&
            S("123").remove(0, 2) == "3"  &&
            S("123").remove(1, 2) == "1"  &&
            S("123").remove(0, 3) == "";
      }
      template<typename S> INLINE static bool replace()
      {
         const bool a = 
            S(""   ).replace('a', 'b')    == ""    &&
            S("a"  ).replace('a', 'b')    == "b"   &&
            S("aaa").replace('a', 'b')    == "bbb" &&
            S("aba").replace('a', 'b')    == "bbb" &&
            S("cdc").replace('a', 'b')    == "cdc" &&
            S("aaa").replace('a', 'b', 1) == "abb" &&
            S("aaa").replace('a', 'b', 3) == "aaa";
         return a;
      }
      template<typename S> INLINE static bool substring()
      {
         return
            S(""   ).substring(0, 0) == ""    &&
            S("123").substring(0, 3) == "123" &&
            S("123").substring(0, 1) == "1"   &&
            S("123").substring(1, 1) == "2"   &&
            S("123").substring(2, 1) == "3"   &&
            S("123").substring(0, 2) == "12"  &&
            S("123").substring(1, 2) == "23"  &&
            S("123").substring(0, 4) == "123" && // more requested than available
            S("123").substring(2, 9) == "3";     // more requested than available
      }
      template<typename S> INLINE static bool tolower()
      {
         return
            S(""      ).toLower()  == ""       &&
            S("123456").toLower()  == "123456" &&
            S("abcxyz").toLower()  == "abcxyz" &&
            S("ABCXYZ").toLower()  == "abcxyz" &&
            S("ABCXYZ").toLower(1) == "Abcxyz" &&
            S("ABCXYZ").toLower(6) == "ABCXYZ" &&
            S("aBcxyZ").toLower()  == "abcxyz";
      }
      template<typename S> INLINE static bool toupper()
      {
         return
            S(""      ).toUpper()  == ""       &&
            S("123456").toUpper()  == "123456" &&
            S("abcxyz").toUpper()  == "ABCXYZ" &&
            S("abcxyz").toUpper(1) == "aBCXYZ" &&
            S("abcxyz").toUpper(6) == "abcxyz" &&
            S("ABCXYZ").toUpper()  == "ABCXYZ" &&
            S("aBcxyZ").toUpper()  == "ABCXYZ";
      }
      template<typename S> INLINE static bool reverse()
      {
         return
            S(""    ).reverse() == ""     &&
            S("a"   ).reverse() == "a"    &&
            S("aa"  ).reverse() == "aa"   &&
            S("abc" ).reverse() == "cba"  &&
            S("1234").reverse() == "4321" &&
            S("0123456789abcdefg").reverse() == "gfedcba9876543210";
      }
      template<typename S> INLINE static bool startswith()
      {
         const bool a =
            S(""      ).startsWith('a') == false &&
            S("123456").startsWith('1') == true  &&
            S("abcxyz").startsWith('A') == false &&
            S("abcxyz").startsWith('a') == true;
         const bool b =
            S(""      ).startsWith("a")       == false &&
            S("123456").startsWith("1")       == true  &&
            S("abcxyz").startsWith("abc")     == true &&
            S("abcxyz").startsWith("Abc")     == false &&
            S("abcxyz").startsWith("abcxyz")  == true  &&
            S("abcxyz").startsWith("abcdxyz") == false;
         const bool c =
            S(""      ).startsWith(std::string("a"))       == false &&
            S("123456").startsWith(std::string("1"))       == true  &&
            S("abcxyz").startsWith(std::string("abc"))     == true  &&
            S("abcxyz").startsWith(std::string("Abc"))     == false &&
            S("abcxyz").startsWith(std::string("abcxyz"))  == true  &&
            S("abcxyz").startsWith(std::string("abcdxyz")) == false;
         const bool d =
            S(""      ).startsWith(std::string_view("a"))       == false &&
            S("123456").startsWith(std::string_view("1"))       == true  &&
            S("abcxyz").startsWith(std::string_view("abc"))     == true  &&
            S("abcxyz").startsWith(std::string_view("Abc"))     == false &&
            S("abcxyz").startsWith(std::string_view("abcxyz"))  == true  &&
            S("abcxyz").startsWith(std::string_view("abcdxyz")) == false;
         const bool e =
            S(""      ).startsWith(S("a"))       == false &&
            S("123456").startsWith(S("1"))       == true  &&
            S("abcxyz").startsWith(S("abc"))     == true  &&
            S("abcxyz").startsWith(S("Abc"))     == false &&
            S("abcxyz").startsWith(S("abcxyz"))  == true  &&
            S("abcxyz").startsWith(S("abcdxyz")) == false;
         return a && b && c && d && e;
      }
      template<typename S> INLINE static bool endswith()
      {
         const bool a =
            S(""      ).endsWith('a') == false &&
            S("123456").endsWith('6') == true  &&
            S("abcxyz").endsWith('Z') == false &&
            S("abcxyz").endsWith('z') == true;
         const bool b =
            S(""      ).endsWith("a")       == false &&
            S("123456").endsWith("6")       == true  &&
            S("abcxyz").endsWith("xyz")     == true  &&
            S("abcxyz").endsWith("Xyz")     == false &&
            S("abcxyz").endsWith("abcxyz")  == true  &&
            S("abcxyz").endsWith("abcdxyz") == false;
         const bool c =
            S(""      ).endsWith(std::string("a"))       == false &&
            S("123456").endsWith(std::string("6"))       == true  &&
            S("abcxyz").endsWith(std::string("xyz"))     == true  &&
            S("abcxyz").endsWith(std::string("Xyz"))     == false &&
            S("abcxyz").endsWith(std::string("abcxyz"))  == true  &&
            S("abcxyz").endsWith(std::string("abcdxyz")) == false;
         const bool d =
            S(""      ).endsWith(std::string_view("a"))       == false &&
            S("123456").endsWith(std::string_view("6"))       == true  &&
            S("abcxyz").endsWith(std::string_view("xyz"))     == true  &&
            S("abcxyz").endsWith(std::string_view("Xyz"))     == false &&
            S("abcxyz").endsWith(std::string_view("abcxyz"))  == true  &&
            S("abcxyz").endsWith(std::string_view("abcdxyz")) == false;
         const bool e =
            S(""      ).endsWith(S("a"))       == false &&
            S("123456").endsWith(S("6"))       == true  &&
            S("abcxyz").endsWith(S("xyz"))     == true  &&
            S("abcxyz").endsWith(S("Xyz"))     == false &&
            S("abcxyz").endsWith(S("abcxyz"))  == true  &&
            S("abcxyz").endsWith(S("abcdxyz")) == false;
         return a && b && c && d && e;
      }
      template<typename S> INLINE static bool findfirst()
      {
         const size_t i1 = S("aaa").findFirst('a', 0);
         const size_t i2 = S("aaa").findFirst('a', 1);
         const size_t i3 = S("aaa").findFirst('a', 2);
         const size_t i4 = S("aaa").findFirst('a', 3);

         const bool a =
            S(""   ).findFirst('a')    == S::npos() &&
            S("z"  ).findFirst('a')    == S::npos() &&
            S("A"  ).findFirst('a')    == S::npos() &&
            S("a"  ).findFirst('a')    == 0U &&
            S("abc").findFirst('b')    == 1U &&
            S("abc").findFirst('c')    == 2U &&
            S("abcdefghijklmnopqr").findFirst('q') == 16U &&
            S("aaa").findFirst('a', 0) == 0U &&
            S("aaa").findFirst('a', 1) == 1U &&
            S("aaa").findFirst('a', 2) == 2U &&
            S("aaa").findFirst('a', 3) == S::npos();


         const bool b =
            S(""   ).findFirst("a")   == S::npos() &&
            S("z"  ).findFirst("a")   == S::npos() &&
            S("z"  ).findFirst("az")  == S::npos() &&
            S("abc").findFirst("Abc") == S::npos() &&
            S("abc").findFirst("abc") == 0U &&
            S("abc").findFirst("ab")  == 0U &&
            S("abc").findFirst("bc")  == 1U &&
            S("abcdefghijklmnopqr").findFirst("qr") == 16U;
         const bool c =
            S(""   ).findFirst(S("a"))   == S::npos() &&
            S("z"  ).findFirst(S("a"))   == S::npos() &&
            S("z"  ).findFirst(S("az"))  == S::npos() &&
            S("abc").findFirst(S("Abc")) == S::npos() &&
            S("abc").findFirst(S("abc")) == 0U &&
            S("abc").findFirst(S("ab"))  == 0U &&
            S("abc").findFirst(S("bc"))  == 1U &&
            S("abcdefghijklmnopqr").findFirst(S("qr")) == 16U;
         const bool d =
            S(""   ).findFirst(std::string("a"))   == S::npos() &&
            S("z"  ).findFirst(std::string("a"))   == S::npos() &&
            S("z"  ).findFirst(std::string("az"))  == S::npos() &&
            S("abc").findFirst(std::string("Abc")) == S::npos() &&
            S("abc").findFirst(std::string("abc")) == 0U &&
            S("abc").findFirst(std::string("ab"))  == 0U &&
            S("abc").findFirst(std::string("bc"))  == 1U &&
            S("abcdefghijklmnopqr").findFirst(std::string("qr")) == 16U;
         const bool e =
            S(""   ).findFirst(std::string_view("a"))   == S::npos() &&
            S("z"  ).findFirst(std::string_view("a"))   == S::npos() &&
            S("z"  ).findFirst(std::string_view("az"))  == S::npos() &&
            S("abc").findFirst(std::string_view("Abc")) == S::npos() &&
            S("abc").findFirst(std::string_view("abc")) == 0U &&
            S("abc").findFirst(std::string_view("ab"))  == 0U &&
            S("abc").findFirst(std::string_view("bc"))  == 1U &&
            S("abcdefghijklmnopqr").findFirst(std::string_view("qr")) == 16U;
         return a && b && c && d && e;
      }

      template<typename S> INLINE static bool findlast()
      {
         const bool a =
            S(""    ).findLast('a')    == S::npos() &&
            S("z"   ).findLast('a')    == S::npos() &&
            S("A"   ).findLast('a')    == S::npos() &&
            S("a"   ).findLast('a')    == 0U &&
            S("babc").findLast('b')    == 2U &&
            S("cabc").findLast('c')    == 3U &&
            S("qabcdefghijklmnopqr").findLast('q') == 17U;
         /*const bool b =
            S(""   ).findLast("a")   == S::npos() &&
            S("z"  ).findLast("a")   == S::npos() &&
            S("z"  ).findLast("az")  == S::npos() &&
            S("abc").findLast("Abc") == S::npos() &&
            S("abc").findLast("abc") == 0U &&
            S("abc").findLast("ab")  == 0U &&
            S("abc").findLast("bc")  == 1U &&
            S("abcdefghijklmnopqr").findLast("qr") == 16U;
         const bool c =
            S(""   ).findLast(S("a"))   == S::npos() &&
            S("z"  ).findLast(S("a"))   == S::npos() &&
            S("z"  ).findLast(S("az"))  == S::npos() &&
            S("abc").findLast(S("Abc")) == S::npos() &&
            S("abc").findLast(S("abc")) == 0U &&
            S("abc").findLast(S("ab"))  == 0U &&
            S("abc").findLast(S("bc"))  == 1U &&
            S("abcdefghijklmnopqr").findLast(S("qr")) == 16U;
         const bool d =
            S(""   ).findLast(std::string("a"))   == S::npos() &&
            S("z"  ).findLast(std::string("a"))   == S::npos() &&
            S("z"  ).findLast(std::string("az"))  == S::npos() &&
            S("abc").findLast(std::string("Abc")) == S::npos() &&
            S("abc").findLast(std::string("abc")) == 0U &&
            S("abc").findLast(std::string("ab"))  == 0U &&
            S("abc").findLast(std::string("bc"))  == 1U &&
            S("abcdefghijklmnopqr").findLast(std::string("qr")) == 16U;
         const bool e =
            S(""   ).findLast(std::string_view("a"))   == S::npos() &&
            S("z"  ).findLast(std::string_view("a"))   == S::npos() &&
            S("z"  ).findLast(std::string_view("az"))  == S::npos() &&
            S("abc").findLast(std::string_view("Abc")) == S::npos() &&
            S("abc").findLast(std::string_view("abc")) == 0U &&
            S("abc").findLast(std::string_view("ab"))  == 0U &&
            S("abc").findLast(std::string_view("bc"))  == 1U &&
            S("abcdefghijklmnopqr").findLast(std::string_view("qr")) == 16U;*/
         return a;// && b&& c&& d&& e;
      }
   };
}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { 
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(String)
   {
   public:
      //GENERIC
      TEST_METHOD(CLEAR_8G)       { Assert::AreEqual(true, CppCore::Test::String::clear<CppCore::String8g>()); }
      TEST_METHOD(RESIZE_8G)      { Assert::AreEqual(true, CppCore::Test::String::resize<CppCore::String8g>()); }
      TEST_METHOD(EQUALS_8G)      { Assert::AreEqual(true, CppCore::Test::String::equals<CppCore::String8g>()); }
      TEST_METHOD(APPEND_8G)      { Assert::AreEqual(true, CppCore::Test::String::append<CppCore::String8g>()); }
      TEST_METHOD(INSERT_8G)      { Assert::AreEqual(true, CppCore::Test::String::insert<CppCore::String8g>()); }
      TEST_METHOD(REMOVE_8G)      { Assert::AreEqual(true, CppCore::Test::String::remove<CppCore::String8g>()); }
      TEST_METHOD(REPLACE_8G)     { Assert::AreEqual(true, CppCore::Test::String::replace<CppCore::String8g>()); }
      TEST_METHOD(SUBSTRING_8G)   { Assert::AreEqual(true, CppCore::Test::String::substring<CppCore::String8g>()); }
      TEST_METHOD(TOLOWER_8G)     { Assert::AreEqual(true, CppCore::Test::String::tolower<CppCore::String8g>()); }
      TEST_METHOD(TOUPPER_8G)     { Assert::AreEqual(true, CppCore::Test::String::toupper<CppCore::String8g>()); }
      TEST_METHOD(REVERSE_8G)     { Assert::AreEqual(true, CppCore::Test::String::reverse<CppCore::String8g>()); }
      TEST_METHOD(STARTSWITH_8G)  { Assert::AreEqual(true, CppCore::Test::String::startswith<CppCore::String8g>()); }
      TEST_METHOD(ENDSWITH_8G)    { Assert::AreEqual(true, CppCore::Test::String::endswith<CppCore::String8g>()); }
      TEST_METHOD(FINDFIRST_8G)   { Assert::AreEqual(true, CppCore::Test::String::findfirst<CppCore::String8g>()); }
      TEST_METHOD(FINDLAST_8G)    { Assert::AreEqual(true, CppCore::Test::String::findlast<CppCore::String8g>()); }

      //OPTIMIZED
      TEST_METHOD(CLEAR_8S)       { Assert::AreEqual(true, CppCore::Test::String::clear<CppCore::String8s>()); }
      TEST_METHOD(RESIZE_8S)      { Assert::AreEqual(true, CppCore::Test::String::resize<CppCore::String8s>()); }
      TEST_METHOD(EQUALS_8S)      { Assert::AreEqual(true, CppCore::Test::String::equals<CppCore::String8s>()); }
      TEST_METHOD(APPEND_8S)      { Assert::AreEqual(true, CppCore::Test::String::append<CppCore::String8s>()); }
      TEST_METHOD(INSERT_8S)      { Assert::AreEqual(true, CppCore::Test::String::insert<CppCore::String8s>()); }
      TEST_METHOD(REMOVE_8S)      { Assert::AreEqual(true, CppCore::Test::String::remove<CppCore::String8s>()); }
      TEST_METHOD(REPLACE_8S)     { Assert::AreEqual(true, CppCore::Test::String::replace<CppCore::String8s>()); }
      TEST_METHOD(SUBSTRING_8S)   { Assert::AreEqual(true, CppCore::Test::String::substring<CppCore::String8s>()); }
      TEST_METHOD(TOLOWER_8S)     { Assert::AreEqual(true, CppCore::Test::String::tolower<CppCore::String8s>()); }
      TEST_METHOD(TOUPPER_8S)     { Assert::AreEqual(true, CppCore::Test::String::toupper<CppCore::String8s>()); }
      TEST_METHOD(REVERSE_8S)     { Assert::AreEqual(true, CppCore::Test::String::reverse<CppCore::String8s>()); }
      TEST_METHOD(STARTSWITH_8S)  { Assert::AreEqual(true, CppCore::Test::String::startswith<CppCore::String8s>()); }
      TEST_METHOD(ENDSWITH_8S)    { Assert::AreEqual(true, CppCore::Test::String::endswith<CppCore::String8s>()); }
      TEST_METHOD(FINDFIRST_8S)   { Assert::AreEqual(true, CppCore::Test::String::findfirst<CppCore::String8s>()); }
      TEST_METHOD(FINDLAST_8S)    { Assert::AreEqual(true, CppCore::Test::String::findlast<CppCore::String8s>()); }
   };
}}}
#endif
