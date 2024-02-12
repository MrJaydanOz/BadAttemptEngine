#include "game.h"
#include <iostream>

Game* Game::GetGame()
{
	static Game* gameSingleton = new Game();

	return gameSingleton;
}

Game* Game::DestroyGame()
{
	delete GetGame();
}

Game* Game::Run() { Initialise(); }

Game::Game() : _isRunning(true)
{
	printf("Game created.\n");
}

Game::~Game()
{
	printf("Game destroyed.\n");
}

void Game::Initialise()
{
	printf("Game initialised.\n");

	Start();
}

void Game::Start()
{
	printf("Game started.\n");

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
	printf("Input read.\n");
}

void Game::Update()
{
	printf("Frame processed.\n");

	static int frameCount = 0;

	if (frameCount >= 30)
		_isRunning = false;
	else
		frameCount++;
}

void Game::Render()
{
	printf("Frame rendered.\n");
}

void Game::CollectGarbage()
{
	printf("garbage collected.\n");
}

void Game::Dispose()
{
	printf("Game disposed.\n");
}
