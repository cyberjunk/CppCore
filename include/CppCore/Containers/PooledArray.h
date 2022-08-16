#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Array.h>
#include <CppCore/Containers/Pool.h>

namespace CppCore
{
   /// <summary>
   /// 
   /// </summary>
   class PooledArray
   {
   public:
      /// <summary>
      /// 
      /// </summary>
      class Fix
      {
      private:
         INLINE Fix() { }

      public:
         /// <summary>
         /// Pooled Array for Single Thread Access
         /// </summary>
         template<class T, size_t SIZE>
         class ST : public Array::Fix::ST<T*, SIZE>
         {
         protected:
            Pool::Fix::ST<T, SIZE> mPool;

         public:
            INLINE ST() : Array::Fix::ST<T*, SIZE>()
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
