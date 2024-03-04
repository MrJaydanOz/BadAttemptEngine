#include "Graphics/ImageClip.h"

ImageClip::ImageClip(Image* image) noexcept :
	image(image),
	clipRectangle(RectI(0, 0, 0, 0))
{ }

ImageClip::ImageClip(Image* image, RectI clipRectangle) noexcept :
	image(image),
	clipRectangle(clipRectangle)
{ }