#pragma once
#include "VectorT.h"

#define DECLARATION_RECT(rectType, vectorType, elementType, ...) \
struct rectType \
{ \
public: \
    vectorType min, max; \
 \
public: \
    rectType(vectorType min, vectorType max) noexcept : min(min), max(max) { } \
    rectType(elementType minX, elementType minY, elementType maxX, elementType maxY) noexcept : min(minX, minY), max(maxX, maxY) { } \
    __VA_ARGS__ \
};

#define DECLARATION_RECT_FLOAT_FUNCTIONS(rectType, vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 2, \
    __VA_ARGS__ \
    )

#define DECLARATION_RECT_INTEGER_FUNCTIONS(rectType, vectorType, elementType, ...) \
    DECLARATION_VECTOR_N(vectorType, elementType, 2, \
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
DECLARATION_RECT_INTEGER(RectL, Vector2L, long)