#pragma once

#include <CppCore/Root.h>
#include <CppCore/Memory.h>
#include <CppCore/Block.h>
#include <CppCore/Math/Util.h>

namespace CppCore
{
   /// <summary>
   /// Base Class for Hashes
   /// </summary>
   template<typename HASHER>
   class Hash
   {
   protected:
      INLINE Hash() { }
      INLINE HASHER& thiss() { return *(HASHER*)this; }
   public:
      INLINE void reset()                               { assert(false); }
      INLINE void step(const void* data, size_t length) { assert(false); }
      INLINE void finish(void* digest)                  { assert(false); }

      //////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Step on memory of any type T
      /// </summary>
      template<typename T> 
      INLINE void step(T& data)
      {
         thiss().step(&data, sizeof(T));
      }

      /// <summary>
      /// Specialization: Step on string
      /// </summary>
      template<> INLINE void step<string>(string& data)
      {
         thiss().step(data.c_str(), data.length());
      }

      /// <summary>
      /// Specialization: Step on string_view
      /// </summary>
      template<> INLINE void step<string_view>(string_view& data)
      {
         thiss().step(data.data(), data.length());
      }

      /// <summary>
      /// Specialization: Step on wstring
      /// </summary>
      template<> INLINE void step<wstring>(wstring& data)
      {
         thiss().step(data.c_str(), data.size() * sizeof(wchar_t));
      }

      /// <summary>
      /// Specialization: Step on wstring_view
      /// </summary>
      template<> INLINE void step<wstring_view>(wstring_view& data)
      {
         thiss().step(data.data(), data.size() * sizeof(wchar_t));
      }

      /// <summary>
      /// Specialization: Step on istream
      /// </summary>
      template<> INLINE void step<istream>(istream& stream)
      {
         CPPCORE_ALIGN64 char buf[8192];
         stream.clear();
         stream.seekg(0, stream.beg);
         while (stream.good())
         {
            stream.read(buf, sizeof(buf));
            const std::streamsize read = stream.gcount();
            if (read)
               thiss().step(buf, read);
         }
      }

      /// <summary>
      /// Specialization: Step on ifstream
      /// </summary>
      template<> INLINE void step<ifstream>(ifstream& stream)
      {
         thiss().template step<istream>(stream);
      }

      //////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Calculates hash of memory with given length.
      /// Shortcut for calling reset(), step() and finish().
      /// </summary>
      INLINE void hash(const void* data, size_t length, void* digest)
      {
         thiss().reset();
         thiss().step(data, length);
         thiss().finish(digest);
      }

      /// <summary>
      /// Calculates hash of memory of any type.
      /// Shortcut for calling reset(), step() and finish().
      /// </summary>
      template<typename T>
      INLINE void hash(T& data, void* digest)
      {
         thiss().hash(&data, sizeof(T), digest);
      }

      /// <summary>
      /// Specialization: Hash of string
      /// </summary>
      template<> INLINE void hash<string>(string& data, void* digest)
      {
         thiss().hash(data.c_str(), data.length(), digest);
      }

      /// <summary>
      /// Specialization: Hash of string_view
      /// </summary>
      template<> INLINE void hash<string_view>(string_view& data, void* digest)
      {
         thiss().hash(data.data(), data.length(), digest);
      }

      /// <summary>
      /// Specialization: Hash of wstring
      /// </summary>
      template<> INLINE void hash<wstring>(wstring& data, void* digest)
      {
         thiss().hash(data.c_str(), data.size() * sizeof(wchar_t), digest);
      }

      /// <summary>
      /// Specialization: Hash of string_view
      /// </summary>
      template<> INLINE void hash<wstring_view>(wstring_view& data, void* digest)
      {
         thiss().hash(data.data(), data.size() * sizeof(wchar_t), digest);
      }

      /// <summary>
      /// Specialization: Hash of istream
      /// </summary>
      template<> INLINE void hash<istream>(istream& stream, void* digest)
      {
         thiss().reset();
         thiss().step(stream);
         thiss().finish(digest);
      }

      /// <summary>
      /// Specialization: Hash of ifstream
      /// </summary>
      template<> INLINE void hash<ifstream>(ifstream& stream, void* digest)
      {
         thiss().template hash<istream>(stream, digest);
      }

      ///////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////

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
      ///////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Calculates hash of arbitrary sized memory.
      /// Hash is returned in digest, default seeds are used.
      /// </summary>
      template<bool REPLACEZEROS = false>
      INLINE static bool hashMem(const void* data, const size_t len, void* digest)
      {
         if (!data || !len || !digest) CPPCORE_UNLIKELY
            return false;

         HASHER hsh;
         hsh.step(data, len);
         hsh.finish(digest);

         // replaces all 0x00 by 0x01
         if (REPLACEZEROS)
            replaceByte((uint8_t*)digest, 16, 0x00, 0x01);

         return true;
      }

      /// <summary>
      /// Calculates hash of an input stream into digest.
      /// </summary>
      INLINE static bool hashStream(istream& s, void* digest)
      {
         if (!digest) CPPCORE_UNLIKELY
            return false;

         HASHER hsh;
         hsh.step(s);
         hsh.finish(digest);

         return true;
      }

      /// <summary>
      /// Calculates hash of a file into digest.
      /// </summary>
      INLINE static bool hashFile(const string& file, void* digest)
      {
         if (!digest) CPPCORE_UNLIKELY
            return false;

         ifstream stream(file, ifstream::binary | ifstream::in);
         if (!stream.is_open()) CPPCORE_UNLIKELY
            return false;

         HASHER hsh;
         hsh.step(stream);
         hsh.finish(digest);

         stream.close();
         return true;
      }
   };
}
