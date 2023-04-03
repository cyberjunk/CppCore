#pragma once

#include <CppCore/Root.h>
#include <CppCore/Hash/Murmur3.h>
#include <CppCore/Containers/Array.h>
#include <CppCore/Containers/HashTable.h>

namespace CppCore
{
   /// <summary>
   /// Example Model
   /// </summary>
   class Model
   {
   protected:
      uint32_t mId;
      string   mName;

   public:
      INLINE Model(uint32_t id = 0, const string& name = "") : mId(id), mName(name) { }

      INLINE uint32_t      getId()   const { return mId;   }
      INLINE const string& getName() const { return mName; }

      INLINE uint32_t& refId()   { return mId;   }
      INLINE string&   refName() { return mName; }

      INLINE void setId(const uint32_t id)    { mId = id;     }
      INLINE void setName(const string& name) { mName = name; }

      INLINE bool  operator == (const Model& m) const { return getId() == m.getId() && getName() == m.getName(); }
      INLINE bool  operator != (const Model& m) const { return !(*this == m); }

      /// <summary>
      /// Example Model ID Comparer
      /// </summary>
      typedef Comparer<Model, uint32_t>::Id ComparerId;

      /// <summary>
      /// Example Model Name Comparer
      /// </summary>
      typedef Comparer<Model, const string&>::Name ComparerName;

