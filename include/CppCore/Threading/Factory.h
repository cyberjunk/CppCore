#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Array.h>
#include <CppCore/Containers/PooledQueue.h>
#include <CppCore/Threading/Runnable.h>
#include <CppCore/Threading/Handler.h>
#include <CppCore/Logger.h>

namespace CppCore
{
   /// <summary>
   /// Factory. Do not exceed CPPCORE_FACTORY_MAXWORKERS in NUMWORKERS.
   /// </summary>
   template<
      typename LOGGER,
      typename TASKDATA,   size_t TASKMAX, 
      typename RESULTDATA, size_t RESULTMAX,
      typename WORKERDATA, size_t NUMWORKERS,
      size_t USERMAX, 
      size_t TASKUSERMAX>
   class Factory : public Logger::Producer<LOGGER, Logger::Channel::Factory>
   {
   public:
      /// <summary>
      /// Factory Task
      /// </summary>
      class Task
      {
      public:
         typedef Array::Fix::ST<size_t, TASKUSERMAX> ArrayUserIds;

      protected:
         size_t       mId;
         ArrayUserIds mUserIds;
         TASKDATA     mData;
      public:
         INLINE size_t getId() const { return mId; }
         INLINE TASKDATA& getData() { return mData; }
         INLINE void setId(const size_t id) { mId = id; }
         INLINE bool pushUserId(const size_t id)
         {
            size_t idx;
            if (mUserIds.findIdxUnsorted(id, idx)) return true;
            else return mUserIds.pushBack(id);
         }
         INLINE bool popUserId(size_t& id)
         { 
            return mUserIds.popBack(id);
         }

         /// <summary>
         /// ComparerId
         /// </summary>
         class ComparerId
         {
         private:
            INLINE ComparerId() { }
         public:
            class O2K
            {
            public:
               INLINE static bool equal(Task& a, size_t key)     { return a.getId() == key; }
               INLINE static bool nequal(Task& a, size_t key)    { return a.getId() != key; }
               INLINE static bool less(Task& a, size_t key)      { return a.getId() <  key; }
               INLINE static bool lesseq(Task& a, size_t key)    { return a.getId() <= key; }
               INLINE static bool greater(Task& a, size_t key)   { return a.getId() >  key; }
               INLINE static bool greatereq(Task& a, size_t key) { return a.getId() >= key; }
            };
            class OP2K
            {
            public:
               INLINE static bool equal(Task* a, size_t key)     { return a->getId() == key; }
               INLINE static bool nequal(Task* a, size_t key)    { return a->getId() != key; }
               INLINE static bool less(Task* a, size_t key)      { return a->getId() <  key; }
               INLINE static bool lesseq(Task* a, size_t key)    { return a->getId() <= key; }
               INLINE static bool greater(Task* a, size_t key)   { return a->getId() >  key; }
               INLINE static bool greatereq(Task* a, size_t key) { return a->getId() >= key; }
            };
            class O2O
            {
            public:
               INLINE static bool equal(Task& a, Task& b)      { return a.getId() == b.getId(); }
               INLINE static bool nequal(Task& a, Task& b)     { return a.getId() != b.getId(); }
               INLINE static bool less(Task& a, Task& b)       { return a.getId() <  b.getId(); }
               INLINE static bool lesseq(Task& a, Task& b)     { return a.getId() <= b.getId(); }
               INLINE static bool greater(Task& a, Task& b)    { return a.getId() >  b.getId(); }
               INLINE static bool greatereq(Task& a, Task& b)  { return a.getId() >= b.getId(); }
            };
            class OP2OP
            {
            public:
               INLINE static bool equal(Task* a, Task* b)      { return a->getId() == b->getId(); }
               INLINE static bool nequal(Task* a, Task* b)     { return a->getId() != b->getId(); }
               INLINE static bool less(Task* a, Task* b)       { return a->getId() <  b->getId(); }
               INLINE static bool lesseq(Task* a, Task* b)     { return a->getId() <= b->getId(); }
               INLINE static bool greater(Task* a, Task* b)    { return a->getId() >  b->getId(); }
               INLINE static bool greatereq(Task* a, Task* b)  { return a->getId() >= b->getId(); }
            };
         };
      };

