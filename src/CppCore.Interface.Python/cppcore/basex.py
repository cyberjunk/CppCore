from cppcore.lib.libcppcore import lib
import ctypes
import sys

lib.cppcore_basex_encode32.argtypes = \
lib.cppcore_basex_encode64.argtypes = \
lib.cppcore_basex_encode128.argtypes = \
lib.cppcore_basex_encode256.argtypes = \
lib.cppcore_basex_encode512.argtypes = \
lib.cppcore_basex_encode1024.argtypes = \
lib.cppcore_basex_encode2048.argtypes = \
lib.cppcore_basex_encode4096.argtypes = \
lib.cppcore_basex_encode8192.argtypes = \
[
    ctypes.c_void_p,  # input
    ctypes.c_char_p,  # output
    ctypes.c_int32,   # len output
    ctypes.c_uint32,  # base
    ctypes.c_char_p,  # alphabet
    ctypes.c_uint32   # write 0x00 term
]

lib.cppcore_basex_decode32.argtypes = \
lib.cppcore_basex_decode64.argtypes = \
lib.cppcore_basex_decode128.argtypes = \
lib.cppcore_basex_decode256.argtypes = \
lib.cppcore_basex_decode512.argtypes = \
lib.cppcore_basex_decode1024.argtypes = \
lib.cppcore_basex_decode2048.argtypes = \
lib.cppcore_basex_decode4096.argtypes = \
lib.cppcore_basex_decode8192.argtypes = \
[
    ctypes.c_char_p,  # input
    ctypes.c_void_p,  # output
    ctypes.c_char_p   # alphabet
]

def encode(v:int, alphabet:str) -> str:
    bitlen:int   = v.bit_length()
    balpha:bytes = str.encode(alphabet, encoding="ascii")
    lalpha:int   = len(balpha)
    if lalpha < 2: raise ValueError("Invalid alphabet")
    if bitlen <= 32:
        output:bytes = bytes(32)
        input :bytes = v.to_bytes(4, byteorder=sys.byteorder)
        lib.cppcore_basex_encode32(input, output, len(output), lalpha, balpha, False)
    elif bitlen <= 64:
        output:bytes = bytes(64)
        input :bytes = v.to_bytes(8, byteorder=sys.byteorder)
        lib.cppcore_basex_encode64(input, output, len(output), lalpha, balpha, False)
    elif bitlen <= 128:
        output:bytes = bytes(128)
        input :bytes = v.to_bytes(16, byteorder=sys.byteorder)
        lib.cppcore_basex_encode128(input, output, len(output), lalpha, balpha, False)
    elif bitlen <= 256:
        output:bytes = bytes(256)
        input :bytes = v.to_bytes(32, byteorder=sys.byteorder)
        lib.cppcore_basex_encode256(input, output, len(output), lalpha, balpha, False)
    elif bitlen <= 512:
        output:bytes = bytes(512)
        input :bytes = v.to_bytes(64, byteorder=sys.byteorder)
        lib.cppcore_basex_encode512(input, output, len(output), lalpha, balpha, False)
    elif bitlen <= 1024:
        output:bytes = bytes(1024)
        input :bytes = v.to_bytes(128, byteorder=sys.byteorder)
        lib.cppcore_basex_encode1024(input, output, len(output), lalpha, balpha, False)
    elif bitlen <= 2048:
        output:bytes = bytes(2048)
        input :bytes = v.to_bytes(256, byteorder=sys.byteorder)
        lib.cppcore_basex_encode2048(input, output, len(output), lalpha, balpha, False)
    elif bitlen <= 4096:
        output:bytes = bytes(4096)
        input :bytes = v.to_bytes(512, byteorder=sys.byteorder)
        lib.cppcore_basex_encode4096(input, output, len(output), lalpha, balpha, False)
    elif bitlen <= 8192:
        output:bytes = bytes(8192)
        input :bytes = v.to_bytes(1024, byteorder=sys.byteorder)
        lib.cppcore_basex_encode8192(input, output, len(output), lalpha, balpha, False)
    else: raise ValueError("Too big. Maximum is 8192 bits.")
    return output.decode(encoding="ascii").rstrip('\x00')

def decode(v:str, alphabet:str, bitlen:int=None) -> int:
    balpha:bytes = str.encode(alphabet, encoding="ascii")
    bvalue:bytes = v.encode(encoding='ascii')
    lalpha:int   = len(balpha)
    if lalpha < 2:
        raise ValueError("Invalid alphabet")
    if bitlen is None: 
        bitlen = lib.cppcore_basex_estimate_bits(len(v), lalpha)
    elif bitlen > 8192:  
        raise ValueError("Too big. Maximum is 8192 bits.")
    if bitlen <= 32:
        output = bytes(4)
        ok = lib.cppcore_basex_decode32(bvalue, output, balpha)
        if not ok: raise ValueError("Value exceeds 32 bits or invalid symbol found.")
    elif bitlen <= 64:
        output = bytes(8)
        ok = lib.cppcore_basex_decode64(bvalue, output, balpha)
        if not ok: raise ValueError("Value exceeds 64 bits or invalid symbol found.")
    elif bitlen <= 128:
        output = bytes(16)
        ok = lib.cppcore_basex_decode128(bvalue, output, balpha)
        if not ok: raise ValueError("Value exceeds 128 bits or invalid symbol found.")
    elif bitlen <= 256:
        output = bytes(32)
        ok = lib.cppcore_basex_decode256(bvalue, output, balpha)
        if not ok: raise ValueError("Value exceeds 256 bits or invalid symbol found.")
    elif bitlen <= 512:
        output = bytes(64)
        ok = lib.cppcore_basex_decode512(bvalue, output, balpha)
        if not ok: raise ValueError("Value exceeds 512 bits or invalid symbol found.")    
    elif bitlen <= 1024:
        output = bytes(128)
        ok = lib.cppcore_basex_decode1024(bvalue, output, balpha)
        if not ok: raise ValueError("Value exceeds 1024 bits or invalid symbol found.")
    elif bitlen <= 2048:
        output = bytes(256)
        ok = lib.cppcore_basex_decode2048(bvalue, output, balpha)
        if not ok: raise ValueError("Value exceeds 2048 bits or invalid symbol found.")
    elif bitlen <= 4096:
        output = bytes(512)
        ok = lib.cppcore_basex_decode4096(bvalue, output, balpha)
        if not ok: raise ValueError("Value exceeds 4096 bits or invalid symbol found.")
    else: # try with max because estimation can be larger
        output = bytes(1024)
        ok = lib.cppcore_basex_decode8192(bvalue, output, balpha)
        if not ok: raise ValueError("Value exceeds 8192 bits or invalid symbol found.")   
    return int.from_bytes(output, byteorder=sys.byteorder)
