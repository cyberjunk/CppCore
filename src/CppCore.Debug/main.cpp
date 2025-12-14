#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>
#include <CppCore/Random.h>
#include <CppCore/Math/BigInt.h>
#include <CppCore/Math/Primes.h>
#include <CppCore/Stopwatch.h>

using namespace CppCore;

CppCore::Random::Default64 prng;

template<typename UINTD, typename UINTR>
INLINE void barret_constant(UINTR& bc, const UINTD& d)
{
   static_assert(sizeof(UINTR) >= sizeof(UINTD) * 2U);

   UINTR t;
   CppCore::clear(t);
   uint8_t* pt = (uint8_t*)&t;
   pt[sizeof(UINTR)-1] |= 0x80;

   UINTD r;
   CppCore::udivmod(bc, r, t, d);
   CppCore::shl(bc, bc, 1);
   //q <<= 1;

   if (!CppCore::testzero(r)) {

      UINTD t1;
      UINTD t2;
      CppCore::shl(r, r, 1);
      CppCore::udivmod(t1, t2, r, d);
      CppCore::uadd(bc, t1, bc);
      //q += (r << 1) / d;
   }
   
   //CppCore::clone(bc, q);

   /*uint512_t numerator = (uint512_t)1 << 511;
   numerator = (numerator / d) * 2;
   if (((uint512_t)1 << 511) % d != 0) {
      numerator += (((uint512_t)1 << 511) % d * 2) / d;
   }*/

}

/// <summary>
/// Barret Reduction on a using constant c and divisor d, r is result.
/// </summary>
template<typename UINTA, typename UINTC>
INLINE void barret_umod(UINTA&r, const UINTA& a, const UINTC& c, const UINTA& d)
{
   struct PRODAC { UINTC c; UINTA a; };
   PRODAC prod;
   
   CppCore::umul(a, c, prod);
   CppCore::umul(prod.a, d, r);
   CppCore::usub(a, r, r);
   while (r >= d) {
      CppCore::usub(r, d, r);
   }
}





typedef uint2048_t UINTX;
typedef uint4096_t UINTX2;

#define N 1024*1024
UINTX a[N];
UINTX v;
Stopwatch w1;
Stopwatch w2;
uint64_t t;
uint64_t s1, s2;


int main()
{
   prng.fill(a);
   prng.fill(v);
   
   s1 = 0;
   s2 = 0;

   const UINTX& divisor = v;

   //uint128_t divisor = uint128_t(2,0);
   UINTX2 bc;
   barret_constant(bc, divisor);
   //std::cout << std::hex << bc.toHexString() << std::endl;

   for (size_t i = 0; i < N; i++)
   {

      //std::cout << std::hex << divisor.toHexString() << std::endl;
      t = __rdtsc();
      UINTX r;
      //uint128_t& a = a[i];
      barret_umod(r, a[i], bc, divisor);
      //std::cout << std::hex << r.toHexString() << std::endl;
      s1 += __rdtsc() -t;

      t = __rdtsc();
      UINTX r2;
      CppCore::umod(r2, a[i], divisor);
      //w2.stop();
      s2 += __rdtsc() - t;





      if (r != r2)
      {
         std::cout << "FAIL" << std::endl;
         std::cout << std::hex << r2.toHexString() << std::endl;
         return 1;
      }
      //std::cout << "------------" << std::endl;
   }
   
   std::cout << s1 << std::endl;
   std::cout << s2 << std::endl;

   return 0;
}




//std::cout << std::setfill('0') << std::setw(5) << std::setprecision(10);

/*double t = 0.5;
double z;
for (size_t i = 0; i < Primes::NUMODDPRIMES; i++)
{
   z = (1.0 - 1.0 / (double)Primes::ODDPRIMES[i]);
   t *= z;
   std::cout << std::setfill('0') << std::setw(5) << i << "  " << Primes::ODDPRIMES[i] << "  " << std::fixed << std::setprecision(10) << (1.0 - t) << std::endl;
}*/