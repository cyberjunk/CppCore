#pragma once
#pragma warning(disable:26495)

#include <CppCore/Root.h>
#include <CppCore/Random.h>
#include <CppCore/Math/BigInt.h>

namespace CppCore
{
   /// <summary>
   /// Data for Uuid. Must be compatible with uintx unions!
   /// </summary>
   union UuidData
   {
   public:
      struct 
      {
         uint64_t l; 
         uint64_t h; 
      };
      uint64_t i64[2];
      uint32_t i32[2 * 2];
      uint16_t i16[2 * 4];
      uint8_t  i8 [2 * 8];
   #if defined(CPPCORE_CPUFEAT_SSE2)
      __m128i  sse[1];
   #endif
      struct
      {
         uint64_t node     : 48;
         uint64_t clockseq : 14;
         uint64_t variant  : 02;
         uint64_t time_hi  : 12;
         uint64_t version  : 04;
         uint64_t time_mid : 16;
         uint64_t time_low : 32;
      } full;
      struct
      {
         uint64_t node     : 48;
         uint64_t clockseq : 16;
         uint64_t time_hi  : 16;
         uint64_t time_mid : 16;
         uint64_t time_low : 32;
      } basic;
      INLINE UuidData() { }
   };

   /// <summary>
   /// UUID (Version 4, Variant 1)
   /// </summary>
   class Uuid
   {
   protected:
      UuidData d;

   public:
      static const size_t SIZE_STRING = 36; // 32x hexadecimal characters + 4x '-' 
      static const size_t SIZE_BINARY = 16; // 128 bit
      static const size_t VERSION     = 4;  // version 4 only
      static const size_t VARIANT     = 2;  // variant 1 (bin 10 = dec 2)

   public:
      ///////////////////////////////////////////////////////////////////////////////////////
      // CONSTRUCTORS

      /// <summary>
      /// Empty Constructor. NO VALID UUID. Must call generate().
      /// </summary>
      INLINE Uuid() 
      {
      }

      /// <summary>
      /// Efficient constructor using provided random bits (from a generator).
      /// </summary>
      INLINE Uuid(const uint64_t l, const uint64_t h = 0ULL, const bool tag = false)
      {
         d.l = l;
         d.h = h;

         if (tag)
            this->tag();
      }

      /// <summary>
      /// Efficient constructor using provided Pseudo Random Number Generatorr.
      /// </summary>
      template<typename PRNG64 = Random::Default64>
      INLINE Uuid(PRNG64& prng)
      {
         this->generate(prng);
      }

      ///////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Get the version that is encoded into the UUID
      /// </summary>
      INLINE uint64_t getVersion() const
      {
         return d.full.version;
      }

      /// <summary>
      /// Get the variant that is encoded into the UUID
      /// </summary>
      INLINE uint64_t getVariant() const
      {
         return d.full.variant;
      }

      /// <summary>
      /// Checks if a string includes a valid UUID. Does not verify embedded version or variant.
      /// </summary>
      INLINE static bool isUuidString(const StdString& s)
      {
         // validate length
         if (s.length() != SIZE_STRING)
            return false;

         // validate hyphen characters
         if (s[8] != '-' || s[13] != '-' || s[18] != '-' || s[23] != '-')
            return false;

         // validate hexadecimal characters
         return
            isxdigit(s[0]) &&
            isxdigit(s[1]) &&
            isxdigit(s[2]) &&
            isxdigit(s[3]) &&
            isxdigit(s[4]) &&
            isxdigit(s[5]) &&
            isxdigit(s[6]) &&
            isxdigit(s[7]) &&
            isxdigit(s[9]) &&
            isxdigit(s[10]) &&
            isxdigit(s[11]) &&
            isxdigit(s[12]) &&
            isxdigit(s[14]) &&
            isxdigit(s[15]) &&
            isxdigit(s[16]) &&
            isxdigit(s[17]) &&
            isxdigit(s[19]) &&
            isxdigit(s[20]) &&
            isxdigit(s[21]) &&
            isxdigit(s[22]) &&
            isxdigit(s[24]) &&
            isxdigit(s[25]) &&
            isxdigit(s[26]) &&
            isxdigit(s[27]) &&
            isxdigit(s[28]) &&
            isxdigit(s[29]) &&
            isxdigit(s[30]) &&
            isxdigit(s[31]) &&
            isxdigit(s[32]) &&
            isxdigit(s[33]) &&
            isxdigit(s[34]) &&
            isxdigit(s[35]);
      }

