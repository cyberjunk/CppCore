#pragma once

#include <CppCore/Root.h>
#include <CppCore/Memory.h>
#include <CppCore/Block.h>
#include <CppCore/Math/Util.h>

namespace CppCore
{
   /// <summary>
   /// Base Class for Hash Classes
   /// </summary>
   class Hash
   {
   public:
      /// <summary>
      /// Smaller helper
      /// </summary>
      INLINE static void replaceByte(uint8_t* m, const size_t len, const uint8_t oc, const uint8_t nc)
      {
         CPPCORE_UNROLL
         for (size_t i = 0; i < len; i++)
            if (m[i] == oc)
               m[i] = nc;
      }

      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Calculates hash of arbitrary sized memory.
      /// Hash is returned in digest, default seeds are used.
      /// </summary>
      template<typename HASHER>
      INLINE static bool hashMem(const void* data, const size_t len, void* digest)
      {
         if (data == 0 || len == 0 || digest == 0) CPPCORE_UNLIKELY
            return false;

         CPPCORE_ALIGN16 HASHER hasher;
         hasher.step(data, len);
         hasher.finish(digest);

         return true;
      }

      /// <summary>
      /// Calculates hash of an input stream of known length.
      /// Hash is returned in digest, default seeds are used.
      /// </summary>
      template<typename HASHER>
      INLINE static bool hashStream(StdIStream& s, const uint64_t len, void* digest)
      {
         // stream with zero size or null digest
         if (len == 0 || digest == 0) CPPCORE_UNLIKELY
            return false;

         CPPCORE_ALIGN16 HASHER  hasher;
         CPPCORE_ALIGN16 uint8_t buf[8192];

         // full buffers and rest
         const uint64_t full = len >> 13;    // div 8192
         const uint32_t rest = len & 0x1FFF; // mod 8192

         // 8192 byte chunks
         for (uint64_t i = 0; i < full; i++)
         {
            s.read((char*)buf, 8192);
            hasher.step(buf, 8192);
         }

         // 0-8191 byte tail
         s.read((char*)buf, rest);
         hasher.step(buf, rest);

         // finish
         hasher.finish(digest);
         return true;
      }

      /// <summary>
      /// Calculates hash of a file using HASHER class.
      /// Hash is returned in digest, default seeds are used.
      /// </summary>
      template<typename HASHER>
      INLINE static bool hashFile(const StdString& file, void* digest)
      {
         // try open file (at the end)
         StdIfStream stream(file, StdIfStream::binary | StdIfStream::in | StdIfStream::ate);

         // failed to open file
         if (!stream.is_open()) CPPCORE_UNLIKELY
            return false;

         // get stream length
         const uint64_t len = stream.tellg();

         // set position back to begin
         stream.seekg(0, stream.beg);

         // call stream variant with filestream
         const bool ok = HASHER::hashStream(stream, len, digest);

         // close file
         stream.close();
         return ok;
      }
   };
}
