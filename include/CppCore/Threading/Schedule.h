#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Queue.h>
#include <CppCore/Containers/MinHeap.h>
#include <CppCore/Threading/Runnable.h>
#include <CppCore/Threading/Handler.h>

#ifndef CPPCORE_DEFAULT_TIMERCOUNT
// Default max. timers in the Schedule (-1 due to memory alignment)
#define CPPCORE_DEFAULT_TIMERCOUNT (16384U-1U) 
#endif

#ifndef CPPCORE_DEFAULT_INSTANTTIMERCOUNT
// Default max. instant timers in the Schedule (-3 due to memory alignment)
#define CPPCORE_DEFAULT_INSTANTTIMERCOUNT (4096U-3U) 
#endif

#ifndef CPPCORE_DEFAULT_SLEEP_MS
// Default sleep time in milliseconds if no runnable is present in the Schedule
#define CPPCORE_DEFAULT_SLEEP_MS 100
#endif

#ifndef CPPCORE_DEFAULT_SLEEP_THRESHOLD_US
// Will not go to full sleep due to sleep precision 
// if next Runnable is less than this microseconds ahead
#define CPPCORE_DEFAULT_SLEEP_THRESHOLD_US 2000
#endif

namespace CppCore
{
   /// <summary>
   /// Multi-Thread Safe Schedule for Runnables
   /// </summary>
   template<
      size_t TIMERCOUNT        = CPPCORE_DEFAULT_TIMERCOUNT, 
      size_t INSTANTTIMERCOUNT = CPPCORE_DEFAULT_INSTANTTIMERCOUNT>
   class CPPCORE_ALIGN64 Schedule : public Handler
   {
      typedef Runnable::MinHeap<TIMERCOUNT>           RunnablePriorityQueue;
      typedef Queue::ST<Runnable*, INSTANTTIMERCOUNT> RunnableQueue;

   protected:
      CPPCORE_ALIGN64 RunnablePriorityQueue  mTimers;
      CPPCORE_ALIGN64 RunnableQueue          mTimersInstant;
      StdMutex               mMutexTimers;
      StdConditionVariable   mCondSleep;
      const DurationHR       mDefaultSleep;
      const DurationHR       mSleepThreshold;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Schedule(
         const DurationHR& defaultSleep   = milliseconds(CPPCORE_DEFAULT_SLEEP_MS),
         const DurationHR& sleepThreshold = microseconds(CPPCORE_DEFAULT_SLEEP_THRESHOLD_US)) :
         mDefaultSleep(defaultSleep),
         mSleepThreshold(sleepThreshold) { }

      /// <summary>
      /// Wakes one sleeping thread (if any)
      /// </summary>
      INLINE void wakeOne()
      {
         mCondSleep.notify_one();
      }

      /// <summary>
      /// Wakes all sleeping threads (if any)
      /// </summary>
      INLINE void wakeAll()
      {
         mCondSleep.notify_all();
      }

      /// <summary>
      /// Tries to add a Runnable to this Schedule
      /// </summary>
      INLINE bool schedule(Runnable& runnable, const TimePointHR executeAt = TimePointHR(DurationHR::zero()))
      {
         bool ok = false;                    // default return
         runnable.lock();                    // first lock runnable (lower scope)
         StdUniqueLockMutex l(mMutexTimers); // then lock schedule (greater scope)

         // get runnable state
         const Runnable::State STATE = runnable.getState();

         // 1) SCHEDULED: Nothing to do
         // 2) IDLE: Schedule it
         // 3) STARTING/RUNNING: Set Reschedule to true

         // idle
         if (STATE == Runnable::State::Idle)
         {
            // set execution time of runnable
            runnable.setExecutionTime(executeAt);

            // schedule instant runnables in the fifo queue O(1)
            // others in the minheap O(log(n))
            ok = runnable.isInstant() ?
               mTimersInstant.pushBack(&runnable) :
               mTimers.push(&runnable);

            // update scheduled state
            if (ok)
               runnable.setState(Runnable::State::Scheduled);
         }
         
         // in execution (TODO: Instants only?)
         else if (STATE == Runnable::State::Starting || STATE == Runnable::State::Running)
         {
            runnable.setReschedule(true);  // mark for reschedule
            ok = true;                     // success return
         }

         l.unlock();        // unlock schedule
         runnable.unlock(); // unlock runnable
         if (ok) wakeOne(); // wake one sleeping thread
         return ok;         // return whether it was scheduled or not
      }

