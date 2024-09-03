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
      /// <summary>
      /// Instruction Enumeration
      /// </summary>
      enum class Instruction
      {
         //                   INTEL ARCH   (YEAR) | AMD ARCH   (YEAR)
         MMX,              // P55C         (1997) | K6         (1997)
         FXSR,             // Pentium 2    (----) | ?          (----)
         SSE,              // Katmai       (1999) | Palomino   (2001)
         SSE2,             // Willamette   (2001) | Clawhammer (2003)
         SSE3,             // Prescott     (2004) | Venice     (2005)
         SSSE3,            // Woodcrest    (2006) | Bulldozer  (2011)
         SAHF,             // Penryn       (2008) | ?          (----)
         CX16,             // Penryn       (2008) | Bulldozer  (2011)
         SSE41,            // Penryn       (2008) | Bulldozer  (2011)
         SSE42,            // Nehalem      (2008) | Bulldozer  (2011)
         POPCNT,           // Nehalem      (2008) | Bulldozer  (2011)
         PCLMUL,           // Westmere     (2010) | Bulldozer  (2011)
         AES,              // Broadwell    (2010) | Bulldozer  (2011)
         AVX,              // Sandy Bridge (2011) | Bulldozer  (2011)
         XSAVE,            // Sandy Bridge (2011) | -          (----)
         F16C,             // Ivy Bridge   (2012) | Bulldozer  (2011)
         FSGSBASE,         // Ivy Bridge   (2012) | Steamroller(2014)
         RDRAND,           // Ivy Bridge   (2012) | Excavator  (2015)
         FMA3,             // Haswell      (2013) | Piledriver (2012)
         LZCNT,            // Haswell      (2013) | Piledriver (2012)
         BMI1,             // Haswell      (2013) | Piledriver (2012)
         BMI2,             // Haswell      (2013) | Excavator  (2015)
         MOVBE,            // Haswell      (2013) | Excavator  (2015)
         HLE,              // Haswell      (2013) | -          (----)
         AVX2,             // Haswell      (2013) | Excavator  (2015)
         RDSEED,           // Broadwell    (2014) | Excavator  (2015)
         ADX,              // Broadwell    (2014) | Zen1       (2017)
         CLFLUSHOPT,       // Skylake      (2015) | Zen1       (2017)
         XSAVEC,           // Skylake      (2015) | Zen1       (2017)
         XSAVES,           // Skylake      (2015) | Zen1       (2017)
         SGX,              // Skylake      (2015) | -          (----)
         SHA,              // Goldmont     (2016) | Zen1       (2017)
         //                   INTEL AVX512
         AVX512F,          // Skylake      (2015)
         AVX512VL,         // Skylake      (2015)
         AVX512BW,         // Skylake      (2015)
         AVX512DQ,         // Skylake      (2015)
         AVX512CD,         // Skylake      (2015)
         AVX512PF,         // Kn. Landing  (----)
         AVX512ER,         // Kn. Landing  (----)
         AVX512VBMI,       // Cannonlake   (2018)
         AVX512IFMA,       // Cannonlake   (2018)
         AVX512VNNI,       // Icelake      (2019)
         AVX512VBMI2,      // Icelake      (2019)
         AVX512BITALG,     // Icelake      (2019)
         AVX512VPOPCNTDQ   // Icelake      (2019)
      };

      /// <summary>
      /// Get Name for Instruction Enum
      /// </summary>
      constexpr static INLINE const char* getName(const Instruction& i)
      {
         switch (i)
         {
         case Instruction::MMX:              return "MMX";
         case Instruction::FXSR:             return "FXSR";
         case Instruction::SSE:              return "SSE";
         case Instruction::SSE2:             return "SSE2";
         case Instruction::SSE3:             return "SSE3";
         case Instruction::SSSE3:            return "SSSE3";
         case Instruction::SAHF:             return "SAHF";
         case Instruction::CX16:             return "CX16";
         case Instruction::SSE41:            return "SSE4.1";
         case Instruction::SSE42:            return "SSE4.2";
         case Instruction::POPCNT:           return "POPCNT";
         case Instruction::PCLMUL:           return "PCLMUL";
         case Instruction::AES:              return "AES";
         case Instruction::AVX:              return "AVX";
         case Instruction::XSAVE:            return "XSAVE";
         case Instruction::F16C:             return "F16C";
         case Instruction::FSGSBASE:         return "FSGSBASE";
         case Instruction::RDRAND:           return "RDRAND";
         case Instruction::FMA3:             return "FMA3";
         case Instruction::LZCNT:            return "LZCNT";
         case Instruction::BMI1:             return "BMI1";
         case Instruction::BMI2:             return "BMI2";
         case Instruction::MOVBE:            return "MOVBE";
         case Instruction::HLE:              return "HLE";
         case Instruction::AVX2:             return "AVX2";
         case Instruction::RDSEED:           return "RDSEED";
         case Instruction::ADX:              return "ADX";
         case Instruction::CLFLUSHOPT:       return "CLFLUSHOPT";
         case Instruction::XSAVEC:           return "XSAVEC";
         case Instruction::XSAVES:           return "XSAVES";
         case Instruction::SGX:              return "SGX";
         case Instruction::SHA:              return "SHA";
         // INTEL AVX512
         case Instruction::AVX512F:          return "AVX512F";
         case Instruction::AVX512VL:         return "AVX512VL";
         case Instruction::AVX512BW:         return "AVX512BW";
         case Instruction::AVX512DQ:         return "AVX512DQ";
         case Instruction::AVX512CD:         return "AVX512CD";
         case Instruction::AVX512PF:         return "AVX512PF";
         case Instruction::AVX512ER:         return "AVX512ER";
         case Instruction::AVX512VBMI:       return "AVX512VBMI";
         case Instruction::AVX512IFMA:       return "AVX512IFMA";
         case Instruction::AVX512VNNI:       return "AVX512VNNI";
         case Instruction::AVX512VBMI2:      return "AVX512VBMI2";
         case Instruction::AVX512BITALG:     return "AVX512BITALG";
         case Instruction::AVX512VPOPCNTDQ:  return "AVX512VPOPCNTDQ";
         default:                            return "";
         }
      }

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

      /// <summary>
      /// Vendor Signatures
      /// </summary>
      class Signature
      {
      private:
         INLINE Signature() { }
      public:
         class Intel
         {
         private:
            INLINE Intel() { }
         public:
            static constexpr uint32_t EBX = 0x756e6547; // Genu
            static constexpr uint32_t EDX = 0x49656e69; // ineI
            static constexpr uint32_t ECX = 0x6c65746e; // ntel
         };
         class AMD
         {
         private:
            INLINE AMD() { }
         public:
            static constexpr uint32_t EBX = 0x68747541; // Auth
            static constexpr uint32_t EDX = 0x69746e65; // enti
            static constexpr uint32_t ECX = 0x444d4163; // cAMD
         };
         INLINE static constexpr bool isIntel(const Data& d)
         {
            return
               d.ebx == Intel::EBX &&
               d.ecx == Intel::ECX &&
               d.edx == Intel::EDX;
         }
         INLINE static constexpr bool isAMD(const Data& d)
         {
            return
               d.ebx == AMD::EBX &&
               d.ecx == AMD::ECX &&
               d.edx == AMD::EDX;
         }
      };

   protected:
      CPPCORE_ALIGN16 Type mType;
      CPPCORE_ALIGN16 Data mF1S0;
      CPPCORE_ALIGN16 Data mF7S0;
      CPPCORE_ALIGN16 Data mF7S1;
      CPPCORE_ALIGN16 Data mF13S1;
      CPPCORE_ALIGN16 Data mFX1S0;
      CPPCORE_ALIGN16 Data mFX8S0;
      union {
         CPPCORE_ALIGN16 char     mVendor[16];
         CPPCORE_ALIGN16 uint32_t mVendor32[4];
         CPPCORE_ALIGN16 Data     mVendor128[1];
      };
      union {
         CPPCORE_ALIGN16 char     mBrand[64];
         CPPCORE_ALIGN16 uint32_t mBrand32[16];
         CPPCORE_ALIGN16 Data     mBrand128[4];
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
         Data t;

         // get highest valid leaf and vendor string
         cpuid(t, 0);

         // set the vendor string
         mVendor32[0] = t.ebx;
         mVendor32[1] = t.edx;
         mVendor32[2] = t.ecx;
         mVendor32[3] = 0U;

         // load the ones we're interested in if they exist
         if (t.eax >= 1)  cpuidex(mF1S0,   1, 0); else mF1S0  = 0U;
         if (t.eax >= 7)  cpuidex(mF7S0,   7, 0); else mF7S0  = 0U;
         if (t.eax >= 7)  cpuidex(mF7S1,   7, 1); else mF7S1  = 0U;
         if (t.eax >= 13) cpuidex(mF13S1, 13, 1); else mF13S1 = 0U;

         // set type
         mType = 
            (Signature::isIntel(t)) ? Type::Intel :
            (Signature::isAMD(t))   ? Type::AMD :
            Type::Unknown;

         // get highest valid extended leaf with 0x80000000 argument
         cpuid(t, 0x80000000);

         if (t.eax >= 0x80000001) cpuidex(mFX1S0,       0x80000001, 0); else mFX1S0       = 0U;
         if (t.eax >= 0x80000002) cpuidex(mBrand128[0], 0x80000002, 0); else mBrand128[0] = 0U;
         if (t.eax >= 0x80000003) cpuidex(mBrand128[1], 0x80000003, 0); else mBrand128[1] = 0U;
         if (t.eax >= 0x80000004) cpuidex(mBrand128[2], 0x80000004, 0); else mBrand128[2] = 0U;
         if (t.eax >= 0x80000008) cpuidex(mFX8S0,       0x80000008, 0); else mFX8S0       = 0U;

         // branding string termination/unused padding
         mBrand128[3] = 0U;
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
      INLINE bool LZCNT()           const { return CppCore::bittest(mFX1S0.ecx, 5); }
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

      /// <summary>
      /// Returns true if all instructions enabled at compile-time
      /// are also supported on the current CPU at run-time.
      /// </summary>
      INLINE bool isCompatible() const 
      {
         if (CPPCORE_CPUFEAT_MMX_ENABLED        && !this->MMX())        return false;
         if (CPPCORE_CPUFEAT_FXSR_ENABLED       && !this->FXSR())       return false;
         if (CPPCORE_CPUFEAT_SSE_ENABLED        && !this->SSE())        return false;
         if (CPPCORE_CPUFEAT_SSE2_ENABLED       && !this->SSE2())       return false;
         if (CPPCORE_CPUFEAT_SSE3_ENABLED       && !this->SSE3())       return false;
         if (CPPCORE_CPUFEAT_SSSE3_ENABLED      && !this->SSSE3())      return false;
         if (CPPCORE_CPUFEAT_SAHF_ENABLED       && !this->LAHF())       return false;
         if (CPPCORE_CPUFEAT_CX16_ENABLED       && !this->CMPXCHG16B()) return false;
         if (CPPCORE_CPUFEAT_SSE41_ENABLED      && !this->SSE41())      return false;
         if (CPPCORE_CPUFEAT_SSE42_ENABLED      && !this->SSE42())      return false;
         if (CPPCORE_CPUFEAT_POPCNT_ENABLED     && !this->POPCNT())     return false;
         if (CPPCORE_CPUFEAT_PCLMUL_ENABLED     && !this->PCLMULQDQ())  return false;
         if (CPPCORE_CPUFEAT_AES_ENABLED        && !this->AES())        return false;
         if (CPPCORE_CPUFEAT_AVX_ENABLED        && !this->AVX())        return false;
         if (CPPCORE_CPUFEAT_XSAVE_ENABLED      && !this->XSAVE())      return false;
         if (CPPCORE_CPUFEAT_F16C_ENABLED       && !this->F16C())       return false;
         if (CPPCORE_CPUFEAT_FSGSBASE_ENABLED   && !this->FSGSBASE())   return false;
         if (CPPCORE_CPUFEAT_RDRAND_ENABLED     && !this->RDRAND())     return false;
         if (CPPCORE_CPUFEAT_FMA3_ENABLED       && !this->FMA())        return false;
         if (CPPCORE_CPUFEAT_LZCNT_ENABLED      && !this->LZCNT())      return false;
         if (CPPCORE_CPUFEAT_BMI1_ENABLED       && !this->BMI1())       return false;
         if (CPPCORE_CPUFEAT_BMI2_ENABLED       && !this->BMI2())       return false;
         if (CPPCORE_CPUFEAT_MOVBE_ENABLED      && !this->MOVBE())      return false;
         if (CPPCORE_CPUFEAT_HLE_ENABLED        && !this->HLE())        return false;
         if (CPPCORE_CPUFEAT_AVX2_ENABLED       && !this->AVX2())       return false;
         if (CPPCORE_CPUFEAT_RDSEED_ENABLED     && !this->RDSEED())     return false;
         if (CPPCORE_CPUFEAT_ADX_ENABLED        && !this->ADX())        return false;
         if (CPPCORE_CPUFEAT_CLFLUSHOPT_ENABLED && !this->CLFLUSHOPT()) return false;
         if (CPPCORE_CPUFEAT_XSAVEC_ENABLED     && !this->XSAVEC())     return false;
         if (CPPCORE_CPUFEAT_XSAVES_ENABLED     && !this->XSAVES())     return false;
         if (CPPCORE_CPUFEAT_SGX_ENABLED        && !this->SGX())        return false;
         if (CPPCORE_CPUFEAT_SHA_ENABLED        && !this->SHA())        return false;
         // AVX512
         if (CPPCORE_CPUFEAT_AVX512F_ENABLED         && !this->AVX512F())         return false;
         if (CPPCORE_CPUFEAT_AVX512VL_ENABLED        && !this->AVX512VL())        return false;
         if (CPPCORE_CPUFEAT_AVX512BW_ENABLED        && !this->AVX512BW())        return false;
         if (CPPCORE_CPUFEAT_AVX512DQ_ENABLED        && !this->AVX512DQ())        return false;
         if (CPPCORE_CPUFEAT_AVX512CD_ENABLED        && !this->AVX512CD())        return false;
         if (CPPCORE_CPUFEAT_AVX512PF_ENABLED        && !this->AVX512PF())        return false;
         if (CPPCORE_CPUFEAT_AVX512ER_ENABLED        && !this->AVX512ER())        return false;
         if (CPPCORE_CPUFEAT_AVX512VBMI_ENABLED      && !this->AVX512VBMI())      return false;
         if (CPPCORE_CPUFEAT_AVX512IFMA_ENABLED      && !this->AVX512IFMA())      return false;
         if (CPPCORE_CPUFEAT_AVX512VNNI_ENABLED      && !this->AVX512VNNI())      return false;
         if (CPPCORE_CPUFEAT_AVX512VBMI2_ENABLED     && !this->AVX512VBMI2())     return false;
         if (CPPCORE_CPUFEAT_AVX512BITALG_ENABLED    && !this->AVX512BITALG())    return false;
         if (CPPCORE_CPUFEAT_AVX512VPOPCNTDQ_ENABLED && !this->AVX512VPOPCNTDQ()) return false;
         // ALL OK
         return true;
      }
   };

   /// <summary>
   /// Writes instruction name to stream
   /// </summary>
   INLINE std::ostream& operator << (std::ostream& os, const CPUID::Instruction& v) { return os << CPUID::getName(v); }

#elif defined(CPPCORE_CPU_ARMORARM64)
   /// <summary>
   /// TODO: FOR ARM/ARM64
   /// </summary>
   class CPUID
   {
   };
#else
   /// <summary>
   /// Empty Stub
   /// </summary>
   class CPUID
   {
   };
#endif
}
