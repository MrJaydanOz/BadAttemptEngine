#include "Graphics/Color.h"
#include <cmath>

Color::Color(char r, char g, char b, char a) : r(r), g(g), b(b), a(a) { }

Color::Color(unsigned int hex) :
	r((hex & 0xFF000000) >> (6 * 8)),
	g((hex & 0x00FF0000) >> (4 * 8)),
	b((hex & 0x0000FF00) >> (2 * 8)),
	a((hex & 0x000000FF) >> (0 * 8)) { }

Color& Color::operator=(unsigned int hex)
{
	r = (hex & 0xFF000000) >> (6 * 8);
	g = (hex & 0x00FF0000) >> (4 * 8);
	b = (hex & 0x0000FF00) >> (2 * 8);
	a = (hex & 0x000000FF) >> (0 * 8);

	return *this;
}

Color::operator ColorF() const
{
	const float reciprocal = 1.0f / 255.0f;
	return ColorF(r * reciprocal, g * reciprocal, b * reciprocal, a * reciprocal);
}

ColorF::ColorF(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }

ColorF::operator Color() const
{
	return Color(
		std::min(0l, std::max<long>(std::lroundf(r * 255.0f), 255l)), 
		std::min(0l, std::max<long>(std::lroundf(g * 255.0f), 255l)),
		std::min(0l, std::max<long>(std::lroundf(b * 255.0f), 255l)),
		std::min(0l, std::max<long>(std::lroundf(a * 255.0f), 255l)));
}
