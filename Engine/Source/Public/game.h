#pragma once
#include <vector>
#include "Nodes/RootNode.h"
#include "GameInput.h"
#include "GameTime.h"
#include "GameGraphics.h"
#include "Nodes/Camera.h"

class RootNode;

class Game
{
	friend class Input;
	friend class Time;
	friend class Graphics;
	friend class Camera;

public:
	RootNode* root;

private:
	bool _isRunning;

	Input* _input;
	Time* _time;
	Graphics* _graphics;
	Camera* _mainCamera;

public:
	static Game* GetGame();

	static void DestroyGame();

	void Run();

	void Quit();

	static Input* GetInput();

	static Time* GetTime();

	static Graphics* GetGraphics();

	static Camera* GetMainCamera();

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
 ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛                     */void/*
                             ↓
 ┏[*/GameLoop/*]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ <─┐                 */();/*
 ┃  Process game functionality for one frame.            ┃   │
 ┃  */void Update();/*                                   ┃   │
 ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ──┘
                             ↓
 ┏[Exit]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 ┃  Deallocate all memory associated with the game.      ┃
 ┃  */void Dispose();/*                                  ┃
 ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */
};