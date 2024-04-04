#include "Nodes/Transform.h"
#include <algorithm>
#include <string>
#include "Def.h"
#include "Nodes/Node.h"
#include "Math/PoseT.h"

namespace bae
{
	Transform::Transform(in<std::string> name) noexcept : Node(name),
		_pose(Vector2F(0.0f), 0.0f),
		_cachedWorldPose(nullptr),
		_hasModified(false)
	{ }

	Transform::~Transform() noexcept
	{
		delete _cachedWorldPose;

		Node::~Node();
	}

	PoseF Transform::GetLocalPose() const noexcept { return _pose; }

	void Transform::SetLocalPose(in<PoseF> pose) noexcept { _pose = pose; _hasModified = true; }

	PoseF Transform::GetPose() const noexcept
	{
		if (_cachedWorldPose != nullptr)
			return *_cachedWorldPose;

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
		if (_cachedWorldPose != nullptr)
			return _cachedWorldPose->position;

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
		if (_cachedWorldPose != nullptr)
			return _cachedWorldPose->rotation;

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

	void Transform::CacheWorldPose(in<bool> recalculateIfAlreadyCached) noexcept
	{
		if (_cachedWorldPose == nullptr)
			_cachedWorldPose = new PoseF(GetPose());
		else if (recalculateIfAlreadyCached)
			*_cachedWorldPose = GetPose();
	}

	void Transform::ClearWorldPoseCache(in<bool> includeChildren) noexcept
	{
		if (includeChildren)
		{
			auto children = GetChildren();

			for (Node* child : children)
			{
				Transform* childTransform = dynamic_cast<Transform*>(child);
				if (childTransform)
					childTransform->ClearWorldPoseCache(true);
			}
		}

		delete _cachedWorldPose;
		_cachedWorldPose = nullptr;
	}

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