import cppcore.pbkdf2
import pbkdf2 # pbkdf2-reboot from pypip
import random
import hashlib
import os

def helper(own, ref):
    for i in range(10):
        pw   = os.urandom(random.randint(1, 128))
        salt = os.urandom(random.randint(1, 128))
        dlen = random.randint(1, 128)
        iter = random.randint(1, 4096)
        assert(
            own(pw, salt, dlen, iter) ==
            pbkdf2.PBKDF2(pw, salt, iter, ref).read(dlen)
        )

def test_sha256(): helper(cppcore.pbkdf2.pbkdf2_sha256, hashlib.sha256)
def test_sha512(): helper(cppcore.pbkdf2.pbkdf2_sha512, hashlib.sha512)
