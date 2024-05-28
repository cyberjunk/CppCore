#pragma once

#include <CppCore/Root.h>
#include <CppCore/Crypto/HMAC.h>

namespace CppCore
{
   /// <summary>
   /// PKCS5 PBKDF2
   /// </summary>
   template<typename HMAC>
   class PBKDF2
   {
   protected:
      HMAC hmac;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE PBKDF2() { }

      /// <summary>
      /// Created digest using pw, salt and iterations.
      /// </summary>
      INLINE void create(
         const void* pw,   const size_t lenpw, 
         const void* salt, const size_t lensalt, 
         const size_t iterations, 
         void* digest, size_t lendigest)
      {
         typename HMAC::Digest md1;
         typename HMAC::Digest mdx;

         uint8_t* pdigest = (uint8_t*)digest;
         uint32_t ctrle = 1U;
         uint32_t ctrbe;

         while (lendigest)
         {
            ctrbe = CppCore::byteswap32(ctrle);
            hmac.reset(pw, lenpw);
            hmac.step(salt, lensalt);
            hmac.step(&ctrbe, 4);
            hmac.finish(md1);

            CppCore::clone(mdx, md1);

            for (size_t i = 1; i < iterations; i++)
            {
               hmac.reset(pw, lenpw);
               hmac.step(md1);
               hmac.finish(md1);
               mdx ^= md1;
            }

            const size_t min = MIN(lendigest, sizeof(mdx));
            Memory::copy(pdigest, &mdx, min);
            lendigest -= min;
            pdigest += min;
            ctrle++;
         }
      }
   };

   /// <summary>
   /// PBKDF2 with HMAC-MD5
   /// </summary>
   using PBKDF2MD5 = PBKDF2<HMACMD5>;

   /// <summary>
   /// PBKDF2 with HMAC-SHA256
   /// </summary>
   using PBKDF2SHA256 = PBKDF2<HMACSHA256>;

   /// <summary>
   /// PBKDF2 with HMAC-SHA512
   /// </summary>
   using PBKDF2SHA512 = PBKDF2<HMACSHA512>;
}
