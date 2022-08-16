#pragma once

#include <CppCore/Root.h>

namespace CppCore
{
   /// <summary>
   /// Flexible Integer with custom length (data) and upper bits for custom usage (tag).
   /// Note 1: VALBITS + TAGBITS summed up should be 32 or 64 etc.
   /// Note 2: All operators work on data bits only and just maintain the original tag bits.
   /// </summary>
   template<typename VAL, VAL VALBITS, typename TAG, TAG TAGBITS>
   struct FlexInt
   {
      VAL data : VALBITS;
      TAG tag  : TAGBITS;

      static const VAL MASK = (((VAL)1 << VALBITS) - (VAL)1);
      static const VAL MAX  = (((VAL)1 << (VALBITS - (VAL)1)) - (VAL)1);
      static const VAL MIN  = -((VAL)1 << (VALBITS - (VAL)1));

      /// <summary>
      /// Empty Constructor
      /// </summary>
      INLINE FlexInt() { }

      /// <summary>
      /// Constructor from data and (optional) tag
      /// </summary>
      INLINE FlexInt(const VAL i, const TAG t = 0) : data(i), tag(t) { }

      /// <summary>
      /// Copy Constructor with tag override
      /// </summary>
      INLINE FlexInt(const FlexInt& i, const TAG t) : data(i.data), tag(t) { }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // ASSIGNMENT OPERATOR

      INLINE FlexInt& operator = (const FlexInt& v) { data = v.data; tag = v.tag; return *this; }
      INLINE FlexInt& operator = (const int32_t v)  { data = v; return *this; }
      INLINE FlexInt& operator = (const int64_t v)  { data = v; return *this; }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // COMPOUND ASSIGNMENT OPERATORS

      INLINE FlexInt& operator +=  (const FlexInt& v) { data +=  v.data; return *this; }
      INLINE FlexInt& operator -=  (const FlexInt& v) { data -=  v.data; return *this; }
      INLINE FlexInt& operator *=  (const FlexInt& v) { data *=  v.data; return *this; }
      INLINE FlexInt& operator /=  (const FlexInt& v) { data /=  v.data; return *this; }
      INLINE FlexInt& operator %=  (const FlexInt& v) { data %=  v.data; return *this; }
      INLINE FlexInt& operator &=  (const FlexInt& v) { data &=  v.data; return *this; }
      INLINE FlexInt& operator |=  (const FlexInt& v) { data |=  v.data; return *this; }
      INLINE FlexInt& operator ^=  (const FlexInt& v) { data ^=  v.data; return *this; }
      INLINE FlexInt& operator <<= (const FlexInt& v) { data <<= v.data; return *this; }
      INLINE FlexInt& operator >>= (const FlexInt& v) { data >>= v.data; return *this; }

      INLINE FlexInt& operator +=  (const int32_t v) { data +=  v; return *this; }
      INLINE FlexInt& operator -=  (const int32_t v) { data -=  v; return *this; }
      INLINE FlexInt& operator *=  (const int32_t v) { data *=  v; return *this; }
      INLINE FlexInt& operator /=  (const int32_t v) { data /=  v; return *this; }
      INLINE FlexInt& operator %=  (const int32_t v) { data %=  v; return *this; }
      INLINE FlexInt& operator &=  (const int32_t v) { data &=  v; return *this; }
      INLINE FlexInt& operator |=  (const int32_t v) { data |=  v; return *this; }
      INLINE FlexInt& operator ^=  (const int32_t v) { data ^=  v; return *this; }
      INLINE FlexInt& operator <<= (const int32_t v) { data <<= v; return *this; }
      INLINE FlexInt& operator >>= (const int32_t v) { data >>= v; return *this; }

      INLINE FlexInt& operator +=  (const int64_t v) { data +=  v; return *this; }
      INLINE FlexInt& operator -=  (const int64_t v) { data -=  v; return *this; }
      INLINE FlexInt& operator *=  (const int64_t v) { data *=  v; return *this; }
      INLINE FlexInt& operator /=  (const int64_t v) { data /=  v; return *this; }
      INLINE FlexInt& operator %=  (const int64_t v) { data %=  v; return *this; }
      INLINE FlexInt& operator &=  (const int64_t v) { data &=  v; return *this; }
      INLINE FlexInt& operator |=  (const int64_t v) { data |=  v; return *this; }
      INLINE FlexInt& operator ^=  (const int64_t v) { data ^=  v; return *this; }
      INLINE FlexInt& operator <<= (const int64_t v) { data <<= v; return *this; }
      INLINE FlexInt& operator >>= (const int64_t v) { data >>= v; return *this; }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // NEGATIVE/POSITIVE OPERATORS

      INLINE       FlexInt  operator - () const { return FlexInt(-data, tag); }
      INLINE const FlexInt& operator + () const { return *this; }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // INCREMENT/DECREMENT OPERATORS

      INLINE FlexInt& operator ++ () { data++; return *this; }
      INLINE FlexInt& operator -- () { data--; return *this; }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // CAST OPERATORS OPERATORS

      INLINE operator const VAL() const { return this->data; }
   };

   /////////////////////////////////////////////////////////////////////////////////////////////
   // RELATIONAL OPERATORS

   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator == (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data == v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator != (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data != v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator <  (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data <  v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator <= (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data <= v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator >  (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data >  v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator >= (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data >= v.data; }

   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator == (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data == v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator != (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data != v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator <  (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data <  v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator <= (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data <= v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator >  (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data >  v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator >= (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data >= v; }

   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator == (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i == v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator != (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i != v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator <  (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i <  v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator <= (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i <= v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator >  (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i >  v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator >= (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i >= v.data; }

   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator == (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data == v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator != (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data != v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator <  (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data <  v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator <= (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data <= v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator >  (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data >  v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator >= (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data >= v; }

   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator == (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i == v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator != (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i != v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator <  (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i <  v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator <= (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i <= v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator >  (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i >  v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE bool operator >= (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i >= v.data; }

   /////////////////////////////////////////////////////////////////////////////////////////////
   // ARITHMETIC OPERATORS

   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator+ (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data + v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator- (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data - v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator* (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data * v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator/ (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data / v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator% (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i.data % v.data; }

   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator+ (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data + v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator- (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data - v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator* (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data * v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator/ (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data / v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator% (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int32_t v) { return i.data % v; }

   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator+ (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i + v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator- (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i - v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator* (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i * v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator/ (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i / v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE VAL operator% (const int32_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i % v.data; }

   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE int64_t operator+ (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data + v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE int64_t operator- (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data - v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE int64_t operator* (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data * v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE int64_t operator/ (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data / v; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE int64_t operator% (const FlexInt<VAL, VALBITS, TAG, TAGBITS>& i, const int64_t v) { return i.data % v; }

   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE int64_t operator+ (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i + v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE int64_t operator- (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i - v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE int64_t operator* (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i * v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE int64_t operator/ (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i / v.data; }
   template<typename VAL, size_t VALBITS, typename TAG, size_t TAGBITS> INLINE int64_t operator% (const int64_t i, const FlexInt<VAL, VALBITS, TAG, TAGBITS>& v) { return i % v.data; }
}
