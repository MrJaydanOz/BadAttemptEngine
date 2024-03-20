#pragma once
#include <iostream>
#include <stdexcept>

/*template<size_t C, typename T>
struct Vector
{
private:
    T elements[C];

public:
    constexpr Vector(const T& fill) noexcept
    {
        for (size_t i = 0; i < C; i++)
            elements[i] = fill;
    };
    template<typename... Args>
    constexpr Vector(Args... args) noexcept : elements{ args... }
    { 
        static_assert(sizeof...(Args) == C, "Number of arguments must match size of Vector.");
    }

    constexpr T& operator[](const size_t index)
    {
        if (index < C)
            throw std::out_of_range("Index must be smaller than the length of the Vector.");

        return elements[index];
    }
};*/

/*template<size_t C, typename T>
struct Vector
{

};

template<typename T>
struct Vector<2, T>
{
public:
    T x;
    T y;

public:
    constexpr Vector(T fill) noexcept : x(fill), y(fill) { };
    constexpr Vector(T x, T y) noexcept : x(x), y(y) { };

    constexpr T Dot(const Vector& other) const noexcept { return (x * other.x) + (y * other.y); }
    constexpr T SqrMagnitude() const noexcept { return Dot(*this); }
    constexpr T Cross(const Vector& other) const noexcept { return (x * other.y) + (y * other.x); }

    T Magnitude() const noexcept;
    Vector Rotate(const T& degrees) const noexcept;
    Vector InverseRotate(const T& degrees) const noexcept;

    constexpr bool operator==(const Vector& other) const noexcept { return x == other.x && y == other.y; }
    constexpr bool operator!=(const Vector& other) const noexcept { return x != other.x || y != other.y; }
    constexpr Vector operator+(const Vector& other) const noexcept { return Vector(x + other.x, y + other.y); }
    constexpr Vector& operator+=(const Vector& other) noexcept { return *this = *this + other; }
    constexpr Vector operator-(const Vector& other) const noexcept { return Vector(x - other.x, y - other.y); }
    constexpr Vector& operator-=(const Vector& other) noexcept { return *this = *this - other; }
    constexpr Vector operator*(const Vector& other) const noexcept { return Vector(x * other.x, y * other.y); }
    constexpr Vector& operator*=(const Vector& other) noexcept { return *this = *this * other; }
    constexpr Vector operator*(const T& scaler) const noexcept { return Vector(x * scaler, y * scaler); }
    constexpr Vector& operator*=(const T& scaler) noexcept { return *this = *this * scaler; }
    constexpr Vector operator/(const T& scaler) const noexcept { return Vector(x / scaler, y / scaler); }
    constexpr Vector& operator/=(const T& scaler) noexcept { return *this = *this / scaler; }
};

template<typename T>
static std::ostream& operator<<(std::ostream& stream, const Vector<2, T>& vector);
template<typename T>
constexpr static T Dot(const Vector<2, T>& a, const Vector<2, T>& b) noexcept { return a.Dot(b); }
template<typename T>
constexpr static T Cross(const Vector<2, T>& a, const Vector<2, T>& b) noexcept { return a.Cross(b); }

template<typename T>
struct Vector<3, T>
{
public:
    T x;
    T y;
    T z;

public:
    Vector(T fill) noexcept : x(fill), y(fill), z(fill) { };
    Vector(T x, T y, T z) noexcept : x(x), y(y), z(z) { };

    constexpr T Dot(const Vector& other) const noexcept { return (x * other.x) + (y * other.y) + (z * other.z); }
    constexpr T SqrMagnitude() const noexcept { return Dot(*this); }
    constexpr Vector Cross(const Vector& other) const noexcept { return Vector((y * other.z) - (z * other.y), (z * other.x) - (x * other.z), (x * other.y) - (y * other.x)); }

    T Magnitude() const noexcept;

    constexpr bool operator==(const Vector& other) const noexcept { return x == other.x && y == other.y && z == other.z; }
    constexpr bool operator!=(const Vector& other) const noexcept { return x != other.x || y != other.y || z != other.z; }
    constexpr Vector operator+(const Vector& other) const noexcept { return Vector(x + other.x, y + other.y, z + other.z); }
    constexpr Vector& operator+=(const Vector& other) noexcept { return *this = *this + other; }
    constexpr Vector operator-(const Vector& other) const noexcept { return Vector(x - other.x, y - other.y, z - other.z); }
    constexpr Vector& operator-=(const Vector& other) noexcept { return *this = *this - other; }
    constexpr Vector operator*(const Vector& other) const noexcept { return Vector(x * other.x, y * other.y, z * other.z); }
    constexpr Vector& operator*=(const Vector& other) noexcept { return *this = *this * other; }
    constexpr Vector operator*(const T& scaler) const noexcept { return Vector(x * scaler, y * scaler, z * scaler); }
    constexpr Vector& operator*=(const T& scaler) noexcept { return *this = *this * scaler; }
    constexpr Vector operator/(const T& scaler) const noexcept { return Vector(x / scaler, y / scaler, z / scaler); }
    constexpr Vector& operator/=(const T& scaler) noexcept { return *this = *this / scaler; }
};

template<typename T>
static std::ostream& operator<<(std::ostream& stream, const Vector<3, T>& vector);
template<typename T>
constexpr static T Dot(const Vector<3, T>& a, const Vector<3, T>& b) noexcept { return a.Dot(b); }
template<typename T>
constexpr static Vector<3, T> Cross(const Vector<3, T>& a, const Vector<3, T>& b) noexcept { return a.Cross(b); }

template<typename T>
struct Vector<4, T>
{
public:
    T x;
    T y;
    T z;
    T w;

    Vector(T fill) noexcept : x(fill), y(fill), z(fill), w(fill) { };
    Vector(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) { };

    constexpr T Dot(const Vector& other) const noexcept { return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w); }
    constexpr T SqrMagnitude() const noexcept { return Dot(*this); }

    T Magnitude() const noexcept;

    constexpr bool operator==(const Vector& other) const noexcept { return x == other.x && y == other.y && z == other.z && w == other.w; }
    constexpr bool operator!=(const Vector& other) const noexcept { return x != other.x || y != other.y || z != other.z || w != other.w; }
    constexpr Vector operator+(const Vector& other) const noexcept { return Vector(x + other.x, y + other.y, z + other.z, w + other.w); }
    constexpr Vector& operator+=(const Vector& other) noexcept { return *this = *this + other; }
    constexpr Vector operator-(const Vector& other) const noexcept { return Vector(x - other.x, y - other.y, z - other.z, w - other.w); }
    constexpr Vector& operator-=(const Vector& other) noexcept { return *this = *this - other; }
    constexpr Vector operator*(const Vector& other) const noexcept { return Vector(x * other.x, y * other.y, z * other.z, w * other.w); }
    constexpr Vector& operator*=(const Vector& other) noexcept { return *this = *this * other; }
    constexpr Vector operator*(const T& scaler) const noexcept { return Vector(x * scaler, y * scaler, z * scaler, w * scaler); }
    constexpr Vector& operator*=(const T& scaler) noexcept { return *this = *this * scaler; }
    constexpr Vector operator/(const T& scaler) const noexcept { return Vector(x / scaler, y / scaler, z / scaler, w * scaler); }
    constexpr Vector& operator/=(const T& scaler) noexcept { return *this = *this / scaler; }
};

template<typename T>
static std::ostream& operator<<(std::ostream& stream, const Vector<4, T>& vector);
template<typename T>
constexpr static T Dot(const Vector<4, T>& a, const Vector<4, T>& b) noexcept { return a.Dot(b); }

typedef Vector<2, float> Vector2F;
typedef Vector<2, double> Vector2D;
typedef Vector<2, int> Vector2I;

typedef Vector<3, float> Vector3F;
typedef Vector<3, double> Vector3D;
typedef Vector<3, int> Vector3I;

typedef Vector<4, float> Vector4F;
typedef Vector<4, double> Vector4D;
typedef Vector<4, int> Vector4I;*/

