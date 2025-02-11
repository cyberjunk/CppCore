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

/*int main_encode()
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

   //const __m128i clt = _mm_cmplt_epi8(val, CMP);
   //const __m128i cge = _mm_xor_si128(clt, _mm_cmpeq_epi8(clt, clt));
   //const __m128i add = _mm_or_si128(
   //   _mm_and_si128(ADD_NUM, clt),
   //   _mm_and_si128(ADD_ALP, cge));

   const __m128i clt = _mm_cmplt_epi8(val, CMP);
   const __m128i add = _mm_or_si128(
      _mm_and_si128(ADD_NUM, clt),
      _mm_andnot_si128(clt, ADD_ALP));

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
}*/

int main()
{     
   const bool reverse = true;

   //__m128i SHUF1 = _mm_setr_epi8(14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
   __m128i SHUF2 = reverse ? 
      _mm_setr_epi8(14,12,10,8,6,4,2,0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80) :
      _mm_setr_epi8(0,2,4,6,8,10,12,14,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80);
   __m128i SHUF3 = reverse ? 
      _mm_setr_epi8(15,13,11,9,7,5,3,1,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80) :
      _mm_setr_epi8(1,3,5,7,9,11,13,15,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80);
   __m128i cmp1_min = _mm_set1_epi8('0'-1); // ge 0
   __m128i cmp1_max = _mm_set1_epi8('9'+1); // le 9
   __m128i cmp1_sub = _mm_set1_epi8('0');
   __m128i cmp2_min = _mm_set1_epi8('A'-1); // ge A
   __m128i cmp2_max = _mm_set1_epi8('F'+1); // le F
   __m128i cmp2_sub = _mm_set1_epi8('A'-10);
   __m128i cmp3_min = _mm_set1_epi8('a'-1); // ge a
   __m128i cmp3_max = _mm_set1_epi8('f'+1); // le f
   __m128i cmp3_sub = _mm_set1_epi8('a'-10);
   
   __m128i e = _mm_setzero_si128();

   char* input = "a1f2f3f4f5f6f7F9";
   uint8_t temp[16];
   uint8_t output[8];

   __m128i val = _mm_loadu_si128((__m128i*)input);

   //if (reverse)
   //   val = _mm_shuffle_epi8(val, SHUF1);

   _mm_storeu_si128((__m128i*)temp, val);
   for (size_t i = 0; i < 16; i++)
   {
      std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)temp[i] << " ";
   }
   std::cout << std::endl;

   __m128i cmp1_gt = _mm_cmpgt_epi8(val, cmp1_min);
   __m128i cmp1_lt = _mm_cmplt_epi8(val, cmp1_max);
   __m128i cmp1 = _mm_and_si128(cmp1_gt, cmp1_lt);
   __m128i cmp1_suba = _mm_and_si128(cmp1_sub, cmp1);

   __m128i cmp2_gt = _mm_cmpgt_epi8(val, cmp2_min);
   __m128i cmp2_lt = _mm_cmplt_epi8(val, cmp2_max);
   __m128i cmp2 = _mm_and_si128(cmp2_gt, cmp2_lt);
   __m128i cmp2_suba = _mm_and_si128(cmp2_sub, cmp2);

   __m128i cmp3_gt = _mm_cmpgt_epi8(val, cmp3_min);
   __m128i cmp3_lt = _mm_cmplt_epi8(val, cmp3_max);
   __m128i cmp3 = _mm_and_si128(cmp3_gt, cmp3_lt);
   __m128i cmp3_suba = _mm_and_si128(cmp3_sub, cmp3);

   __m128i sub = _mm_or_si128(cmp1_suba, _mm_or_si128(cmp2_suba, cmp3_suba));

   e = _mm_or_si128(e, _mm_cmpeq_epi8(sub, _mm_setzero_si128()));
   if (_mm_testz_si128(e, e) == 0)
   {
      std::cout << "ERROR" << std::endl;
   }

   val = _mm_sub_epi8(val, sub);

   __m128i v1 = _mm_shuffle_epi8(val, SHUF2);
   __m128i v2 = _mm_shuffle_epi8(val, SHUF3);
   __m128i v3 = _mm_or_si128(_mm_slli_epi64(v1, 4), v2);

   _mm_storeu_si64(output, v3);
   
   for (size_t i = 0; i < 8; i++)
   {
      std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)output[i] << " ";
   }
   std::cout << std::endl;
}
