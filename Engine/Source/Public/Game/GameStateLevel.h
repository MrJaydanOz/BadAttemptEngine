#pragma once
#include "GameState.h"
#include "Button.h"
#include "Character.h"

class GameStateLevel : public GameState
{
public:
	bae::Font* uIFont = nullptr;

	bae::Image* playerSprites = nullptr;
	bae::Animation* playerAnimation = nullptr;
	PlayerCharacter* player = nullptr;

public:
	GameStateLevel(in<KeyType> key) noexcept :
		GameState::GameState(key) { }

	virtual void OnStart(ParameterType machine) override;

	virtual void OnTick(ParameterType machine) override;

	virtual void OnEnd(ParameterType machine) override;
};