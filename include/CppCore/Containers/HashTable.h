#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Util/Comparer.h>
#include <CppCore/Containers/Pool.h>
#include <CppCore/Hash/Murmur3.h>

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
      template<
         typename T, 
         typename KEY,
         size_t   POOLSIZE,
         typename COMPARER,
         size_t   TABLESIZE = (size_t)ngptwo64(POOLSIZE * 2),
         typename HASHER    = Murmur3>
      class ST
      {
      private:
         static_assert(POOLSIZE <= TABLESIZE);
         static_assert(popcnt64_generic(TABLESIZE) == 1U);

      public:
         using EntryPool = Pool::Fix::ST<Entry<T>, POOLSIZE>;

      protected:
         CPPCORE_ALIGN16 Entry<T>* mTable[TABLESIZE];
         CPPCORE_ALIGN16 size_t    mLength;
         CPPCORE_ALIGN16 HASHER    mHasher;
         CPPCORE_ALIGN16 EntryPool mPool;

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
               while (idx < TABLESIZE && !mHT.mTable[idx])
                  idx++;

               // found
               if (idx < TABLESIZE)
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
                  while (mIdx < TABLESIZE && !mHT.mTable[mIdx])
                     mIdx++;

                  // found
                  if (mIdx < TABLESIZE)
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
         INLINE ST() : mLength(0), mHasher(), mPool()
         {
            CppCore::clear(mTable);
         }

         /// <summary>
         /// Iterator begin()
         /// </summary>
         INLINE Iterator begin() { return Iterator(0, *this); }

         /// <summary>
         /// Iterator end()
         /// </summary>
         INLINE Iterator end() { return Iterator(mLength - 1, *this); }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE size_t size() const { return TABLESIZE; }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE size_t length() const { return mLength; }

         /// <summary>
         /// Clears the hashtable and 
         /// pushes back all used entries to the pool.
         /// </summary>
         INLINE void clear()
         {
            // push used entries back to pool
            for (size_t i = 0; i < TABLESIZE; i++)
            {
               Entry<T>* entry = mTable[i];
               while (entry)
               {
                  mPool.pushBack(entry);
                  entry = entry->Next;
               }
            }

            CppCore::clear(mTable);
            mLength = 0;
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
            // hashed key
            typename HASHER::Digest hash;

            // calc hash from key
            mHasher.hash(key, hash);

            // get index from hash
            const uint32_t idx = 
               hash % TABLESIZE;

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
            // hashed key
            typename HASHER::Digest hash;

            // calc hash from key
            mHasher.hash(key, hash);

            // get index from hash
            const uint32_t idx = 
               hash % TABLESIZE;

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
         /// Uses assignment operator to copy item to entry data.
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
            // hashed key
            typename HASHER::Digest hash;

            // calc hash from key
            mHasher.hash(key, hash);

            // get index from hash
            const uint32_t idx = 
               hash % TABLESIZE;

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

            for (size_t i = 0; i < TABLESIZE; i++)
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
      template<
         typename T, 
         typename KEY,
         size_t   POOLSIZE,
         typename COMPARER,
         size_t   TABLESIZE = (size_t)ngptwo64(POOLSIZE * 2),
         typename HASHER    = Murmur3>
      class MT : ST<T, KEY, POOLSIZE, COMPARER, TABLESIZE, HASHER>
      {
      public:
         using Base = ST<T, KEY, POOLSIZE, COMPARER, TABLESIZE, HASHER>;
      protected:
         CPPCORE_MUTEX_TYPE mLock;
      public:
         INLINE MT() : Base() { CPPCORE_MUTEX_INIT(mLock); }
         INLINE ~MT() { CPPCORE_MUTEX_DELETE(mLock); }
         INLINE size_t size() const { return TABLESIZE; }
         INLINE void clear()
         {
            CPPCORE_MUTEX_LOCK(mLock);
            Base::clear();
            CPPCORE_MUTEX_UNLOCK(mLock);
         }
         INLINE bool find(const KEY& key, T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = Base::find(key, item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         INLINE bool insert(const KEY& key, const T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = Base::insert(key, item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         INLINE bool remove(const KEY& key, T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = Base::remove(key, item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
      };
   };
}
