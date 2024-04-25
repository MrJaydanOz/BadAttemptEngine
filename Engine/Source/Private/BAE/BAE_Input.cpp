#include "BAE_Input.h"
#include "Math/BAE_VectorT.h"
#include "BAE_Game.h"
#include "Menus/BAE_WinMenu.h"
#include "SDL2/SDL_syswm.h"
#include "BAE_Resources.h"
#include "BAE_Engine.h"

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

	Vector2I Input::GetMousePixel() const noexcept
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
				case SDL_SYSWMEVENT:
				{
					_HandleWinMenuEvents(inputEvent);
					break;
				}
				default:
					break;
			}
		}
	}

	void Input::_HandleWinMenuEvents(in<SDL_Event> event)
	{
		switch (event.syswm.msg->msg.win.wParam)
		{
		case ID_FILE_EXITAPP:
			Game::GetGame()->Quit();
			break;
		case ID_FILE_RESTARTGAME:
			BAE_Restart();
			break;
		case ID_GAME_GAMECONTROLS:
			Game::GetWinMenu()->ActivatePopup("Game Controls",
				"WASD - Move Ship\n"
				"Left Mouse Button - Attack"
			);
			break;
		case ID_ABOUT_ABOUTBADATTEMPTENGINE:
			Game::GetWinMenu()->ActivatePopup("Bad Attempt Engine",
				"Once, there was a brilliant but reclusive programmer named Alexander Hargrove. He was a visionary in the field of game development, possessing a rare talent for crafting mediocre\n"
				"digital worlds. However, his life was marred by tragedy from an early age.\n\nAlexander grew up in a small town, where he was often bullied for his introverted nature and passion for\n"
				"computers. His only solace was in the world of video games, where he found refuge from the harsh realities of his daily life. Despite the challenges he faced, Alexander's love for\n"
				"gaming only grew stronger with time, and he dreamt of one day creating his own masterpiece.\n\nAs he grew older, Alexander dedicated himself to mastering the art of programming. He\n"
				"spent countless hours honing his skills, pouring his heart and soul into his work. Finally, after years of perseverance, he achieved his lifelong dream: he developed his own game\n"
				"engine, which he named the \"Bad Attempt Engine\".\n\nThe Bad Attempt Engine was meant to revolutionize the gaming industry, boasting basic graphics, simple physics, and\n"
				"paralleled immersion. Alexander poured every ounce of his being into perfecting his creation, believing it would be his ticket to recognition and success.\n\nHowever, tragedy struck\n"
				"when Alexander's beloved sister, Emily, fell gravely ill. Despite his best efforts to save her, Emily passed away, leaving Alexander shattered and consumed by grief. Devastated by\n"
				"the loss, he withdrew from the world, abandoning his dreams and isolating himself from everyone, including his friends and colleagues.\n\nIn his despair, Alexander became obsessed with\n"
				"his work, using the Bad Attempt Engine as a means of escape from his pain. He threw himself into its development with reckless abandon, pushing himself to the brink of exhaustion in\n"
				"a desperate attempt to fill the void left by his sister's absence.\n\nBut as Alexander's obsession grew, so too did the flaws in his creation. The Bad Attempt Engine, once heralded as\n"
				"quite good, began to crumble under the weight of his grief-fueled madness. Glitches and bugs plagued the system, rendering it unusable for all but the most basic of applications.\n\n"
				"Despite his best efforts to salvage his creation, Alexander's mental and emotional turmoil proved insurmountable. In the end, the Bad Attempt Engine was nothing more than a tragic\n"
				"reminder of what could have been. A testament to the fragility of dreams and the destructive power of grief.\n\nAnd so, Alexander Hargrove faded into obscurity, his genius overshadowed\n"
				"by the darkness that consumed him. The Bad Attempt Engine became little more than a cautionary tale, a warning to those who dared to tread the path of obsession at the expense of\n"
				"everything they held dear."
			);
			break;
		case ID_GAME_CHEATS_DOUBLETIMESCALE:
			Game::GetTime()->SetTimeScale(Game::GetTime()->GetTimeScale() * 2.0f);
			break;
		case ID_GAME_CHEATS_HALFTIMESCALE:
			Game::GetTime()->SetTimeScale(Game::GetTime()->GetTimeScale() * 0.5f);
			break;
		default:
			break;
		}
	}
}