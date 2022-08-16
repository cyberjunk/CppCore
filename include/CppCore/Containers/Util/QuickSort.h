#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Util/Comparer.h>

namespace CppCore
{
   /// <summary>
   /// Non-Recursive QuickSort Implementation.
   /// </summary>
   class QuickSort
   {
   private:
      INLINE QuickSort() { }
   public:
      /// <summary>
      /// Sorts the container elements using the provided temporary stack
      /// and the COMPARATOR class template argument.
      /// Complexity: O(n*log(n))
      /// CONTAINER must provide efficient public length(), index[] and swap() operations.
      /// ITEM must be the class stored in the container.
      /// COMPARER must be a class that provides a static compare() method to define ordering.
      /// MEMSIZE is the work memory array size
      /// </summary>
      template<typename CONTAINER, typename ITEM, typename COMPARER = Comparer<ITEM, ITEM>, size_t MEMSIZE>
      INLINE static bool sort(CONTAINER& container, size_t stack[MEMSIZE])
      {
         const size_t LEN = container.length();
         if (LEN > 1)
         {
            // index on stack
            size_t idx = 0;

            // push start/full interval
            stack[++idx] = LEN;
            stack[++idx] = 0;

            do
            {
               // pop next interval
               size_t beg = stack[idx--];
               size_t end = stack[idx--];

               ITEM& piv = container[beg];
               size_t l = beg + 1, r = end;
               while (l < r)
               {
                  if (COMPARER::less(container[l], piv))
                     l++;
                  else
                     container.swap(l, --r);
               }
               container.swap(--l, beg);

               // push right interval
               if (end > r + 1)
               {
                  if (idx < MEMSIZE - 2)
                  {
                     stack[++idx] = end;
                     stack[++idx] = r;
                  }
                  else
                     return false;
               }

               // push left interval
               if (l > beg + 1)
               {
                  if (idx < MEMSIZE - 2)
                  {
                     stack[++idx] = l;
                     stack[++idx] = beg;
                  }
                  else
                     return false;
               }
            } while (idx);
         }
         return true;
      }
   };
}