      /// <summary>
      /// Factory Result
      /// </summary>
      class Result
      {
      protected:
         Task*      mTask;
         RESULTDATA mData;
      public:
         INLINE Task*       getTask() { return mTask; }
         INLINE RESULTDATA& getData() { return mData; }
         INLINE void setTask(Task* t) { mTask = t; }
      };

      /// <summary>
      /// Factory User and Callback.
      /// Implement this with the class using the factory.
      /// </summary>
      class User
      {
      protected:
         friend Factory;

         size_t   mFactoryUserId;
         Factory* mFactory;
         uint32_t mPendingTaskLimit;
         uint32_t mPendingTasks;

      public:
         /// <summary>
         /// Constructor
         /// </summary>
         INLINE User(Factory* factory = 0) : 
            mFactoryUserId(0),
            mFactory(factory),
            mPendingTaskLimit(0),
            mPendingTasks(0)
         {
            if (mFactory)
               mFactory->registerFactoryUser(*this);
         }

         /// <summary>
         /// Sets the factory used by this factory user.
         /// </summary>
         INLINE void setFactory(Factory* factory)
         {
            // if different
            if (mFactory != factory)
            {
               // unregister from old factory
               if (mFactory)
                  mFactory->unregisterFactoryUser(*this);

               // set to new
               mFactory = factory;

               // register to new (if set)
               if (mFactory)
                  mFactory->registerFactoryUser(*this);
            }
         }

         /// <summary>
         /// Returns the factory user id of this factory user.
         /// </summary>
         INLINE size_t getFactoryUserId() const
         { 
            return mFactoryUserId; 
         }

         /// <summary>
         /// Returns the limit of pending tasks (queries without responses) this user can have.
         /// </summary>
         INLINE uint32_t getPendingTaskLimit() const { return mPendingTaskLimit; }

         /// <summary>
         /// Sets the limit of pending tasks for this user. Default = 0 = no limit.
         /// </summary>
         INLINE void setPendingTaskLimit(const uint32_t v) { mPendingTaskLimit = v; }

         /// <summary>
         /// Returns how many pending tasks this factory user currently got.
         /// </summary>
         INLINE uint32_t getPendingTasks() const { return mPendingTasks; }

         /// <summary>
         /// True if pending task limit is greater than 0 (enabled) and pending tasks
         /// is equal or even greater than pending tasks limit.
         /// </summary>
         INLINE bool isPendingTaskLimitReached() const { return mPendingTaskLimit > 0 && mPendingTasks >= mPendingTaskLimit; }

         /// <summary>
         /// Override this with your MainThread result handler
         /// </summary>
         INLINE virtual void onFactoryResult(TASKDATA& task, RESULTDATA& result) = 0;

         /// <summary>
         /// Tries to register the user for the response of a pending factory task with given id.
         /// </summary>
         INLINE bool hookPendingFactoryTask(const size_t id)
         {
            Task* t;

            // try find existing task id
            if (mFactory->mTasksPending.template findUnsorted<size_t, typename Task::ComparerId::OP2K>(id, t))
            {
               // register to it (prevents multi registering)
               return t->pushUserId(mFactoryUserId);
            }
            else
               return false;
         }

         /// <summary>
         /// Gets a free task from the Factory.
         /// You must call pushTask() with it afterwards!
         /// </summary>
         INLINE Task* getFactoryTask(const size_t id = 0)
         {
            Task* t = 0;

            if (mFactory && mFactory->mTasks.popFree(t))
            {
               // set id on task, either provided one or
               // an unique one from memory address
               t->setId(id ? id : (size_t)t);

               // add us to response receivers
               t->pushUserId(mFactoryUserId);
            }

            return t;
         }

