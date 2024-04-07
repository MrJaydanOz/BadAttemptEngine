#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Comparison.h"))
#endif
#include <type_traits>
#include <cmath>

namespace bae
{
	template<typename T>
	_NODISCARD constexpr in<T> Min(in<T> a, in<T> b) noexcept(noexcept(a < b))
	{ return a < b ? a : b; }

	template<typename T>
	_NODISCARD constexpr in<T> Min(in<T> a, in<T> b, in<T> c) noexcept(noexcept(Min<T>(Min<T>(a, b), c)))
	{ return Min<T>(Min<T>(a, b), c); }

	template<typename T, typename TLessThanPredicate>
	_NODISCARD constexpr in<T> Min(in<T> a, in<T> b, in<TLessThanPredicate> predicate) noexcept(noexcept(predicate(a, b)))
	{ return predicate(a, b) ? a : b; }

	template<typename T, typename TLessThanPredicate>
	_NODISCARD constexpr in<T> Min(in<T> a, in<T> b, in<T> c, in<TLessThanPredicate> predicate) noexcept(noexcept(Min<T>(Min<T>(a, b, predicate), c, predicate)))
	{ return Min<T, TLessThanPredicate>(Min<T, TLessThanPredicate>(a, b, predicate), c, predicate); }

	template<typename T>
	_NODISCARD constexpr in<T> Max(in<T> a, in<T> b) noexcept(noexcept(a > b))
	{ return a > b ? a : b; }

	template<typename T>
	_NODISCARD constexpr in<T> Max(in<T> a, in<T> b, in<T> c) noexcept(noexcept(Max<T>(Max<T>(a, b), c)))
	{ return Max<T>(Max<T>(a, b), c); }

	template<typename T, typename TLessThanPredicate>
	_NODISCARD constexpr in<T> Max(in<T> a, in<T> b, in<TLessThanPredicate> predicate) noexcept(noexcept(predicate(a, b)))
	{ return predicate(a, b) ? b : a; }

	template<typename T, typename TLessThanPredicate>
	_NODISCARD constexpr in<T> Max(in<T> a, in<T> b, in<T> c, in<TLessThanPredicate> predicate) noexcept(noexcept(Max<T>(Max<T>(a, b, predicate), c, predicate)))
	{ return Max<T, TLessThanPredicate>(Max<T, TLessThanPredicate>(a, b, predicate), c, predicate); }

	template<typename T>
	_NODISCARD constexpr in<T> Clamp(in<T> value, in<T> min, in<T> max) noexcept(noexcept(Min<T>(Max<T>(min, value), max)))
	{ return Min<T>(Max<T>(min, value), max); }

	template<typename T, typename TLessThanPredicate>
	_NODISCARD constexpr in<T> Clamp(in<T> value, in<T> min, in<T> max, in<TLessThanPredicate> predicate) noexcept(noexcept(Min<T>(Max<T>(min, value, predicate), max, predicate)))
	{ return Min<T, TLessThanPredicate>(Max<T, TLessThanPredicate>(min, value, predicate), max, predicate); }
}