from cppcore.lib.libcppcore import lib
import ctypes

lib.cppcore_aes128_init.restype = \
lib.cppcore_aes192_init.restype = \
lib.cppcore_aes256_init.restype = ctypes.c_void_p

lib.cppcore_aes128_destroy.argtypes = \
lib.cppcore_aes192_destroy.argtypes = \
lib.cppcore_aes256_destroy.argtypes = \
[
    ctypes.c_void_p  # handle
]

lib.cppcore_aes128_reset.argtypes = \
lib.cppcore_aes192_reset.argtypes = \
lib.cppcore_aes256_reset.argtypes = \
[
    ctypes.c_void_p, # handle
    ctypes.c_void_p  # key
]

lib.cppcore_aes128_encrypt_ecb.argtypes = \
lib.cppcore_aes192_encrypt_ecb.argtypes = \
lib.cppcore_aes256_encrypt_ecb.argtypes = \
[
    ctypes.c_void_p, # handle
    ctypes.c_void_p, # input
    ctypes.c_void_p, # output
    ctypes.c_uint32  # blocks
]

lib.cppcore_aes128_decrypt_ecb.argtypes = \
lib.cppcore_aes192_decrypt_ecb.argtypes = \
lib.cppcore_aes256_decrypt_ecb.argtypes = \
[
    ctypes.c_void_p, # handle
    ctypes.c_void_p, # input
    ctypes.c_void_p, # output
    ctypes.c_uint32  # blocks
]

lib.cppcore_aes128_encrypt_cbc.argtypes = \
lib.cppcore_aes192_encrypt_cbc.argtypes = \
lib.cppcore_aes256_encrypt_cbc.argtypes = \
[
    ctypes.c_void_p, # handle
    ctypes.c_void_p, # input
    ctypes.c_void_p, # output
    ctypes.c_void_p, # iv
    ctypes.c_uint32  # blocks
]

lib.cppcore_aes128_decrypt_cbc.argtypes = \
lib.cppcore_aes192_decrypt_cbc.argtypes = \
lib.cppcore_aes256_decrypt_cbc.argtypes = \
[
    ctypes.c_void_p, # handle
    ctypes.c_void_p, # input
    ctypes.c_void_p, # output
    ctypes.c_void_p, # iv
    ctypes.c_uint32  # blocks
]

lib.cppcore_aes128_encrypt_ctr.argtypes = \
lib.cppcore_aes192_encrypt_ctr.argtypes = \
lib.cppcore_aes256_encrypt_ctr.argtypes = \
[
    ctypes.c_void_p, # handle
    ctypes.c_void_p, # input
    ctypes.c_void_p, # output
    ctypes.c_void_p, # iv
    ctypes.c_uint32  # blocks
]

lib.cppcore_aes128_decrypt_ctr.argtypes = \
lib.cppcore_aes192_decrypt_ctr.argtypes = \
lib.cppcore_aes256_decrypt_ctr.argtypes = \
[
    ctypes.c_void_p, # handle
    ctypes.c_void_p, # input
    ctypes.c_void_p, # output
    ctypes.c_void_p, # iv
    ctypes.c_uint32  # blocks
]

################################################################
# ECB
################################################################

