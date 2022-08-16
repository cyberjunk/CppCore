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
      INLINE virtual bool schedule(Runnable& runnable, const StdTimePoint executeAt = StdTimePoint(StdNanoSeconds(0)))
      {
         return false;
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
