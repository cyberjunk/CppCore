#pragma once
#pragma warning(disable:26495)

#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>

namespace CppCore
{
   //------------------------------------------------------------------------------------------------------------------------//
   //                                          ROOT TEMPLATE [L1, ABSTRACT]                                                  //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 4D Vector Template for Floating Point (32/64) AND Integer (32/64). [L1]
   /// </summary>
   template <typename V, typename F>
   class V4
   {
   protected:
      INLINE V*   thiss() const { return ((V*)this); }

   public:
      union
      {
         struct { F x, y, z, w; };
         F vals[4];
      };
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V4()                                                                                { }
      INLINE V4(const F x, const F y, const F z, const F w) : x(x), y(y), z(z), w(w)             { }
      INLINE V4(const F s)                                  : x(s), y(s), z(s), w(s)             { }
      INLINE V4(const F v[4])                               : x(v[0]), y(v[1]), z(v[2]), w(v[3]) { }
      INLINE V4(F* const v)                                 : x(v[0]), y(v[1]), z(v[2]), w(v[3]) { }
      //------------------------------------------------------------------------------------------------------------------------//
      static INLINE V ZERO()  { return V((F)0.0, (F)0.0, (F)0.0, (F)0.0); }
      static INLINE V UNITX() { return V((F)1.0, (F)0.0, (F)0.0, (F)0.0); }
      static INLINE V UNITY() { return V((F)0.0, (F)1.0, (F)0.0, (F)0.0); }
      static INLINE V UNITZ() { return V((F)0.0, (F)0.0, (F)1.0, (F)0.0); }
      static INLINE V UNITW() { return V((F)0.0, (F)0.0, (F)0.0, (F)1.0); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void* operator new  (size_t size)          { return malloc(size); }
      INLINE void* operator new[](size_t size)          { return malloc(size); }
      INLINE F     operator []   (const size_t i) const { return vals[i];      }
      INLINE F     operator []   (const size_t i)       { return vals[i];      }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE bool  operator ==   (const V& v)     const { return ((x == v.x) & (y == v.y) & (z == v.z) & (w == v.w)); }
      INLINE bool  operator !=   (const V& v)     const { return ((x != v.x) | (y != v.y) | (z != v.z) | (w != v.w)); }
      INLINE bool  operator <    (const V& v)     const { return ((x <  v.x) & (y <  v.y) & (z <  v.z) & (w <  v.w)); }
      INLINE bool  operator <=   (const V& v)     const { return ((x <= v.x) & (y <= v.y) & (z <= v.z) & (w <= v.w)); }
      INLINE bool  operator >    (const V& v)     const { return ((x >  v.x) & (y >  v.y) & (z >  v.z) & (w >  v.w)); }
      INLINE bool  operator >=   (const V& v)     const { return ((x >= v.x) & (y >= v.y) & (z >= v.z) & (w >= v.w)); }
      INLINE V     operator +    (const V& v)     const { return V(x + v.x, y + v.y, z + v.z, w + v.w);               }
      INLINE V     operator -    (const V& v)     const { return V(x - v.x, y - v.y, z - v.z, w - v.w);               }
      INLINE V     operator *    (const V& v)     const { return V(x * v.x, y * v.y, z * v.z, w * v.w);               }
      INLINE V     operator /    (const V& v)     const { return V(x / v.x, y / v.y, z / v.z, w / v.w);               }
      INLINE V     operator +    (const F  s)     const { return V(x + s,   y + s,   z + s,   w + s);                 }
      INLINE V     operator -    (const F  s)     const { return V(x - s,   y - s,   z - s,   w - s);                 }
      INLINE V     operator *    (const F  s)     const { return V(x * s,   y * s,   z * s,   w * s);                 }
      INLINE V     operator /    (const F  s)     const { return V(x / s,   y / s,   z / s,   w / s);                 }
      INLINE V&    operator =    (const V& v)           { x  = v.x; y  = v.y; z  = v.z; w  = v.w; return *thiss();    }
      INLINE V&    operator +=   (const V& v)           { x += v.x; y += v.y; z += v.z; w += v.w; return *thiss();    }
      INLINE V&    operator -=   (const V& v)           { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *thiss();    }
      INLINE V&    operator *=   (const V& v)           { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *thiss();    }
      INLINE V&    operator /=   (const V& v)           { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *thiss();    }
      INLINE V&    operator =    (const F  s)           { x  = s;   y  = s;   z  = s;   w  = s;   return *thiss();    }
      INLINE V&    operator +=   (const F  s)           { x += s;   y += s;   z += s;   w += s;   return *thiss();    }
      INLINE V&    operator -=   (const F  s)           { x -= s;   y -= s;   z -= s;   w -= s;   return *thiss();    }
      INLINE V&    operator *=   (const F  s)           { x *= s;   y *= s;   z *= s;   w *= s;   return *thiss();    }
      INLINE V&    operator /=   (const F  s)           { x /= s;   y /= s;   z /= s;   w /= s;   return *thiss();    }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE       V  operator - ()               const { return V(-x, -y, -z, -w); }
      INLINE const V& operator + ()               const { return *this;             }
      //------------------------------------------------------------------------------------------------------------------------//
      template<typename T> INLINE T& ref()        const { return *((T*)this); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V&   point()                          const { return *thiss();                                                  }
      INLINE void madd(const V& m, const V& a)           { *thiss() = (*thiss() * m) + a;                                    }
      INLINE bool isZero()                         const { return x == (F)0.0 && y == (F)0.0 && z == (F)0.0 && w == (F)0.0;  }
      INLINE bool isZero(const F e2)               const { return thiss()->length2() <= e2;                                  }
      INLINE bool equals(const V& v, const F e2)   const { return (thiss() - v).length2() <= e2;                             }
      INLINE void swap(V& v)                             { std::swap(x, v.x); std::swap(y, v.y); std::swap(z, v.z); std::swap(w, v.w); }
      INLINE F    dot(const V& v)                  const { return x * v.x + y * v.y + z * v.z + w * v.w;                     }
      INLINE F    length2()                        const { return thiss()->dot(*((V*)this));                                 }
      INLINE F    length()                         const { return V::_sqrt(thiss()->length2());                              }
      INLINE F    distance2(const V& v)            const { return (thiss() - v).length2();                                   }
      INLINE F    distance(const V& v)             const { return V::_sqrt(thiss()->distance2(v));                           }
      INLINE V    maxC(const V& v)                 const { return V(v.x > x ? v.x : x, v.y > y ? v.y : y, v.z > z ? v.z : z, v.w > w ? v.w : w); }
      INLINE V    minC(const V& v)                 const { return V(v.x < x ? v.x : x, v.y < y ? v.y : y, v.z < z ? v.z : z, v.w < w ? v.w : w); }
      INLINE V    boundC(const V& mi, const V& ma) const { V t(thiss()->minC(ma)); t.max(mi); return t;                      }
      INLINE V    absC()                           const { return V(V::_abs(x), V::_abs(y), V::_abs(z), V::_abs(w));         }
      INLINE void max(const V& v)                        { if (v.x > x) x = v.x; if (v.y > y) y = v.y; if (v.z > z) z = v.z; if (v.w > w) w = v.w; }
      INLINE void min(const V& v)                        { if (v.x < x) x = v.x; if (v.y < y) y = v.y; if (v.z < z) z = v.z; if (v.w < w) w = v.w; }
      INLINE void bound(const V& mi, const V& ma)        { thiss()->min(ma); thiss()->max(mi);                               }
      INLINE void abs()                                  { x = V::_abs(x); y = V::_abs(y); z = V::_abs(z); w = V::_abs(w);   }
      //------------------------------------------------------------------------------------------------------------------------//
      //INLINE V    xzy()                            const { return V(x, z, y); }
      //INLINE void xzy() { std::swap(y, z); }
      //------------------------------------------------------------------------------------------------------------------------//
      template<typename PRNG>
      INLINE void randomize(PRNG& prng, const F min, const F max)
      { 
         x = prng.next(min, max);
         y = prng.next(min, max);
         z = prng.next(min, max);
         w = prng.next(min, max);
      }
      template<typename PRNG>
      static INLINE V random(PRNG& prng, const F min, const F max) 
      {
         return V(
            prng.next(min, max), 
            prng.next(min, max), 
            prng.next(min, max),
            prng.next(min, max));
      }
      template<typename PRNG>
      static INLINE void random(PRNG& prng, const F min, const F max, V* v, const size_t size)  
      {
         for (size_t i = 0; i < size; i++) 
            v[i].randomize(prng, min, max);
      }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                 FLOATING POINT & INTEGER TEMPLATES V3 [L2, ABSTRACT]                                   //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 4D Vector Template for Floating Point (32/64) [L2]
   /// </summary>
   template <typename V, typename F>
   class V4fdt : public V4<V, F>
   {
   protected:
      using V4<V, F>::thiss;

   public:
      using V4<V, F>::x;
      using V4<V, F>::y;
      using V4<V, F>::z;
      using V4<V, F>::w;
      using V4<V, F>::vals;

   public:
      INLINE V4fdt()                                                                  { }
      INLINE V4fdt(const F x, const F y, const F z, const F w) : V4<V, F>(x, y, z, w) { }
      INLINE V4fdt(const F s)                                  : V4<V, F>(s, s, s, s) { }
      INLINE V4fdt(const F v[4])                               : V4<V, F>(v)          { }
      INLINE V4fdt(F* const v)                                 : V4<V, F>(v)          { }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V& operator /= (const V& v)       { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return (V&)*this;           }
      INLINE V  operator /  (const V& v) const { return V(x / v.x, y / v.y, z / v.z, w / v.w);                       }
      INLINE V& operator /= (const F  s)       { F t = (F)1.0 / s; x *= t; y *= t; z *= t; w *= t; return (V&)*this; }
      INLINE V  operator /  (const F  s) const { F t = (F)1.0 / s; return V(x * t, y * t, z * t, w * t);             }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void  normalise()                                { *thiss() /= thiss()->length();                                   }
      INLINE V     normaliseC()                         const { V t(*thiss()); t.normalise(); return t;                          }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V     roundC()                             const { return V(V::_round(x), V::_round(y), V::_round(z), V::_round(w)); }
      INLINE V     floorC()                             const { return V(V::_floor(x), V::_floor(y), V::_floor(z), V::_floor(w)); }
      INLINE V     ceilC()                              const { return V(V::_ceil(x),  V::_ceil(y),  V::_ceil(z),  V::_ceil(w));  }
      INLINE V     roundC(const F n)                    const { V c(*thiss()); c.round(n); return c;                            }
      INLINE void  round()                                    { x = V::_round(x); y = V::_round(y); z = V::_round(z); w = V::_round(w); }
      INLINE void  floor()                                    { x = V::_floor(x); y = V::_floor(y); z = V::_floor(z); w = V::_floor(w); }
      INLINE void  ceil()                                     { x = V::_ceil(x);  y = V::_ceil(y);  z = V::_ceil(z);  w = V::_ceil(w);  }
      INLINE void  round(const F n)                           { *thiss() /= n; thiss()->round(); *thiss() *= n;                   }
      //------------------------------------------------------------------------------------------------------------------------//
      static INLINE V    randomN() { V t(V::random()); t.normalise(); return t; }
      static INLINE void randomN(V* v, const size_t size) { for (size_t i = 0; i < size; i++) v[i] = V::randomN(); }
      //------------------------------------------------------------------------------------------------------------------------//
   };

   /// <summary>
   /// Abstract 4D Vector for Integer (32/64) [L2]
   /// </summary>
   template <typename V, typename F>
   class V4ilt : public V4<V, F>
   {
   protected:
      using V4<V, F>::thiss;

   public:
      using V4<V, F>::x;
      using V4<V, F>::y;
      using V4<V, F>::z;
      using V4<V, F>::w;
      using V4<V, F>::vals;

   public:
      static INLINE F _abs(const F s)  { return ::abs(s);     }
      static INLINE F _sqrt(const F s) { return (F)::sqrt(s); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V4ilt()                                                                  { }
      INLINE V4ilt(const F x, const F y, const F z, const F w) : V4<V, F>(x, y, z, w) { }
      INLINE V4ilt(const F s)                                  : V4<V, F>(s, s, s, s) { }
      INLINE V4ilt(const F v[4])                               : V4<V, F>(v)          { }
      INLINE V4ilt(F* const v)                                 : V4<V, F>(v)          { }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                       32-BIT & 64-BIT TEMPLATES [L3, ABSTRACT]                                         //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 4D Vector Template for Single Precision FP [L3]
   /// </summary>
   template <typename V>
   class V4ft : public V4fdt<V, float>
   {
   public:
      static INLINE float _abs(const float s) { return ::fabsf(s); }
      static INLINE float _round(const float s) { return ::roundf(s); }
      static INLINE float _floor(const float s) { return ::floorf(s); }
      static INLINE float _ceil(const float s) { return ::ceilf(s); }
      static INLINE float _sqrt(const float s) { return ::sqrtf(s); }
      static INLINE float _cos(const float s) { return ::cosf(s); }
      static INLINE float _sin(const float s) { return ::sinf(s); }
      static INLINE float _acos(const float s) { return ::acosf(s); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V4ft()                                                                                         { }
      INLINE V4ft(const float x, const float y, const float z, const float w) : V4fdt<V, float>(x, y, z, w) { }
      INLINE V4ft(const float s)                                              : V4fdt<V, float>(s, s, s, s) { }
      INLINE V4ft(const float v[4])                                           : V4fdt<V, float>(v) { }
      INLINE V4ft(float* const v)                                             : V4fdt<V, float>(v) { }
   };

   /// <summary>
   /// Abstract 4D Vector Template for Double Precision FP [L3]
   /// </summary>
   template <typename V>
   class V4dt : public V4fdt<V, double>
   {
   public:
      static INLINE double _abs(const double s) { return ::abs(s); }
      static INLINE double _round(const double s) { return ::round(s); }
      static INLINE double _floor(const double s) { return ::floor(s); }
      static INLINE double _ceil(const double s) { return ::ceil(s); }
      static INLINE double _sqrt(const double s) { return ::sqrt(s); }
      static INLINE double _cos(const double s) { return ::cos(s); }
      static INLINE double _sin(const double s) { return ::sin(s); }
      static INLINE double _acos(const double s) { return ::acos(s); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V4dt() { }
      INLINE V4dt(const double x, const double y, const double z, const double w) : V4fdt<V, double>(x, y, z, w) { }
      INLINE V4dt(const double s)                                                 : V4fdt<V, double>(s, s, s, s) { }
      INLINE V4dt(const double v[4])                                              : V4fdt<V, double>(v)          { }
      INLINE V4dt(double* const v)                                                : V4fdt<V, double>(v)          { }
   };

   /// <summary>
   /// Abstract 4D Vector Template for Integer (32) [L3]
   /// </summary>
   template <typename V>
   class V4it : public V4ilt<V, int32_t>
   {
   public:
      INLINE V4it() { }
      INLINE V4it(const int32_t x, const int32_t y, const int32_t z, const int32_t w) : V4ilt<V, int32_t>(x, y, z, w) { }
      INLINE V4it(const int32_t s)                                                    : V4ilt<V, int32_t>(s, s, s, s) { }
      INLINE V4it(const int32_t v[4])                                                 : V4ilt<V, int32_t>(v)          { }
      INLINE V4it(int32_t* const v)                                                   : V4ilt<V, int32_t>(v)          { }
   };

   /// <summary>
   /// Abstract 4D Vector Template for Integer (64) [L3]
   /// </summary>
   template <typename V>
   class V4lt : public V4ilt<V, int64_t>
   {
   public:
      INLINE V4lt() { }
      INLINE V4lt(const int64_t x, const int64_t y, const int64_t z, const int64_t w) : V4ilt<V, int64_t>(x, y, z, w) { }
      INLINE V4lt(const int64_t s)                                                    : V4ilt<V, int64_t>(s, s, s, s) { }
      INLINE V4lt(const int64_t v[4])                                                 : V4ilt<V, int64_t>(v)          { }
      INLINE V4lt(int64_t* const v)                                                   : V4ilt<V, int64_t>(v)          { }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                     GENERIC/NON-SIMD CLASSES [L4]                                                      //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Single Precision 4D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V4fg : public V4ft<V4fg>
   {
   public:
      INLINE V4fg()                                                                                            { }
      INLINE V4fg(const float x, const float y, const float z, const float w)         : V4ft<V4fg>(x, y, z, w) { }
      INLINE V4fg(const float s)                                                      : V4ft<V4fg>(s, s, s, s) { }
      INLINE V4fg(const float v[4])                                                   : V4ft<V4fg>(v)          { }
      INLINE V4fg(float* const v)                                                     : V4ft<V4fg>(v)          { }
      INLINE V4fg(const int32_t v[4])                                                 : V4ft<V4fg>((float)v[0], (float)v[1], (float)v[2], (float)v[3]) { }
      INLINE V4fg(const double x, const double y, const double z, const double w)     : V4ft<V4fg>((float)x, (float)y, (float)z, (float)w)             { }
      INLINE V4fg(const int32_t x, const int32_t y, const int32_t z, const int32_t w) : V4ft<V4fg>((float)x, (float)y, (float)z, (float)w)             { }
   };

   /// <summary>
   /// Double Precision 4D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V4dg : public V4dt<V4dg>
   {
   public:
      INLINE V4dg()                                                                                            { }
      INLINE V4dg(const double x, const double y, const double z, const double w)     : V4dt<V4dg>(x, y, z, w) { }
      INLINE V4dg(const double s)                                                     : V4dt<V4dg>(s, s, s, s) { }
      INLINE V4dg(const double v[4])                                                  : V4dt<V4dg>(v)          { }
      INLINE V4dg(double* const v)                                                    : V4dt<V4dg>(v)          { }
      INLINE V4dg(const int32_t v[4])                                                 : V4dt<V4dg>((double)v[0], (double)v[1], (double)v[2], (double)v[3]) { }
      INLINE V4dg(const float x, const float y, const float z, const float w)         : V4dt<V4dg>((double)x, (double)y, (double)z, (double)w)             { }
      INLINE V4dg(const int32_t x, const int32_t y, const int32_t z, const int32_t w) : V4dt<V4dg>((double)x, (double)y, (double)z, (double)w)             { }
   };

   /// <summary>
   /// 32-Bit Integer 4D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V4ig : public V4it<V4ig>
   {
   public:
      INLINE V4ig()                                                                                            { }
      INLINE V4ig(const int32_t x, const int32_t y, const int32_t z, const int32_t w) : V4it<V4ig>(x, y, z, w) { }
      INLINE V4ig(const int32_t s)                                                    : V4it<V4ig>(s, s, s, s) { }
      INLINE V4ig(const int32_t v[4])                                                 : V4it<V4ig>(v)          { }
      INLINE V4ig(int32_t* const v)                                                   : V4it<V4ig>(v)          { }
   };

   /// <summary>
   /// 64-Bit Integer 4D Vector (Generic, no SIMD) [L4]
   /// </summary>//------------------------------------------------------------------------------------------------------------------------//
   class V4lg : public V4lt<V4lg>
   {
   public:
      INLINE V4lg()                                                                                            { }
      INLINE V4lg(const int64_t x, const int64_t y, const int64_t z, const int64_t w) : V4lt<V4lg>(x, y, z, w) { }
      INLINE V4lg(const int64_t s)                                                    : V4lt<V4lg>(s, s, s, s) { }
      INLINE V4lg(const int64_t v[4])                                                 : V4lt<V4lg>(v)          { }
      INLINE V4lg(int64_t* const v)                                                   : V4lt<V4lg>(v)          { }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                             SIMD CLASSES [L4]                                                          //
   //------------------------------------------------------------------------------------------------------------------------//
#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Single Precision 4D Vector (SIMD)(TODO)
   /// </summary>
   class V4fs : public V4ft<V4fs> { };

   /// <summary>
   /// Double Precision 4D Vector (SIMD)(TODO)
   /// </summary>
   class V4ds : public V4dt<V4ds> { };

   /// <summary>
   /// 32-Bit Integer 4D Vector (SIMD)(TODO)
   /// </summary>
   class V4is : public V4it<V4is> { };

   /// <summary>
   /// 64-Bit Integer 4D Vector (SIMD)(TODO)
   /// </summary>
   class V4ls : public V4lt<V4ls> { };
#else
   typedef V4fg V4fs;
   typedef V4dg V4ds;
   typedef V4ig V4is;
   typedef V4lg V4ls;
#endif

   //------------------------------------------------------------------------------------------------------------------------//
   //------------------------------------------------------------------------------------------------------------------------//

#if defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_OPTIMIZED_VECTORMATH)
   // use optimized ones as defaults
   typedef V4fs V4f;
   typedef V4ds V4d;
   typedef V4is V4i;
   typedef V4ls V4l;
#else
   // use generic ones as defaults
   typedef V4fg V4f;
   typedef V4dg V4d;
   typedef V4ig V4i;
   typedef V4lg V4l;
#endif
}
#pragma warning(default:26495)
