#include "BAE/BAE_Engine.h"
#include "BAE/BAE_Animation.h"

using namespace bae;

class Character : public PhysicsBody
{
	NODE_BEGIN;

public:
	float speed;
	float acceleration;
	Animator* animator;
	Sprite* sprite;
	ColliderAxisBox* colldier;
	float maxHealth;
	float health;
private:
	int _lastAnimationDirection;

public:
	virtual ~Character() noexcept override { PhysicsBody::~PhysicsBody(); }

	void UpdateAnimation()
	{
		Vector2F velocity = GetVelocity();

		if (velocity.SqrMagnitude() < 1.0f)
		{
			std::pair<uint8, Vector2F> pointsAroundAnimations[8]
			{
				{ 0, Vector2F(-1.0f  , +0.0f  ) },
				{ 1, Vector2F(-SQRT_2, -SQRT_2) },
				{ 2, Vector2F(+0.0f  , -1.0f  ) },
				{ 3, Vector2F(+SQRT_2, -SQRT_2) },
				{ 4, Vector2F(+1.0f  , +0.0f  ) },
				{ 5, Vector2F(+SQRT_2, +SQRT_2) },
				{ 6, Vector2F(+0.0f  , +1.0f  ) },
				{ 7, Vector2F(-SQRT_2, +SQRT_2) }
			};

			const auto distanceComparison = [&](in<std::pair<uint8, Vector2F>> a, in<std::pair<uint8, Vector2F>> b) noexcept -> bool 
				{ return a.second.SqrDistance(velocity) < b.second.SqrDistance(velocity); };

			std::pair<uint8, Vector2F> pointAroundAnimation = Min(Min(Min(Min(Min(Min(Min(
				pointsAroundAnimations[0],
				pointsAroundAnimations[1], distanceComparison),
				pointsAroundAnimations[2], distanceComparison),
				pointsAroundAnimations[3], distanceComparison),
				pointsAroundAnimations[4], distanceComparison),
				pointsAroundAnimations[5], distanceComparison),
				pointsAroundAnimations[6], distanceComparison),
				pointsAroundAnimations[7], distanceComparison);

			_lastAnimationDirection = pointAroundAnimation.first;

			switch (_lastAnimationDirection)
			{
			case 0: animator->Play("walking -x"); break;
			case 1: animator->Play("walking -x-y"); break;
			case 2: animator->Play("walking -y"); break;
			case 3: animator->Play("walking +x-y"); break;
			case 4: animator->Play("walking +x"); break;
			case 5: animator->Play("walking +x+y"); break;
			case 6: animator->Play("walking +y"); break;
			case 7: animator->Play("walking -x+y"); break;
			}
		}
		else
		{
			switch (_lastAnimationDirection)
			{
				case 0: animator->Play("idle -x"); break;
				case 1: animator->Play("idle -x-y"); break;
				case 2: animator->Play("idle -y"); break;
				case 3: animator->Play("idle +x-y"); break;
				case 4: animator->Play("idle +x"); break;
				case 5: animator->Play("idle +x+y"); break;
				case 6: animator->Play("idle +y"); break;
				case 7: animator->Play("idle -x+y"); break;
			}
		}
	}

	void MoveWithInput(in<Vector2F> input)
	{
		Vector2F scaledInput = input.SqrMagnitude() > 1.0f ? input.Normalized() : input;

		SetVelocity(MoveTowards(GetVelocity(), scaledInput * 500.0f, 5000.0f * Game::GetTime()->DeltaTime()));
	}

protected:
	Character(in<std::string> name = "") noexcept : PhysicsBody::PhysicsBody(name)
	{
		speed = 0.0f;
		acceleration = 0.0f;
		animator = AddChild<Animator>("Animator");
		sprite = animator->AddChild<Sprite>("Sprite");
		colldier = AddChild<ColliderAxisBox>("Collider");
		maxHealth = 100.0f;
		health = maxHealth;
		_lastAnimationDirection = 0;
	}
};

class PlayerCharacter : public Character
{
	NODE_BEGIN;

public:
	virtual ~PlayerCharacter() noexcept override { Character::~Character(); }

protected:
	PlayerCharacter(in<std::string> name = "") noexcept : Character::Character(name)
	{ 

	}
};

class EnemyCharacter : public Character
{
	NODE_BEGIN;

public:
	virtual ~EnemyCharacter() noexcept override { Character::~Character(); }

	void MoveTowardsPlayer(in<PlayerCharacter*> player)
	{
		Vector2F deltaPosition = player->GetPosition() - GetPosition();
	}

protected:
	EnemyCharacter(in<std::string> name = "") noexcept : Character::Character(name)
	{

	}
};

