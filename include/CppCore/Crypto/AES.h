#pragma once

#include <CppCore/Root.h>
#include <CppCore/Block.h>
#include <CppCore/Math/Util.h>

#define CPPCORE_AES_ROUNDS_128  10
#define CPPCORE_AES_ROUNDS_192  12
#define CPPCORE_AES_ROUNDS_256  14

namespace CppCore
{
   /// <summary>
   /// AES Base
   /// </summary>
   template<uint32_t ROUNDS>
   class AES
   {
   protected:
      static_assert(
         ROUNDS == CPPCORE_AES_ROUNDS_128 ||
         ROUNDS == CPPCORE_AES_ROUNDS_192 ||
         ROUNDS == CPPCORE_AES_ROUNDS_256);

   protected:
      INLINE AES() { }

   public:
      /// <summary>
      /// Template Argument as Constant
      /// </summary>
      static constexpr const uint32_t N = ROUNDS;
   };

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // GENERIC
   /////////////////////////////////////////////////////////////////////////////////////////////////

   /// <summary>
   /// AES Generic
   /// </summary>
   template<uint32_t N>
   class AESg : public AES<N>
   {
   protected:
      /// <summary>
      /// SBox
      /// </summary>
      CPPCORE_ALIGN64 static constexpr const uint8_t sbox[256] = {
         0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
         0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
         0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
         0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
         0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
         0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
         0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
         0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
         0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
         0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
         0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
         0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
         0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
         0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
         0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
         0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
      };

      /// <summary>
      /// Inverse SBox
      /// </summary>
      CPPCORE_ALIGN64 static constexpr const uint8_t isbox[256] = {
         0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
         0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
         0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
         0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
         0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
         0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
         0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
         0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
         0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
         0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
         0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
         0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
         0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
         0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
         0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
         0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
      };

      /// <summary>
      /// Encryption Lookup Table
      /// </summary>
      CPPCORE_ALIGN64 static constexpr const uint32_t te[256] = {
         0xA56363C6, 0x847C7CF8, 0x997777EE, 0x8D7B7BF6, 0x0DF2F2FF, 0xBD6B6BD6, 0xB16F6FDE, 0x54C5C591,
         0x50303060, 0x03010102, 0xA96767CE, 0x7D2B2B56, 0x19FEFEE7, 0x62D7D7B5, 0xE6ABAB4D, 0x9A7676EC,
         0x45CACA8F, 0x9D82821F, 0x40C9C989, 0x877D7DFA, 0x15FAFAEF, 0xEB5959B2, 0xC947478E, 0x0BF0F0FB,
         0xECADAD41, 0x67D4D4B3, 0xFDA2A25F, 0xEAAFAF45, 0xBF9C9C23, 0xF7A4A453, 0x967272E4, 0x5BC0C09B,
         0xC2B7B775, 0x1CFDFDE1, 0xAE93933D, 0x6A26264C, 0x5A36366C, 0x413F3F7E, 0x02F7F7F5, 0x4FCCCC83,
         0x5C343468, 0xF4A5A551, 0x34E5E5D1, 0x08F1F1F9, 0x937171E2, 0x73D8D8AB, 0x53313162, 0x3F15152A,
         0x0C040408, 0x52C7C795, 0x65232346, 0x5EC3C39D, 0x28181830, 0xA1969637, 0x0F05050A, 0xB59A9A2F,
         0x0907070E, 0x36121224, 0x9B80801B, 0x3DE2E2DF, 0x26EBEBCD, 0x6927274E, 0xCDB2B27F, 0x9F7575EA,
         0x1B090912, 0x9E83831D, 0x742C2C58, 0x2E1A1A34, 0x2D1B1B36, 0xB26E6EDC, 0xEE5A5AB4, 0xFBA0A05B,
         0xF65252A4, 0x4D3B3B76, 0x61D6D6B7, 0xCEB3B37D, 0x7B292952, 0x3EE3E3DD, 0x712F2F5E, 0x97848413,
         0xF55353A6, 0x68D1D1B9, 0x00000000, 0x2CEDEDC1, 0x60202040, 0x1FFCFCE3, 0xC8B1B179, 0xED5B5BB6,
         0xBE6A6AD4, 0x46CBCB8D, 0xD9BEBE67, 0x4B393972, 0xDE4A4A94, 0xD44C4C98, 0xE85858B0, 0x4ACFCF85,
         0x6BD0D0BB, 0x2AEFEFC5, 0xE5AAAA4F, 0x16FBFBED, 0xC5434386, 0xD74D4D9A, 0x55333366, 0x94858511,
         0xCF45458A, 0x10F9F9E9, 0x06020204, 0x817F7FFE, 0xF05050A0, 0x443C3C78, 0xBA9F9F25, 0xE3A8A84B,
         0xF35151A2, 0xFEA3A35D, 0xC0404080, 0x8A8F8F05, 0xAD92923F, 0xBC9D9D21, 0x48383870, 0x04F5F5F1,
         0xDFBCBC63, 0xC1B6B677, 0x75DADAAF, 0x63212142, 0x30101020, 0x1AFFFFE5, 0x0EF3F3FD, 0x6DD2D2BF,
         0x4CCDCD81, 0x140C0C18, 0x35131326, 0x2FECECC3, 0xE15F5FBE, 0xA2979735, 0xCC444488, 0x3917172E,
         0x57C4C493, 0xF2A7A755, 0x827E7EFC, 0x473D3D7A, 0xAC6464C8, 0xE75D5DBA, 0x2B191932, 0x957373E6,
         0xA06060C0, 0x98818119, 0xD14F4F9E, 0x7FDCDCA3, 0x66222244, 0x7E2A2A54, 0xAB90903B, 0x8388880B,
         0xCA46468C, 0x29EEEEC7, 0xD3B8B86B, 0x3C141428, 0x79DEDEA7, 0xE25E5EBC, 0x1D0B0B16, 0x76DBDBAD,
         0x3BE0E0DB, 0x56323264, 0x4E3A3A74, 0x1E0A0A14, 0xDB494992, 0x0A06060C, 0x6C242448, 0xE45C5CB8,
         0x5DC2C29F, 0x6ED3D3BD, 0xEFACAC43, 0xA66262C4, 0xA8919139, 0xA4959531, 0x37E4E4D3, 0x8B7979F2,
         0x32E7E7D5, 0x43C8C88B, 0x5937376E, 0xB76D6DDA, 0x8C8D8D01, 0x64D5D5B1, 0xD24E4E9C, 0xE0A9A949,
         0xB46C6CD8, 0xFA5656AC, 0x07F4F4F3, 0x25EAEACF, 0xAF6565CA, 0x8E7A7AF4, 0xE9AEAE47, 0x18080810,
         0xD5BABA6F, 0x887878F0, 0x6F25254A, 0x722E2E5C, 0x241C1C38, 0xF1A6A657, 0xC7B4B473, 0x51C6C697,
         0x23E8E8CB, 0x7CDDDDA1, 0x9C7474E8, 0x211F1F3E, 0xDD4B4B96, 0xDCBDBD61, 0x868B8B0D, 0x858A8A0F,
         0x907070E0, 0x423E3E7C, 0xC4B5B571, 0xAA6666CC, 0xD8484890, 0x05030306, 0x01F6F6F7, 0x120E0E1C,
         0xA36161C2, 0x5F35356A, 0xF95757AE, 0xD0B9B969, 0x91868617, 0x58C1C199, 0x271D1D3A, 0xB99E9E27,
         0x38E1E1D9, 0x13F8F8EB, 0xB398982B, 0x33111122, 0xBB6969D2, 0x70D9D9A9, 0x898E8E07, 0xA7949433,
         0xB69B9B2D, 0x221E1E3C, 0x92878715, 0x20E9E9C9, 0x49CECE87, 0xFF5555AA, 0x78282850, 0x7ADFDFA5,
         0x8F8C8C03, 0xF8A1A159, 0x80898909, 0x170D0D1A, 0xDABFBF65, 0x31E6E6D7, 0xC6424284, 0xB86868D0,
         0xC3414182, 0xB0999929, 0x772D2D5A, 0x110F0F1E, 0xCBB0B07B, 0xFC5454A8, 0xD6BBBB6D, 0x3A16162C
      };

