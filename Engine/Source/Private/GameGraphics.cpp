#include "GameGraphics.h"
#include <SDL2/SDL_image.h>
#include "Debug.h"

Graphics::Graphics(const char* title, int posX, int posY, int sizeX, int sizeY, unsigned int flags) noexcept :
	backgroundColor(COLOR_BLACK),
	_renderBuffer(nullptr),
	_renderBufferSize(0, 0),
	_renderLayerFlags()
{
	_window = SDL_CreateWindow(title, posX, posY, sizeX, sizeY, flags);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

Graphics::~Graphics() noexcept
{
	if (_renderer != nullptr)
	{
		SDL_DestroyRenderer(_renderer);
	}

	if (_window != nullptr)
	{
		SDL_DestroyWindow(_window);
	}
}

void Graphics::DoRender()
{
	if (_window == nullptr)
	{
		DEBUG_LOG_ERROR_CONTEXTED(BAE_LOG_CONTEXT, "Game window is not initialized but the engine is trying to draw to it.");
		return;
	}

	if (_renderer == nullptr)
	{
		DEBUG_LOG_ERROR_CONTEXTED(BAE_LOG_CONTEXT, "Game renderer is not initialized but the engine is trying to draw with it.");
		return;
	}

	Camera* mainCamera = Game::GetGame()->GetMainCamera();

	if (mainCamera == nullptr)
	{
		DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "There is no main camera but the engine is trying to draw with it.");
		return;
	}

	Vector2I rendererSize = Vector2I(0, 0);

	SDL_GetRendererOutputSize(_renderer, &rendererSize.x, &rendererSize.y);

	if (_renderBuffer == nullptr || _renderBufferSize != rendererSize)
	{
		if (_renderBuffer != nullptr)
			SDL_DestroyTexture(_renderBuffer);

		_renderBufferSize = rendererSize;
		_renderBuffer = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rendererSize.x, rendererSize.y);
	}

	SDL_SetRenderDrawColor(_renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_SetRenderTarget(_renderer, nullptr);

	SDL_RenderClear(_renderer);

	std::vector<VisualsInRenderLayer> visualsInRenderLayers = Game::GetGame()->GetGraphics()->_visualsInRenderLayers;

	for (const VisualsInRenderLayer& layer : visualsInRenderLayers)
	{
		SDL_SetRenderTarget(_renderer, _renderBuffer);
		SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(_renderer);

		for (Visual* visual : layer.visualsInZOrder)
		{
			if (visual->IsEnabled(true))
				visual->Render(_renderer, mainCamera);
		}

		SDL_SetTextureBlendMode(_renderBuffer, SDL_BLENDMODE_BLEND);
		SDL_RenderCopy(_renderer, _renderBuffer, nullptr, nullptr);

		SDL_SetRenderTarget(_renderer, nullptr);
	}

	SDL_RenderPresent(_renderer);
}