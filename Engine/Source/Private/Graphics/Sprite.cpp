#include "Graphics/Sprite.h"
#include "debug.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

Sprite::Sprite(SDL_Renderer* rendererReference) : _rendererReference(rendererReference), rotation(0.0f), _path(""), posX(0.0f), posY(0.0f), scale(1.0f), _surfaceData(nullptr), _textureReference(nullptr)
{

}

Sprite::~Sprite()
{

}

bool Sprite::ImportTexture(const char* pathToFile)
{
	_path = pathToFile;

	_surfaceData = IMG_Load(pathToFile);

	if (_surfaceData == nullptr)
	{
		DEBUG_LOG_SDL_ERROR("Image failed to import: ");

		Dispose();
		return false;
	}

	_textureReference = SDL_CreateTextureFromSurface(_rendererReference, _surfaceData);

	if (_textureReference == nullptr)
	{
		DEBUG_LOG_SDL_ERROR("Image failed to convert to texture: ");

		Dispose();
		return false;
	}

	return true;
}

void Sprite::Draw()
{
	float imageWidth = (float)_surfaceData->w;
	float imageHeight = (float)_surfaceData->h;

	SDL_FRect destRect =
	{
		(float)posX, (float)posY,
		imageWidth * scale, imageHeight * scale,
	};

	SDL_FPoint center = { destRect.w / 2.0, destRect.h / 2.0 };

	SDL_RenderCopyExF(
		_rendererReference,
		_textureReference,
		NULL,
		&destRect,
		rotation,
		&center,
		SDL_FLIP_NONE
	);
}

void Sprite::Dispose()
{
	if (_surfaceData != nullptr)
	{
		SDL_FreeSurface(_surfaceData);
		_surfaceData = nullptr;
	}

	if (_textureReference != nullptr)
	{
		SDL_DestroyTexture(_textureReference);
		_surfaceData = nullptr;
	}
}