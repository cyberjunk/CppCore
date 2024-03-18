import cppcore.hmac
import hashlib
import hmac
import os
import random

def helper(own_type, ref_type):
    own = own_type()
    for i in range(10):
        key = os.urandom(random.randint(1, 128))
        ref = hmac.new(key, digestmod=ref_type)
        own.reset(key)
        for j in range(100):
            data = os.urandom(random.randint(1, 128))
            own.step(data)
            ref.update(data)
        h1 = own.finish()
        h2 = ref.digest()
        assert(h1 == h2)

def test_md5():    helper(cppcore.hmac.HMACMD5,    hashlib.md5)
def test_sha256(): helper(cppcore.hmac.HMACSHA256, hashlib.sha256)
def test_sha512(): helper(cppcore.hmac.HMACSHA512, hashlib.sha512)
