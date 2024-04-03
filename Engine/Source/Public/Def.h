#pragma once
#include <vcruntime.h>

#define IN(...) const __VA_ARGS__&
#define IN_NULLABLE(...) const __VA_ARGS__*
#define OUT(...) __VA_ARGS__&
#define OUT_NULLABLE(...) __VA_ARGS__*&
#define REF(...) __VA_ARGS__&
#define REF_NULLABLE(...) __VA_ARGS__*

#define COMMA ,
#define COMMA2 COMMA_ BRACKET_OPEN2 BRACKET_CLOSE2
#define COMMA_() ,
#define BRACKET_OPEN (
#define BRACKET_OPEN2 BRACKET_OPEN_ BRACKET_OPEN BRACKET_CLOSE
#define BRACKET_OPEN_() (
#define BRACKET_CLOSE )
#define BRACKET_CLOSE2  BRACKET_CLOSE_ BRACKET_OPEN BRACKET_CLOSE
#define BRACKET_CLOSE_() )
#define UNPACK(...) __VA_ARGS__
#define UNPACK2(...) UNPACK BRACKET_OPEN __VA_ARGS__ BRACKET_CLOSE