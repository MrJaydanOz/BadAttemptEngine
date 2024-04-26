#pragma once
#include "GameState.h"
#include "Button.h"
#include "Character.h"
#include "Projectiles.h"

class GameStateLevel : public GameState
{
public:
	bae::Font* uIFont = nullptr;

	bae::Image* playerSprites = nullptr;
	bae::Image* playerBulletSprites = nullptr;
	bae::Image* basicEnemyBulletSprites = nullptr;

	bae::Animation* playerAnimation = nullptr;
	bae::Animation* playerBulletAnimation = nullptr;

	PlayerCharacter* player = nullptr;
	bae::List<BasicBullet*> bullets = bae::List<BasicBullet*>();

public:
	GameStateLevel(in<KeyType> key) noexcept :
		GameState::GameState(key) { }

	virtual void OnStart(ParameterType machine) override;

	virtual void OnTick(ParameterType machine) override;

	virtual void OnEnd(ParameterType machine) override;
};