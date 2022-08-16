#pragma once

#include <CppCore/Math/BBox.h>
#include <CppCore/Math/V3.h>

namespace CppCore
{
   /// <summary>
   /// Abstract 3D Bounding Box Template for Floating Point (32/64) AND Integer (32/64). [L1]
   /// </summary>
   template <typename L, typename V, typename F>
   class BBox3 : public BBox<L, V, F>
   {
   public:
      INLINE BBox3()                           : BBox<L, V, F>()         { }
      INLINE BBox3(const V& min, const V& max) : BBox<L, V, F>(min, max) { }
      INLINE BBox3(const V& v)                 : BBox<L, V, F>(v)        { }
      INLINE BBox3(const F s)                  : BBox<L, V, F>(s)        { }
   };
   //------------------------------------------------------------------------------------------------------------------------//
   //                                 FLOATING POINT & INTEGER TEMPLATES                                                     //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 3D Bounding Box Template for Floating Point (32/64)
   /// </summary>
   template <typename L, typename V, typename F>
   class BBox3fdt : public BBox3<L, V, F>
   {
   public:
      INLINE BBox3fdt()                           : BBox3<L, V, F>()         { }
      INLINE BBox3fdt(const V& min, const V& max) : BBox3<L, V, F>(min, max) { }
      INLINE BBox3fdt(const V& v)                 : BBox3<L, V, F>(v)        { }
      INLINE BBox3fdt(const F s)                  : BBox3<L, V, F>(s)        { }
   };
   /// <summary>
   /// Abstract 3D Bounding Box Template for Integer (32/64)
   /// </summary>
   template <typename L, typename V, typename F>
   class BBox3ilt : public BBox3<L, V, F>
   {
   public:
      INLINE BBox3ilt()                           : BBox3<L, V, F>()         { }
      INLINE BBox3ilt(const V& min, const V& max) : BBox3<L, V, F>(min, max) { }
      INLINE BBox3ilt(const V& v)                 : BBox3<L, V, F>(v)        { }
      INLINE BBox3ilt(const F s)                  : BBox3<L, V, F>(s)        { }
   };
   //------------------------------------------------------------------------------------------------------------------------//
   //                                     GENERIC/NON-SIMD CLASSES                                                           //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Single Precision 3D BBox (Generic, no SIMD)
   /// </summary>
   class BBox3fg : public BBox3fdt<BBox3fg, V3fg, float>
   {
   public:
      INLINE BBox3fg()                                 : BBox3fdt<BBox3fg, V3fg, float>()         { }
      INLINE BBox3fg(const V3fg& min, const V3fg& max) : BBox3fdt<BBox3fg, V3fg, float>(min, max) { }
      INLINE BBox3fg(const V3fg& v)                    : BBox3fdt<BBox3fg, V3fg, float>(v)        { }
      INLINE BBox3fg(const float s)                    : BBox3fdt<BBox3fg, V3fg, float>(s)        { }
   };

   /// <summary>
   /// Double Precision 3D BBox (Generic, no SIMD)
   /// </summary>
   class BBox3dg : public BBox3fdt<BBox3dg, V3dg, double>
   {
   public:
      INLINE BBox3dg()                                 : BBox3fdt<BBox3dg, V3dg, double>()         { }
      INLINE BBox3dg(const V3dg& min, const V3dg& max) : BBox3fdt<BBox3dg, V3dg, double>(min, max) { }
      INLINE BBox3dg(const V3dg& v)                    : BBox3fdt<BBox3dg, V3dg, double>(v)        { }
      INLINE BBox3dg(const double s)                   : BBox3fdt<BBox3dg, V3dg, double>(s)        { }
   };

   /// <summary>
   /// 32-Bit Integer 3D BBox (Generic, no SIMD)
   /// </summary>
   class BBox3ig : public BBox3ilt<BBox3ig, V3ig, int32_t>
   {
   public:
      INLINE BBox3ig()                                 : BBox3ilt<BBox3ig, V3ig, int32_t>()         { }
      INLINE BBox3ig(const V3ig& min, const V3ig& max) : BBox3ilt<BBox3ig, V3ig, int32_t>(min, max) { }
      INLINE BBox3ig(const V3ig& v)                    : BBox3ilt<BBox3ig, V3ig, int32_t>(v)        { }
      INLINE BBox3ig(const int32_t s)                  : BBox3ilt<BBox3ig, V3ig, int32_t>(s)        { }
   };

