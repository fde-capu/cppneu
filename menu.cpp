#include "header.hpp"
#include "defines.hpp"
#include "Being.hpp"

void toggleShowMenu() { g_showMenu = !g_showMenu; }
void toggleShowDebug() { g_showDebug = !g_showDebug; }
void toggleRunning() { g_running = !g_running; }

typedef void (*voidFuncPtr)(void);

struct DescriptionFunction {
    std::string description;
    voidFuncPtr functionPtr;
};

static std::map<char, DescriptionFunction> g_menu = {
	{'d', {.description = "debug", .functionPtr = &toggleShowDebug}},
	{'?', {.description = "menu", .functionPtr = &toggleShowMenu}},
	{'q', {.description = "quit", .functionPtr = &doQuit}},
	{'P', {.description = "pause", .functionPtr = &toggleRunning}},
	{'h', {.description = "header", .functionPtr = &Being::toggleDisplayHeader}},
	{'c', {.description = "chars", .functionPtr = &Being::toggleDisplayCharacters}},
	{'p', {.description = "physical", .functionPtr = &Being::toggleDisplayPhysical}},
	{'v', {.description = "vital", .functionPtr = &Being::toggleDisplayVital}},
	{'a', {.description = "action", .functionPtr = &Being::toggleDisplayAction}},
	{'m', {.description = "measures", .functionPtr = &Being::toggleDisplayMeasure}},
	{'w', {.description = "want", .functionPtr = &Being::toggleDisplayActionResolution}},
	{'b', {.description = "bars up", .functionPtr = &Being::toggleDisplayBarsUp}},
	{'B', {.description = "bars down", .functionPtr = &Being::toggleDisplayBarsDown}},
	{'o', {.description = "outs", .functionPtr = &Being::toggleDisplayOuts}},
	{'x', {.description = "axons", .functionPtr = &Being::toggleDisplayAxons}},
	{'i', {.description = "bias bars", .functionPtr = &Being::toggleDisplayBiasBars}},
//	{' ', {.description = "new", .functionPtr = &makeBrain}},
};

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

