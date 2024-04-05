#include "BAE_Engine.h"

int BAE_Initialize()
{
	bae::Game::GetGame()->Run();

	bae::Game::DestroyGame();

	return 0;
}