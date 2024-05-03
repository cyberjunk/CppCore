#include <CppCore/Root.h>

int main()
{
   //uint64_t r[2];
   struct t { uint64_t l; uint64_t h; };
   t r;

   uint32_t* pr32 = (uint32_t*)&r;
   for (size_t i = 0; i < 4; i++)
   {
      *pr32++ = 0U;
   }

   std::cout << r.l << std::endl;
   std::cout << r.h << std::endl;

   if (r.l != 0 || r.h != 0)
   {
      std::cout << "ERROR" << std::endl;
      return 1;
   }

   return 0;
}
