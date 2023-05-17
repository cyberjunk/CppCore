#pragma once

#ifndef CPPCORE_RUNNABLE_EXECUTE_TOLERANCE_US
// A Runnable will be execute even if it is still scheduled this microseconds ahead in the future.
#define CPPCORE_RUNNABLE_EXECUTE_TOLERANCE_US 10 
#endif

#include <CppCore/Root.h>
#include <CppCore/Containers/MinHeap.h>

namespace CppCore
{
   typedef ::std::function<void(void)> RunnableFunction;

   /// <summary>
   /// Forward Declaration
   /// </summary>
   class Schedule;

   /// <summary>
   /// Runnables are used to execute a function in a looper at a given time.
   /// They can also repeat themself in intervals like a timer.
   /// </summary>
   class CPPCORE_ALIGN16 Runnable
   {
      friend Schedule;

   public:
      /// <summary>
      /// Possible States of a Runnable
      /// </summary>
      enum State { Idle, Scheduled, Starting, Running };

   protected:
      RunnableFunction   mFunc;
      TimePointHR        mExecutionTime;
      State              mState;
      DurationHR         mInterval;
      CPPCORE_MUTEX_TYPE mMutex;
      bool               mRepeat;
      bool               mReschedule;

      
      /// <summary>
      /// Sets the time when to execute this runnable in the schedule
      /// </summary>
      INLINE void setExecutionTime(const TimePointHR& time) { mExecutionTime = time; }

      /// <summary>
      /// Sets the current state of the Runnable.
      /// </summary>
      INLINE void setState(State state)
      {
         mState = state;
      }

      /// <summary>
      /// 
      /// </summary>
      INLINE void setReschedule(bool reschedule)
      {
         mReschedule = reschedule;
      }

      /// <summary>
      /// Called by the Looper when executing this Runnable.
      /// </summary>
      INLINE void execute()
      {
         if (mFunc)
            mFunc();
      }

   public:
      /// <summary>
      /// Empty Constructor
      /// </summary>
      INLINE Runnable() :
         mExecutionTime(TimePointHR(DurationHR::zero())),
         mState(State::Idle),
         mFunc(0),
         mRepeat(false),
         mInterval(DurationHR::zero()),
         mReschedule(false) { CPPCORE_MUTEX_INIT(mMutex); }

      /// <summary>
      /// Runnable Constructor
      /// </summary>
      INLINE Runnable(RunnableFunction func) :
         mExecutionTime(TimePointHR(DurationHR::zero())),
         mState(State::Idle),
         mFunc(func),
         mRepeat(false),
         mInterval(DurationHR::zero()),
         mReschedule(false) { CPPCORE_MUTEX_INIT(mMutex); }

      /// <summary>
      /// Timer Constructor
      /// </summary>
      INLINE Runnable(RunnableFunction func, const DurationHR& interval) :
         mExecutionTime(TimePointHR(DurationHR::zero())),
         mState(State::Idle),
         mFunc(func),
         mRepeat(true),
         mInterval(interval),
         mReschedule(false) { CPPCORE_MUTEX_INIT(mMutex); }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~Runnable()
      {
         CPPCORE_MUTEX_DELETE(mMutex);
      }

      /// <summary>
      /// Gets the time when to execute this runnable in the schedule
      /// </summary>
      INLINE const TimePointHR& getExecutionTime() const { return mExecutionTime; }

      /// <summary>
      /// Returns the remaining time until 'ExecutionTime'.
      /// Can be negative if 'ExecutionTime' is in the past
      /// </summary>
      INLINE const DurationHR getRemainingTime() const { return mExecutionTime - ClockHR::now(); }

      /// <summary>
      /// Sets the function that should be executed
      /// </summary>
      INLINE void setFunction(const RunnableFunction& f) { mFunc = f; }

      /// <summary>
      /// Lock the Runnable
      /// </summary>
      INLINE void lock() { CPPCORE_MUTEX_LOCK(mMutex); }

