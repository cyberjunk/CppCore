import cppcore.dh
import cppcore.primes

def helper(type, p:int=None, g:int=None):
    bob = type()
    alice = type()
    # bob generates shared prime, shared constant 
    # and his private + public key 
    if not p or not g:
        bob.reset()
        p = bob.getprime()
        g = bob.getconstant()
    # or bob uses predefined prime and constant
    # and generates only his private + public key
    else: bob.reset_pg(p, g)
    # alice may want to verify bob's generated p and g
    assert(cppcore.primes.test(p) != cppcore.primes.Result.NotPrime)
    assert(g < p)
    # alice uses prime, constant and generates her priv+pub key
    alice.reset_pg(p, g)
    # both exchange their public keys
    Vb = bob.getpubkey()
    Va = alice.getpubkey()
    # both generate same session key from public key of other party
    kb = bob.genkey(Va)
    ka = alice.genkey(Vb)
    assert(kb == ka)

# TESTS WITH GENERATED PRIME AND CONSTANT
    
def test_dh128_gen():  helper(cppcore.dh.DH128)
def test_dh256_gen():  helper(cppcore.dh.DH256)
def test_dh512_gen():  helper(cppcore.dh.DH512)
def test_dh1024_gen(): helper(cppcore.dh.DH1024)
def test_dh2048_gen(): helper(cppcore.dh.DH2048)
def test_dh4096_gen(): helper(cppcore.dh.DH4096)

# TESTS WITH PREDEFINED PRIME AND CONSTANT

def test_dh128_def():  helper(cppcore.dh.DH128,  7, 2)
def test_dh256_def():  helper(cppcore.dh.DH256,  7, 2)
def test_dh512_def():  helper(cppcore.dh.DH512,  7, 2)
def test_dh1024_def(): helper(cppcore.dh.DH1024, 7, 2)
def test_dh2048_def(): helper(cppcore.dh.DH2048, 7, 2)
def test_dh4096_def(): helper(cppcore.dh.DH4096, 7, 2)
