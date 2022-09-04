#pragma once

#include <CppCore/Root.h>

namespace CppCore
{
   /// <summary>
   /// System
   /// </summary>
   class System
   {
   public:
      /// <summary>
      /// Info about Display
      /// </summary>
      class Display
      {
      public:
         uint32_t bpp;
         uint32_t width;
         uint32_t height;
         uint32_t frequency;
      };

      /// <summary>
      /// Info about CPU
      /// </summary>
      class Cpu
      {
      public:
         uint32_t coresphysical;
         uint32_t coreslogical;
      };

      /// <summary>
      /// Info about Folders
      /// </summary>
      class Folder
      {
      public:
         /// <summary>
         /// Returns a temp path to use on this system/user.
         /// </summary>
         INLINE static path getTemp()
         {
            return std::filesystem::temp_directory_path();
         }

         /// <summary>
         /// Returns the curren path of the process.
         /// </summary>
         INLINE static path getCurrent()
         {
            return std::filesystem::current_path();
         }

         /// <summary>
         /// Returns the home folder of the current user.
         /// </summary>
         INLINE static path getHome()
         {
         #if defined(CPPCORE_OS_WINDOWS)
            return path(::getenv("USERPROFILE"));
         #else
            struct passwd* pw = ::getpwuid(::getuid());
            return path(pw->pw_dir);
         #endif
         }

         /// <summary>
         /// Returns full path with filename 
         /// of the current executable.
         /// </summary>
         INLINE static path getExecutable()
         {
         #if defined(CPPCORE_OS_WINDOWS)
            char name[MAX_PATH+1];
            const DWORD len = GetModuleFileName(0, name, sizeof(name));
            return len ? path(name) : path();
         #elif defined(CPPCORE_OS_OSX)
            char name[MAX_PATH+1];
            uint32_t size = sizeof(name);
            return _NSGetExecutablePath(name, &size) == 0 ? path(name) : path();
         #else
            return std::filesystem::canonical("/proc/self/exe");
         #endif
         }

         /// <summary>
         /// Returns the filename of the executable without a path.
         /// </summary>
         INLINE static path getExecutableName()
         {
            return getExecutable().filename();
         }

         /// <summary>
         /// Returns the path containing the executable
         /// </summary>
         INLINE static path getExecutablePath()
         {
            return getExecutable().remove_filename();
         }
      };

      /// <summary>
      /// Returns true if the current process is a 64-bit process
      /// </summary>
      INLINE static bool is64BitProcess()
      {
         return sizeof(void*) == 8U;
      }

      /// <summary>
      /// Returns the installed RAM size (or 0 if not retrievable).
      /// </summary>
      INLINE static uint64_t getRamSize()
      {
      #ifdef CPPCORE_OS_WINDOWS
         ULONGLONG m;
         return GetPhysicallyInstalledSystemMemory(&m) ? m * 1024U : 0;
      #else
         return 0U;
      #endif
      }

      /// <summary>
      /// Sets cpu info including physical and logical cores counts.
      /// </summary>
      INLINE static bool getCpuInfo(Cpu& cpu)
      {
      #ifdef CPPCORE_OS_WINDOWS
         cpu.coresphysical = cpu.coreslogical = 0;
         char* buf = NULL;
         DWORD len = 0;
         if (FALSE == GetLogicalProcessorInformationEx(RelationAll, (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)buf, &len)) 
         {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
               bool success;
               buf = (char*)malloc(len);
               if ((success = GetLogicalProcessorInformationEx(RelationAll, (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)buf, &len)))
               {
                  DWORD offset = 0;
                  char* ptr = buf;
                  while (ptr < buf + len) 
                  {
                     PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX pi = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)ptr;
                     if (pi->Relationship == RelationProcessorCore)
                     {
                        cpu.coresphysical++;
                        for (size_t g = 0; g < pi->Processor.GroupCount; ++g)
                        {
                           DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
                           DWORD bitSetCount = 0;
                           ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
                           for (DWORD i = 0; i <= LSHIFT; ++i) {
                              bitSetCount += ((pi->Processor.GroupMask[g].Mask & bitTest) ? 1 : 0);
                              bitTest /= 2;
                           }
                           cpu.coreslogical += bitSetCount;
                        }
                     }
                     ptr += pi->Size;
                  }
               }
               free(buf);
               if (success)
                  return true;
            }
         }
         return false;
      #else
         cpu.coresphysical = cpu.coreslogical = 1;
         return false;
      #endif
      }

      /// <summary>
      /// Returns info about the current display of the application.
      /// </summary>
      INLINE static bool getCurrentDisplayInfo(Display& display)
      {
      #ifdef CPPCORE_OS_WINDOWS
         DEVMODEA data;
         data.dmSize = sizeof(DEVMODEA);
         if (EnumDisplaySettingsA(0, ENUM_CURRENT_SETTINGS, &data))
         {
            display.bpp       = data.dmBitsPerPel;
            display.width     = data.dmPelsWidth;
            display.height    = data.dmPelsHeight;
            display.frequency = data.dmDisplayFrequency;
            return true;
         }
         else
         {
            display.bpp       = 32;
            display.width     = 640;
            display.height    = 480;
            display.frequency = 60;
            return false;
         }
      #else
         display.bpp       = 32;
         display.width     = 640;
         display.height    = 480;
         display.frequency = 60;
         return false;
      #endif
      }
   };
}
