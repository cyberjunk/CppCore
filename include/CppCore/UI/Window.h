#pragma once

#include <CppCore/Root.h>
#include <CppCore/Math/BBox2.h>
#include <CppCore/UI/Input.h>

#if defined(CPPCORE_OS_LINUX)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#undef Status
#undef None
#undef Bool
#elif defined(CPPCORE_OS_OSX) && defined(__OBJC__)
#include <Cocoa/Cocoa.h>
#endif

#define CPPCORE_WINDOW_SCALE_WHEEL_OSX   120
#define CPPCORE_WINDOW_SCALE_WHEEL_LINUX 120

// FORWARD DECLARATION
namespace CppCore {
   class Window;
}

#if defined(CPPCORE_OS_OSX) && defined(__OBJC__)
/// <summary>
/// Custom NSWindowDelegate
/// </summary>
@interface WindowDelegate : NSObject <NSWindowDelegate>
@property CppCore::Window* wnd;
@end

/// <summary>
/// Custom NSView
/// </summary>
@interface View : NSView
@property CppCore::Window* wnd;
@end
#endif

namespace CppCore
{
   /// <summary>
   /// Simple Window Wrapper.
   /// </summary>
   class Window
   {
   public:
      /// <summary>
      /// Window Callback
      /// </summary>
      class Callback
      {
      public:
         INLINE virtual void onCreating()                                             { }
         INLINE virtual void onCreated()                                              { }
         INLINE virtual void onDestroying()                                           { }
         INLINE virtual void onDestroyed()                                            { }
         INLINE virtual void onFocusChanged(bool focused)                             { }
         INLINE virtual void onClientAreaChanged(bool forced, const BBox2i& area)     { }
         INLINE virtual void onWindowAreaChanged(bool forced, const BBox2i& area)     { }
         INLINE virtual void onMouseMove(const V2i& p)                                { }
         INLINE virtual void onMouseEnter()                                           { }
         INLINE virtual void onMouseLeave()                                           { }
         INLINE virtual void onMouseDown(Input::MouseButton::Enum b)                  { }
         INLINE virtual void onMouseUp(Input::MouseButton::Enum b)                    { }
         INLINE virtual void onMouseWheel(int32_t delta)                              { }
         INLINE virtual void onKeyDown(Input::Key::Enum k)                            { }
         INLINE virtual void onKeyUp(Input::Key::Enum k)                              { }
         INLINE virtual void onChar(uint32_t c)                                       { }
      };

   protected:
      Callback&           mCallback;
      std::string         mTitle;
      BBox2i              mWindowArea;
      BBox2i              mClientArea;
   #if defined(CPPCORE_OS_WINDOWS)
      HWND                mWindow;
      RECT                mRect;
      TRACKMOUSEEVENT     mTME;
   #elif defined(CPPCORE_OS_LINUX)
      ::Display*          mDisplay;
      ::Window            mWindow;
      ::Window            mParent;
      ::XWindowAttributes mWindowAttribs;
      ::Atom              mWindowDelete;
      long                mEventMask;
   #elif defined(CPPCORE_OS_OSX) && defined(__OBJC__)
      NSWindow*           mWindow;
      View*               mView;
   #endif
      bool                mFocus;
      bool                mShow;
      bool                mMouseInWindow;
      bool                mCustomCursor;
      bool                mCursorVisible;

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Window(Callback& callback) :
         mCallback(callback),
         mTitle(""),
         mWindowArea(V2i(0), V2i(256, 256)),
         mClientArea(V2i(0), V2i(0)),
      #if defined(CPPCORE_OS_WINDOWS)
         mWindow(0),
         mRect(),
         mTME(),
      #elif defined(CPPCORE_OS_LINUX)
         mDisplay(0),
         mWindow(0),
         mParent(0),
         mWindowAttribs(),
         mEventMask(
            PointerMotionMask |                                      // MOUSEMOVE
            ButtonMotionMask | ButtonPressMask | ButtonReleaseMask | // MOUSE BUTTON
            EnterWindowMask | LeaveWindowMask |                      // MOUSE ENTER/LEAVE ?
            FocusChangeMask |                                        // FOCUS CHANGE
            KeyPressMask | KeyReleaseMask | KeymapStateMask |        // KEYBOARD
            VisibilityChangeMask |                                   // VISIBILITY
            ExposureMask |
            StructureNotifyMask |                                    // MOVE/RESIZE/DESTROY
            VisibilityChangeMask),
      #elif defined(CPPCORE_OS_OSX) && defined(__OBJC__)
         mWindow(0),
         mView(0),
      #endif
         mFocus(false),
         mShow(false),
         mMouseInWindow(false),
         mCustomCursor(false),
         mCursorVisible(true)
      {
      #if defined(CPPCORE_OS_WINDOWS)
         mTME.cbSize = sizeof(TRACKMOUSEEVENT);
         mTME.dwFlags = TME_HOVER | TME_LEAVE;
         mTME.dwHoverTime = 1;
      #elif defined(CPPCORE_OS_LINUX)

      #endif
      }

