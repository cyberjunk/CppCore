#pragma once

#include <CppCore/Root.h>

namespace CppCore
{
   /// <summary>
   /// Generic Flags Template.
   /// Semantic sugar around binary flags operations.
   /// </summary>
   template <typename T>
   class Flags
   {
   protected:
      T mFlags;

   public:
      /// <summary>
      /// Static Operations on Flags
      /// </summary>
      class Ops
      {
      private: Ops() { }
      public:
         /// <summary>
         /// Tests if all mask bits are set in flags.
         /// Executes: (flags & mask) == mask
         /// </summary>
         INLINE static bool is(T flags, T mask)
         {
            return (flags & mask) == mask;
         }

         /// <summary>
         /// Returns the bits of mask which are set in flags.
         /// Executes: flags & mask
         /// </summary>
         INLINE static T get(T flags, T mask)
         {
            return (flags & mask);
         }

         /// <summary>
         /// Returns a value in flags stored at mask bits shifted to the right.
         /// Executes: (flags & mask) >> rshift
         /// </summary>
         INLINE static T get(T flags, T mask, T rshift)
         {
            return (flags & mask) >> rshift;
         }

         /// <summary>
         /// Sets bits from mask in flags.
         /// Executes: flags |= mask
         /// </summary>
         INLINE static void set(T& flags, T mask)
         {
            flags |= mask;
         }

         /// <summary>
         /// Calls set() or unset() mask based on bool
         /// </summary>
         INLINE static void set(T& flags, T mask, bool value)
         {
            if (value) set(flags, mask);
            else unset(flags, mask);
         }

         /// <summary>
         /// Unsets bits of mask in flags, shifts value to the left
         /// and sets results in flags.
         /// </summary>
         INLINE static void set(T& flags, T mask, T lshift, T value)
         {
            flags &= ~mask;
            flags |= (value << lshift);
         }

         /// <summary>
         /// Unsets bits of mask in flags.
         /// </summary>
         INLINE static void unset(T& flags, T mask)
         {
            flags &= ~mask;
         }
      };

      INLINE Flags()                              {                   }
      INLINE Flags(T flags) : mFlags(flags)       {                   } 
      INLINE Flags(StdIStream& stream)            { readFrom(stream); }
      INLINE ~Flags()                             {                   }

      INLINE void* ptr()                                { return (void*)&mFlags;                 }
      INLINE T     getFlags()                     const { return mFlags;                         }
      INLINE void  setFlags(T value)                    { mFlags = value;                        }
      INLINE bool  is(T mask)                     const { return Ops::is(mFlags, mask);          }
      INLINE T     get(T mask)                    const { return Ops::get(mFlags, mask);         }
      INLINE T     get(T mask, T rshift)          const { return Ops::get(mFlags, mask, rshift); }
      INLINE void  set(T mask)                          { Ops::set(mFlags, mask);                }
      INLINE void  set(T mask, bool value)              { Ops::set(mFlags, mask, value);         }
      INLINE void  set(T mask, T lshift, T value)       { Ops::set(mFlags, mask, lshift, value); }
      INLINE void  unset(T mask)                        { Ops::unset(mFlags, mask);              }

      INLINE size_t getByteLength()               const { return sizeof(T); }
      INLINE void   readFrom(StdIStream& stream)        { stream.read((char*)ptr(), sizeof(T));  }
      INLINE void   writeTo(StdOStream& stream)   const { stream.write((char*)ptr(), sizeof(T)); }
   };
}
