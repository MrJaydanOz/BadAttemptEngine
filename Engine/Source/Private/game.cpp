#include "Game.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Nodes/Sprite.h"
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

const Input* Game::GetInput() { return GetGame()->_input; }

const Time* Game::GetTime() { return GetGame()->_time; }

Game::Game() : 
	_isRunning(true), 
	_windowReference(nullptr), 
	_rendererReference(nullptr),
	_input(nullptr),
	_time(nullptr),
	root(nullptr)
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

	_input = new Input();
	_time = new Time();

	GameLoop();
}

void Game::GameLoop()
{
	while (_isRunning)
	{
		Update();
	}

	Dispose();
}

void Game::Update()
{
	_input->ProcessInput();

	SDL_SetRenderDrawColor(_rendererReference, 0x00, 0x00, 0x00, 0xFF);

	SDL_RenderClear(_rendererReference);

	const float framesPerSecond = 12.0f;
	const unsigned long long millisecondsPerFrame = std::lroundf(1000.0f / framesPerSecond);

	unsigned long long time = SDL_GetTicks64();

	SDL_RenderPresent(_rendererReference);
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

	delete _input;

	SDL_Quit();

	DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game disposed.");
}
