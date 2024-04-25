#pragma once
#include "BAE/BAE_StateMachine.h"
#include "BAE/Nodes/BAE_Text.h"
#include "BAE/Math/BAE_VectorT.h"
#include "Button.h"

struct GlobalState
{
public:
	bool yesState;

public:
	GlobalState() noexcept :
		yesState(false) { }
};

class GameState : public bae::State<std::string, in<bae::tuple<ref<bae::StateMachineInstance<bae::StateMachine<GameState>>>, ref<GlobalState>>>, bae::string_equal_to>
{
public:
	GameState(in<KeyType> key) :
		State::State(key) { }

	virtual void OnStart(ParameterType machine) override = 0;

	virtual void OnTick(ParameterType machine) override = 0;

	virtual void OnEnd(ParameterType machine) override = 0;

	static ButtonState ProcessMenuButton(in<bae::Vector2F> mousePosition, in<bool> mouseClicking, ref<Button> button, in<bae::Text*> text);
};