#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Detect platform
#if defined(_WIN64) || defined(_WIN32)
#define CPPCORE_OS_WINDOWS
#elif defined(__ANDROID__)
#define CPPCORE_OS_ANDROID
#elif defined(__linux__)
#define CPPCORE_OS_LINUX
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_OSX
#define CPPCORE_OS_OSX
#elif TARGET_OS_IPHONE
#define CPPCORE_OS_IPHONE
#else
#error UNKNOWN OPERATING SYSTEM
#endif
#else
#error UNKNOWN OPERATING SYSTEM
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Detect compiler
#if defined(__clang__)
#define CPPCORE_COMPILER_CLANG
#elif defined(_MSC_VER)
#define CPPCORE_COMPILER_MSVC
#else
#error UNKNOWN COMPILER
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Detect processor
#if defined(_M_X64) || defined(__amd64__) || defined(__x86_64__)
#define CPPCORE_CPU_X64
#define CPPCORE_CPU_X86ORX64
#define CPPCORE_CPU_64BIT
#elif defined(_M_IX86) || defined(_X86_) || defined(__i386__) || defined(__i686__)
#define CPPCORE_CPU_X86
#define CPPCORE_CPU_X86ORX64
#define CPPCORE_CPU_32BIT
#elif defined(_M_ARM64) || defined(__aarch64__)
#define CPPCORE_CPU_ARM64
#define CPPCORE_CPU_ARMORARM64
#define CPPCORE_CPU_64BIT
#elif defined (_M_ARM) || defined(__arm__)
#define CPPCORE_CPU_ARM
#define CPPCORE_CPU_ARMORARM64
#define CPPCORE_CPU_32BIT
#else
#error UNKNOWN CPU
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// INTEL CPU
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Set intrinsics macros from /arch setting for x86 on MSVC
#if defined(CPPCORE_COMPILER_MSVC)
#if _M_IX86_FP == 2 // SSE2
#ifndef __SSE2__
#define __SSE2__
#endif
#ifndef __SSE__
#define __SSE__
#endif
#ifndef __MMX__
#define __MMX__
#endif
#elif _M_IX86_FP == 1 // SSE
#ifndef __SSE__
#define __SSE__
#endif
#ifndef __MMX__
#define __MMX__
#endif
#endif
#endif

