#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Trig.h"))
#endif
#include <cmath>

namespace bae
{
	_NODISCARD float Sin(in<float> v) noexcept;
	_NODISCARD double Sin(in<double> v) noexcept;
	_NODISCARD long double Sin(in<long double> v) noexcept;

	_NODISCARD float ASin(in<float> v) noexcept;
	_NODISCARD double ASin(in<double> v) noexcept;
	_NODISCARD long double ASin(in<long double> v) noexcept;

	_NODISCARD float SinH(in<float> v) noexcept;
	_NODISCARD double SinH(in<double> v) noexcept;
	_NODISCARD long double SinH(in<long double> v) noexcept;

	_NODISCARD float ASinH(in<float> v) noexcept;
	_NODISCARD double ASinH(in<double> v) noexcept;
	_NODISCARD long double ASinH(in<long double> v) noexcept;
	

	_NODISCARD float Cos(in<float> v) noexcept;
	_NODISCARD double Cos(in<double> v) noexcept;
	_NODISCARD long double Cos(in<long double> v) noexcept;

	_NODISCARD float ACos(in<float> v) noexcept;
	_NODISCARD double ACos(in<double> v) noexcept;
	_NODISCARD long double ACos(in<long double> v) noexcept;

	_NODISCARD float CosH(in<float> v) noexcept;
	_NODISCARD double CosH(in<double> v) noexcept;
	_NODISCARD long double CosH(in<long double> v) noexcept;

	_NODISCARD float ACosH(in<float> v) noexcept;
	_NODISCARD double ACosH(in<double> v) noexcept;
	_NODISCARD long double ACosH(in<long double> v) noexcept;
	

	_NODISCARD float Tan(in<float> v) noexcept;
	_NODISCARD double Tan(in<double> v) noexcept;
	_NODISCARD long double Tan(in<long double> v) noexcept;

	_NODISCARD float ATan(in<float> v) noexcept;
	_NODISCARD double ATan(in<double> v) noexcept;
	_NODISCARD long double ATan(in<long double> v) noexcept;

	_NODISCARD float TanH(in<float> v) noexcept;
	_NODISCARD double TanH(in<double> v) noexcept;
	_NODISCARD long double TanH(in<long double> v) noexcept;

	_NODISCARD float ATanH(in<float> v) noexcept;
	_NODISCARD double ATanH(in<double> v) noexcept;
	_NODISCARD long double ATanH(in<long double> v) noexcept;
	
	_NODISCARD float ATan2(in<float> y, in<float> x) noexcept;
	_NODISCARD double ATan2(in<double> y, in<double> x) noexcept;
	_NODISCARD long double ATan2(in<long double> y, in<long double> x) noexcept;
}