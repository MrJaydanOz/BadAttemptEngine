#pragma once
#include <iostream>

#define DEBUG_CONSOLE_COLOURID_DEFAULT "0"
#define DEBUG_CONSOLE_COLOURID_BLACK "30"
#define DEBUG_CONSOLE_COLOURID_DARK_BLUE "34"
#define DEBUG_CONSOLE_COLOURID_DARK_GREEN "32"
#define DEBUG_CONSOLE_COLOURID_LIGHT_BLUE "36"
#define DEBUG_CONSOLE_COLOURID_DARK_RED "31"
#define DEBUG_CONSOLE_COLOURID_MAGENTA "35"
#define DEBUG_CONSOLE_COLOURID_ORANGE "33"
#define DEBUG_CONSOLE_COLOURID_LIGHT_GREY "37"
#define DEBUG_CONSOLE_COLOURID_LIGHT_GRAY DEBUG_CONSOLE_COLOURID_LIGHT_GREY
#define DEBUG_CONSOLE_COLOURID_GREY "90"
#define DEBUG_CONSOLE_COLOURID_GRAY DEBUG_CONSOLE_COLOURID_GREY
#define DEBUG_CONSOLE_COLOURID_BLUE "94"
#define DEBUG_CONSOLE_COLOURID_GREEN "92"
#define DEBUG_CONSOLE_COLOURID_CYAN "96"
#define DEBUG_CONSOLE_COLOURID_RED "91"
#define DEBUG_CONSOLE_COLOURID_PINK "95"
#define DEBUG_CONSOLE_COLOURID_YELLOW "93"
#define DEBUG_CONSOLE_COLOURID_WHITE "97"

#define BAE_LOG_CONTEXT "BA Engine"
#define SDL_LOG_CONTEXT "SDL2"

#define DEBUG_LOG(channel, message)											std::cout <<                               "[" << channel << "] " << message <<              std::endl
#define DEBUG_LOG_COLOURED(channel, message, colourId)						std::cout << "\x1B[" << colourId << "m" << "[" << channel << "] " << message << "\x1B[0m" << std::endl
#define DEBUG_LOG_CONTEXTED(channel, context, message)						DEBUG_LOG         (channel, context << " | " << message          )
#define DEBUG_LOG_CONTEXTED_COLOURED(channel, context, message, colourId)	DEBUG_LOG_COLOURED(channel, context << " | " << message, colourId)

#define DEBUG_LOG_SUCCESS(message)											DEBUG_LOG_CONTEXTED_COLOURED("SUCCESS",          message, DEBUG_CONSOLE_COLOURID_GREEN  )
#define DEBUG_LOG_SUCCESS_CONTEXTED(context, message)						DEBUG_LOG_CONTEXTED_COLOURED("SUCCESS", context, message, DEBUG_CONSOLE_COLOURID_GREEN  )
#define DEBUG_LOG_INFO(message)												DEBUG_LOG_CONTEXTED_COLOURED("INFO"   ,          message, DEBUG_CONSOLE_COLOURID_DEFAULT)
#define DEBUG_LOG_INFO_CONTEXTED(context, message)							DEBUG_LOG_CONTEXTED_COLOURED("INFO"   , context, message, DEBUG_CONSOLE_COLOURID_DEFAULT)
#define DEBUG_LOG_WARNING(message)											DEBUG_LOG_CONTEXTED_COLOURED("WARNING",          message, DEBUG_CONSOLE_COLOURID_YELLOW )
#define DEBUG_LOG_WARNING_CONTEXTED(context, message)						DEBUG_LOG_CONTEXTED_COLOURED("WARNING", context, message, DEBUG_CONSOLE_COLOURID_YELLOW )
#define DEBUG_LOG_ERROR(message)											DEBUG_LOG_CONTEXTED_COLOURED("ERROR"  ,          message, DEBUG_CONSOLE_COLOURID_RED    )
#define DEBUG_LOG_ERROR_CONTEXTED(context, message)							DEBUG_LOG_CONTEXTED_COLOURED("ERROR"  , context, message, DEBUG_CONSOLE_COLOURID_RED    )
#define DEBUG_LOG_SDL_ERROR(message)                                        DEBUG_LOG_ERROR_CONTEXTED(SDL_LOG_CONTEXT, message << SDL_GetError());