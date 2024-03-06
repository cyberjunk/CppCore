#include <CppCore/Root.h>

#include <CppCore/Math/Primes.h>
#include <CppCore/Math/BigInt.h>
#include <CppCore/Random.h>

using namespace CppCore;

//uint64_t p[2];

int main()
{

   Random::Default64 prng;

   //CppCore:Primes::Memory<uint32_t> m;
//   uint128_t x;
   int16_t x;

   Primes::Result r = Primes::isprime((int16_t)31);

   Primes::genprime(x, true);

   //Primes::Result r = Primes::isprime((int64_t)-1);

   std::cout << x << std::endl;

   return 0;
}