         /// <summary>
         /// Schedules a task retrieved from popFreeTask() in the Factory.
         /// Do not access 'task' afterwards, neither on 'true' nor on 'false'.
         /// </summary>
         INLINE bool runFactoryTask(Task* task)
         {
            // no factory set yet
            if (!mFactory)
               return false;

            // TODO: There seems to be a bug with this code and runnables
            // not running even though there are tasks in the queue

            // pending task limit set and reached, pushback to free ones
            if (isPendingTaskLimitReached())
            {
               mFactory->mThreadPool.schedule(mFactory->mWorkers[0].mRunnable); //workaround
               mFactory->mTasks.pushFree(task);
               return false;
            }

            // enqueue task, pushback to free on failure
            // or add to pending ones on success
            if (!mFactory->mTasks.pushBack(task))
            {
               mFactory->mTasks.pushFree(task);
               return false;
            }
            else
               mFactory->mTasksPending.pushBack(task);

            // increase pending taskscounter;
            mPendingTasks++;

            // find idle worker runnable to schedule
            for (size_t i = 0; i < NUMWORKERS; i++)
            {
               Runnable& run = mFactory->mWorkers[i].mRunnable;
               if (run.isIdle() && mFactory->mThreadPool.schedule(run))
                  return true;
            }

            // if we get here none was idle, one worker will likely
            // catch the already added task in his loop
            // to be sure we schedule/reschedule(repeat) at least one
            mFactory->mThreadPool.schedule(mFactory->mWorkers[0].mRunnable);
            return true;
         }

         /// <summary>
         /// Comparer
         /// </summary>
         class ComparerFactoryUserId
         {
         private:
            INLINE ComparerFactoryUserId() { }
         public:
            class O2K
            {
            public:
               INLINE static bool equal(User& a, size_t key)     { return a.getFactoryUserId() == key; }
               INLINE static bool nequal(User& a, size_t key)    { return a.getFactoryUserId() != key; }
               INLINE static bool less(User& a, size_t key)      { return a.getFactoryUserId() <  key; }
               INLINE static bool lesseq(User& a, size_t key)    { return a.getFactoryUserId() <= key; }
               INLINE static bool greater(User& a, size_t key)   { return a.getFactoryUserId() >  key; }
               INLINE static bool greatereq(User& a, size_t key) { return a.getFactoryUserId() >= key; }
            };
            class OP2K
            {
            public:
               INLINE static bool equal(User* a, size_t key)     { return a->getFactoryUserId() == key; }
               INLINE static bool nequal(User* a, size_t key)    { return a->getFactoryUserId() != key; }
               INLINE static bool less(User* a, size_t key)      { return a->getFactoryUserId() <  key; }
               INLINE static bool lesseq(User* a, size_t key)    { return a->getFactoryUserId() <= key; }
               INLINE static bool greater(User* a, size_t key)   { return a->getFactoryUserId() >  key; }
               INLINE static bool greatereq(User* a, size_t key) { return a->getFactoryUserId() >= key; }
            };
            class O2O
            {
            public:
               INLINE static bool equal(User& a, User& b)      { return a.getFactoryUserId() == b.getFactoryUserId(); }
               INLINE static bool nequal(User& a, User& b)     { return a.getFactoryUserId() != b.getFactoryUserId(); }
               INLINE static bool less(User& a, User& b)       { return a.getFactoryUserId() <  b.getFactoryUserId(); }
               INLINE static bool lesseq(User& a, User& b)     { return a.getFactoryUserId() <= b.getFactoryUserId(); }
               INLINE static bool greater(User& a, User& b)    { return a.getFactoryUserId() >  b.getFactoryUserId(); }
               INLINE static bool greatereq(User& a, User& b)  { return a.getFactoryUserId() >= b.getFactoryUserId(); }
            };
            class OP2OP
            {
            public:
               INLINE static bool equal(User* a, User* b)      { return a->getFactoryUserId() == b->getFactoryUserId(); }
               INLINE static bool nequal(User* a, User* b)     { return a->getFactoryUserId() != b->getFactoryUserId(); }
               INLINE static bool less(User* a, User* b)       { return a->getFactoryUserId() <  b->getFactoryUserId(); }
               INLINE static bool lesseq(User* a, User* b)     { return a->getFactoryUserId() <= b->getFactoryUserId(); }
               INLINE static bool greater(User* a, User* b)    { return a->getFactoryUserId() >  b->getFactoryUserId(); }
               INLINE static bool greatereq(User* a, User* b)  { return a->getFactoryUserId() >= b->getFactoryUserId(); }
            };
         };
      };

