#pragma once

#include <CppCore/Root.h>
#include <CppCore/BitOps.h>

namespace CppCore
{
#if defined(CPPCORE_CPU_X86ORX64)
   /// <summary>
   /// X86 CPU Information using CPUID Instruction.
   /// </summary>
   class CPUID
   {
   public:
      static constexpr uint32_t MAXFUNCS    = 32;
      static constexpr uint32_t MAXEXTFUNCS = 16;
      static constexpr uint32_t MAGIC1      = 0x80000000;

      // "GenuineIntel"
      static constexpr uint32_t INTELSIGEBX = 0x756e6547;
      static constexpr uint32_t INTELSIGEDX = 0x49656e69;
      static constexpr uint32_t INTELSIGECX = 0x6c65746e;

      // "AuthenticAMD"
      static constexpr uint32_t AMDSIGEBX = 0x68747541;
      static constexpr uint32_t AMDSIGEDX = 0x69746e65;
      static constexpr uint32_t AMDSIGECX = 0x444d4163;

      /// <summary>
      /// X86 CPU Types
      /// </summary>
      enum class Type { Unknown, Intel, AMD };

      /// <summary>
      /// 4x4=16 Bytes Data used in CPUID
      /// </summary>
      struct Data
      {
      public:
         union {
            struct { 
               uint32_t eax; uint32_t ebx;
               uint32_t ecx; uint32_t edx;
            };
            uint32_t u32[4];
            int32_t  i32[4];
            char     c[16];
         };
         INLINE void operator = (const uint32_t v) { eax = ebx = ecx = edx = v; }
         INLINE operator uint32_t* () { return u32; }
         INLINE operator int32_t*  () { return i32; }
         INLINE uint32_t& operator[](size_t index) { return u32[index]; }
      };

   protected:
      Type mType;
      Data mF1S0;
      Data mF7S0;
      Data mF7S1;
      Data mF13S1;
      Data mFX1S0;
      Data mFX8S0;

      union {
         CPPCORE_ALIGN16 char     mVendor[16];
         CPPCORE_ALIGN16 uint32_t mVendor32[4];
      };
      union {
         CPPCORE_ALIGN16 char     mBrand[64];
         CPPCORE_ALIGN16 uint32_t mBrand32[16];
      };

   public:
      /// <summary>
      /// __cpuid() on MSVC and __get_cpuid() on CLANG
      /// </summary>
      INLINE void cpuid(Data& d, uint32_t leaf)
      {
      #if defined(CPPCORE_COMPILER_MSVC)
         ::__cpuid(d, leaf);
      #else
         ::__get_cpuid(leaf, &d.eax, &d.ebx, &d.ecx, &d.edx);
      #endif
      }

      /// <summary>
      /// __cpuidex() on MSVC and __get_cpuid_count() on CLANG
      /// </summary>
      INLINE void cpuidex(Data&d, uint32_t leaf, uint32_t subleaf)
      {
      #if defined(CPPCORE_COMPILER_MSVC)
         ::__cpuidex(d, leaf, subleaf);
      #else
         ::__get_cpuid_count(leaf, subleaf, &d.eax, &d.ebx, &d.ecx, &d.edx);
      #endif
      }

