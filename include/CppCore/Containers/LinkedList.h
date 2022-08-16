#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Array.h>
#include <CppCore/Containers/Pool.h>

namespace CppCore
{
   /// <summary>
   /// TODO: EVALUATE; LIKELY UNREQUIRED
   /// TODO: THIS NEEDS DYNAMIC KEY HANDLING
   /// A double-linked list
   /// </summary>
   template<class T, size_t SIZE>
   class LinkedList
   {
   public:
      /// <summary>
      /// The Item stored in the Linked List
      /// </summary>
      class Item
      {
         friend class Iterator;
         friend class LinkedList<T, SIZE>;
      protected:
         Item* Next;
         Item* Prev;
      public:
         T     Data;
      };

   protected:
      /// <summary>
      /// C++ Iterator
      /// </summary>
      class Iterator 
      {
      protected:
         Item* mItem;
      public:
         INLINE Iterator(Item* item) : mItem(item) {}
         INLINE T&        operator*()  { return mItem->Data; }
         INLINE Iterator& operator++() { mItem = mItem->Next; return *this; }
         INLINE bool      operator!=(const Iterator& end) const { return mItem != NULL; }
      };

      Pool::Fix::ST<Item, SIZE> mFree;
      Item*                     mFirst;
      Item*                     mLast;
      size_t                    mLength;

      /// <summary>
      /// Template to avoid code duplication.
      /// See public variants removeOne and removeAll
      /// </summary>
      template<bool ALL = false>
      INLINE size_t remove(const T& data)
      {
         Item* current  = mFirst;
         size_t removed = 0;

         // loop over list
         while (current)
         {
            // not a match, increment
            if (current->Data != data)
               current = current->Next;

            // found
            else
            {
               Item* prev = current->Prev;
               Item* next = current->Next;

               // hook up previous with next
               if (prev) prev->Next = next;
               if (next) next->Prev = prev;

               // handle removing first
               if (current == mFirst)
                  mFirst = next;

               // handle removing last
               if (current == mLast)
                  mLast = prev;

               // push the list node to our free ones
               mFree.pushBack(current);

               removed++; // increment counter
               mLength--; // decrement length

               // done if removing only the first hit
               if (!ALL)
                  return removed;

               // else loop with next node
               else
                  current = next; 
            }
         }

         return removed;
      }

      /// <summary>
      /// Template to avoid code duplication.
      /// See public variants pushBack and pushFront
      /// </summary>
      template<bool BACK = true>
      INLINE bool push(const T& data)
      {
         Item* entry;

         // try get free list node
         if (mFree.popBack(entry))
         {
            entry->Data = data;

            // add at end
            if (BACK)
            {
               if (mLast)
               {
                  entry->Next = NULL;
                  entry->Prev = mLast;
                  mLast->Next = entry;
                  mLast       = entry;
               }

               // empty list
               else
               {
                  entry->Next = NULL;
                  entry->Prev = NULL;
                  mFirst = entry;
                  mLast  = entry;
               }
            }

            // add at front
            else
            {
               if (mFirst)
               {
                  entry->Next  = mFirst;
                  entry->Prev  = NULL;
                  mFirst->Prev = entry;
                  mFirst       = entry;
               }
               else
               {
                  entry->Next = NULL;
                  entry->Prev = NULL;
                  mFirst = entry;
                  mLast  = entry;
               }
            }

            // increment length
            mLength++;

            return true;
         }
         else
            return false;
      }

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE LinkedList() : mFirst(0), mLast(0), mLength(0) { }

      INLINE Iterator begin() { return Iterator(mFirst); }
      INLINE Iterator end() { return Iterator(mLast); }

      /// <summary>
      /// Retrieves the constant maximum size of the list
      /// Complexity: O(1)
      /// </summary>
      INLINE size_t size() const { return SIZE; }

      /// <summary>
      /// Retrieves the current length of the list
      /// Complexity: O(1)
      /// </summary>
      INLINE size_t length() const { return mLength; }

