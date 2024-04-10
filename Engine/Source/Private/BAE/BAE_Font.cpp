#include "BAE_Font.h"

#include "BAE_Def.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "BAE_Debug.h"
#include "Math/BAE_RectT.h"
#include "Math/BAE_VectorT.h"
#include "BAE_Game.h"

namespace bae
{
	Font::Font(in<TTF_Font*> sdlFont) noexcept :
		_sdlFont(sdlFont) { }

	Font::~Font() noexcept
	{
		TTF_CloseFont(_sdlFont);
	}

	Font* Font::Load(in_value<char*> path, in<int> fontSize) noexcept
	{
		TTF_Font* sdlFont = TTF_OpenFont(path, fontSize);

		if (sdlFont == nullptr)
		{
			DEBUG_LOG_SDL_ERROR("Font failed to load: ");
			return nullptr;
		}

		return new Font(sdlFont);
	}

	bool Font::TryLoad(in_value<char*> path, in<int> fontSize, out<Font*> font) noexcept
	{
		font = Load(path, fontSize);
		return font != nullptr;
	}

	void Font::_CreateSDLComponents(in<std::string> text, in_optional<int> textWrapAtPixel, ref<SDL_Surface*> sdlSurface, ref<SDL_Texture*> sdlTexture)
	{
		if (sdlTexture != nullptr)
		{
			SDL_DestroyTexture(sdlTexture);
		}

		if (sdlSurface != nullptr)
		{
			SDL_FreeSurface(sdlSurface);
		}

		sdlSurface = TTF_RenderUTF8_Solid_Wrapped(_sdlFont, text.data(), SDL_Color(255, 255, 255, 255), textWrapAtPixel.value_or(0));
		sdlTexture = SDL_CreateTextureFromSurface(Game::GetGraphics()->_sdlRenderer, sdlSurface);
	}

	void Font::_RenderAsObject(ref<SDL_Surface*> sdlSurface, ref<SDL_Texture*> sdlTexture, in<PoseF> pose, in<Vector2F> pivot, in<TextHorizonalAlignment> textAlignment, in<Vector2F> scale, in<ImageFlipMode> flipMode, in<Color> color, ImageBlendMode blendingMode)
	{
		Vector2I imageSize = Vector2I(sdlSurface->w, sdlSurface->h);

		RectF destinationRect = RectF(0.0f, 0.0f, 0.0f, 0.0f);
		double rotation = 0.0;
		Vector2F rotationCenter = Vector2F();

		_ObjectParamsToDefaultParams(pose, pivot, ((Vector2F)imageSize) * scale, destinationRect, rotation, rotationCenter);

		_RenderAsDefault(sdlSurface, sdlTexture, destinationRect, textAlignment, rotation, rotationCenter, flipMode, color, blendingMode);
	}

	void Font::_RenderAsDefault(ref<SDL_Surface*> sdlSurface, ref<SDL_Texture*> sdlTexture, in_optional<RectF> destinationRect, in<TextHorizonalAlignment> textAlignment, in<double> rotationClockwise, in_optional<Vector2F> rotationCenter, in<ImageFlipMode> flipMode, in<Color> color, ImageBlendMode blendingMode)
	{
		SDL_FRect* dstRect = destinationRect.has_value() ? new SDL_FRect
		{
			destinationRect->position.x, destinationRect->position.y,
			destinationRect->size.x, destinationRect->size.y
		} : new SDL_FRect
		{
			0.0f, 0.0f,
			(float)sdlSurface->w, (float)sdlSurface->h
		};

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

		int textAlignMode = 0;
		switch (textAlignment)
		{
		case TextHorizonalAlignment::TEXT_ALIGNMENT_LEFT: textAlignMode = TTF_WRAPPED_ALIGN_LEFT; break;
		case TextHorizonalAlignment::TEXT_ALIGNMENT_CENTER: textAlignMode = TTF_WRAPPED_ALIGN_CENTER; break;
		case TextHorizonalAlignment::TEXT_ALIGNMENT_RIGHT: textAlignMode = TTF_WRAPPED_ALIGN_RIGHT; break;
		}

		TTF_SetFontWrappedAlign(_sdlFont, textAlignMode);
		SDL_SetTextureColorMod(sdlTexture, color.r, color.g, color.b);
		SDL_SetTextureAlphaMod(sdlTexture, color.a);
		if (SDL_SetRenderDrawBlendMode(renderer, blendMode) != 0)
			DEBUG_LOG_SDL_ERROR("Failed to set renderer blend mode: ");
		if (SDL_RenderCopyExF(renderer, sdlTexture, nullptr, dstRect, rotationClockwise, center, (SDL_RendererFlip)flipMode) != 0)
			DEBUG_LOG_SDL_ERROR("Failed to render text: ");
	}

	void Font::_ObjectParamsToDefaultParams(in<PoseF> pose, in<Vector2F> pivot, in<Vector2F> resultSize, ref<RectF> destinationRect, ref<double> rotation, ref<Vector2F> rotationCenter)
	{
		Vector2I screenSize = Game::GetGraphics()->GetScreenSize();

		destinationRect = RectF(
			pose.position.x - (resultSize.x * pivot.x),
			screenSize.y - pose.position.y - (resultSize.y * (1.0f - pivot.y)),
			resultSize.x,
			resultSize.y);

		rotation = pose.rotation;

		rotationCenter = Vector2F(pivot.x * resultSize.x, (1.0f - pivot.y) * resultSize.y);
	}
}