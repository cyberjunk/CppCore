#pragma once

#include <CppCore/Root.h>
#include <CppCore/Logger.h>
#include <CppCore/Threading/Handler.h>

namespace CppCore
{
   /// <summary>
   /// Resources stored in a path.
   /// </summary>
   class Resources : public Logger::Producer<Logger, Logger::Channel::Resources>
   {
   public:
      static constexpr char PATHDEV1[]    = "./../../../../resources"; // e.g. $git/build/make/bin/win-x64/
      static constexpr char PATHDEV2[]    = "./../../resources";       // e.g. $git/build/vs/
      static constexpr char PATHDISTWIN[] = "./resources";             // Windows Distribution Packages
      static constexpr char PATHDISTLIN[] = "/usr/share/";             // Linux Distribution Packages (+name)
      static constexpr char PATHDISTOSX[] = "./../Resources";          // OSX Distribution Packages

   public:
      class Callback
      {
      };

   protected:
      path      mPath;
      Handler&  mApplication;
      Handler&  mThreadPool;
      Callback& mCallback;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Resources(
         Handler&      application, 
         Handler&      threadPool, 
         Logger&       logger, 
         Callback&     callback, 
         const string& linuxsharename) :
         Logger::Producer<Logger, Logger::Channel::Resources>(logger),
         mApplication(application),
         mThreadPool(threadPool),
         mCallback(callback),
         mPath(PATHDEV1)
      {
         // log current path (aka. working directory)
         this->log("Current Path: " + std::filesystem::current_path().u8string());

      #if defined(CPPCORE_OS_WINDOWS)
         char name[256];
         if (!std::filesystem::exists(mPath))
            mPath = PATHDEV2;
         if (!std::filesystem::exists(mPath))
            mPath = PATHDISTWIN;
         if (!std::filesystem::exists(mPath))
            if (DWORD len = GetModuleFileName(0, name, sizeof(name)))
               mPath = path(name).remove_filename() / path("resources");
      #elif defined(CPPCORE_OS_LINUX)
         if (!std::filesystem::exists(mPath))
            mPath = PATHDISTLIN + linuxsharename;
      #elif defined(CPPCORE_OS_OSX)
         if (!std::filesystem::exists(mPath))
            mPath = PATHDISTOSX;
      #endif

         // success
         if (std::filesystem::exists(mPath))
            this->log("Found resources in: " + mPath.u8string());

         // fail
         else
            this->logError("Failed to find resources!");
      }

      /// <summary>
      /// Resources Base Path
      /// </summary>
      INLINE const path& getPath() const { return mPath; }

      /// <summary>
      /// Base Path combined with p
      /// </summary>
      INLINE path getPath(const path& p) const { return mPath / p; }

      /// <summary>
      /// Returns true if sub path p exists in resources.
      /// </summary>
      INLINE bool exists(const path& p)
      {
         return std::filesystem::exists(mPath / p);
      }
   };
}
