
#include <CppCore/Root.h>

#include <CppCore.Interface.C/Crypto.h>

uint64_t d[1024];

//uint64_t uint512[8];

char s[8192];

int main()
{
   d[0] = 151512415;
   d[1] = 0;
   /*cppcore_md5* md = cppcore_md5_init();

   cppcore_md5_step(md, md, 8);
   cppcore_md5_finish(md, d);

   cppcore_md5_reset(md);
   cppcore_md5_destroy(md);*/

   //cppcore_prime512_generate(uint512, 100);

   intptr_t a = cppcore_basex_encode8192(d, s, 63, 10, "0123456789", 1);
   cppcore_basex_decode8192(s, d, "0123456789");

   return 0;
}

