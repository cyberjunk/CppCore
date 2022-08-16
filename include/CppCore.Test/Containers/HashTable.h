#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Containers
{
   /// <summary>
   /// Tests for HashTable.h in CppCore::Containers
   /// </summary>
   class HashTable
   {
   public:
      INLINE static bool modelid()
      {
         Model::HashTableId::ST<MAXMODELS, MAXMODELS> ht;
         Model* model;

         resetModels();

         // try insert all into hashtable
         for (size_t i = 0; i < MAXMODELS; i++)
            if (!ht.insert(models[i].getId(), &models[i]))
               return false;

         // check length
         if ((size_t)MAXMODELS != ht.length()) return false;

         // try looking them all up
         for (size_t i = 0; i < MAXMODELS; i++)
         {
            if (!ht.find(models[i].getId(), model)) return false;
            if (models[i].getId() != model->getId()) return false;
         }

         // try removing them all
         for (size_t i = 0; i < MAXMODELS; i++)
            if (!ht.removeAndPushFree(models[i].getId()))
               return false;

         // check length
         if ((size_t)0 != ht.length()) return false;

         return true;
      }
      INLINE static bool modelname()
      {
         Model::HashTableName::ST<MAXMODELS, MAXMODELS> ht;
         Model* model;

         resetModels();

         // try insert all into hashtable
         for (size_t i = 0; i < MAXMODELS; i++)
            if (!ht.insert(models[i].getName(), &models[i]))
               return false;

         // check length
         if ((size_t)MAXMODELS != ht.length()) return false;

         // try looking them all up
         for (size_t i = 0; i < MAXMODELS; i++)
         {
            if (!ht.find(models[i].getName(), model)) return false;
            if (models[i].getId() != model->getId()) return false; // !!
         }

         // try removing them all
         for (size_t i = 0; i < MAXMODELS; i++)
            if (!ht.removeAndPushFree(models[i].getName()))
               return false;

         // check length
         if ((size_t)0 != ht.length()) return false;

         return true;
      }
   };
}}}

#if defined(CPPCORE_COMPILER_MSVC)
namespace CppCore { namespace Test { namespace VS { namespace Containers
{
   /// <summary>
   /// Visual Studio Test Class
   /// </summary>
   TEST_CLASS(HashTable)
   {
   public:
      TEST_METHOD(MODELID)   { Assert::AreEqual(true, CppCore::Test::Containers::HashTable::modelid()); }
      TEST_METHOD(MODELNAME) { Assert::AreEqual(true, CppCore::Test::Containers::HashTable::modelname()); }
   };
}}}}
#endif
