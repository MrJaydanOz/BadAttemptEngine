#pragma once
#include <string>
#include "Nodes/Node.h"
#include "Math/PoseT.h"
#include "Math/VectorT.h"

class Transform : public Node
{
private:
	PoseF _pose;
	PoseF* _cachedWorldPose;
	bool _hasModified;

public:
	Transform(const std::string& name = "") noexcept;
	virtual ~Transform() noexcept override;

	PoseF GetLocalPose() const noexcept;
	void SetLocalPose(const PoseF& pose) noexcept;

	PoseF GetPose() const noexcept;
	void SetPose(const PoseF& pose) noexcept;

	Vector2F GetLocalPosition() const noexcept;
	void SetLocalPosition(const Vector2F& position) noexcept;

	Vector2F GetPosition() const noexcept;
	void SetPosition(const Vector2F& position) noexcept;

	float GetLocalRotation() const noexcept;
	void SetLocalRotation(const float& rotation) noexcept;

	float GetRotation() const noexcept;
	void SetRotation(const float& rotation) noexcept;

	void CacheWorldPose() noexcept;
	void ClearWorldPoseCache(bool includeChildren = true) noexcept;

	PoseF TransformPose(const PoseF& pose) const noexcept;

	Vector2F TransformPoint(const Vector2F& point) const noexcept;

	Vector2F TransformDirection(const Vector2F& direction) const noexcept;

	float TransformRotation(const float& rotation) const noexcept;

	PoseF InverseTransformPose(const PoseF& pose) const noexcept;

	Vector2F InverseTransformPoint(const Vector2F& point) const noexcept;

	Vector2F InverseTransformDirection(const Vector2F& direction) const noexcept;

	float InverseTransformRotation(const float& rotation) const noexcept;

private:
	static bool TryGetNextParentTransform(const Node* node, const Transform*& transform) noexcept;
};