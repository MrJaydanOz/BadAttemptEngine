#include "Nodes/Transform.h"
#include <algorithm>
#include "Def.h"

static bool tryGetNextParentTransform(const Node* node, Transform*& transform)
{
	Node* parent = node->GetParent();

	while (parent != nullptr)
	{
		Transform* parentTransform = dynamic_cast<Transform*>(parent);
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

Transform::~Transform()
{
	delete _cachedWorldPose;

	Node::~Node();
}

PoseF Transform::GetLocalPose() const { return _pose; }

void Transform::SetLocalPose(const PoseF& pose) { _pose = pose; _hasModified = true; }

PoseF Transform::GetPose() const
{
	if (_cachedWorldPose != nullptr)
		return *_cachedWorldPose;

	Transform* parentTransform;

	if (tryGetNextParentTransform(this, parentTransform))
		return parentTransform->TransformPose(GetLocalPose());
	else
		return GetLocalPose();
}

void Transform::SetPose(const PoseF& pose)
{
	Transform* parentTransform;

	if (tryGetNextParentTransform(this, parentTransform))
		SetLocalPose(parentTransform->InverseTransformPose(pose));
	else
		SetLocalPose(pose);

}

Vector2F Transform::GetLocalPosition() const { return _pose.position; }

void Transform::SetLocalPosition(const Vector2F& position) { _pose.position = position; _hasModified = true; }

Vector2F Transform::GetPosition() const
{
	if (_cachedWorldPose != nullptr)
		return _cachedWorldPose->position;

	Transform* parentTransform;

	if (tryGetNextParentTransform(this, parentTransform))
		return parentTransform->TransformPoint(GetLocalPosition());
	else
		return GetLocalPosition();
}

void Transform::SetPosition(const Vector2F& position)
{
	Transform* parentTransform;

	if (tryGetNextParentTransform(this, parentTransform))
		SetLocalPosition(parentTransform->InverseTransformPoint(position));
	else
		SetLocalPosition(position);
}

float Transform::GetLocalRotation() const { return _pose.rotation; }

void Transform::SetLocalRotation(const float& rotation) { _pose.rotation = rotation; _hasModified = true; }

float Transform::GetRotation() const
{
	if (_cachedWorldPose != nullptr)
		return _cachedWorldPose->rotation;

	Transform* parentTransform;

	if (tryGetNextParentTransform(this, parentTransform))
		return parentTransform->TransformRotation(GetLocalRotation());
	else
		return GetLocalRotation();
}

void Transform::SetRotation(const float& rotation)
{
	Transform* parentTransform;

	if (tryGetNextParentTransform(this, parentTransform))
		SetLocalRotation(parentTransform->InverseTransformRotation(rotation));
	else
		SetLocalRotation(rotation);
}

void Transform::CacheWorldPose()
{
	if (_cachedWorldPose == nullptr)
		_cachedWorldPose = new PoseF(GetPose());
	else
		*_cachedWorldPose = GetPose();
}

void Transform::ClearWorldPoseCache(bool includeChildren)
{
	auto children = GetChildren();

	if (includeChildren && children != nullptr)
		std::for_each(children->begin(), children->end(), [](Node* child)
		{
			Transform* childTransform = dynamic_cast<Transform*>(child);
			if (childTransform)
				childTransform->ClearWorldPoseCache(true);
		});

	delete _cachedWorldPose;
	_cachedWorldPose = nullptr;
}

PoseF Transform::TransformPose(const PoseF& pose) const { GetPose().TransformPose(pose); }

Vector2F Transform::TransformPoint(const Vector2F& point) const { GetPose().TransformPoint(point); }

Vector2F Transform::TransformDirection(const Vector2F& direction) const { GetPose().TransformDirection(direction); }

float Transform::TransformRotation(const float& rotation) const { GetPose().TransformRotation(rotation); }

PoseF Transform::InverseTransformPose(const PoseF& pose) const { GetPose().InverseTransformPose(pose); }

Vector2F Transform::InverseTransformPoint(const Vector2F& point) const { GetPose().InverseTransformPoint(point); }

Vector2F Transform::InverseTransformDirection(const Vector2F& direction) const { GetPose().InverseTransformDirection(direction); }

float Transform::InverseTransformRotation(const float& rotation) const { GetPose().InverseTransformRotation(rotation); }
