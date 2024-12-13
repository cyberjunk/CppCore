#pragma once

#include <CppCore/Root.h>
#include <CppCore/Memory.h>
#include <CppCore/Random.h>
#include <CppCore/Iterator.h>
#include <CppCore/Encoding.h>

namespace CppCore
{
   /// <summary>
   /// Base Class for String with Dynamic Size
   /// </summary>
   template<typename S>
   class String8
   {
   protected:
      size_t mLength;
      size_t mSize;
      char*  mData;

   public:
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ITERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      using ItCF = CppCore::ItC<char, false>; // Constant Iterator Class Forward
      using ItCR = CppCore::ItC<char, true>;  // Constant Iterator Class Reverse
      using ItDF = CppCore::ItD<char, false>; // Non-Constant Iterator Class Forward
      using ItDR = CppCore::ItD<char, true>;  // Non-Constant Iterator Class Reverse

      INLINE ItDF begin()        { return ItDF(mData); }
      INLINE ItCF begin()  const { return ItCF(mData); }
      INLINE ItDF end()          { return ItDF(&mData[mLength]); }
      INLINE ItCF end()    const { return ItCF(&mData[mLength]); }
      INLINE ItDR rbegin()       { return ItDR((&mData[mLength])-1U); }
      INLINE ItCR rbegin() const { return ItCR((&mData[mLength])-1U); }
      INLINE ItDR rend()         { return ItDR(mData-1U); }
      INLINE ItCR rend()   const { return ItCR(mData-1U); }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STATIC HELPERS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns size_t::max (the value used to indicate a not found index)
      /// </summary>
      INLINE static size_t npos() { return std::numeric_limits<size_t>::max(); }

      /// <summary>
      /// Determines length of null zerminated c-string
      /// </summary>
      INLINE static size_t strlen(const char* s) { return ::strlen(s); }

      /// <summary>
      /// True if c is greater or equal min and smaller or equal max.
      /// </summary>
      template<bool INCLUSIVE = true>
      INLINE static bool israngechar(const char c, const char min, const char max)
      {
         return CppCore::isinrange<char, INCLUSIVE>(c, min, max);
      }

      /// <summary>
      /// Returns c in lowercase if it's uppercase, else untouched.
      /// </summary>
      INLINE static char tolower(const char c) { return S::israngechar(c, 'A', 'Z') ? c + (char)0x20 : c; }

      /// <summary>
      /// Returns c in uppercase if it's lowercase, else untouched.
      /// </summary>
      INLINE static char toupper(const char c) { return S::israngechar(c, 'a', 'z') ? c - (char)0x20 : c; }

      /// <summary>
      /// Allocates memory for strings
      /// </summary>
      INLINE static char* alloc(const size_t size) { return Memory::alloc(size); }

      /// <summary>
      /// Frees memory for strings
      /// </summary>
      INLINE static void free(void* mem) { return Memory::free(mem); }

      /// <summary>
      /// Returns size to use for a certain requested capacity.
      /// In this base class capacity + 1 (for zero termination).
      /// </summary>
      INLINE static size_t calcsize(size_t capacity) { return capacity + 1U; }

      /// <summary>
      /// Memory Copy used in the resize() operation.
      /// Uses calcsize() to pad len accordingly (in case of base class +1).
      /// Hence, requires a zero termination at the end of src that is copied, too.
      /// </summary>
      INLINE static void clonecopy(void* dst, const void* src, const size_t len) 
      {
         Memory::copy(dst, src, S::calcsize(len));
      }

   protected:
      /// <summary>
      /// Helper. Casts this to final type S.
      /// </summary>
      INLINE S* thiss() const { return (S*)this; }

      /// <summary>
      /// Helper for Empty Constructors.
      /// </summary>
      INLINE void _ctrempty(const size_t size)
      {
         const auto SIZE = S::calcsize(size);
         mLength  = 0U;
         mSize    = SIZE;
         mData    = S::alloc(SIZE);
         mData[0] = (char)0x00;
      }

      /// <summary>
      /// Helper for Constructors.
      /// Initialization from c-string with known length.
      /// </summary>
      INLINE void _ctrfrom1ptr(const char* s, const size_t len)
      {
         const auto SIZE = S::calcsize(len);
         mLength = len;
         mSize   = SIZE;
         mData   = S::alloc(SIZE);
         Memory::copy(mData, s, len);
         mData[len] = (char)0x00;
      }

      /// <summary>
      /// Helper for Concatenation Constructors
      /// Initialization from two c-strings with known lengths.
      /// </summary>
      INLINE void _ctrfrom2ptr(const char* s1, const size_t len1, const char* s2, const size_t len2)
      {
         const auto LENSUM = len1 + len2;
         const auto SIZE   = S::calcsize(LENSUM);
         mLength = LENSUM;
         mSize   = SIZE;
         mData   = S::alloc(SIZE);
         Memory::copy(mData,      s1, len1);
         Memory::copy(mData+len1, s2, len2);
         mData[LENSUM] = (char)0x00;
      }

      /// <summary>
      /// Helper for Optimized Concatenation Constructors
      /// Initialization from own type and c-string with known lengths.
      /// </summary>
      INLINE void _ctrfrom2ptr(const S& s1, const char* s2, const size_t len2)
      {
         const auto LEN1   = s1.length();
         const auto LENSUM = LEN1 + len2;
         const auto SIZE   = S::calcsize(LENSUM);
         mLength = LENSUM;
         mSize   = SIZE;
         mData   = S::alloc(SIZE);
         S::clonecopy(mData, s1.data(), LEN1);
         Memory::copy(mData+LEN1, s2, len2);
         mData[LENSUM] = (char)0x00;
      }

      /// <summary>
      /// Helper for Assignment.
      /// Assigns value from c-string with known length.
      /// </summary>
      INLINE void _assignfrom1ptr(const char* s, const size_t len)
      {
         thiss()->resize(len); 
         Memory::copy(mData, s, len);
         mData[len] = (char)0x00;
         mLength = len;
      }

      /// <summary>
      /// Helper for appending decimal number.
      /// </summary>
      template<typename T, size_t N>
      INLINE S& _appendDecimal(const T v)
      {
         const auto LENOLD = mLength;
         const auto LENNEW = LENOLD + N;
         if (thiss()->available() < N)
            thiss()->resize(LENNEW);
         mLength = Decimal::tostring(v, mData + LENOLD, true) - mData;;
         return *thiss();
      }

      /// <summary>
      /// Helper for appending number in any encoding.
      /// </summary>
      template<typename T>
      INLINE S& _appendEncoded(const T v, const char* alphabet)
      {
         const auto base = S::strlen(alphabet);
         BaseX::tostring(v, *thiss(), base, alphabet);
         return *thiss();
      }

