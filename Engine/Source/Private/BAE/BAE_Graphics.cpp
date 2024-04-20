#include "BAE_Graphics.h"
#include <algorithm>
#include "Nodes/BAE_Node.h"
#include "BAE_Scene.h"
#include "BAE_Game.h"
#include "Nodes/BAE_Visual.h"

namespace bae
{
	Vector2I Graphics::GetScreenSize() const noexcept
	{
		Vector2I size;
		SDL_GetRendererOutputSize(_sdlRenderer, &size.x, &size.y);
		return size;
	}

	Color Graphics::GetBackgroundColor() const noexcept
	{ return _backgroundColor; }

	void Graphics::SetBackgroundColor(in<Color> color) noexcept
	{ _backgroundColor = color; }

	WinMenu* Graphics::GetWinMenu() const noexcept
	{ return _winMenu; }

	Graphics::Graphics() :
		_sdlWindow(nullptr), 
		_sdlRenderer(nullptr),
		_visualsInZOrder(nullptr),
		_backgroundColor(COLOR_BLACK),
		_winMenu(nullptr)
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

		_winMenu = new WinMenu(_sdlWindow);

		if (!_winMenu->InitialiseMenu())
		{
			return;
		}

		_isWorking = true;
	}

	Graphics::~Graphics()
	{
		_isWorking = false;

		if (_winMenu != nullptr)
			delete _winMenu;

		if (_sdlRenderer != nullptr)
			SDL_DestroyRenderer(_sdlRenderer);

		if (_sdlWindow != nullptr)
			SDL_DestroyWindow(_sdlWindow);
	}

	void Graphics::_Render()
	{
		// !! TEMPORARY SOLUTION !!
		if (_visualsInZOrder == nullptr)
		{
			_visualsInZOrder = new bae::List<Visual*>();

			for (Node* child : Game::GetScene()->GetRootNodes())
			{
				_ForeachVisualAndChildren<Visual>(child, [&](Visual* node) -> void
					{
						_visualsInZOrder->InsertAt(_visualsInZOrder->FindIf([&](in<Visual*> v) -> bool
							{ return v->GetZIndex() > node->GetZIndex(); }), node);
					});
			}
		}

		SDL_SetRenderDrawBlendMode(_sdlRenderer, SDL_BLENDMODE_NONE);
		SDL_SetRenderDrawColor(_sdlRenderer, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
		SDL_RenderFillRect(_sdlRenderer, nullptr);

		for (Visual* visual : *_visualsInZOrder)
			visual->Render();

		SDL_RenderPresent(_sdlRenderer);
	}

	void Graphics::_MarkVisualHasBeenModified(Visual* visual) noexcept
	{
		// !! TEMPORARY SOLUTION !!
		if (_visualsInZOrder != nullptr)
		{
			delete _visualsInZOrder;
			_visualsInZOrder = nullptr;
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