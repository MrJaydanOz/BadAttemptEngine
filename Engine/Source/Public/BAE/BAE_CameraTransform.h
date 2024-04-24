#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_CameraTransform.h"))
#endif
#include "Math/BAE_PoseT.h"

namespace bae
{
	#if defined(MESSAGE_WHEN_CLASS_DECLARED)
	#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class CameraTransform))
	#endif
	struct CameraTransform
	{
	public:
		PoseF offset;
		float scale;
	};
}