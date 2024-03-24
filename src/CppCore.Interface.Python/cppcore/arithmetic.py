from cppcore.lib.libcppcore import lib
import ctypes
import sys

lib.cppcore_uint32_mulmod.argtypes = \
lib.cppcore_uint64_mulmod.argtypes = \
lib.cppcore_uint128_mulmod.argtypes = \
lib.cppcore_uint256_mulmod.argtypes = \
lib.cppcore_uint512_mulmod.argtypes = \
lib.cppcore_uint1024_mulmod.argtypes = \
lib.cppcore_uint2048_mulmod.argtypes = \
lib.cppcore_uint4096_mulmod.argtypes = \
lib.cppcore_uint8192_mulmod.argtypes = \
[
    ctypes.c_void_p, # a
    ctypes.c_void_p, # b
    ctypes.c_void_p, # m
    ctypes.c_void_p  # r
]

lib.cppcore_uint32_powmod.argtypes = \
lib.cppcore_uint64_powmod.argtypes = \
lib.cppcore_uint128_powmod.argtypes = \
lib.cppcore_uint256_powmod.argtypes = \
lib.cppcore_uint512_powmod.argtypes = \
lib.cppcore_uint1024_powmod.argtypes = \
lib.cppcore_uint2048_powmod.argtypes = \
lib.cppcore_uint4096_powmod.argtypes = \
lib.cppcore_uint8192_powmod.argtypes = \
[
    ctypes.c_void_p, # a
    ctypes.c_void_p, # b
    ctypes.c_void_p, # m
    ctypes.c_void_p  # r
]

lib.cppcore_uint32_gcd.argtypes = \
lib.cppcore_uint64_gcd.argtypes = \
lib.cppcore_uint128_gcd.argtypes = \
lib.cppcore_uint256_gcd.argtypes = \
lib.cppcore_uint512_gcd.argtypes = \
lib.cppcore_uint1024_gcd.argtypes = \
lib.cppcore_uint2048_gcd.argtypes = \
lib.cppcore_uint4096_gcd.argtypes = \
lib.cppcore_uint8192_gcd.argtypes = \
[
    ctypes.c_void_p, # a
    ctypes.c_void_p, # b
    ctypes.c_void_p  # r
]

