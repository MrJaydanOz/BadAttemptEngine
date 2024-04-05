#include "BAE_Image.h"

#include "BAE_Def.h"
#include <SDL2/SDL_image.h>
#include "BAE_Debug.h"
#include "Math/BAE_RectT.h"
#include "Math/BAE_VectorT.h"

namespace bae
{
	Image* Image::Load(in_array<char> path)
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

	bool Image::TryLoad(in_array<char> path, out<Image*> image)
	{
		image = Load(path);
		return image != nullptr;
	}

	Image::~Image()
	{
		SDL_FreeSurface(_sdlSurface);
		delete _sdlSurface;
	}

	const char* Image::GetPath() const { return _path; }

	Vector2I Image::GetSize() const { return Vector2I(GetWidth(), GetHeight()); }
	int Image::GetWidth() const { return _sdlSurface->w; }
	int Image::GetHeight() const { return _sdlSurface->h; }

	Image::Image(in_array<char> path, in<SDL_Surface*> surfaceData) : _path(path), _sdlSurface(surfaceData) { }
}