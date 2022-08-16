#pragma once

#include <CppCore/Math/BBox.h>
#include <CppCore/Math/V2.h>

namespace CppCore
{
   /// <summary>
   /// Abstract 2D Bounding Box Template for Floating Point (32/64) AND Integer (32/64). [L1]
   /// </summary>
   template <typename L, typename V, typename F>
   class BBox2 : public BBox<L, V, F>
   {
   public:
      INLINE BBox2()                           : BBox<L, V, F>()         { }
      INLINE BBox2(const V& min, const V& max) : BBox<L, V, F>(min, max) { }
      INLINE BBox2(const V& v)                 : BBox<L, V, F>(v)        { }
      INLINE BBox2(const F s)                  : BBox<L, V, F>(s)        { }
   };
   //------------------------------------------------------------------------------------------------------------------------//
   //                                 FLOATING POINT & INTEGER TEMPLATES                                                     //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 2D Bounding Box Template for Floating Point (32/64)
   /// </summary>
   template <typename L, typename V, typename F>
   class BBox2fdt : public BBox2<L, V, F>
   {
   public:
      INLINE BBox2fdt()                           : BBox2<L, V, F>()         { }
      INLINE BBox2fdt(const V& min, const V& max) : BBox2<L, V, F>(min, max) { }
      INLINE BBox2fdt(const V& v)                 : BBox2<L, V, F>(v)        { }
      INLINE BBox2fdt(const F s)                  : BBox2<L, V, F>(s)        { }
   };
   /// <summary>
   /// Abstract 2D Bounding Box Template for Integer (32/64)
   /// </summary>
   template <typename L, typename V, typename F>
   class BBox2ilt : public BBox2<L, V, F>
   {
   public:
      INLINE BBox2ilt()                           : BBox2<L, V, F>()         { }
      INLINE BBox2ilt(const V& min, const V& max) : BBox2<L, V, F>(min, max) { }
      INLINE BBox2ilt(const V& v)                 : BBox2<L, V, F>(v)        { }
      INLINE BBox2ilt(const F s)                  : BBox2<L, V, F>(s)        { }
#if defined(CPPCORE_OS_WINDOWS)
      INLINE BBox2ilt(const RECT& rect)           : BBox2<L, V, F>(V((F)rect.left, (F)rect.top), V((F)rect.right, (F)rect.bottom)) { }
      INLINE operator RECT() const
      {
         RECT r;
         r.left   = (LONG)this->min.x;
         r.top    = (LONG)this->min.y;
         r.right  = (LONG)this->max.x;
         r.bottom = (LONG)this->max.y;
         return r;
      }
#endif
   };
   //------------------------------------------------------------------------------------------------------------------------//
   //                                     GENERIC/NON-SIMD CLASSES                                                           //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Single Precision 2D BBox (Generic, no SIMD)
   /// </summary>
   class BBox2fg : public BBox2fdt<BBox2fg, V2fg, float> 
   {
   public:
      INLINE BBox2fg()                                 : BBox2fdt<BBox2fg, V2fg, float>()         { }
      INLINE BBox2fg(const V2fg& min, const V2fg& max) : BBox2fdt<BBox2fg, V2fg, float>(min, max) { }
      INLINE BBox2fg(const V2fg& v)                    : BBox2fdt<BBox2fg, V2fg, float>(v)        { }
      INLINE BBox2fg(const float s)                    : BBox2fdt<BBox2fg, V2fg, float>(s)        { }
   };

   /// <summary>
   /// Double Precision 2D BBox (Generic, no SIMD)
   /// </summary>
   class BBox2dg : public BBox2fdt<BBox2dg, V2dg, double> 
   {
   public:
      INLINE BBox2dg()                                 : BBox2fdt<BBox2dg, V2dg, double>()         { }
      INLINE BBox2dg(const V2dg& min, const V2dg& max) : BBox2fdt<BBox2dg, V2dg, double>(min, max) { }
      INLINE BBox2dg(const V2dg& v)                    : BBox2fdt<BBox2dg, V2dg, double>(v)        { }
      INLINE BBox2dg(const double s)                   : BBox2fdt<BBox2dg, V2dg, double>(s)        { }
   };

   /// <summary>
   /// 32-Bit Integer 2D BBox (Generic, no SIMD)
   /// </summary>
   class BBox2ig : public BBox2ilt<BBox2ig, V2ig, int32_t> 
   {
   public:
      INLINE BBox2ig()                                 : BBox2ilt<BBox2ig, V2ig, int32_t>()         { }
      INLINE BBox2ig(const V2ig& min, const V2ig& max) : BBox2ilt<BBox2ig, V2ig, int32_t>(min, max) { }
      INLINE BBox2ig(const V2ig& v)                    : BBox2ilt<BBox2ig, V2ig, int32_t>(v)        { }
      INLINE BBox2ig(const int32_t s)                  : BBox2ilt<BBox2ig, V2ig, int32_t>(s)        { }
#if defined(CPPCORE_OS_WINDOWS)
      INLINE BBox2ig(const RECT& rect)                 : BBox2ilt<BBox2ig, V2ig, int32_t>(rect)     { }
#endif
   };

