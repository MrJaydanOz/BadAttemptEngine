#include "Projectiles.h"
#include "BAE/BAE_Game.h"

void BasicBullet::Create(in<const char*> name)
{
	PhysicsBody::Create(name);

	animator = AddChild<bae::Animator>("Animator");
	sprite = animator->AddChild<bae::Sprite>("Sprite");
	collider = AddChild<bae::ColliderAxisBox>("Collider");
	collider->isTrigger = true;
}

void BasicBullet::Destroy()
{
	PhysicsBody::Destroy();
}

void BasicBullet::Update() noexcept
{
	lifeTime -= bae::Game::GetTime()->DeltaTime();
}