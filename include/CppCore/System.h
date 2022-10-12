#pragma once

#include <CppCore/Root.h>

namespace CppCore
{
   /// <summary>
   /// System
   /// </summary>
   class System
   {
   private:
      INLINE System() { }

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
      /// Special Folders
      /// </summary>
      class Folder
      {
      public:
      #if defined(CPPCORE_OS_WINDOWS)
         class Windows
         {
         public:
            /// <summary>
            /// Returns the roaming AppData path on Windows.
            /// This was removed in Windows 11 and is NOT accessible from sandbox.
            /// </summary>
            /// <remarks>
            /// Regular: C:\Users\NAME\AppData\Roaming
            /// Sandbox: C:\Users\NAME\AppData\Roaming
            /// </remarks>
            INLINE static path getAppDataRoaming()
            {
               const char* p = ::getenv("APPDATA");
               return p ? path(p) : path();
            }

            /// <summary>
            /// Returns the local AppData path on Windows.
            /// Preferred persistent location to store user specific app data.
            /// </summary>
            /// <remarks>
            /// Regular: C:\Users\NAME\AppData\Local
            /// Sandbox: C:\Users\NAME\AppData\Local\Packages\PACKAGEID_PUBLISHERID\AC
            /// </remarks>
            INLINE static path getAppDataLocal()
            {
               const char* p = ::getenv("LOCALAPPDATA");
               return p ? path(p) : path();
            }

            /// <summary>
            /// Returns the user's profile path on Windows.
            /// This is NOT accessible from sandbox.
            /// </summary>
            /// <remarks>
            /// Regular: C:\Users\NAME
            /// Sandbox: C:\Users\NAME
            /// </remarks>
            INLINE static path getUserProfile()
            {
               const char* p = ::getenv("USERPROFILE");
               return p ? path(p) : path();
            }
         };
      #endif

      #if defined(CPPCORE_OS_OSX) || defined(CPPCORE_OS_IPHONE)
         class Apple
         {
         public:
            /// <summary>
            /// Always returns home folder (/Users/NAME) of current user.
            /// You may not have access to this folder from sandbox.
            /// </summary>
            INLINE static path getHome()
            {
               struct passwd* pw = ::getpwuid(::getuid());
               return path(pw->pw_dir);
            }

            /// <summary>
            /// Returns home folder of current user or sandbox container root.
            /// Preferred persistent location to store user specific app data.
            /// </summary>
            /// <remarks>
            /// Regular: /Users/NAME
            /// Sandbox: /Users/NAME/Library/Containers/BUNDLEID/Data
            /// </remarks>
            INLINE static path getHomeSandbox()
            {
               NSString* s = NSHomeDirectory();
               return path([s UTF8String]);
            }
         };
      #endif

      #if defined(CPPCORE_OS_LINUX)
         class Linux
         {
         public:
            /// <summary>
            /// Always returns home folder (/home/NAME) of current user.
            /// </summary>
            INLINE static path getHome()
            {
               struct passwd* pw = ::getpwuid(::getuid());
               return path(pw->pw_dir);
            }
         };
      #endif

         /// <summary>
         /// Returns a writable temporary path to use on this system/user.
         /// This is only persistent for one run of the application.
         /// </summary>
         /// <remarks>
         /// WINDOWS:
         ///  Regular: C:\Users\NAME\AppData\Local\Temp
         ///  Sandbox: C:\Users\NAME\AppData\Local\Packages\PACKAGEID_PUBLISHERID\AC\Temp\
         /// MACOS:
         ///  Regular: /var/folders/24/8k48jl6d249_n_qfxwsl6xvm0000gn/T/
         ///  Sandbox: TODO
         /// LINUX:
         ///  Regular: /tmp
         /// </remarks>
         INLINE static path getTemp()
         {
         #if defined(CPPCORE_OS_ANDROID)
            const char* p = ::getenv("TMPDIR");
            return p && *p ? path(p) : path("/data/local/tmp");
         #else
            return std::filesystem::temp_directory_path();
         #endif
         }

         /// <summary>
         /// Returns a writable persistent path to use on this system/user.
         /// </summary>
         INLINE static path getPersistent()
         {
         #if defined(CPPCORE_OS_WINDOWS)
            return Windows::getAppDataLocal();
         #elif defined(CPPCORE_OS_OSX) || defined(CPPCORE_OS_IPHONE)
            return Apple::getHomeSandbox();
         #elif defined(CPPCORE_OS_ANDROID)
            return path("/data/media/0");
            //return path("/storage/self/primary");
         #else
            struct passwd* pw = ::getpwuid(::getuid());
            return path(pw->pw_dir);
         #endif
         }

         /// <summary>
         /// Returns the curren path of the process.
         /// </summary>
         /// <remarks>
         /// WINDOWS:
         ///  Regular: Working Directory on Shortcut | Startup Folder on Shell
         ///  Sandbox: C:\Program Files\WindowsApps\PACKAGEID_VERSION_ARCH__PUBLISHERID
         /// MACOS:
         ///  Regular:
         ///  Sandbox:
         /// LINUX:
         /// </remarks>
         INLINE static path getCurrent()
         {
            return std::filesystem::current_path();
         }

