#pragma once
#include "Math/VectorT.h"

enum KeyCode : unsigned short
{
    UNKNOWN = 0,

    /*
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */

    A = 4,
    B = 5,
    C = 6,
    D = 7,
    E = 8,
    F = 9,
    G = 10,
    H = 11,
    I = 12,
    J = 13,
    K = 14,
    L = 15,
    M = 16,
    N = 17,
    O = 18,
    P = 19,
    Q = 20,
    R = 21,
    S = 22,
    T = 23,
    U = 24,
    V = 25,
    W = 26,
    X = 27,
    Y = 28,
    Z = 29,

    Num1 = 30,
    Num2 = 31,
    Num3 = 32,
    Num4 = 33,
    Num5 = 34,
    Num6 = 35,
    Num7 = 36,
    Num8 = 37,
    Num9 = 38,
    Num0 = 39,

    RETURN = 40,
    ESCAPE = 41,
    BACKSPACE = 42,
    TAB = 43,
    SPACE = 44,

    MINUS = 45,
    EQUALS = 46,
    LEFTBRACKET = 47,
    RIGHTBRACKET = 48,
    /// <summary>Located at the lower left of the return key on ISO keyboards and at the right end of the QWERTY row on ANSI keyboards. Produces REVERSE SOLIDUS (backslash) and VERTICAL LINE in a US layout, REVERSE SOLIDUS and VERTICAL LINE in a UK Mac layout, NUMBER SIGN and TILDE in a UK Windows layout, DOLLAR SIGN and POUND SIGN in a Swiss German layout, NUMBER SIGN and APOSTROPHE in a German layout, GRAVE ACCENT and POUND SIGN in a French Mac layout, and ASTERISK and MICRO SIGN in a French Windows layout.</summary>
    BACKSLASH = 49,
    /// <summary>ISO USB keyboards actually use this code instead of 49 for the same key, but all OSes I've seen treat the two codes identically. So, as an implementor, unless your keyboard generates both of those codes and your OS treats them differently, you should generate SDL_SCANCODE_BACKSLASH instead of this code. As a user, you should not rely on this code because SDL will never generate it with most (all?) keyboards.</summary>
    NONUSHASH = 50,
    SEMICOLON = 51,
    APOSTROPHE = 52,
    /// <summary>Located in the top left corner (on both ANSI and ISO keyboards). Produces GRAVE ACCENT and TILDE in a US Windows layout and in US and UK Mac layouts on ANSI keyboards, GRAVE ACCENT and NOT SIGN in a UK Windows layout, SECTION SIGN and PLUS-MINUS SIGN in US and UK Mac layouts on ISO keyboards, SECTION SIGN and DEGREE SIGN in a Swiss German layout (Mac: only on ISO keyboards), CIRCUMFLEX ACCENT and DEGREE SIGN in a German layout (Mac: only on ISO keyboards), SUPERSCRIPT TWO and TILDE in a French Windows layout, COMMERCIAL AT and NUMBER SIGN in a French Mac layout on ISO keyboards, and LESS-THAN SIGN and GREATER-THAN SIGN in a Swiss German, German, or French Mac layout on ANSI keyboards.</summary>
    GRAVE = 53,
    COMMA = 54,
    PERIOD = 55,
    SLASH = 56,

    CAPSLOCK = 57,

    F1 = 58,
    F2 = 59,
    F3 = 60,
    F4 = 61,
    F5 = 62,
    F6 = 63,
    F7 = 64,
    F8 = 65,
    F9 = 66,
    F10 = 67,
    F11 = 68,
    F12 = 69,

    PRINTSCREEN = 70,
    SCROLLLOCK = 71,
    PAUSE = 72,
    /// <summary>insert on PC, help on some Mac keyboards (but does send code 73, not 117)</summary>
    INSERT = 73,
    HOME = 74,
    PAGEUP = 75,
    DELETE = 76,
    END = 77,
    PAGEDOWN = 78,
    RIGHT = 79,
    LEFT = 80,
    DOWN = 81,
    UP = 82,

    /// <summary>num lock on PC, clear on Mac keyboards</summary>
    NUMLOCKCLEAR = 83,
    KP_DIVIDE = 84,
    KP_MULTIPLY = 85,
    KP_MINUS = 86,
    KP_PLUS = 87,
    KP_ENTER = 88,
    KP_1 = 89,
    KP_2 = 90,
    KP_3 = 91,
    KP_4 = 92,
    KP_5 = 93,
    KP_6 = 94,
    KP_7 = 95,
    KP_8 = 96,
    KP_9 = 97,
    KP_0 = 98,
    KP_PERIOD = 99,

