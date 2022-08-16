
#include "vectors.h"
#include <intrin.h>
#include <CppCore/Random.h>

//------------------------------------------------------------------------------------------------------------------------//
//using namespace simd;
using namespace CppCore;
using namespace std::chrono;
using namespace std;
//------------------------------------------------------------------------------------------------------------------------//
#define LOOPS 50000
#define LOOP(n, x) for (size_t i = 0; i < n; i++) { x }
#define PRINTHEADER                                               \
  printf("-----------------------------------------------------------------------------------------------------------\n"); \
  printf("CLS  |  OPERATION   |    TIME    |        VAL      || CLS  |  OPERATION   |    TIME    |        VAL      ||\n"); \
  printf("-----------------------------------------------------------------------------------------------------------\n");
//------------------------------------------------------------------------------------------------------------------------//
high_resolution_clock clk;
//------------------------------------------------------------------------------------------------------------------------//
template<typename T>
void bench(const char* name, const char* op, void task(T* ARR))
{
   T ARR[LOOPS];
   Random::Default32 rnd;
   assert(sizeof(ARR) % 4 == 0);
   rnd.fill((uint32_t*)ARR, sizeof(ARR) / 4);
   auto t1 = __rdtsc();
   task(ARR);
   auto t2 = __rdtsc();
   auto sp = t2 - t1;
   T s = T::ZERO(); for (size_t i = 0; i < LOOPS; i++) s += ARR[i];
   printf(name); printf(" | "); printf(op); printf("%010I64i | ", sp); printf("%+015.7f || ", s.x + s.y);
}
//------------------------------------------------------------------------------------------------------------------------//
template<typename T>
void benchInt(const char* name, const char* op, void task(T* ARR))
{
   T ARR[LOOPS];
   Random::Default32 rnd;
   assert(sizeof(ARR) % 4 == 0);
   rnd.fill((uint32_t*)ARR, sizeof(ARR) / 4);
   auto t1 = __rdtsc();
   task(ARR);
   auto t2 = __rdtsc();
   auto sp = t2 - t1;
   T s = T::ZERO(); for (size_t i = 0; i < LOOPS; i++) s += ARR[i];
   printf(name); printf(" | "); printf(op); printf("%010I64i | ", sp); printf("%+015.7i || ", s.x + s.y);
}
//------------------------------------------------------------------------------------------------------------------------//
template<typename T, typename F> void benchEqV(T* ARR)       { LOOP(LOOPS - 1, ARR[i].x = (F)(ARR[i] == ARR[i + 1]);)  }
template<typename T, typename F> void benchNeqV(T* ARR)      { LOOP(LOOPS - 1, ARR[i].x = (F)(ARR[i] != ARR[i + 1]);)  }
template<typename T, typename F> void benchLtV(T* ARR)       { LOOP(LOOPS - 1, ARR[i].x = (F)(ARR[i] < ARR[i + 1]);)   }
template<typename T, typename F> void benchLeV(T* ARR)       { LOOP(LOOPS - 1, ARR[i].x = (F)(ARR[i] <= ARR[i + 1]);)  }
template<typename T, typename F> void benchGtV(T* ARR)       { LOOP(LOOPS - 1, ARR[i].x = (F)(ARR[i] > ARR[i + 1]);)   }
template<typename T, typename F> void benchGeV(T* ARR)       { LOOP(LOOPS - 1, ARR[i].x = (F)(ARR[i] >= ARR[i + 1]);)  }
template<typename T, typename F> void benchAddV(T* ARR)      { LOOP(LOOPS - 1, ARR[i] = ARR[i] + ARR[i + 1];)        }
template<typename T, typename F> void benchSubV(T* ARR)      { LOOP(LOOPS - 1, ARR[i] = ARR[i] - ARR[i + 1];)        }
template<typename T, typename F> void benchMulV(T* ARR)      { LOOP(LOOPS - 1, ARR[i] = ARR[i] * ARR[i + 1];)        }
template<typename T, typename F> void benchDivV(T* ARR)      { LOOP(LOOPS - 1, ARR[i] = ARR[i] / ARR[i + 1];)        }
template<typename T, typename F> void benchAddS(T* ARR)      { LOOP(LOOPS - 1, ARR[i] = ARR[i] + ARR[i + 1].x;)      }
template<typename T, typename F> void benchSubS(T* ARR)      { LOOP(LOOPS - 1, ARR[i] = ARR[i] - ARR[i + 1].x;)      }
template<typename T, typename F> void benchMulS(T* ARR)      { LOOP(LOOPS - 1, ARR[i] = ARR[i] * ARR[i + 1].x;)      }
template<typename T, typename F> void benchDivS(T* ARR)      { LOOP(LOOPS - 1, ARR[i] = ARR[i] / ARR[i + 1].x;)      }
template<typename T, typename F> void benchMadd(T* ARR)      { LOOP(LOOPS - 2, ARR[i].madd(ARR[i + 1], ARR[i + 2]);) }
template<typename T, typename F> void benchIsZero(T* ARR)    { LOOP(LOOPS, ARR[i].x = (F)ARR[i].isZero();)           }
template<typename T, typename F> void benchIsZeroE(T* ARR)   { LOOP(LOOPS, ARR[i].x = (F)ARR[i].isZero((F)0.01);)    }
template<typename T, typename F> void benchRotate(T* ARR)    { LOOP(LOOPS, ARR[i].rotate((F)M_PI_2);)                }
template<typename T, typename F> void benchLength(T* ARR)    { LOOP(LOOPS, ARR[i].x = ARR[i].length();)              }
template<typename T, typename F> void benchLength2(T* ARR)   { LOOP(LOOPS, ARR[i].x = ARR[i].length2();)             }
template<typename T, typename F> void benchNormalise(T* ARR) { LOOP(LOOPS, ARR[i].normalise();)                      }
template<typename T, typename F> void benchScaleTo(T* ARR)   { LOOP(LOOPS, ARR[i].scaleTo((F)15.2);)                 }
template<typename T, typename F> void benchRound(T* ARR)     { LOOP(LOOPS, ARR[i].round();)                          }
template<typename T, typename F> void benchRoundF(T* ARR)    { LOOP(LOOPS, ARR[i].round((F)4.0);)                    }
template<typename T, typename F> void benchFloor(T* ARR)     { LOOP(LOOPS, ARR[i].floor();)                          }
template<typename T, typename F> void benchCeil(T* ARR)      { LOOP(LOOPS, ARR[i].ceil();)                           }
template<typename T, typename F> void benchAbs(T* ARR)       { LOOP(LOOPS, ARR[i].abs();)                            }
template<typename T, typename F> void benchSwap(T* ARR)      { LOOP(LOOPS - 1, ARR[i].swap(ARR[i + 1]);)             }
template<typename T, typename F> void benchDot(T* ARR)       { LOOP(LOOPS - 2, ARR[i].x = ARR[i+1].dot(ARR[i + 2]);)   }
template<typename T, typename F> void benchCross(T* ARR)     { LOOP(LOOPS - 1, ARR[i].x = ARR[i].cross(ARR[i + 1]);) }
template<typename T, typename F> void benchCrossV3(T* ARR)   { LOOP(LOOPS - 2, ARR[i] = ARR[i+1].cross(ARR[i + 2]);) }
template<typename T, typename F> void benchMax(T* ARR)       { LOOP(LOOPS - 1, ARR[i].max(ARR[i + 1]);)              }
template<typename T, typename F> void benchMin(T* ARR)       { LOOP(LOOPS - 1, ARR[i].min(ARR[i + 1]);)              }
template<typename T, typename F> void benchBound(T* ARR)     { LOOP(LOOPS - 2, ARR[i].bound(ARR[i + 1], ARR[i + 2]);) }
template<typename T, typename F> void benchSide(T* ARR)      { LOOP(LOOPS - 2, ARR[i].x = ARR[i].side(ARR[i + 1], ARR[i + 2]);)                    }
template<typename T, typename F> void benchInsideR(T* ARR)   { LOOP(LOOPS - 2, ARR[i].x = (F)ARR[i].inside(ARR[i + 1], ARR[i + 2]);)          }
template<typename T, typename F> void benchInsideRE(T* ARR)  { LOOP(LOOPS - 2, ARR[i].x = (F)ARR[i].inside(ARR[i + 1], ARR[i + 2], (F)0.001);)   }
template<typename T, typename F> void benchInsideC(T* ARR)   { LOOP(LOOPS - 2, ARR[i].x = (F)ARR[i].inside(ARR[i + 1], ARR[i + 2].x);)        }
template<typename T, typename F> void benchInsideCE(T* ARR)  { LOOP(LOOPS - 2, ARR[i].x = (F)ARR[i].inside(ARR[i + 1], ARR[i + 2].x, (F)0.001);) }
template<typename T, typename F> void benchAreaTri(T* ARR)   { LOOP(LOOPS - 2, ARR[i].x = ARR[i].area(ARR[i + 1], ARR[i + 2]);)                    }
template<typename T, typename F> void benchAngle(T* ARR)     { LOOP(LOOPS, ARR[i].x = ARR[i].angle();)                                             }
template<typename T, typename F> void benchAngleV(T* ARR)    { LOOP(LOOPS - 1, ARR[i].x = ARR[i].angle(ARR[i + 1]);)                               }
template<typename T, typename T2, typename F> void benchRunV2(const char* name, const char* nameT2)
{
   PRINTHEADER;
   bench<T>(name, "operator ==v | ", benchLtV<T, F>);       bench<T2>(nameT2, "operator ==v | ", benchLtV<T2, F>);       printf("\n");
   bench<T>(name, "operator !=v | ", benchLtV<T, F>);       bench<T2>(nameT2, "operator !=v | ", benchLtV<T2, F>);       printf("\n");
   bench<T>(name, "operator < v | ", benchLtV<T, F>);       bench<T2>(nameT2, "operator < v | ", benchLtV<T2, F>);       printf("\n");
   bench<T>(name, "operator <=v | ", benchLeV<T, F>);       bench<T2>(nameT2, "operator <=v | ", benchLeV<T2, F>);       printf("\n");
   bench<T>(name, "operator > v | ", benchGtV<T, F>);       bench<T2>(nameT2, "operator > v | ", benchGtV<T2, F>);       printf("\n");
   bench<T>(name, "operator >=v | ", benchGeV<T, F>);       bench<T2>(nameT2, "operator >=v | ", benchGeV<T2, F>);       printf("\n");
   bench<T>(name, "operator + v | ", benchAddV<T, F>);      bench<T2>(nameT2, "operator + v | ", benchAddV<T2, F>);      printf("\n");
   bench<T>(name, "operator - v | ", benchSubV<T, F>);      bench<T2>(nameT2, "operator - v | ", benchSubV<T2, F>);      printf("\n");
   bench<T>(name, "operator * v | ", benchMulV<T, F>);      bench<T2>(nameT2, "operator * v | ", benchMulV<T2, F>);      printf("\n");
   bench<T>(name, "operator / v | ", benchDivV<T, F>);      bench<T2>(nameT2, "operator / v | ", benchDivV<T2, F>);      printf("\n");
   bench<T>(name, "operator + s | ", benchAddS<T, F>);      bench<T2>(nameT2, "operator + s | ", benchAddS<T2, F>);      printf("\n");
   bench<T>(name, "operator - s | ", benchSubS<T, F>);      bench<T2>(nameT2, "operator - s | ", benchSubS<T2, F>);      printf("\n");
   bench<T>(name, "operator * s | ", benchMulS<T, F>);      bench<T2>(nameT2, "operator * s | ", benchMulS<T2, F>);      printf("\n");
   bench<T>(name, "operator / s | ", benchDivS<T, F>);      bench<T2>(nameT2, "operator / s | ", benchDivS<T2, F>);      printf("\n");
   bench<T>(name, "madd()       | ", benchMadd<T, F>);      bench<T2>(nameT2, "madd()       | ", benchMadd<T2, F>);      printf("\n");
   bench<T>(name, "isZero()     | ", benchIsZero<T, F>);    bench<T2>(nameT2, "isZero()     | ", benchIsZero<T2, F>);    printf("\n");
   bench<T>(name, "isZero(e)    | ", benchIsZeroE<T, F>);   bench<T2>(nameT2, "isZero(e)    | ", benchIsZeroE<T2, F>);   printf("\n");
   bench<T>(name, "length()     | ", benchLength<T, F>);    bench<T2>(nameT2, "length()     | ", benchLength<T2, F>);    printf("\n");
   bench<T>(name, "length2()    | ", benchLength2<T, F>);   bench<T2>(nameT2, "length2()    | ", benchLength2<T2, F>);   printf("\n");
   bench<T>(name, "abs()        | ", benchAbs<T, F>);       bench<T2>(nameT2, "abs()        | ", benchAbs<T2, F>);       printf("\n");
   bench<T>(name, "swap()       | ", benchSwap<T, F>);      bench<T2>(nameT2, "swap()       | ", benchSwap<T2, F>);      printf("\n");
   bench<T>(name, "dot()        | ", benchDot<T, F>);       bench<T2>(nameT2, "dot()        | ", benchDot<T2, F>);       printf("\n");
   bench<T>(name, "cross()      | ", benchCross<T, F>);     bench<T2>(nameT2, "cross()      | ", benchCross<T2, F>);     printf("\n");
   bench<T>(name, "max()        | ", benchMax<T, F>);       bench<T2>(nameT2, "max()        | ", benchMax<T2, F>);       printf("\n");
   bench<T>(name, "min()        | ", benchMin<T, F>);       bench<T2>(nameT2, "min()        | ", benchMin<T2, F>);       printf("\n");
   bench<T>(name, "bound()      | ", benchBound<T, F>);     bench<T2>(nameT2, "bound()      | ", benchBound<T2, F>);     printf("\n");
   bench<T>(name, "side(v,v)    | ", benchSide<T, F>);      bench<T2>(nameT2, "side(v,v)    | ", benchSide<T2, F>);      printf("\n");
   bench<T>(name, "inside(v,v)  | ", benchInsideR<T, F>);   bench<T2>(nameT2, "inside(v,v)  | ", benchInsideR<T2, F>);   printf("\n");
   bench<T>(name, "inside(v,v,e)| ", benchInsideRE<T, F>);  bench<T2>(nameT2, "inside(v,v,e)| ", benchInsideRE<T2, F>);  printf("\n");
   bench<T>(name, "inside(m,r)  | ", benchInsideC<T, F>);   bench<T2>(nameT2, "inside(m,r)  | ", benchInsideC<T2, F>);   printf("\n");
   bench<T>(name, "inside(m,r,e)| ", benchInsideCE<T, F>);  bench<T2>(nameT2, "inside(m,r,e)| ", benchInsideCE<T2, F>);  printf("\n");
   // fp
   bench<T>(name, "rotate()     | ", benchRotate<T, F>);    bench<T2>(nameT2, "rotate()     | ", benchRotate<T2, F>);    printf("\n");
   bench<T>(name, "normalise()  | ", benchNormalise<T, F>); bench<T2>(nameT2, "normalise()  | ", benchNormalise<T2, F>); printf("\n");
   bench<T>(name, "scaleTo()    | ", benchScaleTo<T, F>);   bench<T2>(nameT2, "scaleTo()    | ", benchScaleTo<T2, F>);   printf("\n");
   bench<T>(name, "round()      | ", benchRound<T, F>);     bench<T2>(nameT2, "round()      | ", benchRound<T2, F>);     printf("\n");
   bench<T>(name, "round(F)     | ", benchRoundF<T, F>);    bench<T2>(nameT2, "round(F)     | ", benchRoundF<T2, F>);    printf("\n");
   bench<T>(name, "floor()      | ", benchFloor<T, F>);     bench<T2>(nameT2, "floor()      | ", benchFloor<T2, F>);     printf("\n");
   bench<T>(name, "ceil()       | ", benchCeil<T, F>);      bench<T2>(nameT2, "ceil()       | ", benchCeil<T2, F>);      printf("\n");
   bench<T>(name, "area(v,v)    | ", benchAreaTri<T, F>);   bench<T2>(nameT2, "area(v,v)    | ", benchAreaTri<T2, F>);   printf("\n");
   bench<T>(name, "angle()      | ", benchAngle<T, F>);     bench<T2>(nameT2, "angle()      | ", benchAngle<T2, F>);     printf("\n");
   bench<T>(name, "angle(v)     | ", benchAngleV<T, F>);    bench<T2>(nameT2, "angle(v)     | ", benchAngleV<T2, F>);    printf("\n");
}
template<typename T, typename T2, typename F> void benchRunV2Int(const char* name, const char* nameT2)
{
   PRINTHEADER;
   benchInt<T>(name, "operator ==v | ", benchLtV<T, F>);       benchInt<T2>(nameT2, "operator ==v | ", benchLtV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator !=v | ", benchLtV<T, F>);       benchInt<T2>(nameT2, "operator !=v | ", benchLtV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator < v | ", benchLtV<T, F>);       benchInt<T2>(nameT2, "operator < v | ", benchLtV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator <=v | ", benchLeV<T, F>);       benchInt<T2>(nameT2, "operator <=v | ", benchLeV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator > v | ", benchGtV<T, F>);       benchInt<T2>(nameT2, "operator > v | ", benchGtV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator >=v | ", benchGeV<T, F>);       benchInt<T2>(nameT2, "operator >=v | ", benchGeV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator + v | ", benchAddV<T, F>);      benchInt<T2>(nameT2, "operator + v | ", benchAddV<T2, F>);      printf("\n");
   benchInt<T>(name, "operator - v | ", benchSubV<T, F>);      benchInt<T2>(nameT2, "operator - v | ", benchSubV<T2, F>);      printf("\n");
   benchInt<T>(name, "operator * v | ", benchMulV<T, F>);      benchInt<T2>(nameT2, "operator * v | ", benchMulV<T2, F>);      printf("\n");
   //benchInt<T>(name, "operator / v | ", benchDivV<T, F>);      benchInt<T2>(nameT2, "operator / v | ", benchDivV<T2, F>);      printf("\n");
   benchInt<T>(name, "operator + s | ", benchAddS<T, F>);      benchInt<T2>(nameT2, "operator + s | ", benchAddS<T2, F>);      printf("\n");
   benchInt<T>(name, "operator - s | ", benchSubS<T, F>);      benchInt<T2>(nameT2, "operator - s | ", benchSubS<T2, F>);      printf("\n");
   benchInt<T>(name, "operator * s | ", benchMulS<T, F>);      benchInt<T2>(nameT2, "operator * s | ", benchMulS<T2, F>);      printf("\n");
   //benchInt<T>(name, "operator / s | ", benchDivS<T, F>);      benchInt<T2>(nameT2, "operator / s | ", benchDivS<T2, F>);      printf("\n");
   //benchInt<T>(name, "madd()       | ", benchMadd<T, F>);      benchInt<T2>(nameT2, "madd()       | ", benchMadd<T2, F>);      printf("\n");
   benchInt<T>(name, "isZero()     | ", benchIsZero<T, F>);    benchInt<T2>(nameT2, "isZero()     | ", benchIsZero<T2, F>);    printf("\n");
   benchInt<T>(name, "isZero(e)    | ", benchIsZeroE<T, F>);   benchInt<T2>(nameT2, "isZero(e)    | ", benchIsZeroE<T2, F>);   printf("\n");
   benchInt<T>(name, "length()     | ", benchLength<T, F>);    benchInt<T2>(nameT2, "length()     | ", benchLength<T2, F>);    printf("\n");
   benchInt<T>(name, "length2()    | ", benchLength2<T, F>);   benchInt<T2>(nameT2, "length2()    | ", benchLength2<T2, F>);   printf("\n");
   benchInt<T>(name, "abs()        | ", benchAbs<T, F>);       benchInt<T2>(nameT2, "abs()        | ", benchAbs<T2, F>);       printf("\n");
   benchInt<T>(name, "swap()       | ", benchSwap<T, F>);      benchInt<T2>(nameT2, "swap()       | ", benchSwap<T2, F>);      printf("\n");
   benchInt<T>(name, "dot()        | ", benchDot<T, F>);       benchInt<T2>(nameT2, "dot()        | ", benchDot<T2, F>);       printf("\n");
   benchInt<T>(name, "cross()      | ", benchCross<T, F>);     benchInt<T2>(nameT2, "cross()      | ", benchCross<T2, F>);     printf("\n");
   benchInt<T>(name, "max()        | ", benchMax<T, F>);       benchInt<T2>(nameT2, "max()        | ", benchMax<T2, F>);       printf("\n");
   benchInt<T>(name, "min()        | ", benchMin<T, F>);       benchInt<T2>(nameT2, "min()        | ", benchMin<T2, F>);       printf("\n");
   benchInt<T>(name, "bound()      | ", benchBound<T, F>);     benchInt<T2>(nameT2, "bound()      | ", benchBound<T2, F>);     printf("\n");
   benchInt<T>(name, "side(v,v)    | ", benchSide<T, F>);      benchInt<T2>(nameT2, "side(v,v)    | ", benchSide<T2, F>);      printf("\n");
   benchInt<T>(name, "inside(v,v)  | ", benchInsideR<T, F>);   benchInt<T2>(nameT2, "inside(v,v)  | ", benchInsideR<T2, F>);   printf("\n");
   benchInt<T>(name, "inside(v,v,e)| ", benchInsideRE<T, F>);  benchInt<T2>(nameT2, "inside(v,v,e)| ", benchInsideRE<T2, F>);  printf("\n");
   benchInt<T>(name, "inside(m,r)  | ", benchInsideC<T, F>);   benchInt<T2>(nameT2, "inside(m,r)  | ", benchInsideC<T2, F>);   printf("\n");
   benchInt<T>(name, "inside(m,r,e)| ", benchInsideCE<T, F>);  benchInt<T2>(nameT2, "inside(m,r,e)| ", benchInsideCE<T2, F>);  printf("\n");
}
template<typename T, typename T2, typename F> void benchRunV3(const char* name, const char* nameT2)
{
   PRINTHEADER;
   bench<T>(name, "operator ==v | ", benchLtV<T, F>);       bench<T2>(nameT2, "operator ==v | ", benchLtV<T2, F>);       printf("\n");
   bench<T>(name, "operator !=v | ", benchLtV<T, F>);       bench<T2>(nameT2, "operator !=v | ", benchLtV<T2, F>);       printf("\n");
   bench<T>(name, "operator < v | ", benchLtV<T, F>);       bench<T2>(nameT2, "operator < v | ", benchLtV<T2, F>);       printf("\n");
   bench<T>(name, "operator <=v | ", benchLeV<T, F>);       bench<T2>(nameT2, "operator <=v | ", benchLeV<T2, F>);       printf("\n");
   bench<T>(name, "operator > v | ", benchGtV<T, F>);       bench<T2>(nameT2, "operator > v | ", benchGtV<T2, F>);       printf("\n");
   bench<T>(name, "operator >=v | ", benchGeV<T, F>);       bench<T2>(nameT2, "operator >=v | ", benchGeV<T2, F>);       printf("\n");
   bench<T>(name, "operator + v | ", benchAddV<T, F>);      bench<T2>(nameT2, "operator + v | ", benchAddV<T2, F>);      printf("\n");
   bench<T>(name, "operator - v | ", benchSubV<T, F>);      bench<T2>(nameT2, "operator - v | ", benchSubV<T2, F>);      printf("\n");
   bench<T>(name, "operator * v | ", benchMulV<T, F>);      bench<T2>(nameT2, "operator * v | ", benchMulV<T2, F>);      printf("\n");
   bench<T>(name, "operator / v | ", benchDivV<T, F>);      bench<T2>(nameT2, "operator / v | ", benchDivV<T2, F>);      printf("\n");
   bench<T>(name, "operator + s | ", benchAddS<T, F>);      bench<T2>(nameT2, "operator + s | ", benchAddS<T2, F>);      printf("\n");
   bench<T>(name, "operator - s | ", benchSubS<T, F>);      bench<T2>(nameT2, "operator - s | ", benchSubS<T2, F>);      printf("\n");
   bench<T>(name, "operator * s | ", benchMulS<T, F>);      bench<T2>(nameT2, "operator * s | ", benchMulS<T2, F>);      printf("\n");
   bench<T>(name, "operator / s | ", benchDivS<T, F>);      bench<T2>(nameT2, "operator / s | ", benchDivS<T2, F>);      printf("\n");
   bench<T>(name, "madd()       | ", benchMadd<T, F>);      bench<T2>(nameT2, "madd()       | ", benchMadd<T2, F>);      printf("\n");
   bench<T>(name, "isZero()     | ", benchIsZero<T, F>);    bench<T2>(nameT2, "isZero()     | ", benchIsZero<T2, F>);    printf("\n");
   bench<T>(name, "isZero(e)    | ", benchIsZeroE<T, F>);   bench<T2>(nameT2, "isZero(e)    | ", benchIsZeroE<T2, F>);   printf("\n");
   bench<T>(name, "length()     | ", benchLength<T, F>);    bench<T2>(nameT2, "length()     | ", benchLength<T2, F>);    printf("\n");
   bench<T>(name, "length2()    | ", benchLength2<T, F>);   bench<T2>(nameT2, "length2()    | ", benchLength2<T2, F>);   printf("\n");
   bench<T>(name, "abs()        | ", benchAbs<T, F>);       bench<T2>(nameT2, "abs()        | ", benchAbs<T2, F>);       printf("\n");
   bench<T>(name, "swap()       | ", benchSwap<T, F>);      bench<T2>(nameT2, "swap()       | ", benchSwap<T2, F>);      printf("\n");
   bench<T>(name, "dot()        | ", benchDot<T, F>);       bench<T2>(nameT2, "dot()        | ", benchDot<T2, F>);       printf("\n");
   bench<T>(name, "cross()      | ", benchCrossV3<T, F>);   bench<T2>(nameT2, "cross()      | ", benchCrossV3<T2, F>);   printf("\n");
   bench<T>(name, "max()        | ", benchMax<T, F>);       bench<T2>(nameT2, "max()        | ", benchMax<T2, F>);       printf("\n");
   bench<T>(name, "min()        | ", benchMin<T, F>);       bench<T2>(nameT2, "min()        | ", benchMin<T2, F>);       printf("\n");
   bench<T>(name, "bound()      | ", benchBound<T, F>);     bench<T2>(nameT2, "bound()      | ", benchBound<T2, F>);     printf("\n");
   //bench<T>(name, "bound()      | ", benchBound<T, F>);     bench<T2>(nameT2, "bound()      | ", benchBound<T2, F>);     printf("\n");

   /*bench<T>(name, "side(v,v)    | ", benchSide<T, F>);      bench<T2>(nameT2, "side(v,v)    | ", benchSide<T2, F>);      printf("\n");
   bench<T>(name, "inside(v,v)  | ", benchInsideR<T, F>);   bench<T2>(nameT2, "inside(v,v)  | ", benchInsideR<T2, F>);   printf("\n");
   bench<T>(name, "inside(v,v,e)| ", benchInsideRE<T, F>);  bench<T2>(nameT2, "inside(v,v,e)| ", benchInsideRE<T2, F>);  printf("\n");
   bench<T>(name, "inside(m,r)  | ", benchInsideC<T, F>);   bench<T2>(nameT2, "inside(m,r)  | ", benchInsideC<T2, F>);   printf("\n");
   bench<T>(name, "inside(m,r,e)| ", benchInsideCE<T, F>);  bench<T2>(nameT2, "inside(m,r,e)| ", benchInsideCE<T2, F>);  printf("\n");*/
   // fp
   //bench<T>(name, "rotate()     | ", benchRotate<T, F>);    bench<T2>(nameT2, "rotate()     | ", benchRotate<T2, F>);    printf("\n");
   bench<T>(name, "normalise()  | ", benchNormalise<T, F>); bench<T2>(nameT2, "normalise()  | ", benchNormalise<T2, F>); printf("\n");
   bench<T>(name, "round()      | ", benchRound<T, F>);     bench<T2>(nameT2, "round()      | ", benchRound<T2, F>);     printf("\n");
   bench<T>(name, "round(F)     | ", benchRoundF<T, F>);    bench<T2>(nameT2, "round(F)     | ", benchRoundF<T2, F>);    printf("\n");
   bench<T>(name, "floor()      | ", benchFloor<T, F>);     bench<T2>(nameT2, "floor()      | ", benchFloor<T2, F>);     printf("\n");
   bench<T>(name, "ceil()       | ", benchCeil<T, F>);      bench<T2>(nameT2, "ceil()       | ", benchCeil<T2, F>);      printf("\n");
   /*bench<T>(name, "area(v,v)    | ", benchAreaTri<T, F>);   bench<T2>(nameT2, "area(v,v)    | ", benchAreaTri<T2, F>);   printf("\n");
   bench<T>(name, "angle()      | ", benchAngle<T, F>);     bench<T2>(nameT2, "angle()      | ", benchAngle<T2, F>);     printf("\n");
   bench<T>(name, "angle(v)     | ", benchAngleV<T, F>);    bench<T2>(nameT2, "angle(v)     | ", benchAngleV<T2, F>);    printf("\n");*/
}
template<typename T, typename T2, typename F> void benchRunV4(const char* name, const char* nameT2)
{
   PRINTHEADER;
   bench<T>(name, "operator ==v | ", benchLtV<T, F>);       bench<T2>(nameT2, "operator ==v | ", benchLtV<T2, F>);       printf("\n");
   bench<T>(name, "operator !=v | ", benchLtV<T, F>);       bench<T2>(nameT2, "operator !=v | ", benchLtV<T2, F>);       printf("\n");
   bench<T>(name, "operator < v | ", benchLtV<T, F>);       bench<T2>(nameT2, "operator < v | ", benchLtV<T2, F>);       printf("\n");
   bench<T>(name, "operator <=v | ", benchLeV<T, F>);       bench<T2>(nameT2, "operator <=v | ", benchLeV<T2, F>);       printf("\n");
   bench<T>(name, "operator > v | ", benchGtV<T, F>);       bench<T2>(nameT2, "operator > v | ", benchGtV<T2, F>);       printf("\n");
   bench<T>(name, "operator >=v | ", benchGeV<T, F>);       bench<T2>(nameT2, "operator >=v | ", benchGeV<T2, F>);       printf("\n");
   bench<T>(name, "operator + v | ", benchAddV<T, F>);      bench<T2>(nameT2, "operator + v | ", benchAddV<T2, F>);      printf("\n");
   bench<T>(name, "operator - v | ", benchSubV<T, F>);      bench<T2>(nameT2, "operator - v | ", benchSubV<T2, F>);      printf("\n");
   bench<T>(name, "operator * v | ", benchMulV<T, F>);      bench<T2>(nameT2, "operator * v | ", benchMulV<T2, F>);      printf("\n");
   bench<T>(name, "operator / v | ", benchDivV<T, F>);      bench<T2>(nameT2, "operator / v | ", benchDivV<T2, F>);      printf("\n");
   bench<T>(name, "operator + s | ", benchAddS<T, F>);      bench<T2>(nameT2, "operator + s | ", benchAddS<T2, F>);      printf("\n");
   bench<T>(name, "operator - s | ", benchSubS<T, F>);      bench<T2>(nameT2, "operator - s | ", benchSubS<T2, F>);      printf("\n");
   bench<T>(name, "operator * s | ", benchMulS<T, F>);      bench<T2>(nameT2, "operator * s | ", benchMulS<T2, F>);      printf("\n");
   bench<T>(name, "operator / s | ", benchDivS<T, F>);      bench<T2>(nameT2, "operator / s | ", benchDivS<T2, F>);      printf("\n");
   bench<T>(name, "madd()       | ", benchMadd<T, F>);      bench<T2>(nameT2, "madd()       | ", benchMadd<T2, F>);      printf("\n");
   bench<T>(name, "isZero()     | ", benchIsZero<T, F>);    bench<T2>(nameT2, "isZero()     | ", benchIsZero<T2, F>);    printf("\n");
   bench<T>(name, "isZero(e)    | ", benchIsZeroE<T, F>);   bench<T2>(nameT2, "isZero(e)    | ", benchIsZeroE<T2, F>);   printf("\n");
   bench<T>(name, "length()     | ", benchLength<T, F>);    bench<T2>(nameT2, "length()     | ", benchLength<T2, F>);    printf("\n");
   bench<T>(name, "length2()    | ", benchLength2<T, F>);   bench<T2>(nameT2, "length2()    | ", benchLength2<T2, F>);   printf("\n");
   bench<T>(name, "abs()        | ", benchAbs<T, F>);       bench<T2>(nameT2, "abs()        | ", benchAbs<T2, F>);       printf("\n");
   bench<T>(name, "swap()       | ", benchSwap<T, F>);      bench<T2>(nameT2, "swap()       | ", benchSwap<T2, F>);      printf("\n");
   bench<T>(name, "dot()        | ", benchDot<T, F>);       bench<T2>(nameT2, "dot()        | ", benchDot<T2, F>);       printf("\n");
   //bench<T>(name, "cross()      | ", benchCrossV3<T, F>);   bench<T2>(nameT2, "cross()      | ", benchCrossV3<T2, F>);   printf("\n");
   bench<T>(name, "max()        | ", benchMax<T, F>);       bench<T2>(nameT2, "max()        | ", benchMax<T2, F>);       printf("\n");
   bench<T>(name, "min()        | ", benchMin<T, F>);       bench<T2>(nameT2, "min()        | ", benchMin<T2, F>);       printf("\n");
   bench<T>(name, "bound()      | ", benchBound<T, F>);     bench<T2>(nameT2, "bound()      | ", benchBound<T2, F>);     printf("\n");
   //bench<T>(name, "bound()      | ", benchBound<T, F>);     bench<T2>(nameT2, "bound()      | ", benchBound<T2, F>);     printf("\n");

   /*bench<T>(name, "side(v,v)    | ", benchSide<T, F>);      bench<T2>(nameT2, "side(v,v)    | ", benchSide<T2, F>);      printf("\n");
   bench<T>(name, "inside(v,v)  | ", benchInsideR<T, F>);   bench<T2>(nameT2, "inside(v,v)  | ", benchInsideR<T2, F>);   printf("\n");
   bench<T>(name, "inside(v,v,e)| ", benchInsideRE<T, F>);  bench<T2>(nameT2, "inside(v,v,e)| ", benchInsideRE<T2, F>);  printf("\n");
   bench<T>(name, "inside(m,r)  | ", benchInsideC<T, F>);   bench<T2>(nameT2, "inside(m,r)  | ", benchInsideC<T2, F>);   printf("\n");
   bench<T>(name, "inside(m,r,e)| ", benchInsideCE<T, F>);  bench<T2>(nameT2, "inside(m,r,e)| ", benchInsideCE<T2, F>);  printf("\n");*/
   // fp
   //bench<T>(name, "rotate()     | ", benchRotate<T, F>);    bench<T2>(nameT2, "rotate()     | ", benchRotate<T2, F>);    printf("\n");
   bench<T>(name, "normalise()  | ", benchNormalise<T, F>); bench<T2>(nameT2, "normalise()  | ", benchNormalise<T2, F>); printf("\n");
   bench<T>(name, "round()      | ", benchRound<T, F>);     bench<T2>(nameT2, "round()      | ", benchRound<T2, F>);     printf("\n");
   bench<T>(name, "round(F)     | ", benchRoundF<T, F>);    bench<T2>(nameT2, "round(F)     | ", benchRoundF<T2, F>);    printf("\n");
   bench<T>(name, "floor()      | ", benchFloor<T, F>);     bench<T2>(nameT2, "floor()      | ", benchFloor<T2, F>);     printf("\n");
   bench<T>(name, "ceil()       | ", benchCeil<T, F>);      bench<T2>(nameT2, "ceil()       | ", benchCeil<T2, F>);      printf("\n");
   /*bench<T>(name, "area(v,v)    | ", benchAreaTri<T, F>);   bench<T2>(nameT2, "area(v,v)    | ", benchAreaTri<T2, F>);   printf("\n");
   bench<T>(name, "angle()      | ", benchAngle<T, F>);     bench<T2>(nameT2, "angle()      | ", benchAngle<T2, F>);     printf("\n");
   bench<T>(name, "angle(v)     | ", benchAngleV<T, F>);    bench<T2>(nameT2, "angle(v)     | ", benchAngleV<T2, F>);    printf("\n");*/
}
template<typename T, typename T2, typename F> void benchRunV4Int(const char* name, const char* nameT2)
{
   PRINTHEADER;
   benchInt<T>(name, "operator ==v | ", benchLtV<T, F>);       benchInt<T2>(nameT2, "operator ==v | ", benchLtV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator !=v | ", benchLtV<T, F>);       benchInt<T2>(nameT2, "operator !=v | ", benchLtV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator < v | ", benchLtV<T, F>);       benchInt<T2>(nameT2, "operator < v | ", benchLtV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator <=v | ", benchLeV<T, F>);       benchInt<T2>(nameT2, "operator <=v | ", benchLeV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator > v | ", benchGtV<T, F>);       benchInt<T2>(nameT2, "operator > v | ", benchGtV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator >=v | ", benchGeV<T, F>);       benchInt<T2>(nameT2, "operator >=v | ", benchGeV<T2, F>);       printf("\n");
   benchInt<T>(name, "operator + v | ", benchAddV<T, F>);      benchInt<T2>(nameT2, "operator + v | ", benchAddV<T2, F>);      printf("\n");
   benchInt<T>(name, "operator - v | ", benchSubV<T, F>);      benchInt<T2>(nameT2, "operator - v | ", benchSubV<T2, F>);      printf("\n");
   benchInt<T>(name, "operator * v | ", benchMulV<T, F>);      benchInt<T2>(nameT2, "operator * v | ", benchMulV<T2, F>);      printf("\n");
   //benchInt<T>(name, "operator / v | ", benchDivV<T, F>);      benchInt<T2>(nameT2, "operator / v | ", benchDivV<T2, F>);      printf("\n");
   benchInt<T>(name, "operator + s | ", benchAddS<T, F>);      benchInt<T2>(nameT2, "operator + s | ", benchAddS<T2, F>);      printf("\n");
   benchInt<T>(name, "operator - s | ", benchSubS<T, F>);      benchInt<T2>(nameT2, "operator - s | ", benchSubS<T2, F>);      printf("\n");
   benchInt<T>(name, "operator * s | ", benchMulS<T, F>);      benchInt<T2>(nameT2, "operator * s | ", benchMulS<T2, F>);      printf("\n");
   //benchInt<T>(name, "operator / s | ", benchDivS<T, F>);      benchInt<T2>(nameT2, "operator / s | ", benchDivS<T2, F>);      printf("\n");
   //benchInt<T>(name, "madd()       | ", benchMadd<T, F>);      benchInt<T2>(nameT2, "madd()       | ", benchMadd<T2, F>);      printf("\n");
   benchInt<T>(name, "isZero()     | ", benchIsZero<T, F>);    benchInt<T2>(nameT2, "isZero()     | ", benchIsZero<T2, F>);    printf("\n");
   benchInt<T>(name, "isZero(e)    | ", benchIsZeroE<T, F>);   benchInt<T2>(nameT2, "isZero(e)    | ", benchIsZeroE<T2, F>);   printf("\n");
   benchInt<T>(name, "length()     | ", benchLength<T, F>);    benchInt<T2>(nameT2, "length()     | ", benchLength<T2, F>);    printf("\n");
   benchInt<T>(name, "length2()    | ", benchLength2<T, F>);   benchInt<T2>(nameT2, "length2()    | ", benchLength2<T2, F>);   printf("\n");
   benchInt<T>(name, "abs()        | ", benchAbs<T, F>);       benchInt<T2>(nameT2, "abs()        | ", benchAbs<T2, F>);       printf("\n");
   benchInt<T>(name, "swap()       | ", benchSwap<T, F>);      benchInt<T2>(nameT2, "swap()       | ", benchSwap<T2, F>);      printf("\n");
   benchInt<T>(name, "dot()        | ", benchDot<T, F>);       benchInt<T2>(nameT2, "dot()        | ", benchDot<T2, F>);       printf("\n");
   //benchInt<T>(name, "cross()      | ", benchCross<T, F>);     benchInt<T2>(nameT2, "cross()      | ", benchCross<T2, F>);     printf("\n");
   benchInt<T>(name, "max()        | ", benchMax<T, F>);       benchInt<T2>(nameT2, "max()        | ", benchMax<T2, F>);       printf("\n");
   benchInt<T>(name, "min()        | ", benchMin<T, F>);       benchInt<T2>(nameT2, "min()        | ", benchMin<T2, F>);       printf("\n");
   benchInt<T>(name, "bound()      | ", benchBound<T, F>);     benchInt<T2>(nameT2, "bound()      | ", benchBound<T2, F>);     printf("\n");
   //benchInt<T>(name, "side(v,v)    | ", benchSide<T, F>);      benchInt<T2>(nameT2, "side(v,v)    | ", benchSide<T2, F>);      printf("\n");
   //benchInt<T>(name, "inside(v,v)  | ", benchInsideR<T, F>);   benchInt<T2>(nameT2, "inside(v,v)  | ", benchInsideR<T2, F>);   printf("\n");
   //benchInt<T>(name, "inside(v,v,e)| ", benchInsideRE<T, F>);  benchInt<T2>(nameT2, "inside(v,v,e)| ", benchInsideRE<T2, F>);  printf("\n");
   //benchInt<T>(name, "inside(m,r)  | ", benchInsideC<T, F>);   benchInt<T2>(nameT2, "inside(m,r)  | ", benchInsideC<T2, F>);   printf("\n");
   //benchInt<T>(name, "inside(m,r,e)| ", benchInsideCE<T, F>);  benchInt<T2>(nameT2, "inside(m,r,e)| ", benchInsideCE<T2, F>);  printf("\n");
}
//------------------------------------------------------------------------------------------------------------------------//

#if defined(CPPCORE_CPUFEAT_SSE2)
void BenchV2f() { benchRunV2<V2fg, V2fs, float>("V2fg", "V2fs");       }
void BenchV2d() { benchRunV2<V2dg, V2ds, double>("V2dg", "V2ds");      }
void BenchV2i() { benchRunV2Int<V2ig, V2is, int>("V2ig", "V2is");      }
void BenchV2l() { benchRunV2Int<V2lg, V2ls, uint64_t>("V2lg", "V2ls"); }
#else
void BenchV2f() { benchRunV2<V2fg, V2fg, float>("V2fg", "V2fg");       }
void BenchV2d() { benchRunV2<V2dg, V2dg, double>("V2dg", "V2dg");      }
void BenchV2i() { benchRunV2Int<V2ig, V2ig, int>("V2ig", "V2ig");      }
void BenchV2l() { benchRunV2Int<V2lg, V2lg, uint64_t>("V2lg", "V2lg"); }
#endif

#if defined(CPPCORE_CPUFEAT_SSE2)
void BenchV3f() { benchRunV3<V3fg, V3fs, float>("V3fg", "V3fs");  }
void BenchV3d() { benchRunV3<V3dg, V3ds, double>("V3dg", "V3ds"); }
void BenchV3i() { }
void BenchV3l() { }
#else
void BenchV3f() { benchRunV3<V3fg, V3fg, float>("V3fg", "V3fg");  }
void BenchV3d() { benchRunV3<V3dg, V3dg, double>("V3dg", "V3dg"); }
void BenchV3i() { }
void BenchV3l() { }
#endif

#if defined(SIMD_SSE2)
void BenchV4f() { benchRunV4<V4fg, V4fs, float>("V4fg", "V4fs");      }
void BenchV4d() { benchRunV4<V4dg, V4ds, double>("V4dg", "V4ds");     }
void BenchV4i() { benchRunV4Int<V4ig, V4is, int>("V4ig", "V4is");     }
void BenchV4l() { benchRunV4Int<V4lg, V4ls, int64_t>("V4lg", "V4ls"); }
#else
void BenchV4f() { benchRunV4<V4fg, V4fg, float>("V4fg", "V4fg");      }
void BenchV4d() { benchRunV4<V4dg, V4dg, double>("V4dg", "V4dg");     }
void BenchV4i() { benchRunV4Int<V4ig, V4ig, int>("V4ig", "V4ig");     }
void BenchV4l() { benchRunV4Int<V4lg, V4lg, int64_t>("V4lg", "V4lg"); }
#endif
