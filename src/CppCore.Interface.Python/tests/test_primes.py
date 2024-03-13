import cppcore.primes

# PRIME TEST

def test_test32():
    assert(cppcore.primes.test(-1) == cppcore.primes.Result.NotPrime)
    assert(cppcore.primes.test(0) == cppcore.primes.Result.NotPrime)
    assert(cppcore.primes.test(1) == cppcore.primes.Result.NotPrime)
    assert(cppcore.primes.test(2) == cppcore.primes.Result.Prime)
    assert(cppcore.primes.test(3) == cppcore.primes.Result.Prime)
    assert(cppcore.primes.test(4) == cppcore.primes.Result.NotPrime)
    assert(cppcore.primes.test(7) == cppcore.primes.Result.Prime)
    assert(cppcore.primes.test(2147483647) == cppcore.primes.Result.Prime)
    assert(cppcore.primes.test(4294967291) == cppcore.primes.Result.Prime)

def test_test64():
    assert(cppcore.primes.test(9223372036854775783) == 
           cppcore.primes.Result.Prime)
    assert(cppcore.primes.test(18446744073709551557) == 
           cppcore.primes.Result.Prime)

def test_test128():
    assert(cppcore.primes.test(2833419889721787128217599) == 
           cppcore.primes.Result.Prime) # within deterministic range
    assert(cppcore.primes.test(4776913109852041418248056622882488319) == 
           cppcore.primes.Result.LikelyPrime) # outside deterministic range
    assert(cppcore.primes.test(170141183460469231731687303715884105727) == 
           cppcore.primes.Result.Prime) # outside but mersenne prime

# PRIME GENERATION
    
def test_generate32():
    p = cppcore.primes.generate(32)
    r = cppcore.primes.test(p)
    assert(p.bit_length() == 32)
    assert(r == cppcore.primes.Result.Prime)

def test_generate64():
    p = cppcore.primes.generate(64)
    r = cppcore.primes.test(p)
    assert(p.bit_length() == 64)
    assert(r == cppcore.primes.Result.Prime)

def test_generate128():
    p = cppcore.primes.generate(128)
    r = cppcore.primes.test(p)
    assert(p.bit_length() == 128)
    assert(r == cppcore.primes.Result.LikelyPrime)

def test_generate256():
    p = cppcore.primes.generate(256)
    r = cppcore.primes.test(p)
    assert(p.bit_length() == 256)
    assert(r == cppcore.primes.Result.LikelyPrime)
