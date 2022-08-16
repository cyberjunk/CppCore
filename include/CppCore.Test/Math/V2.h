#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Math
{
   /// <summary>
   /// Tests for V2.h in CppCore::Math
   /// </summary>
   class V2
   {
   public:
      ///////////////// ALL /////////////////
      INLINE static bool v2_sizeof()
      {
         const bool a = 
            sizeof(V2fg) == 8  &&
            sizeof(V2dg) == 16 &&
            sizeof(V2ig) == 8  &&
            sizeof(V2lg) == 16;
      #if defined(CPPCORE_CPUFEAT_SSE2)
         const bool b = 
            sizeof(V2fs) == 8  &&
            sizeof(V2ds) == 16 &&
            sizeof(V2is) == 8  &&
            sizeof(V2ls) == 16;
      #else
         const bool b = true;
      #endif
         return a && b;
      }
      template<typename T, size_t ALIGNMENT>
      INLINE static bool v2_alignment()
      {
         for (size_t i = 0; i < 64; i++)
            if ((((size_t)&T()) % ALIGNMENT) != 0)
               return false;
         return true;
      }
      ///////////////// FLOAT / DOUBLE /////////////////
      // Constructor
      template<typename T, typename S, typename T1, typename S1, typename T2, typename S2, typename T3, typename S3>
      INLINE static bool v2f_ctr()
      {
         // from array/ptr
         double  td[2]{ 0.9,  1.1  }; T tdt(td); // from double
         float   tf[2]{ 0.9f, 1.1f }; T tft(tf); // from float
         int64_t tl[2]{ 1LL,  1LL  }; T tlt(tl); // from int64 
         int32_t ti[2]{ 1L,   1L   }; T tit(ti); // from int32
         bool ok1 =
            tdt.x == (S)0.9  && tdt.y == (S)1.1  &&
            tft.x == (S)0.9f && tft.y == (S)1.1f &&
            tlt.x == (S)1LL  && tlt.y == (S)1LL  &&
            tit.x == (S)1L   && tit.y == (S)1L;

         // from values
         T md((double)0.9, (double)1.1);  // from double
         T mf((float) 0.9f,(float) 1.1f); // from float
         T ml((int64_t)1LL,(int64_t)1LL); // from int64 
         T mi((int32_t)1L, (int32_t)1L);  // from int32
         bool ok2 =
            md.x  == (S)0.9  && md.y  == (S)1.1  &&
            mf.x  == (S)0.9f && mf.y  == (S)1.1f &&
            ml.x  == (S)1LL  && ml.y  == (S)1LL  &&
            mi.x  == (S)1L   && mi.y  == (S)1L;

         // from scalar
         T mds((double)0.9);  // from double
         T mfs((float) 0.9f); // from float
         T mls((int64_t)1LL); // from int64 
         T mis((int32_t)1L);  // from int32
         bool ok3 = 
            mds.x == (S)0.9  && mds.y == (S)0.9  &&
            mfs.x == (S)0.9f && mfs.y == (S)0.9f &&
            mls.x == (S)1LL  && mls.y == (S)1LL  &&
            mis.x == (S)1L   && mis.y == (S)1L;

         // from three other V2 types
         // e.g. for V2f from V2d, V2i, V2l
         T o1(T1((S1)0.9, (S1)1.1));
         T o2(T2((S2)0.9, (S2)1.1));
         T o3(T3((S3)0.9, (S3)1.1));
         bool ok4 =
               o1.x == (S)(S1)0.9 && o1.y == (S)(S1)1.1 &&
               o2.x == (S)(S2)0.9 && o2.y == (S)(S2)1.1 &&
               o3.x == (S)(S3)0.9 && o3.y == (S)(S3)1.1;

         return ok1 && ok2 && ok3 && ok4;
      }
      // Comparison
      template<typename T>
      INLINE static bool v2f_equal()
      {
         return
            T(1.0, 1.0) == T(1.0, 1.0)  && // both equal
          !(T(1.0, 1.0) == T(2.0, 2.0)) && // both unequal
          !(T(1.0, 2.0) == T(1.0, 3.0)) && // first equal, second unequal
          !(T(1.0, 2.0) == T(2.0, 2.0));   // first unequal, second equal
      }
      template<typename T>
      INLINE static bool v2f_notequal()
      {
         return
            T(1.0, 1.0) != T(0.0, 0.0)  && // both unequal
          !(T(1.0, 1.0) != T(1.0, 1.0)) && // both equal
            T(1.0, 2.0) != T(1.0, 3.0)  && // first equal, second unequal
            T(1.0, 2.0) != T(2.0, 2.0);    // first unequal, second equal
      }
      template<typename T>
      INLINE static bool v2f_greater()
      {
         return
            T(1.0, 1.0) > T(0.0, 0.0)  && // both greater
          !(T(0.0, 0.0) > T(1.0, 1.0)) && // both smaller
          !(T(1.0, 1.0) > T(0.0, 2.0)) && // first greater, second smaller
          !(T(0.0, 2.0) > T(2.0, 1.0));   // first smaller, second greater
      }
      template<typename T>
      INLINE static bool v2f_greaterequal()
      {
         return
            T(1.0, 1.0) >= T(0.0, 0.0)  && // both greater
            T(1.0, 1.0) >= T(1.0, 1.0)  && // both equal
            T(1.0, 1.0) >= T(0.0, 1.0)  && // first greater, second equal
            T(0.0, 1.0) >= T(0.0, 0.0)  && // first equal, second greater
          !(T(1.0, 1.0) >= T(0.0, 2.0)) && // first greater, second less
          !(T(0.0, 2.0) >= T(2.0, 1.0));   // first less, second greater
      }
      template<typename T>
      INLINE static bool v2f_less()
      {
         return
            T(0.0, 0.0) < T(1.0, 1.0)  && // both less
          !(T(1.0, 1.0) < T(0.0, 0.0)) && // both greater
          !(T(1.0, 1.0) < T(0.0, 2.0)) && // first greater, second smaller
          !(T(0.0, 2.0) < T(2.0, 1.0));   // first smaller, second greater
      }
      template<typename T>
      INLINE static bool v2f_lessequal()
      {
         return
            T(0.0, 0.0) <= T(1.0, 1.0)  && // both less
            T(1.0, 1.0) <= T(1.0, 1.0)  && // both equal
            T(0.0, 1.0) <= T(1.0, 1.0)  && // first smaller, second equal
            T(0.0, 0.0) <= T(0.0, 1.0)  && // first equal, second smaller
          !(T(1.0, 1.0) <= T(0.0, 2.0)) && // first greater, second less
          !(T(0.0, 2.0) <= T(2.0, 1.0));   // first less, second greater
      }
      // Arithmetic
      template<typename T>
      INLINE static bool v2f_add()
      {
         return
            T(1.0, 1.0) + T(1.0, 1.0) == T(2.0, 2.0);
      }
      template<typename T>
      INLINE static bool v2f_sub()
      {
         return
            T(2.0, 2.0) - T(1.0, 1.0) == T(1.0, 1.0);
      }
      template<typename T>
      INLINE static bool v2f_mul()
      {
         return
            T(2.0, 2.0) * T(3.0, 3.0) == T(6.0, 6.0);
      }
      template<typename T>
      INLINE static bool v2f_div()
      {
         return
            T(6.0, 6.0) / T(3.0, 3.0) == T(2.0, 2.0);
      }
      template<typename T>
      INLINE static bool v2f_madd()
      {
         T x0(6.0, 6.0); x0.madd(T(3.0, 3.0), T(1.0, 1.0)); if (x0 != T(19.0, 19.0)) return false;
         return true;
      }
      template<typename T>
      INLINE static bool v2f_msub()
      {
         T x0(6.0, 6.0); x0.msub(T(3.0, 3.0), T(1.0, 1.0)); if (x0 != T(17.0, 17.0)) return false;
         return true;
      }
      // Operations
      template<typename T>
      INLINE static bool v2f_swap()
      {
         T x00(6.0, 6.0), x01(3.0, 3.0); x00.swap(x01); if (x00 != T(3.0, 3.0) || x01 != T(6.0, 6.0)) return false;
         return true;
      }
      template<typename T>
      INLINE static bool v2f_abs()
      {
         T x0( 1.0,  1.0); x0.abs(); if (x0 != T(1.0, 1.0)) return false;
         T x1(-1.0, -1.0); x1.abs(); if (x1 != T(1.0, 1.0)) return false;
         return
            T( 1.0,  1.0).absC() == T(1.0, 1.0) &&
            T(-1.0, -1.0).absC() == T(1.0, 1.0);
      }
      template<typename T>
      INLINE static bool v2f_min()
      {
         T x0( 1.0,  1.0); x0.min(T(-1.0, -1.0)); if (x0 != T(-1.0, -1.0)) return false;
         T x1(-1.0, -1.0); x1.min(T( 1.0,  1.0)); if (x1 != T(-1.0, -1.0)) return false;
         return
            T( 1.0,  1.0).minC(T(-1.0, -1.0)) == T(-1.0, -1.0) &&
            T(-1.0, -1.0).minC(T( 1.0,  1.0)) == T(-1.0, -1.0);
      }
      template<typename T>
      INLINE static bool v2f_max()
      {
         T x0( 1.0,  1.0); x0.max(T(-1.0, -1.0)); if (x0 != T(1.0, 1.0)) return false;
         T x1(-1.0, -1.0); x1.max(T( 1.0,  1.0)); if (x1 != T(1.0, 1.0)) return false;
         return
            T( 1.0,  1.0).maxC(T(-1.0, -1.0)) == T(1.0, 1.0) &&
            T(-1.0, -1.0).maxC(T( 1.0,  1.0)) == T(1.0, 1.0);
      }
      template<typename T>
      INLINE static bool v2f_dot()
      {
         return
            T(2.0, 2.0).dot(T(3.0, 3.0)) == 12.0;
      }
      template<typename T>
      INLINE static bool v2f_cross()
      {
         return
            T(2.0, 2.0).cross(T(3.0, 3.0)) == 0.0;
      }
      template<typename T>
      INLINE static bool v2f_length()
      {
         return
            T(0.0, 0.0).length() == 0.0 &&
            T(3.0, 0.0).length() == 3.0;
      }
      template<typename T>
      INLINE static bool v2f_side()
      {
         return
            T(1.0, 0.0).side(T(0.0, 0.0), T(0.0, 1.0)) == -1.0;
      }
      template<typename T>
      INLINE static bool v2f_area()
      {
         return
            T(0.0, 0.0).area(T(2.0, 2.0))              == 4.0 && // Box
            T(0.0, 0.0).area(T(2.0, 0.0), T(0.0, 2.0)) == 2.0;   // Triangle
      }
      template<typename T, typename S>
      INLINE static bool v2f_inside()
      {
         // note: radius and epsilon on circle variants are squared!
         return
            T((S)0.0, (S)0.0).inside(T((S)-1.0,-(S)1.0), T((S)1.0, (S)1.0))         == true  && // Box (middle)
            T((S)0.0, (S)0.0).inside(T((S) 0.0, (S)0.0), T((S)1.0, (S)1.0))         == true  && // Box (edge case)
            T((S)0.0, (S)0.0).inside(T((S) 0.1, (S)0.1), T((S)1.0, (S)1.0), (S)0.1) == true  && // Box (edge case, eps)
            T((S)0.0, (S)0.0).inside(T((S) 1.0, (S)1.0), T((S)2.0, (S)2.0))         == false && // Box (outside)
            T((S)0.0, (S)0.0).inside(T((S) 0.0, (S)0.0), (S)1.0)                    == true  && // Circle (middle)
            T((S)1.0, (S)0.0).inside(T((S) 0.0, (S)0.0), (S)1.0)                    == true  && // Circle (edge case)
            T((S)0.0, (S)0.0).inside(T((S) 3.0, (S)0.0), (S)1.0)                    == false && // Circle (outside)
            T((S)2.1, (S)0.0).inside(T((S) 0.0, (S)0.0), (S)4.0, (S)0.41)           == true;    // Circle (edge case, eps)
      }
      // Operations Float Only
      template<typename T, typename S>
      INLINE static bool v2f_round()
      {
         T x0((S) 1.1, (S) 1.1); x0.round();       if (x0 != T((S) 1.0, (S) 1.0)) return false;
         T x1((S)-1.9, (S)-1.9); x1.round();       if (x1 != T((S)-2.0, (S)-2.0)) return false;
         T x2((S)-9.9, (S)-7.5); x2.round((S)4.0); if (x2 != T((S)-8.0, (S)-8.0)) return false;
         return
            T((S) 1.1, (S) 1.1).roundC()       == T((S) 1.0, (S) 1.0) &&
            T((S)-1.9, (S)-1.9).roundC()       == T((S)-2.0, (S)-2.0) &&
            T((S)-9.9, (S)-7.5).roundC((S)4.0) == T((S)-8.0, (S)-8.0);
      }
      template<typename T>
      INLINE static bool v2f_floor()
      {
         T x0( 1.1,  1.1); x0.floor(); if (x0 != T( 1.0,  1.0)) return false;
         T x1(-1.9, -1.9); x1.floor(); if (x1 != T(-2.0, -2.0)) return false;
         return
            T( 1.1,  1.1).floorC() == T( 1.0,  1.0) &&
            T(-1.9, -1.9).floorC() == T(-2.0, -2.0);
      }
      template<typename T>
      INLINE static bool v2f_ceil()
      {
         T x0( 1.1,  1.1); x0.ceil(); if (x0 != T( 2.0,  2.0)) return false;
         T x1(-1.9, -1.9); x1.ceil(); if (x1 != T(-1.0, -1.0)) return false;
         return
            T( 1.1,  1.1).ceilC() == T( 2.0,  2.0) &&
            T(-1.9, -1.9).ceilC() == T(-1.0, -1.0);
      }
      template<typename T>
      INLINE static bool v2f_normalise()
      {
         T x0(2.0,  0.0); x0.normalise(); if (x0 != T(1.0, 0.0)) return false;
         T x1(1.0 , 1.0); x1.normalise(); if (x1 != T(0.70710678118654746, 0.70710678118654746)) return false;
         return
            T(2.0, 0.0).normaliseC() == T(1.0, 0.0) &&
            T(1.0, 1.0).normaliseC() == T(0.70710678118654746, 0.70710678118654746);
      }
      template<typename V, typename S>
      INLINE static bool v2f_rotate()
      {
         // CLW
         V x0(1.0, 0.0); x0.rotate((S)(0.0));        if (!x0.equals(V( 1.0, 0.0), (S)0.000000000)) return false; // E->E
         V x1(1.0, 0.0); x1.rotate((S)(M_PI * 0.5)); if (!x1.equals(V( 0.0, 1.0), (S)0.000000001)) return false; // E->N
         V x2(1.0, 0.0); x2.rotate((S)(M_PI));       if (!x2.equals(V(-1.0, 0.0), (S)0.000000001)) return false; // E->W
         V x3(1.0, 0.0); x3.rotate((S)(M_PI * 1.5)); if (!x3.equals(V( 0.0,-1.0), (S)0.000000001)) return false; // E->S
         return true;
      }
      template<typename V, typename S>
      INLINE static bool v2f_angle()
      {
         // CLW FROM UNITX (=1,0), RANGE (0-PI)
         bool a =
            ISZERO(V::_abs(V( 1.0, 0.0).angle() - (S)(0.0)),        (S)0.000001) && // EAST  |  0°
            ISZERO(V::_abs(V( 0.0,-1.0).angle() - (S)(M_PI * 0.5)), (S)0.000001) && // SOUTH | 90°
            ISZERO(V::_abs(V(-1.0, 0.0).angle() - (S)(M_PI)),       (S)0.000001) && // WEST  |180°
            ISZERO(V::_abs(V( 0.0, 1.0).angle() - (S)(M_PI * 0.5)), (S)0.000001);   // NORTH | 90°

         // CLW FROM UNITY (=0,1), RANGE (0-PI)
         bool b =
            ISZERO(V::_abs(V(0.0, 1.0).angle(V( 0.0, 1.0)) - (S)(0.0)),        (S)0.000001) && // NORTH-2-NORTH |  0°
            ISZERO(V::_abs(V(0.0, 1.0).angle(V( 1.0, 0.0)) - (S)(M_PI * 0.5)), (S)0.000001) && // NORTH-2-EAST  | 90°
            ISZERO(V::_abs(V(0.0, 1.0).angle(V( 0.0,-1.0)) - (S)(M_PI)),       (S)0.000001) && // NORTH-2-SOUTH |180°
            ISZERO(V::_abs(V(0.0, 1.0).angle(V(-1.0, 0.0)) - (S)(M_PI * 0.5)), (S)0.000001);   // NORTH-2-WEST  | 90°

         return a && b;
      }
      template<typename V, typename S>
      INLINE static bool v2f_angleori()
      {
         // CCLW FROM UNITX (=1,0) RANGE (0-2PI)
         return
            ISZERO(V::_abs(V( 1.0, 0.0).angleOri() - (S)(0.0)),        (S)0.000001) && // EAST  |  0°
            ISZERO(V::_abs(V( 0.0, 1.0).angleOri() - (S)(M_PI * 0.5)), (S)0.000001) && // NORTH | 90°
            ISZERO(V::_abs(V(-1.0, 0.0).angleOri() - (S)(M_PI)),       (S)0.000001) && // WEST  |180°
            ISZERO(V::_abs(V( 0.0,-1.0).angleOri() - (S)(M_PI * 1.5)), (S)0.000001);   // SOUTH |270
      }
      template<typename V, typename S>
      INLINE static bool v2f_intersectcircleline()
      {
         V p;
         return
            // without intersection point
            V(0.0, 0.0).intersectCircleLine(V(0.5, 0.5), V(1.5, 1.5), 1.0, (S)0.000001, false) == true  && // intersect
            V(0.0, 0.0).intersectCircleLine(V(5.5, 5.5), V(6.5, 6.5), 1.0, (S)0.000001, false) == false && // out
            V(0.0, 0.0).intersectCircleLine(V(0.5, 0.5), V(0.6, 0.6), 1.0, (S)0.000001, true)  == true  && // inside (with in=true)
            V(0.0, 0.0).intersectCircleLine(V(0.5, 0.5), V(0.6, 0.6), 1.0, (S)0.000001, false) == false && // inside (with in=false)
            // with intersection point
            V(0.0, 0.0).intersectCircleLine(V(0.0, 0.5), V(0.0, 1.5), 1.0, (S)0.000001, false, p) == true && p == V(0.0, 1.0) && // intersect
            V(0.0, 0.0).intersectCircleLine(V(0.5, 0.0), V(1.5, 0.0), 1.0, (S)0.000001, false, p) == true && p == V(1.0, 0.0) && // intersect
            V(0.0, 0.0).intersectCircleLine(V(0.0, 1.0), V(0.0, 2.0), 1.0, (S)0.000001, false, p) == true && p == V(0.0, 1.0);   // touch at s
      }
      template<typename V>
      INLINE static bool v2f_minsquareddistancetofiniteline()
      {
         size_t c;
         return 
            V(0.0, 0.0).minSquaredDistanceToFiniteLine(V(0.0, 1.0), V(0.0, 2.0), c) == 1.0 && c == 1 && // s closest
            V(0.0, 3.0).minSquaredDistanceToFiniteLine(V(0.0, 1.0), V(0.0, 2.0), c) == 1.0 && c == 2 && // e closest
            V(1.0, 0.0).minSquaredDistanceToFiniteLine(V(0.0, 1.0), V(2.0, 1.0), c) == 1.0 && c == 3;   // p on line closest
      }
      template<typename V, typename S>
      INLINE static bool v2f_insidefrustum()
      {
         return 
            V::insideFrustum(V(-1.0, 0.0), V(0.0, 0.0), (S)0.0, (S)0.1) == false && // back  (exact, facing E)
            V::insideFrustum(V( 1.0, 0.0), V(0.0, 0.0), (S)M_PI,(S)0.1) == false && // back  (exact, facing W)
            V::insideFrustum(V(-0.1, 1.0), V(0.0, 0.0), (S)0.0, (S)1.0) == false && // back  (barely)
            V::insideFrustum(V( 0.1, 1.0), V(0.0, 0.0), (S)0.0, (S)1.0) == false && // front (too left/right 1)
            V::insideFrustum(V( 0.1,-1.0), V(0.0, 0.0), (S)0.0, (S)1.0) == false && // front (too left/right 2)
            V::insideFrustum(V( 1.0, 0.0), V(0.0, 0.0), (S)0.0, (S)0.1) == true  && // front (exact)
            V::insideFrustum(V( 1.0, 1.0), V(0.0, 0.0), (S)0.0, (S)1.0) == true  && // front (inside edge-case)
            V::insideFrustum(V( 1.0, 1.0), V(0.0, 0.0), (S)0.0, (S)0.9) == false;   // front (outside edge-case)
      }
      ///////////////// INT32 / INT64 /////////////////
      // Constructor
      template<typename T, typename S, typename T1, typename S1, typename T2, typename S2, typename T3, typename S3>
      INLINE static bool v2i_ctr()
      {
         // from array/ptr
         double  td[2]{ 0.9,  1.1  }; T tdt(td); // from double
         float   tf[2]{ 0.9f, 1.1f }; T tft(tf); // from float
         int64_t tl[2]{ 1LL,  1LL  }; T tlt(tl); // from int64 
         int32_t ti[2]{ 1L,   1L   }; T tit(ti); // from int32
         bool ok1 = 
            tdt.x == (S)0.0  && tdt.y == (S)1.0  &&
            tft.x == (S)0.0f && tft.y == (S)1.0f &&
            tlt.x == (S)1LL  && tlt.y == (S)1LL  &&
            tit.x == (S)1L   && tit.y == (S)1L;

         // from values
         T md((double)0.9, (double)1.1);  // from double
         T mf((float) 0.9f,(float) 1.1f); // from float
         T ml((int64_t)1LL,(int64_t)1LL); // from int64 
         T mi((int32_t)1L, (int32_t)1L);  // from int32
         bool ok2 =
            md.x  == (S)0.0  && md.y  == (S)1.0  &&
            mf.x  == (S)0.0f && mf.y  == (S)1.0f &&
            ml.x  == (S)1LL  && ml.y  == (S)1LL  &&
            mi.x  == (S)1L   && mi.y  == (S)1L;

         // from scalar
         T mds((double)0.9);  // from double
         T mfs((float) 0.9f); // from float
         T mls((int64_t)1LL); // from int64 
         T mis((int32_t)1L);  // from int32
         bool ok3 =
            mds.x == (S)0.0  && mds.y == (S)0.0  &&
            mfs.x == (S)0.0f && mfs.y == (S)0.0f &&
            mls.x == (S)1LL  && mls.y == (S)1LL  &&
            mis.x == (S)1L   && mis.y == (S)1L;

         // from three other V2 types
         // e.g. for V2i from V2f, V2d, V2l
         T o1(T1((S1)0.9, (S1)1.1));
         T o2(T2((S2)0.9, (S2)1.1));
         T o3(T3((S3)0.9, (S3)1.1));
         bool ok4 =
               o1.x == (S)(S1)0.9 && o1.y == (S)(S1)1.1 &&
               o2.x == (S)(S2)0.9 && o2.y == (S)(S2)1.1 &&
               o3.x == (S)(S3)0.9 && o3.y == (S)(S3)1.1;

         return ok1 && ok2 && ok3 && ok4;
      }
      // Comparison
      template<typename T>
      INLINE static bool v2i_equal()
      {
         return
            T(1, 1) == T(1, 1)  && // both equal
          !(T(1, 1) == T(2, 2)) && // both uneqal
          !(T(1, 2) == T(1, 3)) && // first equal, second unequal
          !(T(1, 2) == T(2, 2));   // first unequal, second equal
      }
      template<typename T>
      INLINE static bool v2i_notequal()
      {
         return
            T(1, 1) != T(0, 0)  && // both unequal
          !(T(1, 1) != T(1, 1)) && // both equal
            T(1, 1) != T(1, 2)  && // first equal, second unequal
            T(2, 1) != T(1, 1);    // first unequal, second equal
      }
      template<typename T>
      INLINE static bool v2i_greater()
      {
         return
            T(1, 1) > T(0, 0)  && // both greater
          !(T(0, 0) > T(1, 1)) && // both smaller
          !(T(1, 1) > T(0, 2)) && // first greater, second smaller
          !(T(0, 2) > T(2, 1));   // first smaller, second greater
      }
      template<typename T>
      INLINE static bool v2i_greaterequal()
      {
         return
            T(1, 1) >= T(0, 0)  && // both greater
            T(1, 1) >= T(1, 1)  && // both equal
            T(1, 1) >= T(0, 1)  && // first greater, second equal
            T(0, 1) >= T(0, 0)  && // first equal, second greater
          !(T(1, 1) >= T(0, 2)) && // first greater, second less
          !(T(0, 2) >= T(2, 1));   // first less, second greater
      }
      template<typename T>
      INLINE static bool v2i_less()
      {
         return
            T(0, 0) < T(1, 1)  && // both less
          !(T(1, 1) < T(0, 0)) && // both greater
          !(T(1, 1) < T(0, 2)) && // first greater, second smaller
          !(T(0, 2) < T(2, 1));   // first smaller, second greater
      }
      template<typename T>
      INLINE static bool v2i_lessequal()
      {
         return
            T(0, 0) <= T(1, 1)  && // both smaller
            T(1, 1) <= T(1, 1)  && // both equal
            T(0, 1) <= T(1, 1)  && // first smaller, second equal
            T(0, 0) <= T(0, 1)  && // first equal, second smaller
          !(T(1, 1) <= T(0, 2)) && // first greater, second less
          !(T(0, 2) <= T(2, 1));   // first less, second greater
      }
      // Arithmetic
      template<typename T>
      INLINE static bool v2i_add()
      {
         return
            T(1, 1) + T(1, 1) == T(2, 2);
      }
      template<typename T>
      INLINE static bool v2i_sub()
      {
         return
            T(2, 2) - T(1, 1) == T(1, 1);
      }
      template<typename T>
      INLINE static bool v2i_mul()
      {
         return
            T(2, 2) * T(3, 3) == T(6, 6);
      }
      template<typename T>
      INLINE static bool v2i_div()
      {
         return
            T(6, 6) / T(3, 3) == T(2, 2);
      }
      template<typename T>
      INLINE static bool v2i_madd()
      {
         T x0(6, 6); x0.madd(T(3, 3), T(1, 1)); if (x0 != T(19, 19)) return false;
         return true;
      }
      template<typename T>
      INLINE static bool v2i_msub()
      {
         T x0(6, 6); x0.msub(T(3, 3), T(1, 1)); if (x0 != T(17, 17)) return false;
         return true;
      }
      // Operations
      template<typename T>
      INLINE static bool v2i_swap()
      {
         T x00(6, 6), x01(3, 3); x00.swap(x01); if (x00 != T(3, 3) || x01 != T(6, 6)) return false;
         return true;
      }
      template<typename T>
      INLINE static bool v2i_abs()
      {
         T x0( 1,  1); x0.abs(); if (x0 != T(1, 1)) return false;
         T x1(-1, -1); x1.abs(); if (x1 != T(1, 1)) return false;

         return
            T( 1,  1).absC() == T(1, 1) &&
            T(-1, -1).absC() == T(1, 1);
      }
      template<typename T>
      INLINE static bool v2i_min()
      {
         T x0( 1,  1); x0.min(T(-1, -1)); if (x0 != T(-1, -1)) return false;
         T x1(-1, -1); x1.min(T( 1,  1)); if (x1 != T(-1, -1)) return false;
         return
            T( 1,  1).minC(T(-1, -1)) == T(-1, -1) &&
            T(-1, -1).minC(T( 1,  1)) == T(-1, -1);
      }
      template<typename T>
      INLINE static bool v2i_max()
      {
         T x0( 1,  1); x0.max(T(-1, -1)); if (x0 != T(1, 1)) return false;
         T x1(-1, -1); x1.max(T( 1,  1)); if (x1 != T(1, 1)) return false;
         return
            T( 1,  1).maxC(T(-1, -1)) == T(1, 1) &&
            T(-1, -1).maxC(T( 1,  1)) == T(1, 1);
      }
      template<typename T>
      INLINE static bool v2i_dot()
      {
         return
            T(2, 2).dot(T(3, 3)) == 12;
      }
      template<typename T>
      INLINE static bool v2i_cross()
      {
         return
            T(2, 2).cross(T(3, 3)) == 0;
      }
      template<typename T>
      INLINE static bool v2i_length()
      {
         return
            T(0, 0).length() == 0 &&
            T(3, 0).length() == 3;
      }
      template<typename T>
      INLINE static bool v2i_side()
      {
         return
            T(1, 0).side(T(0, 0), T(0, 1)) == -1;
      }
      template<typename T>
      INLINE static bool v2i_area()
      {
         return
            T(0, 0).area(T(2, 2))          == 4 && // Box
            T(0, 0).area(T(2, 0), T(0, 2)) == 2;   // Triangle
      }
      template<typename T>
      INLINE static bool v2i_inside()
      {
         return
            T(0, 0).inside(T(-1,-1), T(1, 1))    == true  && // Box (middle)
            T(0, 0).inside(T( 0, 0), T(1, 1))    == true  && // Box (edge case)
            T(0, 0).inside(T( 1, 1), T(2, 2), 1) == true  && // Box (edge case, eps)
            T(0, 0).inside(T( 1, 1), T(2, 2))    == false && // Box (outside)
            T(0, 0).inside(T( 0, 0), 1)          == true  && // Circle (middle)
            T(1, 0).inside(T( 0, 0), 1)          == true  && // Circle (edge case)
            T(0, 0).inside(T( 3, 0), 1)          == false;   // Circle (outside)
      }
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Math {
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(V2)
   {
   public:
      TEST_METHOD(SIZEOF)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2_sizeof()); }
      // FLOAT (GENERIC)
      TEST_METHOD(CTR_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_ctr<V2fg, float, V2dg, double, V2ig, int32_t, V2lg, int64_t>()); }
      TEST_METHOD(EQUAL_FG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_equal<V2fg>()); }
      TEST_METHOD(NOTEQUAL_FG)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_notequal<V2fg>()); }
      TEST_METHOD(GREATER_FG)      { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_greater<V2fg>()); }
      TEST_METHOD(GREATEREQUAL_FG) { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_greaterequal<V2fg>()); }
      TEST_METHOD(LESS_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_less<V2fg>()); }
      TEST_METHOD(LESSEQUAL_FG)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_lessequal<V2fg>()); }
      TEST_METHOD(ADD_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_add<V2fg>()); }
      TEST_METHOD(SUB_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_sub<V2fg>()); }
      TEST_METHOD(MUL_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_mul<V2fg>()); }
      TEST_METHOD(DIV_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_div<V2fg>()); }
      TEST_METHOD(MADD_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_madd<V2fg>()); }
      TEST_METHOD(MSUB_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_msub<V2fg>()); }
      TEST_METHOD(SWAP_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_swap<V2fg>()); }
      TEST_METHOD(ABS_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_abs<V2fg>()); }
      TEST_METHOD(MIN_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_min<V2fg>()); }
      TEST_METHOD(MAX_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_max<V2fg>()); }
      TEST_METHOD(DOT_FG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_dot<V2fg>()); }
      TEST_METHOD(CROSS_FG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_cross<V2fg>()); }
      TEST_METHOD(LENGTH_FG)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_length<V2fg>()); }
      TEST_METHOD(SIDE_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_side<V2fg>()); }
      TEST_METHOD(AREA_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_area<V2fg>()); }
      TEST_METHOD(INSIDE_FG)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_inside<V2fg, float>()); }
      TEST_METHOD(ROUND_FG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_round<V2fg, float>()); }
      TEST_METHOD(FLOOR_FG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_floor<V2fg>()); }
      TEST_METHOD(CEIL_FG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_ceil<V2fg>()); }
      TEST_METHOD(NORMALISE_FG)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_normalise<V2fg>()); }
      TEST_METHOD(ROTATE_FG)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_rotate<V2fg, float>()); }
      TEST_METHOD(ANGLE_FG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_angle<V2fg, float>()); }
      TEST_METHOD(ANGLEORI_FG)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_angleori<V2fg, float>()); }
      TEST_METHOD(INTERSECTCL_FG)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_intersectcircleline<V2fg, float>()); }
      TEST_METHOD(MINSQDISTFL_FG)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_minsquareddistancetofiniteline<V2fg>()); }
      TEST_METHOD(INSIDEFRUST_FG)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_insidefrustum<V2fg, float>()); }

      // DOUBLE (GENERIC)
      TEST_METHOD(CTR_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_ctr<V2dg, double, V2fg, float, V2ig, int32_t, V2lg, int64_t>()); }
      TEST_METHOD(EQUAL_DG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_equal<V2dg>()); }
      TEST_METHOD(NOTEQUAL_DG)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_notequal<V2dg>()); }
      TEST_METHOD(GREATER_DG)      { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_greater<V2dg>()); }
      TEST_METHOD(GREATEREQUAL_DG) { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_greaterequal<V2dg>()); }
      TEST_METHOD(LESS_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_less<V2dg>()); }
      TEST_METHOD(LESSEQUAL_DG)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_lessequal<V2dg>()); }
      TEST_METHOD(ADD_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_add<V2dg>()); }
      TEST_METHOD(SUB_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_sub<V2dg>()); }
      TEST_METHOD(MUL_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_mul<V2dg>()); }
      TEST_METHOD(DIV_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_div<V2dg>()); }
      TEST_METHOD(MADD_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_madd<V2dg>()); }
      TEST_METHOD(MSUB_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_msub<V2dg>()); }
      TEST_METHOD(SWAP_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_swap<V2dg>()); }
      TEST_METHOD(ABS_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_abs<V2dg>()); }
      TEST_METHOD(MIN_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_min<V2dg>()); }
      TEST_METHOD(MAX_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_max<V2dg>()); }
      TEST_METHOD(DOT_DG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_dot<V2dg>()); }
      TEST_METHOD(CROSS_DG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_cross<V2dg>()); }
      TEST_METHOD(LENGTH_DG)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_length<V2dg>()); }
      TEST_METHOD(SIDE_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_side<V2dg>()); }
      TEST_METHOD(AREA_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_area<V2dg>()); }
      TEST_METHOD(INSIDE_DG)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_inside<V2dg, double>()); }
      TEST_METHOD(ROUND_DG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_round<V2dg, double>()); }
      TEST_METHOD(FLOOR_DG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_floor<V2dg>()); }
      TEST_METHOD(CEIL_DG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_ceil<V2dg>()); }
      TEST_METHOD(NORMALISE_DG)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_normalise<V2dg>()); }
      TEST_METHOD(ROTATE_DG)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_rotate<V2dg, double>()); }
      TEST_METHOD(ANGLE_DG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_angle<V2dg, double>()); }
      TEST_METHOD(ANGLEORI_DG)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_angleori<V2dg, double>()); }
      TEST_METHOD(INTERSECTCL_DG)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_intersectcircleline<V2dg, double>()); }
      TEST_METHOD(MINSQDISTFL_DG)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_minsquareddistancetofiniteline<V2dg>()); }
      TEST_METHOD(INSIDEFRUST_DG)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_insidefrustum<V2dg, double>()); }

      // INT32 (GENERIC)
      TEST_METHOD(CTR_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_ctr<V2ig, int32_t, V2lg, int64_t, V2fg, float, V2dg, double>()); }
      TEST_METHOD(EQUAL_IG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_equal<V2ig>()); }
      TEST_METHOD(NOTEQUAL_IG)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_notequal<V2ig>()); }
      TEST_METHOD(GREATER_IG)      { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_greater<V2ig>()); }
      TEST_METHOD(GREATEREQUAL_IG) { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_greaterequal<V2ig>()); }
      TEST_METHOD(LESS_IG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_less<V2ig>()); }
      TEST_METHOD(LESSEQUAL_IG)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_lessequal<V2ig>()); }
      TEST_METHOD(ADD_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_add<V2ig>()); }
      TEST_METHOD(SUB_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_sub<V2ig>()); }
      TEST_METHOD(MUL_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_mul<V2ig>()); }
      TEST_METHOD(DIV_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_div<V2ig>()); }
      TEST_METHOD(MADD_IG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_madd<V2ig>()); }
      TEST_METHOD(MSUB_IG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_msub<V2ig>()); }
      TEST_METHOD(SWAP_IG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_swap<V2ig>()); }
      TEST_METHOD(ABS_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_abs<V2ig>()); }
      TEST_METHOD(MIN_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_min<V2ig>()); }
      TEST_METHOD(MAX_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_max<V2ig>()); }
      TEST_METHOD(DOT_IG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_dot<V2ig>()); }
      TEST_METHOD(CROSS_IG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_cross<V2ig>()); }
      TEST_METHOD(LENGTH_IG)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_length<V2ig>()); }
      TEST_METHOD(SIDE_IG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_side<V2ig>()); }
      TEST_METHOD(AREA_IG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_area<V2ig>()); }
      TEST_METHOD(INSIDE_IG)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_inside<V2ig>()); }
      
      // INT64 (GENERIC)
      TEST_METHOD(CTR_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_ctr<V2lg, int64_t, V2ig, int32_t, V2fg, float, V2dg, double>()); }
      TEST_METHOD(EQUAL_LG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_equal<V2lg>()); }
      TEST_METHOD(NOTEQUAL_LG)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_notequal<V2lg>()); }
      TEST_METHOD(GREATER_LG)      { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_greater<V2lg>()); }
      TEST_METHOD(GREATEREQUAL_LG) { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_greaterequal<V2lg>()); }
      TEST_METHOD(LESS_LG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_less<V2lg>()); }
      TEST_METHOD(LESSEQUAL_LG)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_lessequal<V2lg>()); }
      TEST_METHOD(ADD_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_add<V2lg>()); }
      TEST_METHOD(SUB_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_sub<V2lg>()); }
      TEST_METHOD(MUL_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_mul<V2lg>()); }
      TEST_METHOD(DIV_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_div<V2lg>()); }
      TEST_METHOD(MADD_LG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_madd<V2lg>()); }
      TEST_METHOD(MSUB_LG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_msub<V2lg>()); }
      TEST_METHOD(SWAP_LG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_swap<V2lg>()); }
      TEST_METHOD(ABS_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_abs<V2lg>()); }
      TEST_METHOD(MIN_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_min<V2lg>()); }
      TEST_METHOD(MAX_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_max<V2lg>()); }
      TEST_METHOD(DOT_LG)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_dot<V2lg>()); }
      TEST_METHOD(CROSS_LG)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_cross<V2lg>()); }
      TEST_METHOD(LENGTH_LG)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_length<V2lg>()); }
      TEST_METHOD(SIDE_LG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_side<V2lg>()); }
      TEST_METHOD(AREA_LG)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_area<V2lg>()); }
      TEST_METHOD(INSIDE_LG)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_inside<V2lg>()); }

