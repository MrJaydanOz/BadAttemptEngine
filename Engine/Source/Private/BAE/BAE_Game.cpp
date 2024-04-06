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

	Physics* Game::GetPhysics() noexcept { return GetGame()->_physics; }

	Input* Game::GetInput() noexcept { return GetGame()->_input; }

	void Game::DestroyGame()
	{
		delete GetGame();
	}

	void Game::Run() { Initialize(); }

	void Game::Quit()
	{
		_isRunning = false;
	}

	Game::Game() : 
		_graphics(nullptr),
		_scene(nullptr),
		_physics(nullptr),
		_input(nullptr),
		_isRunning(true)
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

		_physics = new Physics();
		if (!_physics->_isWorking)
			return;

		_input = new Input();
		if (!_input->_isWorking)
			return;

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
		const float framesPerSecond = 60.0f;
		const unsigned long millisecondsPerFrame = std::lroundf(1000.0f / framesPerSecond);

		while (_isRunning)
		{
			auto nextFrameTime = std::chrono::system_clock::now() + std::chrono::milliseconds(millisecondsPerFrame);

			ProcessInput();

			BAE_Update();

			Update();

			BAE_LateUpdate();

			_graphics->Render();

			_scene->ClearWorldPositionCaches();

			std::this_thread::sleep_until(nextFrameTime);
		}

		Dispose();
	}

	void Game::ProcessInput()
	{
		SDL_Event inputEvent;

		while (SDL_PollEvent(&inputEvent))
		{
			if (inputEvent.type == SDL_QUIT)
			{
				Quit();
			}
		}
	}

	void Game::Update()
	{
	}

	void Game::Render()
	{
		/*SDL_SetRenderDrawColor(_rendererReference, 0x00, 0x00, 0x00, 0xFF);

		SDL_RenderClear(_rendererReference);

		SDL_Rect rectS = SDL_Rect();
		SDL_FRect rectD = SDL_FRect();

		// SDL_Rect why no constructer wtf?

		const float framesPerSecond = 12.0f;
		const unsigned long millisecondsPerFrame = std::lroundf(1000.0f / framesPerSecond);

		unsigned long time = SDL_GetTicks64();

		// We're graphics before functionality. But I'm not so here's some spaghetti.
		// Btw the sprites are made in my little sprite sheet generator I made in Unity during off time.

		rectS.x = (int)((time / millisecondsPerFrame) % 12) * 32;
		rectS.y = 0;
		rectS.w = 32;
		rectS.h = 32;

		rectD.x = 50.0f;
		rectD.y = 50.0f;
		rectD.w = (float)rectS.w * 3.0f;
		rectD.h = (float)rectS.h * 3.0f;

		if (SDL_RenderCopyF(_rendererReference, _cube1Texture, &rectS, &rectD) < 0)
			DEBUG_LOG_SDL_ERROR("");

		rectS.x = (int)((time / millisecondsPerFrame) % 10) * 32;
		rectS.y = 0;
		rectS.w = 32;
		rectS.h = 32;

		rectD.x = 200.0f;
		rectD.y = 50.0f;
		rectD.w = (float)rectS.w * 3.0f;
		rectD.h = (float)rectS.h * 3.0f;

		if (SDL_RenderCopyF(_rendererReference, _cube2Texture, &rectS, &rectD) < 0)
			DEBUG_LOG_SDL_ERROR("");

		rectS.x = (int)((time / millisecondsPerFrame) % 20) * 32;
		rectS.y = 0;
		rectS.w = 32;
		rectS.h = 32;

		rectD.x = 350.0f;
		rectD.y = 50.0f;
		rectD.w = (float)rectS.w * 3.0f;
		rectD.h = (float)rectS.h * 3.0f;

		if (SDL_RenderCopyF(_rendererReference, _cube3Texture, &rectS, &rectD) < 0)
			DEBUG_LOG_SDL_ERROR("");

		rectS.x = (int)((time / millisecondsPerFrame) % 10) * 32;
		rectS.y = 0;
		rectS.w = 32;
		rectS.h = 32;

		rectD.x = 500.0f;
		rectD.y = 50.0f;
		rectD.w = (float)rectS.w * 3.0f;
		rectD.h = (float)rectS.h * 3.0f;

		if (SDL_RenderCopyF(_rendererReference, _cube4Texture, &rectS, &rectD) < 0)
			DEBUG_LOG_SDL_ERROR("");

		rectS.x = (int)((time / millisecondsPerFrame) % 12) * 32;
		rectS.y = 0;
		rectS.w = 32;
		rectS.h = 32;

		rectD.x = 650.0f;
		rectD.y = 50.0f;
		rectD.w = (float)rectS.w * 3.0f;
		rectD.h = (float)rectS.h * 3.0f;

		if (SDL_RenderCopyF(_rendererReference, _cube5Texture, &rectS, &rectD) < 0)
			DEBUG_LOG_SDL_ERROR("");

		SDL_RenderPresent(_rendererReference);

		rectS.x = (int)((time / millisecondsPerFrame) % 40) * 192;
		rectS.y = 0;
		rectS.w = 192;
		rectS.h = 192;

		rectD.x = 50.0f;
		rectD.y = 200.0f;
		rectD.w = (float)rectS.w * 3.0f;
		rectD.h = (float)rectS.h * 3.0f;

		if (SDL_RenderCopyF(_rendererReference, _fireRingTexture, &rectS, &rectD) < 0)
			DEBUG_LOG_SDL_ERROR("");

		SDL_RenderPresent(_rendererReference);*/
	}

	void Game::CollectGarbage()
	{

	}

	void Game::Dispose()
	{
		BAE_End();

		/*if (_rendererReference != nullptr)
		{
			SDL_DestroyRenderer(_rendererReference);
			_rendererReference = nullptr;
		}

		if (_windowReference != nullptr)
		{
			SDL_DestroyWindow(_windowReference);
			_windowReference = nullptr;
		}

		if (_cube1Texture != nullptr)
		{
			SDL_DestroyTexture(_cube1Texture);
			_cube1Texture = nullptr;
		}
		delete _cube1Image;

		if (_cube2Texture != nullptr)
		{
			SDL_DestroyTexture(_cube2Texture);
			_cube2Texture = nullptr;
		}
		delete _cube2Image;

		if (_cube3Texture != nullptr)
		{
			SDL_DestroyTexture(_cube3Texture);
			_cube3Texture = nullptr;
		}
		delete _cube3Image;

		if (_cube4Texture != nullptr)
		{
			SDL_DestroyTexture(_cube4Texture);
			_cube4Texture = nullptr;
		}
		delete _cube4Image;

		if (_cube5Texture != nullptr)
		{
			SDL_DestroyTexture(_cube5Texture);
			_cube5Texture = nullptr;
		}
		delete _cube5Image;

		if (_fireRingTexture != nullptr)
		{
			SDL_DestroyTexture(_fireRingTexture);
			_fireRingTexture = nullptr;
		}
		delete _fireRingImage;

		if (_fireSmallTexture != nullptr)
		{
			SDL_DestroyTexture(_fireSmallTexture);
			_fireSmallTexture = nullptr;
		}
		delete _fireSmallImage;*/

		SDL_Quit();

		DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game disposed.");
	}
}