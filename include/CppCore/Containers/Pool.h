#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Array.h>

namespace CppCore
{
   /// <summary>
   /// Fixed size stack with same amount of items locally allocated and pushed.
   /// When you pop an item, you must push it back later.
   /// Do not push items which don't belong to the preallocated ones.
   /// </summary>
   class Pool
   {
   private:
      INLINE Pool() { }

   public:
      /// <summary>
      /// Fixed Size and All Item Memory allocated along with Pool
      /// </summary>
      class Fix
      {
      private:
         INLINE Fix() { }

      protected:
         /// <summary>
         /// Internal Base Class to share some code.
         /// </summary>
         template<class T, size_t SIZE>
         class Base
         {
         protected:
            T mPool[SIZE];
            INLINE Base() { }
         };

      public:
         /// <summary>
         /// Pool for Single Thread Access
         /// </summary>
         template<class T, size_t SIZE>
         class ST : Base<T, SIZE>, public Array::Fix::ST<T*, SIZE>
         {
         public:
            INLINE ST() : Base<T, SIZE>(), Array::Fix::ST<T*, SIZE>()
            {
               // push the items from the pool on the stack
               for (size_t i = 0; i < SIZE; i++)
                  Array::Fix::ST<T*, SIZE>::pushBack(&Base<T, SIZE>::mPool[i]);
            }
            INLINE bool pushBack(T* item)
            {
               return Array::Fix::ST<T*, SIZE>::pushBack(item);
            }
            INLINE bool popBack(T*& item)
            {
               return Array::Fix::ST<T*, SIZE>::popBack(item);
            }
            INLINE T* getPoolPtr() { return &this->mPool[0]; }
         };

      #ifndef CPPCORE_NO_THREADING
         /// <summary>
         /// Pool for Multi Thread Access with internal Locking
         /// </summary>
         template<class T, size_t SIZE>
         class MT : Base<T, SIZE>, public Array::Fix::MT<T*, SIZE>
         {
         public:
            INLINE MT() : Base<T, SIZE>(), Array::Fix::MT<T*, SIZE>()
            {
               // push the items from the pool on the stack
               for (size_t i = 0; i < SIZE; i++)
                  Array::Fix::MT<T*, SIZE>::pushBack(&Base<T, SIZE>::mPool[i]);
            }
            INLINE bool pushBack(T* item)
            {
               return Array::Fix::MT<T*, SIZE>::pushBack(item);
            }
            INLINE bool popBack(T*& item)
            {
               return Array::Fix::MT<T*, SIZE>::popBack(item);
            }
         };
      #endif
      };

      ///////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Fixed Size but Item Memory allocated on-demand/dedicated from Pool
      /// </summary>
      class Dyn
      {
      private:
         INLINE Dyn() { }

      public:
         /// <summary>
         /// Pool for Single Thread Access
         /// </summary>
         template<class T, size_t SIZE>
         class ST
         {
         protected:
            Array::Fix::ST<T*, SIZE> mInstances;
            Array::Fix::ST<T*, SIZE> mFree;

         public:
            INLINE ST(const size_t initSize = SIZE/8)
            {
               // push the pre allocated ones on the stack
               for (size_t i = 0; i < initSize; i++)
               {
                  T* t = new T();         // create new instance
                  mInstances.pushBack(t); // push to internal instance tracking
                  mFree.pushBack(t);      // and to free ones
               }
            }
            INLINE ~ST()
            {
               T* item;

               // delete all allocated instances
               while (mInstances.popBack(item))
                  delete item;

               // reset size on free ones
               mFree.clear();
            }
            INLINE bool pushBack(T* item)
            {
               return mFree.pushBack(item);
            }
            INLINE bool popBack(T*& item)
            {
               // try get existing one from pool first
               if (mFree.popBack(item))
                  return true;

               T* t = new T();         // create new instance
               mInstances.pushBack(t); // push to internal instance tracking
               item = t;               // return it

               return true;
            }
            INLINE size_t memOnHeap() const
            {
               return mInstances.length() * sizeof(T);
            }
         };

      #ifndef CPPCORE_NO_THREADING
         /// <summary>
         /// Pool for Multi Thread Access with internal Locking
         /// </summary>
         template<class T, size_t SIZE>
         class MT
         {
         protected:
            Array::Fix::MT<T*, SIZE> mInstances;
            Array::Fix::MT<T*, SIZE> mFree;

         public:
            INLINE MT(const size_t initSize = SIZE/8)
            {
               // pre-created specified count
               for (size_t i = 0; i < initSize; i++)
               {
                  T* t = new T();         // create new instance
                  mInstances.pushBack(t); // add to tracked instances
                  mFree.pushBack(t);      // and to free ones
               }
            }
            INLINE ~MT()
            {
               T* item;

               // delete all allocated instances
               while (mInstances.popBack(item))
                  delete item;

               // reset size on free ones
               mFree.clear();
            }
            INLINE bool pushBack(T* item)
            {
               return mFree.pushBack(item);
            }
            INLINE bool popBack(T*& item)
            {
               // try get existing one from pool first
               if (mFree.popBack(item))
                  return true;

               T* t = new T();         // create new instance
               mInstances.pushBack(t); // add to tracked instances
               item = t;               // return it

               return true;
            }
            INLINE size_t memOnHeap() const
            {
               return mInstances.length() * sizeof(T);
            }
         };
      #endif
      };
   };
}
