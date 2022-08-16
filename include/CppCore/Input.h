#pragma once

#include <CppCore/Root.h>
#include <CppCore/Math/V2.h>
#include <CppCore/Math/V3.h>
#include <CppCore/Math/BBox2.h>

namespace CppCore
{
   /// <summary>
   /// Input (Keyboard+Mouse)
   /// </summary>
   class Input
   {
   public:
      /// <summary>
      /// Keyboard Key. Enum and Helpers.
      /// </summary>
      class Key
      {
      private:
         INLINE Key() { }

      public:
         /// <summary>
         /// Enumeration of Keys. Taken from CEGUI 
         /// which took it from Ogre OIS 
         /// which took it from DirectInput 
         /// which seems highly compatible with X11 keycodes (just offset..)
         /// </summary>
         enum Enum : uint8_t
         {
            Unknown        = 0x00,
            Escape         = 0x01,
            One            = 0x02,
            Two            = 0x03,
            Three          = 0x04,
            Four           = 0x05,
            Five           = 0x06,
            Six            = 0x07,
            Seven          = 0x08,
            Eight          = 0x09,
            Nine           = 0x0A,
            Zero           = 0x0B,
            Minus          = 0x0C,    /* OEM_MINUS */
            Equals         = 0x0D,    /* OEM_PLUS */
            Backspace      = 0x0E,
            Tab            = 0x0F,
            Q              = 0x10,
            W              = 0x11,
            E              = 0x12,
            R              = 0x13,
            T              = 0x14,
            Y              = 0x15,
            U              = 0x16,
            I              = 0x17,
            O              = 0x18,
            P              = 0x19,
            LeftBracket    = 0x1A,    /* OEM_4 */
            RightBracket   = 0x1B,    /* OEM_6 */
            Return         = 0x1C,    /* Enter on main keyboard */
            LeftControl    = 0x1D,
            A              = 0x1E,
            S              = 0x1F,
            D              = 0x20,
            F              = 0x21,
            G              = 0x22,
            H              = 0x23,
            J              = 0x24,
            K              = 0x25,
            L              = 0x26,
            Semicolon      = 0x27,    /* OEM_1 */
            Apostrophe     = 0x28,    /* OEM_7 */
            Grave          = 0x29,    /* OEM_3 */
            LeftShift      = 0x2A,
            Backslash      = 0x2B,    /* OEM_5 */
            Z              = 0x2C,
            X              = 0x2D,
            C              = 0x2E,
            V              = 0x2F,
            B              = 0x30,
            N              = 0x31,
            M              = 0x32,
            Comma          = 0x33,
            Period         = 0x34,
            Slash          = 0x35,    /* OEM_2*/
            RightShift     = 0x36,
            Multiply       = 0x37,    /* * on numeric keypad */
            LeftAlt        = 0x38,    /* left Alt */
            Space          = 0x39,
            Capital        = 0x3A,
            F1             = 0x3B,
            F2             = 0x3C,
            F3             = 0x3D,
            F4             = 0x3E,
            F5             = 0x3F,
            F6             = 0x40,
            F7             = 0x41,
            F8             = 0x42,
            F9             = 0x43,
            F10            = 0x44,
            NumLock        = 0x45,
            ScrollLock     = 0x46,    /* Scroll Lock */
            Numpad7        = 0x47,
            Numpad8        = 0x48,
            Numpad9        = 0x49,
            Subtract       = 0x4A,    /* - on numeric keypad */
            Numpad4        = 0x4B,
            Numpad5        = 0x4C,
            Numpad6        = 0x4D,
            Add            = 0x4E,    /* + on numeric keypad */
            Numpad1        = 0x4F,
            Numpad2        = 0x50,
            Numpad3        = 0x51,
            Numpad0        = 0x52,
            Decimal        = 0x53,    /* . on numeric keypad */
            OEM_102        = 0x56,    /* < > | on UK/Germany keyboards */
            F11            = 0x57,
            F12            = 0x58,
            F13            = 0x64,    /*                     (NEC PC98) */
            F14            = 0x65,    /*                     (NEC PC98) */
            F15            = 0x66,    /*                     (NEC PC98) */
            Kana           = 0x70,    /* (Japanese keyboard)            */
            ABNT_C1        = 0x73,    /* / ? on Portugese (Brazilian) keyboards */
            Convert        = 0x79,    /* (Japanese keyboard)            */
            NoConvert      = 0x7B,    /* (Japanese keyboard)            */
            Yen            = 0x7D,    /* (Japanese keyboard)            */
            ABNT_C2        = 0x7E,    /* Numpad . on Portugese (Brazilian) keyboards */
            NumpadEquals   = 0x8D,    /* = on numeric keypad (NEC PC98) */
            PrevTrack      = 0x90,    /* Previous Track (KC_CIRCUMFLEX on Japanese keyboard) */
            At             = 0x91,    /*                     (NEC PC98) */
            Colon          = 0x92,    /*                     (NEC PC98) */
            Underline      = 0x93,    /*                     (NEC PC98) */
            Kanji          = 0x94,    /* (Japanese keyboard)            */
            Stop           = 0x95,    /*                     (NEC PC98) */
            AX             = 0x96,    /*                     (Japan AX) */
            Unlabeled      = 0x97,    /*                        (J3100) */
            NextTrack      = 0x99,    /* Next Track */
            NumpadEnter    = 0x9C,    /* Enter on numeric keypad */
            RightControl   = 0x9D,
            Mute           = 0xA0,    /* Mute */
            Calculator     = 0xA1,    /* Calculator */
            PlayPause      = 0xA2,    /* Play / Pause */
            MediaStop      = 0xA4,    /* Media Stop */
            VolumeDown     = 0xAE,    /* Volume - */
            VolumeUp       = 0xB0,    /* Volume + */
            WebHome        = 0xB2,    /* Web home */
            NumpadComma    = 0xB3,    /* , on numeric keypad (NEC PC98) */
            Divide         = 0xB5,    /* / on numeric keypad */
            SysRq          = 0xB7,
            RightAlt       = 0xB8,    /* right Alt */
            Pause          = 0xC5,    /* Pause */
            Home           = 0xC7,    /* Home on arrow keypad */
            ArrowUp        = 0xC8,    /* UpArrow on arrow keypad */
            PageUp         = 0xC9,    /* PgUp on arrow keypad */
            ArrowLeft      = 0xCB,    /* LeftArrow on arrow keypad */
            ArrowRight     = 0xCD,    /* RightArrow on arrow keypad */
            End            = 0xCF,    /* End on arrow keypad */
            ArrowDown      = 0xD0,    /* DownArrow on arrow keypad */
            PageDown       = 0xD1,    /* PgDn on arrow keypad */
            Insert         = 0xD2,    /* Insert on arrow keypad */
            Delete         = 0xD3,    /* Delete on arrow keypad */
            LeftWindows    = 0xDB,    /* Left Windows key */
            RightWindows   = 0xDC,    /* Right Windows key - Correct spelling :) */
            AppMenu        = 0xDD,    /* AppMenu key */
            Power          = 0xDE,    /* System Power */
            Sleep          = 0xDF,    /* System Sleep */
            Wake           = 0xE3,    /* System Wake */
            WebSearch      = 0xE5,    /* Web Search */
            WebFavorites   = 0xE6,    /* Web Favorites */
            WebRefresh     = 0xE7,    /* Web Refresh */
            WebStop        = 0xE8,    /* Web Stop */
            WebForward     = 0xE9,    /* Web Forward */
            WebBack        = 0xEA,    /* Web Back */
            MyComputer     = 0xEB,    /* My Computer */
            Mail           = 0xEC,    /* Mail */
            MediaSelect    = 0xED     /* Media Select */
         };

