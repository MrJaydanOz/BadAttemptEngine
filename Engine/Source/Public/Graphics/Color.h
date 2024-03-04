#pragma once

#define COLOR_WHITE   0xFFFFFFFFu
#define COLOR_BLACK   0x000000FFu
#define COLOR_RED     0xFF0000FFu
#define COLOR_YELLOW  0xFFFF00FFu
#define COLOR_GREEN   0x00FF00FFu
#define COLOR_AQUA    0x00FFFFFFu
#define COLOR_BLUE    0x0000FFFFu
#define COLOR_MAGENTA 0xFF00FFFFu
#define COLOR_CLEAR   0x00000000u

class ColorF;

class Color
{
public:
	unsigned char r, g, b, a;

public:
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = (unsigned char)0xFF) noexcept;
	Color(unsigned int hex) noexcept;

	Color& operator=(unsigned int hex) noexcept;

	operator ColorF() const noexcept;
};

class ColorF
{
public:
	float r, g, b, a;

public:
	ColorF(float r, float g, float b, float a = 1.0f) noexcept;
	ColorF(unsigned int hex) noexcept;

	ColorF& operator=(unsigned int hex) noexcept;

	explicit operator Color() const noexcept;
};