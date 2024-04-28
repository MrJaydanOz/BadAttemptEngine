#include "Character.h"
#include "GameStateLevel.h"

void Character::UpdateAnimation(in<bae::Vector2F> lookDirection, bool shoot)
{
	if (hurtAnimationTimer >= 0.0f)
	{
		const float notRed = bae::Min(1.0f, hurtAnimationTimer);

		sprite->color = (bae::Color)bae::ColorF(1.0f, notRed, notRed);
		sprite->offset.rotation = 15.0f / ((20.0f * hurtAnimationTimer) + 1);

		hurtAnimationTimer += bae::Game::GetTime()->DeltaTime();
	}

	bae::Vector2F velocity = GetVelocity();

	bool isWalking = velocity.SqrMagnitude() > 1.0f;

	int direction = GetDirectionAnimationIndex(lookDirection);

	if (shoot)
	{
		animator->Play((size_t)direction + 32, true);

		lastIsShooting = true;
	}
	else
	{
		auto currentState = animator->GetCurrentState();
		bool isShooting = currentState != nullptr && currentState->GetKey().starts_with("shoot");

		if ((direction != lastLookDirection) || (isWalking != lastIsWalking) || (isShooting != lastIsShooting))
			animator->Play(isShooting
				? (size_t)direction + 32
				: isWalking
				? (size_t)direction + 16
				: (size_t)direction + 0,
				(isWalking != lastIsWalking) || (isShooting != lastIsShooting));

		lastIsShooting = isShooting;
	}

	lastIsWalking = isWalking;
	lastLookDirection = direction;
}

void Character::Damage(in<float> amount)
{
	hurtAnimationTimer = 0.0f;
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
	shadow = animator->AddChild<bae::Sprite>("Shadow");
	shadow->offset = bae::PoseF(bae::Vector2F(-2.0f, 0.0f), 0.0);
	shadow->SetZIndex(-100);
	collider = AddChild<bae::ColliderAxisBox>("Collider");
	healthBar = AddChild<HealthBar>("HealthBar");
}

void Character::Destroy()
{ PhysicsBody::Destroy(); }

void PlayerCharacter::Setup(ref<GameStateLevel> level)
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

