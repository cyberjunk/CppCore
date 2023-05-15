#pragma once

#include <CppCore/Root.h>
#include <CppCore/Threading/Runnable.h>

namespace CppCore
{
   /// <summary>
   /// Handler for Runnables
   /// </summary>
   class Handler
   {
   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Handler() { }

      /// <summary>
      /// Tries to schedule a Runnable for execution in this Handler.
      /// </summary>
      INLINE virtual bool schedule(Runnable& runnable, const TimePointHR executeAt)
      {
         return false;
      }

      /// <summary>
      /// Tries to add a Runnable to this Schedule executing after given duration (from now).
      /// </summary>
      INLINE bool schedule(Runnable& runnable, const DurationHR executeIn)
      {
         return schedule(runnable, ClockHR::now() + executeIn);
      }

      /// <summary>
      /// Tries to add an instant Runnable to this Schedule
      /// </summary>
      INLINE bool schedule(Runnable& runnable)
      {
         return runnable.isRepeat() ?
            schedule(runnable, ClockHR::now() + runnable.getInterval()) :
            schedule(runnable, TimePointHR(DurationHR::zero()));
      }

      /// <summary>
      /// Tries to remove a Runnable from this Handler.
      /// </summary>
      INLINE virtual bool cancel(Runnable& runnable)
      {
         return false;
      }
   };
}
