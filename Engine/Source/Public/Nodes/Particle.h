#pragma once
#include "GamePhysics.h"
#include "Nodes/Transform.h"
#include "Nodes/Behaviour.h"

class Particle : public Transform, public Behaviour
{
	friend Physics;

private:
	Vector2F _velocity;
	float _angularVelocity;
	Vector2F _localCenterOfMass;

public:
	virtual ~Particle() noexcept override;

	virtual void OnEnable() noexcept override;
	virtual void OnDisable() noexcept override;

protected:
	Particle(const std::string& name = "", bool enabled = true) noexcept;
};