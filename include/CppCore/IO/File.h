#pragma once

#include <CppCore/Root.h>

// OS File Access
#if defined(CPPCORE_OS_WINDOWS)
  #define NOMINMAX
  #include <Windows.h>
#endif

namespace CppCore
{
   /// <summary>
   /// Disk File
   /// </summary>
   class File
   {
   private:
      INLINE File() { }

   public:
      /// <summary>
      /// Loads a file completely to memory
      /// </summary>
      template<typename BUFFER>
      INLINE static bool loadToMemory(const StdString& file, BUFFER& buf)
      {
      #ifdef CPPCORE_OS_WINDOWS
         DWORD read;

         HANDLE h = CreateFileA(
            file.c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_READONLY | FILE_FLAG_SEQUENTIAL_SCAN,
            NULL);

         DWORD size = GetFileSize(h, NULL);

         if (size != INVALID_FILE_SIZE && 
             size <= buf.getSize()     && 
             ReadFile(h, buf.getPtr(), size, &read, NULL))
         {
            CloseHandle(h);
            buf.setLength(read);
            buf.setLengthRead(0);
            return true;
         }
         else
         {
            CloseHandle(h);
            buf.setLength(0);
            buf.setLengthRead(0);
            return false;
         }
      #else
         StdIfStream s(file, StdIfStream::binary | StdIfStream::in | StdIfStream::ate);
         s.rdbuf()->pubsetbuf(0, 0);

         if (!s.is_open())
            return false;

         const int64_t len = s.tellg();
         s.seekg(0, s.beg);

         if (len >= 0 && len <= buf.getSize() && s.read(buf.getPtr(), len))
         {
            s.close();
            buf.setLength((size_t)len);
            buf.setLengthRead(0);
            return true;
         }
         else
         {
            s.close();
            buf.setLength(0);
            buf.setLengthRead(0);
            return false;
         }
      #endif
      }
   };
}
