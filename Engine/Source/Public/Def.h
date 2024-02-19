#pragma once

#define COMMA ,
#define BRACKET_OPEN (
#define BRACKET_CLOSE )
#define UNPACK(...) __VA_ARGS__
#define UNPACK2(...) UNPACK BRACKET_OPEN __VA_ARGS__ BRACKET_CLOSE

#define EXPR(...) { return __VA_ARGS__; }