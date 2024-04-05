#pragma once
#include "Nodes/BAE_Behaviour.h"
#include "Math/BAE_PoseT.h"
#include "BAE_Image.h"

class Graphics;

namespace bae
{
	class Visual : public Behaviour
	{
		friend class Graphics;

	public:
		Image* image;
		RectI sourceRect;
		PoseF offset;
		Vector2F pivot;
		Vector2F scale;

	protected:
		void Render()
		{

		}
	};
}

#include "BAE_Graphics.h"