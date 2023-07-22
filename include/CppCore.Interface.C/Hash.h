#pragma once

// Export macro
#ifndef CPPCORE_EXPORT
#if defined(_WIN64) || defined(_WIN32)
#define CPPCORE_EXPORT __declspec(dllexport)
#else
#define CPPCORE_EXPORT __attribute__((visibility("default")))
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

   /////////////////////////////////////////////////////////////////////////////////////
   // MD5
   /////////////////////////////////////////////////////////////////////////////////////
   typedef struct _cppcore_md5 cppcore_md5;

   CPPCORE_EXPORT cppcore_md5* cppcore_md5_init();
   CPPCORE_EXPORT void         cppcore_md5_destroy(cppcore_md5* md5);
   CPPCORE_EXPORT void         cppcore_md5_reset  (cppcore_md5* md5);
   CPPCORE_EXPORT void         cppcore_md5_step   (cppcore_md5* md5, void* data, size_t len);
   CPPCORE_EXPORT void         cppcore_md5_finish (cppcore_md5* md5, void* hash);


   /////////////////////////////////////////////////////////////////////////////////////
   // SHA256
   /////////////////////////////////////////////////////////////////////////////////////
   typedef struct _cppcore_sha256 cppcore_sha256;

   CPPCORE_EXPORT cppcore_sha256* cppcore_sha256_init();
   CPPCORE_EXPORT void            cppcore_sha256_destroy(cppcore_sha256* sha256);
   CPPCORE_EXPORT void            cppcore_sha256_reset  (cppcore_sha256* sha256);
   CPPCORE_EXPORT void            cppcore_sha256_step   (cppcore_sha256* sha256, void* data, size_t len);
   CPPCORE_EXPORT void            cppcore_sha256_finish (cppcore_sha256* sha256, void* hash);

#ifdef __cplusplus
}
#endif