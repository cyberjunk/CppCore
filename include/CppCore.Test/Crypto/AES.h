#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Crypto
{
   /// <summary>
   /// 
   /// </summary>
   class AES
   {
   public:
      static constexpr const uint8_t key128[16] =
      {
         0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
         0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c
      };
      static constexpr const uint8_t key192[24] =
      {
         0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
         0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c,
         0x5f,0x2e,0x6a,0x21,0xde,0xf1,0xa7,0x05
      };
      static constexpr const uint8_t key256[32] =
      {
         0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
         0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c,
         0x5f,0x2e,0x6a,0x21,0xde,0xf1,0xa7,0x05,
         0x15,0x21,0x27,0x41,0x61,0x74,0x84,0x25
      };
      static constexpr const uint8_t plain[64] = 
      {
         0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,
         0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,
         0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,
         0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51,
         0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,
         0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef,
         0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,
         0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10 
      };
      static constexpr const uint8_t ivec[16] =
      {
         0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
         0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
      };
      //////////////////////////////////////////////////

      template<typename TAES>
      INLINE static bool ecb128()
      {
         // plain encrypted with key128
         const uint8_t in_cipher[64]  = 
         {
            0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,
            0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97,
            0xf5,0xd3,0xd5,0x85,0x03,0xb9,0x69,0x9d,
            0xe7,0x85,0x89,0x5a,0x96,0xfd,0xba,0xaf,
            0x43,0xb1,0xcd,0x7f,0x59,0x8e,0xce,0x23,
            0x88,0x1b,0x00,0xe3,0xed,0x03,0x06,0x88,
            0x7b,0x0c,0x78,0x5e,0x27,0xe8,0xad,0x3f,
            0x82,0x23,0x20,0x71,0x04,0x72,0x5d,0xd4
         };
         
         uint8_t out_plain[64];
         uint8_t out_cipher[64];

         // init
         TAES aes(key128);

         // test encrypt
         aes.encryptECB(plain, out_cipher, 4U);
         if (!(::memcmp(in_cipher, out_cipher, 64) == 0))
            return false;
         
         // test decrypt
         aes.decryptECB(in_cipher, out_plain, 4U);
         if (!(::memcmp(plain, out_plain, 64) == 0))
            return false;

         return true;
      }

      template<typename TAES>
      INLINE static bool ecb192()
      {
         // plain encrypted with key192
         const uint8_t in_cipher[64]  = 
         { 
            0xDF,0x86,0x0A,0x21,0xCF,0xB3,0xE0,0xED,
            0x7E,0x54,0xA4,0x17,0x3C,0xB8,0xAB,0x0B,
            0x90,0xE9,0xF6,0xBC,0x5E,0x5F,0xF1,0x55,
            0x14,0xF4,0x2F,0xA2,0x95,0x91,0x0D,0xA5,
            0xAD,0xC2,0x31,0x54,0xF2,0x35,0x1F,0x2F,
            0x51,0x3F,0xD0,0xCC,0x24,0xBA,0xDF,0xAE,
            0x0C,0xB0,0x64,0x2F,0x7E,0x9C,0x01,0x0E,
            0x9C,0x75,0xC9,0x73,0xD5,0x18,0xA6,0x70 
         };
         
         uint8_t out_plain[64];
         uint8_t out_cipher[64];

         // init
         TAES aes(key192);

         // test encrypt
         aes.encryptECB(plain, out_cipher, 4U);
         if (!(::memcmp(in_cipher, out_cipher, 64) == 0))
            return false;
         
         // test decrypt
         aes.decryptECB(in_cipher, out_plain, 4U);
         if (!(::memcmp(plain, out_plain, 64) == 0))
            return false;
 
         return true;
      }

      template<typename TAES>
      INLINE static bool ecb256()
      {
         // plain encrypted with key256
         const uint8_t in_cipher[64]  = 
         { 
            0xE4,0xC3,0xC3,0x0F,0x63,0xEA,0x4B,0xEE,
            0xFE,0xAC,0x2F,0xB8,0x19,0xA1,0xCB,0x93,
            0xD2,0x73,0x87,0xE7,0xDC,0x58,0x0F,0x3E,
            0x04,0xB5,0xF5,0xC2,0x55,0xD9,0x37,0x32, 
            0x42,0xD9,0x5C,0xAD,0xEE,0x47,0x77,0xF2,
            0x14,0xA7,0x91,0x49,0x24,0x34,0x3B,0x25,
            0x37,0x17,0x8E,0x77,0x27,0x9B,0x7E,0x54,
            0x7C,0x20,0x1F,0xF1,0x84,0xDA,0x1C,0x1A 
         };

         uint8_t out_plain[64];
         uint8_t out_cipher[64];

         // init
         TAES aes(key256);

         // test encrypt
         aes.encryptECB(plain, out_cipher, 4U);
         if (!(::memcmp(in_cipher, out_cipher, 64) == 0))
            return false;
         
         // test decrypt
         aes.decryptECB(in_cipher, out_plain, 4U);
         if (!(::memcmp(plain, out_plain, 64) == 0))
            return false;
 
         return true;
      }

      //////////////////////////////////////////////////
      // CBC (Cipher Block Chaining)
      //////////////////////////////////////////////////

      template<typename TAES>
      INLINE static bool cbc128()
      {
         const uint8_t key[16] = {
            0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
            0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c
         };
         const uint8_t cipher[64] = {
            0x76,0x49,0xab,0xac,0x81,0x19,0xb2,0x46,
            0xce,0xe9,0x8e,0x9b,0x12,0xe9,0x19,0x7d,
            0x50,0x86,0xcb,0x9b,0x50,0x72,0x19,0xee,
            0x95,0xdb,0x11,0x3a,0x91,0x76,0x78,0xb2,
            0x73,0xbe,0xd6,0xb8,0xe3,0xc1,0x74,0x3b,
            0x71,0x16,0xe6,0x9e,0x22,0x22,0x95,0x16,
            0x3f,0xf1,0xca,0xa1,0x68,0x1f,0xac,0x09,
            0x12,0x0e,0xca,0x30,0x75,0x86,0xe1,0xa7
         };

         uint8_t out_plain[64];
         uint8_t out_cipher[64];
         uint8_t inout_ivec[16];

         // init
         TAES aes(key);

         // reset ivec and test encrypt
         ::memcpy(inout_ivec, ivec, 16);
         aes.encryptCBC(plain,    out_cipher,    inout_ivec, 2U);
         aes.encryptCBC(plain+32, out_cipher+32, inout_ivec, 2U);
         if (!(::memcmp(cipher, out_cipher, 64) == 0))
            return false;

         // reset ivec and test decrypt
         ::memcpy(inout_ivec, ivec, 16);
         aes.decryptCBC(cipher,    out_plain,    inout_ivec, 2U);
         aes.decryptCBC(cipher+32, out_plain+32, inout_ivec, 2U);
         if (!(::memcmp(plain, out_plain, 64) == 0))
            return false;

         return true;
      }

      template<typename TAES>
      INLINE static bool cbc192()
      {
         const uint8_t key[24] = {
            0x8e,0x73,0xb0,0xf7,0xda,0x0e,0x64,0x52,
            0xc8,0x10,0xf3,0x2b,0x80,0x90,0x79,0xe5,
            0x62,0xf8,0xea,0xd2,0x52,0x2c,0x6b,0x7b
         };
         const uint8_t cipher[64] = {
            0x4f,0x02,0x1d,0xb2,0x43,0xbc,0x63,0x3d,
            0x71,0x78,0x18,0x3a,0x9f,0xa0,0x71,0xe8,
            0xb4,0xd9,0xad,0xa9,0xad,0x7d,0xed,0xf4,
            0xe5,0xe7,0x38,0x76,0x3f,0x69,0x14,0x5a,
            0x57,0x1b,0x24,0x20,0x12,0xfb,0x7a,0xe0,
            0x7f,0xa9,0xba,0xac,0x3d,0xf1,0x02,0xe0,
            0x08,0xb0,0xe2,0x79,0x88,0x59,0x88,0x81,
            0xd9,0x20,0xa9,0xe6,0x4f,0x56,0x15,0xcd
         };

         uint8_t out_plain[64];
         uint8_t out_cipher[64];
         uint8_t inout_ivec[16];

         // init
         TAES aes(key);

         // reset ivec and test encrypt
         ::memcpy(inout_ivec, ivec, 16);
         aes.encryptCBC(plain,    out_cipher,    inout_ivec, 2U);
         aes.encryptCBC(plain+32, out_cipher+32, inout_ivec, 2U);
         if (!(::memcmp(cipher, out_cipher, 64) == 0))
            return false;

         // reset ivec and test decrypt
         ::memcpy(inout_ivec, ivec, 16);
         aes.decryptCBC(cipher,    out_plain,    inout_ivec, 2U);
         aes.decryptCBC(cipher+32, out_plain+32, inout_ivec, 2U);
         if (!(::memcmp(plain, out_plain, 64) == 0))
            return false;

         return true;
      }

      template<typename TAES>
      INLINE static bool cbc256()
      {
         const uint8_t key[32] = {
            0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,
            0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,
            0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,
            0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4
         };
         const uint8_t cipher[64] = {
            0xf5,0x8c,0x4c,0x04,0xd6,0xe5,0xf1,0xba,
            0x77,0x9e,0xab,0xfb,0x5f,0x7b,0xfb,0xd6,
            0x9c,0xfc,0x4e,0x96,0x7e,0xdb,0x80,0x8d,
            0x67,0x9f,0x77,0x7b,0xc6,0x70,0x2c,0x7d,
            0x39,0xf2,0x33,0x69,0xa9,0xd9,0xba,0xcf,
            0xa5,0x30,0xe2,0x63,0x04,0x23,0x14,0x61,
            0xb2,0xeb,0x05,0xe2,0xc3,0x9b,0xe9,0xfc,
            0xda,0x6c,0x19,0x07,0x8c,0x6a,0x9d,0x1b
         };

         uint8_t out_plain[64];
         uint8_t out_cipher[64];
         uint8_t inout_ivec[16];

         // init
         TAES aes(key);

         // reset ivec and test encrypt
         ::memcpy(inout_ivec, ivec, 16);
         aes.encryptCBC(plain,    out_cipher,    inout_ivec, 2U);
         aes.encryptCBC(plain+32, out_cipher+32, inout_ivec, 2U);
         if (!(::memcmp(cipher, out_cipher, 64) == 0))
            return false;

         // reset ivec and test decrypt
         ::memcpy(inout_ivec, ivec, 16);
         aes.decryptCBC(cipher,    out_plain,    inout_ivec, 2U);
         aes.decryptCBC(cipher+32, out_plain+32, inout_ivec, 2U);
         if (!(::memcmp(plain, out_plain, 64) == 0))
            return false;

         return true;
      }

      //////////////////////////////////////////////////
      // CTR (Counter Mode)
      //////////////////////////////////////////////////

      template<typename TAES>
      INLINE static bool ctr128()
      {
         /*
            00 01 02 03 04 05 06 07
            08 09 0A 0B 0C 0D 0E 0F
            10 11 12 13 14 15 16 17
            18 19 1A 1B 1C 1D 1E 1F
         */
         const uint8_t plain[32] = {
            0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
            0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
            0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
            0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F
         };
         /*
            7E 24 06 78 17 FA E0 D7
            43 D6 CE 1F 32 53 91 63
         */
         const uint8_t key[16] = {
            0x7E,0x24,0x06,0x78,0x17,0xFA,0xE0,0xD7,
            0x43,0xD6,0xCE,0x1F,0x32,0x53,0x91,0x63
         };
         /*
            C0 54 3B 59 DA 48 D9 0B
            C0 54 3B 59 DA 48 D9 0B
         */
         const uint8_t iv[16] = {
            0xC0,0x54,0x3B,0x59,0xDA,0x48,0xD9,0x0B,
            0xC0,0x54,0x3B,0x59,0xDA,0x48,0xD9,0x0B
         };
         /*
            2b 7d 52 80 74 83 2c 11
            98 4a e8 79 e7 e9 93 c3
            3b d2 52 74 b9 85 16 e9
            8c 44 37 c4 43 16 a6 fb
         */
         const uint8_t cipher[32] = {
            0x2b,0x7d,0x52,0x80,0x74,0x83,0x2c,0x11,
            0x98,0x4a,0xe8,0x79,0xe7,0xe9,0x93,0xc3,
            0x3b,0xd2,0x52,0x74,0xb9,0x85,0x16,0xe9,
            0x8c,0x44,0x37,0xc4,0x43,0x16,0xa6,0xfb
         };

         uint8_t out_plain[32];
         uint8_t out_cipher[32];
         uint8_t inout_ivec[16];

         // init
         TAES aes;
         aes.reset(key, false);

         // test encrypt multiple 16
         ::memcpy(inout_ivec, iv, 16);
         aes.encryptCTR(plain,    out_cipher,    inout_ivec, 16);
         aes.encryptCTR(plain+16, out_cipher+16, inout_ivec, 16);
         if (!(::memcmp(cipher, out_cipher, 32) == 0))
            return false;

         // test decrypt multiple 16
         ::memcpy(inout_ivec, iv, 16);
         aes.decryptCTR(cipher,    out_plain,    inout_ivec, 16);
         aes.decryptCTR(cipher+16, out_plain+16, inout_ivec, 16);
         if (!(::memcmp(plain, out_plain, 32) == 0))
            return false;

         // test tail 1-15
         for (size_t i = 1; i < 16; i++)
         {
            // test encrypt tail
            ::memcpy(inout_ivec, iv, 16);
            aes.encryptCTR(plain, out_cipher, inout_ivec, i);
            if (!(::memcmp(cipher, out_cipher, i) == 0))
               return false;

            // test decrypt tail
            ::memcpy(inout_ivec, iv, 16);
            aes.decryptCTR(cipher, out_plain, inout_ivec, i);
            if (!(::memcmp(plain, out_plain, i) == 0))
               return false;
         }

         return true;
      }

      template<typename TAES>
      INLINE static bool ctr192()
      {
         const uint8_t plain[32] = {
            0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
            0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
            0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
            0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F
         };
         /*
            7C 5C B2 40 1B 3D C3 3C
            19 E7 34 08 19 E0 F6 9C
            67 8C 3D B8 E6 F6 A9 1A
         */
         const uint8_t key[24] = {
            0x7C,0x5C,0xB2,0x40,0x1B,0x3D,0xC3,0x3C, 
            0x19,0xE7,0x34,0x08,0x19,0xE0,0xF6,0x9C, 
            0x67,0x8C,0x3D,0xB8,0xE6,0xF6,0xA9,0x1A
         };
         /*
            C0 54 3B 59 DA 48 D9 0B
            C0 54 3B 59 DA 48 D9 0B
         */
         const uint8_t iv[16] = {
            0xC0,0x54,0x3B,0x59,0xDA,0x48,0xD9,0x0B,
            0xC0,0x54,0x3B,0x59,0xDA,0x48,0xD9,0x0B
         };
         const uint8_t cipher[32]  = {
           0x5A,0x3A,0x7F,0x35,0x7D,0xEA,0x43,0xB0,
           0xF2,0x55,0xD7,0x0B,0xED,0x5B,0xD9,0xB9,
           0x1F,0x2E,0x64,0xC3,0x24,0x11,0xC3,0x66,
           0x3D,0x1A,0x49,0x8E,0xE5,0x4B,0xC1,0x77
         };

         uint8_t out_plain[32];
         uint8_t out_cipher[32];
         uint8_t inout_ivec[16];

         // init
         TAES aes;
         aes.reset(key, false);

         // test encrypt multiple 16
         ::memcpy(inout_ivec, iv, 16);
         aes.encryptCTR(plain,    out_cipher,    inout_ivec, 16);
         aes.encryptCTR(plain+16, out_cipher+16, inout_ivec, 16);
         if (!(::memcmp(cipher, out_cipher, 32) == 0))
            return false;

         // test decrypt multiple 16
         ::memcpy(inout_ivec, iv, 16);
         aes.decryptCTR(cipher,    out_plain,    inout_ivec, 16);
         aes.decryptCTR(cipher+16, out_plain+16, inout_ivec, 16);
         if (!(::memcmp(plain, out_plain, 32) == 0))
            return false;

         // test tail 1-15
         for (size_t i = 1; i < 16; i++)
         {
            // test encrypt tail
            ::memcpy(inout_ivec, iv, 16);
            aes.encryptCTR(plain, out_cipher, inout_ivec, i);
            if (!(::memcmp(cipher, out_cipher, i) == 0))
               return false;

            // test decrypt tail
            ::memcpy(inout_ivec, iv, 16);
            aes.decryptCTR(cipher, out_plain, inout_ivec, i);
            if (!(::memcmp(plain, out_plain, i) == 0))
               return false;
         }
         return true;
      }

      template<typename TAES>
      INLINE static bool ctr256()
      {
         const uint8_t plain[32] = {
            0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
            0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
            0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
            0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F
         };
         /*
            F6 D6 6D 6B D5 2D 59 BB
            07 96 36 58 79 EF F8 86
            C6 6D D5 1A 5B 6A 99 74
            4B 50 59 0C 87 A2 38 84
         */
         const uint8_t key[32] = {
            0xF6,0xD6,0x6D,0x6B,0xD5,0x2D,0x59,0xBB,
            0x07,0x96,0x36,0x58,0x79,0xEF,0xF8,0x86,
            0xC6,0x6D,0xD5,0x1A,0x5B,0x6A,0x99,0x74,
            0x4B,0x50,0x59,0x0C,0x87,0xA2,0x38,0x84
         };
         /*
            C0 54 3B 59 DA 48 D9 0B
            C0 54 3B 59 DA 48 D9 0B
         */
         const uint8_t iv[16] = {
            0xC0,0x54,0x3B,0x59,0xDA,0x48,0xD9,0x0B,
            0xC0,0x54,0x3B,0x59,0xDA,0x48,0xD9,0x0B
         };

         const uint8_t cipher[32]  = {
            0xa9,0xc5,0xe0,0x07,0x0e,0xf7,0x1e,0xbe,
            0xbb,0x25,0x18,0xf0,0x90,0x94,0xe6,0x51,
            0xdb,0x4a,0x2b,0x7b,0x99,0x74,0x59,0x51,
            0xde,0x5d,0x30,0xad,0xde,0xbb,0x5e,0x7b
         };

         uint8_t out_plain[32];
         uint8_t out_cipher[32];
         uint8_t inout_ivec[16];

         // init
         TAES aes;
         aes.reset(key, false);

         // test encrypt multiple 16
         ::memcpy(inout_ivec, iv, 16);
         aes.encryptCTR(plain,    out_cipher,    inout_ivec, 16);
         aes.encryptCTR(plain+16, out_cipher+16, inout_ivec, 16);
         if (!(::memcmp(cipher, out_cipher, 32) == 0))
            return false;

         // test decrypt multiple 16
         ::memcpy(inout_ivec, iv, 16);
         aes.decryptCTR(cipher,    out_plain,    inout_ivec, 16);
         aes.decryptCTR(cipher+16, out_plain+16, inout_ivec, 16);
         if (!(::memcmp(plain, out_plain, 32) == 0))
            return false;

         // test tail 1-15
         for (size_t i = 1; i < 16; i++)
         {
            // test encrypt tail
            ::memcpy(inout_ivec, iv, 16);
            aes.encryptCTR(plain, out_cipher, inout_ivec, i);
            if (!(::memcmp(cipher, out_cipher, i) == 0))
               return false;

            // test decrypt tail
            ::memcpy(inout_ivec, iv, 16);
            aes.decryptCTR(cipher, out_plain, inout_ivec, i);
            if (!(::memcmp(plain, out_plain, i) == 0))
               return false;
         }

         return true;
      }
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Crypto {
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(AES)
   {
   public:
      TEST_METHOD(ECB128G) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ecb128<CppCore::AES128g>()); }
      TEST_METHOD(ECB192G) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ecb192<CppCore::AES192g>()); }
      TEST_METHOD(ECB256G) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ecb256<CppCore::AES256g>()); }
      TEST_METHOD(CBC128G) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::cbc128<CppCore::AES128g>()); }
      TEST_METHOD(CBC192G) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::cbc192<CppCore::AES192g>()); }
      TEST_METHOD(CBC256G) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::cbc256<CppCore::AES256g>()); }
      TEST_METHOD(CTR128G) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ctr128<CppCore::AES128g>()); }
      TEST_METHOD(CTR192G) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ctr192<CppCore::AES192g>()); }
      TEST_METHOD(CTR256G) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ctr256<CppCore::AES256g>()); }
   #if defined(CPPCORE_CPUFEAT_AES) && defined(CPPCORE_CPUFEAT_SSE41)
      TEST_METHOD(ECB128S) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ecb128<CppCore::AES128s>()); }
      TEST_METHOD(ECB192S) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ecb192<CppCore::AES192s>()); }
      TEST_METHOD(ECB256S) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ecb256<CppCore::AES256s>()); }
      TEST_METHOD(CBC128S) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::cbc128<CppCore::AES128s>()); }
      TEST_METHOD(CBC192S) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::cbc192<CppCore::AES192s>()); }
      TEST_METHOD(CBC256S) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::cbc256<CppCore::AES256s>()); }
      TEST_METHOD(CTR128S) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ctr128<CppCore::AES128s>()); }
      TEST_METHOD(CTR192S) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ctr192<CppCore::AES192s>()); }
      TEST_METHOD(CTR256S) { Assert::AreEqual(true, CppCore::Test::Crypto::AES::ctr256<CppCore::AES256s>()); }
   #endif
   };
}}}}
#endif