      /// <summary>
      /// Retrieves the data item at specified list index.
      /// Unchecked, crashes on index-out-of-bound.
      /// Complexity: O(n)
      /// </summary>
      INLINE T& operator[](size_t index)
      {
         Item* current = mFirst;
         for (size_t i = 0; i < index; i++)
            current = current->Next;
         return current->Data;
      }

      //////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Tries to add an entry to the end of the list.
      /// Returns true on success or false if list is full.
      /// Complexity: O(1)
      /// </summary>
      INLINE bool pushBack(const T& data)
      {
         return push<true>(data);
      }

      /// Tries to add an entry to the front of the list.
      /// Returns true on success or false if list is full.
      /// Complexity: O(1)
      /// </summary>
      INLINE bool pushFront(const T& data)
      {
         return push<false>(data);
      }

      /// <summary>
      /// Tries to insert an entry at an arbitrary existing index.
      /// Returns true on success or false if list is full or idx invalid.
      /// Complexity: O(n)
      /// </summary>
      INLINE bool insertAt(const T& data, size_t idx)
      {
         Item* current = mFirst;

         // iterate to index
         for (size_t i = 0; i < idx; i++)
         {
            if (current) current = current->Next;
            else return false;
         }

         Item* entry;

         // the index must be used by a node
         // and a free node must available
         if (current && mFree.popBack(entry))
         {
            Item* prev = current->Prev;

            // setup new node
            entry->Data = data;
            entry->Next = current;
            entry->Prev = prev;

            // link in current
            current->Prev = entry;

            // not inserted at head
            if (prev) 
               prev->Next = entry;
               
            // update head
            else
               mFirst = entry;

            // increment length
            mLength++;

            return true;
         }
         else
            return false;
      }

      //////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Tries to remove and return the last element of the list.
      /// Returns true on success or false if list was empty
      /// Complexity: O(1)
      /// </summary>
      INLINE bool popBack(T& data)
      {
         if (Item* last = mLast)
         {
            // return last data
            data = last->Data;

            // not the only one
            if (Item* prev = last->Prev)
            {
               prev->Next = NULL;
               mLast      = prev;
            }
            else
            {
               mFirst = NULL;
               mLast  = NULL;
            }

            mFree.push(last); // push free node
            mLength--;        // decrement length

            return true;
         }
         else
            return false;
      }

      /// <summary>
      /// Tries to remove and return the first element of the list.
      /// Returns true on success or false if list was empty
      /// Complexity: O(1)
      /// </summary>
      INLINE bool popFront(T& data)
      {
         if (Item* first = mFirst)
         {
            // return first data
            data = first->Data;

            // not the only one
            if (Item* next = first->Next)
            {
               next->Prev = NULL;
               mFirst     = next;
            }
            else
            {
               mFirst = NULL;
               mLast  = NULL;
            }

            mFree.push(first); // push free node
            mLength--;         // decrement length

            return true;
         }
         else
            return false;
      }

      /// <summary>
      /// Tries to remove the first occurrence of data.
      /// Returns how many entries were removed.
      /// Complexity: O(n)
      /// </summary>
      INLINE size_t removeOne(const T& data)
      {
         return remove<false>(data);
      }

      /// <summary>
      /// Tries to remove all occurrences of data.
      /// Returns how many entries were removed.
      /// Complexity: O(n)
      /// </summary>
      INLINE size_t removeAll(const T& data)
      {
         return remove<true>(data);
      }

      /// <summary>
      /// Removes all list entries.
      /// Complexity: O(n)
      /// </summary>
      INLINE void clear()
      {
         Item* current = mFirst;

         // push all nodes to free ones
         while (current)
         {
            mFree.push(current);
            current = current->Next;
         }

         // reset head, end and length
         mFirst  = NULL;
         mLast   = NULL;
         mLength = 0;
      }
   };
}