from cppcore import lib
import ctypes

################################################################
# ECB
################################################################

class AES128ECB:
    _h:ctypes.c_void_p
    def __init__(self):
        self._h = lib.cppcore_aes128_init()
    def __del__(self):
        lib.cppcore_aes128_destroy(self._h)
    def reset(self, key:bytes):
        if len(key) != 16: raise ValueError("Key must be 16 bytes")
        lib.cppcore_aes128_reset(self._h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes128_encrypt_ecb(self._h, data, o, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes128_decrypt_ecb(self._h, data, o, n[0])
        return o

class AES192ECB:
    _h:ctypes.c_void_p
    def __init__(self):
        self._h = lib.cppcore_aes192_init()
    def __del__(self):
        lib.cppcore_aes192_destroy(self._h)
    def reset(self, key:bytes):
        if len(key) != 24: raise ValueError("Key must be 24 bytes")
        lib.cppcore_aes192_reset(self._h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes192_encrypt_ecb(self._h, data, o, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes192_decrypt_ecb(self._h, data, o, n[0])
        return o

class AES256ECB:
    _h:ctypes.c_void_p
    def __init__(self):
        self._h = lib.cppcore_aes256_init()
    def __del__(self):
        lib.cppcore_aes256_destroy(self._h)
    def reset(self, key:bytes):
        if len(key) != 32: raise ValueError("Key must be 32 bytes")
        lib.cppcore_aes256_reset(self._h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes256_encrypt_ecb(self._h, data, o, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("ECB requires multiples of 16")
        lib.cppcore_aes256_decrypt_ecb(self._h, data, o, n[0])
        return o

################################################################
# CBC
################################################################

class AES128CBC:
    _h:ctypes.c_void_p
    _ivenc:bytes=bytes(16)
    _ivdec:bytes=bytes(16)
    def __init__(self):
        self._h = lib.cppcore_aes128_init()
    def __del__(self):
        lib.cppcore_aes128_destroy(self._h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 16: raise ValueError("Key must be 16 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self._ivenc = bytes(bytearray(iv))
        self._ivdec = bytes(bytearray(iv))
        lib.cppcore_aes128_reset(self._h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes128_encrypt_cbc(self._h, data, o, self._ivenc, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes128_decrypt_cbc(self._h, data, o, self._ivdec, n[0])
        return o
    
class AES192CBC:
    _h:ctypes.c_void_p
    _ivenc:bytes=bytes(16)
    _ivdec:bytes=bytes(16)
    def __init__(self):
        self._h = lib.cppcore_aes192_init()
    def __del__(self):
        lib.cppcore_aes192_destroy(self._h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 24: raise ValueError("Key must be 24 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self._ivenc = bytes(bytearray(iv))
        self._ivdec = bytes(bytearray(iv))
        lib.cppcore_aes192_reset(self._h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes192_encrypt_cbc(self._h, data, o, self._ivenc, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes192_decrypt_cbc(self._h, data, o, self._ivdec, n[0])
        return o

class AES256CBC:
    _h:ctypes.c_void_p
    _ivenc:bytes=bytes(16)
    _ivdec:bytes=bytes(16)
    def __init__(self):
        self._h = lib.cppcore_aes256_init()
    def __del__(self):
        lib.cppcore_aes256_destroy(self._h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 32: raise ValueError("Key must be 32 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self._ivenc = bytes(bytearray(iv))
        self._ivdec = bytes(bytearray(iv))
        lib.cppcore_aes256_reset(self._h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes256_encrypt_cbc(self._h, data, o, self._ivenc, n[0])
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l); n = divmod(l, 16)
        if n[1]: raise ValueError("CBC requires multiples of 16")
        lib.cppcore_aes256_decrypt_cbc(self._h, data, o, self._ivdec, n[0])
        return o

################################################################
# CTR
################################################################

class AES128CTR:
    _h:ctypes.c_void_p
    _ivenc:bytes=bytes(16)
    _ivdec:bytes=bytes(16)
    def __init__(self):
        self._h = lib.cppcore_aes128_init()
    def __del__(self):
        lib.cppcore_aes128_destroy(self._h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 16: raise ValueError("Key must be 16 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self._ivenc = bytes(bytearray(iv))
        self._ivdec = bytes(bytearray(iv))
        lib.cppcore_aes128_reset(self._h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes128_encrypt_ctr(self._h, data, o, self._ivenc, l)
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes128_decrypt_ctr(self._h, data, o, self._ivdec, l)
        return o

class AES192CTR:
    _h:ctypes.c_void_p
    _ivenc:bytes=bytes(16)
    _ivdec:bytes=bytes(16)
    def __init__(self):
        self._h = lib.cppcore_aes192_init()
    def __del__(self):
        lib.cppcore_aes192_destroy(self._h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 24: raise ValueError("Key must be 24 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self._ivenc = bytes(bytearray(iv))
        self._ivdec = bytes(bytearray(iv))
        lib.cppcore_aes192_reset(self._h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes192_encrypt_ctr(self._h, data, o, self._ivenc, l)
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes192_decrypt_ctr(self._h, data, o, self._ivdec, l)
        return o

class AES256CTR:
    _h:ctypes.c_void_p
    _ivenc:bytes=bytes(16)
    _ivdec:bytes=bytes(16)
    def __init__(self):
        self._h = lib.cppcore_aes256_init()
    def __del__(self):
        lib.cppcore_aes256_destroy(self._h)
    def reset(self, key:bytes, iv:bytes):
        if len(key) != 32: raise ValueError("Key must be 32 bytes")
        if len(iv)  != 16: raise ValueError("IV must be 16 bytes")
        self._ivenc = bytes(bytearray(iv))
        self._ivdec = bytes(bytearray(iv))
        lib.cppcore_aes256_reset(self._h, key)
    def encrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes256_encrypt_ctr(self._h, data, o, self._ivenc, l)
        return o
    def decrypt(self, data:bytes) -> bytes:
        l = len(data); o = bytes(l)
        lib.cppcore_aes256_decrypt_ctr(self._h, data, o, self._ivdec, l)
        return o
