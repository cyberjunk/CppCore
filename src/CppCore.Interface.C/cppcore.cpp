
// don't include <ios> and related
#define CPPCORE_NO_INCLUDE_IO

// public c interface
#include <CppCore.Interface.C/cppcore.h>

// private c++ headers
#include <CppCore/Root.h>
#include <CppCore/Math/Util.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INTERNAL MACROS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CPPCORE_ALIGN 64
#define _CPPCORE_ALLOC(name, cname) \
  (name*)CPPCORE_ALIGNED_ALLOC(CppCore::rupptwo32(sizeof(cname), _CPPCORE_ALIGN), _CPPCORE_ALIGN)
#define _CPPCORE_FREE(ptr) CPPCORE_ALIGNED_FREE(ptr)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ENTRY POINT
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_OS_WINDOWS)
BOOL WINAPI DllMain(
   HINSTANCE hinstDLL,  // handle to DLL module
   DWORD fdwReason,     // reason for calling function
   LPVOID lpvReserved)  // reserved
{
   return TRUE;
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LARGE INTEGER ARITHMETIC
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Math/Util.h>
#include <CppCore/Block.h>

#define CPPCORE_UINT_IMPLEMENTATION(name, cname)                                                                           \
  void name ## _shl   (void* a, unsigned int b, void* r)  { CppCore::shl(*(cname*)r,  *(cname*)a, b);}                     \
  void name ## _shr   (void* a, unsigned int b, void* r)  { CppCore::shr(*(cname*)r,  *(cname*)a, b);}                     \
  void name ## _add   (void* a, void* b, void* r)         { CppCore::uadd(*(cname*)a, *(cname*)b, *(cname*)r);}            \
  void name ## _sub   (void* a, void* b, void* r)         { CppCore::usub(*(cname*)a, *(cname*)b, *(cname*)r);}            \
  void name ## _mul   (void* a, void* b, void* r)         { CppCore::umul(*(cname*)a, *(cname*)b, *(cname*)r);}            \
  void name ## _divmod(void* a, void* b, void* q, void* r){ CppCore::udivmod(*(cname*)q,*(cname*)r,*(cname*)a,*(cname*)b);}\
  void name ## _mulmod(void* a, void* b, void* m, void* r){ CppCore::umulmod(*(cname*)a,*(cname*)b,*(cname*)m,*(cname*)r);}\
  void name ## _powmod(void* a, void* b, void* m, void* r){ CppCore::upowmod(*(cname*)a,*(cname*)b,*(cname*)m,*(cname*)r);}\
  void name ## _gcd   (void* a, void* b, void* r)         { CppCore::gcd(*(cname*)a, *(cname*)b, *(cname*)r);}

CPPCORE_UINT_IMPLEMENTATION(cppcore_uint32,       std::uint32_t)
CPPCORE_UINT_IMPLEMENTATION(cppcore_uint64,       std::uint64_t)
CPPCORE_UINT_IMPLEMENTATION(cppcore_uint128,  CppCore::Block128)
CPPCORE_UINT_IMPLEMENTATION(cppcore_uint256,  CppCore::Block256)
CPPCORE_UINT_IMPLEMENTATION(cppcore_uint512,  CppCore::Block512)
CPPCORE_UINT_IMPLEMENTATION(cppcore_uint1024, CppCore::Block1024)
CPPCORE_UINT_IMPLEMENTATION(cppcore_uint2048, CppCore::Block2048)
CPPCORE_UINT_IMPLEMENTATION(cppcore_uint4096, CppCore::Block4096)
CPPCORE_UINT_IMPLEMENTATION(cppcore_uint8192, CppCore::Block8192)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ENCODING
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Encoding.h>
#include <CppCore/Block.h>

#define CPPCORE_BASEX_IMPLEMENTATION(size,block)                                            \
  int cppcore_basex_encode##size(                                                           \
    void*        in,   char* out,      int          len,                                    \
    unsigned int base, char* alphabet, unsigned int writeterm) {                            \
    return (int)CppCore::BaseX::tostring(*(block*)in, out, len, base, alphabet, writeterm); \
  }                                                                                         \
  unsigned int cppcore_basex_decode##size(char* in, void* out, char* alphabet) {            \
    return CppCore::BaseX::tryparse(in, *(block*)out, alphabet);                            \
  }

unsigned int cppcore_basex_estimate_bits(unsigned int symbols, unsigned int base) {
   return CppCore::BaseX::estimateBits(symbols, base);
}
unsigned int cppcore_basex_estimate_symbols(unsigned int bits, unsigned int base) {
   return CppCore::BaseX::estimateSymbols(bits, base);
}

