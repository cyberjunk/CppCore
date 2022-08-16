#include <CppCore/UI/Window.h>

#if defined(CPPCORE_OS_WINDOWS)
LRESULT CALLBACK CppCore::Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   if (uMsg == WM_NCCREATE)
      ::SetWindowLongPtrW(hwnd, 0, reinterpret_cast<LONG_PTR>(
         reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams));

   CppCore::Window* wnd = reinterpret_cast<CppCore::Window*>(
      ::GetWindowLongPtrW(hwnd, 0));

   return (wnd) ? wnd->processEvent(hwnd, uMsg, wParam, lParam) ? 0 : DefWindowProc(hwnd, uMsg, wParam, lParam) :
      DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#elif defined(CPPCORE_OS_OSX) && defined(__OBJC__)
/////////////////////////////////////////////////////////////////////////
// WINDOW
/////////////////////////////////////////////////////////////////////////

/// <summary>
/// OSX WINDOW DELEGATE IMPLEMENTATION
/// </summary>
@implementation WindowDelegate
- (void)windowDidBecomeKey:(NSNotification*)notification
{
   _wnd->onFocusChanged(true);
}

- (void)windowDidBecomeMain : (NSNotification*)notification
{
   // identical to key window for one window cases
   //printf("Window: become main\n");
}

- (void)windowDidResignKey : (NSNotification*)notification
{
   _wnd->onFocusChanged(false);
}

- (void)windowDidResignMain : (NSNotification*)notification
{
   // identical to key window for one window cases
   //printf("Window: resign main\n");
}

- (void)windowDidResize : (NSNotification*)notification
{
   //NSWindow* window = notification.object;
   //printf("Window: resized %f %f \n", window.frame.size.width, window.frame.size.height);
   _wnd->movedOrResized();
}

- (void)windowDidMove : (NSNotification*)notification
{
   //NSWindow* window = notification.object;
   //printf("Window: moved %f %f \n", window.frame.origin.x, window.frame.origin.y);
   _wnd->movedOrResized();
}

- (void)windowWillClose : (NSNotification*)notification
{
   //printf("Window: willClose\n");
   _wnd->destroy();
}
@end

/////////////////////////////////////////////////////////////////////////
// VIEW
/////////////////////////////////////////////////////////////////////////

/// <summary>
/// Custom View Implementation
/// </summary>
@implementation View

- (BOOL)acceptsFirstResponder {
   return YES;
}

// make top-left and not bottom left the origin
- (BOOL)isFlipped {
   return YES;
}

// trigger a real mouse click on a focus in click
- (BOOL)acceptsFirstMouse {
   return YES;
}

- (BOOL)wantsBestResolutionOpenGLSurface {
   // if this is YES you may end up with twice as many pixels
   // as the window has in some rendering engines...
   return NO;
}
/////////////////////////////////////////////////////////////////////////
// MOUSE
/////////////////////////////////////////////////////////////////////////

// LEFT MOUSE DOWN
- (void)mouseDown:(NSEvent*)theEvent {
   //printf("VIEW LEFTMOUSEDOWN %i\n", theEvent.buttonNumber);
   _wnd->onMouseDown(CppCore::Input::MouseButton::Enum::LeftButton);
}

// RIGHT MOUSE DOWN
- (void)rightMouseDown:(NSEvent*)theEvent {
   //printf("VIEW RIGHTMOUSEDOWN %i\n", theEvent.buttonNumber);
   _wnd->onMouseDown(CppCore::Input::MouseButton::Enum::RightButton);
}

// OTHER MOUSE DOWN
- (void)otherMouseDown:(NSEvent*)theEvent {
   //printf("VIEW OTHERMOUSEDOWN %i\n", theEvent.buttonNumber);
   _wnd->onMouseDown(CppCore::Input::MouseButton::Enum::MiddleButton);
}

// LEFT MOUSE UP
- (void)mouseUp:(NSEvent*)theEvent {
   //printf("VIEW LEFTMOUSEUP %i\n", theEvent.buttonNumber);
   _wnd->onMouseUp(CppCore::Input::MouseButton::Enum::LeftButton);
}

// RIGHT MOUSE UP
- (void)rightMouseUp:(NSEvent*)theEvent {
   //printf("VIEW RIGHTMOUSEUP %i\n", theEvent.buttonNumber);
   _wnd->onMouseUp(CppCore::Input::MouseButton::Enum::RightButton);
}

