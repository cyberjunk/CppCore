#pragma once

#include <CppCore/Root.h>
//#include <CppCore/Block.h>
#include <CppCore/Math/BigInt.h>

namespace CppCore
{
   /// <summary>
   /// Diffie-Hellman Key Exchange
   /// </summary>
   class DH
   {
   protected:
      uint2048_t t; // temporary value

   public:
      uint2048_t p; // public large prime (highbit set) 
      uint2048_t g; // public random with g < p
      uint2048_t v; // private key with v < p
      uint2048_t V; // public key generated from v
      uint2048_t k; // private session key

   protected:
      INLINE void genprime(uint32_t certainty)
      {
         p.genprime(certainty);
      }
      INLINE void genconstant()
      {
         g.randomize();
         g.d.i32[uint2048_t::N32-1] &= 0x7FFFFFFFU;
      }
      INLINE void genprivkey()
      {
         v.randomize();
         v.d.i32[uint2048_t::N32-1] &= 0x7FFFFFFFU;
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
         this->genconstant();
         this->genprivkey();
         this->genpubkey();
      }
      /// <summary>
      /// Use predefined prime (p) and constant (g) but generate private key (v).
      /// Requires p to have highbit set and g to be less than p.
      /// </summary>
      INLINE void reset(const uint2048_t& p, const uint2048_t& g)
      {
         assert(CppCore::lzcnt(p) == 0);
         assert(p.isprime(1));
         assert(g < p);
         CppCore::clone(this->p, p);
         CppCore::clone(this->g, g);
         this->genprivkey();
         this->genpubkey();
      }
      /// <summary>
      /// Use predefined prime (p), constant (g) and private key (v).
      /// Requires g and v to be less than p and p to be large.
      /// </summary>
      INLINE void reset(const uint2048_t& p, const uint2048_t& g, const uint2048_t& v)
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
      INLINE void genkey(const uint2048_t& V)
      {
         CppCore::clone(t, V);
         CppCore::upowmod(t, v, p, k);
      }
   };
}
