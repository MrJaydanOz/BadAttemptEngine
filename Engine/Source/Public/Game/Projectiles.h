#pragma once
#include "BAE/Nodes/BAE_PhysicsBody.h"
#include "BAE/Nodes/BAE_ColliderAxisBox.h"
#include "BAE/Nodes/BAE_Animator.h"
#include "BAE/Nodes/BAE_Sprite.h"

class BasicBullet : public bae::PhysicsBody
{
	NODE_BEGIN;

public:
	float damage = 0.0f;
	bae::Animator* animator = nullptr;
	bae::Sprite* sprite = nullptr;
	bae::ColliderAxisBox* collider = nullptr;
	float lifeTime = 10.0f;

protected:
	BasicBullet(in<Node*> parent) noexcept :
		bae::PhysicsBody::PhysicsBody(parent) { }
	virtual ~BasicBullet() noexcept override { }

	void Update() noexcept;

	virtual void Create(in<const char*> name = "") override;

	virtual void Destroy() override;
};