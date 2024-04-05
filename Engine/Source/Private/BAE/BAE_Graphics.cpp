#include "BAE_Graphics.h"

namespace bae
{
	Graphics::Graphics() : 
		_sdlWindow(nullptr), 
		_sdlRenderer(nullptr)
	{
		_isWorking = false;

		_sdlWindow = SDL_CreateWindow("Bad Attempt Engine",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,
			0u);

		if (_sdlWindow == nullptr)
		{
			DEBUG_LOG_SDL_ERROR("Window failed to create: ");

			return;
		}

		_sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, 0u);

		if (_sdlRenderer == nullptr)
		{
			DEBUG_LOG_SDL_ERROR("Renderer failed to create: ");

			return;
		}

		_isWorking = true;
	}

	Graphics::~Graphics()
	{
		_isWorking = false;

		if (_sdlRenderer != nullptr)
		{
			SDL_DestroyRenderer(_sdlRenderer);
			_sdlRenderer = nullptr;
		}

		if (_sdlWindow != nullptr)
		{
			SDL_DestroyWindow(_sdlWindow);
			_sdlWindow = nullptr;
		}
	}

	void Graphics::MarkVisualHasBeenModified() noexcept
	{
		_visualsInZOrder.clear();
	}
}