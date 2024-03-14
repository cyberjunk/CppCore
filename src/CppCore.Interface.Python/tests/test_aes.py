import cppcore.aes
import random
import os

def test_ctr_128():
    bob = cppcore.aes.AES128CTR()
    alice = cppcore.aes.AES128CTR()
    key = os.urandom(16)
    iv = os.urandom(16)
    bob.reset(key, iv)
    alice.reset(key, iv)
    for i in range(10):
        msg1 = os.urandom(random.randint(1, 64))
        msg2 = os.urandom(random.randint(1, 64))
        enc1 = bob.encrypt(msg1)
        dec1 = alice.decrypt(enc1)
        enc2 = alice.encrypt(msg2)
        dec2 = bob.decrypt(enc2)
        assert(dec1 == msg1)
        assert(dec2 == msg2)
    del bob
    del alice
