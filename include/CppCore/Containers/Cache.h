#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/HashTable.h>

namespace CppCore
{
   /// <summary>
   /// Fixed Size Cache.
   /// Use nested classes ST and MT.
   /// </summary>
   class Cache
   {
   public:
      /// <summary>
      /// Entry used in Cache
      /// </summary>
      template<typename T>
      struct Entry
      {
      public:
         T            Data;
         uint32_t     Refs;
         StdTimePoint Tick;
         size_t       Size;

         /// <summary>
         /// Entry Comparers
         /// </summary>
         template<typename U>
         class Comparer
         {
         private:
            INLINE Comparer() { }
         public:
            INLINE static bool equal    (const Entry<T>& a, const U& b) { return a == b; }
            INLINE static bool nequal   (const Entry<T>& a, const U& b) { return a != b; }
            INLINE static bool less     (const Entry<T>& a, const U& b) { return a <  b; }
            INLINE static bool lesseq   (const Entry<T>& a, const U& b) { return a <= b; }
            INLINE static bool greater  (const Entry<T>& a, const U& b) { return a >  b; }
            INLINE static bool greatereq(const Entry<T>& a, const U& b) { return a >= b; }

            /// <summary>
            /// Comparers using getId()
            /// </summary>
            class Id
            {
            private:
               INLINE Id() { }
            public:
               class O2K
               {
               public:
                  INLINE static bool equal(Entry<T>& a, U key)     { return a.Data.getId() == key; }
                  INLINE static bool nequal(Entry<T>& a, U key)    { return a.Data.getId() != key; }
                  INLINE static bool less(Entry<T>& a, U key)      { return a.Data.getId() <  key; }
                  INLINE static bool lesseq(Entry<T>& a, U key)    { return a.Data.getId() <= key; }
                  INLINE static bool greater(Entry<T>& a, U key)   { return a.Data.getId() >  key; }
                  INLINE static bool greatereq(Entry<T>& a, U key) { return a.Data.getId() >= key; }
               };
               class OP2K
               {
               public:
                  INLINE static bool equal(Entry<T>* a, U key)     { return a->Data.getId() == key; }
                  INLINE static bool nequal(Entry<T>* a, U key)    { return a->Data.getId() != key; }
                  INLINE static bool less(Entry<T>* a, U key)      { return a->Data.getId() <  key; }
                  INLINE static bool lesseq(Entry<T>* a, U key)    { return a->Data.getId() <= key; }
                  INLINE static bool greater(Entry<T>* a, U key)   { return a->Data.getId() >  key; }
                  INLINE static bool greatereq(Entry<T>* a, U key) { return a->Data.getId() >= key; }
               };
               class O2O
               {
               public:
                  INLINE static bool equal(Entry<T>& a, Entry<T>& b)      { return a.Data.getId() == b.Data.getId(); }
                  INLINE static bool nequal(Entry<T>& a, Entry<T>& b)     { return a.Data.getId() != b.Data.getId(); }
                  INLINE static bool less(Entry<T>& a, Entry<T>& b)       { return a.Data.getId() <  b.Data.getId(); }
                  INLINE static bool lesseq(Entry<T>& a, Entry<T>& b)     { return a.Data.getId() <= b.Data.getId(); }
                  INLINE static bool greater(Entry<T>& a, Entry<T>& b)    { return a.Data.getId() >  b.Data.getId(); }
                  INLINE static bool greatereq(Entry<T>& a, Entry<T>& b)  { return a.Data.getId() >= b.Data.getId(); }
               };
               class OP2OP
               {
               public:
                  INLINE static bool equal(Entry<T>* a, Entry<T>* b)      { return a->Data.getId() == b->Data.getId(); }
                  INLINE static bool nequal(Entry<T>* a, Entry<T>* b)     { return a->Data.getId() != b->Data.getId(); }
                  INLINE static bool less(Entry<T>* a, Entry<T>* b)       { return a->Data.getId() <  b->Data.getId(); }
                  INLINE static bool lesseq(Entry<T>* a, Entry<T>* b)     { return a->Data.getId() <= b->Data.getId(); }
                  INLINE static bool greater(Entry<T>* a, Entry<T>* b)    { return a->Data.getId() >  b->Data.getId(); }
                  INLINE static bool greatereq(Entry<T>* a, Entry<T>* b)  { return a->Data.getId() >= b->Data.getId(); }
               };
            };
         };
      };

