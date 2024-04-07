#include "BAE/BAE_Engine.h"
#include "BAE/BAE_Animation.h"

using namespace bae;

Image* playerSprites;
Image* enemySprites;
Animation* playerAnimation;
Animation* enemyAnimation;
PhysicsBody* playerBody;
PhysicsBody* enemyBody;

Vector2I lastWalkInput;

void BAE_Start()
{
	// Load images.
	playerSprites = Image::Load("Content/Sprites/PlayerSprites.png");
	enemySprites = Image::Load("Content/Sprites/EnemySprites.png");

	// Load animations.
	playerAnimation = new Animation({});
	enemyAnimation = new Animation({});

	// Path to node from Animator node.
	auto animationControl = AnimationControlSpriteImage({ "Sprite" });
	// AnimationControl settings.
	animationControl.clipSize = Vector2I(32, 32);
	animationControl.clipStartPosition = Vector2I(0, 0);
	animationControl.frameCount = 12;
	animationControl.frameRate = 12.0f;
	animationControl.image = playerSprites;
	// Add an AnimationState with the AnimationControl in it.
	playerAnimation->AddAnimationState("idle", AnimationState({ animationControl }));

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.clipStartPosition = Vector2I(0, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 12.0f;
	animationControl.image = playerSprites;
	playerAnimation->AddAnimationState("walking", AnimationState({ animationControl }));

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.clipStartPosition = Vector2I(0, 0);
	animationControl.frameCount = 12;
	animationControl.frameRate = 12.0f;
	animationControl.image = enemySprites;
	enemyAnimation->AddAnimationState("idle", AnimationState({ animationControl }));

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.clipStartPosition = Vector2I(0, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 12.0f;
	animationControl.image = enemySprites;
	enemyAnimation->AddAnimationState("walking", AnimationState({ animationControl }));

	// Create Objects.

	playerBody = Game::GetScene()->AddNode<PhysicsBody>("Player");
	playerBody->SetPosition(Vector2F(100.0f, 100.0f));

	Sprite* playerSprite = playerBody->AddChild<Sprite>("Sprite");
	playerSprite->image = playerSprites;
	playerSprite->clipRect = RectI(0, 0, 32, 32);
	playerSprite->scale = Vector2F(3.0f, 3.0f);

	ColliderAxisBox* playerCollider = playerBody->AddChild<ColliderAxisBox>("Collider");
	playerCollider->size = Vector2F(32.0f * 3.0f, 32.0f * 3.0f);

	ColliderAxisBox* obstacle1 = Game::GetScene()->AddNode<ColliderAxisBox>("Obstacle");
	obstacle1->size = Vector2F(100.0f, 100.0f);
	obstacle1->SetPosition(Vector2F(300.0f, 300.0f));

	Sprite* enemySprite = obstacle1->AddChild<Sprite>("Sprite");
	enemySprite->image = playerSprites;
	enemySprite->clipRect = RectI(0, 0, 32, 32);
	enemySprite->scale = Vector2F(3.0f, 3.0f);

	DEBUG_LOG_INFO("Created 'Test1'");
}

void BAE_Update()
{
	lastWalkInput = Vector2I(0, 0);

	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_W)) lastWalkInput.y++;
	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_S)) lastWalkInput.y--;
	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_A)) lastWalkInput.x--;
	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_D)) lastWalkInput.x++;
}

void BAE_LateUpdate()
{

}

void BAE_FixedUpdate()
{

}

void BAE_PhysicsUpdate()
{
	playerBody->SetVelocity(MoveTowards(playerBody->GetVelocity(), ((Vector2F)lastWalkInput).Normalized() * 500.0f, 5000.0f * Game::GetTime()->DeltaTime()));
}

void BAE_End()
{
	delete playerAnimation;
	delete enemyAnimation;
	delete playerSprites;
	delete enemySprites;

	DEBUG_LOG_INFO("Bye");
}