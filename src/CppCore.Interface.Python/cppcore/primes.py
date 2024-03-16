from cppcore.lib.libcppcore import lib
from enum import IntEnum
import ctypes
import sys

lib.cppcore_prime32_test.argtypes = \
lib.cppcore_prime64_test.argtypes = \
lib.cppcore_prime128_test.argtypes = \
lib.cppcore_prime256_test.argtypes = \
lib.cppcore_prime512_test.argtypes = \
lib.cppcore_prime1024_test.argtypes = \
lib.cppcore_prime2048_test.argtypes = \
[
    ctypes.c_void_p,  # input
    ctypes.c_uint32,  # signed
    ctypes.c_uint32   # certainty
]

lib.cppcore_prime32_generate.argtypes = \
lib.cppcore_prime64_generate.argtypes = \
lib.cppcore_prime128_generate.argtypes = \
lib.cppcore_prime256_generate.argtypes = \
lib.cppcore_prime512_generate.argtypes = \
lib.cppcore_prime1024_generate.argtypes = \
lib.cppcore_prime2048_generate.argtypes = \
[
    ctypes.c_void_p,  # output
    ctypes.c_uint32,  # signed
    ctypes.c_uint32   # certainty
]

DEFAULT_CERTAINTY = 64

class Result(IntEnum):
    NotPrime    = 0
    Prime       = 1
    LikelyPrime = 2

def test(v:int, certainty:int=DEFAULT_CERTAINTY) -> Result:
    """Test v for being prime"""
    bitlen:int = v.bit_length()
    neg:bool   = v < 0
    if   bitlen <=   32: return Result(lib.cppcore_prime32_test  (v.to_bytes(  4, byteorder=sys.byteorder, signed=neg), neg, certainty))
    elif bitlen <=   64: return Result(lib.cppcore_prime64_test  (v.to_bytes(  8, byteorder=sys.byteorder, signed=neg), neg, certainty))
    elif bitlen <=  128: return Result(lib.cppcore_prime128_test (v.to_bytes( 16, byteorder=sys.byteorder, signed=neg), neg, certainty))
    elif bitlen <=  256: return Result(lib.cppcore_prime256_test (v.to_bytes( 32, byteorder=sys.byteorder, signed=neg), neg, certainty))
    elif bitlen <=  512: return Result(lib.cppcore_prime512_test (v.to_bytes( 64, byteorder=sys.byteorder, signed=neg), neg, certainty))
    elif bitlen <= 1024: return Result(lib.cppcore_prime1024_test(v.to_bytes(128, byteorder=sys.byteorder, signed=neg), neg, certainty))
    elif bitlen <= 2048: return Result(lib.cppcore_prime2048_test(v.to_bytes(256, byteorder=sys.byteorder, signed=neg), neg, certainty))
    else:                raise  ValueError("Too big. Maximum is 2048 bits.")

def generate(bitlen:int, certainty:int=DEFAULT_CERTAINTY) -> int:
    """Returns large random prime number with provided bit length."""
    if   bitlen >  2048: raise ValueError("Too big. Maximum is 2048 bits.")
    elif bitlen <=   32: v=bytes(  4); lib.cppcore_prime32_generate  (v, False, certainty)
    elif bitlen <=   64: v=bytes(  8); lib.cppcore_prime64_generate  (v, False, certainty)
    elif bitlen <=  128: v=bytes( 16); lib.cppcore_prime128_generate (v, False, certainty)
    elif bitlen <=  256: v=bytes( 32); lib.cppcore_prime256_generate (v, False, certainty)
    elif bitlen <=  512: v=bytes( 64); lib.cppcore_prime512_generate (v, False, certainty)
    elif bitlen <= 1024: v=bytes(128); lib.cppcore_prime1024_generate(v, False, certainty)
    elif bitlen <= 2048: v=bytes(256); lib.cppcore_prime2048_generate(v, False, certainty)
    return int.from_bytes(v, byteorder=sys.byteorder, signed=False)
