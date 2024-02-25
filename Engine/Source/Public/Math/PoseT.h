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
	poseType(positionType position, rotationType rotation); \
	positionType TransformPoint(const positionType& point); \
	positionType TransformDirection(const positionType& direction); \
	rotationType TransformRotation(const rotationType& rotation); \
	poseType TransformPose(const poseType& pose); \
	positionType InverseTransformPoint(const positionType& point); \
	positionType InverseTransformDirection(const positionType& direction); \
	rotationType InverseTransformRotation(const rotationType& rotation); \
	poseType InverseTransformPose(const poseType& pose); \
    __VA_ARGS__ \
};

DECLARATION_POSE(PoseF, Vector2F, float, float)
DECLARATION_POSE(PoseD, Vector2D, double, double)