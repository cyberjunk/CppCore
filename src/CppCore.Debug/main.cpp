#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>
#include <CppCore/Random.h>
#include <CppCore/Math/BigInt.h>
#include <CppCore/Math/Primes.h>
#include <CppCore/Stopwatch.h>

using namespace CppCore;

typedef uint64_t UINTX;

#define N 1024*1024

CppCore::Random::Default64 prng;

/*UINTX d;
UINTX a[N];
UINTX r1[N];
UINTX r2[N];

UINTX bc[2];

uint64_t NOINLINE test1()
{
   barrett_constant(bc, d);

   uint64_t t = __rdtsc();

   for (size_t i = 0; i < N; i++)
      barrett_umod(r1[i], a[i], bc, d);

   return __rdtsc() - t;
}

uint64_t NOINLINE test2()
{
   uint64_t t = __rdtsc();

   for (size_t i = 0; i < N; i++)
      CppCore::umod(r2[i], a[i], d);

   return __rdtsc() - t;
}

int main()
{
   prng.fill(a);
   prng.fill(d);

   for (size_t i = 0; i < N; i++)
      ((uint8_t*)&a[i])[sizeof(UINTX) - 1] |= 0x80;

   uint64_t t2 = test2();
   uint64_t t1 = test1();

   std::cout << "BARRETT: " << t1 << std::endl;
   std::cout << "KNUTH:   " << t2 << std::endl;

   for (size_t i = 0; i < N; i++)
   {
      if (r1[i] != r2[i])
      {
         std::cout << "FAIL" << std::endl;
         //std::cout << std::hex << r2.toHexString() << std::endl;
         return 1;
      }
   }

   return 0;
}*/

UINTX a[N];
UINTX b[N];
UINTX m[N];
UINTX r1[N];
UINTX r2[N];

int main()
{
   uint64_t ta = 245373463472;
   uint64_t tb = 3252764873;
   uint64_t tm = 32534684;
   uint64_t tr;
   CppCore::upowmod_kary(ta, tb, tm, tr);
   std::cout << tr << std::endl;

   CppCore::upowmod(ta, tb, tm, tr);
   std::cout << tr << std::endl;


   prng.fill(a);
   prng.fill(b);
   prng.fill(m);

   for (size_t i = 0; i < N; i++)
   {
      UINTX at;
      CppCore::clone(at, a[i]);
      CppCore::upowmod(at, b[i], m[i], r1[i]);
      CppCore::upowmod_kary(a[i], b[i], m[i], r2[i]);

      if (!CppCore::equal(r1[i], r2[i])) {
         std::cout << a[i] << "^" << b[i] << " % " << m[i] << " = " << r1[i] << std::endl;
         std::cout << a[i] << "^" << b[i] << " % " << m[i] << " = " << r2[i] << std::endl;
         return 1;
      }
   }
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