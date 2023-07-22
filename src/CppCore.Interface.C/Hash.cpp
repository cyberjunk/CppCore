
// PUBLIC C INTERFACES
#include <CppCore.Interface.C/Hash.h>

// PRIVATE CPP IMPLEMENTATIONS
#include <CppCore/Hash/MD5.h>
#include <CppCore/Hash/SHA2.h>
#include <CppCore/Hash/CRC32.h>

// macro for function implementations
#define CPPCORE_HASH_IMPLEMENTATION(name, classname)                                                               \
  name* name ## _init   ()                                  { return (name*) new classname();     } \
  void  name ## _destroy(name* hsh)                         { delete (classname*)hsh;             } \
  void  name ## _reset  (name* hsh)                         { ((classname*)hsh)->reset();         } \
  void  name ## _step   (name* hsh, void* data, size_t len) { ((classname*)hsh)->step(data, len); } \
  void  name ## _finish (name* hsh, void* digest)           { ((classname*)hsh)->finish(digest);  }

// generate generic function implementations

CPPCORE_HASH_IMPLEMENTATION(cppcore_md5,    CppCore::MD5)
CPPCORE_HASH_IMPLEMENTATION(cppcore_sha256, CppCore::SHA256)
CPPCORE_HASH_IMPLEMENTATION(cppcore_sha512, CppCore::SHA512)

CPPCORE_HASH_IMPLEMENTATION(cppcore_crc32,  CppCore::CRC32)
CPPCORE_HASH_IMPLEMENTATION(cppcore_crc32c, CppCore::CRC32C)