         /// <summary>
         /// Returns full path with filename of the current executable.
         /// </summary>
         INLINE static path getExecutable()
         {
         #if defined(CPPCORE_OS_WINDOWS)
            TCHAR name[MAX_PATH+1];
            const DWORD len = GetModuleFileName(0, name, MAX_PATH+1);
            return len ? path(name) : path();
         #elif defined(CPPCORE_OS_OSX) || defined(CPPCORE_OS_IPHONE)
            char name[PATH_MAX+1];
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
      #elif defined(CPPCORE_OS_OSX) || defined(CPPCORE_OS_IPHONE)
         return [[NSProcessInfo processInfo] physicalMemory];
      #else
         uint64_t pages = sysconf(_SC_PHYS_PAGES);
         uint64_t page_size = sysconf(_SC_PAGE_SIZE);
         return pages * page_size;
      #endif
      }

      /// <summary>
      /// Returns the number of logical CPU cores (or 0 if not retrievable).
      /// </summary>
      INLINE static uint32_t getCpuCoresLogical()
      {
         return std::thread::hardware_concurrency();
      }

      /// <summary>
      /// Returns the number of physical CPU cores (or 0 if not retrievable).
      /// </summary>
      INLINE static uint32_t getCpuCoresPhysical()
      {
      #ifdef CPPCORE_OS_WINDOWS
         uint32_t cores = 0;
         DWORD len = 0;
         if (GetLogicalProcessorInformationEx(RelationAll, NULL, &len) == FALSE && 
             GetLastError() == ERROR_INSUFFICIENT_BUFFER)
         {
            char* buf = (char*)malloc(len);
            if (GetLogicalProcessorInformationEx(RelationAll, 
               (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)buf, &len))
            {
               char* ptr = buf;
               while (ptr < buf + len) 
               {
                  SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX& pi = 
                     *(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)ptr;
                  if (pi.Relationship == RelationProcessorCore)
                     cores++;
                  ptr += pi.Size;
               }
            }
            free(buf);
         }
         return cores;
      #elif defined(CPPCORE_OS_OSX) || defined(CPPCORE_OS_IPHONE)
         uint32_t cores = 0;
         size_t size = sizeof(cores);
         ::sysctlbyname("hw.physicalcpu", &cores, &size, 0, 0);
         return cores;
      #else
         return 0; // TODO: Linux/Android
      #endif
      }

      /// <summary>
      /// Sets cpu info including physical and logical cores counts.
      /// </summary>
      INLINE static bool getCpuInfo(Cpu& cpu)
      {
         cpu.coreslogical = getCpuCoresLogical();
         cpu.coresphysical = getCpuCoresPhysical();
         return (cpu.coreslogical && cpu.coresphysical);
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

      /// <summary>
      /// System Info
      /// </summary>
      class Info
      {
      protected:
         const uint32_t mCoresPhysical; // physical cores
         const uint32_t mCoresLogical;  // logical cores
         const uint64_t mRamSize;       // ram size of system
         const path     mPathTemp;      // suggestion for temporary path
         const path     mPathPermBase;  // suggestion for persistent base path
         const path     mPathPerm;      // suggestion for persistent path
         const path     mLogFile;       // suggestion for logfile
         const path     mConfigFile;    // suggestion for configfile

      public:
         INLINE Info(
            const string& appname, 
            const string& companyname = "",
            const string& extlog      = ".log", 
            const string& extcfg      = ".json") :
            mCoresPhysical(System::getCpuCoresPhysical()),
            mCoresLogical(System::getCpuCoresLogical()),
            mRamSize(System::getRamSize()),
            mPathTemp(Folder::getTemp()),
            mPathPermBase(Folder::getPersistent()),
            mPathPerm(companyname.length() ? 
               mPathPermBase / companyname / appname :
               mPathPermBase / appname),
            mLogFile(mPathPerm / (appname + extlog)),
            mConfigFile(mPathPerm / (appname + extcfg))
         {
            if (!std::filesystem::exists(mPathPerm))
               std::filesystem::create_directories(mPathPerm);
         }

         INLINE uint32_t    getCpuCoresPhysical( ) const { return mCoresPhysical; }
         INLINE uint32_t    getCpuCoresLogical()   const { return mCoresLogical; }
         INLINE uint64_t    getRamSize()           const { return mRamSize; }
         INLINE const path& getTempPath()          const { return mPathTemp; }
         INLINE const path& getPersistentPath()    const { return mPathPerm; }
         INLINE const path& getConfigFile()        const { return mConfigFile; }
         INLINE const path& getLogFile()           const { return mLogFile; }

         INLINE path getLogFile(const string& name, const string& ext = ".log") const
         {
            return mPathPerm / (name + ext);
         }
      };
   };
}
