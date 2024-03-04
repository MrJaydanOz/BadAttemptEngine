#include "Graphics/Sprite.h"
#include <string>

Sprite::Sprite(const std::string& name) noexcept : Transform(name),
	enabled(true),
	imageClip(nullptr),
	color(COLOR_WHITE),
	blendingMode(None),
	scaleMode(PreservePixelSize),
	scale(1.0f, 1.0f),
	_renderLayer(0),
	_zIndex(0)
{ }

Sprite::~Sprite() noexcept
{
	Transform::~Transform();
}