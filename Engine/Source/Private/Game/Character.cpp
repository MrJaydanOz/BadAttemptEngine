#include "Character.h"
#include "GameStateLevel.h"

void Character::UpdateAnimation(in<bae::Vector2F> lookDirection, bool shoot)
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

	int direction = GetDirectionAnimationIndex(lookDirection);

	if (shoot)
	{
		animator->Play((size_t)direction + 32, true);

		_lastIsShooting = true;
	}
	else
	{
		auto currentState = animator->GetCurrentState();
		bool isShooting = currentState != nullptr && currentState->GetKey().starts_with("shoot");

		if ((direction != _lastLookDirection) || (isWalking != _lastIsWalking) || (isShooting != _lastIsShooting))
			animator->Play(isShooting
				? (size_t)direction + 32
				: isWalking
				? (size_t)direction + 16
				: (size_t)direction + 0,
				(isWalking != _lastIsWalking) || (isShooting != _lastIsShooting));

		_lastIsShooting = isShooting;
	}

	_lastIsWalking = isWalking;
	_lastLookDirection = direction;
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

int Character::GetDirectionAnimationIndex(in<bae::Vector2F> direction)
{
	float angle = bae::ATan2(direction.y, direction.x) + (DEG_TO_RAD * 180.0f);
	return bae::Mod(bae::RoundI(angle * RAD_TO_TURN * 16.0f), 16);
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

void PlayerCharacter::Setup(in<GameStateLevel> level)
{
	speed = 50.0f;
	acceleration = 500.0f;
	animator->SetAnimation(level.playerAnimation);
	animator->Play("idle r0");
}

void PlayerCharacter::Create(in<const char*> name)
{
	Character::Create(name);

	collider->collisionLayers = 0b0010;
	collider->size = bae::Vector2F(20.0f, 20.0f);
	healthBar->SetLocalPosition(bae::Vector2F(0.0f, 12.0f));
	healthBar->SetWidth(16.0f);
	healthBar->SetColor(0x0088FFFF);
}

void PlayerCharacter::Destroy()
{
	Character::Destroy();
}

void EnemyCharacter::Create(in<const char*> name)
{
	Character::Create(name);

	healthBar->SetLocalPosition(bae::Vector2F(0.0f, 12.0f));
	healthBar->SetWidth(16.0f);
	healthBar->SetColor(0xFF0000FF);
}

void EnemyCharacter::Destroy()
{
	Character::Destroy();
}

void RollingEnemy::Setup(in<GameStateLevel> level)
{
	speed = 80.0f;
	acceleration = 40.0f;
	animator->SetAnimation(level.rollingEnemyAnimation);
	animator->Play("roll r0");
}

void RollingEnemy::Tick(in<GameStateLevel> level) noexcept
{
	MoveWithInput(level.player->GetPosition() - GetPosition());

	animator->animationSpeed = GetVelocity().Magnitude() / 60.0f;

	blinkTimer -= bae::Game::GetTime()->DeltaTime();

	if (blinkTimer <= 0.0f)
	{
		blinkTimer += 1.2f;
	}

	int direction = GetDirectionAnimationIndex(GetVelocity());

	animator->Play(blinkTimer < 0.2f
		? (size_t)direction + 16
		: (size_t)direction + 0,
		false);
}

void RollingEnemy::Create(in<const char*> name)
{
	EnemyCharacter::Create(name);

	SetMass(50.0f);
	collider->size = bae::Vector2F(40.0f, 40.0f);
	healthBar->SetLocalPosition(bae::Vector2F(0.0f, 24.0f));
	healthBar->SetWidth(32.0f);
}

void RollingEnemy::Destroy()
{
	EnemyCharacter::Destroy();
}
