#pragma once
#include "Math/Func/Simple.h"
#include "Math/Constants.h"
#include "Def.h"
#include <cmath>

namespace bae
{
	template<size_t elementCount, typename T>
	class Vector { };

	template<typename T>
	class Vector<2, T>
	{
	public:
		T x, y;

	public:
		constexpr Vector(IN(T) fill) noexcept : 
			x(fill), y(fill) { }
		constexpr Vector(IN(T) x, IN(T) y) noexcept : 
			x(x), y(y) { }

		_NODISCARD constexpr T SqrMagnitude() const noexcept(noexcept((x * x) + (y * y)))
		{ return (x * x) + (y * y); }
		_NODISCARD T Magnitude() const noexcept(noexcept(Sqrt(SqrMagnitude())))
		{ return Sqrt(SqrMagnitude()); }

		_NODISCARD constexpr T SqrDistance(IN(Vector) other) const noexcept(noexcept((*this - other).SqrMagnitude()))
		{ return (*this - other).SqrMagnitude(); }
		_NODISCARD T Distance(IN(Vector) other) const noexcept(noexcept(Sqrt(SqrDistance(other))))
		{ return Sqrt(SqrDistance(other)); }
		
		_NODISCARD constexpr T Dot(IN(Vector) other) const noexcept(noexcept((x * other.x) + (y * other.y)))
		{ return (x * other.x) + (y * other.y); }
		
		_NODISCARD constexpr T Cross(IN(Vector) other) const noexcept(noexcept((x * other.y) + (y * other.x)))
		{ return (x * other.y) + (y * other.x); }

		_NODISCARD constexpr Vector Rotate90() const noexcept(noexcept(Vector(-y, x)))
		{ return Vector(-y, x); }
		_NODISCARD constexpr Vector InverseRotate90() const noexcept(noexcept(Vector(y, -x)))
		{ return Vector(y, -x); }

		_NODISCARD Vector Rotate(IN(T) degrees) const noexcept(noexcept(std::sin(degrees* (T)DEG_TO_RAD_D)) && noexcept(std::cos(degrees* (T)DEG_TO_RAD_D)))
		{
			T sin = std::sin(degrees * (T)DEG_TO_RAD_D);
			T cos = std::cos(degrees * (T)DEG_TO_RAD_D);
			return Vector((cos * x) - (sin * y), (sin * x) + (cos * y));
		}

		_NODISCARD Vector InverseRotate(IN(T) degrees) const noexcept(noexcept(Rotate(-degrees))) { return Rotate(-degrees); }

	public:
		_NODISCARD constexpr Vector& operator=(IN(Vector) other) noexcept(noexcept(x = other.x) && noexcept(y = other.y)) { x = other.x; y = other.y; return *this; }

		_NODISCARD constexpr Vector operator+(IN(Vector) other) const noexcept(noexcept(Vector(x + other.x, y + other.y))) { return Vector(x + other.x, y + other.y); }
		_NODISCARD constexpr Vector operator-(IN(Vector) other) const noexcept(noexcept(Vector(x - other.x, y - other.y))) { return Vector(x - other.x, y - other.y); }
		_NODISCARD constexpr Vector operator*(IN(Vector) other) const noexcept(noexcept(Vector(x * other.x, y * other.y))) { return Vector(x * other.x, y * other.y); }
		_NODISCARD constexpr Vector operator*(IN(T) scaler) const noexcept(noexcept(Vector(x * scaler, y * scaler))) { return Vector(x * scaler, y * scaler); }
		_NODISCARD constexpr Vector operator/(IN(T) scaler) const noexcept(noexcept(Vector(x / scaler, y / scaler))) { return Vector(x / scaler, y / scaler); }

		_NODISCARD constexpr Vector& operator+=(IN(Vector) other) noexcept(noexcept(x += other.x) && noexcept(y += other.y)) { x += other.x; y += other.y; return *this; }
		_NODISCARD constexpr Vector& operator-=(IN(Vector) other) noexcept(noexcept(x -= other.x) && noexcept(y -= other.y)) { x -= other.x; y -= other.y; return *this; }
		_NODISCARD constexpr Vector& operator*=(IN(Vector) other) noexcept(noexcept(x *= other.x) && noexcept(y *= other.y)) { x *= other.x; y *= other.y; return *this; }
		_NODISCARD constexpr Vector& operator*=(IN(T) scaler) noexcept(noexcept(x *= scaler) && noexcept(y *= scaler)) { x *= scaler; y *= scaler; return *this; }
		_NODISCARD constexpr Vector& operator/=(IN(T) scaler) noexcept(noexcept(x /= scaler) && noexcept(y /= scaler)) { x /= scaler; y /= scaler; return *this; }

