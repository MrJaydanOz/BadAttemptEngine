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
	ImageClip(Image* image) noexcept;
	ImageClip(Image* image, RectI clipRectangle) noexcept;
};