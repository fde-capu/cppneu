#ifndef MENU_HPP
# define MENU_HPP

# include "prints.hpp"

void toggleShowMenu();
void toggleShowDebug();
void toggleShowStatus();
void toggleRunning();

static bool g_showMenu = true;
void printMenu();
void dealKeyPress(int ch);
void menuInit();
void gotoMenu(std::string);
void printDebug();
void printStatus();

void increment(size_t&, size_t);
void decrement(size_t&, size_t);

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
	{'t', {"status", &toggleShowStatus}},
	{'?', {"menu", &toggleShowMenu}},
	{'q', {"quit", &doQuit}},
	{'n', {"new", &createNewBeing}},
	{'.', {"next", &nextBeing}},
	{',', {"previous", &previousBeing}},
	{'P', {"pause", &toggleRunning}},
	{'l', {"list", []() -> void { chooseBeing(); }}},
}},
{ "main", {
	{'d', {"display", []() -> void { gotoMenu("display"); }}},
	{'p', {"poke", []() -> void { poke(); }}},
	{'s', {"save", []() -> void { save(); }}},
	{'y', {"system_save", []() -> void { sysSave(); }}},
	{'b', {"bias_on/off", []() -> void { switchBias(); }}},
	{'=', {"speed_down", []() -> void { increment(g_tick_ms, 10); }}},
	{'-', {"speed_up", []() -> void { decrement(g_tick_ms, g_tick_ms >= 20 ? 10 : 0); }}},
}},
{ "display", {
	{'d', {"<-", []() -> void { gotoMenu("main"); }}},
	{'b', {"bar", []() -> void { gotoMenu("bar"); }}},
	{'i', {"bias", []() -> void { setDisplay(DISPLAY_BIAS); }}},
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
	{'b', {"<-", []() -> void { gotoMenu("display"); }}},
	{'o', {"on/off", []() -> void { setDisplay(DISPLAY_BAR_ALL); }}},
	{'g', {"gauge", []() -> void { setDisplay(DISPLAY_BAR); }}},
	{'n', {"numbers", []() -> void { setDisplay(DISPLAY_NUMBERS); }}},
	{'c', {"characters", []() -> void { setDisplay(DISPLAY_CHARACTER); }}},
	{'d', {"description", []() -> void { setDisplay(DISPLAY_DESCRIPTION); }}},
	{'s', {"quiets", []() -> void { setDisplay(DISPLAY_QUIETS); }}},
}}
};

static std::map<char, DescriptionFunction> g_menu_global = g_menu_tree["global"];

#endif
