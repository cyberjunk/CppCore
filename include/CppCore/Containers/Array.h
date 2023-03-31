#pragma once

#include <CppCore/Root.h>
#include <CppCore/Memory.h>
#include <CppCore/Iterator.h>
#include <CppCore/Containers/Util/QuickSort.h>
#include <CppCore/Containers/Util/BinarySearch.h>

namespace CppCore
{
   /// <summary>
   /// Array Classes
   /// </summary>
   class Array
   {
   private:
      INLINE Array();
   public:
      /// <summary>
      /// Array Base Class (for fixed and dynamic size)
      /// </summary>
      template<typename T, typename TARRAY>
      class Base
      {
      protected:
         size_t  mLength;

         /// <summary>
         /// Helper for casting this from template to final instance type.
         /// </summary>
         INLINE TARRAY& thiss() { return *((TARRAY*)this); }


      public:
         /// <summary>
         /// Constructor
         /// </summary>
         INLINE Base() : mLength(0) { }

         /////////////////////////////////////////////////////////////////////////////////////////////////////////////

         using ItCF = CppCore::ItC<T, false>; // Constant Iterator Class Forward
         using ItCR = CppCore::ItC<T, true>;  // Constant Iterator Class Reverse
         using ItDF = CppCore::ItD<T, false>; // Non-Constant Iterator Class Forward
         using ItDR = CppCore::ItD<T, true>;  // Non-Constant Iterator Class Reverse

         // todo: forward is reverse and reverse is forward for backwards compatibility

         INLINE ItDF rbegin()        { return ItDF(thiss().mData); }
         INLINE ItCF rbegin()  const { return ItCF(thiss().mData); }
         INLINE ItDF rend()          { return ItDF(&thiss().mData[mLength]); }
         INLINE ItCF rend()    const { return ItCF(&thiss().mData[mLength]); }
         INLINE ItDR begin()         { return ItDR((&thiss().mData[mLength])-1U); }
         INLINE ItCR begin()   const { return ItCR((&thiss().mData[mLength])-1U); }
         INLINE ItDR end()           { return ItDR(thiss().mData-1U); }
         INLINE ItCR end()     const { return ItCR(thiss().mData-1U); }

         /////////////////////////////////////////////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE T& operator[](size_t index) { return thiss().mData[index]; }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE size_t length() const { return mLength; }

