#pragma once
#include "VectorT.h"
#include "Def.h"

namespace bae
{
	template<typename TPosition, typename TRotation = TPosition>
	class Pose
	{
		typedef Vector<2, TPosition> TPositionVector;

	public:
		TPositionVector position;
		TRotation rotation;

	public:
		constexpr Pose(IN(TPositionVector) position, IN(TRotation) rotation) :
			position(position), rotation(rotation) { }

		TPositionVector TransformPoint(IN(TPositionVector) point) const noexcept(noexcept(TransformDirection(point) + position)) 
		{ return TransformDirection(point) + position; }

		TPositionVector TransformDirection(IN(TPositionVector) direction) const noexcept(noexcept(direction.Rotate(rotation))) 
		{ return direction.Rotate(rotation); }

		TRotation TransformRotation(IN(TRotation) rotation) const noexcept(noexcept(rotation + this->rotation))
		{ return rotation + this->rotation; }

		Pose TransformPose(IN(Pose) pose) const noexcept(noexcept(PoseF(TransformPoint(pose.position), TransformRotation(pose.rotation))))
		{ return PoseF(TransformPoint(pose.position), TransformRotation(pose.rotation)); }

		TPositionVector InverseTransformPoint(IN(TPositionVector) point) const noexcept(noexcept(InverseTransformDirection(point - position))) 
		{ return InverseTransformDirection(point - position); }

		TPositionVector InverseTransformDirection(IN(TPositionVector) direction) const noexcept(noexcept(direction.InverseRotate(rotation))) 
		{ return direction.InverseRotate(rotation); }

		TRotation InverseTransformRotation(IN(TRotation) rotation) const noexcept(noexcept(rotation - this->rotation))
		{ return rotation - this->rotation; }

		Pose InverseTransformPose(IN(Pose) pose) const noexcept(noexcept(PoseF(InverseTransformPoint(pose.position), InverseTransformRotation(pose.rotation)))) 
		{ return PoseF(InverseTransformPoint(pose.position), InverseTransformRotation(pose.rotation)); }
	};

	typedef Pose<float> PoseF;
	typedef Pose<double> PoseD;
}