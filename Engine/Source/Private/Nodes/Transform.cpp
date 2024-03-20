#include "Nodes/Transform.h"
#include <algorithm>
#include <string>
#include "Def.h"
#include "Nodes/Node.h"
#include "Math/PoseT.h"

Transform::Transform(const std::string& name) noexcept : Node(name),
	_pose(Vector2F(0.0f, 0.0f), 0.0f),
	_cachedWorldPose(nullptr),
	_hasModified(false)
{ }

Transform::~Transform() noexcept
{
	delete _cachedWorldPose;

	Node::~Node();
}

PoseF Transform::GetLocalPose() const noexcept { return _pose; }

void Transform::SetLocalPose(const PoseF& pose) noexcept { _pose = pose; _hasModified = true; }

PoseF Transform::GetPose() const noexcept
{
	if (_cachedWorldPose != nullptr)
		return *_cachedWorldPose;

	const Transform* parentTransform;

	if (TryGetNextParentTransform(this, parentTransform))
		return parentTransform->TransformPose(GetLocalPose());
	else
		return GetLocalPose();
}

void Transform::SetPose(const PoseF& pose) noexcept
{
	const Transform* parentTransform;

	if (TryGetNextParentTransform(this, parentTransform))
		SetLocalPose(parentTransform->InverseTransformPose(pose));
	else
		SetLocalPose(pose);
}

Vector2F Transform::GetLocalPosition() const noexcept { return _pose.position; }

void Transform::SetLocalPosition(const Vector2F& position) noexcept { _pose.position = position; _hasModified = true; }

Vector2F Transform::GetPosition() const noexcept
{
	if (_cachedWorldPose != nullptr)
		return _cachedWorldPose->position;

	const Transform* parentTransform;

	if (TryGetNextParentTransform(this, parentTransform))
		return parentTransform->TransformPoint(GetLocalPosition());
	else
		return GetLocalPosition();
}

void Transform::SetPosition(const Vector2F& position) noexcept
{
	const Transform* parentTransform;

	if (TryGetNextParentTransform(this, parentTransform))
		SetLocalPosition(parentTransform->InverseTransformPoint(position));
	else
		SetLocalPosition(position);
}

float Transform::GetLocalRotation() const noexcept { return _pose.rotation; }

void Transform::SetLocalRotation(const float& rotation) noexcept { _pose.rotation = rotation; _hasModified = true; }

float Transform::GetRotation() const noexcept
{
	if (_cachedWorldPose != nullptr)
		return _cachedWorldPose->rotation;

	const Transform* parentTransform;

	if (TryGetNextParentTransform(this, parentTransform))
		return parentTransform->TransformRotation(GetLocalRotation());
	else
		return GetLocalRotation();
}

void Transform::SetRotation(const float& rotation) noexcept
{
	const Transform* parentTransform;

	if (TryGetNextParentTransform(this, parentTransform))
		SetLocalRotation(parentTransform->InverseTransformRotation(rotation));
	else
		SetLocalRotation(rotation);
}

void Transform::CacheWorldPose(bool recalculateIfAlreadyCached = false) noexcept
{
	if (_cachedWorldPose == nullptr)
		_cachedWorldPose = new PoseF(GetPose());
	else if (recalculateIfAlreadyCached)
		*_cachedWorldPose = GetPose();
}

void Transform::ClearWorldPoseCache(bool includeChildren) noexcept
{
	if (includeChildren)
	{
		auto children = GetChildren();

		if (children != nullptr)
			for (Node* child : *children)
			{
				Transform* childTransform = dynamic_cast<Transform*>(child);
				if (childTransform)
					childTransform->ClearWorldPoseCache(true);
			}
	}

	delete _cachedWorldPose;
	_cachedWorldPose = nullptr;
}

PoseF Transform::TransformPose(const PoseF& pose) const noexcept { return GetPose().TransformPose(pose); }

Vector2F Transform::TransformPoint(const Vector2F& point) const noexcept { return GetPose().TransformPoint(point); }

Vector2F Transform::TransformDirection(const Vector2F& direction) const noexcept { return GetPose().TransformDirection(direction); }

float Transform::TransformRotation(const float& rotation) const noexcept { return GetPose().TransformRotation(rotation); }

PoseF Transform::InverseTransformPose(const PoseF& pose) const noexcept { return GetPose().InverseTransformPose(pose); }

Vector2F Transform::InverseTransformPoint(const Vector2F& point) const noexcept { return GetPose().InverseTransformPoint(point); }

Vector2F Transform::InverseTransformDirection(const Vector2F& direction) const noexcept { return GetPose().InverseTransformDirection(direction); }

float Transform::InverseTransformRotation(const float& rotation) const noexcept { return GetPose().InverseTransformRotation(rotation); }

bool Transform::TryGetNextParentTransform(const Node* node, const Transform*& transform) noexcept
{
	const Node* parent = node->GetParent();

	while (parent != nullptr)
	{
		const Transform* parentTransform = dynamic_cast<const Transform*>(parent);
		if (parentTransform)
		{
			transform = parentTransform;
			return true;
		}

		parent = parent->GetParent();
	}

	transform = nullptr;
	return false;
}
