import cppcore.hash
import hashlib
import zlib
import random
import os
import sys
import crc32c # from pypip

def helper1(own_type, ref_type):
    """For MD5, SHA256 and SHA512"""
    own = own_type()
    for i in range(10):
        ref = ref_type()
        own.reset()
        for j in range(100):
            data = os.urandom(random.randint(1, 128))
            own.step(data)
            ref.update(data)
        h1 = own.finish()
        h2 = ref.digest()
        assert(h1 == h2)

def helper2(own_type, ref_type):
    """For CRC32 and CRC32C"""
    own = own_type()
    for i in range(10):
        ref = 0
        own.reset()
        for j in range(100):
            data = os.urandom(random.randint(1, 128))
            own.step(data)
            ref = ref_type(data, ref)
        h1 = own.finish()
        assert(h1 == ref.to_bytes(4, byteorder=sys.byteorder))

def test_md5():    helper1(cppcore.hash.MD5,    hashlib.md5)
def test_sha256(): helper1(cppcore.hash.SHA256, hashlib.sha256)
def test_sha512(): helper1(cppcore.hash.SHA512, hashlib.sha512)
def test_crc32():  helper2(cppcore.hash.CRC32,  zlib.crc32)
def test_crc32c(): helper2(cppcore.hash.CRC32C, crc32c.crc32c)
