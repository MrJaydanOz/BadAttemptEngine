#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Image.h"))
#endif
#include "Math/BAE_RectT.h"
#include "Math/BAE_VectorT.h"
#include "Math/BAE_Color.h"
#include "Math/BAE_PoseT.h"

struct SDL_Surface;
struct SDL_Texture;

namespace bae
{
#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(enum class ImageFlipMode))
#endif
	enum class ImageFlipMode : int_fit_t<2>
	{
		FLIP_NONE,
		FLIP_HORIZONTAL,
		FLIP_VERTICAL
	};

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(enum class ImageBlendMode))
#endif
	enum class ImageBlendMode : int_fit_t<4>
	{
		/// <summary>No blending</summary>
		/// <param name="dst.RGBA">= src.RGBA</param>
		BLENDMODE_NONE,
		/// <summary>Alpha blending</summary>
		/// <param name="dst.RGB">= (src.RGB * src.A) + (dst.RGB * (1 - src.A))</param>
		/// <param name="dst.A">= src.A + (dst.A * (1 - src.A))</param>
		BLENDMODE_BLEND,
		/// <summary>Additive blending</summary>
		/// <param name="dst.RGB">= (src.RGB * src.A) + dst.RGB</param>
		/// <param name="dst.A">= dst.A</param>
		BLENDMODE_ADD,
		/// <summary>Modulative blending</summary>
		/// <param name="dst.RGB">= srcRGB + dst.RGB</param>
		/// <param name="dst.A">= dst.A</param>
		BLENDMODE_MOD,
		/// <summary>Modulative blending</summary>
		/// <param name="dst.RGB">= (src.RGB * dst.RGB) + (dst.RGB * (1 - src.A))</param>
		/// <param name="dst.A">= dst.A</param>
		BLENDMODE_MUL
	};

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(struct Image))
#endif
	struct Image
	{
		friend class Graphics;

	private:
		SDL_Surface* _sdlSurface;
		SDL_Texture* _sdlTexture;

		static Image* _whitePixel;

	public:
		/// <summary>
		/// Loads the image at the given path into memory and returns the pointer.
		/// </summary>
		/// <param name="path">- char[]</param>
		/// <returns>Image* or nullptr if failed.</returns>
		_NODISCARD static Image* Load(in<const char*> path) noexcept;

		/// <summary>
		/// Tries to load the image at the given path into memory and returns the pointer.
		/// </summary>
		/// <param name="path">- char[]</param>
		/// <param name="image">- OUT Image*</param>
		/// <returns>true if successful, false otherwise.</returns>
		static bool TryLoad(in<const char*> path, out<Image*> image) noexcept;

		~Image() noexcept;

		_NODISCARD Vector2I GetSize() const noexcept;
		_NODISCARD int GetWidth() const noexcept;
		_NODISCARD int GetHeight() const noexcept;

		_NODISCARD static Image* WhitePixel();

		void RenderAsObject(in_optional<RectI> sourceRect, in<PoseF> pose, in<Vector2F> pivot, in<Vector2F> scale = Vector2F(1.0f, 1.0f), in<ImageFlipMode> flipMode = ImageFlipMode::FLIP_NONE, in<Color> color = COLOR_WHITE, ImageBlendMode blendingMode = ImageBlendMode::BLENDMODE_NONE);

		void RenderAsDefault(in_optional<RectI> sourceRect, in_optional<RectF> destinationRect, in<double> rotation = 0.0, in_optional<Vector2F> rotationCenter = {}, in<ImageFlipMode> flipMode = ImageFlipMode::FLIP_NONE, in<Color> color = COLOR_WHITE, ImageBlendMode blendingMode = ImageBlendMode::BLENDMODE_NONE);

	private:
		Image(in<SDL_Surface*> sdlSurface, in<SDL_Texture*> sdlTexture) noexcept;
	
		static void _ObjectParamsToDefaultParams(in<PoseF> pose, in<Vector2F> pivot, in<Vector2F> resultSize, ref<RectF> destinationRect, ref<double> rotation, ref<Vector2F> rotationCenter);

		static void _DeleteStatics() noexcept;
	};
}