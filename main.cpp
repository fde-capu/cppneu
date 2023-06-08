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
	loadConf(config_file.c_str());
	for (size_t i = 0; i < g_conf.size(); i++)
	{
		(Being(g_conf[i]));
	}
}

int main() {
	prepare();
	Being::reset();
	config(CONFIG_FILE);
	std::cout << "BEING " << Being::readable();
	std::cout << std::endl;
	run();
	destroy();
	return 0;
}
