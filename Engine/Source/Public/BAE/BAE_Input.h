#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Input.h"))
#endif
#include "Math/BAE_VectorT.h"

union SDL_Event;

namespace bae
{
	class Game;
	
    enum class KeyCode : int_fit_t<512>
    {
        KEYCODE_UNKNOWN = 0,

        /*
         *  \name Usage page 0x07
         *
         *  These values are from usage page 0x07 (USB keyboard page).
         */

        KEYCODE_A = 4,
        KEYCODE_B = 5,
        KEYCODE_C = 6,
        KEYCODE_D = 7,
        KEYCODE_E = 8,
        KEYCODE_F = 9,
        KEYCODE_G = 10,
        KEYCODE_H = 11,
        KEYCODE_I = 12,
        KEYCODE_J = 13,
        KEYCODE_K = 14,
        KEYCODE_L = 15,
        KEYCODE_M = 16,
        KEYCODE_N = 17,
        KEYCODE_O = 18,
        KEYCODE_P = 19,
        KEYCODE_Q = 20,
        KEYCODE_R = 21,
        KEYCODE_S = 22,
        KEYCODE_T = 23,
        KEYCODE_U = 24,
        KEYCODE_V = 25,
        KEYCODE_W = 26,
        KEYCODE_X = 27,
        KEYCODE_Y = 28,
        KEYCODE_Z = 29,

        KEYCODE_Num1 = 30,
        KEYCODE_Num2 = 31,
        KEYCODE_Num3 = 32,
        KEYCODE_Num4 = 33,
        KEYCODE_Num5 = 34,
        KEYCODE_Num6 = 35,
        KEYCODE_Num7 = 36,
        KEYCODE_Num8 = 37,
        KEYCODE_Num9 = 38,
        KEYCODE_Num0 = 39,

        KEYCODE_RETURN = 40,
        KEYCODE_ESCAPE = 41,
        KEYCODE_BACKSPACE = 42,
        KEYCODE_TAB = 43,
        KEYCODE_SPACE = 44,

        KEYCODE_MINUS = 45,
        KEYCODE_EQUALS = 46,
        KEYCODE_LEFTBRACKET = 47,
        KEYCODE_RIGHTBRACKET = 48,
        /// <summary>Located at the lower left of the return key on ISO keyboards and at the right end of the QWERTY row on ANSI keyboards. Produces REVERSE SOLIDUS (backslash) and VERTICAL LINE in a US layout, REVERSE SOLIDUS and VERTICAL LINE in a UK Mac layout, NUMBER SIGN and TILDE in a UK Windows layout, DOLLAR SIGN and POUND SIGN in a Swiss German layout, NUMBER SIGN and APOSTROPHE in a German layout, GRAVE ACCENT and POUND SIGN in a French Mac layout, and ASTERISK and MICRO SIGN in a French Windows layout.</summary>
        KEYCODE_BACKSLASH = 49,
        /// <summary>ISO USB keyboards actually use this code instead of 49 for the same key, but all OSes I've seen treat the two codes identically. So, as an implementor, unless your keyboard generates both of those codes and your OS treats them differently, you should generate SDL_SCANCODE_BACKSLASH instead of this code. As a user, you should not rely on this code because SDL will never generate it with most (all?) keyboards.</summary>
        KEYCODE_NONUSHASH = 50,
        KEYCODE_SEMICOLON = 51,
        KEYCODE_APOSTROPHE = 52,
        /// <summary>Located in the top left corner (on both ANSI and ISO keyboards). Produces GRAVE ACCENT and TILDE in a US Windows layout and in US and UK Mac layouts on ANSI keyboards, GRAVE ACCENT and NOT SIGN in a UK Windows layout, SECTION SIGN and PLUS-MINUS SIGN in US and UK Mac layouts on ISO keyboards, SECTION SIGN and DEGREE SIGN in a Swiss German layout (Mac: only on ISO keyboards), CIRCUMFLEX ACCENT and DEGREE SIGN in a German layout (Mac: only on ISO keyboards), SUPERSCRIPT TWO and TILDE in a French Windows layout, COMMERCIAL AT and NUMBER SIGN in a French Mac layout on ISO keyboards, and LESS-THAN SIGN and GREATER-THAN SIGN in a Swiss German, German, or French Mac layout on ANSI keyboards.</summary>
        KEYCODE_GRAVE = 53,
        KEYCODE_COMMA = 54,
        KEYCODE_PERIOD = 55,
        KEYCODE_SLASH = 56,

        KEYCODE_CAPSLOCK = 57,

        KEYCODE_F1 = 58,
        KEYCODE_F2 = 59,
        KEYCODE_F3 = 60,
        KEYCODE_F4 = 61,
        KEYCODE_F5 = 62,
        KEYCODE_F6 = 63,
        KEYCODE_F7 = 64,
        KEYCODE_F8 = 65,
        KEYCODE_F9 = 66,
        KEYCODE_F10 = 67,
        KEYCODE_F11 = 68,
        KEYCODE_F12 = 69,

