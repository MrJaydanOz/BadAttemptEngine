#include "Game.h"
#include "Graphics/Sprite.h"
#include <iostream>
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

	_testTexture = new Sprite(_rendererReference);
	_testTexture->ImportTexture("Content/Sprites/Letters/DBlue.png");

	GameLoop();
}

void Game::GameLoop()
{
	while (_isRunning)
	{
		ProcessInput();

		Update();

		Render();

		CollectGarbage();
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
	SDL_SetRenderDrawColor(_rendererReference, 0xFF, 0x00, 0x00, 0xFF);

	SDL_RenderClear(_rendererReference);

	_testTexture->Draw();

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

	SDL_Quit();

	DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game disposed.");
}
