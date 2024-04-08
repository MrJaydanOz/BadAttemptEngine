#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Transform.h"))
#endif
#include <string.h>
#include "Nodes/BAE_Node.h"
#include "Math/BAE_PoseT.h"
#include "Math/BAE_VectorT.h"

namespace bae
{
	class Scene;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Transform))
#endif
	class Transform : public Node
	{
		NODE_BEGIN;

	private:
		PoseF _pose;
		PoseF* _cachedWorldPose;
		bool _hasModified;

	public:
		virtual ~Transform() noexcept override;

		PoseF GetLocalPose() const noexcept;
		void SetLocalPose(in<PoseF> pose) noexcept;

		PoseF GetPose() const noexcept;
		void SetPose(in<PoseF> pose) noexcept;

		Vector2F GetLocalPosition() const noexcept;
		void SetLocalPosition(in<Vector2F> position) noexcept;

		Vector2F GetPosition() const noexcept;
		void SetPosition(in<Vector2F> position) noexcept;

		float GetLocalRotation() const noexcept;
		void SetLocalRotation(in<float> rotation) noexcept;

		float GetRotation() const noexcept;
		void SetRotation(in<float> rotation) noexcept;

		void Translate(in<Vector2F> deltaPosition) noexcept;
		void TranslateLocal(in<Vector2F> deltaPosition) noexcept;

		void Rotate(in<float> deltaRotation) noexcept;

		void CacheWorldPose(in<bool> recalculateIfAlreadyCached = false) noexcept;
		void ClearWorldPoseCache(in<bool> includeChildren = true) noexcept;

		PoseF TransformPose(in<PoseF> pose) const noexcept;

		Vector2F TransformPoint(in<Vector2F> point) const noexcept;

		Vector2F TransformDirection(in<Vector2F> direction) const noexcept;

		float TransformRotation(in<float> rotation) const noexcept;

		PoseF InverseTransformPose(in<PoseF> pose) const noexcept;

		Vector2F InverseTransformPoint(in<Vector2F> point) const noexcept;

		Vector2F InverseTransformDirection(in<Vector2F> direction) const noexcept;

		float InverseTransformRotation(in<float> rotation) const noexcept;

	protected:
		Transform(in<std::string> name = "") noexcept;
	};
}