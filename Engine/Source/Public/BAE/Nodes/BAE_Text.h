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
#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Text))
#endif
	class Text : public Visual
	{
		NODE_BEGIN;

	public:
		bool isUI;
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

	protected:
		Text(in<Node*> parent) noexcept;
		virtual ~Text() noexcept override;
		virtual void Create(in<const char*> name = "") override;
		virtual void Destroy() override;

		virtual void Render(in<CameraTransform> camera) override;
	};
}