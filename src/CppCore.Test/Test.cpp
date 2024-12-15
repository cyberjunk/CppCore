
#include <CppCore.Test/Precompiled.h>

// test model instances
Model  models[MAXMODELS];
Model* modelptrs[MAXMODELS];

// help macro
#define TEST(f, n, nl)       \
  r = (f)();                   \
  std::cout << (n) << r << (nl); \
  if (!r)                    \
    return 1;                \

template<
    typename VF, typename F, 
    typename VD, typename D, 
    typename VI, typename I, 
    typename VL, typename L>
int v2f_test()
{
   bool r;
   TEST((CppCore::Test::Math::V2::v2f_ctr<VF, 
       F, VD, D, VI, I, VL, L>),                            "ctr:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_equal<VF>),           "eq:     ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_notequal<VF>),        "neq:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_greater<VF>),         "gt:     ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_greaterequal<VF>),    "ge:     ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_less<VF>),            "lt:     ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_lessequal<VF>),       "le:     ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_add<VF>),             "add:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_sub<VF>),             "sub:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_mul<VF>),             "mul:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_div<VF>),             "div:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_madd<VF>),            "madd:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_msub<VF>),            "msub:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_swap<VF>),            "swap:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_abs<VF>),             "abs:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_min<VF>),             "min:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_max<VF>),             "max:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_dot<VF>),             "dot:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_cross<VF>),           "cross:  ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_length<VF>),          "length: ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_side<VF>),            "side:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_area<VF>),            "area:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_inside<VF, F>),       "inside: ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_round<VF, F>),        "round:  ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_floor<VF>),           "floor:  ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_ceil<VF>),            "ceil:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_normalise<VF>),       "norm:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_rotate<VF, F>),       "rot:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_angle<VF, F>),        "angle:  ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_angleori<VF, F>),     "anglori:", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_intersectcircleline<VF, F>),     "intersectcircleline:            ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_minsquareddistancetofiniteline<VF>), "minsquareddistancetofiniteline: ", std::endl);
   TEST((CppCore::Test::Math::V2::v2f_insidefrustum<VF, F>),           "insidefrustum:                  ", std::endl);
   return 0;
}

template<
    typename VF, typename F, 
    typename VD, typename D, 
    typename VI, typename I, 
    typename VL, typename L>
int v2i_test()
{
   bool r;
   TEST((CppCore::Test::Math::V2::v2i_ctr<VF, 
       F, VD, D, VI, I, VL, L>),                            "ctr:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_equal<VF>),           "eq:     ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_notequal<VF>),        "neq:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_greater<VF>),         "gt:     ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_greaterequal<VF>),    "ge:     ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_less<VF>),            "lt:     ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_lessequal<VF>),       "le:     ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_add<VF>),             "add:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_sub<VF>),             "sub:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_mul<VF>),             "mul:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_div<VF>),             "div:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_madd<VF>),            "madd:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_msub<VF>),            "msub:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_swap<VF>),            "swap:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_abs<VF>),             "abs:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_min<VF>),             "min:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_max<VF>),             "max:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_dot<VF>),             "dot:    ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_cross<VF>),           "cross:  ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_length<VF>),          "length: ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_side<VF>),            "side:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_area<VF>),            "area:   ", std::endl);
   TEST((CppCore::Test::Math::V2::v2i_inside<VF>),          "inside: ", std::endl);
   return 0;
}

template<
    typename VF, typename F, 
    typename VD, typename D, 
    typename VI, typename I, 
    typename VL, typename L>
int v3f_test()
{
   bool r;
   TEST((CppCore::Test::Math::V3::v3_ctr<VF, 
       F, VD, D, VI, I, VL, L>),                              "ctr:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_equal<VF, F>),           "eq:        ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_notequal<VF, F>),        "neq:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_greater<VF, F>),         "gt:        ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_greaterequal<VF, F>),    "ge:        ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_less<VF, F>),            "lt:        ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_lessequal<VF, F>),       "le:        ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_add<VF, F>),             "add:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_sub<VF, F>),             "sub:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_mul<VF, F>),             "mul:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_div<VF, F>),             "div:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_madd<VF, F>),            "madd:      ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_msub<VF, F>),            "msub:      ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_swap<VF, F>),            "swap:      ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_abs<VF, F>),             "abs:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_min<VF, F>),             "min:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_max<VF, F>),             "max:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_dot<VF, F>),             "dot:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_cross<VF, F>),           "cross:     ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_length<VF, F>),          "length:    ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_inside<VF, F>),          "inside:    ", std::endl);
   // float/double only
   TEST((CppCore::Test::Math::V3::v3_round<VF, F>),           "round:     ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_floor<VF, F>),           "floor:     ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_ceil<VF, F>),            "ceil:      ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_normalise<VF, F>),       "norm:      ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_intersectlt<VF, F>),     "intrsctlt: ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_intersectlp<VF, F>),     "intrsctlp: ", std::endl);
   return 0;
}
template<
    typename VF, typename F, 
    typename VD, typename D, 
    typename VI, typename I, 
    typename VL, typename L>
int v3i_test()
{
   bool r;
   TEST((CppCore::Test::Math::V3::v3_ctr<VF, 
       F, VD, D, VI, I, VL, L>),                              "ctr:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_equal<VF, F>),           "eq:        ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_notequal<VF, F>),        "neq:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_greater<VF, F>),         "gt:        ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_greaterequal<VF, F>),    "ge:        ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_less<VF, F>),            "lt:        ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_lessequal<VF, F>),       "le:        ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_add<VF, F>),             "add:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_sub<VF, F>),             "sub:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_mul<VF, F>),             "mul:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_div<VF, F>),             "div:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_madd<VF, F>),            "madd:      ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_msub<VF, F>),            "msub:      ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_swap<VF, F>),            "swap:      ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_abs<VF, F>),             "abs:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_min<VF, F>),             "min:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_max<VF, F>),             "max:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_dot<VF, F>),             "dot:       ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_cross<VF, F>),           "cross:     ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_length<VF, F>),          "length:    ", std::endl);
   TEST((CppCore::Test::Math::V3::v3_inside<VF, F>),          "inside:    ", std::endl);
   return 0;
}

CPUID        cpuid;
System::Info sysinfo("CppCore.Test");