		_NODISCARD constexpr bool operator==(IN(Vector) other) const noexcept(noexcept(x == other.x) && noexcept(y == other.y)) { return x == other.x && y == other.y; }
		_NODISCARD constexpr bool operator!=(IN(Vector) other) const noexcept(noexcept(x != other.x) && noexcept(y != other.y)) { return x != other.x || y != other.y; }
	};

	template<typename T>
	_NODISCARD static constexpr T Dot(IN(Vector<2, T>) a, IN(Vector<2, T>) b) noexcept(noexcept(a.Dot(b)))
	{ return a.Dot(b); }

	template<typename T>
	_NODISCARD static constexpr T Cross(IN(Vector<2, T>) a, IN(Vector<2, T>) b) noexcept(noexcept(a.Cross(b)))
	{ return a.Cross(b); }

	template<typename T>
	_NODISCARD static constexpr T SqrDistance(IN(Vector<3, T>) a, IN(Vector<3, T>) b) noexcept(noexcept(a.SqrDistance(b)))
	{ return a.SqrDistance(b); }
	template<typename T>
	_NODISCARD static T Distance(IN(Vector<3, T>) a, IN(Vector<3, T>) b) noexcept(noexcept(a.Distance(b)))
	{ return a.Distance(b); }

	typedef Vector<2, float> Vector2F;
	typedef Vector<2, double> Vector2D;
	typedef Vector<2, int> Vector2I;

	template<typename T>
	class Vector<3, T>
	{
	public:
		T x, y, z;

	public:
		constexpr Vector(IN(T) fill) noexcept : 
			x(fill), y(fill), z(fill) { }
		constexpr Vector(IN(T) x, IN(T) y, IN(T) z) noexcept : 
			x(x), y(y), z(z) { }

		_NODISCARD constexpr T SqrMagnitude() const noexcept(noexcept((x * x) + (y * y) + (z * z)))
		{ return (x * x) + (y * y) + (z * z); }
		_NODISCARD T Magnitude() const noexcept(noexcept(Sqrt(SqrMagnitude())))
		{ return Sqrt(SqrMagnitude()); }
		
		_NODISCARD constexpr T SqrDistance(IN(Vector) other) const noexcept(noexcept((*this - other).SqrMagnitude()))
		{ return (*this - other).SqrMagnitude(); }
		_NODISCARD T Distance(IN(Vector) other) const noexcept(noexcept(Sqrt(SqrDistance(other))))
		{ return Sqrt(SqrDistance(other)); }
		
		_NODISCARD constexpr T Dot(IN(Vector) other) const noexcept(noexcept((x * other.x) + (y * other.y) + (z * other.z)))
		{ return (x * other.x) + (y * other.y) + (z * other.z); }
		
		_NODISCARD constexpr T Cross(IN(Vector) other) const noexcept(noexcept(Vector((y * other.z) - (z * other.y), (z* other.x) - (x * other.z), (x* other.y) - (y * other.x))))
		{ return Vector<3, T>((y * other.z) - (z * other.y), (z * other.x) - (x * other.z), (x * other.y) - (y * other.x)); }

	public:
		_NODISCARD constexpr Vector& operator=(IN(Vector) other) noexcept(noexcept(x = other.x) && noexcept(y = other.y) && noexcept(z = other.z)) { x = other.x; y = other.y; z = other.z; return *this; }

		_NODISCARD constexpr Vector operator+(IN(Vector) other) const noexcept(noexcept(Vector(x + other.x, y + other.y, z + other.z))) { return Vector(x + other.x, y + other.y, z + other.z); }
		_NODISCARD constexpr Vector operator-(IN(Vector) other) const noexcept(noexcept(Vector(x - other.x, y - other.y, z - other.z))) { return Vector(x - other.x, y - other.y, z - other.z); }
		_NODISCARD constexpr Vector operator*(IN(Vector) other) const noexcept(noexcept(Vector(x * other.x, y * other.y, z * other.z))) { return Vector(x * other.x, y * other.y, z * other.z); }
		_NODISCARD constexpr Vector operator*(IN(T) scaler) const noexcept(noexcept(Vector(x * scaler, y * scaler, z * scaler))) { return Vector(x * scaler, y * scaler, z * scaler); }
		_NODISCARD constexpr Vector operator/(IN(T) scaler) const noexcept(noexcept(Vector(x / scaler, y / scaler, z / scaler))) { return Vector(x / scaler, y / scaler, z / scaler); }

