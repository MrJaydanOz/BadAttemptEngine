#include "BAE_Input.h"
#include "BAE_Game.h"

namespace bae
{
	Input::Input() : 
		_isWorking(true),
		_previousKeyStates() { }

	Input::~Input()
	{

	}

	bool Input::KeyHeld(in<KeyCode> keyCode) const noexcept
	{
		// DUDE BRO MATE GUY PAL, BITMASK! BITMASK!!!!!!!!!

		switch (keyCode)
		{
		case KeyCode::KEYCODE_LMB:
			return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK) != 0u;
		case KeyCode::KEYCODE_RMB:
			return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_RMASK) != 0u;
		case KeyCode::KEYCODE_MMB:
			return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MMASK) != 0u;
		default:
			const unsigned char* keyStates = SDL_GetKeyboardState(nullptr);

			return (keyStates[(size_t)keyCode] & 1u) != 0u;
		}
	}

	bool Input::KeyPressed(in<KeyCode> keyCode) const noexcept
	{
		if (_previousKeyStates[(size_t)keyCode] != 0)
			return false; // Key was already pressed before so no point checking if pressed now.

		return KeyHeld(keyCode);
	}

	bool Input::KeyReleased(in<KeyCode> keyCode) const noexcept
	{
		if (_previousKeyStates[(size_t)keyCode] == 0)
			return false; // Key was already released before so no point checking if released now.

		return KeyHeld(keyCode);
	}

	Vector2I Input::GetMousePosition() const noexcept
	{
		Vector2I position = Vector2I(0, 0);

		SDL_GetMouseState(&position.x, &position.y);

		return position;
	}

	void Input::_ProcessInput()
	{
		{
			int keyCount = 0;
			const unsigned char* keyStates = SDL_GetKeyboardState(&keyCount);

			for (int i = 0; i < keyCount; i++)
				_previousKeyStates[i] = keyStates[i];

			unsigned int mouseStates = SDL_GetMouseState(nullptr, nullptr);

			_previousKeyStates[(size_t)KeyCode::KEYCODE_LMB] = (mouseStates & SDL_BUTTON_LMASK) != 0u;
			_previousKeyStates[(size_t)KeyCode::KEYCODE_RMB] = (mouseStates & SDL_BUTTON_RMASK) != 0u;
			_previousKeyStates[(size_t)KeyCode::KEYCODE_MMB] = (mouseStates & SDL_BUTTON_MMASK) != 0u;
		}

		SDL_Event inputEvent;

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
}