#include "Nodes/BAE_ColliderAxisBox.h"

namespace bae
{
	ColliderAxisBox::ColliderAxisBox(in<Node*> parent) noexcept :
		Collider::Collider(parent) { }

	ColliderAxisBox::~ColliderAxisBox() noexcept { }

	void ColliderAxisBox::Create(in<const char*> name)
	{
		Collider::Create(name);
	}

	void ColliderAxisBox::Destroy()
	{
		Collider::Destroy();
	}
}