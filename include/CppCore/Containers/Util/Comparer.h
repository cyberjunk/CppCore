#pragma once

#include <CppCore/Root.h>

namespace CppCore
{
   /// <summary>
   /// Basic Comparer
   /// </summary>
   template<typename T, typename U>
   class Comparer
   {
   private:
      INLINE Comparer() { }
   public:
      INLINE static bool equal    (const T& a, const U& b) { return a == b; }
      INLINE static bool nequal   (const T& a, const U& b) { return a != b; }
      INLINE static bool less     (const T& a, const U& b) { return a <  b; }
      INLINE static bool lesseq   (const T& a, const U& b) { return a <= b; }
      INLINE static bool greater  (const T& a, const U& b) { return a >  b; }
      INLINE static bool greatereq(const T& a, const U& b) { return a >= b; }

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
            INLINE static bool equal(T& a, U key)     { return a.getId() == key; }
            INLINE static bool nequal(T& a, U key)    { return a.getId() != key; }
            INLINE static bool less(T& a, U key)      { return a.getId() <  key; }
            INLINE static bool lesseq(T& a, U key)    { return a.getId() <= key; }
            INLINE static bool greater(T& a, U key)   { return a.getId() >  key; }
            INLINE static bool greatereq(T& a, U key) { return a.getId() >= key; }
         };
         class OP2K
         {
         public:
            INLINE static bool equal(T* a, U key)     { return a->getId() == key; }
            INLINE static bool nequal(T* a, U key)    { return a->getId() != key; }
            INLINE static bool less(T* a, U key)      { return a->getId() <  key; }
            INLINE static bool lesseq(T* a, U key)    { return a->getId() <= key; }
            INLINE static bool greater(T* a, U key)   { return a->getId() >  key; }
            INLINE static bool greatereq(T* a, U key) { return a->getId() >= key; }
         };
         class O2O
         {
         public:
            INLINE static bool equal(T& a, T& b)      { return a.getId() == b.getId(); }
            INLINE static bool nequal(T& a, T& b)     { return a.getId() != b.getId(); }
            INLINE static bool less(T& a, T& b)       { return a.getId() <  b.getId(); }
            INLINE static bool lesseq(T& a, T& b)     { return a.getId() <= b.getId(); }
            INLINE static bool greater(T& a, T& b)    { return a.getId() >  b.getId(); }
            INLINE static bool greatereq(T& a, T& b)  { return a.getId() >= b.getId(); }
         };
         class OP2OP
         {
         public:
            INLINE static bool equal(T* a, T* b)      { return a->getId() == b->getId(); }
            INLINE static bool nequal(T* a, T* b)     { return a->getId() != b->getId(); }
            INLINE static bool less(T* a, T* b)       { return a->getId() <  b->getId(); }
            INLINE static bool lesseq(T* a, T* b)     { return a->getId() <= b->getId(); }
            INLINE static bool greater(T* a, T* b)    { return a->getId() >  b->getId(); }
            INLINE static bool greatereq(T* a, T* b)  { return a->getId() >= b->getId(); }
         };
      };

      /// <summary>
      /// Comparers using getObjectId()
      /// </summary>
      class ObjectId
      {
      private:
         INLINE ObjectId() { }
      public:
         class O2K
         {
         public:
            INLINE static bool equal(T& a, U key)     { return a.getObjectId() == key; }
            INLINE static bool nequal(T& a, U key)    { return a.getObjectId() != key; }
            INLINE static bool less(T& a, U key)      { return a.getObjectId() <  key; }
            INLINE static bool lesseq(T& a, U key)    { return a.getObjectId() <= key; }
            INLINE static bool greater(T& a, U key)   { return a.getObjectId() >  key; }
            INLINE static bool greatereq(T& a, U key) { return a.getObjectId() >= key; }
         };
         class OP2K
         {
         public:
            INLINE static bool equal(T* a, U key)     { return a->getObjectId() == key; }
            INLINE static bool nequal(T* a, U key)    { return a->getObjectId() != key; }
            INLINE static bool less(T* a, U key)      { return a->getObjectId() <  key; }
            INLINE static bool lesseq(T* a, U key)    { return a->getObjectId() <= key; }
            INLINE static bool greater(T* a, U key)   { return a->getObjectId() >  key; }
            INLINE static bool greatereq(T* a, U key) { return a->getObjectId() >= key; }
         };
         class O2O
         {
         public:
            INLINE static bool equal(T& a, T& b)      { return a.getObjectId() == b.getObjectId(); }
            INLINE static bool nequal(T& a, T& b)     { return a.getObjectId() != b.getObjectId(); }
            INLINE static bool less(T& a, T& b)       { return a.getObjectId() <  b.getObjectId(); }
            INLINE static bool lesseq(T& a, T& b)     { return a.getObjectId() <= b.getObjectId(); }
            INLINE static bool greater(T& a, T& b)    { return a.getObjectId() >  b.getObjectId(); }
            INLINE static bool greatereq(T& a, T& b)  { return a.getObjectId() >= b.getObjectId(); }
         };
         class OP2OP
         {
         public:
            INLINE static bool equal(T* a, T* b)      { return a->getObjectId() == b->getObjectId(); }
            INLINE static bool nequal(T* a, T* b)     { return a->getObjectId() != b->getObjectId(); }
            INLINE static bool less(T* a, T* b)       { return a->getObjectId() <  b->getObjectId(); }
            INLINE static bool lesseq(T* a, T* b)     { return a->getObjectId() <= b->getObjectId(); }
            INLINE static bool greater(T* a, T* b)    { return a->getObjectId() >  b->getObjectId(); }
            INLINE static bool greatereq(T* a, T* b)  { return a->getObjectId() >= b->getObjectId(); }
         };
      };

      /// <summary>
      /// Comparers using getKey()
      /// </summary>
      class Key
      {
      private:
         INLINE Key() { }
      public:
         class O2K
         {
         public:
            INLINE static bool equal(T& a, U key)     { return a.getKey() == key; }
            INLINE static bool nequal(T& a, U key)    { return a.getKey() != key; }
            INLINE static bool less(T& a, U key)      { return a.getKey() <  key; }
            INLINE static bool lesseq(T& a, U key)    { return a.getKey() <= key; }
            INLINE static bool greater(T& a, U key)   { return a.getKey() >  key; }
            INLINE static bool greatereq(T& a, U key) { return a.getKey() >= key; }
         };
         class OP2K
         {
         public:
            INLINE static bool equal(T* a, U key)     { return a->getKey() == key; }
            INLINE static bool nequal(T* a, U key)    { return a->getKey() != key; }
            INLINE static bool less(T* a, U key)      { return a->getKey() <  key; }
            INLINE static bool lesseq(T* a, U key)    { return a->getKey() <= key; }
            INLINE static bool greater(T* a, U key)   { return a->getKey() >  key; }
            INLINE static bool greatereq(T* a, U key) { return a->getKey() >= key; }
         };
         class O2O
         {
         public:
            INLINE static bool equal(T& a, T& b)      { return a.getKey() == b.getKey(); }
            INLINE static bool nequal(T& a, T& b)     { return a.getKey() != b.getKey(); }
            INLINE static bool less(T& a, T& b)       { return a.getKey() <  b.getKey(); }
            INLINE static bool lesseq(T& a, T& b)     { return a.getKey() <= b.getKey(); }
            INLINE static bool greater(T& a, T& b)    { return a.getKey() >  b.getKey(); }
            INLINE static bool greatereq(T& a, T& b)  { return a.getKey() >= b.getKey(); }
         };
         class OP2OP
         {
         public:
            INLINE static bool equal(T* a, T* b)      { return a->getKey() == b->getKey(); }
            INLINE static bool nequal(T* a, T* b)     { return a->getKey() != b->getKey(); }
            INLINE static bool less(T* a, T* b)       { return a->getKey() <  b->getKey(); }
            INLINE static bool lesseq(T* a, T* b)     { return a->getKey() <= b->getKey(); }
            INLINE static bool greater(T* a, T* b)    { return a->getKey() >  b->getKey(); }
            INLINE static bool greatereq(T* a, T* b)  { return a->getKey() >= b->getKey(); }
         };
      };

      /// <summary>
      /// Comparers using getNum()
      /// </summary>
      class Num
      {
      private:
         INLINE Num() { }
      public:
         class O2K
         {
         public:
            INLINE static bool equal(T& a, U key)     { return a.getNum() == key; }
            INLINE static bool nequal(T& a, U key)    { return a.getNum() != key; }
            INLINE static bool less(T& a, U key)      { return a.getNum() <  key; }
            INLINE static bool lesseq(T& a, U key)    { return a.getNum() <= key; }
            INLINE static bool greater(T& a, U key)   { return a.getNum() >  key; }
            INLINE static bool greatereq(T& a, U key) { return a.getNum() >= key; }
         };
         class OP2K
         {
         public:
            INLINE static bool equal(T* a, U key)     { return a->getNum() == key; }
            INLINE static bool nequal(T* a, U key)    { return a->getNum() != key; }
            INLINE static bool less(T* a, U key)      { return a->getNum() <  key; }
            INLINE static bool lesseq(T* a, U key)    { return a->getNum() <= key; }
            INLINE static bool greater(T* a, U key)   { return a->getNum() >  key; }
            INLINE static bool greatereq(T* a, U key) { return a->getNum() >= key; }
         };
         class O2O
         {
         public:
            INLINE static bool equal(T& a, T& b)      { return a.getNum() == b.getNum(); }
            INLINE static bool nequal(T& a, T& b)     { return a.getNum() != b.getNum(); }
            INLINE static bool less(T& a, T& b)       { return a.getNum() <  b.getNum(); }
            INLINE static bool lesseq(T& a, T& b)     { return a.getNum() <= b.getNum(); }
            INLINE static bool greater(T& a, T& b)    { return a.getNum() >  b.getNum(); }
            INLINE static bool greatereq(T& a, T& b)  { return a.getNum() >= b.getNum(); }
         };
         class OP2OP
         {
         public:
            INLINE static bool equal(T* a, T* b)      { return a->getNum() == b->getNum(); }
            INLINE static bool nequal(T* a, T* b)     { return a->getNum() != b->getNum(); }
            INLINE static bool less(T* a, T* b)       { return a->getNum() <  b->getNum(); }
            INLINE static bool lesseq(T* a, T* b)     { return a->getNum() <= b->getNum(); }
            INLINE static bool greater(T* a, T* b)    { return a->getNum() >  b->getNum(); }
            INLINE static bool greatereq(T* a, T* b)  { return a->getNum() >= b->getNum(); }
         };
      };

      /// <summary>
      /// Comparers using getName()
      /// </summary>
      class Name
      {
      private:
         INLINE Name() { }
      public:
         class O2K
         {
         public:
            INLINE static bool equal(T& a, U key)     { return a.getName() == key; }
            INLINE static bool nequal(T& a, U key)    { return a.getName() != key; }
            INLINE static bool less(T& a, U key)      { return a.getName() <  key; }
            INLINE static bool lesseq(T& a, U key)    { return a.getName() <= key; }
            INLINE static bool greater(T& a, U key)   { return a.getName() >  key; }
            INLINE static bool greatereq(T& a, U key) { return a.getName() >= key; }
         };
         class OP2K
         {
         public:
            INLINE static bool equal(T* a, U key)     { return a->getName() == key; }
            INLINE static bool nequal(T* a, U key)    { return a->getName() != key; }
            INLINE static bool less(T* a, U key)      { return a->getName() <  key; }
            INLINE static bool lesseq(T* a, U key)    { return a->getName() <= key; }
            INLINE static bool greater(T* a, U key)   { return a->getName() >  key; }
            INLINE static bool greatereq(T* a, U key) { return a->getName() >= key; }
         };
         class O2O
         {
         public:
            INLINE static bool equal(T& a, T& b)      { return a.getName() == b.getName(); }
            INLINE static bool nequal(T& a, T& b)     { return a.getName() != b.getName(); }
            INLINE static bool less(T& a, T& b)       { return a.getName() <  b.getName(); }
            INLINE static bool lesseq(T& a, T& b)     { return a.getName() <= b.getName(); }
            INLINE static bool greater(T& a, T& b)    { return a.getName() >  b.getName(); }
            INLINE static bool greatereq(T& a, T& b)  { return a.getName() >= b.getName(); }
         };
         class OP2OP
         {
         public:
            INLINE static bool equal(T* a, T* b)      { return a->getName() == b->getName(); }
            INLINE static bool nequal(T* a, T* b)     { return a->getName() != b->getName(); }
            INLINE static bool less(T* a, T* b)       { return a->getName() <  b->getName(); }
            INLINE static bool lesseq(T* a, T* b)     { return a->getName() <= b->getName(); }
            INLINE static bool greater(T* a, T* b)    { return a->getName() >  b->getName(); }
            INLINE static bool greatereq(T* a, T* b)  { return a->getName() >= b->getName(); }
         };
      };

      /// <summary>
      /// Comparers using getFileName()
      /// </summary>
      class FileName
      {
      private:
         INLINE FileName() { }
      public:
         class O2K
         {
         public:
            INLINE static bool equal(T& a, U key)     { return a.getFileName() == key; }
            INLINE static bool nequal(T& a, U key)    { return a.getFileName() != key; }
            INLINE static bool less(T& a, U key)      { return a.getFileName() <  key; }
            INLINE static bool lesseq(T& a, U key)    { return a.getFileName() <= key; }
            INLINE static bool greater(T& a, U key)   { return a.getFileName() >  key; }
            INLINE static bool greatereq(T& a, U key) { return a.getFileName() >= key; }
         };
         class OP2K
         {
         public:
            INLINE static bool equal(T* a, U key)     { return a->getFileName() == key; }
            INLINE static bool nequal(T* a, U key)    { return a->getFileName() != key; }
            INLINE static bool less(T* a, U key)      { return a->getFileName() <  key; }
            INLINE static bool lesseq(T* a, U key)    { return a->getFileName() <= key; }
            INLINE static bool greater(T* a, U key)   { return a->getFileName() >  key; }
            INLINE static bool greatereq(T* a, U key) { return a->getFileName() >= key; }
         };
         class O2O
         {
         public:
            INLINE static bool equal(T& a, T& b)      { return a.getFileName() == b.getFileName(); }
            INLINE static bool nequal(T& a, T& b)     { return a.getFileName() != b.getFileName(); }
            INLINE static bool less(T& a, T& b)       { return a.getFileName() <  b.getFileName(); }
            INLINE static bool lesseq(T& a, T& b)     { return a.getFileName() <= b.getFileName(); }
            INLINE static bool greater(T& a, T& b)    { return a.getFileName() >  b.getFileName(); }
            INLINE static bool greatereq(T& a, T& b)  { return a.getFileName() >= b.getFileName(); }
         };
         class OP2OP
         {
         public:
            INLINE static bool equal(T* a, T* b)      { return a->getFileName() == b->getFileName(); }
            INLINE static bool nequal(T* a, T* b)     { return a->getFileName() != b->getFileName(); }
            INLINE static bool less(T* a, T* b)       { return a->getFileName() <  b->getFileName(); }
            INLINE static bool lesseq(T* a, T* b)     { return a->getFileName() <= b->getFileName(); }
            INLINE static bool greater(T* a, T* b)    { return a->getFileName() >  b->getFileName(); }
            INLINE static bool greatereq(T* a, T* b)  { return a->getFileName() >= b->getFileName(); }
         };
      };

      /// <summary>
      /// Comparers using getTime()
      /// </summary>
      class Time
      {
      private:
         INLINE Time() { }
      public:
         class O2K
         {
         public:
            INLINE static bool equal(T& a, U key)     { return a.getTime() == key; }
            INLINE static bool nequal(T& a, U key)    { return a.getTime() != key; }
            INLINE static bool less(T& a, U key)      { return a.getTime() <  key; }
            INLINE static bool lesseq(T& a, U key)    { return a.getTime() <= key; }
            INLINE static bool greater(T& a, U key)   { return a.getTime() >  key; }
            INLINE static bool greatereq(T& a, U key) { return a.getTime() >= key; }
         };
         class OP2K
         {
         public:
            INLINE static bool equal(T* a, U key)     { return a->getTime() == key; }
            INLINE static bool nequal(T* a, U key)    { return a->getTime() != key; }
            INLINE static bool less(T* a, U key)      { return a->getTime() <  key; }
            INLINE static bool lesseq(T* a, U key)    { return a->getTime() <= key; }
            INLINE static bool greater(T* a, U key)   { return a->getTime() >  key; }
            INLINE static bool greatereq(T* a, U key) { return a->getTime() >= key; }
         };
         class O2O
         {
         public:
            INLINE static bool equal(T& a, T& b)      { return a.getTime() == b.getTime(); }
            INLINE static bool nequal(T& a, T& b)     { return a.getTime() != b.getTime(); }
            INLINE static bool less(T& a, T& b)       { return a.getTime() <  b.getTime(); }
            INLINE static bool lesseq(T& a, T& b)     { return a.getTime() <= b.getTime(); }
            INLINE static bool greater(T& a, T& b)    { return a.getTime() >  b.getTime(); }
            INLINE static bool greatereq(T& a, T& b)  { return a.getTime() >= b.getTime(); }
         };
         class OP2OP
         {
         public:
            INLINE static bool equal(T* a, T* b)      { return a->getTime() == b->getTime(); }
            INLINE static bool nequal(T* a, T* b)     { return a->getTime() != b->getTime(); }
            INLINE static bool less(T* a, T* b)       { return a->getTime() <  b->getTime(); }
            INLINE static bool lesseq(T* a, T* b)     { return a->getTime() <= b->getTime(); }
            INLINE static bool greater(T* a, T* b)    { return a->getTime() >  b->getTime(); }
            INLINE static bool greatereq(T* a, T* b)  { return a->getTime() >= b->getTime(); }
         };
      };

      /// <summary>
      /// Comparers using getDate()
      /// </summary>
      class Date
      {
      private:
         INLINE Date() { }
      public:
         class O2K
         {
         public:
            INLINE static bool equal(T& a, U key)     { return a.getDate() == key; }
            INLINE static bool nequal(T& a, U key)    { return a.getDate() != key; }
            INLINE static bool less(T& a, U key)      { return a.getDate() <  key; }
            INLINE static bool lesseq(T& a, U key)    { return a.getDate() <= key; }
            INLINE static bool greater(T& a, U key)   { return a.getDate() >  key; }
            INLINE static bool greatereq(T& a, U key) { return a.getDate() >= key; }
         };
         class OP2K
         {
         public:
            INLINE static bool equal(T* a, U key)     { return a->getDate() == key; }
            INLINE static bool nequal(T* a, U key)    { return a->getDate() != key; }
            INLINE static bool less(T* a, U key)      { return a->getDate() <  key; }
            INLINE static bool lesseq(T* a, U key)    { return a->getDate() <= key; }
            INLINE static bool greater(T* a, U key)   { return a->getDate() >  key; }
            INLINE static bool greatereq(T* a, U key) { return a->getDate() >= key; }
         };
         class O2O
         {
         public:
            INLINE static bool equal(T& a, T& b)      { return a.getDate() == b.getDate(); }
            INLINE static bool nequal(T& a, T& b)     { return a.getDate() != b.getDate(); }
            INLINE static bool less(T& a, T& b)       { return a.getDate() <  b.getDate(); }
            INLINE static bool lesseq(T& a, T& b)     { return a.getDate() <= b.getDate(); }
            INLINE static bool greater(T& a, T& b)    { return a.getDate() >  b.getDate(); }
            INLINE static bool greatereq(T& a, T& b)  { return a.getDate() >= b.getDate(); }
         };
         class OP2OP
         {
         public:
            INLINE static bool equal(T* a, T* b)      { return a->getDate() == b->getDate(); }
            INLINE static bool nequal(T* a, T* b)     { return a->getDate() != b->getDate(); }
            INLINE static bool less(T* a, T* b)       { return a->getDate() <  b->getDate(); }
            INLINE static bool lesseq(T* a, T* b)     { return a->getDate() <= b->getDate(); }
            INLINE static bool greater(T* a, T* b)    { return a->getDate() >  b->getDate(); }
            INLINE static bool greatereq(T* a, T* b)  { return a->getDate() >= b->getDate(); }
         };
      };
   };
}
