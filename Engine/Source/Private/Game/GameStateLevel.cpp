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
	playerBulletSprites = bae::Image::Load("Content/Sprites/PlayerBulletSprites.png");
	basicEnemyBulletSprites = bae::Image::Load("Content/Sprites/BasicEnemyBulletSprites.png");

	using CreateStateT = in_initializer_list<bae::AnimationControl*>;

	playerAnimation = new bae::Animation();
	bae::AnimationState* state = nullptr;

	// Path to node from Animator node.
	auto animationControl = bae::AnimationControlSpriteImage({ "Sprite" });
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

	playerBulletAnimation = new bae::Animation();

	animationControl.clipSize = bae::Vector2I(16, 16);
	animationControl.frameCount = 1;
	animationControl.frameRate = 1.0f;
	animationControl.image = basicEnemyBulletSprites;
	animationControl.clipStartPosition = bae::Vector2I(0, 0);

	playerBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("inair", { new bae::AnimationControlSpriteImage(animationControl) });

	animationControl.clipSize = bae::Vector2I(32, 32);
	animationControl.clipFrameDelta = bae::Vector2I(0, 32);
	animationControl.frameCount = 4;
	animationControl.frameRate = 12.0f;
	animationControl.image = basicEnemyBulletSprites;
	animationControl.clipStartPosition = bae::Vector2I(0, 16);

	state = playerBulletAnimation->CreateState<bae::AnimationState, CreateStateT>("impact", { new bae::AnimationControlSpriteImage(animationControl) });
	state->changeToStateAfterDuration = nullptr;
	state->duration = 4.0f / 12.0f;

	player = scene.AddNode<PlayerCharacter>("Player");
	player->speed = 50.0f;
	player->acceleration = 500.0f;
	player->animator->SetAnimation(playerAnimation);
	player->animator->Play("idle r0");
	player->collider->collisionLayers = 0b0010;
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

	bae::Vector2F aimDirection = graphics.WorldToScreenPoint(player->GetPosition()) - (bae::Vector2F)graphics.PixelToScreenPoint(input.GetMousePixel());
	aimDirection /= aimDirection.Magnitude();

	if (input.KeyPressed(bae::KeyCode::KEYCODE_LMB))
	{
		BasicBullet* bullet = scene.AddNode<BasicBullet>("Bullet");
		bullet->SetPosition(player->GetPosition() + (aimDirection * 4.0f));
		bullet->SetVelocity(aimDirection * 100.0f);
		bullet->collider->size = bae::Vector2F(6.0f, 6.0f);
		bullet->collider->collisionLayers = 0b0100;
		bullet->collider->isTrigger = true;
		bullet->animator->SetAnimation(playerBulletAnimation);
		bullet->damage = 20.0f;
		bullet->animator->Play("inair");
		bullets.Append(bullet);

		player->UpdateAnimation(aimDirection, true);
	}
	else
		player->UpdateAnimation(aimDirection, false);

	graphics.camera.center.position = bae::Lerp(graphics.camera.center.position, player->GetPosition(), 0.025f);
	graphics.camera.size = bae::Lerp(graphics.camera.size, 512.0f, 0.025f);

	if (bullets.size() > 0)
	{
		for (BasicBullet*& i : bullets)
		{
			if ((i->lifeTime -= time.DeltaTime()) <= 0.0f || i->animator->GetCurrentState() == nullptr)
			{
				bae::Destroy(i);
				i = nullptr;
			}
			else if (i->animator->GetCurrentState()->GetKey().starts_with("inair"))
			{
				if (physics.CollisionExistsWithWhere(i, [&](in<bae::PhysicsCollision> collision) -> bool
					{
						return false;// collision.physicsBody2 == player;
					}))
				{
					i->animator->Play("impact");
					i->SetVelocity(bae::Vector2F(0.0f, 0.0f));
				}
			}
		}

		bullets.RemoveWhere([](in<BasicBullet*> bullet) -> bool { return bullet == nullptr; });
	}
}

void GameStateLevel::OnEnd(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();

	time.SetTimeScale(1.0f);

	bae::Destroy(player);

	delete playerAnimation;

	delete playerSprites;
}
