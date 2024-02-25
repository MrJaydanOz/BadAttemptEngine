#pragma once
#include <vector>
#include "Graphics/Image.h"
#include "Graphics/Sprite.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Game
{
private:
	bool _isRunning;

	SDL_Window* _windowReference;
	SDL_Renderer* _rendererReference;
	Image* _cube1Image;
	SDL_Texture* _cube1Texture;
	Image* _cube2Image;
	SDL_Texture* _cube2Texture;
	Image* _cube3Image;
	SDL_Texture* _cube3Texture;
	Image* _cube4Image;
	SDL_Texture* _cube4Texture;
	Image* _cube5Image;
	SDL_Texture* _cube5Texture;
	Image* _fireRingImage;
	SDL_Texture* _fireRingTexture;
	Image* _fireSmallImage;
	SDL_Texture* _fireSmallTexture;

public:
	static Game* GetGame();

	static void DestroyGame();

	void Run();

	void Quit();

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
 ┃  Process game functionality for one frame.            ┃ <─┐
 ┃  */void ProcessInput();/*                             ┃   │
 ┃                                                       ┃   │
 ┃  Render frame to the game window.                     ┃   │
 ┃  */void Update();/*                                   ┃   │
 ┃                                                       ┃   │
 ┃  Deallocate data marked for deletion.                 ┃   │
 ┃  */void Render();/*                                   ┃   │
 ┃                                                       ┃   │
 ┃  Listen for user input and process it.                ┃   │
 ┃  */void CollectGarbage();/*                           ┃ ──┘
 ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ 
                             ↓
 ┏[Exit]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 ┃  Deallocate all memory associated with the game.      ┃
 ┃  */void Dispose();/*                                  ┃
 ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */
};