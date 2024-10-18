#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Util/QuickSort.h>
#include <CppCore/Containers/Util/BinarySearch.h>

namespace CppCore
{
   /// <summary>
   /// Fixed Size FIFO Queue.
   /// Use nested classes ST and MT.
   /// </summary>
   class Queue
   {
   public:
      /// <summary>
      /// FIFO Queue for Single Thread Access
      /// </summary>
      template<class T, size_t SIZE>
      class ST
      {
      protected:
         T      mData[SIZE];
         size_t mLength;
         size_t mIdxEnqueue;
         size_t mIdxDequeue;

      public:
         /// <summary>
         /// References the next item to dequeue at index 0
         /// and the last enqueued item at index length()-1.
         /// </summary>
         INLINE T& operator[](size_t index) { return mData[(mIdxDequeue + index) % SIZE]; }

      protected:
         /// <summary>
         /// C++ Iterator (BACKWARDS)
         /// </summary>
         class Iterator
         {
         protected:
            size_t mIdx;
            ST&    mQueue;
         public:
            INLINE Iterator(size_t idx, ST& queue) : mIdx(idx), mQueue(queue) { }
            INLINE T&        operator*()                           { return mQueue[mIdx];  }
            INLINE Iterator& operator++()                          { mIdx--; return *this; }
            INLINE bool      operator!=(const Iterator& end) const { return mIdx != numeric_limits<size_t>::max(); }
         };

      public:
         /// <summary>
         /// Constructor
         /// </summary>
         INLINE ST() :
            mLength(0), 
            mIdxEnqueue(0),
            mIdxDequeue(0) { }

         INLINE Iterator begin() { return Iterator(mLength-1, *this); }
         INLINE Iterator end()   { return Iterator(0, *this);         }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE size_t size() const { return SIZE; }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE size_t length() const { return mLength; }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE void swap(const size_t idx1, const size_t idx2)
         {
            T tmp = (*this)[idx1];
            (*this)[idx1] = (*this)[idx2];
            (*this)[idx2] = tmp;
         }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE void clear()
         {
            mLength = 0;
            mIdxEnqueue = 0;
            mIdxDequeue = 0;
         }

         //////////////////////////////////////////////////////////////////////
         // INDEX OPS

         /// <summary>
         /// Complexity: O(n)
         /// </summary>
         INLINE bool removeAt(T& item, size_t idx)
         {
            const size_t LEN = mLength;
            if (idx < LEN)
            {
               // return removed item at index
               item = (*this)[idx];

               // swap the item to remove to the last item
               for (; idx < LEN - 1; idx++)
                  swap(idx, idx + 1);

               // decrease length
               mLength = LEN - 1;

               // get index for pushBack
               const size_t IDX = mIdxEnqueue;

               // decrease idx for next pushBack
               mIdxEnqueue = IDX > 0 ?
                  IDX - 1 : SIZE - 1;

               return true;
            }
            else
               return false;
         }

         /// <summary>
         /// Complexity: O(n)
         /// </summary>
         INLINE bool insertAt(const T& item, size_t idx)
         {
            const size_t LEN = mLength;
            if (idx <= LEN && LEN < SIZE)
            {
               // swap the first unused slot to idx slot
               for (size_t k = LEN; k > idx; k--)
                  swap(k, k - 1);

               // save new item at idx
               (*this)[idx] = item;

               // save incremented size
               mLength = LEN + 1;

               // increment index for next pushBack
               mIdxEnqueue = (mIdxEnqueue + 1) % SIZE;

               return true;
            }
            else
               return false;
         }

