#include "Math/PoseT.h"
#include "Math/VectorT.h"

/*template<typename TPos, typename TRot>
Vector<2, TPos> Pose<TPos, TRot>::TransformPoint(const Vector<2, TPos>& point) const noexcept { return TransformDirection(point) + position; }

template<typename TPos, typename TRot>
Vector<2, TPos> Pose<TPos, TRot>::TransformDirection(const Vector<2, TPos>& direction) const noexcept { return direction.Rotate(rotation); }

template<typename TPos, typename TRot>
TRot Pose<TPos, TRot>::TransformRotation(const TRot& rotation) const noexcept { return rotation + this->rotation; }

template<typename TPos, typename TRot>
Pose<TPos, TRot> Pose<TPos, TRot>::TransformPose(const Pose& pose) const noexcept { return Pose(TransformPoint(pose.position), TransformRotation(pose.rotation)); }

template<typename TPos, typename TRot>
Vector<2, TPos> Pose<TPos, TRot>::InverseTransformPoint(const Vector<2, TPos>& point) const noexcept { return InverseTransformDirection(point - position); }

template<typename TPos, typename TRot>
Vector<2, TPos> Pose<TPos, TRot>::InverseTransformDirection(const Vector<2, TPos>& direction) const noexcept { return direction.InverseRotate(rotation); }

template<typename TPos, typename TRot>
TRot Pose<TPos, TRot>::InverseTransformRotation(const TRot& rotation) const noexcept { return rotation - this->rotation; }

template<typename TPos, typename TRot>
Pose<TPos, TRot> Pose<TPos, TRot>::InverseTransformPose(const Pose<TPos, TRot>& pose) const noexcept { return Pose(InverseTransformPoint(pose.position), InverseTransformRotation(pose.rotation)); }
*/
PoseF::PoseF(Vector2F position, float rotation) : position(position), rotation(rotation) { }

Vector2F PoseF::TransformPoint(const Vector2F& point) { return TransformDirection(point) + position; }

Vector2F PoseF::TransformDirection(const Vector2F& direction) { return direction.Rotate(rotation); }

float PoseF::TransformRotation(const float& rotation) { return rotation + this->rotation; }

PoseF PoseF::TransformPose(const PoseF& pose) { return PoseF(TransformPoint(pose.position), TransformRotation(pose.rotation)); }

Vector2F PoseF::InverseTransformPoint(const Vector2F& point) { return InverseTransformDirection(point - position); }

Vector2F PoseF::InverseTransformDirection(const Vector2F& direction) { return direction.InverseRotate(rotation); }

float PoseF::InverseTransformRotation(const float& rotation) { return rotation - this->rotation; }

PoseF PoseF::InverseTransformPose(const PoseF& pose) { return PoseF(InverseTransformPoint(pose.position), InverseTransformRotation(pose.rotation)); }
