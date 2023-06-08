#include "defines.hpp"
#include "Being.hpp"
#include "menu.hpp"

std::vector<t_config> g_conf = {};
bool g_quit = false;
bool g_running = false;

void doQuit() { g_quit = true; }

void run()
{
	menuInit();
	g_running = true;
	while (!g_quit)
	{
		if (g_running)
		{
			Being::processAll();

			clear();
			printMenu();
			if (g_showDebug)
				printDebug();
			Being::printScreen();
			refresh();
		}

		int ch = getch();
		if (ch != ERR) {
			dealKeyPress(ch);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(STEP_MS));
	}
}

void prepare()
{
	srand(time(NULL));
	initscr();
	set_tabsize(LEADING_ZEROS + 1);
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	g_conf = {};
}

void destroy()
{
	endwin();
}

void config(std::string config_file)
{
	debug("HERE6 " + std::to_string(g_conf.size()));
	loadConf(config_file.c_str());
	debug("HERE7 " + std::to_string(g_conf.size()));
	for (size_t i = 0; i < g_conf.size(); i++)
	{
		debug("---" + g_conf[i].name);
		(Being(g_conf[i]));
	}
}

int main() {
	prepare();
	Being::reset();
	debug("HERE3 " + std::to_string(g_conf.size()));
	config(CONFIG_FILE);
	debug("HERE4 " + std::to_string(g_conf.size()));
	run();
	destroy();
	return 0;
}
