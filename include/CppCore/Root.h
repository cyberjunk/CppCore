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
#elif defined(__aarch64__)
#define CPPCORE_CPU_ARM64
#define CPPCORE_CPU_ARMORARM64
#define CPPCORE_CPU_64BIT
#elif defined(__arm__)
#define CPPCORE_CPU_ARM
#define CPPCORE_CPU_ARMORARM64
#define CPPCORE_CPU_32BIT
#else
#error UNKNOWN CPU
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Processor Features From Build Settings
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
#if defined(__SSE4_1__) && !defined(CPPCORE_CPUFEAT_SSE41)
#define CPPCORE_CPUFEAT_SSE41
#endif
#if defined(__SSE4_2__) && !defined(CPPCORE_CPUFEAT_SSE42)
#define CPPCORE_CPUFEAT_SSE42
#endif
#if defined(__PCLMUL__) && !defined(CPPCORE_CPUFEAT_PCLMUL)
#define CPPCORE_CPUFEAT_PCLMUL
#endif
#if defined(__AES__) && !defined(CPPCORE_CPUFEAT_AES)
#define CPPCORE_CPUFEAT_AES
#endif
#if defined(__RDRND__) && !defined(CPPCORE_CPUFEAT_RDRAND)
#define CPPCORE_CPUFEAT_RDRAND
#endif
#if defined(__RDSEED__) && !defined(CPPCORE_CPUFEAT_RDSEED)
#define CPPCORE_CPUFEAT_RDSEED
#endif
#if defined(__MOVBE__) && !defined(CPPCORE_CPUFEAT_MOVBE)
#define CPPCORE_CPUFEAT_MOVBE
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
#if defined(__ADX__) && !defined(CPPCORE_CPUFEAT_ADX)
#define CPPCORE_CPUFEAT_ADX
#endif
#if defined(__AVX__) && !defined(CPPCORE_CPUFEAT_AVX)
#define CPPCORE_CPUFEAT_AVX
#endif
#if defined(__AVX2__) && !defined(CPPCORE_CPUFEAT_AVX2)
#define CPPCORE_CPUFEAT_AVX2
#endif
#if defined(__AVX512F__) && !defined(CPPCORE_CPUFEAT_AVX512)
#define CPPCORE_CPUFEAT_AVX512
#endif

// MSVC - Enabled CPU Instructions    INTEL ARCH   (YEAR) | AMD ARCH   (YEAR)
#if defined(CPPCORE_COMPILER_MSVC)
#if defined(CPPCORE_CPU_X86ORX64)
#define CPPCORE_CPUFEAT_SSE        // Katmai       (1999) | Palomino   (2001)
#define CPPCORE_CPUFEAT_SSE2       // Willamette   (2001) | Clawhammer (2003)
#define CPPCORE_CPUFEAT_SSE3       // Prescott     (2004) | Venice     (2005)
#define CPPCORE_CPUFEAT_SSSE3      // Woodcrest    (2006) | Bulldozer  (2011)
#define CPPCORE_CPUFEAT_SSE41      // Penryn       (2008) | Bulldozer  (2011)
#define CPPCORE_CPUFEAT_SSE42      // Nehalem      (2008) | Bulldozer  (2011)
#define CPPCORE_CPUFEAT_PCLMUL     // Westmere     (2010) | Bulldozer  (2011)
#define CPPCORE_CPUFEAT_AES        // Broadwell    (2010) | Bulldozer  (2011)
#define CPPCORE_CPUFEAT_RDRAND     // Ivy Bridge   (2012) | Excavator  (2015)
#define CPPCORE_CPUFEAT_FMA3       // Haswell      (2013) | Piledriver (2012)
#define CPPCORE_CPUFEAT_LZCNT      // Haswell      (2013) | Piledriver (2012)
#define CPPCORE_CPUFEAT_BMI1       // Haswell      (2013) | Piledriver (2012)
#define CPPCORE_CPUFEAT_BMI2       // Haswell      (2013) | Excavator  (2015)
#define CPPCORE_CPUFEAT_MOVBE      // Haswell      (2013) | Excavator  (2015)
#define CPPCORE_CPUFEAT_RDSEED     // Broadwell    (2014) | Excavator  (2015)
#define CPPCORE_CPUFEAT_ADX        // Broadwell    (2014) | Zen        (2017)
#endif
#if defined(CPPCORE_CPU_X64)
#define CPPCORE_CPUFEAT_AVX        // Sandy Bridge (2011) | Bulldozer  (2011)
#define CPPCORE_CPUFEAT_AVX2       // Haswell      (2013) | Excavator  (2015)
#define CPPCORE_CPUFEAT_AVX512     // Skylake      (2015) | -
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Enable/Disable use of optimized classes
#define CPPCORE_OPTIMIZED_BIGINT
#define CPPCORE_OPTIMIZED_VECTORMATH
#define CPPCORE_OPTIMIZED_STRING8

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_COMPILER_MSVC)
// Memory Alignments
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
#include <fstream>
#include <functional>
#include <ios>
#include <iostream>
#include <iomanip>
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

// Signal Header
#include <signal.h>