        KEYCODE_PRINTSCREEN = 70,
        KEYCODE_SCROLLLOCK = 71,
        KEYCODE_PAUSE = 72,
        /// <summary>insert on PC, help on some Mac keyboards (but does send code 73, not 117)</summary>
        KEYCODE_INSERT = 73,
        KEYCODE_HOME = 74,
        KEYCODE_PAGEUP = 75,
        KEYCODE_DELETE = 76,
        KEYCODE_END = 77,
        KEYCODE_PAGEDOWN = 78,
        KEYCODE_RIGHT = 79,
        KEYCODE_LEFT = 80,
        KEYCODE_DOWN = 81,
        KEYCODE_UP = 82,

        /// <summary>num lock on PC, clear on Mac keyboards</summary>
        KEYCODE_NUMLOCKCLEAR = 83,
        KEYCODE_KP_DIVIDE = 84,
        KEYCODE_KP_MULTIPLY = 85,
        KEYCODE_KP_MINUS = 86,
        KEYCODE_KP_PLUS = 87,
        KEYCODE_KP_ENTER = 88,
        KEYCODE_KP_1 = 89,
        KEYCODE_KP_2 = 90,
        KEYCODE_KP_3 = 91,
        KEYCODE_KP_4 = 92,
        KEYCODE_KP_5 = 93,
        KEYCODE_KP_6 = 94,
        KEYCODE_KP_7 = 95,
        KEYCODE_KP_8 = 96,
        KEYCODE_KP_9 = 97,
        KEYCODE_KP_0 = 98,
        KEYCODE_KP_PERIOD = 99,

        /// <summary>This is the additional key that keyboards have over ANSI oneslocated between left shift and YProduces GRAVE ACCENT and TILDE in US or UK Mac layout, REVERSE (backslash) and VERTICAL LINE in US or UK Windows layout, LESS-THAN SIGN and GREATER-THAN in a Swiss German, German, or layout.</summary>
        KEYCODE_NONUSBACKSLASH = 100,
        /// <summary>windows contextual menu, compose</summary>
        KEYCODE_APPLICATION = 101, /**<  */
        /// <summary>The USB document says this is a status flag, not a physical key - but some Mac keyboards do have a power key.</summary>
        KEYCODE_KEYCODE_POWER = 102,
        KEYCODE_KP_EQUALS = 103,
        KEYCODE_F13 = 104,
        KEYCODE_F14 = 105,
        KEYCODE_F15 = 106,
        KEYCODE_F16 = 107,
        KEYCODE_F17 = 108,
        KEYCODE_F18 = 109,
        KEYCODE_F19 = 110,
        KEYCODE_F20 = 111,
        KEYCODE_F21 = 112,
        KEYCODE_F22 = 113,
        KEYCODE_F23 = 114,
        KEYCODE_F24 = 115,
        KEYCODE_EXECUTE = 116,
        /// <summary>AL Integrated Help Center</summary>
        KEYCODE_HELP = 117, 
        /// <summary>Menu (show menu)</summary>
        KEYCODE_MENU = 118, 
        KEYCODE_SELECT = 119,
        /// <summary>AC Stop</summary>
        KEYCODE_STOP = 120,
        /// <summary>AC Redo/Repeat</summary>
        KEYCODE_AGAIN = 121,
        /// <summary>AC Undo</summary>
        KEYCODE_UNDO = 122,
        /// <summary>AC Cut</summary>
        KEYCODE_CUT = 123,
        /// <summary>AC Copy</summary>
        KEYCODE_COPY = 124,
        /// <summary>AC Paste</summary>
        KEYCODE_PASTE = 125,
        /// <summary>AC Find</summary>
        KEYCODE_FIND = 126,
        KEYCODE_MUTE = 127,
        KEYCODE_VOLUMEUP = 128,
        KEYCODE_VOLUMEDOWN = 129,

    /* not sure whether there's a reason to enable these
        LOCKINGCAPSLOCK = 130,
        LOCKINGNUMLOCK = 131,
        LOCKINGSCROLLLOCK = 132,
    */
        KEYCODE_KP_COMMA = 133,
        KEYCODE_KP_EQUALSAS400 = 134,

