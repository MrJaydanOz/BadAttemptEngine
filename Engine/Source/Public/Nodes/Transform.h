#pragma once
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
	~Transform();

	PoseF GetLocalPose() const;
	void SetLocalPose(const PoseF& pose);

	PoseF GetPose() const;
	void SetPose(const PoseF& pose);

	Vector2F GetLocalPosition() const;
	void SetLocalPosition(const Vector2F& position);

	Vector2F GetPosition() const;
	void SetPosition(const Vector2F& position);

	float GetLocalRotation() const;
	void SetLocalRotation(const float& rotation);

	float GetRotation() const;
	void SetRotation(const float& rotation);

	void CacheWorldPose();
	void ClearWorldPoseCache(bool includeChildren = true);

	PoseF TransformPose(const PoseF& pose) const;

	Vector2F TransformPoint(const Vector2F& point) const;

	Vector2F TransformDirection(const Vector2F& direction) const;

	float TransformRotation(const float& rotation) const;

	PoseF InverseTransformPose(const PoseF& pose) const;

	Vector2F InverseTransformPoint(const Vector2F& point) const;

	Vector2F InverseTransformDirection(const Vector2F& direction) const;

	float InverseTransformRotation(const float& rotation) const;
};