// Processor Features From Build Settings
#if defined(__MMX__) && !defined(CPPCORE_CPUFEAT_MMX)
#define CPPCORE_CPUFEAT_MMX
#endif
#if defined(__FXSR__) && !defined(CPPCORE_CPUFEAT_FXSR)
#define CPPCORE_CPUFEAT_FXSR
#endif
#if defined(__SSE__) && !defined(CPPCORE_CPUFEAT_SSE)
#define CPPCORE_CPUFEAT_SSE
#endif
#if defined(__SSE2__) && !defined(CPPCORE_CPUFEAT_SSE2)
#define CPPCORE_CPUFEAT_SSE2
#endif
#if defined(__SSE3__) && !defined(CPPCORE_CPUFEAT_SSE3)
#define CPPCORE_CPUFEAT_SSE3
#endif
#if defined(__SSSE3__) && !defined(CPPCORE_CPUFEAT_SSSE3)
#define CPPCORE_CPUFEAT_SSSE3
#endif
#if defined(__LAHF_SAHF__ ) && !defined(CPPCORE_CPUFEAT_SAHF)
#define CPPCORE_CPUFEAT_SAHF
#endif
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16 ) && !defined(CPPCORE_CPUFEAT_CX16)
#define CPPCORE_CPUFEAT_CX16
#endif
#if defined(__SSE4_1__) && !defined(CPPCORE_CPUFEAT_SSE41)
#define CPPCORE_CPUFEAT_SSE41
#endif
#if defined(__SSE4_2__) && !defined(CPPCORE_CPUFEAT_SSE42)
#define CPPCORE_CPUFEAT_SSE42
#endif
#if defined(__POPCNT__) && !defined(CPPCORE_CPUFEAT_POPCNT)
#define CPPCORE_CPUFEAT_POPCNT
#endif
#if defined(__PCLMUL__) && !defined(CPPCORE_CPUFEAT_PCLMUL)
#define CPPCORE_CPUFEAT_PCLMUL
#endif
#if defined(__AES__) && !defined(CPPCORE_CPUFEAT_AES)
#define CPPCORE_CPUFEAT_AES
#endif
#if defined(__AVX__) && !defined(CPPCORE_CPUFEAT_AVX)
#define CPPCORE_CPUFEAT_AVX
#endif
#if defined(__XSAVE__) && !defined(CPPCORE_CPUFEAT_XSAVE)
#define CPPCORE_CPUFEAT_XSAVE
#endif
#if defined(__F16C__) && !defined(CPPCORE_CPUFEAT_F16C)
#define CPPCORE_CPUFEAT_F16C
#endif
#if defined(__FSGSBASE__) && !defined(CPPCORE_CPUFEAT_FSGSBASE)
#define CPPCORE_CPUFEAT_FSGSBASE
#endif
#if defined(__RDRND__) && !defined(CPPCORE_CPUFEAT_RDRAND)
#define CPPCORE_CPUFEAT_RDRAND
#endif
#if defined(__FMA__) && !defined(CPPCORE_CPUFEAT_FMA3)
#define CPPCORE_CPUFEAT_FMA3
#endif
#if defined(__LZCNT__) && !defined(CPPCORE_CPUFEAT_LZCNT)
#define CPPCORE_CPUFEAT_LZCNT
#endif
#if defined(__BMI__) && !defined(CPPCORE_CPUFEAT_BMI1)
#define CPPCORE_CPUFEAT_BMI1
#endif
#if defined(__BMI2__) && !defined(CPPCORE_CPUFEAT_BMI2)
#define CPPCORE_CPUFEAT_BMI2
#endif
#if defined(__MOVBE__) && !defined(CPPCORE_CPUFEAT_MOVBE)
#define CPPCORE_CPUFEAT_MOVBE
#endif
#if defined(__HLE__) && !defined(CPPCORE_CPUFEAT_HLE)
#define CPPCORE_CPUFEAT_HLE
#endif
#if defined(__AVX2__) && !defined(CPPCORE_CPUFEAT_AVX2)
#define CPPCORE_CPUFEAT_AVX2
#endif
#if defined(__RDSEED__) && !defined(CPPCORE_CPUFEAT_RDSEED)
#define CPPCORE_CPUFEAT_RDSEED
#endif
#if defined(__ADX__) && !defined(CPPCORE_CPUFEAT_ADX)
#define CPPCORE_CPUFEAT_ADX
#endif
#if defined(__CLFLUSHOPT__) && !defined(CPPCORE_CPUFEAT_CLFLUSHOPT)
#define CPPCORE_CPUFEAT_CLFLUSHOPT
#endif
#if defined(__XSAVEC__) && !defined(CPPCORE_CPUFEAT_XSAVEC)
#define CPPCORE_CPUFEAT_XSAVEC
#endif
#if defined(__XSAVES__) && !defined(CPPCORE_CPUFEAT_XSAVES)
#define CPPCORE_CPUFEAT_XSAVES
#endif
#if defined(__SGX__) && !defined(CPPCORE_CPUFEAT_SGX)
#define CPPCORE_CPUFEAT_SGX
#endif
#if defined(__SHA__) && !defined(CPPCORE_CPUFEAT_SHA)
#define CPPCORE_CPUFEAT_SHA
#endif
#if defined(__AVX512F__) && !defined(CPPCORE_CPUFEAT_AVX512F)
#define CPPCORE_CPUFEAT_AVX512F
#endif
#if defined(__AVX512VL__) && !defined(CPPCORE_CPUFEAT_AVX512VL)
#define CPPCORE_CPUFEAT_AVX512VL
#endif
#if defined(__AVX512BW__) && !defined(CPPCORE_CPUFEAT_AVX512BW)
#define CPPCORE_CPUFEAT_AVX512BW
#endif
#if defined(__AVX512DQ__) && !defined(CPPCORE_CPUFEAT_AVX512DQ)
#define CPPCORE_CPUFEAT_AVX512DQ
#endif
#if defined(__AVX512CD__) && !defined(CPPCORE_CPUFEAT_AVX512CD)
#define CPPCORE_CPUFEAT_AVX512CD
#endif
#if defined(__AVX512PF__) && !defined(CPPCORE_CPUFEAT_AVX512PF)
#define CPPCORE_CPUFEAT_AVX512PF
#endif
#if defined(__AVX512ER__) && !defined(CPPCORE_CPUFEAT_AVX512ER)
#define CPPCORE_CPUFEAT_AVX512ER
#endif
#if defined(__AVX512VBMI__) && !defined(CPPCORE_CPUFEAT_AVX512VBMI)
#define CPPCORE_CPUFEAT_AVX512VBMI
#endif
#if defined(__AVX512IFMA__) && !defined(CPPCORE_CPUFEAT_AVX512IFMA)
#define CPPCORE_CPUFEAT_AVX512IFMA
#endif
#if defined(__AVX512VNNI__) && !defined(CPPCORE_CPUFEAT_AVX512VNNI)
#define CPPCORE_CPUFEAT_AVX512VNNI
#endif
#if defined(__AVX512VBMI2__) && !defined(CPPCORE_CPUFEAT_AVX512VBMI2)
#define CPPCORE_CPUFEAT_AVX512VBMI2
#endif
#if defined(__AVX512BITALG__) && !defined(CPPCORE_CPUFEAT_AVX512BITALG)
#define CPPCORE_CPUFEAT_AVX512BITALG
#endif
#if defined(__AVX512VPOPCNTDQ__) && !defined(CPPCORE_CPUFEAT_AVX512VPOPCNTDQ)
#define CPPCORE_CPUFEAT_AVX512VPOPCNTDQ
#endif

