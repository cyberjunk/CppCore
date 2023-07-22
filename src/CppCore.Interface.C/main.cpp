
#include <CppCore/Root.h>

#include <CppCore.Interface.C/Hash.h>

#include <CppCore/Hash/MD5.h>


template<typename TC, typename TCPP>
TC* cppcore_hash_init()
{

}

cppcore_md5* cppcore_md5_init()                                    { return (cppcore_md5*) new CppCore::MD5(); }
void cppcore_md5_destroy(cppcore_md5* md5)                         { delete (CppCore::MD5*)md5; }
void cppcore_md5_reset  (cppcore_md5* md5)                         { ((CppCore::MD5*)md5)->reset(); }
void cppcore_md5_step   (cppcore_md5* md5, void* data, size_t len) { ((CppCore::MD5*)md5)->step(data, len); }
void cppcore_md5_finish (cppcore_md5* md5, void* hash, size_t len) { ((CppCore::MD5*)md5)->finish(hash); }

#ifdef WIN32
#include <Windows.h>
BOOL WINAPI DllMain(
   HINSTANCE hinstDLL,  // handle to DLL module
   DWORD fdwReason,     // reason for calling function
   LPVOID lpvReserved)  // reserved
{
   return TRUE;
}
#else
int main(int argc, char* argv[])
{
   return 0;
}
#endif
