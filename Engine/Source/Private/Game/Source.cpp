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
	ColliderAxisBox* collider;
	float maxHealth;
	float health;

private:
	int _lastAnimationDirection;
	bool _lastIsWalking;
	float _hurtAnimationTimer;

public:
	virtual ~Character() noexcept override { PhysicsBody::~PhysicsBody(); }

	void UpdateAnimation()
	{
		if (_hurtAnimationTimer >= 0.0f)
		{
			const float notRed = Min(1.0f, _hurtAnimationTimer);

			//sprite->color = (Color)ColorF(1.0f, notRed, notRed);
			sprite->offset.rotation = 15.0f / ((20.0f * _hurtAnimationTimer) + 1);

			_hurtAnimationTimer += Game::GetTime()->DeltaTime();
		}

		Vector2F velocity = GetVelocity();

		if (velocity.SqrMagnitude() > 1.0f)
		{
			std::pair<uint8, Vector2F> pointsAroundAnimations[8]
			{
				{ 0, Vector2F(-1.0f    , +0.0f    ) },
				{ 1, Vector2F(-R_SQRT_2, -R_SQRT_2) },
				{ 2, Vector2F(+0.0f    , -1.0f    ) },
				{ 3, Vector2F(+R_SQRT_2, -R_SQRT_2) },
				{ 4, Vector2F(+1.0f    , +0.0f    ) },
				{ 5, Vector2F(+R_SQRT_2, +R_SQRT_2) },
				{ 6, Vector2F(+0.0f    , +1.0f    ) },
				{ 7, Vector2F(-R_SQRT_2, +R_SQRT_2) }
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

			if (!_lastIsWalking || _lastAnimationDirection != pointAroundAnimation.first)
			{
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

				_lastIsWalking = true;
			}
		}
		else
		{
			if (_lastIsWalking)
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

				_lastIsWalking = false;
			}
		}
	}

	void Damage(in<float> amount)
	{
		_hurtAnimationTimer = 0.0f;
		health -= amount;
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
		animator = AddChild<Animator>(std::string("Animator"));
		sprite = animator->AddChild<Sprite>(std::string("Sprite"));
		collider = AddChild<ColliderAxisBox>(std::string("Collider"));
		maxHealth = 100.0f;
		health = maxHealth;
		_lastAnimationDirection = 0;
		_lastIsWalking = false;
		_hurtAnimationTimer = -1.0f;
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

		MoveWithInput(deltaPosition);
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
std::deque<EnemyCharacter*> enemyCharacters;

Vector2I lastWalkInput;

Font* testFont;

bool isGameOver;

float spawnTimer = 3.0f;

void SpawnEnemy();

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
	playerAnimation->AddAnimationState("idle -x", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle -x-y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle -y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle +x-y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle +x", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle +x+y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle +y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("idle -x+y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 24.0f;
	animationControl.image = playerSprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	playerAnimation->AddAnimationState("walking -x", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking -x-y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking -y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking +x-y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking +x", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking +x+y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking +y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	playerAnimation->AddAnimationState("walking -x+y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));

	enemyAnimation = new Animation({});

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 8.0f;
	animationControl.image = enemySprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	enemyAnimation->AddAnimationState("idle -x", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle -x-y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle -y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle +x-y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle +x", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle +x+y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle +y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("idle -x+y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 24.0f;
	animationControl.image = enemySprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	enemyAnimation->AddAnimationState("walking -x", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking -x-y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking -y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking +x-y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking +x", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking +x+y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking +y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->AddAnimationState("walking -x+y", AnimationState({ new AnimationControlSpriteImage(animationControl) }));

	// Create Objects.
	playerCharacter = Game::GetScene()->AddNode<PlayerCharacter>(std::string("Player"));
	playerCharacter->SetPosition(Vector2F(100.0f, 100.0f));
	playerCharacter->speed = 300.0f;
	playerCharacter->acceleration = 5000.0f;
	playerCharacter->animator->animation = playerAnimation;
	playerCharacter->animator->Play("idle +y");
	playerCharacter->sprite->scale = Vector2F(3.0f, 3.0f);
	playerCharacter->collider->size = Vector2F(50.0f, 50.0f);
}

void BAE_Update()
{
	lastWalkInput = Vector2I(0, 0);

	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_W)) lastWalkInput.y++;
	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_S)) lastWalkInput.y--;
	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_A)) lastWalkInput.x--;
	if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_D)) lastWalkInput.x++;

	playerCharacter->UpdateAnimation();

	for (EnemyCharacter*& enemy : enemyCharacters)
	{
		enemy->UpdateAnimation();

		/*if (Game::GetInput()->KeyPressed(KeyCode::KEYCODE_LMB) && ((Vector2F)Game::GetInput()->GetMousePosition()).SqrDistance(enemy->GetPosition()) < 80.0f)
		{
			enemy->Damage(50.0f);
			if (enemy->health <= 0.0f)
				delete enemy;

			enemy = nullptr;
		}*/
	}

	std::erase_if(enemyCharacters, [](in<EnemyCharacter*> enemy) -> bool 
		{ return enemy == nullptr; });
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

	for (EnemyCharacter*& enemy : enemyCharacters)
	{
		enemy->MoveTowardsPlayer(playerCharacter);
	}

	spawnTimer -= Game::GetTime()->PhysicsDeltaTime();
	if (spawnTimer < 0.0f)
	{
		spawnTimer = 2.0f;

		SpawnEnemy();
	}
}

void BAE_End()
{
	delete playerAnimation;
	delete enemyAnimation;
	delete playerSprites;
	delete enemySprites;

	DEBUG_LOG_INFO("Bye");
}

void SpawnEnemy()
{
	EnemyCharacter* enemyCharacter = Game::GetScene()->AddNode<EnemyCharacter>(std::string("Enemy"));
	enemyCharacter->SetPosition(Vector2F(100.0f, 100.0f));
	enemyCharacter->speed = 200.0f;
	enemyCharacter->acceleration = 1000.0f;
	enemyCharacter->animator->animation = enemyAnimation;
	enemyCharacter->animator->Play("idle +y");
	enemyCharacter->sprite->scale = Vector2F(3.0f, 3.0f);
	enemyCharacter->collider->size = Vector2F(50.0f, 50.0f);

	enemyCharacters.push_back(enemyCharacter);
}