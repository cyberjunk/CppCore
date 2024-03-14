import cppcore.basex
import sys

ALPHABET02 = "01"
ALPHABET10 = "0123456789"
ALPHABET16 = "0123456789ABCDEF"
ALPHABET62 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

MAX32B  :bytes = b'\xff\xff\xff\xff'
MAX64B  :bytes = MAX32B + MAX32B
MAX128B :bytes = MAX64B + MAX64B
MAX256B :bytes = MAX128B + MAX128B
MAX512B :bytes = MAX256B + MAX256B
MAX1024B:bytes = MAX512B + MAX512B
MAX2048B:bytes = MAX1024B + MAX1024B
MAX4096B:bytes = MAX2048B + MAX2048B
MAX8192B:bytes = MAX4096B + MAX4096B

MAX32I  :int = int.from_bytes(bytes=MAX32B,   byteorder=sys.byteorder, signed=False)
MAX64I  :int = int.from_bytes(bytes=MAX64B,   byteorder=sys.byteorder, signed=False)
MAX128I :int = int.from_bytes(bytes=MAX128B,  byteorder=sys.byteorder, signed=False)
MAX256I :int = int.from_bytes(bytes=MAX256B,  byteorder=sys.byteorder, signed=False)
MAX512I :int = int.from_bytes(bytes=MAX512B,  byteorder=sys.byteorder, signed=False)
MAX1024I:int = int.from_bytes(bytes=MAX1024B, byteorder=sys.byteorder, signed=False)
MAX2048I:int = int.from_bytes(bytes=MAX2048B, byteorder=sys.byteorder, signed=False)
MAX4096I:int = int.from_bytes(bytes=MAX4096B, byteorder=sys.byteorder, signed=False)
MAX8192I:int = int.from_bytes(bytes=MAX8192B, byteorder=sys.byteorder, signed=False)

def test_zero_encode():
    assert(cppcore.basex.encode(0, ALPHABET02) == "0")
    assert(cppcore.basex.encode(0, ALPHABET10) == "0")
    assert(cppcore.basex.encode(0, ALPHABET16) == "0")
    assert(cppcore.basex.encode(0, ALPHABET62) == "0")

def test_zero_decode():
    assert(cppcore.basex.decode("0", ALPHABET02) == 0)
    assert(cppcore.basex.decode("0", ALPHABET10) == 0)
    assert(cppcore.basex.decode("0", ALPHABET16) == 0)
    assert(cppcore.basex.decode("0", ALPHABET62) == 0)

def test_max_b02_encode():
    assert(cppcore.basex.encode(MAX32I,   ALPHABET02) == bin(MAX32I)[2:])
    assert(cppcore.basex.encode(MAX64I,   ALPHABET02) == bin(MAX64I)[2:])
    assert(cppcore.basex.encode(MAX128I,  ALPHABET02) == bin(MAX128I)[2:])
    assert(cppcore.basex.encode(MAX256I,  ALPHABET02) == bin(MAX256I)[2:])
    assert(cppcore.basex.encode(MAX512I,  ALPHABET02) == bin(MAX512I)[2:])
    assert(cppcore.basex.encode(MAX1024I, ALPHABET02) == bin(MAX1024I)[2:])
    assert(cppcore.basex.encode(MAX2048I, ALPHABET02) == bin(MAX2048I)[2:])
    assert(cppcore.basex.encode(MAX4096I, ALPHABET02) == bin(MAX4096I)[2:])
    assert(cppcore.basex.encode(MAX8192I, ALPHABET02) == bin(MAX8192I)[2:])

def test_max_b02_decode():
    assert(cppcore.basex.decode(bin(MAX32I)[2:],   ALPHABET02) == MAX32I)
    assert(cppcore.basex.decode(bin(MAX64I)[2:],   ALPHABET02) == MAX64I)
    assert(cppcore.basex.decode(bin(MAX128I)[2:],  ALPHABET02) == MAX128I)
    assert(cppcore.basex.decode(bin(MAX256I)[2:],  ALPHABET02) == MAX256I)
    assert(cppcore.basex.decode(bin(MAX512I)[2:],  ALPHABET02) == MAX512I)
    assert(cppcore.basex.decode(bin(MAX1024I)[2:], ALPHABET02) == MAX1024I)
    assert(cppcore.basex.decode(bin(MAX2048I)[2:], ALPHABET02) == MAX2048I)
    assert(cppcore.basex.decode(bin(MAX4096I)[2:], ALPHABET02) == MAX4096I)
    assert(cppcore.basex.decode(bin(MAX8192I)[2:], ALPHABET02) == MAX8192I)

def test_max_b10_encode():
    assert(cppcore.basex.encode(MAX32I,   ALPHABET10) == str(MAX32I))
    assert(cppcore.basex.encode(MAX64I,   ALPHABET10) == str(MAX64I))
    assert(cppcore.basex.encode(MAX128I,  ALPHABET10) == str(MAX128I))
    assert(cppcore.basex.encode(MAX256I,  ALPHABET10) == str(MAX256I))
    assert(cppcore.basex.encode(MAX512I,  ALPHABET10) == str(MAX512I))
    assert(cppcore.basex.encode(MAX1024I, ALPHABET10) == str(MAX1024I))
    assert(cppcore.basex.encode(MAX2048I, ALPHABET10) == str(MAX2048I))
    assert(cppcore.basex.encode(MAX4096I, ALPHABET10) == str(MAX4096I))
    assert(cppcore.basex.encode(MAX8192I, ALPHABET10) == str(MAX8192I))

def test_max_b10_decode():
    assert(cppcore.basex.decode(str(MAX32I),   ALPHABET10) == MAX32I)
    assert(cppcore.basex.decode(str(MAX64I),   ALPHABET10) == MAX64I)
    assert(cppcore.basex.decode(str(MAX128I),  ALPHABET10) == MAX128I)
    assert(cppcore.basex.decode(str(MAX256I),  ALPHABET10) == MAX256I)
    assert(cppcore.basex.decode(str(MAX512I),  ALPHABET10) == MAX512I)
    assert(cppcore.basex.decode(str(MAX1024I), ALPHABET10) == MAX1024I)
    assert(cppcore.basex.decode(str(MAX2048I), ALPHABET10) == MAX2048I)
    assert(cppcore.basex.decode(str(MAX4096I), ALPHABET10) == MAX4096I)
    assert(cppcore.basex.decode(str(MAX8192I), ALPHABET10) == MAX8192I)
