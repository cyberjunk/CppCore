#pragma once
#pragma warning(disable:26495)

#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>

#if defined(CPPCORE_HAVE_OGRE3D)
#include <Ogre/OgreVector3.h>
#endif

namespace CppCore
{
   //------------------------------------------------------------------------------------------------------------------------//
   //                                          ROOT TEMPLATE [L1, ABSTRACT]                                                  //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 3D Vector Template for Floating Point (32/64) AND Integer (32/64). [L1]
   /// </summary>
   template <typename V, typename F>
   class V3
   {
   protected:
      INLINE V*   thiss() const { return ((V*)this); }

   public:
      union
      {
         struct { F x, y, z; };
         F vals[3];
      };
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V3()                                                            { }
      INLINE V3(const F x, const F y, const F z) : x(x),    y(y),    z(z)    { }
      INLINE V3(const F s)                       : x(s),    y(s),    z(s)    { }
      INLINE V3(const F v[3])                    : x(v[0]), y(v[1]), z(v[2]) { }
      //------------------------------------------------------------------------------------------------------------------------//
      static INLINE V ZERO()  { return V((F)0.0, (F)0.0, (F)0.0); }
      static INLINE V UNITX() { return V((F)1.0, (F)0.0, (F)0.0); }
      static INLINE V UNITY() { return V((F)0.0, (F)1.0, (F)0.0); }
      static INLINE V UNITZ() { return V((F)0.0, (F)0.0, (F)1.0); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void* operator new  (size_t size)          { return malloc(size); }
      INLINE void* operator new[](size_t size)          { return malloc(size); }
      INLINE F     operator []   (const size_t i) const { return vals[i];      }
      INLINE F     operator []   (const size_t i)       { return vals[i];      }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE bool  operator ==   (const V& v)     const { return ((x == v.x) & (y == v.y) & (z == v.z));  }
      INLINE bool  operator !=   (const V& v)     const { return ((x != v.x) | (y != v.y) | (z != v.z));  }
      INLINE bool  operator <    (const V& v)     const { return ((x <  v.x) & (y <  v.y) & (z <  v.z));  }
      INLINE bool  operator <=   (const V& v)     const { return ((x <= v.x) & (y <= v.y) & (z <= v.z));  }
      INLINE bool  operator >    (const V& v)     const { return ((x >  v.x) & (y >  v.y) & (z >  v.z));  }
      INLINE bool  operator >=   (const V& v)     const { return ((x >= v.x) & (y >= v.y) & (z >= v.z));  }
      INLINE V     operator +    (const V& v)     const { return V(x + v.x, y + v.y, z + v.z);            }
      INLINE V     operator -    (const V& v)     const { return V(x - v.x, y - v.y, z - v.z);            }
      INLINE V     operator *    (const V& v)     const { return V(x * v.x, y * v.y, z * v.z);            }
      INLINE V     operator /    (const V& v)     const { return V(x / v.x, y / v.y, z / v.z);            }
      INLINE V     operator +    (const F  s)     const { return V(x + s, y + s, z + s);                  }
      INLINE V     operator -    (const F  s)     const { return V(x - s, y - s, z - s);                  }
      INLINE V     operator *    (const F  s)     const { return V(x * s, y * s, z * s);                  }
      INLINE V     operator /    (const F  s)     const { return V(x / s, y / s, z / s);                  }
      INLINE V&    operator =    (const V& v)           { x = v.x;  y = v.y;  z =  v.z; return *thiss();  }
      INLINE V&    operator +=   (const V& v)           { x += v.x; y += v.y; z += v.z; return *thiss();  }
      INLINE V&    operator -=   (const V& v)           { x -= v.x; y -= v.y; z -= v.z; return *thiss();  }
      INLINE V&    operator *=   (const V& v)           { x *= v.x; y *= v.y; z *= v.z; return *thiss();  }
      INLINE V&    operator /=   (const V& v)           { x /= v.x; y /= v.y; z /= v.z; return *thiss();  }
      INLINE V&    operator =    (const F  s)           { x =  s;   y =  s; z =  s;     return *thiss();  }
      INLINE V&    operator +=   (const F  s)           { x += s;   y += s; z += s;     return *thiss();  }
      INLINE V&    operator -=   (const F  s)           { x -= s;   y -= s; z -= s;     return *thiss();  }
      INLINE V&    operator *=   (const F  s)           { x *= s;   y *= s; z *= s;     return *thiss();  }
      INLINE V&    operator /=   (const F  s)           { x /= s;   y /= s; z /= s;     return *thiss();  }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE       V  operator - ()               const { return V(-x, -y, -z); }
      INLINE const V& operator + ()               const { return *this; }
      //------------------------------------------------------------------------------------------------------------------------//
      template<typename T> INLINE T& ref()        const { return *((T*)this); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V&   point()                          const { return *thiss();                                                   }
      INLINE void madd(const V& m, const V& a)           { *thiss() = (*thiss() * m) + a;                                     }
      INLINE void msub(const V& m, const V& a)           { *thiss() = (*thiss() * m) - a;                                     }
      INLINE bool isZero()                         const { return x == (F)0.0 && y == (F)0.0 && z == (F)0.0;                  }
      INLINE bool isZero(const F e2)               const { return thiss()->length2() <= e2;                                   }
      INLINE bool equals(const V& v, const F e2)   const { return (thiss() - v).length2() <= e2;                              }
      INLINE void swap(V& v)                             { std::swap(x, v.x); std::swap(y, v.y); std::swap(z, v.z);           }
      INLINE V    cross(const V& v)                const { return V(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
      INLINE F    dot(const V& v)                  const { return x * v.x + y * v.y + z * v.z;                                }
      INLINE F    length2()                        const { return thiss()->dot(*((V*)this));                                  }
      INLINE F    length()                         const { return V::_sqrt(thiss()->length2());                               }
      INLINE F    distance2(const V& v)            const { return (*thiss() - v).length2();                                    }
      INLINE F    distance(const V& v)             const { return V::_sqrt(thiss()->distance2(v));                            }
      INLINE V    maxC(const V& v)                 const { return V(v.x > x ? v.x : x, v.y > y ? v.y : y, v.z > z ? v.z : z); }
      INLINE V    minC(const V& v)                 const { return V(v.x < x ? v.x : x, v.y < y ? v.y : y, v.z < z ? v.z : z); }
      INLINE V    boundC(const V& mi, const V& ma) const { V t(thiss()->minC(ma)); t.max(mi); return t;                       }
      INLINE V    absC()                           const { return V(V::_abs(x), V::_abs(y), V::_abs(z));                      }
      INLINE void max(const V& v)                        { if (v.x > x) x = v.x; if (v.y > y) y = v.y; if (v.z > z) z = v.z;  }
      INLINE void min(const V& v)                        { if (v.x < x) x = v.x; if (v.y < y) y = v.y; if (v.z < z) z = v.z;  }
      INLINE void bound(const V& mi, const V& ma)        { thiss()->min(ma); thiss()->max(mi);                                }
      INLINE void abs()                                  { x = V::_abs(x); y = V::_abs(y); z = V::_abs(z);                    }
      INLINE V    signs()                          const { return V((F)SIGN(x), (F)SIGN(y), (F)SIGN(z));                      }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V    xzy()                            const { return V(x, z, y); }
      INLINE void xzy()                                  { std::swap(y, z);   }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE bool inside(const V& min, const V& max)            const { return *thiss() >= min       && *thiss() <= max;       } // Box
      INLINE bool inside(const V& min, const V& max, const F e) const { return *thiss() >= (min - e) && *thiss() <= (max + e); } // Box
      INLINE bool inside(const V& m, const F r2)                const { return thiss()->distance2(m) <= r2;                    } // Sphere
      INLINE bool inside(const V& m, const F r2, const F e)     const { return thiss()->distance2(m) <= (r2 + e);              } // Sphere
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE::std::string toString() { return '('+::std::to_string(x)+'/'+::std::to_string(y)+'/'+::std::to_string(z)+')'; }
      //------------------------------------------------------------------------------------------------------------------------//
      template<typename PRNG>
      INLINE void randomize(PRNG& prng, const F min, const F max)
      { 
         x = prng.next(min, max);
         y = prng.next(min, max);
         z = prng.next(min, max);
      }
      template<typename PRNG>
      static INLINE V random(PRNG& prng, const F min, const F max) 
      {
         return V(prng.next(min, max), prng.next(min, max), prng.next(min, max));
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
   /// Abstract 3D Vector Template for Floating Point (32/64) [L2]
   /// </summary>
   template <typename V, typename F>
   class V3fdt : public V3<V, F>
   {
   protected:
      using V3<V, F>::thiss;

   public:
      using V3<V, F>::x;
      using V3<V, F>::y;
      using V3<V, F>::z;
      using V3<V, F>::vals;

   public:
      INLINE V3fdt()                                                    { }
      INLINE V3fdt(const F x, const F y, const F z) : V3<V, F>(x, y, z) { }
      INLINE V3fdt(const F s)                       : V3<V, F>(s)       { }
      INLINE V3fdt(const F v[3])                    : V3<V, F>(v)       { }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V& operator /= (const V& v)       { x /= v.x; y /= v.y; z /= v.z; return (V&)*this;              }
      INLINE V  operator /  (const V& v) const { return V(x / v.x, y / v.y, z / v.z);                         }
      INLINE V& operator /= (const F  s)       { F t = (F)1.0 / s; x *= t; y *= t; z *= t; return (V&)*this;  }
      INLINE V  operator /  (const F  s) const { F t = (F)1.0 / s; return V(x * t, y * t, z * t);             }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void  normalise()                                { *thiss() /= thiss()->length();                      }
      INLINE V     normaliseC()                         const { V t(*thiss()); t.normalise(); return t;             }
      INLINE void  scaleTo(const F l)                         { *thiss() *= (l / thiss()->length());                }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V     roundC()                             const { return V(V::_round(x), V::_round(y), V::_round(z));   }
      INLINE V     floorC()                             const { return V(V::_floor(x), V::_floor(y), V::_floor(z));   }
      INLINE V     ceilC()                              const { return V(V::_ceil(x),  V::_ceil(y),  V::_ceil(z));    }
      INLINE V     roundC(const F n)                    const { V c(*thiss()); c.round(n); return c;                  }
      INLINE void  round()                                    { x = V::_round(x); y = V::_round(y); z = V::_round(z); }
      INLINE void  floor()                                    { x = V::_floor(x); y = V::_floor(y); z = V::_floor(z); }
      INLINE void  ceil()                                     { x = V::_ceil(x);  y = V::_ceil(y);  z = V::_ceil(z);  }
      INLINE void  round(const F n)                           { *thiss() /= n; thiss()->round(); *thiss() *= n;       }
      //------------------------------------------------------------------------------------------------------------------------//
      static INLINE V    randomN()                            { V t(V::random()); t.normalise(); return t;             }
      static INLINE void randomN(V* v, const size_t size)     { for (size_t i = 0; i < size; i++) v[i] = V::randomN(); }
      //------------------------------------------------------------------------------------------------------------------------//
      static INLINE bool intersectLineTriangle(const V& s, const V& e, const V& p1, const V& p2, const V& p3, V& i, const bool raymode = false, const F eps = (F)0.001)
      {
         V e1, e2, p, q, t, d;
         F u, v, f, det;

         // vectors
         d  = e - s;      // line vector    S->E
         e1 = p2 - p1;    // triangle edge P1->P2
         e2 = p3 - p1;    // triangle edge P1->P3
         p = d.cross(e2); // used to calculate determinant and u,v parms

         // if determinant is near zero, ray lies in plane of triangle
         det = e1.dot(p);
         if (ISZERO(det, eps)) CPPCORE_UNLIKELY
            return false;

         // invert it for faster calc below
         // 1x DIV + 3x MUL instead of 3x DIV
         det = (F)1.0 / det;

         // calculate distance from P1 to line start
         t = s - p1;

         // calculate u parameter and test bound
         u = (t.dot(p)) * det;
         if ((u < (F)0.0) | (u > (F)1.0))
            return false;

         // prepare to test v parameter
         q = t.cross(e1);

         // calculate v parameter and test bound
         v = (d.dot(q)) * det;
         if ((v < (F)0.0) | (u + v > (F)1.0))
            return false;

         // line: additional check for < 1.0f
         f = (e2.dot(q)) * det;
         if ((f >= (F)0.0) && (raymode || f <= (F)1.0))
         {
            i = s + (d * f);
            return true;
         }

         return false;
      }
      template<typename TARR>
      static INLINE bool intersectLinePolygon(const V& s, const V& e, TARR& v, const size_t numPoints, V& i, const bool raymode = false, const F eps = (F)0.001)
      {
         // TODO: Optimize this. Currently it's just the triangle intersection
         // algorithm from above applied on each triangle of the convex polygon.

         // triangle is the smallest valid polygon
         if (numPoints >= 3)
         {
            const V  d  = e - s;
            const V& p1 = v[0];
            const V  t  = s - p1;
            for (size_t j = 0; j < numPoints - 2; j++)
            {
               const V& p2 = v[j+1];
               const V& p3 = v[j+2];

               V e1, e2, p, q;
               F u, v, f, det;

               // vectors
               e1 = p2 - p1;    // triangle edge P1->P2
               e2 = p3 - p1;    // triangle edge P1->P3
               p = d.cross(e2); // used to calculate determinant and u,v parms

               // if determinant is near zero, ray lies in plane of triangle
               det = e1.dot(p);
               if (ISZERO(det, eps)) CPPCORE_UNLIKELY
                  return false;

               // invert it for faster calc below
               // 1x DIV + 3x MUL instead of 3x DIV
               det = (F)1.0 / det;

               // calculate u parameter and test bound
               u = (t.dot(p)) * det;
               if ((u < (F)0.0) | (u > (F)1.0))
                  continue;

               // prepare to test v parameter
               q = t.cross(e1);

               // calculate v parameter and test bound
               v = (d.dot(q)) * det;
               if ((v < (F)0.0) | (u + v > (F)1.0))
                  continue;

               // line: additional check for < 1.0f
               f = (e2.dot(q)) * det;
               if ((f >= (F)0.0) & (raymode || f <= (F)1.0))
               {
                  i = s + (d * f);
                  return true;
               }
            }
         }
         return false;
      }
   };

   /// <summary>
   /// Abstract 3D Vector for Integer (32/64) [L2]
   /// </summary>
   template <typename V, typename F>
   class V3ilt : public V3<V, F>
   {
   protected:
      using V3<V, F>::thiss;

   public:
      using V3<V, F>::x;
      using V3<V, F>::y;
      using V3<V, F>::z;
      using V3<V, F>::vals;

   public:
      static INLINE F _abs(const F s)  { return std::abs(s);     }
      static INLINE F _sqrt(const F s) { return (F)std::sqrt(s); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V3ilt()                                                    { }
      INLINE V3ilt(const F x, const F y, const F z) : V3<V, F>(x, y, z) { }
      INLINE V3ilt(const F s)                       : V3<V, F>(s)       { }
      INLINE V3ilt(const F v[3])                    : V3<V, F>(v)       { }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                       32-BIT & 64-BIT TEMPLATES [L3, ABSTRACT]                                         //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 3D Vector Template for Single Precision FP [L3]
   /// </summary>
   template <typename V>
   class V3ft : public V3fdt<V, float>
   {
   public:
      static INLINE float _abs(const float s)   { return ::fabsf(s);  }
      static INLINE float _round(const float s) { return ::roundf(s); }
      static INLINE float _floor(const float s) { return ::floorf(s); }
      static INLINE float _ceil(const float s)  { return ::ceilf(s);  }
      static INLINE float _sqrt(const float s)  { return ::sqrtf(s);  }
      static INLINE float _cos(const float s)   { return ::cosf(s);   }
      static INLINE float _sin(const float s)   { return ::sinf(s);   }
      static INLINE float _acos(const float s)  { return ::acosf(s);  }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V3ft()                                                                                                         { }
      INLINE V3ft(const float x, const float y, const float z)       : V3fdt<V, float>(x, y, z)                             { }
      INLINE V3ft(const float s)                                     : V3fdt<V, float>(s)                                   { }
      INLINE V3ft(const float v[3])                                  : V3fdt<V, float>(v)                                   { }
      INLINE V3ft(const double x, const double y, const double z)    : V3fdt<V, float>((float)x, (float)y, (float)z)        { }
      INLINE V3ft(const double s)                                    : V3fdt<V, float>((float)s)                            { }
      INLINE V3ft(const double v[3])                                 : V3fdt<V, float>((float)v[0],(float)v[1],(float)v[2]) { }
      INLINE V3ft(const int32_t x, const int32_t y, const int32_t z) : V3fdt<V, float>((float)x, (float)y, (float)z)        { }
      INLINE V3ft(const int32_t s)                                   : V3fdt<V, float>((float)s)                            { }
      INLINE V3ft(const int32_t v[3])                                : V3fdt<V, float>((float)v[0],(float)v[1],(float)v[2]) { }
      INLINE V3ft(const int64_t x, const int64_t y, const int64_t z) : V3fdt<V, float>((float)x, (float)y, (float)z)        { }
      INLINE V3ft(const int64_t s)                                   : V3fdt<V, float>((float)s)                            { }
      INLINE V3ft(const int64_t v[3])                                : V3fdt<V, float>((float)v[0],(float)v[1],(float)v[2]) { }
      //------------------------------------------------------------------------------------------------------------------------//
   #if defined(CPPCORE_HAVE_OGRE3D) && (OGRE_DOUBLE_PRECISION == 0)
      INLINE operator Ogre::Vector3& () { return *(Ogre::Vector3*)this; }
   #endif
   };

   /// <summary>
   /// Abstract 3D Vector Template for Double Precision FP [L3]
   /// </summary>
   template <typename V>
   class V3dt : public V3fdt<V, double>
   {
   public:
      static INLINE double _abs(const double s)   { return std::abs(s); }
      static INLINE double _round(const double s) { return std::round(s); }
      static INLINE double _floor(const double s) { return std::floor(s); }
      static INLINE double _ceil(const double s)  { return std::ceil(s); }
      static INLINE double _sqrt(const double s)  { return std::sqrt(s); }
      static INLINE double _cos(const double s)   { return std::cos(s); }
      static INLINE double _sin(const double s)   { return std::sin(s); }
      static INLINE double _acos(const double s)  { return std::acos(s); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V3dt()                                                                                                              { }
      INLINE V3dt(const double x, const double y, const double z)    : V3fdt<V, double>(x, y, z)                                 { }
      INLINE V3dt(const double s)                                    : V3fdt<V, double>(s)                                       { }
      INLINE V3dt(const double v[3])                                 : V3fdt<V, double>(v)                                       { }
      INLINE V3dt(const float x, const float y, const float z)       : V3fdt<V, double>((double)x, (double)y, (double)z)         { }
      INLINE V3dt(const float s)                                     : V3fdt<V, double>((double)s)                               { }
      INLINE V3dt(const float v[3])                                  : V3fdt<V, double>((double)v[0],(double)v[1], (double)v[2]) { }
      INLINE V3dt(const int32_t x, const int32_t y, const int32_t z) : V3fdt<V, double>((double)x, (double)y, (double)z)         { }
      INLINE V3dt(const int32_t s)                                   : V3fdt<V, double>((double)s)                               { }
      INLINE V3dt(const int32_t v[3])                                : V3fdt<V, double>((double)v[0],(double)v[1], (double)v[2]) { }
      INLINE V3dt(const int64_t x, const int64_t y, const int64_t z) : V3fdt<V, double>((double)x, (double)y, (double)z)         { }
      INLINE V3dt(const int64_t s)                                   : V3fdt<V, double>((double)s)                               { }
      INLINE V3dt(const int64_t v[3])                                : V3fdt<V, double>((double)v[0],(double)v[1], (double)v[2]) { }
      //------------------------------------------------------------------------------------------------------------------------//
   #if defined(CPPCORE_HAVE_OGRE3D) && (OGRE_DOUBLE_PRECISION == 1)
      INLINE operator Ogre::Vector3& () { return *(Ogre::Vector3*)this; }
   #endif
   };

   /// <summary>
   /// Abstract 3D Vector Template for Integer (32) [L3]
   /// </summary>
   template <typename V>
   class V3it : public V3ilt<V, int32_t>
   {
   public:
      INLINE V3it()                                                                                                                 { }
      INLINE V3it(const int32_t x, const int32_t y, const int32_t z) : V3ilt<V, int32_t>(x, y, z)                                   { }
      INLINE V3it(const int32_t s)                                   : V3ilt<V, int32_t>(s)                                         { }
      INLINE V3it(const int32_t v[3])                                : V3ilt<V, int32_t>(v)                                         { }
      INLINE V3it(const float x, const float y, const float z)       : V3ilt<V, int32_t>((int32_t)x,(int32_t)y,(int32_t)z)          { }
      INLINE V3it(const float s)                                     : V3ilt<V, int32_t>((int32_t)s)                                { }
      INLINE V3it(const float v[3])                                  : V3ilt<V, int32_t>((int32_t)v[0],(int32_t)v[1],(int32_t)v[2]) { }
      INLINE V3it(const double x, const double y, const double z)    : V3ilt<V, int32_t>((int32_t)x,(int32_t)y,(int32_t)z)          { }
      INLINE V3it(const double s)                                    : V3ilt<V, int32_t>((int32_t)s)                                { }
      INLINE V3it(const double v[3])                                 : V3ilt<V, int32_t>((int32_t)v[0],(int32_t)v[1],(int32_t)v[2]) { }
      INLINE V3it(const int64_t x, const int64_t y, const int64_t z) : V3ilt<V, int32_t>((int32_t)x,(int32_t)y,(int32_t)z)          { }
      INLINE V3it(const int64_t s)                                   : V3ilt<V, int32_t>((int32_t)s)                                { }
      INLINE V3it(const int64_t v[3])                                : V3ilt<V, int32_t>((int32_t)v[0],(int32_t)v[1],(int32_t)v[2]) { }
   };

   /// <summary>
   /// Abstract 3D Vector Template for Integer (64) [L3]
   /// </summary>
   template <typename V>
   class V3lt : public V3ilt<V, int64_t>
   {
   public:
      INLINE V3lt()                                                                                                                 { }
      INLINE V3lt(const int64_t x, const int64_t y, const int64_t z) : V3ilt<V, int64_t>(x, y, z)                                   { }
      INLINE V3lt(const int64_t s)                                   : V3ilt<V, int64_t>(s)                                         { }
      INLINE V3lt(const int64_t v[3])                                : V3ilt<V, int64_t>(v)                                         { }
      INLINE V3lt(const float x, const float y, const float z)       : V3ilt<V, int64_t>((int64_t)x,(int64_t)y,(int64_t)z)          { }
      INLINE V3lt(const float s)                                     : V3ilt<V, int64_t>((int64_t)s)                                { }
      INLINE V3lt(const float v[3])                                  : V3ilt<V, int64_t>((int64_t)v[0],(int64_t)v[1],(int64_t)v[2]) { }
      INLINE V3lt(const double x, const double y, const double z)    : V3ilt<V, int64_t>((int64_t)x,(int64_t)y,(int64_t)z)          { }
      INLINE V3lt(const double s)                                    : V3ilt<V, int64_t>((int64_t)s)                                { }
      INLINE V3lt(const double v[3])                                 : V3ilt<V, int64_t>((int64_t)v[0],(int64_t)v[1],(int64_t)v[2]) { }
      INLINE V3lt(const int32_t x, const int32_t y, const int32_t z) : V3ilt<V, int64_t>((int64_t)x,(int64_t)y,(int64_t)z)          { }
      INLINE V3lt(const int32_t s)                                   : V3ilt<V, int64_t>((int64_t)s)                                { }
      INLINE V3lt(const int32_t v[3])                                : V3ilt<V, int64_t>((int64_t)v[0],(int64_t)v[1],(int64_t)v[2]) { }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                     GENERIC/NON-SIMD CLASSES [L4]                                                      //
   //------------------------------------------------------------------------------------------------------------------------//
   class V3fg;
   class V3dg;
   class V3ig;
   class V3lg;

   /// <summary>
   /// Single Precision 3D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V3fg : public V3ft<V3fg>
   {
   public:
      INLINE V3fg()                                                                                                 { }
      INLINE V3fg(const float x, const float y, const float z)       : V3ft<V3fg>(x, y, z)                          { }
      INLINE V3fg(const float s)                                     : V3ft<V3fg>(s)                                { }
      INLINE V3fg(const float v[3])                                  : V3ft<V3fg>(v)                                { }
      INLINE V3fg(const double x, const double y, const double z)    : V3ft<V3fg>(x, y, z)                          { }
      INLINE V3fg(const double s)                                    : V3ft<V3fg>(s)                                { }
      INLINE V3fg(const double v[3])                                 : V3ft<V3fg>(v)                                { }
      INLINE V3fg(const int32_t x, const int32_t y, const int32_t z) : V3ft<V3fg>(x, y, z)                          { }
      INLINE V3fg(const int32_t s)                                   : V3ft<V3fg>(s)                                { }
      INLINE V3fg(const int32_t v[3])                                : V3ft<V3fg>(v)                                { }
      INLINE V3fg(const int64_t x, const int64_t y, const int64_t z) : V3ft<V3fg>(x, y, z)                          { }
      INLINE V3fg(const int64_t s)                                   : V3ft<V3fg>(s)                                { }
      INLINE V3fg(const int64_t v[3])                                : V3ft<V3fg>(v)                                { }
      INLINE V3fg(const V3dt<V3dg>& v)                               : V3ft<V3fg>((float)v.x,(float)v.y,(float)v.z) { }
      INLINE V3fg(const V3it<V3ig>& v)                               : V3ft<V3fg>((float)v.x,(float)v.y,(float)v.z) { }
      INLINE V3fg(const V3lt<V3lg>& v)                               : V3ft<V3fg>((float)v.x,(float)v.y,(float)v.z) { }
   };

   /// <summary>
   /// Double Precision 3D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V3dg : public V3dt<V3dg>
   {
   public:
      INLINE V3dg()                                                                                                    { }
      INLINE V3dg(const double x, const double y, const double z)    : V3dt<V3dg>(x, y, z)                             { }
      INLINE V3dg(const double s)                                    : V3dt<V3dg>(s)                                   { }
      INLINE V3dg(const double v[3])                                 : V3dt<V3dg>(v)                                   { }
      INLINE V3dg(const float x, const float y, const float z)       : V3dt<V3dg>(x, y, z)                             { }
      INLINE V3dg(const float s)                                     : V3dt<V3dg>(s)                                   { }
      INLINE V3dg(const float v[3])                                  : V3dt<V3dg>(v)                                   { }
      INLINE V3dg(const int32_t x, const int32_t y, const int32_t z) : V3dt<V3dg>(x, y, z )                            { }
      INLINE V3dg(const int32_t s)                                   : V3dt<V3dg>(s)                                   { }
      INLINE V3dg(const int32_t v[3])                                : V3dt<V3dg>(v)                                   { }
      INLINE V3dg(const int64_t x, const int64_t y, const int64_t z) : V3dt<V3dg>(x, y, z)                             { }
      INLINE V3dg(const int64_t s)                                   : V3dt<V3dg>(s)                                   { }
      INLINE V3dg(const int64_t v[3])                                : V3dt<V3dg>(v)                                   { }
      INLINE V3dg(const V3ft<V3fg>& v)                               : V3dt<V3dg>((double)v.x,(double)v.y,(double)v.z) { }
      INLINE V3dg(const V3it<V3ig>& v)                               : V3dt<V3dg>((double)v.x,(double)v.y,(double)v.z) { }
      INLINE V3dg(const V3lt<V3lg>& v)                               : V3dt<V3dg>((double)v.x,(double)v.y,(double)v.z) { }
   };

   /// <summary>
   /// 32-Bit Integer 3D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V3ig : public V3it<V3ig>
   {
   public:
      INLINE V3ig()                                                                                                       { }
      INLINE V3ig(const int32_t x, const int32_t y, const int32_t z) : V3it<V3ig>(x, y, z)                                { }
      INLINE V3ig(const int32_t s)                                   : V3it<V3ig>(s)                                      { }
      INLINE V3ig(const int32_t v[3])                                : V3it<V3ig>(v)                                      { }
      INLINE V3ig(const float x, const float y, const float z)       : V3it<V3ig>(x, y, z)                                { }
      INLINE V3ig(const float s)                                     : V3it<V3ig>(s)                                      { }
      INLINE V3ig(const float v[3])                                  : V3it<V3ig>(v)                                      { }
      INLINE V3ig(const double x, const double y, const double z)    : V3it<V3ig>(x, y, z)                                { }
      INLINE V3ig(const double s)                                    : V3it<V3ig>(s)                                      { }
      INLINE V3ig(const double v[3])                                 : V3it<V3ig>(v)                                      { }
      INLINE V3ig(const int64_t x, const int64_t y, const int64_t z) : V3it<V3ig>(x, y, z)                                { }
      INLINE V3ig(const int64_t s)                                   : V3it<V3ig>(s)                                      { }
      INLINE V3ig(const int64_t v[3])                                : V3it<V3ig>(v)                                      { }
      INLINE V3ig(const V3ft<V3fg>& v)                               : V3it<V3ig>((int32_t)v.x,(int32_t)v.y,(int32_t)v.z) { }
      INLINE V3ig(const V3dt<V3dg>& v)                               : V3it<V3ig>((int32_t)v.x,(int32_t)v.y,(int32_t)v.z) { }
      INLINE V3ig(const V3lt<V3lg>& v)                               : V3it<V3ig>((int32_t)v.x,(int32_t)v.y,(int32_t)v.z) { }
   };

   /// <summary>
   /// 64-Bit Integer 3D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V3lg : public V3lt<V3lg>
   {
   public:
      INLINE V3lg()                                                                                                       { }
      INLINE V3lg(const int64_t x, const int64_t y, const int64_t z) : V3lt<V3lg>(x, y, z)                                { }
      INLINE V3lg(const int64_t s)                                   : V3lt<V3lg>(s)                                      { }
      INLINE V3lg(const int64_t v[3])                                : V3lt<V3lg>(v)                                      { }
      INLINE V3lg(const float x, const float y, const float z)       : V3lt<V3lg>(x, y, z)                                { }
      INLINE V3lg(const float s)                                     : V3lt<V3lg>(s)                                      { }
      INLINE V3lg(const float v[3])                                  : V3lt<V3lg>(v)                                      { }
      INLINE V3lg(const double x, const double y, const double z)    : V3lt<V3lg>(x, y, z)                                { }
      INLINE V3lg(const double s)                                    : V3lt<V3lg>(s)                                      { }
      INLINE V3lg(const double v[3])                                 : V3lt<V3lg>(v)                                      { }
      INLINE V3lg(const int32_t x, const int32_t y, const int32_t z) : V3lt<V3lg>(x, y, z)                                { }
      INLINE V3lg(const int32_t s)                                   : V3lt<V3lg>(s)                                      { }
      INLINE V3lg(const int32_t v[3])                                : V3lt<V3lg>(v)                                      { }
      INLINE V3lg(const V3ft<V3fg>& v)                               : V3lt<V3lg>((int64_t)v.x,(int64_t)v.y,(int64_t)v.z) { }
      INLINE V3lg(const V3dt<V3dg>& v)                               : V3lt<V3lg>((int64_t)v.x,(int64_t)v.y,(int64_t)v.z) { }
      INLINE V3lg(const V3it<V3ig>& v)                               : V3lt<V3lg>((int64_t)v.x,(int64_t)v.y,(int64_t)v.z) { }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                             SIMD CLASSES [L4]                                                          //
   //------------------------------------------------------------------------------------------------------------------------//
#if defined(CPPCORE_CPUFEAT_SSE2)
   /// <summary>
   /// Single Precision 3D Vector (SSE/SIMD)
   /// </summary>
   class V3fs : public V3ft<V3fs>
   {
   public:
      class Util
      {
      public:
         INLINE static __m128 cross(const __m128& a, const __m128& b)
         {
            const __m128 t1 = CppCore::permute128f<_MM_SHUFFLE(3, 0, 2, 1)>(a);
            const __m128 t2 = CppCore::permute128f<_MM_SHUFFLE(3, 1, 0, 2)>(b);
            const __m128 t3 = CppCore::permute128f<_MM_SHUFFLE(3, 0, 2, 1)>(_mm_mul_ps(t1, b));
            return CppCore::msub128f(t1, t2, t3);
         }
      };
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE __m128 load() const           { return CppCore::load96(vals); }
      INLINE void   store(const __m128& v) { return CppCore::store96(vals, v); }
      INLINE V3fs(const __m128& v)         { store(v); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V3fs()                                                  : V3ft<V3fs>() { }
      INLINE V3fs(const float x, const float y, const float z)       : V3ft<V3fs>(x, y, z)                          { }
      INLINE V3fs(const float s)                                     : V3ft<V3fs>(s)                                { }
      INLINE V3fs(const float v[3])                                  : V3ft<V3fs>(v)                                { }
      INLINE V3fs(const double x, const double y, const double z)    : V3ft<V3fs>(x, y, z)                          { }
      INLINE V3fs(const double s)                                    : V3ft<V3fs>(s)                                { }
      INLINE V3fs(const double v[3])                                 : V3ft<V3fs>(v)                                { }
      INLINE V3fs(const int32_t x, const int32_t y, const int32_t z) : V3ft<V3fs>(x, y, z)                          { }
      INLINE V3fs(const int32_t s)                                   : V3ft<V3fs>(s)                                { }
      INLINE V3fs(const int32_t v[3])                                : V3ft<V3fs>(v)                                { }
      INLINE V3fs(const int64_t x, const int64_t y, const int64_t z) : V3ft<V3fs>(x, y, z)                          { }
      INLINE V3fs(const int64_t s)                                   : V3ft<V3fs>(s)                                { }
      INLINE V3fs(const int64_t v[3])                                : V3ft<V3fs>(v)                                { }
      INLINE V3fs(const V3dt<V3dg>& v)                               : V3ft<V3fs>((float)v.x,(float)v.y,(float)v.z) { }
      INLINE V3fs(const V3it<V3ig>& v)                               : V3ft<V3fs>((float)v.x,(float)v.y,(float)v.z) { }
      INLINE V3fs(const V3lt<V3lg>& v)                               : V3ft<V3fs>((float)v.x,(float)v.y,(float)v.z) { }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE       bool  operator == (const V3fs& v) const { return _mm_movemask_ps(_mm_cmpeq_ps(load(), v.load())) == 0x0F; }
      INLINE       bool  operator != (const V3fs& v) const { return _mm_movemask_ps(_mm_cmpeq_ps(load(), v.load())) != 0x0F; }
      INLINE       bool  operator <  (const V3fs& v) const { return _mm_movemask_ps(_mm_cmplt_ps(load(), v.load())) == 0x07; }
      INLINE       bool  operator <= (const V3fs& v) const { return _mm_movemask_ps(_mm_cmple_ps(load(), v.load())) == 0x0F; }
      INLINE       bool  operator >  (const V3fs& v) const { return _mm_movemask_ps(_mm_cmpgt_ps(load(), v.load())) == 0x07; }
      INLINE       bool  operator >= (const V3fs& v) const { return _mm_movemask_ps(_mm_cmpge_ps(load(), v.load())) == 0x0F; }
      INLINE       V3fs  operator +  (const V3fs& v) const { return V3fs(_mm_add_ps(load(), v.load()));                  }
      INLINE       V3fs  operator -  (const V3fs& v) const { return V3fs(_mm_sub_ps(load(), v.load()));                  }
      INLINE       V3fs  operator *  (const V3fs& v) const { return V3fs(_mm_mul_ps(load(), v.load()));                  }
      INLINE       V3fs  operator /  (const V3fs& v) const { return V3fs(_mm_div_ps(load(), v.load()));                  }
      INLINE       V3fs  operator +  (const float s) const { return V3fs(_mm_add_ps(load(), _mm_set1_ps(s)));            }
      INLINE       V3fs  operator -  (const float s) const { return V3fs(_mm_sub_ps(load(), _mm_set1_ps(s)));            }
      INLINE       V3fs  operator *  (const float s) const { return V3fs(_mm_mul_ps(load(), _mm_set1_ps(s)));            }
      INLINE       V3fs  operator /  (const float s) const { return V3fs(_mm_div_ps(load(), _mm_set1_ps(s)));            }
      INLINE       V3fs  operator -  ()              const { return V3fs(_mm_sub_ps(_mm_setzero_ps(), load()));          }
      INLINE const V3fs& operator +  ()              const { return *this;                                               }
      INLINE       V3fs& operator += (const V3fs& v)       { store(_mm_add_ps(load(), v.load()));          return *this; }
      INLINE       V3fs& operator -= (const V3fs& v)       { store(_mm_sub_ps(load(), v.load()));          return *this; }
      INLINE       V3fs& operator *= (const V3fs& v)       { store(_mm_mul_ps(load(), v.load()));          return *this; }
      INLINE       V3fs& operator /= (const V3fs& v)       { store(_mm_div_ps(load(), v.load()));          return *this; }
      INLINE       V3fs& operator =  (const float s)       { store(_mm_set1_ps(s));                        return *this; }
      INLINE       V3fs& operator += (const float s)       { store(_mm_add_ps(load(), _mm_set1_ps(s)));    return *this; }
      INLINE       V3fs& operator -= (const float s)       { store(_mm_sub_ps(load(), _mm_set1_ps(s)));    return *this; }
      INLINE       V3fs& operator *= (const float s)       { store(_mm_mul_ps(load(), _mm_set1_ps(s)));    return *this; }
      INLINE       V3fs& operator /= (const float s)       { store(_mm_div_ps(load(), _mm_set1_ps(s)));    return *this; }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V3fs absC()                                 const { return V3fs(_mm_andnot_ps(_mm_set1_ps(-0.f), load()));       }
      INLINE V3fs maxC(const V3fs& v)                    const { return V3fs(_mm_max_ps(load(), v.load()));                   }
      INLINE V3fs minC(const V3fs& v)                    const { return V3fs(_mm_min_ps(load(), v.load()));                   }
      INLINE V3fs boundC(const V3fs& mi, const V3fs& ma) const { return V3fs(_mm_max_ps(_mm_min_ps(load(), ma.load()), mi.load())); }
      INLINE void abs()                                        { store(_mm_andnot_ps(_mm_set1_ps(-0.), load()));              }
      INLINE void max(const V3fs& v)                           { store(_mm_max_ps(load(), v.load()));                         }
      INLINE void min(const V3fs& v)                           { store(_mm_min_ps(load(), v.load()));                         }
      INLINE void bound(const V3fs& mi, const V3fs& ma)        { store(_mm_max_ps(_mm_min_ps(load(), ma.load()), mi.load())); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE bool isZero()                               const { return _mm_movemask_ps(_mm_cmpeq_ps(load(), _mm_setzero_ps())) == 0x0F; }
      INLINE bool isZero(const float e2)                 const { return thiss()->length2() <= e2;                             }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void madd(const V3fs& m, const V3fs& a)           { store(madd128f(load(), m.load(), a.load())); }
      INLINE void msub(const V3fs& m, const V3fs& s)           { store(msub128f(load(), m.load(), s.load())); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE float dot(const V3fs& v) const
      {
      #if defined(CPPCORE_CPUFEAT_SSE41)
         return _mm_cvtss_f32(_mm_dp_ps(load(), v.load(), 0x71));
      #else
         __m128 m, s;
         m = _mm_mul_ps(load(), v.load());
         s = permute128f<_MM_SHUFFLE(2, 3, 0, 1)>(m);
         m = _mm_add_ps(m, s);
         s = _mm_movehl_ps(s, m);
         return _mm_cvtss_f32(_mm_add_ss(m, s));
      #endif
      }
      INLINE V3fs cross(const V3fs& v) const
      {
         return V3fs(Util::cross(load(), v.load()));
      }
      INLINE float length() const
      {
      #if defined(CPPCORE_CPUFEAT_SSE41)
         const __m128& v = load();
         return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v,v, 0x71)));
      #else
         __m128 m, s;
         m = load();
         m = _mm_mul_ps(m, m);
         s = permute128f<_MM_SHUFFLE(2, 3, 0, 1)>(m);
         m = _mm_add_ps(m, s);
         s = _mm_movehl_ps(s, m);
         return _mm_cvtss_f32(_mm_sqrt_ss(_mm_add_ss(m, s)));
      #endif
      }
      INLINE bool inside(const V3fs& min, const V3fs& max) const
      {
         __m128 a(load());
         __m128 b(_mm_cmpge_ps(a, min.load()));
         __m128 c(_mm_cmple_ps(a, max.load()));
         __m128 d(_mm_and_ps(b, c));
         return _mm_movemask_ps(d) == 0x0F;
      }
      INLINE bool inside(const V3fs& min, const V3fs& max, const float e) const
      {
         __m128 eps(CppCore::broadcast128f(&e));
         __m128 a(load());
         __m128 b(_mm_cmpge_ps(a, _mm_sub_ps(min.load(), eps)));
         __m128 c(_mm_cmple_ps(a, _mm_add_ps(max.load(), eps)));
         __m128 d(_mm_and_ps(b, c));
         return _mm_movemask_ps(d) == 0x0F;
      }
   #if defined(CPPCORE_CPUFEAT_SSE41)
      INLINE void round()        { store(_mm_round_ps(load(), _MM_FROUND_NINT));        }
      INLINE void floor()        { store(_mm_round_ps(load(), _MM_FROUND_FLOOR));       }
      INLINE void ceil()         { store(_mm_round_ps(load(), _MM_FROUND_CEIL));        }
      INLINE void round(const float n)
      {
         const __m128 t1(broadcast128f(&n));
         store(_mm_mul_ps(_mm_round_ps(_mm_div_ps(load(), t1), _MM_FROUND_NINT), t1));
      }
      INLINE void normalise()
      {
         const __m128 v = load();
         store(_mm_div_ps(v, _mm_sqrt_ps(_mm_dp_ps(v, v, 0x7F))));
      }
      static INLINE bool intersectLineTriangle(const V3fs& s, const V3fs& e, const V3fs& p1, const V3fs& p2, const V3fs& p3, V3fs& i, const bool raymode = false, const float eps = 0.001f)
      {
         static constexpr uint32_t const SIGN = 0x7FFFFFFF;
         static constexpr float    const ONE  = 1.0f;

         const __m128 sse_s  = _mm_loadu_ps(&s.x);
         const __m128 sse_e  = _mm_loadu_ps(&e.x);
         const __m128 sse_p1 = _mm_loadu_ps(&p1.x);
         const __m128 sse_p2 = _mm_loadu_ps(&p2.x);
         const __m128 sse_p3 = _mm_loadu_ps(&p3.x);

         __m128  e1, e2, d, p, det, t, q, uvf, dp1, dp2, dp3, rlt, rgt;
         uint32_t dz, mlt, mgt;

         e1  = _mm_sub_ps(sse_p2, sse_p1); // triangle edge P1->P2
         e2  = _mm_sub_ps(sse_p3, sse_p1); // triangle edge P1->P3
         d   = _mm_sub_ps(sse_e, sse_s);   // line vector    S->E
         t   = _mm_sub_ps(sse_s, sse_p1);
         p   = V3fs::Util::cross(d, e2);
         q   = V3fs::Util::cross(t, e1);
         det = _mm_dp_ps(e1, p, 0x7F);
         dp1 = _mm_dp_ps(t, p, 0x71);
         dp2 = _mm_dp_ps(d, q, 0x71);
         dp3 = _mm_dp_ps(e2, q, 0x71);
         uvf = _mm_unpacklo_ps(dp1, dp2);
         uvf = _mm_movelh_ps(uvf, dp3);
         uvf = _mm_div_ps(uvf, det);
         rlt = _mm_cmplt_ps(uvf, _mm_setzero_ps());               // uvf < 0
         uvf = _mm_add_ss(uvf, _mm_movehdup_ps(uvf));             // u = u+v
         rgt = _mm_cmplt_ps(CppCore::broadcast128f(&ONE), uvf);   // 1 < uvf
         dz  = _mm_comilt_ss(_mm_and_ps(_mm_load_ss((float*)&SIGN), det), _mm_load_ss(&eps));
         //dz  = _mm_comieq_ss(det, _mm_setzero_ps()); // this works for current tests and would be faster
         mlt = _mm_movemask_ps(rlt);
         mgt = _mm_movemask_ps(rgt);
         mgt = raymode ? mgt & 0x03U : mgt;
         i.store(CppCore::madd128f(d, permute128f<_MM_SHUFFLE(2, 2, 2, 2)>(uvf), sse_s));
         return (dz | mlt | mgt) == 0U;
      }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
   };

   /// <summary>
   /// Double Precision 3D Vector (SSE/SIMD) [NOT IMPLEMENTED]
   /// </summary>
   typedef V3dg V3ds;

   /// <summary>
   /// 32-Bit Integer 3D Vector (SSE/SIMD) [NOT IMPLEMENTED]
   /// </summary>
   typedef V3ig V3is;

   /// <summary>
   /// 64-Bit Integer 3D Vector (SSE/SIMD) [NOT IMPLEMENTED]
   /// </summary>
   typedef V3lg V3ls;
#else
   typedef V3fg V3fs;
   typedef V3dg V3ds;
   typedef V3ig V3is;
   typedef V3lg V3ls;
#endif

#if defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_OPTIMIZED_VECTORMATH)
   // use optimized ones as defaults
   typedef V3fs V3f;
   typedef V3ds V3d;
   typedef V3is V3i;
   typedef V3ls V3l;
#else
   // use generic ones as defaults
   typedef V3fg V3f;
   typedef V3dg V3d;
   typedef V3ig V3i;
   typedef V3lg V3l;
#endif
}
#pragma warning(default:26495)
