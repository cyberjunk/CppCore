#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Math
{
   /// <summary>
   /// Tests for BigInt.h in CppCore::Math
   /// </summary>
   class BigInt
   {
   public:
      INLINE static bool eq128()
      {
         return
            uint128_t::Op::eq(uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL), uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) &&
            uint128_t::Op::eq(uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) &&
            uint128_t::Op::eq(uint128_t(0x0000000000000000ULL, 0x0000000000000001ULL), uint128_t(0x0000000000000000ULL, 0x0000000000000001ULL)) &&
            uint128_t::Op::eq(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) &&
            uint128_t::Op::eq(uint128_t(0xF5AA29EC8310BF03ULL, 0xF79164BC1A972E86ULL), uint128_t(0xF5AA29EC8310BF03ULL, 0xF79164BC1A972E86ULL)) &&
           !uint128_t::Op::eq(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) &&
           !uint128_t::Op::eq(uint128_t(0xF5AA29EC8310BF00ULL, 0xF79164BC1A972E86ULL), uint128_t(0xF5AA29EC8310BF03ULL, 0xF79164BC1A972E86ULL)) &&
           !uint128_t::Op::eq(uint128_t(0xF5AA29EC8310BF03ULL, 0xF79164BC1A972E86ULL), uint128_t(0xF5AA29EC8310BF03ULL, 0xF79164BC1A972E80ULL));
      }
      INLINE static bool popcnt128()
      {
         uint32_t r;
         uint128_t::Op::popcnt(uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL), r); if (r != 0U)   return false;
         uint128_t::Op::popcnt(uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), r); if (r != 1U)   return false;
         uint128_t::Op::popcnt(uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL), r); if (r != 1U)   return false;
         uint128_t::Op::popcnt(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), r); if (r != 128U) return false;
         return true;
      }
      INLINE static bool tzcnt128()
      {
         uint32_t r;
         uint128_t::Op::tzcnt(uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL), r); if (r != 128U) return false;
         uint128_t::Op::tzcnt(uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), r); if (r != 0U)   return false;
         uint128_t::Op::tzcnt(uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL), r); if (r != 127U) return false;
         return true;
      }
      INLINE static bool lzcnt128()
      {
         uint32_t r;
         uint128_t::Op::lzcnt(uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL), r); if (r != 128U) return false;
         uint128_t::Op::lzcnt(uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), r); if (r != 127U) return false;
         uint128_t::Op::lzcnt(uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL), r); if (r != 0U)   return false;
         return true;
      }
      INLINE static bool getbit128()
      {
         bool r;
         uint128_t::Op::getbitat(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), 0,  r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), 127,r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), 0,  r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL), 127,r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0x8000000000000000ULL, 0x0000000000000000ULL), 63, r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL), 0,  r); if (r != false) return false;
         uint128_t::Op::getbitat(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL), 64, r); if (r != false) return false;
         uint128_t::Op::getbitat(uint128_t(0xC56EA10BF0BC30FFULL, 0xC56EA10BF0BC30FFULL), 0,  r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0xC56EA10BF0BC30FFULL, 0xC56EA10BF0BC30FFULL), 64, r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0xC56EA10BF0BC30FFULL, 0xC56EA10BF0BC30FFULL), 1,  r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0xC56EA10BF0BC30FFULL, 0xC56EA10BF0BC30FFULL), 65, r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0xC56EA10BF0BC30FFULL, 0xC56EA10BF0BC30FFULL), 2,  r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0xC56EA10BF0BC30FFULL, 0xC56EA10BF0BC30FFULL), 66, r); if (r != true)  return false;
         uint128_t::Op::getbitat(uint128_t(0xC56EA10BF0BC30FFULL, 0xC56EA10BF0BC30FFULL), 15, r); if (r != false) return false;
         uint128_t::Op::getbitat(uint128_t(0xC56EA10BF0BC30FFULL, 0xC56EA10BF0BC30FFULL), 79, r); if (r != false) return false;
         uint128_t::Op::getbitat(uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), 128,r); if (r != true)  return false;
         return true;
      }
      INLINE static bool setbit128()
      {
         uint128_t r;
         r = uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL); uint128_t::Op::setbitat(r, 0,   false); if (r != uint128_t(0xFFFFFFFFFFFFFFFEULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         r = uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL); uint128_t::Op::setbitat(r, 127, false); if (r != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x7FFFFFFFFFFFFFFFULL)) return false;
         r = uint128_t(0x8000000000000000ULL, 0x0000000000000000ULL); uint128_t::Op::setbitat(r, 63,  false); if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL); uint128_t::Op::setbitat(r, 127, false); if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL); uint128_t::Op::setbitat(r, 0,   true);  if (r != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL); uint128_t::Op::setbitat(r, 127, true);  if (r != uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL); uint128_t::Op::setbitat(r, 128, true);  if (r != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         return true;
      }
      INLINE static bool byteswap128()
      {
         uint128_t r;
         r = uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL); uint128_t::Op::byteswap(r); if (r != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL); uint128_t::Op::byteswap(r); if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL); uint128_t::Op::byteswap(r); if (r != uint128_t(0x0000000000000000ULL, 0x0100000000000000ULL)) return false;
         r = uint128_t(0x0706050403020100ULL, 0x0F0E0D0C0B0A0908ULL); uint128_t::Op::byteswap(r); if (r != uint128_t(0x08090A0B0C0D0E0FULL, 0x0001020304050607ULL)) return false;
         return true;
      }
      INLINE static bool shl128()
      {
         uint128_t r;
         r = uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL); uint128_t::Op::shl(r, 1);   if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL); uint128_t::Op::shl(r, 1);   if (r != uint128_t(0x0000000000000002ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL); uint128_t::Op::shl(r, 127); if (r != uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL); uint128_t::Op::shl(r, 1);   if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL); uint128_t::Op::shl(r, 129); if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL); uint128_t::Op::shl(r, 128); if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x7A2B82EE31C9F031ULL, 0x7A2B82EE31C9F031ULL); uint128_t::Op::shl(r, 0);   if (r != uint128_t(0x7A2B82EE31C9F031ULL, 0x7A2B82EE31C9F031ULL)) return false;
         return true;
      }
      INLINE static bool shr128()
      {
         uint128_t r;
         r = uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL); uint128_t::Op::shr(r, 1);   if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL); uint128_t::Op::shr(r, 1);   if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL); uint128_t::Op::shr(r, 127); if (r != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL); uint128_t::Op::shr(r, 1);   if (r != uint128_t(0x0000000000000000ULL, 0x4000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL); uint128_t::Op::shr(r, 129); if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL); uint128_t::Op::shr(r, 128); if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x7A2B82EE31C9F031ULL, 0x7A2B82EE31C9F031ULL); uint128_t::Op::shr(r, 0);   if (r != uint128_t(0x7A2B82EE31C9F031ULL, 0x7A2B82EE31C9F031ULL)) return false;
         return true;
      }
      INLINE static bool rotl128()
      {
         uint128_t r;
         r = uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL); uint128_t::Op::rotl(r, 1);   if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL); uint128_t::Op::rotl(r, 1);   if (r != uint128_t(0x0000000000000002ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL); uint128_t::Op::rotl(r, 127); if (r != uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL); uint128_t::Op::rotl(r, 1);   if (r != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL); uint128_t::Op::rotl(r, 129); if (r != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL); uint128_t::Op::rotl(r, 128); if (r != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         r = uint128_t(0x7A2B82EE31C9F031ULL, 0x7A2B82EE31C9F031ULL); uint128_t::Op::rotl(r, 0);   if (r != uint128_t(0x7A2B82EE31C9F031ULL, 0x7A2B82EE31C9F031ULL)) return false;
         return true;
      }
      INLINE static bool rotr128()
      {
         uint128_t r;
         r = uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL); uint128_t::Op::rotr(r, 1);   if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL); uint128_t::Op::rotr(r, 1);   if (r != uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL); uint128_t::Op::rotr(r, 127); if (r != uint128_t(0x0000000000000002ULL, 0x0000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL); uint128_t::Op::rotr(r, 1);   if (r != uint128_t(0x0000000000000000ULL, 0x4000000000000000ULL)) return false;
         r = uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL); uint128_t::Op::rotr(r, 129); if (r != uint128_t(0x0000000000000000ULL, 0x4000000000000000ULL)) return false;
         r = uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL); uint128_t::Op::rotr(r, 128); if (r != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         r = uint128_t(0x7A2B82EE31C9F031ULL, 0x7A2B82EE31C9F031ULL); uint128_t::Op::rotr(r, 0);   if (r != uint128_t(0x7A2B82EE31C9F031ULL, 0x7A2B82EE31C9F031ULL)) return false;
         return true;
      }
      INLINE static bool mul128()
      {
         uint128_t r;
         uint128_t::Op::mul(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), r); if (r != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         uint128_t::Op::mul(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL), uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL), r); if (r != uint128_t(0x0000000000000001ULL, 0xFFFFFFFFFFFFFFFEULL)) return false;
         uint128_t::Op::mul(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL), uint128_t(0x0000000000000002ULL, 0x0000000000000000ULL), r); if (r != uint128_t(0xFFFFFFFFFFFFFFFEULL, 0x0000000000000001ULL)) return false;
         uint128_t::Op::mul(uint128_t(0x00000000BD35ACFFULL, 0x0000000000000000ULL), uint128_t(0x00000000005F7832ULL, 0x0000000000000000ULL), r); if (r != uint128_t(0x00468FC1503451CEULL, 0x0000000000000000ULL)) return false;
         uint128_t::Op::mul(uint128_t(0x0000000BD35ACFF0ULL, 0x0000000000000000ULL), uint128_t(0x0000000005F78320ULL, 0x0000000000000000ULL), r); if (r != uint128_t(0x468FC1503451CE00ULL, 0x0000000000000000ULL)) return false;
         uint128_t::Op::mul(uint128_t(0x0000000000000000ULL, 0x0000000000000001ULL), uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), r); if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000001ULL)) return false;
         uint128_t::Op::mul(uint128_t(0x0000000000000000ULL, 0x0000000000000001ULL), uint128_t(0x0000000000000002ULL, 0x0000000000000000ULL), r); if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000002ULL)) return false;
         uint128_t::Op::mul(uint128_t(0x0000000000000000ULL, 0x0000000000000001ULL), uint128_t(0x0000000000000000ULL, 0x0000000000000001ULL), r); if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         uint128_t::Op::mul(uint128_t(0x0000000000000006ULL, 0x0000000000000000ULL), uint128_t(0x000000000000000AULL, 0x0000000000000000ULL), r); if (r != uint128_t(0x000000000000003CULL, 0x0000000000000000ULL)) return false;
         return true;
      }
      INLINE static bool mulw128()
      {
         uint128_t r128[2];
         uint128_t::Op::mulw(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), &r128[0].d.l);
         if (r128[0] != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         if (r128[1] != uint128_t(0xFFFFFFFFFFFFFFFEULL, 0xFFFFFFFFFFFFFFFFULL)) return false;

         uint256_t r256;
         uint128_t::Op::mulw(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), &r256.d.l.d.l);
         if (r256.d.l != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         if (r256.d.h != uint128_t(0xFFFFFFFFFFFFFFFEULL, 0xFFFFFFFFFFFFFFFFULL)) return false;

         return true;
      }
      INLINE static bool divmod128()
      {
         uint128_t q, r;

         uint128_t::Op::divmod(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), q, r);
         if (q != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;

         uint128_t::Op::divmod(uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL), uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL), q, r);
         if (q != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;

         uint128_t::Op::divmod(uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL), uint128_t(0x0000000000000002ULL, 0x0000000000000000ULL), q, r);
         if (q != uint128_t(0x0000000000000000ULL, 0x4000000000000000ULL)) return false;
         if (r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;

         uint128_t::Op::divmod(uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL), uint128_t(0x000000000000000AULL, 0x0000000000000000ULL), q, r);
         if (q != uint128_t(0x0000000019999999ULL, 0x0000000000000000ULL)) return false;
         if (r != uint128_t(0x0000000000000005ULL, 0x0000000000000000ULL)) return false;
         
         uint128_t::Op::divmod(uint128_t(0x0000000019999999ULL, 0x0000000000000000ULL), uint128_t(0x000000000000000AULL, 0x0000000000000000ULL), q, r);
         if (q != uint128_t(0x00000000028F5C28ULL, 0x0000000000000000ULL)) return false;
         if (r != uint128_t(0x0000000000000009ULL, 0x0000000000000000ULL)) return false;

         return true;
      }
      INLINE static bool sqrt128()
      {
         uint128_t r;

         uint128_t::Op::sqrt(uint128_t(9U), r);
         if (r != uint128_t(3U)) return false;

         uint128_t::Op::sqrt(uint128_t("340282366920938463463374607431768211455"), r);
         if (r != uint128_t("18446744073709551615")) return false;

         return true;
      }
      INLINE static bool todouble128()
      {
         /*
         // test low 64-bit ones that can be tested with double chast
         for (uint64_t i = 0; i <= 0x000000000000FFFFULL; i++)
         {
            double d1 = (double)uint128_t(i);
            double d2 = (double)i;
            if (d1 != d2)
               return false;
         }

         // test some high 64-bit ones (for rounding) that can be tested with double chast
         for (uint64_t i = 0xFFFFFFFFFFFFFFFFULL; i >= 0xFFFFFFFFFFFF0000ULL; i--)
         {
            double d1 = (double)uint128_t(i);
            double d2 = (double)i;
            if (d1 != d2)
               return false;
         }

         bool specials64 =
            (double)uint128_t(0x0010000000000000ULL) == (double)0x0010000000000000ULL &&
            (double)uint128_t(0x001FFFFFFFFFFFFFULL) == (double)0x001FFFFFFFFFFFFFULL &&
            (double)uint128_t(0x0020000000000000ULL) == (double)0x0020000000000000ULL &&
            (double)uint128_t(0x0020000000000001ULL) == (double)0x0020000000000001ULL &&
            (double)uint128_t(0x0040000000000000ULL) == (double)0x0040000000000000ULL &&
            (double)uint128_t(0x0080000000000000ULL) == (double)0x0080000000000000ULL &&
            (double)uint128_t(0x0100000000000000ULL) == (double)0x0100000000000000ULL &&
            (double)uint128_t(0x0200000000000000ULL) == (double)0x0200000000000000ULL &&
            (double)uint128_t(0x0400000000000000ULL) == (double)0x0400000000000000ULL;

         if (!specials64)
            return false;

         bool specials128 = 
            (double)uint128_t("340282366920938463463374607431768211455") == 3.4028236692093846e+38 &&
            (double)uint128_t(  "4876198776487696981639587937164651357") == 4.8761987764876970e+36 &&
            (double)uint128_t(       "91753285766281837469783734467328") == 9.1753285766281837e+31;

         if (!specials128)
            return false;
         */
         return true;
      }

      INLINE static bool tostring128()
      {
         // decimal
         if (uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B10) != std::string("0"                                      )) return false;
         if (uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B10) != std::string("1"                                      )) return false;
         if (uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B10) != std::string("4294967295"                             )) return false;
         if (uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B10) != std::string("18446744073709551615"                   )) return false;
         if (uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL).toString(CPPCORE_ALPHABET_B10) != std::string("340282366920938463463374607431768211455")) return false;
         if (uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL).toString(CPPCORE_ALPHABET_B10) != std::string("170141183460469231731687303715884105728")) return false;
         // hexadecimal
         if (uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B16) != std::string("0"                                      )) return false;
         if (uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B16) != std::string("1"                                      )) return false;
         if (uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B16) != std::string("FFFFFFFF"                               )) return false;
         if (uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL).toString(CPPCORE_ALPHABET_B16) != std::string("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"       )) return false;
         if (uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL).toString(CPPCORE_ALPHABET_B16) != std::string("80000000000000000000000000000000"       )) return false;
         // binary
         if (uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B02) != std::string("0"                                      )) return false;
         if (uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B02) != std::string("1"                                      )) return false;
         if (uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B02) != std::string("11111111111111111111111111111111"       )) return false;
         if (uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL).toString(CPPCORE_ALPHABET_B02) != std::string("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111")) return false;
         if (uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL).toString(CPPCORE_ALPHABET_B02) != std::string("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")) return false;
         // base62
         if (uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B62) != std::string("0"                                      )) return false;
         if (uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B62) != std::string("1"                                      )) return false;
         if (uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B62) != std::string("4gfFC3"                                 )) return false;
         if (uint128_t(0x000FFFFFFFFFFFFFULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B62) != std::string("KcqObyjK3"                              )) return false;
         if (uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL).toString(CPPCORE_ALPHABET_B62) != std::string("LygHa16AHYF"                            )) return false;
         if (uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL).toString(CPPCORE_ALPHABET_B62) != std::string("7n42DGM5Tflk9n8mt7Fhc7"                 )) return false;
         if (uint128_t(0xF1FF613CE5028CA3ULL, 0xF6BC01EA51DD02C0ULL).toString(CPPCORE_ALPHABET_B62) != std::string("7Va1zNqi95kwJDJZY0WgKZ"                 )) return false;

         return true;
      }
      INLINE static bool tohexstring128()
      {
         if (uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL).toHexString() != std::string("00000000000000000000000000000000")) return false;
         if (uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL).toHexString() != std::string("00000000000000000000000000000001")) return false;
         if (uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL).toHexString() != std::string("000000000000000000000000FFFFFFFF")) return false;
         if (uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL).toHexString() != std::string("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")) return false;
         if (uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL).toHexString() != std::string("80000000000000000000000000000000")) return false;
         return true;
      }
      INLINE static bool tryparse128()
      {
         uint128_t r;
         // decimal
         if (!r.tryParse("0",                                        r, CPPCORE_ALPHABET_B10) || r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("0000000001",                               r, CPPCORE_ALPHABET_B10) || r != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("4294967295",                               r, CPPCORE_ALPHABET_B10) || r != uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("18446744073709551615",                     r, CPPCORE_ALPHABET_B10) || r != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("340282366920938463463374607431768211455",  r, CPPCORE_ALPHABET_B10) || r != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         if (!r.tryParse("170141183460469231731687303715884105728",  r, CPPCORE_ALPHABET_B10) || r != uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL)) return false;
         if (r.tryParse("340282366920938463463374607431768211456",   r, CPPCORE_ALPHABET_B10)) return false;// fail by add overflow
         if (r.tryParse("1340282366920938463463374607431768211455",  r, CPPCORE_ALPHABET_B10)) return false;// fail by mul overflow
         if (r.tryParse("5734X",                                     r, CPPCORE_ALPHABET_B10)) return false;// fail by invalid symbol
         if (r.tryParse("",                                          r, CPPCORE_ALPHABET_B10)) return false;// fail by empty input
         // hexadecimal
         if (!r.tryParse("0",                                        r, CPPCORE_ALPHABET_B16) || r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("1",                                        r, CPPCORE_ALPHABET_B16) || r != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("FFFFFFFF",                                 r, CPPCORE_ALPHABET_B16) || r != uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",         r, CPPCORE_ALPHABET_B16) || r != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         if (!r.tryParse("80000000000000000000000000000000",         r, CPPCORE_ALPHABET_B16) || r != uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL)) return false;
         if (r.tryParse("1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",         r, CPPCORE_ALPHABET_B16)) return false;// fail by mul overflow
         if (r.tryParse("FA3CEX",                                    r, CPPCORE_ALPHABET_B16)) return false;// fail by invalid symbol
         if (r.tryParse("",                                          r, CPPCORE_ALPHABET_B16)) return false;// fail by empty input
         // binary
         if (!r.tryParse("0",                                        r, CPPCORE_ALPHABET_B02) || r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("1",                                        r, CPPCORE_ALPHABET_B02) || r != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("11111111111111111111111111111111",         r, CPPCORE_ALPHABET_B02) || r != uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111",r, CPPCORE_ALPHABET_B02) || r != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         if (!r.tryParse("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",r, CPPCORE_ALPHABET_B02) || r != uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL)) return false;
         // base62
         if (!r.tryParse("0",                                        r, CPPCORE_ALPHABET_B62) || r != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("1",                                        r, CPPCORE_ALPHABET_B62) || r != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("4gfFC3",                                   r, CPPCORE_ALPHABET_B62) || r != uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("KcqObyjK3",                                r, CPPCORE_ALPHABET_B62) || r != uint128_t(0x000FFFFFFFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("LygHa16AHYF",                              r, CPPCORE_ALPHABET_B62) || r != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (!r.tryParse("7n42DGM5Tflk9n8mt7Fhc7",                   r, CPPCORE_ALPHABET_B62) || r != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         if (!r.tryParse("7Va1zNqi95kwJDJZY0WgKZ",                   r, CPPCORE_ALPHABET_B62) || r != uint128_t(0xF1FF613CE5028CA3ULL, 0xF6BC01EA51DD02C0ULL)) return false;
         if (r.tryParse("7n42DGM5Tflk9n8mt7Fhc8",                    r, CPPCORE_ALPHABET_B62)) return false;//fail by add overflow
         if (r.tryParse("17n42DGM5Tflk9n8mt7Fhc7",                   r, CPPCORE_ALPHABET_B62)) return false;//fail by mul overflow
         return true;
      }
      INLINE static bool parsedecimal128()
      {
         if (uint128_t::parseDecimal("0"                                      ) != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         if (uint128_t::parseDecimal("0000000001"                             ) != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         if (uint128_t::parseDecimal("4294967295"                             ) != uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (uint128_t::parseDecimal("18446744073709551615"                   ) != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (uint128_t::parseDecimal("340282366920938463463374607431768211455") != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         if (uint128_t::parseDecimal("170141183460469231731687303715884105728") != uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL)) return false;
         return true;
      }
      INLINE static bool parsehex128()
      {
         if (uint128_t::parseHex("0"                               ) != uint128_t(0x0000000000000000ULL, 0x0000000000000000ULL)) return false;
         if (uint128_t::parseHex("0000000001"                      ) != uint128_t(0x0000000000000001ULL, 0x0000000000000000ULL)) return false;
         if (uint128_t::parseHex("FFFFFFFF"                        ) != uint128_t(0x00000000FFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (uint128_t::parseHex("FFFFFFFFFFFFFFFF"                ) != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL)) return false;
         if (uint128_t::parseHex("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF") != uint128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)) return false;
         if (uint128_t::parseHex("80000000000000000000000000000000") != uint128_t(0x0000000000000000ULL, 0x8000000000000000ULL)) return false;
         return true;
      }

   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Math
{
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(BigInt)
   {
   public:
      TEST_METHOD(EQ128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::eq128()); }
      TEST_METHOD(POPCNT128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::popcnt128()); }
      TEST_METHOD(TZCNT128)  { Assert::AreEqual(true, CppCore::Test::Math::BigInt::tzcnt128()); }
      TEST_METHOD(LZCNT128)  { Assert::AreEqual(true, CppCore::Test::Math::BigInt::lzcnt128()); }
      TEST_METHOD(GETBIT128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::getbit128()); }
      TEST_METHOD(SETBIT128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::setbit128()); }
      TEST_METHOD(BYTESWAP128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::byteswap128()); }
      TEST_METHOD(SHL128)    { Assert::AreEqual(true, CppCore::Test::Math::BigInt::shl128()); }
      TEST_METHOD(SHR128)    { Assert::AreEqual(true, CppCore::Test::Math::BigInt::shr128()); }
      TEST_METHOD(ROTL128)   { Assert::AreEqual(true, CppCore::Test::Math::BigInt::rotl128()); }
      TEST_METHOD(ROTR128)   { Assert::AreEqual(true, CppCore::Test::Math::BigInt::rotr128()); }
      TEST_METHOD(MUL128)    { Assert::AreEqual(true, CppCore::Test::Math::BigInt::mul128()); }
      TEST_METHOD(MULW128)   { Assert::AreEqual(true, CppCore::Test::Math::BigInt::mulw128()); }
      TEST_METHOD(DIVMOD128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::divmod128()); }
      TEST_METHOD(SQRT128)   { Assert::AreEqual(true, CppCore::Test::Math::BigInt::sqrt128()); }
      TEST_METHOD(TODOUBLE128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::todouble128()); }
      TEST_METHOD(TOSTRING128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::tostring128()); }
      TEST_METHOD(TOHEXSTRING128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::tohexstring128()); }
      TEST_METHOD(TRYPARSE128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::tryparse128()); }
      TEST_METHOD(PARSEDECIMAL128) { Assert::AreEqual(true, CppCore::Test::Math::BigInt::parsedecimal128()); }
      TEST_METHOD(PARSEHEX128)   { Assert::AreEqual(true, CppCore::Test::Math::BigInt::parsehex128()); }
   };
}}}}
#endif
