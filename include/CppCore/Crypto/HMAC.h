#pragma once

#include <CppCore/Root.h>
#include <CppCore/Hash/MD5.h>
#include <CppCore/Hash/SHA2.h>

namespace CppCore
{
   /// <summary>
   /// Keyed-Hash Message Authentication Code
   /// </summary>
   template<typename THASH, typename TBLOCK, typename TSTATE>
   class HMAC
   {
      static_assert(sizeof(TBLOCK) % 4 == 0);

   protected:
      THASH  hsh;
      TBLOCK pad;

   public:
      static constexpr const uint8_t INPAD  = (uint8_t)0x36;
      static constexpr const uint8_t OUTPAD = (uint8_t)0x5c;

      /// <summary>
      /// Reset HMAC.
      /// </summary>
      INLINE void reset(
         const void* key, size_t  len, 
         const uint8_t inpad  = INPAD, 
         const uint8_t outpad = OUTPAD)
      {
         TSTATE b;
         hsh.reset();

         // use hash of key if too large
         if (len > sizeof(pad))
         {
            hsh.step(key, len);
            hsh.finish(b);
            hsh.reset();
            key = &b;
            len = sizeof(b);
         }

         // step on in padding^key
         pad.set(inpad);
         pad.xor_(key, len);
         hsh.step(pad);

         // prepare out padding^key
         pad.set(outpad);
         pad.xor_(key, len);
      }

      /// <summary>
      /// Calculate len of data into HMAC.
      /// </summary>
      INLINE void step(const void* data, const size_t len)
      {
         hsh.step(data, len);
      }

      /// <summary>
      /// Calculate type T into HMAC.
      /// </summary>
      template<typename T>
      INLINE void step(T& data)
      {
         hsh.step(data);
      }

      /// <summary>
      /// Finish HMAC calculation into digest.
      /// </summary>
      INLINE void finish(typename THASH::Digest& digest)
      {
         hsh.finish(digest);
         hsh.reset();
         hsh.step(pad);
         hsh.step(digest);
         hsh.finish(digest);
      }
   };

   ////////////////////////////////////////////////////////////////////////////

   using HMACMD5    = HMAC<MD5,    MD5::Block,     MD5::State>;
   using HMACSHA256 = HMAC<SHA256, SHA256::Block,  SHA256::State>;
   using HMACSHA512 = HMAC<SHA512, SHA512::Block,  SHA512::State>;
}
