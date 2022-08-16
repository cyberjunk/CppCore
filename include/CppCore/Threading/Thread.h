#pragma once

// if overwritten you must also adjust fixed size constructor
#ifndef CPPCORE_THREADPOOLSIZE
#define CPPCORE_THREADPOOLSIZE 8
#endif

#include <CppCore/Root.h>
#include <CppCore/Containers/Array.h>
#include <CppCore/Threading/Handler.h>
#include <CppCore/Threading/Schedule.h>
#include <CppCore/Threading/Looper.h>
#include <CppCore/Logger.h>

#ifdef CPPCORE_OS_WINDOWS
#include <processthreadsapi.h>
#endif

namespace CppCore
{
   /// <summary>
   /// Base class wrapping an async worker-thread.
   /// </summary>
   class Thread : public Looper, public Handler
   {
   protected:
      Schedule<>&          mSchedule;
      StdThread            mThread;
      StdMutex             mMutexStartStop;
      StdMutex             mMutexWait;
      StdConditionVariable mWait;
      StdThread::id        mId;

      virtual void init() { }
      virtual void shutdown() { }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Thread(Schedule<>& schedule) :
         Looper(schedule),
         mSchedule(schedule) { }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~Thread() { }

      /// <summary>
      /// Returns the internal Id of the thread
      /// </summary>
      INLINE const StdThread::id& getId() const { return mId; }

      /// <summary>
      /// Start the thread
      /// </summary>
      INLINE void start()
      {
         // lock (1 concurrent execution of start or stop)
         mMutexStartStop.lock();

         // must be stopped to start
         if (!isRunning())
         {
            // mark running
            setIsRunning(true);

            // lock startup wait
            // forces started thread to wait until we're in 'mWait.wait'
            StdUniqueLockMutex l(mMutexWait);

            // start thread
            mThread = ::std::thread(&Thread::threadProc, this);

            // wait until notify of started thread
            // wait unlocks on call and locks again on return
            mWait.wait(l);
            l.unlock();
         }

         // unlock (1 concurrent execution of start or stop)
         mMutexStartStop.unlock();
      }

      /// <summary>
      /// Stop the thread
      /// </summary>
      INLINE void stop()
      {
         // lock (1 concurrent execution of start or stop)
         mMutexStartStop.lock();
         
         if (isRunning())
         {
            // mark stopped
            setIsRunning(false);
            mSchedule.wakeAll();
         }

         // join thread
         if (mThread.joinable())
            mThread.join();

         // unlock (1 concurrent execution of start or stop)
         mMutexStartStop.unlock();
      }

      /// <summary>
      /// Tries to schedule a Runnable for execution in the Schedule used by this Thread.
      /// </summary>
      INLINE bool schedule(Runnable& runnable, StdTimePoint executeAt = StdTimePoint(StdNanoSeconds(0))) override
      {
         return mSchedule.schedule(runnable, executeAt);;
      }

      /// <summary>
      /// Tries to remove a Runnable from this Schedule
      /// </summary>
      INLINE bool cancel(Runnable& runnable) override
      {
         return mSchedule.cancel(runnable);
      }

   private:
      void threadProc()
      {
         // set id of thread
         mId = ::std::this_thread::get_id();

         // lock / wait until 'mWait.wait()' is called
         // and starter is ready for our notification
         StdUniqueLockMutex l(mMutexWait);

         // now notify starter that we're running
         l.unlock();
         mWait.notify_one();

      #ifdef CPPCORE_OS_WINDOWS
         ::SetThreadPriority(::GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN);
      #endif

         // subclass init
         init();

         // threadloop
         loop();

         // subclass shutdown
         shutdown();
      }

   public:
      /// <summary>
      /// Pool of Threads with a shared Schedule
      /// </summary>
      template<typename THREAD = Thread>
      class Pool : public Handler
      {
      protected:
         using Allocator = ::std::allocator<THREAD>;

      protected:
         Schedule<>    mSchedule;
         Allocator     mAllocator;
         StdAtomicBool mIsRunning;
         StdMutex      mMutexStartStop;
         THREAD*       mThreads;
         const size_t  mNumThreads;

         /// <summary>
         ///
         /// </summary>
         INLINE void setIsRunning(bool isRunning) { mIsRunning.store(isRunning); }

      public:
         /// <summary>
         /// Constructor
         /// </summary>
         INLINE Pool(
            const size_t numthreads = CPPCORE_THREADPOOLSIZE, 
            const bool   autoStart  = true) : 
            mNumThreads(numthreads),
            mThreads(mAllocator.allocate(numthreads))
         {
            // construct threads
            for (size_t i = 0; i < mNumThreads; i++)
               mAllocator.construct(&mThreads[i], mSchedule);

            // start if autostart
            if (autoStart)
               start();
         }

         /// <summary>
         /// Destructor
         /// </summary>
         INLINE ~Pool()
         {
            // free memory
            mAllocator.deallocate(mThreads, mNumThreads);
         }

         /// <summary>
         /// Index Operator
         /// </summary>
         INLINE THREAD& operator[](size_t index) { return mThreads[index]; }

         /// <summary>
         /// Returns how many threads are in the pool.
         /// </summary>
         INLINE size_t getSize() const { return mNumThreads; }

         /// <summary>
         /// Returns the internal Id of the thread
         /// </summary>
         INLINE const StdThread::id& getId(size_t idx) const { return mThreads[idx].getId(); }

         /// <summary>
         /// Returns true if the threadpool is runnning
         /// </summary>
         INLINE bool isRunning() const { return mIsRunning.load(); }

         /// <summary>
         /// Returns true if the thread specified by idx is currently executing and not sleeping
         /// </summary>
         INLINE bool isExecuting(size_t idx) const { return mThreads[idx].isExecuting(); }

         /// <summary>
         /// Start the threads in the pool
         /// </summary>
         INLINE void start()
         {
            mMutexStartStop.lock();
            if (!isRunning())
            {
               for (size_t i = 0; i < mNumThreads; i++)
                  mThreads[i].start();
               setIsRunning(true);
            }
            mMutexStartStop.unlock();
         }

         /// <summary>
         /// Stop the threads in the pool
         /// </summary>
         INLINE void stop()
         {
            mMutexStartStop.lock();
            if (isRunning())
            {
               for (size_t i = 0; i < mNumThreads; i++)
                  mThreads[i].stop();
               setIsRunning(false);
            }
            mMutexStartStop.unlock();
         }

         /// <summary>
         /// Tries to schedule a Runnable for execution in the Runnable used by this Pool.
         /// </summary>
         INLINE bool schedule(Runnable& runnable, const StdTimePoint executeAt = StdTimePoint(StdNanoSeconds(0))) override
         {
            return mSchedule.schedule(runnable, executeAt);;
         }

         /// <summary>
         /// Tries to remove a Runnable from this Schedule
         /// </summary>
         INLINE bool cancel(Runnable& runnable) override
         {
            return mSchedule.cancel(runnable);
         }

         /// <summary>
         /// Returns Memory used on Heap
         /// </summary>
         INLINE size_t memOnHeap() const
         {
            return sizeof(THREAD) * mNumThreads;
         }
      };
   };
}
