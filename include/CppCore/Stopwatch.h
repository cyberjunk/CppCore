#pragma once

#include <CppCore/Root.h>

namespace CppCore 
{
   /// <summary>
   /// A basic Stopwatch that measures time intervals and
   /// provides basic statistics such as average/worst/best.
   /// </summary>
   class Stopwatch
   {
   protected:
      TimePointHR mStart;
      TimePointHR mEnd;
      DurationHR  mDuration;
      DurationHR  mDurationSum;
      DurationHR  mAverage;
      DurationHR  mBest;
      DurationHR  mWorst;
      size_t      mTicks;
      bool        mRunning;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Stopwatch()
      {
         reset();
      }

      INLINE const TimePointHR& getStart()       const { return mStart;       }
      INLINE const TimePointHR& getEnd()         const { return mEnd;         }
      INLINE const DurationHR&  getDuration()    const { return mDuration;    }
      INLINE const DurationHR&  getDurationSum() const { return mDurationSum; }
      INLINE const DurationHR&  getAverage()     const { return mAverage;     }
      INLINE const DurationHR&  getBest()        const { return mBest;        }
      INLINE const DurationHR&  getWorst()       const { return mWorst;       }
      INLINE       size_t       getTicks()       const { return mTicks;       }

      /// <summary>
      /// Resets the Stopwatch to default values.
      /// </summary>
      INLINE void reset()
      {
         mStart       = TimePointHR(DurationHR::zero());
         mEnd         = TimePointHR(DurationHR::zero());
         mDuration    = DurationHR::zero();
         mDurationSum = DurationHR::zero();
         mAverage     = DurationHR::zero();
         mBest        = DurationHR::max();
         mWorst       = DurationHR::zero();
         mTicks       = 0;
         mRunning     = false;
      }

      /// <summary>
      /// Starts the watch. Does nothing if started.
      /// </summary>
      INLINE void start()
      {
         if (!mRunning)
         {
            mStart   = ClockHR::now();
            mRunning = true;
         }
      }

      /// <summary>
      /// Stops the watch (and updates stats). Does nothing if stopped.
      /// </summary>
      INLINE void stop()
      {
         if (mRunning)
         {
            // update end tick, calculate duration and duration sum
            mEnd = ClockHR::now();
            mDuration = mEnd - mStart;
            mDurationSum += mDuration;

            // possibly save tick as worst or best
            if (mDuration > mWorst) mWorst = mDuration;
            if (mDuration < mBest)  mBest  = mDuration;

            // increment tick counter for stats
            mTicks++;

            // update average
            mAverage = mDurationSum / mTicks;
            mRunning = false;
         }
      }
   };
}
