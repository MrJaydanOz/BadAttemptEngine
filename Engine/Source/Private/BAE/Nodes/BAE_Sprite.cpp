#include "BAE_Debug.h"
#include "Math/BAE_Color.h"
#include "Nodes/BAE_Sprite.h"
#include "Nodes/BAE_Transform.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "BAE_Image.h"

namespace bae
{
	Sprite::Sprite(in<Node*> parent) noexcept :
		Visual::Visual(parent),
		isUI(false),
		image(nullptr),
		clipRect({}),
		color(COLOR_WHITE),
		flipMode(ImageFlipMode::FLIP_NONE),
		blendingMode(ImageBlendMode::BLENDMODE_NONE),
		offset(),
		pivot(0.5f, 0.5f),
		scale(1.0f, 1.0f) { }

	Sprite::~Sprite() noexcept { }

	void Sprite::Create(in<const char*> name)
	{
		Visual::Create(name);
	}

	void Sprite::Destroy()
	{
		Visual::Destroy();
	}

	void Sprite::Render(in<CameraTransform> camera)
	{
		if (image != nullptr)
		{
			PoseF pose = offset;

			Transform* parentTransform;
			if (TryFindParentOfTypeRecursive<Transform>(parentTransform))
				pose = parentTransform->TransformPose(pose);

			DEBUG_LOG_INFO(camera.offset << ", " << camera.scale);

			Vector2F usedScale = scale;

			if (!isUI)
			{
				pose = camera.offset.InverseTransformPose(pose);
				pose.position *= camera.scale;
				usedScale *= camera.scale;
			}

			image->RenderAsObject(
				clipRect, 
				pose,
				pivot,
				usedScale,
				flipMode, 
				color, 
				blendingMode);
		}
	}
}