    /// <summary>This is the additional key that keyboards have over ANSI oneslocated between left shift and YProduces GRAVE ACCENT and TILDE in US or UK Mac layout, REVERSE (backslash) and VERTICAL LINE in US or UK Windows layout, LESS-THAN SIGN and GREATER-THAN in a Swiss German, German, or layout.</summary>
    NONUSBACKSLASH = 100,
    /// <summary>windows contextual menu, compose</summary>
    APPLICATION = 101, /**<  */
    /// <summary>The USB document says this is a status flag, not a physical key - but some Mac keyboards do have a power key.</summary>
    POWER = 102,
    KP_EQUALS = 103,
    F13 = 104,
    F14 = 105,
    F15 = 106,
    F16 = 107,
    F17 = 108,
    F18 = 109,
    F19 = 110,
    F20 = 111,
    F21 = 112,
    F22 = 113,
    F23 = 114,
    F24 = 115,
    EXECUTE = 116,
    /// <summary>AL Integrated Help Center</summary>
    HELP = 117, 
    /// <summary>Menu (show menu)</summary>
    MENU = 118, 
    SELECT = 119,
    /// <summary>AC Stop</summary>
    STOP = 120,
    /// <summary>AC Redo/Repeat</summary>
    AGAIN = 121,
    /// <summary>AC Undo</summary>
    UNDO = 122,
    /// <summary>AC Cut</summary>
    CUT = 123,
    /// <summary>AC Copy</summary>
    COPY = 124,
    /// <summary>AC Paste</summary>
    PASTE = 125,
    /// <summary>AC Find</summary>
    FIND = 126,
    MUTE = 127,
    VOLUMEUP = 128,
    VOLUMEDOWN = 129,

/* not sure whether there's a reason to enable these
    LOCKINGCAPSLOCK = 130,
    LOCKINGNUMLOCK = 131,
    LOCKINGSCROLLLOCK = 132,
*/
    KP_COMMA = 133,
    KP_EQUALSAS400 = 134,

    /// <summary>used on Asian keyboards, see footnotes in USB doc</summary>
    INTERNATIONAL1 = 135,
    INTERNATIONAL2 = 136,
    /// <summary>Yen</summary>
    INTERNATIONAL3 = 137,
    INTERNATIONAL4 = 138,
    INTERNATIONAL5 = 139,
    INTERNATIONAL6 = 140,
    INTERNATIONAL7 = 141,
    INTERNATIONAL8 = 142,
    INTERNATIONAL9 = 143,
    /// <summary>Hangul/English toggle</summary>
    LANG1 = 144,
    /// <summary>Hanja conversion</summary>
    LANG2 = 145,
    /// <summary>Katakana</summary>
    LANG3 = 146,
    /// <summary>Hiragana</summary>
    LANG4 = 147,
    /// <summary>Zenkaku/Hankaku</summary>
    LANG5 = 148,
    /// <summary>reserved</summary>
    LANG6 = 149,
    /// <summary>reserved</summary>
    LANG7 = 150,
    /// <summary>reserved</summary>
    LANG8 = 151,
    /// <summary>reserved</summary>
    LANG9 = 152,

    /// <summary>Erase-Eaze</summary>
    ALTERASE = 153,
    SYSREQ = 154,
    /// <summary>AC Cancel</summary>
    CANCEL = 155,
    CLEAR = 156,
    PRIOR = 157,
    RETURN2 = 158,
    SEPARATOR = 159,
    OUT = 160,
    OPER = 161,
    CLEARAGAIN = 162,
    CRSEL = 163,
    EXSEL = 164,

