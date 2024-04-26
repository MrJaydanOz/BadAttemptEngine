#pragma once
#include "BAE/BAE_Math.h"
#include "BAE/Nodes/BAE_PhysicsBody.h"
#include "BAE/Nodes/BAE_ColliderAxisBox.h"
#include "BAE/Nodes/BAE_Sprite.h"
#include "BAE/Nodes/BAE_Animator.h"
#include "BAE/Math/BAE_Color.h"
#include "BAE/BAE_Game.h"
#include "HealthBar.h"

class Character : public bae::PhysicsBody
{
	NODE_BEGIN;

public:
	float speed = 0.0f;
	float acceleration = 0.0f;
	bae::Animator* animator = nullptr;
	bae::Sprite* sprite = nullptr;
	bae::ColliderAxisBox* collider = nullptr;
	HealthBar* healthBar = nullptr;

private:
	bool _lastIsWalking = false;
	bool _lastIsShooting = false;
	int _lastLookDirection = -1;
	float _hurtAnimationTimer = 1.0f;

public:
	void UpdateAnimation(in<bae::Vector2F> lookDirection, bool shoot);

	void Damage(in<float> amount);

	void MoveWithInput(in<bae::Vector2F> input);

protected:
	Character(in<Node*> parent) noexcept : 
		PhysicsBody::PhysicsBody(parent) { }
	virtual ~Character() noexcept override { }

	virtual void Create(in<const char*> name = "") override;

	virtual void Destroy() override;
};

class PlayerCharacter : public Character
{
	NODE_BEGIN;

	PlayerCharacter(in<Node*> parent) noexcept : 
		Character::Character(parent) { }
	virtual ~PlayerCharacter() noexcept override { }

	virtual void Create(in<const char*> name = "") override;

	virtual void Destroy() override;
};