#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Font.h"))
#endif
#include "BAE_Image.h"
#include "BAE_Game.h"
#include <SDL2/SDL_ttf.h>

struct SDL_Surface;
struct SDL_Texture;

namespace bae
{
	class Text;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(enum class TextHorizonalAlignment))
#endif
	enum class TextHorizonalAlignment : int_fit_t<2>
	{
		TEXT_ALIGNMENT_LEFT,
		TEXT_ALIGNMENT_CENTER,
		TEXT_ALIGNMENT_RIGHT
	};

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(struct Font))
#endif
	struct Font
	{
		friend class Text;

	private:
		TTF_Font* _sdlFont;

	public:
		/// <summary>
		/// Loads the font at the given path into memory and returns the pointer.
		/// </summary>
		/// <returns>Image* or nullptr if failed.</returns>
		_NODISCARD static Font* Load(in_value<char*> path, in<int> fontSize) noexcept;

		/// <summary>
		/// Tries to load the font at the given path into memory and returns the pointer.
		/// </summary>
		/// <returns>true if successful, false otherwise.</returns>
		static bool TryLoad(in_value<char*> path, in<int> fontSize, out<Font*> font) noexcept;

		~Font() noexcept;

	private:
		Font(in<TTF_Font*> sdlFont) noexcept;

		void _CreateSDLComponents(in<std::string> text, in_optional<int> textWrapAtPixel, ref<SDL_Surface*> sdlSurface, ref<SDL_Texture*> sdlTexture);

		void _RenderAsObject(ref<SDL_Surface*> sdlSurface, ref<SDL_Texture*> sdlTexture, in<PoseF> pose, in<Vector2F> pivot, in<TextHorizonalAlignment> textAlignment, in<Vector2F> scale = Vector2F(1.0f, 1.0f), in<ImageFlipMode> flipMode = ImageFlipMode::FLIP_NONE, in<Color> color = COLOR_WHITE, ImageBlendMode blendingMode = ImageBlendMode::BLENDMODE_NONE);

		void _RenderAsDefault(ref<SDL_Surface*> sdlSurface, ref<SDL_Texture*> sdlTexture, in_optional<RectF> destinationRect, in<TextHorizonalAlignment> textAlignment, in<double> rotationClockwise = 0.0, in_optional<Vector2F> rotationCenter = {}, in<ImageFlipMode> flipMode = ImageFlipMode::FLIP_NONE, in<Color> color = COLOR_WHITE, ImageBlendMode blendingMode = ImageBlendMode::BLENDMODE_NONE);

		static void _ObjectParamsToDefaultParams(in<PoseF> pose, in<Vector2F> pivot, in<Vector2F> resultSize, ref<RectF> destinationRect, ref<double> rotation, ref<Vector2F> rotationCenter);
	};
}