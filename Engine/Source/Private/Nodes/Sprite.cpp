#include "Nodes/Sprite.h"
#include <string>
#include <cmath>
#include "Debug.h"

Sprite::Sprite(int zOrder, int renderLayer) noexcept : Sprite("", zOrder, renderLayer) { }

Sprite::Sprite(const std::string& name, int zOrder, int renderLayer) noexcept : Visual(name, zOrder, renderLayer), Transform(name),
	image(nullptr),
	clipRectangle(0, 0, 0, 0),
	color(COLOR_WHITE),
	blendingMode(VisualBlendingMode_None),
	flipMode(SpriteFlipMode_None),
	scale(1.0f, 1.0f),
	pivot(0.5f, 0.5f)
{ }

Sprite::~Sprite() noexcept
{
	Transform::~Transform();
}

void Sprite::Render(SDL_Renderer* renderer, const Camera* camera)
{
	if (image != nullptr)
	{
		Vector2I imageSize = image->GetSize();

		RectI clipRect = clipRectangle;
		if (clipRect.min.x < 0) clipRect.min.x += imageSize.x;
		if (clipRect.min.y < 0) clipRect.min.y += imageSize.y;
		if (clipRect.max.x <= 0) clipRect.min.x += imageSize.x;
		if (clipRect.max.y <= 0) clipRect.min.y += imageSize.y;

		SDL_Rect sdlClipRect = 
		{ 
			clipRect.min.x, 
			clipRect.min.y, 
			clipRect.max.x - clipRect.min.x, 
			clipRect.max.y - clipRect.min.y
		};

		PoseF pose = GetPose();

		SDL_FRect sdlDestinationRect =
		{
			pose.position.x - (pivot.x * imageSize.x * scale.x),
			pose.position.y - (pivot.y * imageSize.y * scale.y),
			imageSize.x * scale.x,
			imageSize.y * scale.y
		};

		SDL_FPoint sdlPivotPoint =
		{
			pivot.x * imageSize.x * scale.x,
			pivot.y * imageSize.y * scale.y
		};

		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		if (SDL_RenderCopyExF(renderer, image->_sdlTexture, &sdlClipRect, &sdlDestinationRect, -pose.rotation, &sdlPivotPoint, (SDL_RendererFlip)flipMode) < 0)
			DEBUG_LOG_SDL_ERROR("Error drawing sprite:");
	}
}