#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Nodes/BAE_Node.h"
#include <vector>
#include "Nodes/BAE_Visual.h"
#include "BAE_Game.h"

struct Image;

namespace bae
{
	class Graphics
	{
		friend class Game;
		friend struct Image;

	private:
		SDL_Window* _sdlWindow;
		SDL_Renderer* _sdlRenderer;
		std::vector<Visual*> _visualsInZOrder;
		bool _isWorking;

	private:
		Graphics();
		~Graphics();

		void MarkVisualHasBeenModified() noexcept;
	};
}

#include "BAE_Image.h"