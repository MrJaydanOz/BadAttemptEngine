#pragma once
#include "BAE/Math/BAE_VectorT.h"

enum class ButtonState
{
	NONE,
	HOVERING,
	PRESSED,
	HELD,
	RELEASED,
	CLICKED
};

struct Button
{
public:
	bae::Vector2F center;
	bae::Vector2F size;

private:
	bool _hasPressed;

public:
	Button() noexcept :
		_hasPressed(false) { }

	ButtonState Test(in<bae::Vector2F> mousePosition, in<bool> isClicking) noexcept;
};