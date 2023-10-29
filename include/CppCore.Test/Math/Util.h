#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Math
{
   /// <summary>
   /// Tests for Util.h in CppCore::Math
   /// </summary>
   class Util
   {
   public:
      INLINE static bool getbits32()
      {
         const bool a = 
            CppCore::getbits32(0x00000000U, 0,  1 ) == 0U &&
            CppCore::getbits32(0x00000000U, 31, 1 ) == 0U &&
            CppCore::getbits32(0x00000001U, 0,  1 ) == 1U &&
            CppCore::getbits32(0x80000000U, 31, 1 ) == 1U &&
            CppCore::getbits32(0xFFFFFFFFU, 2,  2)  == 3U &&
            CppCore::getbits32(0xFFFFFFFFU, 16, 16) == 0xFFFFU;
         const bool b =
            CppCore::getbits32(0x00000000U, 0xFFFFFFFFU) == 0x00000000U &&
            CppCore::getbits32(0x00000011U, 0x000000FFU) == 0x00000011U &&
            CppCore::getbits32(0x0000FF00U, 0x000000FFU) == 0x00000000U &&
            CppCore::getbits32(0xFFFFFFFFU, 0xFFFFFFFFU) == 0xFFFFFFFFU;
         return a && b;
      }

      INLINE static bool getbits64()
      {
         const bool a = 
            CppCore::getbits64(0x0000000000000000ULL, 0,  1 ) == 0ULL &&
            CppCore::getbits64(0x0000000000000000ULL, 63, 1 ) == 0ULL &&
            CppCore::getbits64(0x0000000000000001ULL, 0,  1 ) == 1ULL &&
            CppCore::getbits64(0x8000000000000000ULL, 63, 1 ) == 1ULL &&
            CppCore::getbits64(0xFFFFFFFFFFFFFFFFULL, 2,  2)  == 3ULL &&
            CppCore::getbits64(0xFFFFFFFFFFFFFFFFULL, 32, 32) == 0xFFFFFFFFULL;
         const bool b = 
            CppCore::getbits64(0x0000000000000000ULL, 0xFFFFFFFFFFFFFFFFULL) == 0x0000000000000000ULL &&
            CppCore::getbits64(0x0000000000000011ULL, 0x00000000000000FFULL) == 0x0000000000000011ULL &&
            CppCore::getbits64(0x000000000000FF00ULL, 0x00000000000000FFULL) == 0x0000000000000000ULL &&
            CppCore::getbits64(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL) == 0xFFFFFFFFFFFFFFFFULL;
         return a && b;
      }

      INLINE static bool setbit32()
      {
         return
            CppCore::setbit32(0x00000000U, 0U,  true)  == 0x00000001U &&
            CppCore::setbit32(0x00000000U, 31U, true)  == 0x80000000U &&
            CppCore::setbit32(0x00000001U, 0U,  false) == 0x00000000U &&
            CppCore::setbit32(0x80000000U, 31U, false) == 0x00000000U &&
            CppCore::setbit32(0xFFFFFFFFU, 0U,  false) == 0xFFFFFFFEU &&
            CppCore::setbit32(0xFFFFFFFFU, 31U, false) == 0x7FFFFFFFU &&
            CppCore::setbit32(0xFFFFFFFFU, 30U, false) == 0xBFFFFFFFU;
      }

      INLINE static bool setbit64()
      {
         return
            CppCore::setbit64(0x0000000000000000ULL, 0U,  true)  == 0x0000000000000001ULL &&
            CppCore::setbit64(0x0000000000000000ULL, 63U, true)  == 0x8000000000000000ULL &&
            CppCore::setbit64(0x0000000000000001ULL, 0U,  false) == 0x0000000000000000ULL &&
            CppCore::setbit64(0x8000000000000000ULL, 63U, false) == 0x0000000000000000ULL &&
            CppCore::setbit64(0xFFFFFFFFFFFFFFFFULL, 0U,  false) == 0xFFFFFFFFFFFFFFFEULL &&
            CppCore::setbit64(0xFFFFFFFFFFFFFFFFULL, 63U, false) == 0x7FFFFFFFFFFFFFFFULL &&
            CppCore::setbit64(0xFFFFFFFFFFFFFFFFULL, 62U, false) == 0xBFFFFFFFFFFFFFFFULL;
      }

      INLINE static bool unsetbits32()
      {
         return
            CppCore::unsetbits32(0x00000000U, 0U,   0U) == 0x00000000U &&
            CppCore::unsetbits32(0x80000000U, 31U,  1U) == 0x00000000U &&
            CppCore::unsetbits32(0x00000001U, 0U,   1U) == 0x00000000U &&
            CppCore::unsetbits32(0xFFFFFFFFU, 24U,  8U) == 0x00FFFFFFU;
      }

      INLINE static bool unsetbits64()
      {
         return
            CppCore::unsetbits64(0x0000000000000000U, 0ULL,  0ULL) == 0x0000000000000000ULL &&
            CppCore::unsetbits64(0x8000000000000000U, 63ULL, 1ULL) == 0x0000000000000000ULL &&
            CppCore::unsetbits64(0x0000000000000001U, 0ULL,  1ULL) == 0x0000000000000000ULL &&
            CppCore::unsetbits64(0xFFFFFFFFFFFFFFFFU, 56ULL, 8ULL) == 0x00FFFFFFFFFFFFFFULL;
      }

      INLINE static bool setbits32()
      {
         return
            CppCore::setbits32(0x00000000U, 0x00000001U, 0x00000001U) == 0x00000001U &&
            CppCore::setbits32(0x00000000U, 0x00000001U, 0x80000000U) == 0x80000000U &&
            CppCore::setbits32(0x00FFFFFFU, 0x000000FFU, 0xFF000000U) == 0xFFFFFFFFU &&
            CppCore::setbits32(0xFFFFFFFFU, 0x00000000U, 0xFFFFFFFFU) == 0x00000000U;
      }

      INLINE static bool setbits64()
      {
         return
            CppCore::setbits64(0x0000000000000000ULL, 0x0000000000000001ULL, 0x0000000000000001ULL) == 0x0000000000000001ULL &&
            CppCore::setbits64(0x0000000000000000ULL, 0x0000000000000001ULL, 0x8000000000000000ULL) == 0x8000000000000000ULL &&
            CppCore::setbits64(0x00FFFFFFFFFFFFFFULL, 0x00000000000000FFULL, 0xFF00000000000000ULL) == 0xFFFFFFFFFFFFFFFFULL &&
            CppCore::setbits64(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 0xFFFFFFFFFFFFFFFFULL) == 0x0000000000000000ULL;
      }

      INLINE static bool rdownptwo32()
      {
         return
            CppCore::rdownptwo32(19U, 8U)  == 16U &&
            CppCore::rdownptwo32(8U, 8U)   == 8U  &&
            CppCore::rdownptwo32(1U, 8U)   == 0U  &&
            CppCore::rdownptwo32(1U, 2U)   == 0U  &&
            CppCore::rdownptwo32(1U, 1U)   == 1U  &&
            CppCore::rdownptwo32(65U, 64U) == 64U &&
            CppCore::rdownptwo32(97U, 8U)  == 96U &&
            CppCore::rdownptwo32(137U, 2U) == 136U;
      }

      INLINE static bool rdownptwo64()
      {
         return
            CppCore::rdownptwo64(19ULL, 8ULL)  == 16ULL &&
            CppCore::rdownptwo64(8ULL, 8ULL)   == 8ULL  &&
            CppCore::rdownptwo64(1ULL, 8ULL)   == 0ULL  &&
            CppCore::rdownptwo64(1ULL, 2ULL)   == 0ULL  &&
            CppCore::rdownptwo64(1ULL, 1ULL)   == 1ULL  &&
            CppCore::rdownptwo64(65ULL, 64ULL) == 64ULL &&
            CppCore::rdownptwo64(97ULL, 8ULL)  == 96ULL &&
            CppCore::rdownptwo64(137ULL, 2ULL) == 136ULL;
      }

      INLINE static bool rupptwo32()
      {
         return
            CppCore::rupptwo32(19U, 8U)  == 24U  &&
            CppCore::rupptwo32(8U, 8U)   == 8U   &&
            CppCore::rupptwo32(1U, 8U)   == 8U   &&
            CppCore::rupptwo32(1U, 2U)   == 2U   &&
            CppCore::rupptwo32(1U, 1U)   == 1U   &&
            CppCore::rupptwo32(65U, 64U) == 128U &&
            CppCore::rupptwo32(97U, 8U)  == 104U &&
            CppCore::rupptwo32(137U, 2U) == 138U;
      }

      INLINE static bool rupptwo64()
      {
         return
            CppCore::rupptwo64(19ULL, 8ULL)  == 24ULL  &&
            CppCore::rupptwo64(8ULL, 8ULL)   == 8ULL   &&
            CppCore::rupptwo64(1ULL, 8ULL)   == 8ULL   &&
            CppCore::rupptwo64(1ULL, 2ULL)   == 2ULL   &&
            CppCore::rupptwo64(1ULL, 1ULL)   == 1ULL   &&
            CppCore::rupptwo64(65ULL, 64ULL) == 128ULL &&
            CppCore::rupptwo64(97ULL, 8ULL)  == 104ULL &&
            CppCore::rupptwo64(137UL, 2ULL)  == 138ULL;
      }

      INLINE static bool rdown32()
      {
         return
            CppCore::rdown32(19U, 10U) == 10U &&
            CppCore::rdown32(10U, 10U) == 10U &&
            CppCore::rdown32(8U, 7U)   == 7U  &&
            CppCore::rdown32(1U, 2U)   == 0U  &&
            CppCore::rdown32(1U, 1U)   == 1U  &&
            CppCore::rdown32(65U, 64U) == 64U &&
            CppCore::rdown32(97U, 8U)  == 96U &&
            CppCore::rdown32(137U, 2U) == 136U;
      }

      INLINE static bool rdown64()
      {
         return
            CppCore::rdown64(19ULL, 10ULL) == 10ULL &&
            CppCore::rdown64(10ULL, 10ULL) == 10ULL &&
            CppCore::rdown64(8ULL, 7ULL)   == 7ULL  &&
            CppCore::rdown64(1ULL, 2ULL)   == 0ULL  &&
            CppCore::rdown64(1ULL, 1ULL)   == 1ULL  &&
            CppCore::rdown64(65ULL, 64ULL) == 64ULL &&
            CppCore::rdown64(97ULL, 8ULL)  == 96ULL &&
            CppCore::rdown64(137ULL, 2ULL) == 136ULL;
      }

      INLINE static bool rup32()
      {
         return
            CppCore::rup32(19U, 10U) == 20U  &&
            CppCore::rup32(10U, 10U) == 10U  &&
            CppCore::rup32(8U, 7U)   == 14U  &&
            CppCore::rup32(1U, 2U)   == 2U   &&
            CppCore::rup32(1U, 1U)   == 1U   &&
            CppCore::rup32(65U, 64U) == 128U &&
            CppCore::rup32(97U, 8U)  == 104U &&
            CppCore::rup32(137U, 2U) == 138U;
      }

      INLINE static bool rup64()
      {
         return
            CppCore::rup64(19ULL, 10ULL) == 20ULL  &&
            CppCore::rup64(10ULL, 10ULL) == 10ULL  &&
            CppCore::rup64(8ULL, 7ULL)   == 14ULL  &&
            CppCore::rup64(1ULL, 2ULL)   == 2ULL   &&
            CppCore::rup64(1ULL, 1ULL)   == 1ULL   &&
            CppCore::rup64(65ULL, 64ULL) == 128ULL &&
            CppCore::rup64(97ULL, 8ULL)  == 104ULL &&
            CppCore::rup64(137ULL, 2ULL) == 138ULL;
      }

      INLINE static bool round32()
      {
         return
            CppCore::round32(19U, 10U) == 20U &&
            CppCore::round32(10U, 10U) == 10U &&
            CppCore::round32(8U, 7U)   == 7U  &&
            CppCore::round32(1U, 2U)   == 2U  &&
            CppCore::round32(1U, 1U)   == 1U  &&
            CppCore::round32(1U, 8U)   == 8U  &&
            CppCore::round32(65U, 64U) == 64U &&
            CppCore::round32(97U, 8U)  == 96U &&
            CppCore::round32(137U, 2U) == 136U;
      }

      INLINE static bool round64()
      {
         return
            CppCore::round64(19ULL, 10ULL) == 20ULL &&
            CppCore::round64(10ULL, 10ULL) == 10ULL &&
            CppCore::round64(8ULL, 7ULL)   == 7ULL  &&
            CppCore::round64(1ULL, 2ULL)   == 2ULL  &&
            CppCore::round64(1ULL, 1ULL)   == 1ULL  &&
            CppCore::round64(1ULL, 8ULL)   == 8ULL  &&
            CppCore::round64(65ULL, 64ULL) == 64ULL &&
            CppCore::round64(97ULL, 8ULL)  == 96ULL &&
            CppCore::round64(137ULL, 2ULL) == 136ULL;
      }

      INLINE static bool ngptwo32()
      {
         return
            CppCore::ngptwo32(19U)  == 32U  &&
            CppCore::ngptwo32(8U)   == 8U   &&
            CppCore::ngptwo32(1U)   == 1U   &&
            CppCore::ngptwo32(0U)   == 0U   &&
            CppCore::ngptwo32(63U)  == 64U  &&
            CppCore::ngptwo32(97U)  == 128U &&
            CppCore::ngptwo32(137U) == 256U &&
            CppCore::ngptwo32(0xFFFFFFFFU) == 0U;
      }

      INLINE static bool ngptwo64()
      {
         return
            CppCore::ngptwo64(19ULL)  == 32ULL  &&
            CppCore::ngptwo64(8ULL)   == 8ULL   &&
            CppCore::ngptwo64(1ULL)   == 1ULL   &&
            CppCore::ngptwo64(0ULL)   == 0ULL   &&
            CppCore::ngptwo64(63ULL)  == 64ULL  &&
            CppCore::ngptwo64(97ULL)  == 128ULL &&
            CppCore::ngptwo64(137ULL) == 256ULL &&
            CppCore::ngptwo64(0x00000000FFFFFFFFULL) == 0x0000000100000000ULL &&
            CppCore::ngptwo64(0xFFFFFFFFFFFFFFFFULL) == 0x0000000000000000ULL;
      }

      INLINE static bool nlptwo32()
      {
         return
            CppCore::nlptwo32(19U)  == 16U  &&
            CppCore::nlptwo32(8U)   == 8U   &&
            CppCore::nlptwo32(1U)   == 1U   &&
            CppCore::nlptwo32(0U)   == 0U   &&
            CppCore::nlptwo32(63U)  == 32U  &&
            CppCore::nlptwo32(97U)  == 64U  &&
            CppCore::nlptwo32(137U) == 128U &&
            CppCore::nlptwo32(0xFFFFFFFFU) == 0x80000000U;
      }

      INLINE static bool nlptwo64()
      {
         return
            CppCore::nlptwo64(19ULL)  == 16ULL  &&
            CppCore::nlptwo64(8ULL)   == 8ULL   &&
            CppCore::nlptwo64(1ULL)   == 1ULL   &&
            CppCore::nlptwo64(0ULL)   == 0ULL   &&
            CppCore::nlptwo64(63ULL)  == 32ULL  &&
            CppCore::nlptwo64(97ULL)  == 64ULL  &&
            CppCore::nlptwo64(137ULL) == 128ULL &&
            CppCore::nlptwo64(0xFFFFFFFFFFFFFFFFULL) == 0x8000000000000000ULL;
      }

      INLINE static bool addcarry32()
      {
         uint32_t r; uint8_t c;
         c = 0; CppCore::addcarry32(0x00000000U, 0x00000000U, r, c); if (c != 0x00 || r != 0x00000000U) return false;
         c = 1; CppCore::addcarry32(0x00000000U, 0x00000000U, r, c); if (c != 0x00 || r != 0x00000001U) return false;
         c = 0; CppCore::addcarry32(0x00000000U, 0xFFFFFFFFU, r, c); if (c != 0x00 || r != 0xFFFFFFFFU) return false;
         c = 1; CppCore::addcarry32(0x00000000U, 0xFFFFFFFFU, r, c); if (c != 0x01 || r != 0x00000000U) return false;
         c = 0; CppCore::addcarry32(0xFFFFFFFFU, 0x00000001U, r, c); if (c != 0x01 || r != 0x00000000U) return false;
         c = 0; CppCore::addcarry32(0xFFFFFFFFU, 0xFFFFFFFFU, r, c); if (c != 0x01 || r != 0xFFFFFFFEU) return false;
         c = 1; CppCore::addcarry32(0xFFFFFFFFU, 0xFFFFFFFFU, r, c); if (c != 0x01 || r != 0xFFFFFFFFU) return false;
         c = 1; CppCore::addcarry32(0x00000000U, 0xFFFFFFFEU, r, c); if (c != 0x00 || r != 0xFFFFFFFFU) return false;
         c = 1; CppCore::addcarry32(0xFFFFFFFEU, 0x00000000U, r, c); if (c != 0x00 || r != 0xFFFFFFFFU) return false;
         c = 1; CppCore::addcarry32(0x5F8BC351U, 0xF924BCA9U, r, c); if (c != 0x01 || r != 0x58B07FFBU) return false;
         c = 1; CppCore::addcarry32(0x5F8BC350U, 0xF924BCA0U, r, c); if (c != 0x01 || r != 0x58B07FF1U) return false;
         return true;
      }

      INLINE static bool addcarry64()
      {
         uint64_t r; uint8_t c;
         c = 0; CppCore::addcarry64(0x0000000000000000ULL, 0x0000000000000000ULL, r, c); if (c != 0x00 || r != 0x0000000000000000ULL) return false;
         c = 1; CppCore::addcarry64(0x0000000000000000ULL, 0x0000000000000000ULL, r, c); if (c != 0x00 || r != 0x0000000000000001ULL) return false;
         c = 0; CppCore::addcarry64(0x0000000000000000ULL, 0xFFFFFFFFFFFFFFFFULL, r, c); if (c != 0x00 || r != 0xFFFFFFFFFFFFFFFFULL) return false;
         c = 1; CppCore::addcarry64(0x0000000000000000ULL, 0xFFFFFFFFFFFFFFFFULL, r, c); if (c != 0x01 || r != 0x0000000000000000ULL) return false;
         c = 0; CppCore::addcarry64(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, r, c); if (c != 0x01 || r != 0x0000000000000000ULL) return false;
         c = 0; CppCore::addcarry64(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, r, c); if (c != 0x01 || r != 0xFFFFFFFFFFFFFFFEULL) return false;
         c = 1; CppCore::addcarry64(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, r, c); if (c != 0x01 || r != 0xFFFFFFFFFFFFFFFFULL) return false;
         c = 1; CppCore::addcarry64(0x0000000000000000ULL, 0xFFFFFFFFFFFFFFFEULL, r, c); if (c != 0x00 || r != 0xFFFFFFFFFFFFFFFFULL) return false;
         c = 1; CppCore::addcarry64(0xFFFFFFFFFFFFFFFEULL, 0x0000000000000000ULL, r, c); if (c != 0x00 || r != 0xFFFFFFFFFFFFFFFFULL) return false;
         c = 1; CppCore::addcarry64(0x5F8BC3515F8BC351ULL, 0xF924BCA9F924BCA9ULL, r, c); if (c != 0x01 || r != 0x58B07FFB58B07FFBULL) return false;
         c = 1; CppCore::addcarry64(0x5F8BC3505F8BC350ULL, 0xF924BCA0F924BCA0ULL, r, c); if (c != 0x01 || r != 0x58B07FF158B07FF1ULL) return false;
         return true;
      }

      INLINE static bool subborrow32()
      {
         uint32_t r; uint8_t c;
         c = 0; CppCore::subborrow32(0x00000000U, 0x00000000U, r, c); if (c != 0x00 || r != 0x00000000U) return false;
         c = 1; CppCore::subborrow32(0x00000000U, 0x00000000U, r, c); if (c != 0x01 || r != 0xFFFFFFFFU) return false;
         c = 1; CppCore::subborrow32(0x00000002U, 0x00000001U, r, c); if (c != 0x00 || r != 0x00000000U) return false;
         c = 1; CppCore::subborrow32(0x00000000U, 0xFFFFFFFFU, r, c); if (c != 0x01 || r != 0x00000000U) return false;
         c = 0; CppCore::subborrow32(0xFFFFFFFFU, 0x00000001U, r, c); if (c != 0x00 || r != 0xFFFFFFFEU) return false;
         c = 1; CppCore::subborrow32(0xFFFFFFFFU, 0xFFFFFFFFU, r, c); if (c != 0x01 || r != 0xFFFFFFFFU) return false;
         c = 1; CppCore::subborrow32(0xFFFFFFFFU, 0xFFFFFFFEU, r, c); if (c != 0x00 || r != 0x00000000U) return false;
         c = 1; CppCore::subborrow32(0x1EF42BC0U, 0x2FC2155BU, r, c); if (c != 0x01 || r != 0xEF321664U) return false;
         return true;
      }

      INLINE static bool subborrow64()
      {
         uint64_t r; uint8_t c;
         c = 0; CppCore::subborrow64(0x0000000000000000ULL, 0x0000000000000000ULL, r, c); if (c != 0x00 || r != 0x0000000000000000ULL) return false;
         c = 1; CppCore::subborrow64(0x0000000000000000ULL, 0x0000000000000000ULL, r, c); if (c != 0x01 || r != 0xFFFFFFFFFFFFFFFFULL) return false;
         c = 1; CppCore::subborrow64(0x0000000000000002ULL, 0x0000000000000001ULL, r, c); if (c != 0x00 || r != 0x0000000000000000ULL) return false;
         c = 1; CppCore::subborrow64(0x0000000000000000ULL, 0xFFFFFFFFFFFFFFFFULL, r, c); if (c != 0x01 || r != 0x0000000000000000ULL) return false;
         c = 0; CppCore::subborrow64(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, r, c); if (c != 0x00 || r != 0xFFFFFFFFFFFFFFFEULL) return false;
         c = 1; CppCore::subborrow64(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, r, c); if (c != 0x01 || r != 0xFFFFFFFFFFFFFFFFULL) return false;
         c = 1; CppCore::subborrow64(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFEULL, r, c); if (c != 0x00 || r != 0x0000000000000000ULL) return false;
         c = 1; CppCore::subborrow64(0x1EF42BC01EF42BC0ULL, 0x2FC2155B2FC2155BULL, r, c); if (c != 0x01 || r != 0xEF321664EF321664ULL) return false;
         return true;
      }

      INLINE static bool mul128()
      {
         int64_t l, h;
         CppCore::mul128( 0,  0, l, h); if (h != 0x0000000000000000 || l != 0x0000000000000000) return false;
         CppCore::mul128( 0,  1, l, h); if (h != 0x0000000000000000 || l != 0x0000000000000000) return false;
         CppCore::mul128( 1,  0, l, h); if (h != 0x0000000000000000 || l != 0x0000000000000000) return false;
         CppCore::mul128( 1,  1, l, h); if (h != 0x0000000000000000 || l != 0x0000000000000001) return false;
         CppCore::mul128(-1, -1, l, h); if (h != 0x0000000000000000 || l != 0x0000000000000001) return false;
         CppCore::mul128(-1,  1, l, h); if (h != 0xFFFFFFFFFFFFFFFF || l != 0xFFFFFFFFFFFFFFFF) return false;
         CppCore::mul128( 1, -1, l, h); if (h != 0xFFFFFFFFFFFFFFFF || l != 0xFFFFFFFFFFFFFFFF) return false;
         CppCore::mul128(0x7FFFFFFFFFFFFFFF, 0x0000000000000002, l, h); if (h != 0x0000000000000000 || l != 0xFFFFFFFFFFFFFFFE) return false; //INT64MAX*2
         CppCore::mul128(0x7FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF, l, h); if (h != 0x3FFFFFFFFFFFFFFF || l != 0x0000000000000001) return false; //INT64MAX*INT64MAX
         CppCore::mul128(0x8000000000000000, 0x8000000000000000, l, h); if (h != 0x4000000000000000 || l != 0x0000000000000000) return false; //INT64MIN*INT64MIN
         CppCore::mul128(0x7FFFFFFFFFFFFFFF, 0x8000000000000000, l, h); if (h != 0xC000000000000000 || l != 0x8000000000000000) return false; //INT64MAX*INT64MIN
         CppCore::mul128(0x0FFFFFFFFFFFFFFF, 0x00000000F0000000, l, h); if (h != 0x000000000EFFFFFF || l != 0xFFFFFFFF10000000) return false; //MSDN MUL128 EX.
         return true;
      }

      INLINE static bool overflowadd16()
      {
         uint16_t ru;
         int16_t  rs;
         const bool a = // unsigned
            CppCore::overflowadd(uint16_t(0x0000), uint16_t(0x0000), ru) == false && ru == uint16_t(0x0000) &&
            CppCore::overflowadd(uint16_t(0x0001), uint16_t(0x0001), ru) == false && ru == uint16_t(0x0002) &&
            CppCore::overflowadd(uint16_t(0xFFFE), uint16_t(0x0001), ru) == false && ru == uint16_t(0xFFFF) &&
            CppCore::overflowadd(uint16_t(0x0001), uint16_t(0xFFFE), ru) == false && ru == uint16_t(0xFFFF) &&
            CppCore::overflowadd(uint16_t(0x7FFF), uint16_t(0x0001), ru) == false && ru == uint16_t(0x8000) &&
            CppCore::overflowadd(uint16_t(0x0001), uint16_t(0x7FFF), ru) == false && ru == uint16_t(0x8000) &&
            CppCore::overflowadd(uint16_t(0xFFFF), uint16_t(0x0000), ru) == false && ru == uint16_t(0xFFFF) &&
            CppCore::overflowadd(uint16_t(0x0000), uint16_t(0xFFFF), ru) == false && ru == uint16_t(0xFFFF) &&
            CppCore::overflowadd(uint16_t(0xFFFF), uint16_t(0x0001), ru) == true  &&
            CppCore::overflowadd(uint16_t(0x0001), uint16_t(0xFFFF), ru) == true  &&
            CppCore::overflowadd(uint16_t(0xFFFF), uint16_t(0xFFFF), ru) == true;
         const bool b = // signed
            CppCore::overflowadd(int16_t(0x0000), int16_t(0x0000), rs) == false && rs == int16_t(0x0000) &&
            CppCore::overflowadd(int16_t(0x0001), int16_t(0x0001), rs) == false && rs == int16_t(0x0002) &&
            CppCore::overflowadd(int16_t(0x7FFE), int16_t(0x0001), rs) == false && rs == int16_t(0x7FFF) &&
            CppCore::overflowadd(int16_t(0x0001), int16_t(0x7FFE), rs) == false && rs == int16_t(0x7FFF) &&
            CppCore::overflowadd(int16_t(0x7FFF), int16_t(0xFFFF), rs) == false && rs == int16_t(0x7FFE) &&
            CppCore::overflowadd(int16_t(0xFFFF), int16_t(0x7FFF), rs) == false && rs == int16_t(0x7FFE) &&
            CppCore::overflowadd(int16_t(0x7FFF), int16_t(0x8001), rs) == false && rs == int16_t(0x0000) &&
            CppCore::overflowadd(int16_t(0x8001), int16_t(0x7FFF), rs) == false && rs == int16_t(0x0000) &&
            CppCore::overflowadd(int16_t(0x8008), int16_t(0xFFF8), rs) == false && rs == int16_t(0x8000) &&
            CppCore::overflowadd(int16_t(0x7FFF), int16_t(0x0001), rs) == true  &&
            CppCore::overflowadd(int16_t(0x0001), int16_t(0x7FFF), rs) == true  &&
            CppCore::overflowadd(int16_t(0xFFFF), int16_t(0x8000), rs) == true  &&
            CppCore::overflowadd(int16_t(0x8000), int16_t(0xFFFF), rs) == true;
         return a && b;
      }

      INLINE static bool overflowadd32()
      {
         uint32_t ru;
         int32_t  rs;
         const bool a = // unsigned
            CppCore::overflowadd(0x00000000U, 0x00000000U, ru) == false && ru == 0x00000000U &&
            CppCore::overflowadd(0x00000001U, 0x00000001U, ru) == false && ru == 0x00000002U &&
            CppCore::overflowadd(0xFFFFFFFEU, 0x00000001U, ru) == false && ru == 0xFFFFFFFFU &&
            CppCore::overflowadd(0x00000001U, 0xFFFFFFFEU, ru) == false && ru == 0xFFFFFFFFU &&
            CppCore::overflowadd(0x7FFFFFFFU, 0x00000001U, ru) == false && ru == 0x80000000U &&
            CppCore::overflowadd(0x00000001U, 0x7FFFFFFFU, ru) == false && ru == 0x80000000U &&
            CppCore::overflowadd(0xFFFFFFFFU, 0x00000000U, ru) == false && ru == 0xFFFFFFFFU &&
            CppCore::overflowadd(0x00000000U, 0xFFFFFFFFU, ru) == false && ru == 0xFFFFFFFFU &&
            CppCore::overflowadd(0xFFFFFFFFU, 0x00000001U, ru) == true  &&
            CppCore::overflowadd(0x00000001U, 0xFFFFFFFFU, ru) == true  &&
            CppCore::overflowadd(0xFFFFFFFFU, 0xFFFFFFFFU, ru) == true;
         const bool b = // signed
            CppCore::overflowadd(int32_t(0x00000000), int32_t(0x00000000), rs) == false && rs == int32_t(0x00000000) &&
            CppCore::overflowadd(int32_t(0x00000001), int32_t(0x00000001), rs) == false && rs == int32_t(0x00000002) &&
            CppCore::overflowadd(int32_t(0x7FFFFFFE), int32_t(0x00000001), rs) == false && rs == int32_t(0x7FFFFFFF) &&
            CppCore::overflowadd(int32_t(0x00000001), int32_t(0x7FFFFFFE), rs) == false && rs == int32_t(0x7FFFFFFF) &&
            CppCore::overflowadd(int32_t(0x7FFFFFFF), int32_t(0xFFFFFFFF), rs) == false && rs == int32_t(0x7FFFFFFE) &&
            CppCore::overflowadd(int32_t(0xFFFFFFFF), int32_t(0x7FFFFFFF), rs) == false && rs == int32_t(0x7FFFFFFE) &&
            CppCore::overflowadd(int32_t(0x7FFFFFFF), int32_t(0x80000001), rs) == false && rs == int32_t(0x00000000) &&
            CppCore::overflowadd(int32_t(0x80000001), int32_t(0x7FFFFFFF), rs) == false && rs == int32_t(0x00000000) &&
            CppCore::overflowadd(int32_t(0x80000008), int32_t(0xFFFFFFF8), rs) == false && rs == int32_t(0x80000000) &&
            CppCore::overflowadd(int32_t(0x7FFFFFFF), int32_t(0x00000001), rs) == true  &&
            CppCore::overflowadd(int32_t(0x00000001), int32_t(0x7FFFFFFF), rs) == true  &&
            CppCore::overflowadd(int32_t(0xFFFFFFFF), int32_t(0x80000000), rs) == true  &&
            CppCore::overflowadd(int32_t(0x80000000), int32_t(0xFFFFFFFF), rs) == true;
         return a && b;
      }

      INLINE static bool overflowadd64()
      {
         uint64_t ru;
         int64_t  rs;
         const bool a = // unsigned
            CppCore::overflowadd(0x0000000000000000ULL, 0x0000000000000000ULL, ru) == false && ru == 0x0000000000000000ULL &&
            CppCore::overflowadd(0x0000000000000001ULL, 0x0000000000000001ULL, ru) == false && ru == 0x0000000000000002ULL &&
            CppCore::overflowadd(0xFFFFFFFFFFFFFFFEULL, 0x0000000000000001ULL, ru) == false && ru == 0xFFFFFFFFFFFFFFFFULL &&
            CppCore::overflowadd(0x0000000000000001ULL, 0xFFFFFFFFFFFFFFFEULL, ru) == false && ru == 0xFFFFFFFFFFFFFFFFULL &&
            CppCore::overflowadd(0x7FFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, ru) == false && ru == 0x8000000000000000ULL &&
            CppCore::overflowadd(0x0000000000000001ULL, 0x7FFFFFFFFFFFFFFFULL, ru) == false && ru == 0x8000000000000000ULL &&
            CppCore::overflowadd(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, ru) == false && ru == 0xFFFFFFFFFFFFFFFFULL &&
            CppCore::overflowadd(0x0000000000000000ULL, 0xFFFFFFFFFFFFFFFFULL, ru) == false && ru == 0xFFFFFFFFFFFFFFFFULL &&
            CppCore::overflowadd(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, ru) == true  &&
            CppCore::overflowadd(0x0000000000000001ULL, 0xFFFFFFFFFFFFFFFFULL, ru) == true  &&
            CppCore::overflowadd(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, ru) == true;
         const bool b = // signed
            CppCore::overflowadd(int64_t(0x0000000000000000), int64_t(0x0000000000000000), rs) == false && rs == int64_t(0x0000000000000000) &&
            CppCore::overflowadd(int64_t(0x0000000000000001), int64_t(0x0000000000000001), rs) == false && rs == int64_t(0x0000000000000002) &&
            CppCore::overflowadd(int64_t(0x7FFFFFFFFFFFFFFE), int64_t(0x0000000000000001), rs) == false && rs == int64_t(0x7FFFFFFFFFFFFFFF) &&
            CppCore::overflowadd(int64_t(0x0000000000000001), int64_t(0x7FFFFFFFFFFFFFFE), rs) == false && rs == int64_t(0x7FFFFFFFFFFFFFFF) &&
            CppCore::overflowadd(int64_t(0x7FFFFFFFFFFFFFFF), int64_t(0xFFFFFFFFFFFFFFFF), rs) == false && rs == int64_t(0x7FFFFFFFFFFFFFFE) &&
            CppCore::overflowadd(int64_t(0xFFFFFFFFFFFFFFFF), int64_t(0x7FFFFFFFFFFFFFFF), rs) == false && rs == int64_t(0x7FFFFFFFFFFFFFFE) &&
            CppCore::overflowadd(int64_t(0x7FFFFFFFFFFFFFFF), int64_t(0x8000000000000001), rs) == false && rs == int64_t(0x0000000000000000) &&
            CppCore::overflowadd(int64_t(0x8000000000000001), int64_t(0x7FFFFFFFFFFFFFFF), rs) == false && rs == int64_t(0x0000000000000000) &&
            CppCore::overflowadd(int64_t(0x8000000000000008), int64_t(0xFFFFFFFFFFFFFFF8), rs) == false && rs == int64_t(0x8000000000000000) &&
            CppCore::overflowadd(int64_t(0x7FFFFFFFFFFFFFFF), int64_t(0x0000000000000001), rs) == true  &&
            CppCore::overflowadd(int64_t(0x0000000000000001), int64_t(0x7FFFFFFFFFFFFFFF), rs) == true  &&
            CppCore::overflowadd(int64_t(0x8000000000000000), int64_t(0xFFFFFFFFFFFFFFFF), rs) == true  &&
            CppCore::overflowadd(int64_t(0xFFFFFFFFFFFFFFFF), int64_t(0x8000000000000000), rs) == true;
         return a && b;
      }

      INLINE static bool overflowsub16()
      {
         uint16_t ru;
         int16_t  rs;
         const bool a = // unsigned
            CppCore::overflowsub(uint16_t(0x0000), uint16_t(0x0000), ru) == false && ru == uint16_t(0x0000) &&
            CppCore::overflowsub(uint16_t(0x0001), uint16_t(0x0001), ru) == false && ru == uint16_t(0x0000) &&
            CppCore::overflowsub(uint16_t(0xFFFF), uint16_t(0x0001), ru) == false && ru == uint16_t(0xFFFE) &&
            CppCore::overflowsub(uint16_t(0x0000), uint16_t(0x0001), ru) == true  &&
            CppCore::overflowsub(uint16_t(0x0001), uint16_t(0xFFFF), ru) == true;
         const bool b = // signed
            CppCore::overflowsub(int16_t(0x0000), int16_t(0x0000), rs) == false && rs == int16_t(0x0000) &&
            CppCore::overflowsub(int16_t(0x0001), int16_t(0x0001), rs) == false && rs == int16_t(0x0000) &&
            CppCore::overflowsub(int16_t(0xFFFF), int16_t(0xFFFF), ru) == false && ru == int16_t(0x0000) &&
            CppCore::overflowsub(int16_t(0x7FFF), int16_t(0x0001), rs) == false && rs == int16_t(0x7FFE) &&
            CppCore::overflowsub(int16_t(0x7FFF), int16_t(0x7FFF), rs) == false && rs == int16_t(0x0000) &&
            CppCore::overflowsub(int16_t(0xFFFF), int16_t(0x8000), rs) == false && rs == int16_t(0x7FFF) &&
            CppCore::overflowsub(int16_t(0x8008), int16_t(0x0008), rs) == false && rs == int16_t(0x8000) &&
            CppCore::overflowsub(int16_t(0x0000), int16_t(0x7FFF), rs) == false && rs == int16_t(0x8001) &&
            CppCore::overflowsub(int16_t(0x7FFF), int16_t(0xFFFF), rs) == true  &&
            CppCore::overflowsub(int16_t(0x0000), int16_t(0x8000), rs) == true  &&
            CppCore::overflowsub(int16_t(0x8000), int16_t(0x0001), rs) == true;
         return a && b;
      }

      INLINE static bool overflowsub32()
      {
         uint32_t ru;
         int32_t  rs;
         const bool a = // unsigned
            CppCore::overflowsub(0x00000000U, 0x00000000U, ru) == false && ru == 0x00000000U &&
            CppCore::overflowsub(0x00000001U, 0x00000001U, ru) == false && ru == 0x00000000U &&
            CppCore::overflowsub(0xFFFFFFFFU, 0x00000001U, ru) == false && ru == 0xFFFFFFFEU &&
            CppCore::overflowsub(0x00000000U, 0x00000001U, ru) == true  &&
            CppCore::overflowsub(0x00000001U, 0xFFFFFFFFU, ru) == true;
         const bool b = // signed
            CppCore::overflowsub(int32_t(0x00000000), int32_t(0x00000000), rs) == false && rs == int32_t(0x00000000) &&
            CppCore::overflowsub(int32_t(0x00000001), int32_t(0x00000001), rs) == false && rs == int32_t(0x00000000) &&
            CppCore::overflowsub(int32_t(0xFFFFFFFF), int32_t(0xFFFFFFFF), ru) == false && ru == int32_t(0x00000000) &&
            CppCore::overflowsub(int32_t(0x7FFFFFFF), int32_t(0x00000001), rs) == false && rs == int32_t(0x7FFFFFFE) &&
            CppCore::overflowsub(int32_t(0x7FFFFFFF), int32_t(0x7FFFFFFF), rs) == false && rs == int32_t(0x00000000) &&
            CppCore::overflowsub(int32_t(0xFFFFFFFF), int32_t(0x80000000), rs) == false && rs == int32_t(0x7FFFFFFF) &&
            CppCore::overflowsub(int32_t(0x80000008), int32_t(0x00000008), rs) == false && rs == int32_t(0x80000000) &&
            CppCore::overflowsub(int32_t(0x00000000), int32_t(0x7FFFFFFF), rs) == false && rs == int32_t(0x80000001) &&
            CppCore::overflowsub(int32_t(0x7FFFFFFF), int32_t(0xFFFFFFFF), rs) == true  &&
            CppCore::overflowsub(int32_t(0x00000000), int32_t(0x80000000), rs) == true  &&
            CppCore::overflowsub(int32_t(0x80000000), int32_t(0x00000001), rs) == true;
         return a && b;
      }

      INLINE static bool overflowsub64()
      {
         uint64_t ru;
         int64_t  rs;
         const bool a = // unsigned
            CppCore::overflowsub(0x0000000000000000ULL, 0x0000000000000000ULL, ru) == false && ru == 0x0000000000000000ULL &&
            CppCore::overflowsub(0x0000000000000001ULL, 0x0000000000000001ULL, ru) == false && ru == 0x0000000000000000ULL &&
            CppCore::overflowsub(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, ru) == false && ru == 0xFFFFFFFFFFFFFFFEULL &&
            CppCore::overflowsub(0x0000000000000000ULL, 0x0000000000000001ULL, ru) == true  &&
            CppCore::overflowsub(0x0000000000000001ULL, 0xFFFFFFFFFFFFFFFFULL, ru) == true;
         const bool b = // signed
            CppCore::overflowsub(int64_t(0x0000000000000000), int64_t(0x0000000000000000), rs) == false && rs == int64_t(0x0000000000000000) &&
            CppCore::overflowsub(int64_t(0x0000000000000001), int64_t(0x0000000000000001), rs) == false && rs == int64_t(0x0000000000000000) &&
            CppCore::overflowsub(int64_t(0xFFFFFFFFFFFFFFFF), int64_t(0xFFFFFFFFFFFFFFFF), rs) == false && rs == int64_t(0x0000000000000000) &&
            CppCore::overflowsub(int64_t(0x7FFFFFFFFFFFFFFF), int64_t(0x0000000000000001), rs) == false && rs == int64_t(0x7FFFFFFFFFFFFFFE) &&
            CppCore::overflowsub(int64_t(0x7FFFFFFFFFFFFFFF), int64_t(0x7FFFFFFFFFFFFFFF), rs) == false && rs == int64_t(0x0000000000000000) &&
            CppCore::overflowsub(int64_t(0xFFFFFFFFFFFFFFFF), int64_t(0x8000000000000000), rs) == false && rs == int64_t(0x7FFFFFFFFFFFFFFF) &&
            CppCore::overflowsub(int64_t(0x8000000000000008), int64_t(0x0000000000000008), rs) == false && rs == int64_t(0x8000000000000000) &&
            CppCore::overflowsub(int64_t(0x0000000000000000), int64_t(0x7FFFFFFFFFFFFFFF), rs) == false && rs == int64_t(0x8000000000000001) &&
            CppCore::overflowsub(int64_t(0x7FFFFFFFFFFFFFFF), int64_t(0xFFFFFFFFFFFFFFFF), rs) == true  &&
            CppCore::overflowsub(int64_t(0x0000000000000000), int64_t(0x8000000000000000), rs) == true  &&
            CppCore::overflowsub(int64_t(0x8000000000000000), int64_t(0x0000000000000001), rs) == true;
         return a && b;
      }

      INLINE static bool overflowmul16()
      {
         uint16_t ru;
         int16_t  rs;
         const bool a = // unsigned
            CppCore::overflowmul(uint16_t(0x0000), uint16_t(0x0000), ru) == false && ru == uint16_t(0x0000) &&
            CppCore::overflowmul(uint16_t(0x0001), uint16_t(0x0001), ru) == false && ru == uint16_t(0x0001) &&
            CppCore::overflowmul(uint16_t(0xFFFF), uint16_t(0x0001), ru) == false && ru == uint16_t(0xFFFF) &&
            CppCore::overflowmul(uint16_t(0x7FFF), uint16_t(0x0002), ru) == false && ru == uint16_t(0xFFFE) &&
            CppCore::overflowmul(uint16_t(0x8000), uint16_t(0x0002), ru) == true  &&
            CppCore::overflowmul(uint16_t(0xFFFF), uint16_t(0xFFFF), ru) == true;
         const bool b = // signed
            CppCore::overflowmul(int16_t(0x0000), int16_t(0x0000), rs) == false && rs == int16_t(0x0000) &&
            CppCore::overflowmul(int16_t(0x0001), int16_t(0x0001), rs) == false && rs == int16_t(0x0001) &&
            CppCore::overflowmul(int16_t(0xFFFF), int16_t(0x0001), rs) == false && rs == int16_t(0xFFFF) &&
            CppCore::overflowmul(int16_t(0xFFFF), int16_t(0xFFFF), rs) == false && rs == int16_t(0x0001) &&
            CppCore::overflowmul(int16_t(0x7FFF), int16_t(0x0002), rs) == true  &&
            CppCore::overflowmul(int16_t(0x8000), int16_t(0x0002), rs) == true;
         return a && b;
      }

      INLINE static bool overflowmul32()
      {
         uint32_t ru;
         int32_t  rs;
         const bool a = // unsigned
            CppCore::overflowmul(0x00000000U, 0x00000000U, ru) == false && ru == 0x00000000U &&
            CppCore::overflowmul(0x00000001U, 0x00000001U, ru) == false && ru == 0x00000001U &&
            CppCore::overflowmul(0xFFFFFFFFU, 0x00000001U, ru) == false && ru == 0xFFFFFFFFU &&
            CppCore::overflowmul(0x7FFFFFFFU, 0x00000002U, ru) == false && ru == 0xFFFFFFFEU &&
            CppCore::overflowmul(0x80000000U, 0x00000002U, ru) == true  &&
            CppCore::overflowmul(0xFFFFFFFFU, 0xFFFFFFFFU, ru) == true;
         const bool b = // signed
            CppCore::overflowmul(int32_t(0x00000000), int32_t(0x00000000), rs) == false && rs == int32_t(0x00000000) &&
            CppCore::overflowmul(int32_t(0x00000001), int32_t(0x00000001), rs) == false && rs == int32_t(0x00000001) &&
            CppCore::overflowmul(int32_t(0xFFFFFFFF), int32_t(0x00000001), rs) == false && rs == int32_t(0xFFFFFFFF) &&
            CppCore::overflowmul(int32_t(0xFFFFFFFF), int32_t(0xFFFFFFFF), rs) == false && rs == int32_t(0x00000001) &&
            CppCore::overflowmul(int32_t(0x7FFFFFFF), int32_t(0x00000002), rs) == true  &&
            CppCore::overflowmul(int32_t(0x80000000), int32_t(0x00000002), rs) == true;
         return a && b;
      }

      INLINE static bool overflowmul64()
      {
         uint64_t ru;
         int64_t  rs;
         const bool a = // unsigned
            CppCore::overflowmul(0x0000000000000000ULL, 0x0000000000000000ULL, ru) == false && ru == 0x0000000000000000ULL &&
            CppCore::overflowmul(0x0000000000000001ULL, 0x0000000000000001ULL, ru) == false && ru == 0x0000000000000001ULL &&
            CppCore::overflowmul(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, ru) == false && ru == 0xFFFFFFFFFFFFFFFFULL &&
            CppCore::overflowmul(0x7FFFFFFFFFFFFFFFULL, 0x0000000000000002ULL, ru) == false && ru == 0xFFFFFFFFFFFFFFFEULL &&
            CppCore::overflowmul(0x8000000000000000ULL, 0x0000000000000002ULL, ru) == true  &&
            CppCore::overflowmul(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, ru) == true;
         const bool b = // signed
            CppCore::overflowmul(0x0000000000000000LL, 0x0000000000000000LL, rs) == false && rs == 0x0000000000000000LL &&
            CppCore::overflowmul(0x0000000000000001LL, 0x0000000000000001LL, rs) == false && rs == 0x0000000000000001LL &&
            CppCore::overflowmul(0xFFFFFFFFFFFFFFFFLL, 0x0000000000000001LL, rs) == false && rs == 0xFFFFFFFFFFFFFFFFLL &&
            CppCore::overflowmul(0xFFFFFFFFFFFFFFFFLL, 0xFFFFFFFFFFFFFFFFLL, rs) == false && rs == 0x0000000000000001LL &&
            CppCore::overflowmul(0x7FFFFFFFFFFFFFFFLL, 0x0000000000000002LL, rs) == true  &&
            CppCore::overflowmul(0x8000000000000000LL, 0x0000000000000002LL, rs) == true;
         return a && b;
      }

      INLINE static bool umod()
      {
         uint128_t r128;
         uint128_t un128[2];

         // 0 % 1= 0
         CppCore::umod(r128,
            uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL),
            uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), un128);
         if (r128 != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL))
            return false;

         // 0 % MAX = 0
         CppCore::umod(r128,
            uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL),
            uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), un128);
         if (r128 != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL))
            return false;

         // 1 % 1= 0
         CppCore::umod(r128,
            uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL),
            uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), un128);
         if (r128 != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL))
            return false;

         // MAX % MAX = 0
         CppCore::umod(r128,
            uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL),
            uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), un128);
         if (r128 != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL))
            return false;

         // MAX % 1 = 0
         CppCore::umod(r128,
            uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL),
            uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), un128);
         if (r128 != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL))
            return false;

         // MAX % 1 = 0
         CppCore::umod(r128,
            uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL),
            uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), un128);
         if (r128 != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL))
            return false;

         // MAX % 2 = 1
         CppCore::umod(r128,
            uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL),
            uint128_t(0x0000000000000002ULL, 0x0000000000000000ULL), un128);
         if (r128 != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL))
            return false;

         // (MAX-1) % 2 = 0
         CppCore::umod(r128,
            uint128_t(0xFFFFFFFFFFFFFFFEULL, 0xFFFFFFFFFFFFFFFFULL),
            uint128_t(0x0000000000000002ULL, 0x0000000000000000ULL), un128);
         if (r128 != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL))
            return false;

         // CUSTOM: 32-BIT DIVISOR
         CppCore::umod(r128,
            uint128_t("8061880385625529040957037702"),
            uint128_t(                   "616726810"), un128);
         if (r128 != uint128_t(          "197575092"))
            return false;

         // CUSTOM: 64-BIT DIVISOR
         CppCore::umod(r128,
            uint128_t("8061880385625529040957037702"),
            uint128_t(         "3452186764624784266"), un128);
         if (r128 != uint128_t("2248286253981825640"))
            return false;

         // CUSTOM
         CppCore::umod(r128,
            uint128_t(  "340282366920938463463374607431768211455"),
            uint128_t(         "53553149753549569918930606026810"), un128);
         if (r128 != uint128_t("30306160373493648049023784656405"))
            return false;

         // CUSTOM
         CppCore::umod(r128,
            uint128_t(        "26127266920938463463374607431768211455"),
            uint128_t(        "23553149753549569918930606026468345810"), un128);
         if (r128 != uint128_t( "2574117167388893544444001405299865645"))
            return false;

         // CUSTOM
         CppCore::umod(r128,
            uint128_t("8061880385625529040957037702"),
            uint128_t("2687293461875176346985679234"), un128);
         if (r128 != uint128_t(                  "0"))
            return false;

         return true;
      }

      INLINE static bool umulmod32()
      {
         uint32_t r;

         CppCore::umulmod(0x00000000U, 0x00000000U, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod(0x00000000U, 0xFFFFFFFFU, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod(0xFFFFFFFFU, 0x00000000U, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod(0x00000001U, 0x00000001U, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod(0x00000003U, 0x00000004U, 0x00000003U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod(0x00000003U, 0x00000004U, 0x00000004U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod(0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, r); if (r != 0x00000000U) return false;
         CppCore::umulmod(0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFEU, r); if (r != 0x00000001U) return false;
         CppCore::umulmod(0xFFFFFFFFU, 0xFFFFFFFFU, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod(0xFFFFFFFFU, 0xFFFFFFFFU, 0x00000002U, r); if (r != 0x00000001U) return false;
         CppCore::umulmod(0xFA35C2E1U, 0x2ECF0157U, 0x03BE8372U, r); if (r != 0x02C838DFU) return false;

         CppCore::umulmod32(0x00000000U, 0x00000000U, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod32(0x00000000U, 0xFFFFFFFFU, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod32(0xFFFFFFFFU, 0x00000000U, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod32(0x00000001U, 0x00000001U, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod32(0x00000003U, 0x00000004U, 0x00000003U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod32(0x00000003U, 0x00000004U, 0x00000004U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod32(0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, r); if (r != 0x00000000U) return false;
         CppCore::umulmod32(0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFEU, r); if (r != 0x00000001U) return false;
         CppCore::umulmod32(0xFFFFFFFFU, 0xFFFFFFFFU, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::umulmod32(0xFFFFFFFFU, 0xFFFFFFFFU, 0x00000002U, r); if (r != 0x00000001U) return false;
         CppCore::umulmod32(0xFA35C2E1U, 0x2ECF0157U, 0x03BE8372U, r); if (r != 0x02C838DFU) return false;

         return true;
      }

      INLINE static bool umulmod64()
      {
         uint64_t r;

         CppCore::umulmod((uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x000000000000000ULL) return false;
         CppCore::umulmod((uint64_t)0x0000000000000000ULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x000000000000000ULL) return false;
         CppCore::umulmod((uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x000000000000000ULL) return false;
         CppCore::umulmod((uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x000000000000000ULL) return false;
         CppCore::umulmod((uint64_t)0x0000000000000003ULL, (uint64_t)0x0000000000000004ULL, (uint64_t)0x0000000000000003ULL, r); if (r != (uint64_t)0x000000000000000ULL) return false;
         CppCore::umulmod((uint64_t)0x0000000000000003ULL, (uint64_t)0x0000000000000004ULL, (uint64_t)0x0000000000000004ULL, r); if (r != (uint64_t)0x000000000000000ULL) return false;
         CppCore::umulmod((uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, r); if (r != (uint64_t)0x000000000000000ULL) return false;
         CppCore::umulmod((uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFEULL, r); if (r != (uint64_t)0x000000000000001ULL) return false;
         CppCore::umulmod((uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x000000000000000ULL) return false;
         CppCore::umulmod((uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0x0000000000000002ULL, r); if (r != (uint64_t)0x000000000000001ULL) return false;
         CppCore::umulmod((uint64_t)0xFA35C2E1FA35C2E1ULL, (uint64_t)0x2ECF01572ECF0157ULL, (uint64_t)0x03BE837203BE8372ULL, r); if (r != (uint64_t)0x17413F7017413F7ULL) return false;

         CppCore::umulmod64((uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::umulmod64((uint64_t)0x0000000000000000ULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::umulmod64((uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::umulmod64((uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::umulmod64((uint64_t)0x0000000000000003ULL, (uint64_t)0x0000000000000004ULL, (uint64_t)0x0000000000000003ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::umulmod64((uint64_t)0x0000000000000003ULL, (uint64_t)0x0000000000000004ULL, (uint64_t)0x0000000000000004ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::umulmod64((uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::umulmod64((uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFEULL, r); if (r != (uint64_t)0x0000000000000001ULL) return false;
         CppCore::umulmod64((uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::umulmod64((uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0x0000000000000002ULL, r); if (r != (uint64_t)0x0000000000000001ULL) return false;
         CppCore::umulmod64((uint64_t)0xFA35C2E1FA35C2E1ULL, (uint64_t)0x2ECF01572ECF0157ULL, (uint64_t)0x03BE837203BE8372ULL, r); if (r != (uint64_t)0x017413F7017413F7ULL) return false;

         return true;
      }

      INLINE static bool upowmod32()
      {
         uint32_t r;
         uint32_t a;

         a = 0x00000000U; CppCore::upowmod(a, 0x00000000U, 0x00000001U, r); if (r != 0x00000000U) return false;
         a = 0x00000001U; CppCore::upowmod(a, 0x00000000U, 0x00000001U, r); if (r != 0x00000000U) return false;
         a = 0x00000001U; CppCore::upowmod(a, 0x00000000U, 0x00000002U, r); if (r != 0x00000001U) return false;
         a = 0x00000002U; CppCore::upowmod(a, 0x00000000U, 0x00000001U, r); if (r != 0x00000000U) return false;
         a = 0x00000000U; CppCore::upowmod(a, 0x00000001U, 0x00000001U, r); if (r != 0x00000000U) return false;
         a = 0x00000001U; CppCore::upowmod(a, 0x00000001U, 0x00000001U, r); if (r != 0x00000000U) return false;
         a = 0x00000002U; CppCore::upowmod(a, 0x00000001U, 0x00000001U, r); if (r != 0x00000000U) return false;
         a = 0xFFFFFFFFU; CppCore::upowmod(a, 0xFFFFFFFFU, 0x00000001U, r); if (r != 0x00000000U) return false;
         a = 0xFFFFFFFFU; CppCore::upowmod(a, 0xFFFFFFFFU, 0xFFFFFFFFU, r); if (r != 0x00000000U) return false;
         a = 0xFFFFFFFFU; CppCore::upowmod(a, 0x00000002U, 0x00000002U, r); if (r != 0x00000001U) return false;
         a = 0xFFFFFFFFU; CppCore::upowmod(a, 0xFFFFFFFFU, 0x00000002U, r); if (r != 0x00000001U) return false;
         a = 0x00000003U; CppCore::upowmod(a, 0x00000003U, 0x00000005U, r); if (r != 0x00000002U) return false;
         a = 0xFA35C2E1U; CppCore::upowmod(a, 0x00000002U, 0x03BE8372U, r); if (r != 0x03840BCBU) return false;
         a = 0xF9AC3157U; CppCore::upowmod(a, 0x00000003U, 0x01BE8372U, r); if (r != 0x004a6079U) return false;

         return true;
      }

      INLINE static bool upowmod64()
      {
         uint64_t r;
         uint64_t a;

         a = 0x0000000000000000ULL; CppCore::upowmod(a, (uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         a = 0x0000000000000001ULL; CppCore::upowmod(a, (uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         a = 0x0000000000000001ULL; CppCore::upowmod(a, (uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000002ULL, r); if (r != (uint64_t)0x0000000000000001ULL) return false;
         a = 0x0000000000000002ULL; CppCore::upowmod(a, (uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         a = 0x0000000000000000ULL; CppCore::upowmod(a, (uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         a = 0x0000000000000001ULL; CppCore::upowmod(a, (uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         a = 0x0000000000000002ULL; CppCore::upowmod(a, (uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         a = 0xFFFFFFFFFFFFFFFFULL; CppCore::upowmod(a, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         a = 0xFFFFFFFFFFFFFFFFULL; CppCore::upowmod(a, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0xFFFFFFFFFFFFFFFFULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         a = 0xFFFFFFFFFFFFFFFFULL; CppCore::upowmod(a, (uint64_t)0x0000000000000002ULL, (uint64_t)0x0000000000000002ULL, r); if (r != (uint64_t)0x0000000000000001ULL) return false;
         a = 0xFFFFFFFFFFFFFFFFULL; CppCore::upowmod(a, (uint64_t)0xFFFFFFFFFFFFFFFFULL, (uint64_t)0x0000000000000002ULL, r); if (r != (uint64_t)0x0000000000000001ULL) return false;
         a = 0x0000000000000003ULL; CppCore::upowmod(a, (uint64_t)0x0000000000000003ULL, (uint64_t)0x0000000000000005ULL, r); if (r != (uint64_t)0x0000000000000002ULL) return false;
         a = 0xFA35C2E1FA35C2E1ULL; CppCore::upowmod(a, (uint64_t)0x0000000000000002ULL, (uint64_t)0x03BE837203BE8372ULL, r); if (r != (uint64_t)0x0182158D0182158DULL) return false;
         a = 0xF9AC3157F9AC3157ULL; CppCore::upowmod(a, (uint64_t)0x0000000000000003ULL, (uint64_t)0x01BE837201BE8372ULL, r); if (r != (uint64_t)0x00359D2100359D21ULL) return false;

         return true;
      }

      INLINE static bool upow32()
      {
         for (uint32_t base = 0; base < 20; base++)
            for (uint32_t exp = 0; exp < 4; exp++)
               if ((uint32_t)::pow((double)base, (double)exp) != CppCore::upow(base, exp))
                  return false;
         return true;
      }

      INLINE static bool upow64()
      {
         for (uint64_t base = 0; base < 100; base++)
            for (uint32_t exp = 0; exp < 4; exp++)
               if ((uint64_t)::pow((double)base, (double)exp) != CppCore::upow(base, exp))
                  return false;
         return true;
      }

      INLINE static bool udivmod32()
      {
         uint32_t q, r;
         CppCore::udivmod32(0x00000000U, 0x00000001U, q, r); if (q != 0x00000000U || r != 0x00000000U) return false;
         CppCore::udivmod32(0x00000001U, 0x00000001U, q, r); if (q != 0x00000001U || r != 0x00000000U) return false;
         CppCore::udivmod32(0x00000002U, 0x00000003U, q, r); if (q != 0x00000000U || r != 0x00000002U) return false;
         CppCore::udivmod32(0xFFFFFFFFU, 0xFFFFFFFFU, q, r); if (q != 0x00000001U || r != 0x00000000U) return false;
         CppCore::udivmod32(0xFFFFFFFFU, 0x00000001U, q, r); if (q != 0xFFFFFFFFU || r != 0x00000000U) return false;
         CppCore::udivmod32(0x00000010U, 0x00000005U, q, r); if (q != 0x00000003U || r != 0x00000001U) return false;
         CppCore::udivmod32(0x00000010U, 0x00000002U, q, r); if (q != 0x00000008U || r != 0x00000000U) return false;
         return true;
      }

      INLINE static bool udivmod64()
      {
         uint64_t q, r;
         CppCore::udivmod64(0x0000000000000000ULL, 0x0000000000000001ULL, q, r); if (q != 0x0000000000000000ULL || r != 0x0000000000000000ULL) return false;
         CppCore::udivmod64(0x0000000000000001ULL, 0x0000000000000001ULL, q, r); if (q != 0x0000000000000001ULL || r != 0x0000000000000000ULL) return false;
         CppCore::udivmod64(0x0000000000000002ULL, 0x0000000000000003ULL, q, r); if (q != 0x0000000000000000ULL || r != 0x0000000000000002ULL) return false;
         CppCore::udivmod64(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, q, r); if (q != 0x0000000000000001ULL || r != 0x0000000000000000ULL) return false;
         CppCore::udivmod64(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, q, r); if (q != 0xFFFFFFFFFFFFFFFFULL || r != 0x0000000000000000ULL) return false;
         CppCore::udivmod64(0x0000000000000010ULL, 0x0000000000000005ULL, q, r); if (q != 0x0000000000000003ULL || r != 0x0000000000000001ULL) return false;
         CppCore::udivmod64(0x0000000000000010ULL, 0x0000000000000002ULL, q, r); if (q != 0x0000000000000008ULL || r != 0x0000000000000000ULL) return false;
         return true;
      }

      INLINE static bool udivmod64_32()
      {
         uint32_t q, r;
         CppCore::udivmod64_32(0x0000000000000000ULL, 0x00000001U, q, r); if (q != 0x00000000U || r != 0x00000000U) return false;
         CppCore::udivmod64_32(0x0000000000000001ULL, 0x00000001U, q, r); if (q != 0x00000001U || r != 0x00000000U) return false;
         CppCore::udivmod64_32(0x0000000000000002ULL, 0x00000003U, q, r); if (q != 0x00000000U || r != 0x00000002U) return false;
         CppCore::udivmod64_32(0x00000000FFFFFFFFULL, 0x00000001U, q, r); if (q != 0xFFFFFFFFU || r != 0x00000000U) return false;
         CppCore::udivmod64_32(0x00000000FFFFFFFFULL, 0xFFFFFFFFU, q, r); if (q != 0x00000001U || r != 0x00000000U) return false;
         CppCore::udivmod64_32(0x0000000000000010ULL, 0x00000005U, q, r); if (q != 0x00000003U || r != 0x00000001U) return false;
         CppCore::udivmod64_32(0x0000000000000010ULL, 0x00000002U, q, r); if (q != 0x00000008U || r != 0x00000000U) return false;
         CppCore::udivmod64_32(0x7FFFFFFFFFFFFFFFULL, 0x80000000U, q, r); if (q != 0xFFFFFFFFU || r != 0x7FFFFFFFU) return false;
         CppCore::udivmod64_32(0x7FFFFFFFFFFFFFFFULL, 0xFFFFFFFFU, q, r); if (q != 0x80000000U || r != 0x7FFFFFFFU) return false;
         CppCore::udivmod64_32(0x00000001FFFFFFFFULL, 0x00000002U, q, r); if (q != 0xFFFFFFFFU || r != 0x00000001U) return false;
         return true;
      }

      INLINE static bool udivmod128_64()
      {
      #if defined(CPPCORE_CPU_X64)
         uint64_t q, r;
         CppCore::udivmod128_64(0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000001ULL, q, r); if (q != 0x0000000000000000ULL || r != 0x0000000000000000ULL) return false;
         CppCore::udivmod128_64(0x0000000000000000ULL, 0x0000000000000001ULL, 0x0000000000000001ULL, q, r); if (q != 0x0000000000000001ULL || r != 0x0000000000000000ULL) return false;
         CppCore::udivmod128_64(0x0000000000000000ULL, 0x0000000000000002ULL, 0x0000000000000003ULL, q, r); if (q != 0x0000000000000000ULL || r != 0x0000000000000002ULL) return false;
         CppCore::udivmod128_64(0x0000000000000000ULL, 0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, q, r); if (q != 0xFFFFFFFFFFFFFFFFULL || r != 0x0000000000000000ULL) return false;
         CppCore::udivmod128_64(0x0000000000000000ULL, 0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, q, r); if (q != 0x0000000000000001ULL || r != 0x0000000000000000ULL) return false;
         CppCore::udivmod128_64(0x0000000000000000ULL, 0x0000000000000010ULL, 0x0000000000000005ULL, q, r); if (q != 0x0000000000000003ULL || r != 0x0000000000000001ULL) return false;
         CppCore::udivmod128_64(0x0000000000000000ULL, 0x0000000000000010ULL, 0x0000000000000002ULL, q, r); if (q != 0x0000000000000008ULL || r != 0x0000000000000000ULL) return false;
         CppCore::udivmod128_64(0x7FFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0x8000000000000000ULL, q, r); if (q != 0xFFFFFFFFFFFFFFFFULL || r != 0x7FFFFFFFFFFFFFFFULL) return false;
         CppCore::udivmod128_64(0x7FFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, q, r); if (q != 0x8000000000000000ULL || r != 0x7FFFFFFFFFFFFFFFULL) return false;
         CppCore::udivmod128_64(0x0000000000000001ULL, 0xFFFFFFFFFFFFFFFFULL, 0x0000000000000002ULL, q, r); if (q != 0xFFFFFFFFFFFFFFFFULL || r != 0x0000000000000001ULL) return false;
         return true;
      #else
         return true;
      #endif
      }

      INLINE static bool udivmod128_128()
      {
      #if defined(CPPCORE_CPU_X64)
         uint64_t qh, ql, rh, rl;
         CppCore::udivmod128_128(0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000001ULL, qh, ql, rh, rl);
         if (qh != 0x0000000000000000ULL || ql != 0x0000000000000000ULL || rh != 0x0000000000000000ULL || rl != 0x0000000000000000ULL) return false;
         CppCore::udivmod128_128(0x0000000000000000ULL, 0x0000000000000001ULL, 0x0000000000000000ULL, 0x0000000000000001ULL, qh, ql, rh, rl);
         if (qh != 0x0000000000000000ULL || ql != 0x0000000000000001ULL || rh != 0x0000000000000000ULL || rl != 0x0000000000000000ULL) return false;
         CppCore::udivmod128_128(0x0000000000000000ULL, 0x0000000000000002ULL, 0x0000000000000000ULL, 0x0000000000000003ULL, qh, ql, rh, rl);
         if (qh != 0x0000000000000000ULL || ql != 0x0000000000000000ULL || rh != 0x0000000000000000ULL || rl != 0x0000000000000002ULL) return false;
         CppCore::udivmod128_128(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 0x0000000000000001ULL, qh, ql, rh, rl);
         if (qh != 0xFFFFFFFFFFFFFFFFULL || ql != 0xFFFFFFFFFFFFFFFFULL || rh != 0x0000000000000000ULL || rl != 0x0000000000000000ULL) return false;
         CppCore::udivmod128_128(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 0x0000000000000002ULL, qh, ql, rh, rl);
         if (qh != 0x7FFFFFFFFFFFFFFFULL || ql != 0xFFFFFFFFFFFFFFFFULL || rh != 0x0000000000000000ULL || rl != 0x0000000000000001ULL) return false;
         CppCore::udivmod128_128(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, qh, ql, rh, rl);
         if (qh != 0x0000000000000000ULL || ql != 0x0000000000000001ULL || rh != 0x0000000000000000ULL || rl != 0x0000000000000000ULL) return false;
         CppCore::udivmod128_128(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0x8000000000000000ULL, 0x0000000000000000ULL, qh, ql, rh, rl);
         if (qh != 0x0000000000000000ULL || ql != 0x0000000000000001ULL || rh != 0x7FFFFFFFFFFFFFFFULL || rl != 0xFFFFFFFFFFFFFFFFULL) return false;

         CppCore::Random::Default64 rnd;
         for (size_t i = 0; i < 10000; i++)
         {
            struct U { uint64_t u[2]; };
            struct V { uint64_t v[2]; };
            U u; u.u[0] = rnd.next(); u.u[1] = rnd.next();
            V v; v.v[0] = rnd.next(); v.v[1] = rnd.next();
            
            U q1, q2;
            V r1, r2;

            CppCore::udivmod(q1, r1, u, v);
            CppCore::udivmod128_128(u.u[1], u.u[0], v.v[1], v.v[0], q2.u[1], q2.u[0], r2.v[1], r2.v[0]);

            if (q1.u[0] != q2.u[0] || q1.u[1] != q2.u[1] || r1.v[0] != r2.v[0] || r1.v[1] != r2.v[1])
               return false;
         }

         return true;
      #else
         return true;
      #endif
      }

      INLINE static bool udivmod16x()
      {
         uint16_t q[2], r[2], u[2], v[2];
         uint16_t vn[2*2];
         uint16_t un[2*(2+1)];

         u[0] = 0xFFFF; u[1] = 0x0000; v[0] = 0xFFFF; v[1] = 0x0000;
         q[0] = 0x0000; q[1] = 0x0000; r[0] = 0x0000; r[1] = 0x0000;
         if (!CppCore::udivmod(q, r, u, v, 1, 1, vn, 2*1, un, 2*(1+1)) || q[0] != 0x0001 || q[1] != 0x0000 || r[0] != 0x0000 || r[1] != 0x0000) return false;

         u[0] = 0x6055; u[1] = 0xA04C; v[0] = 0xFE81; v[1] = 0x83F0;
         q[0] = 0x0000; q[1] = 0x0000; r[0] = 0x0000; r[1] = 0x0000;
         if (!CppCore::udivmod(q, r, u, v, 2, 2, vn, 2*2, un, 2*(2+1)) || q[0] != 0x0001 || q[1] != 0x0000 || r[0] != 0x61D4 || r[1] != 0x1C5B) return false;

         uint64_t q64 = 0;
         uint64_t r64 = 0;
         uint16_t vn64[2*4];
         uint16_t un64[2*(4+1)];
         CppCore::Random::Default64 rnd;

         for (size_t i = 0; i < 10000; i++)
         {
            uint64_t u64 = rnd.next();
            uint64_t v64 = 0;
            while (v64 == 0) v64 = rnd.next();
            q64 = 0;
            r64 = 0;

            if (!CppCore::udivmod((uint16_t*)&q64, (uint16_t*)&r64, (uint16_t*)&u64, (uint16_t*)&v64, 4, 4, vn64, 2*4, un64, 2*(4+1)))
               return false;

            const uint64_t tq = u64 / v64;
            const uint64_t tr = u64 % v64;

            if (q64 != tq)
               return false;

            if (r64 != tr)
               return false;
         }

         return true;
      }

      INLINE static bool udivmod32x()
      {
         struct U64 { uint32_t u[2]; };
         struct V64 { uint32_t v[2]; };

         U64 u64, q64;
         V64 v64, r64;

         u64.u[0] = 0xFFFFFFFF; u64.u[1] = 0x00000000; v64.v[0] = 0xFFFFFFFF; v64.v[1] = 0x00000000;
         q64.u[0] = 0x00000000; q64.u[1] = 0x00000000; r64.v[0] = 0x00000000; r64.v[1] = 0x00000000;
         if (!CppCore::udivmod(q64, r64, u64, v64) || q64.u[0] != 0x00000001 || q64.u[1] != 0x00000000 || r64.v[0] != 0x00000000 || r64.v[1] != 0x00000000) return false;

         u64.u[0] = 0xF2EA8105; u64.u[1] = 0xA8F307C1; v64.v[0] = 0x8BF62367; v64.v[1] = 0x82CE7A02;
         q64.u[0] = 0x00000000; q64.u[1] = 0x00000000; r64.v[0] = 0x00000000; r64.v[1] = 0x00000000;
         if (!CppCore::udivmod(q64, r64, u64, v64) || q64.u[0] != 0x00000001 || q64.u[1] != 0x00000000 || r64.v[0] != 0x66F45D9E || r64.v[1] != 0x26248DBF) return false;

         CppCore::Random::Default32 rnd;

         for (size_t i = 0; i < 10000; i++)
         {
            U64 u64;
            u64.u[0] = rnd.next();
            u64.u[1] = rnd.next();
            V64 v64;
            v64.v[0] = 0;
            v64.v[1] = 0;
            while (v64.v[0] == 0) v64.v[0] = rnd.next();
            v64.v[1] = rnd.next();

            if (!CppCore::udivmod(q64, r64, u64, v64))
               return false;

            const uint64_t tq = *(uint64_t*)&u64 / *(uint64_t*)&v64;
            const uint64_t tr = *(uint64_t*)&u64 % *(uint64_t*)&v64;

            if (*(uint64_t*)&q64 != tq)
               return false;

            if (*(uint64_t*)&r64 != tr)
               return false;
         }

         return true;
      }

      template<typename UINT1, typename UINT2>
      INLINE static bool udivmod(const size_t loops)
      {
         static_assert(sizeof(UINT1) % 4 == 0);
         static_assert(sizeof(UINT2) % 4 == 0);
         constexpr size_t N32UINT1 = sizeof(UINT1) / 4;
         constexpr size_t N32UINT2 = sizeof(UINT2) / 4;
         constexpr size_t N16UINT1 = sizeof(UINT1) / 2;
         constexpr size_t N16UINT2 = sizeof(UINT2) / 2;
         CppCore::Random::Default32 rnd;
         UINT1     u, q1, q2;
         UINT2     v, r1, r2;
         UINT1     mem[2];
         bool      ret1, ret2;
         uint16_t  un[N16UINT1+1];
         uint16_t  vn[N16UINT2];
         uint32_t* up = (uint32_t*)&u;
         uint32_t* vp = (uint32_t*)&v;
         for (size_t j = 0; j < loops; j++)
         {
            // generate randoms
            for (size_t i = 0; i < N32UINT1; i++)
               up[i] = rnd.next();
            do { vp[0] = rnd.next(); } while (vp[0] == 0);
            for (size_t i = 1; i < N32UINT2; i++)
               vp[i] = rnd.next();

            // the reference implementation
            ::memset(&q1, 0, sizeof(q1));
            ::memset(&r1, 0, sizeof(r1));
            ret1 = CppCore::udivmod((uint16_t*)&q1, (uint16_t*)&r1, (uint16_t*)&u, (uint16_t*)&v, N16UINT1, N16UINT2, vn, N16UINT2, un, N16UINT1+1);

            // the optimized one
            ret2 = CppCore::udivmod<UINT1, UINT2>(q2, r2, u, v, mem);

            // compare
            if (ret1 != ret2)
               return false;
            if (::memcmp(&q1, &q2, sizeof(UINT1)) != 0)
               return false;
            if (::memcmp(&r1, &r2, sizeof(UINT2)) != 0)
               return false;
         }
         return true;
      }

      template<typename UINT1, typename UINT2>
      INLINE static bool umod(const size_t loops)
      {
         static_assert(sizeof(UINT1) % 4 == 0);
         static_assert(sizeof(UINT2) % 4 == 0);
         constexpr size_t N32UINT1 = sizeof(UINT1) / 4;
         constexpr size_t N32UINT2 = sizeof(UINT2) / 4;
         constexpr size_t N16UINT1 = sizeof(UINT1) / 2;
         constexpr size_t N16UINT2 = sizeof(UINT2) / 2;
         CppCore::Random::Default32 rnd;
         UINT1     u, q1, q2;
         UINT2     v, r1, r2;
         UINT1     mem[2];
         uint16_t  un[N16UINT1+1];
         uint16_t  vn[N16UINT2];
         uint32_t* up = (uint32_t*)&u;
         uint32_t* vp = (uint32_t*)&v;
         for (size_t j = 0; j < loops; j++)
         {
            // generate randoms
            for (size_t i = 0; i < N32UINT1; i++)
               up[i] = rnd.next();
            do { vp[0] = rnd.next(); } while (vp[0] == 0);
            for (size_t i = 1; i < N32UINT2; i++)
               vp[i] = rnd.next();

            // the reference implementation
            ::memset(&q1, 0, sizeof(q1));
            ::memset(&r1, 0, sizeof(r1));
            CppCore::udivmod((uint16_t*)&q1, (uint16_t*)&r1, (uint16_t*)&u, (uint16_t*)&v, N16UINT1, N16UINT2, vn, N16UINT2, un, N16UINT1+1);

            // the optimized one
            CppCore::umod<UINT1, UINT2>(r2, u, v, mem);

            // compare
            if (::memcmp(&r1, &r2, sizeof(UINT2)) != 0)
               return false;
         }
         return true;
      }

      INLINE static bool ismersenne32()
      {
         if (CppCore::ismersenne32(0) != 0)
            return false;
         for (uint32_t i = 1; i < 32; i++)
            if (CppCore::ismersenne32((1U << i) - 1U) != i)
               return false;
         if (CppCore::ismersenne32(0xFFFFFFFFU) != 32)
            return false;
         return true;
      }

      INLINE static bool ismersenne64()
      {
         if (CppCore::ismersenne64(0) != 0)
            return false;
         for (uint64_t i = 1; i < 64; i++)
            if (CppCore::ismersenne64((1ULL << i) - 1ULL) != i)
               return false;
         if (CppCore::ismersenne64(0xFFFFFFFFFFFFFFFFULL) != 64)
            return false;
         return true;
      }

      INLINE static bool ismersenne128()
      {
         if (CppCore::ismersenne(uint128_t(0)) != 0U)
            return false;
         for (size_t i = 1; i < 128; i++)
            if (CppCore::ismersenne(((uint128_t(1) << i) - (uint64_t)1)) != i)
               return false;
         if (CppCore::ismersenne(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) != 128U)
            return false;
         return true;
      }

      INLINE static bool clmul32()
      {
         uint32_t r;
         CppCore::clmul(0x00000000U, 0x00000000U, r); if (r != 0x00000000U) return false;
         CppCore::clmul(0x00000001U, 0x00000000U, r); if (r != 0x00000000U) return false;
         CppCore::clmul(0x00000000U, 0x00000001U, r); if (r != 0x00000000U) return false;
         CppCore::clmul(0x00000001U, 0x00000001U, r); if (r != 0x00000001U) return false;          
         CppCore::clmul(0x00000002U, 0x00000003U, r); if (r != 0x00000006U) return false;
         CppCore::clmul(0x726f6e5dU, 0x5d53475dU, r); if (r != 0xd36f0451U) return false;
         CppCore::clmul(0x68617929U, 0x5d53475dU, r); if (r != 0x2a281315U) return false;
         CppCore::clmul(0x726f6e5dU, 0x73745665U, r); if (r != 0xf4b7d5c9U) return false;
         CppCore::clmul(0x68617929U, 0x73745665U, r); if (r != 0x410fd4edU) return false;
         return true;
      }

      INLINE static bool clmul64()
      {
         uint64_t r;
         CppCore::clmul((uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000000ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::clmul((uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000000ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::clmul((uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::clmul((uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000001ULL, r); if (r != (uint64_t)0x0000000000000001ULL) return false;
         CppCore::clmul((uint64_t)0x0000000000000002ULL, (uint64_t)0x0000000000000003ULL, r); if (r != (uint64_t)0x0000000000000006ULL) return false;
         CppCore::clmul((uint64_t)0x5b477565726f6e5dULL, (uint64_t)0x63746f725d53475dULL, r); if (r != (uint64_t)0x929633d5d36f0451ULL) return false;
         CppCore::clmul((uint64_t)0x4869285368617929ULL, (uint64_t)0x63746f725d53475dULL, r); if (r != (uint64_t)0x7fa540ac2a281315ULL) return false;
         CppCore::clmul((uint64_t)0x5b477565726f6e5dULL, (uint64_t)0x7b5b546573745665ULL, r); if (r != (uint64_t)0xbabf262df4b7d5c9ULL) return false;
         CppCore::clmul((uint64_t)0x4869285368617929ULL, (uint64_t)0x7b5b546573745665ULL, r); if (r != (uint64_t)0xd66ee03e410fd4edULL) return false;
         return true;
      }

      INLINE static bool clmul64to128()
      {
         uint64_t r[2];
         CppCore::clmul((uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000000ULL, r); if (r[0] != (uint64_t)0x0000000000000000ULL || r[1] != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::clmul((uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000000ULL, r); if (r[0] != (uint64_t)0x0000000000000000ULL || r[1] != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::clmul((uint64_t)0x0000000000000000ULL, (uint64_t)0x0000000000000001ULL, r); if (r[0] != (uint64_t)0x0000000000000000ULL || r[1] != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::clmul((uint64_t)0x0000000000000001ULL, (uint64_t)0x0000000000000001ULL, r); if (r[0] != (uint64_t)0x0000000000000001ULL || r[1] != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::clmul((uint64_t)0x0000000000000002ULL, (uint64_t)0x0000000000000003ULL, r); if (r[0] != (uint64_t)0x0000000000000006ULL || r[1] != (uint64_t)0x0000000000000000ULL) return false;
         CppCore::clmul((uint64_t)0x5b477565726f6e5dULL, (uint64_t)0x63746f725d53475dULL, r); if (r[0] != (uint64_t)0x929633d5d36f0451ULL || r[1] != (uint64_t)0x1d4d84c85c3440c0ULL) return false;
         CppCore::clmul((uint64_t)0x4869285368617929ULL, (uint64_t)0x63746f725d53475dULL, r); if (r[0] != (uint64_t)0x7fa540ac2a281315ULL || r[1] != (uint64_t)0x1bd17c8d556ab5a1ULL) return false;
         CppCore::clmul((uint64_t)0x5b477565726f6e5dULL, (uint64_t)0x7b5b546573745665ULL, r); if (r[0] != (uint64_t)0xbabf262df4b7d5c9ULL || r[1] != (uint64_t)0x1a2bf6db3a30862fULL) return false;
         CppCore::clmul((uint64_t)0x4869285368617929ULL, (uint64_t)0x7b5b546573745665ULL, r); if (r[0] != (uint64_t)0xd66ee03e410fd4edULL || r[1] != (uint64_t)0x1d1e1f2c592e7c45ULL) return false;
         return true;
      }

      INLINE static bool clmul128()
      {
         uint64_t a[2];
         uint64_t b[2];
         uint64_t r[2];

         a[0] = 0x5b477565726f6e5dULL; a[1] = 0x63746f725d53475dULL;
         b[0] = 0x4869285368617929ULL; b[1] = 0x7b5b546573745665ULL;
         CppCore::clmul(a, b, r);
         if (r[0] != 0xDD4DF8F142E15215ULL) return false;
         if (r[1] != 0xD10EB19DC031B4CEULL) return false;

         return true;
      }

      INLINE static bool clmul128to256()
      {
         uint64_t a[2];
         uint64_t b[2];
         uint64_t r[4];

         a[0] = 0x5b477565726f6e5dULL; a[1] = 0x63746f725d53475dULL;
         b[0] = 0x4869285368617929ULL; b[1] = 0x7b5b546573745665ULL;
         CppCore::clmul(a, b, r);
         if (r[0] != 0xDD4DF8F142E15215ULL) return false;
         if (r[1] != 0xD10EB19DC031B4CEULL) return false;
         if (r[2] != 0x3FFA51F634880B47ULL) return false;
         if (r[3] != 0x1127A41FDF07AF62ULL) return false;

         return true;
      }

      INLINE static bool todouble()
      {
         // test low ones
         for (uint64_t i = 0; i <= 0x0000000000FFFFFFULL; i++)
         {
            double d1 = CppCore::todouble(i);
            double d2 = (double)i;
            if (d1 != d2)
               return false;
         }

         // test some high ones (for rounding)
         for (uint64_t i = 0xFFFFFFFFFFFFFFFFULL; i >= 0xFFFFFFFFFF000000ULL; i--)
         {
            double d1 = CppCore::todouble(i);
            double d2 = (double)i;
            if (d1 != d2)
               return false;
         }

         bool specials =
            CppCore::todouble(0x0010000000000000ULL) == (double)0x0010000000000000ULL &&
            CppCore::todouble(0x001FFFFFFFFFFFFFULL) == (double)0x001FFFFFFFFFFFFFULL &&
            CppCore::todouble(0x0020000000000000ULL) == (double)0x0020000000000000ULL &&
            CppCore::todouble(0x0020000000000001ULL) == (double)0x0020000000000001ULL &&
            CppCore::todouble(0x0040000000000000ULL) == (double)0x0040000000000000ULL &&
            CppCore::todouble(0x0080000000000000ULL) == (double)0x0080000000000000ULL &&
            CppCore::todouble(0x0100000000000000ULL) == (double)0x0100000000000000ULL &&
            CppCore::todouble(0x0200000000000000ULL) == (double)0x0200000000000000ULL &&
            CppCore::todouble(0x0400000000000000ULL) == (double)0x0400000000000000ULL;

         if (!specials)
            return false;

         // test some random ones
         CppCore::Random::Default64 rnd;
         for (size_t i = 0; i < 100000; i++)
         {
            uint64_t r = rnd.next();
            double d1 = CppCore::todouble(r);
            double d2 = (double)r;
            if (d1 != d2)
               return false;
         }
         return true;
      }

      INLINE static bool gcd32()
      {
         return
            CppCore::gcd32(0U,  0U)  == 0U &&
            CppCore::gcd32(1U,  0U)  == 1U &&
            CppCore::gcd32(7U,  5U)  == 1U &&
            CppCore::gcd32(20U, 16U) == 4U;
      }

      INLINE static bool gcd64()
      {
         return
            CppCore::gcd64(0ULL,   0ULL) == 0ULL &&
            CppCore::gcd64(1ULL,   0ULL) == 1ULL &&
            CppCore::gcd64(7ULL,   5ULL) == 1ULL &&
            CppCore::gcd64(20ULL, 16ULL) == 4ULL;
      }

      INLINE static bool gcd()
      {
         const uint128_t l1 = uint128_t("2687293461875176346985679234");
         const uint128_t l2 = l1 * 3;

         bool t128 =
            CppCore::gcd(uint128_t(0), uint128_t(0)) == 0U &&
            CppCore::gcd(uint128_t(1), uint128_t(0)) == 1U &&
            CppCore::gcd(uint128_t(7), uint128_t(5)) == 1U &&
            CppCore::gcd(uint128_t(20), uint128_t(16)) == 4U &&
            CppCore::gcd(uint128_t(CppCore::Primes::MERSENNE128), uint128_t(CppCore::Primes::LARGE128)) == 1U &&
            CppCore::gcd(l1, l2) == l1;

         return t128;
      }
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Math {
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(Util)
   {
   public:
      TEST_METHOD(GETBITS32)        { Assert::AreEqual(true, CppCore::Test::Math::Util::getbits32()); }
      TEST_METHOD(GETBITS64)        { Assert::AreEqual(true, CppCore::Test::Math::Util::getbits64()); }
      TEST_METHOD(UNSETBITS32)      { Assert::AreEqual(true, CppCore::Test::Math::Util::unsetbits32()); }
      TEST_METHOD(UNSETBITS64)      { Assert::AreEqual(true, CppCore::Test::Math::Util::unsetbits64()); }
      TEST_METHOD(SETBIT32)         { Assert::AreEqual(true, CppCore::Test::Math::Util::setbit32()); }
      TEST_METHOD(SETBIT64)         { Assert::AreEqual(true, CppCore::Test::Math::Util::setbit64()); }
      TEST_METHOD(SETBITS32)        { Assert::AreEqual(true, CppCore::Test::Math::Util::setbits32()); }
      TEST_METHOD(SETBITS64)        { Assert::AreEqual(true, CppCore::Test::Math::Util::setbits64()); }
      TEST_METHOD(RDOWNPTWO32)      { Assert::AreEqual(true, CppCore::Test::Math::Util::rdownptwo32()); }
      TEST_METHOD(RDOWNPTWO64)      { Assert::AreEqual(true, CppCore::Test::Math::Util::rdownptwo64()); }
      TEST_METHOD(RUPPTWO32)        { Assert::AreEqual(true, CppCore::Test::Math::Util::rupptwo32()); }
      TEST_METHOD(RUPPTWO64)        { Assert::AreEqual(true, CppCore::Test::Math::Util::rupptwo64()); }
      TEST_METHOD(RDOWN32)          { Assert::AreEqual(true, CppCore::Test::Math::Util::rdown32()); }
      TEST_METHOD(RDOWN64)          { Assert::AreEqual(true, CppCore::Test::Math::Util::rdown64()); }
      TEST_METHOD(RUP32)            { Assert::AreEqual(true, CppCore::Test::Math::Util::rup32()); }
      TEST_METHOD(RUP64)            { Assert::AreEqual(true, CppCore::Test::Math::Util::rup64()); }
      TEST_METHOD(ROUND32)          { Assert::AreEqual(true, CppCore::Test::Math::Util::round32()); }
      TEST_METHOD(ROUND64)          { Assert::AreEqual(true, CppCore::Test::Math::Util::round64()); }
      TEST_METHOD(NGPTWO32)         { Assert::AreEqual(true, CppCore::Test::Math::Util::ngptwo32()); }
      TEST_METHOD(NGPTWO64)         { Assert::AreEqual(true, CppCore::Test::Math::Util::ngptwo64()); }
      TEST_METHOD(NLPTWO32)         { Assert::AreEqual(true, CppCore::Test::Math::Util::nlptwo32()); }
      TEST_METHOD(NLPTWO64)         { Assert::AreEqual(true, CppCore::Test::Math::Util::nlptwo64()); }
      TEST_METHOD(ADDCARRY32)       { Assert::AreEqual(true, CppCore::Test::Math::Util::addcarry32()); }
      TEST_METHOD(ADDCARRY64)       { Assert::AreEqual(true, CppCore::Test::Math::Util::addcarry64()); }
      TEST_METHOD(SUBBORROW32)      { Assert::AreEqual(true, CppCore::Test::Math::Util::subborrow32()); }
      TEST_METHOD(SUBBORROW64)      { Assert::AreEqual(true, CppCore::Test::Math::Util::subborrow64()); }
      TEST_METHOD(MUL128)           { Assert::AreEqual(true, CppCore::Test::Math::Util::mul128()); }
      TEST_METHOD(OVERFLOWADD16)    { Assert::AreEqual(true, CppCore::Test::Math::Util::overflowadd16()); }
      TEST_METHOD(OVERFLOWADD32)    { Assert::AreEqual(true, CppCore::Test::Math::Util::overflowadd32()); }
      TEST_METHOD(OVERFLOWADD64)    { Assert::AreEqual(true, CppCore::Test::Math::Util::overflowadd64()); }
      TEST_METHOD(OVERFLOWSUB16)    { Assert::AreEqual(true, CppCore::Test::Math::Util::overflowsub16()); }
      TEST_METHOD(OVERFLOWSUB32)    { Assert::AreEqual(true, CppCore::Test::Math::Util::overflowsub32()); }
      TEST_METHOD(OVERFLOWSUB64)    { Assert::AreEqual(true, CppCore::Test::Math::Util::overflowsub64()); }
      TEST_METHOD(OVERFLOWMUL16)    { Assert::AreEqual(true, CppCore::Test::Math::Util::overflowmul16()); }
      TEST_METHOD(OVERFLOWMUL32)    { Assert::AreEqual(true, CppCore::Test::Math::Util::overflowmul32()); }
      TEST_METHOD(OVERFLOWMUL64)    { Assert::AreEqual(true, CppCore::Test::Math::Util::overflowmul64()); }
      TEST_METHOD(UMOD)             { Assert::AreEqual(true, CppCore::Test::Math::Util::umod()); }
      TEST_METHOD(UMULMOD32)        { Assert::AreEqual(true, CppCore::Test::Math::Util::umulmod32()); }
      TEST_METHOD(UMULMOD64)        { Assert::AreEqual(true, CppCore::Test::Math::Util::umulmod64()); }
      TEST_METHOD(UPOWMOD32)        { Assert::AreEqual(true, CppCore::Test::Math::Util::upowmod32()); }
      TEST_METHOD(UPOWMOD64)        { Assert::AreEqual(true, CppCore::Test::Math::Util::upowmod64()); }
      TEST_METHOD(UPOW32)           { Assert::AreEqual(true, CppCore::Test::Math::Util::upow32()); }
      TEST_METHOD(UPOW64)           { Assert::AreEqual(true, CppCore::Test::Math::Util::upow64()); }
      TEST_METHOD(UDIVMOD32)        { Assert::AreEqual(true, CppCore::Test::Math::Util::udivmod32()); }
      TEST_METHOD(UDIVMOD64)        { Assert::AreEqual(true, CppCore::Test::Math::Util::udivmod64()); }
      TEST_METHOD(UDIVMOD64_32)     { Assert::AreEqual(true, CppCore::Test::Math::Util::udivmod64_32()); }
      TEST_METHOD(UDIVMOD128_64)    { Assert::AreEqual(true, CppCore::Test::Math::Util::udivmod128_64()); }
      TEST_METHOD(UDIVMOD128_128)   { Assert::AreEqual(true, CppCore::Test::Math::Util::udivmod128_128()); }
      TEST_METHOD(UDIVMOD256_64)    { Assert::AreEqual(true, CppCore::Test::Math::Util::udivmod<uint256_t, uint64_t> (100000)); }
      TEST_METHOD(UDIVMOD256_128)   { Assert::AreEqual(true, CppCore::Test::Math::Util::udivmod<uint256_t, uint128_t>(100000)); }
      TEST_METHOD(UDIVMOD256_256)   { Assert::AreEqual(true, CppCore::Test::Math::Util::udivmod<uint256_t, uint256_t>(100000)); }
      TEST_METHOD(UMOD256_64)       { Assert::AreEqual(true, CppCore::Test::Math::Util::umod<uint256_t, uint64_t> (100000)); }
      TEST_METHOD(UMOD256_128)      { Assert::AreEqual(true, CppCore::Test::Math::Util::umod<uint256_t, uint128_t>(100000)); }
      TEST_METHOD(UMOD256_256)      { Assert::AreEqual(true, CppCore::Test::Math::Util::umod<uint256_t, uint256_t>(100000)); }
      TEST_METHOD(UDIVMOD16X)       { Assert::AreEqual(true, CppCore::Test::Math::Util::udivmod16x()); }
      TEST_METHOD(UDIVMOD32X)       { Assert::AreEqual(true, CppCore::Test::Math::Util::udivmod32x()); }
      TEST_METHOD(ISMERSENNE32)     { Assert::AreEqual(true, CppCore::Test::Math::Util::ismersenne32()); }
      TEST_METHOD(ISMERSENNE64)     { Assert::AreEqual(true, CppCore::Test::Math::Util::ismersenne64()); }
      TEST_METHOD(ISMERSENNE128)    { Assert::AreEqual(true, CppCore::Test::Math::Util::ismersenne128()); }
      TEST_METHOD(CLMUL32)          { Assert::AreEqual(true, CppCore::Test::Math::Util::clmul32()); }
      TEST_METHOD(CLMUL64)          { Assert::AreEqual(true, CppCore::Test::Math::Util::clmul64()); }
      TEST_METHOD(CLMUL64TO128)     { Assert::AreEqual(true, CppCore::Test::Math::Util::clmul64to128()); }
      TEST_METHOD(CLMUL128)         { Assert::AreEqual(true, CppCore::Test::Math::Util::clmul128()); }
      TEST_METHOD(CLMUL128TO256)    { Assert::AreEqual(true, CppCore::Test::Math::Util::clmul128to256()); }
      TEST_METHOD(TODOUBLE)         { Assert::AreEqual(true, CppCore::Test::Math::Util::todouble()); }
      TEST_METHOD(GCD32)            { Assert::AreEqual(true, CppCore::Test::Math::Util::gcd32()); }
      TEST_METHOD(GCD64)            { Assert::AreEqual(true, CppCore::Test::Math::Util::gcd64()); }
      TEST_METHOD(GCD)              { Assert::AreEqual(true, CppCore::Test::Math::Util::gcd()); }
   };
}}}}
#endif
