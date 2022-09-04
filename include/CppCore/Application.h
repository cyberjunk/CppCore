#pragma once

#include <CppCore/Root.h>
#include <CppCore/Threading/Handler.h>
#include <CppCore/Threading/Thread.h>
#include <CppCore/Logger.h>
#include <CppCore/CPUID.h>
#include <CppCore/Resources.h>

namespace CppCore
{
   /// <summary>
   /// Application Main Class
   /// </summary>
   template<typename TAPPLICATION, typename RESOURCES = Resources, typename LOGGER = Logger>
   class Application : public Looper, public Handler, public RESOURCES::Callback
   {
   protected:
      Thread::Pool<Thread> mThreadPool;
      Schedule<>           mSchedule;
      LOGGER               mLogger;
      CPUID                mCPUID;
      RESOURCES            mResources;

      /// <summary>
      /// Helper for casting this from template to final instance type.
      /// </summary>
      INLINE TAPPLICATION& thiss() { return *((TAPPLICATION*)this); }

      /// <summary>
      /// Let class implementations do initialization work with
      /// command line arguments before we enter mainthread loop
      /// </summary>
      INLINE virtual void init(int argc, char* argv[]) { }

      /// <summary>
      /// Let class implementations do shutdown work after we exit main loop.
      /// </summary>
      INLINE virtual void shutdown() 
      {
         this->mThreadPool.stop();
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Application(
         const bool    logToConsole   = true, 
         const bool    logToFile      = true, 
         const string& logFile        = "app.log",
         const string& linuxsharename = "CppCore") :
         Looper(mSchedule),
         mThreadPool(),
         mLogger(mThreadPool, logToConsole, logToFile, logFile),
         mResources(thiss(), mThreadPool, mLogger, thiss(), linuxsharename)
      {
      #if defined(CPPCORE_CPU_X86ORX64)
         this->log(std::string("CPU: ") + mCPUID.getBrand());
         if (!mCPUID.isCompatible())
            this->logError("Some enabled instructions are incompatible with your CPU.");
      #endif

         // log some folders
         this->log("Temp: " + System::Folder::getTemp().string());
         this->log("Home: " + System::Folder::getHome().string());
         this->log("Current: " + System::Folder::getCurrent().string());
         this->log("Executable: " + System::Folder::getExecutablePath().string());

         // log thread count and ids
         stringstream s;
         s << "ThreadPool started with " << mThreadPool.getSize() << " threads: ";
         for (size_t i = 0; i < mThreadPool.getSize(); i++)
            s << mThreadPool.getId(i) << ' ';

         this->log(s.str());

         // log fixed memory size
         const size_t MEMSIZEAPP = sizeof(TAPPLICATION) / (1024 * 1024);
         this->log("Initialized " + std::to_string(MEMSIZEAPP) + " MB fixed memory.");
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////

      INLINE void log(const string& message, const Logger::Type logType = Logger::Type::Info)
      {
         mLogger.log(message, Logger::Channel::App, logType);
      }
      INLINE void logError(const string& message) { this->log(message, Logger::Type::Error);   }
      INLINE void logWarn(const string& message)  { this->log(message, Logger::Type::Warning); }
      INLINE void logDebug(const string& message) { this->log(message, Logger::Type::Debug);   }

      /////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Starts the application. Does not return until shutdown.
      /// </summary>
      INLINE void start(int argc = 0, char* argv[] = nullptr)
      {
         if (!this->mIsRunning)
         {
         #ifdef CPPCORE_OS_WINDOWS
            ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
         #endif

            this->mIsRunning = true; // set as running
            this->init(argc, argv);  // do init before loopstart
            this->loop();            // enter mainthread loop
            this->shutdown();        // run shutdown
         }
      }

      /// <summary>
      /// Sets the mainthread to exit next loop.
      /// </summary>
      INLINE void stop(const int signal = 0)
      {
         if (this->mIsRunning)
         {
            log("Flagged for shutdown. Signal: " + ::std::to_string(signal));
            this->mIsRunning = false;
         }
      }

      /// <summary>
      /// Tries to schedule a Runnable for execution in the mainthread.
      /// </summary>
      INLINE bool schedule(Runnable& runnable, TimePointHR executeAt = TimePointHR(nanoseconds(0))) override
      {
         return mSchedule.schedule(runnable, executeAt);
      }

      /// <summary>
      /// Tries to remove a Runnable from the schedule of the mainthread.
      /// </summary>
      INLINE bool cancel(Runnable& runnable) override
      {
         return mSchedule.cancel(runnable);
      }

      /// <summary>
      /// Returns the cumulated memory usage from heap allocations
      /// for all sub-instances.
      /// </summary>
      INLINE virtual size_t memOnHeap()
      {
         return mThreadPool.memOnHeap();
      }
   };
}
