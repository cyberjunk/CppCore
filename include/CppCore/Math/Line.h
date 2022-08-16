#pragma once

#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>
#include <CppCore/Math/V2.h>

namespace CppCore
{
   /// <summary>
   /// Line with two points
   /// </summary>
   template <typename L, typename V, typename F>
   class Line
   {
   protected:
      INLINE L*   thiss() const { return (L*)this; }

   public:
      V s;
      V e;
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE Line()                                    { }
      INLINE Line(const V& s, const V& e) : s(s), e(e) { }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE L&    operator +=   (const F tr) { s += tr; e += tr; return *thiss(); }
      INLINE L&    operator -=   (const F tr) { s -= tr; e -= tr; return *thiss(); }
      INLINE L&    operator *=   (const F sc) { s *= sc; e *= sc; return *thiss(); }
      INLINE L&    operator /=   (const F sc) { s /= sc; e /= sc; return *thiss(); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE L&    operator +=   (const V& tr) { s += tr; e += tr; return *thiss(); }
      INLINE L&    operator -=   (const V& tr) { s -= tr; e -= tr; return *thiss(); }
      INLINE L&    operator *=   (const V& sc) { s *= sc; e *= sc; return *thiss(); }
      INLINE L&    operator /=   (const V& sc) { s /= sc; e /= sc; return *thiss(); }
   };
   //------------------------------------------------------------------------------------------------------------------------//
   //                                 FLOATING POINT & INTEGER TEMPLATES                                                     //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 2D Line Template for Floating Point (32/64)
   /// </summary>
   template <typename L, typename V, typename F>
   class LineV2fdt : public Line<L, V, F>
   {
   public:
      INLINE bool intersectCircle(const V& m, const F r, const F eps, const bool withinside) 
      {
         return m.intersectCircleLine(this->s, this->e, r, eps, withinside);
      }
   };
   /// <summary>
   /// Abstract 2D Line Template for Integer (32/64)
   /// </summary>
   template <typename L, typename V, typename F>
   class LineV2ilt : public Line<L, V, F>
   {
   };
   //------------------------------------------------------------------------------------------------------------------------//
   //                                     GENERIC/NON-SIMD CLASSES                                                           //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Single Precision 2D Line (Generic, no SIMD)
   /// </summary>
   class LineV2fg : public LineV2fdt<LineV2fg, V2fg, float> { };

   /// <summary>
   /// Double Precision 2D Line (Generic, no SIMD)
   /// </summary>
   class LineV2dg : public LineV2fdt<LineV2dg, V2dg, double> { };

   /// <summary>
   /// 32-Bit Integer 2D Line (Generic, no SIMD)
   /// </summary>
   class LineV2ig : public LineV2ilt<LineV2ig, V2ig, int32_t> { };

   /// <summary>
   /// 64-Bit Integer 2D Line (Generic, no SIMD)
   /// </summary>
   class LineV2lg : public LineV2ilt<LineV2lg, V2lg, int64_t> { };
   //------------------------------------------------------------------------------------------------------------------------//
   //                                             SIMD CLASSES                                                               //
   //------------------------------------------------------------------------------------------------------------------------//
#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Single Precision 2D Line (SIMD)(TODO)
   /// </summary>
   class LineV2fs : public LineV2fdt<LineV2fs, V2fs, float> { };

   /// <summary>
   /// Double Precision 2D Line (SIMD)(TODO)
   /// </summary>
   class LineV2ds : public LineV2fdt<LineV2ds, V2ds, double> { };

   /// <summary>
   /// 32-Bit Integer 2D Line (SIMD)(TODO)
   /// </summary>
   class LineV2is : public LineV2ilt<LineV2is, V2is, int32_t> { };

   /// <summary>
   /// 64-Bit Integer 2D Line (SIMD)(TODO)
   /// </summary>
   class LineV2ls : public LineV2ilt<LineV2ls, V2ls, int64_t> { };
#endif

#if defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_OPTIMIZED_VECTORMATH)
   // use optimized ones as defaults
   typedef LineV2fs LineV2f;
   typedef LineV2ds LineV2d;
   typedef LineV2is LineV2i;
   typedef LineV2ls LineV2l;
#else
   // use generic ones as defaults
   typedef LineV2fg LineV2f;
   typedef LineV2dg LineV2d;
   typedef LineV2ig LineV2i;
   typedef LineV2lg LineV2l;
#endif
}
