#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Array.h>
#include <CppCore/Containers/Queue.h>
#include <CppCore/Containers/PooledArray.h>
#include <CppCore/Containers/PooledQueue.h>

namespace CppCore
{
   /// <summary>
   /// Observable Containers
   /// </summary>
   class Observable
   {
   public:
      /// <summary>
      /// Observable Container Listener
      /// </summary>
      template<typename T>
      class Listener
      {
      public:
         INLINE virtual void onItemAdded(T& item, const size_t idx) = 0;
         INLINE virtual void onItemRemoved(T& item, const size_t idx) = 0;
         INLINE virtual void onItemChanged(T& item, const size_t idx) = 0;
      };

      /////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Observable Container Base Class
      /// </summary>
      template<typename T, size_t MAXLISTENER>
      class Container
      {
      protected:
         CppCore::Array::Fix::ST<Listener<T>*, MAXLISTENER> mListeners;

      public:
         /// <summary>
         /// Fire onItemAdded() on all current listeners
         /// </summary>
         INLINE void fireOnItemAdded(T& item, const size_t idx)
         {
            const size_t LEN = mListeners.length();
            for (size_t i = 0; i < LEN; i++)
               mListeners[i]->onItemAdded(item, idx);
         }

         /// <summary>
         /// Fire onItemRemoved() on all current listeners
         /// </summary>
         INLINE void fireOnItemRemoved(T& item, const size_t idx)
         {
            const size_t LEN = mListeners.length();
            for (size_t i = 0; i < LEN; i++)
               mListeners[i]->onItemRemoved(item, idx);
         }

         /// <summary>
         /// Fire onItemChanged() on all current listeners
         /// </summary>
         INLINE void fireOnItemChanged(T& item, const size_t idx)
         {
            const size_t LEN = mListeners.length();
            for (size_t i = 0; i < LEN; i++)
               mListeners[i]->onItemChanged(item, idx);
         }

      public:
         /// <summary>
         /// Constructor
         /// </summary>
         INLINE Container()
         {
         }

         /// <summary>
         /// Register a listener on the container
         /// </summary>
         INLINE bool registerListener(Listener<T>* listener)
         {
            return mListeners.pushBack(listener);
         }

         /// <summary>
         /// Unregister a listener on the container
         /// </summary>
         INLINE bool unregisterListener(Listener<T>* listener)
         {
            Listener<T>* l;
            size_t idx;
            return mListeners.removeOneUnsorted(listener, l, idx);
         }
      };

      /////////////////////////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////////////////////
      
