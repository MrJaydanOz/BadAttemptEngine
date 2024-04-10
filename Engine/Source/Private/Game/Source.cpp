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
	void UpdateAnimation()
	{
		if (_hurtAnimationTimer >= 0.0f)
		{
			const float notRed = Min(1.0f, _hurtAnimationTimer);

			sprite->color = (Color)ColorF(1.0f, notRed, notRed);
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

		SetVelocity(MoveTowards(GetVelocity(), scaledInput * speed, acceleration * Game::GetTime()->DeltaTime()));
	}

protected:
	Character(in<Node*> parent) noexcept : PhysicsBody::PhysicsBody(parent),
		speed(0.0f),
		acceleration(0.0f),
		animator(nullptr),
		sprite(nullptr),
		collider(nullptr),
		maxHealth(100.0f),
		health(maxHealth),
		_lastAnimationDirection(0),
		_lastIsWalking(false),
		_hurtAnimationTimer(1.0f) { }
	virtual ~Character() noexcept override { }
	virtual void Create(in<const char*> name = "") override
	{
		PhysicsBody::Create(name);

		animator = AddChild<Animator>("Animator");
		sprite = animator->AddChild<Sprite>("Sprite");
		collider = AddChild<ColliderAxisBox>("Collider");
	}
};

class PlayerCharacter : public Character
{
	NODE_BEGIN;

public:

protected:
	PlayerCharacter(in<Node*> parent) noexcept : Character::Character(parent) { }
	virtual ~PlayerCharacter() noexcept override { }
};

class EnemyCharacter : public Character
{
	NODE_BEGIN;

public:
	void MoveTowardsPlayer(in<PlayerCharacter*> player)
	{
		Vector2F deltaPosition = player->GetPosition() - GetPosition();

		MoveWithInput(deltaPosition);
	}

	void Die(ref<float> globalScore)
	{
		globalScore += 500.0f;
	}

protected:
	EnemyCharacter(in<Node*> parent) noexcept : Character::Character(parent) { }
	virtual ~EnemyCharacter() noexcept override { }
};

class Collectable : public PhysicsBody
{
	NODE_BEGIN;

public:
	Animator* animator;
	Sprite* sprite;
	ColliderAxisBox* collider;
	float value;

public:
	virtual ~Collectable() noexcept override { }

	void Collect(ref<float> globalScore)
	{
		globalScore += value;
	}

protected:
	Collectable(in<Node*> parent) noexcept : PhysicsBody::PhysicsBody(parent)
	{
		value = 100.0f;
		animator = AddChild<Animator>("Animator");
		sprite = animator->AddChild<Sprite>("Sprite");
		collider = AddChild<ColliderAxisBox>("Collider");
	}
};

Image* playerSprites;
Image* enemySprites;
Image* collectableSprites;
Animation* playerAnimation;
Animation* enemyAnimation;
Animation* collectableAnimation;
PlayerCharacter* playerCharacter;
bae::List<EnemyCharacter*> enemyCharacters;
bae::List<Collectable*> collectables;

Vector2I lastWalkInput;

Font* testFont;

bool isGameOver;

float spawnTimer = 3.0f;

float globalScore = 0.0f;

void SpawnEnemy();
void SpawnCollectable(in<Vector2F> position);