Image* playerSprites;
Image* enemySprites;
Animation* playerAnimation;
Animation* enemyAnimation;
PlayerCharacter* playerCharacter;
EnemyCharacter* enemyCharacter;

Vector2I lastWalkInput;

Font* testFont;

bool isGameOver;

void BAE_Start()
{
	// Load images.
	playerSprites = Image::Load("Content/Sprites/PlayerSprites.png");
	enemySprites = Image::Load("Content/Sprites/EnemySprites.png");
	testFont = Font::Load("Content/Fonts/Roboto/Roboto-Medium.ttf", 64);

	// Load animations.
	playerAnimation = new Animation({});

	// Path to node from Animator node.
	auto animationControl = AnimationControlSpriteImage({ "Sprite" });
	// AnimationControl settings.
	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 8.0f;
	animationControl.image = playerSprites;
	// Add an AnimationState with the AnimationControl in it.
	animationControl.clipStartPosition = Vector2I(0, 0);
	playerAnimation->AddAnimationState("idle -x", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle -x-y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle -y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle +x-y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle +x", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle +x+y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle +y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle -x+y", AnimationState({ animationControl }));

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 24.0f;
	animationControl.image = playerSprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	playerAnimation->AddAnimationState("walking -x", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking -x-y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking -y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking +x-y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking +x", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking +x+y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking +y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking -x+y", AnimationState({ animationControl }));

	enemyAnimation = new Animation({});

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 8.0f;
	animationControl.image = playerSprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	enemyAnimation->AddAnimationState("idle -x", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle -x-y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle -y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle +x-y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle +x", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle +x+y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle +y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle -x+y", AnimationState({ animationControl }));

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 24.0f;
	animationControl.image = playerSprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	enemyAnimation->AddAnimationState("walking -x", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking -x-y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking -y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking +x-y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking +x", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking +x+y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking +y", AnimationState({ animationControl }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking -x+y", AnimationState({ animationControl }));

	// Create Objects.
	playerCharacter = Game::GetScene()->AddNode<PlayerCharacter>("Player");
	playerCharacter->SetPosition(Vector2F(100.0f, 100.0f));
	playerCharacter->speed = 500.0f;
	playerCharacter->acceleration = 5000.0f;
	playerCharacter->animator->animation = playerAnimation;
	playerCharacter->sprite->scale = Vector2F(3.0f, 3.0f);
	playerCharacter->colldier->size = Vector2F(50.0f, 50.0f);

	for (int i = 0; i < 5; i++)
	{
		PhysicsBody* obstacle1Body = Game::GetScene()->AddNode<PhysicsBody>("Obstacle");
		obstacle1Body->SetMass(10.0f);

		ColliderAxisBox* obstacle1 = obstacle1Body->AddChild<ColliderAxisBox>("Obstacle");
		obstacle1->size = Vector2F(100.0f, 100.0f);
		obstacle1->SetPosition(Vector2F(300.0f, 300.0f));

		Sprite* enemySprite = obstacle1->AddChild<Sprite>("Sprite");
		enemySprite->image = enemySprites;
		enemySprite->clipRect = RectI(0, 0, 32, 32);
		enemySprite->scale = Vector2F(3.0f, 3.0f);
	}

	enemyCharacter = Game::GetScene()->AddNode<EnemyCharacter>("Enemy");
	enemyCharacter->SetPosition(Vector2F(100.0f, 100.0f));
	enemyCharacter->speed = 500.0f;
	enemyCharacter->acceleration = 5000.0f;
	enemyCharacter->animator->animation = enemyAnimation;
	enemyCharacter->sprite->scale = Vector2F(3.0f, 3.0f);
	enemyCharacter->colldier->size = Vector2F(50.0f, 50.0f);
}

void BAE_Update()
{
	lastWalkInput = Vector2I(0, 0);

	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_W)) lastWalkInput.y++;
	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_S)) lastWalkInput.y--;
	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_A)) lastWalkInput.x--;
	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_D)) lastWalkInput.x++;

	playerCharacter->UpdateAnimation();
}

void BAE_LateUpdate()
{

}

void BAE_FixedUpdate()
{

}

void BAE_PhysicsUpdate()
{
	playerCharacter->MoveWithInput((Vector2F)lastWalkInput);
}

void BAE_End()
{
	delete playerAnimation;
	delete enemyAnimation;
	delete playerSprites;
	delete enemySprites;

	DEBUG_LOG_INFO("Bye");
}