   public:
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // EMPTY/SIZE CONSTRUCTOR + DESTRUCTOR
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
      /// <summary>
      /// Empty Constructor
      /// </summary>
      INLINE String8() { thiss()->_ctrempty((size_t)0); }

      /// <summary>
      /// Constructor with specified capacity
      /// </summary>
      INLINE String8(const size_t capacity) { thiss()->_ctrempty(capacity); }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~String8()
      {
         S::free(mData);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // COPY CONSTRUCTORS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Constructor from single char
      /// </summary>
      INLINE String8(const char c)
      {
         const size_t LEN  = 1U;
         const size_t SIZE = S::calcsize(LEN);

         mLength  = LEN;
         mSize    = SIZE;
         mData    = S::alloc(SIZE);
         mData[0] = c;
         mData[1] = (char)0x00;
      }

      /// <summary>
      /// Constructor from zero terminated c-string with known length.
      /// </summary>
      INLINE String8(const char* s, const size_t length)
      {
         thiss()->_ctrfrom1ptr(s, length);
      }

      /// <summary>
      /// Constructor from zero terminated c-string with unknown length
      /// </summary>
      INLINE String8(const char* s)
      {
         thiss()->_ctrfrom1ptr(s, S::strlen(s));
      }

      /// <summary>
      /// Constructor from C++ std::string.
      /// </summary>
      INLINE String8(const ::std::string& s)
      {
         thiss()->_ctrfrom1ptr(s.c_str(), s.length());
      }

      /// <summary>
      /// Constructor from C++ std::string_view.
      /// </summary>
      INLINE String8(const ::std::string_view& s)
      {
         thiss()->_ctrfrom1ptr(s.data(), s.length());
      }

      /// <summary>
      /// Constructor from other instance.
      /// </summary>
      INLINE String8(const S& s)
      {
         const auto LEN  = s.length();
         const auto SIZE = S::calcsize(LEN);
         mLength = LEN;
         mSize   = SIZE;
         mData   = S::alloc(SIZE);
         S::clonecopy(mData, s.data(), LEN);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CONCATENATION CONSTRUCTORS (SAME TYPE)
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Concatenation Constructor from two single characters
      /// </summary>
      INLINE String8(const char c1, const char c2)
      {
         const size_t LEN  = 2U;
         const size_t SIZE = S::calcsize(LEN);

         mLength  = LEN;
         mSize    = SIZE;
         mData    = S::alloc(SIZE);
         mData[0] = c1;
         mData[1] = c2;
         mData[2] = (char)0x00;
      }

      /// <summary>
      /// Concatenation Constructor from two zero terminated c-string with known length.
      /// </summary>
      INLINE String8(const char* s1, const size_t len1, const char* s2, const size_t len2)
      {
         thiss()->_ctrfrom2ptr(s1, len1, s2, len2);
      }

      /// <summary>
      /// Concatenation Constructor from two zero terminated c-string with unknown length.
      /// </summary>
      INLINE String8(const char* s1, const char* s2)
      {
         thiss()->_ctrfrom2ptr(s1, S::strlen(s1), s2, S::strlen(s2));
      }

      /// <summary>
      /// Concatenation Constructor from two C++ std::string.
      /// </summary>
      INLINE String8(const ::std::string& s1, const ::std::string& s2)
      {
         thiss()->_ctrfrom2ptr(s1.c_str(), s1.length(), s2.c_str(), s2.length());
      }

      /// <summary>
      /// Concatenation Constructor from two C++ std::string_view.
      /// </summary>
      INLINE String8(const ::std::string_view& s1, const ::std::string_view& s2)
      {
         thiss()->_ctrfrom2ptr(s1.data(), s1.length(), s2.data(), s2.length());
      }

      /// <summary>
      /// Concatenation Constructor from two other instance.
      /// </summary>
      INLINE String8(const S& s1, const S& s2)
      {
         thiss()->_ctrfrom2ptr(s1, s2.data(), s2.length());
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CONCATENATION CONSTRUCTORS (OWN TYPE + OTHER)
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Concatenation Constructor from own instance and single character.
      /// </summary>
      INLINE String8(const S& s, const char c)
      {
         const auto LEN    = s.length();
         const auto LENSUM = LEN + 1U;
         const auto SIZE   = S::calcsize(LENSUM);

         mLength = LENSUM;
         mSize   = SIZE;
         mData   = S::alloc(SIZE);

         S::clonecopy(mData, s.data(), LEN);

         mData[LEN]    = c;
         mData[LENSUM] = (char)0x00;
      }

      /// <summary>
      /// Concatenation Constructor from own instance and zero terminated c-string with known length.
      /// </summary>
      INLINE String8(const S& s1, const char* s2, const size_t len2)
      {
         thiss()->_ctrfrom2ptr(s1, s2, len2);
      }

      /// <summary>
      /// Concatenation Constructor from own instance and zero terminated c-string with unknown length.
      /// </summary>
      INLINE String8(const S& s1, const char* s2)
      {
         thiss()->_ctrfrom2ptr(s1, s2, S::strlen(s2));
      }

      /// <summary>
      /// Concatenation Constructor from own instance and C++ std::string.
      /// </summary>
      INLINE String8(const S& s1, const ::std::string& s2)
      {
         thiss()->_ctrfrom2ptr(s1, s2.data(), s2.length());
      }

      /// <summary>
      /// Concatenation Constructor from own instance and C++ std::string_view.
      /// </summary>
      INLINE String8(const S& s1, const ::std::string_view& s2)
      {
         thiss()->_ctrfrom2ptr(s1, s2.data(), s2.length());
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CONCATENATION CONSTRUCTORS (OTHER + OWN TYPE)
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Concatenation Constructor from single character and own instance.
      /// </summary>
      INLINE String8(const char c, const S& s)
      {
         const auto LEN    = s.length();
         const auto LENSUM = LEN + 1U;
         const auto SIZE   = S::calcsize(LENSUM);

         mLength  = LENSUM;
         mSize    = SIZE;
         mData    = S::alloc(SIZE);
         mData[0] = c;

         Memory::copy(mData+1U, s.c_str(), LEN+1U);
      }

      /// <summary>
      /// Concatenation Constructor from zero terminated c-string with known length and own instance.
      /// </summary>
      INLINE String8(const char* s1, const size_t len1, const S& s2)
      {
         thiss()->_ctrfrom2ptr(s1, len1, s2.c_str(), s2.length());
      }

      /// <summary>
      /// Concatenation Constructor from zero terminated c-string with unknown length and own instance.
      /// </summary>
      INLINE String8(const char* s1, const S& s2)
      {
         thiss()->_ctrfrom2ptr(s1, S::strlen(s1), s2.c_str(), s2.length());
      }

      /// <summary>
      /// Concatenation Constructor from C++ std::string and own instance.
      /// </summary>
      INLINE String8(const ::std::string& s1, const S& s2)
      {
         thiss()->_ctrfrom2ptr(s1.c_str(), s1.length(), s2.c_str(), s2.length());
      }

      /// <summary>
      /// Concatenation Constructor from C++ std::string_view and own instance.
      /// </summary>
      INLINE String8(const ::std::string_view& s1, const S& s2)
      {
         thiss()->_ctrfrom2ptr(s1.data(), s1.length(), s2.c_str(), s2.length());
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // DECIMAL STRING FROM VALUE
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns string with decimal encoding of v.
      /// </summary>
      INLINE static S decimal(const uint16_t v)
      {
         S s(CPPCORE_MAXLENGTH_B10_16U);
         s.appendDecimal(v);
         return s;
      }

      /// <summary>
      /// Returns string with decimal encoding of v.
      /// </summary>
      INLINE static S decimal(const uint32_t v)
      {
         S s(CPPCORE_MAXLENGTH_B10_32U);
         s.appendDecimal(v);
         return s;
      }

      /// <summary>
      /// Returns string with decimal encoding of v.
      /// </summary>
      INLINE static S decimal(const uint64_t v)
      {
         S s(CPPCORE_MAXLENGTH_B10_64U);
         s.appendDecimal(v);
         return s;
      }

      /// <summary>
      /// Returns string with decimal encoding of v.
      /// </summary>
      INLINE static S decimal(const int16_t v)
      {
         S s(CPPCORE_MAXLENGTH_B10_16S);
         s.appendDecimal(v);
         return s;
      }

      /// <summary>
      /// Returns string with decimal encoding of v.
      /// </summary>
      INLINE static S decimal(const int32_t v)
      {
         S s(CPPCORE_MAXLENGTH_B10_32S);
         s.appendDecimal(v);
         return s;
      }

      /// <summary>
      /// Returns string with decimal encoding of v.
      /// </summary>
      INLINE static S decimal(const int64_t v)
      {
         S s(CPPCORE_MAXLENGTH_B10_64S);
         s.appendDecimal(v);
         return s;
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // HEX STRING FROM VALUE
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns string with hex encoding of v.
      /// </summary>
      INLINE static S hex(const uint16_t v, const bool bigendian = true)
      {
         S s(CPPCORE_MAXLENGTH_B16_16);
         s.appendHex(v, bigendian);
         return s;
      }

      /// <summary>
      /// Returns string with hex encoding of v.
      /// </summary>
      INLINE static S hex(const uint32_t v, const bool bigendian = true)
      {
         S s(CPPCORE_MAXLENGTH_B16_32);
         s.appendHex(v, bigendian);
         return s;
      }

      /// <summary>
      /// Returns string with hex encoding of v.
      /// </summary>
      INLINE static S hex(const uint64_t v, const bool bigendian = true)
      {
         S s(CPPCORE_MAXLENGTH_B16_64);
         s.appendHex(v, bigendian);
         return s;
      }

      /// <summary>
      /// Returns string with hex encoding of v.
      /// </summary>
      INLINE static S hex(const int16_t v, const bool bigendian = true)
      {
         S s(CPPCORE_MAXLENGTH_B16_16);
         s.appendHex(v, bigendian);
         return s;
      }

      /// <summary>
      /// Returns string with hex encoding of v.
      /// </summary>
      INLINE static S hex(const int32_t v, const bool bigendian = true)
      {
         S s(CPPCORE_MAXLENGTH_B16_32);
         s.appendHex(v, bigendian);
         return s;
      }

      /// <summary>
      /// Returns string with hex encoding of v.
      /// </summary>
      INLINE static S hex(const int64_t v, const bool bigendian = true)
      {
         S s(CPPCORE_MAXLENGTH_B16_64);
         s.appendHex(v, bigendian);
         return s;
      }

      /// <summary>
      /// Returns string with hex encoding of v.
      /// </summary>
      INLINE static S hex(const void* mem, const size_t len, const bool bigendian = true)
      {
         S s(len << 1U);
         s.appendHex(mem, len, bigendian);
         return s;
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // BASEX STRING FROM VALUE
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns string with v encoded using alphabet.
      /// </summary>
      INLINE static S basex(const uint16_t v, const char* alphabet)
      {
         S s;
         s.appendEncoded(v, alphabet);
         return s;
      }

      /// <summary>
      /// Returns string with v encoded using alphabet.
      /// </summary>
      INLINE static S basex(const uint32_t v, const char* alphabet)
      {
         S s;
         s.appendEncoded(v, alphabet);
         return s;
      }

      /// <summary>
      /// Returns string with v encoded using alphabet.
      /// </summary>
      INLINE static S basex(const uint64_t v, const char* alphabet)
      {
         S s;
         s.appendEncoded(v, alphabet);
         return s;
      }

      /// <summary>
      /// Returns string with v encoded using alphabet.
      /// </summary>
      INLINE static S basex(const int16_t v, const char* alphabet)
      {
         S s;
         s.appendEncoded(v, alphabet);
         return s;
      }

      /// <summary>
      /// Returns string with v encoded using alphabet.
      /// </summary>
      INLINE static S basex(const int32_t v, const char* alphabet)
      {
         S s;
         s.appendEncoded(v, alphabet);
         return s;
      }

      /// <summary>
      /// Returns string with v encoded using alphabet.
      /// </summary>
      INLINE static S basex(const int64_t v, const char* alphabet)
      {
         S s;
         s.appendEncoded(v, alphabet);
         return s;
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SMALL GETTERS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      INLINE size_t capacity()  const { return mSize - 1U; }
      INLINE size_t length()    const { return mLength; }
      INLINE size_t available() const { return mSize - mLength - 1U; }
      INLINE char*  data()      const { return mData; }
      INLINE char*  c_str()     const { return mData; }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Resets length to zero and sets termination zero accordingly.
      /// </summary>
      INLINE S& clear()
      {
         mLength  = 0U;
         mData[0] = (char)0x00;
         return *thiss();
      }

      /// <summary>
      /// Resizes the string capacity.
      /// The requested newsize must be at least the current length
      /// and must be different from the current size or else nothing will happen.
      /// </summary>
      INLINE void resize(size_t capacity)
      {
         const auto LEN  = mLength;
         const auto SIZE = mSize;

         // need one more for termination 0x00
         capacity = S::calcsize(capacity);

         // must have space for existing chars + 1 and different size
         if ((capacity > LEN) & (capacity != SIZE))
         {
            char* newmem = S::alloc(capacity);
            S::clonecopy(newmem, mData, LEN);
            S::free(mData);
            mData = newmem;
            mSize = capacity;
         }
      }

      /// <summary>
      /// Shrinks the allocated memory to the currrently required length (may apply additional padding)
      /// </summary>
      INLINE void shrink()
      {
         thiss()->resize(mLength);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ASSIGNMENT OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Assignment from single char
      /// </summary>
      INLINE S& operator= (const char c)
      {
         if (thiss()->capacity() == 0U)
            thiss()->resize(1U);
         mData[0] = c;
         mData[1] = (char)0x00;
         mLength  = 1U;
         return *thiss();
      }

      /// <summary>
      /// Assignment from zero terminated c-string with unknown length.
      /// </summary>
      INLINE S& operator= (const char* s)
      {
         thiss()->_assignfrom1ptr(s, S::strlen(s));
         return *thiss();
      }

      /// <summary>
      /// Assignment from std::string
      /// </summary>
      INLINE S& operator= (const std::string& s)
      {
         thiss()->_assignfrom1ptr(s.data(), s.length());
         return *thiss();
      }

      /// <summary>
      /// Assignment from std::string_view
      /// </summary>
      INLINE S& operator= (const std::string_view& s)
      {
         thiss()->_assignfrom1ptr(s.data(), s.length());
         return *thiss();
      }

      /// <summary>
      /// Assignment from other instance
      /// </summary>
      INLINE S& operator= (const S& s)
      {
         const auto LEN = s.length();
         thiss()->resize(LEN);
         S::clonecopy(mData, s.data(), LEN);
         mLength = LEN;
         return *thiss();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // INDEX OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Index Operator (for const)
      /// </summary>
      INLINE char operator[](const size_t index) const { return mData[index]; }

      /// <summary>
      /// Index Operator
      /// </summary>
      INLINE char& operator[](const size_t index) { return mData[index]; }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // EQUALS FUNCTIONS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
      /// <summary>
      /// Equal Check for single character
      /// </summary>
      INLINE bool equals(const char c, const bool casesensitive = true) const
      {
         return mLength == 1U && (casesensitive ? mData[0] == c : S::tolower(mData[0]) == S::tolower(c));
      }

      /// <summary>
      /// Equal Check for C-String with zero termination and known length
      /// </summary>
      INLINE bool equals(const char* s, const size_t len, const bool casesensitive = true) const
      {
         if (mLength == len)
         {
            if (casesensitive)
               return Memory::equal(mData, s, len);

            else
            {
               for (size_t i = 0; i < len; i++)
                  if (S::tolower(mData[i]) != S::tolower(s[i]))
                     return false;

               return true;
            }
         }
         else
            return false;
      }

      /// <summary>
      /// Equal Check for C-String with zero termination and unknown length
      /// </summary>
      INLINE bool equals(const char* s, const bool casesensitive = true) const
      {
         const size_t LEN = mLength;
         size_t i;
         if (casesensitive)
         {
            for (i = 0; i < LEN; i++)
               if (s[i] != mData[i] || s[i] == 0)
                  return false;
         }
         else
         {
            for (i = 0; i < LEN; i++)
               if (S::tolower(s[i]) != S::tolower(mData[i]) || s[i] == 0)
                  return false;
         }
         if (s[i] != 0x00)
            return false;
         return true;
      }

      /// <summary>
      /// Equal Check for std::string
      /// </summary>
      INLINE bool equals(const std::string& s, const bool casesensitive = true) const
      {
         return thiss()->equals(s.data(), s.length(), casesensitive);
      }

      /// <summary>
      /// Equal Check for std::string_view
      /// </summary>
      INLINE bool equals(const std::string_view& s, const bool casesensitive = true) const
      {
         return thiss()->equals(s.data(), s.length(), casesensitive);
      }

      /// <summary>
      /// Equal Check for own type
      /// </summary>
      INLINE bool equals(const S& s, const bool casesensitive = true) const
      {
         return thiss()->equals(s.data(), s.length(), casesensitive);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // COMPARISON OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Equal Operator same type
      /// </summary>
      INLINE bool operator == (const S& v) const
      {
         return thiss()->equals(v);
      }

      /// <summary>
      /// Equal Operator std::string
      /// </summary>
      INLINE bool operator == (const std::string& v) const
      {
         return thiss()->equals(v);
      }

      /// <summary>
      /// Equal Operator std::string_view
      /// </summary>
      INLINE bool operator == (const std::string_view& v) const
      {
         return thiss()->equals(v);
      }

      /// <summary>
      /// Equal Operator c-string
      /// </summary>
      INLINE bool operator == (const char* v) const
      {
         return thiss()->equals(v);
      }

      /// <summary>
      /// Unequal Operator
      /// </summary>
      INLINE bool operator != (const S& v) const
      {
         return !(*thiss() == v);
      }

      /// <summary>
      /// Unequal Operator
      /// </summary>
      INLINE bool operator != (const std::string& v) const
      {
         return !(*thiss() == v);
      }

      /// <summary>
      /// Unequal Operator
      /// </summary>
      INLINE bool operator != (const std::string_view& v) const
      {
         return !(*thiss() == v);
      }
      
      /// <summary>
      /// Unequal Operator
      /// </summary>
      INLINE bool operator != (const char* v) const
      {
         return !(*thiss() == v);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // APPEND STRING FUNCTIONS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Append Single Character
      /// </summary>
      INLINE S& append(const char c)
      {
         const auto LENTHIS  = mLength;
         const auto LENSUM   = LENTHIS + 1U;

         if (LENSUM >= mSize)
            thiss()->resize(LENSUM);

         mData[LENTHIS]   = c;
         mData[LENTHIS+1] = (char)0x00;

         mLength = LENSUM;
         return *thiss();
      }

      /// <summary>
      /// Append C-String with zero termination and known length
      /// </summary>
      INLINE S& append(const char* v, const size_t len)
      {
         const auto LENTHIS = mLength;
         const auto LENSUM  = LENTHIS + len;

         if (LENSUM >= mSize)
            thiss()->resize(LENSUM);

         Memory::copy(mData + LENTHIS, v, len + 1);

         mLength = LENSUM;
         return *thiss();
      }

      /// <summary>
      /// Append C-String with zero termination and unknown length
      /// </summary>
      INLINE S& append(const char* s)
      {
         return thiss()->append(s, S::strlen(s));
      }

      /// <summary>
      /// Append C++ std::string
      /// </summary>
      INLINE S& append(const std::string& s)
      {
         return thiss()->append(s.c_str(), s.length());
      }

      /// <summary>
      /// Append C++ std::string_view
      /// </summary>
      INLINE S& append(const std::string_view& s)
      {
         return thiss()->append(s.data(), s.length());
      }

      /// <summary>
      /// Append Own Type
      /// </summary>
      INLINE S& append(const S& s)
      {
         return thiss()->append(s.c_str(), s.length());
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // APPEND DECIMAL FUNCTIONS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Append v in decimal encoding.
      /// </summary>
      INLINE S& appendDecimal(const uint16_t v)
      {
         return thiss()->template _appendDecimal<uint16_t, CPPCORE_MAXLENGTH_B10_16U>(v);
      }

      /// <summary>
      /// Append v in decimal encoding.
      /// </summary>
      INLINE S& appendDecimal(const uint32_t v)
      {
         return thiss()->template _appendDecimal<uint32_t, CPPCORE_MAXLENGTH_B10_32U>(v);
      }

      /// <summary>
      /// Append v in decimal encoding.
      /// </summary>
      INLINE S& appendDecimal(const uint64_t v)
      {
         return thiss()->template _appendDecimal<uint64_t, CPPCORE_MAXLENGTH_B10_64U>(v);
      }

      /// <summary>
      /// Append v in decimal encoding.
      /// </summary>
      INLINE S& appendDecimal(const int16_t v)
      {
         return thiss()->template _appendDecimal<int16_t, CPPCORE_MAXLENGTH_B10_16S>(v);
      }

      /// <summary>
      /// Append v in decimal encoding.
      /// </summary>
      INLINE S& appendDecimal(const int32_t v)
      {
         return thiss()->template _appendDecimal<int32_t, CPPCORE_MAXLENGTH_B10_32S>(v);
      }

      /// <summary>
      /// Append v in decimal encoding.
      /// </summary>
      INLINE S& appendDecimal(const int64_t v)
      {
         return thiss()->template _appendDecimal<int64_t, CPPCORE_MAXLENGTH_B10_64S>(v);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // APPEND HEX FUNCTIONS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Append integer in hex encoding.
      /// </summary>
      template<typename T, size_t N = sizeof(T)*2>
      INLINE S& appendHex(const T v, const bool bigendian = true)
      {
         const auto LENOLD = mLength;
         const auto LENNEW = LENOLD + N;
         if (thiss()->available() < N)
            thiss()->resize(LENNEW);
         Hex::tostring(v, mData + LENOLD, bigendian, true);
         mLength = LENNEW; // always writes N symbols
         //mLength = Hex::tostring(v, mData + LENOLD, true) - mData;;
         return *thiss();
      }

      /// <summary>
      /// Append memory with len in hex encoding.
      /// </summary>
      INLINE S& appendHex(const void* mem, const size_t len, const bool reverse = false)
      {
         const auto LENMEM = len << 1U;
         const auto LENOLD = mLength;
         const auto LENNEW = LENOLD + LENMEM;
         if (thiss()->available() < LENMEM)
            thiss()->resize(LENNEW);
         Hex::encode(mem, mData + LENOLD, len, reverse, true);
         mLength = LENNEW;
         return *thiss();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // APPEND ENCODED FUNCTIONS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Append v encoded in alphabet.
      /// </summary>
      INLINE S& appendEncoded(const uint16_t v, const char* alphabet)
      {
         return thiss()->template _appendEncoded<uint16_t>(v, alphabet);
      }

      /// <summary>
      /// Append v encoded in alphabet.
      /// </summary>
      INLINE S& appendEncoded(const uint32_t v, const char* alphabet)
      {
         return thiss()->template _appendEncoded<uint32_t>(v, alphabet);
      }

      /// <summary>
      /// Append v encoded in alphabet.
      /// </summary>
      INLINE S& appendEncoded(const uint64_t v, const char* alphabet)
      {
         return thiss()->template _appendEncoded<uint64_t>(v, alphabet);
      }

      /// <summary>
      /// Append v encoded in alphabet.
      /// </summary>
      INLINE S& appendEncoded(const int16_t v, const char* alphabet)
      {
         return thiss()->template _appendEncoded<int16_t>(v, alphabet);
      }

      /// <summary>
      /// Append v encoded in alphabet.
      /// </summary>
      INLINE S& appendEncoded(const int32_t v, const char* alphabet)
      {
         return thiss()->template _appendEncoded<int32_t>(v, alphabet);
      }

      /// <summary>
      /// Append v encoded in alphabet.
      /// </summary>
      INLINE S& appendEncoded(const int64_t v, const char* alphabet)
      {
         return thiss()->template _appendEncoded<int64_t>(v, alphabet);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // APPEND OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      INLINE S& operator += (const char c)              { return thiss()->append(c); }
      INLINE S& operator += (const char* s)             { return thiss()->append(s); }
      INLINE S& operator += (const std::string& s)      { return thiss()->append(s); }
      INLINE S& operator += (const std::string_view& s) { return thiss()->append(s); }
      INLINE S& operator += (const S& s)                { return thiss()->append(s); }

      //INLINE S& operator += (const uint16_t v)          { return thiss()->appendDecimal(v); }
      //INLINE S& operator += (const uint32_t v)          { return thiss()->appendDecimal(v); }
      //INLINE S& operator += (const uint64_t v)          { return thiss()->appendDecimal(v); }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CAST/CONVERT OPERATORS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      INLINE operator std::string()      const { return ::std::string(mData, mLength);      }
      INLINE operator std::string_view() const { return ::std::string_view(mData, mLength); }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // INSERT FUNCTIONS
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Insert Single Character
      /// </summary>
      INLINE S& insert(const char c, const size_t idx)
      {
         const size_t LEN  = mLength;
         if (idx <= LEN)
         {
            const size_t LENS = LEN + 1U;
            if (LENS >= mSize)
               thiss()->resize(LENS);
            Memory::copy(&mData[idx + 1U], &mData[idx], LEN - idx);
            mData[idx] = c;
            mData[LENS] = (char)0x00;
            mLength = LENS;
         }
         return *thiss();
      }

      /// <summary>
      /// Insert C-String with zero termination and known length
      /// </summary>
      INLINE S& insert(const char* s, const size_t len, const size_t idx)
      {
         const size_t LEN  = mLength;
         if (idx <= LEN)
         {
            const size_t LENS = LEN + len;
            if (LENS >= mSize)
               thiss()->resize(LENS);
            Memory::copy(&mData[idx + len], &mData[idx], LEN - idx);
            Memory::copy(&mData[idx], s, len);
            mData[LENS] = (char)0x00;
            mLength = LENS;
         }
         return *thiss();
      }

      /// <summary>
      /// Insert C-String with zero termination and unknown length
      /// </summary>
      INLINE S& insert(const char* s, const size_t idx)
      {
         return thiss()->insert(s, S::strlen(s), idx);
      }

      /// <summary>
      /// Insert C++ std::string
      /// </summary>
      INLINE S& insert(const std::string& s, const size_t idx)
      {
         return thiss()->insert(s.c_str(), s.length(), idx);
      }

      /// <summary>
      /// Insert C++ std::string_view
      /// </summary>
      INLINE S& insert(const std::string_view& s, const size_t idx)
      {
         return thiss()->insert(s.data(), s.length(), idx);
      }

      /// <summary>
      /// Insert Own Type
      /// </summary>
      INLINE S& insert(const S& s, const size_t idx)
      {
         return thiss()->insert(s.c_str(), s.length(), idx);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // REMOVE
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Remove substring from idx with len.
      /// </summary>
      INLINE S& remove(const size_t idx, const size_t len)
      {
         const size_t LEN = mLength;
         const size_t END = idx + len;
         if (END <= LEN)
         {
            const size_t LENNEW = LEN - len;
            Memory::copy(&mData[idx], &mData[END], LENNEW - idx);
            mData[LENNEW] = (char)0x00;
            mLength = LENNEW;
         }
         return *thiss();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // REPLACE
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Replace all occurences of oldc by newc starting from startidx.
      /// </summary>
      INLINE S& replace(const char oldc, const char newc, const size_t startidx = 0)
      {
         const size_t LEN = mLength;
         for (size_t i = startidx; i < LEN; i++)
            if (mData[i] == oldc)
               mData[i] = newc;
         return *thiss();
      }

      // TODO: Replace for Strings
      // TODO: Replace as combined remove() + insert()

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SUBSTRING
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns substring starting at idx with len.
      /// Returns substring from idx until the end if len is too large.
      /// Returns empty string if idx is invalid.
      /// </summary>
      INLINE S substring(const size_t idx, const size_t len) const
      {
         const size_t END = idx + len;
         const size_t LEN = mLength;
         return (END <= LEN) ?
            S(&mData[idx], len) : (idx < LEN) ?
            S(&mData[idx], LEN - idx) : S((size_t)0U);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // LOWER/UPPER CASE
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Converts all uppercase characters to lowercase starting from startidx.
      /// </summary>
      INLINE S& toLower(const size_t startidx = 0)
      {
         const size_t LEN = mLength;
         for (size_t i = startidx; i < LEN; i++)
         {
            const char c = mData[i];
            if (S::israngechar(c, 'A', 'Z'))
               mData[i] = c + (char)0x20;
         }
         return *thiss();
      }

      /// <summary>
      /// Converts all lowercase characters to uppercase starting from startidx.
      /// </summary>
      INLINE S& toUpper(const size_t startidx = 0)
      {
         const size_t LEN = mLength;
         for (size_t i = startidx; i < LEN; i++)
         {
            const char c = mData[i];
            if (S::israngechar(c, 'a', 'z'))
               mData[i] = c - (char)0x20;
         }
         return *thiss();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // REVERSE
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Reverses string (e.g. turns 'abc' into 'cba')
      /// </summary>
      INLINE S& reverse()
      {
         Memory::reverse(mData, mLength);
         return *thiss();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STARTSWITH
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns true if string starts with character c.
      /// </summary>
      INLINE bool startsWith(const char c) const
      {
         return mLength && mData[0] == c;
      }

      /// <summary>
      /// Returns true if string starts with c-string with known length
      /// </summary>
      INLINE bool startsWith(const char* s, const size_t len) const
      {
         return mLength >= len && Memory::equal(mData, s, len);
      }

      /// <summary>
      /// Returns true if string starts with c-string with unknown length
      /// </summary>
      INLINE bool startsWith(const char* s) const
      {
         return thiss()->startsWith(s, S::strlen(s));
      }

      /// <summary>
      /// Returns true if string starts with std::string
      /// </summary>
      INLINE bool startsWith(const std::string& s) const
      {
         return thiss()->startsWith(s.data(), s.length());
      }

      /// <summary>
      /// Returns true if string starts with std::string_view
      /// </summary>
      INLINE bool startsWith(const std::string_view& s) const
      {
         return thiss()->startsWith(s.data(), s.length());
      }

      /// <summary>
      /// Returns true if string starts with string of same type
      /// </summary>
      INLINE bool startsWith(const S& s) const
      {
         return thiss()->startsWith(s.data(), s.length());
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ENDSWITH
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns true if string ends with character c.
      /// </summary>
      INLINE bool endsWith(const char c) const
      {
         const size_t LEN = mLength;
         return LEN && mData[LEN-1U] == c;
      }

      /// <summary>
      /// Returns true if string ends with c-string with known length
      /// </summary>
      INLINE bool endsWith(const char* s, const size_t len) const
      {
         const size_t LEN = mLength;
         return LEN >= len ? Memory::equal(&mData[LEN - len], s, len) : false;
      }

      /// <summary>
      /// Returns true if string ends with c-string with unknown length
      /// </summary>
      INLINE bool endsWith(const char* s) const
      {
         return thiss()->endsWith(s, S::strlen(s));
      }

      /// <summary>
      /// Returns true if string ends with std::string
      /// </summary>
      INLINE bool endsWith(const std::string& s) const
      {
         return thiss()->endsWith(s.data(), s.length());
      }

      /// <summary>
      /// Returns true if string ends with std::string_view
      /// </summary>
      INLINE bool endsWith(const std::string_view& s) const
      {
         return thiss()->endsWith(s.data(), s.length());
      }

      /// <summary>
      /// Returns true if string ends with string of same type
      /// </summary>
      INLINE bool endsWith(const S& s) const
      {
         return thiss()->endsWith(s.data(), s.length());
      }



      // BELOW IS STILL WIP



      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // FINDFIRST
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns index of first occurence of character c or npos if not found.
      /// </summary>
      INLINE size_t findFirst(const char c, const size_t startidx = 0U) const
      {
         const size_t LEN = mLength;
         if (startidx < LEN)
         {
            const size_t idx = Memory::byteidxf(&mData[startidx], LEN - startidx, c);
            return (idx != std::numeric_limits<size_t>::max()) ? idx + startidx : idx;
         }
         return S::npos();
      }

      /// <summary>
      /// Returns index of first occurence of C-String with known length or npos if not found.
      /// </summary>
      INLINE size_t findFirst(const char* s, const size_t len, size_t idx = 0U) const
      {
         //TODO: This needs optimization
         const size_t LEN = mLength;
         if (LEN >= len + idx)
         {
            const size_t LST = LEN - len;
            for (; idx <= LST; idx++)
            {
               size_t j;
               for (j = 0; j < len; j++)
                  if (s[j] != mData[idx + j])
                     break;
               if (j == len)
                  return idx;
            }
         }
         return S::npos();
      }

      /// <summary>
      /// Returns index of first occurence of C-String with unknown length or npos if not found.
      /// </summary>
      INLINE size_t findFirst(const char* s, const size_t startidx = 0U) const
      {
         return thiss()->findFirst(s, S::strlen(s), startidx);
      }

      /// <summary>
      /// Returns index of first occurence of std::string or npos if not found.
      /// </summary>
      INLINE size_t findFirst(const ::std::string& s, const size_t startidx = 0U) const
      {
         return thiss()->findFirst(s.data(), s.length(), startidx);
      }

      /// <summary>
      /// Returns index of first occurence of std::string_view or npos if not found.
      /// </summary>
      INLINE size_t findFirst(const ::std::string_view& s, const size_t startidx = 0U) const
      {
         return thiss()->findFirst(s.data(), s.length(), startidx);
      }

      /// <summary>
      /// Returns index of first occurence of other instance of same type or npos if not found.
      /// </summary>
      INLINE size_t findFirst(const S& s, const size_t startidx = 0U) const
      {
         return thiss()->findFirst(s.data(), s.length(), startidx);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // FINDLAST
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns index of last occurence of character c or npos if not found.
      /// </summary>
      INLINE size_t findLast(const char c) const
      {
         // TODO: Optimize this, see findFirst(char)
         size_t i;
         for (i = mLength - 1U; i != std::numeric_limits<size_t>::max(); i--)
            if (mData[i] == c)
               return i;
         return i;
      }

      /// <summary>
      /// Returns index of last occurence of C-String with known length or npos if not found.
      /// </summary>
      INLINE size_t findLast(const char* s, const size_t len) const
      {
         //TODO: This needs optimization
         const size_t LEN = mLength;
         if (LEN >= len)
         {
            const size_t LST = LEN - len;
            for (size_t i = LST; i != std::numeric_limits<size_t>::max(); i--)
            {
               size_t j;
               for (j = 0; j < len; j++)
                  if (s[j] != mData[i + j])
                     break;
               if (j == len)
                  return i;
            }
         }
         return S::npos();
      }

      /// <summary>
      /// Returns index of last occurence of C-String with unknown length or npos if not found.
      /// </summary>
      INLINE size_t findLast(const char* s) const
      {
         return thiss()->findLast(s, S::strlen(s));
      }

      /// <summary>
      /// Returns index of last occurence of std::string or npos if not found.
      /// </summary>
      INLINE size_t findLast(const std::string& s) const
      {
         return thiss()->findLast(s.data(), s.length());
      }

      /// <summary>
      /// Returns index of last occurence of std::string_view or npos if not found.
      /// </summary>
      INLINE size_t findLast(const std::string_view& s) const
      {
         return thiss()->findLast(s.data(), s.length());
      }

      /// <summary>
      /// Returns index of last occurence of string of same type or npos if not found.
      /// </summary>
      INLINE size_t findLast(const S& s) const
      {
         return thiss()->findLast(s.data(), s.length());
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // TRIM
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Removes all leading and trailing characters that match c.
      /// </summary>
      INLINE S& trim(const char c = ' ')
      {
         const size_t LEN = mLength;
         if (LEN > 0)
         {
            const size_t LAST = LEN - 1U;

            // search left
            size_t s;
            for (s = 0; s < LEN; s++)
               if (mData[s] != c)
                  break;

            // only white spaces
            if (s >= LEN)
            {
               mData[0] = 0x00;
               mLength  = 0U;
               return *thiss();
            }

            // search right
            size_t e;
            for (e = LAST; e != std::numeric_limits<size_t>::max(); e--)
               if (mData[e] != c)
                  break;

            // trim start only
            if ((s > 0U) & (e == LAST))
            {
               const size_t NLEN = LEN - s;
               Memory::copy(mData, &mData[s], NLEN);
               mData[NLEN] = 0x00;
               mLength     = NLEN;
            }
            // trim end only
            else if ((s == 0U) & (e < LAST))
            {
               const size_t NLEN = e + 1;
               mData[NLEN] = 0x00;
               mLength     = NLEN;
            }
            // trim both
            else if ((s > 0U) & (e < LAST))
            {
               const size_t NLEN = e + 1 - s;
               Memory::copy(mData, &mData[s], NLEN);
               mData[NLEN] = 0x00;
               mLength     = NLEN;
            }
            // nothing to trim
            else { }
         }
         return *thiss();
      }
   };

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Generic String with Dynamic Size
   /// </summary>
   class String8g : public String8<String8g>
   {
      typedef String8<String8g> String8gb;
      friend  String8gb;

   public:
      INLINE String8g()                                                     : String8gb()         { }
      INLINE String8g(const size_t capacity)                                : String8gb(capacity) { }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8g(const char c)                                         : String8gb(c)      { }
      INLINE String8g(const char* s, const size_t len)                      : String8gb(s, len) { }
      INLINE String8g(const char* s)                                        : String8gb(s)      { }
      INLINE String8g(const ::std::string& s)                               : String8gb(s)      { }
      INLINE String8g(const ::std::string_view& s)                          : String8gb(s)      { }
      INLINE String8g(const String8g& s)                                    : String8gb(s)      { }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8g(const char c1, const char c2)                          : String8gb(c1, c2)             { }
      INLINE String8g(const char* s1, const size_t len1, 
                      const char* s2, const size_t len2)                     : String8gb(s1, len1, s2, len2) { }
      INLINE String8g(const char* s1, const char* s2)                        : String8gb(s1, s2)             { }
      INLINE String8g(const ::std::string& s1, const ::std::string& s2)      : String8gb(s1, s2)             { }
      INLINE String8g(const ::std::string_view& s1, 
                      const ::std::string_view& s2)                          : String8gb(s1, s2)             { }
      INLINE String8g(const String8g& s1, const String8g& s2)                : String8gb(s1, s2)             { }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8g(const String8g& s,  const char c)                      : String8gb(s, c)         { }
      INLINE String8g(const String8g& s1, const char* s2, const size_t len2) : String8gb(s1, s2, len2) { }
      INLINE String8g(const String8g& s1, const char* s2)                    : String8gb(s1, s2)       { }
      INLINE String8g(const String8g& s1, const ::std::string& s2)           : String8gb(s1, s2)       { }
      INLINE String8g(const String8g& s1, const ::std::string_view& s2)      : String8gb(s1, s2)       { }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8g(const char c, const String8g& s)                       : String8gb(c, s)         { }
      INLINE String8g(const char* s1, size_t len1, const String8g& s2)       : String8gb(s1, len1, s2) { }
      INLINE String8g(const char* s1, const String8g& s2)                    : String8gb(s1, s2)       { }
      INLINE String8g(const ::std::string& s1, const String8g& s2)           : String8gb(s1, s2)       { }
      INLINE String8g(const ::std::string_view& s1, const String8g& s2)      : String8gb(s1, s2)       { }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8g& operator= (const char  c)             { return String8gb::operator=(c); }
      INLINE String8g& operator= (const char* s)             { return String8gb::operator=(s); }
      INLINE String8g& operator= (const std::string& s)      { return String8gb::operator=(s); }
      INLINE String8g& operator= (const std::string_view& s) { return String8gb::operator=(s); }
      INLINE String8g& operator= (const String8g& s)         { return String8gb::operator=(s); }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8g& operator= (const uint16_t) = delete;
      INLINE String8g& operator= (const uint32_t) = delete;
      INLINE String8g& operator= (const uint64_t) = delete;
      INLINE String8g& operator= (const int16_t)  = delete;
      INLINE String8g& operator= (const int32_t)  = delete;
      INLINE String8g& operator= (const int64_t)  = delete;
   };

   INLINE static String8g operator + (const String8g&           s1, const String8g&           s2) { return String8g(s1, s2); }
   INLINE static String8g operator + (const String8g&           s,  const char                c)  { return String8g(s, c);   }
   INLINE static String8g operator + (const String8g&           s1, const char*               s2) { return String8g(s1, s2); }
   INLINE static String8g operator + (const String8g&           s1, const ::std::string&      s2) { return String8g(s1, s2); }
   INLINE static String8g operator + (const String8g&           s1, const ::std::string_view& s2) { return String8g(s1, s2); }
   INLINE static String8g operator + (const char                c,  const String8g&           s)  { return String8g(c, s);   }
   INLINE static String8g operator + (const char*               s1, const String8g&           s2) { return String8g(s1, s2); }
   INLINE static String8g operator + (const ::std::string&      s1, const String8g&           s2) { return String8g(s1, s2); }
   INLINE static String8g operator + (const ::std::string_view& s1, const String8g&           s2) { return String8g(s1, s2); }
   INLINE static std::ostream& operator << (std::ostream& os, const String8g& v) { os.write(v.data(), v.length()); return os; }

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// Optimized String with Dynamic Size
   /// </summary>
   class String8s : public String8<String8s>
   {
      typedef String8<String8s> String8sb;
      friend  String8sb;

   public:
      INLINE static char* alloc(const size_t size) { return Memory::alignedalloc(size, 16); }
      INLINE static void  free (void* mem)         { return Memory::alignedfree(mem); }
      INLINE static size_t calcsize(size_t capacity)
      {
         return CppCore::rupptwo(capacity + 1U, (size_t)16U);
      }
   #if defined(CPPCORE_CPUFEAT_SSE2)
      INLINE static void clonecopy(void* dst, const void* src, const size_t len)
      {
         Memory::streamcopy128x1(dst, src, len + 1U);
      }
   #endif
   public:
      INLINE String8s()                                                      : String8sb()         { }
      INLINE String8s(const size_t capacity)                                 : String8sb(capacity) { }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8s(const char c)                                          : String8sb(c)      { }
      INLINE String8s(const char* s, const size_t len)                       : String8sb(s, len) { }
      INLINE String8s(const char* s)                                         : String8sb(s)      { }
      INLINE String8s(const ::std::string& s)                                : String8sb(s)      { }
      INLINE String8s(const ::std::string_view& s)                           : String8sb(s)      { }
      INLINE String8s(const String8s& s)                                     : String8sb(s)      { }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8s(const char c1, const char c2)                          : String8sb(c1, c2)             { }
      INLINE String8s(const char* s1, const size_t len1, 
                      const char* s2, const size_t len2)                     : String8sb(s1, len1, s2, len2) { }
      INLINE String8s(const char* s1, const char* s2)                        : String8sb(s1, s2)             { }
      INLINE String8s(const ::std::string& s1, const ::std::string& s2)      : String8sb(s1, s2)             { }
      INLINE String8s(const ::std::string_view& s1, 
                      const ::std::string_view& s2)                          : String8sb(s1, s2)             { }
      INLINE String8s(const String8s& s1, const String8s& s2)                : String8sb(s1, s2)             { }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8s(const String8s& s,  const char c)                      : String8sb(s, c)         { }
      INLINE String8s(const String8s& s1, const char* s2, const size_t len2) : String8sb(s1, s2, len2) { }
      INLINE String8s(const String8s& s1, const char* s2)                    : String8sb(s1, s2)       { }
      INLINE String8s(const String8s& s1, const ::std::string& s2)           : String8sb(s1, s2)       { }
      INLINE String8s(const String8s& s1, const ::std::string_view& s2)      : String8sb(s1, s2)       { }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8s(const char c, const String8s& s)                       : String8sb(c, s)         { }
      INLINE String8s(const char* s1, size_t len1, const String8s& s2)       : String8sb(s1, len1, s2) { }
      INLINE String8s(const char* s1, const String8s& s2)                    : String8sb(s1, s2)       { }
      INLINE String8s(const ::std::string& s1, const String8s& s2)           : String8sb(s1, s2)       { }
      INLINE String8s(const ::std::string_view& s1, const String8s& s2)      : String8sb(s1, s2)       { }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8s& operator= (const char  c)             { return String8sb::operator=(c); }
      INLINE String8s& operator= (const char* s)             { return String8sb::operator=(s); }
      INLINE String8s& operator= (const std::string& s)      { return String8sb::operator=(s); }
      INLINE String8s& operator= (const std::string_view& s) { return String8sb::operator=(s); }
      INLINE String8s& operator= (const String8s& s)         { return String8sb::operator=(s); }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE String8s& operator= (const uint16_t) = delete;
      INLINE String8s& operator= (const uint32_t) = delete;
      INLINE String8s& operator= (const uint64_t) = delete;
      INLINE String8s& operator= (const int16_t)  = delete;
      INLINE String8s& operator= (const int32_t)  = delete;
      INLINE String8s& operator= (const int64_t)  = delete;
   };

   INLINE static String8s operator + (const String8s&           s1, const String8s&           s2) { return String8s(s1, s2); }
   INLINE static String8s operator + (const String8s&           s,  const char                c)  { return String8s(s, c);   }
   INLINE static String8s operator + (const String8s&           s1, const char*               s2) { return String8s(s1, s2); }
   INLINE static String8s operator + (const String8s&           s1, const ::std::string&      s2) { return String8s(s1, s2); }
   INLINE static String8s operator + (const String8s&           s1, const ::std::string_view& s2) { return String8s(s1, s2); }
   INLINE static String8s operator + (const char                c,  const String8s&           s)  { return String8s(c, s);   }
   INLINE static String8s operator + (const char*               s1, const String8s&           s2) { return String8s(s1, s2); }
   INLINE static String8s operator + (const ::std::string&      s1, const String8s&           s2) { return String8s(s1, s2); }
   INLINE static String8s operator + (const ::std::string_view& s1, const String8s&           s2) { return String8s(s1, s2); }
   INLINE static std::ostream& operator << (std::ostream& os, const String8s& v) { os.write(v.data(), v.length()); return os; }

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_OPTIMIZED_STRING8)
   typedef String8s String;
#else
   typedef String8g String;
#endif
}
