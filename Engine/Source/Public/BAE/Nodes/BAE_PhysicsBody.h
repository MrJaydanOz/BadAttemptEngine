#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_PhysicsBody.h"))
#endif
#include "Nodes/BAE_Transform.h"

namespace bae
{
	class Scene;
	class Physics;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class PhysicsBody))
#endif
	class PhysicsBody : public Transform
	{
		NODE_BEGIN;
		friend class Physics;

	private:
		Vector2F _velocity;
		float _angularVelocity;
		Vector2F _localCenterOfMass;
		float _mass;

	public:
		virtual ~PhysicsBody() noexcept override;

		_NODISCARD Vector2F GetVelocity() const noexcept;
		void SetVelocity(in<Vector2F> velocity) noexcept;

		void AddAcceleration(in<Vector2F> acceleration) noexcept;

		_NODISCARD float GetAngularVelocity() const noexcept;
		void SetAngularVelocity(in<float> velocity) noexcept;

		_NODISCARD Vector2F GetLocalCenterOfMass() const noexcept;
		void SetLocalCenterOfMass(in<Vector2F> velocity) noexcept;

		_NODISCARD float GetMass() const noexcept;
		void SetMass(in<float> mass) noexcept;

	protected:
		PhysicsBody(in<std::string> name = "") noexcept;

		virtual void OnLoad() noexcept override;

		virtual void OnParentChanged() noexcept override;

		virtual void OnDestroy() noexcept override;
	};
}