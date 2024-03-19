#pragma once

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

#define FLAGGED_ENUM(enumName, inheritedType) \
enum enumName : inheritedType; \
static constexpr enumName operator~ (enumName e) { return (enumName)(~(inheritedType)e); } \
static constexpr enumName operator| (enumName e, enumName other) { return (enumName)((inheritedType)e | (inheritedType)other); } \
static constexpr enumName& operator|= (enumName& e, enumName other) { return (enumName&)(e = (enumName)(e | other)); } \
static constexpr enumName operator& (enumName e, enumName other) { return (enumName)((inheritedType)e & (inheritedType)other); } \
static constexpr enumName& operator&= (enumName& e, enumName other) { return (enumName&)(e = (enumName)(e & other)); } \
static constexpr enumName operator^ (enumName e, enumName other) { return (enumName)((inheritedType)e ^ (inheritedType)other); } \
static constexpr enumName& operator^= (enumName& e, enumName other) { return (enumName&)(e = (enumName)(e ^ other)); } \
enum enumName : inheritedType