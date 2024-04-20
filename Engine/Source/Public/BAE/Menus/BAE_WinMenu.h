#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("WinMenu.h"))
#endif

#include <SDL2/SDL_syswm.h>

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(struct WinMenu))
#endif
class WinMenu
{
private:
	SDL_Window* _window;
	SDL_SysWMinfo _windowInfo;

public:
	WinMenu(SDL_Window* window);
	~WinMenu() = default;

	bool InitialiseMenu();

	void ActivatePopup(in<const char*> title, in<const char*> message);

	void ActivateWarningPopup(in<const char*> title, in<const char*> message);

	void ActivateErrorPopup(in<const char*> title, in<const char*> message);
};