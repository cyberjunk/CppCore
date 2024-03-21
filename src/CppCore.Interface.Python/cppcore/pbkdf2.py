from cppcore.lib.libcppcore import lib
import ctypes

lib.cppcore_pbkdf2_md5_create.argtypes = \
lib.cppcore_pbkdf2_sha256_create.argtypes = \
lib.cppcore_pbkdf2_sha512_create.argtypes = \
[
    ctypes.c_void_p,  # pw
    ctypes.c_uint32,  # pw len
    ctypes.c_void_p,  # salt
    ctypes.c_uint32,  # salt len
    ctypes.c_void_p,  # digest
    ctypes.c_uint32,  # digest len
    ctypes.c_uint32   # iterations
]

def pbkdf2_md5(pw:bytes, salt:bytes, length:int, iterations:int) -> bytes:
    r = bytes(length)
    lib.cppcore_pbkdf2_md5_create(pw, len(pw), salt, len(salt), r, length, iterations)
    return r

def pbkdf2_sha256(pw:bytes, salt:bytes, length:int, iterations:int) -> bytes:
    r = bytes(length)
    lib.cppcore_pbkdf2_sha256_create(pw, len(pw), salt, len(salt), r, length, iterations)
    return r

def pbkdf2_sha512(pw:bytes, salt:bytes, length:int, iterations:int) -> bytes:
    r = bytes(length)
    lib.cppcore_pbkdf2_sha512_create(pw, len(pw), salt, len(salt), r, length, iterations)
    return r
