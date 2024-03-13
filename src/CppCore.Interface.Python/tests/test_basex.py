import cppcore.basex
import sys

ALPHABET10 = "0123456789"
ALPHABET62 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

MAX32B  :bytes = b'\xff\xff\xff\xff'
MAX64B  :bytes = MAX32B + MAX32B
MAX128B :bytes = MAX64B + MAX64B
MAX256B :bytes = MAX128B + MAX128B
MAX512B :bytes = MAX256B + MAX256B
MAX1024B:bytes = MAX512B + MAX512B
MAX2048B:bytes = MAX1024B + MAX1024B

MAX32I :int = int.from_bytes(bytes=MAX32B, byteorder=sys.byteorder, signed=False)
MAX64I :int = int.from_bytes(bytes=MAX64B, byteorder=sys.byteorder, signed=False)
MAX128I:int = int.from_bytes(bytes=MAX128B, byteorder=sys.byteorder, signed=False)
MAX256I:int = int.from_bytes(bytes=MAX256B, byteorder=sys.byteorder, signed=False)

def test_simple1():
    assert(cppcore.basex.encode(0, ALPHABET10) == "0")

def test_max_b10():
    assert(cppcore.basex.encode(MAX32I,  ALPHABET10) == str(MAX32I))
    assert(cppcore.basex.encode(MAX64I,  ALPHABET10) == str(MAX64I))
    assert(cppcore.basex.encode(MAX128I, ALPHABET10) == str(MAX128I))
    assert(cppcore.basex.encode(MAX256I, ALPHABET10) == str(MAX256I))
