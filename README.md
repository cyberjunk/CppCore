# Introduction

CppCore is my personal [C++17](https://en.wikipedia.org/wiki/C%2B%2B17) framework with focus on:

* High Performance
* Cross Platform Compatibility
* Easy Integration (almost header-only)

# License

[MIT License](https://github.com/cyberjunk/cppcore/blob/master/LICENSE.md)

# Supported Platforms

|      Min. OS    |  X64  |  X86  |  ARM64  |  ARM  |  Github Action  |
|-----------------|:-----:|:-----:|:-------:|:-----:|-----------------|
| Windows 10      |  :white_check_mark: |  :white_check_mark:  |   :white_check_mark:   |  :red_circle:  | [![Windows](https://github.com/cyberjunk/cppcore/actions/workflows/build-win.yml/badge.svg)](https://github.com/cyberjunk/cppcore/actions/workflows/build-win.yml)         |
| Ubuntu 20.04    |  :white_check_mark:  |  :white_check_mark:  |   :white_check_mark:   |  :white_check_mark:  | [![Linux](https://github.com/cyberjunk/cppcore/actions/workflows/build-linux.yml/badge.svg)](https://github.com/cyberjunk/cppcore/actions/workflows/build-linux.yml)     |
| OSX 10.15       |  :white_check_mark:  |  :red_circle:  |   :white_check_mark:   |  :red_circle:  | [![OSX](https://github.com/cyberjunk/cppcore/actions/workflows/build-osx.yml/badge.svg)](https://github.com/cyberjunk/cppcore/actions/workflows/build-osx.yml)         |
| Android 21      |  :white_check_mark:  |  :white_check_mark:  |   :white_check_mark:   |  :white_check_mark:  | [![Android](https://github.com/cyberjunk/cppcore/actions/workflows/build-android.yml/badge.svg)](https://github.com/cyberjunk/cppcore/actions/workflows/build-android.yml) |
| iOS 13.0        |  :red_circle:  |  :red_circle:  |   :white_check_mark:   |  :red_circle:  | [![iOS](https://github.com/cyberjunk/cppcore/actions/workflows/build-ios.yml/badge.svg)](https://github.com/cyberjunk/cppcore/actions/workflows/build-ios.yml)         |

# How-To

* CppCore is an almost header-only library. Just include the headers and build the CppCore.cpp with your project.
* Only examples and test executables can be built from this repository (see [Build Notes](https://github.com/cyberjunk/cppcore/blob/master/BUILDING.md) for them).


# Implementations

### Hashing

| Name                                                                                       | Notes         |
|--------------------------------------------------------------------------------------------|---------------|
| [CRC32](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/CRC32.h)     | |
| [CRC32C](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/CRC32.h)    | Supports CRC32 CPU Instructions |
| [MD5](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/MD5.h)         | |
| [Murmur3](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/Murmur3.h) | |
| [SHA2-256](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/SHA2.h)   | |
| [SHA2-512](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/SHA2.h)   | |

### Crypto

* AES
* HMAC
* PBKDF2
  
### Math
 
* [BigInt](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/BigInt.h)
* [Primes](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/Primes.h)
* Vectors: [2D](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/V2.h), 3D, 4D

### Containers
Array, Queue, MinHeap, HashTable, ...

### Threading 
Low-Latency Multi-Threading Model

### Network
TCP, Custom-Binary-Protocol, ...

### UI
Cross-Platform Window/Input Wrapper
