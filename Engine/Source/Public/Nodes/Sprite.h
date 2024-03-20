#pragma once
#include <string>
#include "Graphics/Color.h"
#include "Graphics/Image.h"
#include "Math/VectorT.h"
#include "Nodes/Behaviour.h"
#include "Nodes/Transform.h"
#include "Nodes/Visual.h"

class Image;

enum SpriteFlipMode
{
	SpriteFlipMode_None,
	SpriteFlipMode_Horizontal,
	SpriteFlipMode_Vertical,
};

class Sprite : public Transform, public Visual
{
public:
	Image* image;
	/// <summary>
	/// The rectangle measured in pixels that will be drawn. If the minimum is less than 0 it will
	/// be interpreted as subtracting from the positive corner of the Image. The same for the
	/// maximum except it includes 0.
	/// <para>Eg: RectI(0, 0, 0, 0) == RectI(0, 0, Image.size.x, Image.size.y)</para>
	/// </summary>
	RectI clipRectangle;
	Color color;
	VisualBlendingMode blendingMode;
	SpriteFlipMode flipMode;
	Vector2F scale;
	Vector2F pivot;

public:
	Sprite(int zOrder, int renderLayer = 0) noexcept;
	Sprite(const std::string& name = "", int zOrder = 0, int renderLayer = 0) noexcept;
	virtual ~Sprite() noexcept override;

protected:
	void Render(SDL_Renderer* renderer, const Camera* camera) override;
};