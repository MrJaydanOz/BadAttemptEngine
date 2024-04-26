#include "HealthBar.h"

void HealthBar::Create(in<const char*> name, in<float> health)
{
	currentHealth = maxHealth = health;

	backing = AddChild<bae::Sprite>("Backing");
	backing->image = bae::Image::WhitePixel();
	backing->SetZIndex(20);

	fill = backing->AddChild<bae::Sprite>("Fill");
	fill->image = bae::Image::WhitePixel();
	fill->SetZIndex(21);

	Node::Create(name);
}

void HealthBar::Create(in<const char*> name)
{ Create(name, 100.0f); }

void HealthBar::Destroy()
{ Transform::Destroy(); }

void HealthBar::SetColor(in<bae::Color> color) noexcept
{
	backing->color = color;
	backing->color.r /= 4;
	backing->color.g /= 4;
	backing->color.b /= 4;

	fill->color = color;
}

void HealthBar::SetWidth(in<float> width) noexcept
{
	backing->scale = bae::Vector2F(width, 2.0f);
	backing->offset = bae::PoseF(bae::Vector2F(width * -0.5f, 0.0f), 0.0f);
	backing->pivot = bae::Vector2F(0.0f, 0.0f);

	fill->offset = backing->offset;
	fill->pivot = backing->pivot;

	Update();
}

void HealthBar::Update() noexcept
{
	fill->scale = bae::Vector2F((currentHealth / maxHealth) * backing->scale.x, backing->scale.y);
}