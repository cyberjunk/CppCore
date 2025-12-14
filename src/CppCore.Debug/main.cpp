#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>
#include <CppCore/Random.h>
#include <CppCore/Math/BigInt.h>
#include <CppCore/Math/Primes.h>
#include <CppCore/Stopwatch.h>

using namespace CppCore;

CppCore::Random::Default64 prng;





typedef uint2048_t UINTX;
//typedef uint4096_t UINTX2;

#define N 1024*1024
UINTX a[N];
UINTX v;
Stopwatch w1;
Stopwatch w2;
uint64_t t;
uint64_t s1, s2;


int main()
{

   //union { UINTX2 r; UINTX d; };
   
   prng.fill(a);
   prng.fill(v);
   
   s1 = 0;
   s2 = 0;

   const UINTX& divisor = v;

   //uint128_t divisor = uint128_t(2,0);
   UINTX bc[2];
   barrett_constant(bc, divisor);
   //std::cout << std::hex << bc.toHexString() << std::endl;

   for (size_t i = 0; i < N; i++)
   {

      //std::cout << std::hex << divisor.toHexString() << std::endl;
      t = __rdtsc();
      UINTX r;
      //uint128_t& a = a[i];
      barrett_umod(r, a[i], bc, divisor);
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