// MSVC does not define a lot of them so let's
// set them based on MVSC setting for AVX/AVX2/AVX512
#if defined(CPPCORE_COMPILER_MSVC)
#if defined(CPPCORE_CPUFEAT_AVX512F)
#ifndef CPPCORE_CPUFEAT_AVX2
#define CPPCORE_CPUFEAT_AVX2
#endif
#endif
#if defined(CPPCORE_CPUFEAT_AVX2)
#ifndef CPPCORE_CPUFEAT_AVX
#define CPPCORE_CPUFEAT_AVX
#endif
#ifndef CPPCORE_CPUFEAT_RDRAND
#define CPPCORE_CPUFEAT_RDRAND
#endif
#ifndef CPPCORE_CPUFEAT_FMA3
#define CPPCORE_CPUFEAT_FMA3
#endif
#ifndef CPPCORE_CPUFEAT_LZCNT
#define CPPCORE_CPUFEAT_LZCNT
#endif
#ifndef CPPCORE_CPUFEAT_BMI1
#define CPPCORE_CPUFEAT_BMI1
#endif
#ifndef CPPCORE_CPUFEAT_BMI2
#define CPPCORE_CPUFEAT_BMI2
#endif
#ifndef CPPCORE_CPUFEAT_MOVBE
#define CPPCORE_CPUFEAT_MOVBE
#endif
#endif
#if defined(CPPCORE_CPUFEAT_AVX)
#ifndef CPPCORE_CPUFEAT_FXSR
#define CPPCORE_CPUFEAT_FXSR
#endif
#ifndef CPPCORE_CPUFEAT_MMX
#define CPPCORE_CPUFEAT_MMX
#endif
#ifndef CPPCORE_CPUFEAT_SSE
#define CPPCORE_CPUFEAT_SSE
#endif
#ifndef CPPCORE_CPUFEAT_SSE2
#define CPPCORE_CPUFEAT_SSE2
#endif
#ifndef CPPCORE_CPUFEAT_SSE3
#define CPPCORE_CPUFEAT_SSE3
#endif
#ifndef CPPCORE_CPUFEAT_SSSE3
#define CPPCORE_CPUFEAT_SSSE3
#endif
#ifndef CPPCORE_CPUFEAT_SAHF
#define CPPCORE_CPUFEAT_SAHF
#endif
#ifndef CPPCORE_CPUFEAT_CX16
#define CPPCORE_CPUFEAT_CX16
#endif
#ifndef CPPCORE_CPUFEAT_SSE41
#define CPPCORE_CPUFEAT_SSE41
#endif
#ifndef CPPCORE_CPUFEAT_SSE42
#define CPPCORE_CPUFEAT_SSE42
#endif
#ifndef CPPCORE_CPUFEAT_POPCNT
#define CPPCORE_CPUFEAT_POPCNT
#endif
#ifndef CPPCORE_CPUFEAT_PCLMUL
#define CPPCORE_CPUFEAT_PCLMUL
#endif
#ifndef CPPCORE_CPUFEAT_AES
#define CPPCORE_CPUFEAT_AES
#endif
#ifndef CPPCORE_CPUFEAT_F16C
#define CPPCORE_CPUFEAT_F16C
#endif
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CPPCORE_CPUFEAT_MMX
#define CPPCORE_CPUFEAT_MMX_ENABLED 1
#else
#define CPPCORE_CPUFEAT_MMX_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_FXSR
#define CPPCORE_CPUFEAT_FXSR_ENABLED 1
#else
#define CPPCORE_CPUFEAT_FXSR_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_SSE
#define CPPCORE_CPUFEAT_SSE_ENABLED 1
#else
#define CPPCORE_CPUFEAT_SSE_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_SSE2
#define CPPCORE_CPUFEAT_SSE2_ENABLED 1
#else
#define CPPCORE_CPUFEAT_SSE2_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_SSE3
#define CPPCORE_CPUFEAT_SSE3_ENABLED 1
#else
#define CPPCORE_CPUFEAT_SSE3_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_SSSE3
#define CPPCORE_CPUFEAT_SSSE3_ENABLED 1
#else
#define CPPCORE_CPUFEAT_SSSE3_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_SAHF
#define CPPCORE_CPUFEAT_SAHF_ENABLED 1
#else
#define CPPCORE_CPUFEAT_SAHF_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_CX16
#define CPPCORE_CPUFEAT_CX16_ENABLED 1
#else
#define CPPCORE_CPUFEAT_CX16_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_SSE41
#define CPPCORE_CPUFEAT_SSE41_ENABLED 1
#else
#define CPPCORE_CPUFEAT_SSE41_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_SSE42
#define CPPCORE_CPUFEAT_SSE42_ENABLED 1
#else
#define CPPCORE_CPUFEAT_SSE42_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_POPCNT
#define CPPCORE_CPUFEAT_POPCNT_ENABLED 1
#else
#define CPPCORE_CPUFEAT_POPCNT_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_PCLMUL
#define CPPCORE_CPUFEAT_PCLMUL_ENABLED 1
#else
#define CPPCORE_CPUFEAT_PCLMUL_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AES
#define CPPCORE_CPUFEAT_AES_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AES_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX
#define CPPCORE_CPUFEAT_AVX_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_XSAVE
#define CPPCORE_CPUFEAT_XSAVE_ENABLED 1
#else
#define CPPCORE_CPUFEAT_XSAVE_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_F16C
#define CPPCORE_CPUFEAT_F16C_ENABLED 1
#else
#define CPPCORE_CPUFEAT_F16C_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_FSGSBASE
#define CPPCORE_CPUFEAT_FSGSBASE_ENABLED 1
#else
#define CPPCORE_CPUFEAT_FSGSBASE_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_RDRAND
#define CPPCORE_CPUFEAT_RDRAND_ENABLED 1
#else
#define CPPCORE_CPUFEAT_RDRAND_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_FMA3
#define CPPCORE_CPUFEAT_FMA3_ENABLED 1
#else
#define CPPCORE_CPUFEAT_FMA3_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_LZCNT
#define CPPCORE_CPUFEAT_LZCNT_ENABLED 1
#else
#define CPPCORE_CPUFEAT_LZCNT_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_BMI1
#define CPPCORE_CPUFEAT_BMI1_ENABLED 1
#else
#define CPPCORE_CPUFEAT_BMI1_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_BMI2
#define CPPCORE_CPUFEAT_BMI2_ENABLED 1
#else
#define CPPCORE_CPUFEAT_BMI2_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_MOVBE
#define CPPCORE_CPUFEAT_MOVBE_ENABLED 1
#else
#define CPPCORE_CPUFEAT_MOVBE_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_HLE
#define CPPCORE_CPUFEAT_HLE_ENABLED 1
#else
#define CPPCORE_CPUFEAT_HLE_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX2
#define CPPCORE_CPUFEAT_AVX2_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX2_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_RDSEED
#define CPPCORE_CPUFEAT_RDSEED_ENABLED 1
#else
#define CPPCORE_CPUFEAT_RDSEED_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_ADX
#define CPPCORE_CPUFEAT_ADX_ENABLED 1
#else
#define CPPCORE_CPUFEAT_ADX_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_CLFLUSHOPT
#define CPPCORE_CPUFEAT_CLFLUSHOPT_ENABLED 1
#else
#define CPPCORE_CPUFEAT_CLFLUSHOPT_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_XSAVEC
#define CPPCORE_CPUFEAT_XSAVEC_ENABLED 1
#else
#define CPPCORE_CPUFEAT_XSAVEC_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_XSAVES
#define CPPCORE_CPUFEAT_XSAVES_ENABLED 1
#else
#define CPPCORE_CPUFEAT_XSAVES_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_SGX
#define CPPCORE_CPUFEAT_SGX_ENABLED 1
#else
#define CPPCORE_CPUFEAT_SGX_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_SHA
#define CPPCORE_CPUFEAT_SHA_ENABLED 1
#else
#define CPPCORE_CPUFEAT_SHA_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512F
#define CPPCORE_CPUFEAT_AVX512F_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512F_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512VL
#define CPPCORE_CPUFEAT_AVX512VL_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512VL_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512BW
#define CPPCORE_CPUFEAT_AVX512BW_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512BW_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512DQ
#define CPPCORE_CPUFEAT_AVX512DQ_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512DQ_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512CD
#define CPPCORE_CPUFEAT_AVX512CD_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512CD_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512PF
#define CPPCORE_CPUFEAT_AVX512PF_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512PF_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512ER
#define CPPCORE_CPUFEAT_AVX512ER_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512ER_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512VBMI
#define CPPCORE_CPUFEAT_AVX512VBMI_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512VBMI_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512IFMA
#define CPPCORE_CPUFEAT_AVX512IFMA_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512IFMA_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512VNNI
#define CPPCORE_CPUFEAT_AVX512VNNI_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512VNNI_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512VBMI2
#define CPPCORE_CPUFEAT_AVX512VBMI2_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512VBMI2_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512BITALG
#define CPPCORE_CPUFEAT_AVX512BITALG_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512BITALG_ENABLED 0
#endif
#ifdef CPPCORE_CPUFEAT_AVX512VPOPCNTDQ
#define CPPCORE_CPUFEAT_AVX512VPOPCNTDQ_ENABLED 1
#else
#define CPPCORE_CPUFEAT_AVX512VPOPCNTDQ_ENABLED 0
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARM CPU
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#if (defined(__ARM_NEON) || defined(__ARM_NEON__)) && !defined(CPPCORE_CPUFEAT_ARM_NEON)
#define CPPCORE_CPUFEAT_ARM_NEON
#endif
#if defined(__ARM_FEATURE_CRC32) && !defined(CPPCORE_CPUFEAT_ARM_CRC32)
#define CPPCORE_CPUFEAT_ARM_CRC32
#endif
#if defined(__ARM_FEATURE_SHA2) && !defined(CPPCORE_CPUFEAT_ARM_SHA2)
#define CPPCORE_CPUFEAT_ARM_SHA2
#endif
#if defined(__ARM_FEATURE_SHA512) && !defined(CPPCORE_CPUFEAT_ARM_SHA512)
#define CPPCORE_CPUFEAT_ARM_SHA512
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Enable/Disable use of optimized classes
#define CPPCORE_OPTIMIZED_BIGINT
#define CPPCORE_OPTIMIZED_VECTORMATH
#define CPPCORE_OPTIMIZED_STRING8

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
// Standard C++ Includes
#define _USE_MATH_DEFINES
#include <algorithm>
#include <atomic>
#include <cassert>
#include <cfenv>
#include <cinttypes>
#include <cmath>
#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <functional>
#include <ios>
#include <iostream>
#include <iomanip>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <shared_mutex>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Standard C Includes
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <limits.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// INTEL Intrinsics
#if defined(CPPCORE_CPU_X86ORX64)
 #if defined(CPPCORE_COMPILER_MSVC)
  #include <intrin.h>
 #elif defined(CPPCORE_COMPILER_CLANG)
  #include <x86intrin.h>
  #include <cpuid.h>
 #endif

