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
   INLINE static uint32_t calcsize(uint32_t type, uint32_t b64, uint32_t cr = 0)
   {
      const uint32_t SL = 5U + 6U + type + 5U + 1U + cr;
      const uint32_t EL = 5U + 4U + type + 5U;
      const uint32_t NL1 = (1U + cr) * (b64 >> 6);
      const uint32_t NL2 = (1U + cr) * ((b64 & 0x3F) != 0);
      return SL + EL + NL1 + NL2 + b64;
   }

   INLINE static void serialize(const char* type, const char* b64, char* out)
   {
      const char* t;
      for (size_t i = 0; i < 5; i++)
         *out++ = '-';
      *out++ = 'B';
      *out++ = 'E';
      *out++ = 'G';
      *out++ = 'I';
      *out++ = 'N';
      *out++ = ' ';
      t = type;
      while (char c = *t++)
         *out++ = c;
      for (size_t i = 0; i < 5; i++)
         *out++ = '-';

      *out++ = '\n';
      //*out++ = '\r';

      uint32_t n = 0;
      while (char c = *b64++) {
         *out++ = c;
         if (++n == 64U) {
            *out++ = '\n';
            n = 0;
         }
      }
      if (n)
         *out++ = '\n';

      for (size_t i = 0; i < 5; i++)
         *out++ = '-';
      *out++ = 'E';
      *out++ = 'N';
      *out++ = 'D';
      *out++ = ' ';
      t = type;
      while (char c = *t++)
         *out++ = c;
      for (size_t i = 0; i < 5; i++)
         *out++ = '-';

      *out = 0x00;

      //0x2D2D2D2D
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

   PEM::serialize("TEST", b64, out);
   uint32_t w = ::strlen(out);
   printf("%s", out);

   //Buffer<8192, true> buf;
   //File::loadToMemory("f:/base64test.txt", buf);
   

   return 0;
}
