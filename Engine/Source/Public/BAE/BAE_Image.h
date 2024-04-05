#pragma once
#include "BAE_Def.h"
#include <SDL2/SDL_image.h>
#include "Math/BAE_RectT.h"
#include "Math/BAE_VectorT.h"
#include "BAE_Game.h"

class Visual;

namespace bae
{
	enum ImageFlipMode : bae::int_fit_t<FLIP_VERTIAL>
	{
		FLIP_NONE,
		FLIP_HORIZONTAL,
		FLIP_VERTIAL
	};

	enum ImageBlendMode
	{
		BLENDMODE_NONE = 0x00000000,     /**< no blending
												  dstRGBA = srcRGBA */
		BLENDMODE_BLEND = 0x00000001,    /**< alpha blending
												  dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
												  dstA = srcA + (dstA * (1-srcA)) */
		BLENDMODE_ADD = 0x00000002,      /**< additive blending
												  dstRGB = (srcRGB * srcA) + dstRGB
												  dstA = dstA */
		BLENDMODE_MOD = 0x00000004,      /**< color modulate
												  dstRGB = srcRGB * dstRGB
												  dstA = dstA */
		BLENDMODE_MUL = 0x00000008,      /**< color multiply
												  dstRGB = (srcRGB * dstRGB) + (dstRGB * (1-srcA))
												  dstA = dstA */

		/* Additional custom blend modes can be returned by SDL_ComposeCustomBlendMode() */

	};

	struct Image
	{
		friend class Visual;

	private:
		SDL_Surface* _sdlSurface;
		SDL_Texture* _sdlTexture;

		const char* _path;

	public:
		/// <summary>
		/// Loads the image at the given path into memory and returns the pointer.
		/// </summary>
		/// <param name="path">- char[]</param>
		/// <returns>Image* or nullptr if failed.</returns>
		static Image* Load(in_array<char> path);
		/// <summary>
		/// Tries to load the image at the given path into memory and returns the pointer.
		/// </summary>
		/// <param name="path">- char[]</param>
		/// <param name="image">- OUT Image*</param>
		/// <returns>true if successful, false otherwise.</returns>
		static bool TryLoad(in_array<char> path, out<Image*> image);

		~Image();

		const char* GetPath() const;

		Vector2I GetSize() const;
		int GetWidth() const;
		int GetHeight() const;

		void Render(in<RectI> sourceRect, in<RectF> destinationRect, in<double> rotation, in<Vector2F> rotationCenter, in<ImageFlipMode> flipMode = ImageFlipMode::FLIP_NONE, in<Color> color = COLOR_WHITE)
		{
			SDL_Rect srcRect =
			{
				sourceRect.position.x, sourceRect.position.y,
				sourceRect.size.x, sourceRect.size.y
			};

			SDL_FRect dstRect =
			{
				destinationRect.position.x, destinationRect.position.y,
				destinationRect.size.x, destinationRect.size.y
			};

			SDL_FPoint center =
			{
				rotationCenter.x, rotationCenter.y
			};

			SDL_Renderer* renderer = Game::GetGraphics()->_sdlRenderer;

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)
			SDL_RenderCopyExF(renderer, _sdlTexture, &srcRect, &dstRect, rotation, &center, (SDL_RendererFlip)flipMode);
		}

	private:
		Image(in_array<char> path, in<SDL_Surface*> surfaceData);
	};
}

#include "Nodes/BAE_Visual.h"