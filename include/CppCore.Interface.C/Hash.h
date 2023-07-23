#pragma once

// export macro
#ifndef CPPCORE_EXPORT
#if defined(_WIN64) || defined(_WIN32)
#define CPPCORE_EXPORT __declspec(dllexport)
#else
#define CPPCORE_EXPORT __attribute__((visibility("default")))
#endif
#endif

// macro for function declarations
#define CPPCORE_HASH_DECLARATION(name)                       \
  typedef struct _ ## name name; \
  CPPCORE_EXPORT name* name ## _init   ();                                  \
  CPPCORE_EXPORT void  name ## _destroy(name* hsh);                         \
  CPPCORE_EXPORT void  name ## _reset  (name* hsh);                         \
  CPPCORE_EXPORT void  name ## _step   (name* hsh, void* data, size_t len); \
  CPPCORE_EXPORT void  name ## _finish (name* hsh, void* digest);

#ifdef __cplusplus
extern "C" {
#endif

   // generate generic function declarations

   CPPCORE_HASH_DECLARATION(cppcore_md5)
   CPPCORE_HASH_DECLARATION(cppcore_sha256)
   CPPCORE_HASH_DECLARATION(cppcore_sha512)
   CPPCORE_HASH_DECLARATION(cppcore_crc32)
   CPPCORE_HASH_DECLARATION(cppcore_crc32c)
   CPPCORE_HASH_DECLARATION(cppcore_murmur3)

#ifdef __cplusplus
}
#endif
