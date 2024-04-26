#include "GameStateLevel.h"
#include "BAE/BAE_Time.h"

void GameStateLevel::OnStart(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();
	bae::Scene& scene = *bae::Game::GetScene();
	bae::Graphics& graphics = *bae::Game::GetGraphics();

	time.SetTimeScale(1.0f);

	graphics.camera.size = 256.0f;
	graphics.camera.sizeAxisFactor = 0.0f;
	graphics.camera.center = bae::PoseF({ 0.0f, 0.0f }, 0.0f);

	playerSprites = bae::Image::Load("Content/Sprites/PlayerSprites.png");

	playerAnimation = new bae::Animation();

	using CreateStateT = in_initializer_list<bae::AnimationControl*>;

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

	player = scene.AddNode<PlayerCharacter>("Player");
	player->speed = 50.0f;
	player->acceleration = 500.0f;
	player->animator->SetAnimation(playerAnimation);
	player->animator->Play("idle r0");
}

void GameStateLevel::OnTick(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();
	bae::Input& input = *bae::Game::GetInput();
	bae::Graphics& graphics = *bae::Game::GetGraphics();

	bae::Vector2F inputDirection = bae::Vector2F(0, 0);

	if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_W)) inputDirection.y++;
	if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_S)) inputDirection.y--;
	if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_A)) inputDirection.x--;
	if (bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_D)) inputDirection.x++;

	player->MoveWithInput(inputDirection);
	player->UpdateAnimation(graphics.WorldToScreenPoint(player->GetPosition()) - (bae::Vector2F)graphics.PixelToScreenPoint(input.GetMousePixel()));

	graphics.camera.center.position = bae::Lerp(graphics.camera.center.position, player->GetPosition(), 0.1f);
}

void GameStateLevel::OnEnd(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();

	time.SetTimeScale(1.0f);

	bae::Destroy(player);

	delete playerAnimation;

	delete playerSprites;
}
