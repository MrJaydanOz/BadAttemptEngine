#include "Math/VectorT.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Math/Constants.h"

template<typename T>
T Vector<2, T>::Magnitude() const noexcept { return sqrt(SqrMagnitude()); }

template<typename T>
Vector<2, T> Vector<2, T>::Rotate(const T& degrees) const noexcept
{
    T sin = (T)std::sin(degrees * (T)DEG_TO_RAD_D);
    T cos = (T)std::cos(degrees * (T)DEG_TO_RAD_D);

    T tx = x;
    T ty = y;
    return Vector((cos * tx) - (sin * ty), (sin * tx) + (cos * ty));
}

template<typename T>
Vector<2, T> Vector<2, T>::InverseRotate(const T& degrees) const noexcept { return Rotate(-degrees); }

template<typename T>
static std::ostream& operator<<(std::ostream& stream, const Vector<2, T>& vector) 
{ 
    stream << '(' << 
        std::setprecision(5) << vector.x << ", " << 
        std::setprecision(5) << vector.y << ')';
}

template<typename T>
static std::ostream& operator<<(std::ostream& stream, const Vector<3, T>& vector) 
{ 
    stream << '(' << 
        std::setprecision(5) << vector.x << ", " << 
        std::setprecision(5) << vector.y << ", " << 
        std::setprecision(5) << vector.z << ')'; 
}

template<typename T>
static std::ostream& operator<<(std::ostream& stream, const Vector<4, T>& vector) 
{ 
    stream << '(' << 
        std::setprecision(5) << vector.x << ", " << 
        std::setprecision(5) << vector.y << ", " << 
        std::setprecision(5) << vector.z << ", " << 
        std::setprecision(5) << vector.w << ')';
}