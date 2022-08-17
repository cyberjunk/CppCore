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

| Header                                                                                       | Bits | Reference | Notes                       |
|----------------------------------------------------------------------------------------------|------|-----------|-----------------------------|
| [CRC32.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/CRC32.h)     |  32  |           | CRC32/CRC32C (CPU)          |
| [Murmur3.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/Murmur3.h) |  32  |           | Popular for hash tables     |
| [MD5.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/MD5.h)         | 128  | [Wikipedia](https://en.wikipedia.org/wiki/MD5) |
| [SHA2.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/SHA2.h)       | 256/512  | [Wikipedia](https://en.wikipedia.org/wiki/SHA-2) |

### Crypto

| Header                                                                                       | Reference | Notes         |
|----------------------------------------------------------------------------------------------|-----------|---------------|
| [AES.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Crypto/AES.h)       | [Wikipedia](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) | 128/192/256 Bit \| ECB/CBC/CTR \| [AES-NI](https://en.wikipedia.org/wiki/AES_instruction_set) |
| [HMAC.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Crypto/HMAC.h)     | [Wikipedia](https://en.wikipedia.org/wiki/HMAC) | MD5 \| SHA2-256 \| SHA2-512
| [PBKDF2.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Crypto/PBKDF2.h) | [Wikipedia](https://en.wikipedia.org/wiki/PBKDF2) | HMAC-SHA2-256 \| HMAC-SHA2-512
  
### Math

| Header                                                                                     | Notes                                       |
|--------------------------------------------------------------------------------------------|---------------------------------------------|
| [BigInt.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/BigInt.h) | Large unsigned integers from ```uint128_t``` up to ```uint2048_t``` |
| [Primes.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/Primes.h) | Prime Tests (Miller-Rabin/Lucas-Lehmer/...) |
| [V2.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/V2.h) | 
| [V3.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/V3.h) | 
| [V4.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/V4.h) | 

### Containers

| Header | Operation | Complexity | Notes |
|--------|-----------|------------|-------|
| [Array.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/Array.h)        | `operator[]`</br>`pushFront()`</br>`pushBack()`</br>`popFront()`</br>`popBack()`</br>`insertAt()` | `O(1)`</br>`O(n)`</br>`O(1)`</br>`O(n)`</br>`O(1)`</br>`O(n)` | Simple Array |
| [BinTree.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/BinTree.h)    | |
| [Queue.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/Queue.h)        | `operator[]`</br>`pushFront()`</br>`pushBack()`</br>`popFront()`</br>`popBack()`</br>`insertAt()` | `O(1)`</br>`O(1)`</br>`O(1)`</br>`O(1)`</br>`O(1)`</br>`O(n)` | FIFO Queue |
| [MinHeap.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/MinHeap.h)     | |
| [HashTable.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/HashTable.h) |
| ... | | | |

### Threading 
Low-Latency Multi-Threading Model

### Network

| Header                                                                                               | Notes                |
|------------------------------------------------------------------------------------------------------|----------------------|
| [Socket.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/Socket.h)        | <ul><li>Basic [POSIX Socket](https://en.wikipedia.org/wiki/Berkeley_sockets) Wrapper Class</li><li>Works around remaining differences on platforms</li></ul> |
| [TcpSocket.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/TcpSocket.h)  | <ul><li>Builds upon `Socket.h`</li><li>TCP IPv6 Dual-Stack Socket</li><li>For Server and Client</li><li>Advanced ```connect()```, ```listen()``` and ```accept()``` methods</li></ul> |
| [TcpLink.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/TcpLink.h)  | <ul><li>Builds upon `TcpSocket.h`</li><li>Implements a raw TCP connection</li><li>For Server and Client</li></ul> |
| [TcpClient.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/TcpClient.h)  | <ul><li>Builds upon `TcpLink.h`</li><li>For Client</li></ul> |
| [TcpSession.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/TcpSession.h)  | <ul><li>Builds upon `TcpLink.h`</li><li>For Server</li></ul> |
| [TcpServer.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/TcpServer.h)  | <ul><li>Builds upon `TcpSession.h`</li><li>For Server</li></ul> |
| ... | |

### UI

| Header                                                                                     | Notes                |
|--------------------------------------------------------------------------------------------|----------------------|
| [Input.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Input.h)        | Keyboard/Mouse Input from Window-Events on Win/Linux/OSX |
| [Window.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/UI/Window.h)   | Windows Wrapper for Windows/Linux/OSX |