         /// <summary>
         /// Creates Key Enum value for X11 compatible keycode.
         /// </summary>
         INLINE static Key::Enum fromKeyCode(const uint8_t keycode)
         {
            static const Key::Enum table[] = {
               Key::Unknown,            // 0x00:
               Key::Unknown,            // 0x01:
               Key::Unknown,            // 0x02:
               Key::Unknown,            // 0x03:
               Key::Unknown,            // 0x04:
               Key::Unknown,            // 0x05:
               Key::Unknown,            // 0x06:
               Key::Unknown,            // XKB   evdev (XKB - 8)      X KeySym
               Key::Unknown,            // ===   ===============      ======
               Key::Escape,             // 0x09: KEY_ESC              Escape
               Key::One,                // 0x0A: KEY_1                1
               Key::Two,                // 0x0B: KEY_2                2
               Key::Three,              // 0x0C: KEY_3                3
               Key::Four,               // 0x0D: KEY_4                4
               Key::Five,               // 0x0E: KEY_5                5
               Key::Six,                // 0x0F: KEY_6                6
               Key::Seven,              // 0x10: KEY_7                7
               Key::Eight,              // 0x11: KEY_8                8
               Key::Nine,               // 0x12: KEY_9                9
               Key::Zero,               // 0x13: KEY_0                0
               Key::Minus,              // 0x14: KEY_MINUS            minus
               Key::Equals,             // 0x15: KEY_EQUAL            equal
               Key::Backspace,          // 0x16: KEY_BACKSPACE        BackSpace
               Key::Tab,                // 0x17: KEY_TAB              Tab
               Key::Q,                  // 0x18: KEY_Q                q
               Key::W,                  // 0x19: KEY_W                w
               Key::E,                  // 0x1A: KEY_E                e
               Key::R,                  // 0x1B: KEY_R                r
               Key::T,                  // 0x1C: KEY_T                t
               Key::Y,                  // 0x1D: KEY_Y                y
               Key::U,                  // 0x1E: KEY_U                u
               Key::I,                  // 0x1F: KEY_I                i
               Key::O,                  // 0x20: KEY_O                o
               Key::P,                  // 0x21: KEY_P                p
               Key::LeftBracket,        // 0x22: KEY_LEFTBRACE        bracketleft
               Key::RightBracket,       // 0x23: KEY_RIGHTBRACE       bracketright
               Key::Return,             // 0x24: KEY_ENTER            Return
               Key::LeftControl,        // 0x25: KEY_LEFTCTRL         Control_L
               Key::A,                  // 0x26: KEY_A                a
               Key::S,                  // 0x27: KEY_S                s
               Key::D,                  // 0x28: KEY_D                d
               Key::F,                  // 0x29: KEY_F                f
               Key::G,                  // 0x2A: KEY_G                g
               Key::H,                  // 0x2B: KEY_H                h
               Key::J,                  // 0x2C: KEY_J                j
               Key::K,                  // 0x2D: KEY_K                k
               Key::L,                  // 0x2E: KEY_L                l
               Key::Semicolon,          // 0x2F: KEY_SEMICOLON        semicolon
               Key::Apostrophe,         // 0x30: KEY_APOSTROPHE       apostrophe
               Key::Grave,              // 0x31: KEY_GRAVE            grave
               Key::LeftShift,          // 0x32: KEY_LEFTSHIFT        Shift_L
               Key::Backslash,          // 0x33: KEY_BACKSLASH        backslash
               Key::Z,                  // 0x34: KEY_Z                z
               Key::X,                  // 0x35: KEY_X                x
               Key::C,                  // 0x36: KEY_C                c
               Key::V,                  // 0x37: KEY_V                v
               Key::B,                  // 0x38: KEY_B                b
               Key::N,                  // 0x39: KEY_N                n
               Key::M,                  // 0x3A: KEY_M                m
               Key::Comma,              // 0x3B: KEY_COMMA            comma
               Key::Period,             // 0x3C: KEY_DOT              period
               Key::Slash,              // 0x3D: KEY_SLASH            slash
               Key::RightShift,         // 0x3E: KEY_RIGHTSHIFT       Shift_R
               Key::Multiply,           // 0x3F: KEY_KPASTERISK       KP_Multiply
               Key::LeftAlt,            // 0x40: KEY_LEFTALT          Alt_L
               Key::Space,              // 0x41: KEY_SPACE            space
               Key::Capital,            // 0x42: KEY_CAPSLOCK         Caps_Lock
               Key::F1,                 // 0x43: KEY_F1               F1
               Key::F2,                 // 0x44: KEY_F2               F2
               Key::F3,                 // 0x45: KEY_F3               F3
               Key::F4,                 // 0x46: KEY_F4               F4
               Key::F5,                 // 0x47: KEY_F5               F5
               Key::F6,                 // 0x48: KEY_F6               F6
               Key::F7,                 // 0x49: KEY_F7               F7
               Key::F8,                 // 0x4A: KEY_F8               F8
               Key::F9,                 // 0x4B: KEY_F9               F9
               Key::F10,                // 0x4C: KEY_F10              F10
               Key::NumLock,            // 0x4D: KEY_NUMLOCK          Num_Lock
               Key::ScrollLock,         // 0x4E: KEY_SCROLLLOCK       Scroll_Lock
               Key::Numpad7,            // 0x4F: KEY_KP7              KP_7
               Key::Numpad8,            // 0x50: KEY_KP8              KP_8
               Key::Numpad9,            // 0x51: KEY_KP9              KP_9
               Key::Subtract,           // 0x52: KEY_KPMINUS          KP_Subtract
               Key::Numpad4,            // 0x53: KEY_KP4              KP_4
               Key::Numpad5,            // 0x54: KEY_KP5              KP_5
               Key::Numpad6,            // 0x55: KEY_KP6              KP_6
               Key::Add,                // 0x56: KEY_KPPLUS           KP_Add
               Key::Numpad1,            // 0x57: KEY_KP1              KP_1
               Key::Numpad2,            // 0x58: KEY_KP2              KP_2
               Key::Numpad3,            // 0x59: KEY_KP3              KP_3
               Key::Numpad0,            // 0x5A: KEY_KP0              KP_0
               Key::NumpadComma,        // 0x5B: KEY_KPDOT            KP_Decimal
               Key::Unknown,            // 0x5C:
               Key::Unknown,            // 0x5D: KEY_ZENKAKUHANKAKU   Zenkaku_Hankaku
               Key::Backslash,          // 0x5E: KEY_102ND            backslash
               Key::F11,                // 0x5F: KEY_F11              F11
               Key::F12,                // 0x60: KEY_F12              F12
               Key::Home,               // 0x61: KEY_HOME             Home
               Key::ArrowUp,            // 0x62: KEY_UP               Up
               Key::PageUp,             // 0x63: KEY_PAGEUP           Page_Up
               Key::ArrowLeft,          // 0x64: KEY_LEFT             Left
               Key::Unknown,            // 0x65:
               Key::ArrowRight,         // 0x66: KEY_RIGHT            Right
               Key::End,                // 0x67: KEY_END              End
               Key::ArrowDown,          // 0x68: KEY_DOWN             Down
               Key::PageDown,           // 0x69: KEY_PAGEDOWN         Page_Down
               Key::Insert,             // 0x6A: KEY_INSERT           Insert
               Key::Delete,             // 0x6B: KEY_DELETE           Delete
               Key::NumpadEnter,        // 0x6C: KEY_KPENTER          KP_Enter
               Key::RightControl,       // 0x6D: KEY_RIGHTCTRL        Control_R
               Key::Pause,              // 0x6E: KEY_PAUSE            Pause
               Key::Unknown,            // 0x6F:
               Key::Unknown,            // 0x70:
               Key::RightAlt            // 0x71: KEY_RIGHTALT         Alt_R
            };
            return keycode <= 0x71 ? table[keycode] : Key::Unknown;
         }

