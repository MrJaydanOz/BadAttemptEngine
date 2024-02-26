#pragma once

class ColorF;

class Color
{
public:
	unsigned char r, g, b, a;

	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = (unsigned char)0xFF);
	Color(unsigned int hex);

	Color& operator=(unsigned int hex);

	operator ColorF() const;
};

class ColorF
{
public:
	float r, g, b, a;

	ColorF(float r, float g, float b, float a = 1.0f);

	explicit operator Color() const;
};