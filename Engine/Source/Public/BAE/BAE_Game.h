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
#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Game))
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
		static Game* GetGame() noexcept;

		static Graphics* GetGraphics() noexcept;

		static Scene* GetScene() noexcept;

		static Time* GetTime() noexcept;

		static Physics* GetPhysics() noexcept;

		static Input* GetInput() noexcept;

		static void DestroyGame();

		void Run();

		void Quit();

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