         /// <summary>
         /// Creates Key Enum value for APPLE compatible keycode.
         /// </summary>
         INLINE static Key::Enum fromAppleKeyCode(const uint8_t keycode)
         {
            // see Events.h in OSX SDK (Carbon)
            static const Key::Enum table[] = {
                                        // KEY   OSX CONSTANT
                                        // ===   ===============
               Key::A,                  // 0x00: kVK_ANSI_A
               Key::S,                  // 0x01: kVK_ANSI_S
               Key::D,                  // 0x02: kVK_ANSI_D
               Key::F,                  // 0x03: kVK_ANSI_F
               Key::H,                  // 0x04: kVK_ANSI_H
               Key::G,                  // 0x05: kVK_ANSI_G
               Key::Z,                  // 0x06: kVK_ANSI_Z
               Key::X,                  // 0x07: kVK_ANSI_X
               Key::C,                  // 0x08: kVK_ANSI_C
               Key::V,                  // 0x09: kVK_ANSI_V
               Key::Unknown,            // 0x0A: kVK_ISO_Section
               Key::B,                  // 0x0B: kVK_ANSI_B
               Key::Q,                  // 0x0C: kVK_ANSI_Q
               Key::W,                  // 0x0D: kVK_ANSI_W
               Key::E,                  // 0x0E: kVK_ANSI_E
               Key::R,                  // 0x0F: kVK_ANSI_R
               Key::Y,                  // 0x10: kVK_ANSI_Y
               Key::T,                  // 0x11: kVK_ANSI_T
               Key::One,                // 0x12: kVK_ANSI_1
               Key::Two,                // 0x13: kVK_ANSI_2
               Key::Three,              // 0x14: kVK_ANSI_3
               Key::Four,               // 0x15: kVK_ANSI_4
               Key::Six,                // 0x16: kVK_ANSI_6 WTF?
               Key::Five,               // 0x17: kVK_ANSI_5 WTF?
               Key::Unknown,            // 0x18: kVK_ANSI_Equal
               Key::Nine,               // 0x19: kVK_ANSI_9
               Key::Seven,              // 0x1A: kVK_ANSI_7
               Key::Unknown,            // 0x1B: kVK_ANSI_Minus
               Key::Eight,              // 0x1C: kVK_ANSI_8
               Key::Zero,               // 0x1D: kVK_ANSI_0
               Key::RightBracket,       // 0x1E: kVK_ANSI_RightBracket
               Key::O,                  // 0x1F: kVK_ANSI_O
               Key::U,                  // 0x20: kVK_ANSI_U
               Key::LeftBracket,        // 0x21: kVK_ANSI_LeftBracket
               Key::I,                  // 0x22: kVK_ANSI_I
               Key::P,                  // 0x23: kVK_ANSI_P
               Key::Return,             // 0x24: kVK_Return
               Key::L,                  // 0x25: kVK_ANSI_L
               Key::J,                  // 0x26: kVK_ANSI_J
               Key::Unknown,            // 0x27: kVK_ANSI_Quote
               Key::K,                  // 0x28: kVK_ANSI_K
               Key::Semicolon,          // 0x29: kVK_ANSI_Semicolon
               Key::Backslash,          // 0x2A: kVK_ANSI_Backslash
               Key::Comma,              // 0x2B: kVK_ANSI_Comma
               Key::Slash,              // 0x2C: kVK_ANSI_Slash
               Key::N,                  // 0x2D: kVK_ANSI_N
               Key::M,                  // 0x2E: kVK_ANSI_M
               Key::Period,             // 0x2F: kVK_ANSI_Period
               Key::Tab,                // 0x30: kVK_Tab
               Key::Space,              // 0x31: kVK_Space
               Key::Grave,              // 0x32: kVK_ANSI_Grave
               Key::Backspace,          // 0x33: kVK_Delete
               Key::Unknown,            // 0x34: 
               Key::Escape,             // 0x35: kVK_Escape
               Key::Unknown,            // 0x36: 
               Key::Unknown,            // 0x37: kVK_Command
               Key::LeftShift,          // 0x38: kVK_Shift
               Key::Capital,            // 0x39: kVK_CapsLock
               Key::LeftAlt,            // 0x3A: kVK_Option
               Key::LeftControl,        // 0x3B: kVK_Control
               Key::RightShift,         // 0x3C: kVK_RightShift
               Key::RightAlt,           // 0x3D: kVK_RightOption
               Key::RightControl,       // 0x3E: kVK_RightControl
               Key::Unknown,            // 0x3F: kVK_Function
               Key::Unknown,            // 0x40: kVK_F17
               Key::Decimal,            // 0x41: kVK_ANSI_KeypadDecimal
               Key::Unknown,            // 0x42: 
               Key::Multiply,           // 0x43: kVK_ANSI_KeypadMultiply
               Key::Unknown,            // 0x44: 
               Key::Add,                // 0x45: kVK_ANSI_KeypadPlus
               Key::Unknown,            // 0x46: 
               Key::Unknown,            // 0x47: kVK_ANSI_KeypadClear
               Key::VolumeUp,           // 0x48: kVK_VolumeUp
               Key::VolumeDown,         // 0x49: kVK_VolumeDown
               Key::Mute,               // 0x4A: kVK_Mute 
               Key::Divide,             // 0x4B: kVK_ANSI_KeypadDivide
               Key::NumpadEnter,        // 0x4C: kVK_ANSI_KeypadEnter
               Key::Unknown,            // 0x4D: 
               Key::Subtract,           // 0x4E: kVK_ANSI_KeypadMinus
               Key::Unknown,            // 0x4F: kVK_F18
               Key::Unknown,            // 0x50: kVK_F19
               Key::NumpadEquals,       // 0x51: kVK_ANSI_KeypadEquals
               Key::Numpad0,            // 0x52: kVK_ANSI_Keypad0
               Key::Numpad1,            // 0x53: kVK_ANSI_Keypad1
               Key::Numpad2,            // 0x54: kVK_ANSI_Keypad2
               Key::Numpad3,            // 0x55: kVK_ANSI_Keypad3
               Key::Numpad4,            // 0x56: kVK_ANSI_Keypad4
               Key::Numpad5,            // 0x57: kVK_ANSI_Keypad5
               Key::Numpad6,            // 0x58: kVK_ANSI_Keypad6
               Key::Numpad7,            // 0x59: kVK_ANSI_Keypad7
               Key::Unknown,            // 0x5A: kVK_F20
               Key::Numpad8,            // 0x5B: kVK_ANSI_Keypad8
               Key::Numpad9,            // 0x5C: kVK_ANSI_Keypad9
               Key::Unknown,            // 0x5D: kVK_JIS_Yen
               Key::Unknown,            // 0x5E: kVK_JIS_Underscore
               Key::NumpadComma,        // 0x5F: kVK_JIS_KeypadComma
               Key::F5,                 // 0x60: kVK_F5
               Key::F6,                 // 0x61: kVK_F6
               Key::F7,                 // 0x62: kVK_F7
               Key::F3,                 // 0x63: kVK_F3
               Key::F8,                 // 0x64: kVK_F8
               Key::F9,                 // 0x65: kVK_F9
               Key::Unknown,            // 0x66: kVK_JIS_Eisu
               Key::F11,                // 0x67: kVK_F11
               Key::Kana,               // 0x68: kVK_JIS_Kana
               Key::Unknown,            // 0x69: kVK_F13
               Key::Unknown,            // 0x6A: kVK_F16
               Key::Unknown,            // 0x6B: kVK_F14
               Key::Unknown,            // 0x6C: 
               Key::F10,                // 0x6D: kVK_F10
               Key::Unknown,            // 0x6E: 
               Key::F12,                // 0x6F: kVK_F12
               Key::Unknown,            // 0x70:
               Key::Unknown,            // 0x71: kVK_F15
               Key::Unknown,            // 0x72: kVK_Help
               Key::Home,               // 0x73: kVK_Home
               Key::PageUp,             // 0x74: kVK_PageUp
               Key::Delete,             // 0x75: kVK_ForwardDelete
               Key::F4,                 // 0x76: kVK_F4
               Key::End,                // 0x77: kVK_End
               Key::F2,                 // 0x78: kVK_F2
               Key::PageDown,           // 0x79: kVK_PageDown
               Key::F1,                 // 0x7A: kVK_F1
               Key::ArrowLeft,          // 0x7B: kVK_LeftArrow
               Key::ArrowRight,         // 0x7C: kVK_RightArrow
               Key::ArrowDown,          // 0x7D: kVK_DownArrow
               Key::ArrowUp             // 0x7E: kVK_UpArrow
            };
            return keycode <= 0x7E ? table[keycode] : Key::Unknown;
         }