#if defined(CPPCORE_CPUFEAT_SSE2)
      // FLOAT (SIMD)
      TEST_METHOD(ALIGNMENT_FS)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2_alignment<V2fs, 8>()); }
      TEST_METHOD(CTR_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_ctr<V2fs, float, V2ds, double, V2is, int32_t, V2ls, int64_t>()); }
      TEST_METHOD(EQUAL_FS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_equal<V2fs>()); }
      TEST_METHOD(NOTEQUAL_FS)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_notequal<V2fs>()); }
      TEST_METHOD(GREATER_FS)      { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_greater<V2fs>()); }
      TEST_METHOD(GREATEREQUAL_FS) { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_greaterequal<V2fs>()); }
      TEST_METHOD(LESS_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_less<V2fs>()); }
      TEST_METHOD(LESSEQUAL_FS)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_lessequal<V2fs>()); }
      TEST_METHOD(ADD_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_add<V2fs>()); }
      TEST_METHOD(SUB_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_sub<V2fs>()); }
      TEST_METHOD(MUL_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_mul<V2fs>()); }
      TEST_METHOD(DIV_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_div<V2fs>()); }
      TEST_METHOD(MADD_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_madd<V2fs>()); }
      TEST_METHOD(MSUB_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_msub<V2fs>()); }
      TEST_METHOD(SWAP_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_swap<V2fs>()); }
      TEST_METHOD(ABS_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_abs<V2fs>()); }
      TEST_METHOD(MIN_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_min<V2fs>()); }
      TEST_METHOD(MAX_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_max<V2fs>()); }
      TEST_METHOD(DOT_FS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_dot<V2fs>()); }
      TEST_METHOD(CROSS_FS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_cross<V2fs>()); }
      TEST_METHOD(LENGTH_FS)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_length<V2fs>()); }
      TEST_METHOD(SIDE_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_side<V2fs>()); }
      TEST_METHOD(AREA_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_area<V2fs>()); }
      TEST_METHOD(INSIDE_FS)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_inside<V2fs, float>()); }
      TEST_METHOD(ROUND_FS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_round<V2fs, float>()); }
      TEST_METHOD(FLOOR_FS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_floor<V2fs>()); }
      TEST_METHOD(CEIL_FS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_ceil<V2fs>()); }
      TEST_METHOD(NORMALISE_FS)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_normalise<V2fs>()); }
      TEST_METHOD(ROTATE_FS)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_rotate<V2fs, float>()); }
      TEST_METHOD(ANGLE_FS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_angle<V2fs, float>()); }
      TEST_METHOD(ANGLEORI_FS)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_angleori<V2fs, float>()); }
      TEST_METHOD(INTERSECTCL_FS)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_intersectcircleline<V2fs, float>()); }
      TEST_METHOD(MINSQDISTFL_FS)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_minsquareddistancetofiniteline<V2fs>()); }
      TEST_METHOD(INSIDEFRUST_FS)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_insidefrustum<V2fs, float>()); }

      // DOUBLE (SIMD)
      TEST_METHOD(ALIGNMENT_DS)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2_alignment<V2ds, 16>()); }
      TEST_METHOD(CTR_DS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_ctr<V2ds, double, V2fs, float, V2is, int32_t, V2ls, int64_t>()); }
      TEST_METHOD(EQUAL_DS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_equal<V2ds>()); }
      TEST_METHOD(NOTEQUAL_DS)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_notequal<V2ds>()); }
      TEST_METHOD(GREATER_DS)      { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_greater<V2ds>()); }
      TEST_METHOD(GREATEREQUAL_DS) { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_greaterequal<V2ds>()); }
      TEST_METHOD(LESS_DS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_less<V2ds>()); }
      TEST_METHOD(LESSEQUAL_DS)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_lessequal<V2ds>()); }
      TEST_METHOD(ADD_DS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_add<V2ds>()); }
      TEST_METHOD(SUB_DS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_sub<V2ds>()); }
      TEST_METHOD(MUL_DS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_mul<V2ds>()); }
      TEST_METHOD(DIV_DS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_div<V2ds>()); }
      TEST_METHOD(MADD_DS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_madd<V2ds>()); }
      TEST_METHOD(MSUB_DS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_msub<V2ds>()); }
      TEST_METHOD(SWAP_DS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_swap<V2ds>()); }
      TEST_METHOD(ABS_DS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_abs<V2ds>()); }
      TEST_METHOD(MIN_DS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_min<V2ds>()); }
      TEST_METHOD(MAX_DS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_max<V2ds>()); }
      TEST_METHOD(DOT_DS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_dot<V2ds>()); }
      TEST_METHOD(CROSS_DS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_cross<V2ds>()); }
      TEST_METHOD(LENGTH_DS)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_length<V2ds>()); }
      TEST_METHOD(SIDE_DS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_side<V2ds>()); }
      TEST_METHOD(AREA_DS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_area<V2ds>()); }
      TEST_METHOD(INSIDE_DS)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_inside<V2ds, double>()); }
      TEST_METHOD(ROUND_DS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_round<V2ds, double>()); }
      TEST_METHOD(FLOOR_DS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_floor<V2ds>()); }
      TEST_METHOD(CEIL_DS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_ceil<V2ds>()); }
      TEST_METHOD(NORMALISE_DS)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_normalise<V2ds>()); }
      TEST_METHOD(ROTATE_DS)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_rotate<V2ds, double>()); }
      TEST_METHOD(ANGLE_DS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_angle<V2ds, double>()); }
      TEST_METHOD(ANGLEORI_DS)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_angleori<V2ds, double>()); }
      TEST_METHOD(INTERSECTCL_DS)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_intersectcircleline<V2ds, double>()); }
      TEST_METHOD(MINSQDISTFL_DS)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_minsquareddistancetofiniteline<V2ds>()); }
      TEST_METHOD(INSIDEFRUST_DS)  { Assert::AreEqual(true, CppCore::Test::Math::V2::v2f_insidefrustum<V2ds, double>()); }

      // INT32 (SIMD)
      TEST_METHOD(ALIGNMENT_IS)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2_alignment<V2is, 8>()); }
      TEST_METHOD(CTR_IS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_ctr<V2is, int32_t, V2ls, int64_t, V2fs, float, V2ds, double>()); }
      TEST_METHOD(EQUAL_IS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_equal<V2is>()); }
      TEST_METHOD(NOTEQUAL_IS)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_notequal<V2is>()); }
      TEST_METHOD(GREATER_IS)      { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_greater<V2is>()); }
      TEST_METHOD(GREATEREQUAL_IS) { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_greaterequal<V2is>()); }
      TEST_METHOD(LESS_IS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_less<V2is>()); }
      TEST_METHOD(LESSEQUAL_IS)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_lessequal<V2is>()); }
      TEST_METHOD(ADD_IS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_add<V2is>()); }
      TEST_METHOD(SUB_IS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_sub<V2is>()); }
      TEST_METHOD(MUL_IS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_mul<V2is>()); }
      TEST_METHOD(DIV_IS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_div<V2is>()); }
      TEST_METHOD(MADD_IS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_madd<V2is>()); }
      TEST_METHOD(MSUB_IS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_msub<V2is>()); }
      TEST_METHOD(ABS_IS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_abs<V2is>()); }
      TEST_METHOD(MIN_IS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_min<V2is>()); }
      TEST_METHOD(MAX_IS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_max<V2is>()); }
      TEST_METHOD(SWAP_IS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_swap<V2is>()); }
      TEST_METHOD(DOT_IS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_dot<V2is>()); }
      TEST_METHOD(CROSS_IS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_cross<V2is>()); }
      TEST_METHOD(LENGTH_IS)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_length<V2is>()); }
      TEST_METHOD(SIDE_IS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_side<V2is>()); }
      TEST_METHOD(AREA_IS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_area<V2is>()); }
      TEST_METHOD(INSIDE_IS)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_inside<V2is>()); }

      // INT64 (SIMD)
      TEST_METHOD(ALIGNMENT_LS)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2_alignment<V2ls, 16>()); }
      TEST_METHOD(CTR_LS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_ctr<V2ls, int64_t, V2is, int32_t, V2fs, float, V2ds, double>()); }
      TEST_METHOD(EQUAL_LS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_equal<V2ls>()); }
      TEST_METHOD(NOTEQUAL_LS)     { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_notequal<V2ls>()); }
      TEST_METHOD(GREATER_LS)      { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_greater<V2ls>()); }
      TEST_METHOD(GREATEREQUAL_LS) { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_greaterequal<V2ls>()); }
      TEST_METHOD(LESS_LS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_less<V2ls>()); }
      TEST_METHOD(LESSEQUAL_LS)    { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_lessequal<V2ls>()); }
      TEST_METHOD(ADD_LS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_add<V2ls>()); }
      TEST_METHOD(SUB_LS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_sub<V2ls>()); }
      TEST_METHOD(MUL_LS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_mul<V2ls>()); }
      TEST_METHOD(DIV_LS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_div<V2ls>()); }
      TEST_METHOD(MADD_LS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_madd<V2ls>()); }
      TEST_METHOD(MSUB_LS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_msub<V2ls>()); }
      TEST_METHOD(ABS_LS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_abs<V2ls>()); }
      TEST_METHOD(MIN_LS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_min<V2ls>()); }
      TEST_METHOD(MAX_LS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_max<V2ls>()); }
      TEST_METHOD(SWAP_LS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_swap<V2ls>()); }
      TEST_METHOD(DOT_LS)          { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_dot<V2ls>()); }
      TEST_METHOD(CROSS_LS)        { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_cross<V2ls>()); }
      TEST_METHOD(LENGTH_LS)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_length<V2ls>()); }
      TEST_METHOD(SIDE_LS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_side<V2ls>()); }
      TEST_METHOD(AREA_LS)         { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_area<V2ls>()); }
      TEST_METHOD(INSIDE_LS)       { Assert::AreEqual(true, CppCore::Test::Math::V2::v2i_inside<V2ls>()); }
#endif
   };
}}}}
#endif
