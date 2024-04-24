#include "BAE_Debug.h"
#include "Math/BAE_Color.h"
#include "Nodes/BAE_Text.h"
#include "Nodes/BAE_Transform.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "BAE_Image.h"

namespace bae
{
	Text::Text(in<Node*> parent) noexcept :
		Visual::Visual(parent),
		isUI(false),
		font(nullptr),
		color(COLOR_WHITE),
		flipMode(ImageFlipMode::FLIP_NONE),
		blendingMode(ImageBlendMode::BLENDMODE_NONE),
		textAlignment(TextHorizonalAlignment::TEXT_ALIGNMENT_CENTER),
		offset(),
		pivot(0.5f, 0.5f),
		scale(1.0f, 1.0f),
		wrapTextAfterUnits({}),
		_lastFont(nullptr),
		_sdlSurface(nullptr),
		_sdlTexture(nullptr) { }

	Text::~Text() noexcept { }

	void Text::Create(in<const char*> name)
	{
		Visual::Create(name);
	}

	void Text::Destroy()
	{
		if (_sdlSurface != nullptr)
			SDL_FreeSurface(_sdlSurface);

		if (_sdlTexture != nullptr)
			SDL_DestroyTexture(_sdlTexture);

		Visual::Destroy();
	}

	void Text::Render(in<CameraTransform> camera)
	{
		if (font != nullptr)
		{
			PoseF pose = offset;

			Transform* parentTransform;
			if (TryFindParentOfTypeRecursive<Transform>(parentTransform))
				pose = parentTransform->TransformPose(pose);

			if (_lastText.compare(text) != 0 || _lastFont != font)
			{
				font->_CreateSDLComponents(text, wrapTextAfterUnits, _sdlSurface, _sdlTexture);
				_lastText = text;
				_lastFont = font;
			}

			Vector2F usedScale = scale;

			if (!isUI)
			{
				pose = camera.offset.InverseTransformPose(pose);
				pose.position *= camera.scale;
				usedScale *= camera.scale;
			}

			font->_RenderAsObject(
				_sdlSurface, 
				_sdlTexture,
				pose,
				pivot, 
				textAlignment, 
				usedScale,
				flipMode, 
				color, 
				blendingMode);
		}
	}
}