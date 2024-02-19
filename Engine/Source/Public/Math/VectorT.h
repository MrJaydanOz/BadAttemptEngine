#pragma once

template<typename T>
class Vector2
{
public:
    T x, y;

public:
    Vector2<T>(T x, T y) : x(x), y(y) { }
};

class Vector2F : Vector2<float>
{

public:
    Vector2F(float x, float y) { }

    float SqrMagnitude() const;
    float Magnitude() const;
    float SqrDistance(const Vector2F other) const;
    float Distance(const Vector2F other) const;

public:
    Vector2F operator+(const Vector2F other);
    Vector2F operator-(const Vector2F other);
    Vector2F operator*(const Vector2F other);
    Vector2F operator*(const float scaler);
    Vector2F operator/(const float scaler);
};