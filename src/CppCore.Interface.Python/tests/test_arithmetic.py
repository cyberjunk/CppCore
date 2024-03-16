from cppcore.util.maxint import *
import cppcore.arithmetic
import random

def helper_upowmod(min:int, max:int, n:int):
    for i in range(n):
        a = random.randint(min, max)
        b = random.randint(min, max)
        m = random.randint(min, max)
        assert(cppcore.arithmetic.upowmod(a,b,m) == pow(a,b,m))

def test_upowmod32():   helper_upowmod(1, MAX32I,   100)
def test_upowmod64():   helper_upowmod(1, MAX64I,   100)
def test_upowmod128():  helper_upowmod(1, MAX128I,  100)
def test_upowmod256():  helper_upowmod(1, MAX256I,  100)
def test_upowmod512():  helper_upowmod(1, MAX512I,  100)
def test_upowmod1024(): helper_upowmod(1, MAX1024I, 100)
def test_upowmod2048(): helper_upowmod(1, MAX2048I, 10)
def test_upowmod4096(): helper_upowmod(1, MAX4096I, 10)
def test_upowmod8192(): helper_upowmod(1, MAX8192I, 5)