      /// <summary>
      /// Factory Worker
      /// </summary>
      class Worker
      {
      public:
         Runnable   mRunnable;
         bool       mBlocked;
         WORKERDATA mData;
         INLINE Worker() : mRunnable(), mBlocked(false) { }
         INLINE void setFunction(const RunnableFunction& f) { mRunnable.setFunction(f); }
      };

   protected:
      typedef Array::Fix::ST<Task*, TASKMAX>          ArrayTask;
      typedef PooledQueue::Fix::MT<Task, TASKMAX>     QueueTask;
      typedef PooledQueue::Fix::MT<Result, RESULTMAX> QueueResult;
      typedef Array::Fix::ST<User*, USERMAX>          ArrayUser;

      uint32_t    mNextUserId;
      ArrayUser   mUsers;
      Handler&    mApplication;
      Handler&    mThreadPool;
      ArrayTask   mTasksPending;
      QueueTask   mTasks;
      QueueResult mResults;
      Runnable    mRunnableOnResult;
      Worker      mWorkers[NUMWORKERS];

      /// <summary>
      /// Executed by the worker runnables
      /// </summary>
      INLINE void work(Worker& worker)
      {
         Task* task;
         Result* result;

         // loop pending tasks
         while (mTasks.popFront(task))
         {
            // try to get a free result
            if (mResults.popFree(result))
            {
               // mark as not blocked by nonfree result
               worker.mBlocked = false;

               // init the result by attaching the task
               result->setTask(task);

               // run the calculation
               process(worker.mData, task->getData(), result->getData());

               // push result and schedule mainthread callback
               mResults.pushBack(result);
               mApplication.schedule(mRunnableOnResult);
            }

            // no free result, push back task to front of queue
            else
            {
               // mark as blocked by nonfree result
               worker.mBlocked = true;

               // push task back and break (goto sleep)
               mTasks.pushFront(task);
               break;
            }
         }
      }

      /// <summary>
      /// Override this in own factory class and create result from task
      /// </summary>
      INLINE virtual void process(WORKERDATA& worker, TASKDATA& task, RESULTDATA& result) { }

