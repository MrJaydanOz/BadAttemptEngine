#include "Math/VectorT.h"
#include <iostream>
#include <cmath>
#include <string>
#include <limits>
#include <type_traits>
#include "For.h"
#include "Math/Constants.h"

#define DEFINITION_VECTOR_N(vectorType, elementType, elementCount) \

#define DEFINITION_VECTOR_N_OPERATORS(vectorType, elementType, elementCount, ...) \
    vectorType::operator Vector##elementCount<elementType>() const noexcept { return Vector##elementCount<elementType>(__VA_ARGS__); } \
    bool vectorType::operator==(const vectorType& other) const noexcept { return FOR_AA_IN(elementCount, , == other., , &&, __VA_ARGS__); } \
    bool vectorType::operator!=(const vectorType& other) const noexcept { return FOR_AA_IN(elementCount, , != other., , ||, __VA_ARGS__); } \
    vectorType vectorType::operator+(const vectorType& other) const noexcept { return vectorType(FOR_AA_IN(elementCount, , + other., , COMMA2, __VA_ARGS__)); } \
    vectorType& vectorType::operator+=(const vectorType& other) noexcept { return *this = *this + other; } \
    vectorType vectorType::operator-(const vectorType& other) const noexcept { return vectorType(FOR_AA_IN(elementCount, , - other., , COMMA2, __VA_ARGS__)); } \
    vectorType& vectorType::operator-=(const vectorType& other) noexcept { return *this = *this - other; } \
    vectorType vectorType::operator*(const vectorType& other) const noexcept { return vectorType(FOR_AA_IN(elementCount, , * other., , COMMA2, __VA_ARGS__)); } \
    vectorType& vectorType::operator*=(const vectorType& other) noexcept { return *this = *this * other; } \
    vectorType vectorType::operator*(const elementType& scaler) const noexcept { return vectorType(FOR_A_IN(elementCount, , * scaler, COMMA2, __VA_ARGS__)); } \
    vectorType& vectorType::operator*=(const elementType& scaler) noexcept { return *this = *this * scaler; } \
    vectorType vectorType::operator/(const elementType& scaler) const noexcept { return vectorType(FOR_A_IN(elementCount, , / scaler, COMMA2, __VA_ARGS__)); } \
    vectorType& vectorType::operator/=(const elementType& scaler) noexcept { return *this = *this / scaler; } \
    static std::ostream& operator<<(std::ostream& stream, vectorType const& vector) { return stream << "(" << FOR_A_IN(elementCount, vector.,, << ", " <<, __VA_ARGS__) << ")"; } \

#define DEFINITION_VECTOR_2(vectorType, elementType) \
    DEFINITION_VECTOR_N(vectorType, elementType, 2) \
    DEFINITION_VECTOR_N_OPERATORS(vectorType, elementType, 2, x, y) \

#define DEFINITION_VECTOR_3(vectorType, elementType) \
    DEFINITION_VECTOR_N(vectorType, elementType, 3) \
    DEFINITION_VECTOR_N_OPERATORS(vectorType, elementType, 3, x, y, z) \

#define DEFINITION_VECTOR_4(vectorType, elementType) \
    DEFINITION_VECTOR_N(vectorType, elementType, 4) \
    DEFINITION_VECTOR_N_OPERATORS(vectorType, elementType, 4, x, y, z, w) \

#define DEFINITION_VECTOR_N_INTEGER(vectorType, elementType, elementCount) \
    elementType vectorType::SqrMagnitude() const noexcept { return Dot(*this, *this); } \
    elementType vectorType::SqrDistance(const vectorType& other) const noexcept { vectorType delta = other - *this; return delta.SqrMagnitude(); } \
    elementType vectorType::Dot(const vectorType& other) const noexcept { return Dot(*this, other); } \

