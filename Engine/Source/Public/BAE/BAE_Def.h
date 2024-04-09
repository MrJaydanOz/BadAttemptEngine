#pragma once
#include <iostream>
#include <iomanip> // gets "std::setprecision(int)"
#include <vcruntime.h> // gets "_NODISCARD"
#include <type_traits>
#include <limits> // gets "std::numeric_limits<T>"
#include <optional> // gets "std::optional<T>" (write '{}' for no value)
#include <initializer_list> // gets "std::initializer_list<T>"

#define _NODISCARD_ONLY_READ _NODISCARD_MSG( /* Just to add my own compiler message. */\
	"This function returns a value representing some property of an object and has no other " \
	"effects. It is not useful to call this function and discard the return value.")

#define _NODISCARD_RESULT _NODISCARD_MSG( /* Just to add my own compiler message. */\
	"This function returns a value that was calculated to get and has no other effects. It is not " \
	"useful to call this function and discard the return value.")

// I had to debug the compiler at one point because of the order of the #includes.
#if false
#define MESSAGE_WHEN_INCLUDED(...) " --[ Compiling '" __VA_ARGS__ "' ]--"
#endif
#if false
#define MESSAGE_WHEN_CLASS_DEFINED(...) " --[ Compiling '" #__VA_ARGS__ "' ]--"
#endif

typedef signed char            int8;
typedef unsigned char          uint8;
typedef signed short int       int16;
typedef unsigned short int     uint16;
typedef signed int             int32;
typedef unsigned int           uint32;
typedef signed long int        int64;
typedef unsigned long int      uint64;
typedef signed long long int   int128;
typedef unsigned long long int uint128;

namespace bae
{
	template<size_t bitCount>
	struct intx
	{
		using type = 
			std::conditional_t<(bitCount > 128), void, 
			std::conditional_t<(bitCount > 64), int128, 
			std::conditional_t<(bitCount > 32), int64, 
			std::conditional_t<(bitCount > 16), int32, 
			std::conditional_t<(bitCount > 8), int16, 
			std::conditional_t<(bitCount > 0), int8, void>>>>>>;
	};

	template<size_t bitCount>
	using intx_t = typename bae::intx<bitCount>::type;

	template<size_t bitCount>
	struct uintx
	{
		using type =
			std::conditional_t<(bitCount > 128), void,
			std::conditional_t<(bitCount > 64), uint128,
			std::conditional_t<(bitCount > 32), uint64,
			std::conditional_t<(bitCount > 16), uint32,
			std::conditional_t<(bitCount > 8), uint16,
			std::conditional_t<(bitCount > 0), uint8, void>>>>>>;
	};

	template<size_t bitCount>
	using uintx_t = typename bae::uintx<bitCount>::type;

	template<long long int limit>
	struct int_fit
	{
		using type =
			std::conditional_t<(limit > 0),
			std::conditional_t<(limit > std::numeric_limits<uint64>::max()), uint128,
			std::conditional_t<(limit > std::numeric_limits<uint32>::max()), uint64,
			std::conditional_t<(limit > std::numeric_limits<uint16>::max()), uint32,
			std::conditional_t<(limit > std::numeric_limits<uint8>::max()), uint16,
			std::conditional_t<(limit > 0), uint8, void>>>>>,
			std::conditional_t<(limit < std::numeric_limits<int64>::min()), int128,
			std::conditional_t<(limit < std::numeric_limits<int32>::min()), int64,
			std::conditional_t<(limit < std::numeric_limits<int16>::min()), int32,
			std::conditional_t<(limit < std::numeric_limits<int8>::min()), int16,
			std::conditional_t<(limit < 0), int8, void>>>>>>;
	};

	template<long long int limit>
	using int_fit_t = typename bae::int_fit<limit>::type;

	template<typename TLeft, typename TRight = TLeft>
	concept Equatable =
		requires(TLeft a, TRight b) { { a == b } -> std::convertible_to<bool>; }&&
		requires(TLeft a, TRight b) { { a != b } -> std::convertible_to<bool>; };

	template<typename T>
	concept EmptyConstructor =
		requires { { T() } -> std::convertible_to<T>; };

	template<typename TFrom, typename TTo = TFrom>
	concept CopyOperator =
		requires(TFrom a, TTo& b) { { a = b } -> std::convertible_to<TTo&>; };

	template<typename TFrom, typename TTo>
	concept CastOperator =
		requires(TFrom v) { { (TTo)v } -> std::convertible_to<TTo>; };

	template<typename TCollection, typename TIndex>
	concept Indexable =
		requires(TCollection v, TIndex i) { v[i]; };

	template<typename TCollection, typename TIndex = size_t>
	concept Sizable =
		requires(TCollection v) { { v.size() } -> std::convertible_to<TIndex>; };

	template<typename T, typename TReturnValue = void, typename... TArguments>
	concept Callable =
		requires(T v, TArguments... arguments) { { v(arguments...) } -> std::convertible_to<TReturnValue>; };

	template<typename T>
	concept Iterable =
		requires(T v) { v.begin(); v.end(); };

	template<typename T>
	concept Printable =
		requires(std::ostream s, T v) { s << v; };
}

template<typename T> 
using in = const T&;
template<typename T> 
using in_value = std::conditional_t<std::is_same_v<std::remove_pointer_t<T>, T>, const T, const std::remove_pointer_t<T>*>;
template<typename T>
using in_delegate = T;
template<typename T>
using in_optional = in<std::optional<T>>;
template<typename T>
using in_initializer_list = in<std::initializer_list<T>>;

template<typename T>
using out = T&;

template<typename T>
using ref = T&;
template<typename T>
using ref_optional = std::optional<T*>;

template<typename T>
using value = T;

#define COMMA ,
#define COMMA2 COMMA_ BRACKET_OPEN2 BRACKET_CLOSE2
#define COMMA_() ,
#define BRACKET_OPEN (
#define BRACKET_OPEN2 BRACKET_OPEN_ BRACKET_OPEN BRACKET_CLOSE
#define BRACKET_OPEN_() (
#define BRACKET_CLOSE )
#define BRACKET_CLOSE2  BRACKET_CLOSE_ BRACKET_OPEN BRACKET_CLOSE
#define BRACKET_CLOSE_() )
#define UNPACK(...) __VA_ARGS__
#define UNPACK2(...) UNPACK BRACKET_OPEN __VA_ARGS__ BRACKET_CLOSE

#define CASEVARIATION2(v_,c1,c2,_v) v_ c1 _v v_ c2 _v