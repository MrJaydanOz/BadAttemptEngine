#include "Game.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>
#include <chrono>
#include <thread>
#include "Graphics/Sprite.h"
#include "SDL2/SDL.h"
#include "Debug.h"

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

void Game::Quit() { _isRunning = false; }

Game::Game() : _isRunning(true), _windowReference(nullptr), _rendererReference(nullptr),
_playerPosition(100.0f, 100.0f),
_enemy1Position(200.0f, 200.0f),
_enemy2Position(300.0f, 300.0f)
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

	// If you want to see the Unity scripts: Engine/UnityScripts/...
	// It's not supposed to be optimised.

	if (
		Image::TryLoad("Content/Images/EnemySprites.png", _enemyImage) &&
		Image::TryLoad("Content/Images/PlayerSprites.png", _playerImage) &&
		Image::TryLoad("Content/Images/Complaint.png", _complaintImage)
		)
	{
		if (
			(_enemyTexture = SDL_CreateTextureFromSurface(_rendererReference, _enemyImage->_surfaceData)) != nullptr &&
			(_playerTexture = SDL_CreateTextureFromSurface(_rendererReference, _playerImage->_surfaceData)) != nullptr &&
			(_complaintTexture = SDL_CreateTextureFromSurface(_rendererReference, _complaintImage->_surfaceData)) != nullptr
			)
		{

		}
		else
		{
			DEBUG_LOG_SDL_ERROR("Sigh: ");
		}
	}

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

		Update();

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
	int keyCount = 0;
	const unsigned char* keyStates = SDL_GetKeyboardState(&keyCount);

	Vector2I delta = Vector2I(0.0f, 0.0f);

	if (keyStates[SDL_SCANCODE_S])
		delta.y += 1;
	if (keyStates[SDL_SCANCODE_W])
		delta.y -= 1;
	if (keyStates[SDL_SCANCODE_D])
		delta.x += 1;
	if (keyStates[SDL_SCANCODE_A])
		delta.x -= 1;

	_playerPosition.x += delta.x * 10.0f;
	_playerPosition.y += delta.y * 10.0f;

	if      (delta.x < 0 && delta.y == 0)
		_playerRotation = 0;
	else if (delta.x < 0 && delta.y > 0)
		_playerRotation = 1;
	else if (delta.x == 0 && delta.y > 0)
		_playerRotation = 2;
	else if (delta.x > 0 && delta.y > 0)
		_playerRotation = 3;
	else if (delta.x > 0 && delta.y == 0)
		_playerRotation = 4;
	else if (delta.x > 0 && delta.y < 0)
		_playerRotation = 5;
	else if (delta.x == 0 && delta.y < 0)
		_playerRotation = 6;
	else if (delta.x < 0 && delta.y < 0)
		_playerRotation = 7;

	_enemy1Position.x -= 10.0f;
	if (_enemy1Position.x < -40.0f)
		_enemy1Position.x = 1300.0;

	_enemy2Position.x -= 7.0f;
	if (_enemy2Position.x < -40.0f)
		_enemy2Position.x = 1300.0;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(_rendererReference, 0x00, 0x00, 0x00, 0xFF);

	SDL_RenderClear(_rendererReference);

	SDL_Rect rectS = SDL_Rect();
	SDL_FRect rectD = SDL_FRect();

	const float framesPerSecond = 12.0f;
	const unsigned long millisecondsPerFrame = std::lroundf(1000.0f / framesPerSecond);

	unsigned long time = SDL_GetTicks64();

	/*
	* I took a break to fix my mental health and now I'm pissed off because I'm getting f***ed 
	* by this f***ing university! I have been programming for 4 years now and I get less marks
	* than some chap who just copied the example! I am here to learn. I already know how basics
	* work. I am learning things by making this "unnecessarily complicated". I am using bitmasks.
	* Do you know what they are? Is 'SDL_GetMouseState' ringing any bells? I mean it says it in
	* the comments above the ctrl+click. Why didn't you use?
	* 
	* This engine is just a mess now bolting through drawing basic crap to the screen. I am
	* starting this engine over again, this time with my own plan. I'm not giving up and copying
	* the example anymore. I am learning my way whether I fail or not. 
	* 
	* BTW want proof? Look on steam. Search 'BombsweeperVR'.
	*/

	rectS.x = (int)((time / millisecondsPerFrame) % 12) * 32;
	rectS.y = (_enemy1Rotation % 8) * 32;
	rectS.w = 32;
	rectS.h = 32;

	rectD.x = _enemy1Position.x;
	rectD.y = _enemy1Position.y;
	rectD.w = (float)rectS.w * 3.0f;
	rectD.h = (float)rectS.h * 3.0f;

	if (SDL_RenderCopyF(_rendererReference, _enemyTexture, &rectS, &rectD) < 0)
		DEBUG_LOG_SDL_ERROR("");

	rectS.x = (int)((time / millisecondsPerFrame) % 12) * 32;
	rectS.y = (_enemy2Rotation % 8) * 32;
	rectS.w = 32;
	rectS.h = 32;

	rectD.x = _enemy2Position.x;
	rectD.y = _enemy2Position.y;
	rectD.w = (float)rectS.w * 3.0f;
	rectD.h = (float)rectS.h * 3.0f;

	if (SDL_RenderCopyF(_rendererReference, _enemyTexture, &rectS, &rectD) < 0)
		DEBUG_LOG_SDL_ERROR("");

	rectS.x = (int)((time / millisecondsPerFrame) % 12) * 32;
	rectS.y = (_playerRotation % 8) * 32;
	rectS.w = 32;
	rectS.h = 32;

	rectD.x = _playerPosition.x;
	rectD.y = _playerPosition.y;
	rectD.w = (float)rectS.w * 3.0f;
	rectD.h = (float)rectS.h * 3.0f;

	if (SDL_RenderCopyF(_rendererReference, _playerTexture, &rectS, &rectD) < 0)
		DEBUG_LOG_SDL_ERROR("");

	rectS.x = 0;
	rectS.y = 0;
	rectS.w = 691;
	rectS.h = 17;

	rectD.x = 0.0f;
	rectD.y = 720.0f - 17.0f;
	rectD.w = (float)rectS.w * 1.0f;
	rectD.h = (float)rectS.h * 1.0f;

	if (SDL_RenderCopyF(_rendererReference, _complaintTexture, &rectS, &rectD) < 0)
		DEBUG_LOG_SDL_ERROR("");

	// This assesment took me one f***ing hour. Why do you think I'm going complex?

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

	if (_enemyTexture != nullptr)
	{
		SDL_DestroyTexture(_enemyTexture);
		_enemyTexture = nullptr;
	}
	delete _enemyImage;

	if (_playerTexture != nullptr)
	{
		SDL_DestroyTexture(_playerTexture);
		_playerTexture = nullptr;
	}
	delete _playerImage;

	SDL_Quit();

	DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game disposed.");
}
