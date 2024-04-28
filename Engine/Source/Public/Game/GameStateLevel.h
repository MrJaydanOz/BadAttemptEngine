#pragma once
#include "GameState.h"
#include "Button.h"
#include "Character.h"
#include "Projectiles.h"
#include "Collectables.h"
#include "Effect.h"

class GameStateDiedScreen : public GameState
{
public:
	bae::Font* titleFont;
	bae::Font* buttonFont;

	bae::Text* title;

	Button playButton;
	bae::Text* playText;
	Button quitButton;
	bae::Text* quitText;

public:
	GameStateDiedScreen(in<KeyType> key) noexcept :
		GameState::GameState(key),
		titleFont(nullptr),
		buttonFont(nullptr),
		title(nullptr),
		playButton(),
		playText(nullptr),
		quitButton(),
		quitText(nullptr) { }

	virtual void OnStart(ParameterType machine) override;

	virtual void OnTick(ParameterType machine) override;

	virtual void OnEnd(ParameterType machine) override;
};

class GameStateLevel : public GameState
{
	// This is the wrong way to use these states but time is ticking.

public:
	bae::Font* uIFont = nullptr;
	bae::Font* titleFont = nullptr;
	bae::Font* buttonFont = nullptr;

	bae::Text* scoreText = nullptr;

	bae::Text* pauseTitle = nullptr;

	Button pauseResumeButton = Button();
	bae::Text* pauseResumeText = nullptr;
	Button pauseExitButton = Button();
	bae::Text* pauseExitText = nullptr;

	bool isPaused = false;

	bae::Image* playerSprites = nullptr;
	bae::Image* basicEnemySprites = nullptr;
	bae::Image* rollingEnemySprites = nullptr;
	bae::Image* mortarEnemySprites = nullptr;
	bae::Image* playerBulletSprites = nullptr;
	bae::Image* basicEnemyBulletSprites = nullptr;
	bae::Image* collectableSprites = nullptr;

	bae::Image* playerShadows = nullptr;
	bae::Image* basicEnemyShadows = nullptr;
	bae::Image* rollingEnemyShadows = nullptr;
	bae::Image* mortarEnemyShadows = nullptr;

	bae::Animation* playerAnimation = nullptr;
	bae::Animation* basicEnemyAnimation = nullptr;
	bae::Animation* rollingEnemyAnimation = nullptr;
	bae::Animation* mortarEnemyAnimation = nullptr;
	bae::Animation* playerBulletAnimation = nullptr;
	bae::Animation* basicEnemyBulletAnimation = nullptr;
	bae::Animation* collectableAnimation = nullptr;

	PlayerCharacter* player = nullptr;
	bae::List<BasicBullet*> basicBullets = bae::List<BasicBullet*>();
	bae::List<Effect*> effects = bae::List<Effect*>();
	bae::List<EnemyCharacter*> enemies = bae::List<EnemyCharacter*>();
	bae::List<Collectable*> collectables = bae::List<Collectable*>();

	float enemySpawnRate = 0.3f;
	float enemySpawnTimer = 1.0f;
	float playerShootCooldown = 0.0f;
	float playerFireRate = 5.0f;
	int score = 0;
	float loseCountdown = 0.0f;

public:
	GameStateLevel(in<KeyType> key) noexcept :
		GameState::GameState(key) { }

	void CreateCollectable(in<bae::Vector2F> position);

	virtual void OnStart(ParameterType machine) override;

	virtual void OnTick(ParameterType machine) override;

	virtual void OnEnd(ParameterType machine) override;
};