      #if defined(CPPCORE_OS_WINDOWS)
         /// <summary>
         /// Converts key information from WM_MESSAGE to internal enum.
         /// </summary>
         INLINE static Key::Enum fromWindowsMessage(WPARAM vk, LPARAM lParam)
         {
            // turn combined L+R into dedicated L+R (alt/ctrl/..)
            UINT scancode = (lParam & 0x00ff0000) >> 16;
            int extended  = (lParam & 0x01000000) != 0;

            switch (vk) 
            {
            case VK_SHIFT:   vk = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX); break;
            case VK_CONTROL: vk = extended ? VK_RCONTROL : VK_LCONTROL;        break;
            case VK_MENU:    vk = extended ? VK_RMENU : VK_LMENU;              break;
            default:                                                           break;
            }

            // map key
            switch (vk)
            {
            case VK_ESCAPE:               return Key::Escape;
            case 0x31:                    return Key::One;
            case 0x32:                    return Key::Two;
            case 0x33:                    return Key::Three;
            case 0x34:                    return Key::Four;
            case 0x35:                    return Key::Five;
            case 0x36:                    return Key::Six;
            case 0x37:                    return Key::Seven;
            case 0x38:                    return Key::Eight;
            case 0x39:                    return Key::Nine;
            case 0x30:                    return Key::Zero;
            case VK_OEM_MINUS:            return Key::Minus;       /* - on main keyboard */
            case VK_OEM_PLUS:             return Key::Equals;
            case VK_BACK:                 return Key::Backspace;   /* backspace */
            case VK_TAB:                  return Key::Tab;
            case 0x51:                    return Key::Q;
            case 0x57:                    return Key::W;
            case 0x45:                    return Key::E;
            case 0x52:                    return Key::R;
            case 0x54:                    return Key::T;
            case 0x59:                    return Key::Y;
            case 0x55:                    return Key::U;
            case 0x49:                    return Key::I;
            case 0x4F:                    return Key::O;
            case 0x50:                    return Key::P;
            case VK_OEM_4:                return Key::LeftBracket;
            case VK_OEM_6:                return Key::RightBracket;
            case VK_RETURN:               return extended ? Key::NumpadEnter : Key::Return;
            case VK_LCONTROL:             return Key::LeftControl;
            case 0x41:                    return Key::A;
            case 0x53:                    return Key::S;
            case 0x44:                    return Key::D;
            case 0x46:                    return Key::F;
            case 0x47:                    return Key::G;
            case 0x48:                    return Key::H;
            case 0x4A:                    return Key::J;
            case 0x4B:                    return Key::K;
            case 0x4C:                    return Key::L;
            case VK_OEM_1:                return Key::Semicolon;
            case VK_OEM_7:                return Key::Apostrophe;
            case VK_OEM_3:                return Key::Grave;
            case VK_LSHIFT:               return Key::LeftShift;
            case VK_OEM_5:                return Key::Backslash;
            case 0x5A:                    return Key::Z;
            case 0x58:                    return Key::X;
            case 0x43:                    return Key::C;
            case 0x56:                    return Key::V;
            case 0x42:                    return Key::B;
            case 0x4E:                    return Key::N;
            case 0x4D:                    return Key::M;
            case VK_OEM_COMMA:            return Key::Comma;
            case VK_OEM_PERIOD:           return Key::Period;
            case VK_OEM_2:                return Key::Slash;
            case VK_RSHIFT:               return Key::RightShift;
            case VK_MULTIPLY:             return Key::Multiply;    /* * on numeric keypad */
            case VK_LMENU:                return Key::LeftAlt;     /* left Alt */
            case VK_SPACE:                return Key::Space;
            case VK_CAPITAL:              return Key::Capital;
            case VK_F1:                   return Key::F1;
            case VK_F2:                   return Key::F2;
            case VK_F3:                   return Key::F3;
            case VK_F4:                   return Key::F4;
            case VK_F5:                   return Key::F5;
            case VK_F6:                   return Key::F6;
            case VK_F7:                   return Key::F7;
            case VK_F8:                   return Key::F8;
            case VK_F9:                   return Key::F9;
            case VK_F10:                  return Key::F10;
            case VK_NUMLOCK:              return Key::NumLock;
            case VK_SCROLL:               return Key::ScrollLock;
            case VK_NUMPAD7:              return Key::Numpad7;
            case VK_NUMPAD8:              return Key::Numpad8;
            case VK_NUMPAD9:              return Key::Numpad9;
            case VK_SUBTRACT:             return Key::Subtract;      /* - on numeric keypad */
            case VK_NUMPAD4:              return Key::Numpad4;
            case VK_NUMPAD5:              return Key::Numpad5;
            case VK_NUMPAD6:              return Key::Numpad6;
            case VK_ADD:                  return Key::Add;           /* + on numeric keypad */
            case VK_NUMPAD1:              return Key::Numpad1;
            case VK_NUMPAD2:              return Key::Numpad2;
            case VK_NUMPAD3:              return Key::Numpad3;
            case VK_NUMPAD0:              return Key::Numpad0;
            case VK_DECIMAL:              return Key::Decimal;       /* . on numeric keypad */
            case VK_OEM_102:              return Key::OEM_102;       /* < > | on UK/Germany keyboards */
            case VK_F11:                  return Key::F11;
            case VK_F12:                  return Key::F12;
            case VK_F13:                  return Key::F13;           /*                     (NEC PC98) */
            case VK_F14:                  return Key::F14;           /*                     (NEC PC98) */
            case VK_F15:                  return Key::F15;           /*                     (NEC PC98) */
            case VK_KANA:                 return Key::Kana;          /* (Japanese keyboard)            */
            //                            return Key::ABNT_C1;       /* / ? on Portugese (Brazilian) keyboards */
            case VK_CONVERT:              return Key::Convert;       /* (Japanese keyboard)            */
            case VK_NONCONVERT:           return Key::NoConvert;     /* (Japanese keyboard)            */
            //                            return Key::Yen;           /* (Japanese keyboard)            */
            //                            return Key::ABNT_C;        /* Numpad . on Portugese (Brazilian) keyboards */
            //                            return Key::NumpadEquals;  /* = on numeric keypad (NEC PC98) */
            case VK_MEDIA_PREV_TRACK:     return Key::PrevTrack;     /* Previous Track (KC_CIRCUMFLEX on Japanese keyboard) */
            //                            return Key::At;            /*                     (NEC PC98) */
            //                            return Key::Colon;         /*                     (NEC PC98) */
            //                            return Key::Underline;     /*                     (NEC PC98) */
            case VK_KANJI:                return Key::Kanji;         /* (Japanese keyboard)            */
            //                            return Key::Stop;          /*                     (NEC PC98) */
            case VK_OEM_AX:               return Key::AX;            /*                     (Japan AX) */
            //                            return Key::Unlabeled;     /*                        (J3100) */
            case VK_MEDIA_NEXT_TRACK:     return Key::NextTrack;     /* Next Track */
            //                            return Key::NumpadEnter;   /* Enter on numeric keypad, see normal case above */
            case VK_RCONTROL:             return Key::RightControl;
            case VK_VOLUME_MUTE:          return Key::Mute;          /* Mute */
            //                            return Key::Calculator;    /* Calculator */
            case VK_MEDIA_PLAY_PAUSE:     return Key::PlayPause;     /* Play / Pause */
            case VK_MEDIA_STOP:           return Key::MediaStop;     /* Media Stop */
            case VK_VOLUME_DOWN:          return Key::VolumeDown;    /* Volume - */
            case VK_VOLUME_UP:            return Key::VolumeUp;      /* Volume + */
            case VK_BROWSER_HOME:         return Key::WebHome;       /* Web home */
            //                            return Key::NumpadComma;   /* , on numeric keypad (NEC PC98) */
            case VK_DIVIDE:               return Key::Divide;        /* / on numeric keypad */
            //                            return Key::SysRq;
            case VK_RMENU:                return Key::RightAlt;      /* right Alt */
            case VK_PAUSE:                return Key::Pause;         /* Pause */
            case VK_HOME:                 return Key::Home;          /* Home on arrow keypad */
            case VK_UP:                   return Key::ArrowUp;       /* UpArrow on arrow keypad */
            case VK_PRIOR:                return Key::PageUp;        /* PgUp on arrow keypad */
            case VK_LEFT:                 return Key::ArrowLeft;     /* LeftArrow on arrow keypad */
            case VK_RIGHT:                return Key::ArrowRight;    /* RightArrow on arrow keypad */
            case VK_END:                  return Key::End;           /* End on arrow keypad */
            case VK_DOWN:                 return Key::ArrowDown;     /* DownArrow on arrow keypad */
            case VK_NEXT:                 return Key::PageDown;      /* PgDn on arrow keypad */
            case VK_INSERT:               return Key::Insert;        /* Insert on arrow keypad */
            case VK_DELETE:               return Key::Delete;        /* Delete on arrow keypad */
            case VK_LWIN:                 return Key::LeftWindows;   /* Left Windows key */
            case VK_RWIN:                 return Key::RightWindows;  /* Right Windows key - Correct spelling :) */
            case VK_APPS:                 return Key::AppMenu;       /* AppMenu key */
            //                            return Key::Power;         /* System Power */
            case VK_SLEEP:                return Key::Sleep;         /* System Sleep */
            //                            return Key::Wake;          /* System Wake */
            case VK_BROWSER_SEARCH:       return Key::WebSearch;     /* Web Search */
            case VK_BROWSER_FAVORITES:    return Key::WebFavorites;  /* Web Favorites */
            case VK_BROWSER_REFRESH:      return Key::WebRefresh;    /* Web Refresh */
            case VK_BROWSER_STOP:         return Key::WebStop;       /* Web Stop */
            case VK_BROWSER_FORWARD:      return Key::WebForward;    /* Web Forward */
            case VK_BROWSER_BACK:         return Key::WebBack;       /* Web Back */
            //                            return Key::MyComputer;    /* My Computer */
            case VK_LAUNCH_MAIL:          return Key::Mail;          /* Mail */
            case VK_LAUNCH_MEDIA_SELECT:  return Key::MediaSelect;   /* Media Select */
            default:                      return Key::Unknown;
            }
         }
      #endif