      /// <summary>
      /// Executed in MainThread. Invokes callback on User.
      /// </summary>
      INLINE void onResult()
      {
         Result* r;
         User* u;

         // switched to true if got at least one result
         bool processed = false;

         // process available results
         while (mResults.popFront(r))
         {
            // invoke callback on all users that registered on that task
            size_t userid;
            while (r->getTask()->popUserId(userid))
            {
               if (mUsers.template findSorted<size_t, typename User::ComparerFactoryUserId::OP2K>(userid, u))
               {
                  u->mPendingTasks--;
                  u->onFactoryResult(r->getTask()->getData(), r->getData());
               }
            }

            // remove from pending tasks
            size_t idx;
            Task* item;
            mTasksPending.removeOneUnsorted(r->getTask(), item, idx);

            // add task and result back to free ones
            mTasks.pushFree(r->getTask());
            mResults.pushFree(r);

            // flag as processed one
            processed = true;
         }

         // if pushed back at least one free result
         // reschedule workers which got blocked
         if (processed)
            for (size_t i = 0; i < NUMWORKERS; i++)
               if (mWorkers[i].mBlocked)
                  mThreadPool.schedule(mWorkers[i].mRunnable);
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Factory(Handler& application, Handler& threadPool, LOGGER& logger) :
         Logger::Producer<LOGGER, Logger::Channel::Factory>(logger),
         mApplication(application),
         mThreadPool(threadPool),
         mNextUserId(0),
         mRunnableOnResult([this]() { onResult(); })
      {
         // log startup
         this->log("Initializing factory with " + ::std::to_string(NUMWORKERS) + " workers."));

         // validate maxworkers
         if (NUMWORKERS > 16)
         {
            this->logError("NUMWORKERS in Factory.h is set too large! Prepare for crash!");
            assert(false);
         }

         // disable the array bounds warning
         #if defined(CPPCORE_COMPILER_MSVC)
         //#pragma warning(disable:111)
         #elif defined(CPPCORE_COMPILER_CLANG)
         #pragma clang diagnostic push
         #pragma clang diagnostic ignored "-Warray-bounds"
         #endif

         // init workers
         CPPCORE_UNROLL
         for (size_t i = 0; i < NUMWORKERS; i++)
         {
            switch (i)
            {
            case  0: mWorkers[0].setFunction([this]() { work(mWorkers[0]);  });  break;
            case  1: mWorkers[1].setFunction([this]() { work(mWorkers[1]);  });  break;
            case  2: mWorkers[2].setFunction([this]() { work(mWorkers[2]);  });  break;
            case  3: mWorkers[3].setFunction([this]() { work(mWorkers[3]);  });  break;
            case  4: mWorkers[4].setFunction([this]() { work(mWorkers[4]);  });  break;
            case  5: mWorkers[5].setFunction([this]() { work(mWorkers[5]);  });  break;
            case  6: mWorkers[6].setFunction([this]() { work(mWorkers[6]);  });  break;
            case  7: mWorkers[7].setFunction([this]() { work(mWorkers[7]);  });  break;
            case  8: mWorkers[8].setFunction([this]() { work(mWorkers[8]);  });  break;
            case  9: mWorkers[9].setFunction([this]() { work(mWorkers[9]);  });  break;
            case 10: mWorkers[10].setFunction([this]() { work(mWorkers[10]);  }); break;
            case 11: mWorkers[11].setFunction([this]() { work(mWorkers[11]);  }); break;
            case 12: mWorkers[12].setFunction([this]() { work(mWorkers[12]);  }); break;
            case 13: mWorkers[13].setFunction([this]() { work(mWorkers[13]);  }); break;
            case 14: mWorkers[14].setFunction([this]() { work(mWorkers[14]);  }); break;
            case 15: mWorkers[15].setFunction([this]() { work(mWorkers[15]);  }); break;
            default: // ERROR TOO MANY WORKERS
               break;
            }
         }

         // enable the array bounds warning
         #if defined(CPPCORE_COMPILER_MSVC)
         //#pragma warning(default:111)
         #elif defined(CPPCORE_COMPILER_CLANG)
         #pragma clang diagnostic pop
         #endif
      }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~Factory()
      {
      }

      /// <summary>
      /// Register a Factory user that creates tasks to be processed on ThreadPool
      /// and processes results on MainThread.
      /// </summary>
      INLINE bool registerFactoryUser(User& user)
      {
         // assign id to this user to find his results
         user.mFactoryUserId = mNextUserId++;

         // ids always increase so we can pushback even if sorted
         return mUsers.pushBack(&user);
      }

      /// <summary>
      /// Unregister a Factory user.
      /// </summary>
      INLINE bool unregisterFactoryUser(const User& user)
      {
         User* item; size_t idx;
         return mUsers.template removeOneSorted<size_t, typename User::ComparerFactoryUserId::OP2K>(user.getFactoryUserId(), item, idx);
      }
   };
}
