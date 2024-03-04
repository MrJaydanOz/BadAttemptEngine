#pragma once
#include <string>
#include "Nodes/Transform.h"
#include "Graphics/ImageClip.h"
#include "Graphics/Image.h"
#include "Graphics/Color.h"
#include "Math/VectorT.h"

enum SpriteBlendingMode
{
	None,
	Alpha,
	Add,
	Modulate,
	Multiply
};

enum SpriteScaleMode
{
	PreservePixelSize,
	UnitSquare,
	UnitWidth,
	UnitHeight
};

class Sprite : public Transform
{
public:
	bool enabled;
	ImageClip imageClip;
	Color color;
	SpriteBlendingMode blendingMode;
	SpriteScaleMode scaleMode;
	Vector2F scale;

private:
	int _renderLayer;
	int _zIndex;

public:
	Sprite(const std::string& name = "") noexcept;
	virtual ~Sprite() noexcept override;
};