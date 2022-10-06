#pragma once

#include <CppCore/Application.h> // the base class
#include <CppCore/UI/Window.h>   // base window class
#include "Input.h"               // own input

namespace CppCore { namespace Example 
{
   /// <summary>
   /// Example UI Application
   /// </summary>
   class Application :
      public CppCore::Application<Application>,
      public CppCore::Window::Callback
   {
      /// <summary>
      /// Application Base Class
      /// </summary>
      using Base = CppCore::Application<Application>;

   protected:
      Window    mWindow;
      TestInput mInput;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Application() : 
         Base(true, true, "CppCore.Example.UI"),
         mWindow(*this),
         mInput() { }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~Application() { }

      /// <summary>
      /// Gets the Application window
      /// </summary>
      INLINE Window& getWindow() { return mWindow; }

      /// <summary>
      /// Post Constructor Initialization
      /// </summary>
      INLINE void init(int argc, char* argv[]) override 
      {
         // init window
         mWindow.setTitle("Test Window");
         mWindow.setWindowPosition(CppCore::V2i(100, 100));
         mWindow.setClientSize(CppCore::V2i(800, 800));
         mWindow.setCustomCursor(true);
         mWindow.create();
      }

      /// <summary>
      /// Message Pump on Application Level
      /// </summary>
      INLINE virtual size_t messagePump() override
      {
         size_t num = 0;
         num += Base::messagePump();
         num += mWindow.messagePump();
         return num;
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////
      // Window Callback
      ////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE void onCreating() override
      {
         this->log("WINDOW Creating");
      }
      INLINE void onCreated() override
      {
         this->log("WINDOW Created");
      }
      INLINE void onDestroying() override
      {
         this->log("WINDOW Destroying");
      }
      INLINE void onDestroyed() override
      {
         this->log("WINDOW Destroyed");
         this->setIsRunning(false); // stop
      }
      INLINE void onFocusChanged(bool focused) override
      {
         if (focused) this->log("WINDOW Focus Gained");
         else this->log("WINDOW Focus Lost");
      }
      INLINE void onClientAreaChanged(bool forced, const CppCore::BBox2i& area) override
      {
         this->log("WINDOW Client Area changed: " +
            std::to_string(forced) + " " +
            std::to_string(area.min.x) + " " +
            std::to_string(area.min.y) + " " +
            std::to_string(area.max.x) + " " +
            std::to_string(area.max.y));
         mInput.setMouseArea(area); // apply on input
      }
      INLINE void onWindowAreaChanged(bool forced, const CppCore::BBox2i& area) override
      {
         this->log("WINDOW Window Area changed: " +
            std::to_string(forced) + " " +
            std::to_string(area.min.x) + " " +
            std::to_string(area.min.y) + " " +
            std::to_string(area.max.x) + " " +
            std::to_string(area.max.y));
      }
      ////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE void onMouseMove(const CppCore::V2i& p) override
      {
         //printf("WINDOW Mouse Move (%i, %i)\n", p.x, p.y);
         mInput.injectMousePosition(p);
      }
      INLINE void onMouseEnter() override
      {
         //printf("WINDOW  Mouse Entered Client Area\n");
         // no inject - input has its own area and tracks it (for now?)
      }
      INLINE void onMouseLeave() override
      {
         //printf("WINDOW Mouse Left Client Area\n");
         // no inject - input has its own area and tracks it (for now?)
      }
      INLINE void onMouseDown(CppCore::Input::MouseButton::Enum b) override
      {
         //printf("WINDOW Mouse Button down: %i \n", (int32_t)b);
         mInput.injectMouseButtonDown(b);
      }
      INLINE void onMouseUp(CppCore::Input::MouseButton::Enum b) override
      {
         //printf("WINDOW Mouse Button up: %i \n", (int32_t)b);
         mInput.injectMouseButtonUp(b);
      }
      INLINE void onMouseWheel(int32_t delta) override
      {
         //printf("WINDOW Mouse Wheel: %i \n", (int32_t)delta);
         mInput.injectMouseWheelChange(delta);
      }
      ////////////////////////////////////////////////////////////////////////////////////////////////
      INLINE void onKeyDown(CppCore::Input::Key::Enum k) override
      {
         //printf("WINDOW Key Down: %i \n", (int32_t)k);
         mInput.injectKeyDown(k);
      }
      INLINE void onKeyUp(CppCore::Input::Key::Enum k) override
      {
         //printf("WINDOW Key Up: %i \n", (int32_t)k);
         mInput.injectKeyUp(k);
      }
      INLINE void onChar(uint32_t c) override
      {
         //printf("WINDOW CHAR: Int: %i  Char: %s \n", c, (char*)&c);
         mInput.injectChar(c);
      }
   };
}}
