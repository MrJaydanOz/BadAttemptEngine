#include "Nodes/Behaviour.h"

Behaviour::~Behaviour() noexcept
{
	Node::~Node();
}

Behaviour::Behaviour(const std::string& name) noexcept :
	Node(name),
	_enabled(true),
	_isFirstFrame(true)
{ }

void Behaviour::SetEnabled(const bool& enabled)
{
	this->_enabled = enabled;
}

bool Behaviour::IsEnabled(const bool& includeHerarchy) const
{
	if (!_enabled)
		return false;

	if (includeHerarchy)
	{
		Node* parent = GetParent();

		while (parent != nullptr)
		{
			Behaviour* parentBehaviour = dynamic_cast<Behaviour*>(parent);
			if (parentBehaviour && !parentBehaviour->_enabled)
				return false;

			parent = parent->GetParent();
		}
	}

	return true;
}