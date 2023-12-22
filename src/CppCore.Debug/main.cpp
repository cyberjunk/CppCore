#include <CppCore/Root.h>

#include <CppCore/BitOps.h>
#include <CppCore/Random.h>
#include <CppCore/Encoding.h>
#include <CppCore/Stopwatch.h>

using namespace CppCore;

#ifdef CPPCORE_COMPILER_MSVC
#define NOINLINE
#else
//#define NOINLINE
#define NOINLINE __attribute__((noinline))
#endif

CppCore::Random::Default64 rnd;
CppCore::Stopwatch watch;

constexpr size_t n = 100000;
constexpr size_t m = 4097;

//char* v = "678";
char v[n][m];

//uint8_t r[4];
uint32_t r[m/8];
//uint32_t r2 = 0;
uint32_t sum;

NOINLINE
void test(char* v, size_t strlen)
{
   CppCore::Hex::parse(v, strlen, r, sizeof(r));
   sum += r[0];
}

NOINLINE
void test2(char* v)
{
   r[0] = CppCore::Hex::Util::parse<uint32_t, 8>(v);
   sum += r[0];
}

NOINLINE
void test3(char* v)
{
   CppCore::Hex::parse(v, r[0]);
   sum += r[0];
}

NOINLINE
void test4(char* v)
{
   //CppCore::Hex::Fix::parse1(v, r[0]);
   sum += r[0];
}

NOINLINE
void test5(char* v)
{
   CppCore::Hex::Fix::parse2(v, r[0]);
   sum += r[0];
}

NOINLINE
void test6(char* v)
{
   //CppCore::Hex::Fix::parse3(v, r[0]);
   sum += r[0];
}

NOINLINE
void test7(char* v)
{
   CppCore::Hex::Fix::parse4(v, r, m/2);
   sum += r[0];
}
NOINLINE
void test8(char* v)
{
   CppCore::Hex::Fix::decode(v, r);
   sum += r[0];
}

int main()
{
   CppCore::clear(v);
   for (size_t j = 0; j < n; j++)
      for (size_t i = 0; i < sizeof(v[j]) - 1; i++)
         v[j][i] = (uint8_t)rnd.next((uint64_t)'0', (uint64_t)'9');

   for (uint32_t j = 0; j < 1; j++)
   {
      //r2 = std::strtoul(v, 0, 16);
      //std::cout << std::hex << r2 << std::endl;

      //   watch.reset();
      size_t strlen = ::strlen(v[0]);
      uint64_t t;


      std::cout << "test1" << std::endl;
      sum = 0;
      t = __rdtsc();
      for (uint32_t i = 0; i < n; i++) CPPCORE_UNROLL for (uint32_t j=0; j < 2; j++) test(v[i], strlen);
      t = __rdtsc() - t;
      std::cout << std::hex << r[0] << std::endl;
      std::cout << std::hex << sum << std::endl;
      std::cout << std::dec << t << std::endl;

      std::cout << "-----------" << std::endl;

      std::cout << "test2" << std::endl;
      sum = 0;
      t = __rdtsc();
      for (uint32_t i = 0; i < n; i++) CPPCORE_UNROLL for (uint32_t j=0; j < 2; j++)  test2(v[i]);
      t = __rdtsc() - t;
      std::cout << std::hex << r[0] << std::endl;
      std::cout << std::hex << sum << std::endl;
      std::cout << std::dec << t << std::endl;

      std::cout << "-----------" << std::endl;

      std::cout << "test3" << std::endl;
      sum = 0;
      t = __rdtsc();
      for (uint32_t i = 0; i < n; i++) CPPCORE_UNROLL for (uint32_t j=0; j < 2; j++) test3(v[i]);
      t = __rdtsc() - t;
      std::cout << std::hex << r[0] << std::endl;
      std::cout << std::hex << sum << std::endl;
      std::cout << std::dec << t << std::endl;

      std::cout << "-----------" << std::endl;

      std::cout << "test4" << std::endl;
      sum = 0;
      t = __rdtsc();
      for (uint32_t i = 0; i < n; i++) CPPCORE_UNROLL for (uint32_t j=0; j < 2; j++) test4(v[i]);
      t = __rdtsc() - t;
      std::cout << std::hex << r[0] << std::endl;
      std::cout << std::hex << sum << std::endl;
      std::cout << std::dec << t << std::endl;
      
      std::cout << "-----------" << std::endl;

      std::cout << "test5" << std::endl;
      sum = 0;
      t = __rdtsc();
      for (uint32_t i = 0; i < n; i++) CPPCORE_UNROLL for (uint32_t j=0; j < 2; j++)  test5(v[i]);
      t = __rdtsc() - t;
      std::cout << std::hex << r[0] << std::endl;
      std::cout << std::hex << sum << std::endl;
      std::cout << std::dec << t << std::endl;

      std::cout << "-----------" << std::endl;

      std::cout << "test6" << std::endl;
      sum = 0;
      t = __rdtsc();
      for (uint32_t i = 0; i < n; i++) CPPCORE_UNROLL for (uint32_t j=0; j < 2; j++)  test6(v[i]);
      t = __rdtsc() - t;
      std::cout << std::hex << r[0] << std::endl;
      std::cout << std::hex << sum << std::endl;
      std::cout << std::dec << t << std::endl;

      std::cout << "-----------" << std::endl;

      std::cout << "test7" << std::endl;
      sum = 0;
      t = __rdtsc();
      for (uint32_t i = 0; i < n; i++) CPPCORE_UNROLL for (uint32_t j = 0; j < 2; j++)  test7(v[i]);
      t = __rdtsc() - t;
      std::cout << std::hex << r[0] << std::endl;
      std::cout << std::hex << sum << std::endl;
      std::cout << std::dec << t << std::endl;

      std::cout << "-----------" << std::endl;

      std::cout << "test8" << std::endl;
      sum = 0;
      t = __rdtsc();
      for (uint32_t i = 0; i < n; i++) CPPCORE_UNROLL for (uint32_t j = 0; j < 2; j++)  test8(v[i]);
      t = __rdtsc() - t;
      std::cout << std::hex << r[0] << std::endl;
      std::cout << std::hex << sum << std::endl;
      std::cout << std::dec << t << std::endl;

   }

   return 0;
}
