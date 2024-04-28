#pragma once
#include "BAE/BAE_Math.h"
#include "BAE/Nodes/BAE_PhysicsBody.h"
#include "BAE/Nodes/BAE_ColliderAxisBox.h"
#include "BAE/Nodes/BAE_Sprite.h"
#include "BAE/Nodes/BAE_Animator.h"
#include "BAE/Math/BAE_Color.h"
#include "BAE/BAE_Game.h"
#include "HealthBar.h"

class GameStateLevel;

class Character : public bae::PhysicsBody
{
	NODE_BEGIN;

public:
	float speed = 0.0f;
	float acceleration = 0.0f;
	bae::Animator* animator = nullptr;
	bae::Sprite* sprite = nullptr;
	bae::Sprite* shadow = nullptr;
	bae::ColliderAxisBox* collider = nullptr;
	HealthBar* healthBar = nullptr;

protected:
	bool lastIsWalking = false;
	bool lastIsShooting = false;
	int lastLookDirection = -1;
	float hurtAnimationTimer = -1.0f;

public:
	void UpdateAnimation(in<bae::Vector2F> lookDirection, bool shoot);

	void Damage(in<float> amount);

	void MoveWithInput(in<bae::Vector2F> input);

	virtual void Setup(ref<GameStateLevel> level) { }

	static int GetDirectionAnimationIndex(in<bae::Vector2F> direction);

protected:
	Character(in<Node*> parent) noexcept : 
		PhysicsBody::PhysicsBody(parent) { }
	virtual ~Character() noexcept override { }

	virtual void Create(in<const char*> name) override;

	virtual void Destroy() override;
};

class PlayerCharacter : public Character
{
	NODE_BEGIN;

public:
	virtual void Setup(ref<GameStateLevel> level) override;

protected:
	PlayerCharacter(in<Node*> parent) noexcept : 
		Character::Character(parent) { }
	virtual ~PlayerCharacter() noexcept override { }

	virtual void Create(in<const char*> name) override;

	virtual void Destroy() override;
};

class EnemyCharacter : public Character
{
	NODE_BEGIN;

public:
	virtual void Tick(ref<GameStateLevel> level) noexcept;

	virtual void Die(ref<GameStateLevel> level) noexcept = 0;

protected:
	EnemyCharacter(in<Node*> parent) noexcept :
		Character::Character(parent) { }
	virtual ~EnemyCharacter() noexcept override { }

	virtual void Create(in<const char*> name) override;

	virtual void Destroy() override;
};

class RollingEnemy : public EnemyCharacter
{
	NODE_BEGIN;

public:
	float blinkTimer = 0.0f;

public:
	virtual void Setup(ref<GameStateLevel> level) override;

	virtual void Tick(ref<GameStateLevel> level) noexcept override;

	virtual void Die(ref<GameStateLevel> level) noexcept;

protected:
	RollingEnemy(in<Node*> parent) noexcept :
		EnemyCharacter::EnemyCharacter(parent) { }
	virtual ~RollingEnemy() noexcept override { }

	virtual void Create(in<const char*> name) override;

	virtual void Destroy() override;
};

class BasicEnemy : public EnemyCharacter
{
	NODE_BEGIN;

public:
	float shootTimer = 0.0f;
	float moveTimer = 0.0f;
	bae::Vector2F moveTarget = bae::Vector2F();

public:
	virtual void Setup(ref<GameStateLevel> level) override;

	virtual void Tick(ref<GameStateLevel> level) noexcept override;

	virtual void Die(ref<GameStateLevel> level) noexcept;

protected:
	BasicEnemy(in<Node*> parent) noexcept :
		EnemyCharacter::EnemyCharacter(parent) { }
	virtual ~BasicEnemy() noexcept override { }

	virtual void Create(in<const char*> name) override;

	virtual void Destroy() override;
};

class ShotgunEnemy : public EnemyCharacter
{
	NODE_BEGIN;

public:
	float shootTimer = 0.0f;
	float moveTimer = 0.0f;
	bae::Vector2F moveTarget = bae::Vector2F();

public:
	virtual void Setup(ref<GameStateLevel> level) override;

	virtual void Tick(ref<GameStateLevel> level) noexcept override;

	virtual void Die(ref<GameStateLevel> level) noexcept;

protected:
	ShotgunEnemy(in<Node*> parent) noexcept :
		EnemyCharacter::EnemyCharacter(parent) { }
	virtual ~ShotgunEnemy() noexcept override { }

	virtual void Create(in<const char*> name) override;

	virtual void Destroy() override;
};