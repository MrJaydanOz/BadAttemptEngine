#pragma once
#include <type_traits>
#include <cmath>
#include "Def.h"

namespace bae
{
	template<typename T>
	_NODISCARD constexpr std::int_fit_t<-1> Sign(in<T> v) noexcept(noexcept(v > 0 ? true : v == 0))
	{ return v > 0 ? 1 : (v == 0 ? 0 : -1); }

	template<typename T>
	_NODISCARD constexpr T Sqr(in<T> v) noexcept(noexcept(v * v))
	{ return v * v; }

	template<typename T>
	_NODISCARD constexpr T Cube(in<T> v) noexcept(noexcept(v * v * v))
	{ return v * v * v; }

	_NODISCARD float32 Sqrt(in<float32> v) noexcept(noexcept(sqrt(v)))
	{ return std::sqrt(v); }
	_NODISCARD float64 Sqrt(in<float64> v) noexcept(noexcept(sqrt(v)))
	{ return std::sqrt(v); }
	_NODISCARD float128 Sqrt(in<float128> v) noexcept(noexcept(sqrt(v)))
	{ return std::sqrt(v); }

	template<typename T>
	constexpr void Swap(ref<T> a, ref<T> b) noexcept(noexcept(std::swap(a, b)))
	{ std::swap<T>(a, b); }
}