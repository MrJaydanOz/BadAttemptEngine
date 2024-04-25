#include "Button.h"

ButtonState Button::Test(in<bae::Vector2F> mousePosition, in<bool> isClicking) noexcept
{
	bae::Vector2F extents = size * 0.5f;
	bae::Vector2F deltaMousePosition = mousePosition - center;

	if (_hasPressed)
	{
		if (isClicking)
			return ButtonState::HELD;
		else
		{
			bool hovering =
				deltaMousePosition.x <= extents.x && deltaMousePosition.x >= -extents.x &&
				deltaMousePosition.y <= extents.y && deltaMousePosition.y >= -extents.y;

			_hasPressed = false;
			return hovering ? ButtonState::CLICKED : ButtonState::RELEASED;
		}
	}
	else
	{
		bool hovering = 
			deltaMousePosition.x <= extents.x && deltaMousePosition.x >= -extents.x &&
			deltaMousePosition.y <= extents.y && deltaMousePosition.y >= -extents.y;

		if (isClicking && hovering)
		{
			_hasPressed = true;
			return ButtonState::PRESSED;
		}
		else
			return hovering ? ButtonState::HOVERING : ButtonState::NONE;
	}
}