// OTHER MOUSE UP
- (void)otherMouseUp:(NSEvent*)theEvent {
   //printf("VIEW OTHERMOUSEUP %i\n", theEvent.buttonNumber);
   _wnd->onMouseUp(CppCore::Input::MouseButton::Enum::MiddleButton);
}

// MOUSE WHEEL
- (void)scrollWheel:(NSEvent*)theEvent {
   //printf("VIEW MOUSEWHEEL %i\n", theEvent.deltaY);
   _wnd->onMouseWheel(theEvent.deltaY * CPPCORE_WINDOW_SCALE_WHEEL_OSX);
}

// LEFT MOUSE DRAGGED
- (void)mouseDragged:(NSEvent*)theEvent {
   NSPoint p = [theEvent locationInWindow];
   p = [self convertPoint : p fromView : nil];
   //printf("VIEW LEFTMOUSEDRAGGED %i\n", theEvent.buttonNumber);
   _wnd->onMouseMove(CppCore::V2i(p.x, p.y));
}

// RIGHT MOUSE DRAGGED
- (void)rightMouseDragged:(NSEvent*)theEvent {
   NSPoint p = [theEvent locationInWindow];
   p = [self convertPoint : p fromView : nil];
   //printf("VIEW RIGHTMOUSEDRAGGED %i\n", theEvent.buttonNumber);
   _wnd->onMouseMove(CppCore::V2i(p.x, p.y));
}

// OTHER MOUSE DRAGGED
- (void)otherMouseDragged:(NSEvent*)theEvent {
   NSPoint p = [theEvent locationInWindow];
   p = [self convertPoint : p fromView : nil];
   //printf("VIEW OTHERMOUSEDRAGGED %i\n", theEvent.buttonNumber);
   _wnd->onMouseMove(CppCore::V2i(p.x, p.y));
}

// MOUSE MOVED
- (void)mouseMoved:(NSEvent*)theEvent {
   NSPoint p = [theEvent locationInWindow];
   p = [self convertPoint : p fromView : nil];
   //printf("VIEW MOUSEMOVED %f %f \n", p.x, p.y);
   _wnd->onMouseMove(CppCore::V2i(p.x, p.y));
}

// MOUSE ENTERED
- (void)mouseEntered:(NSEvent*)theEvent {
   //NSPoint p = [theEvent locationInWindow];
   //p = [self convertPoint : p fromView : nil];
   //printf("VIEW MOUSE ENTERED %f %f \n", p.x, p.y);
   _wnd->onMouseEnter();
}

// MOUSE LEFT
- (void)mouseExited:(NSEvent*)theEvent {
   //NSPoint p = [theEvent locationInWindow];
   //p = [self convertPoint : p fromView : nil];
   //printf("VIEW MOUSE EXITED %f %f \n", p.x, p.y);
   _wnd->onMouseLeave();
}

/////////////////////////////////////////////////////////////////////////
// KEYBOARD
/////////////////////////////////////////////////////////////////////////

// KEY DOWN
-(void)keyDown:(NSEvent*)theEvent {
   //printf("VIEW KEYDOWN %i\n", theEvent.keyCode);
   _wnd->onKeyDown(
      CppCore::Input::Key::fromAppleKeyCode((uint8_t)theEvent.keyCode));
   if (theEvent.characters.length > 0)
   {
      UTF32Char c;
      if ([theEvent.characters getBytes : &c 
            maxLength : 4 
            usedLength : NULL 
            encoding : NSUTF32LittleEndianStringEncoding 
            options : 0 
            range : NSMakeRange(0, 1)
            remainingRange : NULL])
      {
         c = NSSwapLittleIntToHost(c);
         _wnd->onChar(c);
      }
   }
}

// KEY UP
- (void)keyUp : (NSEvent*)theEvent {
   //printf("VIEW KEYUP %i\n", theEvent.keyCode);
   _wnd->onKeyUp(
      CppCore::Input::Key::fromAppleKeyCode((uint8_t)theEvent.keyCode));
}

// FLAGS CHANGED
- (void)flagsChanged : (NSEvent*)theEvent {
   //printf("VIEW FLAGSCHANGED %i %i\n", theEvent.keyCode, theEvent.modifierFlags);

   /*if (theEvent.modifierFlags & NSEventModifierFlagShift)
   {
      printf("SHIFT\n");
   }*/
   //_wnd->onKeyUp(
   //   CppCore::Input::Key::fromAppleKeyCode((uint8_t)theEvent.keyCode));
}
@end

#elif defined(CPPCORE_OS_LINUX)
#endif