         /// <summary>
         /// True for keys 0-9 on main keyboard.
         /// </summary>
         INLINE static bool isNumericMain(const Enum k)
         {
            return
               k == Zero || k == One || k == Two   || k == Three || k == Four ||
               k == Five || k == Six || k == Seven || k == Eight || k == Nine;
         }

         /// <summary>
         /// True for keys 0-9 on numpad.
         /// </summary>
         INLINE static bool isNumericNumPad(const Enum k)
         {
            return
               k == Numpad0 || k == Numpad1 || k == Numpad2 || k == Numpad3 || k == Numpad4 ||
               k == Numpad5 || k == Numpad6 || k == Numpad7 || k == Numpad8 || k == Numpad9;
         }

         /// <summary>
         /// True for keys 0-9 on main keyboard or numpad.
         /// </summary>
         INLINE static bool isNumeric(const Enum k)
         {
            return isNumericMain(k) || isNumericNumPad(k);
         }

         /// <summary>
         /// True for keys A-Z
         /// </summary>
         INLINE static bool isLetter(const Enum k)
         {
            return
               k == A || k == B || k == C || k == D || k == E || k == F || k == G ||
               k == H || k == I || k == J || k == K || k == L || k == M || k == N ||
               k == O || k == P || k == Q || k == R || k == S || k == T || k == U ||
               k == V || k == W || k == X || k == Y || k == Z;
         }