void EnemyCharacter::Tick(ref<GameStateLevel> level) noexcept
{
	if (hurtAnimationTimer >= 0.0f)
	{
		hurtAnimationTimer += bae::Game::GetTime()->DeltaTime();
		const float notRed = bae::Min(1.0f, hurtAnimationTimer);

		sprite->color = (bae::Color)bae::ColorF(1.0f, notRed, notRed);
		sprite->offset.rotation = 15.0f / ((20.0f * hurtAnimationTimer) + 1);
	}
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

void RollingEnemy::Setup(ref<GameStateLevel> level)
{
	speed = 60.0f;
	acceleration = 10.0f;
	animator->SetAnimation(level.rollingEnemyAnimation);
	animator->Play("roll r0");
}

void RollingEnemy::Tick(ref<GameStateLevel> level) noexcept
{
	EnemyCharacter::Tick(level);

	bae::Time& time = *bae::Game::GetTime();

	MoveWithInput(level.player->GetPosition() - GetPosition());

	animator->animationSpeed = GetVelocity().Magnitude() / 60.0f;

	blinkTimer -= time.DeltaTime();

	if (blinkTimer <= 0.0f)
	{
		blinkTimer += 1.2f;
	}

	int direction = GetDirectionAnimationIndex(-GetVelocity());

	animator->Play(blinkTimer < 0.2f
		? (size_t)direction + 16
		: (size_t)direction + 0,
		false);

	if (GetPosition().SqrDistance(level.player->GetPosition()) < 20.0f * 20.0f)
	{
		level.player->Damage(time.DeltaTime() * 200.0f);
	}
}

void RollingEnemy::Die(ref<GameStateLevel> level) noexcept
{
	bae::Vector2F position = GetPosition();
	level.CreateCollectable(position);
	level.CreateCollectable(position);
	level.CreateCollectable(position);
	level.CreateCollectable(position);
	level.CreateCollectable(position);

	level.score += 200;
}

void RollingEnemy::Create(in<const char*> name)
{
	EnemyCharacter::Create(name);

	SetMass(50.0f);
	collider->collisionLayers = 0b0100;
	collider->size = bae::Vector2F(40.0f, 40.0f);
	healthBar->SetLocalPosition(bae::Vector2F(0.0f, 24.0f));
	healthBar->SetWidth(32.0f);
	healthBar->maxHealth = 250.0f;
	healthBar->currentHealth = healthBar->maxHealth;
}

void RollingEnemy::Destroy()
{
	EnemyCharacter::Destroy();
}

void BasicEnemy::Setup(ref<GameStateLevel> level)
{
	speed = 25.0f;
	acceleration = 500.0f;
	animator->SetAnimation(level.basicEnemyAnimation);
	animator->Play("idle r0");
}

void BasicEnemy::Tick(ref<GameStateLevel> level) noexcept
{
	EnemyCharacter::Tick(level);

	bae::Time& time = *bae::Game::GetTime();
	bae::Scene& scene = *bae::Game::GetScene();

	bae::Vector2F deltaTarget = moveTarget - GetPosition();

	bae::Vector2F deltaPlayer = level.player->GetPosition() - GetPosition();

	if (deltaTarget.SqrMagnitude() > 100.0f * 100.0f)
	{
		moveTimer = (rand() % 2) + 2.0f;

		moveTarget = GetPosition() + ((moveTarget - GetPosition()).Normalized() * 100.0f);

		bae::Vector2F deltaTarget = moveTarget - GetPosition();
	}
	else if (deltaTarget.SqrMagnitude() < 5.0f * 5.0f)
	{
		bae::Vector2F deltaPlayer = level.player->GetPosition() - GetPosition();

		if (moveTimer <= 0.0f)
		{
			moveTarget = level.player->GetPosition() - (deltaPlayer.Normalized() * 100.0f);
			moveTarget += bae::Vector2F((rand() % 20) - 10.0f, (rand() % 20) - 10.0f);

			moveTimer = (rand() % 4) + 4.0f;
		}
		else
		{
			moveTimer -= time.DeltaTime();

			MoveWithInput(deltaTarget);

			if (shootTimer <= 0.0f)
			{
				shootTimer = 0.8f;

				bae::Vector2F aimDirection = deltaPlayer.Normalized();

				BasicBullet* bullet = scene.AddNode<BasicBullet>("Bullet");
				bullet->SetPosition(GetPosition() + (aimDirection * 8.0f));
				bullet->SetVelocity(aimDirection * 100.0f);
				bullet->collider->size = bae::Vector2F(6.0f, 6.0f);
				bullet->collider->collisionLayers = 0b0010;
				bullet->collider->isTrigger = true;
				bullet->animator->SetAnimation(level.basicEnemyBulletAnimation);
				bullet->animator->Play("inair");
				bullet->damage = 26.0f;
				bullet->lifeTime = 15.0f;
				level.basicBullets.Append(bullet);

				Effect* muzzleFlash = scene.AddNode<Effect>("Flash");
				muzzleFlash->sprite->offset = bae::PoseF(GetPosition() + (aimDirection * 8.0f), 0.0f);
				muzzleFlash->SetAnimation(level.basicEnemyBulletAnimation);
				muzzleFlash->Play("fire r" + std::to_string(bae::Mod(Character::GetDirectionAnimationIndex(aimDirection) + 8, 16)));
				level.effects.Append(muzzleFlash);

				UpdateAnimation(deltaPlayer, true);
			}
			else
			{
				shootTimer -= time.DeltaTime();

				UpdateAnimation(deltaPlayer, false);
			}
		}
	}
	else
	{
		MoveWithInput(deltaTarget);
		UpdateAnimation(deltaTarget, false);
	}
}

void BasicEnemy::Die(ref<GameStateLevel> level) noexcept
{
	bae::Vector2F position = GetPosition();
	level.CreateCollectable(position);
	level.CreateCollectable(position);

	level.score += 100;
}

void BasicEnemy::Create(in<const char*> name)
{
	EnemyCharacter::Create(name);

	collider->collisionLayers = 0b0100;
	collider->size = bae::Vector2F(20.0f, 20.0f);
	healthBar->maxHealth = 50.0f;
	healthBar->currentHealth = healthBar->maxHealth;
}

void BasicEnemy::Destroy()
{
	EnemyCharacter::Destroy();
}

void ShotgunEnemy::Setup(ref<GameStateLevel> level)
{
	speed = 25.0f;
	acceleration = 500.0f;
	animator->SetAnimation(level.mortarEnemyAnimation);
	animator->Play("idle r0");
}

void ShotgunEnemy::Tick(ref<GameStateLevel> level) noexcept
{
	EnemyCharacter::Tick(level);

	bae::Time& time = *bae::Game::GetTime();
	bae::Scene& scene = *bae::Game::GetScene();

	bae::Vector2F deltaTarget = moveTarget - GetPosition();

	bae::Vector2F deltaPlayer = level.player->GetPosition() - GetPosition();

	if (deltaTarget.SqrMagnitude() > 100.0f * 100.0f)
	{
		moveTimer = (rand() % 2) + 2.0f;

		moveTarget = GetPosition() + ((moveTarget - GetPosition()).Normalized() * 100.0f);

		bae::Vector2F deltaTarget = moveTarget - GetPosition();
	}
	if (deltaTarget.SqrMagnitude() < 5.0f * 5.0f)
	{
		bae::Vector2F deltaPlayer = level.player->GetPosition() - GetPosition();

		if (moveTimer <= 0.0f)
		{
			moveTarget = level.player->GetPosition() - (deltaPlayer.Normalized() * 100.0f);
			moveTarget += bae::Vector2F((rand() % 20) - 10.0f, (rand() % 20) - 10.0f);

			moveTimer = (rand() % 4) + 4.0f;
		}
		else
		{
			moveTimer -= time.DeltaTime();

			MoveWithInput(deltaTarget);

			if (shootTimer <= 0.0f)
			{
				shootTimer = 1.8f;

				bae::Vector2F aimDirection = deltaPlayer.Normalized();

				auto shoot = [&](in<bae::Vector2F> direction) -> void
					{
						BasicBullet* bullet = scene.AddNode<BasicBullet>("Bullet");
						bullet->SetPosition(GetPosition() + (direction * 8.0f));
						bullet->SetVelocity(direction * 100.0f);
						bullet->collider->size = bae::Vector2F(6.0f, 6.0f);
						bullet->collider->collisionLayers = 0b0010;
						bullet->collider->isTrigger = true;
						bullet->animator->SetAnimation(level.basicEnemyBulletAnimation);
						bullet->animator->Play("inair");
						bullet->damage = 26.0f;
						bullet->lifeTime = 15.0f;
						level.basicBullets.Append(bullet);
					};

				shoot(aimDirection.Rotate(-20.0f));
				shoot(aimDirection.Rotate(+20.0f));
				shoot(aimDirection.Rotate(-10.0f));
				shoot(aimDirection.Rotate(+10.0f));
				shoot(aimDirection);

				Effect* muzzleFlash = scene.AddNode<Effect>("Flash");
				muzzleFlash->sprite->offset = bae::PoseF(GetPosition() + (aimDirection * 8.0f), 0.0f);
				muzzleFlash->SetAnimation(level.basicEnemyBulletAnimation);
				muzzleFlash->Play("fire r" + std::to_string(bae::Mod(Character::GetDirectionAnimationIndex(aimDirection) + 8, 16)));
				level.effects.Append(muzzleFlash);

				UpdateAnimation(deltaPlayer, true);
			}
			else
			{
				shootTimer -= time.DeltaTime();

				UpdateAnimation(deltaPlayer, false);
			}
		}
	}
	else
	{
		MoveWithInput(deltaTarget);
		UpdateAnimation(deltaTarget, false);
	}
}

void ShotgunEnemy::Die(ref<GameStateLevel> level) noexcept
{
	bae::Vector2F position = GetPosition();
	level.CreateCollectable(position);
	level.CreateCollectable(position);
	level.CreateCollectable(position);

	level.score += 150;
}

void ShotgunEnemy::Create(in<const char*> name)
{
	EnemyCharacter::Create(name);

	collider->collisionLayers = 0b0100;
	collider->size = bae::Vector2F(20.0f, 20.0f);
	healthBar->maxHealth = 50.0f;
	healthBar->currentHealth = healthBar->maxHealth;
}

void ShotgunEnemy::Destroy()
{
	EnemyCharacter::Destroy();
}
