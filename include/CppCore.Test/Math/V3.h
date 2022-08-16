#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Math
{
   /// <summary>
   /// Tests for V3.h in CppCore::Math
   /// </summary>
   class V3
   {
   public:
      ///////////////// ALL /////////////////
      INLINE static bool v3_sizeof()
      {
         const bool a = 
            sizeof(V3fg) == 12 &&
            sizeof(V3dg) == 24 &&
            sizeof(V3ig) == 12 &&
            sizeof(V3lg) == 24;
      #if defined(CPPCORE_CPUFEAT_SSE2)
         const bool b = 
            sizeof(V3fs) == 12 &&
            sizeof(V3ds) == 24 &&
            sizeof(V3is) == 12 &&
            sizeof(V3ls) == 24;
      #else
         const bool b = true;
      #endif
         return a && b;
      }
      // Constructor
      template<typename T, typename S, typename T1, typename S1, typename T2, typename S2, typename T3, typename S3>
      INLINE static bool v3_ctr()
      {
         // from array/ptr
         double  td[3]{ 0.9,  1.1,  3.5  }; T tdt(td); // from double
         float   tf[3]{ 0.9f, 1.1f, 3.5f }; T tft(tf); // from float
         int64_t tl[3]{ 1LL,  1LL,  4LL  }; T tlt(tl); // from int64 
         int32_t ti[3]{ 1L,   1L,   4L   }; T tit(ti); // from int32
         bool ok1 =
            tdt.x == (S)0.9  && tdt.y == (S)1.1  && tdt.z == (S)3.5  &&
            tft.x == (S)0.9f && tft.y == (S)1.1f && tft.z == (S)3.5f &&
            tlt.x == (S)1LL  && tlt.y == (S)1LL  && tlt.z == (S)4LL  &&
            tit.x == (S)1L   && tit.y == (S)1L   && tit.z == (S)4L;

         // from values
         T md((double)0.9, (double)1.1, (double)3.5);  // from double
         T mf((float) 0.9f,(float) 1.1f,(float)3.5f);  // from float
         T ml((int64_t)1LL,(int64_t)1LL,(int64_t)4LL); // from int64 
         T mi((int32_t)1L, (int32_t)1L, (int32_t)4L);  // from int32
         bool ok2 =
            md.x  == (S)0.9  && md.y  == (S)1.1  && md.z == (S)3.5  &&
            mf.x  == (S)0.9f && mf.y  == (S)1.1f && mf.z == (S)3.5f &&
            ml.x  == (S)1LL  && ml.y  == (S)1LL  && ml.z == (S)4LL  &&
            mi.x  == (S)1L   && mi.y  == (S)1L   && mi.z == (S)4L;

         // from scalar
         T mds((double)0.9);  // from double
         T mfs((float) 0.9f); // from float
         T mls((int64_t)1LL); // from int64 
         T mis((int32_t)1L);  // from int32
         bool ok3 = 
            mds.x == (S)0.9  && mds.y == (S)0.9  && mds.z == (S)0.9  &&
            mfs.x == (S)0.9f && mfs.y == (S)0.9f && mfs.z == (S)0.9f &&
            mls.x == (S)1LL  && mls.y == (S)1LL  && mls.z == (S)1LL  &&
            mis.x == (S)1L   && mis.y == (S)1L   && mis.z == (S)1L;

         // from three other V3 types
         // e.g. for V3f from V3d, V3i, V3l
         T o1(T1((S1)0.9, (S1)1.1, (S1)3.5));
         T o2(T2((S2)0.9, (S2)1.1, (S2)3.5));
         T o3(T3((S3)0.9, (S3)1.1, (S3)3.5));
         bool ok4 =
            o1.x == (S)(S1)0.9 && o1.y == (S)(S1)1.1 && o1.z == (S)(S1)3.5 &&
            o2.x == (S)(S2)0.9 && o2.y == (S)(S2)1.1 && o2.z == (S)(S2)3.5 &&
            o3.x == (S)(S3)0.9 && o3.y == (S)(S3)1.1 && o3.z == (S)(S3)3.5;

         return ok1 && ok2 && ok3 && ok4;
      }
      // Comparison
      template<typename T, typename S>
      INLINE static bool v3_equal()
      {
         return
            T((S)1.0, (S)1.0, (S)1.0) == T((S)1.0, (S)1.0, (S)1.0)  && // all equal
          !(T((S)1.0, (S)1.0, (S)1.0) == T((S)2.0, (S)2.0, (S)2.0)) && // all unequal
          !(T((S)1.0, (S)2.0, (S)2.0) == T((S)1.0, (S)3.0, (S)3.0)) && // 1 equal, 2+3 unequal
          !(T((S)1.0, (S)2.0, (S)2.0) == T((S)2.0, (S)2.0, (S)3.0)) && // 2 equal, 1+3 unequal
          !(T((S)1.0, (S)1.0, (S)3.0) == T((S)2.0, (S)2.0, (S)3.0)) && // 3 equal, 1+2 unequal
          !(T((S)1.0, (S)1.0, (S)3.0) == T((S)1.0, (S)1.0, (S)2.0)) && // 1+2 equal, 3 unequal
          !(T((S)1.0, (S)2.0, (S)2.0) == T((S)1.0, (S)1.0, (S)2.0)) && // 1+3 equal, 2 unequal
          !(T((S)1.0, (S)2.0, (S)2.0) == T((S)2.0, (S)2.0, (S)2.0));   // 2+3 equal, 1 unequal
      }
      template<typename T, typename S>
      INLINE static bool v3_notequal()
      {
         return
          !(T((S)1.0, (S)1.0, (S)1.0) != T((S)1.0, (S)1.0, (S)1.0)) && // all equal
           (T((S)1.0, (S)1.0, (S)1.0) != T((S)2.0, (S)2.0, (S)2.0)) && // all unequal
           (T((S)1.0, (S)2.0, (S)2.0) != T((S)1.0, (S)3.0, (S)3.0)) && // 1 equal, 2+3 unequal
           (T((S)1.0, (S)2.0, (S)2.0) != T((S)2.0, (S)2.0, (S)3.0)) && // 2 equal, 1+3 unequal
           (T((S)1.0, (S)1.0, (S)3.0) != T((S)2.0, (S)2.0, (S)3.0)) && // 3 equal, 1+2 unequal
           (T((S)1.0, (S)1.0, (S)3.0) != T((S)1.0, (S)1.0, (S)2.0)) && // 1+2 equal, 3 unequal
           (T((S)1.0, (S)2.0, (S)2.0) != T((S)1.0, (S)1.0, (S)2.0)) && // 1+3 equal, 2 unequal
           (T((S)1.0, (S)2.0, (S)2.0) != T((S)2.0, (S)2.0, (S)2.0));   // 2+3 equal, 1 unequal
      }
      template<typename T, typename S>
      INLINE static bool v3_greater()
      {
         return
           (T((S)2.0, (S)2.0, (S)2.0) > T((S)1.0, (S)1.0, (S)1.0)) && // all greater
          !(T((S)1.0, (S)1.0, (S)1.0) > T((S)2.0, (S)2.0, (S)2.0)) && // all smaller
          !(T((S)2.0, (S)1.0, (S)1.0) > T((S)1.0, (S)2.0, (S)2.0)) && // 1 greater, 2+3 smaller
          !(T((S)1.0, (S)2.0, (S)1.0) > T((S)2.0, (S)1.0, (S)2.0)) && // 2 greater, 1+3 smaller
          !(T((S)1.0, (S)1.0, (S)2.0) > T((S)2.0, (S)2.0, (S)1.0)) && // 3 greater, 1+2 smaller
          !(T((S)2.0, (S)1.0, (S)1.0) > T((S)1.0, (S)1.0, (S)1.0)) && // 1 greater, 2+3 equal
          !(T((S)1.0, (S)2.0, (S)1.0) > T((S)1.0, (S)1.0, (S)1.0)) && // 2 greater, 1+3 equal
          !(T((S)1.0, (S)1.0, (S)2.0) > T((S)1.0, (S)1.0, (S)1.0)) && // 3 greater, 1+2 equal
          !(T((S)2.0, (S)2.0, (S)1.0) > T((S)1.0, (S)1.0, (S)2.0)) && // 1+2 greater, 3 smaller
          !(T((S)2.0, (S)1.0, (S)2.0) > T((S)1.0, (S)2.0, (S)1.0)) && // 1+3 greater, 2 smaller
          !(T((S)1.0, (S)2.0, (S)2.0) > T((S)2.0, (S)1.0, (S)1.0)) && // 2+3 greater, 1 smaller
          !(T((S)2.0, (S)2.0, (S)1.0) > T((S)1.0, (S)1.0, (S)1.0)) && // 1+2 greater, 3 equal
          !(T((S)2.0, (S)1.0, (S)2.0) > T((S)1.0, (S)1.0, (S)1.0)) && // 1+3 greater, 2 equal
          !(T((S)1.0, (S)2.0, (S)2.0) > T((S)1.0, (S)1.0, (S)1.0));   // 2+3 greater, 1 equal
      }
      template<typename T, typename S>
      INLINE static bool v3_greaterequal()
      {
         return
           (T((S)2.0, (S)2.0, (S)2.0) >= T((S)1.0, (S)1.0, (S)1.0)) && // all greater
          !(T((S)1.0, (S)1.0, (S)1.0) >= T((S)2.0, (S)2.0, (S)2.0)) && // all smaller
          !(T((S)2.0, (S)1.0, (S)1.0) >= T((S)1.0, (S)2.0, (S)2.0)) && // 1 greater, 2+3 smaller
          !(T((S)1.0, (S)2.0, (S)1.0) >= T((S)2.0, (S)1.0, (S)2.0)) && // 2 greater, 1+3 smaller
          !(T((S)1.0, (S)1.0, (S)2.0) >= T((S)2.0, (S)2.0, (S)1.0)) && // 3 greater, 1+2 smaller
           (T((S)2.0, (S)1.0, (S)1.0) >= T((S)1.0, (S)1.0, (S)1.0)) && // 1 greater, 2+3 equal
           (T((S)1.0, (S)2.0, (S)1.0) >= T((S)1.0, (S)1.0, (S)1.0)) && // 2 greater, 1+3 equal
           (T((S)1.0, (S)1.0, (S)2.0) >= T((S)1.0, (S)1.0, (S)1.0)) && // 3 greater, 1+2 equal
          !(T((S)2.0, (S)2.0, (S)1.0) >= T((S)1.0, (S)1.0, (S)2.0)) && // 1+2 greater, 3 smaller
          !(T((S)2.0, (S)1.0, (S)2.0) >= T((S)1.0, (S)2.0, (S)1.0)) && // 1+3 greater, 2 smaller
          !(T((S)1.0, (S)2.0, (S)2.0) >= T((S)2.0, (S)1.0, (S)1.0)) && // 2+3 greater, 1 smaller
           (T((S)2.0, (S)2.0, (S)1.0) >= T((S)1.0, (S)1.0, (S)1.0)) && // 1+2 greater, 3 equal
           (T((S)2.0, (S)1.0, (S)2.0) >= T((S)1.0, (S)1.0, (S)1.0)) && // 1+3 greater, 2 equal
           (T((S)1.0, (S)2.0, (S)2.0) >= T((S)1.0, (S)1.0, (S)1.0));   // 2+3 greater, 1 equal
      }
      template<typename T, typename S>
      INLINE static bool v3_less()
      {
         return
          !(T((S)2.0, (S)2.0, (S)2.0) < T((S)1.0, (S)1.0, (S)1.0)) && // all greater
           (T((S)1.0, (S)1.0, (S)1.0) < T((S)2.0, (S)2.0, (S)2.0)) && // all smaller
          !(T((S)2.0, (S)1.0, (S)1.0) < T((S)1.0, (S)2.0, (S)2.0)) && // 1 greater, 2+3 smaller
          !(T((S)1.0, (S)2.0, (S)1.0) < T((S)2.0, (S)1.0, (S)2.0)) && // 2 greater, 1+3 smaller
          !(T((S)1.0, (S)1.0, (S)2.0) < T((S)2.0, (S)2.0, (S)1.0)) && // 3 greater, 1+2 smaller
          !(T((S)2.0, (S)1.0, (S)1.0) < T((S)1.0, (S)1.0, (S)1.0)) && // 1 greater, 2+3 equal
          !(T((S)1.0, (S)2.0, (S)1.0) < T((S)1.0, (S)1.0, (S)1.0)) && // 2 greater, 1+3 equal
          !(T((S)1.0, (S)1.0, (S)2.0) < T((S)1.0, (S)1.0, (S)1.0)) && // 3 greater, 1+2 equal
          !(T((S)2.0, (S)2.0, (S)1.0) < T((S)1.0, (S)1.0, (S)2.0)) && // 1+2 greater, 3 smaller
          !(T((S)2.0, (S)1.0, (S)2.0) < T((S)1.0, (S)2.0, (S)1.0)) && // 1+3 greater, 2 smaller
          !(T((S)1.0, (S)2.0, (S)2.0) < T((S)2.0, (S)1.0, (S)1.0)) && // 2+3 greater, 1 smaller
          !(T((S)2.0, (S)2.0, (S)1.0) < T((S)1.0, (S)1.0, (S)1.0)) && // 1+2 greater, 3 equal
          !(T((S)2.0, (S)1.0, (S)2.0) < T((S)1.0, (S)1.0, (S)1.0)) && // 1+3 greater, 2 equal
          !(T((S)1.0, (S)2.0, (S)2.0) < T((S)1.0, (S)1.0, (S)1.0));   // 2+3 greater, 1 equal
      }
      template<typename T, typename S>
      INLINE static bool v3_lessequal()
      {
         return
          !(T((S)2.0, (S)2.0, (S)2.0) <= T((S)1.0, (S)1.0, (S)1.0)) && // all greater
           (T((S)1.0, (S)1.0, (S)1.0) <= T((S)2.0, (S)2.0, (S)2.0)) && // all smaller
          !(T((S)2.0, (S)1.0, (S)1.0) <= T((S)1.0, (S)2.0, (S)2.0)) && // 1 greater, 2+3 smaller
          !(T((S)1.0, (S)2.0, (S)1.0) <= T((S)2.0, (S)1.0, (S)2.0)) && // 2 greater, 1+3 smaller
          !(T((S)1.0, (S)1.0, (S)2.0) <= T((S)2.0, (S)2.0, (S)1.0)) && // 3 greater, 1+2 smaller
          !(T((S)2.0, (S)1.0, (S)1.0) <= T((S)1.0, (S)1.0, (S)1.0)) && // 1 greater, 2+3 equal
          !(T((S)1.0, (S)2.0, (S)1.0) <= T((S)1.0, (S)1.0, (S)1.0)) && // 2 greater, 1+3 equal
          !(T((S)1.0, (S)1.0, (S)2.0) <= T((S)1.0, (S)1.0, (S)1.0)) && // 3 greater, 1+2 equal
          !(T((S)2.0, (S)2.0, (S)1.0) <= T((S)1.0, (S)1.0, (S)2.0)) && // 1+2 greater, 3 smaller
          !(T((S)2.0, (S)1.0, (S)2.0) <= T((S)1.0, (S)2.0, (S)1.0)) && // 1+3 greater, 2 smaller
          !(T((S)1.0, (S)2.0, (S)2.0) <= T((S)2.0, (S)1.0, (S)1.0)) && // 2+3 greater, 1 smaller
          !(T((S)2.0, (S)2.0, (S)1.0) <= T((S)1.0, (S)1.0, (S)1.0)) && // 1+2 greater, 3 equal
          !(T((S)2.0, (S)1.0, (S)2.0) <= T((S)1.0, (S)1.0, (S)1.0)) && // 1+3 greater, 2 equal
          !(T((S)1.0, (S)2.0, (S)2.0) <= T((S)1.0, (S)1.0, (S)1.0));   // 2+3 greater, 1 equal
      }
      // Arithmetic
      template<typename T, typename S>
      INLINE static bool v3_add()
      {
         return
            T((S)1.0, (S)1.0, (S)1.0) + T((S)1.0, (S)1.0, (S)1.0) == T((S)2.0, (S)2.0, (S)2.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_sub()
      {
         return
            T((S)2.0, (S)2.0, (S)2.0) - T((S)1.0, (S)1.0, (S)1.0) == T((S)1.0, (S)1.0, (S)1.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_mul()
      {
         return
            T((S)2.0, (S)2.0, (S)2.0) * T((S)3.0, (S)3.0, (S)3.0) == T((S)6.0, (S)6.0, (S)6.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_div()
      {
         return
            T((S)6.0, (S)6.0, (S)6.0) / T((S)3.0, (S)3.0, (S)3.0) == T((S)2.0, (S)2.0, (S)2.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_madd()
      {
         T x0((S)6.0, (S)6.0, (S)6.0); x0.madd(T((S)3.0, (S)3.0, (S)3.0), T((S)1.0, (S)1.0, (S)1.0)); if (x0 != T((S)19.0, (S)19.0, (S)19.0)) return false;
         return true;
      }
      template<typename T, typename S>
      INLINE static bool v3_msub()
      {
         T x0((S)6.0, (S)6.0, (S)6.0); x0.msub(T((S)3.0, (S)3.0, (S)3.0), T((S)1.0, (S)1.0, (S)1.0)); if (x0 != T((S)17.0, (S)17.0, (S)17.0)) return false;
         return true;
      }
      // Operations
      template<typename T, typename S>
      INLINE static bool v3_swap()
      {
         T x00((S)6.0, (S)6.0, (S)6.0), x01((S)3.0, (S)3.0, (S)3.0); x00.swap(x01); if (x00 != T((S)3.0, (S)3.0, (S)3.0) || x01 != T((S)6.0, (S)6.0, (S)6.0)) return false;
         return true;
      }
      template<typename T, typename S>
      INLINE static bool v3_abs()
      {
         T x0((S) 1.0, (S) 1.0, (S) 1.0); x0.abs(); if (x0 != T((S)1.0, (S)1.0, (S)1.0)) return false;
         T x1((S)-1.0, (S)-1.0, (S)-1.0); x1.abs(); if (x1 != T((S)1.0, (S)1.0, (S)1.0)) return false;
         return
            T((S) 1.0, (S) 1.0, (S) 1.0).absC() == T((S)1.0, (S)1.0, (S)1.0) &&
            T((S)-1.0, (S)-1.0, (S)-1.0).absC() == T((S)1.0, (S)1.0, (S)1.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_min()
      {
         T x0((S) 1.0, (S) 1.0, (S) 1.0); x0.min(T((S)-1.0, (S)-1.0, (S)-1.0)); if (x0 != T((S)-1.0, (S)-1.0, (S)-1.0)) return false;
         T x1((S)-1.0, (S)-1.0, (S)-1.0); x1.min(T((S) 1.0, (S) 1.0, (S) 1.0)); if (x1 != T((S)-1.0, (S)-1.0, (S)-1.0)) return false;
         return
            T((S) 1.0, (S) 1.0, (S) 1.0).minC(T((S)-1.0, (S)-1.0, (S)-1.0)) == T((S)-1.0, (S)-1.0, (S)-1.0) &&
            T((S)-1.0, (S)-1.0, (S)-1.0).minC(T((S) 1.0, (S) 1.0, (S) 1.0)) == T((S)-1.0, (S)-1.0, (S)-1.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_max()
      {
         T x0((S) 1.0, (S) 1.0, (S) 1.0); x0.max(T((S)-1.0, (S)-1.0, (S)-1.0)); if (x0 != T((S)1.0, (S)1.0, (S)1.0)) return false;
         T x1((S)-1.0, (S)-1.0, (S)-1.0); x1.max(T((S) 1.0, (S) 1.0, (S) 1.0)); if (x1 != T((S)1.0, (S)1.0, (S)1.0)) return false;
         return
            T((S) 1.0, (S) 1.0, (S) 1.0).maxC(T((S)-1.0, (S)-1.0, (S)-1.0)) == T((S)1.0, (S)1.0, (S)1.0) &&
            T((S)-1.0, (S)-1.0, (S)-1.0).maxC(T((S) 1.0, (S) 1.0, (S) 1.0)) == T((S)1.0, (S)1.0, (S)1.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_dot()
      {
         return
            T((S)2.0, (S)2.0, (S)2.0).dot(T((S)3.0, (S)3.0, (S)3.0)) == (S)18.0;
      }
      template<typename T, typename S>
      INLINE static bool v3_cross()
      {
         return
            T((S)1.0, (S)0.0, (S)0.0).cross(T((S)0.0, (S)1.0, (S)0.0)) == T((S)0.0, (S)0.0, (S)1.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_length()
      {
         return
            T((S)0.0, (S)0.0, (S)0.0).length() == (S)0.0 &&
            T((S)3.0, (S)0.0, (S)0.0).length() == (S)3.0;
      }
      template<typename T, typename S>
      INLINE static bool v3_inside()
      {
         return
            T((S)0.0, (S)0.0, (S)0.0).inside(T((S)-1.0, (S)-1.0, (S)-1.0), T((S)1.0, (S)1.0, (S)1.0))         == true  && // Box (middle)
            T((S)0.0, (S)0.0, (S)0.0).inside(T((S) 0.0, (S) 0.0, (S) 0.0), T((S)1.0, (S)1.0, (S)1.0))         == true  && // Box (edge case)
            T((S)0.0, (S)0.0, (S)0.0).inside(T((S) 0.1, (S) 0.1, (S) 0.1), T((S)1.0, (S)1.0, (S)1.0), (S)0.1) == true  && // Box (edge case, eps)
            T((S)0.0, (S)0.0, (S)0.0).inside(T((S) 1.0, (S) 1.0, (S) 1.0), T((S)2.0, (S)2.0, (S)2.0))         == false && // Box (outside)
            T((S)0.0, (S)0.0, (S)0.0).inside(T((S) 0.0, (S) 0.0, (S) 0.0), (S)1.0)                            == true  && // Circle (middle)
            T((S)1.0, (S)0.0, (S)0.0).inside(T((S) 0.0, (S) 0.0, (S) 0.0), (S)1.0)                            == true  && // Circle (edge case)
            T((S)0.0, (S)0.0, (S)0.0).inside(T((S) 3.0, (S) 0.0, (S) 0.0), (S)1.0)                            == false;   // Circle (outside)*/
      }
      // Float/Double Only
      template<typename T, typename S>
      INLINE static bool v3_round()
      {
         T x0((S) 1.1, (S) 1.1, (S) 1.1); x0.round();       if (x0 != T((S) 1.0, (S) 1.0, (S) 1.0)) return false;
         T x1((S)-1.9, (S)-1.9, (S)-1.9); x1.round();       if (x1 != T((S)-2.0, (S)-2.0, (S)-2.0)) return false;
         T x2((S)-9.9, (S)-7.5, (S) 3.5); x2.round((S)4.0); if (x2 != T((S)-8.0, (S)-8.0, (S) 4.0)) return false;
         return
            T((S) 1.1, (S) 1.1, (S) 1.1).roundC()       == T((S) 1.0, (S) 1.0, (S) 1.0) &&
            T((S)-1.9, (S)-1.9, (S)-1.9).roundC()       == T((S)-2.0, (S)-2.0, (S)-2.0) &&
            T((S)-9.9, (S)-7.5, (S) 3.5).roundC((S)4.0) == T((S)-8.0, (S)-8.0, (S) 4.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_floor()
      {
         T x0((S) 1.1, (S) 1.1, (S) 1.1); x0.floor(); if (x0 != T((S) 1.0, (S) 1.0, (S) 1.0)) return false;
         T x1((S)-1.9, (S)-1.9, (S)-1.9); x1.floor(); if (x1 != T((S)-2.0, (S)-2.0, (S)-2.0)) return false;
         return
            T((S) 1.1, (S) 1.1, (S) 1.1).floorC() == T((S) 1.0, (S) 1.0, (S) 1.0) &&
            T((S)-1.9, (S)-1.9, (S)-1.9).floorC() == T((S)-2.0, (S)-2.0, (S)-2.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_ceil()
      {
         T x0((S) 1.1, (S) 1.1, (S) 1.1); x0.ceil(); if (x0 != T((S) 2.0, (S) 2.0, (S) 2.0)) return false;
         T x1((S)-1.9, (S)-1.9, (S)-1.9); x1.ceil(); if (x1 != T((S)-1.0, (S)-1.0, (S)-1.0)) return false;
         return
            T((S) 1.1, (S) 1.1, (S) 1.1).ceilC() == T((S) 2.0, (S) 2.0, (S) 2.0) &&
            T((S)-1.9, (S)-1.9, (S)-1.9).ceilC() == T((S)-1.0, (S)-1.0, (S)-1.0);
      }
      template<typename T, typename S>
      INLINE static bool v3_normalise()
      {
         const S c = (S)0.70710678118654746; // c = 1 / sqrt(2)
         T x0((S)2.0, (S)0.0, (S)0.0); x0.normalise(); if (x0 != T((S)1.0, (S)0.0, (S)0.0)) return false;
         T x1((S)1.0, (S)1.0, (S)0.0); x1.normalise(); if (x1 != T((S)c,   (S)c,   (S)0.0)) return false;
         return
            T((S)2.0, (S)0.0, (S)0.0).normaliseC() == T((S)1.0, (S)0.0, (S)0.0) &&
            T((S)1.0, (S)1.0, (S)0.0).normaliseC() == T((S)c,   (S)c,   (S)0.0);
      }

      template<typename T, typename S>
      INLINE static bool v3_intersectlt()
      {
         T i;
         constexpr S EPS_S = std::numeric_limits<S>::epsilon();
         // --------------------------------------------------------------
         // TODO: This needs at least a non horizontal/vertical test case!
         // --------------------------------------------------------------
         // RAY-MODE | TRIANGLE IN HORIZONTAL PLANE
         // orthogonal ray intersecting it somewhere in the middle
         if (!T::intersectLineTriangle(
            T((S)1.25, (S)1.25, (S)2.0), // ray start
            T((S)1.25, (S)1.25, (S)1.8), // ray goes through this
            T((S)1.0,  (S)1.0,  (S)1.0), // triangle p1
            T((S)2.0,  (S)1.0,  (S)1.0), // triangle p2
            T((S)1.0,  (S)2.0,  (S)1.0), // triangle p3
            i, true, (S)0.001) || !T((S)1.25, (S)1.25, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal ray intersecting it at p1
         if (!T::intersectLineTriangle(
            T((S)1.0, (S)1.0, (S)2.0), // ray start
            T((S)1.0, (S)1.0, (S)1.8), // ray goes through this
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, true, (S)0.001) || !T((S)1.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal ray intersecting it at p2
         if (!T::intersectLineTriangle(
            T((S)2.0, (S)1.0, (S)2.0), // ray start
            T((S)2.0, (S)1.0, (S)1.8), // ray goes through this
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, true, (S)0.001) || !T((S)2.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal ray intersecting it at p3
         if (!T::intersectLineTriangle(
            T((S)1.0, (S)2.0, (S)2.0), // ray start
            T((S)1.0, (S)2.0, (S)1.8), // ray goes through this
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, true, (S)0.001) || !T((S)1.0, (S)2.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal ray not intersecting
         if (T::intersectLineTriangle(
            T((S)0.0, (S)0.0, (S)2.0), // ray start
            T((S)0.0, (S)0.0, (S)1.8), // ray goes through this
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, true, (S)0.001))
            return false;
         // parallel ray not intersecting
         if (T::intersectLineTriangle(
            T((S)1.0, (S)1.0, (S)2.0), // ray start
            T((S)2.0, (S)2.0, (S)2.0), // ray goes through this
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, true, (S)0.001))
            return false;
         // ray in triangle plane (starting inside)
         if (T::intersectLineTriangle(
            T((S)1.2, (S)1.2, (S)1.0), // ray start
            T((S)1.4, (S)1.4, (S)1.0), // ray goes through this
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, true, (S)0.001))
            return false;
         // --------------------------------------------------------------
         // LINE MODE | TRIANGLE IN HORIZONTAL PLANE
         // orthogonal line intersecting it somewhere in the middle
         if (!T::intersectLineTriangle(
            T((S)1.25, (S)1.25, (S)2.0), // line start
            T((S)1.25, (S)1.25, (S)0.0), // line end
            T((S)1.0,  (S)1.0,  (S)1.0), // triangle p1
            T((S)2.0,  (S)1.0,  (S)1.0), // triangle p2
            T((S)1.0,  (S)2.0,  (S)1.0), // triangle p3
            i, false, (S)0.001) || !T((S)1.25, (S)1.25, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line intersecting it at p1
         if (!T::intersectLineTriangle(
            T((S)1.0, (S)1.0, (S)2.0), // line start
            T((S)1.0, (S)1.0, (S)0.0), // line end
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, false, (S)0.001) || !T((S)1.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line intersecting it at p2
         if (!T::intersectLineTriangle(
            T((S)2.0, (S)1.0, (S)2.0), // line start
            T((S)2.0, (S)1.0, (S)0.0), // line end
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, false, (S)0.001) || !T((S)2.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line intersecting it at p3
         if (!T::intersectLineTriangle(
            T((S)1.0, (S)2.0, (S)2.0), // line start
            T((S)1.0, (S)2.0, (S)0.0), // line end
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, false, (S)0.001) || !T((S)1.0, (S)2.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // --------------------------------------------------------------
         // LINE MODE | TRIANGLE IN HORIZONTAL PLANE
         // orthogonal line touching it somewhere in the middle
         if (!T::intersectLineTriangle(
            T((S)1.25, (S)1.25, (S)2.0), // line start
            T((S)1.25, (S)1.25, (S)1.0), // line end
            T((S)1.0,  (S)1.0,  (S)1.0), // triangle p1
            T((S)2.0,  (S)1.0,  (S)1.0), // triangle p2
            T((S)1.0,  (S)2.0,  (S)1.0), // triangle p3
            i, false, (S)0.001) || !T((S)1.25, (S)1.25, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line touching it at p1
         if (!T::intersectLineTriangle(
            T((S)1.0, (S)1.0, (S)2.0), // line start
            T((S)1.0, (S)1.0, (S)1.0), // line end
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, false, (S)0.001) || !T((S)1.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line touching it at p2
         if (!T::intersectLineTriangle(
            T((S)2.0, (S)1.0, (S)2.0), // line start
            T((S)2.0, (S)1.0, (S)1.0), // line end
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, false, (S)0.001) || !T((S)2.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line touching it at p3
         if (!T::intersectLineTriangle(
            T((S)1.0, (S)2.0, (S)2.0), // line start
            T((S)1.0, (S)2.0, (S)1.0), // line end
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, false, (S)0.001) || !T((S)1.0, (S)2.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line not intersecting
         if (T::intersectLineTriangle(
            T((S)0.0, (S)0.0, (S)2.0), // line start
            T((S)0.0, (S)0.0, (S)0.0), // line end
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, false, (S)0.001))
            return false;
         // parallel line not intersecting
         if (T::intersectLineTriangle(
            T((S)1.0, (S)1.0, (S)2.0), // line start
            T((S)2.0, (S)2.0, (S)2.0), // line end
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, false, (S)0.001))
            return false;
         // line in triangle plane (start+end inside triangle)
         if (T::intersectLineTriangle(
            T((S)1.2, (S)1.2, (S)1.0), // line start
            T((S)1.4, (S)1.4, (S)1.0), // line end
            T((S)1.0, (S)1.0, (S)1.0), // triangle p1
            T((S)2.0, (S)1.0, (S)1.0), // triangle p2
            T((S)1.0, (S)2.0, (S)1.0), // triangle p3
            i, false, (S)0.001))
            return false;
         // --------------------------------------------------------------

         return true;
      }

      template<typename T, typename S>
      INLINE static bool v3_intersectlp()
      {
         T i;
         constexpr S EPS_S = std::numeric_limits<S>::epsilon();
         // --------------------------------------------------------------
         // TODO: This needs at least a non horizontal/vertical test case!
         // --------------------------------------------------------------
         // SIMPLE HEXAGON IN HORIZONTAL PLANE
         const T p1[6] = { T((S)1.0, (S)1.0, (S)1.0),
                           T((S)2.0, (S)1.0, (S)1.0),
                           T((S)3.0, (S)2.0, (S)1.0),
                           T((S)2.0, (S)3.0, (S)1.0),
                           T((S)1.0, (S)3.0, (S)1.0),
                           T((S)0.0, (S)2.0, (S)1.0)};
         // RAY-MODE
         // orthogonal ray intersecting it in its middle
         if (!T::intersectLinePolygon(
            T((S)1.5, (S)2.0, (S)2.0), // ray start
            T((S)1.5, (S)2.0, (S)1.8), // ray goes through this
            p1, 6U,                    // points and numpoints
            i, true, (S)0.001) || !T((S)1.5, (S)2.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal ray intersecting it at p1
         if (!T::intersectLinePolygon(
            T((S)1.0, (S)1.0, (S)2.0), // ray start
            T((S)1.0, (S)1.0, (S)1.8), // ray goes through this
            p1, 6U,                    // points and numpoints
            i, true, (S)0.001) || !T((S)1.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal ray intersecting it at p2
         if (!T::intersectLinePolygon(
            T((S)2.0, (S)1.0, (S)2.0), // ray start
            T((S)2.0, (S)1.0, (S)1.8), // ray goes through this
            p1, 6U,                    // points and numpoints
            i, true, (S)0.001) || !T((S)2.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal ray intersecting it at p3
         if (!T::intersectLinePolygon(
            T((S)3.0, (S)2.0, (S)2.0), // ray start
            T((S)3.0, (S)2.0, (S)1.8), // ray goes through this
            p1, 6U,                    // points and numpoints
            i, true, (S)0.001) || !T((S)3.0, (S)2.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal ray not intersecting
         if (T::intersectLinePolygon(
            T((S)0.0, (S)0.0, (S)2.0), // ray start
            T((S)0.0, (S)0.0, (S)1.8), // ray goes through this
            p1, 6U,                    // points and numpoints
            i, true, (S)0.001))
            return false;
         // parallel ray not intersecting
         if (T::intersectLinePolygon(
            T((S)1.0, (S)1.0, (S)2.0), // ray start
            T((S)2.0, (S)2.0, (S)2.0), // ray goes through this
            p1, 6U,                    // points and numpoints
            i, true, (S)0.001))
            return false;
         // ray in hexagon plane (starting inside)
         if (T::intersectLinePolygon(
            T((S)1.2, (S)1.2, (S)1.0), // ray start
            T((S)1.4, (S)1.4, (S)1.0), // ray goes through this
            p1, 6U,                    // points and numpoints
            i, true, (S)0.001))
            return false;
         // LINE MODE
         // orthogonal line intersecting it in its middle
         if (!T::intersectLinePolygon(
            T((S)1.5, (S)2.0, (S)2.0), // line start
            T((S)1.5, (S)2.0, (S)0.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001) || !T((S)1.5, (S)2.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line intersecting it at p1
         if (!T::intersectLinePolygon(
            T((S)1.0, (S)1.0, (S)2.0), // line start
            T((S)1.0, (S)1.0, (S)0.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001) || !T((S)1.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line intersecting it at p2
         if (!T::intersectLinePolygon(
            T((S)2.0, (S)1.0, (S)2.0), // line start
            T((S)2.0, (S)1.0, (S)0.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001) || !T((S)2.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line intersecting it at p3
         if (!T::intersectLinePolygon(
            T((S)1.0, (S)2.0, (S)2.0), // line start
            T((S)1.0, (S)2.0, (S)0.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001) || !T((S)1.0, (S)2.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line touching it in its middle
         if (!T::intersectLinePolygon(
            T((S)1.5, (S)2.0, (S)2.0), // line start
            T((S)1.5, (S)2.0, (S)1.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001) || !T((S)1.5, (S)2.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line touching it at p1
         if (!T::intersectLinePolygon(
            T((S)1.0, (S)1.0, (S)2.0), // line start
            T((S)1.0, (S)1.0, (S)1.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001) || !T((S)1.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line touching it at p2
         if (!T::intersectLinePolygon(
            T((S)2.0, (S)1.0, (S)2.0), // line start
            T((S)2.0, (S)1.0, (S)1.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001) || !T((S)2.0, (S)1.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line touching it at p3
         if (!T::intersectLinePolygon(
            T((S)1.0, (S)2.0, (S)2.0), // line start
            T((S)1.0, (S)2.0, (S)1.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001) || !T((S)1.0, (S)2.0, (S)1.0).inside(i, i, EPS_S))
            return false;
         // orthogonal line not intersecting
         if (T::intersectLinePolygon(
            T((S)0.0, (S)0.0, (S)2.0), // line start
            T((S)0.0, (S)0.0, (S)0.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001))
            return false;
         // parallel line not intersecting
         if (T::intersectLinePolygon(
            T((S)1.0, (S)1.0, (S)2.0), // line start
            T((S)2.0, (S)2.0, (S)2.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001))
            return false;
         // line in triangle plane (start+end inside triangle)
         if (T::intersectLinePolygon(
            T((S)1.2, (S)1.2, (S)1.0), // line start
            T((S)1.4, (S)1.4, (S)1.0), // line end
            p1, 6U,                    // points and numpoints
            i, false, (S)0.001))
            return false;
         // --------------------------------------------------------------

         return true;
      }
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Math {
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(V3)
   {
   public:
      TEST_METHOD(SIZEOF)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_sizeof()); }

      // FLOAT (GENERIC)
      TEST_METHOD(CTR_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_ctr<V3fg, float, V3dg, double, V3ig, int32_t, V3lg, int64_t>()); }
      TEST_METHOD(EQUAL_FG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_equal<V3fg, float>()); }
      TEST_METHOD(NOTEQUAL_FG)     { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_notequal<V3fg, float>()); }
      TEST_METHOD(GREATER_FG)      { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_greater<V3fg, float>()); }
      TEST_METHOD(GREATEREQUAL_FG) { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_greaterequal<V3fg, float>()); }
      TEST_METHOD(LESS_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_less<V3fg, float>()); }
      TEST_METHOD(LESSEQUAL_FG)    { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_lessequal<V3fg, float>()); }
      TEST_METHOD(ADD_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_add<V3fg, float>()); }
      TEST_METHOD(SUB_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_sub<V3fg, float>()); }
      TEST_METHOD(MUL_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_mul<V3fg, float>()); }
      TEST_METHOD(DIV_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_div<V3fg, float>()); }
      TEST_METHOD(MADD_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_madd<V3fg, float>()); }
      TEST_METHOD(MSUB_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_msub<V3fg, float>()); }
      TEST_METHOD(SWAP_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_swap<V3fg, float>()); }
      TEST_METHOD(ABS_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_abs<V3fg, float>()); }
      TEST_METHOD(MIN_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_min<V3fg, float>()); }
      TEST_METHOD(MAX_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_max<V3fg, float>()); }
      TEST_METHOD(DOT_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_dot<V3fg, float>()); }
      TEST_METHOD(CROSS_FG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_cross<V3fg, float>()); }
      TEST_METHOD(LENGTH_FG)       { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_length<V3fg, float>()); }
      TEST_METHOD(INSIDE_FG)       { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_inside<V3fg, float>()); }
      TEST_METHOD(ROUND_FG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_round<V3fg, float>()); }
      TEST_METHOD(FLOOR_FG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_floor<V3fg, float>()); }
      TEST_METHOD(CEIL_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_ceil<V3fg, float>()); }
      TEST_METHOD(NORMALISE_FG)    { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_normalise<V3fg, float>()); }
      TEST_METHOD(INTERSECTLT_FG)  { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_intersectlt<V3fg, float>()); }
      TEST_METHOD(INTERSECTLP_FG)  { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_intersectlp<V3fg, float>()); }

      // DOUBLE (GENERIC)
      TEST_METHOD(CTR_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_ctr<V3dg, double, V3fg, float, V3ig, int32_t, V3lg, int64_t>()); }
      TEST_METHOD(EQUAL_DG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_equal<V3dg, double>()); }
      TEST_METHOD(NOTEQUAL_DG)     { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_notequal<V3dg, double>()); }
      TEST_METHOD(GREATER_DG)      { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_greater<V3dg, double>()); }
      TEST_METHOD(GREATEREQUAL_DG) { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_greaterequal<V3dg, double>()); }
      TEST_METHOD(LESS_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_less<V3dg, double>()); }
      TEST_METHOD(LESSEQUAL_DG)    { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_lessequal<V3dg, double>()); }
      TEST_METHOD(ADD_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_add<V3dg, double>()); }
      TEST_METHOD(SUB_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_sub<V3dg, double>()); }
      TEST_METHOD(MUL_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_mul<V3dg, double>()); }
      TEST_METHOD(DIV_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_div<V3dg, double>()); }
      TEST_METHOD(MADD_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_madd<V3dg, double>()); }
      TEST_METHOD(MSUB_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_msub<V3dg, double>()); }
      TEST_METHOD(SWAP_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_swap<V3dg, double>()); }
      TEST_METHOD(ABS_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_abs<V3dg, double>()); }
      TEST_METHOD(MIN_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_min<V3dg, double>()); }
      TEST_METHOD(MAX_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_max<V3dg, double>()); }
      TEST_METHOD(DOT_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_dot<V3dg, double>()); }
      TEST_METHOD(CROSS_DG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_cross<V3dg, double>()); }
      TEST_METHOD(LENGTH_DG)       { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_length<V3dg, double>()); }
      TEST_METHOD(INSIDE_DG)       { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_inside<V3dg, double>()); }
      TEST_METHOD(ROUND_DG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_round<V3dg, double>()); }
      TEST_METHOD(FLOOR_DG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_floor<V3dg, double>()); }
      TEST_METHOD(CEIL_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_ceil<V3dg, double>()); }
      TEST_METHOD(NORMALISE_DG)    { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_normalise<V3dg, double>()); }
      TEST_METHOD(INTERSECTLT_DG)  { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_intersectlt<V3dg, double>()); }
      TEST_METHOD(INTERSECTLP_DG)  { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_intersectlp<V3dg, double>()); }

      // INT32 (GENERIC)
      TEST_METHOD(CTR_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_ctr<V3ig, int32_t, V3lg, int64_t, V3fg, float, V3dg, double>()); }
      TEST_METHOD(EQUAL_IG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_equal<V3ig, int32_t>()); }
      TEST_METHOD(NOTEQUAL_IG)     { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_notequal<V3ig, int32_t>()); }
      TEST_METHOD(GREATER_IG)      { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_greater<V3ig, int32_t>()); }
      TEST_METHOD(GREATEREQUAL_IG) { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_greaterequal<V3ig, int32_t>()); }
      TEST_METHOD(LESS_IG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_less<V3ig, int32_t>()); }
      TEST_METHOD(LESSEQUAL_IG)    { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_lessequal<V3ig, int32_t>()); }
      TEST_METHOD(ADD_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_add<V3ig, int32_t>()); }
      TEST_METHOD(SUB_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_sub<V3ig, int32_t>()); }
      TEST_METHOD(MUL_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_mul<V3ig, int32_t>()); }
      TEST_METHOD(DIV_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_div<V3ig, int32_t>()); }
      TEST_METHOD(MADD_IG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_madd<V3ig, int32_t>()); }
      TEST_METHOD(MSUB_IG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_msub<V3ig, int32_t>()); }
      TEST_METHOD(SWAP_IG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_swap<V3ig, int32_t>()); }
      TEST_METHOD(ABS_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_abs<V3ig, int32_t>()); }
      TEST_METHOD(MIN_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_min<V3ig, int32_t>()); }
      TEST_METHOD(MAX_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_max<V3ig, int32_t>()); }
      TEST_METHOD(DOT_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_dot<V3ig, int32_t>()); }
      TEST_METHOD(CROSS_IG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_cross<V3ig, int32_t>()); }
      TEST_METHOD(LENGTH_IG)       { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_length<V3ig, int32_t>()); }
      TEST_METHOD(INSIDE_IG)       { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_inside<V3ig, int32_t>()); }

      // INT64 (GENERIC)
      TEST_METHOD(CTR_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_ctr<V3lg, int64_t, V3ig, int32_t, V3fg, float, V3dg, double>()); }
      TEST_METHOD(EQUAL_LG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_equal<V3lg, int64_t>()); }
      TEST_METHOD(NOTEQUAL_LG)     { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_notequal<V3lg, int64_t>()); }
      TEST_METHOD(GREATER_LG)      { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_greater<V3lg, int64_t>()); }
      TEST_METHOD(GREATEREQUAL_LG) { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_greaterequal<V3lg, int64_t>()); }
      TEST_METHOD(LESS_LG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_less<V3lg, int64_t>()); }
      TEST_METHOD(LESSEQUAL_LG)    { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_lessequal<V3lg, int64_t>()); }
      TEST_METHOD(ADD_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_add<V3lg, int64_t>()); }
      TEST_METHOD(SUB_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_sub<V3lg, int64_t>()); }
      TEST_METHOD(MUL_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_mul<V3lg, int64_t>()); }
      TEST_METHOD(DIV_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_div<V3lg, int64_t>()); }
      TEST_METHOD(MADD_LG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_madd<V3lg, int64_t>()); }
      TEST_METHOD(MSUB_LG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_msub<V3lg, int64_t>()); }
      TEST_METHOD(SWAP_LG)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_swap<V3lg, int64_t>()); }
      TEST_METHOD(ABS_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_abs<V3lg, int64_t>()); }
      TEST_METHOD(MIN_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_min<V3lg, int64_t>()); }
      TEST_METHOD(MAX_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_max<V3lg, int64_t>()); }
      TEST_METHOD(DOT_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_dot<V3lg, int64_t>()); }
      TEST_METHOD(CROSS_LG)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_cross<V3lg, int64_t>()); }
      TEST_METHOD(LENGTH_LG)       { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_length<V3lg, int64_t>()); }
      TEST_METHOD(INSIDE_LG)       { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_inside<V3lg, int64_t>()); }

