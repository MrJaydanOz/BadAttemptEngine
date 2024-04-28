#include "GameStateMainMenu.h"
#include "BAE/BAE_Game.h"
#include "BAE/BAE_Font.h"
#include "BAE/Nodes/BAE_Text.h"
#include "BAE/BAE_Debug.h"
#include "BAE/BAE_Math.h"

void GameStateSplashScreen::OnStart(ParameterType machine)
{
	bae::Vector2I screenSize = bae::Game::GetGraphics()->GetScreenSize();
	bae::Vector2F screenSizef = (bae::Vector2F)screenSize;

	bae::Scene& scene = *bae::Game::GetScene();

	titleFont = bae::Font::Load("Content/Fonts/Roboto/Roboto-Bold.ttf", 86);

	title = scene.AddNode<bae::Text>("Title");
	title->offset = bae::PoseF((screenSizef * 0.5f), 0.0f);
	title->font = titleFont;
	title->isUI = true;
	title->text = "Bad Attempt Engine";
}

void GameStateSplashScreen::OnTick(ParameterType machine)
{
	timer += bae::Game::GetTime()->UnscaledDeltaTime();

	float brightness = bae::Min(1.0f, timer, 3.0f - timer);

	title->color = (bae::Color)bae::ColorF(1.0f, 1.0f, 1.0f, brightness);
	title->scale = bae::Vector2F(1.0f, 1.0f) * (1.0f + (timer * 0.01f));

	if (timer > 3.0f)
		machine.a.QueueState("MainMenu");
}

void GameStateSplashScreen::OnEnd(ParameterType machine)
{
	delete titleFont;

	bae::Destroy(title);
}

void GameStateMainMenu::OnStart(ParameterType machine)
{
	bae::Vector2I screenSize = bae::Game::GetGraphics()->GetScreenSize();
	bae::Vector2F screenSizef = (bae::Vector2F)screenSize;

	bae::Scene& scene = *bae::Game::GetScene();

	titleFont = bae::Font::Load("Content/Fonts/Roboto/Roboto-Medium.ttf", 64);
	buttonFont = bae::Font::Load("Content/Fonts/Roboto/Roboto-Medium.ttf", 32);

	title = scene.AddNode<bae::Text>("Title");
	title->offset = bae::PoseF((screenSizef * 0.5f) + bae::Vector2F(0.0f, 128.0f), 0.0f);
	title->font = titleFont;
	title->isUI = true;
	title->text = "Pixel Blasters";

	playButton.center = (screenSizef * 0.5f) + bae::Vector2F(0.0f, 32.0f);
	playButton.size = bae::Vector2F(96.0f, 48.0f);
	playText = scene.AddNode<bae::Text>("Play Text");
	playText->offset = bae::PoseF(playButton.center, 0.0f);
	playText->font = buttonFont;
	playText->isUI = true;
	playText->text = "Play";

	optionsButton.center = (screenSizef * 0.5f) + bae::Vector2F(0.0f, -32.0f);
	optionsButton.size = bae::Vector2F(96.0f, 48.0f);
	optionsText = scene.AddNode<bae::Text>("Options Text");
	optionsText->offset = bae::PoseF(optionsButton.center, 0.0f);
	optionsText->font = buttonFont;
	optionsText->isUI = true;
	optionsText->text = "Options";

	quitButton.center = (screenSizef * 0.5f) + bae::Vector2F(0.0f, -96.0f);
	quitButton.size = bae::Vector2F(96.0f, 48.0f);
	quitText = scene.AddNode<bae::Text>("Quit Text");
	quitText->offset = bae::PoseF(quitButton.center, 0.0f);
	quitText->font = buttonFont;
	quitText->isUI = true;
	quitText->text = "Quit";
}

void GameStateMainMenu::OnTick(ParameterType machine)
{
	bae::Vector2F mousePosition = (bae::Vector2F)bae::Game::GetInput()->GetMousePixel();
	mousePosition = bae::Game::GetGraphics()->PixelToScreenPoint(mousePosition);
	bool mouseClick = bae::Game::GetInput()->KeyHeld(bae::KeyCode::KEYCODE_LMB);

	switch (ProcessMenuButton(mousePosition, mouseClick, playButton, playText))
	{
	case ButtonState::CLICKED:
		machine.a.QueueState("Game");
		return;
	}

	switch (ProcessMenuButton(mousePosition, mouseClick, optionsButton, optionsText))
	{
	case ButtonState::CLICKED:
		machine.a.QueueState("Options");
		return;
	}

	switch (ProcessMenuButton(mousePosition, mouseClick, quitButton, quitText))
	{
	case ButtonState::CLICKED:
		bae::Game::GetGame()->Quit();
		return;
	}
}

void GameStateMainMenu::OnEnd(ParameterType machine)
{
	delete titleFont;
	delete buttonFont;

	bae::Destroy(title);
	bae::Destroy(playText);
	bae::Destroy(optionsText);
	bae::Destroy(quitText);
}
