#include "GameState.h"

ButtonState GameState::ProcessMenuButton(in<bae::Vector2F> mousePosition, in<bool> mouseClicking, ref<Button> button, in<bae::Text*> text)
{
	ButtonState state = button.Test(mousePosition, mouseClicking);

	switch (state)
	{
	case ButtonState::RELEASED:
	case ButtonState::NONE:
		text->color = 0xFFFFFFFFu;
		text->scale = bae::Vector2F(1.0f, 1.0f);
		break;
	case ButtonState::HOVERING:
		text->color = 0xFFFF00FFu;
		text->scale = bae::Vector2F(1.1f, 1.1f);
		break;
	case ButtonState::CLICKED:
	case ButtonState::PRESSED:
	case ButtonState::HELD:
		text->color = 0x00FF00FFu;
		text->scale = bae::Vector2F(1.0f, 1.0f);
		break;
	}

	return state;
}