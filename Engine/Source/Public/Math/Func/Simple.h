#pragma once
#include <type_traits>
#include <cmath>
#include "Def.h";

namespace bae
{
	template<typename T>
	_NODISCARD constexpr signed char Sign(IN(T) v) noexcept(noexcept(v > 0 ? true : v == 0))
	{ return v > 0 ? 1 : (v == 0 ? 0 : -1); }

	template<typename T>
	_NODISCARD constexpr T Sqr(IN(T) v) noexcept(noexcept(v * v))
	{ return v * v; }

	template<typename T>
	_NODISCARD constexpr T Cube(IN(T) v) noexcept(noexcept(v * v * v))
	{ return v * v * v; }

	template<typename T>
	_NODISCARD T Sqrt(IN(T) v) noexcept(noexcept(sqrt(v)))
	{ return std::sqrt(v); }

	template<typename T>
	constexpr void Swap(REF(T) a, REF(T) b) noexcept(noexcept(std::swap(a, b)))
	{ std::swap(a, b); }
}