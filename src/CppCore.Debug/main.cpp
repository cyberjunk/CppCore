#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>

NOINLINE static int clmul64to128()
{
   struct t { uint64_t l; uint64_t h; };
   t r;

   uint32_t* pr32 = (uint32_t*)&r;

   for (size_t i = 0; i < 4; i++)
   {
      *pr32++ = 0U;
   }

   std::cout << std::hex << "-----------" << std::endl;

   size_t s = sizeof(r);
   std::cout << std::hex << r.l << std::endl;
   std::cout << std::hex << r.h << std::endl;

   uint64_t a = (uint64_t)0x0000000000000000ULL;
   uint64_t b = (uint64_t)0x0000000000000000ULL;
   CppCore::clmul(a, b, r);
   std::cout << std::hex << r.l << std::endl;
   std::cout << std::hex << r.h << std::endl;

   if (r.l != (uint64_t)0x0000000000000000ULL || r.h != (uint64_t)0x0000000000000000ULL) {
      std::cout << std::hex << r.l << std::endl;
      std::cout << std::hex << r.h << std::endl;

      return 1;
   }

   return 0;
}


int main()
{
   return clmul64to128();
}
