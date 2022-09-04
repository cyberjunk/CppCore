#pragma once

// CppCore Headers
#include <CppCore/Containers/Array.h>
#include <CppCore/Containers/Queue.h>
#include <CppCore/Containers/LinkedList.h>
#include <CppCore/Containers/MinHeap.h>
#include <CppCore/Encoding.h>
#include <CppCore/BitOps.h>
#include <CppCore/CPUID.h>
#include <CppCore/Math/Util.h>
#include <CppCore/Math/BigInt.h>
#include <CppCore/Math/Primes.h>
#include <CppCore/Math/V2.h>
#include <CppCore/Math/V3.h>
#include <CppCore/Hash/CRC32.h>
#include <CppCore/Hash/MD5.h>
#include <CppCore/Hash/Murmur3.h>
#include <CppCore/Hash/SHA2.h>
#include <CppCore/Crypto/AES.h>
#include <CppCore/Crypto/HMAC.h>
#include <CppCore/Crypto/PBKDF2.h>
#include <CppCore/Uuid.h>
#include <CppCore/Memory.h>
#include <CppCore/String.h>
#include <CppCore/Buffer.h>
#include <CppCore/Random.h>
#include <CppCore/System.h>
#include <CppCore/Network/Socket.h>
#include <CppCore/Example/Model.h>

// Visual Studio Test Framework
#if defined(CPPCORE_COMPILER_MSVC)
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#endif

#define MAXMODELS 4

// TEST MODELS
#define MODEL1_ID    7U
#define MODEL1_NAME  "Thomas"
#define MODEL2_ID    3U
#define MODEL2_NAME  "Clara"
#define MODEL3_ID    5U
#define MODEL3_NAME  "Alex"
#define MODEL4_ID    1U
#define MODEL4_NAME  "Max"

// TEST MODEL IDS IN ORDER
#define ORDER1_ID MODEL4_ID
#define ORDER2_ID MODEL2_ID
#define ORDER3_ID MODEL3_ID
#define ORDER4_ID MODEL1_ID

// TEST MODEL NAMES IN ORDER
#define ORDER1_NAME MODEL3_NAME
#define ORDER2_NAME MODEL2_NAME
#define ORDER3_NAME MODEL4_NAME
#define ORDER4_NAME MODEL1_NAME

using namespace CppCore;

extern Model models[MAXMODELS];

INLINE void resetModels()
{
   models[0].setId(MODEL1_ID);
   models[0].setName(MODEL1_NAME);

   models[1].setId(MODEL2_ID);
   models[1].setName(MODEL2_NAME);

   models[2].setId(MODEL3_ID);
   models[2].setName(MODEL3_NAME);

   models[3].setId(MODEL4_ID);
   models[3].setName(MODEL4_NAME);
}
