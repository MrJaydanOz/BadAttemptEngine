#include "GameStateLevel.h"
#include "BAE/BAE_Time.h"

void GameStateLevel::OnStart(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();

	time.SetTimeScale(1.0f);
}

void GameStateLevel::OnTick(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();
	bae::Input& input = *bae::Game::GetInput();


}

void GameStateLevel::OnEnd(ParameterType machine)
{
	bae::Time& time = *bae::Game::GetTime();

	time.SetTimeScale(1.0f);
}
