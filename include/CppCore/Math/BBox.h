#pragma once

#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>

namespace CppCore
{
   /// <summary>
   /// Abstract Bounding Box Template for 2D/3D Floating Point (32/64) AND Integer (32/64). [L1]
   /// </summary>
   template <typename L, typename V, typename F>
   class BBox
   {
   protected:
      INLINE L* thiss() const { return (L*)this; }
   public:
      V min;
      V max;
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE BBox() { }
      INLINE BBox(const V& min, const V& max) : min(min), max(max) { }
      INLINE BBox(const V& v)                 : min(v),   max(v)   { }
      INLINE BBox(const F s)                  : min(s),   max(s)   { }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE bool  operator ==   (const L& b) const { return min == b.min && max == b.max; }
      INLINE bool  operator !=   (const L& b) const { return min != b.min || max != b.max; }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE L&    operator +=   (const F tr) { min += tr; max += tr; return *thiss(); }
      INLINE L&    operator -=   (const F tr) { min -= tr; max -= tr; return *thiss(); }
      INLINE L&    operator *=   (const F sc) { min *= sc; max *= sc; return *thiss(); }
      INLINE L&    operator /=   (const F sc) { min /= sc; max /= sc; return *thiss(); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE L&    operator +=   (const V& tr) { min += tr; max += tr; return *thiss(); }
      INLINE L&    operator -=   (const V& tr) { min -= tr; max -= tr; return *thiss(); }
      INLINE L&    operator *=   (const V& sc) { min *= sc; max *= sc; return *thiss(); }
      INLINE L&    operator /=   (const V& sc) { min /= sc; max /= sc; return *thiss(); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void extend(const V& p)       { min.min(p); max.max(p); }
      INLINE bool inside(const V& p) const { return p >= min && p <= max; }
      INLINE V    size()             const { return max - min; }
   };
}