#pragma once

#define DECLARATION_VECTOR_N(vectorType, elementType, elementCount, ...) \
struct vectorType \
{ \
public: \
    __VA_ARGS__ \
 \
public: \
    vectorType operator+(const vectorType& other) const; \
    vectorType operator-(const vectorType& other) const; \
    vectorType operator*(const vectorType& other) const; \
    vectorType operator*(const elementType& scaler) const; \
    vectorType operator/(const elementType& scaler) const; \
    vectorType& operator+=(const vectorType& other); \
    vectorType& operator-=(const vectorType& other); \
    vectorType& operator*=(const vectorType& other); \
    vectorType& operator*=(const elementType& scaler); \
    vectorType& operator/=(const elementType& scaler); \
    bool operator==(const vectorType& other) const; \
    bool operator!=(const vectorType& other) const; \
};

#define DECLARATION_VECTOR_2(vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 2, \
    elementType x, y; \
public:  \
    vectorType(elementType x, elementType y) : x(x), y(y) { } \
    __VA_ARGS__ \
    operator Vector2<elementType>() const; \
    )

#define DECLARATION_VECTOR_3(vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 3, \
    elementType x, y, z; \
public:  \
    vectorType(elementType x, elementType y, elementType z) : x(x), y(y), z(z) { } \
    __VA_ARGS__ \
    operator Vector3<elementType>() const; \
    )

#define DECLARATION_VECTOR_4(vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 4, \
    elementType x, y, z, w; \
public:  \
    vectorType(elementType x, elementType y, elementType z, elementType w) : x(x), y(y), z(z), w(w) { } \
    __VA_ARGS__ \
    operator Vector4<elementType>() const; \
    )

