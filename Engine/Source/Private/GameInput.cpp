#include "GameInput.h"
#include "SDL2/SDL.h"
#include "Game.h"

void Input::ProcessInput()
{
	SDL_Event inputEvent;

	{
		int keyCount = 0;
		const unsigned char* keyStates = SDL_GetKeyboardState(&keyCount);

		for (int i = 0; i < keyCount; i++)
			_previousKeyStates[i] = keyStates[i];

		unsigned int mouseStates = SDL_GetMouseState(nullptr, nullptr);

		_previousKeyStates[KEYCODE_LMB] = (mouseStates & SDL_BUTTON_LMASK) != 0u;
		_previousKeyStates[KEYCODE_RMB] = (mouseStates & SDL_BUTTON_RMASK) != 0u;
		_previousKeyStates[KEYCODE_MMB] = (mouseStates & SDL_BUTTON_MMASK) != 0u;
	}

	while (SDL_PollEvent(&inputEvent) == 1)
	{
		switch (inputEvent.type)
		{
		case SDL_QUIT:
		{
			Game::GetGame()->Quit();
			break;
		}
		default:
			break;
		}
	}
}

bool Input::KeyHeld(KeyCode keyCode) const
{
	// DUDE BRO MATE GUY PAL, BITMASK! BITMASK!!!!!!!!!

	switch (keyCode)
	{
	case KEYCODE_LMB:
		return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK) != 0u;
	case KEYCODE_RMB:
		return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_RMASK) != 0u;
	case KEYCODE_MMB:
		return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MMASK) != 0u;
	default:
		const unsigned char* keyStates = SDL_GetKeyboardState(nullptr);

		return (keyStates[keyCode] & 1u) != 0u;
	}
}

bool Input::KeyPressed(KeyCode keyCode) const
{
	if (_previousKeyStates[keyCode] != 0)
		return false; // Key was already pressed before so no point checking if pressed now.

	return KeyHeld(keyCode);
}

bool Input::KeyReleased(KeyCode keyCode) const
{
	if (_previousKeyStates[keyCode] == 0)
		return false; // Key was already released before so no point checking if released now.

	return KeyHeld(keyCode);
}

Vector2I Input::MousePosition() const
{
	Vector2I position = Vector2I(0);

	SDL_GetMouseState(&position.x, &position.y);

	return position;
}

Input::Input()
{
	//_previousKeyStates = new unsigned char[KEYCODE_NUM_CODES];
}

Input::~Input()
{

}
