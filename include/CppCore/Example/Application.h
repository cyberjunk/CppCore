#pragma once

#include <CppCore/Root.h>
#include <CppCore/Application.h>
#include <CppCore/Example/Network.h>

namespace CppCore { namespace Example
{
   /// <summary>
   /// Example Application
   /// </summary>
   class Application : public CppCore::Application<CppCore::Logger>
   {
   protected:
      Runnable mTestRunnableST;
      Runnable mTestTimer;
      StdTimePoint mStart;

      void testTimerWork()
      {
         StdDuration offset = mTestTimer.getRemainingTime();
         mLogger.log("Timer4 Executed at " + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(offset).count()));
         mStart = StdClock::now();
         mThreadPool.schedule(mTestRunnableST);
      }

      void testRunnableWork()
      {
         StdDuration delay = StdClock::now() - mStart;
         mLogger.log("Runnable Executed after " + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(delay).count()));
      }

   public:
      INLINE Application() :
         CppCore::Application<CppCore::Logger>(),
         mTestRunnableST([this]() { testRunnableWork(); }),
         mTestTimer([this]() { testTimerWork(); }, true, StdMilliSeconds(1000))
      {
         mThreadPool.schedule(mTestTimer, StdClock::now() + mTestTimer.getInterval());
      }
   };
}}