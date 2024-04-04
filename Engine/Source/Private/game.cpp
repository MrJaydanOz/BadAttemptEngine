#include "Game.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>
#include <chrono>
#include <thread>
#include "Graphics/Sprite.h"
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Engine.h"

namespace bae
{
	Game* Game::GetGame()
	{
		static Game* gameSingleton = new Game();

		return gameSingleton;
	}

	void Game::DestroyGame()
	{
		delete GetGame();
	}

	void Game::Run() { Initialize(); }

	void Game::Quit()
	{
		BAE_End();

		_isRunning = false;
	}

	Game::Game() : _isRunning(true), _windowReference(nullptr), _rendererReference(nullptr)
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

		DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game initialised.");

		Start();
	}

	void Game::Start()
	{
		_windowReference = SDL_CreateWindow("Bad Attempt Engine",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,
			0u);

		if (_windowReference == nullptr)
		{
			DEBUG_LOG_SDL_ERROR("Window failed to create: ");

			Dispose();
			return;
		}

		_rendererReference = SDL_CreateRenderer(_windowReference, -1, 0u);

		if (_rendererReference == nullptr)
		{
			DEBUG_LOG_SDL_ERROR("Renderer failed to create: ");

			Dispose();
			return;
		}

		// I honsetly don't care right now I'm busy with other things.

		if (
			Image::TryLoad("Content/Images/Cube1.png", _cube1Image) &&
			Image::TryLoad("Content/Images/Cube2.png", _cube2Image) &&
			Image::TryLoad("Content/Images/Cube3.png", _cube3Image) &&
			Image::TryLoad("Content/Images/Cube4.png", _cube4Image) &&
			Image::TryLoad("Content/Images/Cube5.png", _cube5Image) &&
			Image::TryLoad("Content/Images/FireRing.png", _fireRingImage) &&
			Image::TryLoad("Content/Images/FireSmall.png", _fireSmallImage)
			)
		{
			if (
				(_cube1Texture = SDL_CreateTextureFromSurface(_rendererReference, _cube1Image->_surfaceData)) != nullptr &&
				(_cube2Texture = SDL_CreateTextureFromSurface(_rendererReference, _cube2Image->_surfaceData)) != nullptr &&
				(_cube3Texture = SDL_CreateTextureFromSurface(_rendererReference, _cube3Image->_surfaceData)) != nullptr &&
				(_cube4Texture = SDL_CreateTextureFromSurface(_rendererReference, _cube4Image->_surfaceData)) != nullptr &&
				(_cube5Texture = SDL_CreateTextureFromSurface(_rendererReference, _cube5Image->_surfaceData)) != nullptr &&
				(_fireRingTexture = SDL_CreateTextureFromSurface(_rendererReference, _fireRingImage->_surfaceData)) != nullptr &&
				(_fireSmallTexture = SDL_CreateTextureFromSurface(_rendererReference, _fireSmallImage->_surfaceData)) != nullptr
				)
			{

			}
			else
			{
				DEBUG_LOG_SDL_ERROR("Sigh: ");
			}
		}

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

			Render();

			CollectGarbage();

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
		SDL_SetRenderDrawColor(_rendererReference, 0x00, 0x00, 0x00, 0xFF);

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

		SDL_RenderPresent(_rendererReference);
	}

	void Game::CollectGarbage()
	{

	}

	void Game::Dispose()
	{
		if (_rendererReference != nullptr)
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
		delete _fireSmallImage;

		SDL_Quit();

		DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game disposed.");
	}
}