def umulmod(a:int, b:int, m:int) -> int:
    """Calculates (a*b) % m"""
    if a <  0: raise ValueError("Negative a")
    if b <  0: raise ValueError("Negative b")
    if m <= 0: raise ValueError("Negative or zero m")
    bitlen:int = max(a.bit_length(), b.bit_length(), m.bit_length())
    if bitlen <= 32:
        r = bytes(4)
        a = a.to_bytes(4, byteorder=sys.byteorder)
        b = b.to_bytes(4, byteorder=sys.byteorder)
        m = m.to_bytes(4, byteorder=sys.byteorder)
        lib.cppcore_uint32_mulmod(a,b,m,r)
    elif bitlen <= 64:
        r = bytes(8)
        a = a.to_bytes(8, byteorder=sys.byteorder)
        b = b.to_bytes(8, byteorder=sys.byteorder)
        m = m.to_bytes(8, byteorder=sys.byteorder)
        lib.cppcore_uint64_mulmod(a,b,m,r)
    elif bitlen <= 128:
        r = bytes(16)
        a = a.to_bytes(16, byteorder=sys.byteorder)
        b = b.to_bytes(16, byteorder=sys.byteorder)
        m = m.to_bytes(16, byteorder=sys.byteorder)
        lib.cppcore_uint128_mulmod(a,b,m,r)
    elif bitlen <= 256:
        r = bytes(32)
        a = a.to_bytes(32, byteorder=sys.byteorder)
        b = b.to_bytes(32, byteorder=sys.byteorder)
        m = m.to_bytes(32, byteorder=sys.byteorder)
        lib.cppcore_uint256_mulmod(a,b,m,r)
    elif bitlen <= 512:
        r = bytes(64)
        a = a.to_bytes(64, byteorder=sys.byteorder)
        b = b.to_bytes(64, byteorder=sys.byteorder)
        m = m.to_bytes(64, byteorder=sys.byteorder)
        lib.cppcore_uint512_mulmod(a,b,m,r)
    elif bitlen <= 1024:
        r = bytes(128)
        a = a.to_bytes(128, byteorder=sys.byteorder)
        b = b.to_bytes(128, byteorder=sys.byteorder)
        m = m.to_bytes(128, byteorder=sys.byteorder)
        lib.cppcore_uint1024_mulmod(a,b,m,r)
    elif bitlen <= 2048:
        r = bytes(256)
        a = a.to_bytes(256, byteorder=sys.byteorder)
        b = b.to_bytes(256, byteorder=sys.byteorder)
        m = m.to_bytes(256, byteorder=sys.byteorder)
        lib.cppcore_uint2048_mulmod(a,b,m,r)
    elif bitlen <= 4096:
        r = bytes(512)
        a = a.to_bytes(512, byteorder=sys.byteorder)
        b = b.to_bytes(512, byteorder=sys.byteorder)
        m = m.to_bytes(512, byteorder=sys.byteorder)
        lib.cppcore_uint4096_mulmod(a,b,m,r)
    elif bitlen <= 8192:
        r = bytes(1024)
        a = a.to_bytes(1024, byteorder=sys.byteorder)
        b = b.to_bytes(1024, byteorder=sys.byteorder)
        m = m.to_bytes(1024, byteorder=sys.byteorder)
        lib.cppcore_uint8192_mulmod(a,b,m,r)
    else: raise ValueError("Too big. Maximum is 8192 bits")
    return int.from_bytes(r, byteorder=sys.byteorder)

def upowmod(a:int, b:int, m:int) -> int:
    """Calculates (a**b) % m"""
    if a <  0: raise ValueError("Negative a")
    if b <  0: raise ValueError("Negative b")
    if m <= 0: raise ValueError("Negative or zero m")
    bitlen:int = max(a.bit_length(), b.bit_length(), m.bit_length())
    if bitlen <= 32:
        r = bytes(4)
        a = a.to_bytes(4, byteorder=sys.byteorder)
        b = b.to_bytes(4, byteorder=sys.byteorder)
        m = m.to_bytes(4, byteorder=sys.byteorder)
        lib.cppcore_uint32_powmod(a,b,m,r)
    elif bitlen <= 64:
        r = bytes(8)
        a = a.to_bytes(8, byteorder=sys.byteorder)
        b = b.to_bytes(8, byteorder=sys.byteorder)
        m = m.to_bytes(8, byteorder=sys.byteorder)
        lib.cppcore_uint64_powmod(a,b,m,r)
    elif bitlen <= 128:
        r = bytes(16)
        a = a.to_bytes(16, byteorder=sys.byteorder)
        b = b.to_bytes(16, byteorder=sys.byteorder)
        m = m.to_bytes(16, byteorder=sys.byteorder)
        lib.cppcore_uint128_powmod(a,b,m,r)
    elif bitlen <= 256:
        r = bytes(32)
        a = a.to_bytes(32, byteorder=sys.byteorder)
        b = b.to_bytes(32, byteorder=sys.byteorder)
        m = m.to_bytes(32, byteorder=sys.byteorder)
        lib.cppcore_uint256_powmod(a,b,m,r)
    elif bitlen <= 512:
        r = bytes(64)
        a = a.to_bytes(64, byteorder=sys.byteorder)
        b = b.to_bytes(64, byteorder=sys.byteorder)
        m = m.to_bytes(64, byteorder=sys.byteorder)
        lib.cppcore_uint512_powmod(a,b,m,r)
    elif bitlen <= 1024:
        r = bytes(128)
        a = a.to_bytes(128, byteorder=sys.byteorder)
        b = b.to_bytes(128, byteorder=sys.byteorder)
        m = m.to_bytes(128, byteorder=sys.byteorder)
        lib.cppcore_uint1024_powmod(a,b,m,r)
    elif bitlen <= 2048:
        r = bytes(256)
        a = a.to_bytes(256, byteorder=sys.byteorder)
        b = b.to_bytes(256, byteorder=sys.byteorder)
        m = m.to_bytes(256, byteorder=sys.byteorder)
        lib.cppcore_uint2048_powmod(a,b,m,r)
    elif bitlen <= 4096:
        r = bytes(512)
        a = a.to_bytes(512, byteorder=sys.byteorder)
        b = b.to_bytes(512, byteorder=sys.byteorder)
        m = m.to_bytes(512, byteorder=sys.byteorder)
        lib.cppcore_uint4096_powmod(a,b,m,r)
    elif bitlen <= 8192:
        r = bytes(1024)
        a = a.to_bytes(1024, byteorder=sys.byteorder)
        b = b.to_bytes(1024, byteorder=sys.byteorder)
        m = m.to_bytes(1024, byteorder=sys.byteorder)
        lib.cppcore_uint8192_powmod(a,b,m,r)
    else: raise ValueError("Too big. Maximum is 8192 bits")
    return int.from_bytes(r, byteorder=sys.byteorder)

