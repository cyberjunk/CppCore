
#include <CppCore/Root.h>

#include <CppCore.Interface.C/Crypto.h>

uint64_t d[2];

uint64_t uint512[8];

int main()
{
   /*cppcore_md5* md = cppcore_md5_init();

   cppcore_md5_step(md, md, 8);
   cppcore_md5_finish(md, d);

   cppcore_md5_reset(md);
   cppcore_md5_destroy(md);*/

   cppcore_prime512_generate(uint512, 100);

   return 0;
}

