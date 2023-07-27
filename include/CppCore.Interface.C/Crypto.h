#pragma once

// export macro
#ifndef CPPCORE_EXPORT
#if defined(_WIN64) || defined(_WIN32)
#define CPPCORE_EXPORT __declspec(dllexport)
#else
#define CPPCORE_EXPORT __attribute__((visibility("default")))
#endif
#endif

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// macro for basex function declarations
#define CPPCORE_BASEX_DECLARATION(size)                                             \
  CPPCORE_EXPORT intptr_t cppcore_basex_encode##size(                               \
    void* in, char* out, intptr_t len, size_t base, char* alphabet, int writeterm); \
  CPPCORE_EXPORT unsigned int cppcore_basex_decode##size(                           \
    char* in, void* out, size_t base, char* alphabet);

// macro for hash function declarations
#define CPPCORE_HASH_DECLARATION(name)                                      \
  typedef struct _ ## name name;                                            \
  CPPCORE_EXPORT name* name ## _init   ();                                  \
  CPPCORE_EXPORT void  name ## _destroy(name* hsh);                         \
  CPPCORE_EXPORT void  name ## _reset  (name* hsh);                         \
  CPPCORE_EXPORT void  name ## _step   (name* hsh, void* data, size_t len); \
  CPPCORE_EXPORT void  name ## _finish (name* hsh, void* digest);

// macro for hmac function declarations
#define CPPCORE_HMAC_DECLARATION(name)                                      \
  typedef struct _ ## name name;                                            \
  CPPCORE_EXPORT name* name ## _init   ();                                  \
  CPPCORE_EXPORT void  name ## _destroy(name* hsh);                         \
  CPPCORE_EXPORT void  name ## _reset  (name* hsh, void* key,  size_t len); \
  CPPCORE_EXPORT void  name ## _step   (name* hsh, void* data, size_t len); \
  CPPCORE_EXPORT void  name ## _finish (name* hsh, void* digest);

// macro for pbkdf2 declarations
#define CPPCORE_PBKDF2_DECLARATION(name) \
  CPPCORE_EXPORT void  name ## _create(  \
    void*  pw,     size_t lenpw,         \
    void*  salt,   size_t lensalt,       \
    void*  digest, size_t lendigest,     \
    size_t iterations);

// macro for aes function declarations
#define CPPCORE_AES_DECLARATION(name)                                                            \
  typedef struct _ ## name name;                                                                 \
  CPPCORE_EXPORT name* name ## _init       ();                                                   \
  CPPCORE_EXPORT void  name ## _destroy    (name* aes);                                          \
  CPPCORE_EXPORT void  name ## _reset      (name* aes, void* key);                               \
  CPPCORE_EXPORT void  name ## _encrypt_ecb(name* aes, void* in, void* out, size_t n);           \
  CPPCORE_EXPORT void  name ## _decrypt_ecb(name* aes, void* in, void* out, size_t n);           \
  CPPCORE_EXPORT void  name ## _encrypt_cbc(name* aes, void* in, void* out, void* iv, size_t n); \
  CPPCORE_EXPORT void  name ## _decrypt_cbc(name* aes, void* in, void* out, void* iv, size_t n); \
  CPPCORE_EXPORT void  name ## _encrypt_ctr(name* aes, void* in, void* out, void* iv, size_t n); \
  CPPCORE_EXPORT void  name ## _decrypt_ctr(name* aes, void* in, void* out, void* iv, size_t n);

// macro for prime declarations
#define CPPCORE_PRIME_DECLARATION(name)                                 \
  CPPCORE_EXPORT int  name ## _test     (void* data, size_t certainty); \
  CPPCORE_EXPORT void name ## _generate (void* data, size_t certainty);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

   // basex

   CPPCORE_BASEX_DECLARATION(128)
   CPPCORE_BASEX_DECLARATION(256)
   CPPCORE_BASEX_DECLARATION(512)
   CPPCORE_BASEX_DECLARATION(1024)
   CPPCORE_BASEX_DECLARATION(2048)
   CPPCORE_BASEX_DECLARATION(4096)
   CPPCORE_BASEX_DECLARATION(8192)

   // hash

   CPPCORE_HASH_DECLARATION(cppcore_md5)
   CPPCORE_HASH_DECLARATION(cppcore_sha256)
   CPPCORE_HASH_DECLARATION(cppcore_sha512)
   CPPCORE_HASH_DECLARATION(cppcore_crc32)
   CPPCORE_HASH_DECLARATION(cppcore_crc32c)
   CPPCORE_HASH_DECLARATION(cppcore_murmur3)

   // hmac

   CPPCORE_HMAC_DECLARATION(cppcore_hmac_md5)
   CPPCORE_HMAC_DECLARATION(cppcore_hmac_sha256)
   CPPCORE_HMAC_DECLARATION(cppcore_hmac_sha512)

   // pbkdf2

   CPPCORE_PBKDF2_DECLARATION(cppcore_pbkdf2_sha256)
   CPPCORE_PBKDF2_DECLARATION(cppcore_pbkdf2_sha512)

   // aes

   CPPCORE_AES_DECLARATION(cppcore_aes128)
   CPPCORE_AES_DECLARATION(cppcore_aes192)
   CPPCORE_AES_DECLARATION(cppcore_aes256)

   // primes

   CPPCORE_PRIME_DECLARATION(cppcore_prime128)
   CPPCORE_PRIME_DECLARATION(cppcore_prime256)
   CPPCORE_PRIME_DECLARATION(cppcore_prime512)
   CPPCORE_PRIME_DECLARATION(cppcore_prime1024)
   CPPCORE_PRIME_DECLARATION(cppcore_prime2048)

#ifdef __cplusplus
}
#endif
