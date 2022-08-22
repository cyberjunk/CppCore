#pragma once

#include <CppCore/UI/Input.h> // the base class

namespace CppCore { namespace Example 
{
   /// <summary>
   /// Example Input Class
   /// </summary>
   class TestInput : public CppCore::Input
   {
   public:
      INLINE void onKeyChanged(const Key::Enum k, const bool down) override
      {
         printf("INPUT Key Change: %i %i\n", (int32_t)k, (int32_t)down);
      }
      INLINE void onCharacter(const uint32_t c) override
      {
         printf("INPUT Char: Int %i Char %c\n", (int32_t)c, (char)c);
      }
      INLINE void onMouseButtonChanged(const MouseButton::Enum b, const bool down) override
      {
         printf("INPUT Mouse Button %i %i \n", (int32_t)b, (int32_t)down);
      }
      INLINE void onMouseWheel(const int32_t delta) override
      {
         printf("INPUT Mouse Wheel: %i\n", delta);
      }
      INLINE void onMouseMove(const CppCore::V2i& p) override
      {
         printf("INPUT: Mouse Move (%i, %i)\n", p.x, p.y);
      }
      INLINE void onMouseEnter() override
      {
         printf("INPUT: Mouse Enter\n");
      }
      INLINE void onMouseLeave() override
      {
         printf("INPUT: Mouse Leave\n");
      }
   };
}}
