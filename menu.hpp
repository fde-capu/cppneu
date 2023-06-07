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
	{'d', {"debug", &toggleShowDebug}},
	{'?', {"menu", &toggleShowMenu}},
	{'q', {"quit", &doQuit}},
	{'P', {"pause", &toggleRunning}},
}},
{ "main", {
	{'h', {"header", &Being::toggleDisplayHeader}},
	{'c', {"chars", &Being::toggleDisplayCharacters}},
	{'p', {"physical", &Being::toggleDisplayPhysical}},
	{'v', {"vital", &Being::toggleDisplayVital}},
	{'a', {"action", &Being::toggleDisplayAction}},
	{'m', {"measures", &Being::toggleDisplayMeasure}},
	{'w', {"want", &Being::toggleDisplayActionResolution}},
	{'D', {"display", []() -> void { gotoMenu("display"); }}},
}},
{ "display", {
	{'D', {"back", &menuInit}},
	{'n', {"numbers", []() -> void { Being::toggleBit(DISPLAY_NUMBERS); }}},
	{'b', {"bars", []() -> void { Being::toggleBit(DISPLAY_BAR); }}},
	{'c', {"characters", []() -> void { Being::toggleBit(DISPLAY_CHARACTER); }}},
	{'d', {"description", []() -> void { Being::toggleBit(DISPLAY_DESCRIPTION); }}},
	{'o', {"outs", &Being::toggleDisplayOuts}},
	{'x', {"axons", &Being::toggleDisplayAxons}},
	{'i', {"bias bars", &Being::toggleDisplayBiasBars}},
	{'+', {"up", &Being::toggleDisplayBarsUp}},
	{'-', {"down", &Being::toggleDisplayBarsDown}},
}}
};

static std::map<char, DescriptionFunction> g_menu_global = g_menu_tree["global"];

#endif
