#include <CppCore/Root.h>

int main()
{
   uint64_t r[2];

   uint32_t* pr32 = (uint32_t*)&r;
   for (size_t i = 0; i < 4; i++)
   {
      *pr32++ = 0U;
   }

   std::cout << r[0] << std::endl;
   std::cout << r[1] << std::endl;

   if (r[0] != 0 || r[1] != 0)
   {
      std::cout << "ERROR" << std::endl;
      return 1;
   }

   return 0;
}