    KP_00 = 176,
    KP_000 = 177,
    THOUSANDSSEPARATOR = 178,
    DECIMALSEPARATOR = 179,
    CURRENCYUNIT = 180,
    CURRENCYSUBUNIT = 181,
    KP_LEFTPAREN = 182,
    KP_RIGHTPAREN = 183,
    KP_LEFTBRACE = 184,
    KP_RIGHTBRACE = 185,
    KP_TAB = 186,
    KP_BACKSPACE = 187,
    KP_A = 188,
    KP_B = 189,
    KP_C = 190,
    KP_D = 191,
    KP_E = 192,
    KP_F = 193,
    KP_XOR = 194,
    KP_POWER = 195,
    KP_PERCENT = 196,
    KP_LESS = 197,
    KP_GREATER = 198,
    KP_AMPERSAND = 199,
    KP_DBLAMPERSAND = 200,
    KP_VERTICALBAR = 201,
    KP_DBLVERTICALBAR = 202,
    KP_COLON = 203,
    KP_HASH = 204,
    KP_SPACE = 205,
    KP_AT = 206,
    KP_EXCLAM = 207,
    KP_MEMSTORE = 208,
    KP_MEMRECALL = 209,
    KP_MEMCLEAR = 210,
    KP_MEMADD = 211,
    KP_MEMSUBTRACT = 212,
    KP_MEMMULTIPLY = 213,
    KP_MEMDIVIDE = 214,
    KP_PLUSMINUS = 215,
    KP_CLEAR = 216,
    KP_CLEARENTRY = 217,
    KP_BINARY = 218,
    KP_OCTAL = 219,
    KP_DECIMAL = 220,
    KP_HEXADECIMAL = 221,

    LCTRL = 224,
    LSHIFT = 225,
    /// <summary>alt, option</summary>
    LALT = 226,
    /// <summary>windows, command (apple), meta</summary>
    LGUI = 227,
    RCTRL = 228,
    RSHIFT = 229,
    /// <summary>alt gr, option</summary>
    RALT = 230,
    /// <summary>windows, command (apple), meta</summary>
    RGUI = 231,

    /// <summary>I'm not sure if this is really not covered by any of the above, but since there's a special KMOD_MODE for it I'm adding it here</summary>
    MODE = 257,

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

    AUDIONEXT = 258,
    AUDIOPREV = 259,
    AUDIOSTOP = 260,
    AUDIOPLAY = 261,
    AUDIOMUTE = 262,
    MEDIASELECT = 263,
    /// <summary>AL Internet Browser</summary>
    WWW = 264,
    MAIL = 265,
    /// <summary>AL Calculator</summary>
    CALCULATOR = 266,
    COMPUTER = 267,
    /// <summary>AC Search</summary>
    AC_SEARCH = 268,
    /// <summary>AC Home</summary>
    AC_HOME = 269,
    /// <summary>AC Back</summary>
    AC_BACK = 270,
    /// <summary>AC Forward</summary>
    AC_FORWARD = 271,
    /// <summary>AC Stop</summary>
    AC_STOP = 272,
    /// <summary>AC Refresh</summary>
    AC_REFRESH = 273,
    /// <summary>AC Bookmarks</summary>
    AC_BOOKMARKS = 274,

    /* Usage page 0x0C */

    /*
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */

    BRIGHTNESSDOWN = 275,
    BRIGHTNESSUP = 276,
    /// <summary>display mirroring/dual display switch, video mode switch</summary>
    DISPLAYSWITCH = 277,
    KBDILLUMTOGGLE = 278,
    KBDILLUMDOWN = 279,
    KBDILLUMUP = 280,
    EJECT = 281,
    /// <summary>SC System Sleep</summary>
    SLEEP = 282,

    APP1 = 283,
    APP2 = 284,

    /* Walther keys */

    /*
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */

    AUDIOREWIND = 285,
    AUDIOFASTFORWARD = 286,

    /* Usage page 0x0C (additional media keys) */

    /*
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */

    /// <summary>Usually situated below the display on phones and used as a multi-function feature key for selecting a software defined function shown on the bottom left of the display.</summary>
    SOFTLEFT = 287,
    /// <summary>Usually situated below the display on phones and used as a multi-function feature key for selecting a software defined function shown on the bottom right of the display.</summary>
    SOFTRIGHT = 288,
    /// <summary>Used for accepting phone calls.</summary>
    CALL = 289,
    /// <summary>Used for rejecting phone calls.</summary>
    ENDCALL = 290,

    /* Mobile keys */

    /* Add any other keys here. */

    /// <summary>Left mouse button.</summary>
    LMB = 400,
    /// <summary>Right mouse button.</summary>
    RMB = 401,
    /// <summary>Middle mouse button.</summary>
    MMB = 402,

    /// <summary>Not a key, just marks the number of codes for array bounds.</summary>
    NUM_CODES = 512
};

class Input
{
private:
    unsigned char _previousKeyStates[NUM_CODES];

public:
    Input();
    ~Input();

	void ProcessInput();

    bool KeyHeld(KeyCode keyCode) const;
    bool KeyPressed(KeyCode keyCode) const;
    bool KeyReleased(KeyCode keyCode) const;

    Vector2I MousePosition() const;
};