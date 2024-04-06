#include "BAE_Graphics.h"
#include <algorithm>
#include "Nodes/BAE_Node.h"
#include "BAE_Scene.h"
#include "BAE_Game.h"
#include "Nodes/BAE_Visual.h"

namespace bae
{
	Vector2I Graphics::GetScreenSize()
	{
		Vector2I size;
		SDL_GetRendererOutputSize(_sdlRenderer, &size.x, &size.y);
		return size;
	}

	Graphics::Graphics() :
		_sdlWindow(nullptr), 
		_sdlRenderer(nullptr),
		_visualsInZOrder(nullptr)
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

	void Graphics::Render()
	{
		// !! TEMPORARY SOLUTION !!
		if (_visualsInZOrder == nullptr)
		{
			_visualsInZOrder = new std::deque<Visual*>();

			for (Node* child : Game::GetScene()->GetRootNodes())
			{
				_ForeachVisualAndChildren<Visual>(child, [&](in<Visual*> node) -> void
					{
						_visualsInZOrder->insert(
							std::upper_bound(_visualsInZOrder->begin(), _visualsInZOrder->end(), node, [](in<Visual*> a, in<Visual*> b) -> bool
								{ return a->GetZIndex() < b->GetZIndex(); }),
							node);
					});
			}
		}

		auto end = _visualsInZOrder->end();
		for (auto i = _visualsInZOrder->begin(); i < end; i++)
			(*i)->Render();
	}

	void Graphics::_MarkVisualHasBeenModified(Visual* visual) noexcept
	{
		// !! TEMPORARY SOLUTION !!
		if (_visualsInZOrder != nullptr)
		{
			_visualsInZOrder->clear();
			delete _visualsInZOrder;
		}

		//std::lower_bound(_visualsInZOrder.begin(), _visualsInZOrder.end(), visual, _CompareVisuals);
	}

	void Graphics::_MarkVisualHasBeenDeleted(Visual* visual) noexcept
	{
		// !! TEMPORARY SOLUTION !!
		_MarkVisualHasBeenModified(visual);
	}

	/*bool Graphics::_CompareVisuals(Visual* a, Visual* b) noexcept
	{
		const int aZIndex = a->GetZIndex();
		const int bZIndex = b->GetZIndex();

		if (aZIndex != bZIndex)
			return aZIndex < bZIndex;
		else
		{
			size_t aIndex
		}
	}*/
}