#pragma once
#include "VectorT.h"
#include "Def.h"

namespace bae
{
    template<typename T>
    class Rect
    {
    public:
        Vector<2, T> position;
        Vector<2, T> size;

    public:
        constexpr Rect(IN(Vector<2, T>) position, IN(Vector<2, T>) size) noexcept : 
            position(position), size(size) { }
        static constexpr AsPositionSize(IN(Vector<2, T>) position, IN(Vector<2, T>) size) noexcept(noexcept(Rect<T>(position, size)))
        { return Rect<T>(position, size); }
        static constexpr AsMinMax(IN(Vector<2, T>) min, IN(Vector<2, T>) max) noexcept(noexcept(Rect<T>(min, max - min)))
        { return Rect<T>(min, max - min); }
        static constexpr AsCenterExtents(IN(Vector<2, T>) center, IN(Vector<2, T>) extents) noexcept(noexcept(Rect<T>(center - extents, extents * 2)))
        { return Rect<T>(center - extents, extents * 2); }
        static constexpr AsCenterSize(IN(Vector<2, T>) center, IN(Vector<2, T>) size) noexcept(noexcept(AsCenterExtents(center, size * 0.5f)))
        { return AsCenterExtents(center, size * 0.5f); }

        static constexpr Vector<2, T> GetMin() const noexcept
        { return position; }
        static constexpr Vector<2, T> GetMax() const noexcept(noexcept(position + size))
        { return position + size; }
        static constexpr Vector<2, T> GetCenter() const noexcept(noexcept(position + (size * 0.5f)))
        { return position - (size * 0.5f); }
        static constexpr Vector<2, T> GetSize() const noexcept
        { return size; }
        static constexpr Vector<2, T> GetExtent() const noexcept
        { return size * 0.5f; }

        constexpr bool Contains(IN(Vector<2, T>) point) const noexcept(noexcept(position + size) && noexcept(point.x <= max.x && point.x >= min.x && point.y <= max.y && point.y >= min.y))
        {
            const Vector<2, T>& min = position;
            const Vector<2, T> max = position + size;

            return 
                point.x <= max.x && point.x >= min.x &&
                point.y <= max.y && point.y >= min.y;
        }

        constexpr void FixNegative() const noexcept(noexcept(size.x < 0) && noexcept(position.x += size.x) && noexcept(size.x = -size.x) && noexcept(size.y < 0) && noexcept(position.y += size.y) && noexcept(size.y = -size.y))
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
        constexpr Bounds(IN(Vector<2, T>) min, IN(Vector<2, T>) max) noexcept :
            min(min), max(max) { }
        static constexpr AsPositionSize(IN(Vector<2, T>) position, IN(Vector<2, T>) size) noexcept(noexcept(Rect<T>(position, size)))
        { return Bounds<T>(position, position + size); }
        static constexpr AsMinMax(IN(Vector<2, T>) min, IN(Vector<2, T>) max) noexcept(noexcept(Rect<T>(min, max - min)))
        { return Bounds<T>(min, max); }
        static constexpr AsCenterExtents(IN(Vector<2, T>) center, IN(Vector<2, T>) extents) noexcept(noexcept(Rect<T>(center - extents, center + extents)))
        { return Bounds<T>(center - extents, center + extents); }
        static constexpr AsCenterSize(IN(Vector<2, T>) center, IN(Vector<2, T>) size) noexcept(noexcept(AsCenterExtents(center, size * 0.5f)))
        { return AsCenterExtents(center, size * 0.5f); }
        
        static constexpr Vector<2, T> GetMin() const noexcept
        { return min; }
        static constexpr Vector<2, T> GetMax() const noexcept
        { return max; }
        static constexpr Vector<2, T> GetCenter() const noexcept(noexcept((min + max) * 0.5f))
        { return (min + max) * 0.5f; }
        static constexpr Vector<2, T> GetSize() const noexcept(noexcept(max - min))
        { return max - min; }
        static constexpr Vector<2, T> GetExtent() const noexcept(noexcept((max - min) * 0.5f))
        { return (max - min) * 0.5f; }

        constexpr bool Contains(IN(Vector<2, T>) point) noexcept(noexcept(point.x <= max.x && point.x >= min.x && point.y <= max.y && point.y >= min.y))
        {
            return
                point.x <= max.x && point.x >= min.x &&
                point.y <= max.y && point.y >= min.y;
        }

        constexpr void FixNegative() noexcept(noexcept(size.x < 0) && noexcept(position.x += size.x) && noexcept(size.x = -size.x) && noexcept(size.y < 0) && noexcept(position.y += size.y) && noexcept(size.y = -size.y))
        {
            if (min.x > max.x)
                Swap(min.x, max.x);
            if (min.y > max.y)
                Swap(min.y, max.y);
        }
    };

    typedef Bounds<float> BoundsF;
    typedef Bounds<double> BoundsD;
    typedef Bounds<int> BoundsI;
}