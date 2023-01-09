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
   template<typename HASHER, typename DIGEST>
   class Hash
   {
   protected:
      INLINE Hash() { }
      INLINE HASHER& thiss() { return *(HASHER*)this; }

   public:
      using Digest = DIGEST;

      /// <summary>
      /// Step on char* string with unknown length.
      /// </summary>
      INLINE void step(char* data)
      {
         thiss().step(data, ::strlen(data));
      }

      /// <summary>
      /// Step on const char* string with unknown length.
      /// </summary>
      INLINE void step(const char* data)
      {
         thiss().step(data, ::strlen(data));
      }

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
      /// Specialization: Step on const string
      /// </summary>
      template<> INLINE void step<const string>(const string& data)
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
      /// Specialization: Step on const string_view
      /// </summary>
      template<> INLINE void step<const string_view>(const string_view& data)
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
      /// Specialization: Step on const wstring
      /// </summary>
      template<> INLINE void step<const wstring>(const wstring& data)
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
      /// Specialization: Step on const wstring_view
      /// </summary>
      template<> INLINE void step<const wstring_view>(const wstring_view& data)
      {
         thiss().step(data.data(), data.size() * sizeof(wchar_t));
      }

      /// <summary>
      /// Specialization: Step on path
      /// </summary>
      template<> INLINE void step<path>(path& data)
      {
         thiss().step(data.native());
      }

      /// <summary>
      /// Specialization: Step on const path
      /// </summary>
      template<> INLINE void step<const path>(const path& data)
      {
         thiss().step(data.native());
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
               thiss().step(buf, (size_t)read);
         }
      }

      /// <summary>
      /// Specialization: Step on ifstream
      /// </summary>
      template<> INLINE void step<ifstream>(ifstream& stream)
      {
         thiss().template step<istream>(stream);
      }

      /// <summary>
      /// Step on path or file path contents.
      /// </summary>
      template<bool CONTENTS = false>
      INLINE void step(const path& data)
      {
         if constexpr (CONTENTS)
         {
            ifstream stream(data.native(), ifstream::binary | ifstream::in);
            if (!stream.is_open()) CPPCORE_UNLIKELY
               return;
            thiss().template step<ifstream>(stream);
            stream.close();
         }
         else
            thiss().template step<const path>(data);
      }

      //////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Calculates hash of memory with given length.
      /// Shortcut for calling reset(), step() and finish().
      /// </summary>
      INLINE void hash(const void* data, size_t length, Digest& digest)
      {
         thiss().reset();
         thiss().step(data, length);
         thiss().finish(digest);
      }

      /// <summary>
      /// Hash of char* string with unknown length.
      /// </summary>
      INLINE void hash(char* data, Digest& digest)
      {
         thiss().hash(data, ::strlen(data), digest);
      }

      /// <summary>
      /// Hash of const char* string with unknown length.
      /// </summary>
      INLINE void hash(const char* data, Digest& digest)
      {
         thiss().hash(data, ::strlen(data), digest);
      }

      /// <summary>
      /// Calculates hash of memory of any type.
      /// Shortcut for calling reset(), step() and finish().
      /// </summary>
      template<typename T>
      INLINE void hash(T& data, Digest& digest)
      {
         thiss().hash(&data, sizeof(T), digest);
      }

      /// <summary>
      /// Specialization: Hash of string
      /// </summary>
      template<> INLINE void hash<string>(string& data, Digest& digest)
      {
         thiss().hash(data.c_str(), data.length(), digest);
      }

      /// <summary>
      /// Specialization: Hash of const string
      /// </summary>
      template<> INLINE void hash<const string>(const string& data, Digest& digest)
      {
         thiss().hash(data.c_str(), data.length(), digest);
      }

      /// <summary>
      /// Specialization: Hash of string_view
      /// </summary>
      template<> INLINE void hash<string_view>(string_view& data, Digest& digest)
      {
         thiss().hash(data.data(), data.length(), digest);
      }

      /// <summary>
      /// Specialization: Hash of const string_view
      /// </summary>
      template<> INLINE void hash<const string_view>(const string_view& data, Digest& digest)
      {
         thiss().hash(data.data(), data.length(), digest);
      }

      /// <summary>
      /// Specialization: Hash of wstring
      /// </summary>
      template<> INLINE void hash<wstring>(wstring& data, Digest& digest)
      {
         thiss().hash(data.c_str(), data.size() * sizeof(wchar_t), digest);
      }

      /// <summary>
      /// Specialization: Hash of const wstring
      /// </summary>
      template<> INLINE void hash<const wstring>(const wstring& data, Digest& digest)
      {
         thiss().hash(data.c_str(), data.size() * sizeof(wchar_t), digest);
      }

      /// <summary>
      /// Specialization: Hash of string_view
      /// </summary>
      template<> INLINE void hash<wstring_view>(wstring_view& data, Digest& digest)
      {
         thiss().hash(data.data(), data.size() * sizeof(wchar_t), digest);
      }

      /// <summary>
      /// Specialization: Hash of const string_view
      /// </summary>
      template<> INLINE void hash<const wstring_view>(const wstring_view& data, Digest& digest)
      {
         thiss().hash(data.data(), data.size() * sizeof(wchar_t), digest);
      }

      /// <summary>
      /// Specialization: Hash of istream
      /// </summary>
      template<> INLINE void hash<istream>(istream& stream, Digest& digest)
      {
         thiss().reset();
         thiss().step(stream);
         thiss().finish(digest);
      }

      /// <summary>
      /// Specialization: Hash of ifstream
      /// </summary>
      template<> INLINE void hash<ifstream>(ifstream& stream, Digest& digest)
      {
         thiss().template hash<istream>(stream, digest);
      }

      /// <summary>
      /// Specialization: Hash of path
      /// </summary>
      template<> INLINE void hash<path>(path& path, Digest& digest)
      {
         thiss().reset();
         thiss().step(path);
         thiss().finish(digest);
      }

      /// <summary>
      /// Specialization: Hash of const path
      /// </summary>
      template<> INLINE void hash<const path>(const path& path, Digest& digest)
      {
         thiss().reset();
         thiss().step(path);
         thiss().finish(digest);
      }

      /// <summary>
      /// Hash of path or file path contents
      /// </summary>
      template<bool CONTENTS = false>
      INLINE void hash(const path& data, Digest& digest)
      {
         thiss().reset();
         thiss().step<CONTENTS>(data);
         thiss().finish(digest);
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
      INLINE static bool hashMem(const void* data, const size_t len, Digest& digest)
      {
         if (!data || !len) CPPCORE_UNLIKELY
            return false;

         HASHER hsh;
         hsh.step(data, len);
         hsh.finish(digest);

         // replaces all 0x00 by 0x01
         if (REPLACEZEROS)
            replaceByte((uint8_t*)&digest, 16, 0x00, 0x01);

         return true;
      }

      /// <summary>
      /// Calculates hash of an input stream into digest.
      /// </summary>
      INLINE static bool hashStream(istream& s, Digest& digest)
      {
         HASHER hsh;
         hsh.step(s);
         hsh.finish(digest);

         return true;
      }

      /// <summary>
      /// Calculates hash of a file into digest.
      /// </summary>
      INLINE static bool hashFile(const string& file, Digest& digest)
      {
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
