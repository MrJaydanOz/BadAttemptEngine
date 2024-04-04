#pragma once
#include "Game.h"

int BAE_Initialize()
{
	bae::Game::GetGame()->Run();

	bae::Game::DestroyGame();

	return 0;
}

extern void BAE_Start();

extern void BAE_Update();

extern void BAE_LateUpdate();

extern void BAE_FixedUpdate();

extern void BAE_End();