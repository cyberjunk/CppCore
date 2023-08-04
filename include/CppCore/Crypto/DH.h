#pragma once

#include <CppCore/Root.h>
#include <CppCore/Math/BigInt.h>

namespace CppCore
{
   /// <summary>
   /// Diffie-Hellman Key Exchange
   /// </summary>
   template<typename UINT>
   class DH
   {
   protected:
      UINT t; // temporary value

   public:
      UINT p; // public large prime (highbit set) 
      UINT g; // public random with g < p
      UINT v; // private key with v < p
      UINT V; // public key generated from v using p and g
      UINT k; // private session key

      /// <summary>
      /// Size in Bytes
      /// </summary>
      static constexpr const size_t SIZE = sizeof(UINT);

   protected:
      INLINE void genrnd(UINT& x)
      {
         x.randomize();
         x.d.i32[UINT::N32-1] &= 0x7FFFFFFFU; // make smaller than p
         x.d.i32[UINT::N32-1] |= 0x40000000U; // make large and not zero
      }
      INLINE void genprime(uint32_t certainty)
      {
         p.genprime(certainty);
      }
      INLINE void genpubkey()
      {
         CppCore::clone(t, g);
         CppCore::upowmod(t, v, p, V);
      }
   public:
      /// <summary>
      /// Automatically generate prime, constant and private key.
      /// You must share prime (p), constant (g) and public key (V).
      /// </summary>
      INLINE void reset(uint32_t certainty = 0)
      {
         this->genprime(certainty);
         this->genrnd(g);
         this->genrnd(v);
         this->genpubkey();
      }
      /// <summary>
      /// Use predefined prime (p) and constant (g) but generate private key (v).
      /// Requires p to have highbit set and g to be less than p.
      /// </summary>
      INLINE void reset(const UINT& p, const UINT& g)
      {
         assert(CppCore::lzcnt(p) == 0);
         assert(p.isprime(1));
         assert(g < p);
         CppCore::clone(this->p, p);
         CppCore::clone(this->g, g);
         this->genrnd(v);
         this->genpubkey();
      }
      /// <summary>
      /// Use predefined prime (p), constant (g) and private key (v).
      /// Requires g and v to be less than p and p to be large.
      /// </summary>
      INLINE void reset(const UINT& p, const UINT& g, const UINT& v)
      {
         assert(p.isprime(1));
         assert(g < p);
         assert(v < p);
         CppCore::clone(this->p, p);
         CppCore::clone(this->g, g);
         CppCore::clone(this->v, v);
         this->genpubkey();
      }
      /// <summary>
      /// Generate session key (k) from received public key of other party.
      /// </summary>
      INLINE void genkey(const UINT& V)
      {
         CppCore::clone(t, V);
         CppCore::upowmod(t, v, p, k);
      }
   };

   using DH128  = DH<uint128_t>;  // Diffi-Hellman 128 Bit Key Exchange
   using DH256  = DH<uint256_t>;  // Diffi-Hellman 256 Bit Key Exchange
   using DH512  = DH<uint512_t>;  // Diffi-Hellman 512 Bit Key Exchange
   using DH1024 = DH<uint1024_t>; // Diffi-Hellman 1024 Bit Key Exchange
   using DH2048 = DH<uint2048_t>; // Diffi-Hellman 2048 Bit Key Exchange
}
