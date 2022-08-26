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
      static constexpr uint32_t MAXFUNCS      = 32;
      static constexpr uint32_t MAXEXTFUNCS   = 16;
      static constexpr char     VENDORINTEL[] = "GenuineIntel";
      static constexpr char     VENDORAMD[]   = "AuthenticAMD";
      static constexpr uint32_t MAGIC1        = 0x80000000;

      /// <summary>
      /// X86 CPU Types
      /// </summary>
      enum class Type { Unknown, Intel, AMD };

   public:
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
      Type     mType;
      uint32_t mNumIds;
      uint32_t mNumExtIds;
      union {
         CPPCORE_ALIGN16 char     mVendor[16];
         CPPCORE_ALIGN16 uint32_t mVendor32[4];
      };
      union {
         CPPCORE_ALIGN16 char     mBrand[64];
         CPPCORE_ALIGN16 uint32_t mBrand32[16];
      };
      union {
         struct {
            Data mF0;  Data mF1;  Data mF2;  Data mF3;
            Data mF4;  Data mF5;  Data mF6;  Data mF7;
            Data mF8;  Data mF9;  Data mF10; Data mF11;
            Data mF12; Data mF13; Data mF14; Data mF15;
            Data mF16; Data mF17; Data mF18; Data mF19;
            Data mF20; Data mF21; Data mF22; Data mF23;
            Data mF24; Data mF25; Data mF26; Data mF27;
            Data mF28; Data mF29; Data mF30; Data mF31;
         };
         CPPCORE_ALIGN16 Data mF[MAXFUNCS];
      };

      union {
         struct {
            Data mFX0;  Data mFX1;  Data mFX2;  Data mFX3;
            Data mFX4;  Data mFX5;  Data mFX6;  Data mFX7;
            Data mFX8;  Data mFX9;  Data mFX10; Data mFX11;
            Data mFX12; Data mFX13; Data mFX14; Data mFX15;
         };
         CPPCORE_ALIGN16 Data mFX[MAXEXTFUNCS];
      };

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE CPUID()
      {
         Data t;

         // get highest valid function ID with 0x00 argument
         ::__cpuid(t, 0);
         mNumIds = t.eax + 1U;

         // load them all
         for (uint32_t i = 0; i < MIN(mNumIds, MAXFUNCS); i++)
            ::__cpuidex(mF[i], i, 0);

         // and clear the unused
         for (uint32_t i = mNumIds; i < MAXFUNCS; i++)
            mF[i] = 0U;

         // get the vendor string
         mVendor32[0] = mF[0].ebx;
         mVendor32[1] = mF[0].edx;
         mVendor32[2] = mF[0].ecx;
         mVendor32[3] = 0U;

         // set type (todo: remove strcmp)
         if      (0 == ::strcmp(mVendor, VENDORINTEL)) mType = Type::Intel;
         else if (0 == ::strcmp(mVendor, VENDORAMD))   mType = Type::AMD;
         else                                          mType = Type::Unknown;

         // get highest valid extended ID with 0x80000000 argument
         ::__cpuid(t, MAGIC1);
         mNumExtIds = t.eax - MAGIC1;

         // load them all
         for (uint32_t i = 0; i < MIN(mNumExtIds, MAXEXTFUNCS); i++)
            ::__cpuidex(mFX[i], MAGIC1 + i, 0);
      
         // and clear the unused
         for (uint32_t i = mNumExtIds; i < MAXEXTFUNCS; i++)
            mFX[i] = 0U;

         // load the branding string
         mBrand32[0]  = mFX2.eax; mBrand32[1]  = mFX2.ebx; 
         mBrand32[2]  = mFX2.ecx; mBrand32[3]  = mFX2.edx;
         mBrand32[4]  = mFX3.eax; mBrand32[5]  = mFX3.ebx;
         mBrand32[6]  = mFX3.ecx; mBrand32[7]  = mFX3.edx;
         mBrand32[8]  = mFX4.eax; mBrand32[9]  = mFX4.ebx;
         mBrand32[10] = mFX4.ecx; mBrand32[11] = mFX4.edx;
         mBrand32[12] = 0;        mBrand32[13] = 0;
         mBrand32[14] = 0;        mBrand32[15] = 0;
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

      // From F1.ECX

      INLINE bool SSE3()       const { return CppCore::bittest(mF1.ecx, 0);  }
      INLINE bool PCLMULQDQ()  const { return CppCore::bittest(mF1.ecx, 1);  }
      INLINE bool MONITOR()    const { return CppCore::bittest(mF1.ecx, 3);  }
      INLINE bool SSSE3()      const { return CppCore::bittest(mF1.ecx, 9);  }
      INLINE bool FMA()        const { return CppCore::bittest(mF1.ecx, 12); }
      INLINE bool CMPXCHG16B() const { return CppCore::bittest(mF1.ecx, 13); }
      INLINE bool SSE41()      const { return CppCore::bittest(mF1.ecx, 19); }
      INLINE bool SSE42()      const { return CppCore::bittest(mF1.ecx, 20); }
      INLINE bool MOVBE()      const { return CppCore::bittest(mF1.ecx, 22); }
      INLINE bool POPCNT()     const { return CppCore::bittest(mF1.ecx, 23); }
      INLINE bool AES()        const { return CppCore::bittest(mF1.ecx, 25); }
      INLINE bool XSAVE()      const { return CppCore::bittest(mF1.ecx, 26); }
      INLINE bool OSXSAVE()    const { return CppCore::bittest(mF1.ecx, 27); }
      INLINE bool AVX()        const { return CppCore::bittest(mF1.ecx, 28); }
      INLINE bool F16C()       const { return CppCore::bittest(mF1.ecx, 29); }
      INLINE bool RDRAND()     const { return CppCore::bittest(mF1.ecx, 30); }
   
      // From F1.EDX

      INLINE bool MSR()        const { return CppCore::bittest(mF1.edx, 5);  }
      INLINE bool CX8()        const { return CppCore::bittest(mF1.edx, 8);  }
      INLINE bool SEP()        const { return CppCore::bittest(mF1.edx, 11); }
      INLINE bool CMOV()       const { return CppCore::bittest(mF1.edx, 15); }
      INLINE bool CLFSH()      const { return CppCore::bittest(mF1.edx, 19); }
      INLINE bool MMX()        const { return CppCore::bittest(mF1.edx, 23); }
      INLINE bool FXSR()       const { return CppCore::bittest(mF1.edx, 24); }
      INLINE bool SSE()        const { return CppCore::bittest(mF1.edx, 25); }
      INLINE bool SSE2()       const { return CppCore::bittest(mF1.edx, 26); }

      // From F7.EBX

      INLINE bool FSGSBASE() const { return CppCore::bittest(mF7.ebx, 0);  }
      INLINE bool BMI1()     const { return CppCore::bittest(mF7.ebx, 3);  }
      INLINE bool HLE()      const { return CppCore::bittest(mF7.ebx, 4)  && isIntel(); }
      INLINE bool AVX2()     const { return CppCore::bittest(mF7.ebx, 5);  }
      INLINE bool BMI2()     const { return CppCore::bittest(mF7.ebx, 8);  }
      INLINE bool ERMS()     const { return CppCore::bittest(mF7.ebx, 9);  }
      INLINE bool INVPCID()  const { return CppCore::bittest(mF7.ebx, 10); }
      INLINE bool RTM()      const { return CppCore::bittest(mF7.ebx, 11) && isIntel(); }
      INLINE bool AVX512F()  const { return CppCore::bittest(mF7.ebx, 16); }
      INLINE bool RDSEED()   const { return CppCore::bittest(mF7.ebx, 18); }
      INLINE bool ADX()      const { return CppCore::bittest(mF7.ebx, 19); }
      INLINE bool AVX512PF() const { return CppCore::bittest(mF7.ebx, 26); }
      INLINE bool AVX512ER() const { return CppCore::bittest(mF7.ebx, 27); }
      INLINE bool AVX512CD() const { return CppCore::bittest(mF7.ebx, 28); }
      INLINE bool SHA()      const { return CppCore::bittest(mF7.ebx, 29); }

      // From F7.ECX

      INLINE bool PREFETCHWT1() const { return CppCore::bittest(mF7.ecx, 0); }

      // From FX1.ECX (F81.ECX)

      INLINE bool LAHF()  const { return CppCore::bittest(mFX1.ecx, 0); }
      INLINE bool LZCNT() const { return CppCore::bittest(mFX1.ecx, 5)  && isIntel(); }
      INLINE bool ABM()   const { return CppCore::bittest(mFX1.ecx, 5)  && isAMD();   }
      INLINE bool SSE4a() const { return CppCore::bittest(mFX1.ecx, 6)  && isAMD();   }
      INLINE bool XOP()   const { return CppCore::bittest(mFX1.ecx, 11) && isAMD();   }
      INLINE bool TBM()   const { return CppCore::bittest(mFX1.ecx, 21) && isAMD();   }

      // From FX1.EDX (F81.EDX)

      INLINE bool SYSCALL()   const { return CppCore::bittest(mFX1.edx, 11) && isIntel(); }
      INLINE bool MMXEXT()    const { return CppCore::bittest(mFX1.edx, 22) && isAMD();   }
      INLINE bool RDTSCP()    const { return CppCore::bittest(mFX1.edx, 27) && isIntel(); }
      INLINE bool _3DNOWEXT() const { return CppCore::bittest(mFX1.edx, 30) && isAMD();   }
      INLINE bool _3DNOW()    const { return CppCore::bittest(mFX1.edx, 31) && isAMD();   }
   };
#endif







}
