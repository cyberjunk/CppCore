#include <cstdio>
#include <chrono>
#include <CppCore/Stopwatch.h>
#include <CppCore/Math/Primes.h>
#include <CppCore/Math/BigInt.h>
#include <CppCore/Random.h>

using namespace CppCore;

template<typename UINT>
static void bench(const char* name, uint32_t iter)
{
   // Generate a large prime to exercise the full MR path
   Random::Default prng;
   Primes::Memory<UINT> genmem;
   UINT n;
   Primes::genprime(n, prng, genmem, false);

   Primes::Memory<UINT> mem;

   Stopwatch sw;
   sw.start();
   for (uint32_t i = 0; i < iter; i++)
      (void)Primes::isprime_ai(n, mem, false);
   sw.stop();
   auto ai_ns = sw.getDuration().count() / iter;

   sw.reset();
   sw.start();
   for (uint32_t i = 0; i < iter; i++)
      (void)Primes::isprime(n, false);
   sw.stop();
   auto orig_ns = sw.getDuration().count() / iter;

   // Print the value's high words for reference
   const uint64_t* p = (const uint64_t*)&n;
   const uint32_t N64 = (uint32_t)(sizeof(UINT) / 8);
   std::printf("%s: isprime=%lld ns  isprime_ai=%lld ns  speedup=%.2fx  [0x%016llX..%016llX]\n",
      name, (long long)orig_ns, (long long)ai_ns, (double)orig_ns / (double)ai_ns,
      (unsigned long long)p[N64-1], (unsigned long long)p[0]);
}

int main()
{
   std::printf("=== CppCore Prime Benchmark (isprime vs isprime_ai) ===\n");
   std::printf("    using generated primes (full MR path)\n\n");
   bench<uint64_t>   ("  64-bit", 500);
   bench<uint128_t>  (" 128-bit", 500);
   bench<uint256_t>  (" 256-bit", 200);
   bench<uint512_t>  (" 512-bit", 100);
   bench<uint1024_t> ("1024-bit",  50);
   bench<uint2048_t> ("2048-bit",  20);
   bench<uint4096_t> ("4096-bit",  10);
   return 0;
}
