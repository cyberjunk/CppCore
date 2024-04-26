import ctypes
import sys
import os

if   sys.platform == 'win32':  ext = ".dll"
elif sys.platform == 'linux':  ext = ".so"
elif sys.platform == "darwin": ext = ".dylib"
else: raise ImportError("Unsupported Platform")

file = os.path.abspath(os.path.join(os.path.dirname(__file__), "libcppcore"+ext))
lib = ctypes.CDLL(file)

################################################################
# AES
################################################################

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
# ARITHMETIC
################################################################

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

################################################################
# BASEX
################################################################

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

################################################################
# DH
################################################################

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

################################################################
# HASH
################################################################

lib.cppcore_md5_init.restype = \
lib.cppcore_sha256_init.restype = \
lib.cppcore_sha512_init.restype = \
lib.cppcore_crc32_init.restype = \
lib.cppcore_crc32c_init.restype = ctypes.c_void_p

lib.cppcore_md5_destroy.argtypes = \
lib.cppcore_sha256_destroy.argtypes = \
lib.cppcore_sha512_destroy.argtypes = \
lib.cppcore_crc32_destroy.argtypes = \
lib.cppcore_crc32c_destroy.argtypes = \
[
    ctypes.c_void_p  # handle
]

lib.cppcore_md5_reset.argtypes = \
lib.cppcore_sha256_reset.argtypes = \
lib.cppcore_sha512_reset.argtypes = \
lib.cppcore_crc32_reset.argtypes = \
lib.cppcore_crc32c_reset.argtypes = \
[
    ctypes.c_void_p  # handle
]

lib.cppcore_md5_blockstep.argtypes = \
lib.cppcore_sha256_blockstep.argtypes = \
lib.cppcore_sha512_blockstep.argtypes = \
lib.cppcore_crc32_blockstep.argtypes = \
lib.cppcore_crc32c_blockstep.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p,  # data
    ctypes.c_uint32   # len
]

lib.cppcore_md5_step.argtypes = \
lib.cppcore_sha256_step.argtypes = \
lib.cppcore_sha512_step.argtypes = \
lib.cppcore_crc32_step.argtypes = \
lib.cppcore_crc32c_step.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p,  # data
    ctypes.c_uint32   # len
]

lib.cppcore_md5_finish.argtypes = \
lib.cppcore_sha256_finish.argtypes = \
lib.cppcore_sha512_finish.argtypes = \
lib.cppcore_crc32_finish.argtypes = \
lib.cppcore_crc32c_finish.argtypes = \
[
    ctypes.c_void_p,  # handle
    ctypes.c_void_p   # digest
]

################################################################
# HMAC
################################################################

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

################################################################
# PBKDF2
################################################################

lib.cppcore_pbkdf2_md5_create.argtypes = \
lib.cppcore_pbkdf2_sha256_create.argtypes = \
lib.cppcore_pbkdf2_sha512_create.argtypes = \
[
    ctypes.c_void_p,  # pw
    ctypes.c_uint32,  # pw len
    ctypes.c_void_p,  # salt
    ctypes.c_uint32,  # salt len
    ctypes.c_void_p,  # digest
    ctypes.c_uint32,  # digest len
    ctypes.c_uint32   # iterations
]

################################################################
# PRIMES
################################################################

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