      /// <summary>
      /// Constructor
      /// </summary>
      INLINE CPUID()
      {
         uint32_t n;
         Data     t, f0s0, fx2s0, fx3s0, fx4s0;

         // get highest valid function ID with 0x00 argument
         cpuid(t, 0);
         n = t.eax + 1U;

         // if exists, load the ones we're interested in
         if (n > 0) cpuidex(f0s0,   0,  0); else f0s0   = 0;
         if (n > 1) cpuidex(mF1S0,  1,  0); else mF1S0  = 0;
         if (n > 2) cpuidex(mF7S0,  7,  0); else mF7S0  = 0;
         if (n > 3) cpuidex(mF7S1,  7,  1); else mF7S1  = 0;
         if (n > 4) cpuidex(mF13S1, 13, 1); else mF13S1 = 0;

         // get the vendor string
         mVendor32[0] = f0s0.ebx;
         mVendor32[1] = f0s0.edx;
         mVendor32[2] = f0s0.ecx;
         mVendor32[3] = 0U;

         // set type
         mType =
            (f0s0.ebx == INTELSIGEBX &&
             f0s0.edx == INTELSIGEDX && 
             f0s0.ecx == INTELSIGECX) ? 
            Type::Intel :
            (f0s0.ebx == AMDSIGEBX   &&
             f0s0.edx == AMDSIGEDX   && 
             f0s0.ecx == AMDSIGECX)   ? 
            Type::AMD :
            Type::Unknown;

         // get highest valid extended ID with 0x80000000 argument
         cpuid(t, MAGIC1);

         // map 0x80000000 to 0 and turn into count
         n = t.eax + 1U - MAGIC1;

         if (n > 1) cpuidex(mFX1S0, MAGIC1 + 1U, 0); else mFX1S0 = 0;
         if (n > 2) cpuidex(fx2s0,  MAGIC1 + 2U, 0); else fx2s0  = 0;
         if (n > 3) cpuidex(fx3s0,  MAGIC1 + 3U, 0); else fx3s0  = 0;
         if (n > 4) cpuidex(fx4s0,  MAGIC1 + 4U, 0); else fx4s0  = 0;
         if (n > 8) cpuidex(mFX8S0, MAGIC1 + 8U, 0); else mFX8S0 = 0;

         // load the branding string
         mBrand32[0]  = fx2s0.eax; mBrand32[1]  = fx2s0.ebx;
         mBrand32[2]  = fx2s0.ecx; mBrand32[3]  = fx2s0.edx;
         mBrand32[4]  = fx3s0.eax; mBrand32[5]  = fx3s0.ebx;
         mBrand32[6]  = fx3s0.ecx; mBrand32[7]  = fx3s0.edx;
         mBrand32[8]  = fx4s0.eax; mBrand32[9]  = fx4s0.ebx;
         mBrand32[10] = fx4s0.ecx; mBrand32[11] = fx4s0.edx;
         mBrand32[12] = 0;         mBrand32[13] = 0;
         mBrand32[14] = 0;         mBrand32[15] = 0;
      }

      ///////////////////////////////////////////////////////////////////////////////

      INLINE Type getType()   const { return mType; }
      INLINE bool isIntel()   const { return mType == Type::Intel; }
      INLINE bool isAMD()     const { return mType == Type::AMD; }
      INLINE bool isUnknown() const { return mType == Type::Unknown; }

      ///////////////////////////////////////////////////////////////////////////////

      INLINE const char* getVendor() const { return mVendor; }
      INLINE const char* getBrand()  const { return mBrand; }

      ///////////////////////////////////////////////////////////////////////////////
      // See: https://clang.llvm.org/doxygen/cpuid_8h_source.html
      // For a complete list of flags
      ///////////////////////////////////////////////////////////////////////////////

