import cppcore.aes
import random
import os

def helper(type, keysize:int, use_iv:bool, block_mode:bool):
    bob = type()
    alice = type()
    key = os.urandom(keysize)
    if use_iv:
        iv = os.urandom(16)
        bob.reset(key, iv)
        alice.reset(key, iv)
    else:
        bob.reset(key)
        alice.reset(key)
    for i in range(10):
        if block_mode:
            msg1 = os.urandom(random.randrange(16, 129, 16))
            msg2 = os.urandom(random.randrange(16, 129, 16))
        else:
            msg1 = os.urandom(random.randint(1, 128))
            msg2 = os.urandom(random.randint(1, 128))
        enc1 = bob.encrypt(msg1)
        dec1 = alice.decrypt(enc1)
        enc2 = alice.encrypt(msg2)
        dec2 = bob.decrypt(enc2)
        assert(dec1 == msg1)
        assert(dec2 == msg2)
    del bob
    del alice

def test_ecb_128(): helper(cppcore.aes.AES128ECB, 16, False, True)
def test_ecb_192(): helper(cppcore.aes.AES192ECB, 24, False, True)
def test_ecb_256(): helper(cppcore.aes.AES256ECB, 32, False, True)

def test_cbc_128(): helper(cppcore.aes.AES128CBC, 16, True, True)
def test_cbc_192(): helper(cppcore.aes.AES192CBC, 24, True, True)
def test_cbc_256(): helper(cppcore.aes.AES256CBC, 32, True, True)

def test_ctr_128(): helper(cppcore.aes.AES128CTR, 16, True, False)
def test_ctr_192(): helper(cppcore.aes.AES192CTR, 24, True, False)
def test_ctr_256(): helper(cppcore.aes.AES256CTR, 32, True, False)
