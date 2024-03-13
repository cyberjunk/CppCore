import cppcore.basex
import time
import sys

ALPAHBET10 = "0123456789"
ALPHABET62 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

MAX128B :bytes = b'\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff'
MAX256B :bytes = MAX128B + MAX128B
MAX512B :bytes = MAX256B + MAX256B
MAX1024B:bytes = MAX512B + MAX512B
MAX2048B:bytes = MAX1024B + MAX1024B

def test_1():
    assert(cppcore.basex.encode(0, ALPAHBET10) == "0")
