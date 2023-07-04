#pragma once

#include <CppCore/Root.h>

#ifdef __cplusplus
extern "C" {
#endif

   /////////////////////////////////////////////////////////////////////////////////////

   typedef struct _cppcore_md5 cppcore_md5;

   CPPCORE_EXPORT cppcore_md5* cppcore_md5_init();
   CPPCORE_EXPORT void cppcore_md5_destroy(cppcore_md5* md5);
   CPPCORE_EXPORT void cppcore_md5_reset(cppcore_md5* md5);

   CPPCORE_EXPORT void cppcore_md5_step(cppcore_md5* md5, void* data, size_t len);

#ifdef __cplusplus
}
#endif
