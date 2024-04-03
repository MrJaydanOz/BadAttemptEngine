#pragma once
#include <type_traits>
#include <cmath>
#include "Def.h";

namespace bae
{
	template<typename T>
	_NODISCARD constexpr IN(T) Min(IN(T) a, IN(T) b) noexcept(noexcept(a < b))
	{ return a < b ? a : b; }

	template<typename T>
	_NODISCARD constexpr IN(T) Min(IN(T) a, IN(T) b, IN(T) c) noexcept(noexcept(Min<T>(Min<T>(a, b), c)))
	{ return Min<T>(Min<T>(a, b), c); }

	template<typename T, typename TLessThanPredicate>
	_NODISCARD constexpr IN(T) Min(IN(T) a, IN(T) b, IN(TLessThanPredicate) predicate) noexcept(noexcept(predicate(a, b)))
	{ return predicate(a, b) ? a : b; }

	template<typename T, typename TLessThanPredicate>
	_NODISCARD constexpr IN(T) Min(IN(T) a, IN(T) b, IN(T) c, IN(TLessThanPredicate) predicate) noexcept(noexcept(Min<T>(Min<T>(a, b, predicate), c, predicate)))
	{ return Min<T>(Min<T>(a, b, predicate), c, predicate); }

	template<typename T>
	_NODISCARD constexpr IN(T) Max(IN(T) a, IN(T) b) noexcept(noexcept(a > b))
	{ return a > b ? a : b; }

	template<typename T>
	_NODISCARD constexpr IN(T) Max(IN(T) a, IN(T) b, IN(T) c) noexcept(noexcept(Max<T>(Max<T>(a, b), c)))
	{ return Max<T>(Max<T>(a, b), c); }

	template<typename T, typename TLessThanPredicate>
	_NODISCARD constexpr IN(T) Max(IN(T) a, IN(T) b, IN(TLessThanPredicate) predicate) noexcept(noexcept(predicate(a, b)))
	{ return predicate(a, b) ? b : a; }

	template<typename T, typename TLessThanPredicate>
	_NODISCARD constexpr IN(T) Max(IN(T) a, IN(T) b, IN(T) c, IN(TLessThanPredicate) predicate) noexcept(noexcept(Max<T>(Max<T>(a, b, predicate), c, predicate)))
	{ return Max<T>(Max<T>(a, b, predicate), c, predicate); }
}