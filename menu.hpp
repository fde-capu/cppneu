#ifndef MENU_HPP
# define MENU_HPP
# include "Being.hpp"
# include "defines.hpp"

void toggleShowMenu();
void toggleShowDebug();
void toggleRunning();

static bool g_showMenu = true;
void printMenu();
void dealKeyPress(int ch);
void menuInit();
void gotoMenu(std::string);

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
	{'d', {"bar", []() -> void { gotoMenu("display"); }}},
}},
{ "display", {
	{'d', {"back", []() -> void { gotoMenu("main"); }}},
	{'b', {"bar", []() -> void { gotoMenu("bar"); }}},
	{'h', {"header", []() -> void { Being::setDisplay(DISPLAY_HEADER); }}},
	{'c', {"chars", []() -> void { Being::setDisplay(DISPLAY_CHARS); }}},
	{'p', {"physical", []() -> void { Being::setDisplay(DISPLAY_PHYSICAL); }}},
	{'v', {"vital", []() -> void { Being::setDisplay(DISPLAY_VITAL); }}},
	{'a', {"action", []() -> void { Being::setDisplay(DISPLAY_ACTION); }}},
	{'m', {"measures", []() -> void { Being::setDisplay(DISPLAY_MEASURES); }}},
	{'w', {"want", []() -> void { Being::setDisplay(DISPLAY_WANT); }}},
	{'x', {"axons", []() -> void { Being::setDisplay(DISPLAY_AXONS); }}},
	{'o', {"outs", []() -> void { Being::setDisplay(DISPLAY_OUTS); }}},
}},
{ "bar", {
	{'b', {"back", []() -> void { gotoMenu("display"); }}},
	{'o', {"on/off", []() -> void { Being::setDisplay(DISPLAY_BAR_ALL); }}},
	{'g', {"gauge", []() -> void { Being::setDisplay(DISPLAY_BAR); }}},
	{'n', {"numbers", []() -> void { Being::setDisplay(DISPLAY_NUMBERS); }}},
	{'c', {"characters", []() -> void { Being::setDisplay(DISPLAY_CHARACTER); }}},
	{'d', {"description", []() -> void { Being::setDisplay(DISPLAY_DESCRIPTION); }}},
	{'i', {"bias", []() -> void { Being::setDisplay(DISPLAY_BIAS); }}},
}}
};

static std::map<char, DescriptionFunction> g_menu_global = g_menu_tree["global"];

#endif