      /// <summary>
      /// Tries to remove a Runnable from this Schedule
      /// </summary>
      INLINE bool cancel(Runnable& runnable)
      {
         bool ok = false;                    // default return
         runnable.lock();                    // first lock runnable (lower scope)
         StdUniqueLockMutex l(mMutexTimers); // then lock schedule (greater scope)

         // must be scheduled to cancel
         if (runnable.isScheduled())
         {
            Runnable* tmp;

            // try find and remove it either from fifo queue O(n)
            // or minheap also O(n)
            ok = runnable.isInstant() ?
               mTimersInstant.removeOneUnsorted(&runnable, tmp) :
               mTimers.removeOne(&runnable, tmp);

            // update scheduled state
            if (ok)
               runnable.setState(Runnable::State::Idle);
         }

         if (runnable.isReschedule())
            runnable.setReschedule(false);

         l.unlock();        // unlock schedule
         runnable.unlock(); // unlock runnable
         return ok;         // return whether it was canceled or not
      }

      /// <summary>
      /// Execute the next elapsed timer or instant runnable.
      /// Or sleeps until it is time to run the next timer or woken up.
      /// </summary>
      template<typename TLOOPER>
      INLINE void execute(TLOOPER& looper)
      {
         looper.setExecuting(true);
         Runnable* runnable = nullptr;

         ///////////////////////////////////////////////////////////////////////////////////////////
         // (1) Get a Runnable to execute (locked)

         // lock schedule
         StdUniqueLockMutex l(mMutexTimers);

         // try to get an instant runnable first, otherwise try to get a normal runnable
         bool ok = mTimersInstant.popFront(runnable) ||
            (mTimers.peek(runnable) && runnable->isTimeToExecute() && mTimers.pop(runnable));

         if (ok)
            runnable->setState(Runnable::State::Starting);

         // unlock schedule
         l.unlock();

         ///////////////////////////////////////////////////////////////////////////////////////////
         // (2) Execute the Runnable if any (unlocked)

         if (ok)
         {
            // execute it (this must not be inside a lock or else will block badly!)
            runnable->setState(Runnable::State::Running);
            runnable->execute();
            
            // lock runnable here before switching to idle
            runnable->lock();
            runnable->setState(Runnable::State::Idle);

            // reschedule repeating runnables
            if (runnable->isRepeat())
            {
               // preferred next execution
               const StdTimePoint nextRun =
                  runnable->getExecutionTime() +
                  runnable->getInterval();

               // unlock
               runnable->unlock();

               // reschedule timer, but not too much in the past
               // else a late one would try to repeat itself a lot
               schedule(*runnable, std::max(nextRun, ClockHR::now()));
            }

            // reschedule instant runnables if schedule was called while running
            else if (runnable->isReschedule())
            {
               runnable->setReschedule(false);
               runnable->unlock();
               schedule(*runnable);
            }
            else
               runnable->unlock();
         }

         ///////////////////////////////////////////////////////////////////////////////////////////
         // (3) See how long we can sleep/wait (locked)

         // lock schedule again
         l.lock();

         // 1) Based on next Runnable to execute
         if (mTimersInstant.peekFront(runnable) || mTimers.peek(runnable))
         {
            const DurationHR& timeLeft = runnable->getRemainingTime();

            // only go to sleep if next task is above threshold ahead (can't properly sleep for < ~1ms without missing time)
            // note: wait_for and wait_until unlock on execution and lock on return
            if (timeLeft > mSleepThreshold)
            {
               looper.setExecuting(false);
               StdCvStatus cvstat = mCondSleep.wait_until(l, runnable->getExecutionTime());
               looper.setExecuting(true);
            }

            // if still ahead but less than threshold, perform nano sleep (if available)
            else if (timeLeft > microseconds(CPPCORE_RUNNABLE_EXECUTE_TOLERANCE_US))
            {
               CPPCORE_NANOSLEEP();
               CPPCORE_NANOSLEEP();
               CPPCORE_NANOSLEEP();
               CPPCORE_NANOSLEEP();
            }

            // already behind execution time (or nanoseconds before)
            else { }
         }

         // 2) Default Sleep (no Runnable)
         else
         {
            looper.setExecuting(false);
            StdCvStatus cvstat = mCondSleep.wait_for(l, mDefaultSleep);
            looper.setExecuting(true);
         }

         // unlock schedule
         l.unlock();
      }
   };
}
