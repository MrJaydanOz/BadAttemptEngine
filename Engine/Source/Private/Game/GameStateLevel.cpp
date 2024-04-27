#include "GameStateLevel.h"
#include "BAE/BAE_Time.h"

void GameStateLevel::OnStart(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();
	bae::Scene& scene = *bae::Game::GetScene();
	bae::Graphics& graphics = *bae::Game::GetGraphics();

	time.SetTimeScale(1.0f);

	graphics.camera.size = 1.0f;
	graphics.camera.sizeAxisFactor = 0.0f;
	graphics.camera.center = bae::PoseF({ 0.0f, 0.0f }, 0.0f);

	playerSprites = bae::Image::Load("Content/Sprites/PlayerSprites.png");
	basicEnemySprites = bae::Image::Load("Content/Sprites/BasicEnemySprites.png");
	rollingEnemySprites = bae::Image::Load("Content/Sprites/RollingEnemySprites.png");
	mortarEnemySprites = bae::Image::Load("Content/Sprites/MortarEnemySprites.png");
	playerBulletSprites = bae::Image::Load("Content/Sprites/PlayerBulletSprites.png");
	basicEnemyBulletSprites = bae::Image::Load("Content/Sprites/BasicEnemyBulletSprites.png");

	using CreateStateT = in_initializer_list<bae::AnimationControl*>;

	bae::AnimationState* state = nullptr;
	// Path to node from Animator node.
	auto animationControl = bae::AnimationControlSpriteImage({ "Sprite" });

	playerAnimation = new bae::Animation();
	{
		// AnimationControl settings.
		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 8.0f;
		animationControl.image = playerSprites;
		// Add an AnimationState with the AnimationControl in it.
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			playerAnimation->CreateState<bae::AnimationState, CreateStateT>("idle r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 24.0f;
		animationControl.image = playerSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			playerAnimation->CreateState<bae::AnimationState, CreateStateT>("walk r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 6;
		animationControl.frameRate = 24.0f;
		animationControl.image = playerSprites;
		animationControl.clipStartPosition = bae::Vector2I(32 * 8, 0);
		LOOP(i, 16)
		{
			state = playerAnimation->CreateState<bae::AnimationState, CreateStateT>("shoot r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			state->changeToStateAfterDuration = playerAnimation->GetState("idle r" + std::to_string(i));
			state->duration = 6.0f / 24.0f;
			animationControl.clipStartPosition.y += 32;
		}
	}

	playerBulletAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(16, 16);
		animationControl.frameCount = 1;
		animationControl.frameRate = 1.0f;
		animationControl.image = playerBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);

		playerBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("inair", { new bae::AnimationControlSpriteImage(animationControl) });

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.clipFrameDelta = bae::Vector2I(0, 32);
		animationControl.frameCount = 4;
		animationControl.frameRate = 12.0f;
		animationControl.image = playerBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 16);

		state = playerBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("impact", { new bae::AnimationControlSpriteImage(animationControl) });
		state->changeToStateAfterDuration = nullptr;
		state->duration = 4.0f / 12.0f;
		animationControl.clipFrameDelta = {};

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 4;
		animationControl.frameRate = 24.0f;
		animationControl.image = playerBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(32, 0);
		LOOP(i, 16)
		{
			state = playerBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("fire r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			state->changeToStateAfterDuration = nullptr;
			state->duration = 4.0f / 24.0f;
			animationControl.clipStartPosition.y += 32;
		}
	}

	basicEnemyAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 8.0f;
		animationControl.image = basicEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			basicEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("idle r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 24.0f;
		animationControl.image = basicEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			basicEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("walk r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 6;
		animationControl.frameRate = 24.0f;
		animationControl.image = basicEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(32 * 8, 0);
		LOOP(i, 16)
		{
			state = basicEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("shoot r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			state->changeToStateAfterDuration = basicEnemyAnimation->GetState("idle r" + std::to_string(i));
			state->duration = 6.0f / 24.0f;
			animationControl.clipStartPosition.y += 32;
		}
	}

	mortarEnemyAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 8.0f;
		animationControl.image = mortarEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			mortarEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("idle r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 8;
		animationControl.frameRate = 24.0f;
		animationControl.image = mortarEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			mortarEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("walk r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			animationControl.clipStartPosition.y += 32;
		}

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 6;
		animationControl.frameRate = 24.0f;
		animationControl.image = mortarEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(32 * 8, 0);
		LOOP(i, 16)
		{
			state = mortarEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("shoot r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			state->changeToStateAfterDuration = mortarEnemyAnimation->GetState("idle r" + std::to_string(i));
			state->duration = 6.0f / 24.0f;
			animationControl.clipStartPosition.y += 32;
		}
	}

	rollingEnemyAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(64, 64);
		animationControl.frameCount = 12;
		animationControl.frameRate = 12.0f;
		animationControl.image = rollingEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);
		LOOP(i, 16)
		{
			rollingEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("roll r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			animationControl.clipStartPosition.y += 64;
		}

		animationControl.clipSize = bae::Vector2I(64, 64);
		animationControl.frameCount = 12;
		animationControl.frameRate = 12.0f;
		animationControl.image = rollingEnemySprites;
		animationControl.clipStartPosition = bae::Vector2I(64 * 12, 0);
		LOOP(i, 16)
		{
			rollingEnemyAnimation->CreateState<bae::AnimationState, CreateStateT>("blink r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			animationControl.clipStartPosition.y += 64;
		}
	}

	basicEnemyBulletAnimation = new bae::Animation();
	{
		animationControl.clipSize = bae::Vector2I(16, 16);
		animationControl.frameCount = 1;
		animationControl.frameRate = 1.0f;
		animationControl.image = basicEnemyBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 0);

		basicEnemyBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("inair", { new bae::AnimationControlSpriteImage(animationControl) });

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.clipFrameDelta = bae::Vector2I(0, 32);
		animationControl.frameCount = 4;
		animationControl.frameRate = 12.0f;
		animationControl.image = basicEnemyBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(0, 16);

		state = basicEnemyBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("impact", { new bae::AnimationControlSpriteImage(animationControl) });
		state->changeToStateAfterDuration = nullptr;
		state->duration = 4.0f / 12.0f;
		animationControl.clipFrameDelta = {};

		animationControl.clipSize = bae::Vector2I(32, 32);
		animationControl.frameCount = 4;
		animationControl.frameRate = 24.0f;
		animationControl.image = basicEnemyBulletSprites;
		animationControl.clipStartPosition = bae::Vector2I(32, 0);
		LOOP(i, 16)
		{
			state = basicEnemyBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("fire r" + std::to_string(i), { new bae::AnimationControlSpriteImage(animationControl) });
			state->changeToStateAfterDuration = nullptr;
			state->duration = 4.0f / 24.0f;
			animationControl.clipStartPosition.y += 32;
		}
	}

	player = scene.AddNode<PlayerCharacter>("Player");
	player->Setup(*this);
}

void GameStateLevel::OnTick(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();
	bae::Input& input = *bae::Game::GetInput();
	bae::Graphics& graphics = *bae::Game::GetGraphics();
	bae::Scene& scene = *bae::Game::GetScene();
	bae::Physics& physics = *bae::Game::GetPhysics();

	bae::Vector2F inputDirection = bae::Vector2F(0, 0);

	if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_W)) inputDirection.y++;
	if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_S)) inputDirection.y--;
	if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_A)) inputDirection.x--;
	if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_D)) inputDirection.x++;

	player->MoveWithInput(inputDirection);

	bae::Vector2F aimDirection = (bae::Vector2F)graphics.PixelToScreenPoint(input.GetMousePixel()) - graphics.WorldToScreenPoint(player->GetPosition());
	aimDirection /= aimDirection.Magnitude();

	if (effects.size() > 0)
	{
		bool someDeletion = false;
		for (Effect*& i : effects)
		{
			if (i->IsDone())
			{
				bae::Destroy(i);
				i = nullptr;
				someDeletion = true;
			}
		}

		if (someDeletion)
			effects.RemoveWhere([](in<Effect*> effect) -> bool { return effect == nullptr; });
	}

	if (basicBullets.size() > 0)
	{
		bae::List<bae::PhysicsCollision> collisions;

		bool someDeletion = false;
		for (ref<BasicBullet*> i : basicBullets)
		{
			if ((i->lifeTime -= time.DeltaTime()) <= 0.0f || i->animator->GetCurrentState() == nullptr)
			{
				bae::Destroy(i);
				i = nullptr;
				someDeletion = true;
			}
			else if (i->animator->GetCurrentState()->GetKey().starts_with("inair"))
			{
				physics.FindCollisionsOf(i, collisions);
				for (in<bae::PhysicsCollision> collision : collisions)
				{
					EnemyCharacter** result;
					if (enemies.TryFindIf([&](in<EnemyCharacter*> enemy) -> bool { return enemy == collision.physicsBody2; }, result))
					{
						i->animator->Play("impact");
						i->SetVelocity(bae::Vector2F(0.0f, 0.0f));

						(*result)->Damage(i->damage);
					}
				}
			}
		}

		if (someDeletion)
			basicBullets.RemoveWhere([](in<BasicBullet*> bullet) -> bool { return bullet == nullptr; });
	}

	if (enemies.size() > 0)
	{
		bool someDeletion = false;
		for (ref<EnemyCharacter*> i : enemies)
		{
			i->Tick(*this);

			if (i->healthBar->currentHealth < 0.0f)
			{
				bae::Destroy(i);
				i = nullptr;
				someDeletion = true;
			}
		}

		if (someDeletion)
			enemies.RemoveWhere([](in<EnemyCharacter*> enemy) -> bool { return enemy == nullptr; });
	}

	enemySpawnRate += time.DeltaTime() * 0.1f;
	enemySpawnTimer -= time.DeltaTime();

	if (enemySpawnTimer <= 0.0f)
	{
		enemySpawnTimer = 1.0f / enemySpawnRate;

		int random = rand() % 8;

		EnemyCharacter* newEnemy;

		switch (random)
		{
		case 0: 
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			newEnemy = scene.AddNode<RollingEnemy>("Rolling Enemy");
			newEnemy->SetPosition(bae::Vector2F(0.0f, 300.0f).Rotate(rand() % 360));
			newEnemy->Setup(*this);
			enemies.Append(newEnemy);
			break;
		}

	}

	if (input.KeyPressed(bae::KeyCode::KEYCODE_LMB))
	{
		BasicBullet* bullet = scene.AddNode<BasicBullet>("Bullet");
		bullet->SetPosition(player->GetPosition() + (aimDirection * 8.0f));
		bullet->SetVelocity(aimDirection * 400.0f);
		bullet->collider->size = bae::Vector2F(6.0f, 6.0f);
		bullet->collider->collisionLayers = 0b0100;
		bullet->collider->isTrigger = true;
		bullet->animator->SetAnimation(playerBulletAnimation);
		bullet->animator->Play("inair");
		bullet->damage = 26.0f;
		bullet->lifeTime = 3.0f;
		basicBullets.Append(bullet);

		Effect* muzzleFlash = scene.AddNode<Effect>("Flash");
		muzzleFlash->sprite->offset = bae::PoseF(player->GetPosition() + (aimDirection * 8.0f), 0.0f);
		muzzleFlash->SetAnimation(playerBulletAnimation);
		muzzleFlash->Play("fire r" + std::to_string(bae::Mod(Character::GetDirectionAnimationIndex(aimDirection) + 8, 16)));
		effects.Append(muzzleFlash);

		player->UpdateAnimation(aimDirection, true);
	}
	else
		player->UpdateAnimation(aimDirection, false);

	graphics.camera.center.position = bae::Lerp(graphics.camera.center.position, player->GetPosition(), 0.025f);
	graphics.camera.size = bae::Lerp(graphics.camera.size, 512.0f, 0.025f);
}

void GameStateLevel::OnEnd(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();

	time.SetTimeScale(1.0f);

	bae::Destroy(player);

	delete playerAnimation;

	delete playerSprites;
}
