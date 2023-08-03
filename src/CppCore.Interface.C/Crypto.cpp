
// public c interface
#include <CppCore.Interface.C/Crypto.h>

// private c++ headers
#include <CppCore/Root.h>

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
#else
int main(int argc, char* argv[])
{
   return 0;
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ENCODING
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Encoding.h>
#include <CppCore/Block.h>

#define CPPCORE_BASEX_IMPLEMENTATION(size,block)                                                  \
  int cppcore_basex_encode##size(                                                                 \
    void*        in,   char* out,      int          len,                                          \
    unsigned int base, char* alphabet, unsigned int writeterm) {                                  \
    return (int)CppCore::BaseX::tostring(*(block*)in, out, len, base, alphabet, writeterm);       \
  }                                                                                               \
  unsigned int cppcore_basex_decode##size(char* in, void* out, unsigned int base, char* alphabet){\
    return CppCore::BaseX::tryparse(in, *(block*)out, alphabet);                            \
  }

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

#define CPPCORE_HASH_IMPLEMENTATION(name, classname)                                                             \
  name* name ## _init     ()                                        { return (name*) new classname();          } \
  void  name ## _destroy  (name* hsh)                               { delete (classname*)hsh;                  } \
  void  name ## _reset    (name* hsh)                               { ((classname*)hsh)->reset();              } \
  void  name ## _blockstep(name* hsh, void* data, unsigned int len) { ((classname*)hsh)->blockstep(data, len); } \
  void  name ## _step     (name* hsh, void* data, unsigned int len) { ((classname*)hsh)->step(data, len);      } \
  void  name ## _finish   (name* hsh, void* digest)                 { ((classname*)hsh)->finish(digest);       }

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

#define CPPCORE_HMAC_IMPLEMENTATION(name, classname)                                                           \
  name* name ## _init   ()                                        { return (name*) new classname();          } \
  void  name ## _destroy(name* hsh)                               { delete (classname*)hsh;                  } \
  void  name ## _reset  (name* hsh, void* key,  unsigned int len) { ((classname*)hsh)->reset(key, len);      } \
  void  name ## _step   (name* hsh, void* data, unsigned int len) { ((classname*)hsh)->step(data, len);      } \
  void  name ## _finish (name* hsh, void* digest)                 { ((classname*)hsh)->finish(digest);       }

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

CPPCORE_PBKDF2_IMPLEMENTATION(cppcore_pbkdf2_sha256, CppCore::PBKDF2SHA256)
CPPCORE_PBKDF2_IMPLEMENTATION(cppcore_pbkdf2_sha512, CppCore::PBKDF2SHA512)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AES
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Crypto/AES.h>

#define CPPCORE_AES_IMPLEMENTATION(name, cname)                                                                                  \
  name* name ## _init       ()                                                    { return (name*) new cname();                } \
  void  name ## _destroy    (name* aes)                                           { delete (cname*)aes;                        } \
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

#define CPPCORE_PRIME_IMPLEMENTATION(name, classname, copyop1, copyop2)                                             \
  int  name ## _test    (void* data, unsigned int certainty) { classname v; copyop1; return v.isprime(certainty); } \
  void name ## _generate(void* data, unsigned int certainty) { classname v; v.genprime(certainty); copyop2;       }

CPPCORE_PRIME_IMPLEMENTATION(
   cppcore_prime128, CppCore::uint128_t,
   CppCore::Memory::singlecopy128 (&v, data),
   CppCore::Memory::singlecopy128 (data, &v))
CPPCORE_PRIME_IMPLEMENTATION(
   cppcore_prime256, CppCore::uint256_t,
   CppCore::Memory::singlecopy256 (&v, data),
   CppCore::Memory::singlecopy256 (data, &v))
CPPCORE_PRIME_IMPLEMENTATION(
   cppcore_prime512, CppCore::uint512_t,
   CppCore::Memory::singlecopy512 (&v, data),
   CppCore::Memory::singlecopy512 (data, &v))
CPPCORE_PRIME_IMPLEMENTATION(
   cppcore_prime1024, CppCore::uint1024_t,
   CppCore::Memory::singlecopy1024(&v, data),
   CppCore::Memory::singlecopy1024(data, &v))
CPPCORE_PRIME_IMPLEMENTATION(
   cppcore_prime2048, CppCore::uint2048_t,
   CppCore::Memory::singlecopy2048(&v, data),
   CppCore::Memory::singlecopy2048(data, &v))
