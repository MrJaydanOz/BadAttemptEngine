#include "BAE_Game.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>
#include <chrono>
#include <thread>
#include "Nodes/BAE_Sprite.h"
#include "SDL2/SDL.h"
#include "BAE_Debug.h"
#include "BAE_Engine.h"

namespace bae
{
	Game* Game::GetGame() noexcept
	{
		static Game* gameSingleton = new Game();

		return gameSingleton;
	}

	Graphics* Game::GetGraphics() noexcept { return GetGame()->_graphics; }

	Scene* Game::GetScene() noexcept { return GetGame()->_scene; }
	
	Time* Game::GetTime() noexcept { return GetGame()->_time; }

	Physics* Game::GetPhysics() noexcept { return GetGame()->_physics; }

	Input* Game::GetInput() noexcept { return GetGame()->_input; }

	void Game::DestroyGame()
	{
		delete GetGame();
	}

	void Game::Run() 
	{ 
		if (!_isRunning)
		{
			Initialize();
		}
	}

	void Game::Quit()
	{
		_isRunning = false;
	}

	Game::Game() : 
		_graphics(nullptr),
		_scene(nullptr),
		_time(nullptr),
		_physics(nullptr),
		_input(nullptr),
		_isRunning(false)
	{
		DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game created.");
	}

	Game::~Game()
	{
		DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game destroyed.");
	}

	void Game::Initialize()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			DEBUG_LOG_SDL_ERROR("");
			return;
		}

		_graphics = new Graphics();
		if (!_graphics->_isWorking)
			return;

		_scene = new Scene();
		if (!_scene->_isWorking)
			return;

		_time = new Time();
		if (!_time->_isWorking)
			return;

		_physics = new Physics();
		if (!_physics->_isWorking)
			return;

		_input = new Input();
		if (!_input->_isWorking)
			return;

		_isRunning = true;

		DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game initialised.");

		Start();
	}

	void Game::Start()
	{
		BAE_Start();

		GameLoop();
	}

	void Game::GameLoop()
	{
		while (_isRunning)
		{
			_input->_ProcessInput();

			BAE_Update();

			bool useFixedTimeForPhysics = _time->GetUseFixedTimeForPhysics();

			while (_time->_IsFixedUpdateQueued())
			{
				if (useFixedTimeForPhysics)
				{
					_scene->_ClearWorldPositionCaches();
					_physics->_Simulate(_time->FixedDeltaTime());

					_scene->_ClearWorldPositionCaches();
					BAE_PhysicsUpdate();
				}

				BAE_FixedUpdate();
			}

			if (!useFixedTimeForPhysics)
			{
				_scene->_ClearWorldPositionCaches();
				_physics->_Simulate(_time->DeltaTime());

				_scene->_ClearWorldPositionCaches();
				BAE_PhysicsUpdate();
			}

			_scene->_ProcessAnimation();

			BAE_LateUpdate();

			_scene->_ClearWorldPositionCaches();
			_graphics->_Render();

			_time->_SleepUntilNextFrame();
		}

		Dispose();
	}

	void Game::Dispose()
	{
		BAE_End();

		SDL_Quit();

		DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game disposed.");
	}
}