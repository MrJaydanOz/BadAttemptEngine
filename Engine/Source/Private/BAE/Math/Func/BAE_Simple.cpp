#include "Math/Func/BAE_Simple.h"

float bae::Sqrt(in<float> v) noexcept(noexcept(sqrt(v)))
{ return std::sqrt(v); }
double bae::Sqrt(in<double> v) noexcept(noexcept(sqrt(v)))
{ return std::sqrt(v); }
long double bae::Sqrt(in<long double> v) noexcept(noexcept(sqrt(v)))
{ return std::sqrt(v); }

int bae::RoundI(in<float> value) noexcept
{ return (int)std::lround(value); }
long bae::RoundL(in<float> value) noexcept
{ return std::lround(value); }
long long bae::RoundLL(in<float> value) noexcept
{ return std::llround(value); }

int bae::RoundI(in<double> value) noexcept
{ return (int)std::lround(value); }
long bae::RoundL(in<double> value) noexcept
{ return std::lround(value); }
long long bae::RoundLL(in<double> value) noexcept
{ return std::llround(value); }

int bae::RoundI(in<long double> value) noexcept
{ return (int)std::lround(value); }
long bae::RoundL(in<long double> value) noexcept
{ return std::lround(value); }
long long bae::RoundLL(in<long double> value) noexcept
{ return std::llround(value); }