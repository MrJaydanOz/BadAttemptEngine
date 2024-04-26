#pragma once
#include "BAE/Nodes/BAE_Node.h"
#include "BAE/Nodes/BAE_Sprite.h"

class HealthBar : public bae::Transform
{
	NODE_BEGIN;

public:
	float maxHealth;
	float currentHealth;

	bae::Sprite* backing;
	bae::Sprite* fill;

public:
	void Update() noexcept;

	void SetWidth(in<float> width) noexcept;

	void SetColor(in<bae::Color> color) noexcept;

protected:
	HealthBar(in<Node*> parent) noexcept : bae::Transform::Transform(parent),
		maxHealth(0.0f),
		currentHealth(maxHealth),
		backing(nullptr),
		fill(nullptr) { }
	virtual ~HealthBar() noexcept override { }

	virtual void Create(in<const char*> name, in<float> health = 100.0f);
	virtual void Create(in<const char*> name = "") override;

	virtual void Destroy() override;
};