#if defined(CPPCORE_CPUFEAT_SSE2)
      // FLOAT (SIMD)
      TEST_METHOD(CTR_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_ctr<V3fs, float, V3ds, double, V3is, int32_t, V3ls, int64_t>()); }
      TEST_METHOD(EQUAL_FS)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_equal<V3fs, float>()); }
      TEST_METHOD(NOTEQUAL_FS)     { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_notequal<V3fs, float>()); }
      TEST_METHOD(GREATER_FS)      { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_greater<V3fs, float>()); }
      TEST_METHOD(GREATEREQUAL_FS) { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_greaterequal<V3fs, float>()); }
      TEST_METHOD(LESS_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_less<V3fs, float>()); }
      TEST_METHOD(LESSEQUAL_FS)    { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_lessequal<V3fs, float>()); }
      TEST_METHOD(ADD_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_add<V3fs, float>()); }
      TEST_METHOD(SUB_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_sub<V3fs, float>()); }
      TEST_METHOD(MUL_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_mul<V3fs, float>()); }
      TEST_METHOD(DIV_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_div<V3fs, float>()); }
      TEST_METHOD(MADD_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_madd<V3fs, float>()); }
      TEST_METHOD(MSUB_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_msub<V3fs, float>()); }
      TEST_METHOD(SWAP_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_swap<V3fs, float>()); }
      TEST_METHOD(ABS_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_abs<V3fs, float>()); }
      TEST_METHOD(MIN_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_min<V3fs, float>()); }
      TEST_METHOD(MAX_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_max<V3fs, float>()); }
      TEST_METHOD(DOT_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_dot<V3fs, float>()); }
      TEST_METHOD(CROSS_FS)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_cross<V3fs, float>()); }
      TEST_METHOD(LENGTH_FS)       { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_length<V3fs, float>()); }
      TEST_METHOD(INSIDE_FS)       { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_inside<V3fs, float>()); }
      TEST_METHOD(ROUND_FS)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_round<V3fs, float>()); }
      TEST_METHOD(FLOOR_FS)        { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_floor<V3fs, float>()); }
      TEST_METHOD(CEIL_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_ceil<V3fs, float>()); }
      TEST_METHOD(NORMALISE_FS)    { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_normalise<V3fs, float>()); }
      TEST_METHOD(INTERSECTLT_FS)  { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_intersectlt<V3fs, float>()); }
      TEST_METHOD(INTERSECTLP_FS)  { Assert::AreEqual(true, CppCore::Test::Math::V3::v3_intersectlp<V3fs, float>()); }

#endif
   };
}}}}
#endif
