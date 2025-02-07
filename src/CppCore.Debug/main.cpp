#include <CppCore/Root.h>
#include <CppCore/Encoding.h>
#include <CppCore/Random.h>
#include <CppCore/Stopwatch.h>

using namespace CppCore;

Stopwatch watch;
Random::Default prng;
uint8_t in[1024*1024*32];
char out[sizeof(in)*2U];

int main_old()
{
   prng.fill(in);

   double t;
   double s;
   double x;

   size_t len = Base64::symbollength(sizeof(in), true);

   watch.reset();
   watch.start();
   Base64::encode(in, sizeof(in), out, true, true);
   watch.stop();
   t = (double)watch.getDuration().count() / 1000000000.0;
   s = (double)sizeof(in) / (double)(1024*1024);
   x = s / t;

   printf("ENCODE: %i MB/s\n", (int)x);

   watch.reset();
   watch.start();
   bool ok = Base64::decode(out, len, (void*)in, true);
   watch.stop();
   t = (double)watch.getDuration().count() / 1000000000.0;
   s = (double)len / (double)(1024 * 1024);
   x = s / t;

   printf("DECODE: %i MB/s (%i)\n", (int)x, ok);

   return 0;
}

int main()
{
   constexpr bool UPPERCASE = false;
   constexpr bool REVERSE   = false;

   const __m128i SHUF = REVERSE ? 
      _mm_setr_epi8(7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0) :
      _mm_set_epi8 (7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0);
   const __m128i M1 = _mm_set_epi8(
      0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00,
      0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00);
   const __m128i M2 = _mm_srli_si128(M1, 1);
   const __m128i CMP = _mm_set1_epi8(0x0A);
   const __m128i ADD_NUM = _mm_set1_epi8('0');
   const __m128i ADD_ALP = UPPERCASE ? 
      _mm_set1_epi8('A'-10) :
      _mm_set1_epi8('a'-10);

   uint8_t input[8] = { 0xa1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf9 };
   uint8_t output[16];

   __m128i val;

   val = _mm_loadu_si64(input);
   val = _mm_shuffle_epi8(val, SHUF);
   val = _mm_or_si128(
      _mm_and_si128(val, M1), 
      _mm_and_si128(_mm_srli_epi64(val, 4), M2));

   _mm_storeu_epi8(output, val);
   for (size_t i = 0; i < 16; i++)
   {
      std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)output[i] << " ";
   }
   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////////////////////

   const __m128i clt = _mm_cmplt_epi8(val, CMP);
   const __m128i cge = _mm_xor_si128(clt, _mm_cmpeq_epi8(clt, clt));
   const __m128i add = _mm_or_si128(
      _mm_and_si128(ADD_NUM, clt),
      _mm_and_si128(ADD_ALP, cge));

   /////////////////////////////////////////////////////////////////////////////////////////////

   _mm_storeu_epi8(output, add);
   for (size_t i = 0; i < 16; i++)
   {
      std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)output[i] << " ";
   }
   std::cout << std::endl;

   /////////////////////////////////////////////////////////////////////////////////////////////

   _mm_storeu_epi8(output, _mm_add_epi8(val, add));

   for (size_t i = 0; i < 16; i++)
   {
      std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)output[i] << " ";
   }
   std::cout << std::endl;
   std::cout << output;

   int kjdf = 1;
}
