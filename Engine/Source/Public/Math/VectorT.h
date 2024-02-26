#pragma once

#define DECLARATION_VECTOR_N(vectorType, elementType, elementCount, ...) \
struct vectorType \
{ \
public: \
    __VA_ARGS__ \
 \
public: \
    bool operator==(const vectorType& other) const; \
    bool operator!=(const vectorType& other) const; \
    vectorType operator+(const vectorType& other) const; \
    vectorType& operator+=(const vectorType& other); \
    vectorType operator-(const vectorType& other) const; \
    vectorType& operator-=(const vectorType& other); \
    vectorType operator*(const vectorType& other) const; \
    vectorType& operator*=(const vectorType& other); \
    vectorType operator*(const elementType& scaler) const; \
    vectorType& operator*=(const elementType& scaler); \
    vectorType operator/(const elementType& scaler) const; \
    vectorType& operator/=(const elementType& scaler); \
};

#define DECLARATION_VECTOR_2(vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 2, \
    elementType x, y; \
public:  \
    vectorType(elementType x, elementType y) : x(x), y(y) { } \
    vectorType(elementType fill) : x(fill), y(fill) { } \
    __VA_ARGS__ \
    operator Vector2<elementType>() const; \
    )

#define DECLARATION_VECTOR_3(vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 3, \
    elementType x, y, z; \
public:  \
    vectorType(elementType x, elementType y, elementType z) : x(x), y(y), z(z) { } \
    vectorType(elementType fill) : x(fill), y(fill), z(fill) { } \
    __VA_ARGS__ \
    operator Vector3<elementType>() const; \
    )

#define DECLARATION_VECTOR_4(vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 4, \
    elementType x, y, z, w; \
public:  \
    vectorType(elementType x, elementType y, elementType z, elementType w) : x(x), y(y), z(z), w(w) { } \
    vectorType(elementType fill) : x(fill), y(fill), z(fill), w(fill) { } \
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
    Vector2(T fill) : x(fill), y(fill) { }
};

template<typename T>
class Vector3
{
public:
    T x, y, z;

public:
    Vector3(T x, T y, T z) : x(x), y(y), z(z) { }
    Vector3(T fill) : x(fill), y(fill), z(fill) { }
};

template<typename T>
class Vector4
{
public:
    T x, y, z, w;

public:
    Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }
    Vector4(T fill) : x(fill), y(fill), z(fill), w(fill) { }
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