#pragma once

// export macro
#ifndef CPPCORE_EXPORT
#if defined(_WIN64) || defined(_WIN32)
#define CPPCORE_EXPORT __declspec(dllexport)
#else
#define CPPCORE_EXPORT __attribute__((visibility("default")))
#endif
#endif

#include <stddef.h>

// macro for prime declarations
#define CPPCORE_PRIME_DECLARATION(name)                                 \
  CPPCORE_EXPORT int  name ## _test     (void* data, size_t certainty); \
  CPPCORE_EXPORT void name ## _generate (void* data, size_t certainty);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

   CPPCORE_PRIME_DECLARATION(cppcore_prime128)
   CPPCORE_PRIME_DECLARATION(cppcore_prime256)
   CPPCORE_PRIME_DECLARATION(cppcore_prime512)

#ifdef __cplusplus
}
#endif
