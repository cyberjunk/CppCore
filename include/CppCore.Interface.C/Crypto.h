#pragma once

// export macro
#ifndef CPPCORE_EXPORT
#if defined(_WIN64) || defined(_WIN32)
#define CPPCORE_EXPORT __declspec(dllexport)
#else
#define CPPCORE_EXPORT __attribute__((visibility("default")))
#endif
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// macro for large integer arithmetic function declarations
#define CPPCORE_UINT_DECLARATION(name)                                     \
  CPPCORE_EXPORT void name ## _add   (void* a, void* b, void* r);          \
  CPPCORE_EXPORT void name ## _sub   (void* a, void* b, void* r);          \
  CPPCORE_EXPORT void name ## _mul   (void* a, void* b, void* r);          \
  CPPCORE_EXPORT void name ## _divmod(void* a, void* b, void* q, void* r); \
  CPPCORE_EXPORT void name ## _mulmod(void* a, void* b, void* m, void* r); \
  CPPCORE_EXPORT void name ## _powmod(void* a, void* b, void* m, void* r);

// macro for basex function declarations
#define CPPCORE_BASEX_DECLARATION(size)                                             \
  CPPCORE_EXPORT int cppcore_basex_encode##size(void* in, char* out, int len, unsigned int base, char* alphabet, unsigned int writeterm); \
  CPPCORE_EXPORT unsigned int cppcore_basex_decode##size(char* in, void* out, char* alphabet);

// macro for hash function declarations
#define CPPCORE_HASH_DECLARATION(name)                                              \
  typedef struct _ ## name name;                                                    \
  CPPCORE_EXPORT name* name ## _init     ();                                        \
  CPPCORE_EXPORT void  name ## _destroy  (name* hsh);                               \
  CPPCORE_EXPORT void  name ## _reset    (name* hsh);                               \
  CPPCORE_EXPORT void  name ## _blockstep(name* hsh, void* data, unsigned int len); \
  CPPCORE_EXPORT void  name ## _step     (name* hsh, void* data, unsigned int len); \
  CPPCORE_EXPORT void  name ## _finish   (name* hsh, void* digest);

// macro for hmac function declarations
#define CPPCORE_HMAC_DECLARATION(name)                                            \
  typedef struct _ ## name name;                                                  \
  CPPCORE_EXPORT name* name ## _init   ();                                        \
  CPPCORE_EXPORT void  name ## _destroy(name* hsh);                               \
  CPPCORE_EXPORT void  name ## _reset  (name* hsh, void* key,  unsigned int len); \
  CPPCORE_EXPORT void  name ## _step   (name* hsh, void* data, unsigned int len); \
  CPPCORE_EXPORT void  name ## _finish (name* hsh, void* digest);

// macro for pbkdf2 declarations
#define CPPCORE_PBKDF2_DECLARATION(name)  \
  CPPCORE_EXPORT void  name ## _create(   \
    void* pw,     unsigned int lenpw,     \
    void* salt,   unsigned int lensalt,   \
    void* digest, unsigned int lendigest, \
    unsigned int iterations);

// macro for dh declarations
#define CPPCORE_DH_DECLARATION(name)                                                \
  typedef struct _ ## name name;                                                    \
  CPPCORE_EXPORT name* name ## _init         ();                                    \
  CPPCORE_EXPORT void  name ## _destroy      (name* dh);                            \
  CPPCORE_EXPORT void  name ## _reset        (name* dh, unsigned int certainty);    \
  CPPCORE_EXPORT void  name ## _reset_pg     (name* dh, void* p, void* g);          \
  CPPCORE_EXPORT void  name ## _reset_pgv    (name* dh, void* p, void* g, void* v); \
  CPPCORE_EXPORT void  name ## _genkey       (name* dh, void* V);                   \
  CPPCORE_EXPORT void  name ## _getprime     (name* dh, void* p);                   \
  CPPCORE_EXPORT void  name ## _getconstant  (name* dh, void* g);                   \
  CPPCORE_EXPORT void  name ## _getprivkey   (name* dh, void* v);                   \
  CPPCORE_EXPORT void  name ## _getpubkey    (name* dh, void* V);                   \
  CPPCORE_EXPORT void  name ## _getsessionkey(name* dh, void* k);

