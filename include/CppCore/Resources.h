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
         Handler& application, 
         Handler& threadPool, 
         Logger& logger, 
         Callback& callback, 
         const string& linuxsharename) :
         Logger::Producer<Logger, Logger::Channel::Resources>(logger),
         mApplication(application),
         mThreadPool(threadPool),
         mCallback(callback),
         // default: from build output location (development)
         // e.g. $git/build/make/bin/win-x64/
         mPath("./../../../../resources")
      {
         this->log("Current Path: " + std::filesystem::current_path().u8string());

      #if defined(CPPCORE_OS_WINDOWS)
         // from build projects folder
         // e.g. $git/build/vs/
         if (!std::filesystem::exists(mPath))
            mPath = "./../../resources";
         // platform distribution package location
         if (!std::filesystem::exists(mPath))
            mPath = "./resources";
      #elif defined(CPPCORE_OS_LINUX)
         // platform distribution package location
         if (!std::filesystem::exists(mPath))
            mPath = "/usr/share/" + linuxsharename;
      #elif defined(CPPCORE_OS_OSX)
         // platform distribution package location
         if (!std::filesystem::exists(mPath))
            mPath = "./../Resources";
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
