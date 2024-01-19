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

const char* v1 = "000001ff"; // 01ff
uint32_t r1;

const char* v2 = "ff01"; // ff01
uint32_t r2;

int main()
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
   printf("little\n");
   printf("%i\n",__BYTE_ORDER__);
#else
   printf("big");
#endif

   Hex::parse(v1, ::strlen(v1), r1, true);
   Hex::parse(v2, ::strlen(v2), r2, false);

   std::cout << std::hex << r1 << std::endl;
   std::cout << std::hex << r2 << std::endl;

   return 0;
}