        /// <summary>used on Asian keyboards, see footnotes in USB doc</summary>
        KEYCODE_INTERNATIONAL1 = 135,
        KEYCODE_INTERNATIONAL2 = 136,
        /// <summary>Yen</summary>
        KEYCODE_INTERNATIONAL3 = 137,
        KEYCODE_INTERNATIONAL4 = 138,
        KEYCODE_INTERNATIONAL5 = 139,
        KEYCODE_INTERNATIONAL6 = 140,
        KEYCODE_INTERNATIONAL7 = 141,
        KEYCODE_INTERNATIONAL8 = 142,
        KEYCODE_INTERNATIONAL9 = 143,
        /// <summary>Hangul/English toggle</summary>
        KEYCODE_LANG1 = 144,
        /// <summary>Hanja conversion</summary>
        KEYCODE_LANG2 = 145,
        /// <summary>Katakana</summary>
        KEYCODE_LANG3 = 146,
        /// <summary>Hiragana</summary>
        KEYCODE_LANG4 = 147,
        /// <summary>Zenkaku/Hankaku</summary>
        KEYCODE_LANG5 = 148,
        /// <summary>reserved</summary>
        KEYCODE_LANG6 = 149,
        /// <summary>reserved</summary>
        KEYCODE_LANG7 = 150,
        /// <summary>reserved</summary>
        KEYCODE_LANG8 = 151,
        /// <summary>reserved</summary>
        KEYCODE_LANG9 = 152,

        /// <summary>Erase-Eaze</summary>
        KEYCODE_ALTERASE = 153,
        KEYCODE_SYSREQ = 154,
        /// <summary>AC Cancel</summary>
        KEYCODE_CANCEL = 155,
        KEYCODE_CLEAR = 156,
        KEYCODE_PRIOR = 157,
        KEYCODE_RETURN2 = 158,
        KEYCODE_SEPARATOR = 159,
        KEYCODE_OUT = 160,
        KEYCODE_OPER = 161,
        KEYCODE_CLEARAGAIN = 162,
        KEYCODE_CRSEL = 163,
        KEYCODE_EXSEL = 164,

        KEYCODE_KP_00 = 176,
        KEYCODE_KP_000 = 177,
        KEYCODE_THOUSANDSSEPARATOR = 178,
        KEYCODE_DECIMALSEPARATOR = 179,
        KEYCODE_CURRENCYUNIT = 180,
        KEYCODE_CURRENCYSUBUNIT = 181,
        KEYCODE_KP_LEFTPAREN = 182,
        KEYCODE_KP_RIGHTPAREN = 183,
        KEYCODE_KP_LEFTBRACE = 184,
        KEYCODE_KP_RIGHTBRACE = 185,
        KEYCODE_KP_TAB = 186,
        KEYCODE_KP_BACKSPACE = 187,
        KEYCODE_KP_A = 188,
        KEYCODE_KP_B = 189,
        KEYCODE_KP_C = 190,
        KEYCODE_KP_D = 191,
        KEYCODE_KP_E = 192,
        KEYCODE_KP_F = 193,
        KEYCODE_KP_XOR = 194,
        KEYCODE_KP_POWER = 195,
        KEYCODE_KP_PERCENT = 196,
        KEYCODE_KP_LESS = 197,
        KEYCODE_KP_GREATER = 198,
        KEYCODE_KP_AMPERSAND = 199,
        KEYCODE_KP_DBLAMPERSAND = 200,
        KEYCODE_KP_VERTICALBAR = 201,
        KEYCODE_KP_DBLVERTICALBAR = 202,
        KEYCODE_KP_COLON = 203,
        KEYCODE_KP_HASH = 204,
        KEYCODE_KP_SPACE = 205,
        KEYCODE_KP_AT = 206,
        KEYCODE_KP_EXCLAM = 207,
        KEYCODE_KP_MEMSTORE = 208,
        KEYCODE_KP_MEMRECALL = 209,
        KEYCODE_KP_MEMCLEAR = 210,
        KEYCODE_KP_MEMADD = 211,
        KEYCODE_KP_MEMSUBTRACT = 212,
        KEYCODE_KP_MEMMULTIPLY = 213,
        KEYCODE_KP_MEMDIVIDE = 214,
        KEYCODE_KP_PLUSMINUS = 215,
        KEYCODE_KP_CLEAR = 216,
        KEYCODE_KP_CLEARENTRY = 217,
        KEYCODE_KP_BINARY = 218,
        KEYCODE_KP_OCTAL = 219,
        KEYCODE_KP_DECIMAL = 220,
        KEYCODE_KP_HEXADECIMAL = 221,

        KEYCODE_LCTRL = 224,
        KEYCODE_LSHIFT = 225,
        /// <summary>alt, option</summary>
        KEYCODE_LALT = 226,
        /// <summary>windows, command (apple), meta</summary>
        KEYCODE_LGUI = 227,
        KEYCODE_RCTRL = 228,
        KEYCODE_RSHIFT = 229,
        /// <summary>alt gr, option</summary>
        KEYCODE_RALT = 230,
        /// <summary>windows, command (apple), meta</summary>
        KEYCODE_RGUI = 231,

