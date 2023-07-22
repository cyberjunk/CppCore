
// PUBLIC C INTERFACES
#include <CppCore.Interface.C/Hash.h>

// PRIVATE CPP IMPLEMENTATIONS
#include <CppCore/Root.h>
#include <CppCore/Hash/MD5.h>
#include <CppCore/Hash/SHA2.h>

/////////////////////////////////////////////////////////////////////////////////////
// MD5
/////////////////////////////////////////////////////////////////////////////////////

cppcore_md5* cppcore_md5_init()                                            { return (cppcore_md5*) new CppCore::MD5(); }
void         cppcore_md5_destroy(cppcore_md5* md5)                         { delete (CppCore::MD5*)md5;                }
void         cppcore_md5_reset  (cppcore_md5* md5)                         { ((CppCore::MD5*)md5)->reset();            }
void         cppcore_md5_step   (cppcore_md5* md5, void* data, size_t len) { ((CppCore::MD5*)md5)->step(data, len);    }
void         cppcore_md5_finish (cppcore_md5* md5, void* hash)             { ((CppCore::MD5*)md5)->finish(hash);       }

/////////////////////////////////////////////////////////////////////////////////////
// SHA256
/////////////////////////////////////////////////////////////////////////////////////

cppcore_sha256* cppcore_sha256_init()                                                  { return (cppcore_sha256*) new CppCore::SHA256(); }
void            cppcore_sha256_destroy(cppcore_sha256* sha256)                         { delete (CppCore::SHA256*)sha256;                }
void            cppcore_sha256_reset  (cppcore_sha256* sha256)                         { ((CppCore::SHA256*)sha256)->reset();            }
void            cppcore_sha256_step   (cppcore_sha256* sha256, void* data, size_t len) { ((CppCore::SHA256*)sha256)->step(data, len);    }
void            cppcore_sha256_finish (cppcore_sha256* sha256, void* hash)             { ((CppCore::SHA256*)sha256)->finish(hash);       }
