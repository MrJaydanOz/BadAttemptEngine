#include "Math/PoseT.h"

#define DEFINITION_POSE(poseType, positionType, positionElementType, rotationType) \
poseType::poseType(positionType position, rotationType rotation) noexcept : position(position), rotation(rotation) { } \
positionType poseType::TransformPoint(const positionType& point) const noexcept { return TransformDirection(point) + position; } \
positionType poseType::TransformDirection(const positionType& direction) const noexcept { return direction.Rotate(rotation); } \
rotationType poseType::TransformRotation(const rotationType& rotation) const noexcept { return rotation + this->rotation; } \
poseType poseType::TransformPose(const poseType& pose) const noexcept { return poseType(TransformPoint(pose.position), TransformRotation(pose.rotation)); } \
positionType poseType::InverseTransformPoint(const positionType& point) const noexcept { return InverseTransformDirection(point - position); } \
positionType poseType::InverseTransformDirection(const positionType& direction) const noexcept { return direction.InverseRotate(rotation); } \
rotationType poseType::InverseTransformRotation(const rotationType& rotation) const noexcept { return rotation - this->rotation; } \
poseType poseType::InverseTransformPose(const poseType& pose) const noexcept { return poseType(InverseTransformPoint(pose.position), InverseTransformRotation(pose.rotation)); }

DEFINITION_POSE(PoseF, Vector2F, float, float)
DEFINITION_POSE(PoseD, Vector2D, double, double)