#pragma once

#include <CppCore/Root.h>

namespace CppCore
{
   /// <summary>
   /// Iterator Base Class
   /// </summary>
   template<typename T, bool REVERSE>
   class ItB
   {
   protected:
      T* p;
   public:
      INLINE ItB(T* x) : p(x) { }
      INLINE bool operator==(const ItB& x) const { return p == x.p;   }
      INLINE bool operator!=(const ItB& x) const { return p != x.p;   }
   };

   /// <summary>
   /// Constant Iterator Class
   /// </summary>
   template<typename T, bool REVERSE>
   class ItC : public ItB<T, REVERSE>
   {
   public:
      INLINE ItC(T* x) : ItB<T, REVERSE>(x) { }
      INLINE ItC& operator++() { this->p = REVERSE ? this->p-1U : this->p+1U; return *this; }
      INLINE ItC& operator--() { this->p = REVERSE ? this->p+1U : this->p-1U; return *this; }
      INLINE const T& operator*() const { return *this->p; }
   };

   /// <summary>
   /// Iterator Class
   /// </summary>
   template<typename T, bool REVERSE>
   class ItD : public ItB<T, REVERSE>
   {
   public:
      INLINE ItD(T* x) : ItB<T, REVERSE>(x) { }
      INLINE ItD& operator++() { this->p = REVERSE ? this->p-1U : this->p+1U; return *this; }
      INLINE ItD& operator--() { this->p = REVERSE ? this->p+1U : this->p-1U; return *this; }
      INLINE T& operator*() { return *this->p; }
   };
}
