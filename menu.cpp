#include "menu.hpp"
#include "helpers.hpp"

std::string g_debugString("");
std::vector<std::string> g_status({});

void toggleShowMenu() { g_showMenu = !g_showMenu; }
void toggleRunning() { g_running = !g_running; }

void gotoMenu(std::string u_menu)
{
	g_menu = g_menu_tree[u_menu];
	g_menu_name = u_menu;
}

void menuInit()
{
	gotoMenu(FIRST_MENU);
}

void menuHighlight(const std::string& entry, char key, bool underline = false, bool divisor = true)
{
	if (entry == "<-")
		return;

	char p;
	bool high;
	bool key_match;
	bool highlighted = false;

	key_match =
		( to_lower(entry).find(std::tolower(key)) != std::string::npos );

	if (key && !key_match)
	{
		BOLD
		printw("%c", key);
		UNBOLD
		printw(":");
	}

	for (size_t i = 0; i < entry.length(); i++)
	{
		p = entry.at(i);
		p = std::tolower(p) == std::tolower(key) ? key : p;
		high = p == key && !highlighted;
		highlighted = high ? true : highlighted;
		if (high) BOLD;
		if (high && underline) UNDERLINE;
		printw("%c", p);
		if (high && underline) UNUNDERLINE;
		if (high) UNBOLD;
	}

	if (divisor)
		printw(" | ");
	else
		printw(" ");
}

void printMenu()
{
	if (!g_showMenu)
		return;

	char back_key = 0;

	for (const auto& kv : g_menu)
		if (kv.second.description == "<-")
			back_key = kv.first;

	menuHighlight("[ " + g_menu_name + " ]", back_key, true, false);

	for (const auto& kv : g_menu)
		menuHighlight(kv.second.description, kv.first);

	printw("\n| ");

	for (const auto& kv : g_menu_global)
		menuHighlight(kv.second.description, kv.first);

	printw("\n");
}

void dealKeyPress(int ch)
{
	if (g_menu_global.find(ch) != g_menu_global.end())
		g_menu_global[ch].functionPtr();
	if (g_menu.find(ch) != g_menu.end())
		g_menu[ch].functionPtr();
}

void debug(std::string s)
{
	g_debugString += s;
}

void status(const std::string& s)
{
	g_status.push_back(s);
}

void warn(const std::string& s)
{
	status(s);
	std::cerr << s;
}

void statusAppend(const std::string& s)
{
	g_status.back() += s;
}

void printDebug()
{
	if (g_showDebug)
		printw("%s\n", g_debugString.c_str());
}

void printStatus()
{
	static size_t status_time = 0;
	static size_t status_size = 0;

	if (g_showStatus == 3)
		g_showStatus = 0;
	if (!g_status.size())
		return ;
	if (g_showStatus == 1)
	{
		if (g_status.size() == status_size)
		{
			status_time++;
			if (status_time > 100)
				g_status.push_back("");
		}
		else
		{
			status_time = 0;
			status_size = g_status.size();
		}
		printw("%s\n", (g_status.back()).c_str());
	}
	if (g_showStatus == 2)
	{
		for (auto s : g_status)
			printw("%s\n", s.c_str());
	}
}

void toggleShowDebug() { g_showDebug = !g_showDebug; }
void toggleShowStatus() { g_showStatus++; }

void increment(size_t& v, size_t a) { v += a; }
void decrement(size_t& v, size_t a) { v -= a; }
