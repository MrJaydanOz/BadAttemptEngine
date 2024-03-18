#include "Nodes/Behaviour.h"

Behaviour::Behaviour(const std::string& name) noexcept :
	enabled(true),
	isFirstFrame(true)
{ }

void Behaviour::SetEnabled(const bool& enabled)
{
	this->enabled = enabled;
}

bool Behaviour::IsEnabled(const bool& includeHerarchy) const
{
	if (!enabled)
		return false;

	if (includeHerarchy)
	{

	}
	else
		return true;
}