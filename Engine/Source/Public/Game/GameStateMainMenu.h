#pragma once
#include "GameState.h"
#include "Button.h"

namespace bae
{
	class Text;
	struct Font;
}

class GameStateMainMenu : public GameState
{
public:
	bae::Font* titleFont;
	bae::Font* buttonFont;

	bae::Text* title;

	Button playButton;
	bae::Text* playText;
	Button optionsButton;
	bae::Text* optionsText;
	Button quitButton;
	bae::Text* quitText;

public:
	GameStateMainMenu(in<KeyType> key) noexcept :
		GameState::GameState(key),
		titleFont(nullptr),
		buttonFont(nullptr),
		title(nullptr),
		playButton(),
		playText(nullptr),
		optionsButton(),
		optionsText(nullptr),
		quitButton(),
		quitText(nullptr) { }

	virtual void OnStart(ParameterType machine) override;

	virtual void OnTick(ParameterType machine) override;

	virtual void OnEnd(ParameterType machine) override;
};