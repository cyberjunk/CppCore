#include <CppCore/Root.h>
#include <CppCore/Encoding.h>
#include <CppCore/IO/File.h>
#include <CppCore/Buffer.h>
#include <CppCore/Random.h>
#include <CppCore/Stopwatch.h>

using namespace CppCore;

class PEM
{
public:
   static constexpr char PREFIX_SL[11] = { '-','-','-','-','-','B','E','G','I','N',' ' };
   static constexpr char PREFIX_EL[9]  = { '-','-','-','-','-','E','N','D',' ' };
   static constexpr char POSTFIX[6]    = { '-','-','-','-','-','\n' };

   INLINE static size_t calcsize(size_t tlen, size_t blen)
   {
      const size_t SL  = 11U + tlen + 6U;    // start line
      const size_t EL  = 9U  + tlen + 6U;    // end line
      const size_t NL1 = blen >> 6;          // line breaks full rows
      const size_t NL2 = (blen & 0x3F) != 0; // line break tail row
      return SL + EL + NL1 + NL2 + blen;     // sum
   }

   INLINE static void serialize(const char* type, size_t tlen, const char* b64, size_t blen, char* out, bool writeterm = true)
   {
      Memory::copy(out, PREFIX_SL, 11); out += 11;
      Memory::copy(out, type, tlen);    out += tlen;
      Memory::copy(out, POSTFIX, 6);    out += 6;
      while (blen >= 64)
      {
         Memory::singlecopy512(out, b64);
         out  += 64;
         b64  += 64;
         blen -= 64;
         *out++ = '\n';
      }
      if (blen)
      {
         Memory::copy(out, b64, blen);
         out += blen;
         *out++ = '\n';
      }
      Memory::copy(out, PREFIX_EL, 9); out += 9;
      Memory::copy(out, type, tlen);   out += tlen;
      Memory::copy(out, POSTFIX, 6);   out += 6;
      if (writeterm)
         *out = 0x00;
   }
};





char out[8192];
char b64[8192];

int main()
{
   uint64_t v[128];
   CppCore::Random::Default rnd;
   rnd.fill(v);

   Base64::encode(v, b64, false, true);
   
   uint32_t l1 = Base64::symbollength(sizeof(v));
   uint32_t l2 = PEM::calcsize(4, l1);

   PEM::serialize("TEST", 4, b64, l1, out);
   uint32_t w = ::strlen(out);
   printf("%s", out);

   //Buffer<8192, true> buf;
   //File::loadToMemory("f:/base64test.txt", buf);
   

   return 0;
}
