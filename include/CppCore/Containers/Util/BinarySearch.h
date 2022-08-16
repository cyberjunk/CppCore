#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Util/Comparer.h>

namespace CppCore
{
   /// <summary>
   /// Non-Recursive Binary Search Implementation.
   /// CONTAINER must provide efficient public length() and index[] operations
   /// and must be sorted.
   /// ITEM must be the class stored in the container.
   /// CMPLESS and CMPGREATER must be classes providing a static compare() method
   /// correct for the active sorting of CONTAINER.
   /// </summary>
   template<
      typename CONTAINER, 
      typename ITEM,
      typename KEY = ITEM,
      typename COMPARER = Comparer<ITEM, KEY>>
   class BinarySearch
   {
   private:
      INLINE BinarySearch() { }
   public:
      /// <summary>
      /// Searches the container using the comparers from class template.
      /// Returns true if found, false otherwise.
      /// Sets idx either with found index or with index to insert the not found one.
      /// Complexity: O(log(n))
      /// </summary>
      INLINE static bool search(CONTAINER& container, const KEY& item, size_t& idx)
      {
         // default return (zero length)
         idx = 0;

         // get length of container
         const size_t LEN = container.length();

         // must have at least one item
         if (LEN > 0)
         {
            size_t l = 0;
            size_t r = LEN - 1;

            while (true)
            {
               idx = l + ((r - l) / 2);

               if (COMPARER::less(container[idx], item))
               {
                  // continue search on right side
                  if (idx < r)
                     l = idx + 1;

                  // not found
                  else
                  {
                     idx++;
                     return false;
                  }
               }
               else if (COMPARER::greater(container[idx], item))
               {
                  // continue search on left side
                  if (idx > l)
                     r = idx - 1;

                  // not found
                  else
                     return false;;
               }

               // found
               else
                  return true;
            }
         }

         // not found
         return false;
      }
   };
}