      /// <summary>
      /// Example Model Arrays
      /// </summary>
      class Array
      {
      private:
         INLINE Array() { }
      public:
         class Dyn
         {
         public:
            /// <summary>
            /// Dynamic Sized Model Pointer Array for Single Threaded Access
            /// </summary>
            template<typename T = Model*, bool CONSTRUCT = !::std::is_trivially_constructible<T>::value>
            class ST : public CppCore::Array::Dyn::ST<T, CONSTRUCT>
            {
            public:
               INLINE ST(size_t initialSize) : ::CppCore::Array::Dyn::ST<T, CONSTRUCT>(initialSize) { }
               ////////////////////////////////////////////////////////////////////////////////////
               template<size_t MEMSIZE>
               INLINE bool sortById(size_t stack[MEMSIZE])
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template sort<ComparerId::OP2OP, MEMSIZE>(stack);
               }
               template<size_t MEMSIZE>
               INLINE bool sortByName(size_t* stack)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template sort<ComparerName::OP2OP, MEMSIZE>(stack);
               }
               ////////////////////////////////////////////////////////////////////////////////////
               INLINE bool findIdxUnsortedById(const uint32_t id, size_t& idx)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template findIdxUnsorted<
                     uint32_t, ComparerId::OP2K>(id, idx);
               }
               INLINE bool findIdxSortedById(const uint32_t id, size_t& idx)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template findIdxSorted<
                     uint32_t, ComparerId::OP2K>(id, idx);
               }
               ////////////////////////////////////////////////////////////////////////////////////
               INLINE bool findIdxUnsortedByName(const string& name, size_t& idx)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template findIdxUnsorted<
                     string, ComparerName::OP2K>(name, idx);
               }
               INLINE bool findIdxSortedByName(const string& name, size_t& idx)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template findIdxSorted<
                     string, ComparerName::OP2K>(name, idx);
               }
               ////////////////////////////////////////////////////////////////////////////////////
               INLINE bool removeOneUnsortedById(const uint32_t id, T& item, size_t& idx)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template removeOneUnsorted<
                     uint32_t, ComparerId::OP2K>(id, item, idx);
               }
               INLINE bool removeOneSortedById(const uint32_t id, T& item, size_t& idx)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template removeOneSorted<
                     uint32_t, ComparerId::OP2K>(id, item, idx);
               }
               ////////////////////////////////////////////////////////////////////////////////////
               INLINE bool removeOneUnsortedByName(const string& name, T& item, size_t& idx)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template removeOneUnsorted<
                     string, ComparerName::OP2K>(name, item, idx);
               }
               INLINE bool removeOneSortedByName(const string& name, T& item, size_t& idx)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template removeOneSorted<
                     string, ComparerName::OP2K>(name, item, idx);
               }
               ////////////////////////////////////////////////////////////////////////////////////
               INLINE size_t removeAllById(uint32_t id)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template removeAll<
                     uint32_t, ComparerId::OP2K>(id);
               }
               INLINE size_t removeAllByName(const string& name)
               {
                  return ::CppCore::Array::Dyn::ST<T, CONSTRUCT>::template removeAll<
                     string, ComparerName::OP2K>(name);
               }
               ////////////////////////////////////////////////////////////////////////////////////
            };

            /// <summary>
            /// Dynamic Sized Model Pointer Array for Multi Threaded Access
            /// </summary>
            template<typename T = Model*, bool CONSTRUCT = !::std::is_trivially_constructible<T>::value>
            class MT : public CppCore::Array::Dyn::MT<T, CONSTRUCT>
            {
            public:
               INLINE MT(const size_t size = 0) : ::CppCore::Array::Dyn::MT<T, CONSTRUCT>(size) { }
            };
         };
         class Fix
         {
         public:
            /// <summary>
            /// Fixed Sized Model Array for Single Threaded Access
            /// </summary>
            template<size_t SIZE, typename T = Model*>
            class ST : public CppCore::Array::Fix::ST<T, SIZE>
            {
            public:
               INLINE ST() : ::CppCore::Array::Fix::ST<T, SIZE>() { }
               ////////////////////////////////////////////////////////////////////////////////////
               template<size_t MEMSIZE>
               INLINE bool sortById(size_t stack[MEMSIZE])
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template sort<ComparerId::OP2OP, MEMSIZE>(stack);
               }
               template<size_t MEMSIZE>
               INLINE bool sortByName(size_t stack[MEMSIZE])
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template sort<ComparerName::OP2OP, MEMSIZE>(stack);
               }
               ////////////////////////////////////////////////////////////////////////////////////
               INLINE bool findIdxUnsortedById(const uint32_t id, size_t& idx)
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template findIdxUnsorted<
                     uint32_t, ComparerId::OP2K>(id, idx);
               }
               INLINE bool findIdxSortedById(const uint32_t id, size_t& idx)
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template findIdxSorted<
                     uint32_t, ComparerId::OP2K>(id, idx);
               }
               ////////////////////////////////////////////////////////////////////////////////////
               INLINE bool findIdxUnsortedByName(const string& name, size_t& idx)
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template findIdxUnsorted<
                     string, ComparerName::OP2K>(name, idx);
               }
               INLINE bool findIdxSortedByName(const string& name, size_t& idx)
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template findIdxSorted<
                     string, ComparerName::OP2K>(name, idx);
               }
               ////////////////////////////////////////////////////////////////////////////////////
               INLINE bool removeOneUnsortedById(const uint32_t id, T& item, size_t& idx)
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template removeOneUnsorted<
                     uint32_t, ComparerId::OP2K>(id, item, idx);
               }
               INLINE bool removeOneSortedById(const uint32_t id, T& item, size_t& idx)
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template removeOneSorted<
                     uint32_t, ComparerId::OP2K>(id, item, idx);
               }
               ////////////////////////////////////////////////////////////////////////////////////
               INLINE bool removeOneUnsortedByName(const string& name, T& item, size_t& idx)
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template removeOneUnsorted<
                     string, ComparerName::OP2K>(name, item, idx);
               }
               INLINE bool removeOneSortedByName(const string& name, T& item, size_t& idx)
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template removeOneSorted<
                     string, ComparerName::OP2K>(name, item, idx);
               }
               ////////////////////////////////////////////////////////////////////////////////////
               INLINE size_t removeAllById(uint32_t id)
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template removeAll<
                     uint32_t, ComparerId::OP2K>(id);
               }
               INLINE size_t removeAllByName(const string& name)
               {
                  return ::CppCore::Array::Fix::ST<T, SIZE>::template removeAll<
                     string, ComparerName::OP2K>(name);
               }
               ////////////////////////////////////////////////////////////////////////////////////
            };

            /// <summary>
            /// Fixed Sized Model Array for Multi Threaded Access
            /// </summary>
            template<size_t SIZE, typename T = Model * >
            class MT : public CppCore::Array::Fix::MT<T, SIZE>
            {
            public:
               INLINE MT() : ::CppCore::Array::Fix::MT<T, SIZE>() { }
            };
         };
      };

      /// <summary>
      /// Example Model HashTable (using Name as Key)
      /// </summary>
      class HashTableName
      {
      private:
         INLINE HashTableName() { }
      public:
         template<
            size_t   POOLSIZE, 
            typename TMODEL   = Model*, 
            typename COMPARER = Model::ComparerName::OP2K>
         class ST : public HashTable::ST<TMODEL, string, POOLSIZE, COMPARER>
         {
         };
      };

      /// <summary>
      /// Example Model HashTable (using Id as Key)
      /// </summary>
      class HashTableId
      {
      private:
         INLINE HashTableId() { }
      public:
         template<
            size_t   POOLSIZE, 
            typename TMODEL   = Model*,
            typename COMPARER = Model::ComparerId::OP2K>
         class ST : public HashTable::ST<TMODEL, uint32_t, POOLSIZE, COMPARER>
         {
         };
      };
   };
}
