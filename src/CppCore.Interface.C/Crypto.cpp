
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
// HASH
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Hash/MD5.h>
#include <CppCore/Hash/SHA2.h>
#include <CppCore/Hash/CRC32.h>
#include <CppCore/Hash/Murmur3.h>

#define CPPCORE_HASH_IMPLEMENTATION(name, classname)                                                \
  name* name ## _init   ()                                  { return (name*) new classname();     } \
  void  name ## _destroy(name* hsh)                         { delete (classname*)hsh;             } \
  void  name ## _reset  (name* hsh)                         { ((classname*)hsh)->reset();         } \
  void  name ## _step   (name* hsh, void* data, size_t len) { ((classname*)hsh)->step(data, len); } \
  void  name ## _finish (name* hsh, void* digest)           { ((classname*)hsh)->finish(digest);  }

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

#define CPPCORE_HMAC_IMPLEMENTATION(name, classname)                                                \
  name* name ## _init   ()                                  { return (name*) new classname();     } \
  void  name ## _destroy(name* hsh)                         { delete (classname*)hsh;             } \
  void  name ## _reset  (name* hsh, void* key,  size_t len) { ((classname*)hsh)->reset(key, len); } \
  void  name ## _step   (name* hsh, void* data, size_t len) { ((classname*)hsh)->step(data, len); } \
  void  name ## _finish (name* hsh, void* digest)           { ((classname*)hsh)->finish(digest);  }

CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_md5,     CppCore::HMACMD5)
CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_sha256,  CppCore::HMACSHA256)
CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_sha512,  CppCore::HMACSHA512)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PBKDF2
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Crypto/PBKDF2.h>

#define CPPCORE_PBKDF2_IMPLEMENTATION(name, classname) \
  void name ## _create(                                \
    void*  pw,     size_t lenpw,                       \
    void*  salt,   size_t lensalt,                     \
    void*  digest, size_t lendigest,                   \
    size_t iterations)                                 \
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
// PRIMES
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <CppCore/Memory.h>
#include <CppCore/Math/BigInt.h>

#define CPPCORE_PRIME_IMPLEMENTATION(name, classname, copyop1, copyop2)                                       \
  int  name ## _test    (void* data, size_t certainty) { classname v; copyop1; return v.isprime(certainty); } \
  void name ## _generate(void* data, size_t certainty) { classname v; v.genprime(certainty); copyop2;       }

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
