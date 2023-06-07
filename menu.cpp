#include "header.hpp"
#include "defines.hpp"
#include "Being.hpp"

typedef void (*voidFuncPtr)(void);

void toggleShowMenu() { g_showMenu = !g_showMenu; }
void toggleShowDebug() { g_showDebug = !g_showDebug; }
void toggleRunning() { g_running = !g_running; }

struct DescriptionFunction {
    std::string description;
    voidFuncPtr functionPtr;
};

std::map<char, DescriptionFunction> g_menu;

void gotoMenu();

static std::map<std::string, std::map<char, DescriptionFunction> >
g_menu_tree = 
{
{ "main", {
	{'d', {"debug", &toggleShowDebug}},
	{'?', {"menu", &toggleShowMenu}},
	{'q', {"quit", &doQuit}},
	{'P', {"pause", &toggleRunning}},
	{'h', {"header", &Being::toggleDisplayHeader}},
	{'c', {"chars", &Being::toggleDisplayCharacters}},
	{'p', {"physical", &Being::toggleDisplayPhysical}},
	{'v', {"vital", &Being::toggleDisplayVital}},
	{'a', {"action", &Being::toggleDisplayAction}},
	{'m', {"measures", &Being::toggleDisplayMeasure}},
	{'w', {"want", &Being::toggleDisplayActionResolution}},
	{'b', {"bars up", &Being::toggleDisplayBarsUp}},
	{'B', {"bars menu", &gotoMenu}},
	{'o', {"outs", &Being::toggleDisplayOuts}},
	{'x', {"axons", &Being::toggleDisplayAxons}},
	{'i', {"bias bars", &Being::toggleDisplayBiasBars}},
//	{' ', {.description = "new", &makeBrain}},
}},
{ "bars", {
	{'B', {"back", &menuInit}},
  {'n', {"numbers", &printDebug}},
  {'b', {"bars", &printDebug}},
}}
};

void gotoMenu()
{
	g_menu = g_menu_tree["bars"];
}

void menuInit()
{
	g_menu = g_menu_tree["main"];
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
	printw(":");
	for (const auto& kv : g_menu) {
		printw("%c:%s ", kv.first, kv.second.description.c_str());
	}
	printw(":\n");
}

void dealKeyPress(int ch)
{
	if (g_menu.find(ch) != g_menu.end())
		g_menu[ch].functionPtr();
}
