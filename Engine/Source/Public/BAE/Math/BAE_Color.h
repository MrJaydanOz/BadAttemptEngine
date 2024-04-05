#pragma once
#include "BAE_Def.h"

namespace bae
{
	struct ColorF;

	struct Color
	{
	public:
		uint8 r, g, b, a;

	public:
		constexpr Color(in<uint8> r, in<uint8> g, in<uint8> b, in<uint8> a = (uint8)0xFF) noexcept;
		constexpr Color(in<bae::uintx_t<8 * 4>> hex) noexcept;

		constexpr Color& operator=(in<bae::uintx_t<8 * 4>> hex) noexcept;

		constexpr operator ColorF() const noexcept;
	};

	struct ColorF
	{
	public:
		float r, g, b, a;

	public:
		constexpr ColorF(in<float> r, in<float> g, in<float> b, in<float> a = 1.0f) noexcept;
		constexpr ColorF(in<bae::uintx_t<8 * 4>> hex) noexcept;

		constexpr ColorF& operator=(in<bae::uintx_t<8 * 4>> hex) noexcept;

		constexpr explicit operator Color() const noexcept;
	};

	static const Color COLOR_WHITE =    0xFFFFFFFFu;
	static const Color COLOR_BLACK =    0x000000FFu;
	static const Color COLOR_RED =      0xFF0000FFu;
	static const Color COLOR_YELLOW =   0xFFFF00FFu;
	static const Color COLOR_GREEN =    0x00FF00FFu;
	static const Color COLOR_AQUA =     0x00FFFFFFu;
	static const Color COLOR_BLUE =     0x0000FFFFu;
	static const Color COLOR_MAGENTA =  0xFF00FFFFu;
	static const Color COLOR_CLEAR =    0x00000000u;
}