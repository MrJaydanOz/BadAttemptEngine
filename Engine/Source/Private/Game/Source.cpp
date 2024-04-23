#include "BAE/BAE_Engine.h"
#include "BAE/Nodes/BAE_Animator.h"

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
			float angle = ATan2(velocity.y, velocity.x) + (DEG_TO_RAD * 180.0f);
			int direction = Mod(RoundI(angle * RAD_TO_TURN * 16.0f), 16);

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
Text* scoreDisplay;
Text* helpDisplay;

Vector2I lastWalkInput;

Font* largeFont;
Font* smallFont;

bool isGameOver;

float spawnTimer = 3.0f;

float globalScore = 0.0f;

void SpawnEnemy();
void SpawnCollectable(in<Vector2F> position);
void Restart();

void BAE_Start()
{
	// Load images.
	playerSprites = Image::Load("Content/Sprites/PlayerSprites.png");
	enemySprites = Image::Load("Content/Sprites/BasicEnemySprites.png");
	collectableSprites = Image::Load("Content/Sprites/Cube4.png");
	largeFont = Font::Load("Content/Fonts/Roboto/Roboto-Medium.ttf", 64);
	smallFont = Font::Load("Content/Fonts/Roboto/Roboto-Medium.ttf", 24);

	// Load animations.
	playerAnimation = new Animation({});

	using CreateStateT = in_initializer_list<AnimationControl*>;

	// Path to node from Animator node.
	auto animationControl = AnimationControlSpriteImage({ "Sprite" });
	// AnimationControl settings.
	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 8;
	animationControl.frameRate = 8.0f;
	animationControl.image = playerSprites;
	// Add an AnimationState with the AnimationControl in it.
	animationControl.clipStartPosition = Vector2I(0, 0);
	LOOP(i, 16)
	{
		playerAnimation->CreateState<CreateStateT>("idle r" + std::to_string(i), {new AnimationControlSpriteImage(animationControl)});
		animationControl.clipStartPosition.y += 32;
	}

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 8;
	animationControl.frameRate = 24.0f;
	animationControl.image = playerSprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	LOOP(i, 16)
	{
		playerAnimation->CreateState<CreateStateT>("walking r" + std::to_string(i), { new AnimationControlSpriteImage(animationControl) });
		animationControl.clipStartPosition.y += 32;
	}

	enemyAnimation = new Animation({});

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 8;
	animationControl.frameRate = 8.0f;
	animationControl.image = enemySprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	LOOP(i, 16)
	{
		enemyAnimation->CreateState<CreateStateT>("idle r" + std::to_string(i), { new AnimationControlSpriteImage(animationControl) });
		animationControl.clipStartPosition.y += 32;
	}

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 8;
	animationControl.frameRate = 24.0f;
	animationControl.image = enemySprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	LOOP(i, 16)
	{
		enemyAnimation->CreateState<CreateStateT>("walking r" + std::to_string(i), { new AnimationControlSpriteImage(animationControl) });
		animationControl.clipStartPosition.y += 32;
	}

	collectableAnimation = new Animation({});

	animationControl.clipSize = Vector2I(32, 32);
	animationControl.frameCount = 10;
	animationControl.frameRate = 12.0f;
	animationControl.image = collectableSprites;
	animationControl.clipStartPosition = Vector2I(0, 0);
	collectableAnimation->CreateState<CreateStateT>("spin", { new AnimationControlSpriteImage(animationControl) });

	// Create Objects.

	Transform* scoreDisplayHolder = Game::GetScene()->AddNode<Transform>("Score Display Holder");
	scoreDisplayHolder->SetPosition(((Vector2F)Game::GetGraphics()->GetScreenSize()) - Vector2F(20.0f, 50.0f));
	scoreDisplay = scoreDisplayHolder->AddChild<Text>("Score Display");
	scoreDisplay->text = "0";
	scoreDisplay->pivot = Vector2F(1.0f, 1.0f);
	scoreDisplay->font = smallFont;
	scoreDisplay->SetZIndex(100);

	Transform* infoDisplayHolder = Game::GetScene()->AddNode<Transform>("Info Display Holder");
	infoDisplayHolder->SetPosition(((Vector2F)Game::GetGraphics()->GetScreenSize()) - Vector2F(20.0f, 20.0f));
	Text* infoDisplay = infoDisplayHolder->AddChild<Text>("Info Display");
	infoDisplay->text = "Click on the enemies to damage them and collect the cubies.";
	infoDisplay->pivot = Vector2F(1.0f, 1.0f);
	infoDisplay->font = smallFont;
	infoDisplay->SetZIndex(100);

	Restart();
}