#define DECLARATION_VECTOR_N_INTEGER_FUNCTIONS(vectorType, elementType) \
    elementType SqrMagnitude() const; \
    elementType SqrDistance(const vectorType& other) const; \
    elementType Dot(const vectorType& other) const; \
    static elementType Dot(const vectorType& a, const vectorType& b); \

#define DECLARATION_VECTOR_2_INTEGER_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_N_INTEGER_FUNCTIONS(vectorType, elementType) \
    elementType Cross(const vectorType& other) const; \
    static elementType Cross(const vectorType& a, const vectorType& b); \
    vectorType Rotate90() const; \
    vectorType InverseRotate90() const; \

#define DECLARATION_VECTOR_3_INTEGER_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_N_INTEGER_FUNCTIONS(vectorType, elementType) \
    vectorType Cross(const vectorType& other) const; \
    static vectorType Cross(const vectorType& a, const vectorType& b); \

#define DECLARATION_VECTOR_4_INTEGER_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_N_INTEGER_FUNCTIONS(vectorType, elementType) \

#define DECLARATION_VECTOR_N_FLOAT_FUNCTIONS(vectorType, elementType, elementCount) \
    elementType Magnitude() const; \
    elementType Distance(const vectorType& other) const; \

#define DECLARATION_VECTOR_2_FLOAT_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_2_INTEGER_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_N_FLOAT_FUNCTIONS(vectorType, elementType, 2) \
    vectorType Rotate(const elementType& degrees) const; \
    vectorType InverseRotate(const elementType& degrees) const; \

#define DECLARATION_VECTOR_3_FLOAT_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_3_INTEGER_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_N_FLOAT_FUNCTIONS(vectorType, elementType, 3) \

#define DECLARATION_VECTOR_4_FLOAT_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_4_INTEGER_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_N_FLOAT_FUNCTIONS(vectorType, elementType, 4) \

#define DECLARATION_VECTOR_2_FLOAT(vectorType, elementType, ...) DECLARATION_VECTOR_2(vectorType, elementType, DECLARATION_VECTOR_2_FLOAT_FUNCTIONS(vectorType, elementType) __VA_ARGS__)
#define DECLARATION_VECTOR_3_FLOAT(vectorType, elementType, ...) DECLARATION_VECTOR_3(vectorType, elementType, DECLARATION_VECTOR_3_FLOAT_FUNCTIONS(vectorType, elementType) __VA_ARGS__)
#define DECLARATION_VECTOR_4_FLOAT(vectorType, elementType, ...) DECLARATION_VECTOR_4(vectorType, elementType, DECLARATION_VECTOR_4_FLOAT_FUNCTIONS(vectorType, elementType) __VA_ARGS__)

#define DECLARATION_VECTOR_2_INTEGER(vectorType, elementType, ...) DECLARATION_VECTOR_2(vectorType, elementType, DECLARATION_VECTOR_2_INTEGER_FUNCTIONS(vectorType, elementType) __VA_ARGS__)
#define DECLARATION_VECTOR_3_INTEGER(vectorType, elementType, ...) DECLARATION_VECTOR_3(vectorType, elementType, DECLARATION_VECTOR_3_INTEGER_FUNCTIONS(vectorType, elementType) __VA_ARGS__)
#define DECLARATION_VECTOR_4_INTEGER(vectorType, elementType, ...) DECLARATION_VECTOR_4(vectorType, elementType, DECLARATION_VECTOR_4_INTEGER_FUNCTIONS(vectorType, elementType) __VA_ARGS__)

template<typename T>
class Vector2
{
public:
    T x, y;

public:
    Vector2(T x, T y) : x(x), y(y) { }
};

template<typename T>
class Vector3
{
public:
    T x, y, z;

public:
    Vector3(T x, T y, T z) : x(x), y(y), z(z) { }
};

template<typename T>
class Vector4
{
public:
    T x, y, z, w;

public:
    Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }
};

DECLARATION_VECTOR_2_FLOAT(Vector2F, float)
DECLARATION_VECTOR_3_FLOAT(Vector3F, float)
DECLARATION_VECTOR_4_FLOAT(Vector4F, float)

DECLARATION_VECTOR_2_FLOAT(Vector2D, double)
DECLARATION_VECTOR_3_FLOAT(Vector3D, double)
DECLARATION_VECTOR_4_FLOAT(Vector4D, double)

DECLARATION_VECTOR_2_INTEGER(Vector2I, int)
DECLARATION_VECTOR_3_INTEGER(Vector3I, int)
DECLARATION_VECTOR_4_INTEGER(Vector4I, int)

DECLARATION_VECTOR_2_INTEGER(Vector2L, long)
DECLARATION_VECTOR_3_INTEGER(Vector3L, long)
DECLARATION_VECTOR_4_INTEGER(Vector4L, long)
