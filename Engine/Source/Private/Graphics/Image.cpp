#include "Graphics/Image.h"
#include "Debug.h"

namespace bae
{
	Image* Image::Load(const char* path)
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

	bool Image::TryLoad(const char* path, Image*& image)
	{
		image = Load(path);
		return image != nullptr;
	}

	Image::~Image()
	{
		SDL_FreeSurface(_surfaceData);
		delete _surfaceData;
	}

	Vector2I Image::GetSize() const { return Vector2I(GetWidth(), GetHeight()); }

	int Image::GetWidth() const { return _surfaceData->w; }

	int Image::GetHeight() const { return _surfaceData->h; }

	Image::Image(const char* path, SDL_Surface* surfaceData) : _path(path), _surfaceData(surfaceData) { }
}