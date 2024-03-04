#include "Graphics/Color.h"
#include <cmath>

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) noexcept : r(r), g(g), b(b), a(a) { }

Color::Color(unsigned int hex) noexcept :
	r((hex & 0xFF000000) >> (6 * 4)),
	g((hex & 0x00FF0000) >> (4 * 4)),
	b((hex & 0x0000FF00) >> (2 * 4)),
	a((hex & 0x000000FF) >> (0 * 4)) { }

Color& Color::operator=(unsigned int hex) noexcept
{
	r = (hex & 0xFF000000) >> (6 * 4);
	g = (hex & 0x00FF0000) >> (4 * 4);
	b = (hex & 0x0000FF00) >> (2 * 4);
	a = (hex & 0x000000FF) >> (0 * 4);

	return *this;
}

Color::operator ColorF() const noexcept
{
	const float reciprocal = 1.0f / 255.0f;
	return ColorF(r * reciprocal, g * reciprocal, b * reciprocal, a * reciprocal);
}

ColorF::ColorF(float r, float g, float b, float a) noexcept : r(r), g(g), b(b), a(a) { }

ColorF::ColorF(unsigned int hex) noexcept
{
	const float reciprocal = 1.0f / 255.0f;

	r = ((hex & 0xFF000000) >> (6 * 4)) * reciprocal;
	g = ((hex & 0x00FF0000) >> (4 * 4)) * reciprocal;
	b = ((hex & 0x0000FF00) >> (2 * 4)) * reciprocal;
	a = ((hex & 0x000000FF) >> (0 * 4)) * reciprocal;
}

ColorF& ColorF::operator=(unsigned int hex) noexcept { return (ColorF)Color(hex); }

ColorF::operator Color() const noexcept
{
	return Color(
		(unsigned char)std::max(0l, std::min(std::lroundf(r * 255.0f), 255l)),
		(unsigned char)std::max(0l, std::min(std::lroundf(g * 255.0f), 255l)),
		(unsigned char)std::max(0l, std::min(std::lroundf(b * 255.0f), 255l)),
		(unsigned char)std::max(0l, std::min(std::lroundf(a * 255.0f), 255l)));
}
