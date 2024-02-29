#pragma once
#include "VectorT.h"

#define DECLARATION_POSE(poseType, positionType, positionElementType, rotationType, ...) \
struct poseType \
{ \
public: \
    positionType position; \
    rotationType rotation; \
 \
public: \
	poseType(positionType position, rotationType rotation) noexcept; \
	positionType TransformPoint(const positionType& point) const noexcept; \
	positionType TransformDirection(const positionType& direction) const noexcept; \
	rotationType TransformRotation(const rotationType& rotation) const noexcept; \
	poseType TransformPose(const poseType& pose) const noexcept; \
	positionType InverseTransformPoint(const positionType& point) const noexcept; \
	positionType InverseTransformDirection(const positionType& direction) const noexcept; \
	rotationType InverseTransformRotation(const rotationType& rotation) const noexcept; \
	poseType InverseTransformPose(const poseType& pose) const noexcept; \
    __VA_ARGS__ \
};

DECLARATION_POSE(PoseF, Vector2F, float, float)
DECLARATION_POSE(PoseD, Vector2D, double, double)