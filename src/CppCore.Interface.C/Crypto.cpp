
// PUBLIC C INTERFACE
#include <CppCore.Interface.C/Crypto.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// HASH
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// private c++ headers
#include <CppCore/Hash/MD5.h>
#include <CppCore/Hash/SHA2.h>
#include <CppCore/Hash/CRC32.h>
#include <CppCore/Hash/Murmur3.h>

// macro for function implementations
#define CPPCORE_HASH_IMPLEMENTATION(name, classname)                                                \
  name* name ## _init   ()                                  { return (name*) new classname();     } \
  void  name ## _destroy(name* hsh)                         { delete (classname*)hsh;             } \
  void  name ## _reset  (name* hsh)                         { ((classname*)hsh)->reset();         } \
  void  name ## _step   (name* hsh, void* data, size_t len) { ((classname*)hsh)->step(data, len); } \
  void  name ## _finish (name* hsh, void* digest)           { ((classname*)hsh)->finish(digest);  }

// function implementations

CPPCORE_HASH_IMPLEMENTATION(cppcore_md5,     CppCore::MD5)
CPPCORE_HASH_IMPLEMENTATION(cppcore_sha256,  CppCore::SHA256)
CPPCORE_HASH_IMPLEMENTATION(cppcore_sha512,  CppCore::SHA512)
CPPCORE_HASH_IMPLEMENTATION(cppcore_crc32,   CppCore::CRC32)
CPPCORE_HASH_IMPLEMENTATION(cppcore_crc32c,  CppCore::CRC32C)
CPPCORE_HASH_IMPLEMENTATION(cppcore_murmur3, CppCore::Murmur3)

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// HMAC
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// private c++ headers
#include <CppCore/Crypto/HMAC.h>

// macro for function implementations
#define CPPCORE_HMAC_IMPLEMENTATION(name, classname)                                                \
  name* name ## _init   ()                                  { return (name*) new classname();     } \
  void  name ## _destroy(name* hsh)                         { delete (classname*)hsh;             } \
  void  name ## _reset  (name* hsh, void* key,  size_t len) { ((classname*)hsh)->reset(key, len); } \
  void  name ## _step   (name* hsh, void* data, size_t len) { ((classname*)hsh)->step(data, len); } \
  void  name ## _finish (name* hsh, void* digest)           { ((classname*)hsh)->finish(digest);  }

// function implementations

CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_md5,     CppCore::HMACMD5)
CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_sha256,  CppCore::HMACSHA256)
CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_sha512,  CppCore::HMACSHA512)