         /// <summary>
         /// True for keys A-Z and 0-9.
         /// </summary>
         INLINE static bool isAlphaNumeric(const Enum k)
         {
            return isLetter(k) || isNumeric(k);
         }

         /// <summary>
         /// Gets a single character represented by the key.
         /// Only works for alphanumerics (so far), others 0x00.
         /// </summary>
         INLINE static const char getChar(const Enum k)
         {
            switch (k)
            {
            // Numerics Main
            case Zero: return '0'; case One: return '1'; case Two:   return '2'; case Three: return '3'; case Four: return '4';
            case Five: return '5'; case Six: return '6'; case Seven: return '7'; case Eight: return '8'; case Nine: return '9';

            // Numerics NumPad
            case Numpad0: return '0'; case Numpad1: return '1'; case Numpad2: return '2'; case Numpad3: return '3'; case Numpad4: return '4';
            case Numpad5: return '5'; case Numpad6: return '6'; case Numpad7: return '7'; case Numpad8: return '8'; case Numpad9: return '9';

            // Letters
            case A: return 'A'; case B: return 'B'; case C: return 'C'; case D: return 'D'; case E: return 'E';
            case F: return 'F'; case G: return 'G'; case H: return 'H'; case I: return 'I'; case J: return 'J';
            case K: return 'K'; case L: return 'L'; case M: return 'M'; case N: return 'N'; case O: return 'O';
            case P: return 'P'; case Q: return 'Q'; case R: return 'R'; case S: return 'S'; case T: return 'T';
            case U: return 'U'; case V: return 'V'; case W: return 'W'; case X: return 'X'; case Y: return 'Y';
            case Z: return 'Z';

            // Not supported
            default: return 0x00;
            }
         }
      };

      /// <summary>
      /// Mouse Button. Enum and Helpers.
      /// </summary>
      class MouseButton
      {
      public:
         enum Enum : uint8_t
         {
            Unknown      = 0x00,
            LeftButton   = 0x01,
            RightButton  = 0x02,
            MiddleButton = 0x03,
            X1Button     = 0x04,
            X2Button     = 0x05,
            _MAXIMUM     = 0x05     /* NOT A VALUE, MUST BE HIGHEST FROM ABOVE OR DIE */
         };
      };

