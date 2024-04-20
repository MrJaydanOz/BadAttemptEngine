#include "Menus/BAE_WinMenu.h"

#include <Windows.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_messagebox.h>
#include "BAE_Resources.h"
#include "BAE_Debug.h"

WinMenu::WinMenu(SDL_Window* window) : 
	_window(window)
{
	SDL_VERSION(&_windowInfo.version);

	SDL_GetWindowWMInfo(_window, &_windowInfo);
}

bool WinMenu::InitialiseMenu()
{
	HWND sysWMInfo = _windowInfo.info.win.window;

	HINSTANCE windowInstance = GetModuleHandle(0);

	LPCWSTR vSMenuStr = MAKEINTRESOURCE(IDR_MENU1);

	HMENU sysWMenu = LoadMenu(windowInstance, vSMenuStr);

	if (!SetMenu(sysWMInfo, sysWMenu))
	{
		DEBUG_LOG_ERROR_CONTEXTED(BAE_LOG_CONTEXT, "Windows could not assign menu.");
		return false;
	}

	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

	return true;
}

void WinMenu::ActivatePopup(in<const char*> title, in<const char*> message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, _window);
}

void WinMenu::ActivateWarningPopup(in<const char*> title, in<const char*> message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title, message, _window);
}

void WinMenu::ActivateErrorPopup(in<const char*> title, in<const char*> message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, _window);
}