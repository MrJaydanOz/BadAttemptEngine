#include "Math/VectorT.h"
#include <cmath>
#include "Def.h"

template<typename T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) { }
Vector2F::Vector2F(float x, float y) : Vector2<float>::Vector2(x, y) { }

float Vector2F::SqrMagnitude() const
	EXPR((x * x) + (y * y))
float Vector2F::Magnitude() const
	EXPR(sqrtf(SqrMagnitude()))
float Vector2F::SqrDistance(const Vector2F other) const
	{ return (this - other).SqrMagnitude(); }
float Vector2F::Distance(const Vector2F other) const
	EXPR(sqrtf(SqrDistance(other)))

Vector2F Vector2F::operator+(const Vector2F other)
	EXPR(Vector2F(x + other.x, y + other.y))
Vector2F Vector2F::operator-(const Vector2F other)
	EXPR(Vector2F(x - other.x, y - other.y))
Vector2F Vector2F::operator*(const Vector2F other)
	EXPR(Vector2F(x * other.x, y * other.y))
Vector2F Vector2F::operator*(const float scaler)
	EXPR(Vector2F(x * scaler, y * scaler))
Vector2F Vector2F::operator/(const float scaler)
	EXPR(Vector2F(x / scaler, y / scaler))