// silence experimental filesystem deprecated warnings for clang
#ifndef _LIBCPP_NO_EXPERIMENTAL_DEPRECATION_WARNING_FILESYSTEM
#define _LIBCPP_NO_EXPERIMENTAL_DEPRECATION_WARNING_FILESYSTEM
#endif
// silence experimental filesystem deprecated warnings for msvc
#ifndef _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif
#include <experimental/filesystem>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Intrinsics Includes
#if defined(CPPCORE_CPU_X86ORX64) && defined(CPPCORE_COMPILER_MSVC)
#include <intrin.h>
#elif defined(CPPCORE_CPU_X86ORX64) && defined(CPPCORE_COMPILER_CLANG)
#include <x86intrin.h>
#elif defined(CPPCORE_CPU_ARMORARM64) && defined(CPPCORE_COMPILER_CLANG)
#include <arm_neon.h>
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// make sure c++ 2017 features are enabled
/*#if !defined(_HAS_CXX17) || _HAS_CXX17 == 0
#error C++ 2017 Support Required
#endif*/

// validate integer sizes
static_assert(sizeof(uint8_t)  == 1U);
static_assert(sizeof(uint16_t) == 2U);
static_assert(sizeof(uint32_t) == 4U);
static_assert(sizeof(uint64_t) == 8U);

// validate floating point sizes
static_assert(sizeof(float)  == 4U);
static_assert(sizeof(double) == 8U);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Inline Macro
#if defined(CPPCORE_COMPILER_MSVC)
#define INLINE  __forceinline
#else
#define INLINE  inline
#endif

// Macro for constexpr when CLANG supports it but MSVC does not
#if defined(CPPCORE_COMPILER_CLANG)
#define CONSTEXPR constexpr
#else
#define CONSTEXPR 
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
#define MAX(a,b)      ((a) >= (b) ? (a) : (b))
#define MIN(a,b)      ((a) <= (b) ? (a) : (b))
#define ABS(a)        ((a) < 0 ? -(a) : (a))

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Native Mutex
#if defined(CPPCORE_OS_WINDOWS)
#define NOMINMAX
#include <Winsock2.h>
#undef NOMINMAX
#include <windowsx.h>
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

#ifndef CPPCORE_COUNT_OF
#define CPPCORE_COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Micro Sleep / Spin Loop Relaxation (only if available)

#if defined(CPPCORE_CPUFEAT_SSE2)
#define CPPCORE_NANOSLEEP() _mm_pause()
#elif false && defined(CPPCORE_CPU_ARM64)
#define CPPCORE_NANOSLEEP()  __yield()
#else
#define CPPCORE_NANOSLEEP()
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

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
   
   // for timestamps/dates
   using Clock     = system_clock;
   using TimePoint = Clock::time_point;
   using Duration  = Clock::duration;

   // for measuring intervals
   using ClockHR     = high_resolution_clock;
   using TimePointHR = ClockHR::time_point;
   using DurationHR  = ClockHR::duration;

   // deprecated old for chrono
   typedef ::std::chrono::high_resolution_clock           StdClock;
   typedef ::std::chrono::time_point<StdClock>            StdTimePoint;
   typedef ::std::chrono::high_resolution_clock::duration StdDuration;
   typedef ::std::chrono::seconds                         StdSeconds;
   typedef ::std::chrono::milliseconds                    StdMilliSeconds;
   typedef ::std::chrono::microseconds                    StdMicroSeconds;
   typedef ::std::chrono::nanoseconds                     StdNanoSeconds;

   // Standard C++ TypeDefs
   typedef ::std::thread                        StdThread;
   typedef ::std::atomic<bool>                  StdAtomicBool;
   typedef ::std::mutex                         StdMutex;
   typedef ::std::recursive_mutex               StdRecursiveMutex;
   typedef ::std::shared_mutex                  StdSharedMutex;
   typedef ::std::condition_variable_any        StdConditionVariableAny;
   typedef ::std::condition_variable            StdConditionVariable;
   typedef ::std::milli                         StdMilli;
   typedef ::std::micro                         StdMicro;
   typedef ::std::nano                          StdNano;
   typedef ::std::unique_lock<StdMutex>                   StdUniqueLockMutex;
   typedef ::std::shared_lock<StdSharedMutex>             StdSharedLockMutex;
   typedef ::std::cv_status                               StdCvStatus;

   typedef ::std::atomic<uint64_t> StdAtomicUInt64;
   typedef ::std::atomic<uint32_t> StdAtomicUInt32;

   typedef ::std::ostream StdOStream;
   typedef ::std::istream StdIStream;
   typedef ::std::ifstream StdIfStream;
   typedef ::std::ofstream StdOfStream;


   typedef ::std::string       StdString;
   typedef ::std::stringstream StdStringStream;
   typedef ::std::numeric_limits<size_t> StdLimitSizeT;

   // C++17
   typedef ::std::string_view StdStringView;
   typedef ::std::experimental::filesystem::directory_iterator  StdFileSystemDirectoryIterator;
   typedef ::std::experimental::filesystem::path                StdFileSystemPath;

   /// <summary>
   /// Checks if 'str' starts with 'match'.
   /// </summary>
   template<bool CASESENSITIVE = false>
   INLINE bool startsWith(const StdString& str, const StdString& match)
   {
      // get lengths
      const size_t LENS = str.length();
      const size_t LENM = match.length();

      // match must be smaller or equal to str
      if (LENM <= LENS)
      {
         // compare characters
         for (size_t i = 0; i < LENM; i++)
         {
            if (CASESENSITIVE)
            {
               if (str[i] != match[i])
                  return false;
            }
            else
            {
               if (::tolower(str[i]) != ::tolower(match[i]))
                  return false;
            }
         }

         // match
         return true;
      }

      // match is larger than str
      // hence str can not start with match
      else
         return false;
   }
}
