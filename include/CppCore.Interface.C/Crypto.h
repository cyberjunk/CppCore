#pragma once

// export macro
#ifndef CPPCORE_EXPORT
#if defined(_WIN64) || defined(_WIN32)
#define CPPCORE_EXPORT __declspec(dllexport)
#else
#define CPPCORE_EXPORT __attribute__((visibility("default")))
#endif
#endif

#include <stddef.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// macro for hash function declarations
#define CPPCORE_HASH_DECLARATION(name)                                      \
  typedef struct _ ## name name;                                            \
  CPPCORE_EXPORT name* name ## _init   ();                                  \
  CPPCORE_EXPORT void  name ## _destroy(name* hsh);                         \
  CPPCORE_EXPORT void  name ## _reset  (name* hsh);                         \
  CPPCORE_EXPORT void  name ## _step   (name* hsh, void* data, size_t len); \
  CPPCORE_EXPORT void  name ## _finish (name* hsh, void* digest);

// macro for hmach function declarations
#define CPPCORE_HMAC_DECLARATION(name)                                      \
  typedef struct _ ## name name;                                            \
  CPPCORE_EXPORT name* name ## _init   ();                                  \
  CPPCORE_EXPORT void  name ## _destroy(name* hsh);                         \
  CPPCORE_EXPORT void  name ## _reset  (name* hsh, void* key,  size_t len); \
  CPPCORE_EXPORT void  name ## _step   (name* hsh, void* data, size_t len); \
  CPPCORE_EXPORT void  name ## _finish (name* hsh, void* digest);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

   // hash function declarations

   CPPCORE_HASH_DECLARATION(cppcore_md5)
   CPPCORE_HASH_DECLARATION(cppcore_sha256)
   CPPCORE_HASH_DECLARATION(cppcore_sha512)
   CPPCORE_HASH_DECLARATION(cppcore_crc32)
   CPPCORE_HASH_DECLARATION(cppcore_crc32c)
   CPPCORE_HASH_DECLARATION(cppcore_murmur3)

   // hmac function declarations

   CPPCORE_HMAC_DECLARATION(cppcore_hmac_md5)
   CPPCORE_HMAC_DECLARATION(cppcore_hmac_sha256)
   CPPCORE_HMAC_DECLARATION(cppcore_hmac_sha512)

#ifdef __cplusplus
}
#endif