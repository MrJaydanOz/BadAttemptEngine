#pragma once
#include <type_traits>
#include <cmath>
#include "BAE_Def.h"
#include "BAE_FOR.h"

namespace bae
{
	template<typename T>
	_NODISCARD constexpr bae::int_fit_t<-1> Sign(in<T> v) noexcept(noexcept(v > 0 ? true : v == 0))
	{ return v > 0 ? 1 : (v == 0 ? 0 : -1); }

	template<typename T>
	_NODISCARD constexpr T Sqr(in<T> v) noexcept(noexcept(v * v))
	{ return v * v; }

	template<typename T>
	_NODISCARD constexpr T Cube(in<T> v) noexcept(noexcept(v * v * v))
	{ return v * v * v; }

	_NODISCARD float32 Sqrt(in<float32> v) noexcept(noexcept(sqrt(v)));
	_NODISCARD float64 Sqrt(in<float64> v) noexcept(noexcept(sqrt(v)));
	_NODISCARD float128 Sqrt(in<float128> v) noexcept(noexcept(sqrt(v)));

	template<typename T>
	constexpr void Swap(ref<T> a, ref<T> b) noexcept(noexcept(std::swap(a, b)))
	{ std::swap<T>(a, b); }

	template<typename T>
	constexpr bool BitGet(in<T> bitMask, in<int> bitIndex)
	{ return (bitMask & ((T)1 << bitIndex)) != 0; }
	template<typename T>
	constexpr void BitSet(ref<T> bitMask, in<int> bitIndex, in<bool> value)
	{
		const T mask = (T)1 << bitIndex;
		bitMask &= ~mask;
		if (value)
			bitMask |= mask;
	}
}