#include "BAE_Debug.h"
#include "Math/BAE_Color.h"
#include "Nodes/BAE_Sprite.h"
#include "Nodes/BAE_Transform.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "BAE_Image.h"

namespace bae
{
	Sprite::Sprite(in<std::string> name, in<bool> enabled) noexcept : 
		Visual::Visual(name, enabled),
		image(nullptr),
		clipRect({}),
		color(COLOR_WHITE),
		flipMode(ImageFlipMode::FLIP_NONE),
		blendingMode(ImageBlendMode::BLENDMODE_NONE),
		offset(),
		pivot(0.5f, 0.5f),
		scale(1.0f, 1.0f) { }

	Sprite::Sprite(in<bool> enabled) noexcept : 
		Sprite::Sprite("", enabled) { }

	Sprite::~Sprite() noexcept
	{
		Visual::~Visual();
	}

	Sprite* Sprite::CloneInto(Node* parent) noexcept
	{
		Sprite* newNode = CloneIntoBegin<Sprite>(parent, GetName(), IsEnabledSelf());
		newNode->image = image;
		newNode->clipRect = clipRect;
		newNode->color = color;
		newNode->flipMode = flipMode;
		newNode->blendingMode = blendingMode;
		newNode->offset = offset;
		newNode->pivot = pivot;
		newNode->scale = scale;

		return newNode;
	}

	void Sprite::Render()
	{
		if (image != nullptr)
		{
			PoseF pose = offset;

			Transform* parentTransform;
			if (TryFindParentOfTypeRecursive<Transform>(parentTransform))
			{
				parentTransform->CacheWorldPose();
				pose = parentTransform->TransformPose(pose);
			}

			image->RenderAsObject(clipRect, pose, pivot, scale, flipMode, color, blendingMode);
		}
	}
}