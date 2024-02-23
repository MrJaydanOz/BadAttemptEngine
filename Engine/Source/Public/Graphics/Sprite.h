#pragma once
#include <SDL2/SDL_image.h>
#include "Nodes/Transform.h"
#include "Image.h"
#include "Color.h"

enum SpriteBlendingMode
{
	None,
	Alpha,
	Add,
	Modulate,
	Multiply
};

class Sprite : public Transform
{
public:
	bool enabled = true;
	Image* image;
	Color color = 0xFFFFFFFF;
	SpriteBlendingMode blendingMode = SpriteBlendingMode::None;

private:
	int _renderLayer;
	int _zIndex;

public:
};