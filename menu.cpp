#include "menu.hpp"

void toggleShowMenu() { g_showMenu = !g_showMenu; }
void toggleRunning() { g_running = !g_running; }

void gotoMenu(std::string u_menu)
{
	g_menu = g_menu_tree[u_menu];
	g_menu_name = u_menu;
}

void menuInit()
{
	gotoMenu("main");
}

void printMenu()
{
	if (!g_showMenu) return;
	printw("%s ", g_menu_name.c_str());
	for (const auto& kv : g_menu)
		printw("%c:%s ", kv.first, kv.second.description.c_str());
	for (const auto& kv : g_menu_global)
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

std::string g_debugString("");

void debug(std::string s)
{
	g_debugString += s + " ";
}

void printDebug()
{
	if (g_showDebug)
		printw("%s\n", g_debugString.c_str());
}

void toggleShowDebug() { g_showDebug = !g_showDebug; }
