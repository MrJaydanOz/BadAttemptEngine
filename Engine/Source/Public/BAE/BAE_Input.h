#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Input.h"))
#endif

namespace bae
{
	class Game;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Input))
#endif
	class Input
	{
		friend class Game;

	private:
		bool _isWorking;

	private:
		Input();
		~Input();
	};
}