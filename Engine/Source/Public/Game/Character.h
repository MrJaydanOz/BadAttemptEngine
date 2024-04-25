#pragma once
#include "BAE/BAE_Math.h"
#include "BAE/Nodes/BAE_PhysicsBody.h"
#include "BAE/Nodes/BAE_ColliderAxisBox.h"
#include "BAE/Nodes/BAE_Sprite.h"
#include "BAE/Nodes/BAE_Animator.h"
#include "BAE/Math/BAE_Color.h"
#include "HealthBar.h"

class Character : public bae::PhysicsBody
{
	NODE_BEGIN;

public:
	float speed;
	float acceleration;
	bae::Animator* animator;
	bae::Sprite* sprite;
	bae::ColliderAxisBox* collider;
	HealthBar* healthBar;

private:
	int _lastAnimationDirection;
	bool _lastIsWalking;
	float _hurtAnimationTimer;

public:
	void UpdateAnimation();

	void Damage(in<float> amount);

	void MoveWithInput(in<bae::Vector2F> input);

protected:
	Character(in<Node*> parent) noexcept : PhysicsBody::PhysicsBody(parent),
		speed(0.0f),
		acceleration(0.0f),
		animator(nullptr),
		sprite(nullptr),
		collider(nullptr),
		healthBar(nullptr),
		_lastAnimationDirection(0),
		_lastIsWalking(false),
		_hurtAnimationTimer(1.0f) { }
	virtual ~Character() noexcept override { }

	virtual void Create(in<const char*> name = "") override;

	virtual void Destroy() override;
};

class PlayerCharacter : public Character
{

};