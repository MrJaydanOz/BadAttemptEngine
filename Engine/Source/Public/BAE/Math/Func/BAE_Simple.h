#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Simple.h"))
#endif
#include <type_traits>
#include <cmath>

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

	_NODISCARD float Sqrt(in<float> v) noexcept(noexcept(sqrt(v)));
	_NODISCARD double Sqrt(in<double> v) noexcept(noexcept(sqrt(v)));
	_NODISCARD long double Sqrt(in<long double> v) noexcept(noexcept(sqrt(v)));
	
	template<typename TValue, typename TProgress>
	_NODISCARD constexpr TValue Lerp(in<TValue> a, in<TValue> b, in<TProgress> t) noexcept(noexcept(a + ((b - a) * t)))
	{ return a + ((b - a) * t); }
	template<typename T>
	_NODISCARD constexpr T InverseLerp(in<T> a, in<T> b, in<T> v) noexcept(noexcept((v - a) / (b - a)))
	{ return (v - a) / (b - a); }

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