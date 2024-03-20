/*#pragma once
#include "VectorT.h"

template<typename TPos, typename TRot>
struct Pose
{
public:
	Vector<2, TPos> position;
	TRot rotation;

public:
	constexpr Pose(Vector<2, TPos> position, TRot rotation) noexcept : position(position), rotation(rotation) { }
	Vector<2, TPos> TransformPoint(const Vector<2, TPos>& point) const noexcept;
	Vector<2, TPos> TransformDirection(const Vector<2, TPos>& direction) const noexcept;
	TRot TransformRotation(const TRot& rotation) const noexcept;
	Pose TransformPose(const Pose& pose) const noexcept;
	Vector<2, TPos> InverseTransformPoint(const Vector<2, TPos>& point) const noexcept;
	Vector<2, TPos> InverseTransformDirection(const Vector<2, TPos>& direction) const noexcept;
	TRot InverseTransformRotation(const TRot& rotation) const noexcept;
	Pose InverseTransformPose(const Pose& pose) const noexcept;
};

typedef Pose<float, float> PoseF;
typedef Pose<double, double> PoseD;*/
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
