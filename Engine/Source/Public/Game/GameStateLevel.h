#pragma once
#include "GameState.h"
#include "Button.h"
#include "Character.h"
#include "Projectiles.h"
#include "Effect.h"

class GameStateLevel : public GameState
{
public:
	bae::Font* uIFont = nullptr;

	bae::Image* playerSprites = nullptr;
	bae::Image* basicEnemySprites = nullptr;
	bae::Image* rollingEnemySprites = nullptr;
	bae::Image* mortarEnemySprites = nullptr;
	bae::Image* playerBulletSprites = nullptr;
	bae::Image* basicEnemyBulletSprites = nullptr;

	bae::Animation* playerAnimation = nullptr;
	bae::Animation* basicEnemyAnimation = nullptr;
	bae::Animation* rollingEnemyAnimation = nullptr;
	bae::Animation* mortarEnemyAnimation = nullptr;
	bae::Animation* playerBulletAnimation = nullptr;
	bae::Animation* basicEnemyBulletAnimation = nullptr;

	PlayerCharacter* player = nullptr;
	bae::List<BasicBullet*> basicBullets = bae::List<BasicBullet*>();
	bae::List<Effect*> effects = bae::List<Effect*>();
	bae::List<EnemyCharacter*> enemies = bae::List<EnemyCharacter*>();

	float enemySpawnRate = 0.5f;
	float enemySpawnTimer = 1.0f;

public:
	GameStateLevel(in<KeyType> key) noexcept :
		GameState::GameState(key) { }

	virtual void OnStart(ParameterType machine) override;

	virtual void OnTick(ParameterType machine) override;

	virtual void OnEnd(ParameterType machine) override;
};