		_NODISCARD constexpr Vector& operator+=(IN(Vector) other) noexcept(noexcept(x += other.x) && noexcept(y += other.y) && noexcept(z += other.z)) { x += other.x; y += other.y; z += other.z; return *this; }
		_NODISCARD constexpr Vector& operator-=(IN(Vector) other) noexcept(noexcept(x -= other.x) && noexcept(y -= other.y) && noexcept(z -= other.z)) { x -= other.x; y -= other.y; z -= other.z; return *this; }
		_NODISCARD constexpr Vector& operator*=(IN(Vector) other) noexcept(noexcept(x *= other.x) && noexcept(y *= other.y) && noexcept(z *= other.z)) { x *= other.x; y *= other.y; z *= other.z; return *this; }
		_NODISCARD constexpr Vector& operator*=(IN(T) scaler) noexcept(noexcept(x *= scaler) && noexcept(y *= scaler) && noexcept(z *= scaler)) { x *= scaler; y *= scaler; z *= scaler; return *this; }
		_NODISCARD constexpr Vector& operator/=(IN(T) scaler) noexcept(noexcept(x /= scaler) && noexcept(y /= scaler) && noexcept(z /= scaler)) { x /= scaler; y /= scaler; z /= scaler; return *this; }

		_NODISCARD constexpr bool operator==(IN(Vector) other) const noexcept(noexcept(x == other.x) && noexcept(y == other.y) && noexcept(z == other.z)) { return x == other.x && y == other.y && z == other.z; }
		_NODISCARD constexpr bool operator!=(IN(Vector) other) const noexcept(noexcept(x != other.x) && noexcept(y != other.y) && noexcept(z != other.z)) { return x != other.x || y != other.y || z != other.z; }
	};

	template<typename T>
	_NODISCARD static constexpr T Dot(IN(Vector<3, T>) a, IN(Vector<3, T>) b) noexcept(noexcept(a.Dot(b)))
	{ return a.Dot(b); }

	template<typename T>
	_NODISCARD static constexpr T Cross(IN(Vector<3, T>) a, IN(Vector<3, T>) b) noexcept(noexcept(a.Cross(b)))
	{ return a.Cross(b); }

	template<typename T>
	_NODISCARD static constexpr T SqrDistance(IN(Vector<3, T>) a, IN(Vector<3, T>) b) noexcept(noexcept(a.SqrDistance(b)))
	{ return a.SqrDistance(b); }
	template<typename T>
	_NODISCARD static T Distance(IN(Vector<3, T>) a, IN(Vector<3, T>) b) noexcept(noexcept(a.Distance(b)))
	{ return a.Distance(b); }

	typedef Vector<3, float> Vector3F;
	typedef Vector<3, double> Vector3D;
	typedef Vector<3, int> Vector3I;

	template<typename T>
	class Vector<4, T>
	{
	public:
		T x, y, z, w;

	public:
		constexpr Vector(IN(T) fill) noexcept : 
			x(fill), y(fill), z(fill), w(fill) { }
		constexpr Vector(IN(T) x, IN(T) y, IN(T) z, IN(T) w) noexcept : 
			x(x), y(y), z(z), w(w) { }

		_NODISCARD constexpr T SqrMagnitude() const noexcept(noexcept((x* x) + (y * y) + (z * z) + (w * w)))
		{ return (x * x) + (y * y) + (z * z) + (w * w); }
		_NODISCARD T Magnitude() const noexcept(noexcept(Sqrt(SqrMagnitude())))
		{ return Sqrt(SqrMagnitude()); }
		
		_NODISCARD constexpr T SqrDistance(IN(Vector) other) const noexcept(noexcept((*this - other).SqrMagnitude()))
		{ return (*this - other).SqrMagnitude(); }
		_NODISCARD T Distance(IN(Vector) other) const noexcept(noexcept(Sqrt(SqrDistance(other))))
		{ return Sqrt(SqrDistance(other)); }
		
