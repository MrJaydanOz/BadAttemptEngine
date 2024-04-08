#include "Nodes/BAE_ColliderAxisBox.h"

namespace bae
{
	ColliderAxisBox::ColliderAxisBox(in<std::string> name) noexcept :
		Collider::Collider(name) { }

	ColliderAxisBox::~ColliderAxisBox() noexcept
	{
		Collider::~Collider();
	}
}