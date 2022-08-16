#pragma once

#include <CppCore.Test/Root.h>

namespace CppCore { namespace Test { namespace Containers
{
   /// <summary>
   /// Tests for Array.h in CppCore::Containers
   /// </summary>
   class Array
   {
   public:
      INLINE static bool modelid()
      {
         Model::Array::Fix::ST<MAXMODELS> arr;
         size_t stack[MAXMODELS*4];
         size_t idx;
         Model* model;

         resetModels();

         for(size_t i = 0; i < MAXMODELS; i++)
            arr.pushBack(&models[i]);

         // unordered: coded check
         if (arr.validateSorted<Model::ComparerId::OP2OP>()) return false;

         // unordered: manual check
         if (arr[0]->getId() != MODEL1_ID) return false;
         if (arr[1]->getId() != MODEL2_ID) return false;
         if (arr[2]->getId() != MODEL3_ID) return false;
         if (arr[3]->getId() != MODEL4_ID) return false;

         // unsorted lookup
         if (!arr.findIdxUnsortedById(MODEL3_ID, idx)) return false;
         if (idx != (size_t)2U) return false;

         // sort
         arr.sortById<MAXMODELS*4>(&stack[0]);

         // ordered: coded check
         if (!arr.validateSorted<Model::ComparerId::OP2OP>()) return false;

         // ordered: manual check
         if (arr[0]->getId() != ORDER1_ID) return false;
         if (arr[1]->getId() != ORDER2_ID) return false;
         if (arr[2]->getId() != ORDER3_ID) return false;
         if (arr[3]->getId() != ORDER4_ID) return false;

         // sorted lookup
         if (!arr.findIdxUnsortedById(ORDER3_ID, idx)) return false;
         if (idx != (size_t)2U) return false;

         // unsorted remove
         if (!arr.removeOneUnsortedById(ORDER3_ID, model, idx)) return false;
         if (arr[0]->getId() != ORDER1_ID) return false;
         if (arr[1]->getId() != ORDER2_ID) return false;
         if (arr[2]->getId() != ORDER4_ID) return false;

         // sorted remove
         if (!arr.removeOneSortedById(ORDER2_ID, model, idx)) return false;
         if (arr[0]->getId() != ORDER1_ID) return false;
         if (arr[1]->getId() != ORDER4_ID) return false;

         // all remove
         if (arr.removeAllById(ORDER1_ID) != (size_t)1U) return false;
         if (arr.removeAllById(ORDER4_ID) != (size_t)1U) return false;

         return true;
      }

      INLINE static bool modelname()
      {
         Model::Array::Fix::ST<MAXMODELS> arr;
         size_t stack[MAXMODELS*4];
         size_t idx;
         Model* model;

         resetModels();

         for (size_t i = 0; i < MAXMODELS; i++)
            arr.pushBack(&models[i]);

         // unordered: coded check
         if (arr.validateSorted<Model::ComparerName::OP2OP>()) return false;

         // unordered: manual check
         if (arr[0]->getName() != MODEL1_NAME) return false;
         if (arr[1]->getName() != MODEL2_NAME) return false;
         if (arr[2]->getName() != MODEL3_NAME) return false;
         if (arr[3]->getName() != MODEL4_NAME) return false;

         // unsorted lookup
         if (!arr.findIdxUnsortedByName(MODEL3_NAME, idx)) return false;
         if (idx != (size_t)2U) return false;

         // sort
         arr.sortByName<MAXMODELS*4>(&stack[0]);

         // ordered: coded check
         if (!arr.validateSorted<Model::ComparerName::OP2OP>()) return false;

         // ordered: manual check
         if (arr[0]->getName() != ORDER1_NAME) return false;
         if (arr[1]->getName() != ORDER2_NAME) return false;
         if (arr[2]->getName() != ORDER3_NAME) return false;
         if (arr[3]->getName() != ORDER4_NAME) return false;

         // sorted lookup
         if (!arr.findIdxSortedByName(ORDER3_NAME, idx)) return false;
         if (idx != (size_t)2U) return false;

         // unsorted remove
         if (!arr.removeOneUnsortedByName(ORDER3_NAME, model, idx)) return false;
         if (arr[0]->getName() != ORDER1_NAME) return false;
         if (arr[1]->getName() != ORDER2_NAME) return false;
         if (arr[2]->getName() != ORDER4_NAME) return false;

         // sorted remove
         if (!arr.removeOneSortedByName(ORDER2_NAME, model, idx)) return false;
         if (arr[0]->getName() != ORDER1_NAME) return false;
         if (arr[1]->getName() != ORDER4_NAME) return false;

         // all remove
         if (arr.removeAllByName(ORDER1_NAME) != (size_t)1U) return false;
         if (arr.removeAllByName(ORDER4_NAME) != (size_t)1U) return false;

         return true;
      }

