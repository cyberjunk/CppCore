

// PUBLIC C INTERFACE
#include <CppCore.Interface.C/Primes.h>

// private c++ headers
#include <CppCore/Memory.h>
#include <CppCore/Math/BigInt.h>

// macro for function implementations
#define CPPCORE_PRIME_IMPLEMENTATION(name, classname, copyop1, copyop2)                                       \
  int  name ## _test    (void* data, size_t certainty) { classname v; copyop1; return v.isprime(certainty); } \
  void name ## _generate(void* data, size_t certainty) { classname v; v.genprime(certainty); copyop2;       }

// function implementations

CPPCORE_PRIME_IMPLEMENTATION(cppcore_prime128, CppCore::uint128_t, CppCore::Memory::singlecopy128(&v, data), CppCore::Memory::singlecopy128(data, &v))
CPPCORE_PRIME_IMPLEMENTATION(cppcore_prime256, CppCore::uint256_t, CppCore::Memory::singlecopy256(&v, data), CppCore::Memory::singlecopy256(data, &v))
CPPCORE_PRIME_IMPLEMENTATION(cppcore_prime512, CppCore::uint512_t, CppCore::Memory::singlecopy512(&v, data), CppCore::Memory::singlecopy512(data, &v))