      /// <summary>
      /// Observable Containers Base Class
      /// </summary>
      class Containers
      {
      private:
         INLINE Containers() { }
      public:
         /// <summary>
         /// Base class for fixed size observable containers (e.g. array/queue)
         /// </summary>
         template<typename T, typename CONTAINER, size_t MAXLISTENER>
         class Fix :
            public CONTAINER,
            public Observable::Container<T*, MAXLISTENER>
         {
         public:
            template<bool NOTIFY = true>
            INLINE bool pushBack(T* item)
            {
               if (CONTAINER::pushBack(item))
               {
                  if (NOTIFY) this->fireOnItemAdded(item, this->mLength - 1);
                  return true;
               }
               else
                  return false;
            }
            template<bool NOTIFY = true>
            INLINE bool pushFront(T* item)
            {
               if (CONTAINER::pushFront(item))
               {
                  if (NOTIFY) this->fireOnItemAdded(item, 0);
                  return true;
               }
               else
                  return false;
            }
            template<bool NOTIFY = true>
            INLINE bool popBack(T*& item)
            {
               if (CONTAINER::popBack(item))
               {
                  if (NOTIFY) this->fireOnItemRemoved(item, this->mLength);
                  return true;
               }
               else
                  return false;
            }
            template<bool NOTIFY = true>
            INLINE bool popFront(T*& item)
            {
               if (CONTAINER::popFront(item))
               {
                  if (NOTIFY) this->fireOnItemRemoved(item, 0);
                  return true;
               }
               else
                  return false;
            }
            template<bool NOTIFY = true>
            INLINE void clear()
            {
               T* item;
               while (popBack<NOTIFY>(item)) { }
            }

            template<bool NOTIFY = true>
            INLINE bool insertAt(T*& item, size_t idx)
            {
               if (CONTAINER::insertAt(item, idx))
               {
                  if (NOTIFY) this->fireOnItemAdded(item, idx);
                  return true;
               }
               else
                  return false;
            }

            template<bool NOTIFY = true>
            INLINE bool removeAt(T*& item, size_t idx)
            {
               if (CONTAINER::removeAt(item, idx))
               {
                  if (NOTIFY) this->fireOnItemRemoved(item, idx);
                  return true;
               }
               else
                  return false;
            }

            template<typename KEY = T*, typename COMPARER = Comparer<T*, KEY>, bool NOTIFY = true>
            INLINE bool removeOneUnsorted(const KEY& key, T*& item, size_t& idx)
            {
               if (CONTAINER::template removeOneUnsorted<KEY, COMPARER>(key, item, idx))
               {
                  if (NOTIFY) this->fireOnItemRemoved(item, idx);
                  return true;
               }
               else
                  return false;
            }
            template<typename KEY = T*, typename COMPARER = Comparer<T*, KEY>, bool NOTIFY = true>
            INLINE bool removeOneSorted(const KEY& key, T*& item, size_t& idx)
            {
               if (CONTAINER::template removeOneSorted<KEY, COMPARER>(key, item, idx))
               {
                  if (NOTIFY) this->fireOnItemRemoved(item, idx);
                  return true;
               }
               else
                  return false;
            }
            template<typename KEY = T*, typename COMPARER = Comparer<T*, T*>, bool UNIQUE = false, bool NOTIFY = true>
            INLINE bool insertSorted(T* item, size_t& idx)
            {
               if (CONTAINER::template insertSorted<KEY, COMPARER, UNIQUE>(item, idx))
               {
                  if (NOTIFY) this->fireOnItemAdded(item, idx);
                  return true;
               }
               else
                  return false;
            }
            INLINE void fireEventsAfterReset(const size_t oldLength)
            {
               const size_t NEWLENGTH = this->length();

               // more than before:
               // fire change for the ones that already existed
               // fire add for the new ones
               if (NEWLENGTH > oldLength)
               {
                  for (size_t i = 0; i < oldLength; i++)
                     this->fireOnItemChanged(this->operator[](i), i);

                  for (size_t i = oldLength; i < NEWLENGTH; i++)
                     this->fireOnItemAdded(this->operator[](i), i);
               }

               // less than before:
               // fire change for the ones that still existed
               // fire remove for the ones that do not anymore
               else if (NEWLENGTH < oldLength)
               {
                  for (size_t i = 0; i < NEWLENGTH; i++)
                     this->fireOnItemChanged(this->operator[](i), i);

                  for (size_t i = NEWLENGTH; i < oldLength; i++)
                     this->fireOnItemRemoved(this->operator[](i), i);
               }

               // same as before
               // fire change for all
               else
               {
                  for (size_t i = 0; i < NEWLENGTH; i++)
                     this->fireOnItemChanged(this->operator[](i), i);
               }
            }
         };
      };

      /// <summary>
      /// Observable Array
      /// </summary>
      class Array
      {
      private:
         INLINE Array() { }
      public:
         template<typename T, size_t SIZE, size_t MAXLISTENER>
         class Fix : public Containers::Fix<T, CppCore::Array::Fix::ST<T*, SIZE>, MAXLISTENER>
         {
            typedef Containers::Fix<T, CppCore::Array::Fix::ST<T*, SIZE>, MAXLISTENER> Base;

         public:
         };
      };

      /// <summary>
      /// Observable PooledArray
      /// </summary>
      class PooledArray
      {
      private:
         INLINE PooledArray() { }
      public:
         template<typename T, size_t SIZE, size_t MAXLISTENER>
         class Fix : public Containers::Fix<T, CppCore::PooledArray::Fix::ST<T, SIZE>, MAXLISTENER>
         {
            typedef Containers::Fix<T, CppCore::PooledArray::Fix::ST<T, SIZE>, MAXLISTENER> Base;

         public:
            template<bool NOTIFY = true>
            INLINE void clear()
            {
               T* item;
               while (Base::template popBack<NOTIFY>(item))
                  Base::pushFree(item);
            }
         };
      };

      /// <summary>
      /// Observable PooledQueue
      /// </summary>
      class PooledQueue
      {
      private:
         INLINE PooledQueue() { }
      public:
         template<typename T, size_t SIZE, size_t MAXLISTENER>
         class Fix : public Containers::Fix<T, CppCore::PooledQueue::Fix::ST<T, SIZE>, MAXLISTENER>
         {
            typedef Containers::Fix<T, CppCore::PooledQueue::Fix::ST<T, SIZE>, MAXLISTENER> Base;

         public:
            template<bool NOTIFY = true>
            INLINE void clear()
            {
               T* item;
               while (Base::popBack<NOTIFY>(item))
                  Base::pushFree(item);
            }
         };
      };
   };
}
