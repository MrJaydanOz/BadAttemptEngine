#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Game.h"))
#endif
#include "BAE_Collections.h"
#include "BAE_Graphics.h"
#include "BAE_Scene.h"
#include "BAE_Time.h"
#include "BAE_Physics.h"
#include "BAE_Input.h"

namespace bae
{
#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Game))
#endif
	class Game
	{
	private:
		bool _isRunning;
		Graphics* _graphics;
		Scene* _scene;
		Time* _time;
		Physics* _physics;
		Input* _input;

	public:
		_NODISCARD static Game* GetGame() noexcept;

		_NODISCARD static Graphics* GetGraphics() noexcept;

		_NODISCARD static Scene* GetScene() noexcept;

		_NODISCARD static Time* GetTime() noexcept;

		_NODISCARD static Physics* GetPhysics() noexcept;

		_NODISCARD static Input* GetInput() noexcept;

		_NODISCARD static WinMenu* GetWinMenu() noexcept;

		static void DestroyGame();

		void Run();

		void Quit();

		// Makes no sense but ok? Though maybe to readjust some driver settings?
		void Restart();

	private:
		Game();
		~Game();

		/*
		┏[Setup]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
		┃  Initialise core and external functionality.          ┃
		┃  */void Initialize();/*                               ┃
		┃                                                       ┃
		┃  Initialise internal functionality and load assets.   ┃
		┃  */void Start();/*                                    ┃
		┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
									↓
		┏[Loop]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ <─┐
		┃  Process game functionality for one frame.            ┃   │
		┃  */void GameLoop();/*                                 ┃   │
		┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ──┘
									↓
		┏[Exit]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
		┃  Deallocate all memory associated with the game.      ┃
		┃  */void Dispose();/*                                  ┃
		┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
		*/
	};
}