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
		constexpr Pose(in<TPositionVector> position, in<TRotation> rotation) :
			position(position), rotation(rotation) { }

		TPositionVector TransformPoint(in<TPositionVector> point) const noexcept(noexcept(TransformDirection(point) + position)) 
		{ return TransformDirection(point) + position; }

		TPositionVector TransformDirection(in<TPositionVector> direction) const noexcept(noexcept(direction.Rotate(rotation))) 
		{ return direction.Rotate(rotation); }

		TRotation TransformRotation(in<TRotation> rotation) const noexcept(noexcept(rotation + this->rotation))
		{ return rotation + this->rotation; }

		Pose TransformPose(in<Pose> pose) const noexcept(noexcept(Pose(TransformPoint(pose.position), TransformRotation(pose.rotation))))
		{ return Pose(TransformPoint(pose.position), TransformRotation(pose.rotation)); }

		TPositionVector InverseTransformPoint(in<TPositionVector> point) const noexcept(noexcept(InverseTransformDirection(point - position))) 
		{ return InverseTransformDirection(point - position); }

		TPositionVector InverseTransformDirection(in<TPositionVector> direction) const noexcept(noexcept(direction.InverseRotate(rotation))) 
		{ return direction.InverseRotate(rotation); }

		TRotation InverseTransformRotation(in<TRotation> rotation) const noexcept(noexcept(rotation - this->rotation))
		{ return rotation - this->rotation; }

		Pose InverseTransformPose(in<Pose> pose) const noexcept(noexcept(Pose(InverseTransformPoint(pose.position), InverseTransformRotation(pose.rotation)))) 
		{ return Pose(InverseTransformPoint(pose.position), InverseTransformRotation(pose.rotation)); }
	};

	typedef Pose<float> PoseF;
	typedef Pose<double> PoseD;
}