   /// <summary>
   /// 64-Bit Integer 2D BBox (Generic, no SIMD)
   /// </summary>
   class BBox2lg : public BBox2ilt<BBox2lg, V2lg, int64_t> 
   {
   public:
      INLINE BBox2lg()                                 : BBox2ilt<BBox2lg, V2lg, int64_t>()         { }
      INLINE BBox2lg(const V2lg& min, const V2lg& max) : BBox2ilt<BBox2lg, V2lg, int64_t>(min, max) { }
      INLINE BBox2lg(const V2lg& v)                    : BBox2ilt<BBox2lg, V2lg, int64_t>(v)        { }
      INLINE BBox2lg(const int64_t s)                  : BBox2ilt<BBox2lg, V2lg, int64_t>(s)        { }
#if defined(CPPCORE_OS_WINDOWS)
      INLINE BBox2lg(const RECT& rect)                 : BBox2ilt<BBox2lg, V2lg, int64_t>(rect)     { }
#endif
   };
   //------------------------------------------------------------------------------------------------------------------------//
   //                                             SIMD CLASSES                                                               //
   //------------------------------------------------------------------------------------------------------------------------//
#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Single Precision 2D BBox (SIMD)(TODO)
   /// </summary>
   class BBox2fs : public BBox2fdt<BBox2fs, V2fs, float>
   {
   public:
      INLINE BBox2fs()                                 : BBox2fdt<BBox2fs, V2fs, float>()         { }
      INLINE BBox2fs(const V2fs& min, const V2fs& max) : BBox2fdt<BBox2fs, V2fs, float>(min, max) { }
      INLINE BBox2fs(const V2fs& v)                    : BBox2fdt<BBox2fs, V2fs, float>(v)        { }
      INLINE BBox2fs(const float s)                    : BBox2fdt<BBox2fs, V2fs, float>(s)        { }
   };

   /// <summary>
   /// Double Precision 2D BBox (SIMD)(TODO)
   /// </summary>
   class BBox2ds : public BBox2fdt<BBox2ds, V2ds, double>
   {
   public:
      INLINE BBox2ds()                                 : BBox2fdt<BBox2ds, V2ds, double>()         { }
      INLINE BBox2ds(const V2ds& min, const V2ds& max) : BBox2fdt<BBox2ds, V2ds, double>(min, max) { }
      INLINE BBox2ds(const V2ds& v)                    : BBox2fdt<BBox2ds, V2ds, double>(v)        { }
      INLINE BBox2ds(const double s)                   : BBox2fdt<BBox2ds, V2ds, double>(s)        { }
   };

   /// <summary>
   /// 32-Bit Integer 2D BBox (SIMD)(TODO)
   /// </summary>
   class BBox2is : public BBox2ilt<BBox2is, V2is, int32_t>
   {
   public:
      INLINE BBox2is()                                 : BBox2ilt<BBox2is, V2is, int32_t>()         { }
      INLINE BBox2is(const V2is& min, const V2is& max) : BBox2ilt<BBox2is, V2is, int32_t>(min, max) { }
      INLINE BBox2is(const V2is& v)                    : BBox2ilt<BBox2is, V2is, int32_t>(v)        { }
      INLINE BBox2is(const int32_t s)                  : BBox2ilt<BBox2is, V2is, int32_t>(s)        { }
#if defined(CPPCORE_OS_WINDOWS)
      INLINE BBox2is(const RECT& rect)                 : BBox2ilt<BBox2is, V2is, int32_t>(rect)     { }
#endif
   };

   /// <summary>
   /// 64-Bit Integer 2D BBox (SIMD)(TODO)
   /// </summary>
   class BBox2ls : public BBox2ilt<BBox2ls, V2ls, int64_t>
   {
   public:
      INLINE BBox2ls()                                 : BBox2ilt<BBox2ls, V2ls, int64_t>()         { }
      INLINE BBox2ls(const V2ls& min, const V2ls& max) : BBox2ilt<BBox2ls, V2ls, int64_t>(min, max) { }
      INLINE BBox2ls(const V2ls& v)                    : BBox2ilt<BBox2ls, V2ls, int64_t>(v)        { }
      INLINE BBox2ls(const int64_t s)                  : BBox2ilt<BBox2ls, V2ls, int64_t>(s)        { }
#if defined(CPPCORE_OS_WINDOWS)
      INLINE BBox2ls(const RECT& rect)                 : BBox2ilt<BBox2ls, V2ls, int64_t>(rect)     { }
#endif
   };
#endif

#if defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_OPTIMIZED_VECTORMATH)
   // use optimized ones as defaults
   typedef BBox2fs BBox2f;
   typedef BBox2ds BBox2d;
   typedef BBox2is BBox2i;
   typedef BBox2ls BBox2l;
#else
   // use generic ones as defaults
   typedef BBox2fg BBox2f;
   typedef BBox2dg BBox2d;
   typedef BBox2ig BBox2i;
   typedef BBox2lg BBox2l;
#endif
}
