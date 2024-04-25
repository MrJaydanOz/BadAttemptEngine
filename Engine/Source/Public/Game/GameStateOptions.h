#pragma once
#include "GameState.h"
#include "Button.h"

namespace bae
{
	class Text;
	struct Font;
}

class GameStateOptions : public GameState
{
public:
	bae::Font* titleFont;
	bae::Font* buttonFont;

	bae::Text* title;

	Button option1Button;
	bae::Text* option1Text;
	Button backButton;
	bae::Text* backText;

public:
	GameStateOptions(in<KeyType> key) noexcept :
		GameState::GameState(key),
		titleFont(nullptr),
		buttonFont(nullptr),
		title(nullptr),
		option1Button(),
		option1Text(nullptr),
		backButton(),
		backText(nullptr) { }

	virtual void OnStart(ParameterType machine) override;

	virtual void OnTick(ParameterType machine) override;

	virtual void OnEnd(ParameterType machine) override;
};