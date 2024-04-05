#pragma once
#include <type_traits>
#include <cmath>
#include "BAE_Def.h"

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
	{ return Min<T>(Min<T>(a, b, predicate), c, predicate); }

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
	{ return Max<T>(Max<T>(a, b, predicate), c, predicate); }
}