#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Util/Comparer.h>
#include <CppCore/Containers/Util/Hasher.h>
#include <CppCore/Containers/Pool.h>

namespace CppCore
{
   /// <summary>
   /// Fixed Size HashTable.
   /// Use nested classes ST and MT.
   /// </summary>
   class HashTable
   {
   public:
      /// <summary>
      /// Entry used in HashTable
      /// </summary>
      template<typename T>
      struct Entry
      {
      public:
         T         Data;
         Entry<T>* Next;
      };

      /// <summary>
      /// HashTable for Single Threaded Access
      /// </summary>
      template<typename T, size_t SIZE, size_t MAXENTRIES, typename KEY=T, typename HASHER=Hasher::Murmur3::Generic<KEY>, typename COMPARER=Comparer<T, KEY>>
      class ST
      {
         typedef Pool::Fix::ST<Entry<T>, MAXENTRIES> EntryPool;

      protected:
         EntryPool mPool;
         Entry<T>* mTable[SIZE];
         size_t    mLength;

         /// <summary>
         /// C++ Iterator
         /// </summary>
         class Iterator
         {
         protected:
            size_t    mIdx;
            Entry<T>* mEntry;
            ST&       mHT;
         public:
            INLINE Iterator(size_t idx, ST& ht) : mIdx(idx), mHT(ht)
            {
               // find first used slot
               while (idx < SIZE && !mHT.mTable[idx])
                  idx++;

               // found
               if (idx < SIZE)
               {
                  mIdx = idx;
                  mEntry = mHT.mTable[idx];
               }

               // end
               else
               {
                  mIdx = 0;
                  mEntry = 0;
               }
            }
            INLINE Iterator& operator++()
            {
               // go to next collision
               if (mEntry->Next)
                  mEntry = mEntry->Next;

               // go to next used slot
               else
               {
                  mIdx++;

                  // find next used slot
                  while (mIdx < SIZE && !mHT.mTable[mIdx])
                     mIdx++;

                  // found
                  if (mIdx < SIZE)
                     mEntry = mHT.mTable[mIdx];

                  // end
                  else
                  {
                     mIdx = 0;
                     mEntry = 0;
                  }
               }
               return *this;
            }
            INLINE T& operator*() { return mEntry->Data; }
            INLINE bool operator!=(const Iterator& end) const { return mEntry != 0; }
         };

      public:
         /// <summary>
         /// Constructor
         /// </summary>
         INLINE ST()
         {
            mLength = 0;
            memset(mTable, 0, sizeof(mTable));
         }

         INLINE Iterator begin() { return Iterator(0, *this); }
         INLINE Iterator end() { return Iterator(mLength - 1, *this); }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE size_t size() const { return SIZE; }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE size_t length() const { return mLength; }

         /// <summary>
         /// Includes memory zeroing
         /// </summary>
         INLINE void clear()
         {
            // push used entries back to pool
            for (size_t i = 0; i < SIZE; i++)
            {
               Entry<T>* entry = mTable[i];
               while (entry)
               {
                  mPool.pushBack(entry);
                  entry = entry->Next;
               }
            }

            mLength = 0;
            memset(mTable, 0, sizeof(mTable));
         }

         /// <summary>
         /// Gets a free entry from the hash table entry pool.
         /// You MUST insert the entry afterwards by calling insert(),
         /// or push it back by calling pushFreeEntry().
         /// Useful to fill hashtable entries if T is not a pointer type.
         /// </summary>
         INLINE Entry<T>* popFreeEntry()
         {
            Entry<T>* entry;
            return mPool.popBack(entry) ? entry : nullptr;
         }

         /// <summary>
         /// Pushes a free entry back to the hash table entry pool.
         /// Only call this for unused entries retrieved via popFreeEntry()
         /// </summary>
         INLINE bool pushFreeEntry(Entry<T>* entry)
         {
            return mPool.pushBack(entry);
         }

         /// <summary>
         /// Complexity: O(1) - O(n)
         /// </summary>
         INLINE T* find(const KEY& key)
         {
            // first seed, then hash, then index
            uint32_t idx = 0;

            // calc hash from key and seed
            if (!HASHER::hash(key, idx))
               return nullptr;

            // get index from hash
            idx %= SIZE;

            // entry at idx
            Entry<T>* entry = mTable[idx];

            // lookup
            while (entry)
            {
               if (COMPARER::equal(entry->Data, key))
               {
                  // found
                  return &entry->Data;
               }
               else
                  entry = entry->Next;
            }

            // not found
            return nullptr;
         }

