#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Queue.h>
#include <CppCore/Containers/Pool.h>

namespace CppCore
{
   /// <summary>
   /// Pooled Queue
   /// </summary>
   class PooledQueue
   {
   public:
      /// <summary>
      /// Fixed Size
      /// </summary>
      class Fix
      {
      private:
         INLINE Fix() { }

      public:
         /// <summary>
         /// Pooled Queue for Single Thread Access
         /// </summary>
         template<class T, size_t SIZE>
         class ST : public Queue::ST<T*, SIZE>
         {
         protected:
            Pool::Fix::ST<T, SIZE> mPool;

         public:
            INLINE ST() : Queue::ST<T*, SIZE>()
            {
            }
            INLINE bool pushFree(T* item)
            {
               return mPool.pushBack(item);
            }
            INLINE bool popFree(T*& item)
            {
               return mPool.popBack(item);
            }
            INLINE T* popFree()
            {
               T* item; 
               return mPool.popBack(item) ? item : 0;
            }
            INLINE void clear()
            {
               T* item;
               while (this->popBack(item))
                  pushFree(item);
            }
         };

         /// <summary>
         /// Pooled Queue for Multi Thread Access
         /// </summary>
         template<class T, size_t SIZE>
         class MT : public Queue::MT<T*, SIZE>
         {
         protected:
            Pool::Fix::MT<T, SIZE> mPool;

         public:
            INLINE MT() : Queue::MT<T*, SIZE>()
            {
            }
            INLINE bool pushFree(T* item)
            {
               return mPool.pushBack(item);
            }
            INLINE bool popFree(T*& item)
            {
               return mPool.popBack(item);
            }
            INLINE T* popFree()
            {
               T* item; 
               return mPool.popBack(item) ? item : 0;
            }
            INLINE void clear()
            {
               T* item;
               while (this->popBack(item))
                  pushFree(item);
            }
         };
      };
   };
}
