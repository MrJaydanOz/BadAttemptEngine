#include "Game.h"
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

Input* Game::GetInput() { return GetGame()->_input; }

Time* Game::GetTime() { return GetGame()->_time; }

Graphics* Game::GetGraphics() { return GetGame()->_graphics; }

Camera* Game::GetMainCamera() { return GetGame()->_mainCamera; }

Game::Game() : 
	_isRunning(true), 
	_input(nullptr),
	_time(nullptr),
	_graphics(nullptr),
	_mainCamera(nullptr),
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
	_input = new Input();
	_time = new Time();
	_graphics = new Graphics("Bad Attempt Engine", 
		Graphics::CenteredWindowFlag(), Graphics::CenteredWindowFlag(), 
		1280, 720, 
		Graphics::WindowFlags::None);

	GameLoop();
}

void Game::GameLoop()
{
	while (_isRunning)
	{
		Update();

		_time->SleepUntilNextFrame();
	}

	Dispose();
}

void Game::Update()
{
	_input->ProcessInput();
	_graphics->DoRender();
}

void Game::Dispose()
{
	delete _time;
	delete _graphics;
	delete _input;

	SDL_Quit();

	DEBUG_LOG_SUCCESS_CONTEXTED(BAE_LOG_CONTEXT, "Game disposed.");
}