         /// <summary>
         /// Complexity: O(1) - O(n)
         /// </summary>
         INLINE bool find(const KEY& key, T& item)
         {
            if (T* r = find(key))
            {
               item = *r;
               return true;
            }
            else
               return false;
         }

         /// <summary>
         /// Use this variant only with entries retrieved from getFreeEntry()
         /// Complexity: O(1) - O(n)
         /// </summary>
         INLINE bool insert(const KEY& key, Entry<T>* entry)
         {
            // first seed, then hash, then index
            uint32_t idx = 0;

            // calc hash from key and seed
            if (!HASHER::hash(key, idx))
               return false;

            // get index from hash
            idx %= SIZE;

            // slot is empty
            if (!mTable[idx])
            {
               entry->Next = 0;
               mTable[idx] = entry;
            }

            // collision
            else
            {
               entry->Next = mTable[idx];
               mTable[idx] = entry;
            }

            // success
            mLength++;
            return true;
         }

         /// <summary>
         /// Complexity: O(1) - O(n)
         /// </summary>
         INLINE bool insert(const KEY& key, const T& item)
         {
            Entry<T>* entry;

            // must have empty slot
            if (!mPool.popBack(entry))
               return false;

            // set data on entry
            entry->Data = item;

            // insert
            return insert(key, entry);
         }

         /// <summary>
         /// Tries to remove an entry from the HashTable.
         /// You must call pushFreeEntry() with the return if it is not null
         /// and once you're done with further operations on it.
         /// </summary>
         INLINE Entry<T>* remove(const KEY& key)
         {
            // first seed, then hash, then index
            uint32_t idx = 0;

            // calc hash from key and seed
            if (!HASHER::hash(key, idx))
               return nullptr;

            // get index from hash
            idx %= SIZE;

            // entry at idx
            Entry<T>* entry = mTable[idx];
            Entry<T>* prev = 0;

            // lookup
            while (entry)
            {
               // found
               if (COMPARER::equal(entry->Data, key))
               {
                  // remove
                  if (prev) prev->Next = entry->Next;
                  else      mTable[idx] = entry->Next;

                  // success
                  mLength--;
                  return entry;
               }
               // test next
               else
               {
                  prev = entry;
                  entry = entry->Next;
               }
            }

            // not found
            return nullptr;
         }

         /// <summary>
         /// Tries to remove an item from the HashTable and
         /// pushes it back to the free ones directly.
         /// </summary>
         INLINE bool removeAndPushFree(const KEY& key)
         {
            if (Entry<T>* o = remove(key))
            {
               mPool.pushBack(o);
               return true;
            }
            else
               return false;
         }

         /// <summary>
         /// Dynamically determines the amount of collisions and
         /// the highest collisions found for a single bucket.
         /// Complexity: O(SIZE)
         /// </summary>
         INLINE void collisions(size_t& collisions, size_t& worst)
         {
            collisions = 0;
            worst = 0;

            for (size_t i = 0; i < SIZE; i++)
            {
               if (Entry<T>* entry = mTable[i])
               {
                  size_t tmp = 0;
                  while (entry->Next)
                  {
                     tmp++;
                     
                     if (tmp > worst)
                        worst = tmp;

                     entry = entry->Next;
                  }
                  collisions += tmp;
               }
            }
         }
      };

      /// <summary>
      /// HashTable for Multi Threaded Access
      /// </summary>
      template<typename T, size_t SIZE, size_t MAXENTRIES, typename KEY = T, typename HASHER = Hasher::Murmur3::Generic<KEY>, typename COMPARER = Comparer<T, KEY>>
      class MT : ST<T, SIZE, MAXENTRIES, KEY, HASHER, COMPARER>
      {
      protected:
         CPPCORE_MUTEX_TYPE mLock;
      public:
         INLINE MT() : ST<T, SIZE, MAXENTRIES, KEY, HASHER, COMPARER>() { CPPCORE_MUTEX_INIT(mLock); }
         INLINE ~MT() { CPPCORE_MUTEX_DELETE(mLock); }
         INLINE size_t size() const { return SIZE; }
         INLINE void clear()
         {
            CPPCORE_MUTEX_LOCK(mLock);
            ST<T, SIZE, MAXENTRIES, KEY, HASHER, COMPARER>::clear();
            CPPCORE_MUTEX_UNLOCK(mLock);
         }
         INLINE bool find(const KEY& key, T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE, MAXENTRIES, KEY, HASHER, COMPARER>::find(key, item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         INLINE bool insert(const KEY& key, const T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE, MAXENTRIES, KEY, HASHER, COMPARER>::insert(key, item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         INLINE bool remove(const KEY& key, T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE, MAXENTRIES, KEY, HASHER, COMPARER>::remove(key, item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
      };
   };
}
