#pragma once

#include <CppCore/Root.h>

#define CPPCORE_TICKER_NANOSECONDS_IN_SECOND      1000000000
#define CPPCORE_TICKER_NANOSECONDS_IN_MILLISECOND 1000000
#define CPPCORE_TICKER_NANOSECONDS_IN_MIKROSECOND 1000

namespace CppCore 
{
   /// <summary>
   /// A basic Ticker that remembers a tick, the duration and some stats
   /// </summary>
   template<size_t DIVISOR>
   class Ticker
   {
   protected:
      double mTick;
      double mDuration;
      double mDurationSum;
      double mAverage;
      double mBest;
      double mWorst;
      size_t mTicks;
      double mStatReset;

   public:
      /// <summary>
      /// Returns a double tick from the clock
      /// </summary>
      INLINE static double getClockTick() 
      {
         return (double)StdClock::now().time_since_epoch().count() / (double)DIVISOR;
      }

      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Ticker()
      {
         reset();
      }

      INLINE double getTick()        const { return mTick;        }
      INLINE double getDuration()    const { return mDuration;    }
      INLINE double getDurationSum() const { return mDurationSum; }
      INLINE double getAverage()     const { return mAverage;     }
      INLINE double getBest()        const { return mBest;        }
      INLINE double getWorst()       const { return mWorst;       }
      INLINE size_t getTicks()       const { return mTicks;       }
      INLINE double getStatReset()   const { return mStatReset;   }

      /// <summary>
      /// Calculates the duration since last stat reset
      /// </summary>
      INLINE double getDurationStatReset() const
      { 
         return mTick - mStatReset; 
      }

      /// <summary>
      /// Resets the Ticker to default values.
      /// </summary>
      INLINE void reset()
      {
         mTick        = getClockTick();
         mDuration    = 0.0;
         resetStats();
      }

      /// <summary>
      /// Returns the Ticks per Second rate since the last stat reset.
      /// </summary>
      INLINE double getTps() const
      {
         // nanoseconds since last stat reset
         const double SPANLASTSTATS = getDurationStatReset();
         
         // multiplier from ns to s scaled by scaler
         const double CONVERT = 0.000000001 * (double)DIVISOR;

         const double DTICKS = (double)mTicks;
         const double DSPAN  = (double)SPANLASTSTATS * CONVERT;

         // return ticks per second
         return DTICKS / DSPAN;
      }

      /// <summary>
      /// Resets the Stats, but leaves the current tick and duration untouched.
      /// Returns the ticks per seconds 
      /// </summary>
      INLINE void resetStats()
      {
         mDurationSum = 0.0;
         mAverage     = 0.0;
         mBest        = (double)UINT32_MAX;
         mWorst       = 0.0;
         mTicks       = 0;
         mStatReset   = getClockTick();
      }

      /// <summary>
      /// Ticks the Ticker
      /// </summary>
      INLINE void tick()
      {
         const double NOW = getClockTick();

         // update end tick, calculate duration and duration sum
         mDuration = NOW - mTick;
         mDurationSum += mDuration;
         mTick = NOW;

         // possibly save tick as worst or best
         if (mDuration > mWorst) mWorst = mDuration;
         if (mDuration < mBest)  mBest = mDuration;

         // increment tick counter for stats
         mTicks++;

         // update average
         mAverage = mDurationSum / (double)mTicks;
      }

      /////////////////////////////////////////////////////////////////////

      /// <summary>
      /// True if reset stats has not been called at least for the desiredInterval
      /// </summary>
      INLINE bool canStatReset(const double desiredInterval) const
      {
         return getDurationStatReset() >= desiredInterval;
      }
   };

   typedef Ticker<CPPCORE_TICKER_NANOSECONDS_IN_SECOND>      TickerS;
   typedef Ticker<CPPCORE_TICKER_NANOSECONDS_IN_MILLISECOND> TickerMS;
   typedef Ticker<CPPCORE_TICKER_NANOSECONDS_IN_MIKROSECOND> TickerUS;
}