      /// <summary>
      /// Unlock the Runnable
      /// </summary>
      INLINE void unlock() { CPPCORE_MUTEX_UNLOCK(mMutex); }

      /// <summary>
      /// Returns the current state of the Runnable.
      /// </summary>
      INLINE State getState() const
      {
         return mState;
      }

      /// <summary>
      /// True if the Runnable is idle
      /// </summary>
      INLINE bool isIdle() const
      {
         return mState == State::Idle;
      }

      /// <summary>
      /// True if the Runnable is scheduled in the schedule
      /// </summary>
      INLINE bool isScheduled() const
      {
         return mState == State::Scheduled;
      }

      /// <summary>
      /// True if the Runnable is starting
      /// </summary>
      INLINE bool isStarting() const
      {
         return mState == State::Starting; 
      }

      /// <summary>
      /// True if the Runnable is executing
      /// </summary>
      INLINE bool isRunning() const
      {
         return mState == State::Running; 
      }

      /// <summary>
      /// True if the Runnable should be executed immediately
      /// </summary>
      INLINE bool isInstant() const
      {
         return mExecutionTime.time_since_epoch() == DurationHR::zero(); 
      }

      /// <summary>
      /// Compares the execution time with the current clock and returns true
      /// if the time to execute is less than 100us ahead, exactly reached or even in the past.
      /// </summary>
      INLINE bool isTimeToExecute() const
      {
         return getRemainingTime() < microseconds(CPPCORE_RUNNABLE_EXECUTE_TOLERANCE_US);
      }

      /// <summary>
      /// Returns the interval between runnable executions
      /// </summary>
      INLINE const DurationHR& getInterval() const
      {
         return mInterval;
      }

      /// <summary>
      /// Sets the interval between Runnable executions
      /// </summary>
      INLINE void setInterval(const DurationHR& time)
      {
         mInterval = time;
      }

      /// <summary>
      /// True if the Runnable repeats itself in intervals.
      /// </summary>
      INLINE bool isRepeat() const
      {
         return mRepeat;
      }

      /// <summary>
      /// Sets whether the Runnable should repeat itself or not.
      /// </summary>
      INLINE void setRepeat(bool repeat)
      {
         mRepeat = repeat;
      }

      /// <summary>
      /// 
      /// </summary>
      INLINE bool isReschedule() const
      {
         return mReschedule;
      }

      /////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// MinHeap for Runnable
      /// </summary>
      template<size_t SIZE, class T = Runnable*>
      class MinHeap : public ::CppCore::MinHeap::ST<T, SIZE, T>
      {
      protected:
         /// <summary>
         /// Comparer for Runnables on the MinHeap
         /// </summary>
         class Comparer
         {
         private:
            INLINE Comparer() { }
         public:
            INLINE static bool equal(const T& a, const T& b) { return a == b; }
            INLINE static bool less (const T& a, const T& b) 
            {
               return
                  a->getExecutionTime().time_since_epoch().count() <
                  b->getExecutionTime().time_since_epoch().count();
            }
         };

      public:
         INLINE bool removeAt(T& item, size_t idx)
         {
            return CppCore::MinHeap::ST<T, SIZE, T>::template removeAt<
               Comparer>(item, idx);
         }
         INLINE bool push(const T& item)
         {
            return CppCore::MinHeap::ST<T, SIZE, T>::template push<
               Comparer>(item);
         }
         INLINE bool pop(T& item)
         {
            return CppCore::MinHeap::ST<T, SIZE, T>::template pop<
               Comparer>(item);
         }
         INLINE bool find(const T& item, size_t& idx)
         {
            return CppCore::MinHeap::ST<T, SIZE, T>::template find<
               Comparer>(item, idx);
         }
         INLINE bool removeOne(const T& key, T& item)
         {
            return CppCore::MinHeap::ST<T, SIZE, T>::template removeOne<
               Comparer, Comparer>(key, item);
         }
         INLINE size_t removeAll(const T& key)
         {
            return CppCore::MinHeap::ST<T, SIZE, T>::template removeAll<
               Comparer>(key);
         }
      };
   };
}
