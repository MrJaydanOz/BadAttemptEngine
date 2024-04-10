#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_PhysicsBody.h"))
#endif
#include "Nodes/BAE_Transform.h"

namespace bae
{
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
		float _drag;

	public:
		_NODISCARD Vector2F GetVelocity() const noexcept;
		void SetVelocity(in<Vector2F> velocity) noexcept;

		void AddAcceleration(in<Vector2F> acceleration) noexcept;

		_NODISCARD float GetAngularVelocity() const noexcept;
		void SetAngularVelocity(in<float> velocity) noexcept;

		_NODISCARD Vector2F GetLocalCenterOfMass() const noexcept;
		void SetLocalCenterOfMass(in<Vector2F> velocity) noexcept;

		_NODISCARD float GetMass() const noexcept;
		void SetMass(in<float> mass) noexcept;

		_NODISCARD float GetDrag() const noexcept;
		void SetDrag(in<float> drag) noexcept;

	protected:
		PhysicsBody(in<Node*> parent) noexcept;
		virtual ~PhysicsBody() noexcept override;
		virtual void Create(in<const char*> name = "") override;
		virtual void Destroy() override;

		virtual void OnParentChanged() noexcept override;
	};
}