      /// <summary>
      ///
      /// </summary>
      template<typename T, size_t SIZE, size_t MAXENTRIES, size_t SIZEPRUNE, typename KEY = T, typename HASHER = Hasher::Murmur3::Generic<KEY>, typename COMPARER = Comparer<T, KEY>>
      class ST
      {
      public:
         typedef HashTable::ST<Entry<T>, SIZE, MAXENTRIES, KEY, HASHER, COMPARER> HT;
         typedef Array::Fix::ST<Entry<T>*, SIZEPRUNE>                             ArrayEntry;

      protected:
         HT           mHT;
         ArrayEntry   mPruneList;
         size_t     mMemoryUsage;
         size_t     mMemoryLimit;

      public:
         INLINE size_t        length()         const { return mHT.length(); }
         INLINE size_t        getMemoryUsage() const { return mMemoryUsage; }
         INLINE size_t        getMemoryLimit() const { return mMemoryLimit; }

         INLINE HT&           getHT()          { return mHT; }
         INLINE ArrayEntry&   getPruneList()   { return mPruneList; }

         INLINE void setMemoryLimit(size_t v) { mMemoryLimit = v; }

         /// <summary>
         /// Constructor
         /// </summary>
         INLINE ST() : mMemoryUsage(0), mMemoryLimit(0)
         {

         }

         ////////////////////////////////////////////////////////////////////////////////////////////////

         /// <summary>
         ///
         /// </summary>
         INLINE HashTable::Entry<Entry<T>>* popFreeEntry()
         {
            return mHT.popFreeEntry();
         }

         /// <summary>
         ///
         /// </summary>
         INLINE bool pushFreeEntry(HashTable::Entry<Entry<T>>* entry)
         {
            return mHT.pushFreeEntry(entry);
         }

         ////////////////////////////////////////////////////////////////////////////////////////////////

         /// <summary>
         ///
         /// </summary>
         INLINE Entry<T>* find(const KEY& key)
         {
            if (Entry<T>* o = mHT.find(key))
            {
               o->Tick = StdClock::now();
               o->Refs++;

               return o;
            }
            else
               return 0;
         }

         /// <summary>
         /// Tries to insert an entry into the cache. Invoke with entries received from popFreeEntry().
         /// Sets the active references to 1 and the tick to now.
         /// </summary>
         INLINE bool insert(const KEY& key, HashTable::Entry<Entry<T>>* entry, const size_t size = 0)
         {
            if (entry)
            {
               entry->Data.Tick = StdClock::now();
               entry->Data.Refs = 1;
               entry->Data.Size = size;

               if (mHT.insert(key, entry))
               {
                  mMemoryUsage += size;
                  return true;
               }
               else
                  return false;
            }
            else
               return false;
         }

         /// <summary>
         /// Tries to remove an entry from the cache. Returns false if
         /// the entry could not be found or still has active references.
         /// Preferrably call this with elements from the prune list, see prune().
         /// </summary>
         INLINE bool remove(const KEY& key)
         {
            // try remove it
            if (HashTable::Entry<Entry<T>>* o = mHT.remove(key))
            {
               // must have zero references to get removed
               if (o->Data.Refs == 0)
               {
                  mMemoryUsage -= o->Data.Size;
                  mHT.pushFreeEntry(o);
                  return true;
               }

               // add it back to the cache
               else
                  mHT.insert(key, o);
            }
            return false;
         }

         ////////////////////////////////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Builds a prune list (see getPruneList) with cache entries that have no active
         /// references and match filters in parameters. Returns true if the list contains
         /// elements afterwards which can be removed by calling remove().
         /// </summary>
         INLINE bool prune(
            const StdDuration& minage = StdSeconds(60), 
            const size_t       maxnum = 16)
         {
            // true if exceeded soft limit
            const bool URGENT = mMemoryLimit > 0 && mMemoryUsage > mMemoryLimit;

            // get current tick
            auto now = StdClock::now();

            // clear old prune list
            mPruneList.clear();

            // loop over all cache entries
            for (Entry<T>& o : mHT)
            {
               // ignore ones with references
               if (o.Refs > 0)
                  continue;

               // get time span since it was last used
               const auto span = now - o.Tick;

               // ignore too recently used ones
               if (!URGENT && span < minage)
                  continue;

               // try add to prune list, stop if full
               if (!mPruneList.pushBack(&o))
                  break;

               // also stop if reached desired maximum
               if (mPruneList.length() >= maxnum)
                  break;
            }

            return mPruneList.length() > 0;
         }
      };
   };
}