      /// <summary>
      /// Decryption Lookup Table
      /// </summary>
      CPPCORE_ALIGN64 static constexpr const uint32_t td[256] = {
         0x50A7F451, 0x5365417E, 0xC3A4171A, 0x965E273A, 0xCB6BAB3B, 0xF1459D1F, 0xAB58FAAC, 0x9303E34B,
         0x55FA3020, 0xF66D76AD, 0x9176CC88, 0x254C02F5, 0xFCD7E54F, 0xD7CB2AC5, 0x80443526, 0x8FA362B5,
         0x495AB1DE, 0x671BBA25, 0x980EEA45, 0xE1C0FE5D, 0x02752FC3, 0x12F04C81, 0xA397468D, 0xC6F9D36B,
         0xE75F8F03, 0x959C9215, 0xEB7A6DBF, 0xDA595295, 0x2D83BED4, 0xD3217458, 0x2969E049, 0x44C8C98E,
         0x6A89C275, 0x78798EF4, 0x6B3E5899, 0xDD71B927, 0xB64FE1BE, 0x17AD88F0, 0x66AC20C9, 0xB43ACE7D,
         0x184ADF63, 0x82311AE5, 0x60335197, 0x457F5362, 0xE07764B1, 0x84AE6BBB, 0x1CA081FE, 0x942B08F9,
         0x58684870, 0x19FD458F, 0x876CDE94, 0xB7F87B52, 0x23D373AB, 0xE2024B72, 0x578F1FE3, 0x2AAB5566,
         0x0728EBB2, 0x03C2B52F, 0x9A7BC586, 0xA50837D3, 0xF2872830, 0xB2A5BF23, 0xBA6A0302, 0x5C8216ED,
         0x2B1CCF8A, 0x92B479A7, 0xF0F207F3, 0xA1E2694E, 0xCDF4DA65, 0xD5BE0506, 0x1F6234D1, 0x8AFEA6C4,
         0x9D532E34, 0xA055F3A2, 0x32E18A05, 0x75EBF6A4, 0x39EC830B, 0xAAEF6040, 0x069F715E, 0x51106EBD,
         0xF98A213E, 0x3D06DD96, 0xAE053EDD, 0x46BDE64D, 0xB58D5491, 0x055DC471, 0x6FD40604, 0xFF155060,
         0x24FB9819, 0x97E9BDD6, 0xCC434089, 0x779ED967, 0xBD42E8B0, 0x888B8907, 0x385B19E7, 0xDBEEC879,
         0x470A7CA1, 0xE90F427C, 0xC91E84F8, 0x00000000, 0x83868009, 0x48ED2B32, 0xAC70111E, 0x4E725A6C,
         0xFBFF0EFD, 0x5638850F, 0x1ED5AE3D, 0x27392D36, 0x64D90F0A, 0x21A65C68, 0xD1545B9B, 0x3A2E3624,
         0xB1670A0C, 0x0FE75793, 0xD296EEB4, 0x9E919B1B, 0x4FC5C080, 0xA220DC61, 0x694B775A, 0x161A121C,
         0x0ABA93E2, 0xE52AA0C0, 0x43E0223C, 0x1D171B12, 0x0B0D090E, 0xADC78BF2, 0xB9A8B62D, 0xC8A91E14,
         0x8519F157, 0x4C0775AF, 0xBBDD99EE, 0xFD607FA3, 0x9F2601F7, 0xBCF5725C, 0xC53B6644, 0x347EFB5B,
         0x7629438B, 0xDCC623CB, 0x68FCEDB6, 0x63F1E4B8, 0xCADC31D7, 0x10856342, 0x40229713, 0x2011C684,
         0x7D244A85, 0xF83DBBD2, 0x1132F9AE, 0x6DA129C7, 0x4B2F9E1D, 0xF330B2DC, 0xEC52860D, 0xD0E3C177,
         0x6C16B32B, 0x99B970A9, 0xFA489411, 0x2264E947, 0xC48CFCA8, 0x1A3FF0A0, 0xD82C7D56, 0xEF903322,
         0xC74E4987, 0xC1D138D9, 0xFEA2CA8C, 0x360BD498, 0xCF81F5A6, 0x28DE7AA5, 0x268EB7DA, 0xA4BFAD3F,
         0xE49D3A2C, 0x0D927850, 0x9BCC5F6A, 0x62467E54, 0xC2138DF6, 0xE8B8D890, 0x5EF7392E, 0xF5AFC382,
         0xBE805D9F, 0x7C93D069, 0xA92DD56F, 0xB31225CF, 0x3B99ACC8, 0xA77D1810, 0x6E639CE8, 0x7BBB3BDB,
         0x097826CD, 0xF418596E, 0x01B79AEC, 0xA89A4F83, 0x656E95E6, 0x7EE6FFAA, 0x08CFBC21, 0xE6E815EF,
         0xD99BE7BA, 0xCE366F4A, 0xD4099FEA, 0xD67CB029, 0xAFB2A431, 0x31233F2A, 0x3094A5C6, 0xC066A235,
         0x37BC4E74, 0xA6CA82FC, 0xB0D090E0, 0x15D8A733, 0x4A9804F1, 0xF7DAEC41, 0x0E50CD7F, 0x2FF69117,
         0x8DD64D76, 0x4DB0EF43, 0x544DAACC, 0xDF0496E4, 0xE3B5D19E, 0x1B886A4C, 0xB81F2CC1, 0x7F516546,
         0x04EA5E9D, 0x5D358C01, 0x737487FA, 0x2E410BFB, 0x5A1D67B3, 0x52D2DB92, 0x335610E9, 0x1347D66D,
         0x8C61D79A, 0x7A0CA137, 0x8E14F859, 0x893C13EB, 0xEE27A9CE, 0x35C961B7, 0xEDE51CE1, 0x3CB1477A,
         0x59DFD29C, 0x3F73F255, 0x79CE1418, 0xBF37C773, 0xEACDF753, 0x5BAAFD5F, 0x146F3DDF, 0x86DB4478,
         0x81F3AFCA, 0x3EC468B9, 0x2C342438, 0x5F40A3C2, 0x72C31D16, 0x0C25E2BC, 0x8B493C28, 0x41950DFF,
         0x7101A839, 0xDEB30C08, 0x9CE4B4D8, 0x90C15664, 0x6184CB7B, 0x70B632D5, 0x745C6C48, 0x4257B8D0
      };