         //////////////////////////////////////////////////////////////////////
         // FRONT/BACK OPS

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE bool pushBack(const T& item)
         {
            const size_t CURSIZE = mLength;
            if (CURSIZE < SIZE)
            {
               const size_t IDX = mIdxEnqueue; // get index for enqueue
               mData[IDX]  = item;             // save item
               mLength     = CURSIZE + 1;      // save incremented size
               mIdxEnqueue = (IDX + 1) % SIZE; // increment index with overflow handling
               return true;
            }
            else
               return false;
         }
         
         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE bool pushFront(const T& item)
         {
            const size_t CURSIZE = mLength;
            if (CURSIZE < SIZE)
            {
               // decrement index with underflow handling
               const size_t IDX = mIdxDequeue > 0 ?
                  mIdxDequeue - 1 : SIZE - 1;

               mData[IDX]  = item;        // save item
               mLength     = CURSIZE + 1; // save incremented size
               mIdxDequeue = IDX;         // save index
               return true;
            }
            else
               return false;
         }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE bool popBack(T& item)
         {
            const size_t CURSIZE = mLength;
            if (CURSIZE > 0)
            {
               const size_t IDX = mIdxEnqueue; // get index for dequeue
               item       = mData[IDX];        // set return item
               mLength     = CURSIZE - 1;      // save decremented size
               mIdxEnqueue = IDX > 0 ? IDX - 1 : SIZE - 1;
               return true;
            }
            else
               return false;
         }
         
         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE bool popFront(T& item)
         {
            const size_t CURSIZE = mLength;
            if (CURSIZE > 0)
            {
               const size_t IDX = mIdxDequeue; // get index for dequeue
               item       = mData[IDX];        // set return item
               mLength     = CURSIZE - 1;      // save decremented size
               mIdxDequeue = (IDX + 1) % SIZE; // increment index with overflow handling
               return true;
            }
            else
               return false;
         }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE bool peekBack(T& item)
         {
            if (mLength > 0)
            {
               item = mData[mIdxEnqueue];
               return true;
            }
            else
               return false;
         }
         
         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE bool peekFront(T& item)
         {
            if (mLength > 0)
            {
               item = mData[mIdxDequeue];
               return true;
            }
            else
               return false;
         }
         
         //////////////////////////////////////////////////////////////////////
         // FIX ORDER OPS

         /// <summary>
         /// Moves entry with changed key in sorted list
         /// to the left until in right spot again. No bound check on idx.
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE void fixOrderAtLeft(size_t idx)
         {
            while (idx > 0)
            {
               const size_t left = idx - 1;
               if (COMPARER::less(mData[idx], mData[left]))
               {
                  swap(idx, left);
                  idx = left;
               }
               else
                  return;
            }
         }

         /// <summary>
         /// Moves entry with changed key in sorted list
         /// to the right until in right spot again. No bound check on idx.
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE void fixOrderAtRight(size_t idx, const size_t len)
         {
            while (idx < len - 1)
            {
               const size_t right = idx + 1;
               if (COMPARER::less(mData[right], mData[idx]))
               {
                  swap(idx, right);
                  idx = right;
               }
               else
                  return;
            }
         }

         /// <summary>
         /// Moves entry with changed key in list array
         /// until in right spot again. No bound check on idx.
         /// Use one of the subfunc if you know the direction!
         /// </summary>
         template<typename CMPLESS = Comparer<T, T>>
         INLINE void fixOrderAt(size_t idx)
         {
            fixOrderAtLeft<CMPLESS>(idx);
            fixOrderAtRight<CMPLESS>(idx, mLength);
         }

         //////////////////////////////////////////////////////////////////////
         // SORT

         /// <summary>
         /// Complexity: O(n*log(n))
         /// </summary>
         template<typename COMPARER = Comparer<T, T>, size_t MEMSIZE>
         INLINE bool sort(size_t stack[MEMSIZE])
         {
            return QuickSort::sort<ST, T, COMPARER, MEMSIZE>((*this), stack);
         }

         //////////////////////////////////////////////////////////////////////
         // KEY OPS

         /// <summary>
         /// Complexity: O(n)
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool findIdxUnsorted(const KEY& item, size_t& idx)
         {
            const size_t LEN = length();
            for (idx = 0; idx < LEN; idx++)
            {
               if (COMPARER::nequal((*this)[idx], item))
                  continue;

               else
                  return true;
            }
            return false;
         }

         /// <summary>
         /// Complexity: O(log(n))
         /// </summary>
         template<typename KEY = T,  typename COMPARER = Comparer<T, KEY>>
         INLINE bool findIdxSorted(const KEY& item, size_t& idx)
         {
            return BinarySearch<ST, T, KEY, COMPARER>::search((*this), item, idx);
         }

         /// <summary>
         /// Complexity: O(n)
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool findUnsorted(const KEY& key, T& item)
         {
            size_t idx;
            if (findIdxUnsorted<KEY, COMPARER>(key, idx))
            {
               item = (*this)[idx];
               return true;
            }
            return false;
         }

