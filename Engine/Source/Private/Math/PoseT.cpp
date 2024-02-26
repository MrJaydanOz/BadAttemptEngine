#include "Math/PoseT.h"

#define DEFINITION_POSE(poseType, positionType, positionElementType, rotationType) \
poseType::poseType(positionType position, rotationType rotation) : position(position), rotation(rotation) { } \
positionType poseType::TransformPoint(const positionType& point) { return TransformDirection(point) + position; } \
positionType poseType::TransformDirection(const positionType& direction) { return direction.Rotate(rotation); } \
rotationType poseType::TransformRotation(const rotationType& rotation) { return rotation + this->rotation; } \
poseType poseType::TransformPose(const poseType& pose) { return poseType(TransformPoint(pose.position), TransformRotation(pose.rotation)); } \
positionType poseType::InverseTransformPoint(const positionType& point) { return InverseTransformDirection(point - position); } \
positionType poseType::InverseTransformDirection(const positionType& direction) { return direction.InverseRotate(rotation); } \
rotationType poseType::InverseTransformRotation(const rotationType& rotation) { return rotation - this->rotation; } \
poseType poseType::InverseTransformPose(const poseType& pose) { return poseType(InverseTransformPoint(pose.position), InverseTransformRotation(pose.rotation)); }

DEFINITION_POSE(PoseF, Vector2F, float, float)
DEFINITION_POSE(PoseD, Vector2D, double, double)