      /// <summary>
      /// Destructor
      /// </summary>
      INLINE ~Window()
      {
         destroy();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns the area of the window in absolute coordinates on the screen.
      /// This includes the window title bar etc.
      /// </summary>
      INLINE const BBox2i& getWindowArea() const
      {
         return mWindowArea;
      }

      /// <summary>
      /// Returns the client area within the window in relative window coordinates.
      /// </summary>
      INLINE const BBox2i& getClientArea() const
      {
         return mClientArea;
      }

      /// <summary>
      /// True if the windows has focus
      /// </summary>
      INLINE bool hasFocus() const
      {
         return mFocus;
      }

      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns the title of the window
      /// </summary>
      INLINE const std::string& getTitle() const
      {
         return mTitle;
      }

      /// <summary>
      /// Sets the title of the window
      /// </summary>
      INLINE void setTitle(const char* title)
      {
         mTitle = title;
      #if defined(CPPCORE_OS_WINDOWS)
         if (mWindow)
            ::SetWindowTextA(mWindow, title);
      #elif defined(CPPCORE_OS_LINUX)
         if (mDisplay && mWindow)
            ::XStoreName(mDisplay, mWindow, title);
      #elif defined(CPPCORE_OS_OSX)
         if (mWindow)
         {
            [mWindow setTitle : [
               NSString stringWithCString : mTitle.c_str() 
               encoding : [NSString defaultCStringEncoding]]];
         }
      #endif
      }

      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// True if a custom mouse cursor is rendered and the default one 
      /// from Operating System should be hidden while focused and inside.
      /// </summary>
      INLINE bool hasCustomCursor() const
      {
         return mCustomCursor;
      }

      /// <summary>
      /// Set this to true if a custom mouse cursor is rendered and the default one 
      /// from Operating System should be hidden while focused and inside.
      /// </summary>
      INLINE void setCustomCursor(bool enabled)
      {
         mCustomCursor = enabled;
         // todo apply it
      }

      /// <summary>
      /// Shows or hides the Operating System mouse cursor.
      /// Don't call explicitly if using setCustomCursor() also.
      /// </summary>
      INLINE void setCursorVisible(bool visible)
      {
         if (visible != mCursorVisible)
         {
            mCursorVisible = visible;
         #if defined(CPPCORE_OS_WINDOWS)
            ShowCursor(visible);
         #elif defined(CPPCORE_OS_LINUX)
         #endif
         }
      }

      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns the size of the window
      /// </summary>
      INLINE V2i getWindowSize() const 
      {
         return mWindowArea.size();
      }

      /// <summary>
      /// Returns the position of the top-left corner of the window
      /// in absolute coordinates on the screen.
      /// </summary>
      INLINE const V2i& getWindowPosition() const 
      {
         return mWindowArea.min;
      }

      /// <summary>
      /// Sets the position of the top-left corner of the outer window
      /// in absolute coordinates on the screen.
      /// </summary>
      INLINE void setWindowPosition(const V2i& position)
      {
         V2i translate = position - mWindowArea.min;
         mWindowArea.min = position;
         mWindowArea.max += translate;
      #if defined(CPPCORE_OS_WINDOWS)
         if (mWindow)
         {
            const V2i& size = mWindowArea.size();
            ::MoveWindow(mWindow, mWindowArea.min.x, mWindowArea.min.y, size.x, size.y, true);
         }
      #elif defined(CPPCORE_OS_LINUX)
         if (mDisplay && mWindow)
         {
            if (mParent && mParent != XDefaultRootWindow(mDisplay))
               ::XMoveWindow(mDisplay, mParent, position.x, position.y);
            else
               ::XMoveWindow(mDisplay, mWindow, position.x, position.y);
         }
      #elif defined(CPPCORE_OS_OSX)
         if (mWindow)
         {
            /*NSRect screenRect = [[NSScreen mainScreen]frame];
            NSPoint pos;
            pos.x = position.x;
            pos.y = screenRect.size.height - position.y;
            [mWindow setFrameTopLeftPoint : pos] ;*/
         }
      #endif
      }

      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns the size of the inner client area
      /// </summary>
      INLINE V2i getClientSize() const
      {
         return mClientArea.size();
      }

      /// <summary>
      /// Sets the inner client size of the window.
      /// The resulting outter full window may get lager than this.
      /// </summary>
      INLINE void setClientSize(const V2i& size)
      {
         mClientArea.max = mClientArea.min + size;
      #if defined(CPPCORE_OS_WINDOWS)
         if (mWindow)
         {
            // convert to win rect
            mRect = mClientArea;

            // gives outter window area from
            // requested inner client area
            ::AdjustWindowRect(&mRect, 
               ::GetWindowLong(mWindow, GWL_STYLE), false);

            // store in own format
            mWindowArea = mRect;

            // resize outter to achieve inner
            setWindowSize(mWindowArea.size());
         }
      #elif defined(CPPCORE_OS_LINUX)
         if (mDisplay && mWindow)
            ::XResizeWindow(mDisplay, mWindow, size.x, size.y);
      #endif
      }

      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Updates the current window area and its
      /// inner client area from operating system.
      /// </summary>
      INLINE void movedOrResized(bool forceEvent = false)
      {
         const BBox2i oldClientArea(mClientArea);
         const BBox2i oldWindowArea(mWindowArea);

      #if defined(CPPCORE_OS_WINDOWS)
         if (mWindow)
         {
            // inner area of the window (relative, min always at 0,0)
            if (::GetClientRect(mWindow, &mRect))
               mClientArea = mRect;

            // full area of the window (absolute screen coords)
            if (::GetWindowRect(mWindow, &mRect))
               mWindowArea = mRect;
         }
      #elif defined(CPPCORE_OS_LINUX)
         if (mDisplay && mWindow)
         {
            // inner client area (topleft relative to window topleft)
            if (::XGetWindowAttributes(mDisplay, mWindow, &mWindowAttribs))
            {
               // update to new values
               mClientArea.min.x = mWindowAttribs.x;
               mClientArea.min.y = mWindowAttribs.y;
               mClientArea.max.x = mWindowAttribs.x + mWindowAttribs.width;
               mClientArea.max.y = mWindowAttribs.y + mWindowAttribs.height;

               // translate client area to (0,0) like on windows
               mClientArea += -mClientArea.min;
            }

            // make sure we got latest parent
            updateParent();

            // outter window area (absolute screen cords)
            ::Window  wnd;
            uint32_t  width, height, border, depth;

            // parent is root (this may be the case at the beginning even with WM)
            if (mParent == XDefaultRootWindow(mDisplay))
            {
               ::XGetGeometry(mDisplay, mWindow, &wnd,
                  &mWindowArea.min.x,
                  &mWindowArea.min.y,
                  &width,
                  &height,
                  &border,
                  &depth);
               mWindowArea.max = mWindowArea.min + V2i((int32_t)width, (int32_t)height);
            }
            // parent is not root but decoration window of WM
            else
            {
               ::XGetGeometry(mDisplay, mParent, &wnd,
                  &mWindowArea.min.x,
                  &mWindowArea.min.y,
                  &width,
                  &height,
                  &border,
                  &depth);
               mWindowArea.max = mWindowArea.min + V2i((int32_t)width, (int32_t)height);
            }
         }
      #elif defined(CPPCORE_OS_OSX)
         if (mWindow && mView)
         {
            // window area
            mWindowArea.min.x = mWindow.frame.origin.x;
            mWindowArea.min.y = mWindow.frame.origin.y;
            mWindowArea.max   = mWindowArea.min + V2i(mWindow.frame.size.width, mWindow.frame.size.height);

            // client/view area
            mClientArea.min.x = mView.frame.origin.x;
            mClientArea.min.y = mView.frame.origin.y;
            mClientArea.max.x = mClientArea.min.x + mView.frame.size.width;
            mClientArea.max.y = mClientArea.min.y + mView.frame.size.height;
      }
      #endif

         //printf("WIND: %i %i %i %i\n", mWindowArea.min.x, mWindowArea.min.y, mWindowArea.max.x, mWindowArea.max.y);
         //printf("CLNT: %i %i %i %i\n", mClientArea.min.x, mClientArea.min.y, mClientArea.max.x, mClientArea.max.y);

         // client area changed
         const bool changedClientArea = mClientArea != oldClientArea;
         if (forceEvent || changedClientArea)
            onClientAreaChanged(forceEvent, mClientArea);

         // window area changed
         const bool changedWindowArea = mWindowArea != oldWindowArea;
         if (forceEvent || changedWindowArea)
            onWindowAreaChanged(forceEvent, mWindowArea);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Dispatches/processes pending messages/events in the Window Manager Event Queue.
      /// Returns amount of processed messages/events.
      /// </summary>
      INLINE size_t messagePump()
      {
         size_t i = 0;
      #if defined(CPPCORE_OS_WINDOWS)
         MSG msg;
         while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
         {
            i++;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            // continues in WndProc
         }
      #elif defined(CPPCORE_OS_LINUX)
         XEvent msg;
         while (mDisplay && mWindow && XCheckWindowEvent(mDisplay, mWindow, mEventMask , &msg))
         {
            i++;
            processEvent(msg);
         }
         while (mDisplay && mWindow && XCheckTypedWindowEvent(mDisplay, mWindow, ClientMessage, &msg))
         {
            i++;
            processEvent(msg);
         }
      #elif defined(CPPCORE_OS_OSX) && defined(__OBJC__)
         // happens on Application level, e.g. (NSApp nextEventMatchingMask)
      #endif
         return i;
      }

#if defined(CPPCORE_OS_WINDOWS)
      /////////////////////////////////////////////////////////////////////////////////////////////
      // WINDOWS ONLY
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns Platform Window Handle
      /// </summary>
      INLINE HWND getWindow() const { return mWindow; }

      /// <summary>
      /// Returns Handle to Render Element
      /// </summary>
      INLINE size_t getRenderHandle() const { return (size_t)mWindow; }

      /// <summary>
      /// The WndProc. Fed with messages from the Queue in DispatchMessage().
      /// You MUST implement this in your deriving class cpp file.
      /// </summary>
      static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

      /// <summary>
      /// Create the Window (WINDOWS)
      /// </summary>
      INLINE bool create(HINSTANCE hinstance = GetModuleHandle(0), int cmdshow = SW_SHOW)
      {
         // already created
         if (mWindow)
            return false;

         // event at start
         onCreating();

         // Create Window Class
         WNDCLASS wc = { };
         wc.lpfnWndProc = WindowProc;
         wc.hInstance = hinstance;
         wc.lpszClassName = mTitle.c_str();
         wc.hCursor = LoadCursor(NULL, IDC_ARROW);
         wc.hIcon = LoadIcon(hinstance, IDI_APPLICATION);
         wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
         wc.cbWndExtra = sizeof(Window*);
         //wc.style = CS_DBLCLKS; // <-- disabled for CEGUI, see WM_MESSAGE handler
         //wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
         //wc.cbClsExtra = 0;
         //wc.lpszMenuName = NULL;
         RegisterClass(&wc);

         // used styles, also needed to calculate actual outter window dimensions
         const DWORD wndstyles = WS_OVERLAPPEDWINDOW;
         const DWORD optstyles = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

         // remember user set window position
         V2i  wpos = mWindowArea.min;
         RECT rect = mClientArea;

         // gives outter window area from
         // requested inner client area
         ::AdjustWindowRect(&rect, wndstyles | optstyles, false);

         // save calculated window size at old position
         mWindowArea  = rect;
         mWindowArea += wpos;

         // size
         const V2i& size = mWindowArea.size();

         // create window with calculated outter dimensions
         mWindow = CreateWindowEx(
            optstyles,         // Optional window styles.
            wc.lpszClassName,  // Window class
            mTitle.c_str(),    // Window text
            wndstyles,         // Main Window styles

            // Size and position
            mWindowArea.min.x, mWindowArea.min.y, size.x, size.y,

            NULL,       // Parent window
            NULL,       // Menu
            hinstance,  // Instance handle
            static_cast<LPVOID>(this) // Additional application data
         );

         // set window to mousetracking
         mTME.hwndTrack = mWindow;

         // show window
         // continue in WM_SHOWWINDOW event when constructed/visible
         ShowWindow(mWindow, cmdshow);
         return true;
      }

      /// <summary>
      /// Sets the size of the outter window itself (includes titlebar etc).
      /// The resulting inner client area might be smaller than this.
      /// Works only on Windows.
      /// </summary>
      INLINE void setWindowSize(const V2i& size)
      {
         mWindowArea.max = mWindowArea.min + size;
         if (mWindow)
            ::MoveWindow(mWindow, mWindowArea.min.x, mWindowArea.min.y, size.x, size.y, true);
      }

      /// <summary>
      /// Process a WM_MESSAGE. Call this from your WNDPROC.
      /// Returns True if the WM_MESSAGE was handled.
      /// </summary>
      INLINE bool processEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
      {
         if (!mWindow || hwnd != mWindow)
            return false;

         switch (uMsg)
         {
         //////////////////////////////////////////////////////////////////////////////////
         // WINDOW
         //////////////////////////////////////////////////////////////////////////////////

         // SHOW
         case WM_SHOWWINDOW:
            if (lParam == 0)
            {
               mShow = true;
               movedOrResized(true);
               onCreated();
            }
            return true;

         // MOVED OR RESIZED
         case WM_SIZE:
         case WM_MOVE:
            if (mShow)
               movedOrResized();
            return true;

         // FOCUS LOST OR GAINED
         case WM_ACTIVATE:
            if (LOWORD(wParam) == WA_ACTIVE || LOWORD(wParam) == WA_CLICKACTIVE)
            {
               if (!mFocus)
               {
                  mFocus = true;
                  onFocusChanged(true);
               }
            }
            else if (LOWORD(wParam) == WA_INACTIVE)
            {
               if (mFocus)
               {
                  mFocus = false;
                  setCursorVisible(true);
                  onFocusChanged(false);
               }
            }
            return true;

         // CLOSE REQUESTED
         case WM_CLOSE:
            destroy();
            return true;

         //////////////////////////////////////////////////////////////////////////////////
         // MOUSE
         //////////////////////////////////////////////////////////////////////////////////

         // MOUSE MOVE
         case WM_MOUSEMOVE:
            if (!mMouseInWindow)
            {
               TrackMouseEvent(&mTME);
               mMouseInWindow = true;
               onMouseEnter();
            }
            if (mFocus && mCustomCursor)
               setCursorVisible(false);
            onMouseMove(V2i(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            return true;

         // WM_MOUSEENTER DOES NOT EXIST, SEE ABOVE

         // MOUSE LEAVE
         case WM_MOUSELEAVE:
            mMouseInWindow = false;
            setCursorVisible(true);
            onMouseLeave();
            return true;

         // MOUSE DOWN
         case WM_LBUTTONDOWN: onMouseDown(Input::MouseButton::LeftButton);   return true;
         case WM_RBUTTONDOWN: onMouseDown(Input::MouseButton::RightButton);  return true;
         case WM_MBUTTONDOWN: onMouseDown(Input::MouseButton::MiddleButton); return true;
         case WM_XBUTTONDOWN:
         {
            const auto button = GET_XBUTTON_WPARAM(wParam);
            if      (button == XBUTTON1) onMouseDown(Input::MouseButton::X1Button);
            else if (button == XBUTTON2) onMouseDown(Input::MouseButton::X2Button);
            else                         onMouseDown(Input::MouseButton::Unknown);
            return true;
         }

         // MOUSE UP
         case WM_LBUTTONUP: onMouseUp(Input::MouseButton::LeftButton);   return true;;
         case WM_RBUTTONUP: onMouseUp(Input::MouseButton::RightButton);  return true;;
         case WM_MBUTTONUP: onMouseUp(Input::MouseButton::MiddleButton); return true;;
         case WM_XBUTTONUP:
         {
            const auto button = GET_XBUTTON_WPARAM(wParam);
            if      (button == XBUTTON1) onMouseUp(Input::MouseButton::X1Button);
            else if (button == XBUTTON2) onMouseUp(Input::MouseButton::X2Button);
            else                         onMouseUp(Input::MouseButton::Unknown);
            return true;
         }

         // MOUSE WHEEL
         case WM_MOUSEWHEEL:
         {
            const auto zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
            onMouseWheel(zDelta);
            return true;
         }

         //////////////////////////////////////////////////////////////////////////////////
         // KEYBOARD
         //////////////////////////////////////////////////////////////////////////////////

         // KEY DOWN
         case WM_KEYDOWN:
         case WM_SYSKEYDOWN: 
            onKeyDown(Input::Key::fromWindowsMessage(wParam, lParam));
            return true;

         // KEY UP
         case WM_KEYUP:
         case WM_SYSKEYUP:
            onKeyUp(Input::Key::fromWindowsMessage(wParam, lParam));
            return true;

         // CHAR KEY PRESSED
         case WM_CHAR:
            // TODO: wParam is UTF-16. The ones larger 0xffff (aka. surrogated?)
            // would need special handling here to become valid UTF-32.
            onChar((uint32_t)wParam);
            return true;

         //////////////////////////////////////////////////////////////////////////////////
         default: return false;
         }
      }

#elif defined(CPPCORE_OS_LINUX)
      /////////////////////////////////////////////////////////////////////////////////////////////
      // LINUX ONLY
      /////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns Platform Display Handle
      /// </summary>
      INLINE ::Display* getDisplay() const { return mDisplay; }

      /// <summary>
      /// Returns Platform Window Handle
      /// </summary>
      INLINE ::Window getWindow() const { return mWindow; }

      /// <summary>
      /// Returns Handle to Render Element
      /// </summary>
      INLINE size_t getRenderHandle() const { return (size_t)mWindow; }

      /// <summary>
      /// Returns Eventmask
      /// </summary>
      INLINE long getEventMask() const { return mEventMask; }

      /// <summary>
      /// Refreshes the reference to the parent
      /// </summary>
      INLINE void updateParent()
      {
         if (mDisplay && mWindow)
         {
            ::Window  rootwnd     = 0;
            ::Window* children    = 0;
            uint32_t  numchildren = 0;
            ::XQueryTree(mDisplay, mWindow, &rootwnd, &mParent, &children, &numchildren);
            if (children)
               XFree(children);
         }
      }

      /// <summary>
      /// Create the Window (LINUX)
      /// </summary>
      INLINE bool create()
      {
         if (mWindow)
            return false;

         onCreating();
         if (!mDisplay)
         {
            mDisplay = XOpenDisplay(0);
            if (!mDisplay)
               return false;
         }

         // get current inner client size
         const V2i& size = mClientArea.size();

         // todo: just assume the max for now
         // there is nothing like AdjustWindowRect() 
         // to calculate outter size on X11
         mWindowArea.max = mWindowArea.min + size;

         // create window
         mWindow = XCreateSimpleWindow(
            mDisplay,
            DefaultRootWindow(mDisplay),
            mWindowArea.min.x, mWindowArea.min.y,
            size.x, size.y, 1,
            BlackPixel(mDisplay, DefaultScreen(mDisplay)),
            WhitePixel(mDisplay, DefaultScreen(mDisplay)));

         // make sure position and size is really used
         ::XSizeHints hints = { 0 };
         hints.flags = PPosition | PSize;
         hints.x = mWindowArea.min.x;
         hints.y = mWindowArea.min.y;
         hints.width = size.x;
         hints.height = size.y;
         ::XSetNormalHints(mDisplay, mWindow, &hints);

         // set title
         setTitle(mTitle.c_str());

         // select kind of events we are interested in
         XSelectInput(mDisplay, mWindow, mEventMask);

         // also register to the 'X' icon close click event
         mWindowDelete = ::XInternAtom(mDisplay, "WM_DELETE_WINDOW", False);
         ::XSetWMProtocols(mDisplay, mWindow, &mWindowDelete, 1);

         // map (show) the window
         // continue in "MapNotify" event when
         // it is fully constructed/visible
         ::XMapWindow(mDisplay, mWindow);
         return true;
      }

      /// <summary>
      /// Processes an XEvent from the queue
      /// </summary>
      INLINE void processEvent(const XEvent& event)
      {
         if (!mDisplay || !mWindow)
            return;

         switch (event.type)
         {
         //////////////////////////////////////////////////////////////////////////////////
         // WINDOW
         //////////////////////////////////////////////////////////////////////////////////

         // SHOWN/FULLY INITIALIZED
         case MapNotify:
            mShow = true;
            movedOrResized(true);
            onCreated();
            break;

         //
         case UnmapNotify:
            mShow = false;
            break;

         // MOVED OR RESIZED
         case ConfigureNotify:
            if (mShow)
               movedOrResized();
            break;

         // FOCUS GAINED
         case FocusIn:
            if (!mFocus)
            {
               mFocus = true;
               onFocusChanged(true);
            }
            break;

         // FOCUS LOST
         case FocusOut:
            if (mFocus)
            {
               mFocus = false;
               onFocusChanged(false);
            }
            break;

         // CLOSED BY USER
         case ClientMessage:
            if(event.xclient.format == 32 && 
               event.xclient.data.l[0] == mWindowDelete)
            {
               destroy();
            }
            break;

         //////////////////////////////////////////////////////////////////////////////////
         // MOUSE
         //////////////////////////////////////////////////////////////////////////////////

         // MOUSE MOVE
         case MotionNotify:
            onMouseMove(V2i(event.xmotion.x, event.xmotion.y));
            break;

         // MOUSE ENTER
         case EnterNotify:
            mMouseInWindow = true;
            onMouseEnter();
            break;

         // MOUSE LEAVE
         case LeaveNotify:
            mMouseInWindow = false;
            onMouseLeave();
            break;

         // MOUSE DOWN
         case ButtonPress:
            switch (event.xbutton.button)
            {
            case Button1: onMouseDown(Input::MouseButton::LeftButton);   break;
            case Button2: onMouseDown(Input::MouseButton::MiddleButton); break;
            case Button3: onMouseDown(Input::MouseButton::RightButton);  break;
            case Button4: onMouseWheel(CPPCORE_WINDOW_SCALE_WHEEL_LINUX);  break;
            case Button5: onMouseWheel(-CPPCORE_WINDOW_SCALE_WHEEL_LINUX); break;
            case 6:       onMouseDown(Input::MouseButton::X1Button); break;
            case 7:       onMouseDown(Input::MouseButton::X2Button); break;
            default:      onMouseDown(Input::MouseButton::Unknown);  break;
            }
            break;

         // MOUSE UP
         case ButtonRelease:
            switch (event.xbutton.button)
            {
            case Button1: onMouseUp(Input::MouseButton::LeftButton);   break;
            case Button2: onMouseUp(Input::MouseButton::MiddleButton); break;
            case Button3: onMouseUp(Input::MouseButton::RightButton);  break;
            case Button4: break;
            case Button5: break;
            case 6:       onMouseUp(Input::MouseButton::X1Button); break;
            case 7:       onMouseUp(Input::MouseButton::X2Button); break;
            default:      onMouseUp(Input::MouseButton::Unknown);  break;
            }
            break;

         //////////////////////////////////////////////////////////////////////////////////
         // KEYBOARD
         //////////////////////////////////////////////////////////////////////////////////

         // KEY DOWN
         case KeyPress:
         {
            // TODO: XLookupString is Latin-1, no UTF.
            KeySym   k;
            uint32_t c = 0;
            onKeyDown(Input::Key::fromKeyCode(event.xkey.keycode));
            int len = XLookupString((XKeyEvent*)&event.xkey, (char*)&c, 4, &k, 0);
            if (len)
               onChar(c);
            break;
         }

         // KEY UP
         case KeyRelease:
            //printf("KEYRELEASE %i\n", event.xkey.keycode);
            onKeyUp(Input::Key::fromKeyCode(event.xkey.keycode));
            break;

         default:
            break;
         }
      }
#elif defined(CPPCORE_OS_OSX) && defined(__OBJC__)

      /// <summary>
      /// Returns Platform Window Handle
      /// </summary>
      INLINE NSWindow* getWindow() const { return mWindow; }

      /// <summary>
      /// Returns Handle to the internal view in the window
      /// </summary>
      INLINE View* getView() const { return mView; }

      /// <summary>
      /// Returns Handle to Render Element
      /// </summary>
      INLINE size_t getRenderHandle() const { return (size_t)mView; }

      /// <summary>
      /// Create the Window (OSX)
      /// </summary>
      INLINE void create()
      {
         if (mWindow)
            return;

         // window styles
         NSUInteger windowStyle = 
            NSWindowStyleMaskTitled |
            NSWindowStyleMaskClosable |
            NSWindowStyleMaskResizable |
            NSWindowStyleMaskMiniaturizable;

         // screen rectangle
         NSRect screenRect = [[NSScreen mainScreen]frame];

         // client/view rectangle
         NSRect clientRect = NSMakeRect(
            mClientArea.min.x, 
            mClientArea.min.y, 
            mClientArea.max.x - mClientArea.min.x, 
            mClientArea.max.y - mClientArea.min.y);

         // window rectangle (0,0 is bottom left)
         NSRect windowRect = NSMakeRect(
            mWindowArea.min.x, 
            mWindowArea.min.y,
            mClientArea.max.x - mClientArea.min.x,
            mClientArea.max.y - mClientArea.min.y);

         // create window
         mWindow = [[NSWindow alloc]initWithContentRect:windowRect
            styleMask : windowStyle
            backing : NSBackingStoreBuffered
            defer : NO];

         // window controller (needed?)
         NSWindowController* windowController = [[NSWindowController alloc]initWithWindow:mWindow];
         [windowController autorelease] ;

         // view in the window
         mView = [[[View alloc]initWithFrame:clientRect] autorelease];
         [mView setWnd : this];
         //[mView setBackgroundColor : [NSColor redColor]];
         [mWindow setContentView : mView];

         // setup mouse tracking
         NSTrackingAreaOptions trackingOptions = NSTrackingMouseEnteredAndExited | NSTrackingActiveInKeyWindow;
         NSTrackingArea* trackingArea = [[NSTrackingArea alloc] initWithRect:clientRect options:trackingOptions owner: mView userInfo:nil];
         [mView addTrackingArea:trackingArea];

         // custom NSWindowDelegate
         WindowDelegate* windowDelegate = [[WindowDelegate alloc]init];
         [windowDelegate setWnd : this] ;
         [mWindow setDelegate : windowDelegate] ;

         [mWindow setAcceptsMouseMovedEvents : YES];
         [mWindow setBackgroundColor : [NSColor blueColor]];
         [mWindow setTitle : [NSString stringWithCString : mTitle.c_str() encoding : [NSString defaultCStringEncoding]]];
         [mWindow setCollectionBehavior : NSWindowCollectionBehaviorFullScreenPrimary];
         [mWindow makeKeyAndOrderFront : nil];
      }
#else
      /// <summary>
      /// Create the Window (ANDROID)
      /// </summary>
      INLINE void create()
      {
      }
#endif

      /// <summary>
      /// Destroy the Window
      /// </summary>
      INLINE void destroy()
      {
         onDestroying();
      #if defined(CPPCORE_OS_WINDOWS)
         if (mWindow)
         {
            DestroyWindow(mWindow);
            mWindow = 0;
         }
      #elif defined(CPPCORE_OS_LINUX)
         if (mDisplay && mWindow)
         {
            XDestroyWindow(mDisplay, mWindow);
            mWindow = 0;
         }
         if (mDisplay)
         {
            XCloseDisplay(mDisplay);
            mDisplay = 0;
         }
      #elif defined(CPPCORE_OS_OSX)
         if (mWindow)
         {
            // TODO: Cleanup?
            mWindow = 0;
         }
         if (mView)
         {
            // TODO: Cleanup?
            mView = 0;
         }
      #endif
         onDestroyed();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////

      INLINE virtual void onCreating()                                         { mCallback.onCreating(); }
      INLINE virtual void onCreated()                                          { mCallback.onCreated(); }
      INLINE virtual void onDestroying()                                       { mCallback.onDestroying(); }
      INLINE virtual void onDestroyed()                                        { mCallback.onDestroyed(); }
      INLINE virtual void onFocusChanged(bool focused)                         { mCallback.onFocusChanged(focused); }
      INLINE virtual void onClientAreaChanged(bool forced, const BBox2i& area) { mCallback.onClientAreaChanged(forced, area); }
      INLINE virtual void onWindowAreaChanged(bool forced, const BBox2i& area) { mCallback.onWindowAreaChanged(forced, area); }
      INLINE virtual void onMouseMove(const V2i& p)                            { mCallback.onMouseMove(p); }
      INLINE virtual void onMouseEnter()                                       { mCallback.onMouseEnter(); }
      INLINE virtual void onMouseLeave()                                       { mCallback.onMouseLeave(); }
      INLINE virtual void onMouseDown(Input::MouseButton::Enum b)              { mCallback.onMouseDown(b); }
      INLINE virtual void onMouseUp(Input::MouseButton::Enum b)                { mCallback.onMouseUp(b); }
      INLINE virtual void onMouseWheel(int32_t delta)                          { mCallback.onMouseWheel(delta); }
      INLINE virtual void onKeyDown(Input::Key::Enum k)                        { mCallback.onKeyDown(k); }
      INLINE virtual void onKeyUp(Input::Key::Enum k)                          { mCallback.onKeyUp(k); }
      INLINE virtual void onChar(uint32_t c)                                   { mCallback.onChar(c); }
   };
}