// macro for aes function declarations
#define CPPCORE_AES_DECLARATION(name)                                                                  \
  typedef struct _ ## name name;                                                                       \
  CPPCORE_EXPORT name* name ## _init       ();                                                         \
  CPPCORE_EXPORT void  name ## _destroy    (name* aes);                                                \
  CPPCORE_EXPORT void  name ## _reset      (name* aes, void* key);                                     \
  CPPCORE_EXPORT void  name ## _encrypt_ecb(name* aes, void* in, void* out, unsigned int n);           \
  CPPCORE_EXPORT void  name ## _decrypt_ecb(name* aes, void* in, void* out, unsigned int n);           \
  CPPCORE_EXPORT void  name ## _encrypt_cbc(name* aes, void* in, void* out, void* iv, unsigned int n); \
  CPPCORE_EXPORT void  name ## _decrypt_cbc(name* aes, void* in, void* out, void* iv, unsigned int n); \
  CPPCORE_EXPORT void  name ## _encrypt_ctr(name* aes, void* in, void* out, void* iv, unsigned int n); \
  CPPCORE_EXPORT void  name ## _decrypt_ctr(name* aes, void* in, void* out, void* iv, unsigned int n);

// macro for prime declarations
#define CPPCORE_PRIME_DECLARATION(name)                                                          \
  CPPCORE_EXPORT int  name ## _test     (void* data, unsigned int sign, unsigned int certainty); \
  CPPCORE_EXPORT void name ## _generate (void* data, unsigned int sign, unsigned int certainty);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

   // large integer arithmetic

   CPPCORE_UINT_DECLARATION(cppcore_uint32)
   CPPCORE_UINT_DECLARATION(cppcore_uint64)
   CPPCORE_UINT_DECLARATION(cppcore_uint128)
   CPPCORE_UINT_DECLARATION(cppcore_uint256)
   CPPCORE_UINT_DECLARATION(cppcore_uint512)
   CPPCORE_UINT_DECLARATION(cppcore_uint1024)
   CPPCORE_UINT_DECLARATION(cppcore_uint2048)
   CPPCORE_UINT_DECLARATION(cppcore_uint4096)
   CPPCORE_UINT_DECLARATION(cppcore_uint8192)

   // basex

   CPPCORE_EXPORT unsigned int cppcore_basex_estimate_bits(unsigned int symbols, unsigned int base);
   CPPCORE_EXPORT unsigned int cppcore_basex_estimate_symbols(unsigned int bits, unsigned int base);

   CPPCORE_BASEX_DECLARATION(32)
   CPPCORE_BASEX_DECLARATION(64)
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

   CPPCORE_PBKDF2_DECLARATION(cppcore_pbkdf2_md5)
   CPPCORE_PBKDF2_DECLARATION(cppcore_pbkdf2_sha256)
   CPPCORE_PBKDF2_DECLARATION(cppcore_pbkdf2_sha512)

   // dh

   CPPCORE_DH_DECLARATION(cppcore_dh128)
   CPPCORE_DH_DECLARATION(cppcore_dh256)
   CPPCORE_DH_DECLARATION(cppcore_dh512)
   CPPCORE_DH_DECLARATION(cppcore_dh1024)
   CPPCORE_DH_DECLARATION(cppcore_dh2048)

   // aes

   CPPCORE_AES_DECLARATION(cppcore_aes128)
   CPPCORE_AES_DECLARATION(cppcore_aes192)
   CPPCORE_AES_DECLARATION(cppcore_aes256)

   // primes

   CPPCORE_PRIME_DECLARATION(cppcore_prime32)
   CPPCORE_PRIME_DECLARATION(cppcore_prime64)
   CPPCORE_PRIME_DECLARATION(cppcore_prime128)
   CPPCORE_PRIME_DECLARATION(cppcore_prime256)
   CPPCORE_PRIME_DECLARATION(cppcore_prime512)
   CPPCORE_PRIME_DECLARATION(cppcore_prime1024)
   CPPCORE_PRIME_DECLARATION(cppcore_prime2048)

#ifdef __cplusplus
}
#endif
