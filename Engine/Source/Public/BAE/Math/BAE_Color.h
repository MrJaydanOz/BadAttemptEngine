#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Color.h"))
#endif
#include <cmath>

namespace bae
{
#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(struct Color))
#endif
	struct Color
	{
	public:
		uint8 r, g, b, a;

	public:
		constexpr Color(in<uint8> r, in<uint8> g, in<uint8> b, in<uint8> a = (uint8)0xFF) noexcept :
			r(r), g(g), b(b), a(a) { }
		constexpr Color(in<bae::uintx_t<8 * 4>> hex) noexcept :
			r((hex & 0xFF000000u) >> (6 * 4)),
			g((hex & 0x00FF0000u) >> (4 * 4)),
			b((hex & 0x0000FF00u) >> (2 * 4)),
			a((hex & 0x000000FFu) >> (0 * 4)) { }

		constexpr Color& operator=(in<bae::uintx_t<8 * 4>> hex) noexcept
		{
			r = (hex & 0xFF000000u) >> (6 * 4);
			g = (hex & 0x00FF0000u) >> (4 * 4);
			b = (hex & 0x0000FF00u) >> (2 * 4);
			a = (hex & 0x000000FFu) >> (0 * 4);

			return *this;
		}

		friend std::ostream& operator<<(ref<std::ostream> stream, in<Color> color)
		{
			return stream <<
				"(r:" << (int)color.r <<
				", g:" << (int)color.g <<
				", b:" << (int)color.b <<
				", a:" << (int)color.a << ')';
		}
	};

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(struct ColorF))
#endif
	struct ColorF
	{
	public:
		float r, g, b, a;

	public:
		constexpr ColorF(in<float> r, in<float> g, in<float> b, in<float> a = 1.0f) noexcept :
			r(r), g(g), b(b), a(a) { }
		constexpr ColorF(in<bae::uintx_t<8 * 4>> hex) noexcept :
			r(((hex & 0xFF000000u) >> (6 * 4))* (1.0f / 255.0f)),
			g(((hex & 0x00FF0000u) >> (4 * 4))* (1.0f / 255.0f)),
			b(((hex & 0x0000FF00u) >> (2 * 4))* (1.0f / 255.0f)),
			a(((hex & 0x000000FFu) >> (0 * 4))* (1.0f / 255.0f)) { }

		constexpr ColorF& operator=(in<bae::uintx_t<8 * 4>> hex) noexcept
		{
			r = ((hex & 0xFF000000u) >> (6 * 4)) * (1.0f / 255.0f);
			g = ((hex & 0x00FF0000u) >> (4 * 4)) * (1.0f / 255.0f);
			b = ((hex & 0x0000FF00u) >> (2 * 4)) * (1.0f / 255.0f);
			a = ((hex & 0x000000FFu) >> (0 * 4)) * (1.0f / 255.0f);

			return *this;
		}
		
		friend std::ostream& operator<<(ref<std::ostream> stream, in<ColorF> color)
		{
			return stream <<
				 "(r:" << std::setprecision(2) << std::fixed << color.r <<
				", g:" << std::setprecision(2) << std::fixed << color.g <<
				", b:" << std::setprecision(2) << std::fixed << color.b <<
				", a:" << std::setprecision(2) << std::fixed << color.a << ')';
		}

		constexpr explicit operator Color() const noexcept
		{
			return Color(
				(uint8)std::max(0l, std::min(std::lroundf(r * 255.0f), 255l)),
				(uint8)std::max(0l, std::min(std::lroundf(g * 255.0f), 255l)),
				(uint8)std::max(0l, std::min(std::lroundf(b * 255.0f), 255l)),
				(uint8)std::max(0l, std::min(std::lroundf(a * 255.0f), 255l)));
		}
	};

	static const bae::uintx_t<8 * 4> COLOR_WHITE =    0xFFFFFFFFu;
	static const bae::uintx_t<8 * 4> COLOR_BLACK =    0x000000FFu;
	static const bae::uintx_t<8 * 4> COLOR_RED =      0xFF0000FFu;
	static const bae::uintx_t<8 * 4> COLOR_YELLOW =   0xFFFF00FFu;
	static const bae::uintx_t<8 * 4> COLOR_GREEN =    0x00FF00FFu;
	static const bae::uintx_t<8 * 4> COLOR_AQUA =     0x00FFFFFFu;
	static const bae::uintx_t<8 * 4> COLOR_BLUE =     0x0000FFFFu;
	static const bae::uintx_t<8 * 4> COLOR_MAGENTA =  0xFF00FFFFu;
	static const bae::uintx_t<8 * 4> COLOR_CLEAR =    0x00000000u;
}