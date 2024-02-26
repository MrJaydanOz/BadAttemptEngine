#include "Input.h"
#include "SDL2/SDL.h"
#include "Game.h"

void Input::ProcessInput() const
{
	SDL_Event inputEvent;

	while (SDL_PollEvent(&inputEvent))
	{
		switch (inputEvent.type)
		{
		case SDL_MOUSEBUTTONDOWN:
		{
			switch (inputEvent.button.button)
			{
			case SDL_BUTTON_LEFT:
				_mouseStates[KEYCODE_LMB - KEYCODE_LMB] = 1u;
				break;
			case SDL_BUTTON_MIDDLE:
				_mouseStates[KEYCODE_MMB - KEYCODE_LMB] = 1u;
				break;
			case SDL_BUTTON_RIGHT:
				_mouseStates[KEYCODE_RMB - KEYCODE_LMB] = 1u;
				break;
			default:
				break;
			};
		}
		case SDL_QUIT:
		{
			Game::GetGame()->Quit();
		}
		default:
			break;
		}
	}
}

bool Input::KeyHeld(KeyCode keyCode) const
{
	switch (keyCode)
	{
	case KEYCODE_LMB || KEYCODE_RMB || KEYCODE_MMB:
		return _mouseStates[keyCode - KEYCODE_LMB] != 0u;
	default:
		const unsigned char* keyStates = SDL_GetKeyboardState(nullptr);

		return (keyStates[keyCode] & 1u) != 0u;
	}
}

Vector2I Input::MousePosition() const
{
	Vector2I position = Vector2I(0);

	SDL_GetMouseState(&position.x, &position.y);

	return position;
}
