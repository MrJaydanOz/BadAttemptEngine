#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Physics.h"))
#endif

namespace bae
{
	class Game;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Physics))
#endif
	class Physics
	{
		friend class Game;

	private:
		bool _isWorking;

	private:
		Physics();
		~Physics();
	};
}