		constexpr T Dot(IN(Vector) other) const noexcept(noexcept((x * other.x) + (y * other.y) + (z * other.z) + (w * other.w)))
		{ return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w); }

	public:
		_NODISCARD constexpr Vector& operator=(IN(Vector) other) noexcept(noexcept(x = other.x) && noexcept(y = other.y) && noexcept(z = other.z) && noexcept(w = other.w)) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }

		_NODISCARD constexpr Vector operator+(IN(Vector) other) const noexcept(noexcept(Vector(x + other.x, y + other.y, z + other.z, w + other.w))) { return Vector(x + other.x, y + other.y, z + other.z, w + other.w); }
		_NODISCARD constexpr Vector operator-(IN(Vector) other) const noexcept(noexcept(Vector(x - other.x, y - other.y, z - other.z, w - other.w))) { return Vector(x - other.x, y - other.y, z - other.z, w - other.w); }
		_NODISCARD constexpr Vector operator*(IN(Vector) other) const noexcept(noexcept(Vector(x * other.x, y * other.y, z * other.z, w * other.w))) { return Vector(x * other.x, y * other.y, z * other.z, w * other.w); }
		_NODISCARD constexpr Vector operator*(IN(T) scaler) const noexcept(noexcept(Vector(x * scaler, y * scaler, z * scaler, w * scaler))) { return Vector(x * scaler, y * scaler, z * scaler, w * scaler); }
		_NODISCARD constexpr Vector operator/(IN(T) scaler) const noexcept(noexcept(Vector(x / scaler, y / scaler, z / scaler, w / scaler))) { return Vector(x / scaler, y / scaler, z / scaler, w / scaler); }

		_NODISCARD constexpr Vector& operator+=(IN(Vector) other) noexcept(noexcept(x += other.x) && noexcept(y += other.y) && noexcept(z += other.z) && noexcept(w += other.w)) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
		_NODISCARD constexpr Vector& operator-=(IN(Vector) other) noexcept(noexcept(x -= other.x) && noexcept(y -= other.y) && noexcept(z -= other.z) && noexcept(w -= other.w)) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
		_NODISCARD constexpr Vector& operator*=(IN(Vector) other) noexcept(noexcept(x *= other.x) && noexcept(y *= other.y) && noexcept(z *= other.z) && noexcept(w *= other.w)) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
		_NODISCARD constexpr Vector& operator*=(IN(T) scaler) noexcept(noexcept(x *= scaler) && noexcept(y *= scaler) && noexcept(z *= scaler) && noexcept(w *= scaler)) { x *= scaler; y *= scaler; z *= scaler; w *= scaler; return *this; }
		_NODISCARD constexpr Vector& operator/=(IN(T) scaler) noexcept(noexcept(x /= scaler) && noexcept(y /= scaler) && noexcept(z /= scaler) && noexcept(w /= scaler)) { x /= scaler; y /= scaler; z /= scaler; w /= scaler; return *this; }

		_NODISCARD constexpr bool operator==(IN(Vector) other) const noexcept(noexcept(x == other.x) && noexcept(y == other.y) && noexcept(z == other.z) && noexcept(w == other.w)) { return x == other.x && y == other.y && z == other.z && w == other.w; }
		_NODISCARD constexpr bool operator!=(IN(Vector) other) const noexcept(noexcept(x != other.x) && noexcept(y != other.y) && noexcept(z != other.z) && noexcept(w != other.w)) { return x != other.x || y != other.y || z != other.z || w != other.w; }
	};

	template<typename T>
	_NODISCARD static constexpr T Dot(IN(Vector<4, T>) a, IN(Vector<4, T>) b) noexcept(noexcept(a.Dot(b)))
	{ return a.Dot(b); }

	template<typename T>
	_NODISCARD static constexpr T SqrDistance(IN(Vector<4, T>) a, IN(Vector<4, T>) b) noexcept(noexcept(a.SqrDistance(b)))
	{ return a.SqrDistance(b); }
	template<typename T>
	_NODISCARD static T Distance(IN(Vector<4, T>) a, IN(Vector<4, T>) b) noexcept(noexcept(a.Distance(b)))
	{ return a.Distance(b); }

	typedef Vector<4, float> Vector4F;
	typedef Vector<4, double> Vector4D;
	typedef Vector<4, int> Vector4I;
}