#define DEFINITION_VECTOR_2_INTEGER(vectorType, elementType) \
    DEFINITION_VECTOR_2(vectorType, elementType) \
    DEFINITION_VECTOR_N_INTEGER(vectorType, elementType, elementCount) \
    elementType vectorType::Dot(const vectorType& a, const vectorType& b) noexcept { return (a.x * b.x) + (a.y * b.y); } \
    elementType vectorType::Cross(const vectorType& other) const noexcept { return Cross(*this, other); } \
    elementType vectorType::Cross(const vectorType& a, const vectorType& b) noexcept { return (a.x * b.y) + (a.y * b.x); } \
    vectorType vectorType::Rotate90() const noexcept { return vectorType(-y, x); }\
    vectorType vectorType::InverseRotate90() const noexcept { return vectorType(y, -x); } \

#define DEFINITION_VECTOR_3_INTEGER(vectorType, elementType) \
    DEFINITION_VECTOR_3(vectorType, elementType) \
    DEFINITION_VECTOR_N_INTEGER(vectorType, elementType, elementCount) \
    elementType vectorType::Dot(const vectorType& a, const vectorType& b) noexcept { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); } \
    vectorType vectorType::Cross(const vectorType& other) const noexcept { return Cross(*this, other); } \
    vectorType vectorType::Cross(const vectorType& a, const vectorType& b) noexcept { return vectorType((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)); } \

#define DEFINITION_VECTOR_4_INTEGER(vectorType, elementType) \
    DEFINITION_VECTOR_4(vectorType, elementType) \
    DEFINITION_VECTOR_N_INTEGER(vectorType, elementType, elementCount) \
    elementType vectorType::Dot(const vectorType& a, const vectorType& b) noexcept { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w); } \

#define DEFINITION_VECTOR_N_FLOAT(vectorType, elementType, elementCount) \
    elementType vectorType::Magnitude() const noexcept { return std::sqrt(SqrMagnitude()); } \
    elementType vectorType::Distance(const vectorType& other) const noexcept { vectorType delta = other - *this; return delta.Magnitude(); } \

#define DEFINITION_VECTOR_2_FLOAT(vectorType, elementType) \
    DEFINITION_VECTOR_2_INTEGER(vectorType, elementType) \
    DEFINITION_VECTOR_N_FLOAT(vectorType, elementType, 2) \
    vectorType vectorType::Rotate(const elementType& degrees) const noexcept \
    { \
        elementType sin = (elementType)std::sin(degrees * DEG_TO_RAD_D); \
        elementType cos = (elementType)std::cos(degrees * DEG_TO_RAD_D); \
 \
        elementType tx = x; \
        elementType ty = y; \
        return vectorType((cos * tx) - (sin * ty), (sin * tx) + (cos * ty)); \
    } \
    vectorType vectorType::InverseRotate(const elementType& degrees) const noexcept { return Rotate(-degrees); }\

#define DEFINITION_VECTOR_3_FLOAT(vectorType, elementType) \
    DEFINITION_VECTOR_3_INTEGER(vectorType, elementType) \
    DEFINITION_VECTOR_N_FLOAT(vectorType, elementType, 3) \

#define DEFINITION_VECTOR_4_FLOAT(vectorType, elementType) \
    DEFINITION_VECTOR_4_INTEGER(vectorType, elementType) \
    DEFINITION_VECTOR_N_FLOAT(vectorType, elementType, 4) \

DEFINITION_VECTOR_2_FLOAT(Vector2F, float)
DEFINITION_VECTOR_3_FLOAT(Vector3F, float)
DEFINITION_VECTOR_4_FLOAT(Vector4F, float)

DEFINITION_VECTOR_2_FLOAT(Vector2D, double)
DEFINITION_VECTOR_3_FLOAT(Vector3D, double)
DEFINITION_VECTOR_4_FLOAT(Vector4D, double)

DEFINITION_VECTOR_2_INTEGER(Vector2I, int)
DEFINITION_VECTOR_3_INTEGER(Vector3I, int)
DEFINITION_VECTOR_4_INTEGER(Vector4I, int)

DEFINITION_VECTOR_2_INTEGER(Vector2L, long int)
DEFINITION_VECTOR_3_INTEGER(Vector3L, long int)
DEFINITION_VECTOR_4_INTEGER(Vector4L, long int)