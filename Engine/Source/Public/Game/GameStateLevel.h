#pragma once
#include "GameState.h"
#include "Button.h"

class GameStateLevel : public GameState
{
public:
	bae::Font* uIFont;



public:
	GameStateLevel(in<KeyType> key) noexcept :
		GameState::GameState(key),
		uIFont(nullptr) { }

	virtual void OnStart(ParameterType machine) override;

	virtual void OnTick(ParameterType machine) override;

	virtual void OnEnd(ParameterType machine) override;
};