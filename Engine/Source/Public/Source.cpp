#include <iostream>
#include "Game.h"



int main(int argc, char* argv[])
{
	bae::Game::GetGame()->Run();

	bae::Game::DestroyGame();

	return 0;
}