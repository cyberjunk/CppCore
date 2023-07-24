
// PUBLIC C INTERFACES
#include <CppCore.Interface.C/HMAC.h>

// PRIVATE CPP IMPLEMENTATIONS
#include <CppCore/Crypto/HMAC.h>

//#include <CppCore/Hash/SHA2.h>
//#include <CppCore/Hash/CRC32.h>
//#include <CppCore/Hash/Murmur3.h>

// macro for function implementations
#define CPPCORE_HMAC_IMPLEMENTATION(name, classname)                                                \
  name* name ## _init   ()                                  { return (name*) new classname();     } \
  void  name ## _destroy(name* hsh)                         { delete (classname*)hsh;             } \
  void  name ## _reset  (name* hsh, void* key,  size_t len) { ((classname*)hsh)->reset(key, len); } \
  void  name ## _step   (name* hsh, void* data, size_t len) { ((classname*)hsh)->step(data, len); } \
  void  name ## _finish (name* hsh, void* digest)           { ((classname*)hsh)->finish(digest);  }

// generate generic function implementations

CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_md5,     CppCore::HMACMD5)
CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_sha256,  CppCore::HMACSHA256)
CPPCORE_HMAC_IMPLEMENTATION(cppcore_hmac_sha512,  CppCore::HMACSHA512)
