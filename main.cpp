#include "defines.hpp"
#include "Being.hpp"
#include "menu.hpp"
#include "prints.hpp"

std::vector<t_config> g_conf = {};
bool g_quit = false;
bool g_running = false;
size_t g_tick_ms = INITIAL_TICK_MS;

Being g_being;

void doQuit() { g_quit = true; }

void run()
{
	menuInit();
	g_running = true;
	while (!g_quit)
	{
		if (g_running)
		{
			g_being.process();

			clear();
			printMenu();
			printDebug();
			printScreen(g_being);
			refresh();
		}

		int ch = getch();
		if (ch != ERR) {
			dealKeyPress(ch);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(g_tick_ms));
	}
}

void switchBias()
{
	g_being.switchBias();
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
		if (g_conf[i].type & T_AXON)
			g_being.addAxon();
		else
			g_being.addNeuron(g_conf[i]);
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

int main() {
	prepare();
	config(CONFIG_FILE);
	debug(g_being.readable());
	run();
	destroy();
	return 0;
}
