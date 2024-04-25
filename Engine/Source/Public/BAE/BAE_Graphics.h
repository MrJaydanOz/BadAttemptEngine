#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Graphics.h"))
#endif
#include "BAE_Debug.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math/BAE_VectorT.h"
#include "Math/BAE_Color.h"
#include "Menus/BAE_WinMenu.h"
#include "BAE_CameraTransform.h"

// !! TEMPORARY SOLUTION !!
#include "Nodes/BAE_Node.h"

namespace bae
{
	class Game;
	class Visual;
	struct Image;
	struct Font;

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Camera))
#endif
	struct Camera
	{
	public:
		PoseF center;
		float size;
		float sizeAxisFactor;

	public:
		float CalculateUnitsPerPixel(in<Vector2F> screenSize) const;

		CameraTransform CalculateTransform(in<float> unitsPerPixel) const;
	};

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Graphics))
#endif
	class Graphics
	{
		friend class Game;
		friend class Visual;
		friend struct Image;
		friend struct Font;

	public:
		Camera camera;

	private:
		SDL_Window* _sdlWindow;
		SDL_Renderer* _sdlRenderer;
		// !! TEMPORARY SOLUTION !!
		//bae::List<Visual*> _visualsInZOrder;
		bae::List<Visual*>* _visualsInZOrder;
		bool _isWorking;
		Color _backgroundColor;
		WinMenu* _winMenu;

	public:
		_NODISCARD Vector2I GetScreenSize() const noexcept;

		_NODISCARD Color GetBackgroundColor() const noexcept;
		void SetBackgroundColor(in<Color> color) noexcept;

		_NODISCARD WinMenu* GetWinMenu() const noexcept;

		_NODISCARD Vector2F WorldToScreenPoint(in<Vector2F> point) const noexcept;

		_NODISCARD Vector2F ScreenToWorldPoint(in<Vector2F> point) const noexcept;

		_NODISCARD Vector2I PixelToScreenPoint(in<Vector2I> pixel);
		_NODISCARD Vector2F PixelToScreenPoint(in<Vector2F> pixel);

		_NODISCARD Vector2I ScreenToPixelPoint(in<Vector2I> point);
		_NODISCARD Vector2F ScreenToPixelPoint(in<Vector2F> point);

		_NODISCARD Vector2F PixelToWorldPoint(in<Vector2I> pixel);
		_NODISCARD Vector2F PixelToWorldPoint(in<Vector2F> pixel);

		_NODISCARD Vector2F WorldToPixelPoint(in<Vector2F> point);

	private:
		Graphics();
		~Graphics();

		void _Render();

		void _MarkVisualHasBeenModified(Visual* visual) noexcept;

		void _MarkVisualHasBeenDeleted(Visual* visual) noexcept;

		// !! TEMPORARY SOLUTION !!
		template<typename T, typename TDelegate>
		void _ForeachVisualAndChildren(Node* node, in_delegate<TDelegate> action) const noexcept
		{
			if (node == nullptr)
				return;

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