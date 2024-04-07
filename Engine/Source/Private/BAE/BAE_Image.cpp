#include "BAE_Image.h"

#include "BAE_Def.h"
#include <SDL2/SDL_image.h>
#include "BAE_Debug.h"
#include "Math/BAE_RectT.h"
#include "Math/BAE_VectorT.h"
#include "BAE_Game.h"
#include <optional>
#include "Nodes/BAE_Visual.h"

namespace bae
{
	Image::Image(in_value<char*> path, in<SDL_Surface*> surfaceData, in<SDL_Texture*> textureData) noexcept : 
		_path(path), 
		_sdlSurface(surfaceData), 
		_sdlTexture(textureData) { }

	Image::~Image() noexcept
	{
		SDL_FreeSurface(_sdlSurface);
	}

	Image* Image::Load(in_value<char*> path) noexcept
	{
		SDL_Surface* surfaceData = IMG_Load(path);

		if (surfaceData == nullptr)
		{
			DEBUG_LOG_SDL_ERROR("Image failed to load: ");
			return nullptr;
		}

		SDL_Texture* textureData = SDL_CreateTextureFromSurface(Game::GetGraphics()->_sdlRenderer, surfaceData);

		if (textureData == nullptr)
		{
			DEBUG_LOG_SDL_ERROR("Image failed to load: ");
			return nullptr;
		}

		return new Image(path, surfaceData, textureData);
	}

	bool Image::TryLoad(in_value<char*> path, out<Image*> image) noexcept
	{
		image = Load(path);
		return image != nullptr;
	}

	const char* Image::GetPath() const noexcept { return _path; }

	Vector2I Image::GetSize() const noexcept { return Vector2I(GetWidth(), GetHeight()); }
	int Image::GetWidth() const noexcept { return _sdlSurface->w; }
	int Image::GetHeight() const noexcept { return _sdlSurface->h; }

	/*void Image::RenderBlankAsObject(in<PoseF> pose, in<Vector2F> pivot, in<Vector2F> size, in<Color> color, ImageBlendMode blendingMode)
	{

	}*/

	void Image::RenderAsObject(in_optional<RectI> sourceRect, in<PoseF> pose, in<Vector2F> pivot, in<Vector2F> scale, in<ImageFlipMode> flipMode, in<Color> color, ImageBlendMode blendingMode)
	{
		Vector2I imageSize = GetSize();

		RectF destinationRect = RectF(0.0f, 0.0f, 0.0f, 0.0f);
		double rotation = 0.0;
		Vector2F rotationCenter = Vector2F();

		_ObjectParamsToDefaultParams(pose, pivot, (Vector2F)(sourceRect.has_value() ? sourceRect.value().size : imageSize) * scale, destinationRect, rotation, rotationCenter);

		RenderAsDefault(sourceRect, destinationRect, rotation, rotationCenter, flipMode, color, blendingMode);
	}

	/*void Image::RenderBlankAsDefault(in_optional<RectF> destinationRect, in<double> rotation, in_optional<Vector2F> rotationCenter, in<Color> color, ImageBlendMode blendingMode)
	{
	
	}*/

	void Image::RenderAsDefault(in_optional<RectI> sourceRect, in_optional<RectF> destinationRect, in<double> rotationClockwise, in_optional<Vector2F> rotationCenter, in<ImageFlipMode> flipMode, in<Color> color, ImageBlendMode blendingMode)
	{
		SDL_Rect* srcRect = sourceRect.has_value() ? new SDL_Rect
		{
			sourceRect->position.x, sourceRect->position.y,
			sourceRect->size.x, sourceRect->size.y
		} : nullptr;

		SDL_FRect* dstRect = destinationRect.has_value() ? new SDL_FRect
		{
			destinationRect->position.x, destinationRect->position.y,
			destinationRect->size.x, destinationRect->size.y
		} : nullptr;

		SDL_FPoint* center = rotationCenter.has_value() ? new SDL_FPoint
		{
			rotationCenter->x, rotationCenter->y
		} : nullptr;

		SDL_Renderer* renderer = Game::GetGraphics()->_sdlRenderer;

		SDL_BlendMode blendMode = SDL_BlendMode::SDL_BLENDMODE_NONE;
		switch (blendingMode)
		{
		case ImageBlendMode::BLENDMODE_NONE:  blendMode = SDL_BlendMode::SDL_BLENDMODE_NONE;  break;
		case ImageBlendMode::BLENDMODE_BLEND: blendMode = SDL_BlendMode::SDL_BLENDMODE_BLEND; break;
		case ImageBlendMode::BLENDMODE_ADD:   blendMode = SDL_BlendMode::SDL_BLENDMODE_ADD;   break;
		case ImageBlendMode::BLENDMODE_MOD:   blendMode = SDL_BlendMode::SDL_BLENDMODE_MOD;   break;
		case ImageBlendMode::BLENDMODE_MUL:   blendMode = SDL_BlendMode::SDL_BLENDMODE_MUL;   break;
		}

		if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) != 0)
			DEBUG_LOG_SDL_ERROR("Failed to set renderer color: ");
		if (SDL_SetRenderDrawBlendMode(renderer, blendMode) != 0)
			DEBUG_LOG_SDL_ERROR("Failed to set renderer blend mode: ");
		if (SDL_RenderCopyExF(renderer, _sdlTexture, srcRect, dstRect, rotationClockwise, center, (SDL_RendererFlip)flipMode) != 0)
			DEBUG_LOG_SDL_ERROR("Failed to render image: ");
	}

	void Image::_ObjectParamsToDefaultParams(in<PoseF> pose, in<Vector2F> pivot, in<Vector2F> resultSize, ref<RectF> destinationRect, ref<double> rotation, ref<Vector2F> rotationCenter)
	{
		Vector2I screenSize = Game::GetGraphics()->GetScreenSize();

		destinationRect = RectF(
			pose.position.x - (resultSize.x * pivot.x), 
			screenSize.y - pose.position.y - (resultSize.y * pivot.y),
			resultSize.x,
			resultSize.y);

		rotation = pose.rotation;

		rotationCenter = Vector2F(pivot.x * resultSize.x, (1.0f - pivot.y) * resultSize.y);
	}
}