// console based tests
int main()
{
   std::cout << "--------------------------------------------------" << std::endl;
   std::cout << "VERSION: " << CPPCORE_VERSION_MAJOR << "." << CPPCORE_VERSION_MINOR << "." << CPPCORE_VERSION_PATCH << std::endl;
   std::cout << "ENDIAN:  " << (CPPCORE_ENDIANESS_LITTLE ? "LITTLE" : "BIG") << std::endl;

#if defined(CPPCORE_CPU_X86ORX64)
   std::cout << "--------------------------------------------------"             << std::endl;
   std::cout << "VEN: " << cpuid.getVendor()                                     << std::endl;
   std::cout << "CPU: " << cpuid.getBrand()                                      << std::endl;
   std::cout << "COR: " << sysinfo.getCpuCoresPhysical()          << " PHYSICAL" << std::endl;
   std::cout << "COR: " << sysinfo.getCpuCoresLogical()           << " LOGICAL"  << std::endl;
   std::cout << "RAM: " << sysinfo.getRamSize()/(1024ULL*1024ULL) << " MB"       << std::endl;
   std::cout << "SUP: " << (cpuid.isCompatible() ? "YES" : "NO")                 << std::endl;
   std::cout << "--------------------------------------------------"             << std::endl;
   std::cout << "                 ENABLED " << "SUPPORTED" << std::endl;
   std::cout << "MMX:             " << (CPPCORE_CPUFEAT_MMX_ENABLED             ? "YES" : "NO ") << "     " << (cpuid.MMX()             ? "YES" : "NO") << std::endl;
   std::cout << "FXSR:            " << (CPPCORE_CPUFEAT_FXSR_ENABLED            ? "YES" : "NO ") << "     " << (cpuid.FXSR()            ? "YES" : "NO") << std::endl;
   std::cout << "SSE:             " << (CPPCORE_CPUFEAT_SSE_ENABLED             ? "YES" : "NO ") << "     " << (cpuid.SSE()             ? "YES" : "NO") << std::endl;
   std::cout << "SSE2:            " << (CPPCORE_CPUFEAT_SSE2_ENABLED            ? "YES" : "NO ") << "     " << (cpuid.SSE2()            ? "YES" : "NO") << std::endl;
   std::cout << "SSE3:            " << (CPPCORE_CPUFEAT_SSE3_ENABLED            ? "YES" : "NO ") << "     " << (cpuid.SSE3()            ? "YES" : "NO") << std::endl;
   std::cout << "SSSE3:           " << (CPPCORE_CPUFEAT_SSSE3_ENABLED           ? "YES" : "NO ") << "     " << (cpuid.SSSE3()           ? "YES" : "NO") << std::endl;
   std::cout << "SAHF:            " << (CPPCORE_CPUFEAT_SAHF_ENABLED            ? "YES" : "NO ") << "     " << (cpuid.LAHF()            ? "YES" : "NO") << std::endl;
   std::cout << "CX16:            " << (CPPCORE_CPUFEAT_CX16_ENABLED            ? "YES" : "NO ") << "     " << (cpuid.CMPXCHG16B()      ? "YES" : "NO") << std::endl;
   std::cout << "SSE4.1:          " << (CPPCORE_CPUFEAT_SSE41_ENABLED           ? "YES" : "NO ") << "     " << (cpuid.SSE41()           ? "YES" : "NO") << std::endl;
   std::cout << "SSE4.2:          " << (CPPCORE_CPUFEAT_SSE42_ENABLED           ? "YES" : "NO ") << "     " << (cpuid.SSE42()           ? "YES" : "NO") << std::endl;
   std::cout << "POPCNT:          " << (CPPCORE_CPUFEAT_POPCNT_ENABLED          ? "YES" : "NO ") << "     " << (cpuid.POPCNT()          ? "YES" : "NO") << std::endl;
   std::cout << "PCLMUL:          " << (CPPCORE_CPUFEAT_PCLMUL_ENABLED          ? "YES" : "NO ") << "     " << (cpuid.PCLMULQDQ()       ? "YES" : "NO") << std::endl;
   std::cout << "AES:             " << (CPPCORE_CPUFEAT_AES_ENABLED             ? "YES" : "NO ") << "     " << (cpuid.AES()             ? "YES" : "NO") << std::endl;
   std::cout << "AVX:             " << (CPPCORE_CPUFEAT_AVX_ENABLED             ? "YES" : "NO ") << "     " << (cpuid.AVX()             ? "YES" : "NO") << std::endl;
   std::cout << "XSAVE:           " << (CPPCORE_CPUFEAT_XSAVE_ENABLED           ? "YES" : "NO ") << "     " << (cpuid.XSAVE()           ? "YES" : "NO") << std::endl;
   std::cout << "F16C:            " << (CPPCORE_CPUFEAT_F16C_ENABLED            ? "YES" : "NO ") << "     " << (cpuid.F16C()            ? "YES" : "NO") << std::endl;
   std::cout << "FSGSBASE:        " << (CPPCORE_CPUFEAT_FSGSBASE_ENABLED        ? "YES" : "NO ") << "     " << (cpuid.FSGSBASE()        ? "YES" : "NO") << std::endl;
   std::cout << "RDRAND:          " << (CPPCORE_CPUFEAT_RDRAND_ENABLED          ? "YES" : "NO ") << "     " << (cpuid.RDRAND()          ? "YES" : "NO") << std::endl;
   std::cout << "FMA3:            " << (CPPCORE_CPUFEAT_FMA3_ENABLED            ? "YES" : "NO ") << "     " << (cpuid.FMA()             ? "YES" : "NO") << std::endl;
   std::cout << "LZCNT:           " << (CPPCORE_CPUFEAT_LZCNT_ENABLED           ? "YES" : "NO ") << "     " << (cpuid.LZCNT()           ? "YES" : "NO") << std::endl;
   std::cout << "BMI1:            " << (CPPCORE_CPUFEAT_BMI1_ENABLED            ? "YES" : "NO ") << "     " << (cpuid.BMI1()            ? "YES" : "NO") << std::endl;
   std::cout << "BMI2:            " << (CPPCORE_CPUFEAT_BMI2_ENABLED            ? "YES" : "NO ") << "     " << (cpuid.BMI2()            ? "YES" : "NO") << std::endl;
   std::cout << "MOVBE:           " << (CPPCORE_CPUFEAT_MOVBE_ENABLED           ? "YES" : "NO ") << "     " << (cpuid.MOVBE()           ? "YES" : "NO") << std::endl;
   std::cout << "HLE:             " << (CPPCORE_CPUFEAT_HLE_ENABLED             ? "YES" : "NO ") << "     " << (cpuid.HLE()             ? "YES" : "NO") << std::endl;
   std::cout << "AVX2:            " << (CPPCORE_CPUFEAT_AVX2_ENABLED            ? "YES" : "NO ") << "     " << (cpuid.AVX2()            ? "YES" : "NO") << std::endl;
   std::cout << "RDSEED:          " << (CPPCORE_CPUFEAT_RDSEED_ENABLED          ? "YES" : "NO ") << "     " << (cpuid.RDSEED()          ? "YES" : "NO") << std::endl;
   std::cout << "ADX:             " << (CPPCORE_CPUFEAT_ADX_ENABLED             ? "YES" : "NO ") << "     " << (cpuid.ADX()             ? "YES" : "NO") << std::endl;
   std::cout << "CLFLUSHOPT:      " << (CPPCORE_CPUFEAT_CLFLUSHOPT_ENABLED      ? "YES" : "NO ") << "     " << (cpuid.CLFLUSHOPT()      ? "YES" : "NO") << std::endl;
   std::cout << "XSAVEC:          " << (CPPCORE_CPUFEAT_XSAVEC_ENABLED          ? "YES" : "NO ") << "     " << (cpuid.XSAVEC()          ? "YES" : "NO") << std::endl;
   std::cout << "XSAVES:          " << (CPPCORE_CPUFEAT_XSAVES_ENABLED          ? "YES" : "NO ") << "     " << (cpuid.XSAVES()          ? "YES" : "NO") << std::endl;
   std::cout << "SGX:             " << (CPPCORE_CPUFEAT_SGX_ENABLED             ? "YES" : "NO ") << "     " << (cpuid.SGX()             ? "YES" : "NO") << std::endl;
   std::cout << "SHA:             " << (CPPCORE_CPUFEAT_SHA_ENABLED             ? "YES" : "NO ") << "     " << (cpuid.SHA()             ? "YES" : "NO") << std::endl;
   std::cout << "AVX512F:         " << (CPPCORE_CPUFEAT_AVX512F_ENABLED         ? "YES" : "NO ") << "     " << (cpuid.AVX512F()         ? "YES" : "NO") << std::endl;
   std::cout << "AVX512VL:        " << (CPPCORE_CPUFEAT_AVX512VL_ENABLED        ? "YES" : "NO ") << "     " << (cpuid.AVX512VL()        ? "YES" : "NO") << std::endl;
   std::cout << "AVX512BW:        " << (CPPCORE_CPUFEAT_AVX512BW_ENABLED        ? "YES" : "NO ") << "     " << (cpuid.AVX512BW()        ? "YES" : "NO") << std::endl;
   std::cout << "AVX512DQ:        " << (CPPCORE_CPUFEAT_AVX512DQ_ENABLED        ? "YES" : "NO ") << "     " << (cpuid.AVX512DQ()        ? "YES" : "NO") << std::endl;
   std::cout << "AVX512CD:        " << (CPPCORE_CPUFEAT_AVX512CD_ENABLED        ? "YES" : "NO ") << "     " << (cpuid.AVX512CD()        ? "YES" : "NO") << std::endl;
   std::cout << "AVX512PF:        " << (CPPCORE_CPUFEAT_AVX512PF_ENABLED        ? "YES" : "NO ") << "     " << (cpuid.AVX512PF()        ? "YES" : "NO") << std::endl;
   std::cout << "AVX512ER:        " << (CPPCORE_CPUFEAT_AVX512ER_ENABLED        ? "YES" : "NO ") << "     " << (cpuid.AVX512ER()        ? "YES" : "NO") << std::endl;
   std::cout << "AVX512VBMI:      " << (CPPCORE_CPUFEAT_AVX512VBMI_ENABLED      ? "YES" : "NO ") << "     " << (cpuid.AVX512VBMI()      ? "YES" : "NO") << std::endl;
   std::cout << "AVX512IFMA:      " << (CPPCORE_CPUFEAT_AVX512IFMA_ENABLED      ? "YES" : "NO ") << "     " << (cpuid.AVX512IFMA()      ? "YES" : "NO") << std::endl;
   std::cout << "AVX512VNNI:      " << (CPPCORE_CPUFEAT_AVX512VNNI_ENABLED      ? "YES" : "NO ") << "     " << (cpuid.AVX512VNNI()      ? "YES" : "NO") << std::endl;
   std::cout << "AVX512VBMI2:     " << (CPPCORE_CPUFEAT_AVX512VBMI2_ENABLED     ? "YES" : "NO ") << "     " << (cpuid.AVX512VBMI2()     ? "YES" : "NO") << std::endl;
   std::cout << "AVX512BITALG:    " << (CPPCORE_CPUFEAT_AVX512BITALG_ENABLED    ? "YES" : "NO ") << "     " << (cpuid.AVX512BITALG()    ? "YES" : "NO") << std::endl;
   std::cout << "AVX512VPOPCNTDQ: " << (CPPCORE_CPUFEAT_AVX512VPOPCNTDQ_ENABLED ? "YES" : "NO ") << "     " << (cpuid.AVX512VPOPCNTDQ() ? "YES" : "NO") << std::endl;
#endif

   std::cout << "-------------------------------" << std::endl;
   std::cout << "FOLDERS"                         << std::endl;
   std::cout << "-------------------------------" << std::endl;
   std::cout << "TEMP: " << sysinfo.getTempPath()                    << std::endl;
   std::cout << "PERM: " << sysinfo.getPersistentPath()              << std::endl;
   std::cout << "EXEC: " << CppCore::System::Folder::getExecutable() << std::endl;
   std::cout << "CURR: " << CppCore::System::Folder::getCurrent()    << std::endl;

   bool r;

   std::cout << "-------------------------------" << std::endl;
   std::cout << "CppCore::BitOps"                 << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::BitOps::bytemaskequal128,    "bytemaskequal128: ", std::endl);
   TEST(CppCore::Test::BitOps::bytemaskequal256,    "bytemaskequal256: ", std::endl);
   TEST(CppCore::Test::BitOps::bytemaskequal512,    "bytemaskequal512: ", std::endl);
   TEST(CppCore::Test::BitOps::equal128,            "equal128:         ", std::endl);
   TEST(CppCore::Test::BitOps::equal256,            "equal256:         ", std::endl);
   TEST(CppCore::Test::BitOps::equal512,            "equal512:         ", std::endl);
   TEST(CppCore::Test::BitOps::testzero128,         "testzero128:      ", std::endl);
   TEST(CppCore::Test::BitOps::testzero256,         "testzero256:      ", std::endl);
   TEST(CppCore::Test::BitOps::testzero512,         "testzero512:      ", std::endl);
   TEST(CppCore::Test::BitOps::shld32,              "shld32:           ", std::endl);
   TEST(CppCore::Test::BitOps::shld64,              "shld64:           ", std::endl);
   TEST(CppCore::Test::BitOps::shrd32,              "shrd32:           ", std::endl);
   TEST(CppCore::Test::BitOps::shrd64,              "shrd64:           ", std::endl);
   TEST(CppCore::Test::BitOps::rotl32,              "rotl32:           ", std::endl);
   TEST(CppCore::Test::BitOps::rotl64,              "rotl64:           ", std::endl);
   TEST(CppCore::Test::BitOps::rotr32,              "rotr32:           ", std::endl);
   TEST(CppCore::Test::BitOps::rotr64,              "rotr64:           ", std::endl);
   TEST(CppCore::Test::BitOps::rorx32,              "rorx32:           ", std::endl);
   TEST(CppCore::Test::BitOps::rorx64,              "rorx64:           ", std::endl);
   TEST(CppCore::Test::BitOps::popcnt8,             "popcnt8:          ", std::endl);
   TEST(CppCore::Test::BitOps::popcnt16,            "popcnt16:         ", std::endl);
   TEST(CppCore::Test::BitOps::popcnt32,            "popcnt32:         ", std::endl);
   TEST(CppCore::Test::BitOps::popcnt64,            "popcnt64:         ", std::endl);
   TEST(CppCore::Test::BitOps::popcnt,              "popcnt:           ", std::endl);
   TEST(CppCore::Test::BitOps::tzcnt8,              "tzcnt8:           ", std::endl);
   TEST(CppCore::Test::BitOps::tzcnt16,             "tzcnt16:          ", std::endl);
   TEST(CppCore::Test::BitOps::tzcnt32,             "tzcnt32:          ", std::endl);
   TEST(CppCore::Test::BitOps::tzcnt64,             "tzcnt64:          ", std::endl);
   TEST(CppCore::Test::BitOps::tzcnt,               "tzcnt:            ", std::endl);
   TEST(CppCore::Test::BitOps::lzcnt8,              "lzcnt8:           ", std::endl);
   TEST(CppCore::Test::BitOps::lzcnt16,             "lzcnt16:          ", std::endl);
   TEST(CppCore::Test::BitOps::lzcnt32,             "lzcnt32:          ", std::endl);
   TEST(CppCore::Test::BitOps::lzcnt64,             "lzcnt64:          ", std::endl);
   TEST(CppCore::Test::BitOps::lzcnt,               "lzcnt:            ", std::endl);
   TEST(CppCore::Test::BitOps::bittest32,           "bittest32:        ", std::endl);
   TEST(CppCore::Test::BitOps::bittest64,           "bittest64:        ", std::endl);
   TEST(CppCore::Test::BitOps::bittest,             "bittest:          ", std::endl);
   TEST(CppCore::Test::BitOps::bitextract32,        "bitextract32:     ", std::endl);
   TEST(CppCore::Test::BitOps::bitextract64,        "bitextract64:     ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap<1>,         "byteswap8:        ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap16,          "byteswap16:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap<3>,         "byteswap24:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap32,          "byteswap32:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap<5>,         "byteswap40:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap<6>,         "byteswap48:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap<7>,         "byteswap56:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap64,          "byteswap64:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap<16>,        "byteswap128:      ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap<32>,        "byteswap256:      ", std::endl);
   TEST(CppCore::Test::BitOps::byteswap<64>,        "byteswap512:      ", std::endl);
   TEST(CppCore::Test::BitOps::bytedup16,           "bytedup16:        ", std::endl);
   TEST(CppCore::Test::BitOps::bytedup32,           "bytedup32:        ", std::endl);
   TEST(CppCore::Test::BitOps::bytedup64,           "bytedup64:        ", std::endl);
   TEST(CppCore::Test::BitOps::loadr16,             "loadr16:          ", std::endl);
   TEST(CppCore::Test::BitOps::loadr32,             "loadr32:          ", std::endl);
   TEST(CppCore::Test::BitOps::loadr64,             "loadr64:          ", std::endl);
   TEST(CppCore::Test::BitOps::storer16,            "storer16:         ", std::endl);
   TEST(CppCore::Test::BitOps::storer32,            "storer32:         ", std::endl);
   TEST(CppCore::Test::BitOps::storer64,            "storer64:         ", std::endl);
   TEST(CppCore::Test::BitOps::bitswap8,            "bitswap8:         ", std::endl);
   TEST(CppCore::Test::BitOps::bitswap16,           "bitswap16:        ", std::endl);
   TEST(CppCore::Test::BitOps::bitswap32,           "bitswap32:        ", std::endl);
   TEST(CppCore::Test::BitOps::bitswap64,           "bitswap64:        ", std::endl);
   TEST(CppCore::Test::BitOps::bitswap128,          "bitswap128:       ", std::endl);
   TEST(CppCore::Test::BitOps::bitswap256,          "bitswap256:       ", std::endl);
   TEST(CppCore::Test::BitOps::zbyteidxl32,         "zbyteidxl32:      ", std::endl);
   TEST(CppCore::Test::BitOps::zbyteidxl64,         "zbyteidxl64:      ", std::endl);
   TEST(CppCore::Test::BitOps::zbyteidxl128,        "zbyteidxl128:     ", std::endl);
   TEST(CppCore::Test::BitOps::zbyteidxl256,        "zbyteidxl256:     ", std::endl);
   TEST(CppCore::Test::BitOps::zbyteidxl512,        "zbyteidxl512:     ", std::endl);
   TEST(CppCore::Test::BitOps::zbyteidxr32,         "zbyteidxr32:      ", std::endl);
   TEST(CppCore::Test::BitOps::zbyteidxr64,         "zbyteidxr64:      ", std::endl);
   TEST(CppCore::Test::BitOps::zbyteidxr128,        "zbyteidxr128:     ", std::endl);
   TEST(CppCore::Test::BitOps::zbyteidxr256,        "zbyteidxr256:     ", std::endl);
   TEST(CppCore::Test::BitOps::zbyteidxr512,        "zbyteidxr512:     ", std::endl);
   TEST(CppCore::Test::BitOps::byteidxl32,          "byteidxl32:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteidxl64,          "byteidxl64:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteidxl128,         "byteidxl128:      ", std::endl);
   TEST(CppCore::Test::BitOps::byteidxl256,         "byteidxl256:      ", std::endl);
   TEST(CppCore::Test::BitOps::byteidxl512,         "byteidxl512:      ", std::endl);
   TEST(CppCore::Test::BitOps::byteidxr32,          "byteidxr32:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteidxr64,          "byteidxr64:       ", std::endl);
   TEST(CppCore::Test::BitOps::byteidxr128,         "byteidxr128:      ", std::endl);
   TEST(CppCore::Test::BitOps::byteidxr256,         "byteidxr256:      ", std::endl);
   TEST(CppCore::Test::BitOps::byteidxr512,         "byteidxr512:      ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "CppCore::Math::Util"             << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Math::Util::getbits32,       "getbits32:        ", std::endl);
   TEST(CppCore::Test::Math::Util::getbits64,       "getbits64:        ", std::endl);
   TEST(CppCore::Test::Math::Util::unsetbits32,     "unsetbits32:      ", std::endl);
   TEST(CppCore::Test::Math::Util::unsetbits64,     "unsetbits64:      ", std::endl);
   TEST(CppCore::Test::Math::Util::setbit32,        "setbit32:         ", std::endl);
   TEST(CppCore::Test::Math::Util::setbit64,        "setbit64:         ", std::endl);
   TEST(CppCore::Test::Math::Util::setbits32,       "setbits32:        ", std::endl);
   TEST(CppCore::Test::Math::Util::setbits64,       "setbits64:        ", std::endl);
   TEST(CppCore::Test::Math::Util::rdownptwo32,     "rdownptwo32:      ", std::endl);
   TEST(CppCore::Test::Math::Util::rdownptwo64,     "rdownptwo64:      ", std::endl);
   TEST(CppCore::Test::Math::Util::rupptwo32,       "rupptwo32:        ", std::endl);
   TEST(CppCore::Test::Math::Util::rupptwo64,       "rupptwo64:        ", std::endl);
   TEST(CppCore::Test::Math::Util::rdown32,         "rdown32:          ", std::endl);
   TEST(CppCore::Test::Math::Util::rdown64,         "rdown64:          ", std::endl);
   TEST(CppCore::Test::Math::Util::rup32,           "rup32:            ", std::endl);
   TEST(CppCore::Test::Math::Util::rup64,           "rup64:            ", std::endl);
   TEST(CppCore::Test::Math::Util::round32,         "round32:          ", std::endl);
   TEST(CppCore::Test::Math::Util::round64,         "round64:          ", std::endl);
   TEST(CppCore::Test::Math::Util::ngptwo32,        "ngptwo32:         ", std::endl);
   TEST(CppCore::Test::Math::Util::ngptwo64,        "ngptwo64:         ", std::endl);
   TEST(CppCore::Test::Math::Util::nlptwo32,        "nlptwo32:         ", std::endl);
   TEST(CppCore::Test::Math::Util::nlptwo64,        "nlptwo64:         ", std::endl);
   TEST(CppCore::Test::Math::Util::addcarry8,       "addcarry8:        ", std::endl);
   TEST(CppCore::Test::Math::Util::addcarry16,      "addcarry16:       ", std::endl);
   TEST(CppCore::Test::Math::Util::addcarry32,      "addcarry32:       ", std::endl);
   TEST(CppCore::Test::Math::Util::addcarry64,      "addcarry64:       ", std::endl);
   TEST(CppCore::Test::Math::Util::subborrow8,      "subborrow8:       ", std::endl);
   TEST(CppCore::Test::Math::Util::subborrow16,     "subborrow16:      ", std::endl);
   TEST(CppCore::Test::Math::Util::subborrow32,     "subborrow32:      ", std::endl);
   TEST(CppCore::Test::Math::Util::subborrow64,     "subborrow64:      ", std::endl);
   TEST(CppCore::Test::Math::Util::mul128,          "mul128:           ", std::endl);
   TEST(CppCore::Test::Math::Util::overflowadd16,   "overflowadd16:    ", std::endl);
   TEST(CppCore::Test::Math::Util::overflowadd32,   "overflowadd32:    ", std::endl);
   TEST(CppCore::Test::Math::Util::overflowadd64,   "overflowadd64:    ", std::endl);
   TEST(CppCore::Test::Math::Util::overflowsub16,   "overflowsub16:    ", std::endl);
   TEST(CppCore::Test::Math::Util::overflowsub32,   "overflowsub32:    ", std::endl);
   TEST(CppCore::Test::Math::Util::overflowsub64,   "overflowsub64:    ", std::endl);
   TEST(CppCore::Test::Math::Util::overflowmul16,   "overflowmul16:    ", std::endl);
   TEST(CppCore::Test::Math::Util::overflowmul32,   "overflowmul32:    ", std::endl);
   TEST(CppCore::Test::Math::Util::overflowmul64,   "overflowmul64:    ", std::endl);
   TEST(CppCore::Test::Math::Util::umod,            "umod:             ", std::endl);
   TEST(CppCore::Test::Math::Util::umulmod32,       "umulmod32:        ", std::endl);
   TEST(CppCore::Test::Math::Util::umulmod64,       "umulmod64:        ", std::endl);
   TEST(CppCore::Test::Math::Util::upowmod32,       "upowmod32:        ", std::endl);
   TEST(CppCore::Test::Math::Util::upowmod64,       "upowmod64:        ", std::endl);
   TEST(CppCore::Test::Math::Util::upow32,          "upow32:           ", std::endl);
   TEST(CppCore::Test::Math::Util::upow64,          "upow64:           ", std::endl);
   TEST(CppCore::Test::Math::Util::udivmod32,       "udivmod32:        ", std::endl);
   TEST(CppCore::Test::Math::Util::udivmod64,       "udivmod64:        ", std::endl);
   TEST(CppCore::Test::Math::Util::udivmod64_32,    "udivmod64_32:     ", std::endl);
   TEST(CppCore::Test::Math::Util::udivmod128_64,   "udivmod128_64:    ", std::endl);
   TEST(CppCore::Test::Math::Util::udivmod128_128,  "udivmod128_128:   ", std::endl);
   TEST(CppCore::Test::Math::Util::udivmod16x,      "udivmod16x:       ", std::endl);
   TEST(CppCore::Test::Math::Util::udivmod32x,      "udivmod32x:       ", std::endl);
   TEST(CppCore::Test::Math::Util::ismersenne32,    "ismersenne32:     ", std::endl);
   TEST(CppCore::Test::Math::Util::ismersenne64,    "ismersenne64:     ", std::endl);
   TEST(CppCore::Test::Math::Util::ismersenne128,   "ismersenne128:    ", std::endl);
   TEST(CppCore::Test::Math::Util::clmul32,         "clmul32:          ", std::endl);
   TEST(CppCore::Test::Math::Util::clmul32to64,     "clmul32to64:      ", std::endl);
   TEST(CppCore::Test::Math::Util::clmul64,         "clmul64:          ", std::endl);
   TEST(CppCore::Test::Math::Util::clmul64to128,    "clmul64to128:     ", std::endl);
   TEST(CppCore::Test::Math::Util::clmul128,        "clmul128:         ", std::endl);
   TEST(CppCore::Test::Math::Util::clmul128to256,   "clmul128to256:    ", std::endl);
   TEST(CppCore::Test::Math::Util::todouble,        "todouble:         ", std::endl);
   TEST(CppCore::Test::Math::Util::gcd32,           "gcd32:            ", std::endl);
   TEST(CppCore::Test::Math::Util::gcd64,           "gcd64:            ", std::endl);
   TEST(CppCore::Test::Math::Util::gcd,             "gcd:              ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "CppCore::Memory"                 << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Memory::equal32,                "equal32:                ", std::endl);
   TEST(CppCore::Test::Memory::equal64,                "equal64:                ", std::endl);
   TEST(CppCore::Test::Memory::equal128,               "equal128:               ", std::endl);
   TEST(CppCore::Test::Memory::equal256,               "equal256:               ", std::endl);
   TEST(CppCore::Test::Memory::equal512,               "equal512:               ", std::endl);
   TEST(CppCore::Test::Memory::equal,                  "equal:                  ", std::endl);
   TEST(CppCore::Test::Memory::testzero128,            "testzero128:            ", std::endl);
   TEST(CppCore::Test::Memory::testzero256,            "testzero256:            ", std::endl);
   TEST(CppCore::Test::Memory::streamset128x4,         "streamset128x4:         ", std::endl);
   TEST(CppCore::Test::Memory::streamset256x4,         "streamset256x4:         ", std::endl);
   TEST(CppCore::Test::Memory::streamset512x4,         "streamset512x4:         ", std::endl);
   TEST(CppCore::Test::Memory::singlecopy128,          "singlecopy128:          ", std::endl);
   TEST(CppCore::Test::Memory::singlecopy256,          "singlecopy256:          ", std::endl);
   TEST(CppCore::Test::Memory::singlecopy512,          "singlecopy512:          ", std::endl);
   TEST(CppCore::Test::Memory::singlecopy1024,         "singlecopy1024:         ", std::endl);
   TEST(CppCore::Test::Memory::singlecopy2048,         "singlecopy2048:         ", std::endl);
   TEST(CppCore::Test::Memory::copy32,                 "copy32:                 ", std::endl);
   TEST(CppCore::Test::Memory::copy64,                 "copy64:                 ", std::endl);
   TEST(CppCore::Test::Memory::copy128,                "copy128:                ", std::endl);
   TEST(CppCore::Test::Memory::copy256,                "copy256:                ", std::endl);
   TEST(CppCore::Test::Memory::copy512,                "copy512:                ", std::endl);
   TEST(CppCore::Test::Memory::copy,                   "copy:                   ", std::endl);
   TEST(CppCore::Test::Memory::copybackwards,          "copybackwards:          ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy128,          "streamcopy128:          ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy128x1,        "streamcopy128x1:        ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy128x2,        "streamcopy128x2:        ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy128x4,        "streamcopy128x4:        ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy256,          "streamcopy256:          ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy256x1,        "streamcopy256x1:        ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy256x2,        "streamcopy256x2:        ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy256x4,        "streamcopy256x4:        ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy512,          "streamcopy512:          ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy512x1,        "streamcopy512x1:        ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy512x2,        "streamcopy512x2:        ", std::endl);
   TEST(CppCore::Test::Memory::streamcopy512x4,        "streamcopy512x4:        ", std::endl);
   TEST(CppCore::Test::Memory::copyreverse8,           "copyreverse8:           ", std::endl);
   TEST(CppCore::Test::Memory::copyreverse16,          "copyreverse16:          ", std::endl);
   TEST(CppCore::Test::Memory::copyreverse32,          "copyreverse32:          ", std::endl);
   TEST(CppCore::Test::Memory::copyreverse64,          "copyreverse64:          ", std::endl);
   TEST(CppCore::Test::Memory::copyreverse128,         "copyreverse128:         ", std::endl);
   TEST(CppCore::Test::Memory::copyreverse,            "copyreverse:            ", std::endl);
   TEST(CppCore::Test::Memory::streamcopyreverse128,   "streamcopyreverse128:   ", std::endl);
   TEST(CppCore::Test::Memory::streamcopyreverse128x1, "streamcopyreverse128x1: ", std::endl);
   TEST(CppCore::Test::Memory::streamcopyreverse128x2, "streamcopyreverse128x2: ", std::endl);
   TEST(CppCore::Test::Memory::streamcopyreverse128x4, "streamcopyreverse128x4: ", std::endl);
   TEST(CppCore::Test::Memory::swap8,                  "swap8:                  ", std::endl);
   TEST(CppCore::Test::Memory::swap16,                 "swap16:                 ", std::endl);
   TEST(CppCore::Test::Memory::swap32,                 "swap32:                 ", std::endl);
   TEST(CppCore::Test::Memory::swap64,                 "swap64:                 ", std::endl);
   TEST(CppCore::Test::Memory::swap128,                "swap128:                ", std::endl);
   TEST(CppCore::Test::Memory::swap256,                "swap256:                ", std::endl);
   TEST(CppCore::Test::Memory::swap512,                "swap512:                ", std::endl);
   TEST(CppCore::Test::Memory::swap,                   "swap:                   ", std::endl);
   TEST(CppCore::Test::Memory::streamswap128,          "streamswap128:          ", std::endl);
   TEST(CppCore::Test::Memory::streamswap128x1,        "streamswap128x1:        ", std::endl);
   TEST(CppCore::Test::Memory::streamswap128x2,        "streamswap128x2:        ", std::endl);
   TEST(CppCore::Test::Memory::streamswap128x4,        "streamswap128x4:        ", std::endl);
   TEST(CppCore::Test::Memory::streamswap256,          "streamswap256:          ", std::endl);
   TEST(CppCore::Test::Memory::streamswap512,          "streamswap512:          ", std::endl);
   TEST(CppCore::Test::Memory::reverse8,               "reverse8:               ", std::endl);
   TEST(CppCore::Test::Memory::reverse16,              "reverse16:              ", std::endl);
   TEST(CppCore::Test::Memory::reverse32,              "reverse32:              ", std::endl);
   TEST(CppCore::Test::Memory::reverse64,              "reverse64:              ", std::endl);
   TEST(CppCore::Test::Memory::reverse128,             "reverse128:             ", std::endl);
   TEST(CppCore::Test::Memory::reverse,                "reverse:                ", std::endl);
   TEST(CppCore::Test::Memory::clear,                  "clear:                  ", std::endl);
   TEST(CppCore::Test::Memory::zbyteidxf32,            "zbyteidxf32:            ", std::endl);
   TEST(CppCore::Test::Memory::zbyteidxf64,            "zbyteidxf64:            ", std::endl);
   TEST(CppCore::Test::Memory::zbyteidxf128,           "zbyteidxf128:           ", std::endl);
   TEST(CppCore::Test::Memory::zbyteidxf256,           "zbyteidxf256:           ", std::endl);
   TEST(CppCore::Test::Memory::zbyteidxf512,           "zbyteidxf512:           ", std::endl);
   TEST(CppCore::Test::Memory::zbyteidxf,              "zbyteidxf:              ", std::endl);
   TEST(CppCore::Test::Memory::byteidxf32,             "byteidxf32:             ", std::endl);
   TEST(CppCore::Test::Memory::byteidxf64,             "byteidxf64:             ", std::endl);
   TEST(CppCore::Test::Memory::byteidxf128,            "byteidxf128:            ", std::endl);
   TEST(CppCore::Test::Memory::byteidxf256,            "byteidxf256:            ", std::endl);
   TEST(CppCore::Test::Memory::byteidxf512,            "byteidxf512:            ", std::endl);
   TEST(CppCore::Test::Memory::byteidxf,               "byteidxf:               ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "     CppCore::Math::BigInt"      << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Math::BigInt::eq128,           "eq128:           ", std::endl);
   TEST(CppCore::Test::Math::BigInt::popcnt128,       "popcnt128:       ", std::endl);
   TEST(CppCore::Test::Math::BigInt::tzcnt128,        "tzcnt128:        ", std::endl);
   TEST(CppCore::Test::Math::BigInt::lzcnt128,        "lzcnt128:        ", std::endl);
   TEST(CppCore::Test::Math::BigInt::getbit128,       "getbit128:       ", std::endl);
   TEST(CppCore::Test::Math::BigInt::setbit128,       "setbit128:       ", std::endl);
   TEST(CppCore::Test::Math::BigInt::byteswap128,     "byteswap128:     ", std::endl);
   TEST(CppCore::Test::Math::BigInt::shl128,          "shl128:          ", std::endl);
   TEST(CppCore::Test::Math::BigInt::shr128,          "shr128:          ", std::endl);
   TEST(CppCore::Test::Math::BigInt::rotl128,         "rotl128:         ", std::endl);
   TEST(CppCore::Test::Math::BigInt::rotr128,         "rotr128:         ", std::endl);
   TEST(CppCore::Test::Math::BigInt::mul128,          "mul128:          ", std::endl);
   TEST(CppCore::Test::Math::BigInt::mulw128,         "mulw128:         ", std::endl);
   TEST(CppCore::Test::Math::BigInt::divmod128,       "divmod128:       ", std::endl);
   TEST(CppCore::Test::Math::BigInt::tostring128,     "tostring128:     ", std::endl);
   TEST(CppCore::Test::Math::BigInt::tohexstring128,  "tohexstring128:  ", std::endl);
   TEST(CppCore::Test::Math::BigInt::tryparse128,     "tryparse128:     ", std::endl);
   TEST(CppCore::Test::Math::BigInt::parsedecimal128, "parsedecimal128: ", std::endl);
   TEST(CppCore::Test::Math::BigInt::parsehex128,     "parsehex128:     ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "CppCore::Math::Primes"           << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Math::Primes::isprime_trivial<uint32_t>,  "isprime_trivial32:       ", std::endl);
   TEST(CppCore::Test::Math::Primes::isprime_trivial<uint64_t>,  "isprime_trivial64:       ", std::endl);
   TEST(CppCore::Test::Math::Primes::isprime_trial<uint32_t>,    "isprime_trial32:         ", std::endl);
   TEST(CppCore::Test::Math::Primes::isprime_trial<uint64_t>,    "isprime_trial64:         ", std::endl);
   TEST(CppCore::Test::Math::Primes::isprime32,                  "isprime32:               ", std::endl);
   TEST(CppCore::Test::Math::Primes::isprime64,                  "isprime64:               ", std::endl);
   TEST(CppCore::Test::Math::Primes::isprime128,                 "isprime128:              ", std::endl);
   TEST(CppCore::Test::Math::Primes::ismersenneprime32,          "ismersenneprime32:       ", std::endl);
   TEST(CppCore::Test::Math::Primes::ismersenneprime64,          "ismersenneprime64:       ", std::endl);
   TEST(CppCore::Test::Math::Primes::ismersenneprime128,         "ismersenneprime128:      ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "         CppCore::Random       " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Random::next32<CppCore::Random::Xorshift32>, "Xorshift32_next: ", std::endl);
   TEST(CppCore::Test::Random::fill32<CppCore::Random::Xorshift32>, "Xorshift32_fill: ", std::endl);
   TEST(CppCore::Test::Random::next64<CppCore::Random::Xorshift64>, "Xorshift64_next: ", std::endl);
   TEST(CppCore::Test::Random::fill64<CppCore::Random::Xorshift64>, "Xorshift64_fill: ", std::endl);
   TEST(CppCore::Test::Random::next32<CppCore::Random::Xoshiro32>,  "Xoshiro32_next:  ", std::endl);
   TEST(CppCore::Test::Random::fill32<CppCore::Random::Xoshiro32>,  "Xoshiro32_fill:  ", std::endl);
   TEST(CppCore::Test::Random::next64<CppCore::Random::Xoshiro64>,  "Xoshiro64_next:  ", std::endl);
   TEST(CppCore::Test::Random::fill64<CppCore::Random::Xoshiro64>,  "Xoshiro64_fill:  ", std::endl);
   TEST(CppCore::Test::Random::next32<CppCore::Random::Mulberry32>, "Mulberry32_next: ", std::endl);
   TEST(CppCore::Test::Random::fill32<CppCore::Random::Mulberry32>, "Mulberry32_fill: ", std::endl);
   TEST(CppCore::Test::Random::next64<CppCore::Random::Splitmix64>, "Splitmix64_next: ", std::endl);
   TEST(CppCore::Test::Random::fill64<CppCore::Random::Splitmix64>, "Splitmix64_fill: ", std::endl);
#if defined(CPPCORE_CPUFEAT_RDRAND) && defined(CPPCORE_CPUFEAT_SSE2)
   TEST(CppCore::Test::Random::next32<CppCore::Random::Cpu32>,      "Cpu32_next:      ", std::endl);
   TEST(CppCore::Test::Random::fill32<CppCore::Random::Cpu32>,      "Cpu32_fill:      ", std::endl);
   TEST(CppCore::Test::Random::next64<CppCore::Random::Cpu64>,      "Cpu64_next:      ", std::endl);
   TEST(CppCore::Test::Random::fill64<CppCore::Random::Cpu64>,      "Cpu64_fill:      ", std::endl);
#endif
#if defined(CPPCORE_CPUFEAT_SSE2)
   TEST((CppCore::Test::Random::next32x4<CppCore::Random::Xorshift32x4, CppCore::Random::Xorshift32>), "Xorshift32x4_next:      ", std::endl);
   TEST((CppCore::Test::Random::fill32x4<CppCore::Random::Xorshift32x4>),                              "Xorshift32x4_fill:      ", std::endl);
#endif
#if defined(CPPCORE_CPUFEAT_SSE41)
   TEST((CppCore::Test::Random::next32x4<CppCore::Random::Mulberry32x4, CppCore::Random::Mulberry32>), "Mulberry32x4_next:      ", std::endl);
   TEST((CppCore::Test::Random::fill32x4<CppCore::Random::Mulberry32x4>),                              "Mulberry32x4_fill:      ", std::endl);
#endif

   std::cout << "-------------------------------" << std::endl;
   std::cout << "      CppCore::Hash::CRC32"      << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Hash::CRC32::crc32test1<CppCore::CRC32g>, "crc32gtest1: ", std::endl);
   TEST(CppCore::Test::Hash::CRC32::crc32test2<CppCore::CRC32g>, "crc32gtest2: ", std::endl);
   TEST(CppCore::Test::Hash::CRC32::crc32test3<CppCore::CRC32g>, "crc32gtest3: ", std::endl);
#if defined(CPPCORE_CPUFEAT_ARM_CRC32)
   TEST(CppCore::Test::Hash::CRC32::crc32test1<CppCore::CRC32s>, "crc32stest1: ", std::endl);
   TEST(CppCore::Test::Hash::CRC32::crc32test2<CppCore::CRC32s>, "crc32stest2: ", std::endl);
   TEST(CppCore::Test::Hash::CRC32::crc32test3<CppCore::CRC32s>, "crc32stest3: ", std::endl);
#endif
   TEST(CppCore::Test::Hash::CRC32::crc32ctest1<CppCore::CRC32Cg>, "crc32cgtest1: ", std::endl);
   TEST(CppCore::Test::Hash::CRC32::crc32ctest2<CppCore::CRC32Cg>, "crc32cgtest2: ", std::endl);
   TEST(CppCore::Test::Hash::CRC32::crc32ctest3<CppCore::CRC32Cg>, "crc32cgtest3: ", std::endl);
#if defined(CPPCORE_CPUFEAT_SSE42) || defined(CPPCORE_CPUFEAT_ARM_CRC32)
   TEST(CppCore::Test::Hash::CRC32::crc32ctest1<CppCore::CRC32Cs>, "crc32cstest1: ", std::endl);
   TEST(CppCore::Test::Hash::CRC32::crc32ctest2<CppCore::CRC32Cs>, "crc32cstest2: ", std::endl);
   TEST(CppCore::Test::Hash::CRC32::crc32ctest3<CppCore::CRC32Cs>, "crc32cstest3: ", std::endl);
#endif

   std::cout << "-------------------------------" << std::endl;
   std::cout << "       CppCore::Hash::MD5"       << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Hash::MD5::test1, "test1: ", " ");
   TEST(CppCore::Test::Hash::MD5::test2, "test2: ", std::endl);
   TEST(CppCore::Test::Hash::MD5::test3, "test3: ", " ");
   TEST(CppCore::Test::Hash::MD5::test4, "test4: ", std::endl);
   TEST(CppCore::Test::Hash::MD5::test5, "test5: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "       CppCore::Hash::SHA2"       << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Hash::SHA2::sha256<CppCore::SHA256g>, "sha256g: ", std::endl);
   TEST(CppCore::Test::Hash::SHA2::sha512<CppCore::SHA512g>, "sha512g: ", std::endl);
   TEST(CppCore::Test::Hash::SHA2::sha256<CppCore::SHA256s>, "sha256s: ", std::endl);
   TEST(CppCore::Test::Hash::SHA2::sha512<CppCore::SHA512s>, "sha512s: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "    CppCore::Hash::Murmur3"     << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Hash::Murmur3::test1, "test1: ", std::endl);
   TEST(CppCore::Test::Hash::Murmur3::test2, "test2: ", std::endl);
   TEST(CppCore::Test::Hash::Murmur3::test3, "test3: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "    CppCore::Crypto::DH"       << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Crypto::DH::test1<CppCore::DH128>,  "test1dh128:    ", std::endl);
   TEST(CppCore::Test::Crypto::DH::test1<CppCore::DH256>,  "test1dh256:    ", std::endl);
   TEST(CppCore::Test::Crypto::DH::test1<CppCore::DH512>,  "test1dh512:    ", std::endl);
   TEST(CppCore::Test::Crypto::DH::test1<CppCore::DH1024>, "test1dh1024:   ", std::endl);
   TEST(CppCore::Test::Crypto::DH::test1<CppCore::DH2048>, "test1dh2048:   ", std::endl);
   //TEST(CppCore::Test::Crypto::DH::test1<CppCore::DH4096>, "test1dh4096:   ", std::endl);
   TEST(CppCore::Test::Crypto::DH::test2<CppCore::DH128>,  "test2dh128:    ", std::endl);
   TEST(CppCore::Test::Crypto::DH::test2<CppCore::DH256>,  "test2dh256:    ", std::endl);
   TEST(CppCore::Test::Crypto::DH::test2<CppCore::DH512>,  "test2dh512:    ", std::endl);
   TEST(CppCore::Test::Crypto::DH::test2<CppCore::DH1024>, "test2dh1024:   ", std::endl);
   TEST(CppCore::Test::Crypto::DH::test2<CppCore::DH2048>, "test2dh2048:   ", std::endl);
   //TEST(CppCore::Test::Crypto::DH::test2<CppCore::DH4096>, "test2dh4096:   ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "    CppCore::Crypto::HMAC"       << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Crypto::HMAC::md5test1,    "md5test1:    ", std::endl);
   TEST(CppCore::Test::Crypto::HMAC::sha256test1, "sha256test1: ", std::endl);
   TEST(CppCore::Test::Crypto::HMAC::sha512test1, "sha512test1: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "    CppCore::Crypto::PBKDF2"       << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Crypto::PBKDF2::md5test1,    "md5test1:    ", std::endl);
   TEST(CppCore::Test::Crypto::PBKDF2::sha256test1, "sha256test1: ", std::endl);
   TEST(CppCore::Test::Crypto::PBKDF2::sha512test1, "sha512test1: ", std::endl);
   TEST(CppCore::Test::Crypto::PBKDF2::sha512test2, "sha512test2: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "    CppCore::Crypto::AES128g   " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Crypto::AES::ecb128<CppCore::AES128g>, "ecb128g: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::cbc128<CppCore::AES128g>, "cbc128g: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::ctr128<CppCore::AES128g>, "ctr128g: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "    CppCore::Crypto::AES192g   " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Crypto::AES::ecb192<CppCore::AES192g>, "ecb192g: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::cbc192<CppCore::AES192g>, "cbc192g: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::ctr192<CppCore::AES192g>, "ctr192g: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "    CppCore::Crypto::AES256g   " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Crypto::AES::ecb256<CppCore::AES256g>, "ecb256g: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::cbc256<CppCore::AES256g>, "cbc256g: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::ctr256<CppCore::AES256g>, "ctr256g: ", std::endl);

#if defined(CPPCORE_CPUFEAT_AES) && defined(CPPCORE_CPUFEAT_SSE41)
   std::cout << "-------------------------------" << std::endl;
   std::cout << "    CppCore::Crypto::AES128s   " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Crypto::AES::ecb128<CppCore::AES128s>, "ecb128s: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::cbc128<CppCore::AES128s>, "cbc128s: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::ctr128<CppCore::AES128s>, "ctr128s: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "    CppCore::Crypto::AES192s   " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Crypto::AES::ecb192<CppCore::AES192s>, "ecb192s: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::cbc192<CppCore::AES192s>, "cbc192s: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::ctr192<CppCore::AES192s>, "ctr192s: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "    CppCore::Crypto::AES256s   " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Crypto::AES::ecb256<CppCore::AES256s>, "ecb256s: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::cbc256<CppCore::AES256s>, "cbc256s: ", std::endl);
   TEST(CppCore::Test::Crypto::AES::ctr256<CppCore::AES256s>, "ctr256s: ", std::endl);
#endif

   std::cout << "-------------------------------" << std::endl;
   std::cout << "  CppCore::Containers::Array"    << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Containers::Array::modelid<false>,       "modelid:         ", std::endl);
   TEST(CppCore::Test::Containers::Array::modelid<true>,        "modelid_b:       ", std::endl);
   TEST(CppCore::Test::Containers::Array::modelname<false>,     "modelname:       ", std::endl);
   TEST(CppCore::Test::Containers::Array::modelname<true>,      "modelname_b:     ", std::endl);
   TEST(CppCore::Test::Containers::Array::integerbulk,          "integerbulk:     ", std::endl);
   TEST(CppCore::Test::Containers::Array::integerresize,        "integerresize:   ", std::endl);
   TEST(CppCore::Test::Containers::Array::iterator,             "iterator:        ", std::endl);
#ifndef CPPCORE_NO_THREADING
   TEST(CppCore::Test::Containers::Array::multithreaded<false>, "multithreaded:   ", std::endl);
   TEST(CppCore::Test::Containers::Array::multithreaded<true>,  "multithreaded_b: ", std::endl);
#endif

   std::cout << "-------------------------------" << std::endl;
   std::cout << "  CppCore::Containers::Queue"    << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Containers::Queue::fillmaxthenempty1, "fillmaxthenempty1: ", std::endl);
   TEST(CppCore::Test::Containers::Queue::fillmaxthenempty2, "fillmaxthenempty2: ", std::endl);
   TEST(CppCore::Test::Containers::Queue::fillmaxthenempty3, "fillmaxthenempty3: ", std::endl);
   TEST(CppCore::Test::Containers::Queue::fillmaxthenempty4, "fillmaxthenempty4: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "CppCore::Containers::HashTable"  << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Containers::HashTable::modelid,   "modelid:   ", std::endl);
   TEST(CppCore::Test::Containers::HashTable::modelname, "modelname: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "          CppCore::Uuid"         << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Uuid::sizeOf,       "sizeof:       ", std::endl);
   TEST(CppCore::Test::Uuid::constructor,  "constructor:  ", std::endl);
   TEST(CppCore::Test::Uuid::isuuidstring, "isuuidstring: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "      CppCore::Encoding"         << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Encoding::isdigit,  "isdigit:  ",  std::endl);
   TEST(CppCore::Test::Encoding::isxdigit, "isxdigit: ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "   CppCore::Encoding::BaseX    " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Encoding::BaseX::estimatebits,    "estimatebits:    ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::estimatesymbols, "estimatesymbols: ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::tostring8,       "tostring8:       ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::tostring16,      "tostring16:      ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::tostring32,      "tostring32:      ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::tostring64,      "tostring64:      ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::parse8,          "parse8:          ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::parse16,         "parse16:         ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::parse32,         "parse32:         ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::parse64,         "parse64:         ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::parse128,        "parse128:        ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::tryparse8,       "tryparse8:       ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::tryparse16,      "tryparse16:      ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::tryparse32,      "tryparse32:      ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::tryparse64,      "tryparse64:      ", std::endl);
   TEST(CppCore::Test::Encoding::BaseX::tryparse128,     "tryparse128:     ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "   CppCore::Encoding::Decimal  " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Encoding::Decimal::tostring8u,  "tostring8u:  ",  std::endl);
   TEST(CppCore::Test::Encoding::Decimal::tostring8s,  "tostring8s:  ",  std::endl);
   TEST(CppCore::Test::Encoding::Decimal::tostring16u, "tostring16u: ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::tostring16s, "tostring16s: ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::tostring32u, "tostring32u: ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::tostring32s, "tostring32s: ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::tostring64u, "tostring64u: ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::tostring64s, "tostring64s: ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::parse8u,     "parse8u:     ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::parse8s,     "parse8s:     ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::parse16u,    "parse16u:    ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::parse16s,    "parse16s:    ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::parse32u,    "parse32u:    ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::parse32s,    "parse32s:    ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::parse64u,    "parse64u:    ", std::endl);
   TEST(CppCore::Test::Encoding::Decimal::parse64s,    "parse64s:    ", std::endl);

   std::cout << "-------------------------------" << std::endl;
   std::cout << "   CppCore::Encoding::Hex      " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Encoding::Hex::encode,             "encode:     ", std::endl);
   TEST(CppCore::Test::Encoding::Hex::decode,             "decode:     ", std::endl);
   TEST(CppCore::Test::Encoding::Hex::tostring16,         "tostring16: ", std::endl);
   TEST(CppCore::Test::Encoding::Hex::tostring32,         "tostring32: ", std::endl);
   TEST(CppCore::Test::Encoding::Hex::tostring64,         "tostring64: ", std::endl);
   TEST(CppCore::Test::Encoding::Hex::parse16,            "parse16:    ", std::endl);
   TEST(CppCore::Test::Encoding::Hex::parse32,            "parse32:    ", std::endl);
   TEST(CppCore::Test::Encoding::Hex::parse64,            "parse64:    ", std::endl);

#ifndef CPPCORE_NO_SOCKET
   std::cout << "-------------------------------" << std::endl;
   std::cout << "        CppCore::Socket"         << std::endl;
   std::cout << "-------------------------------" << std::endl;
   TEST(CppCore::Test::Network::Socket::createcloseipv4tcp,   "createcloseipv4tcp:   ", std::endl);
   TEST(CppCore::Test::Network::Socket::createcloseipv6tcp,   "createcloseipv6tcp:   ", std::endl);
   TEST(CppCore::Test::Network::Socket::createcloseipv6dstcp, "createcloseipv6dstcp: ", std::endl);
   TEST(CppCore::Test::Network::Socket::createcloseipv4udp,   "createcloseipv4udp:   ", std::endl);
   TEST(CppCore::Test::Network::Socket::createcloseipv6udp,   "createcloseipv6udp:   ", std::endl);
   TEST(CppCore::Test::Network::Socket::createcloseipv6dsudp, "createcloseipv6dsudp: ", std::endl);
   TEST(CppCore::Test::Network::Socket::bindlistenipv4tcp,    "bindlistenipv4tcp:    ", std::endl);
   TEST(CppCore::Test::Network::Socket::bindlistenipv6tcp,    "bindlistenipv6tcp:    ", std::endl);
   TEST(CppCore::Test::Network::Socket::bindlistenipv6dstcp,  "bindlistenipv6dstcp:  ", std::endl);
   TEST(CppCore::Test::Network::Socket::setoptsipv4tcp,       "setoptsipv4tcp:       ", std::endl);
   TEST(CppCore::Test::Network::Socket::setoptsipv6tcp,       "setoptsipv6tcp:       ", std::endl);
#endif

   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V2fg                 " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v2f_test<V2fg, float, V2dg, double, V2ig, int32_t, V2lg, int64_t>() == 1) return 1;
   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V2fs                 " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v2f_test<V2fs, float, V2ds, double, V2is, int32_t, V2ls, int64_t>() == 1) return 1;
   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V2dg                 " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v2f_test<V2dg, double, V2fg, float, V2ig, int32_t, V2lg, int64_t>() == 1) return 1;
   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V2ds                 " << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v2f_test<V2ds, double, V2fs, float, V2is, int32_t, V2ls, int64_t>() == 1) return 1;
   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V2ig"                  << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v2i_test<V2ig, int32_t, V2lg, int64_t, V2fg, float, V2dg, double>() == 1) return 1;
   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V2is"                  << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v2i_test<V2is, int32_t, V2ls, int64_t, V2fs, float, V2ds, double>() == 1) return 1;
   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V2lg"                  << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v2i_test<V2lg, int64_t, V2ig, int32_t, V2fg, float, V2dg, double>() == 1) return 1;
   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V2ls"                  << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v2i_test<V2ls, int64_t, V2is, int32_t, V2fs, float, V2ds, double>() == 1) return 1;

   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V3fg"                  << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v3f_test<V3fg, float, V3dg, double, V3ig, int32_t, V3lg, int64_t>() == 1) return 1;
   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V3fs"                  << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v3f_test<V3fs, float, V3ds, double, V3is, int32_t, V3ls, int64_t>() == 1) return 1;
   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V3dg"                  << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v3f_test<V3dg, double, V3fg, float, V3ig, int32_t, V3lg, int64_t>() == 1) return 1;
   //std::cout << "-------------------------------" << std::endl;
   //std::cout << " CppCore::V3ds"                  << std::endl;
   //std::cout << "-------------------------------" << std::endl;
   //if (v3f_test<V3ds, double, V3fs, float, V3is, int32_t, V3ls, int64_t>() == 1) return 1;
   std::cout << "-------------------------------" << std::endl;
   std::cout << " CppCore::V3ig"                  << std::endl;
   std::cout << "-------------------------------" << std::endl;
   if (v3i_test<V3ig, int32_t, V3lg, int64_t, V3fg, float, V3dg, double>() == 1) return 1;
   //std::cout << "-------------------------------" << std::endl;
   //std::cout << " CppCore::V3is"                  << std::endl;
   //std::cout << "-------------------------------" << std::endl;
   //if (v3i_test<V3is, int32_t, V3ls, int64_t, V3fs, float, V3ds, double>() == 1) return 1;

   return 0;
}