         /// <summary>
         /// Complexity: O(1)
         /// Use with caution! Directly sets length to any provided value.
         /// Calling is not required for normal operations like push or pop.
         /// Mostly used after directly filling objects at indices in non-pointer use cases.
         /// </summary>
         INLINE void setLength(const size_t length) { mLength = length; }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE void clear()
         {
            mLength = 0;
         }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE void swap(const size_t idx1, const size_t idx2)
         {
            T tmp = thiss().mData[idx1];
            thiss().mData[idx1] = thiss().mData[idx2];
            thiss().mData[idx2] = tmp;
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
               item = thiss().mData[idx];

               // swap the item to remove to the last item
               for (; idx < LEN - 1; idx++)
                  swap(idx, idx + 1);

               // decrease length
               mLength = LEN - 1;

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
            if (idx <= LEN && LEN < thiss().size())
            {
               // swap the first unused slot to idx slot
               for (size_t k = LEN; k > idx; k--)
                  swap(k, k - 1);

               // save new item at idx
               thiss().mData[idx] = item;

               // save incremented size
               mLength = LEN + 1;

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
            size_t len = mLength;
            if (len < thiss().size())
            {
               thiss().mData[len] = item;
               mLength = len + 1;
               return true;
            }
            else
               return false;
         }

         /// <summary>
         /// Complexity: O(n)
         /// </summary>
         INLINE bool pushFront(const T& item)
         {
            return insertAt(item, 0);
         }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE bool popBack(T& item)
         {
            size_t len = mLength;
            if (len > 0)
            {
               len--;
               item = thiss().mData[len];
               mLength = len;
               return true;
            }
            else
               return false;
         }

         /// <summary>
         /// Complexity: O(n)
         /// </summary>
         INLINE bool popFront(T& item)
         {
            return removeAt(item, 0);
         }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE bool peekBack(T& item)
         {
            const size_t len = mLength;
            if (len > 0)
            {
               item = thiss().mData[len - 1];
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
               item = thiss().mData[0];
               return true;
            }
            else
               return false;
         }

         //////////////////////////////////////////////////////////////////////
         // FRONT/BACK OPTIMIZED BULK OPS

         /// <summary>
         /// Pushes n elements to the end of the array.
         /// Returns number of elements pushed.
         /// </summary>
         template<bool FLATCOPY = ::std::is_trivially_constructible<T>::value>
         INLINE size_t pushBack(const T* items, size_t n)
         {
            size_t len = mLength;
            size_t siz = thiss().size();
            n = MIN(n, siz-len);
            if constexpr (FLATCOPY)
            {
               Memory::copy(&thiss().mData[len], items, n*sizeof(T));
               mLength = len + n;
            }
            else
            {
               for (size_t i = 0U; i < n; i++)
                  thiss().mData[len++] = items[i];
               mLength = len;
            }
            return n;
         }

         /// <summary>
         /// Pops n elements from the end of the array.
         /// Returns number of elements popped.
         /// </summary>
         template<bool FLATCOPY = ::std::is_trivially_constructible<T>::value>
         INLINE size_t popBack(T* items, size_t n)
         {
            size_t len = mLength;
            n = MIN(n, len);
            if constexpr (FLATCOPY)
            {
               len -= n;
               Memory::copy(items, &thiss().mData[len], n*sizeof(T));
               mLength = len;
            }
            else
            {
               len -= n;
               mLength = len;
               for (size_t i = 0U; i < n; i++)
                  items[i] = thiss().mData[len++];
            }
            return n;
         }

         //////////////////////////////////////////////////////////////////////
         // FIX ORDER OPS

         /// <summary>
         /// Moves array entry with changed key in sorted array
         /// to the left until in right spot again. No bound check on idx.
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE void fixOrderAtLeft(size_t idx)
         {
            while (idx > 0)
            {
               const size_t left = idx - 1;
               if (COMPARER::less(thiss().mData[idx], thiss().mData[left]))
               {
                  swap(idx, left);
                  idx = left;
               }
               else 
                  return;
            }
         }

         /// <summary>
         /// Moves array entry with changed key in sorted array
         /// to the right until in right spot again. No bound check on idx.
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE void fixOrderAtRight(size_t idx, const size_t len)
         {
            while (idx < len - 1)
            {
               const size_t right = idx + 1;
               if (COMPARER::less(thiss().mData[right], thiss().mData[idx]))
               {
                  swap(idx, right);
                  idx = right;
               }
               else
                  return;
            }
         }

         /// <summary>
         /// Moves array entry with changed key in sorted array
         /// until in right spot again. No bound check on idx.
         /// Use one of the subfunc if you know the direction!
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE void fixOrderAt(size_t idx)
         {
            fixOrderAtLeft<COMPARER>(idx);
            fixOrderAtRight<COMPARER>(idx, mLength);
         }

         //////////////////////////////////////////////////////////////////////
         // SORT

         /// <summary>
         /// Complexity: O(n*log(n))
         /// </summary>
         template<typename COMPARER = Comparer<T, T>, size_t MEMSIZE>
         INLINE bool sort(size_t stack[MEMSIZE])
         {
            return QuickSort::sort<TARRAY, T, COMPARER, MEMSIZE>((thiss()), stack);
         }

         //////////////////////////////////////////////////////////////////////
         // KEY OPS

         /// <summary>
         /// Complexity: O(n)
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool findIdxUnsorted(const KEY& key, size_t& idx)
         {
            const size_t LEN = length();
            for (idx = 0; idx < LEN; idx++)
            {
               if (COMPARER::nequal(thiss().mData[idx], key))
                  continue;

               else
                  return true;
            }
            return false;
         }

         /// <summary>
         /// Complexity: O(log(n))
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool findIdxSorted(const KEY& key, size_t& idx)
         {
            return BinarySearch<TARRAY, T, KEY, COMPARER>::search((thiss()), key, idx);
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
               item = thiss().mData[idx];
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
               item = thiss().mData[idx];
               return true;
            }
            return false;
         }

         //////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Complexity: O(n+n)
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool removeOneUnsorted(const KEY& key, T& item, size_t& idx)
         {
            if (findIdxUnsorted<KEY, COMPARER>(key, idx))
               return removeAt(item, idx);

            return false;
         }

         /// <summary>
         /// Complexity: O(log(n)+n)
         /// </summary>
         template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
         INLINE bool removeOneSorted(const KEY& key, T& item, size_t& idx)
         {
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
               if (COMPARER::nequal(thiss().mData[i], key))
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
         INLINE bool insertSorted(const T& item, size_t& idx)
         {
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
                  if (!COMPARER::lesseq(thiss().mData[i], thiss().mData[i + 1]))
                     return false;
            }
            
            return true;
         }
      };
      
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Dynamic Sized Arrays
      /// </summary>
      class Dyn
      {
      private:
         INLINE Dyn();
      public:
         /// <summary>
         /// Dynamic Size Array for Single Thread Access
         /// </summary>
         template<typename T, bool CONSTRUCT = !::std::is_trivially_constructible<T>::value>
         class ST : public Array::Base<T, ST<T, CONSTRUCT>>
         {
            friend Array::Base<T, ST<T, CONSTRUCT>>;

