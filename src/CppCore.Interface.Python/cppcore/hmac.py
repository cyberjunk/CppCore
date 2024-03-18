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

class HMAC:
    def __init__(self):    
        self._h = self._init()
    def __del__(self):
        self._destroy(self._h)
    def reset(self, key:bytes):
        self._reset(self._h, key, len(key))
    def step(self, data:bytes):
        self._step(self._h, data, len(data))
    def finish(self) -> bytes:
        r = bytes(self._nbytes)
        self._finish(self._h, r)
        return r

class HMACMD5(HMAC):
    def __init__(self):
        self._nbytes    = 16
        self._init      = lib.cppcore_hmac_md5_init
        self._destroy   = lib.cppcore_hmac_md5_destroy
        self._reset     = lib.cppcore_hmac_md5_reset
        self._step      = lib.cppcore_hmac_md5_step
        self._finish    = lib.cppcore_hmac_md5_finish
        super().__init__()

class HMACSHA256(HMAC):
    def __init__(self):
        self._nbytes    = 32
        self._init      = lib.cppcore_hmac_sha256_init
        self._destroy   = lib.cppcore_hmac_sha256_destroy
        self._reset     = lib.cppcore_hmac_sha256_reset
        self._step      = lib.cppcore_hmac_sha256_step
        self._finish    = lib.cppcore_hmac_sha256_finish
        super().__init__()

class HMACSHA512(HMAC):
    def __init__(self):
        self._nbytes    = 64
        self._init      = lib.cppcore_hmac_sha512_init
        self._destroy   = lib.cppcore_hmac_sha512_destroy
        self._reset     = lib.cppcore_hmac_sha512_reset
        self._step      = lib.cppcore_hmac_sha512_step
        self._finish    = lib.cppcore_hmac_sha512_finish
        super().__init__()
