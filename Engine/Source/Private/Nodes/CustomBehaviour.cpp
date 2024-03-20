#include "Nodes/CustomBehaviour.h"

CustomBehaviour::CustomBehaviour(const std::string& name) noexcept : Behaviour(name),
	_isFirstFrame(true)
{
}