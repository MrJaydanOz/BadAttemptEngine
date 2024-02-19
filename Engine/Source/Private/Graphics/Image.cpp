#include "Graphics/Image.h"
#include "Debug.h"
#include <SDL2/SDL_image.h>

Image* Image::Load(const char* path)
{
	SDL_Surface* surfaceData = IMG_Load(path);

	if (surfaceData == nullptr)
	{
		DEBUG_LOG_ERROR_CONTEXTED(BAE_LOG_CONTEXT, "Image failed to load: " << SDL_GetError());
		return nullptr;
	}
	else
		return new Image(path, surfaceData);
}

Image::~Image()
{
	SDL_FreeSurface(_surfaceData);
}

Image::Image(const char* path, SDL_Surface* surfaceData) : _path(path), _surfaceData(surfaceData) { }