      /// <summary>
      /// Sets the version and variant bits in the UUID.
      /// </summary>
      INLINE void tag()
      {
         d.full.version = VERSION; // set version
         d.full.variant = VARIANT; // set variant
      }

      ///////////////////////////////////////////////////////////////////////////////////////
      // GENERATE OPS

      /// <summary>
      /// Generates the UUIDv4 efficiently using provided randoms.
      /// </summary>
      INLINE void generate(const uint64_t rnd1, const uint64_t rnd2)
      {
         d.l = rnd1;  // randomize low 64 bits
         d.h = rnd2;  // randomize high 64 bits
         this->tag();
      }

      /// <summary>
      /// Generates the UUIDv4 efficiently using provided Pseudo Random Number Generator.
      /// </summary>
      template<typename PRNG64 = Random::Default64>
      INLINE void generate(PRNG64& prng)
      {
         this->generate(prng.next(), prng.next());
      }

      /// <summary>
      /// Generates the UUIDv4 inefficiently using on-the-fly initialized and discarded generator.
      /// Don't use this if you have to create a lot of UUIDs or very regulary.
      /// </summary>
      template<typename PRNG64 = Random::Default64>
      INLINE void generate()
      {
         PRNG64 prng;
         this->generate<PRNG64>(prng);
      }

      ///////////////////////////////////////////////////////////////////////////////////////
      // STRING OPS

      /// <summary>
      /// Returns hexadecimal Uuid string with '-' included.
      /// TODO: Optimize this
      /// </summary>
      INLINE ::std::string toUuidString() const
      {
         std::stringstream stream;

         stream 
            << std::setfill('0') << std::setw(8)  << std::hex << d.basic.time_low << '-'
            << std::setfill('0') << std::setw(4)  << std::hex << d.basic.time_mid << '-'
            << std::setfill('0') << std::setw(4)  << std::hex << d.basic.time_hi  << '-'
            << std::setfill('0') << std::setw(4)  << std::hex << d.basic.clockseq << '-'
            << std::setfill('0') << std::setw(12) << std::hex << d.basic.node;

         return stream.str();
      }

      /// <summary>
      /// Parses the UUID from string. Does not guarantee Version 4.
      /// TODO: Optimize this
      /// </summary>
      INLINE bool fromUuidString(const StdString& s)
      {
         if (isUuidString(s))
         {
            std::stringstream ss;

            // 64 bit chunks in string notation
            // hhhhhhhh-hhhh-hhhh-llll-llllllllllll

            // load first 64 high bits
            ss << std::hex << s.substr(0,  8);
            ss << std::hex << s.substr(9,  4);
            ss << std::hex << s.substr(14, 4);
            ss >> d.h;

            ss.clear();

            // load second 64 low bits
            ss << std::hex << s.substr(19, 4);
            ss << std::hex << s.substr(24, 12);
            ss >> d.l;

            return true;
         }
         else
            return false;
      }
      
      ///////////////////////////////////////////////////////////////////////////////////////
      // STATIC OPS

      /// <summary>
      /// Creates a new UUIDv4 inefficiently using on-the-fly initialized and discarded generator.
      /// Don't use this if you have to create a lot of UUIDs or very regulary. See Generator class.
      /// </summary>
      INLINE static Uuid create()
      {
         Uuid id;
         id.generate();
         return id;
      }

      /// <summary>
      /// Creates a new UUIDv4 from given string.
      /// </summary>
      INLINE static Uuid createFromUuidString(const StdString& s)
      {
         Uuid id;
         id.fromUuidString(s);
         return id;
      }
   };

   INLINE std::ostream& operator << (std::ostream& os, const Uuid& v) { os << v.toUuidString(); return os; }
}
#pragma warning(default:26495)
