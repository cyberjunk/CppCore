#pragma once
#pragma warning(disable:26495)

#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>

namespace CppCore
{
   //------------------------------------------------------------------------------------------------------------------------//
   //                                          ROOT TEMPLATE V2 [L1, ABSTRACT]                                               //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 2D Vector Template for Floating Point (32/64) AND Integer (32/64). [L1]
   /// </summary>
   template <typename V, typename F>
   class V2
   {
   protected:
      INLINE V*   thiss() const { return (V*)this; }

   public:
      union
      {
         struct { F x, y; };
         F vals[2];
      };
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V2()                                                  { }
      INLINE V2(const F x, const F y) : x(x),         y(y)         { }
      INLINE V2(const F scalar)       : x(scalar),    y(scalar)    { }
      INLINE V2(const F values[2])    : x(values[0]), y(values[1]) { }
      //------------------------------------------------------------------------------------------------------------------------//
      static INLINE V ZERO()  { return V((F)0.0, (F)0.0); }
      static INLINE V UNITX() { return V((F)1.0, (F)0.0); }
      static INLINE V UNITY() { return V((F)0.0, (F)1.0); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void* operator new  (size_t size)          { return ::malloc(size); }
      INLINE void* operator new[](size_t size)          { return ::malloc(size); }
      INLINE void  operator delete   (void* ptr)        { return ::free(ptr);    }
      INLINE void  operator delete[] (void* ptr)        { return ::free(ptr);    }
      INLINE F     operator []   (const size_t i) const { return vals[i];        }
      INLINE F     operator []   (const size_t i)       { return vals[i];        }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE bool  operator ==   (const V& v)     const { return ((x == v.x) & (y == v.y));     }
      INLINE bool  operator !=   (const V& v)     const { return ((x != v.x) | (y != v.y));     }
      INLINE bool  operator <    (const V& v)     const { return ((x <  v.x) & (y <  v.y));     }
      INLINE bool  operator <=   (const V& v)     const { return ((x <= v.x) & (y <= v.y));     }
      INLINE bool  operator >    (const V& v)     const { return ((x >  v.x) & (y >  v.y));     }
      INLINE bool  operator >=   (const V& v)     const { return ((x >= v.x) & (y >= v.y));     }
      INLINE V     operator +    (const V& v)     const { return V(x + v.x, y + v.y);           }
      INLINE V     operator -    (const V& v)     const { return V(x - v.x, y - v.y);           }
      INLINE V     operator *    (const V& v)     const { return V(x * v.x, y * v.y);           }
      INLINE V     operator /    (const V& v)     const { return V(x / v.x, y / v.y);           }
      INLINE V     operator +    (const F  s)     const { return V(x + s,   y + s);             }
      INLINE V     operator -    (const F  s)     const { return V(x - s,   y - s);             }
      INLINE V     operator *    (const F  s)     const { return V(x * s,   y * s);             }
      INLINE V     operator /    (const F  s)     const { return V(x / s,   y / s);             }
      INLINE V&    operator =    (const V& v)           { x =  v.x; y =  v.y; return *thiss();  }
      INLINE V&    operator +=   (const V& v)           { x += v.x; y += v.y; return *thiss();  }
      INLINE V&    operator -=   (const V& v)           { x -= v.x; y -= v.y; return *thiss();  }
      INLINE V&    operator *=   (const V& v)           { x *= v.x; y *= v.y; return *thiss();  }
      INLINE V&    operator /=   (const V& v)           { x /= v.x; y /= v.y; return *thiss();  }
      INLINE V&    operator =    (const F  s)           { x =  s;   y =  s;   return *thiss();  }
      INLINE V&    operator +=   (const F  s)           { x += s;   y += s;   return *thiss();  }
      INLINE V&    operator -=   (const F  s)           { x -= s;   y -= s;   return *thiss();  }
      INLINE V&    operator *=   (const F  s)           { x *= s;   y *= s;   return *thiss();  }
      INLINE V&    operator /=   (const F  s)           { x /= s;   y /= s;   return *thiss();  }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE       V  operator - ()               const { return V(-x, -y);      }
      INLINE const V& operator + ()               const { return *this;          }
      //------------------------------------------------------------------------------------------------------------------------//
      template<typename T> INLINE T& ref()        const { return *((T*)this); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V&   point()                          const { return *thiss();                                }
      INLINE void madd(const V& m, const V& a)           { *thiss() = (*thiss() * m) + a;                  }
      INLINE void msub(const V& m, const V& s)           { *thiss() = (*thiss() * m) - s;                  }
      INLINE bool isZero()                         const { return x == (F)0.0 && y == (F)0.0;              }
      INLINE bool isZero(const F e2)               const { return thiss()->length2() <= e2;                }
      INLINE bool equals(const V& v, const F e2)   const { return (*thiss() - v).length2() <= e2;          }
      INLINE void swap(V& v)                             { V t(v); v=*thiss(); *thiss()=t;                 }
      INLINE F    cross(const V& v)                const { return x * v.y - y * v.x;                       }
      INLINE F    dot(const V& v)                  const { return x * v.x + y * v.y;                       }
      INLINE F    length2()                        const { return thiss()->dot(*thiss());                  }
      INLINE F    length()                         const { return V::_sqrt(thiss()->length2());            }
      INLINE F    distance2(const V& v)            const { return (*thiss() - v).length2();                }
      INLINE F    distance(const V& v)             const { return V::_sqrt(thiss()->distance2(v));         }
      INLINE V    yx()                             const { return V(y, x);                                 }
      INLINE void yx()                                   { std::swap(x, y);                                }
      INLINE V    maxC(const V& v)                 const { return V(v.x > x ? v.x : x, v.y > y ? v.y : y); }
      INLINE V    minC(const V& v)                 const { return V(v.x < x ? v.x : x, v.y < y ? v.y : y); }
      INLINE V    boundC(const V& mi, const V& ma) const { V t(thiss()->minC(ma)); t.max(mi); return t;    }
      INLINE V    absC()                           const { return V(V::_abs(x), V::_abs(y));               }
      INLINE void max(const V& v)                        { if (v.x > x) x = v.x; if (v.y > y) y = v.y;     }
      INLINE void min(const V& v)                        { if (v.x < x) x = v.x; if (v.y < y) y = v.y;     }
      INLINE void bound(const V& mi, const V& ma)        { thiss()->min(ma); thiss()->max(mi);             }
      INLINE void abs()                                  { x = V::_abs(x); y = V::_abs(y);                 }
      INLINE V    perp1()                          const { return V(y, -x);                                }
      INLINE V    perp2()                          const { return V(-y, x);                                }
      INLINE V    signs()                          const { return V((F)SIGN(x), (F)SIGN(y));               }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE F    side(const V& s, const V& e)                  const { return (e - s).cross(*thiss() - s);                    }
      INLINE bool inside(const V& min, const V& max)            const { return *thiss() >= min       && *thiss() <= max;       } // Box
      INLINE bool inside(const V& min, const V& max, const F e) const { return *thiss() >= (min - e) && *thiss() <= (max + e); } // Box
      INLINE bool inside(const V& m, const F r2)                const { return thiss()->distance2(m) <= r2;                    } // Circle
      INLINE bool inside(const V& m, const F r2, const F e)     const { return thiss()->distance2(m) <= (r2 + e);              } // Circle
      INLINE F    area(const V& p)                              const { V t(p-*thiss()); t.abs(); return t.x*t.y;              } // Box
      INLINE F    area(const V& p, const V& q)                  const { return (p-*thiss()).cross(q-*thiss()) / (F)2;          } // Triangle
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE::std::string toString()                      { return '(' + ::std::to_string(x) + '/' + ::std::to_string(y) + ')';}
      //------------------------------------------------------------------------------------------------------------------------//
      template<typename PRNG>
      INLINE void randomize(PRNG& prng, const F min, const F max)
      { 
         x = prng.next(min, max);
         y = prng.next(min, max);
      }
      template<typename PRNG>
      static INLINE V random(PRNG& prng, const F min, const F max) 
      {
         return V(prng.next(min, max), prng.next(min, max));
      }
      template<typename PRNG>
      static INLINE void random(PRNG& prng, const F min, const F max, V* v, const size_t size)  
      {
         for (size_t i = 0; i < size; i++) 
            v[i].randomize(prng, min, max);
      }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                 FLOATING POINT & INTEGER TEMPLATES [L2, ABSTRACT]                                      //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 2D Vector Template for Floating Point (32/64) [L2]
   /// </summary>
   template <typename V, typename F>
   class V2fdt : public V2<V, F>
   {
   protected:
      using V2<V, F>::thiss;

   public:
      using V2<V, F>::x;
      using V2<V, F>::y;
      using V2<V, F>::vals;

   public:
      INLINE V2fdt()                                        { }
      INLINE V2fdt(const F x, const F y) : V2<V, F>(x, y)   { }
      INLINE V2fdt(const F scalar)       : V2<V, F>(scalar) { }
      INLINE V2fdt(const F values[2])    : V2<V, F>(values) { }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V& operator /= (const V& v)       { x /= v.x; y /= v.y; return (V&)*this;               }
      INLINE V  operator /  (const V& v) const { return V(x / v.x, y / v.y);                         }
      INLINE V& operator /= (const F  s)       { F t = (F)1.0 / s; x *= t; y *= t; return (V&)*this; }
      INLINE V  operator /  (const F  s) const { F t = (F)1.0 / s; return V(x * t, y * t);           }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void  normalise()                                { *thiss() /= thiss()->length();          }
      INLINE V     normaliseC()                         const { V t(*thiss()); t.normalise(); return t; }
      INLINE void  scaleTo(const F l)                         { *thiss() *= (l / thiss()->length());    }
      INLINE V     scaleToC(const F l)                  const { V t(*thiss()); t.scaleTo(l); return t;  }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V     roundC()                             const { return V(V::_round(x), V::_round(y));           }
      INLINE V     floorC()                             const { return V(V::_floor(x), V::_floor(y));           }
      INLINE V     ceilC()                              const { return V(V::_ceil(x),  V::_ceil(y));            }
      INLINE V     roundC(const F n)                    const { V c(*thiss()); c.round(n); return c;          }
      INLINE V     ceilPow2C()                          const { V c(*thiss()); c.ceilPow2(); return c;          }
      INLINE void  round()                                    { x = V::_round(x); y = V::_round(y);             }
      INLINE void  floor()                                    { x = V::_floor(x); y = V::_floor(y);             }
      INLINE void  ceil()                                     { x = V::_ceil(x);  y = V::_ceil(y);              }
      INLINE void  round(const F n)                           { *thiss() /= n; thiss()->round(); *thiss() *= n; }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void  ceilPow2()  { thiss()->ceil();  x = (F)ngptwo32((uint32_t)x); y = (F)ngptwo32((uint32_t)y); }
      INLINE void  floorPow2() { thiss()->floor(); x = (F)nlptwo32((uint32_t)x); y = (F)nlptwo32((uint32_t)y); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE F angle()              const { return V::_acos(x / thiss()->length());                                       }
      INLINE F angleNoN()           const { return V::_acos(x);                                                           }
      INLINE F angleOri()           const { F t = thiss()->angle();    if (y < (F)0.0) t = (F)TWOPI - t; return t;        }
      INLINE F angleOriNoN()        const { F t = thiss()->angleNoN(); if (y < (F)0.0) t = (F)TWOPI - t; return t;        }
      INLINE F angle(const V& v)    const { F lp = thiss()->length() * v.length(); return V::_acos(thiss()->dot(v) / lp); }
      INLINE F angleOri(const V& v) const { F t = thiss()->angle(v); if (thiss()->cross(v) < (F)0.0) t = (F)TWOPI - t; return t;   }
      //------------------------------------------------------------------------------------------------------------------------//
      //INLINE F area(const V& p, const V& q) const { return (F)0.5 * (p - *thiss()).cross(q - *thiss()); } // Triangle
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void rotate(F r)
      {
         F cs = V::_cos(r);
         F sn = V::_sin(r);
         F p = x;
         x = p * cs - y * sn;
         y = p * sn + y * cs;
      }
      INLINE V project(const V& v) const
      {
         const F denom = v.length2();
         if (denom > 0.0f)
         {
            const F num = thiss()->dot(v);
            return v * (num / denom);
         }
         else
            return V::ZERO();
      }
      INLINE bool intersectCircleLineInternal(const V& s, const V& e, const F r, const F eps, V& d, F& t1, F& t2) const
      {
         d = e - s;
         V f = s - *thiss();

         const F a = d.length2();
         const F b = (F)2.0 * f.dot(d);
         const F c = f.length2() - (r*r);
         const F div = (F)2.0 * a;
         const F discriminant = b * b - (F)4.0 * a * c;

         if (discriminant < (F)0.0 || ISZERO(div, eps))
            return false;

         const F sqrt = V::_sqrt(discriminant);
         t1 = (-b - sqrt) / div;
         t2 = (-b + sqrt) / div;
         return true;
      }
      INLINE bool intersectCircleLine(const V& s, const V& e, const F r, const F eps, const bool withinside) const
      {
         V d;
         F t1, t2;

         if (!intersectCircleLineInternal(s, e, r, eps, d, t1, t2))
            return false;

         return
            (t1 >= (F)0.0 && t1 <= (F)1.0) ||             // intersect
            (t2 >= (F)0.0 && t2 <= (F)1.0) ||             // intersect
            (withinside && t1 <= (F)0.0 && t2 >= (F)1.0); // inside
      }
      INLINE bool intersectCircleLine(const V& s, const V& e, const F r, const F eps, const bool withinside, V& p) const
      {
         V d;
         F t1, t2;

         if (!intersectCircleLineInternal(s, e, r, eps, d, t1, t2))
            return false;

         if (t1 >= (F)0.0 && t1 <= (F)1.0) // intersect
         {
            p = s + (d * t1);
            return true;
         }
         else if (t2 >= (F)0.0 && t2 <= (F)1.0) // intersect
         {
            p = s + (d * t2);
            return true;
         }
         else if (withinside && t1 <= (F)0.0 && t2 >= (F)1.0) // inside
         {
            p = (F)0.0;
            return true;
         }
         else // outside
         {
            p = (F)0.0;
            return false;
         }
      }
      INLINE F minSquaredDistanceToFiniteLine(const V& p1, const V& p2, size_t& closest) const
      {
         // from p1 to p2
         V diff = p2 - p1;

         // squared length
         const F l2  = diff.length2();

         // p1=p2, both closest
         if (l2 == (F)0.0)
         {
            closest = 1; 
            return thiss()->distance2(p1);
         }

         const F t = ((*thiss() - p1).dot(diff)) / l2;

         // p1 is closest
         if (t < (F)0.0)
         {
            closest = 1;
            return thiss()->distance2(p1);
         }

         // p2 is closest
         else if (t > (F)1.0)
         {
            closest = 2;
            return thiss()->distance2(p2);
         }

         // point on line is closest
         else
         {
            closest = 3;
            diff *= t;
            return thiss()->distance2(p1 + diff);
         }
      }
      static INLINE bool insideFrustum(const V& p, const V& vp, const F vangle, const F width)
      {
         // from vp to p
         const V se = p - vp;

         // center
         V c(V::_cos(vangle), V::_sin(vangle));

         // behind
         if (c.dot(se) < (F)0.0)
            return false;

         // offset
         const V o = c * width;

         // first left than right
         V v;

         // too left
         v.x = -c.y;
         v.y =  c.x;
         v += o;
         if (v.dot(se) < (F)0.0)
            return false;

         // too right
         v.x =  c.y;
         v.y = -c.x;
         v += o;
         if (v.dot(se) < (F)0.0)
            return false;

         // ok
         return true;
      }
      //------------------------------------------------------------------------------------------------------------------------//
      static INLINE V    randomN()                        { V t(V::random()); t.normalise(); return t;             }
      static INLINE void randomN(V* v, const size_t size) { for (size_t i = 0; i < size; i++) v[i] = V::randomN(); }
      static INLINE V    fromAngle(const F rad)           { V t(V::UNITX()); t.rotate(rad); return t;                 }
      //------------------------------------------------------------------------------------------------------------------------//
   };

   /// <summary>
   /// Abstract 2D Vector for Integer (32/64) [L2]
   /// </summary>
   template <typename V, typename F>
   class V2ilt : public V2<V, F>
   {
   protected:
      using V2<V, F>::thiss;

   public:
      using V2<V, F>::x;
      using V2<V, F>::y;
      using V2<V, F>::vals;

   public:
      static INLINE F _abs(const F s)  { return std::abs(s);       }
      static INLINE F _sqrt(const F s) { return (F)std::sqrt(s);   }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V2ilt()                                      { }
      INLINE V2ilt(const F x, const F y) : V2<V, F>(x, y) { }
      INLINE V2ilt(const F s)            : V2<V, F>(s)    { }
      INLINE V2ilt(const F v[2])         : V2<V, F>(v)    { }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                       32-BIT & 64-BIT TEMPLATES [L3, ABSTRACT]                                         //
   //------------------------------------------------------------------------------------------------------------------------//
   /// <summary>
   /// Abstract 2D Vector Template for Single Precision FP [L3]
   /// </summary>
   template <typename V>
   class V2ft : public V2fdt<V, float>
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
      INLINE V2ft() { }
      INLINE V2ft(const float x, const float y)     : V2fdt<V, float>(x, y)                     { }
      INLINE V2ft(const float s)                    : V2fdt<V, float>(s)                        { }
      INLINE V2ft(const float v[2])                 : V2fdt<V, float>(v)                        { }
      INLINE V2ft(const double x, const double y)   : V2fdt<V, float>((float)x,    (float)y)    { }
      INLINE V2ft(const double s)                   : V2fdt<V, float>((float)s)                 { }
      INLINE V2ft(const double v[2])                : V2fdt<V, float>((float)v[0], (float)v[1]) { }
      INLINE V2ft(const int32_t x, const int32_t y) : V2fdt<V, float>((float)x,    (float)y)    { }
      INLINE V2ft(const int32_t s)                  : V2fdt<V, float>((float)s)                 { }
      INLINE V2ft(const int32_t v[2])               : V2fdt<V, float>((float)v[0], (float)v[1]) { }
      INLINE V2ft(const int64_t x, const int64_t y) : V2fdt<V, float>((float)x,    (float)y)    { }
      INLINE V2ft(const int64_t s)                  : V2fdt<V, float>((float)s)                 { }
      INLINE V2ft(const int64_t v[2])               : V2fdt<V, float>((float)v[0], (float)v[1]) { }
   };

   /// <summary>
   /// Abstract 2D Vector Template for Double Precision FP [L3]
   /// </summary>
   template <typename V>
   class V2dt : public V2fdt<V, double>
   {
   public:
      static INLINE double _abs(const double s)   { return std::abs(s);   }
      static INLINE double _round(const double s) { return std::round(s); }
      static INLINE double _floor(const double s) { return std::floor(s); }
      static INLINE double _ceil(const double s)  { return std::ceil(s);  }
      static INLINE double _sqrt(const double s)  { return std::sqrt(s);  }
      static INLINE double _cos(const double s)   { return std::cos(s);   }
      static INLINE double _sin(const double s)   { return std::sin(s);   }
      static INLINE double _acos(const double s)  { return std::acos(s);  }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V2dt()                                                                                { }
      INLINE V2dt(const double x, const double y)   : V2fdt<V, double>(x, y)                       { }
      INLINE V2dt(const double s)                   : V2fdt<V, double>(s)                          { }
      INLINE V2dt(const double v[2])                : V2fdt<V, double>(v)                          { }
      INLINE V2dt(const float x, const float y)     : V2fdt<V, double>((double)x,    (double)y)    { }
      INLINE V2dt(const float s)                    : V2fdt<V, double>((double)s)                  { }
      INLINE V2dt(const float v[2])                 : V2fdt<V, double>((double)v[0], (double)v[1]) { }
      INLINE V2dt(const int32_t x, const int32_t y) : V2fdt<V, double>((double)x,    (double)y)    { }
      INLINE V2dt(const int32_t s)                  : V2fdt<V, double>((double)s)                  { }
      INLINE V2dt(const int32_t v[2])               : V2fdt<V, double>((double)v[0], (double)v[1]) { }
      INLINE V2dt(const int64_t x, const int64_t y) : V2fdt<V, double>((double)x,    (double)y)    { }
      INLINE V2dt(const int64_t s)                  : V2fdt<V, double>((double)s)                  { }
      INLINE V2dt(const int64_t v[2])               : V2fdt<V, double>((double)v[0], (double)v[1]) { }
   };

   /// <summary>
   /// Abstract 2D Vector Template for Integer (32) [L3]
   /// </summary>
   template <typename V>
   class V2it : public V2ilt<V, int32_t>
   {
   public:
      INLINE V2it()                                                           { }
      INLINE V2it(const int32_t x, const int32_t y) : V2ilt<V, int32_t>(x, y) { }
      INLINE V2it(const int32_t s)                  : V2ilt<V, int32_t>(s)    { }
      INLINE V2it(const int32_t v[2])               : V2ilt<V, int32_t>(v)    { }
      INLINE V2it(const float x, const float y)     : V2ilt<V, int32_t>((int32_t)x,(int32_t)y)       { }
      INLINE V2it(const float s)                    : V2ilt<V, int32_t>((int32_t)s)                  { }
      INLINE V2it(const float v[2])                 : V2ilt<V, int32_t>((int32_t)v[0],(int32_t)v[1]) { }
      INLINE V2it(const double x, const double y)   : V2ilt<V, int32_t>((int32_t)x,(int32_t)y)       { }
      INLINE V2it(const double s)                   : V2ilt<V, int32_t>((int32_t)s)                  { }
      INLINE V2it(const double v[2])                : V2ilt<V, int32_t>((int32_t)v[0], (int32_t)v[1]){ }
      INLINE V2it(const int64_t x, const int64_t y) : V2ilt<V, int32_t>((int32_t)x,(int32_t)y)       { }
      INLINE V2it(const int64_t s)                  : V2ilt<V, int32_t>((int32_t)s)                  { }
      INLINE V2it(const int64_t v[2])               : V2ilt<V, int32_t>((int32_t)v[0],(int32_t)v[1]) { }
   };

   /// <summary>
   /// Abstract 2D Vector Template for Integer (64) [L3]
   /// </summary>
   template <typename V>
   class V2lt : public V2ilt<V, int64_t>
   {
   public:
      INLINE V2lt()                                                           { }
      INLINE V2lt(const int64_t x, const int64_t y) : V2ilt<V, int64_t>(x, y) { }
      INLINE V2lt(const int64_t s)                  : V2ilt<V, int64_t>(s)    { }
      INLINE V2lt(const int64_t v[2])               : V2ilt<V, int64_t>(v)    { }
      INLINE V2lt(const float x, const float y)     : V2ilt<V, int64_t>((int64_t)x, (int64_t)y)      { }
      INLINE V2lt(const float s)                    : V2ilt<V, int64_t>((int64_t)s)                  { }
      INLINE V2lt(const float v[2])                 : V2ilt<V, int64_t>((int64_t)v[0],(int64_t)v[1]) { }
      INLINE V2lt(const double x, const double y)   : V2ilt<V, int64_t>((int64_t)x,(int64_t)y)       { }
      INLINE V2lt(const double s)                   : V2ilt<V, int64_t>((int64_t)s)                  { }
      INLINE V2lt(const double v[2])                : V2ilt<V, int64_t>((int64_t)v[0],(int64_t)v[1]) { }
      INLINE V2lt(const int32_t x, const int32_t y) : V2ilt<V, int64_t>((int64_t)x,(int64_t)y)       { }
      INLINE V2lt(const int32_t s)                  : V2ilt<V, int64_t>((int64_t)s)                  { }
      INLINE V2lt(const int32_t v[2])               : V2ilt<V, int64_t>((int64_t)v[0],(int64_t)v[1]) { }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                     GENERIC/NON-SIMD CLASSES [L4]                                                      //
   //------------------------------------------------------------------------------------------------------------------------//
   class V2fg;
   class V2dg;
   class V2ig;
   class V2lg;

   /// <summary>
   /// Single Precision 2D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V2fg : public V2ft<V2fg>
   {
   public:
      INLINE V2fg()                                                    { }
      INLINE V2fg(const float x, const float y)     : V2ft<V2fg>(x, y) { }
      INLINE V2fg(const float s)                    : V2ft<V2fg>(s)    { }
      INLINE V2fg(const float v[2])                 : V2ft<V2fg>(v)    { }
      INLINE V2fg(const double x, const double y)   : V2ft<V2fg>(x, y) { }
      INLINE V2fg(const double s)                   : V2ft<V2fg>(s)    { }
      INLINE V2fg(const double v[2])                : V2ft<V2fg>(v)    { }
      INLINE V2fg(const int32_t x, const int32_t y) : V2ft<V2fg>(x, y) { }
      INLINE V2fg(const int32_t s)                  : V2ft<V2fg>(s)    { }
      INLINE V2fg(const int32_t v[2])               : V2ft<V2fg>(v)    { }
      INLINE V2fg(const int64_t x, const int64_t y) : V2ft<V2fg>(x, y) { }
      INLINE V2fg(const int64_t s)                  : V2ft<V2fg>(s)    { }
      INLINE V2fg(const int64_t v[2])               : V2ft<V2fg>(v)    { }
      INLINE V2fg(const V2dt<V2dg>& v)              : V2ft<V2fg>((float)v.x,  (float)v.y)  { }
      INLINE V2fg(const V2it<V2ig>& v)              : V2ft<V2fg>((float)v.x,  (float)v.y)  { }
      INLINE V2fg(const V2lt<V2lg>& v)              : V2ft<V2fg>((float)v.x,  (float)v.y)  { }
   };

   /// <summary>
   /// Double Precision 2D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V2dg : public V2dt<V2dg>
   {
   public:
      INLINE V2dg()                                                    { }
      INLINE V2dg(const double x, const double y)   : V2dt<V2dg>(x, y) { }
      INLINE V2dg(const double s)                   : V2dt<V2dg>(s, s) { }
      INLINE V2dg(const double v[2])                : V2dt<V2dg>(v)    { }
      INLINE V2dg(const float x, const float y)     : V2dt<V2dg>(x, y) { }
      INLINE V2dg(const float s)                    : V2dt<V2dg>(s)    { }
      INLINE V2dg(const float v[2])                 : V2dt<V2dg>(v)    { }
      INLINE V2dg(const int32_t x, const int32_t y) : V2dt<V2dg>(x, y) { }
      INLINE V2dg(const int32_t s)                  : V2dt<V2dg>(s)    { }
      INLINE V2dg(const int32_t v[2])               : V2dt<V2dg>(v)    { }
      INLINE V2dg(const int64_t x, const int64_t y) : V2dt<V2dg>(x, y) { }
      INLINE V2dg(const int64_t s)                  : V2dt<V2dg>(s)    { }
      INLINE V2dg(const int64_t v[2])               : V2dt<V2dg>(v)    { }
      INLINE V2dg(const V2ft<V2fg>& v)              : V2dt<V2dg>((double)v.x,  (double)v.y)  { }
      INLINE V2dg(const V2it<V2ig>& v)              : V2dt<V2dg>((double)v.x,  (double)v.y)  { }
      INLINE V2dg(const V2lt<V2lg>& v)              : V2dt<V2dg>((double)v.x,  (double)v.y)  { }
   };

   /// <summary>
   /// 32-Bit Integer 2D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V2ig : public V2it<V2ig>
   {
   public:
      INLINE V2ig()                                                    { }
      INLINE V2ig(const int32_t x, const int32_t y) : V2it<V2ig>(x, y) { }
      INLINE V2ig(const int32_t s)                  : V2it<V2ig>(s, s) { }
      INLINE V2ig(const int32_t v[2])               : V2it<V2ig>(v)    { }
      INLINE V2ig(const float x, const float y)     : V2it<V2ig>(x, y) { }
      INLINE V2ig(const float s)                    : V2it<V2ig>(s)    { }
      INLINE V2ig(const float v[2])                 : V2it<V2ig>(v)    { }
      INLINE V2ig(const double x, const double y)   : V2it<V2ig>(x, y) { }
      INLINE V2ig(const double s)                   : V2it<V2ig>(s)    { }
      INLINE V2ig(const double v[2])                : V2it<V2ig>(v)    { }
      INLINE V2ig(const int64_t x, const int64_t y) : V2it<V2ig>(x, y) { }
      INLINE V2ig(const int64_t s)                  : V2it<V2ig>(s)    { }
      INLINE V2ig(const int64_t v[2])               : V2it<V2ig>(v)    { }
      INLINE V2ig(const V2ft<V2fg>& v)              : V2it<V2ig>((int32_t)v.x, (int32_t)v.y)  { }
      INLINE V2ig(const V2dt<V2dg>& v)              : V2it<V2ig>((int32_t)v.x, (int32_t)v.y)  { }
      INLINE V2ig(const V2lt<V2lg>& v)              : V2it<V2ig>((int32_t)v.x, (int32_t)v.y)  { }
   };

   /// <summary>
   /// 64-Bit Integer 2D Vector (Generic, no SIMD) [L4]
   /// </summary>
   class V2lg : public V2lt<V2lg>
   {
   public:
      INLINE V2lg()                                                    { }
      INLINE V2lg(const int64_t x, const int64_t y) : V2lt<V2lg>(x, y) { }
      INLINE V2lg(const int64_t s)                  : V2lt<V2lg>(s)    { }
      INLINE V2lg(const int64_t v[2])               : V2lt<V2lg>(v)    { }
      INLINE V2lg(const float x, const float y)     : V2lt<V2lg>(x, y) { }
      INLINE V2lg(const float s)                    : V2lt<V2lg>(s)    { }
      INLINE V2lg(const float v[2])                 : V2lt<V2lg>(v)    { }
      INLINE V2lg(const double x, const double y)   : V2lt<V2lg>(x, y) { }
      INLINE V2lg(const double s)                   : V2lt<V2lg>(s)    { }
      INLINE V2lg(const double v[2])                : V2lt<V2lg>(v)    { }
      INLINE V2lg(const int32_t x, const int32_t y) : V2lt<V2lg>(x, y) { }
      INLINE V2lg(const int32_t s)                  : V2lt<V2lg>(s)    { }
      INLINE V2lg(const int32_t v[2])               : V2lt<V2lg>(v)    { }
      INLINE V2lg(const V2ft<V2fg>& v)              : V2lt<V2lg>((int64_t)v.x, (int64_t)v.y)  { }
      INLINE V2lg(const V2dt<V2dg>& v)              : V2lt<V2lg>((int64_t)v.x, (int64_t)v.y)  { }
      INLINE V2lg(const V2it<V2ig>& v)              : V2lt<V2lg>((int64_t)v.x, (int64_t)v.y)  { }
   };

   //------------------------------------------------------------------------------------------------------------------------//
   //                                             SIMD CLASSES [L4]                                                          //
   //------------------------------------------------------------------------------------------------------------------------//
#if defined(CPPCORE_CPUFEAT_SSE2)
   class V2fs;
   class V2ds;
   class V2is;
   class V2ls;

   /// <summary>
   /// Single Precision 2D Vector (SSE/SIMD)
   /// </summary>
   class CPPCORE_ALIGN8_INTRIN V2fs : public V2ft<V2fs>
   {
   public:
      INLINE __m128 load()                 const    { return _mm_castpd_ps(_mm_load_sd((const double*)vals));   }
      INLINE void   store(const __m128& v)          { _mm_store_sd((double*)vals, _mm_castps_pd(v));            }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V2fs()                                 { }
      INLINE V2fs(const __m128& v)                  { store(v);                                                 }
      INLINE V2fs(const float x, const float y)     { store(_mm_set_ps(0.0f, 0.0f, y, x));                      }
      INLINE V2fs(const float s)                    { store(_mm_set_ps(0.0f, 0.0f, s, s));                      }
      INLINE V2fs(const float v[2])                 { store(_mm_castpd_ps(_mm_load_sd((const double*)v)));      }
      INLINE V2fs(const double x, const double y)   { store(_mm_cvtpd_ps(_mm_set_pd(y, x)));                    }
      INLINE V2fs(const double s)                   { store(_mm_cvtpd_ps(_mm_set1_pd(s)));                      }
      INLINE V2fs(const double v[2])                { store(_mm_cvtpd_ps(_mm_loadu_pd(v)));                     }
      INLINE V2fs(const int32_t x, const int32_t y) { store(_mm_cvtepi32_ps(_mm_set_epi32(0, 0, y, x)));        }
      INLINE V2fs(const int32_t s)                  { store(_mm_cvtepi32_ps(_mm_set_epi32(0, 0, s, s)));        }
      INLINE V2fs(const int32_t v[2])               { store(_mm_cvtepi32_ps(_mm_castpd_si128(_mm_load_sd((const double*)v))));    }
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      INLINE V2fs(const int64_t x, const int32_t y) { store(_mm_cvtepi64_ps(_mm_set_epi64x(y, x)));             }
      INLINE V2fs(const int64_t s)                  { store(_mm_cvtepi64_ps(_mm_set1_epi64x(s)));               }
      INLINE V2fs(const int64_t v[2])               { store(_mm_cvtepi64_ps(_mm_loadu_epi64(v)));               }
   #else
      INLINE V2fs(const int64_t x, const int32_t y) { store(_mm_set_ps(0.0f, 0.0f, (float)y, (float)x));        }
      INLINE V2fs(const int64_t s)                  { store(_mm_set_ps(0.0f, 0.0f, (float)s, (float)s));        }
      INLINE V2fs(const int64_t v[2])               { store(_mm_set_ps(0.0f, 0.0f, (float)v[1], (float)v[0]));  }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
      template<typename V> INLINE V2fs(const V2dt<V>& v) { store(_mm_cvtpd_ps(_mm_loadu_pd(v.vals)));                 }
      template<typename V> INLINE V2fs(const V2it<V>& v) { store(_mm_cvtepi32_ps(_mm_castpd_si128(_mm_load_sd((const double*)v.vals)))); }
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      template<typename V> INLINE V2fs(const V2lt<V>& v) { store(_mm_cvtepi64_ps(_mm_loadu_epi64(v.vals)));           }
   #else
      template<typename V> INLINE V2fs(const V2lt<V>& v) { store(_mm_set_ps(0.0f, 0.0f, (float)v.y, (float)v.x));     }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE       void* operator new  (size_t size)        { return CPPCORE_ALIGNED_ALLOC(size, 8U);                          }
      INLINE       void* operator new[](size_t size)        { return CPPCORE_ALIGNED_ALLOC(size, 8U);                          }
      INLINE       void  operator delete   (void* ptr)      { return CPPCORE_ALIGNED_FREE(ptr);                                }
      INLINE       void  operator delete[] (void* ptr)      { return CPPCORE_ALIGNED_FREE(ptr);                                }
      INLINE       bool  operator == (const V2fs&  v) const { return _mm_movemask_ps(_mm_cmpeq_ps(load(), v.load())) == 0x0F;  }
      INLINE       bool  operator != (const V2fs&  v) const { return _mm_movemask_ps(_mm_cmpeq_ps(load(), v.load())) != 0x0F;  }
      INLINE       bool  operator <  (const V2fs&  v) const { return _mm_movemask_ps(_mm_cmplt_ps(load(), v.load())) == 0x03;  }
      INLINE       bool  operator <= (const V2fs&  v) const { return _mm_movemask_ps(_mm_cmple_ps(load(), v.load())) == 0x0F;  }
      INLINE       bool  operator >  (const V2fs&  v) const { return _mm_movemask_ps(_mm_cmpgt_ps(load(), v.load())) == 0x03;  }
      INLINE       bool  operator >= (const V2fs&  v) const { return _mm_movemask_ps(_mm_cmpge_ps(load(), v.load())) == 0x0F;  }
      INLINE       V2fs  operator +  (const V2fs&  v) const { return V2fs(_mm_add_ps(load(), v.load()));                       }
      INLINE       V2fs  operator -  (const V2fs&  v) const { return V2fs(_mm_sub_ps(load(), v.load()));                       }
      INLINE       V2fs  operator *  (const V2fs&  v) const { return V2fs(_mm_mul_ps(load(), v.load()));                       }
      INLINE       V2fs  operator /  (const V2fs&  v) const { return V2fs(_mm_div_ps(load(), v.load()));                       }
      INLINE       V2fs  operator +  (const float  s) const { return V2fs(_mm_add_ps(load(), _mm_set1_ps(s)));                 }
      INLINE       V2fs  operator -  (const float  s) const { return V2fs(_mm_sub_ps(load(), _mm_set1_ps(s)));                 }
      INLINE       V2fs  operator *  (const float  s) const { return V2fs(_mm_mul_ps(load(), _mm_set1_ps(s)));                 }
      INLINE       V2fs  operator /  (const float  s) const { return V2fs(_mm_div_ps(load(), _mm_set1_ps(s)));                 }
      INLINE       V2fs  operator -  ()               const { return V2fs(_mm_sub_ps(_mm_setzero_ps(), load()));               }
      INLINE const V2fs& operator +  ()               const { return *this;                                                    }
      INLINE       V2fs& operator =  (const V2fs&  v)       { store(v.load());                           return *this;         }
      INLINE       V2fs& operator += (const V2fs&  v)       { store(_mm_add_ps(load(), v.load()));       return *this;         }
      INLINE       V2fs& operator -= (const V2fs&  v)       { store(_mm_sub_ps(load(), v.load()));       return *this;         }
      INLINE       V2fs& operator *= (const V2fs&  v)       { store(_mm_mul_ps(load(), v.load()));       return *this;         }
      INLINE       V2fs& operator /= (const V2fs&  v)       { store(_mm_div_ps(load(), v.load()));       return *this;         }
      INLINE       V2fs& operator =  (const float  s)       { store(_mm_set1_ps(s));                     return *this;         }
      INLINE       V2fs& operator += (const float  s)       { store(_mm_add_ps(load(), _mm_set1_ps(s))); return *this;         }
      INLINE       V2fs& operator -= (const float  s)       { store(_mm_sub_ps(load(), _mm_set1_ps(s))); return *this;         }
      INLINE       V2fs& operator *= (const float  s)       { store(_mm_mul_ps(load(), _mm_set1_ps(s))); return *this;         }
      INLINE       V2fs& operator /= (const float  s)       { store(_mm_div_ps(load(), _mm_set1_ps(s))); return *this;         }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void swap(V2fs& v)                                { __m128 t(load()); store(v.load()); v.store(t);                }
      INLINE V2fs absC()                                 const { return V2fs(_mm_andnot_ps(_mm_set1_ps(-0.f), load()));        }
      INLINE V2fs maxC(const V2fs& v)                    const { return V2fs(_mm_max_ps(load(), v.load()));                    }
      INLINE V2fs minC(const V2fs& v)                    const { return V2fs(_mm_min_ps(load(), v.load()));                    }
      INLINE V2fs boundC(const V2fs& mi, const V2fs& ma) const { return V2fs(_mm_max_ps(_mm_min_ps(load(), ma.load()), mi.load())); }
      INLINE void abs()                                        { store(_mm_andnot_ps(_mm_set1_ps(-0.), load()));               }
      INLINE void max(const V2fs& v)                           { store(_mm_max_ps(load(), v.load()));                          }
      INLINE void min(const V2fs& v)                           { store(_mm_min_ps(load(), v.load()));                          }
      INLINE void bound(const V2fs& mi, const V2fs& ma)        { store(_mm_max_ps(_mm_min_ps(load(), ma.load()), mi.load()));  }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void madd(const V2fs& m, const V2fs& a) { store(madd128f(load(), m.load(), a.load())); }
      INLINE void msub(const V2fs& m, const V2fs& s) { store(msub128f(load(), m.load(), s.load())); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE float dot(const V2fs& v) const
      {
         __m128 a(_mm_mul_ps(load(), v.load()));
         __m128 b(permute128f<_MM_SHUFFLE(2, 3, 0, 1)>(a));
         __m128 c(_mm_add_ss(a, b));
         return _mm_cvtss_f32(c);
      }
      INLINE float length() const
      {
         __m128 t(load());
         __m128 a(_mm_mul_ps(t, t));
         __m128 b(permute128f<_MM_SHUFFLE(2, 3, 0, 1)>(a));
         __m128 c(_mm_add_ss(a, b));
         __m128 d(_mm_sqrt_ss(c));
         return _mm_cvtss_f32(d);
      }
      INLINE float side(const V2fs& s, const V2fs& e) const
      {
         __m128 t(s.load());
         __m128 a(_mm_sub_ps(e.load(), t));
         __m128 b(_mm_sub_ps(load(), t));
         __m128 c(permute128f<_MM_SHUFFLE(2, 3, 0, 1)>(b));
         __m128 d(_mm_mul_ps(a, c));
         __m128 f(permute128f<_MM_SHUFFLE(2, 3, 0, 1)>(d));
         __m128 g(_mm_sub_ss(d, f));
         return _mm_cvtss_f32(g);
      }
      INLINE bool inside(const V2fs& min, const V2fs& max) const
      {
         const __m128 t = load();
         return _mm_movemask_ps(_mm_and_ps(
            _mm_cmpge_ps(t, min.load()), 
            _mm_cmple_ps(t, max.load()))) == 0x0F;
      }
      INLINE bool inside(const V2fs& min, const V2fs& max, const float e) const
      {
         const __m128 t = load();
         const __m128 eps(broadcast128f(&e));
         const __m128 a(_mm_and_ps(
            _mm_cmpge_ps(t, _mm_sub_ps(min.load(), eps)), 
            _mm_cmple_ps(t, _mm_add_ps(max.load(), eps))));
         return _mm_movemask_ps(a) == 0x0F;
      }
      INLINE bool inside(const V2fs& m, const float r2) const
      {
         __m128 t(_mm_sub_ps(load(), m.load()));
         __m128 a(_mm_mul_ps(t, t));
         __m128 b(permute128f<_MM_SHUFFLE(2, 3, 0, 1)>(a));
         __m128 c(_mm_add_ss(a, b));
         return _mm_comile_ss(c, _mm_load_ss(&r2));
      }
      INLINE bool inside(const V2fs& m, const float r2, const float e) const
      {
         __m128 t(_mm_sub_ps(load(), m.load()));
         __m128 a(_mm_mul_ps(t, t));
         __m128 b(permute128f<_MM_SHUFFLE(2, 3, 0, 1)>(a));
         __m128 c(_mm_add_ss(a, b));
         return _mm_comile_ss(c, _mm_add_ss(_mm_load_ss(&r2), _mm_load_ss(&e)));
      }
      INLINE float area(const V2fs& p) const
      {
         return V2ft<V2fs>::area(p);
      }
      INLINE float area(const V2fs& p, const V2fs& q) const
      {
         static constexpr const float HALF = 0.5f;
         __m128 t(load());
         __m128 a(_mm_sub_ps(p.load(), t));
         __m128 b(_mm_sub_ps(q.load(), t));
         __m128 c(permute128f<_MM_SHUFFLE(2, 3, 0, 1)>(b));
         __m128 d(_mm_mul_ps(a, c));
         __m128 e(permute128f<_MM_SHUFFLE(2, 3, 0, 1)>(d));
         __m128 f(_mm_sub_ss(d, e));
         return _mm_cvtss_f32(_mm_mul_ss(f, _mm_load_ss(&HALF)));
      }
   #if defined(CPPCORE_CPUFEAT_SSE41)
      INLINE void  round()                       { store(_mm_round_ps(load(), _MM_FROUND_NINT));        }
      INLINE void  floor()                       { store(_mm_round_ps(load(), _MM_FROUND_FLOOR));       }
      INLINE void  ceil()                        { store(_mm_round_ps(load(), _MM_FROUND_CEIL));        }
      INLINE void  round(const float n)
      {
         const __m128 t1(broadcast128f(&n));
         store(_mm_mul_ps(_mm_round_ps(_mm_div_ps(load(), t1), _MM_FROUND_NINT), t1));
      }
   #endif
   };

   /// <summary>
   /// Double Precision 2D Vector (SSE/SIMD)
   /// </summary>
   class CPPCORE_ALIGN16_INTRIN V2ds : public V2dt<V2ds>
   {
   public:
      INLINE __m128d load()                  const  { return _mm_load_pd(vals); }
      INLINE void    store(const __m128d& v)        { _mm_store_pd(vals, v);    }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V2ds()                                 {                                                                         }
      INLINE V2ds(const __m128d& v)                 { store(v);                                                               }
      INLINE V2ds(const double x, const double y)   { store(_mm_set_pd(y, x));                                                }
      INLINE V2ds(const double s)                   { store(_mm_set1_pd(s));                                                  }
      INLINE V2ds(const double v[2])                { store(_mm_loadu_pd(v));                                                 }
      INLINE V2ds(const float x, const float y)     { store(_mm_cvtps_pd(_mm_set_ps(0.0f, 0.0f, y, x)));                      }
      INLINE V2ds(const float s)                    { store(_mm_cvtps_pd(_mm_set1_ps(s)));                                    }
      INLINE V2ds(const float v[2])                 { store(_mm_cvtps_pd(_mm_castsi128_ps(_mm_loadl_epi64((__m128i*)v))));    }
      INLINE V2ds(const int32_t x, const int32_t y) { store(_mm_cvtepi32_pd(_mm_set_epi32(0, 0, y, x)));                      }
      INLINE V2ds(const int32_t s)                  { store(_mm_cvtepi32_pd(_mm_set1_epi32(s)));                              }
      INLINE V2ds(const int32_t v[2])               { store(_mm_cvtepi32_pd(_mm_loadl_epi64((__m128i*)v)));                   }
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      INLINE V2ds(const int64_t x, const int64_t y) { store(_mm_cvtepi64_pd(_mm_set_epi64x(y, x)));                           }
      INLINE V2ds(const int64_t s)                  { store(_mm_cvtepi64_pd(_mm_set1_epi64x(s)));                             }
      INLINE V2ds(const int64_t v[2])               { store(_mm_cvtepi64_pd(_mm_loadu_si128((__m128i*)v)));                   }
   #else
      INLINE V2ds(const int64_t x, const int64_t y) { store(_mm_set_pd((double)y, (double)x));                                }
      INLINE V2ds(const int64_t s)                  { store(_mm_set1_pd((double)s));                                          }
      INLINE V2ds(const int64_t v[2])               { store(_mm_set_pd((double)v[1], (double)v[0]));                          }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
      template<typename V> INLINE V2ds(const V2ft<V>& v) { store(_mm_cvtps_pd(_mm_castsi128_ps(_mm_loadl_epi64((__m128i*)v.vals))));}
      template<typename V> INLINE V2ds(const V2it<V>& v) { store(_mm_cvtepi32_pd(_mm_loadl_epi64((__m128i*)v.vals)));         }
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      template<typename V> INLINE V2ds(const V2lt<V>& v) { store(_mm_cvtepi64_pd(_mm_loadu_si128((__m128i*)v.vals)));         }
   #else
      template<typename V> INLINE V2ds(const V2lt<V>& v) { store(_mm_set_pd((double)v.y, (double)v.x));                       }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE       void* operator new  (size_t size)        { return CPPCORE_ALIGNED_ALLOC(size, 16U);                        }
      INLINE       void* operator new[](size_t size)        { return CPPCORE_ALIGNED_ALLOC(size, 16U);                        }
      INLINE       void  operator delete   (void* ptr)      { return CPPCORE_ALIGNED_FREE(ptr);                               }
      INLINE       void  operator delete[] (void* ptr)      { return CPPCORE_ALIGNED_FREE(ptr);                               }
      INLINE       bool  operator == (const V2ds&  v) const { return _mm_movemask_pd(_mm_cmpeq_pd(load(), v.load())) == 0x03; }
      INLINE       bool  operator != (const V2ds&  v) const { return _mm_movemask_pd(_mm_cmpeq_pd(load(), v.load())) != 0x03; }
      INLINE       bool  operator <  (const V2ds&  v) const { return _mm_movemask_pd(_mm_cmplt_pd(load(), v.load())) == 0x03; }
      INLINE       bool  operator <= (const V2ds&  v) const { return _mm_movemask_pd(_mm_cmple_pd(load(), v.load())) == 0x03; }
      INLINE       bool  operator >  (const V2ds&  v) const { return _mm_movemask_pd(_mm_cmpgt_pd(load(), v.load())) == 0x03; }
      INLINE       bool  operator >= (const V2ds&  v) const { return _mm_movemask_pd(_mm_cmpge_pd(load(), v.load())) == 0x03; }
      INLINE       V2ds  operator +  (const V2ds&  v) const { return V2ds(_mm_add_pd(load(), v.load()));                      }
      INLINE       V2ds  operator -  (const V2ds&  v) const { return V2ds(_mm_sub_pd(load(), v.load()));                      }
      INLINE       V2ds  operator *  (const V2ds&  v) const { return V2ds(_mm_mul_pd(load(), v.load()));                      }
      INLINE       V2ds  operator /  (const V2ds&  v) const { return V2ds(_mm_div_pd(load(), v.load()));                      }
      INLINE       V2ds  operator +  (const double s) const { return V2ds(_mm_add_pd(load(), _mm_set1_pd(s)));                }
      INLINE       V2ds  operator -  (const double s) const { return V2ds(_mm_sub_pd(load(), _mm_set1_pd(s)));                }
      INLINE       V2ds  operator *  (const double s) const { return V2ds(_mm_mul_pd(load(), _mm_set1_pd(s)));                }
      INLINE       V2ds  operator /  (const double s) const { return V2ds(_mm_div_pd(load(), _mm_set1_pd(s)));                }
      INLINE       V2ds  operator -  ()               const { return V2ds(_mm_sub_pd(_mm_setzero_pd(), load()));              }
      INLINE const V2ds& operator +  ()               const { return *this;                                                   }
      INLINE       V2ds& operator =  (const V2ds&  v)       { store(v.load());                           return *this;        }
      INLINE       V2ds& operator += (const V2ds&  v)       { store(_mm_add_pd(load(), v.load()));       return *this;        }
      INLINE       V2ds& operator -= (const V2ds&  v)       { store(_mm_sub_pd(load(), v.load()));       return *this;        }
      INLINE       V2ds& operator *= (const V2ds&  v)       { store(_mm_mul_pd(load(), v.load()));       return *this;        }
      INLINE       V2ds& operator /= (const V2ds&  v)       { store(_mm_div_pd(load(), v.load()));       return *this;        }
      INLINE       V2ds& operator =  (const double s)       { store(_mm_set1_pd(s));                     return *this;        }
      INLINE       V2ds& operator += (const double s)       { store(_mm_add_pd(load(), _mm_set1_pd(s))); return *this;        }
      INLINE       V2ds& operator -= (const double s)       { store(_mm_sub_pd(load(), _mm_set1_pd(s))); return *this;        }
      INLINE       V2ds& operator *= (const double s)       { store(_mm_mul_pd(load(), _mm_set1_pd(s))); return *this;        }
      INLINE       V2ds& operator /= (const double s)       { store(_mm_div_pd(load(), _mm_set1_pd(s))); return *this;        }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void swap(V2ds& v)                                { __m128d t(load()); store(v.load()); v.store(t);              }
      INLINE V2ds absC()                                 const { return V2ds(_mm_andnot_pd(_mm_set1_pd(-0.), load()));        }
      INLINE V2ds maxC(const V2ds& v)                    const { return V2ds(_mm_max_pd(load(), v.load()));                   }
      INLINE V2ds minC(const V2ds& v)                    const { return V2ds(_mm_min_pd(load(), v.load()));                   }
      INLINE V2ds boundC(const V2ds& mi, const V2ds& ma) const { return V2ds(_mm_max_pd(_mm_min_pd(load(), ma.load()), mi.load())); }
      INLINE void abs()                                        { store(_mm_andnot_pd(_mm_set1_pd(-0.), load()));              }
      INLINE void max(const V2ds& v)                           { store(_mm_max_pd(load(), v.load()));                         }
      INLINE void min(const V2ds& v)                           { store(_mm_min_pd(load(), v.load()));                         }
      INLINE void bound(const V2ds& mi, const V2ds& ma)        { store(_mm_max_pd(_mm_min_pd(load(), ma.load()), mi.load())); }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void rotate(double r)
      {
         __m128d cs(_mm_set1_pd(_cos(r)));
         __m128d sn(_mm_set1_pd(_sin(r)));
         __m128d p(_mm_set_pd(x, -y));
         store(_mm_add_pd(_mm_mul_pd(load(), cs), _mm_mul_pd(p, sn)));
      }
      INLINE double cross(const V2ds& v) const
      {
         __m128d a(_mm_shuffle_pd(v.load(), v.load(), _MM_SHUFFLE2(0, 1)));
         __m128d b(_mm_mul_pd(load(), a));
         __m128d c(_mm_shuffle_pd(b, b, _MM_SHUFFLE2(0, 1)));
         __m128d d(_mm_sub_sd(b, c));
         return _mm_cvtsd_f64(d);
      }
      INLINE bool inside(const V2ds& min, const V2ds& max) const
      {
         __m128d a(_mm_cmpge_pd(load(), min.load()));
         __m128d b(_mm_cmple_pd(load(), max.load()));
         __m128d c(_mm_and_pd(a, b));
         return _mm_movemask_pd(c) == 0x03;
      }
      INLINE bool inside(const V2ds& min, const V2ds& max, const double e) const
      {
         __m128d eps(_mm_set1_pd(e));
         __m128d a(_mm_cmpge_pd(load(), _mm_sub_pd(min.load(), eps)));
         __m128d b(_mm_cmple_pd(load(), _mm_add_pd(max.load(), eps)));
         __m128d c(_mm_and_pd(a, b));
         return _mm_movemask_pd(c) == 0x03;
      }
   #if defined(CPPCORE_CPUFEAT_SSE41)
      INLINE double dot(const V2ds& v) const { return _mm_cvtsd_f64(_mm_dp_pd(load(), v.load(), 0x31));                          }
      INLINE double length()           const { __m128d t(load()); return _mm_cvtsd_f64(_mm_sqrt_pd(_mm_dp_pd(t, t, 0x31)));      }
      INLINE void   round()                  { store(_mm_round_pd(load(), _MM_FROUND_NINT));                                     }
      INLINE void   floor()                  { store(_mm_round_pd(load(), _MM_FROUND_FLOOR));                                    }
      INLINE void   ceil()                   { store(_mm_round_pd(load(), _MM_FROUND_CEIL));                                     }
      INLINE void   normalise()              { __m128d t(load()); store(_mm_div_pd(t, _mm_sqrt_pd(_mm_dp_pd(t, t, 0x33)))); }
      INLINE void   round(const double n)
      {
         const __m128d t1(_mm_set1_pd(n));
         store(_mm_mul_pd(_mm_round_pd(_mm_div_pd(load(), t1), _MM_FROUND_NINT), t1));
      }
   #else
      INLINE double dot(const V2ds& v) const 
      {
         __m128d a(_mm_mul_pd(load(), v.load()));
         __m128d b(_mm_castps_pd(_mm_movehl_ps(_mm_undefined_ps(), _mm_castpd_ps(a))));
         __m128d c(_mm_add_sd(a, b));
         return _mm_cvtsd_f64(c);
      }
      INLINE double length() const 
      { 
         __m128d t(load());
         __m128d a(_mm_mul_pd(t, t));
         __m128d b(_mm_castps_pd(_mm_movehl_ps(_mm_undefined_ps(), _mm_castpd_ps(a))));
         __m128d c(_mm_add_sd(a, b));
         __m128d d(_mm_sqrt_sd(c, c));
         return _mm_cvtsd_f64(d);
      }
      INLINE void   normalise()
      { 
         __m128d t(load());
         __m128d a(_mm_mul_pd(t, t));
         __m128d b(_mm_shuffle_pd(a, a, _MM_SHUFFLE2(0,1)));
         __m128d c(_mm_add_pd(a, b));
         __m128d d(_mm_sqrt_pd(c));
         store(_mm_div_pd(t, d));
      }
   #endif
   #if defined(CPPCORE_CPUFEAT_FMA3)
      INLINE void madd(const V2ds& m, const V2ds& a) { store(_mm_fmadd_pd(load(), m.load(), a.load())); }
      INLINE void msub(const V2ds& m, const V2ds& s) { store(_mm_fmsub_pd(load(), m.load(), s.load())); }
   #else
      INLINE void madd(const V2ds& m, const V2ds& a) { store(_mm_add_pd(_mm_mul_pd(load(), m.load()), a.load())); }
      INLINE void msub(const V2ds& m, const V2ds& s) { store(_mm_sub_pd(_mm_mul_pd(load(), m.load()), s.load())); }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
   };

   /// <summary>
   /// 32-Bit Integer 2D Vector (SSE/SIMD)
   /// </summary>
   class CPPCORE_ALIGN8_INTRIN V2is : public V2it<V2is>
   {
   private:
      static const int64_t HIGHONES = 0x0000000100000001;
   public:
      INLINE __m128i load()                  const  { return _mm_loadl_epi64((__m128i*)vals); }
      INLINE void    store(const __m128i& v)        { _mm_storel_epi64((__m128i*)vals, v);    }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V2is()                                 {                                                                          }
      INLINE V2is(const __m128i& v)                 { store(v);                                                                }
      INLINE V2is(const int32_t x, const int32_t y) { store(_mm_set_epi32(0, 0, y, x));                                        }
      INLINE V2is(const int32_t s)                  { store(_mm_set_epi32(0, 0, s, s));                                        }
      INLINE V2is(const int32_t values[2])          { store(_mm_loadl_epi64((__m128i*)values));                                }
      INLINE V2is(const float x, const float y)     { store(_mm_cvttps_epi32(_mm_set_ps(0.0f, 0.0f, y, x)));                   }
      INLINE V2is(const float s)                    { store(_mm_cvttps_epi32(_mm_set_ps(0.0f, 0.0f, s, s)));                   }
      INLINE V2is(const float v[2])                 { store(_mm_cvttps_epi32(_mm_castsi128_ps(_mm_loadl_epi64((__m128i*)v)))); }
      INLINE V2is(const double x, const double y)   { store(_mm_cvttpd_epi32(_mm_set_pd(y, x)));                               }
      INLINE V2is(const double s)                   { store(_mm_cvttpd_epi32(_mm_set1_pd(s)));                                 }
      INLINE V2is(const double v[2])                { store(_mm_cvttpd_epi32(_mm_loadu_pd(v)));                                }
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      INLINE V2is(const int64_t x, const int64_t y) { store(_mm_cvtepi64_epi32(_mm_set_epi64x(y, x)));                         }
      INLINE V2is(const int64_t s)                  { store(_mm_cvtepi64_epi32(_mm_set1_epi64x(s)));                           }
      INLINE V2is(const int64_t v[2])               { store(_mm_cvtepi64_epi32(_mm_loadu_si128((__m128i*)v)));                 }
   #else
      INLINE V2is(const int64_t x, const int64_t y) { store(_mm_set_epi32(0, 0, (int32_t)y, (int32_t)x));                      }
      INLINE V2is(const int64_t s)                  { store(_mm_set_epi32(0, 0, (int32_t)s, (int32_t)s));                      }
      INLINE V2is(const int64_t v[2])               { store(_mm_set_epi32(0, 0, (int32_t)v[1], (int32_t)v[0]));                }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
      template<typename V> INLINE V2is(const V2ft<V>& v) { store(_mm_cvttps_epi32(_mm_castsi128_ps(_mm_loadl_epi64((__m128i*)v.vals))));}
      template<typename V> INLINE V2is(const V2dt<V>& v) { store(_mm_cvttpd_epi32(_mm_loadu_pd(v.vals)));                      }
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      template<typename V> INLINE V2is(const V2lt<V>& v) { store(_mm_cvtepi64_epi32(_mm_loadu_si128((__m128i*)v.vals)));       }
   #else
      template<typename V> INLINE V2is(const V2lt<V>& v) { store(_mm_set_epi32(0, 0, (int32_t)v.y, (int32_t)v.x));             }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE       void* operator new  (size_t size)         { return CPPCORE_ALIGNED_ALLOC(size, 8U);                         }
      INLINE       void* operator new[](size_t size)         { return CPPCORE_ALIGNED_ALLOC(size, 8U);                         }
      INLINE       void  operator delete   (void* ptr)       { return CPPCORE_ALIGNED_FREE(ptr);                               }
      INLINE       void  operator delete[] (void* ptr)       { return CPPCORE_ALIGNED_FREE(ptr);                               }
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      INLINE       bool  operator == (const V2is&   v) const { return _mm_cmpeq_epi32_mask(load(), v.load()) == 0x0F;          }
      INLINE       bool  operator != (const V2is&   v) const { return _mm_cmpeq_epi32_mask(load(), v.load()) != 0x0F;          }
      INLINE       bool  operator <  (const V2is&   v) const { return _mm_cmplt_epi32_mask(load(), v.load()) == 0x03;          }
      INLINE       bool  operator <= (const V2is&   v) const { return _mm_cmple_epi32_mask(load(), v.load()) == 0x0F;          }
      INLINE       bool  operator >  (const V2is&   v) const { return _mm_cmpgt_epi32_mask(load(), v.load()) == 0x03;          }
      INLINE       bool  operator >= (const V2is&   v) const { return _mm_cmpge_epi32_mask(load(), v.load()) == 0x0F;          }
   #else
      INLINE       bool  operator == (const V2is&   v) const { return _mm_movemask_epi8(_mm_cmpeq_epi32(load(),v.load()))==0xFFFF;}
      INLINE       bool  operator != (const V2is&   v) const { return _mm_movemask_epi8(_mm_cmpeq_epi32(load(),v.load()))!=0xFFFF;}
      INLINE       bool  operator <  (const V2is&   v) const { return _mm_movemask_epi8(_mm_cmplt_epi32(load(),v.load()))==0xFF;  }
      INLINE       bool  operator >  (const V2is&   v) const { return _mm_movemask_epi8(_mm_cmpgt_epi32(load(),v.load()))==0xFF;  }
   #endif
      INLINE       V2is  operator +  (const V2is&   v) const { return V2is(_mm_add_epi32(load(), v.load()));                      }
      INLINE       V2is  operator +  (const int32_t s) const { return V2is(_mm_add_epi32(load(), _mm_set1_epi32(s)));             }
      INLINE       V2is  operator -  (const V2is&   v) const { return V2is(_mm_sub_epi32(load(), v.load()));                      }
      INLINE       V2is  operator -  (const int32_t s) const { return V2is(_mm_sub_epi32(load(), _mm_set1_epi32(s)));             }
      INLINE       V2is  operator -  ()                const { return V2is(_mm_sub_epi32(_mm_setzero_si128(), load()));           }
      INLINE const V2is& operator +  ()                const { return *this;                                                      }
      INLINE       V2is& operator =  (const V2is&   v)       { store(v.load());                                   return *this;   }
      INLINE       V2is& operator += (const V2is&   v)       { store(_mm_add_epi32(load(), v.load()));            return *this;   }
      INLINE       V2is& operator -= (const V2is&   v)       { store(_mm_sub_epi32(load(), v.load()));            return *this;   }
      INLINE       V2is& operator =  (const int32_t s)       { store(_mm_set1_epi32(s));                          return *this;   }
      INLINE       V2is& operator += (const int32_t s)       { store(_mm_add_epi32(load(), _mm_set1_epi32(s)));   return *this;   }
      INLINE       V2is& operator -= (const int32_t s)       { store(_mm_sub_epi32(load(), _mm_set1_epi32(s)));   return *this;   }
   #if defined(CPPCORE_COMPILER_MSVC)
      INLINE       V2is  operator /  (const V2is&   v) const { return V2is(_mm_div_epi32(load(), v.load(HIGHONES)));              }
      INLINE       V2is  operator /  (const int32_t s) const { return V2is(_mm_div_epi32(load(), _mm_set1_epi32(s)));             }
      INLINE       V2is& operator /= (const V2is&   v)       { store(_mm_div_epi32(load(), v.load(HIGHONES)));    return *this;   }
      INLINE       V2is& operator /= (const int32_t s)       { store(_mm_div_epi32(load(), _mm_set1_epi32(s)));   return *this;   }
   #endif
   #if defined(CPPCORE_CPUFEAT_SSE41)
      INLINE       V2is  operator *  (const V2is&   v) const { return V2is(_mm_mullo_epi32(load(), v.load()));                    }
      INLINE       V2is  operator *  (const int32_t s) const { return V2is(_mm_mullo_epi32(load(), _mm_set1_epi32(s)));           }
      INLINE       V2is& operator *= (const V2is&   v)       { store(_mm_mullo_epi32(load(), v.load()));          return *this;   }
      INLINE       V2is& operator *= (const int32_t s)       { store(_mm_mullo_epi32(load(), _mm_set1_epi32(s))); return *this;   }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void swap(V2is& v)                              { __m128i t(load()); store(v.load()); v.store(t); }
   #if defined(CPPCORE_CPUFEAT_SSSE3)
      INLINE V2is absC()                               const { return V2is(_mm_abs_epi32(load()));             }
      INLINE void abs()                                      { store(_mm_abs_epi32(load()));                   }
   #endif
   #if defined(CPPCORE_CPUFEAT_SSE41)
      INLINE V2is maxC(const V2is& v)                  const { return V2is(_mm_max_epi32(load(), v.load()));   }
      INLINE V2is minC(const V2is& v)                  const { return V2is(_mm_min_epi32(load(), v.load()));   }
      INLINE void max(const V2is& v)                         { store(_mm_max_epi32(load(), v.load()));         }
      INLINE void min(const V2is& v)                         { store(_mm_min_epi32(load(), v.load()));         }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE __m128i load(const int64_t h) const 
      {
         __m128i a(_mm_loadl_epi64((__m128i*)vals));
         __m128d b(_mm_loadh_pd(_mm_castsi128_pd(a), (double*)&h));
         return _mm_castpd_si128(b);
      }
   #if !defined(CPPCORE_CPUFEAT_AVX512F)
      INLINE bool operator <= (const V2is& v) const 
      {
         __m128i a(load());
         __m128i b(v.load());
         __m128i lt(_mm_cmplt_epi32(a, b));
         __m128i eq(_mm_cmpeq_epi32(a, b));
         __m128i _or(_mm_or_si128(lt, eq));
         return _mm_movemask_epi8(_or) == 0xFFFF;

      }
      INLINE bool operator >= (const V2is& v) const
      {
         __m128i a(load());
         __m128i b(v.load());
         __m128i lt(_mm_cmpgt_epi32(a, b));
         __m128i eq(_mm_cmpeq_epi32(a, b));
         __m128i _or (_mm_or_si128(lt, eq));
         return _mm_movemask_epi8(_or) == 0xFFFF;
      }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
   };

   /// <summary>
   /// 64-Bit Integer 2D Vector (SSE/SIMD)
   /// </summary>
   class CPPCORE_ALIGN16_INTRIN V2ls : public V2lt<V2ls>
   {
   public:
      INLINE __m128i load()                  const  { return _mm_load_si128((__m128i*)vals); }
      INLINE void    store(const __m128i& v)        { _mm_store_si128((__m128i*)vals, v);    }
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE V2ls()                                 {                                                                          }
      INLINE V2ls(const int64_t x, const int64_t y) { store(_mm_set_epi64x(y, x));                                             }
      INLINE V2ls(const int64_t s)                  { store(_mm_set1_epi64x(s));                                               }
      INLINE V2ls(const int64_t v[2])               { store(_mm_loadu_si128((__m128i*)v));                                     }
      INLINE V2ls(const __m128i& v)                 { store(v);                                                                }
   #if defined(CPPCORE_CPUFEAT_SSE41)
      INLINE V2ls(const int32_t x, const int32_t y) { store(_mm_cvtepi32_epi64(_mm_set_epi32(0, 0, y, x)));                    }
      INLINE V2ls(const int32_t s)                  { store(_mm_cvtepi32_epi64(_mm_set1_epi32(s)));                            }
      INLINE V2ls(const int32_t v[2])               { store(_mm_cvtepi32_epi64(_mm_loadl_epi64((__m128i*)v)));                 }
   #else
      INLINE V2ls(const int32_t x, const int32_t y) { store(_mm_set_epi64x ((int64_t)y, (int64_t)x));                          }
      INLINE V2ls(const int32_t s)                  { store(_mm_set1_epi64x((int64_t)s));                                      }
      INLINE V2ls(const int32_t v[2])               { store(_mm_set_epi64x ((int64_t)v[1], (int64_t)v[0]));                    }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      INLINE V2ls(const float x, const float y)     { store(_mm_cvttps_epi64(_mm_set_ps(0.0f, 0.0f, y, x)));                   }
      INLINE V2ls(const float s)                    { store(_mm_cvttps_epi64(_mm_set1_ps(s)));                                 }
      INLINE V2ls(const float v[2])                 { store(_mm_cvttps_epi64(_mm_castsi128_ps(_mm_loadl_epi64((__m128i*)v)))); }
      INLINE V2ls(const double x, const double y)   { store(_mm_cvttpd_epi64(_mm_set_pd(y, x)));                               }
      INLINE V2ls(const double s)                   { store(_mm_cvttpd_epi64(_mm_set1_pd(s)));                                 }
      INLINE V2ls(const double v[2])                { store(_mm_cvttpd_epi64(_mm_loadu_pd(v)));                                }
   #else
      INLINE V2ls(const float x, const float y)     { store(_mm_set_epi64x ((int64_t)y, (int64_t)x));                          }
      INLINE V2ls(const float s)                    { store(_mm_set1_epi64x((int64_t)s));                                      }
      INLINE V2ls(const float v[2])                 { store(_mm_set_epi64x ((int64_t)v[1], (int64_t)v[0]));                    }
      INLINE V2ls(const double x, const double y)   { store(_mm_set_epi64x ((int64_t)y, (int64_t)x));                          }
      INLINE V2ls(const double s)                   { store(_mm_set1_epi64x((int64_t)s));                                      }
      INLINE V2ls(const double v[2])                { store(_mm_set_epi64x ((int64_t)v[1], (int64_t)v[0]));                    }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      template<typename V> INLINE V2ls(const V2ft<V>& v) { store(_mm_cvttps_epi64(_mm_castsi128_ps(_mm_loadl_epi64((__m128i*)v.vals))));}
      template<typename V> INLINE V2ls(const V2dt<V>& v) { store(_mm_cvttpd_epi64(_mm_loadu_pd(v.vals)));                      }
   #else
      template<typename V> INLINE V2ls(const V2ft<V>& v) { store(_mm_set_epi64x((int64_t)v.y, (int64_t)v.x));                  }
      template<typename V> INLINE V2ls(const V2dt<V>& v) { store(_mm_set_epi64x((int64_t)v.y, (int64_t)v.x));                  }
   #endif
   #if defined(CPPCORE_CPUFEAT_SSE41)
      template<typename V> INLINE V2ls(const V2it<V>& v) { store(_mm_cvtepi32_epi64(_mm_loadl_epi64((__m128i*)v.vals)));       }
   #else
      template<typename V> INLINE V2ls(const V2it<V>& v) { store(_mm_set_epi64x((int64_t)v.y, (int64_t)v.x));                  }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE       void* operator new  (size_t size)         { return CPPCORE_ALIGNED_ALLOC(size, 16U);                         }
      INLINE       void* operator new[](size_t size)         { return CPPCORE_ALIGNED_ALLOC(size, 16U);                         }
      INLINE       void  operator delete   (void* ptr)       { return CPPCORE_ALIGNED_FREE(ptr);                                }
      INLINE       void  operator delete[] (void* ptr)       { return CPPCORE_ALIGNED_FREE(ptr);                                }
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      INLINE       bool  operator == (const V2ls&   v) const { return _mm_cmpeq_epi64_mask(load(), v.load()) == 0x03;           }
      INLINE       bool  operator != (const V2ls&   v) const { return _mm_cmpeq_epi64_mask(load(), v.load()) != 0x03;           }
      INLINE       bool  operator <  (const V2ls&   v) const { return _mm_cmplt_epi64_mask(load(), v.load()) == 0x03;           }
      INLINE       bool  operator <= (const V2ls&   v) const { return _mm_cmple_epi64_mask(load(), v.load()) == 0x03;           }
      INLINE       bool  operator >  (const V2ls&   v) const { return _mm_cmpgt_epi64_mask(load(), v.load()) == 0x03;           }
      INLINE       bool  operator >= (const V2ls&   v) const { return _mm_cmpge_epi64_mask(load(), v.load()) == 0x03;           }
   #elif defined(CPPCORE_CPUFEAT_SSE41)
      INLINE       bool  operator == (const V2ls&   v) const { return _mm_movemask_epi8(_mm_cmpeq_epi64(load(),v.load()))==0xFFFF;}
      INLINE       bool  operator != (const V2ls&   v) const { return _mm_movemask_epi8(_mm_cmpeq_epi64(load(),v.load()))!=0xFFFF;}
      INLINE       bool  operator >  (const V2ls&   v) const { return _mm_movemask_epi8(_mm_cmpgt_epi64(load(),v.load()))==0xFFFF;}
   #endif
      INLINE       V2ls  operator +  (const V2ls&   v) const { return V2ls(_mm_add_epi64(load(), v.load()));                    }
      INLINE       V2ls  operator +  (const int64_t s) const { return V2ls(_mm_add_epi64(load(), _mm_set1_epi64x(s)));          }
      INLINE       V2ls  operator -  (const V2ls&   v) const { return V2ls(_mm_sub_epi64(load(), v.load()));                    }
      INLINE       V2ls  operator -  (const int64_t s) const { return V2ls(_mm_sub_epi64(load(), _mm_set1_epi64x(s)));          }
      INLINE       V2ls  operator -  ()                const { return V2ls(_mm_sub_epi64(_mm_setzero_si128(), load()));         }
      INLINE const V2ls& operator +  ()                const { return *this;                                                    }
      INLINE       V2ls& operator =  (const V2ls&   v)       { store(v.load());                                   return *this; }
      INLINE       V2ls& operator += (const V2ls&   v)       { store(_mm_add_epi64(load(), v.load()));            return *this; }
      INLINE       V2ls& operator -= (const V2ls&   v)       { store(_mm_sub_epi64(load(), v.load()));            return *this; }
      INLINE       V2ls& operator =  (const int64_t s)       { store(_mm_set1_epi64x(s));                         return *this; }
      INLINE       V2ls& operator += (const int64_t s)       { store(_mm_add_epi64(load(), _mm_set1_epi64x(s)));  return *this; }
      INLINE       V2ls& operator -= (const int64_t s)       { store(_mm_sub_epi64(load(), _mm_set1_epi64x(s)));  return *this; }
   #if defined(CPPCORE_COMPILER_MSVC)
      INLINE       V2ls  operator /  (const V2ls&   v) const { return V2ls(_mm_div_epi64(load(), v.load()));                    }
      INLINE       V2ls  operator /  (const int64_t s) const { return V2ls(_mm_div_epi64(load(), _mm_set1_epi64x(s)));          }
      INLINE       V2ls& operator /= (const V2ls&   v)       { store(_mm_div_epi64(load(), v.load()));            return *this; }
      INLINE       V2ls& operator /= (const int64_t s)       { store(_mm_div_epi64(load(), _mm_set1_epi64x(s)));  return *this; }
   #endif
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      INLINE       V2ls  operator *  (const V2ls&   v) const { return V2ls(_mm_mullo_epi64(load(), v.load()));                  }
      INLINE       V2ls  operator *  (const int64_t s) const { return V2ls(_mm_mullo_epi64(load(), _mm_set1_epi64x(s)));        }
      INLINE       V2ls& operator *= (const V2ls&   v)       { store(_mm_mullo_epi64(load(), v.load()));          return *this; }
      INLINE       V2ls& operator *= (const int64_t s)       { store(_mm_mullo_epi64(load(), _mm_set1_epi64x(s)));return *this; }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
      INLINE void swap(V2ls& v)                                { __m128i t(load()); store(v.load()); v.store(t); }
   #if defined(CPPCORE_CPUFEAT_AVX512F)
      INLINE V2ls absC()                                 const { return V2ls(_mm_abs_epi64(load()));             }
      INLINE V2ls maxC(const V2ls& v)                    const { return V2ls(_mm_max_epi64(load(), v.load()));   }
      INLINE V2ls minC(const V2ls& v)                    const { return V2ls(_mm_min_epi64(load(), v.load()));   }
      INLINE void abs()                                        { store(_mm_abs_epi64(load()));                   }
      INLINE void max(const V2ls& v)                           { store(_mm_max_epi64(load(), v.load()));         }
      INLINE void min(const V2ls& v)                           { store(_mm_min_epi64(load(), v.load()));         }
   #endif
      //------------------------------------------------------------------------------------------------------------------------//
   };
#else
   typedef V2fg V2fs;
   typedef V2dg V2ds;
   typedef V2ig V2is;
   typedef V2lg V2ls;
#endif

   //------------------------------------------------------------------------------------------------------------------------//
   //------------------------------------------------------------------------------------------------------------------------//

#if defined(CPPCORE_CPUFEAT_SSE2) && defined(CPPCORE_OPTIMIZED_VECTORMATH)
   // use optimized ones as defaults
   typedef V2fs V2f;
   typedef V2ds V2d;
   typedef V2is V2i;
   typedef V2ls V2l;
#else
   // use generic ones as defaults
   typedef V2fg V2f;
   typedef V2dg V2d;
   typedef V2ig V2i;
   typedef V2lg V2l;
#endif
}
#pragma warning(default:26495)
