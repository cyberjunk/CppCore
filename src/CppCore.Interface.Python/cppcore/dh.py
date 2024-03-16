from cppcore.lib.libcppcore import lib
from cppcore.primes import DEFAULT_CERTAINTY
import ctypes
import sys

lib.cppcore_dh128_init.restype = \
lib.cppcore_dh256_init.restype = \
lib.cppcore_dh512_init.restype = \
lib.cppcore_dh1024_init.restype = \
lib.cppcore_dh2048_init.restype = ctypes.c_void_p

lib.cppcore_dh128_destroy.argtypes = \
lib.cppcore_dh256_destroy.argtypes = \
lib.cppcore_dh512_destroy.argtypes = \
lib.cppcore_dh1024_destroy.argtypes = \
lib.cppcore_dh2048_destroy.argtypes = \
[
    ctypes.c_void_p  # handle
]

lib.cppcore_dh128_reset.argtypes = \
lib.cppcore_dh256_reset.argtypes = \
lib.cppcore_dh512_reset.argtypes = \
lib.cppcore_dh1024_reset.argtypes = \
lib.cppcore_dh2048_reset.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_uint32   # certainty
]

lib.cppcore_dh128_reset_pg.argtypes = \
lib.cppcore_dh256_reset_pg.argtypes = \
lib.cppcore_dh512_reset_pg.argtypes = \
lib.cppcore_dh1024_reset_pg.argtypes = \
lib.cppcore_dh2048_reset_pg.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p,  # p: large prime
    ctypes.c_void_p   # g: random < large prime
]

lib.cppcore_dh128_reset_pgv.argtypes = \
lib.cppcore_dh256_reset_pgv.argtypes = \
lib.cppcore_dh512_reset_pgv.argtypes = \
lib.cppcore_dh1024_reset_pgv.argtypes = \
lib.cppcore_dh2048_reset_pgv.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p,  # p: large prime
    ctypes.c_void_p,  # g: random < large prime
    ctypes.c_void_p   # v: private key
]

lib.cppcore_dh128_genkey.argtypes = \
lib.cppcore_dh256_genkey.argtypes = \
lib.cppcore_dh512_genkey.argtypes = \
lib.cppcore_dh1024_genkey.argtypes = \
lib.cppcore_dh2048_genkey.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p   # V: public key of other party
]

lib.cppcore_dh128_getprime.argtypes = \
lib.cppcore_dh256_getprime.argtypes = \
lib.cppcore_dh512_getprime.argtypes = \
lib.cppcore_dh1024_getprime.argtypes = \
lib.cppcore_dh2048_getprime.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p   # p: large prime
]

lib.cppcore_dh128_getconstant.argtypes = \
lib.cppcore_dh256_getconstant.argtypes = \
lib.cppcore_dh512_getconstant.argtypes = \
lib.cppcore_dh1024_getconstant.argtypes = \
lib.cppcore_dh2048_getconstant.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p   # g: random < large prime
]

lib.cppcore_dh128_getprivkey.argtypes = \
lib.cppcore_dh256_getprivkey.argtypes = \
lib.cppcore_dh512_getprivkey.argtypes = \
lib.cppcore_dh1024_getprivkey.argtypes = \
lib.cppcore_dh2048_getprivkey.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p   # v: private key
]

lib.cppcore_dh128_getpubkey.argtypes = \
lib.cppcore_dh256_getpubkey.argtypes = \
lib.cppcore_dh512_getpubkey.argtypes = \
lib.cppcore_dh1024_getpubkey.argtypes = \
lib.cppcore_dh2048_getpubkey.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p   # V: public key of other party
]

lib.cppcore_dh128_getsessionkey.argtypes = \
lib.cppcore_dh256_getsessionkey.argtypes = \
lib.cppcore_dh512_getsessionkey.argtypes = \
lib.cppcore_dh1024_getsessionkey.argtypes = \
lib.cppcore_dh2048_getsessionkey.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p   # k: session key
]

####################################################################

class DH:
    def __init__(self):    
        self._h = self._init()
    def __del__(self):
        self._destroy(self._h)
    def reset(self, certainty:int=DEFAULT_CERTAINTY):
        """Generates prime, constant and private + public key"""
        self._reset(self._h, certainty)
    def reset_pg(self, p:int, g:int):
        """Uses predefined prime, constant and generates private + public key"""
        self._reset_pg(self._h,
            p.to_bytes(self._nbytes, byteorder=sys.byteorder),
            g.to_bytes(self._nbytes, byteorder=sys.byteorder))
    def reset_pgv(self, p:int, g:int, v:int):
        """Uses predefined prime, constant and private key. Generates only public key."""
        self._reset_pgv(self._h,
            p.to_bytes(self._nbytes, byteorder=sys.byteorder),
            g.to_bytes(self._nbytes, byteorder=sys.byteorder),
            v.to_bytes(self._nbytes, byteorder=sys.byteorder))
    def genkey(self, V:int) -> int:
        """Generates the session key from public key of other party"""
        self._genkey(self._h,
            V.to_bytes(self._nbytes, byteorder=sys.byteorder))
        return self.getsessionkey()
    def getprime(self) -> int:
        """Returns the prime"""
        p=bytes(self._nbytes); self._getprime(self._h, p)
        return int.from_bytes(p, byteorder=sys.byteorder)
    def getconstant(self) -> int:
        """Returns the constant"""
        g=bytes(self._nbytes); self._getconstant(self._h, g)
        return int.from_bytes(g, byteorder=sys.byteorder)
    def getprivkey(self) -> int:
        """Returns the private key"""
        v=bytes(self._nbytes); self._getprivkey(self._h, v)
        return int.from_bytes(v, byteorder=sys.byteorder)
    def getpubkey(self) -> int:
        """Returns the public key"""
        V=bytes(self._nbytes); self._getpubkey(self._h, V)
        return int.from_bytes(V, byteorder=sys.byteorder)
    def getsessionkey(self) -> int:
        """Returns the session key"""
        k=bytes(self._nbytes); self._getsessionkey(self._h, k)
        return int.from_bytes(k, byteorder=sys.byteorder)

