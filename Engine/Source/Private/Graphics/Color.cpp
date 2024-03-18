#include "Graphics/Color.h"
#include <cmath>

constexpr Color::Color(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a) noexcept : r(r), g(g), b(b), a(a) { }

constexpr Color::Color(const unsigned int& hex) noexcept :
	r((hex & 0xFF000000) >> (6 * 4)),
	g((hex & 0x00FF0000) >> (4 * 4)),
	b((hex & 0x0000FF00) >> (2 * 4)),
	a((hex & 0x000000FF) >> (0 * 4)) { }

constexpr Color& Color::operator=(const unsigned int& hex) noexcept
{
	r = (hex & 0xFF000000) >> (6 * 4);
	g = (hex & 0x00FF0000) >> (4 * 4);
	b = (hex & 0x0000FF00) >> (2 * 4);
	a = (hex & 0x000000FF) >> (0 * 4);

	return *this;
}

constexpr Color::operator ColorF() const noexcept
{
	const float reciprocal = 1.0f / 255.0f;
	return ColorF(r * reciprocal, g * reciprocal, b * reciprocal, a * reciprocal);
}

constexpr ColorF::ColorF(const float& r, const float& g, const float& b, const float& a) noexcept : r(r), g(g), b(b), a(a) { }

constexpr ColorF::ColorF(const unsigned int& hex) noexcept :
	r(((hex & 0xFF000000) >> (6 * 4)) * (1.0f / 255.0f)),
	g(((hex & 0x00FF0000) >> (4 * 4)) * (1.0f / 255.0f)),
	b(((hex & 0x0000FF00) >> (2 * 4)) * (1.0f / 255.0f)),
	a(((hex & 0x000000FF) >> (0 * 4)) * (1.0f / 255.0f)) { }

constexpr ColorF& ColorF::operator=(const unsigned int& hex) noexcept
{
	r = ((hex & 0xFF000000) >> (6 * 4)) * (1.0f / 255.0f);
	g = ((hex & 0x00FF0000) >> (4 * 4)) * (1.0f / 255.0f);
	b = ((hex & 0x0000FF00) >> (2 * 4)) * (1.0f / 255.0f);
	a = ((hex & 0x000000FF) >> (0 * 4)) * (1.0f / 255.0f);

	return *this;
}

constexpr ColorF::operator Color() const noexcept
{
	return Color(
		(unsigned char)std::max(0l, std::min(std::lroundf(r * 255.0f), 255l)),
		(unsigned char)std::max(0l, std::min(std::lroundf(g * 255.0f), 255l)),
		(unsigned char)std::max(0l, std::min(std::lroundf(b * 255.0f), 255l)),
		(unsigned char)std::max(0l, std::min(std::lroundf(a * 255.0f), 255l)));
}