        /// <summary>I'm not sure if this is really not covered by any of the above, but since there's a special KMOD_MODE for it I'm adding it here</summary>
        KEYCODE_MODE = 257,

        /* Usage page 0x07 */

        /*
         *  \name Usage page 0x0C
         *
         *  These values are mapped from usage page 0x0C (USB consumer page).
         *  See https://usb.org/sites/default/files/hut1_2.pdf
         *
         *  There are way more keys in the spec than we can represent in the
         *  current scancode range, so pick the ones that commonly come up in
         *  real world usage.
         */

        KEYCODE_AUDIONEXT = 258,
        KEYCODE_AUDIOPREV = 259,
        KEYCODE_AUDIOSTOP = 260,
        KEYCODE_AUDIOPLAY = 261,
        KEYCODE_AUDIOMUTE = 262,
        KEYCODE_MEDIASELECT = 263,
        /// <summary>AL Internet Browser</summary>
        KEYCODE_WWW = 264,
        KEYCODE_MAIL = 265,
        /// <summary>AL Calculator</summary>
        KEYCODE_CALCULATOR = 266,
        KEYCODE_COMPUTER = 267,
        /// <summary>AC Search</summary>
        KEYCODE_AC_SEARCH = 268,
        /// <summary>AC Home</summary>
        KEYCODE_AC_HOME = 269,
        /// <summary>AC Back</summary>
        KEYCODE_AC_BACK = 270,
        /// <summary>AC Forward</summary>
        KEYCODE_AC_FORWARD = 271,
        /// <summary>AC Stop</summary>
        KEYCODE_AC_STOP = 272,
        /// <summary>AC Refresh</summary>
        KEYCODE_AC_REFRESH = 273,
        /// <summary>AC Bookmarks</summary>
        KEYCODE_AC_BOOKMARKS = 274,

        /* Usage page 0x0C */

        /*
         *  \name Walther keys
         *
         *  These are values that Christian Walther added (for mac keyboard?).
         */

        KEYCODE_BRIGHTNESSDOWN = 275,
        KEYCODE_BRIGHTNESSUP = 276,
        /// <summary>display mirroring/dual display switch, video mode switch</summary>
        KEYCODE_DISPLAYSWITCH = 277,
        KEYCODE_KBDILLUMTOGGLE = 278,
        KEYCODE_KBDILLUMDOWN = 279,
        KEYCODE_KBDILLUMUP = 280,
        KEYCODE_EJECT = 281,
        /// <summary>SC System Sleep</summary>
        KEYCODE_SLEEP = 282,

        KEYCODE_APP1 = 283,
        KEYCODE_APP2 = 284,

        /* Walther keys */

        /*
         *  \name Usage page 0x0C (additional media keys)
         *
         *  These values are mapped from usage page 0x0C (USB consumer page).
         */

        KEYCODE_AUDIOREWIND = 285,
        KEYCODE_AUDIOFASTFORWARD = 286,

        /* Usage page 0x0C (additional media keys) */

        /*
         *  \name Mobile keys
         *
         *  These are values that are often used on mobile phones.
         */

        /// <summary>Usually situated below the display on phones and used as a multi-function feature key for selecting a software defined function shown on the bottom left of the display.</summary>
        KEYCODE_SOFTLEFT = 287,
        /// <summary>Usually situated below the display on phones and used as a multi-function feature key for selecting a software defined function shown on the bottom right of the display.</summary>
        KEYCODE_SOFTRIGHT = 288,
        /// <summary>Used for accepting phone calls.</summary>
        KEYCODE_CALL = 289,
        /// <summary>Used for rejecting phone calls.</summary>
        KEYCODE_ENDCALL = 290,

        /* Mobile keys */

        /* Add any other keys here. */

        /// <summary>Left mouse button.</summary>
        KEYCODE_LMB = 400,
        /// <summary>Right mouse button.</summary>
        KEYCODE_RMB = 401,
        /// <summary>Middle mouse button.</summary>
        KEYCODE_MMB = 402,

        /// <summary>Not a key, just marks the number of codes for array bounds.</summary>
        KEYCODE_NUM_CODES = 512
};

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Input))
#endif
	class Input
	{
		friend class Game;

	private:
		bool _isWorking;
        uint8 _previousKeyStates[(size_t)KeyCode::KEYCODE_NUM_CODES];

    public:
        _NODISCARD bool KeyHeld(in<KeyCode> keyCode) const noexcept;
        _NODISCARD bool KeyPressed(in<KeyCode> keyCode) const noexcept;
        _NODISCARD bool KeyReleased(in<KeyCode> keyCode) const noexcept;

        _NODISCARD Vector2I GetMousePosition() const noexcept;

	private:
		Input();
		~Input();

        void _ProcessInput();

        void _HandleWinMenuEvents(in<SDL_Event> event);
	};
}