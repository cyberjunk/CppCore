#pragma once

#include <CppCore/Root.h>
#include <CppCore/Logger.h>
#include <CppCore/System.h>
#include <CppCore/Threading/Handler.h>

namespace CppCore
{
   /// <summary>
   /// Resources stored in path on disk.
   /// </summary>
   class Resources : public Logger::Producer<Logger, Logger::Channel::Resources>
   {
   public:
      /// <summary>
      /// Possible Locations for Resources
      /// </summary>
      class Locations
      {
      public:
         const string name;
         const path exepath = System::Folder::getExecutablePath();
         const path curpath = System::Folder::getCurrent();
         const path folders[6] = { 
            absolute(curpath / "resources"),                               // Development (e.g. $git)
            absolute(curpath / ".." / ".." / "resources"),                 // Development (e.g. $git/build/vs)
            absolute(curpath / ".." / ".." / ".." / ".." / "resources"),   // Development (e.g. $git/build/make/bin/win-x64)
            absolute(exepath / "resources"),                               // Windows Distribution Packages
            absolute(exepath / ".." / "Resources"),                        // OSX Distribution Packages
            absolute(path("/") / "usr" / "share" / name)                   // Linux Distribution Packages
         };
         INLINE Locations(const string& name) : name(name) { }
         INLINE path find() const
         {
            // search locations
            for (auto& p : folders)
               if (std::filesystem::exists(p))
                  return p;

            // not found
            return path();
         }
      };

      /// <summary>
      /// Callback. Derive from this.
      /// </summary>
      class Callback { };

   protected:
      const Locations mLocations;   // possible resource locations
      const path      mPath;        // detected path of resources
      Handler&        mApplication; // ref to application
      Handler&        mThreadPool;  // ref to threadpool
      Callback&       mCallback;    // ref to callback instance

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
         mLocations(linuxsharename),
         mPath(mLocations.find()),
         mApplication(application),
         mThreadPool(threadPool),
         mCallback(callback)
      {
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
      /// Returns true if resources base path exists.
      /// </summary>
      INLINE bool exists()
      {
         return std::filesystem::exists(mPath);
      }

      /// <summary>
      /// Returns true if sub path p exists in resources.
      /// </summary>
      INLINE bool exists(const path& p)
      {
         return std::filesystem::exists(mPath / p);
      }
   };
}
