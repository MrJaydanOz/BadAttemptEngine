#include "Nodes/Behaviour.h"

Behaviour::~Behaviour() noexcept
{
	if (IsEnabled(true))
		OnDisable();
	Node::~Node();
}

void Behaviour::OnParentChanged() noexcept
{
	if (IsEnabled(true))
		OnDisable();

	Node::OnParentChanged();
}

Behaviour::Behaviour(const std::string& name, bool enabled) noexcept :
	Node(name),
	_enabled(enabled)
{

}

void Behaviour::SetEnabled(const bool& enabled) noexcept
{
	this->_enabled = enabled;
}

bool Behaviour::IsEnabled(const bool& includeHerarchy) const noexcept
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