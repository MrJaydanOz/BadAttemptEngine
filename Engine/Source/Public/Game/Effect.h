#pragma once
#include "BAE/Nodes/BAE_Animator.h"
#include "BAE/Nodes/BAE_Sprite.h"

class Effect : public bae::Animator
{
	NODE_BEGIN;

public:
	bae::Sprite* sprite = nullptr;

public:
	bool IsDone() const noexcept;

protected:
	Effect(in<Node*> parent) noexcept :
		bae::Animator::Animator(parent) { }
	virtual ~Effect() noexcept override { }

	virtual void Create(in<const char*> name = "") override;

	virtual void Destroy() override;
};