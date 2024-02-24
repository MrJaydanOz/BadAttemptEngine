#pragma once
#include "Nodes/Transform.h"
#include "Graphics/Image.h"
#include "Graphics/Color.h"

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
	bool enabled;
	Image* image;
	Color color;
	SpriteBlendingMode blendingMode;

private:
	int _renderLayer;
	int _zIndex;

public:
};