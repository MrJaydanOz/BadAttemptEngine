#pragma once
#include <string>
#include "Graphics/Color.h"
#include "Graphics/Image.h"
#include "Graphics/ImageClip.h"
#include "Math/VectorT.h"
#include "Nodes/Behaviour.h"
#include "Nodes/Transform.h"
#include "Nodes/Visual.h"

enum SpriteFlipMode
{
	None,
	Horizontal,
	Vertical,
};

class Sprite : public Transform, public Visual
{
public:
	ImageClip imageClip;
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