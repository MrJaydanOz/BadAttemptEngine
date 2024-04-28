#pragma once
#include "BAE/BAE_Math.h"
#include "BAE/Nodes/BAE_PhysicsBody.h"
#include "BAE/Nodes/BAE_ColliderAxisBox.h"
#include "BAE/Nodes/BAE_Sprite.h"
#include "BAE/Nodes/BAE_Animator.h"
#include "BAE/Math/BAE_Color.h"
#include "BAE/BAE_Game.h"

class GameStateLevel;

class Collectable : public bae::PhysicsBody
{
	NODE_BEGIN;

public:
	bae::Animator* animator = nullptr;
	bae::Sprite* sprite = nullptr;
	bae::ColliderAxisBox* collider = nullptr;

public:
	virtual void Setup(ref<GameStateLevel> level);

	virtual void Collect(ref<GameStateLevel> level) = 0;

protected:
	Collectable(in<Node*> parent) noexcept :
		PhysicsBody::PhysicsBody(parent) { }
	virtual ~Collectable() noexcept override { }

	virtual void Create(in<const char*> name) override;

	virtual void Destroy() override;
};

class PointsCollectable : public Collectable
{
	NODE_BEGIN;

public:
	virtual void Setup(ref<GameStateLevel> level) override;

	virtual void Collect(ref<GameStateLevel> level) override;

protected:
	PointsCollectable(in<Node*> parent) noexcept :
		Collectable::Collectable(parent) { }
	virtual ~PointsCollectable() noexcept override { }
};

class HealthCollectable : public Collectable
{
	NODE_BEGIN;

public:
	virtual void Setup(ref<GameStateLevel> level) override;

	virtual void Collect(ref<GameStateLevel> level) override;

protected:
	HealthCollectable(in<Node*> parent) noexcept :
		Collectable::Collectable(parent) { }
	virtual ~HealthCollectable() noexcept override { }
};

class FireRateCollectable : public Collectable
{
	NODE_BEGIN;

public:
	virtual void Setup(ref<GameStateLevel> level) override;

	virtual void Collect(ref<GameStateLevel> level) override;

protected:
	FireRateCollectable(in<Node*> parent) noexcept :
		Collectable::Collectable(parent) { }
	virtual ~FireRateCollectable() noexcept override { }
};

class SpeedCollectable : public Collectable
{
	NODE_BEGIN;

public:
	virtual void Setup(ref<GameStateLevel> level) override;

	virtual void Collect(ref<GameStateLevel> level) override;

protected:
	SpeedCollectable(in<Node*> parent) noexcept :
		Collectable::Collectable(parent) { }
	virtual ~SpeedCollectable() noexcept override { }
};