def gcd(a:int, b:int) -> int:
    """Calculates GCD of a and b"""
    if a < 0: raise ValueError("Negative a")
    if b < 0: raise ValueError("Negative b")
    bitlen:int = max(a.bit_length(), b.bit_length())
    if bitlen <= 32:
        r = bytes(4)
        a = a.to_bytes(4, byteorder=sys.byteorder)
        b = b.to_bytes(4, byteorder=sys.byteorder)
        lib.cppcore_uint32_gcd(a,b,r)
    elif bitlen <= 64:
        r = bytes(8)
        a = a.to_bytes(8, byteorder=sys.byteorder)
        b = b.to_bytes(8, byteorder=sys.byteorder)
        lib.cppcore_uint64_gcd(a,b,r)
    elif bitlen <= 128:
        r = bytes(16)
        a = a.to_bytes(16, byteorder=sys.byteorder)
        b = b.to_bytes(16, byteorder=sys.byteorder)
        lib.cppcore_uint128_gcd(a,b,r)
    elif bitlen <= 256:
        r = bytes(32)
        a = a.to_bytes(32, byteorder=sys.byteorder)
        b = b.to_bytes(32, byteorder=sys.byteorder)
        lib.cppcore_uint256_gcd(a,b,r)
    elif bitlen <= 512:
        r = bytes(64)
        a = a.to_bytes(64, byteorder=sys.byteorder)
        b = b.to_bytes(64, byteorder=sys.byteorder)
        lib.cppcore_uint512_gcd(a,b,r)
    elif bitlen <= 1024:
        r = bytes(128)
        a = a.to_bytes(128, byteorder=sys.byteorder)
        b = b.to_bytes(128, byteorder=sys.byteorder)
        lib.cppcore_uint1024_gcd(a,b,r)
    elif bitlen <= 2048:
        r = bytes(256)
        a = a.to_bytes(256, byteorder=sys.byteorder)
        b = b.to_bytes(256, byteorder=sys.byteorder)
        lib.cppcore_uint2048_gcd(a,b,r)
    elif bitlen <= 4096:
        r = bytes(512)
        a = a.to_bytes(512, byteorder=sys.byteorder)
        b = b.to_bytes(512, byteorder=sys.byteorder)
        lib.cppcore_uint4096_gcd(a,b,r)
    elif bitlen <= 8192:
        r = bytes(1024)
        a = a.to_bytes(1024, byteorder=sys.byteorder)
        b = b.to_bytes(1024, byteorder=sys.byteorder)
        lib.cppcore_uint8192_gcd(a,b,r)
    else: raise ValueError("Too big. Maximum is 8192 bits")
    return int.from_bytes(r, byteorder=sys.byteorder)
