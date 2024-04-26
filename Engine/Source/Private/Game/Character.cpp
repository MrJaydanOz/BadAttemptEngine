#include "Character.h"

void Character::UpdateAnimation(in<bae::Vector2F> lookDirection)
{
	if (_hurtAnimationTimer >= 0.0f)
	{
		const float notRed = bae::Min(1.0f, _hurtAnimationTimer);

		sprite->color = (bae::Color)bae::ColorF(1.0f, notRed, notRed);
		sprite->offset.rotation = 15.0f / ((20.0f * _hurtAnimationTimer) + 1);

		_hurtAnimationTimer += bae::Game::GetTime()->DeltaTime();
	}

	bae::Vector2F velocity = GetVelocity();

	bool isWalking = velocity.SqrMagnitude() > 1.0f;

	float angle = bae::ATan2(lookDirection.y, lookDirection.x) + (DEG_TO_RAD * 180.0f);
	int direction = bae::Mod(bae::RoundI(angle * RAD_TO_TURN * 16.0f), 16);

	animator->Play(isWalking 
		? ((size_t)direction + 16) 
		: (size_t)direction + 0,
		isWalking != _lastIsWalking);

	_lastIsWalking = isWalking;
}

void Character::Damage(in<float> amount)
{
	_hurtAnimationTimer = 0.0f;
	healthBar->currentHealth -= amount;
	healthBar->Update();
}

void Character::MoveWithInput(in<bae::Vector2F> input)
{
	bae::Vector2F scaledInput = input.SqrMagnitude() > 1.0f ? input.Normalized() : input;

	SetVelocity(bae::MoveTowards(GetVelocity(), scaledInput * speed, acceleration * bae::Game::GetTime()->DeltaTime()));
}

void Character::Create(in<const char*> name)
{
	PhysicsBody::Create(name);

	animator = AddChild<bae::Animator>("Animator");
	sprite = animator->AddChild<bae::Sprite>("Sprite");
	collider = AddChild<bae::ColliderAxisBox>("Collider");
	healthBar = AddChild<HealthBar>("HealthBar");
}

void Character::Destroy()
{ PhysicsBody::Destroy(); }

void PlayerCharacter::Create(in<const char*> name)
{
	Character::Create(name);

	healthBar->SetLocalPosition(bae::Vector2F(0.0f, 12.0f));
	healthBar->SetWidth(16.0f);
	healthBar->SetColor(0x0088FFFF);
}

void PlayerCharacter::Destroy()
{
	Character::Destroy();
}
