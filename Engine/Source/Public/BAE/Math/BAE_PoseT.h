#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_PoseT.h"))
#endif
#include "Math/BAE_VectorT.h"

namespace bae
{
#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Pose<typename, typename>))
#endif
	template<typename TPosition, typename TRotation = TPosition>
	class Pose
	{
		typedef Vector<2, TPosition> TPositionVector;

	public:
		TPositionVector position;
		TRotation rotation;

	public:
		constexpr Pose() :
			position(0.0f, 0.0f), rotation(0.0f) { }
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

		friend std::ostream& operator<<(ref<std::ostream> stream, in<Pose> pose)
		{
			return stream <<
				 "(x:" << std::setprecision(2) << std::fixed << pose.position.x <<
				", y:" << std::setprecision(2) << std::fixed << pose.position.y <<
				", r:" << std::setprecision(2) << std::fixed << pose.rotation << ')';
		}

		constexpr Pose& operator=(in<Pose> other) noexcept(noexcept(position = other.position) && noexcept(rotation = other.rotation)) { position = other.position; rotation = other.rotation; return *this; }
	};

	typedef Pose<float> PoseF;
	typedef Pose<double> PoseD;
}