CPPCORE_BASEX_IMPLEMENTATION(32,       std::uint32_t)
CPPCORE_BASEX_IMPLEMENTATION(64,       std::uint64_t)
CPPCORE_BASEX_IMPLEMENTATION(128,  CppCore::Block128)
CPPCORE_BASEX_IMPLEMENTATION(256,  CppCore::Block256)
CPPCORE_BASEX_IMPLEMENTATION(512,  CppCore::Block512)
CPPCORE_BASEX_IMPLEMENTATION(1024, CppCore::Block1024)
CPPCORE_BASEX_IMPLEMENTATION(2048, CppCore::Block2048)
CPPCORE_BASEX_IMPLEMENTATION(4096, CppCore::Block4096)
CPPCORE_BASEX_IMPLEMENTATION(8192, CppCore::Block8192)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HASH
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Hash/MD5.h>
#include <CppCore/Hash/SHA2.h>
#include <CppCore/Hash/CRC32.h>
#include <CppCore/Hash/Murmur3.h>

#define CPPCORE_HASH_IMPLEMENTATION(name, cname)                                                             \
  name* name ## _init     ()                                        { return _CPPCORE_ALLOC(name, cname);  } \
  void  name ## _destroy  (name* hsh)                               { _CPPCORE_FREE(hsh);                  } \
  void  name ## _reset    (name* hsh)                               { ((cname*)hsh)->reset();              } \
  void  name ## _blockstep(name* hsh, void* data, unsigned int len) { ((cname*)hsh)->blockstep(data, len); } \
  void  name ## _step     (name* hsh, void* data, unsigned int len) { ((cname*)hsh)->step(data, len);      } \
  void  name ## _finish   (name* hsh, void* digest)                 { ((cname*)hsh)->finish(digest);       }

CPPCORE_HASH_IMPLEMENTATION(cppcore_md5,     CppCore::MD5)
CPPCORE_HASH_IMPLEMENTATION(cppcore_sha256,  CppCore::SHA256)
CPPCORE_HASH_IMPLEMENTATION(cppcore_sha512,  CppCore::SHA512)
CPPCORE_HASH_IMPLEMENTATION(cppcore_crc32,   CppCore::CRC32)
CPPCORE_HASH_IMPLEMENTATION(cppcore_crc32c,  CppCore::CRC32C)
CPPCORE_HASH_IMPLEMENTATION(cppcore_murmur3, CppCore::Murmur3)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HMAC
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Crypto/HMAC.h>

#define CPPCORE_HMAC_IMPLEMENTATION(name, cname)                                                           \
  name* name ## _init   ()                                        { return _CPPCORE_ALLOC(name, cname);  } \
  void  name ## _destroy(name* hsh)                               { _CPPCORE_FREE(hsh);                  } \
  void  name ## _reset  (name* hsh, void* key,  unsigned int len) { ((cname*)hsh)->reset(key, len);      } \
  void  name ## _step   (name* hsh, void* data, unsigned int len) { ((cname*)hsh)->step(data, len);      } \
  void  name ## _finish (name* hsh, void* digest)                 { ((cname*)hsh)->finish(digest);       }

CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_md5,    CppCore::HMACMD5)
CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_sha256, CppCore::HMACSHA256)
CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_sha512, CppCore::HMACSHA512)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PBKDF2
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Crypto/PBKDF2.h>

#define CPPCORE_PBKDF2_IMPLEMENTATION(name, classname) \
  void name ## _create(                                \
    void* pw,     unsigned int lenpw,                  \
    void* salt,   unsigned int lensalt,                \
    void* digest, unsigned int lendigest,              \
    unsigned int iterations)                           \
  {                                                    \
    classname pbkdf2;                                  \
    pbkdf2.create(                                     \
      pw, lenpw,                                       \
      salt, lensalt,                                   \
      iterations,                                      \
      digest, lendigest);                              \
  }

CPPCORE_PBKDF2_IMPLEMENTATION(cppcore_pbkdf2_md5,    CppCore::PBKDF2MD5)
CPPCORE_PBKDF2_IMPLEMENTATION(cppcore_pbkdf2_sha256, CppCore::PBKDF2SHA256)
CPPCORE_PBKDF2_IMPLEMENTATION(cppcore_pbkdf2_sha512, CppCore::PBKDF2SHA512)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DH
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Memory.h>
#include <CppCore/Crypto/DH.h>