      /// <summary>
      /// Constants
      /// </summary>
      CPPCORE_ALIGN16 static constexpr const uint32_t rcon[11] = {
         0x00000000U, //todo: remove? this is never needed
         0x00000001U,
         0x00000002U,
         0x00000004U,
         0x00000008U,
         0x00000010U,
         0x00000020U,
         0x00000040U,
         0x00000080U,
         0x0000001BU,
         0x00000036U
      };

      /// <summary>
      /// Use Block128
      /// </summary>
      using Block = Block128;

   protected:
      union {
         CPPCORE_ALIGN16 Block    ekb[N + 1U];
         CPPCORE_ALIGN16 uint32_t ek[(N + 1U) * 4U];
      };
      union {
         CPPCORE_ALIGN16 Block    dkb[N + 1U];
         CPPCORE_ALIGN16 uint32_t dk[(N + 1U) * 4U];
      };

      /// <summary>
      /// Empty Constructor
      /// </summary>
      INLINE AESg() { }

      /// <summary>
      /// Constructor for AES128 (n=4), AES192 (n=6), AES256 (n=8)
      /// </summary>
      INLINE AESg(const uint32_t* key, const uint32_t n, const bool builddec = true)
      {
         reset(key, n, builddec);
      }

   public:
      /// <summary>
      /// Reset with new key
      /// </summary>
      INLINE void reset(const uint32_t* key, const uint32_t n, const bool builddec = true)
      {
         // AES128 || AES192 || AES256
         assert(n == 4 || n == 6 || n == 8);

         // copy the original key
         for (uint32_t i = 0; i < n; i++)
            this->ek[i] = key[i];

         // generate encryption key
         for (uint32_t i = n; i < (N+1U)*4U; i++)
         {
            const uint32_t v = this->ek[i - 1];
            const uint32_t r = i % n;
            if(r == 0)
            {
               this->ek[i] = 
                  (sbox[CppCore::getbits32(v, 8,  8)]        |
                  (sbox[CppCore::getbits32(v, 16, 8)] << 8)  |
                  (sbox[CppCore::getbits32(v, 24, 8)] << 16) |
                  (sbox[v & 0xFF] << 24)) ^ rcon[i / n];
            }
            else if(n > 6 && r == 4)
            {
               this->ek[i] = 
                  (sbox[v & 0xFF])                           |
                  (sbox[CppCore::getbits32(v, 8,  8)] << 8)  |
                  (sbox[CppCore::getbits32(v, 16, 8)] << 16) |
                  (sbox[CppCore::getbits32(v, 24, 8)] << 24);
            }
            else
            {
               this->ek[i] = v;
            }
            this->ek[i] ^= this->ek[i - n];
         }

         // generate decryption key
         if (builddec)
         {
            this->dkb[0] = this->ekb[0];
            CPPCORE_UNROLL
            for (uint32_t i = 1U; i < N; i++)
            {
               const Block& v = this->ekb[i];
               this->dkb[i].u32[0] = td[sbox[v.u32[0] & 0xFF]]
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[0], 8,  8)]], 8)
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[0], 16, 8)]], 16)
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[0], 24, 8)]], 24);
               this->dkb[i].u32[1] = td[sbox[v.u32[1] & 0xFF]]
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[1], 8,  8)]], 8)
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[1], 16, 8)]], 16)
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[1], 24, 8)]], 24);
               this->dkb[i].u32[2] = td[sbox[v.u32[2] & 0xFF]]
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[2], 8,  8)]], 8)
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[2], 16, 8)]], 16)
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[2], 24, 8)]], 24);
               this->dkb[i].u32[3] = td[sbox[v.u32[3] & 0xFF]]
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[3], 8,  8)]], 8)
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[3], 16, 8)]], 16)
                  ^ CppCore::rotl32(td[sbox[CppCore::getbits32(v.u32[3], 24, 8)]], 24);
            }
            this->dkb[N] = this->ekb[N];
         }
      }

      /// <summary>
      /// Encrypts one Block in ECB mode
      /// </summary>
      INLINE void encrypt(const Block& in, Block& out)
      {
         Block t;

         // initial round key addition on input
         out = in ^ this->ekb[0];

         // n rounds
         CPPCORE_UNROLL
         for (uint32_t i = 1U; i < N; i++)
         {
            // round function
            t.u32[0] = te[out.u32[0] & 0xFF];
            t.u32[0] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[1], 8,  8)], 8);
            t.u32[0] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[2], 16, 8)], 16);
            t.u32[0] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[3], 24, 8)], 24);

            t.u32[1] = te[out.u32[1] & 0xFF];
            t.u32[1] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[2], 8,  8)], 8);
            t.u32[1] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[3], 16, 8)], 16);
            t.u32[1] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[0], 24, 8)], 24);

            t.u32[2] = te[out.u32[2] & 0xFF];
            t.u32[2] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[3], 8,  8)], 8);
            t.u32[2] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[0], 16, 8)], 16);
            t.u32[2] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[1], 24, 8)], 24);

            t.u32[3] = te[out.u32[3] & 0xFF];
            t.u32[3] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[0], 8,  8)], 8);
            t.u32[3] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[1], 16, 8)], 16);
            t.u32[3] ^= CppCore::rotl32(te[CppCore::getbits32(out.u32[2], 24, 8)], 24);

            // round key addition
            out = t ^ this->ekb[i];
         }

         // last round
         t.u32[0] = sbox[out.u32[0] & 0xFF];
         t.u32[0] |= sbox[CppCore::getbits32(out.u32[1], 8,  8)] << 8;
         t.u32[0] |= sbox[CppCore::getbits32(out.u32[2], 16, 8)] << 16;
         t.u32[0] |= sbox[CppCore::getbits32(out.u32[3], 24, 8)] << 24;

         t.u32[1] = sbox[out.u32[1] & 0xFF];
         t.u32[1] |= sbox[CppCore::getbits32(out.u32[2], 8,  8)] << 8;
         t.u32[1] |= sbox[CppCore::getbits32(out.u32[3], 16, 8)] << 16;
         t.u32[1] |= sbox[CppCore::getbits32(out.u32[0], 24, 8)] << 24;

         t.u32[2] = sbox[out.u32[2] & 0xFF];
         t.u32[2] |= sbox[CppCore::getbits32(out.u32[3], 8,  8)] << 8;
         t.u32[2] |= sbox[CppCore::getbits32(out.u32[0], 16, 8)] << 16;
         t.u32[2] |= sbox[CppCore::getbits32(out.u32[1], 24, 8)] << 24;

         t.u32[3] = sbox[out.u32[3] & 0xFF];
         t.u32[3] |= sbox[CppCore::getbits32(out.u32[0], 8,  8)] << 8;
         t.u32[3] |= sbox[CppCore::getbits32(out.u32[1], 16, 8)] << 16;
         t.u32[3] |= sbox[CppCore::getbits32(out.u32[2], 24, 8)] << 24;

         // last round key addition
         out = t ^ this->ekb[N];
      }

      /// <summary>
      /// Decrypts one Block in ECB mode
      /// </summary>
      INLINE void decrypt(const Block& in, Block& out)
      {
         Block t;

         // initial round key addition on input
         out = in ^ this->dkb[N];

         // n rounds
         CPPCORE_UNROLL
         for(uint32_t i = N - 1U; i >= 1U; i--)
         {
            // round function
            t.u32[0] = td[out.u32[0] & 0xFF];
            t.u32[0] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[3], 8,  8)], 8);
            t.u32[0] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[2], 16, 8)], 16);
            t.u32[0] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[1], 24, 8)], 24);

            t.u32[1] = td[out.u32[1] & 0xFF];
            t.u32[1] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[0], 8,  8)], 8);
            t.u32[1] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[3], 16, 8)], 16);
            t.u32[1] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[2], 24, 8)], 24);

            t.u32[2] = td[out.u32[2] & 0xFF];
            t.u32[2] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[1], 8,  8)], 8);
            t.u32[2] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[0], 16, 8)], 16);
            t.u32[2] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[3], 24, 8)], 24);

            t.u32[3] = td[out.u32[3] & 0xFF];
            t.u32[3] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[2], 8,  8)], 8);
            t.u32[3] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[1], 16, 8)], 16);
            t.u32[3] ^= CppCore::rotl32(td[CppCore::getbits32(out.u32[0], 24, 8)], 24);

            // round key addition
            out = t ^ this->dkb[i];
         }

         // last round
         t.u32[0] = isbox[out.u32[0] & 0xFF];
         t.u32[0] |= isbox[CppCore::getbits32(out.u32[3], 8,  8)] << 8;
         t.u32[0] |= isbox[CppCore::getbits32(out.u32[2], 16, 8)] << 16;
         t.u32[0] |= isbox[CppCore::getbits32(out.u32[1], 24, 8)] << 24;

         t.u32[1] = isbox[out.u32[1] & 0xFF];
         t.u32[1] |= isbox[CppCore::getbits32(out.u32[0], 8,  8)] << 8;
         t.u32[1] |= isbox[CppCore::getbits32(out.u32[3], 16, 8)] << 16;
         t.u32[1] |= isbox[CppCore::getbits32(out.u32[2], 24, 8)] << 24;

         t.u32[2] = isbox[out.u32[2] & 0xFF];
         t.u32[2] |= isbox[CppCore::getbits32(out.u32[1], 8,  8)] << 8;
         t.u32[2] |= isbox[CppCore::getbits32(out.u32[0], 16, 8)] << 16;
         t.u32[2] |= isbox[CppCore::getbits32(out.u32[3], 24, 8)] << 24;

         t.u32[3] = isbox[out.u32[3] & 0xFF];
         t.u32[3] |= isbox[CppCore::getbits32(out.u32[2], 8,  8)] << 8;
         t.u32[3] |= isbox[CppCore::getbits32(out.u32[1], 16, 8)] << 16;
         t.u32[3] |= isbox[CppCore::getbits32(out.u32[0], 24, 8)] << 24;

         // last round key addition
         out = t ^ this->dkb[0];
      }

      /// <summary>
      /// Encrypts one Block in CBC mode
      /// </summary>
      INLINE void encrypt(const Block& in, Block& out, Block& iv)
      {
         out = in ^ iv;
         encrypt(out, out);
         iv = out;
      }

      /// <summary>
      /// Decrypts one Block in CBC mode
      /// </summary>
      INLINE void decrypt(const Block& in, Block& out, Block& iv)
      {
         decrypt(in, out);
         out = out ^ iv;
         iv = in;
      }

      ///////////////////////////////////////////////////////////////

      /// <summary>
      /// Encrypts n Blocks of 16 Bytes in ECB mode
      /// </summary>
      INLINE void encryptECB(const void* in, void* out, const size_t n)
      {
         Block* bin  = (Block*)in;
         Block* bout = (Block*)out;
         CPPCORE_UNROLL
         for (size_t i = 0; i < n; i++)
            encrypt(bin[i], bout[i]);
      }

      /// <summary>
      /// Decrypts n Blocks of 16 Bytes in ECB mode
      /// </summary>
      INLINE void decryptECB(const void* in, void* out, const size_t n)
      {
         Block* bin  = (Block*)in;
         Block* bout = (Block*)out;
         CPPCORE_UNROLL
         for (size_t i = 0; i < n; i++)
            decrypt(bin[i], bout[i]);
      }

      /// <summary>
      /// Encrypts n Blocks of 16 Bytes in CBC mode
      /// </summary>
      INLINE void encryptCBC(const void* in, void* out, void* ivec, const size_t n)
      {
         Block* bin  = (Block*)in;
         Block* bout = (Block*)out;
         Block* iv   = (Block*)ivec;
         CPPCORE_UNROLL
         for (size_t i = 0; i < n; i++)
            encrypt(bin[i], bout[i], *iv);
      }

      /// <summary>
      /// Decrypts n Blocks of 16 Bytes in CBC mode
      /// </summary>
      INLINE void decryptCBC(const void* in, void* out, void* ivec, const size_t n)
      {
         Block* bin  = (Block*)in;
         Block* bout = (Block*)out;
         Block* iv   = (Block*)ivec;
         CPPCORE_UNROLL
         for (size_t i = 0; i < n; i++)
            decrypt(bin[i], bout[i], *iv);
      }

      /// <summary>
      /// Encrypts n Bytes in CTR mode.
      /// Performs 64-Bit increment on the counter part of ivec.
      /// </summary>
      INLINE void encryptCTR(const void* in, void* out, void* ivec, size_t len)
      {
         Block* bin  = (Block*)in;
         Block* bout = (Block*)out;
         Block& iv   = *(Block*)ivec;
         Block  enc;

         while (len)
         {
            // encrypt iv using ECB
            encrypt(iv, enc);

         #if false
            // full 128 bit big endian integer increment on counter
            // overflowing into iv like in OpenSSL or Tiny-AES
            for (int j = 15; j >= 0; --j)
            {
               if (iv.v8[j] == 255)
               {
                  iv.v8[j] = 0;
                  continue;
               }
               iv.v8[j] += 1;
               break;
            }
         #else
            // only 64 bit big endian integer increment on counter
            // not overflowing into iv (just like in SSE optimized version)
            CppCore::storer64(&iv.u64[1], CppCore::loadr64(&iv.u64[1]) + 1ULL);
         #endif

            if (len >= 16U)
            {
               // xor encrypted iv with input
               *bout++ = enc ^ *bin++;
               len -= 16U;
            }
            else
            {
               uint8_t* cin  = (uint8_t*)bin;
               uint8_t* cout = (uint8_t*)bout;
               uint8_t* cend = (uint8_t*)cin + len;
               uint8_t* cenc = (uint8_t*)&enc;
               if (cin + 8U <= cend)
               {
                  *(uint64_t*)cout = *(uint64_t*)cenc ^ *(uint64_t*)cin;
                  cin  += 8U;
                  cout += 8U;
                  cenc += 8U;
               }
               if (cin + 4U <= cend)
               {
                  *(uint32_t*)cout = *(uint32_t*)cenc ^ *(uint32_t*)cin;
                  cin  += 4U;
                  cout += 4U;
                  cenc += 4U;
               }
               if (cin + 2U <= cend)
               {
                  *(uint16_t*)cout = *(uint16_t*)cenc ^ *(uint16_t*)cin;
                  cin  += 2U;
                  cout += 2U;
                  cenc += 2U;
               }
               if (cin < cend) *cout = *cenc ^ *cin;
               return;
            }
         }
      }

      /// <summary>
      /// Decrypts n Bytes in CTR mode.
      /// </summary>
      INLINE void decryptCTR(const void* in, void* out, void* ivec, const size_t n)
      {
         encryptCTR(in, out, ivec, n);
      }
   };

   /// <summary>
   /// AES128 Generic
   /// </summary>
   class CPPCORE_ALIGN16 AES128g : public AESg<CPPCORE_AES_ROUNDS_128>
   {
   public:
      /// <summary>
      /// Empty Constructor. Call reset() before using the instance!
      /// </summary>
      INLINE AES128g() : AESg<CPPCORE_AES_ROUNDS_128>() { }

      /// <summary>
      /// Constructor. Key must be 16 Bytes.
      /// </summary>
      INLINE AES128g(const void* key, const bool builddec = true) : 
         AESg<CPPCORE_AES_ROUNDS_128>((uint32_t*)key, 4, builddec) { }

      /// <summary>
      /// Reset with new 16 bytes key
      /// </summary>
      INLINE void reset(const void* key, const bool builddec = true)
      {
         AESg<CPPCORE_AES_ROUNDS_128>::reset((uint32_t*)key, 4, builddec);
      }
   };

   /// <summary>
   /// AES192 Generic
   /// </summary>
   class CPPCORE_ALIGN16 AES192g : public AESg<CPPCORE_AES_ROUNDS_192>
   {
   public:
      /// <summary>
      /// Empty Constructor. Call reset() before using the instance!
      /// </summary>
      INLINE AES192g() : AESg<CPPCORE_AES_ROUNDS_192>() { }

      /// <summary>
      /// Constructor. Key must be 24 Bytes.
      /// </summary>
      INLINE AES192g(const void* key, const bool builddec = true) :
         AESg<CPPCORE_AES_ROUNDS_192>((uint32_t*)key, 6, builddec) { }

      /// <summary>
      /// Reset with new 24 bytes key
      /// </summary>
      INLINE void reset(const void* key, const bool builddec = true)
      {
         AESg<CPPCORE_AES_ROUNDS_192>::reset((uint32_t*)key, 6, builddec);
      }
   };

   /// <summary>
   /// AES256 Generic
   /// </summary>
   class CPPCORE_ALIGN16 AES256g : public AESg<CPPCORE_AES_ROUNDS_256>
   {
   public:
      /// <summary>
      /// Empty Constructor. Call reset() before using the instance!
      /// </summary>
      INLINE AES256g() : AESg<CPPCORE_AES_ROUNDS_256>() { }

      /// <summary>
      /// Constructor. Key must be 32 Bytes.
      /// </summary>
      INLINE AES256g(const void* key, const bool builddec = true) :
         AESg<CPPCORE_AES_ROUNDS_256>((uint32_t*)key, 8, builddec) { }

      /// <summary>
      /// Reset with new 32 bytes key
      /// </summary>
      INLINE void reset(const void* key, const bool builddec = true)
      {
         AESg<CPPCORE_AES_ROUNDS_256>::reset((uint32_t*)key, 8, builddec);
      }
   };

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // AES-NI
   /////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_AES) && defined(CPPCORE_CPUFEAT_SSE41)
   /// <summary>
   /// AES-NI
   /// </summary>
   template<uint32_t N>
   class AESs : public AES<N>
   {
   protected:
      __m128i ek[N + 1U];
      __m128i dk[N + 1U];

      INLINE AESs() { }

      template<bool ALIGNED = false>
      INLINE __m128i load(const void* m)
      {
         return ALIGNED ?
            _mm_load_si128((const __m128i*)m) :
            _mm_loadu_si128((const __m128i*)m);
      }

      template<bool ALIGNED = false>
      INLINE void store(void* m, const __m128i& v)
      {
         if (ALIGNED) _mm_store_si128 ((__m128i*)m, v);
         else         _mm_storeu_si128((__m128i*)m, v);
      }

   public:
      /// <summary>
      /// Encrypts one Block in ECB mode
      /// </summary>
      INLINE void encrypt(__m128i& m)
      {
         m = _mm_xor_si128(m, ek[0]);
         CPPCORE_UNROLL
         for (uint32_t i = 1U; i < N; i++)
            m = _mm_aesenc_si128(m, ek[i]);
         m = _mm_aesenclast_si128(m, ek[N]);
      }

      /// <summary>
      /// Decrypts one Block in ECB mode
      /// </summary>
      INLINE void decrypt(__m128i& m)
      {
         m = _mm_xor_si128(m, dk[0]);
         CPPCORE_UNROLL
         for (uint32_t i = 1U; i < N; i++)
            m = _mm_aesdec_si128(m, dk[i]);
         m = _mm_aesdeclast_si128(m, dk[N]);
      }

      /// <summary>
      /// Encrypts one Block in CBC mode
      /// </summary>
      INLINE void encrypt(__m128i& m, __m128i& iv)
      {
         m = _mm_xor_si128(m, iv);
         encrypt(m);
         iv = m;
      }

      /// <summary>
      /// Decrypts one Block in CBC mode
      /// </summary>
      INLINE void decrypt(__m128i& m, __m128i& iv)
      {
         __m128i t = m;
         decrypt(m);
         m = _mm_xor_si128(m, iv);
         iv = t;
      }

      ///////////////////////////////////////////////////////////////

      /// <summary>
      /// Encrypts n Blocks of 16 Bytes in ECB mode
      /// </summary>
      template<bool ALIGNED = false>
      INLINE void encryptECB(const void* in, void* out, const size_t n)
      {
         __m128i* bin  = (__m128i*)in;
         __m128i* bout = (__m128i*)out;
         __m128i* bine = bin + n;
         __m128i  m;
         while (bin < bine)
         {
            m = load<ALIGNED>(bin++);
            encrypt(m);
            store<ALIGNED>(bout++, m);
         }
      }

      /// <summary>
      /// Decrypts n Blocks of 16 Bytes in ECB mode
      /// </summary>
      template<bool ALIGNED = false>
      INLINE void decryptECB(const void* in, void* out, const size_t n)
      {
         __m128i* bin  = (__m128i*)in;
         __m128i* bout = (__m128i*)out;
         __m128i* bine = bin + n;
         __m128i  m;
         while (bin < bine)
         {
            m = load<ALIGNED>(bin++);
            decrypt(m);
            store<ALIGNED>(bout++, m);
         }
      }

      /// <summary>
      /// Encrypts n Blocks of 16 Bytes in CBC mode
      /// </summary>
      template<bool ALIGNED = false>
      INLINE void encryptCBC(const void* in, void* out, void* ivec, const size_t n)
      {
         __m128i  iv   = load<ALIGNED>(ivec);
         __m128i* bin  = (__m128i*)in;
         __m128i* bout = (__m128i*)out;
         __m128i* bine = bin + n;
         __m128i  m;
         while (bin < bine)
         {
            m = load<ALIGNED>(bin++);
            encrypt(m, iv);
            store<ALIGNED>(bout++, m);
         }
         store<ALIGNED>(ivec, iv);
      }

      /// <summary>
      /// Decrypts n Blocks of 16 Bytes in CBC mode
      /// </summary>
      template<bool ALIGNED = false>
      INLINE void decryptCBC(const void* in, void* out, void* ivec, const size_t n)
      {
         __m128i  iv   = load<ALIGNED>(ivec);
         __m128i* bin  = (__m128i*)in;
         __m128i* bout = (__m128i*)out;
         __m128i* bine = bin + n;
         __m128i  m;
         while (bin < bine)
         {
            m = load<ALIGNED>(bin++);
            decrypt(m, iv);
            store<ALIGNED>(bout++, m);
         }
         store<ALIGNED>(ivec, iv);
      }

      /// <summary>
      /// Encrypts len Bytes in CTR mode.
      /// Performs 64-Bit increment on the counter part of ivec.
      /// </summary>
      template<bool ALIGNED = false>
      INLINE void encryptCTR(const void* in, void* out, void* ivec, size_t len)
      {
         const __m128i& ONE   = _mm_set_epi32(0,1,0,0);
         const __m128i& BSWAP = _mm_setr_epi8(7,6,5,4,3,2,1,0,15,14,13,12,11,10,9,8);

         __m128i  ctr  = _mm_shuffle_epi8(load<ALIGNED>(ivec), BSWAP);
         __m128i* bin  = (__m128i*)in;
         __m128i* bout = (__m128i*)out;
         __m128i  enc;

         while (len)
         {
            enc = _mm_shuffle_epi8(ctr, BSWAP);
            ctr = _mm_add_epi64(ctr, ONE);
            encrypt(enc);

            if (len >= 16U)
            {
               store<ALIGNED>(bout++, _mm_xor_si128(enc, load<ALIGNED>(bin++)));
               len -= 16U;
            }
            else
            {
               uint8_t* cin  = (uint8_t*)bin;
               uint8_t* cout = (uint8_t*)bout;
               uint8_t* cend = (uint8_t*)cin + len;
               uint8_t* cenc  = (uint8_t*)&enc;
               if (cin + 8U <= cend)
               {
                  *(uint64_t*)cout = *(uint64_t*)cenc ^ *(uint64_t*)cin;
                  cin  += 8U;
                  cout += 8U;
                  cenc += 8U;
               }
               if (cin + 4U <= cend)
               {
                  *(uint32_t*)cout = *(uint32_t*)cenc ^ *(uint32_t*)cin;
                  cin  += 4U;
                  cout += 4U;
                  cenc += 4U;
               }
               if (cin + 2U <= cend)
               {
                  *(uint16_t*)cout = *(uint16_t*)cenc ^ *(uint16_t*)cin;
                  cin  += 2U;
                  cout += 2U;
                  cenc += 2U;
               }
               if (cin < cend) *cout = *cenc ^ *cin;
               break;
            }
         }
         store<ALIGNED>(ivec, _mm_shuffle_epi8(ctr, BSWAP));
      }

      /// <summary>
      /// Decrypts len Bytes in CTR mode
      /// </summary>
      template<bool ALIGNED = false>
      INLINE void decryptCTR(const void* in, void* out, void* ivec, const size_t len)
      {
         encryptCTR<ALIGNED>(in, out, ivec, len);
      }
   };

   /// <summary>
   /// AES128 AES-NI
   /// </summary>
   class CPPCORE_ALIGN64 AES128s : public AESs<CPPCORE_AES_ROUNDS_128>
   {
   protected:
      template<int C> 
      INLINE __m128i keyassist(__m128i k) const
      {
         __m128i kg;
         kg = _mm_shuffle_epi32(_mm_aeskeygenassist_si128(k, C), 0xff);
         k  = _mm_xor_si128(k, _mm_slli_si128(k, 0x4));
         k  = _mm_xor_si128(k, _mm_slli_si128(k, 0x4));
         k  = _mm_xor_si128(k, _mm_slli_si128(k, 0x4));
         return _mm_xor_si128(k, kg);
      }

   public:
      /// <summary>
      /// Empty Constructor. Call reset() before using the instance!
      /// </summary>
      INLINE AES128s() : AESs<CPPCORE_AES_ROUNDS_128>() { }

      /// <summary>
      /// Constructor. Key must be 16 Bytes.
      /// </summary>
      INLINE AES128s(const void* key, const bool builddec = true) : 
         AESs<CPPCORE_AES_ROUNDS_128>()
      {
         reset(key, builddec);
      }

      /// <summary>
      /// Reset with new key
      /// </summary>
      INLINE void reset(const void* key, const bool builddec = true)
      {
         // generate encryption key schedule
         ek[0]  = _mm_loadu_si128((const __m128i*)key);
         ek[1]  = keyassist<0x01>(ek[0]);
         ek[2]  = keyassist<0x02>(ek[1]);
         ek[3]  = keyassist<0x04>(ek[2]);
         ek[4]  = keyassist<0x08>(ek[3]);
         ek[5]  = keyassist<0x10>(ek[4]);
         ek[6]  = keyassist<0x20>(ek[5]);
         ek[7]  = keyassist<0x40>(ek[6]);
         ek[8]  = keyassist<0x80>(ek[7]);
         ek[9]  = keyassist<0x1B>(ek[8]);
         ek[10] = keyassist<0x36>(ek[9]);

         // generate decryption key schedule
         if (builddec)
         {
            dk[0]  = ek[10];
            dk[1]  = _mm_aesimc_si128(ek[9]);
            dk[2]  = _mm_aesimc_si128(ek[8]);
            dk[3]  = _mm_aesimc_si128(ek[7]);
            dk[4]  = _mm_aesimc_si128(ek[6]);
            dk[5]  = _mm_aesimc_si128(ek[5]);
            dk[6]  = _mm_aesimc_si128(ek[4]);
            dk[7]  = _mm_aesimc_si128(ek[3]);
            dk[8]  = _mm_aesimc_si128(ek[2]);
            dk[9]  = _mm_aesimc_si128(ek[1]);
            dk[10] = ek[0];
         }
      }
   };

   /// <summary>
   /// AES192 AES-NI
   /// </summary>
   class CPPCORE_ALIGN64 AES192s : public AESs<CPPCORE_AES_ROUNDS_192>
   {
   protected:
      template<int N> 
      INLINE void keyassist(__m128i& t1, __m128i& t2) const
      { 
         __m128i t3, t4;
         t3 = _mm_aeskeygenassist_si128(t2, N);
         t3 = _mm_shuffle_epi32(t3, 0x55);
         t4 = _mm_slli_si128(t1, 0x04);
         t1 = _mm_xor_si128(t1, t4);
         t4 = _mm_slli_si128(t4, 0x04);
         t1 = _mm_xor_si128(t1, t4);
         t4 = _mm_slli_si128(t4, 0x04);
         t1 = _mm_xor_si128(t1, t4);
         t1 = _mm_xor_si128(t1, t3);
         t3 = _mm_shuffle_epi32(t1, 0xff);
         t4 = _mm_slli_si128(t2, 0x04);
         t2 = _mm_xor_si128(t2, t4);
         t2 = _mm_xor_si128(t2, t3);
      }

      template<int N> 
      static INLINE __m128i shuffle(const __m128i& a, const __m128i& b)
      {
         return _mm_castpd_si128(
            _mm_shuffle_pd(_mm_castsi128_pd(a), _mm_castsi128_pd(b), N));
      }

   public:
      /// <summary>
      /// Empty Constructor. Call reset() before using the instance!
      /// </summary>
      INLINE AES192s() : AESs<CPPCORE_AES_ROUNDS_192>() { }

      /// <summary>
      /// Constructor. Key must be 24 Bytes.
      /// </summary>
      INLINE AES192s(const void* key, const bool builddec = true) : 
         AESs<CPPCORE_AES_ROUNDS_192>()
      {
         reset(key, builddec);
      }

      /// <summary>
      /// Reset with new key
      /// </summary>
      INLINE void reset(const void* key, const bool builddec = true)
      {
         // generate encryption key schedule
         __m128i t1, t2;
         ek[0] = t1 = _mm_loadu_si128(&((const __m128i*)key)[0]);
         ek[1] = t2 = _mm_loadu_si128(&((const __m128i*)key)[1]);
         keyassist<0x01>(t1, t2);
         ek[1] = shuffle<0>(ek[1], t1);
         ek[2] = shuffle<1>(t1, t2);
         keyassist<0x02>(t1, t2);
         ek[3] = t1;
         ek[4] = t2;
         keyassist<0x04>(t1, t2);
         ek[4] = shuffle<0>(ek[4], t1);
         ek[5] = shuffle<1>(t1, t2);
         keyassist<0x08>(t1, t2);
         ek[6] = t1;
         ek[7] = t2;
         keyassist<0x10>(t1, t2);
         ek[7] = shuffle<0>(ek[7], t1);
         ek[8] = shuffle<1>(t1, t2);
         keyassist<0x20>(t1, t2);
         ek[9] = t1;
         ek[10] = t2;
         keyassist<0x40>(t1, t2);
         ek[10] = shuffle<0>(ek[10], t1);
         ek[11] = shuffle<1>(t1, t2);
         keyassist<0x80>(t1, t2);
         ek[12] = t1;

         // generate decryption key schedule
         if (builddec)
         {
            dk[0]  = ek[12];
            dk[1]  = _mm_aesimc_si128(ek[11]);
            dk[2]  = _mm_aesimc_si128(ek[10]);
            dk[3]  = _mm_aesimc_si128(ek[9]);
            dk[4]  = _mm_aesimc_si128(ek[8]);
            dk[5]  = _mm_aesimc_si128(ek[7]);
            dk[6]  = _mm_aesimc_si128(ek[6]);
            dk[7]  = _mm_aesimc_si128(ek[5]);
            dk[8]  = _mm_aesimc_si128(ek[4]);
            dk[9]  = _mm_aesimc_si128(ek[3]);
            dk[10] = _mm_aesimc_si128(ek[2]);
            dk[11] = _mm_aesimc_si128(ek[1]);
            dk[12] = ek[0];
         }
      }
   };

   /// <summary>
   /// AES256 AES-NI
   /// </summary>
   class CPPCORE_ALIGN64 AES256s : public AESs<CPPCORE_AES_ROUNDS_256>
   {
   protected:
      template<int C> 
      INLINE __m128i keyassist1(__m128i& t1, __m128i t2) const
      {
         __m128i t3;
         t2 = _mm_aeskeygenassist_si128(t2, C);
         t2 = _mm_shuffle_epi32(t2, 0xff);
         t3 = _mm_slli_si128(t1, 0x4);
         t1 = _mm_xor_si128(t1, t3);
         t3 = _mm_slli_si128(t3, 0x4);
         t1 = _mm_xor_si128(t1, t3);
         t3 = _mm_slli_si128(t3, 0x4);
         t1 = _mm_xor_si128(t1, t3);
         t1 = _mm_xor_si128(t1, t2);
         return t1;
      }

      INLINE __m128i keyassist2(__m128i t1, __m128i& t2) const
      {
         __m128i t3;
         t1 = _mm_aeskeygenassist_si128(t1, 0x0);
         t3 = _mm_shuffle_epi32(t1, 0xaa);
         t1 = _mm_slli_si128(t2, 0x4);
         t2 = _mm_xor_si128(t2, t1);
         t1 = _mm_slli_si128(t1, 0x4);
         t2 = _mm_xor_si128(t2, t1);
         t1 = _mm_slli_si128(t1, 0x4);
         t2 = _mm_xor_si128(t2, t1);
         t2 = _mm_xor_si128(t2, t3);
         return t2;
      }

   public:
      /// <summary>
      /// Empty Constructor. Call reset() before using the instance!
      /// </summary>
      INLINE AES256s() : AESs<CPPCORE_AES_ROUNDS_256>() { }

      /// <summary>
      /// Constructor. Key must be 32 Bytes.
      /// </summary>
      INLINE AES256s(const void* key, const bool builddec = true) : 
         AESs<CPPCORE_AES_ROUNDS_256>()
      {
         reset(key, builddec);
      }

      /// <summary>
      /// Reset with new key
      /// </summary>
      INLINE void reset(const void* key, const bool builddec = true)
      {
         // generate encryption key schedule
         __m128i t1, t2;
         ek[0]  = t1 = _mm_loadu_si128(&((const __m128i*)key)[0]);
         ek[1]  = t2 = _mm_loadu_si128(&((const __m128i*)key)[1]);
         ek[2]  = keyassist1<0x01>(t1, t2);
         ek[3]  = keyassist2(t1, t2);
         ek[4]  = keyassist1<0x02>(t1, t2);
         ek[5]  = keyassist2(t1, t2);
         ek[6]  = keyassist1<0x04>(t1, t2);
         ek[7]  = keyassist2(t1, t2);
         ek[8]  = keyassist1<0x08>(t1, t2);
         ek[9]  = keyassist2(t1, t2);
         ek[10] = keyassist1<0x10>(t1, t2);
         ek[11] = keyassist2(t1, t2);
         ek[12] = keyassist1<0x20>(t1, t2);
         ek[13] = keyassist2(t1, t2);
         ek[14] = keyassist1<0x40>(t1, t2);

         // generate decryption key schedule
         if (builddec)
         {
            dk[0]  = ek[14];
            dk[1]  = _mm_aesimc_si128(ek[13]);
            dk[2]  = _mm_aesimc_si128(ek[12]);
            dk[3]  = _mm_aesimc_si128(ek[11]);
            dk[4]  = _mm_aesimc_si128(ek[10]);
            dk[5]  = _mm_aesimc_si128(ek[9]);
            dk[6]  = _mm_aesimc_si128(ek[8]);
            dk[7]  = _mm_aesimc_si128(ek[7]);
            dk[8]  = _mm_aesimc_si128(ek[6]);
            dk[9]  = _mm_aesimc_si128(ek[5]);
            dk[10] = _mm_aesimc_si128(ek[4]);
            dk[11] = _mm_aesimc_si128(ek[3]);
            dk[12] = _mm_aesimc_si128(ek[2]);
            dk[13] = _mm_aesimc_si128(ek[1]);
            dk[14] = ek[0];
         }
      }
   };
#endif
   
   /////////////////////////////////////////////////////////////////////////////////////////////////
   // DEFAULT SELECTION
   /////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(CPPCORE_CPUFEAT_AES) && defined(CPPCORE_CPUFEAT_SSE41)
   using AES128 = AES128s;
   using AES192 = AES192s;
   using AES256 = AES256s;
#else
   using AES128 = AES128g;
   using AES192 = AES192g;
   using AES256 = AES256g;
#endif
}
