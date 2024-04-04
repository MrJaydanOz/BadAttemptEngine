#pragma once
#include <vcruntime.h>
#include <type_traits>
#include <limits>

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

typedef float                  float32;
typedef double                 float64;
typedef long double            float128;

namespace std
{
	template<size_t bitCount>
	class intx
	{
	public:
		using type = 
			std::conditional_t<(bitCount > 128), void, 
			std::conditional_t<(bitCount > 64), int128, 
			std::conditional_t<(bitCount > 32), int64, 
			std::conditional_t<(bitCount > 16), int32, 
			std::conditional_t<(bitCount > 8), int16, 
			std::conditional_t<(bitCount > 0), int8, void>>>>>>;
	};

	template<size_t bitCount>
	using intx_t = typename std::intx<bitCount>::type;

	template<size_t bitCount>
	class uintx
	{
	public:
		using type =
			std::conditional_t<(bitCount > 128), void,
			std::conditional_t<(bitCount > 64), uint128,
			std::conditional_t<(bitCount > 32), uint64,
			std::conditional_t<(bitCount > 16), uint32,
			std::conditional_t<(bitCount > 8), uint16,
			std::conditional_t<(bitCount > 0), uint8, void>>>>>>;
	};

	template<size_t bitCount>
	using uintx_t = typename std::uintx<bitCount>::type;

	template<long long int limit>
	class int_fit
	{
	public:
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
	using int_fit_t = typename std::int_fit<limit>::type;
}

template<typename T> 
using in = const T&;
template<typename T> 
using in_nullable = const T*;

template<typename T>
using out = T&;
template<typename T>
using out_nullable = T*;

template<typename T>
using ref = T&;
template<typename T>
using ref_nullable = T*;
template<typename T>
using ref_optional = T*;

template<typename T>
using value = T;
template<typename T>
using delegate = T;

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