// ARM Intrinsics
#elif defined(CPPCORE_CPU_ARMORARM64)
 #if defined(CPPCORE_COMPILER_MSVC)
  #if defined(CPPCORE_CPU_ARM64)
    #include <arm64intr.h>
    #include <arm64_neon.h>
  #else
    #include <armintr.h>
    #include <arm_neon.h>
  #endif
 #elif defined(CPPCORE_COMPILER_CLANG)
  #include <arm_acle.h>
  #include <arm_neon.h>
 #endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Platform POSIX Socket
#if defined(CPPCORE_OS_WINDOWS)
#define NOMINMAX
#include <WinSock2.h>
#include <ws2ipdef.h>
#include <Ws2tcpip.h>
#include <mstcpip.h>
#undef NOMINMAX
#define socklen_t int
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <netdb.h>
#define SOCKET int
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR    -1
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Platform Specific Headers
#if defined(CPPCORE_OS_WINDOWS)
#define NOMINMAX
#include <windowsx.h>
#undef NOMINMAX
#include <sysinfoapi.h>
#include <WinUser.h>
#elif defined(CPPCORE_OS_LINUX)
#include <pwd.h>
#elif defined(CPPCORE_OS_OSX)
#include <pwd.h>
#include <mach-o/dyld.h>
#include <sys/sysctl.h>
#if defined(__OBJC__)
#include <Foundation/Foundation.h>
#endif
#elif defined(CPPCORE_OS_ANDROID)
#include <pwd.h>
#elif defined(CPPCORE_OS_IPHONE)
#include <pwd.h>
#include <mach-o/dyld.h>
#include <sys/sysctl.h>
#if defined(__OBJC__)
#include <Foundation/Foundation.h>
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_COMPILER_MSVC)
// Memory Alignments
#define CPPCORE_ALIGN4  __declspec(align(4))
#define CPPCORE_ALIGN8  __declspec(align(8))
#define CPPCORE_ALIGN16 __declspec(align(16))
#define CPPCORE_ALIGN32 __declspec(align(32))
#define CPPCORE_ALIGN64 __declspec(align(64))
// Memory Alignments for Intrinsic Types
#define CPPCORE_ALIGN8_INTRIN                          CPPCORE_ALIGN8
#define CPPCORE_ALIGN16_INTRIN __declspec(intrin_type) CPPCORE_ALIGN16
#define CPPCORE_ALIGN32_INTRIN __declspec(intrin_type) CPPCORE_ALIGN32
#define CPPCORE_ALIGN64_INTRIN __declspec(intrin_type) CPPCORE_ALIGN64
#else
// Memory Alignments
#define CPPCORE_ALIGN4  alignas(4)
#define CPPCORE_ALIGN8  alignas(8)
#define CPPCORE_ALIGN16 alignas(16)
#define CPPCORE_ALIGN32 alignas(32)
#define CPPCORE_ALIGN64 alignas(64)
// Memory Alignments for Intrinsic Types
#define CPPCORE_ALIGN8_INTRIN  CPPCORE_ALIGN8
#define CPPCORE_ALIGN16_INTRIN CPPCORE_ALIGN16
#define CPPCORE_ALIGN32_INTRIN CPPCORE_ALIGN32
#define CPPCORE_ALIGN64_INTRIN CPPCORE_ALIGN64
#endif

