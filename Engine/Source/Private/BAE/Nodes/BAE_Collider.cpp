#include "Nodes/BAE_Collider.h"
#include "BAE_Game.h"

namespace bae
{
	Collider::Collider(in<Node*> parent) noexcept :
		Transform::Transform(parent),
		collisionLayers(std::numeric_limits<decltype(collisionLayers)>::max()),
		isTrigger(false) { }

	Collider::~Collider() noexcept { }

	void Collider::Create(in<const char*> name)
	{
		Transform::Create(name);
	}

	void Collider::Destroy()
	{
		Game::GetPhysics()->_RemoveCollider(this);

		Transform::Destroy();
	}

	void Collider::OnParentChanged() noexcept
	{
		Transform::OnParentChanged();

		Game::GetPhysics()->_RemoveCollider(this);
		Game::GetPhysics()->_AddCollider(this);
	}
}