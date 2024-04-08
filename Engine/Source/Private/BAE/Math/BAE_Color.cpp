#include "Math/BAE_Color.h"
#include <cmath>

namespace bae
{
	constexpr Color::Color(in<uint8> r, in<uint8> g, in<uint8> b, in<uint8> a) noexcept :
		r(r), g(g), b(b), a(a) { }

	constexpr Color::Color(in<bae::uintx_t<8 * 4>> hex) noexcept :
		r((hex & 0xFF000000u) >> (6 * 4)),
		g((hex & 0x00FF0000u) >> (4 * 4)),
		b((hex & 0x0000FF00u) >> (2 * 4)),
		a((hex & 0x000000FFu) >> (0 * 4)) { }

	constexpr Color& Color::operator=(in<bae::uintx_t<8 * 4>> hex) noexcept
	{
		r = (hex & 0xFF000000u) >> (6 * 4);
		g = (hex & 0x00FF0000u) >> (4 * 4);
		b = (hex & 0x0000FF00u) >> (2 * 4);
		a = (hex & 0x000000FFu) >> (0 * 4);

		return *this;
	}

	std::ostream& operator<<(ref<std::ostream> stream, in<Color> color)
	{
		return stream <<
			 "(r:" << (int)color.r <<
			", g:" << (int)color.g <<
			", b:" << (int)color.b <<
			", a:" << (int)color.a << ')';
	}

	constexpr Color::operator ColorF() const noexcept
	{
		const float reciprocal = 1.0f / 255.0f;
		return ColorF(r * reciprocal, g * reciprocal, b * reciprocal, a * reciprocal);
	}

	constexpr ColorF::ColorF(in<float> r, in<float> g, in<float> b, in<float> a) noexcept :
		r(r), g(g), b(b), a(a) { }

	constexpr ColorF::ColorF(in<bae::uintx_t<8 * 4>> hex) noexcept :
		r(((hex & 0xFF000000u) >> (6 * 4)) * (1.0f / 255.0f)),
		g(((hex & 0x00FF0000u) >> (4 * 4)) * (1.0f / 255.0f)),
		b(((hex & 0x0000FF00u) >> (2 * 4)) * (1.0f / 255.0f)),
		a(((hex & 0x000000FFu) >> (0 * 4)) * (1.0f / 255.0f)) { }

	constexpr ColorF& ColorF::operator=(in<bae::uintx_t<8 * 4>> hex) noexcept
	{
		r = ((hex & 0xFF000000u) >> (6 * 4)) * (1.0f / 255.0f);
		g = ((hex & 0x00FF0000u) >> (4 * 4)) * (1.0f / 255.0f);
		b = ((hex & 0x0000FF00u) >> (2 * 4)) * (1.0f / 255.0f);
		a = ((hex & 0x000000FFu) >> (0 * 4)) * (1.0f / 255.0f);

		return *this;
	}

	std::ostream& operator<<(ref<std::ostream> stream, in<ColorF> color)
	{
		return stream <<
			 "(r:" << std::setprecision(2) << std::fixed << color.r <<
			", g:" << std::setprecision(2) << std::fixed << color.g <<
			", b:" << std::setprecision(2) << std::fixed << color.b <<
			", a:" << std::setprecision(2) << std::fixed << color.a << ')';
	}

	constexpr ColorF::operator Color() const noexcept
	{
		return Color(
			(uint8)std::max(0l, std::min(std::lroundf(r * 255.0f), 255l)),
			(uint8)std::max(0l, std::min(std::lroundf(g * 255.0f), 255l)),
			(uint8)std::max(0l, std::min(std::lroundf(b * 255.0f), 255l)),
			(uint8)std::max(0l, std::min(std::lroundf(a * 255.0f), 255l)));
	}
}