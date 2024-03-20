#include "Graphics/Image.h"
#include "Debug.h"
#include <SDL2/SDL_image.h>
#include "Math/VectorT.h"

Image* Image::Load(const char* path) noexcept
{
	SDL_Surface* surfaceData = IMG_Load(path);

	if (surfaceData == nullptr)
	{
		DEBUG_LOG_SDL_ERROR("Image failed to load: ");
		return nullptr;
	}
	else
		return new Image(path, surfaceData);
}

bool Image::TryLoad(const char* path, Image*& image) noexcept
{
	image = Load(path);
	return image != nullptr;
}

Image::~Image() noexcept
{
	SDL_FreeSurface(_sdlSurface);
}

Vector2I Image::GetSize() const noexcept { return Vector2I(GetWidth(), GetHeight()); }

int Image::GetWidth() const noexcept { return _sdlSurface->w; }

int Image::GetHeight() const noexcept { return _sdlSurface->h; }

Image::Image(const char* path, SDL_Surface* surfaceData) noexcept : _path(path), _sdlSurface(surfaceData) { }