####################################################################

class DH128(DH):
    """Diffie-Hellman 128-Bit Key Exchange"""
    def __init__(self):
        self._nbytes        = 16
        self._init          = lib.cppcore_dh128_init
        self._destroy       = lib.cppcore_dh128_destroy
        self._reset         = lib.cppcore_dh128_reset
        self._reset_pg      = lib.cppcore_dh128_reset_pg
        self._reset_pgv     = lib.cppcore_dh128_reset_pgv
        self._genkey        = lib.cppcore_dh128_genkey
        self._getprime      = lib.cppcore_dh128_getprime
        self._getconstant   = lib.cppcore_dh128_getconstant
        self._getprivkey    = lib.cppcore_dh128_getprivkey
        self._getpubkey     = lib.cppcore_dh128_getpubkey
        self._getsessionkey = lib.cppcore_dh128_getsessionkey
        super().__init__()

class DH256(DH):
    """Diffie-Hellman 256-Bit Key Exchange"""
    def __init__(self):
        self._nbytes        = 32
        self._init          = lib.cppcore_dh256_init
        self._destroy       = lib.cppcore_dh256_destroy
        self._reset         = lib.cppcore_dh256_reset
        self._reset_pg      = lib.cppcore_dh256_reset_pg
        self._reset_pgv     = lib.cppcore_dh256_reset_pgv
        self._genkey        = lib.cppcore_dh256_genkey
        self._getprime      = lib.cppcore_dh256_getprime
        self._getconstant   = lib.cppcore_dh256_getconstant
        self._getprivkey    = lib.cppcore_dh256_getprivkey
        self._getpubkey     = lib.cppcore_dh256_getpubkey
        self._getsessionkey = lib.cppcore_dh256_getsessionkey
        super().__init__()

class DH512(DH):
    """Diffie-Hellman 512-Bit Key Exchange"""
    def __init__(self):
        self._nbytes        = 64
        self._init          = lib.cppcore_dh512_init
        self._destroy       = lib.cppcore_dh512_destroy
        self._reset         = lib.cppcore_dh512_reset
        self._reset_pg      = lib.cppcore_dh512_reset_pg
        self._reset_pgv     = lib.cppcore_dh512_reset_pgv
        self._genkey        = lib.cppcore_dh512_genkey
        self._getprime      = lib.cppcore_dh512_getprime
        self._getconstant   = lib.cppcore_dh512_getconstant
        self._getprivkey    = lib.cppcore_dh512_getprivkey
        self._getpubkey     = lib.cppcore_dh512_getpubkey
        self._getsessionkey = lib.cppcore_dh512_getsessionkey
        super().__init__()

class DH1024(DH):
    """Diffie-Hellman 1024-Bit Key Exchange"""
    def __init__(self):
        self._nbytes        = 128
        self._init          = lib.cppcore_dh1024_init
        self._destroy       = lib.cppcore_dh1024_destroy
        self._reset         = lib.cppcore_dh1024_reset
        self._reset_pg      = lib.cppcore_dh1024_reset_pg
        self._reset_pgv     = lib.cppcore_dh1024_reset_pgv
        self._genkey        = lib.cppcore_dh1024_genkey
        self._getprime      = lib.cppcore_dh1024_getprime
        self._getconstant   = lib.cppcore_dh1024_getconstant
        self._getprivkey    = lib.cppcore_dh1024_getprivkey
        self._getpubkey     = lib.cppcore_dh1024_getpubkey
        self._getsessionkey = lib.cppcore_dh1024_getsessionkey
        super().__init__()

class DH2048(DH):
    """Diffie-Hellman 2048-Bit Key Exchange"""
    def __init__(self):
        self._nbytes        = 256
        self._init          = lib.cppcore_dh2048_init
        self._destroy       = lib.cppcore_dh2048_destroy
        self._reset         = lib.cppcore_dh2048_reset
        self._reset_pg      = lib.cppcore_dh2048_reset_pg
        self._reset_pgv     = lib.cppcore_dh2048_reset_pgv
        self._genkey        = lib.cppcore_dh2048_genkey
        self._getprime      = lib.cppcore_dh2048_getprime
        self._getconstant   = lib.cppcore_dh2048_getconstant
        self._getprivkey    = lib.cppcore_dh2048_getprivkey
        self._getpubkey     = lib.cppcore_dh2048_getpubkey
        self._getsessionkey = lib.cppcore_dh2048_getsessionkey
        super().__init__()
