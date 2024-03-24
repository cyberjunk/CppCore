from cppcore.util.maxint import *
import cppcore.arithmetic
import random
import math

def helper_umulmod(min:int, max:int, n:int):
    for i in range(n):
        a = random.randint(min, max)
        b = random.randint(min, max)
        m = random.randint(min, max)
        assert(cppcore.arithmetic.umulmod(a,b,m) == (a*b)%m)

def helper_upowmod(min:int, max:int, n:int):
    for i in range(n):
        a = random.randint(min, max)
        b = random.randint(min, max)
        m = random.randint(min, max)
        assert(cppcore.arithmetic.upowmod(a,b,m) == pow(a,b,m))

def helper_gcd(min:int, max:int, n:int):
    for i in range(n):
        a = random.randint(min, max)
        b = random.randint(min, max)
        assert(cppcore.arithmetic.gcd(a,b) == math.gcd(a,b))

def test_umulmod32():   helper_umulmod(1, MAX32I,   100)
def test_umulmod64():   helper_umulmod(1, MAX64I,   100)
def test_umulmod128():  helper_umulmod(1, MAX128I,  100)
def test_umulmod256():  helper_umulmod(1, MAX256I,  100)
def test_umulmod512():  helper_umulmod(1, MAX512I,  100)
def test_umulmod1024(): helper_umulmod(1, MAX1024I, 100)
def test_umulmod2048(): helper_umulmod(1, MAX2048I, 10)
def test_umulmod4096(): helper_umulmod(1, MAX4096I, 10)
def test_umulmod8192(): helper_umulmod(1, MAX8192I, 10)

def test_upowmod32():   helper_upowmod(1, MAX32I,   100)
def test_upowmod64():   helper_upowmod(1, MAX64I,   100)
def test_upowmod128():  helper_upowmod(1, MAX128I,  100)
def test_upowmod256():  helper_upowmod(1, MAX256I,  100)
def test_upowmod512():  helper_upowmod(1, MAX512I,  100)
def test_upowmod1024(): helper_upowmod(1, MAX1024I, 100)
def test_upowmod2048(): helper_upowmod(1, MAX2048I, 10)
def test_upowmod4096(): helper_upowmod(1, MAX4096I, 10)
def test_upowmod8192(): helper_upowmod(1, MAX8192I, 5)

def test_gcd32():       helper_gcd(0, MAX32I,   100)
def test_gcd64():       helper_gcd(0, MAX64I,   100)
def test_gcd128():      helper_gcd(0, MAX128I,  100)
def test_gcd256():      helper_gcd(0, MAX256I,  100)
def test_gcd512():      helper_gcd(0, MAX512I,  100)
def test_gcd1024():     helper_gcd(0, MAX1024I, 100)
def test_gcd2048():     helper_gcd(0, MAX2048I, 100)
def test_gcd4096():     helper_gcd(0, MAX4096I, 100)
def test_gcd8192():     helper_gcd(0, MAX8192I, 100)