      INLINE static bool modelresize()
      {
         CppCore::Array::Dyn::ST<Model, true> arr(MAXMODELS);

         resetModels();

         for (size_t i = 0; i < MAXMODELS; i++)
            arr.pushBack(models[i]);

         if (arr[0] != models[0]) return false;
         if (arr[1] != models[1]) return false;
         if (arr[2] != models[2]) return false;
         if (arr[3] != models[3]) return false;

         arr.resize(2);
         if (arr.size()   != 2U)  return false;
         if (arr.length() != 2U)  return false;
         if (arr[0] != models[0]) return false;
         if (arr[1] != models[1]) return false;

         arr.resize(6);
         if (arr.size()   != 6U)  return false;
         if (arr.length() != 2U)  return false;

         for (size_t i = 0; i < MAXMODELS; i++)
            arr.pushBack(models[i]);

         if (arr.size()   != 6U)  return false;
         if (arr.length() != 6U)  return false;
         if (arr[0] != models[0]) return false;
         if (arr[1] != models[1]) return false;
         if (arr[2] != models[0]) return false;
         if (arr[3] != models[1]) return false;
         if (arr[4] != models[2]) return false;
         if (arr[5] != models[3]) return false;

         return true;
      }

      INLINE static bool integerresize()
      {
         CppCore::Array::Dyn::ST<uint32_t, false> arr(4);

         // init
         arr[0] = 3U;
         arr[1] = 0xFFFFFFFFU;
         arr[2] = 0x73FA81EBU;
         arr[3] = 1U;
         arr.setLength(4);

         // shrink
         arr.resize(2);
         if (arr.size()   != 2U)    return false;
         if (arr.length() != 2U)    return false;
         if (arr[0] != 3U)          return false;
         if (arr[1] != 0xFFFFFFFFU) return false;

         // grow
         arr.resize(6);
         if (arr.size()   != 6U)    return false;
         if (arr.length() != 2U)    return false;
         if (arr[0] != 3U)          return false;
         if (arr[1] != 0xFFFFFFFFU) return false;
         arr[2] = 0x3FA81EBCU;
         arr[3] = 0x00000009U;
         arr[4] = 0x3FA81EBCU;
         arr[5] = 0x00000007U;
         arr.setLength(6);

         if (arr.size()   != 6U)    return false;
         if (arr.length() != 6U)    return false;
         if (arr[0] != 3U)          return false;
         if (arr[1] != 0xFFFFFFFFU) return false;
         if (arr[2] != 0x3FA81EBCU) return false;
         if (arr[3] != 0x00000009U) return false;
         if (arr[4] != 0x3FA81EBCU) return false;
         if (arr[5] != 0x00000007U) return false;

         return true;
      }

      INLINE static bool iterator()
      {
         size_t i = 0;
         resetModels();
         // FIXED SIZE
         Model::Array::Fix::ST<MAXMODELS> arr;
         for (size_t i = 0; i < MAXMODELS; i++)
            arr.pushBack(&models[i]);
         // iterator is reverse by default
         i = 0;
         for (Model* m : arr)
         {
            if (m->getId() != models[MAXMODELS-1-i].getId())
               return false;
            else
               i++;
         }
         // DYN SIZE
         Model::Array::Dyn::ST dyn(4);
         for (size_t i = 0; i < MAXMODELS; i++)
            dyn.pushBack(&models[i]);
         // iterator is reverse by default
         i = 0;
         for (Model* m : dyn)
         {
            if (m->getId() != models[MAXMODELS-1-i].getId())
               return false;
            else
               i++;
         }

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
   TEST_CLASS(Array)
   {
   public:
      TEST_METHOD(MODELID)     { Assert::AreEqual(true, CppCore::Test::Containers::Array::modelid()); }
      TEST_METHOD(MODELNAME)   { Assert::AreEqual(true, CppCore::Test::Containers::Array::modelname()); }
      TEST_METHOD(MODELRESIZE) { Assert::AreEqual(true, CppCore::Test::Containers::Array::modelresize()); }
      TEST_METHOD(RESIZE)      { Assert::AreEqual(true, CppCore::Test::Containers::Array::integerresize()); }
      TEST_METHOD(ITERATOR)    { Assert::AreEqual(true, CppCore::Test::Containers::Array::iterator()); }
   };
}}}}
#endif