         public:
            /// <summary>
            /// Alignment used for Memory on the Heap.
            /// </summary>
            static constexpr size_t ALIGNMENT = 64;

         protected:
            size_t mSize;
            T*     mData;

         public:
            /// <summary>
            /// Constructor
            /// </summary>
            INLINE ST(const size_t size = 0) : Array::Base<T, ST<T, CONSTRUCT>>(),
               mSize(size),
               mData(Memory::alignedalloc<T>(size, ALIGNMENT))
            {
               if (CONSTRUCT)
                  for (size_t i = 0; i < mSize; i++)
                     new (&mData[i]) T();
            }

            /// <summary>
            /// Destructor
            /// </summary>
            INLINE ~ST()
            {
               if (CONSTRUCT)
                  for (size_t i = 0; i < mSize; i++)
                     mData[i].~T();

               Memory::alignedfree(mData);
            }

            /// <summary>
            /// Complexity: O(1)
            /// </summary>
            INLINE size_t size() const { return mSize; }

            /// <summary>
            /// Resizes memory.
            /// </summary>
            INLINE void resize(const size_t newSize)
            {
               const size_t LEN  = this->mLength;
               const size_t SIZE = this->mSize;
               if (newSize != SIZE)
               {
                  // allocate new memory with new size
                  T* newData = Memory::alignedalloc<T>(newSize, ALIGNMENT);

                  // grow
                  if (newSize > SIZE)
                  {
                     Memory::streamcopy128x4(newData, mData, sizeof(T) * SIZE);
                     if (CONSTRUCT)
                        for (size_t i = SIZE; i < newSize; i++)
                           new (&newData[i]) T();
                  }
                  // shrink
                  else
                  {
                     Memory::streamcopy128x4(newData, mData, sizeof(T) * newSize);
                     if (CONSTRUCT)
                        for (size_t i = newSize; i < SIZE; i++)
                           mData[i].~T();
                  }

                  // set length to new size if we shrinked below
                  if (newSize < LEN)
                     this->mLength = newSize;

                  Memory::alignedfree(mData); // free old mem
                  mData = newData;            // update data
                  mSize = newSize;            // update size
               }
            }

            /// <summary>
            /// Returns memory consumption of dynamic heap allocation
            /// </summary>
            INLINE size_t memOnHeap()
            {
               return mSize * sizeof(T);
            }
         };
      };

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

       /// <summary>
      /// Fixed Sized Arrays
      /// </summary>
      class Fix
      {
      private:
         INLINE Fix();
      public:
         /// <summary>
         /// Fixed Size Array for Single Thread Access
         /// </summary>
         template<class T, size_t SIZE>
         class ST : public Array::Base<T, ST<T, SIZE>>
         {
            friend Array::Base<T, ST<T, SIZE>>;

         protected:
            T mData[SIZE];

         public:
            /// <summary>
            /// Constructor
            /// </summary>
            INLINE ST() : Array::Base<T, ST<T, SIZE>>() { }

            /// <summary>
            /// Complexity: O(1)
            /// </summary>
            INLINE size_t size() { return SIZE; }
         };

         /// <summary>
         /// Fixed Size Array for Multi Thread Access
         /// </summary>
         template<typename T, size_t SIZE>
         class MT : ST<T, SIZE>
         {
            friend Array::Base<T, ST<T, SIZE>>;

         protected:
            CPPCORE_MUTEX_TYPE mLock;
         public:
            INLINE MT() : ST<T, SIZE>() { CPPCORE_MUTEX_INIT(mLock); }
            INLINE ~MT() { CPPCORE_MUTEX_DELETE(mLock); }
            INLINE size_t size() { return SIZE; }
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
            INLINE bool removeOneSorted(const KEY& key, T& item, size_t& idx)
            {
               CPPCORE_MUTEX_LOCK(mLock);
               bool ret = ST<T, SIZE>::template removeOneSorted<KEY, COMPARER>(key, item, idx);
               CPPCORE_MUTEX_UNLOCK(mLock);
               return ret;
            }
            template<typename KEY = T, typename COMPARER = Comparer<T, KEY>>
            INLINE bool removeOneUnsorted(const KEY& key, T& item, size_t& idx)
            {
               CPPCORE_MUTEX_LOCK(mLock);
               bool ret = ST<T, SIZE>::template removeOneUnsorted<KEY, COMPARER>(key, item, idx);
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
      };
   };
}
