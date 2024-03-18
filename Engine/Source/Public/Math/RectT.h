#pragma once
#include "VectorT.h"

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