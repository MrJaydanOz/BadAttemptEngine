#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Graphics.h"))
#endif
#include "BAE_Debug.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <deque>
#include "Math/BAE_VectorT.h"

// !! TEMPORARY SOLUTION !!
#include "Nodes/BAE_Node.h"

namespace bae
{
	class Game;
	class Visual;
	struct Image;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Graphics))
#endif
	class Graphics
	{
		friend class Game;
		friend class Visual;
		friend struct Image;

	private:
		SDL_Window* _sdlWindow;
		SDL_Renderer* _sdlRenderer;
		// !! TEMPORARY SOLUTION !!
		//std::deque<Visual*> _visualsInZOrder;
		std::deque<Visual*>* _visualsInZOrder;
		bool _isWorking;

	public:
		_NODISCARD Vector2I GetScreenSize();

	private:
		Graphics();
		~Graphics();

		void Render();

		void _MarkVisualHasBeenModified(Visual* visual) noexcept;

		void _MarkVisualHasBeenDeleted(Visual* visual) noexcept;

		// !! TEMPORARY SOLUTION !!
		template<typename T, typename TDelegate>
		void _ForeachVisualAndChildren(Node* node, in_delegate<TDelegate> action) const noexcept
		{
			T* castedNode = dynamic_cast<T*>(node);
			if (castedNode != nullptr)
				action(castedNode);

			for (Node* child : node->GetChildren())
				if (child != nullptr)
					_ForeachVisualAndChildren<T, TDelegate>(child, action);
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(node) << " has a null child.");
		}

		/*bool _CompareVisuals(Visual* a, Visual* b) noexcept;*/
	};
}