   /// <summary>
   /// 64-Bit Integer 3D BBox (Generic, no SIMD)
   /// </summary>
   class BBox3lg : public BBox3ilt<BBox3lg, V3lg, int64_t>
   {
   public:
      INLINE BBox3lg()                                 : BBox3ilt<BBox3lg, V3lg, int64_t>()         { }
      INLINE BBox3lg(const V3lg& min, const V3lg& max) : BBox3ilt<BBox3lg, V3lg, int64_t>(min, max) { }
      INLINE BBox3lg(const V3lg& v)                    : BBox3ilt<BBox3lg, V3lg, int64_t>(v)        { }
      INLINE BBox3lg(const int64_t s)                  : BBox3ilt<BBox3lg, V3lg, int64_t>(s)        { }
   };
   //------------------------------------------------------------------------------------------------------------------------//
   //                                             SIMD CLASSES                                                               //
   //------------------------------------------------------------------------------------------------------------------------//
#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Single Precision 3D BBox (SIMD)(TODO)
   /// </summary>
   class BBox3fs : public BBox3fdt<BBox3fs, V3fs, float>
   {
   public:
      INLINE BBox3fs()                                 : BBox3fdt<BBox3fs, V3fs, float>()         { }
      INLINE BBox3fs(const V3fs& min, const V3fs& max) : BBox3fdt<BBox3fs, V3fs, float>(min, max) { }
      INLINE BBox3fs(const V3fs& v)                    : BBox3fdt<BBox3fs, V3fs, float>(v)        { }
      INLINE BBox3fs(const float s)                    : BBox3fdt<BBox3fs, V3fs, float>(s)        { }
   };

   /// <summary>
   /// Double Precision 3D BBox (SIMD)(TODO)
   /// </summary>
   class BBox3ds : public BBox3fdt<BBox3ds, V3ds, double>
   {
   public:
      INLINE BBox3ds()                                 : BBox3fdt<BBox3ds, V3ds, double>()         { }
      INLINE BBox3ds(const V3ds& min, const V3ds& max) : BBox3fdt<BBox3ds, V3ds, double>(min, max) { }
      INLINE BBox3ds(const V3ds& v)                    : BBox3fdt<BBox3ds, V3ds, double>(v)        { }
      INLINE BBox3ds(const double s)                   : BBox3fdt<BBox3ds, V3ds, double>(s)        { }
   };

   /// <summary>
   /// 32-Bit Integer 3D BBox (SIMD)(TODO)
   /// </summary>
   class BBox3is : public BBox3ilt<BBox3is, V3is, int32_t>
   {
   public:
      INLINE BBox3is()                                 : BBox3ilt<BBox3is, V3is, int32_t>()         { }
      INLINE BBox3is(const V3is& min, const V3is& max) : BBox3ilt<BBox3is, V3is, int32_t>(min, max) { }
      INLINE BBox3is(const V3is& v)                    : BBox3ilt<BBox3is, V3is, int32_t>(v)        { }
      INLINE BBox3is(const int32_t s)                  : BBox3ilt<BBox3is, V3is, int32_t>(s)        { }
   };

   /// <summary>
   /// 64-Bit Integer 3D BBox (SIMD)(TODO)
   /// </summary>
   class BBox3ls : public BBox3ilt<BBox3ls, V3ls, int64_t>
   {
   public:
      INLINE BBox3ls()                                 : BBox3ilt<BBox3ls, V3ls, int64_t>()         { }
      INLINE BBox3ls(const V3ls& min, const V3ls& max) : BBox3ilt<BBox3ls, V3ls, int64_t>(min, max) { }
      INLINE BBox3ls(const V3ls& v)                    : BBox3ilt<BBox3ls, V3ls, int64_t>(v)        { }
      INLINE BBox3ls(const int64_t s)                  : BBox3ilt<BBox3ls, V3ls, int64_t>(s)        { }
   };
#endif

#if defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_OPTIMIZED_VECTORMATH)
   // use optimized ones as defaults
   typedef BBox3fs BBox3f;
   typedef BBox3ds BBox3d;
   typedef BBox3is BBox3i;
   typedef BBox3ls BBox3l;
#else
   // use generic ones as defaults
   typedef BBox3fg BBox3f;
   typedef BBox3dg BBox3d;
   typedef BBox3ig BBox3i;
   typedef BBox3lg BBox3l;
#endif
}
