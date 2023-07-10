#ifndef MENU_HPP
# define MENU_HPP
# include "Being.hpp"
# include "header.hpp"
# include "prints.hpp"

void toggleShowMenu();
void toggleShowDebug();
void toggleRunning();

static bool g_showMenu = true;
void printMenu();
void dealKeyPress(int ch);
void menuInit();
void gotoMenu(std::string);
void debug(std::string s);
void printDebug();

void increment(size_t&, size_t);
void decrement(size_t&, size_t);

template <typename T>
void debug(std::string s, T any)
{ debug(s + " " + std::to_string(any)); }

typedef void (*voidFuncPtr)(void);

struct DescriptionFunction {
    std::string description;
    voidFuncPtr functionPtr;
};

static std::map<char, DescriptionFunction> g_menu;
static std::string g_menu_name = "";

static std::map<std::string, std::map<char, DescriptionFunction> >
g_menu_tree = 
{
{ "global", {
	{'!', {"debug", &toggleShowDebug}},
	{'?', {"menu", &toggleShowMenu}},
	{'q', {"quit", &doQuit}},
	{'P', {"pause", &toggleRunning}},
}},
{ "main", {
	{'d', {"display", []() -> void { gotoMenu("display"); }}},
	{'b', {"bias_on/off", []() -> void { switchBias(); }}},
	{'s', {"speed_down", []() -> void { increment(g_tick_ms, 10); }}},
	{'S', {"speed_up", []() -> void { decrement(g_tick_ms, g_tick_ms >= 20 ? 10 : 0); }}},
	{'p', {"poke", []() -> void { poke(); }}},
}},
{ "display", {
	{'d', {"back", []() -> void { gotoMenu("main"); }}},
	{'b', {"bar", []() -> void { gotoMenu("bar"); }}},
	{'h', {"header", []() -> void { setDisplay(DISPLAY_HEADER); }}},
	{'c', {"chars", []() -> void { setDisplay(DISPLAY_CHARS); }}},
	{'p', {"physical", []() -> void { setDisplay(DISPLAY_PHYSICAL); }}},
	{'v', {"vital", []() -> void { setDisplay(DISPLAY_VITAL); }}},
	{'a', {"action", []() -> void { setDisplay(DISPLAY_ACTION); }}},
	{'m', {"measures", []() -> void { setDisplay(DISPLAY_MEASURES); }}},
	{'w', {"want", []() -> void { setDisplay(DISPLAY_WANT); }}},
	{'x', {"axons", []() -> void { setDisplay(DISPLAY_AXONS); }}},
	{'o', {"outs", []() -> void { setDisplay(DISPLAY_OUTS); }}},
}},
{ "bar", {
	{'b', {"back", []() -> void { gotoMenu("display"); }}},
	{'o', {"on/off", []() -> void { setDisplay(DISPLAY_BAR_ALL); }}},
	{'g', {"gauge", []() -> void { setDisplay(DISPLAY_BAR); }}},
	{'n', {"numbers", []() -> void { setDisplay(DISPLAY_NUMBERS); }}},
	{'c', {"characters", []() -> void { setDisplay(DISPLAY_CHARACTER); }}},
	{'d', {"description", []() -> void { setDisplay(DISPLAY_DESCRIPTION); }}},
	{'i', {"bias", []() -> void { setDisplay(DISPLAY_BIAS); }}},
	{'s', {"quiets", []() -> void { setDisplay(DISPLAY_QUIETS); }}},
}}
};

static std::map<char, DescriptionFunction> g_menu_global = g_menu_tree["global"];

#endif
