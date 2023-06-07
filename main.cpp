#include "header.hpp"
#include "Being.hpp"

void doQuit() { g_quit = true; }

void run()
{
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
}

void destroy()
{
	endwin();
}

int main() {
	prepare();
	Being::reset();
	loadConf(CONFIG_FILE);
	menuInit();
	run();
	destroy();
	return 0;
}