      ///////////////////////////////////////////////////////////////////////////////
      // From ECX of leaf 1 subleaf 0
      ///////////////////////////////////////////////////////////////////////////////
      INLINE bool SSE3()       const { return CppCore::bittest(mF1S0.ecx, 0);  }
      INLINE bool PCLMULQDQ()  const { return CppCore::bittest(mF1S0.ecx, 1);  }
      INLINE bool DTES64()     const { return CppCore::bittest(mF1S0.ecx, 2);  }
      INLINE bool MONITOR()    const { return CppCore::bittest(mF1S0.ecx, 3);  }
      INLINE bool DSCPL()      const { return CppCore::bittest(mF1S0.ecx, 4);  }
      INLINE bool VMX()        const { return CppCore::bittest(mF1S0.ecx, 5);  }
      INLINE bool SMX()        const { return CppCore::bittest(mF1S0.ecx, 6);  }
      INLINE bool EIST()       const { return CppCore::bittest(mF1S0.ecx, 7);  }
      INLINE bool TM2()        const { return CppCore::bittest(mF1S0.ecx, 8);  }
      INLINE bool SSSE3()      const { return CppCore::bittest(mF1S0.ecx, 9);  }
      INLINE bool CNXTID()     const { return CppCore::bittest(mF1S0.ecx, 10); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF1S0.ecx, 11); }
      INLINE bool FMA()        const { return CppCore::bittest(mF1S0.ecx, 12); }
      INLINE bool CMPXCHG16B() const { return CppCore::bittest(mF1S0.ecx, 13); }
      INLINE bool xTPR()       const { return CppCore::bittest(mF1S0.ecx, 14); }
      INLINE bool PDCM()       const { return CppCore::bittest(mF1S0.ecx, 15); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF1S0.ecx, 16); }
      INLINE bool PCID()       const { return CppCore::bittest(mF1S0.ecx, 17); }
      INLINE bool DCA()        const { return CppCore::bittest(mF1S0.ecx, 18); }
      INLINE bool SSE41()      const { return CppCore::bittest(mF1S0.ecx, 19); }
      INLINE bool SSE42()      const { return CppCore::bittest(mF1S0.ecx, 20); }
      INLINE bool x2APIC()     const { return CppCore::bittest(mF1S0.ecx, 21); }
      INLINE bool MOVBE()      const { return CppCore::bittest(mF1S0.ecx, 22); }
      INLINE bool POPCNT()     const { return CppCore::bittest(mF1S0.ecx, 23); }
      INLINE bool TSCDeadline()const { return CppCore::bittest(mF1S0.ecx, 24); }
      INLINE bool AES()        const { return CppCore::bittest(mF1S0.ecx, 25); }
      INLINE bool XSAVE()      const { return CppCore::bittest(mF1S0.ecx, 26); }
      INLINE bool OSXSAVE()    const { return CppCore::bittest(mF1S0.ecx, 27); }
      INLINE bool AVX()        const { return CppCore::bittest(mF1S0.ecx, 28); }
      INLINE bool F16C()       const { return CppCore::bittest(mF1S0.ecx, 29); }
      INLINE bool RDRAND()     const { return CppCore::bittest(mF1S0.ecx, 30); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF1S0.ecx, 31); }
      ///////////////////////////////////////////////////////////////////////////////
      // From EDX of leaf 1 subleaf 0
      ///////////////////////////////////////////////////////////////////////////////
      INLINE bool FPU()        const { return CppCore::bittest(mF1S0.edx, 0);  }
      INLINE bool VME()        const { return CppCore::bittest(mF1S0.edx, 1);  }
      INLINE bool DE()         const { return CppCore::bittest(mF1S0.edx, 2);  }
      INLINE bool PSE()        const { return CppCore::bittest(mF1S0.edx, 3);  }
      INLINE bool TSC()        const { return CppCore::bittest(mF1S0.edx, 4);  }
      INLINE bool MSR()        const { return CppCore::bittest(mF1S0.edx, 5);  }
      INLINE bool PAE()        const { return CppCore::bittest(mF1S0.edx, 6);  }
      INLINE bool MCE()        const { return CppCore::bittest(mF1S0.edx, 7);  }
      INLINE bool CX8()        const { return CppCore::bittest(mF1S0.edx, 8);  }
      INLINE bool APIC()       const { return CppCore::bittest(mF1S0.edx, 9);  }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF1S0.edx, 10); }
      INLINE bool SEP()        const { return CppCore::bittest(mF1S0.edx, 11); }
      INLINE bool MTRR()       const { return CppCore::bittest(mF1S0.edx, 12); }
      INLINE bool PGE()        const { return CppCore::bittest(mF1S0.edx, 13); }
      INLINE bool MCA()        const { return CppCore::bittest(mF1S0.edx, 14); }
      INLINE bool CMOV()       const { return CppCore::bittest(mF1S0.edx, 15); }
      INLINE bool PAT()        const { return CppCore::bittest(mF1S0.edx, 16); }
      INLINE bool PSE36()      const { return CppCore::bittest(mF1S0.edx, 17); }
      INLINE bool PSN()        const { return CppCore::bittest(mF1S0.edx, 18); }
      INLINE bool CLFSH()      const { return CppCore::bittest(mF1S0.edx, 19); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF1S0.edx, 20); }
      INLINE bool DS()         const { return CppCore::bittest(mF1S0.edx, 21); }
      INLINE bool ACPI()       const { return CppCore::bittest(mF1S0.edx, 22); }
      INLINE bool MMX()        const { return CppCore::bittest(mF1S0.edx, 23); }
      INLINE bool FXSR()       const { return CppCore::bittest(mF1S0.edx, 24); }
      INLINE bool SSE()        const { return CppCore::bittest(mF1S0.edx, 25); }
      INLINE bool SSE2()       const { return CppCore::bittest(mF1S0.edx, 26); }
      INLINE bool SS()         const { return CppCore::bittest(mF1S0.edx, 27); }
      INLINE bool HTT()        const { return CppCore::bittest(mF1S0.edx, 28); }
      INLINE bool TM()         const { return CppCore::bittest(mF1S0.edx, 29); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF1S0.edx, 30); }
      INLINE bool PBE()        const { return CppCore::bittest(mF1S0.edx, 31); }
      ///////////////////////////////////////////////////////////////////////////////
      // From EBX of leaf 7 subleaf 0
      ///////////////////////////////////////////////////////////////////////////////
      INLINE bool FSGSBASE()   const { return CppCore::bittest(mF7S0.ebx, 0);  }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF7S0.ebx, 1);  }
      INLINE bool SGX()        const { return CppCore::bittest(mF7S0.ebx, 2);  }
      INLINE bool BMI1()       const { return CppCore::bittest(mF7S0.ebx, 3);  }
      INLINE bool HLE()        const { return CppCore::bittest(mF7S0.ebx, 4)  && isIntel(); }
      INLINE bool AVX2()       const { return CppCore::bittest(mF7S0.ebx, 5);  }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF7S0.ebx, 6);  }
      INLINE bool SMEP()       const { return CppCore::bittest(mF7S0.ebx, 7);  }
      INLINE bool BMI2()       const { return CppCore::bittest(mF7S0.ebx, 8);  }
      INLINE bool ERMS()       const { return CppCore::bittest(mF7S0.ebx, 9);  }
      INLINE bool INVPCID()    const { return CppCore::bittest(mF7S0.ebx, 10); }
      INLINE bool RTM()        const { return CppCore::bittest(mF7S0.ebx, 11) && isIntel(); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF7S0.ebx, 12); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF7S0.ebx, 13); }
      INLINE bool MPX()        const { return CppCore::bittest(mF7S0.ebx, 14); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF7S0.ebx, 15); }
      INLINE bool AVX512F()    const { return CppCore::bittest(mF7S0.ebx, 16); }
      INLINE bool AVX512DQ()   const { return CppCore::bittest(mF7S0.ebx, 17); }
      INLINE bool RDSEED()     const { return CppCore::bittest(mF7S0.ebx, 18); }
      INLINE bool ADX()        const { return CppCore::bittest(mF7S0.ebx, 19); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF7S0.ebx, 20); }
      INLINE bool AVX512IFMA() const { return CppCore::bittest(mF7S0.ebx, 21); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF7S0.ebx, 22); }
      INLINE bool CLFLUSHOPT() const { return CppCore::bittest(mF7S0.ebx, 23); }
      INLINE bool CLWB()       const { return CppCore::bittest(mF7S0.ebx, 24); }
