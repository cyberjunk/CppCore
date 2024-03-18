from cppcore.lib.libcppcore import lib
import ctypes

lib.cppcore_hmac_md5_init.restype = \
lib.cppcore_hmac_sha256_init.restype = \
lib.cppcore_hmac_sha512_init.restype = ctypes.c_void_p

lib.cppcore_hmac_md5_destroy.argtypes = \
lib.cppcore_hmac_sha256_destroy.argtypes = \
lib.cppcore_hmac_sha512_destroy.argtypes = \
[
    ctypes.c_void_p  # handle
]

lib.cppcore_hmac_md5_reset.argtypes = \
lib.cppcore_hmac_sha256_reset.argtypes = \
lib.cppcore_hmac_sha512_reset.argtypes = \
[
    ctypes.c_void_p, # handle
    ctypes.c_void_p, # key
    ctypes.c_uint32  # len

]

lib.cppcore_hmac_md5_step.argtypes = \
lib.cppcore_hmac_sha256_step.argtypes = \
lib.cppcore_hmac_sha512_step.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p,  # data
    ctypes.c_uint32   # len
]

lib.cppcore_hmac_md5_finish.argtypes = \
lib.cppcore_hmac_sha256_finish.argtypes = \
lib.cppcore_hmac_sha512_finish.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p   # digest
]
