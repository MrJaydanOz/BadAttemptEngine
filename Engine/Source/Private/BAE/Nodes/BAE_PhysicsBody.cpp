#include "Nodes/BAE_PhysicsBody.h"
#include "Math/Func/BAE_Comparison.h"
#include "BAE_Game.h"

namespace bae
{
	PhysicsBody::PhysicsBody(in<Node*> parent) noexcept :
		Transform::Transform(parent),
		_velocity(0.0f, 0.0f),
		_angularVelocity(0.0f),
		_localCenterOfMass(0.0f, 0.0f),
		_mass(1.0f),
		_drag(0.0f) { }

	PhysicsBody::~PhysicsBody() noexcept { }

	void PhysicsBody::Create(in<const char*> name)
	{
		Transform::Create(name);
	}

	void PhysicsBody::Destroy()
	{
		Game::GetPhysics()->_RemovePhysicsBody(this);

		Transform::Destroy();
	}

	void PhysicsBody::OnParentChanged() noexcept
	{
		Transform::OnParentChanged();

		Game::GetPhysics()->_RemovePhysicsBody(this);
		Game::GetPhysics()->_AddPhysicsBody(this);
	}

	Vector2F PhysicsBody::GetVelocity() const noexcept
	{ return _velocity; }
	void PhysicsBody::SetVelocity(in<Vector2F> velocity) noexcept
	{ _velocity = velocity; }

	void PhysicsBody::AddAcceleration(in<Vector2F> acceleration) noexcept
	{ _velocity += acceleration * Game::GetTime()->GetPhysicsTimestep(); }

	float PhysicsBody::GetAngularVelocity() const noexcept
	{ return _angularVelocity; }
	void PhysicsBody::SetAngularVelocity(in<float> angularVelocity) noexcept
	{ _angularVelocity = angularVelocity; }

	Vector2F PhysicsBody::GetLocalCenterOfMass() const noexcept
	{ return _localCenterOfMass; }
	void PhysicsBody::SetLocalCenterOfMass(in<Vector2F> localCenterOfMass) noexcept
	{ _localCenterOfMass = localCenterOfMass; }

	float PhysicsBody::GetMass() const noexcept
	{ return _mass; }
	void PhysicsBody::SetMass(in<float> mass) noexcept
	{ _mass = mass; }

	float PhysicsBody::GetDrag() const noexcept
	{ return _drag; }
	void PhysicsBody::SetDrag(in<float> drag) noexcept
	{ _drag = Clamp(drag, 0.0f, 1.0f); }
}