// Aligned Memory Allocation
#if defined(CPPCORE_OS_WINDOWS)
#define CPPCORE_ALIGNED_ALLOC(S, A) ::_aligned_malloc(S, A)
#define CPPCORE_ALIGNED_FREE(A)     ::_aligned_free(A)
#elif defined(CPPCORE_OS_ANDROID)
#define CPPCORE_ALIGNED_ALLOC(S, A) ::memalign(A, S)
#define CPPCORE_ALIGNED_FREE(A)     ::free(A)
#else
#define CPPCORE_ALIGNED_ALLOC(S, A) ::aligned_alloc(A, S)
#define CPPCORE_ALIGNED_FREE(A)     ::free(A)
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// signed/unsigned integer types for C
#ifndef __cplusplus
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef char               int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
#else
// make sure c++ 2017 features are enabled
/*#if !defined(_HAS_CXX17) || _HAS_CXX17 == 0
#error C++ 2017 Support Required
#endif*/
#endif

// validate integer sizes
static_assert(sizeof(uint8_t)  == 1U, "uint8_t not 1 byte");
static_assert(sizeof(uint16_t) == 2U, "uint16_t not 2 bytes");
static_assert(sizeof(uint32_t) == 4U, "uint32_t not 4 bytes");
static_assert(sizeof(uint64_t) == 8U, "uint64_t not 8 bytes");

