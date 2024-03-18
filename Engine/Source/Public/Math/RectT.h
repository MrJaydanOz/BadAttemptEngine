#pragma once
#include "VectorT.h"

/*#define DECLARATION_RECT(rectType, vectorType, elementType, ...) \
struct rectType \
{ \
public: \
    vectorType min, max; \
 \
public: \
    rectType(vectorType min, vectorType max) noexcept : min(min), max(max) { } \
    rectType(elementType minX, elementType minY, elementType maxX, elementType maxY) noexcept : min(minX, minY), max(maxX, maxY) { } \
    operator Rect<vectorType>() const noexcept; \
    __VA_ARGS__ \
};

#define DECLARATION_RECT_FLOAT_FUNCTIONS(rectType, vectorType, elementType, ...) \
    DECLARATION_RECT(vectorType, elementType, elementType, \
    __VA_ARGS__ \
    )

#define DECLARATION_RECT_INTEGER_FUNCTIONS(rectType, vectorType, elementType, ...) \
    DECLARATION_RECT(vectorType, elementType, elementType, \
    __VA_ARGS__ \
    )

#define DECLARATION_RECT_FLOAT(rectType, vectorType, elementType, ...) DECLARATION_RECT(rectType, vectorType, elementType, DECLARATION_RECT_FLOAT_FUNCTIONS(rectType, vectorType, elementType) __VA_ARGS__)
#define DECLARATION_RECT_INTEGER(rectType, vectorType, elementType, ...) DECLARATION_RECT(rectType, vectorType, elementType, DECLARATION_RECT_INTEGER_FUNCTIONS(rectType, vectorType, elementType) __VA_ARGS__)

template<typename T>
class Rect
{
public:
    T min, max;

public:
    Rect(T min, T max) : min(min), max(max) { }
};

DECLARATION_RECT_FLOAT(RectF, Vector2F, float)
DECLARATION_RECT_FLOAT(RectD, Vector2D, double)

DECLARATION_RECT_INTEGER(RectI, Vector2I, int)
DECLARATION_RECT_INTEGER(RectL, Vector2L, long)*/

template<typename T>
struct Rect
{
public:
    Vector<2, T> min, max;

public:
    constexpr Rect(T minX, T minY, T maxX, T maxY) noexcept : min(minX, minY), max(maxX, maxY) { }
    constexpr Rect(Vector<2, T> min, Vector<2, T> max) noexcept : min(min), max(max) { }

    constexpr Vector<2, T> GetCenter() noexcept { return (min + max) * 0.5f; }
    constexpr Vector<2, T> GetSize() noexcept { return max - min; }
    constexpr Vector<2, T> GetExtent() noexcept { return GetSize() * 0.5f; }

    constexpr void SetCenter(Vector<2, T> position) noexcept
    {
        Vector<2, T> extent = GetExtent();

        min = position - extent;
        max = position + extent;
    }
    constexpr void SetExtent(Vector<2, T> extent) noexcept
    {
        Vector<2, T> center = GetCenter();

        min = center - extent;
        max = center + extent;
    }
    constexpr void SetSize(Vector<2, T> size) noexcept { SetExtent(size * 0.5f); }

    constexpr bool operator==(const Rect& other) const noexcept { return min == other.min && max == other.max; }
    constexpr bool operator!=(const Rect& other) const noexcept { return min != other.min || max != other.max; }
    constexpr Rect operator+(const Vector<2, T>& translation) const noexcept { return Rect(min + translation, max + translation); }
    constexpr Rect& operator+=(const Vector<2, T>& translation) noexcept { return *this = *this + translation; }
    constexpr Rect operator-(const Vector<2, T>& translation) const noexcept { return Rect(min - translation, max - translation); }
    constexpr Rect& operator-=(const Vector<2, T>& translation) noexcept { return *this = *this - translation; }
};

typedef Rect<float> RectF;
typedef Rect<double> RectD;
typedef Rect<int> RectI;