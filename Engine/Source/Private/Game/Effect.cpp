#include "Effect.h"

void Effect::Create(in<const char*> name)
{
	Animator::Create(name);

	sprite = AddChild<bae::Sprite>("Sprite");
}

void Effect::Destroy()
{
	Animator::Destroy();
}

bool Effect::IsDone() const noexcept
{
	return GetCurrentState() == nullptr;
}