static_assert(sizeof(int8_t)  == 1U, "int8_t not 1 byte");
static_assert(sizeof(int16_t) == 2U, "int16_t not 2 bytes");
static_assert(sizeof(int32_t) == 4U, "int32_t not 4 bytes");
static_assert(sizeof(int64_t) == 8U, "int64_t not 8 bytes");

// validate floating point sizes
static_assert(sizeof(float)  == 4U, "float not 4 bytes");
static_assert(sizeof(double) == 8U, "double not 8 bytes");

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Inline Macro
#ifndef INLINE
#if defined(CPPCORE_COMPILER_MSVC)
#define INLINE  inline
#else
#define INLINE  inline
#endif
#endif

// Force Inline Macro
#ifndef FORCEINLINE
#if defined(CPPCORE_COMPILER_MSVC)
#define FORCEINLINE  __forceinline
#else
#define FORCEINLINE  inline
#endif
#endif

// Macro for constexpr when CLANG supports it but MSVC does not
#if defined(CPPCORE_COMPILER_CLANG)
#define CONSTEXPR constexpr
#else
#define CONSTEXPR 
#endif

// Export macro
#if defined(CPPCORE_OS_WINDOWS)
#define CPPCORE_EXPORT __declspec(dllexport)
#else
#define CPPCORE_EXPORT __attribute__((visibility("default")))
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// has_builtin broken on vs?
#if defined(CPPCORE_COMPILER_MSVC)
#undef __has_builtin
#define __has_builtin(x) 0
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Branching Likely/Unlikely Attributes
#if _HAS_CXX20
#define CPPCORE_LIKELY   [[likely]]
#define CPPCORE_UNLIKELY [[unlikely]]
#else
#define CPPCORE_LIKELY
#define CPPCORE_UNLIKELY
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Loop Unrolling (#pragma unroll)
#if defined(CPPCORE_COMPILER_CLANG)
#define CPPCORE_UNROLL   _Pragma("unroll")
#else
#define CPPCORE_UNROLL
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Assert Checks
#define CPPCORE_ASSERT_MULTIPLE16(m)   assert(((size_t)(m) & 0x0FU) == 0);
#define CPPCORE_ASSERT_MULTIPLE32(m)   assert(((size_t)(m) & 0x1FU) == 0);
#define CPPCORE_ASSERT_MULTIPLE64(m)   assert(((size_t)(m) & 0x3FU) == 0);
#define CPPCORE_ASSERT_MULTIPLE128(m)  assert(((size_t)(m) & 0x7FU) == 0);
#define CPPCORE_ASSERT_MULTIPLE256(m)  assert(((size_t)(m) & 0xFFU) == 0);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Constants
#define TWOPI         (2.0*M_PI)

#define ISZERO(a, e)  (((a) > -e) & ((a) < e))
#define SIGN(a)       (((a) > 0) ? 1 : (((a) < 0) ? -1 : 0))

#ifndef MAX
#define MAX(a,b)      ((a) >= (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b)      ((a) <= (b) ? (a) : (b))
#endif
#ifndef ABS
#define ABS(a)        ((a) < 0 ? -(a) : (a))
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Native Mutex
#if defined(CPPCORE_OS_WINDOWS)
#define CPPCORE_MUTEX_TYPE       CRITICAL_SECTION
#define CPPCORE_MUTEX_INIT(m)    InitializeCriticalSection(&m)
#define CPPCORE_MUTEX_DELETE(m)  DeleteCriticalSection(&m)
#define CPPCORE_MUTEX_TRYLOCK(m) TryEnterCriticalSection(&m)
#define CPPCORE_MUTEX_LOCK(m)    EnterCriticalSection(&m)
#define CPPCORE_MUTEX_UNLOCK(m)  LeaveCriticalSection(&m)
#else
#define CPPCORE_MUTEX_TYPE      ::std::mutex
#define CPPCORE_MUTEX_INIT(m)
#define CPPCORE_MUTEX_DELETE(m)
#define CPPCORE_MUTEX_TRYLOCK(m) (m).try_lock()
#define CPPCORE_MUTEX_LOCK(m)    (m).lock()
#define CPPCORE_MUTEX_UNLOCK(m)  (m).unlock()
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Helper to retrieve size of compile time arrays
#define CPPCORE_COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Micro Sleep / Spin Loop Relaxation (only if available)

#if defined(CPPCORE_CPUFEAT_SSE2)
#define CPPCORE_NANOSLEEP() _mm_pause()
#elif defined(CPPCORE_CPU_ARM64)
#define CPPCORE_NANOSLEEP()  __yield()
#else
#define CPPCORE_NANOSLEEP()
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace CppCore
{
   // from std::chrono
   using ::std::chrono::system_clock;
   using ::std::chrono::high_resolution_clock; 
   using ::std::chrono::time_point;
   using ::std::chrono::duration;
   using ::std::chrono::hours;
   using ::std::chrono::minutes;
   using ::std::chrono::seconds;
   using ::std::chrono::milliseconds;
   using ::std::chrono::microseconds;
   using ::std::chrono::nanoseconds;
   
   // for timestamps/dates (precision: seconds)
   using Clock     = system_clock;
   using TimePoint = Clock::time_point;
   using Duration  = Clock::duration;

   // for measuring intervals (precision: nanoseconds)
   using ClockHR     = high_resolution_clock;
   using TimePointHR = ClockHR::time_point;
   using DurationHR  = ClockHR::duration;

   // thread
   using ::std::thread;

   // mutexes
   using ::std::mutex;
   using ::std::shared_mutex;
   using ::std::recursive_mutex;

   // locks
   using ::std::unique_lock;
   using ::std::shared_lock;

   // condition variable
   using ::std::condition_variable_any;
   using ::std::condition_variable;
   using ::std::cv_status;

   // atomic
   using ::std::atomic;

   // streams
   using ::std::ostream;
   using ::std::ofstream;
   using ::std::istream;
   using ::std::ifstream;

   // string
   using ::std::string;
   using ::std::stringstream;
   using ::std::string_view;

   // wstring
   using ::std::wstring;
   using ::std::wstringstream;
   using ::std::wstring_view;

   // numeric_limits
   using ::std::numeric_limits;

   // allocator
   using ::std::allocator;
   using ::std::allocator_traits;

   // filesystem
   using ::std::filesystem::path;
   using ::std::filesystem::directory_iterator;

   // deprecated: to be removed
   typedef ::std::string StdString;
}
#endif
