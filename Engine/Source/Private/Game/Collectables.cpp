#include "Collectables.h"
#include "GameStateLevel.h"

void Collectable::Setup(ref<GameStateLevel> level)
{
	animator->SetAnimation(level.collectableAnimation);
	animator->Play((size_t)(rand() % 2));
	animator->animationSpeed = (1.0f + (((rand() % 200) - 100) * 0.005f));
	SetVelocity(bae::Vector2F(((rand() % 200) - 100), ((rand() % 200) - 100)));
	SetDrag(0.05f);
}

void Collectable::Create(in<const char*> name)
{
	PhysicsBody::Create(name);

	animator = AddChild<bae::Animator>("Animator");
	sprite = animator->AddChild<bae::Sprite>("Sprite");
	collider = AddChild<bae::ColliderAxisBox>("Collider");
	collider->isTrigger = true;
	collider->collisionLayers = 0b0010;
}

void Collectable::Destroy()
{
	PhysicsBody::Destroy();
}

void PointsCollectable::Setup(ref<GameStateLevel> level)
{
	Collectable::Setup(level);

	sprite->color = 0xFFFFFFFF;
	sprite->scale = bae::Vector2F(0.3f, 0.3f);
	collider->size = bae::Vector2F(10.0f, 10.0f);
}

void PointsCollectable::Collect(ref<GameStateLevel> level)
{
	level.score += 50;
}

void HealthCollectable::Setup(ref<GameStateLevel> level)
{
	Collectable::Setup(level);

	sprite->color = 0xFF3333FF;
	sprite->scale = bae::Vector2F(0.5f, 0.5f);
	collider->size = bae::Vector2F(10.0f, 10.0f);
}

void HealthCollectable::Collect(ref<GameStateLevel> level)
{
	level.player->healthBar->currentHealth += 25.0f;
	if (level.player->healthBar->currentHealth > level.player->healthBar->maxHealth)
		level.player->healthBar->currentHealth = level.player->healthBar->maxHealth;

	level.player->healthBar->Update();
}

void FireRateCollectable::Setup(ref<GameStateLevel> level)
{
	Collectable::Setup(level);

	sprite->color = 0x33FF33FF;
	sprite->scale = bae::Vector2F(0.6f, 0.6f);
	collider->size = bae::Vector2F(10.0f, 10.0f);
}

void FireRateCollectable::Collect(ref<GameStateLevel> level)
{
	level.playerFireRate += 1.0f;
}

void SpeedCollectable::Setup(ref<GameStateLevel> level)
{
	Collectable::Setup(level);

	sprite->color = 0x3333FFFF;
	sprite->scale = bae::Vector2F(0.6f, 0.6f);
	collider->size = bae::Vector2F(10.0f, 10.0f);
}

void SpeedCollectable::Collect(ref<GameStateLevel> level)
{
	level.player->speed += 5.0f;
}