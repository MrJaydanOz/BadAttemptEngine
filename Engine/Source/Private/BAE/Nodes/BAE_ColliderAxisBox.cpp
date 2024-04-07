#include "Nodes/BAE_ColliderAxisBox.h"

namespace bae
{
	ColliderAxisBox::ColliderAxisBox(in<std::string> name) noexcept :
		Collider::Collider(name) { }

	ColliderAxisBox::~ColliderAxisBox() noexcept
	{
		Collider::~Collider();
	}

	ColliderAxisBox* ColliderAxisBox::CloneInto(in<Node*> parent) noexcept
	{
		ColliderAxisBox* newNode = CloneIntoBegin<ColliderAxisBox>(parent, GetName());
		newNode->center = center;
		newNode->size = size;
		return newNode;
	}
}