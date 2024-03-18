#pragma once
#include <type_traits>

/*#define DECLARATION_VECTOR_N(vectorType, elementType, elementCount, ...) \
struct vectorType \
{ \
public: \
    __VA_ARGS__ \
 \
public: \
    bool operator==(const vectorType& other) const noexcept; \
    bool operator!=(const vectorType& other) const noexcept; \
    vectorType operator+(const vectorType& other) const noexcept; \
    vectorType& operator+=(const vectorType& other) noexcept; \
    vectorType operator-(const vectorType& other) const noexcept; \
    vectorType& operator-=(const vectorType& other) noexcept; \
    vectorType operator*(const vectorType& other) const noexcept; \
    vectorType& operator*=(const vectorType& other) noexcept; \
    vectorType operator*(const elementType& scaler) const noexcept; \
    vectorType& operator*=(const elementType& scaler) noexcept; \
    vectorType operator/(const elementType& scaler) const noexcept; \
    vectorType& operator/=(const elementType& scaler) noexcept; \
};

#define DECLARATION_VECTOR_2(vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 2, \
    elementType x, y; \
public:  \
    vectorType(elementType x, elementType y) noexcept : x(x), y(y) { } \
    vectorType(elementType fill) noexcept : x(fill), y(fill) { } \
    __VA_ARGS__ \
    operator Vector2<elementType>() const noexcept; \
    )

#define DECLARATION_VECTOR_3(vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 3, \
    elementType x, y, z; \
public:  \
    vectorType(elementType x, elementType y, elementType z) noexcept : x(x), y(y), z(z) { } \
    vectorType(elementType fill) noexcept : x(fill), y(fill), z(fill) { } \
    __VA_ARGS__ \
    operator Vector3<elementType>() const noexcept; \
    )

#define DECLARATION_VECTOR_4(vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 4, \
    elementType x, y, z, w; \
public:  \
    vectorType(elementType x, elementType y, elementType z, elementType w) noexcept : x(x), y(y), z(z), w(w) { } \
    vectorType(elementType fill) noexcept : x(fill), y(fill), z(fill), w(fill) { } \
    __VA_ARGS__ \
    operator Vector4<elementType>() const noexcept; \
    )

#define DECLARATION_VECTOR_N_INTEGER_FUNCTIONS(vectorType, elementType) \
    elementType SqrMagnitude() const noexcept; \
    elementType SqrDistance(const vectorType& other) const noexcept; \
    elementType Dot(const vectorType& other) const noexcept; \
    static elementType Dot(const vectorType& a, const vectorType& b) noexcept; \

#define DECLARATION_VECTOR_2_INTEGER_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_N_INTEGER_FUNCTIONS(vectorType, elementType) \
    elementType Cross(const vectorType& other) const noexcept; \
    static elementType Cross(const vectorType& a, const vectorType& b) noexcept; \
    vectorType Rotate90() const noexcept; \
    vectorType InverseRotate90() const noexcept; \

#define DECLARATION_VECTOR_3_INTEGER_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_N_INTEGER_FUNCTIONS(vectorType, elementType) \
    vectorType Cross(const vectorType& other) const noexcept; \
    static vectorType Cross(const vectorType& a, const vectorType& b) noexcept; \

#define DECLARATION_VECTOR_4_INTEGER_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_N_INTEGER_FUNCTIONS(vectorType, elementType) \

#define DECLARATION_VECTOR_N_FLOAT_FUNCTIONS(vectorType, elementType, elementCount) \
    elementType Magnitude() const noexcept; \
    elementType Distance(const vectorType& other) const noexcept; \

#define DECLARATION_VECTOR_2_FLOAT_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_2_INTEGER_FUNCTIONS(vectorType, elementType) \
    DECLARATION_VECTOR_N_FLOAT_FUNCTIONS(vectorType, elementType, 2) \
    vectorType Rotate(const elementType& degrees) const noexcept; \
    vectorType InverseRotate(const elementType& degrees) const noexcept; \

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
    Vector2(T x, T y) noexcept : x(x), y(y) { }
    Vector2(T fill) noexcept : x(fill), y(fill) { }
};

template<typename T>
class Vector3
{
public:
    T x, y, z;

public:
    Vector3(T x, T y, T z) noexcept : x(x), y(y), z(z) { }
    Vector3(T fill) noexcept : x(fill), y(fill), z(fill) { }
};

template<typename T>
class Vector4
{
public:
    T x, y, z, w;

public:
    Vector4(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) { }
    Vector4(T fill) noexcept : x(fill), y(fill), z(fill), w(fill) { }
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
DECLARATION_VECTOR_4_INTEGER(Vector4L, long)*/

template<int C, typename T>
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

    constexpr T Dot(const Vector& other) noexcept { return (x * other.x) + (y * other.y); }
    constexpr T SqrMagnitude() noexcept { return (x * x) + (y * y); }

    T Magnitude() noexcept;
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
constexpr static T Dot(const Vector<2, T>& a, const Vector<2, T>& b) noexcept { return (a.x * b.x) + (a.y * b.y); }

template<typename T>
struct Vector<3, T>
{
public:
    T x;
    T y;
    T z;

    Vector(T fill) noexcept : x(fill), y(fill), z(fill) { };
    Vector(T x, T y, T z) noexcept : x(x), y(y), z(z) { };
};

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
};

typedef Vector<2, float> Vector2F;
typedef Vector<2, double> Vector2D;
typedef Vector<2, int> Vector2I;

typedef Vector<3, float> Vector3F;
typedef Vector<3, double> Vector3D;
typedef Vector<3, int> Vector3I;

typedef Vector<4, float> Vector4F;
typedef Vector<4, double> Vector4D;
typedef Vector<4, int> Vector4I;