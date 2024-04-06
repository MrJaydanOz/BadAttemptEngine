#include "Math/Func/BAE_Simple.h"

float bae::Sqrt(in<float> v) noexcept(noexcept(sqrt(v)))
{ return std::sqrt(v); }
double bae::Sqrt(in<double> v) noexcept(noexcept(sqrt(v)))
{ return std::sqrt(v); }
long double bae::Sqrt(in<long double> v) noexcept(noexcept(sqrt(v)))
{ return std::sqrt(v); }