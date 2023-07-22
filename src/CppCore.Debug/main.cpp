
#include <CppCore/Root.h>

#include <CppCore.Interface.C/Hash.h>

uint64_t d[2];

int main()
{
   cppcore_md5* md = cppcore_md5_init();

   cppcore_md5_step(md, md, 8);
   cppcore_md5_finish(md, d, sizeof(d));

   cppcore_md5_reset(md);
   cppcore_md5_destroy(md);

   return 0;
}

