#include "Nodes/BAE_Transform.h"
#include <algorithm>
#include <string>
#include "BAE_Def.h"
#include "Nodes/BAE_Node.h"
#include "Math/BAE_PoseT.h"

namespace bae
{
	Transform::Transform(in<Node*> parent) noexcept : 
		Node::Node(parent),
		_pose(),
		_hasModified(false)
	{ }

	Transform::~Transform() noexcept { }

	void Transform::Create(in<const char*> name)
	{
		Node::Create(name);
	}

	void Transform::Destroy()
	{
		Node::Destroy();
	}

	PoseF Transform::GetLocalPose() const noexcept { return _pose; }
	void Transform::SetLocalPose(in<PoseF> pose) noexcept { _pose = pose; _hasModified = true; }

	PoseF Transform::GetPose() const noexcept
	{
		Transform* parentTransform;

		if (TryFindParentOfTypeRecursive<Transform>(parentTransform))
			return parentTransform->TransformPose(GetLocalPose());
		else
			return GetLocalPose();
	}
	void Transform::SetPose(in<PoseF> pose) noexcept
	{
		Transform* parentTransform;

		if (TryFindParentOfTypeRecursive<Transform>(parentTransform))
			SetLocalPose(parentTransform->InverseTransformPose(pose));
		else
			SetLocalPose(pose);
	}

	Vector2F Transform::GetLocalPosition() const noexcept { return _pose.position; }
	void Transform::SetLocalPosition(in<Vector2F> position) noexcept { _pose.position = position; _hasModified = true; }

	Vector2F Transform::GetPosition() const noexcept
	{
		Transform* parentTransform;

		if (TryFindParentOfTypeRecursive<Transform>(parentTransform))
			return parentTransform->TransformPoint(GetLocalPosition());
		else
			return GetLocalPosition();
	}
	void Transform::SetPosition(in<Vector2F> position) noexcept
	{
		Transform* parentTransform;

		if (TryFindParentOfTypeRecursive<Transform>(parentTransform))
			SetLocalPosition(parentTransform->InverseTransformPoint(position));
		else
			SetLocalPosition(position);
	}

	float Transform::GetLocalRotation() const noexcept { return _pose.rotation; }
	void Transform::SetLocalRotation(in<float> rotation) noexcept { _pose.rotation = rotation; _hasModified = true; }

	float Transform::GetRotation() const noexcept
	{
		Transform* parentTransform;

		if (TryFindParentOfTypeRecursive<Transform>(parentTransform))
			return parentTransform->TransformRotation(GetLocalRotation());
		else
			return GetLocalRotation();
	}
	void Transform::SetRotation(in<float> rotation) noexcept
	{
		Transform* parentTransform;

		if (TryFindParentOfTypeRecursive<Transform>(parentTransform))
			SetLocalRotation(parentTransform->InverseTransformRotation(rotation));
		else
			SetLocalRotation(rotation);
	}

	void Transform::Translate(in<Vector2F> deltaPosition) noexcept
	{ SetLocalPosition(GetLocalPosition() + InverseTransformDirection(deltaPosition)); }

	void Transform::TranslateLocal(in<Vector2F> deltaPosition) noexcept
	{ SetLocalPosition(GetLocalPosition() + deltaPosition); }

	void Transform::Rotate(in<float> deltaRotation) noexcept
	{ SetLocalRotation(GetLocalRotation() + deltaRotation); }

	PoseF Transform::TransformPose(in<PoseF> pose) const noexcept 
	{ return GetPose().TransformPose(pose); }

	Vector2F Transform::TransformPoint(in<Vector2F> point) const noexcept 
	{ return GetPose().TransformPoint(point); }

	Vector2F Transform::TransformDirection(in<Vector2F> direction) const noexcept 
	{ return GetPose().TransformDirection(direction); }

	float Transform::TransformRotation(in<float> rotation) const noexcept 
	{ return GetPose().TransformRotation(rotation); }

	PoseF Transform::InverseTransformPose(in<PoseF> pose) const noexcept 
	{ return GetPose().InverseTransformPose(pose); }

	Vector2F Transform::InverseTransformPoint(in<Vector2F> point) const noexcept 
	{ return GetPose().InverseTransformPoint(point); }

	Vector2F Transform::InverseTransformDirection(in<Vector2F> direction) const noexcept 
	{ return GetPose().InverseTransformDirection(direction); }

	float Transform::InverseTransformRotation(in<float> rotation) const noexcept 
	{ return GetPose().InverseTransformRotation(rotation); }
}