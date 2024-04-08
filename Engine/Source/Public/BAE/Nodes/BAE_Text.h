#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Sprite.h"))
#endif

#include "Nodes/BAE_Transform.h"
#include "Nodes/BAE_Visual.h"
#include "Math/BAE_RectT.h"
#include "Math/BAE_Color.h"
#include "BAE_Font.h"

struct SDL_Surface;
struct SDL_Texture;

namespace bae
{
	class Scene;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Text))
#endif
	class Text : public Visual
	{
		NODE_BEGIN;

	public:
		std::string text;
		Font* font;
		Color color;
		ImageFlipMode flipMode;
		ImageBlendMode blendingMode;
		TextHorizonalAlignment textAlignment;
		PoseF offset;
		Vector2F pivot;
		Vector2F scale;
		std::optional<float> wrapTextAfterUnits;

	private:
		std::string _lastText;
		Font* _lastFont;
		SDL_Surface* _sdlSurface;
		SDL_Texture* _sdlTexture;

	public:
		virtual ~Text() noexcept override;

	protected:
		Text(in<std::string> name = "", in<bool> enabled = true) noexcept;
		Text(in<bool> enabled) noexcept;

		virtual void Render() override;
	};
}