// macro for dh declarations
#define CPPCORE_DH_IMPLEMENTATION(name, cname)                                                                           \
  name* name ## _init         ()                                   { return _CPPCORE_ALLOC(name, cname);               } \
  void  name ## _destroy      (name* dh)                           { _CPPCORE_FREE((cname*)dh);                        } \
  void  name ## _reset        (name* dh, unsigned int certainty)   { ((cname*)dh)->reset(certainty);                   } \
  void  name ## _reset_pg     (name* dh, void* p, void* g)         { ((cname*)dh)->reset(p,g);                         } \
  void  name ## _reset_pgv    (name* dh, void* p, void* g, void* v){ ((cname*)dh)->reset(p,g,v);                       } \
  void  name ## _genkey       (name* dh, void* V)                  { ((cname*)dh)->genkey(V);                          } \
  void  name ## _getprime     (name* dh, void* p)                  { CppCore::Memory::singlecopy(p, &((cname*)dh)->p); } \
  void  name ## _getconstant  (name* dh, void* g)                  { CppCore::Memory::singlecopy(g, &((cname*)dh)->g); } \
  void  name ## _getprivkey   (name* dh, void* v)                  { CppCore::Memory::singlecopy(v, &((cname*)dh)->v); } \
  void  name ## _getpubkey    (name* dh, void* V)                  { CppCore::Memory::singlecopy(V, &((cname*)dh)->V); } \
  void  name ## _getsessionkey(name* dh, void* k)                  { CppCore::Memory::singlecopy(k, &((cname*)dh)->k); }

CPPCORE_DH_IMPLEMENTATION(cppcore_dh128,  CppCore::DH128)
CPPCORE_DH_IMPLEMENTATION(cppcore_dh256,  CppCore::DH256)
CPPCORE_DH_IMPLEMENTATION(cppcore_dh512,  CppCore::DH512)
CPPCORE_DH_IMPLEMENTATION(cppcore_dh1024, CppCore::DH1024)
CPPCORE_DH_IMPLEMENTATION(cppcore_dh2048, CppCore::DH2048)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AES
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Crypto/AES.h>

#define CPPCORE_AES_IMPLEMENTATION(name, cname)                                                                                  \
  name* name ## _init       ()                                                    { return _CPPCORE_ALLOC(name, cname);        } \
  void  name ## _destroy    (name* aes)                                           { _CPPCORE_FREE(aes);                        } \
  void  name ## _reset      (name* aes,void* key)                                 { ((cname*)aes)->reset(key);                 } \
  void  name ## _encrypt_ecb(name* aes,void* in,void* out,unsigned int n)         { ((cname*)aes)->encryptECB(in, out, n);     } \
  void  name ## _decrypt_ecb(name* aes,void* in,void* out,unsigned int n)         { ((cname*)aes)->decryptECB(in, out, n);     } \
  void  name ## _encrypt_cbc(name* aes,void* in,void* out,void* iv,unsigned int n){ ((cname*)aes)->encryptCBC(in, out, iv, n); } \
  void  name ## _decrypt_cbc(name* aes,void* in,void* out,void* iv,unsigned int n){ ((cname*)aes)->decryptCBC(in, out, iv, n); } \
  void  name ## _encrypt_ctr(name* aes,void* in,void* out,void* iv,unsigned int n){ ((cname*)aes)->encryptCTR(in, out, iv, n); } \
  void  name ## _decrypt_ctr(name* aes,void* in,void* out,void* iv,unsigned int n){ ((cname*)aes)->decryptCTR(in, out, iv, n); }

CPPCORE_AES_IMPLEMENTATION(cppcore_aes128, CppCore::AES128)
CPPCORE_AES_IMPLEMENTATION(cppcore_aes192, CppCore::AES192)
CPPCORE_AES_IMPLEMENTATION(cppcore_aes256, CppCore::AES256)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PRIMES
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Memory.h>
#include <CppCore/Math/BigInt.h>
#include <CppCore/Math/Primes.h>

#define CPPCORE_PRIME_IMPLEMENTATION(name, classname)                             \
  int  name ## _test(void* data, unsigned int sign, unsigned int certainty) {     \
    classname v;                                                                  \
    CppCore::Memory::singlecopy(&v, data);                                        \
    return CppCore::Primes::isprime(v, (bool)sign, certainty);                    \
  }                                                                               \
  void name ## _generate(void* data, unsigned int sign, unsigned int certainty) { \
    classname v;                                                                  \
    CppCore::Primes::genprime(v, (bool)sign, certainty);                          \
    CppCore::Memory::singlecopy(data, &v);                                        \
  }

CPPCORE_PRIME_IMPLEMENTATION(cppcore_prime32,       std::uint32_t)
CPPCORE_PRIME_IMPLEMENTATION(cppcore_prime64,       std::uint64_t)
CPPCORE_PRIME_IMPLEMENTATION(cppcore_prime128,  CppCore::uint128_t)
CPPCORE_PRIME_IMPLEMENTATION(cppcore_prime256,  CppCore::uint256_t)
CPPCORE_PRIME_IMPLEMENTATION(cppcore_prime512,  CppCore::uint512_t)
CPPCORE_PRIME_IMPLEMENTATION(cppcore_prime1024, CppCore::uint1024_t)
CPPCORE_PRIME_IMPLEMENTATION(cppcore_prime2048, CppCore::uint2048_t)