      /// <summary>
      /// Mouse Button State for each Button.
      /// </summary>
      class MouseButtonState
      {
      public:
         bool     isdown;
         V2i      downpos;
         double   downtick;
         uint32_t numclicks;
         double   clickstart;
      };

   protected:
      static const size_t KEYSIZE         = UINT8_MAX;
      static const size_t MOUSEBUTTONSIZE = MouseButton::Enum::_MAXIMUM;

      double           mTick;
      uint32_t         mLastChar;
      double           mMouseButtonClicksTimeout;
      V3i              mMousePosition;
      V3i              mMousePositionLast;
      V3i              mMouseDelta;
      BBox2i           mMouseArea;
      bool             mMouseInArea;
      bool             mMouseInAreaLast;
      bool             mMouseLook;
      bool             mKey[KEYSIZE];
      MouseButtonState mMouseButton[MOUSEBUTTONSIZE];

   public:
      /// <summary>
      /// Constructor
      /// </summary>
      INLINE Input() :
         mTick(0.0),
         mLastChar(0),
         mMouseButtonClicksTimeout(333.333),
         mMousePosition(0),
         mMousePositionLast(0),
         mMouseDelta(0),
         mMouseArea(V2i(0), V2i(0)),
         mMouseInArea(false),
         mMouseInAreaLast(false),
         mMouseLook(false)
      {
         // init states to zero
         memset(mKey, 0, sizeof(mKey));
         memset(mMouseButton, 0, sizeof(mMouseButton));
      }

      //////////////////////////////////////////////////////////////////////////////////////////////
      // KEYBOARD
      //////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Injects key up for all keys.
      /// Triggers onKeyChanged for all that were actually down.
      /// </summary>
      INLINE void releaseKeys()
      {
         for (size_t k = 0; k < KEYSIZE; k++)
            injectKeyUp((Key::Enum)k);
      }

      /// <summary>
      /// True if key k is currently pressed.
      /// </summary>
      INLINE bool isKeyDown(const Key::Enum k) const
      {
         return mKey[k];
      }

      /// <summary>
      /// Notifies the Input that a key went down.
      /// Triggers onKeyChanged if state changed.
      /// </summary>
      INLINE virtual void injectKeyDown(const Key::Enum k)
      {
         if (!mKey[k])
         {
            mKey[k] = true;
            onKeyChanged(k, true);
         }
      }

      /// <summary>
      /// Notifies the Input that a key was released.
      /// Triggers onKeyChanged if state changed.
      /// </summary>
      INLINE virtual void injectKeyUp(const Key::Enum k)
      {
         if (mKey[k])
         {
            mKey[k] = false;
            onKeyChanged(k, false);
         }
      }

      /// <summary>
      /// Notifies the Input that a char was pressed.
      /// Triggers onCharacter.
      /// </summary>
      INLINE virtual void injectChar(const uint32_t c)
      {
         mLastChar = c;
         onCharacter(c);
      }

      /// <summary>
      /// Gets the last char that was injected.
      /// </summary>
      INLINE uint32_t getLastChar() const { return mLastChar; }

      //////////////////////////////////////////////////////////////////////////////////////////////
      // MOUSE AREA
      //////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Returns current mouse area.
      /// </summary>
      INLINE const BBox2i& getMouseArea() const
      {
         return mMouseArea;
      }

      /// <summary>
      /// Updates the mouse area.
      /// </summary>
      INLINE void setMouseArea(const BBox2i& area)
      {
         mMouseArea = area;
      }

      /// <summary>
      /// Updates the mouse area.
      /// </summary>
      INLINE void setMouseArea(const V2i& min, const V2i& max)
      {
         mMouseArea.min = min;
         mMouseArea.max = max;
      }

      /// <summary>
      /// Updates the mouse area.
      /// </summary>
      INLINE void setMouseArea(const int32_t left, const int32_t top, const int32_t right, const int32_t bottom)
      {
         mMouseArea.min.x = left;
         mMouseArea.min.y = top;
         mMouseArea.max.x = right;
         mMouseArea.max.y = bottom;
      }

      /// <summary>
      /// True if mouse position is in mouse area set by setMouseArea().
      /// Might change after a call to injectMousePoisition().
      /// </summary>
      INLINE bool isMouseInArea() const
      {
         return mMouseInArea;
      }

      /// <summary>
      /// True if previous mouse position was in mouse area set by setMouseArea().
      /// Might change after a call to injectMousePoisition().
      /// </summary>
      INLINE bool wasMouseInArea() const
      {
         return mMouseInAreaLast;
      }

      //////////////////////////////////////////////////////////////////////////////////////////////
      // MOUSE
      //////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// True if mouse look is currently enabled.
      /// </summary>
      INLINE bool isMouseLook() const { return mMouseLook; }

      /// <summary>
      /// Gets how many milliseconds you can make a second or third click after a first click.
      /// </summary>
      INLINE double getMouseButtonClicksTimeout() const { return mMouseButtonClicksTimeout; }

      /// <summary>
      /// Sets how many milliseconds you can make a second or third click after a first click.
      /// </summary>
      INLINE void setMouseButtonClicksTimeout(const double v) { mMouseButtonClicksTimeout = v; }

      /// <summary>
      /// True if given mousebutton is currently pressed.
      /// </summary>
      INLINE bool isMouseButtonDown(const MouseButton::Enum b) const
      {
         return b < MOUSEBUTTONSIZE ? mMouseButton[b].isdown : false;
      }

      /// <summary>
      /// True if given mousebutton has been pressed for at least given time span
      /// and if is still pressed.
      /// </summary>
      INLINE bool isMouseButtonDown(const MouseButton::Enum b, const double span) const
      {
         return isMouseButtonDown(b) && getMouseDownSpan(b) > span;
      }

      /// <summary>
      /// Shortcut. True if left mousebutton is currently pressed.
      /// </summary>
      INLINE bool isLeftMouseButtonDown() const
      {
         return isMouseButtonDown(MouseButton::LeftButton);
      }

      /// <summary>
      /// Shortcut. True if right mousebutton is currently pressed.
      /// </summary>
      INLINE bool isRightMouseButtonDown() const
      {
         return isMouseButtonDown(MouseButton::RightButton);
      }

      /// <summary>
      /// Shortcut. True if left and right mousebutton are currently pressed.
      /// </summary>
      INLINE bool isBothMouseButtonDown() const
      {
         return isLeftMouseButtonDown() && isRightMouseButtonDown();
      }

