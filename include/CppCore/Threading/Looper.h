#pragma once

#include <CppCore/Root.h>
#include <CppCore/Stopwatch.h>
#include <CppCore/Threading/Runnable.h>
#include <CppCore/Threading/Schedule.h>

namespace CppCore
{
   /// <summary>
   /// A wrapper around a while loop which allows configuring tickrate of loop,
   /// waking up from other threads while sleeping and executing timers/runnables.
   /// </summary>
   class Looper
   {
      friend Schedule<>;

   protected:
      StdAtomicBool mIsRunning;
      Schedule<>&   mSchedule;
      StdThread::id mThreadId;
      StdTimePoint  mExecutionStarted;
      StdTimePoint  mExecutionStopped;
      StdDuration   mDurationExecute;
      StdDuration   mDurationSleep;
      bool          mExecuting;

      /// <summary>
      /// Switches executing state
      /// </summary>
      INLINE void setExecuting(bool value) 
      {
         if (mExecuting)
         {
            // 1->0
            if (!value)
            {
               mExecutionStopped = StdClock::now();
               mDurationExecute += (mExecutionStopped - mExecutionStarted);
               mExecuting = false;
            }
            // 1->1
            else
            {
               mExecutionStopped = StdClock::now();
               mDurationExecute += (mExecutionStopped - mExecutionStarted);
               mExecutionStarted = mExecutionStopped;
            }
         }
         else
         {
            // 0->1
            if (value)
            {
               mExecutionStarted = StdClock::now();
               mDurationSleep += (mExecutionStarted - mExecutionStopped);
               mExecuting = true;
            }
         }
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Looper(Schedule<>& schedule) :
         mIsRunning(false),
         mSchedule(schedule),
         mThreadId(::std::this_thread::get_id()),
         mExecuting(false),
         mExecutionStarted(StdClock::now()),
         mExecutionStopped(StdClock::now()),
         mDurationExecute(StdNanoSeconds(0)),
         mDurationSleep(StdNanoSeconds(0)) { }

      /// <summary>
      /// True if this Looper is currently executing
      /// </summary>
      INLINE bool isExecuting() const { return mExecuting; }

      /// <summary>
      /// True if the Looper is currently looping
      /// </summary>
      INLINE bool isRunning() const
      {
         return mIsRunning.load();
      }

      /// <summary>
      /// 
      /// </summary>
      INLINE void setIsRunning(bool isRunning) 
      {
         mIsRunning.store(isRunning);
         mSchedule.wakeAll();
      }

      /// <summary>
      /// Id of the Thread that's running this looper
      /// </summary>
      INLINE const StdThread::id& getThreadId() const
      { 
         return mThreadId; 
      }

      /// <summary>
      /// Returns how long this looper has been sleeping since last duration reset.
      /// Note: This does not include sleeps during execute (e.g. socket poll)
      /// </summary>
      INLINE const StdDuration& getDurationSleep() const { return mDurationSleep; }

      /// <summary>
      /// Returns how long this looper has been executing since last duration reset
      /// Note: This also includes custom sleeps during execute (e.g. socket poll)
      /// </summary>
      INLINE const StdDuration& getDurationExecute() const { return mDurationExecute; }

      /// <summary>
      /// Resets the sleep and execute durations.
      /// </summary>
      INLINE void resetDurations()
      {
         mDurationSleep = StdNanoSeconds(0);
         mDurationExecute = StdNanoSeconds(0);
      }

      /// <summary>
      /// Starts and stays in the Looper's loop
      /// until mIsRunning is flipped.
      /// </summary>
      INLINE void loop()
      {
         // set as not sleeping
         setExecuting(true);

         // save id of looper thread in case it's different from constructor
         mThreadId = ::std::this_thread::get_id();

         // enter loop on executing schedule
         while (mIsRunning.load())
            mSchedule.execute(*this);
      }
   };
}
