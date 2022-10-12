<p align="center">
<img src="/CppCore.png?raw=true" width="512" />
</p>

# Introduction

CppCore is my personal [C++17](https://en.wikipedia.org/wiki/C%2B%2B17) framework with focus on:

* High Performance
* Cross Platform Compatibility
* Easy Integration (almost header-only)

It was made for my own use but I am happy to share it with everyone.

# License

[MIT License](https://github.com/cyberjunk/cppcore/blob/master/LICENSE.md)

# Supported Platforms

|      Min. OS    |  X64  |  X86  |  ARM64  |  ARM  |  Github Action  |
|-----------------|:-----:|:-----:|:-------:|:-----:|-----------------|
| Windows 10      |  :white_check_mark: |  :white_check_mark:  |   :white_check_mark:   |  :red_circle:  | [![Windows](https://github.com/cyberjunk/cppcore/actions/workflows/build-win.yml/badge.svg)](https://github.com/cyberjunk/cppcore/actions/workflows/build-win.yml)         |
| Ubuntu 20.04    |  :white_check_mark:  |  :white_check_mark:  |   :white_check_mark:   |  :white_check_mark:  | [![Linux](https://github.com/cyberjunk/cppcore/actions/workflows/build-linux.yml/badge.svg)](https://github.com/cyberjunk/cppcore/actions/workflows/build-linux.yml)     |
| OSX 10.15       |  :white_check_mark:  |  :red_circle:  |   :white_check_mark:   |  :red_circle:  | [![OSX](https://github.com/cyberjunk/cppcore/actions/workflows/build-osx.yml/badge.svg)](https://github.com/cyberjunk/cppcore/actions/workflows/build-osx.yml)         |
| Android 23      |  :white_check_mark:  |  :white_check_mark:  |   :white_check_mark:   |  :white_check_mark:  | [![Android](https://github.com/cyberjunk/cppcore/actions/workflows/build-android.yml/badge.svg)](https://github.com/cyberjunk/cppcore/actions/workflows/build-android.yml) |
| iOS 13.0        |  :red_circle:  |  :red_circle:  |   :white_check_mark:   |  :red_circle:  | [![iOS](https://github.com/cyberjunk/cppcore/actions/workflows/build-ios.yml/badge.svg)](https://github.com/cyberjunk/cppcore/actions/workflows/build-ios.yml)         |

# Design Principles

1) **Performance, Performance, Performance**: </br> The most important principle. This framework was design to be used in real-time critical applications such as games. If you find something that can be done faster, please let me know.
2) **Fixed-Size Memory Pooling**: </br> This framework avoids using `malloc()` and `free()` (respectively `new` and `delete`) to allocate memory at runtime in favor of a fully compile-time specified memory layout. Almost all memory is allocated on startup and used until shutdown - faster, predictable and no undefined out-of-memory behaviour. Yes, there are always exclusions.
3) **Virtual Function Pointers**: </br> OOB programming is great but its disadvantages are often forgotten. No, you won't find things like tiny vector classes blown up in size due to a VFPTR with horribly slow non-inlined arithmetic function calls in this library.
4) **Header-Only**: </br> Allows the compiler to efficiently inline all the framework code into your object files and therefore making integration much simpler and code executing faster. There are a few exclusions to this pattern due to platform limitations (e.g. Windows Message Processing Function)
5) **Multithreading**: </br> This framework comes with its own multithreading patterns and uses multiple cores whenever possible/useful.

# How-To

* CppCore is an almost header-only library. Just include the headers and build the CppCore.cpp with your project.
* Only examples and test executables can be built from this repository (see [Build Notes](https://github.com/cyberjunk/cppcore/blob/master/BUILDING.md) for them).

# Implementations

## Hashing

| Header                                                                                       | Bits | Reference | Notes                       |
|----------------------------------------------------------------------------------------------|------|-----------|-----------------------------|
| [CRC32.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/CRC32.h)     |  32  |           | CRC32/CRC32C (CPU)          |
| [Murmur3.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/Murmur3.h) |  32  |           | Popular for hash tables     |
| [MD5.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/MD5.h)         | 128  | [Wikipedia](https://en.wikipedia.org/wiki/MD5) |
| [SHA2.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Hash/SHA2.h)       | 256/512  | [Wikipedia](https://en.wikipedia.org/wiki/SHA-2) |

## Crypto

| Header                                                                                       | Reference | Notes         |
|----------------------------------------------------------------------------------------------|-----------|---------------|
| [AES.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Crypto/AES.h)       | [Wikipedia](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) | 128/192/256 Bit \| ECB/CBC/CTR \| [AES-NI](https://en.wikipedia.org/wiki/AES_instruction_set) |
| [HMAC.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Crypto/HMAC.h)     | [Wikipedia](https://en.wikipedia.org/wiki/HMAC) | MD5 \| SHA2-256 \| SHA2-512
| [PBKDF2.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Crypto/PBKDF2.h) | [Wikipedia](https://en.wikipedia.org/wiki/PBKDF2) | HMAC-SHA2-256 \| HMAC-SHA2-512
  
## Math

| Header                                                                                     | Notes                                       |
|--------------------------------------------------------------------------------------------|---------------------------------------------|
| [BigInt.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/BigInt.h) | Large unsigned integers from ```uint128_t``` up to ```uint2048_t``` |
| [Primes.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/Primes.h) | Prime Tests (Miller-Rabin/Lucas-Lehmer/...) |
| [V2.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/V2.h) | 2D Vector for `float` `double` `int32_t` `int64_t` with SSE/AVX |
| [V3.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/V3.h) | 3D Vector for `float` `double` `int32_t` `int64_t` with SSE/AVX |
| [V4.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Math/V4.h) | 4D Vector for `float` `double` `int32_t` `int64_t` with SSE/AVX |

## Containers

### Algorithms

| Header | Complexity | Notes |
|--------|------------|-------|
| [QuickSort.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Containers/Util/QuickSort.h)       | `O(n*log(n))` | Non-Recursive [Quicksort](https://en.wikipedia.org/wiki/Quicksort) Algorithm
| [BinarySearch.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Containers/Util/BinarySearch.h) | `O(log(n))`   | Non-Recursive [Binarysearch](https://en.wikipedia.org/wiki/Binary_search_algorithm) Algorithm

### Basic

Different `O(k)` are used to outline some differences between operations with constant complexity on different containers.

| Header | Operation | Complexity | Notes |
|--------|-----------|------------|-------------------|
| [Array.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Containers/Array.h)        | `operator[]`</br>`pushFront()`</br>`pushBack()`</br>`popFront()`</br>`popBack()`</br>`insertAt()`</br>`removeAt()` | `O(1)`</br>`O(n)`</br>`O(1)`</br>`O(n)`</br>`O(1)`</br>`O(n)`</br>`O(n)` | <ul><li>Simple Array</li><li>Sorted or Unsorted</li><li>Fastest `operator[]` `pushBack()` `popBack()`</li></ul>
| [BinTree.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Containers/BinTree.h)    |
| [Queue.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Containers/Queue.h)        | `operator[]`</br>`pushFront()`</br>`pushBack()`</br>`popFront()`</br>`popBack()`</br>`insertAt()`</br>`removeAt()` | `O(10)`</br>`O(10)`</br>`O(10)`</br>`O(10)`</br>`O(10)`</br>`O(n)`</br>`O(n)` | <ul><li>Simple Queue</li><li>Sorted or Unsorted</li><li>Constant `O(k)` for `pushFront()` `popFront()` </li><li>Example: Message Queue</li></ul> | |
| [MinHeap.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Containers/MinHeap.h)     | `operator[]`</br>`push()`</br>`pop()`</br>`removeAt()` | `O(1)`</br>`O(log(n))`</br>`O(log(n))`</br>`O(log(n))` | <ul><li>[Binary Min Heap](https://en.wikipedia.org/wiki/Binary_heap)</li><li>Always Sorted</li><li>Finds minimum at root in `O(1)`</li><li>Example: Timer Schedule</li><li>Example: A* Open-List</li></ul>
| [HashTable.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Containers/HashTable.h) | `insert()`</br>`remove()`</br>`find()` | `O(1000)`</br>`O(1000)`</br>`O(1000)` | <ul><li>Example: Large Lookup Dictionary</li><li>Example: Database Table</li></ul> |
| ... | | | |

### Advanced

| Header | Operation | Complexity | Notes |
|--------|-----------|------------|-------------------|
| [Cache.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Containers/Cache.h)  |

## Threading

| Header                                                                                     | Notes                |
|--------------------------------------------------------------------------------------------|----------------------|
| [Runnable.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Threading/Runnable.h)      | Wraps [std::function](https://en.cppreference.com/w/cpp/utility/functional/function) executing a piece of code on a thread at a certain time.  |
| [Thread.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Threading/Thread.h)          | Uses [std::thread](https://en.cppreference.com/w/cpp/thread/thread) |
| [Schedule.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Threading/Schedule.h)      |  |

## Network

| Header                                                                                               | Notes                |
|------------------------------------------------------------------------------------------------------|----------------------|
| [Socket.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/Socket.h)        | <ul><li>Basic [POSIX Socket](https://en.wikipedia.org/wiki/Berkeley_sockets) Wrapper Class</li><li>Works around remaining differences on platforms</li></ul> |
| [TcpSocket.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/TcpSocket.h)  | <ul><li>Builds upon `Socket.h`</li><li>TCP IPv6 Dual-Stack Socket</li><li>For Server and Client</li><li>Advanced ```connect()```, ```listen()``` and ```accept()``` methods</li></ul> |
| [TcpLink.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/TcpLink.h)  | <ul><li>Builds upon `TcpSocket.h`</li><li>Implements a raw TCP connection</li><li>For Server and Client</li></ul> |
| [TcpClient.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/TcpClient.h)  | <ul><li>Builds upon `TcpLink.h`</li><li>For Client</li></ul> |
| [TcpSession.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/TcpSession.h)  | <ul><li>Builds upon `TcpLink.h`</li><li>For Server</li></ul> |
| [TcpServer.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Network/TcpServer.h)  | <ul><li>Builds upon `TcpSession.h`</li><li>For Server</li></ul> |
| ... | |

## UI

| Header                                                                                     | Notes                |
|--------------------------------------------------------------------------------------------|----------------------|
| [Input.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Input.h)        | Keyboard/Mouse Input from Window-Events on Win/Linux/OSX |
| [Window.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/UI/Window.h)   | Windows Wrapper for Windows/Linux/OSX |

## Misc

| Header                                                                                     | Notes                    |
|--------------------------------------------------------------------------------------------|--------------------------|
| [Buffer.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Buffer.h)      | Fixed Size Memory Buffer |
| [Random.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Random.h)      | Pseudo Random Number Generators <ul><li>`Xorshift32`</li><li>`Xorshift64`</li><li>`Xoshiro32`</li><li>`Xoshiro64`</li><li>`Mulberry32`</li><li>`Splitmix64`</li><li>`Cpu32*`</li><li>`Cpu64*`</li></ul> `*` with [RDRAND](https://en.wikipedia.org/wiki/RDRAND) |
| [Uuid.h](https://github.com/cyberjunk/cppcore/blob/master/include/CppCore/Uuid.h)          | Universally Unique Identifier |

# Applications

Start type `Console` from terminal on OSX.

## Examples

|                                                                      | Name | Type    | Folder | Notes |
|----------------------------------------------------------------------|------|---------|--------|-------|
|<img src="/src/CppCore.Example.Client/app.png?raw=true" width="24" /> | CppCore.Example.Client | Console | [Link](https://github.com/cyberjunk/CppCore/tree/master/src/CppCore.Example.Client) | Custom binary network protocol client |
|<img src="/src/CppCore.Example.Server/app.png?raw=true" width="24" /> | CppCore.Example.Server | Console | [Link](https://github.com/cyberjunk/CppCore/tree/master/src/CppCore.Example.Server) | Custom binary network protocol server |
|<img src="/src/CppCore.Example.UI/app.png?raw=true" width="24" /> | CppCore.Example.UI | Window | [Link](https://github.com/cyberjunk/CppCore/tree/master/src/CppCore.Example.UI) | Cross-Platform Application Window and Input |

## Others

|                                                                      | Name | Type    | Folder | Notes |
|----------------------------------------------------------------------|------|---------|--------|-------|
|<img src="/src/CppCore.Test/app.png?raw=true" width="24" /> | CppCore.Test | Console \| VS-Test | [Link](https://github.com/cyberjunk/CppCore/tree/master/src/CppCore.Test) | Unit Tests |
|<img src="/src/CppCore.Debug/app.png?raw=true" width="24" /> | CppCore.Debug | Console | [Link](https://github.com/cyberjunk/CppCore/tree/master/src/CppCore.Debug) | Empty project to run code during development |
