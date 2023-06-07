#include "header.hpp"
#include "defines.hpp"
#include "Being.hpp"

void toggleShowMenu() { g_showMenu = !g_showMenu; }
void toggleShowDebug() { g_showDebug = !g_showDebug; }
void toggleRunning() { g_running = !g_running; }
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

void gotoMenu(std::string u_menu)
{
	g_menu = g_menu_tree[u_menu];
	g_menu_name = u_menu;
}

void menuInit()
{
	gotoMenu("main");
}

std::string g_debugString("");

void debug(std::string s)
{
	g_debugString += s + " ";
}

void printDebug()
{ printw("%s\n", g_debugString.c_str()); }

void printMenu()
{
	if (!g_showMenu) return;
	printw("%s ", g_menu_name.c_str());
	for (const auto& kv : g_menu_global)
		printw("%c:%s ", kv.first, kv.second.description.c_str());
	for (const auto& kv : g_menu)
		printw("%c:%s ", kv.first, kv.second.description.c_str());
	printw("\n");
}

void dealKeyPress(int ch)
{
	if (g_menu_global.find(ch) != g_menu_global.end())
		g_menu_global[ch].functionPtr();
	if (g_menu.find(ch) != g_menu.end())
		g_menu[ch].functionPtr();
}
