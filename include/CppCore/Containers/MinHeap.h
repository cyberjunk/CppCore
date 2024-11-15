#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Util/Comparer.h>

namespace CppCore
{
   /// <summary>
   /// Fixed Size MinHeap.
   /// See nested classes ST and MT.
   /// </summary>
   class MinHeap
   {
   private:
      INLINE MinHeap() { }

   public:
      /// <summary>
      /// MinHeap for Single Thread Access
      /// </summary>
      template <typename T, size_t SIZE, typename KEY=T>
      class ST
      {
      protected:
         T      mHeap[SIZE];
         size_t mLength;

         INLINE static size_t left(const size_t i) { return (2 * i + 1); }
         INLINE static size_t right(const size_t i) { return (2 * i + 2); }
         INLINE static size_t parent(const size_t i) { return ((i - 1) / 2); }

      public:
         /// <summary>
         /// Complexity: (1)
         /// Root is stored at index 0, then breadth-first.
         /// </summary>
         INLINE T& operator[](size_t index) { return mHeap[index]; }

      protected:
         /// <summary>
         /// C++ Iterator (BACKWARDS)
         /// </summary>
         class Iterator
         {
         protected:
            size_t mIdx;
            ST&    mHeap;
         public:
            INLINE Iterator(size_t idx, ST& heap) : mIdx(idx), mHeap(heap) { }
            INLINE T&        operator*()  { return mHeap[mIdx]; }
            INLINE Iterator& operator++() { mIdx--; return *this; }
            INLINE bool      operator!=(const Iterator& end) const { return mIdx != numeric_limits<size_t>::max(); }
         };

         /// <summary>
         /// Helper Function
         /// </summary>
         INLINE void swap(const size_t idx1, const size_t idx2)
         {
            T temp = mHeap[idx1];
            mHeap[idx1] = mHeap[idx2];
            mHeap[idx2] = temp;
         }

      public:
         /// <summary>
         /// Constructor
         /// </summary>
         INLINE ST() : mLength(0) { }

         INLINE Iterator begin() { return Iterator(mLength - 1, *this); }
         INLINE Iterator end()   { return Iterator(0, *this);           }

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
         INLINE void clear()
         {
            mLength = 0;
         }

         //////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Moves heap entry with changed key upwards until in right spot again.
         /// No bound check on idx.
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE void fixOrderAtUp(size_t idx)
         {
            // move node up until in place
            while (idx > 0)
            {
               // idx of parent
               const size_t p = parent(idx);

               // move up as long as smaller
               if (COMPARER::less(mHeap[idx], mHeap[p]))
               {
                  swap(idx, p); // swap them
                  idx = p;      // loop again with parent
               }
               else
                  return;
            }
         }

         /// <summary>
         /// Moves heap entry with changed key downwards until in right spot again.
         /// No bound check on idx.
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE void fixOrderAtDown(size_t idx, const size_t len)
         {
            // move node down until in place
            while (true)
            {
               // left and right child
               const size_t lc = left(idx);
               const size_t rc = right(idx);

               // min of this and both children
               size_t min = idx;

               // left is smaller
               if (lc < len && COMPARER::less(mHeap[lc], mHeap[min]))
                  min = lc;

               // right is (even) smaller
               if (rc < len && COMPARER::less(mHeap[rc], mHeap[min]))
                  min = rc;

               // left or right was smaller
               if (min != idx)
               {
                  swap(idx, min);
                  idx = min;
               }
               else
                  return;
            }
         }

         /// <summary>
         /// Moves heap entry with changed key until in right spot again.
         /// No bound check on idx.
         /// If you know the direction, call the subfunc directly!
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE void fixOrderAt(size_t idx)
         {
            fixOrderAtUp<COMPARER>(idx);            // move up if necessary
            fixOrderAtDown<COMPARER>(idx, mLength); // move down if necessary
         }

         //////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Complexity: O(log(n))
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE bool removeAt(T& item, size_t idx)
         {
            size_t len = mLength;
            if (idx < len)
            {
               len--;                              // decrement length
               mLength = len;                      // write back new length
               item = mHeap[idx];                  // set node at idx as return value
               mHeap[idx] = mHeap[len];            // put last at removed position
               fixOrderAtDown<COMPARER>(idx, len); // move down until in place again
               return true;
            }
            return false;
         }