//    INLINE bool UNUSED()     const { return CppCore::bittest(mF7S0.ebx, 25); }
      INLINE bool AVX512PF()   const { return CppCore::bittest(mF7S0.ebx, 26); }
      INLINE bool AVX512ER()   const { return CppCore::bittest(mF7S0.ebx, 27); }
      INLINE bool AVX512CD()   const { return CppCore::bittest(mF7S0.ebx, 28); }
      INLINE bool SHA()        const { return CppCore::bittest(mF7S0.ebx, 29); }
      INLINE bool AVX512BW()   const { return CppCore::bittest(mF7S0.ebx, 30); }
      INLINE bool AVX512VL()   const { return CppCore::bittest(mF7S0.ebx, 31); }
      ///////////////////////////////////////////////////////////////////////////////
      // From ECX of leaf 7 subleaf 0
      ///////////////////////////////////////////////////////////////////////////////
      INLINE bool PREFETCHWT1()     const { return CppCore::bittest(mF7S0.ecx, 0);  }
      INLINE bool AVX512VBMI()      const { return CppCore::bittest(mF7S0.ecx, 1);  }
      INLINE bool PKU()             const { return CppCore::bittest(mF7S0.ecx, 2);  }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 3);  }
      INLINE bool OSPKE()           const { return CppCore::bittest(mF7S0.ecx, 4);  }
      INLINE bool WAITPKG()         const { return CppCore::bittest(mF7S0.ecx, 5);  }
      INLINE bool AVX512VBMI2()     const { return CppCore::bittest(mF7S0.ecx, 6);  }
      INLINE bool SHSTK()           const { return CppCore::bittest(mF7S0.ecx, 7);  }
      INLINE bool GFNI()            const { return CppCore::bittest(mF7S0.ecx, 8);  }
      INLINE bool VAES()            const { return CppCore::bittest(mF7S0.ecx, 9);  }
      INLINE bool VPCLMULQDQ()      const { return CppCore::bittest(mF7S0.ecx, 10); }
      INLINE bool AVX512VNNI()      const { return CppCore::bittest(mF7S0.ecx, 11); }
      INLINE bool AVX512BITALG()    const { return CppCore::bittest(mF7S0.ecx, 12); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 13); }
      INLINE bool AVX512VPOPCNTDQ() const { return CppCore::bittest(mF7S0.ecx, 14); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 15); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 16); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 17); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 18); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 19); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 20); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 21); }
      INLINE bool RDPID()           const { return CppCore::bittest(mF7S0.ecx, 22); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 23); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 24); }
      INLINE bool CLDEMOTE()        const { return CppCore::bittest(mF7S0.ecx, 25); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 26); }
      INLINE bool MOVDIRI()         const { return CppCore::bittest(mF7S0.ecx, 27); }
      INLINE bool MOVDIR64B()       const { return CppCore::bittest(mF7S0.ecx, 28); }
      INLINE bool ENQCMD()          const { return CppCore::bittest(mF7S0.ecx, 29); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 30); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.ecx, 31); }
      ///////////////////////////////////////////////////////////////////////////////
      // From EDX of leaf 7 subleaf 0
      ///////////////////////////////////////////////////////////////////////////////
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 0);  }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 1);  }
      INLINE bool AVX5124VNNIW()    const { return CppCore::bittest(mF7S0.edx, 2);  }
      INLINE bool AVX5124FMAPS()    const { return CppCore::bittest(mF7S0.edx, 3);  }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 4);  }
      INLINE bool UINTR()           const { return CppCore::bittest(mF7S0.edx, 5);  }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 6);  }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 7);  }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 8);  }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 9);  }
      INLINE bool SERIALIZE()       const { return CppCore::bittest(mF7S0.edx, 10); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 11); }
      INLINE bool TSXLDTRK()        const { return CppCore::bittest(mF7S0.edx, 12); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 13); }
      INLINE bool PCONFIG()         const { return CppCore::bittest(mF7S0.edx, 14); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 15); }
      INLINE bool IBT()             const { return CppCore::bittest(mF7S0.edx, 16); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mF7S0.edx, 17); }
      INLINE bool AMXBF16()         const { return CppCore::bittest(mF7S0.edx, 18); }
      INLINE bool AVX512FP16()      const { return CppCore::bittest(mF7S0.edx, 19); }
      INLINE bool AMXTILE()         const { return CppCore::bittest(mF7S0.edx, 20); }
      INLINE bool AMXINT8()         const { return CppCore::bittest(mF7S0.edx, 21); }
      ///////////////////////////////////////////////////////////////////////////////
      // From EAX of leaf 7 subleaf 1
      ///////////////////////////////////////////////////////////////////////////////
      INLINE bool AVXVNNI()         const { return CppCore::bittest(mF7S1.eax, 4);  }
      INLINE bool AVX512BF16()      const { return CppCore::bittest(mF7S1.eax, 5);  }
      INLINE bool HRESET()          const { return CppCore::bittest(mF7S1.eax, 22); }
      ///////////////////////////////////////////////////////////////////////////////
      // From EAX of leaf 13 subleaf 1
      ///////////////////////////////////////////////////////////////////////////////
      INLINE bool XSAVEOPT()        const { return CppCore::bittest(mF13S1.eax, 0); }
      INLINE bool XSAVEC()          const { return CppCore::bittest(mF13S1.eax, 1); }
      INLINE bool XSAVES()          const { return CppCore::bittest(mF13S1.eax, 3); }
      ///////////////////////////////////////////////////////////////////////////////
      // From ECX of leaf 0x80000001 subleaf 0
      ///////////////////////////////////////////////////////////////////////////////
      INLINE bool LAHF()            const { return CppCore::bittest(mFX1S0.ecx, 0); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 1); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 2); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 3); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 4); }
      INLINE bool LZCNT()           const { return CppCore::bittest(mFX1S0.ecx, 5)  && isIntel(); }
      INLINE bool ABM()             const { return CppCore::bittest(mFX1S0.ecx, 5)  && isAMD();   }
      INLINE bool SSE4a()           const { return CppCore::bittest(mFX1S0.ecx, 6)  && isAMD();   }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 7); }
      INLINE bool PRFCHW()          const { return CppCore::bittest(mFX1S0.ecx, 8); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 9); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 10); }
      INLINE bool XOP()             const { return CppCore::bittest(mFX1S0.ecx, 11); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 12); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 13); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 14); }
      INLINE bool LWP()             const { return CppCore::bittest(mFX1S0.ecx, 15); }
      INLINE bool FMA4()            const { return CppCore::bittest(mFX1S0.ecx, 16); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 17); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 18); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 19); }
