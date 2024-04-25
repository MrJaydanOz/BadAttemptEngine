#include "GameStateOptions.h"
#include "BAE/BAE_Game.h"
#include "Bae/BAE_Font.h"
#include "Bae/Nodes/BAE_Text.h"
#include "Bae/BAE_Debug.h"

void GameStateOptions::OnStart(ParameterType machine)
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
	title->text = "Options";

	option1Button.center = (screenSizef * 0.5f) + bae::Vector2F(0.0f, 32.0f);
	option1Button.size = bae::Vector2F(96.0f, 48.0f);
	option1Text = scene.AddNode<bae::Text>("Option1 Text");
	option1Text->offset = bae::PoseF(option1Button.center, 0.0f);
	option1Text->font = buttonFont;
	option1Text->isUI = true;
	option1Text->text = machine.b.yesState ? "Yes? : YES" : "Yes? : NO";

	backButton.center = (screenSizef * 0.5f) + bae::Vector2F(-64.0f, -96.0f);
	backButton.size = bae::Vector2F(96.0f, 48.0f);
	backText = scene.AddNode<bae::Text>("Back Text");
	backText->offset = bae::PoseF(backButton.center, 0.0f);
	backText->font = buttonFont;
	backText->isUI = true;
	backText->text = "Back";
}

void GameStateOptions::OnTick(ParameterType machine)
{
	bae::Graphics& graphics = *bae::Game::GetGraphics();
	bae::Input& input = *bae::Game::GetInput();

	bae::Vector2F mousePosition = (bae::Vector2F)input.GetMousePixel();
	mousePosition = graphics.PixelToScreenPoint(mousePosition);
	bool mouseClick = input.KeyHeld(bae::KeyCode::KEYCODE_LMB);

	if (input.KeyReleased(bae::KeyCode::KEYCODE_ESCAPE))
	{
		machine.a.QueueState("MainMenu");
		return;
	}

	switch (ProcessMenuButton(mousePosition, mouseClick, option1Button, option1Text))
	{
	case ButtonState::CLICKED:
		machine.b.yesState = !machine.b.yesState;
		option1Text->text = machine.b.yesState ? "Yes? : YES" : "Yes? : NO";
		break;
	}

	switch (ProcessMenuButton(mousePosition, mouseClick, backButton, backText))
	{
	case ButtonState::CLICKED:
		machine.a.QueueState("MainMenu");
		return;
	}
}

void GameStateOptions::OnEnd(ParameterType machine)
{
	delete titleFont;
	delete buttonFont;

	bae::Destroy(title);
	bae::Destroy(option1Text);
	bae::Destroy(backText);
}