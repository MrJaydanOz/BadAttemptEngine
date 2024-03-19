#pragma once

class ColorF;

class Color
{
public:
	unsigned char r, g, b, a;

public:
	constexpr Color(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a = (unsigned char)0xFF) noexcept;
	constexpr Color(const unsigned int& hex) noexcept;

	constexpr Color& operator=(const unsigned int& hex) noexcept;

	constexpr operator ColorF() const noexcept;
};

class ColorF
{
public:
	float r, g, b, a;

public:
	constexpr ColorF(const float& r, const float& g, const float& b, const float& a = 1.0f) noexcept;
	constexpr ColorF(const unsigned int& hex) noexcept;

	constexpr ColorF& operator=(const unsigned int& hex) noexcept;

	constexpr explicit operator Color() const noexcept;
};

const Color COLOR_WHITE   = 0xFFFFFFFFu;
const Color COLOR_BLACK   = 0x000000FFu;
const Color COLOR_RED     = 0xFF0000FFu;
const Color COLOR_YELLOW  = 0xFFFF00FFu;
const Color COLOR_GREEN   = 0x00FF00FFu;
const Color COLOR_AQUA    = 0x00FFFFFFu;
const Color COLOR_BLUE    = 0x0000FFFFu;
const Color COLOR_MAGENTA = 0xFF00FFFFu;
const Color COLOR_CLEAR   = 0x00000000u;

const Color COLOUR_WHITE   = COLOR_WHITE;
const Color COLOUR_BLACK   = COLOR_BLACK;
const Color COLOUR_RED     = COLOR_RED;
const Color COLOUR_YELLOW  = COLOR_YELLOW;
const Color COLOUR_GREEN   = COLOR_GREEN;
const Color COLOUR_AQUA    = COLOR_AQUA;
const Color COLOUR_BLUE    = COLOR_BLUE;
const Color COLOUR_MAGENTA = COLOR_MAGENTA;
const Color COLOUR_CLEAR   = COLOR_CLEAR;