void BAE_Start()
{
	// Load images.
	playerSprites = Image::Load("Content/Sprites/PlayerSprites.png");
	enemySprites = Image::Load("Content/Sprites/EnemySprites.png");
	collectableSprites = Image::Load("Content/Sprites/Cube4.png");
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
	playerAnimation->CreateAnimationState("idle -x", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("idle -x-y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("idle -y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("idle +x-y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("idle +x", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("idle +x+y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("idle +y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("idle -x+y", { new AnimationControlSpriteImage(animationControl) });

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 24.0f;
	animationControl.image = playerSprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	playerAnimation->CreateAnimationState("walking -x", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("walking -x-y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("walking -y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("walking +x-y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("walking +x", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("walking +x+y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("walking +y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	playerAnimation->CreateAnimationState("walking -x+y", { new AnimationControlSpriteImage(animationControl) });

	enemyAnimation = new Animation({});

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 8.0f;
	animationControl.image = enemySprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	enemyAnimation->CreateAnimationState("idle -x", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("idle -x-y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("idle -y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("idle +x-y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("idle +x", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("idle +x+y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("idle +y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("idle -x+y", { new AnimationControlSpriteImage(animationControl) });

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 12;
	animationControl.frameRate = 24.0f;
	animationControl.image = enemySprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	enemyAnimation->CreateAnimationState("walking -x", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("walking -x-y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("walking -y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("walking +x-y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("walking +x", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("walking +x+y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("walking +y", { new AnimationControlSpriteImage(animationControl) });
	animationControl.clipStartPosition.y += 32;
	enemyAnimation->CreateAnimationState("walking -x+y", { new AnimationControlSpriteImage(animationControl) });

	collectableAnimation = new Animation({});

	animationControl.clipSize = Vector2I(16, 16);
	animationControl.frameCount = 10;
	animationControl.frameRate = 12.0f;
	animationControl.image = collectableSprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	collectableAnimation->CreateAnimationState("spin", { new AnimationControlSpriteImage(animationControl) });

	// Create Objects.
	playerCharacter = Game::GetScene()->AddNode<PlayerCharacter>("Player");
	playerCharacter->SetPosition(Vector2F(100.0f, 100.0f));
	playerCharacter->speed = 500.0f;
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

	Vector2F mousePosition = (Vector2F)Game::GetInput()->GetMousePosition();
	mousePosition.y = Game::GetGraphics()->GetScreenSize().y - mousePosition.y;

	for (EnemyCharacter*& enemy : enemyCharacters)
	{
		enemy->UpdateAnimation();

		if (Game::GetInput()->KeyPressed(KeyCode::KEYCODE_LMB) && mousePosition.SqrDistance(enemy->GetPosition()) < 80.0f * 80.0f)
		{
			enemy->Damage(50.0f);
			if (enemy->health <= 0.0f)
			{
				//SpawnCollectable(enemy->GetPosition());
				//SpawnCollectable(enemy->GetPosition());
				//SpawnCollectable(enemy->GetPosition());

				enemy->Die(globalScore);
				Destroy(enemy);
				enemy = nullptr;
			}
		}
	}

	enemyCharacters.RemoveWhere([](in<EnemyCharacter*> enemy) -> bool 
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

	if (!isGameOver && Game::GetPhysics()->CollisionExistsWithWhere(playerCharacter, [](in<PhysicsCollision> collision) -> bool
		{ return collision.physicsBody2 != nullptr && collision.physicsBody2->NameIs("Enemy"); }))
	{
		playerCharacter->Damage(0.0f);

		Transform* textHolder = Game::GetScene()->AddNode<Transform>("Game Over Text");
		textHolder->SetPosition(((Vector2F)Game::GetGraphics()->GetScreenSize()) * 0.5f);

		Text* text = textHolder->AddChild<Text>("Game Over Text");
		text->font = testFont;
		text->color = COLOR_YELLOW;
		text->textAlignment = TextHorizonalAlignment::TEXT_ALIGNMENT_CENTER;
		text->text = "Game Over";
		text->SetZIndex(100);

		isGameOver = true;

		Game::GetTime()->SetTimeScale(0.2f);
	}

	for (Collectable*& collectable : collectables)
	{
		if (Game::GetPhysics()->CollisionExistsWithWhere(collectable, [&](in<PhysicsCollision> collision) -> bool
			{ return collision.physicsBody2 == playerCharacter; }))
		{
			collectable->Collect(globalScore);
			Destroy(collectable);
			collectable = nullptr;
		}
	}

	collectables.RemoveWhere([](in<Collectable*> collectable) -> bool
		{ return collectable == nullptr; });
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
	EnemyCharacter* enemyCharacter = Game::GetScene()->AddNode<EnemyCharacter>("Enemy");
	enemyCharacter->SetPosition(Vector2F(100.0f, 100.0f));
	enemyCharacter->speed = 200.0f;
	enemyCharacter->acceleration = 1000.0f;
	enemyCharacter->animator->animation = enemyAnimation;
	enemyCharacter->animator->Play("idle +y");
	enemyCharacter->sprite->scale = Vector2F(3.0f, 3.0f);
	enemyCharacter->collider->size = Vector2F(50.0f, 50.0f);

	enemyCharacters.Append(enemyCharacter);
}

void SpawnCollectable(in<Vector2F> position)
{
	Collectable* collectable = Game::GetScene()->AddNode<Collectable>("Collectable");
	collectable->SetPosition(position);
	collectable->value = 100.0f;
	collectable->SetMass(0.01f);
	collectable->SetDrag(0.05f);
	collectable->SetVelocity(Vector2F(Lerp(-1.0f, 1.0f, std::rand() / (float)RAND_MAX), Lerp(-1.0f, 1.0f, std::rand() / (float)RAND_MAX)) * 100.0f);
	collectable->animator->animation = collectableAnimation;
	collectable->animator->Play("spin");
	collectable->sprite->scale = Vector2F(2.0f, 2.0f);
	collectable->collider->size = Vector2F(10.0f, 10.0f);

	collectables.Append(collectable);
}