         //////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Complexity: O(log(n))
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE bool push(const T& item)
         {
            size_t idx = mLength;
            if (idx < SIZE)
            {
               mHeap[idx] = item;           // add item at the end
               mLength = idx + 1;           // write back incremented length
               fixOrderAtUp<COMPARER>(idx); // move node up until in place
               return true;
            }
            return false;
         }

         /// <summary>
         /// Complexity: O(log(n))
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE bool pop(T& item)
         {
            return removeAt<COMPARER>(item, 0);
         }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE bool peek(T& item)
         {
            if (mLength > 0)
            {
               item = mHeap[0];
               return true;
            }
            return false;
         }

         //////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Complexity: O(n)
         /// </summary>
         template<typename COMPARER = Comparer<T, KEY>>
         INLINE bool find(const KEY& key, size_t& idx)
         {
            const size_t LEN = mLength;

            for (idx = 0; idx < LEN; idx++)
               if (COMPARER::equal(mHeap[idx], key))
                  return true;

            return false;
         }

         //////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Complexity: O(n+log(n))
         /// </summary>
         template<typename CMPKEY = Comparer<T, KEY>, typename CMPOBJ  = Comparer<T, T>>
         INLINE bool removeOne(const KEY& key, T& item)
         {
            size_t idx = 0;

            if (find<CMPKEY>(key, idx))
               return removeAt<CMPOBJ>(item, idx);

            return false;
         }

         /// <summary>
         /// Complexity: O(k*(n+log(n))) , k=found matches
         /// </summary>
         template<typename CMPKEY = Comparer<T, KEY>, typename CMPOBJ = Comparer<T, T>>
         INLINE size_t removeAll(const KEY& key)
         {
            T temp;
            size_t idx = 0;
            size_t counter = 0;

            // find all occurences
            while (find<CMPKEY>(key, idx))
            {
               // remove it
               if (removeAt<CMPOBJ>(temp, idx))
                  counter++;

               // must search from root again
               idx = 0;
            }

            return counter;
         }

         /// <summary>
         /// For debugging purposes only.
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE bool validate(size_t* stack, size_t idx = 0)
         {
            const size_t LEN = mLength;
            if (idx < LEN)
            {
               size_t stidx = 0;   // index on stack
               stack[++stidx] = idx; // push first index

               do
               {
                  // pop next index/node
                  idx = stack[stidx--];

                  // get indices of children
                  const size_t lc = left(idx);
                  const size_t rc = right(idx);

                  // test left child
                  if (lc < LEN)
                  {
                     // left child must not be smaller
                     if (COMPARER::less(mHeap[lc], mHeap[idx]))
                        return false;

                     // if ok add to ones to evaluate next
                     else
                        stack[++stidx] = lc;
                  }

                  // test right child
                  if (rc < LEN)
                  {
                     // right child must not be smaller
                     if (COMPARER::less(mHeap[rc], mHeap[idx]))
                        return false;

                     // if ok add to ones to evaluate next
                     else
                        stack[++stidx] = rc;
                  }

               } while (stidx);

               // all good
               return true;
            }

            // index out ouf bound
            else
               return false;
         }
      };

   #ifndef CPPCORE_NO_THREADING
      /// <summary>
      /// MinHeap for Multi Thread Access with internal Locking
      /// </summary>
      template <typename T, size_t SIZE, typename KEY=T>
      class MT : ST<T, SIZE, KEY>
      {
      protected:
         CPPCORE_MUTEX_TYPE mLock;
      public:
         INLINE MT() : ST<T, SIZE, KEY>() { }
         INLINE size_t size() { return SIZE; }
         template<typename COMPARER = Comparer<T, T>>
         INLINE bool push(const T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE, KEY>::template push<COMPARER>(item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         template<typename COMPARER = Comparer<T, T>>
         INLINE bool pop(T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE, KEY>::template pop<COMPARER>(item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         INLINE void clear()
         {
            CPPCORE_MUTEX_LOCK(mLock);
            ST<T, SIZE, KEY>::clear();
            CPPCORE_MUTEX_UNLOCK(mLock);
         }
         /// <summary>
         /// BEWARE: You must consider the returned value already outdated/invalid.
         /// This is for e.g. monitoring usage only.
         /// </summary>
         INLINE size_t length()
         {
            CPPCORE_MUTEX_LOCK(mLock);
            size_t ret = ST<T, SIZE, KEY>::length();
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
      };
   #endif
   };
}
