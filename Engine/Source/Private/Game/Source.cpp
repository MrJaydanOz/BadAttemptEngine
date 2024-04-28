#include "BAE/BAE_Engine.h"
#include "GameState.h"
#include "GameStateMainMenu.h"
#include "GameStateOptions.h"
#include "GameStateLevel.h"

bae::StateMachineInstance<bae::StateMachine<GameState>> stateMachine;
GlobalState state;

void BAE_Start()
{
	stateMachine.machine = new bae::StateMachine<GameState>();
	stateMachine.QueueState(
		stateMachine.machine->CreateState<GameStateSplashScreen>("SplashScreen"));
	stateMachine.machine->CreateState<GameStateMainMenu>("MainMenu");
	stateMachine.machine->CreateState<GameStateOptions>("Options");
	stateMachine.machine->CreateState<GameStateLevel>("Game");
	stateMachine.machine->CreateState<GameStateDiedScreen>("DiedScreen");
}

void BAE_Update()
{
	stateMachine.Tick({ stateMachine, state });
}

void BAE_LateUpdate()
{

}

void BAE_FixedUpdate()
{

}

void BAE_PhysicsUpdate()
{
	
}

void BAE_Restart()
{
	stateMachine.ChangeState("MainMenu", { stateMachine, state });
}

void BAE_End()
{
	stateMachine.ChangeState(nullptr, { stateMachine, state });
	delete stateMachine.machine;

	DEBUG_LOG_INFO("Bye");
}