#include "Math/PoseT.h"
#include "Math/VectorT.h"

template<typename TPos, typename TRot>
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
