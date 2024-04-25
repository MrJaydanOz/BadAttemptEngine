#include "Character.h"

void Character::UpdateAnimation()
{
	if (_hurtAnimationTimer >= 0.0f)
	{
		const float notRed = bae::Min(1.0f, _hurtAnimationTimer);

		sprite->color = (bae::Color)bae::ColorF(1.0f, notRed, notRed);
		sprite->offset.rotation = 15.0f / ((20.0f * _hurtAnimationTimer) + 1);

		_hurtAnimationTimer += bae::Game::GetTime()->DeltaTime();
	}

	bae::Vector2F velocity = GetVelocity();

	if (velocity.SqrMagnitude() > 1.0f)
	{
		float angle = bae::ATan2(velocity.y, velocity.x) + (DEG_TO_RAD * 180.0f);
		int direction = bae::Mod(bae::RoundI(angle * RAD_TO_TURN * 16.0f), 16);

		if (!_lastIsWalking || _lastAnimationDirection != direction)
		{
			_lastAnimationDirection = direction;

			animator->Play((size_t)_lastAnimationDirection + 16, !_lastIsWalking);

			_lastIsWalking = true;
		}
	}
	else
	{
		if (_lastIsWalking)
		{
			animator->Play((size_t)_lastAnimationDirection, _lastIsWalking);

			_lastIsWalking = false;
		}
	}
}

void Character::Damage(in<float> amount)
{
	_hurtAnimationTimer = 0.0f;
	healthBar->currentHealth -= amount;
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