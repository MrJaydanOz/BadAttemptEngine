#include "HealthBar.h"

void HealthBar::Create(in<const char*> name, in<bae::Image*> image, in<float> health, in<float> width, bae::Color color)
{
	currentHealth = maxHealth = health;

	backing = AddChild<bae::Sprite>("Backing");
	backing->color = color;
	backing->color.r /= 4;
	backing->color.g /= 4;
	backing->color.b /= 4;
	backing->image = image;
	backing->scale = bae::Vector2F(width, 2.0f);
	backing->offset = bae::PoseF(bae::Vector2F(width * -0.5f, 0.0f), 0.0f);
	backing->pivot = bae::Vector2F(0.0f, 0.0f);
	backing->SetZIndex(20);

	fill = backing->AddChild<bae::Sprite>("Fill");
	fill->color = color;
	fill->image = image;
	fill->scale = bae::Vector2F(width, 2.0f);
	fill->pivot = bae::Vector2F(0.0f, 0.0f);
	fill->SetZIndex(21);

	Node::Create(name);
}

void HealthBar::Create(in<const char*> name)
{ Create(name, nullptr, 100.0f); }

void HealthBar::Destroy()
{ Transform::Destroy(); }

void HealthBar::Update() noexcept
{
	fill->scale = bae::Vector2F((currentHealth / maxHealth) * backing->scale.x, backing->scale.y);
}