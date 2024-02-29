#pragma once

class ColorF;

class Color
{
public:
	unsigned char r, g, b, a;

	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = (unsigned char)0xFF) noexcept;
	Color(unsigned int hex) noexcept;

	Color& operator=(unsigned int hex) noexcept;

	operator ColorF() const noexcept;
};

class ColorF
{
public:
	float r, g, b, a;

	ColorF(float r, float g, float b, float a = 1.0f) noexcept;

	explicit operator Color() const noexcept;
};