      /// <summary>
      /// Get the mouseposition where a mouse button went down last.
      /// </summary>
      INLINE V2i getMouseDownPosition(const MouseButton::Enum  b) const
      {
         return b < MOUSEBUTTONSIZE ? mMouseButton[b].downpos : 0;
      }

      /// <summary>
      /// Get the tick when a mouse button went down last.
      /// Meaningless if button is not down!
      /// </summary>
      INLINE double getMouseDownTick(const MouseButton::Enum  b) const
      {
         return b < MOUSEBUTTONSIZE ? mMouseButton[b].downtick : 0.0;
      }

      /// <summary>
      /// Get the time span that a mouse button has been pressed already.
      /// Meaningless if button is not down!
      /// </summary>
      INLINE double getMouseDownSpan(const MouseButton::Enum  b) const
      {
         return b < MOUSEBUTTONSIZE ? mTick - mMouseButton[b].downtick : 0.0;
      }

      /// <summary>
      /// Gets current mouse position.
      /// </summary>
      INLINE const V2i& getMousePosition() const { return mMousePosition.ref<V2i>(); }

      /// <summary>
      /// Gets last mouse position.
      /// </summary>
      INLINE const V2i& getMousePositionLast() const { return mMousePositionLast.ref<V2i>(); }

      /// <summary>
      /// Gets current relative mouse position with 0 being at minimum of mouse-area
      /// and 1 being at maximum of mouse area.
      /// </summary>
      INLINE V2f getMousePositionRelative() const
      {
         const V2i& size = mMouseArea.size();
         return size != 0 ? V2f(mMousePosition.ref<V2i>()) / V2f(size) : 0.0f;
      }

      /// <summary>
      /// Gets delta between last and current mouse position.
      /// </summary>
      INLINE const V2i& getMouseDelta() const { return mMouseDelta.ref<V2i>(); }

      /// <summary>
      /// Gets current mouse wheel position.
      /// </summary>
      INLINE int32_t getMouseWheelPosition() const { return mMousePosition.z; }

      /// <summary>
      /// Notifies the Input that a mouse button went down.
      /// </summary>
      INLINE virtual void injectMouseButtonDown(const MouseButton::Enum b)
      {
         if (b < MOUSEBUTTONSIZE && !mMouseButton[b].isdown)
         {
            mMouseButton[b].isdown = true;
            mMouseButton[b].downpos = mMousePosition.ref<V2i>();
            mMouseButton[b].downtick = mTick;
            onMouseButtonChanged(b, true);
         }
      }

      /// <summary>
      /// Notifies the Input that a mouse button was released.
      /// </summary>
      INLINE virtual void injectMouseButtonUp(const MouseButton::Enum b)
      {
         if (b < MOUSEBUTTONSIZE && mMouseButton[b].isdown)
         {
            mMouseButton[b].isdown = false;
            onMouseButtonChanged(b, false);
         }
      }

      /// <summary>
      /// Injects a mouse wheel change (z coordinate) to the Input.
      /// </summary>
      INLINE virtual void injectMouseWheelChange(const int32_t z)
      {
         mMouseDelta.z        = z;
         mMousePositionLast.z = mMousePosition.z;
         mMousePosition.z    += z;

         // wheeling inside mouse area
         if (mMouseInArea && mMouseDelta.z != 0)
            onMouseWheel(z);
      }

      /// <summary>
      /// Injects a new mouse position to the Input.
      /// </summary>
      INLINE virtual void injectMousePosition(const V2i& p)
      {
         // calculate delta
         const V2i delta = p - mMousePosition.ref<V2i>();

         // no change
         if (delta.isZero())
            return;

         // set new delta
         mMouseDelta.ref<V2i>() = delta;

         // mouse look mode
         if (mMouseLook)
            onMouseLooking();

         // normal mode
         else
         {
            mMousePositionLast.ref<V2i>() = mMousePosition.ref<V2i>(); // save x,y, into last
            mMousePosition.ref<V2i>()     = p;                         // set new x,y
            mMouseInAreaLast              = mMouseInArea;              // save to last in-area
            mMouseInArea                  = mMouseArea.inside(p);      // update in-area state

            // leaving mouse area
            if (mMouseInAreaLast && !mMouseInArea)
            {
               releaseMouseButtons();
               onMouseLeave();
            }

            // entering mouse area
            else if (!mMouseInAreaLast && mMouseInArea)
               onMouseEnter();

            // moving inside mouse area
            if (mMouseInArea)
               onMouseMove(mMousePosition.ref<V2i>());
         }
      }

      /// <summary>
      /// Injects a new mouse position to the Input.
      /// </summary>
      INLINE virtual void injectMousePosition(const int32_t x, const int32_t y)
      {
         injectMousePosition(V2i(x, y));
      }

      /// <summary>
      /// Injects mouse button up event for all mouse buttons that are currently down.
      /// </summary>
      INLINE void releaseMouseButtons()
      {
         for (size_t b = 0; b < MOUSEBUTTONSIZE; b++)
            injectMouseButtonUp((MouseButton::Enum)b);
      }

      //////////////////////////////////////////////////////////////////////////////////////////////
      // EVENTS
      //////////////////////////////////////////////////////////////////////////////////////////////

      /// <summary>
      /// Executed when a key went down or up
      /// </summary>
      INLINE virtual void onKeyChanged(const Key::Enum k, const bool down) { }

      /// <summary>
      /// Executed when a character code was received
      /// </summary>
      INLINE virtual void onCharacter(const uint32_t c) { }

      /// <summary>
      /// Executed when a mouse button was pressed or released
      /// </summary>
      INLINE virtual void onMouseButtonChanged(const MouseButton::Enum b, const bool down) { }

      /// <summary>
      /// Executed when the mouse is wheeled
      /// </summary>
      INLINE virtual void onMouseWheel(const int32_t delta) { }

      /// <summary>
      /// Executed when the mouse entered the defined mouse area
      /// </summary>
      INLINE virtual void onMouseEnter() { }

      /// <summary>
      /// Executed when the mouse left the defined mouse area
      /// </summary>
      INLINE virtual void onMouseLeave() { }

      /// <summary>
      /// Executed when the mouse moved and mouselook is not active
      /// </summary>
      INLINE virtual void onMouseMove(const V2i& p) { }

      /// <summary>
      /// Executed when mouse is moved while mouselook is active
      /// </summary>
      INLINE virtual void onMouseLooking() { }
   };
}
