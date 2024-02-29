#pragma once
#include <vector>
#include "Nodes/RootNode.h"
#include "Graphics/Image.h"
#include "Graphics/Sprite.h"
#include "GameInput.h"
#include "GameTime.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Game
{
public:
	RootNode* root;

private:
	bool _isRunning;

	SDL_Window* _windowReference;
	SDL_Renderer* _rendererReference;

	Input* _input;
	Time* _time;

public:
	static Game* GetGame();

	static void DestroyGame();

	void Run();

	void Quit();

	static const Input* GetInput();

	static const Time* GetTime();

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
 ┏[*/void GameLoop();/*]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 ┃  Listen for user input and process it.                ┃ <─┐
 ┃  */void ProcessInput();/*                             ┃   │
 ┃                                                       ┃   │
 ┃  Process game functionality for one frame.            ┃   │
 ┃  */void Update();/*                                   ┃   │
 ┃                                                       ┃   │
 ┃  Render frame to the game window.                     ┃   │
 ┃  */void Render();/*                                   ┃   │
 ┃                                                       ┃   │
 ┃  Deallocate data marked for deletion.                 ┃   │
 ┃  */void CollectGarbage();/*                           ┃ ──┘
 ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ 
                             ↓
 ┏[Exit]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 ┃  Deallocate all memory associated with the game.      ┃
 ┃  */void Dispose();/*                                  ┃
 ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */
};