class AES128ECB:
    h:ctypes.c_void_p
    def __init__(self):
        self.h = lib.cppcore_aes128_init()
    def __del__(self):
        lib.cppcore_aes128_destroy(self.h)
    def reset(self, key:bytes):
        if len(key) != 16: raise ValueError("Key must be 16 bytes")
        lib.cppcore_aes128_reset(self.h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes128_encrypt_ecb(self.h, data, o, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes128_decrypt_ecb(self.h, data, o, n[0])
        return o

class AES192ECB:
    h:ctypes.c_void_p
    def __init__(self):
        self.h = lib.cppcore_aes192_init()
    def __del__(self):
        lib.cppcore_aes192_destroy(self.h)
    def reset(self, key:bytes):
        if len(key) != 24: raise ValueError("Key must be 24 bytes")
        lib.cppcore_aes192_reset(self.h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes192_encrypt_ecb(self.h, data, o, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes192_decrypt_ecb(self.h, data, o, n[0])
        return o

class AES256ECB:
    h:ctypes.c_void_p
    def __init__(self):
        self.h = lib.cppcore_aes256_init()
    def __del__(self):
        lib.cppcore_aes256_destroy(self.h)
    def reset(self, key:bytes):
        if len(key) != 32: raise ValueError("Key must be 32 bytes")
        lib.cppcore_aes256_reset(self.h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes256_encrypt_ecb(self.h, data, o, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes256_decrypt_ecb(self.h, data, o, n[0])
        return o

################################################################
# CBC
################################################################

class AES128CBC:
    h:ctypes.c_void_p
    ivenc:bytes=bytes(16)
    ivdec:bytes=bytes(16)
    def __init__(self):
        self.h = lib.cppcore_aes128_init()
    def __del__(self):
        lib.cppcore_aes128_destroy(self.h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 16: raise ValueError("Key must be 16 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self.ivenc = bytes(bytearray(iv))
        self.ivdec = bytes(bytearray(iv))
        lib.cppcore_aes128_reset(self.h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes128_encrypt_cbc(self.h, data, o, self.ivenc, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes128_decrypt_cbc(self.h, data, o, self.ivdec, n[0])
        return o
    
class AES192CBC:
    h:ctypes.c_void_p
    ivenc:bytes=bytes(16)
    ivdec:bytes=bytes(16)
    def __init__(self):
        self.h = lib.cppcore_aes192_init()
    def __del__(self):
        lib.cppcore_aes192_destroy(self.h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 24: raise ValueError("Key must be 24 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self.ivenc = bytes(bytearray(iv))
        self.ivdec = bytes(bytearray(iv))
        lib.cppcore_aes192_reset(self.h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes192_encrypt_cbc(self.h, data, o, self.ivenc, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes192_decrypt_cbc(self.h, data, o, self.ivdec, n[0])
        return o

class AES256CBC:
    h:ctypes.c_void_p
    ivenc:bytes=bytes(16)
    ivdec:bytes=bytes(16)
    def __init__(self):
        self.h = lib.cppcore_aes256_init()
    def __del__(self):
        lib.cppcore_aes256_destroy(self.h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 32: raise ValueError("Key must be 32 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self.ivenc = bytes(bytearray(iv))
        self.ivdec = bytes(bytearray(iv))
        lib.cppcore_aes256_reset(self.h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes256_encrypt_cbc(self.h, data, o, self.ivenc, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes256_decrypt_cbc(self.h, data, o, self.ivdec, n[0])
        return o

################################################################
# CTR
################################################################

class AES128CTR:
    h:ctypes.c_void_p
    ivenc:bytes=bytes(16)
    ivdec:bytes=bytes(16)
    def __init__(self):
        self.h = lib.cppcore_aes128_init()
    def __del__(self):
        lib.cppcore_aes128_destroy(self.h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 16: raise ValueError("Key must be 16 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self.ivenc = bytes(bytearray(iv))
        self.ivdec = bytes(bytearray(iv))
        lib.cppcore_aes128_reset(self.h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes128_encrypt_ctr(self.h, data, o, self.ivenc, l)
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes128_decrypt_ctr(self.h, data, o, self.ivdec, l)
        return o

class AES192CTR:
    h:ctypes.c_void_p
    ivenc:bytes=bytes(16)
    ivdec:bytes=bytes(16)
    def __init__(self):
        self.h = lib.cppcore_aes192_init()
    def __del__(self):
        lib.cppcore_aes192_destroy(self.h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 24: raise ValueError("Key must be 24 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self.ivenc = bytes(bytearray(iv))
        self.ivdec = bytes(bytearray(iv))
        lib.cppcore_aes192_reset(self.h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes192_encrypt_ctr(self.h, data, o, self.ivenc, l)
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes192_decrypt_ctr(self.h, data, o, self.ivdec, l)
        return o

class AES256CTR:
    h:ctypes.c_void_p
    ivenc:bytes=bytes(16)
    ivdec:bytes=bytes(16)
    def __init__(self):
        self.h = lib.cppcore_aes256_init()
    def __del__(self):
        lib.cppcore_aes256_destroy(self.h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 32: raise ValueError("Key must be 32 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self.ivenc = bytes(bytearray(iv))
        self.ivdec = bytes(bytearray(iv))
        lib.cppcore_aes256_reset(self.h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes256_encrypt_ctr(self.h, data, o, self.ivenc, l)
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes256_decrypt_ctr(self.h, data, o, self.ivdec, l)
        return o
