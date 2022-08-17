#pragma once

#include <CppCore/Root.h>

namespace CppCore
{
   /// <summary>
   /// Checks if 'str' starts with 'match'.
   /// </summary>
   template<bool CASESENSITIVE = false>
   INLINE bool startsWith(const string& str, const string& match)
   {
      // get lengths
      const size_t LENS = str.length();
      const size_t LENM = match.length();

      // match must be smaller or equal to str
      if (LENM <= LENS)
      {
         // compare characters
         for (size_t i = 0; i < LENM; i++)
         {
            if (CASESENSITIVE)
            {
               if (str[i] != match[i])
                  return false;
            }
            else
            {
               if (::tolower(str[i]) != ::tolower(match[i]))
                  return false;
            }
         }

         // match
         return true;
      }

      // match is larger than str
      // hence str can not start with match
      else
         return false;
   }
}
