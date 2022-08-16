#include <CppCore/Root.h>
#include <CppCore/Math/BigInt.h>
#include <CppCore/Stopwatch.h>

using namespace CppCore;

uint2048_t x;
Primes::Memory<uint2048_t> mem;
Random::Default64 gen;
std::string s;
Stopwatch watch;

int main()
{
   while (true)
   {
      watch.start();
      x.genprime(gen, mem, 512);
      watch.stop();
      s = x.toString();
      printf("%lli  %s\n\n", watch.getDuration().count() / 1000000, s.c_str());
   }
   
   return 0;
}