void BAE_Update()
{
	lastWalkInput = Vector2I(0, 0);

	if (!isGameOver)
	{
		if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_W)) lastWalkInput.y++;
		if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_S)) lastWalkInput.y--;
		if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_A)) lastWalkInput.x--;
		if (Game::GetInput()->KeyHeld(KeyCode::KEYCODE_D)) lastWalkInput.x++;
	}

	playerCharacter->UpdateAnimation();

	Vector2F mousePosition = (Vector2F)Game::GetInput()->GetMousePosition();
	mousePosition.y = Game::GetGraphics()->GetScreenSize().y - mousePosition.y;

	if (!isGameOver)
	{
		for (EnemyCharacter*& enemy : enemyCharacters)
		{
			enemy->UpdateAnimation();

			if (Game::GetInput()->KeyPressed(KeyCode::KEYCODE_LMB) && mousePosition.SqrDistance(enemy->GetPosition()) < 40.0f * 40.0f)
			{
				enemy->Damage(40.0f);
				if (enemy->health <= 0.0f)
				{
					SpawnCollectable(enemy->GetPosition());
					SpawnCollectable(enemy->GetPosition());
					SpawnCollectable(enemy->GetPosition());

					enemy->Die(globalScore);
					Destroy(enemy);
					enemy = nullptr;
				}
			}
		}

		enemyCharacters.RemoveWhere([](in<EnemyCharacter*> enemy) -> bool
			{ return enemy == nullptr; });
	}
	else
	{
		if (Game::GetInput()->KeyPressed(KeyCode::KEYCODE_LMB))
		{
			Restart();
		}
	}
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
		text->font = largeFont;
		text->color = COLOR_YELLOW;
		text->textAlignment = TextHorizonalAlignment::TEXT_ALIGNMENT_CENTER;
		text->text = "Game Over";
		text->SetZIndex(100);

		isGameOver = true;

		Game::GetTime()->SetTimeScale(0.2f);
	}

	if (!isGameOver)
	{
		bool hasScoreChanged = false;

		for (Collectable*& collectable : collectables)
		{
			if (Game::GetPhysics()->CollisionExistsWithWhere(collectable, [&](in<PhysicsCollision> collision) -> bool
				{ return collision.physicsBody2 == playerCharacter; }))
			{
				collectable->Collect(globalScore);
				Destroy(collectable);
				collectable = nullptr;

				hasScoreChanged = true;
			}
		}

		collectables.RemoveWhere([](in<Collectable*> collectable) -> bool
			{ return collectable == nullptr; });

		scoreDisplay->text = std::to_string((int)globalScore);
	}
}

void BAE_Restart()
{
	Restart();
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
	enemyCharacter->animator->SetAnimation(enemyAnimation);
	enemyCharacter->animator->Play("idle r0");
	enemyCharacter->sprite->scale = Vector2F(3.0f, 3.0f);
	enemyCharacter->collider->size = Vector2F(40.0f, 40.0f);

	enemyCharacters.Append(enemyCharacter);
}

void SpawnCollectable(in<Vector2F> position)
{
	Collectable* collectable = Game::GetScene()->AddNode<Collectable>("Collectable");
	collectable->SetPosition(position);
	collectable->value = 100.0f;
	collectable->SetMass(0.01f);
	collectable->SetDrag(0.05f);
	collectable->SetVelocity(Vector2F(Lerp(-1.0f, 1.0f, std::rand() / (float)RAND_MAX), Lerp(-1.0f, 1.0f, std::rand() / (float)RAND_MAX)) * 200.0f);
	collectable->animator->SetAnimation(collectableAnimation);
	collectable->animator->Play("spin");
	collectable->sprite->scale = Vector2F(1.0f, 1.0f);
	collectable->collider->size = Vector2F(10.0f, 10.0f);
	collectable->sprite->SetZIndex(-10);

	collectables.Append(collectable);
}

void Restart()
{
	Destroy(playerCharacter);

	for (Collectable*& collectable : collectables)
		Destroy(collectable);
	collectables.Clear();

	for (EnemyCharacter*& enemy : enemyCharacters)
		Destroy(enemy);
	enemyCharacters.Clear();

	Text* gameOverText = Game::GetScene()->FindNodeWithName<Text>("Game Over Text");
	Destroy(gameOverText);
	Game::GetTime()->SetTimeScale(1.0f);
	isGameOver = false;
	globalScore = 0.0f;
	spawnTimer = 3.0f;

	playerCharacter = Game::GetScene()->AddNode<PlayerCharacter>("Player");
	playerCharacter->SetPosition(Vector2F(100.0f, 100.0f));
	playerCharacter->speed = 500.0f;
	playerCharacter->acceleration = 5000.0f;
	playerCharacter->animator->SetAnimation(playerAnimation);
	playerCharacter->animator->Play("idle r0");
	playerCharacter->sprite->scale = Vector2F(3.0f, 3.0f);
	playerCharacter->collider->size = Vector2F(40.0f, 40.0f);
}