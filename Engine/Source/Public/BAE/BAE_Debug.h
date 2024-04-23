#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Debug.h"))
#endif
#include <iostream>

#if false
#define THROW_EXCEPTIONS_INSTEAD_OF_LOG
#endif

#define CONSOLE_COLORID_DEFAULT "0"
#define CONSOLE_COLORID_BLACK "30"
#define CONSOLE_COLORID_DARK_BLUE "34"
#define CONSOLE_COLORID_DARK_GREEN "32"
#define CONSOLE_COLORID_LIGHT_BLUE "36"
#define CONSOLE_COLORID_DARK_RED "31"
#define CONSOLE_COLORID_MAGENTA "35"
#define CONSOLE_COLORID_ORANGE "33"
#define CONSOLE_COLORID_LIGHT_GRAY "37"
#define CONSOLE_COLORID_LIGHT_GREY DEBUG_CONSOLE_COLORID_LIGHT_GRAY
#define CONSOLE_COLORID_GRAY "90"
#define CONSOLE_COLORID_GREY DEBUG_CONSOLE_COLORID_GRAY
#define CONSOLE_COLORID_BLUE "94"
#define CONSOLE_COLORID_GREEN "92"
#define CONSOLE_COLORID_CYAN "96"
#define CONSOLE_COLORID_RED "91"
#define CONSOLE_COLORID_PINK "95"
#define CONSOLE_COLORID_YELLOW "93"
#define CONSOLE_COLORID_WHITE "97"

#define BAE_LOG_CONTEXT "BA Engine"
#define SDL_LOG_CONTEXT "SDL2"

#define DEBUG_LOG(channel, message)											std::cout <<                               "[" << channel << "] " << message <<              std::endl
#define DEBUG_LOG_COLOURED(channel, message, colourId)						std::cout << "\x1B[" << colourId << "m" << "[" << channel << "] " << message << "\x1B[0m" << std::endl
#define DEBUG_LOG_CONTEXTED(channel, context, message)						DEBUG_LOG         (channel, context << " | " << message          )
#define DEBUG_LOG_CONTEXTED_COLOURED(channel, context, message, colourId)	DEBUG_LOG_COLOURED(channel, context << " | " << message, colourId)

#define DEBUG_LOG_SUCCESS(message)											DEBUG_LOG_COLOURED          ("SUCCESS"  ,          message         , CONSOLE_COLORID_GREEN  )
#define DEBUG_LOG_SUCCESS_CONTEXTED(context, message)						DEBUG_LOG_CONTEXTED_COLOURED("SUCCESS"  , context, message         , CONSOLE_COLORID_GREEN  )
#define DEBUG_LOG_INFO(message)												DEBUG_LOG_COLOURED          ("INFO"     ,          message         , CONSOLE_COLORID_DEFAULT)
#define DEBUG_LOG_INFO_CONTEXTED(context, message)							DEBUG_LOG_CONTEXTED_COLOURED("INFO"     , context, message         , CONSOLE_COLORID_DEFAULT)
#define DEBUG_LOG_WARNING(message)											DEBUG_LOG_COLOURED          ("WARNING"  ,          message         , CONSOLE_COLORID_YELLOW )
#define DEBUG_LOG_WARNING_CONTEXTED(context, message)						DEBUG_LOG_CONTEXTED_COLOURED("WARNING"  , context, message         , CONSOLE_COLORID_YELLOW )
#define DEBUG_LOG_ERROR(message)											DEBUG_LOG_COLOURED          ("ERROR"    ,          message         , CONSOLE_COLORID_RED    )
#define DEBUG_LOG_ERROR_CONTEXTED(context, message)							DEBUG_LOG_CONTEXTED_COLOURED("ERROR"    , context, message         , CONSOLE_COLORID_RED    )
#if THROW_EXCEPTIONS_INSTEAD_OF_LOG
#define DEBUG_EXCEPTION_NOEXCEPT                                            false
#define DEBUG_LOG_EXCEPTION(exception)										throw exception
#define DEBUG_LOG_EXCEPTION_CONTEXTED(context, exception)					throw exception
#define DEBUG_RETURN_EXCEPTION(exception)									DEBUG_LOG_EXCEPTION(exception)
#define DEBUG_RETURN_EXCEPTION_CONTEXTED(context, exception)				DEBUG_LOG_EXCEPTION_CONTEXTED(context, exception)
#else
#define DEBUG_EXCEPTION_NOEXCEPT                                            true
#define DEBUG_LOG_EXCEPTION(exception)										DEBUG_LOG_COLOURED          ("EXCEPTION",          exception.what(), CONSOLE_COLORID_RED    )
#define DEBUG_LOG_EXCEPTION_CONTEXTED(context, exception)					DEBUG_LOG_CONTEXTED_COLOURED("EXCEPTION", context, exception.what(), CONSOLE_COLORID_RED    )
#define DEBUG_RETURN_EXCEPTION(exception)									{ DEBUG_LOG_EXCEPTION(exception); return; }
#define DEBUG_RETURN_EXCEPTION_CONTEXTED(context, exception)				{ DEBUG_LOG_EXCEPTION_CONTEXTED(context, exception); return; }
#endif
#define DEBUG_LOG_SDL_ERROR(message)                                        DEBUG_LOG_ERROR_CONTEXTED(SDL_LOG_CONTEXT, message << SDL_GetError());

#define DEBUG_NODE_NAME(nodePointer) "\'" << (nodePointer)->GetName() << "'(" << typeid(nodePointer).name() << ')'