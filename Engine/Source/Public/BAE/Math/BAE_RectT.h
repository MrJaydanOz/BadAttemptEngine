#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_RectT.h"))
#endif
#include "Math/BAE_VectorT.h"

namespace bae
{
#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Rect<typename>))
#endif
    template<typename T>
    class Rect
    {
    public:
        Vector<2, T> position;
        Vector<2, T> size;

    public:
        constexpr Rect(in<Vector<2, T>> position, in<Vector<2, T>> size) noexcept : 
            position(position), size(size) { }
        constexpr Rect(in<T> positionX, in<T> positionY, in<T> sizeX, in<T> sizeY) noexcept :
            position(positionX, positionY), size(sizeX, sizeY) { }
        static constexpr Rect AsPositionSize(in<Vector<2, T>> position, in<Vector<2, T>> size) noexcept(noexcept(Rect<T>(position, size)))
        { return Rect(position, size); }
        static constexpr Rect AsMinMax(in<Vector<2, T>> min, in<Vector<2, T>> max) noexcept(noexcept(Rect<T>(min, max - min)))
        { return Rect(min, max - min); }
        static constexpr Rect AsCenterExtents(in<Vector<2, T>> center, in<Vector<2, T>> extents) noexcept(noexcept(Rect<T>(center - extents, extents * 2)))
        { return Rect(center - extents, extents * 2); }
        static constexpr Rect AsCenterSize(in<Vector<2, T>> center, in<Vector<2, T>> size) noexcept(noexcept(AsCenterExtents(center, size * 0.5f)))
        { return AsCenterExtents(center, size * 0.5f); }

        constexpr Vector<2, T> GetMin() noexcept
        { return position; }
        constexpr Vector<2, T> GetMax() noexcept(noexcept(position + size))
        { return position + size; }
        constexpr Vector<2, T> GetCenter() noexcept(noexcept(position + (size * 0.5f)))
        { return position - (size * 0.5f); }
        constexpr Vector<2, T> GetSize() noexcept
        { return size; }
        constexpr Vector<2, T> GetExtent() noexcept
        { return size * 0.5f; }

        constexpr bool Contains(in<Vector<2, T>> point) const noexcept(noexcept(point.x <= (position + size).x && point.x >= position.x && point.y <= (position + size).y && point.y >= position.y))
        {
            const Vector<2, T>& min = position;
            const Vector<2, T> max = position + size;

            return 
                point.x <= max.x && point.x >= min.x &&
                point.y <= max.y && point.y >= min.y;
        }

        constexpr void FixNegative() noexcept(noexcept(size.x < 0) && noexcept(position.x += size.x) && noexcept(size.x = -size.x) && noexcept(size.y < 0) && noexcept(position.y += size.y) && noexcept(size.y = -size.y))
        {
            if (size.x < 0)
            {
                position.x += size.x;
                size.x = -size.x;
            }
            if (size.y < 0)
            {
                position.y += size.y;
                size.y = -size.y;
            }
        }

        friend std::ostream& operator<<(ref<std::ostream> stream, in<Rect> rect)
        {
            return stream <<
                 "(x:" << std::setprecision(2) << std::fixed << rect.position.x <<
                ", y:" << std::setprecision(2) << std::fixed << rect.position.y <<
                ", w:" << std::setprecision(2) << std::fixed << rect.size.x <<
                ", h:" << std::setprecision(2) << std::fixed << rect.size.y << ')';
        }

        constexpr Rect& operator=(in<Rect> other) noexcept(noexcept(position = other.position) && noexcept(size = other.size)) { position = other.position; size = other.size; return *this; }
    };

    typedef Rect<float> RectF;
    typedef Rect<double> RectD;
    typedef Rect<int> RectI;

    template<typename T>
    class Bounds
    {
    public:
        Vector<2, T> min;
        Vector<2, T> max;

    public:
        constexpr Bounds(in<Vector<2, T>> min, in<Vector<2, T>> max) noexcept :
            min(min), max(max) { }
        static constexpr Bounds AsPositionSize(in<Vector<2, T>> position, in<Vector<2, T>> size) noexcept(noexcept(Rect<T>(position, size)))
        { return Bounds(position, position + size); }
        static constexpr Bounds AsMinMax(in<Vector<2, T>> min, in<Vector<2, T>> max) noexcept(noexcept(Rect<T>(min, max - min)))
        { return Bounds(min, max); }
        static constexpr Bounds AsCenterExtents(in<Vector<2, T>> center, in<Vector<2, T>> extents) noexcept(noexcept(Rect<T>(center - extents, center + extents)))
        { return Bounds(center - extents, center + extents); }
        static constexpr Bounds AsCenterSize(in<Vector<2, T>> center, in<Vector<2, T>> size) noexcept(noexcept(AsCenterExtents(center, size * 0.5f)))
        { return AsCenterExtents(center, size * 0.5f); }
        
        constexpr Vector<2, T> GetMin() noexcept
        { return min; }
        constexpr Vector<2, T> GetMax() noexcept
        { return max; }
        constexpr Vector<2, T> GetCenter() noexcept(noexcept((min + max) * 0.5f))
        { return (min + max) * 0.5f; }
        constexpr Vector<2, T> GetSize() noexcept(noexcept(max - min))
        { return max - min; }
        constexpr Vector<2, T> GetExtent() noexcept(noexcept((max - min) * 0.5f))
        { return (max - min) * 0.5f; }

        constexpr bool Contains(in<Vector<2, T>> point) const noexcept(noexcept(point.x <= max.x && point.x >= min.x && point.y <= max.y && point.y >= min.y))
        {
            return
                point.x <= max.x && point.x >= min.x &&
                point.y <= max.y && point.y >= min.y;
        }

        constexpr void FixNegative() noexcept(noexcept(min.x > max.x) && noexcept(Swap(min.x, max.x)) && noexcept(min.y > max.y) && noexcept(Swap(min.y, max.y)))
        {
            if (min.x > max.x)
                Swap(min.x, max.x);
            if (min.y > max.y)
                Swap(min.y, max.y);
        }

        friend std::ostream& operator<<(ref<std::ostream> stream, in<Bounds> bounds)
        {
            return stream <<
                 "(-x:" << std::setprecision(2) << std::fixed << bounds.min.x <<
                ", -y:" << std::setprecision(2) << std::fixed << bounds.min.y <<
                ", +x:" << std::setprecision(2) << std::fixed << bounds.max.x <<
                ", +y:" << std::setprecision(2) << std::fixed << bounds.max.y << ')';
        }

        constexpr Bounds& operator=(in<Bounds> other) noexcept(noexcept(min = other.min) && noexcept(max = other.max)) { min = other.min; max = other.max; return *this; }
    };

    typedef Bounds<float> BoundsF;
    typedef Bounds<double> BoundsD;
    typedef Bounds<int> BoundsI;
}