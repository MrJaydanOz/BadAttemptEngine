#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Sprite.h"))
#endif

#include "Nodes/BAE_Transform.h"
#include "Nodes/BAE_Visual.h"
#include "Math/BAE_RectT.h"
#include "Math/BAE_Color.h"
#include "BAE_Image.h"

namespace bae
{
	class Scene;

	#if defined(MESSAGE_WHEN_CLASS_DEFINED)
	#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Sprite))
	#endif
	class Sprite : public Visual
	{
		NODE_BEGIN;

	public:
		Image* image;
		std::optional<RectI> clipRect;
		Color color;
		ImageFlipMode flipMode;
		ImageBlendMode blendingMode;
		PoseF offset;
		Vector2F pivot;
		Vector2F scale;

	public:
		virtual ~Sprite() noexcept override;

	protected:
		Sprite(in<std::string> name = "", in<bool> enabled = true) noexcept;
		Sprite(in<bool> enabled) noexcept;

		virtual void Render() override;
	};
}