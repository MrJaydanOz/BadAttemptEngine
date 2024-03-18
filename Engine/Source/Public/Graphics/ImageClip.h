#pragma once
#include "Graphics/Image.h"

struct ImageClip
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

public:
	constexpr ImageClip(Image* image) noexcept :
		image(image),
		clipRectangle(RectI(0, 0, 0, 0))
	{ }
	constexpr ImageClip(Image* image, const RectI& clipRectangle) noexcept :
		image(image),
		clipRectangle(clipRectangle)
	{ }
	constexpr ImageClip(Image* image, const Vector2I& clipRectangleMin, const Vector2I& clipRectangleMax) noexcept :
		image(image),
		clipRectangle(clipRectangleMin, clipRectangleMax)
	{ }
	constexpr ImageClip(Image* image, const int& clipRectangleMinX, const int& clipRectangleMinY, const int& clipRectangleMaxX, const int& clipRectangleMaxY) noexcept :
		image(image),
		clipRectangle(clipRectangleMinX, clipRectangleMinY, clipRectangleMaxX, clipRectangleMaxY)
	{ }
};