         /// <summary>
         /// Complexity: O(log(n))
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool findSorted(const KEY& key, T& item)
         {
            size_t idx;
            if (findIdxSorted<KEY, COMPARER>(key, idx))
            {
               item = (*this)[idx];
               return true;
            }
            return false;
         }

         //////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Complexity: O(n+n)
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool removeOneUnsorted(const KEY& key, T& item)
         { 
            size_t idx;

            if (findIdxUnsorted<KEY, COMPARER>(key, idx))
               return removeAt(item, idx);

            return false;
         }
         
         /// <summary>
         /// Complexity: O(log(n)+n)
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool removeOneSorted(const KEY& key, T& item)
         {
            size_t idx;

            // found, remove it
            if (findIdxSorted<KEY, COMPARER>(key, idx))
               return removeAt(item, idx);

            // not found
            return false;
         }

         /// <summary>
         /// Complexity: O(n+k*n) , k=found matches
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE size_t removeAll(const KEY& key)
         {
            // remove counter
            size_t removed = 0;

            // backwards for removal!
            const size_t beg = mLength - 1;
            const size_t end = numeric_limits<size_t>::max();

            for (size_t i = beg; i != end; i--)
            {
               // no match
               if (COMPARER::nequal((*this)[i], key))
                  continue;

               // found
               else
               {
                  T temp;
                  removeAt(temp, i);
                  removed++;
               }
            }

            return removed;
         }

         /// <summary>
         /// Complexity: O(log(n)+n)
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, T>, bool UNIQUE = false>
         INLINE bool insertSorted(const T& item)
         {
            size_t idx;

            // check if item exists/find slot for insert
            const bool exists = findIdxSorted<KEY, COMPARER>(item, idx);

            // don't allow duplicates
            if (UNIQUE)
            {
               if (!exists) return insertAt(item, idx);
               else         return false;
            }

            // allow duplicates
            else
               return insertAt(item, idx);
         }

         //////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Helper function. Don't use.
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE bool validateSorted()
         {
            const size_t LEN = mLength;
            if (LEN > 0)
            {
               for (size_t i = 0; i < LEN - 1; i++)
                  if (!COMPARER::lesseq((*this)[i], (*this)[i + 1]))
                     return false;
            }
            
            return true;
         }
      };

   #ifndef CPPCORE_NO_THREADING
      /// <summary>
      /// FIFO Queue for Multi Thread Access with internal Locking
      /// </summary>
      /// <remarks>
      /// The peek() and length() operation semantics are incompatible
      /// with multithreaded access because their return can be
      /// already invalid/changed the moment it has been returned.
      /// </remarks>
      template<typename T, size_t SIZE>
      class MT : ST<T, SIZE>
      {
      protected:
         CPPCORE_MUTEX_TYPE mLock;
      public:
         INLINE MT() : ST<T, SIZE>() { CPPCORE_MUTEX_INIT(mLock); }
         INLINE ~MT() { CPPCORE_MUTEX_DELETE(mLock); }
         INLINE size_t size() const { return SIZE; }
         INLINE bool pushBack(const T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE>::pushBack(item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         INLINE bool pushFront(const T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE>::pushFront(item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         INLINE bool popBack(T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE>::popBack(item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         INLINE bool popFront(T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE>::popFront(item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         INLINE void clear()
         {
            CPPCORE_MUTEX_LOCK(mLock);
            ST<T, SIZE>::clear();
            CPPCORE_MUTEX_UNLOCK(mLock);
         }
         /// <summary>
         /// BEWARE: You must consider the returned value already outdated/invalid.
         /// This is for e.g. monitoring usage only.
         /// </summary>
         INLINE size_t length()
         {
            CPPCORE_MUTEX_LOCK(mLock);
            size_t ret = ST<T, SIZE>::length();
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }

         // TODO: Several function wrapping missing, e.g. sort/find/insertSorted..

         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool removeOneSorted(const KEY& key, T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE>::template removeOneSorted<KEY, COMPARER>(key, item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool removeOneUnsorted(const KEY& key, T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE>::template removeOneUnsorted<KEY, COMPARER>(key, item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE size_t removeAll(const KEY& key)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            size_t ret = ST<T, SIZE>::template removeAll<KEY, COMPARER>(key);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
      };
   #endif
   };
}
