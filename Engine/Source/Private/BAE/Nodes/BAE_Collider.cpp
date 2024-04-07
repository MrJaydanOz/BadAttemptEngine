#include "Nodes/BAE_Collider.h"
#include "BAE_Game.h"

namespace bae
{
	Collider::Collider(in<std::string> name) noexcept : 
		Transform::Transform(name),
		isTrigger(false) { }

	Collider::~Collider() noexcept
	{
		Transform::~Transform();
	}

	void Collider::OnLoad() noexcept
	{
		Transform::OnLoad();
	}

	void Collider::OnParentChanged() noexcept
	{
		Game::GetPhysics()->_RemoveCollider(this);
		Game::GetPhysics()->_AddCollider(this);
		Transform::OnParentChanged();
	}

	void Collider::OnDestroy() noexcept
	{
		Game::GetPhysics()->_RemoveCollider(this);
		Transform::OnDestroy();
	}
}