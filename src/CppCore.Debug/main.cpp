#include <CppCore/Root.h>
#include <CppCore/Math/Primes.h>
#include <CppCore/Math/BigInt.h>
#include <CppCore/Stopwatch.h>

using namespace CppCore;

typedef uint4096_t UINT;

UINT p;
Random::Default64 prng;
Primes::Memory<UINT> mem;
Stopwatch watch1;
Stopwatch watch2;
Stopwatch watch3;
Stopwatch watch_all;

uint8_t* p8 = (uint8_t*)&p;
uint32_t nFailsTrial = 0;
uint32_t nFailsBase2 = 0;
uint32_t nFailsBase3 = 0;

int main()
{
   /*uint32_t x = 3;
   uint32_t found = 0;
   while(found < 1024)
   {
      if (Primes::isprime_trivial(x)) {
         found++;
         std::cout << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << x << ",";
         if (found % 16 == 0) std::cout << std::endl;  
      }
      x += 2;
   }
   std::cout << std::endl;
   return 0;*/





   uint16_t t;
   watch_all.start();

   do {

      prng.fill(p);

      p8[0] |= 0x01; // make odd
      p8[UINT::N8-1] |= 0x80; // make large

      std::cout << "-------------" << std::endl;
      
      std::cout << "Trial Fails: " << nFailsTrial << std::endl;
      std::cout << "Base2 Fails: " << nFailsBase2 << std::endl;
      std::cout << "Base3 Fails: " << nFailsBase3 << std::endl;
      //std::cout << watch.getDurationSum().count() << std::endl;

      //std::cout << "Testing:" << std::endl;
      //std::cout << p.toHexString() << std::endl;

      //

      watch1.start();
      t = Primes::isprime_trial(p);
      watch1.stop();
      if (t == 0) {
         nFailsTrial++;
         //std::cout << "Failed Trial" << std::endl;
         continue;
      }
      
      uint32_t&   s = mem.s; // s constant, see below 
      UINT& t = mem.t; // t constant, see below
      UINT& d = mem.d; // d constant, see below
      UINT& a = mem.a; // base a to test
      UINT& r = mem.r; // temporary result
      UINT* m = mem.m; // work memory

      Primes::sprp_tsd(p, t, s, d);

      // miller-rabin test
      a = 2U; watch2.start(); if (!Primes::sprp(p,a,t,s,d,r,m)) { watch2.stop(); nFailsBase2++; continue; }; watch2.stop();
      
      //a = 3U; if (!Primes::sprp(p,a,t,s,d,r,m)) { nFailsBase3++; continue; }
      
      assert(!CppCore::testzero(p));
      const auto lz = CppCore::lzcnt(p); // p is not 0
      const auto bp = (sizeof(UINT)*8) - lz - 1U;
      std::cout << "HIGH BIT AT IDX " << bp << std::endl;
      UINT mask(1U);
      //mask = 1U;
      mask <<= bp;
      mask -= 1U;
      std::cout << mask.toHexString() << std::endl;

      //CppCore::setbit64();
      //const UINT min = 2U;
      //const UINT max = p-2U;
      
      for (size_t i = 0; i < 100; i++) {
         prng.fill(a);
         a &= mask;
         //a = prng.next;
         watch3.start();
         if (!Primes::sprp(p,a,t,s,d,r,m)) { watch3.stop(); continue; }
         else watch3.stop();
      }

     
      break;

   } while (true);

   watch_all.stop();

   std::cout << "Done" << std::endl;

   constexpr double SCALE = 0.000001;

   std::cout << "TRIAL STATS" << std::endl;
   std::cout << "SUM: " << ((double)watch1.getDurationSum().count() * SCALE) << std::endl;
   std::cout << "MAX: " << ((double)watch1.getWorst().count() * SCALE) << std::endl;
   std::cout << "MIN: " << ((double)watch1.getBest().count() * SCALE) << std::endl;
   std::cout << "AVG: " << ((double)watch1.getAverage().count() * SCALE) << std::endl;

   std::cout << "SPRP2 STATS" << std::endl;
   std::cout << "SUM: " << ((double)watch2.getDurationSum().count() * SCALE) << std::endl;
   std::cout << "MAX: " << ((double)watch2.getWorst().count() * SCALE) << std::endl;
   std::cout << "MIN: " << ((double)watch2.getBest().count() * SCALE) << std::endl;
   std::cout << "AVG: " << ((double)watch2.getAverage().count() * SCALE) << std::endl;

   std::cout << "SPRPX STATS" << std::endl;
   std::cout << "SUM: " << ((double)watch3.getDurationSum().count() * SCALE) << std::endl;
   std::cout << "MAX: " << ((double)watch3.getWorst().count() * SCALE) << std::endl;
   std::cout << "MIN: " << ((double)watch3.getBest().count() * SCALE) << std::endl;
   std::cout << "AVG: " << ((double)watch3.getAverage().count() * SCALE) << std::endl;

   std::cout << "ALL STATS" << std::endl;
   std::cout << "SUM: " << ((double)watch_all.getDurationSum().count() * SCALE) << std::endl;
   std::cout << "MAX: " << ((double)watch_all.getWorst().count() * SCALE) << std::endl;
   std::cout << "MIN: " << ((double)watch_all.getBest().count() * SCALE) << std::endl;
   std::cout << "AVG: " << ((double)watch_all.getAverage().count() * SCALE) << std::endl;

   return 0;
}
