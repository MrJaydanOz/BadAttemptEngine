#pragma once

class ColorF;

class Color
{
public:
	char r, g, b, a;

	Color(char r, char g, char b, char a = 0xFF);
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