//    INLINE bool UNUSED()          const { return CppCore::bittest(mFX1S0.ecx, 20); }
      INLINE bool TBM()             const { return CppCore::bittest(mFX1S0.ecx, 21) && isAMD();   }
      INLINE bool MWAITX()          const { return CppCore::bittest(mFX1S0.ecx, 29); }
      ///////////////////////////////////////////////////////////////////////////////
      // From EDX of leaf 0x80000001 subleaf 0
      ///////////////////////////////////////////////////////////////////////////////
      INLINE bool MMXEXT()          const { return CppCore::bittest(mFX1S0.edx, 22) && isAMD();   }
      INLINE bool LM()              const { return CppCore::bittest(mFX1S0.edx, 29) && isAMD(); }
      INLINE bool _3DNOWEXT()       const { return CppCore::bittest(mFX1S0.edx, 30) && isAMD(); }
      INLINE bool _3DNOW()          const { return CppCore::bittest(mFX1S0.edx, 31) && isAMD(); }
      ///////////////////////////////////////////////////////////////////////////////
      // From EBX of leaf 0x80000008 subleaf 0
      ///////////////////////////////////////////////////////////////////////////////
      INLINE bool CLZERO()          const { return CppCore::bittest(mFX8S0.ebx, 0); }
      INLINE bool RDPRU()           const { return CppCore::bittest(mFX8S0.ebx, 4); }
      INLINE bool WBNOINVD()        const { return CppCore::bittest(mFX8S0.ebx, 9); }
   };
#endif
}
