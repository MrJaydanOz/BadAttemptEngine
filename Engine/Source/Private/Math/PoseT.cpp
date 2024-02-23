#include "Math/PoseT.h"

PoseF::PoseF(Vector2F position, float rotation) : position(position), rotation(rotation) { }

Vector2F PoseF::TransformPoint(const Vector2F& point) { return TransformDirection(point) + position; }

Vector2F PoseF::TransformDirection(const Vector2F& direction) { return direction.Rotate(rotation); }

float PoseF::TransformRotation(const float& rotation) { return rotation + this->rotation; }

PoseF PoseF::TransformPose(const PoseF& pose) { return PoseF(TransformPoint(pose.position), TransformRotation(pose.rotation)); }

Vector2F PoseF::InverseTransformPoint(const Vector2F& point) { return InverseTransformDirection(point - position); }

Vector2F PoseF::InverseTransformDirection(const Vector2F& direction) { return direction.InverseRotate(rotation); }

float PoseF::InverseTransformRotation(const float& rotation) { return rotation - this->rotation; }

PoseF PoseF::InverseTransformPose(const PoseF& pose) { return PoseF(InverseTransformPoint(pose.position), InverseTransformRotation(pose.rotation)); }
