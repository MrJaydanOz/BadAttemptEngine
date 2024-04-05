#pragma once
#include "Math/Func/BAE_Simple.h"
#include "Math/BAE_Constants.h"
#include "BAE_Def.h"
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
		constexpr Vector(in<T> fill) noexcept : 
			x(fill), y(fill) { }
		constexpr Vector(in<T> x, in<T> y) noexcept : 
			x(x), y(y) { }

		_NODISCARD constexpr T SqrMagnitude() const noexcept(noexcept((x * x) + (y * y)))
		{ return (x * x) + (y * y); }
		_NODISCARD T Magnitude() const noexcept(noexcept(Sqrt(SqrMagnitude())))
		{ return Sqrt(SqrMagnitude()); }

		_NODISCARD constexpr T SqrDistance(in<Vector> other) const noexcept(noexcept((*this - other).SqrMagnitude()))
		{ return (*this - other).SqrMagnitude(); }
		_NODISCARD T Distance(in<Vector> other) const noexcept(noexcept(Sqrt(SqrDistance(other))))
		{ return Sqrt(SqrDistance(other)); }
		
		_NODISCARD constexpr T Dot(in<Vector> other) const noexcept(noexcept((x * other.x) + (y * other.y)))
		{ return (x * other.x) + (y * other.y); }
		
		_NODISCARD constexpr T Cross(in<Vector> other) const noexcept(noexcept((x * other.y) + (y * other.x)))
		{ return (x * other.y) + (y * other.x); }

		_NODISCARD constexpr Vector Rotate90() const noexcept(noexcept(Vector(-y, x)))
		{ return Vector(-y, x); }
		_NODISCARD constexpr Vector InverseRotate90() const noexcept(noexcept(Vector(y, -x)))
		{ return Vector(y, -x); }

		_NODISCARD Vector Rotate(in<T> degrees) const noexcept(noexcept(std::sin(degrees* (T)DEG_TO_RAD_D)) && noexcept(std::cos(degrees* (T)DEG_TO_RAD_D)))
		{
			T sin = std::sin(degrees * (T)DEG_TO_RAD_D);
			T cos = std::cos(degrees * (T)DEG_TO_RAD_D);
			return Vector((cos * x) - (sin * y), (sin * x) + (cos * y));
		}

		_NODISCARD Vector InverseRotate(in<T> degrees) const noexcept(noexcept(Rotate(-degrees))) { return Rotate(-degrees); }

	public:
		constexpr Vector& operator=(in<Vector> other) noexcept(noexcept(x = other.x) && noexcept(y = other.y)) { x = other.x; y = other.y; return *this; }

		_NODISCARD constexpr Vector operator+(in<Vector> other) const noexcept(noexcept(Vector(x + other.x, y + other.y))) { return Vector(x + other.x, y + other.y); }
		_NODISCARD constexpr Vector operator-(in<Vector> other) const noexcept(noexcept(Vector(x - other.x, y - other.y))) { return Vector(x - other.x, y - other.y); }
		_NODISCARD constexpr Vector operator*(in<Vector> other) const noexcept(noexcept(Vector(x * other.x, y * other.y))) { return Vector(x * other.x, y * other.y); }
		_NODISCARD constexpr Vector operator*(in<T> scaler) const noexcept(noexcept(Vector(x * scaler, y * scaler))) { return Vector(x * scaler, y * scaler); }
		_NODISCARD constexpr Vector operator/(in<T> scaler) const noexcept(noexcept(Vector(x / scaler, y / scaler))) { return Vector(x / scaler, y / scaler); }

		_NODISCARD constexpr Vector& operator+=(in<Vector> other) noexcept(noexcept(x += other.x) && noexcept(y += other.y)) { x += other.x; y += other.y; return *this; }
		_NODISCARD constexpr Vector& operator-=(in<Vector> other) noexcept(noexcept(x -= other.x) && noexcept(y -= other.y)) { x -= other.x; y -= other.y; return *this; }
		_NODISCARD constexpr Vector& operator*=(in<Vector> other) noexcept(noexcept(x *= other.x) && noexcept(y *= other.y)) { x *= other.x; y *= other.y; return *this; }
		_NODISCARD constexpr Vector& operator*=(in<T> scaler) noexcept(noexcept(x *= scaler) && noexcept(y *= scaler)) { x *= scaler; y *= scaler; return *this; }
		_NODISCARD constexpr Vector& operator/=(in<T> scaler) noexcept(noexcept(x /= scaler) && noexcept(y /= scaler)) { x /= scaler; y /= scaler; return *this; }

		_NODISCARD constexpr bool operator==(in<Vector> other) const noexcept(noexcept(x == other.x) && noexcept(y == other.y)) { return x == other.x && y == other.y; }
		_NODISCARD constexpr bool operator!=(in<Vector> other) const noexcept(noexcept(x != other.x) && noexcept(y != other.y)) { return x != other.x || y != other.y; }
	};

	template<typename T>
	_NODISCARD static constexpr T Dot(in<Vector<2, T>> a, in<Vector<2, T>> b) noexcept(noexcept(a.Dot(b)))
	{ return a.Dot(b); }

	template<typename T>
	_NODISCARD static constexpr T Cross(in<Vector<2, T>> a, in<Vector<2, T>> b) noexcept(noexcept(a.Cross(b)))
	{ return a.Cross(b); }

	template<typename T>
	_NODISCARD static constexpr T SqrDistance(in<Vector<2, T>> a, in<Vector<2, T>> b) noexcept(noexcept(a.SqrDistance(b)))
	{ return a.SqrDistance(b); }
	template<typename T>
	_NODISCARD static T Distance(in<Vector<2, T>> a, in<Vector<2, T>> b) noexcept(noexcept(a.Distance(b)))
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
		constexpr Vector(in<T> fill) noexcept : 
			x(fill), y(fill), z(fill) { }
		constexpr Vector(in<T> x, in<T> y, in<T> z) noexcept : 
			x(x), y(y), z(z) { }

		_NODISCARD constexpr T SqrMagnitude() const noexcept(noexcept((x * x) + (y * y) + (z * z)))
		{ return (x * x) + (y * y) + (z * z); }
		_NODISCARD T Magnitude() const noexcept(noexcept(Sqrt(SqrMagnitude())))
		{ return Sqrt(SqrMagnitude()); }
		
		_NODISCARD constexpr T SqrDistance(in<Vector> other) const noexcept(noexcept((*this - other).SqrMagnitude()))
		{ return (*this - other).SqrMagnitude(); }
		_NODISCARD T Distance(in<Vector> other) const noexcept(noexcept(Sqrt(SqrDistance(other))))
		{ return Sqrt(SqrDistance(other)); }
		
		_NODISCARD constexpr T Dot(in<Vector> other) const noexcept(noexcept((x * other.x) + (y * other.y) + (z * other.z)))
		{ return (x * other.x) + (y * other.y) + (z * other.z); }
		
		_NODISCARD constexpr T Cross(in<Vector> other) const noexcept(noexcept(Vector((y * other.z) - (z * other.y), (z* other.x) - (x * other.z), (x* other.y) - (y * other.x))))
		{ return Vector<3, T>((y * other.z) - (z * other.y), (z * other.x) - (x * other.z), (x * other.y) - (y * other.x)); }

	public:
		constexpr Vector& operator=(in<Vector> other) noexcept(noexcept(x = other.x) && noexcept(y = other.y) && noexcept(z = other.z)) { x = other.x; y = other.y; z = other.z; return *this; }

		_NODISCARD constexpr Vector operator+(in<Vector> other) const noexcept(noexcept(Vector(x + other.x, y + other.y, z + other.z))) { return Vector(x + other.x, y + other.y, z + other.z); }
		_NODISCARD constexpr Vector operator-(in<Vector> other) const noexcept(noexcept(Vector(x - other.x, y - other.y, z - other.z))) { return Vector(x - other.x, y - other.y, z - other.z); }
		_NODISCARD constexpr Vector operator*(in<Vector> other) const noexcept(noexcept(Vector(x * other.x, y * other.y, z * other.z))) { return Vector(x * other.x, y * other.y, z * other.z); }
		_NODISCARD constexpr Vector operator*(in<T> scaler) const noexcept(noexcept(Vector(x * scaler, y * scaler, z * scaler))) { return Vector(x * scaler, y * scaler, z * scaler); }
		_NODISCARD constexpr Vector operator/(in<T> scaler) const noexcept(noexcept(Vector(x / scaler, y / scaler, z / scaler))) { return Vector(x / scaler, y / scaler, z / scaler); }

		_NODISCARD constexpr Vector& operator+=(in<Vector> other) noexcept(noexcept(x += other.x) && noexcept(y += other.y) && noexcept(z += other.z)) { x += other.x; y += other.y; z += other.z; return *this; }
		_NODISCARD constexpr Vector& operator-=(in<Vector> other) noexcept(noexcept(x -= other.x) && noexcept(y -= other.y) && noexcept(z -= other.z)) { x -= other.x; y -= other.y; z -= other.z; return *this; }
		_NODISCARD constexpr Vector& operator*=(in<Vector> other) noexcept(noexcept(x *= other.x) && noexcept(y *= other.y) && noexcept(z *= other.z)) { x *= other.x; y *= other.y; z *= other.z; return *this; }
		_NODISCARD constexpr Vector& operator*=(in<T> scaler) noexcept(noexcept(x *= scaler) && noexcept(y *= scaler) && noexcept(z *= scaler)) { x *= scaler; y *= scaler; z *= scaler; return *this; }
		_NODISCARD constexpr Vector& operator/=(in<T> scaler) noexcept(noexcept(x /= scaler) && noexcept(y /= scaler) && noexcept(z /= scaler)) { x /= scaler; y /= scaler; z /= scaler; return *this; }

		_NODISCARD constexpr bool operator==(in<Vector> other) const noexcept(noexcept(x == other.x) && noexcept(y == other.y) && noexcept(z == other.z)) { return x == other.x && y == other.y && z == other.z; }
		_NODISCARD constexpr bool operator!=(in<Vector> other) const noexcept(noexcept(x != other.x) && noexcept(y != other.y) && noexcept(z != other.z)) { return x != other.x || y != other.y || z != other.z; }
	};

	template<typename T>
	_NODISCARD static constexpr T Dot(in<Vector<3, T>> a, in<Vector<3, T>> b) noexcept(noexcept(a.Dot(b)))
	{ return a.Dot(b); }

	template<typename T>
	_NODISCARD static constexpr T Cross(in<Vector<3, T>> a, in<Vector<3, T>> b) noexcept(noexcept(a.Cross(b)))
	{ return a.Cross(b); }

	template<typename T>
	_NODISCARD static constexpr T SqrDistance(in<Vector<3, T>> a, in<Vector<3, T>> b) noexcept(noexcept(a.SqrDistance(b)))
	{ return a.SqrDistance(b); }
	template<typename T>
	_NODISCARD static T Distance(in<Vector<3, T>> a, in<Vector<3, T>> b) noexcept(noexcept(a.Distance(b)))
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
		constexpr Vector(in<T> fill) noexcept : 
			x(fill), y(fill), z(fill), w(fill) { }
		constexpr Vector(in<T> x, in<T> y, in<T> z, in<T> w) noexcept : 
			x(x), y(y), z(z), w(w) { }

		_NODISCARD constexpr T SqrMagnitude() const noexcept(noexcept((x* x) + (y * y) + (z * z) + (w * w)))
		{ return (x * x) + (y * y) + (z * z) + (w * w); }
		_NODISCARD T Magnitude() const noexcept(noexcept(Sqrt(SqrMagnitude())))
		{ return Sqrt(SqrMagnitude()); }
		
		_NODISCARD constexpr T SqrDistance(in<Vector> other) const noexcept(noexcept((*this - other).SqrMagnitude()))
		{ return (*this - other).SqrMagnitude(); }
		_NODISCARD T Distance(in<Vector> other) const noexcept(noexcept(Sqrt(SqrDistance(other))))
		{ return Sqrt(SqrDistance(other)); }
		
		constexpr T Dot(in<Vector> other) const noexcept(noexcept((x * other.x) + (y * other.y) + (z * other.z) + (w * other.w)))
		{ return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w); }

	public:
		constexpr Vector& operator=(in<Vector> other) noexcept(noexcept(x = other.x) && noexcept(y = other.y) && noexcept(z = other.z) && noexcept(w = other.w)) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }

		_NODISCARD constexpr Vector operator+(in<Vector> other) const noexcept(noexcept(Vector(x + other.x, y + other.y, z + other.z, w + other.w))) { return Vector(x + other.x, y + other.y, z + other.z, w + other.w); }
		_NODISCARD constexpr Vector operator-(in<Vector> other) const noexcept(noexcept(Vector(x - other.x, y - other.y, z - other.z, w - other.w))) { return Vector(x - other.x, y - other.y, z - other.z, w - other.w); }
		_NODISCARD constexpr Vector operator*(in<Vector> other) const noexcept(noexcept(Vector(x * other.x, y * other.y, z * other.z, w * other.w))) { return Vector(x * other.x, y * other.y, z * other.z, w * other.w); }
		_NODISCARD constexpr Vector operator*(in<T> scaler) const noexcept(noexcept(Vector(x * scaler, y * scaler, z * scaler, w * scaler))) { return Vector(x * scaler, y * scaler, z * scaler, w * scaler); }
		_NODISCARD constexpr Vector operator/(in<T> scaler) const noexcept(noexcept(Vector(x / scaler, y / scaler, z / scaler, w / scaler))) { return Vector(x / scaler, y / scaler, z / scaler, w / scaler); }

		_NODISCARD constexpr Vector& operator+=(in<Vector> other) noexcept(noexcept(x += other.x) && noexcept(y += other.y) && noexcept(z += other.z) && noexcept(w += other.w)) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
		_NODISCARD constexpr Vector& operator-=(in<Vector> other) noexcept(noexcept(x -= other.x) && noexcept(y -= other.y) && noexcept(z -= other.z) && noexcept(w -= other.w)) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
		_NODISCARD constexpr Vector& operator*=(in<Vector> other) noexcept(noexcept(x *= other.x) && noexcept(y *= other.y) && noexcept(z *= other.z) && noexcept(w *= other.w)) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
		_NODISCARD constexpr Vector& operator*=(in<T> scaler) noexcept(noexcept(x *= scaler) && noexcept(y *= scaler) && noexcept(z *= scaler) && noexcept(w *= scaler)) { x *= scaler; y *= scaler; z *= scaler; w *= scaler; return *this; }
		_NODISCARD constexpr Vector& operator/=(in<T> scaler) noexcept(noexcept(x /= scaler) && noexcept(y /= scaler) && noexcept(z /= scaler) && noexcept(w /= scaler)) { x /= scaler; y /= scaler; z /= scaler; w /= scaler; return *this; }

		_NODISCARD constexpr bool operator==(in<Vector> other) const noexcept(noexcept(x == other.x) && noexcept(y == other.y) && noexcept(z == other.z) && noexcept(w == other.w)) { return x == other.x && y == other.y && z == other.z && w == other.w; }
		_NODISCARD constexpr bool operator!=(in<Vector> other) const noexcept(noexcept(x != other.x) && noexcept(y != other.y) && noexcept(z != other.z) && noexcept(w != other.w)) { return x != other.x || y != other.y || z != other.z || w != other.w; }
	};

	template<typename T>
	_NODISCARD static constexpr T Dot(in<Vector<4, T>> a, in<Vector<4, T>> b) noexcept(noexcept(a.Dot(b)))
	{ return a.Dot(b); }

	template<typename T>
	_NODISCARD static constexpr T SqrDistance(in<Vector<4, T>> a, in<Vector<4, T>> b) noexcept(noexcept(a.SqrDistance(b)))
	{ return a.SqrDistance(b); }
	template<typename T>
	_NODISCARD static T Distance(in<Vector<4, T>> a, in<Vector<4, T>> b) noexcept(noexcept(a.Distance(b)))
	{ return a.Distance(b); }

	typedef Vector<4, float> Vector4F;
	typedef Vector<4, double> Vector4D;
	typedef Vector<4, int> Vector4I;
}