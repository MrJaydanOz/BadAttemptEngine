#include "Math/Func/BAE_Simple.h"

float32 bae::Sqrt(in<float32> v) noexcept(noexcept(sqrt(v)))
{ return std::sqrt(v); }
float64 bae::Sqrt(in<float64> v) noexcept(noexcept(sqrt(v)))
{ return std::sqrt(v); }
float128 bae::Sqrt(in<float128> v) noexcept(noexcept(sqrt(v)))
{ return std::sqrt(v); }