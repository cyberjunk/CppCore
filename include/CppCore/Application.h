#pragma once

#include <CppCore/Root.h>
#include <CppCore/Threading/Handler.h>
#include <CppCore/Threading/Thread.h>
#include <CppCore/Logger.h>
#include <CppCore/CPUID.h>
#include <CppCore/Resources.h>

#if defined(CPPCORE_OS_OSX) && defined(__OBJC__)
#include <Cocoa/Cocoa.h>
#endif

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
      Runnable             mRunMessagePump;
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

      /// <summary>
      /// Message Pump on Application Level.
      /// </summary>
      INLINE virtual size_t messagePump()
      {
         size_t num = 0;
      #if defined(CPPCORE_OS_WINDOWS)
         MSG msg;
         while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
         {
            num++;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            // continues in WndProc
         }
      #elif defined(CPPCORE_OS_OSX) && defined(__OBJC__)
         @autoreleasepool
         {
            NSEvent * ev;
            while((ev = [NSApp
               nextEventMatchingMask : NSEventMaskAny
               untilDate : nil
               inMode : NSDefaultRunLoopMode
               dequeue : YES]))
            {
               num++;
               [NSApp sendEvent : ev];
               // continues in delegates
            }
         }
      #elif defined(CPPCORE_OS_LINUX)
         // needs a Window, see messagePump() in Window.h
      #endif
         return num;
      }

      /// <summary>
      /// Executes the Message Pump
      /// </summary>
      INLINE void runMessagePump()
      {
         size_t num = messagePump();
         if (num > 10)
            this->logWarn("Processed " + std::to_string((int32_t)num) + 
               " events in one tick.");
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Application(
         const bool        logToConsole        = true, 
         const bool        logToFile           = true, 
         const string&     logFile             = "app.log",
         const string&     linuxsharename      = "CppCore",
         const DurationHR& messagePumpInterval = std::chrono::milliseconds(16)) :
         Looper(mSchedule),
         mThreadPool(),
         mRunMessagePump([this] { runMessagePump(); }, true, messagePumpInterval),
         mLogger(mThreadPool, logToConsole, logToFile, logFile),
         mResources(thiss(), mThreadPool, mLogger, thiss(), linuxsharename)
      {
      #if defined(CPPCORE_CPU_X86ORX64)
         this->log(std::string("CPU: ") + mCPUID.getBrand());
         if (!mCPUID.isCompatible())
            this->logError("Some enabled instructions are incompatible with your CPU.");
      #endif

      #if defined(CPPCORE_OS_OSX) && defined(__OBJC__)
         [NSApplication sharedApplication];
         [NSApp setActivationPolicy : NSApplicationActivationPolicyRegular];
         [NSApp setPresentationOptions : NSApplicationPresentationDefault];
         [NSApp activateIgnoringOtherApps : YES];
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
            // set as running
            this->mIsRunning = true;

         #ifdef CPPCORE_OS_WINDOWS
            // set mainthread priority
            ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
         #endif

            // do init before loopstart
            this->init(argc, argv);

         #if defined(CPPCORE_OS_OSX) && defined(__OBJC__)
            // emit startup finished on macos
            [NSApp finishLaunching]; 
         #endif

            // schedule messagepump
            this->schedule(mRunMessagePump, ClockHR::now());

            // enter mainthread loop
            this->loop();

            // run shutdown
            this->shutdown();
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
