#include "header.hpp"

void makeBrain();

static bool g_quit = false;
static bool g_running = false;
static bool g_showMenu = true;
void doQuit() { g_quit = true; }
void toggleShowMenu() { g_showMenu = !g_showMenu; }
void toggleRunning() { g_running = !g_running; }

typedef void (*voidFuncPtr)(void);

struct KeyValue {
    std::string description;
    voidFuncPtr functionPtr;
};

static std::map<char, KeyValue> g_menu = {
	{'?', {.description = "menu", .functionPtr = &toggleShowMenu}},
	{'q', {.description = "quit", .functionPtr = &doQuit}},
	{'P', {.description = "pause", .functionPtr = &toggleRunning}},
	{'h', {.description = "header", .functionPtr = &Neuron::toggleDisplayHeader}},
	{'c', {.description = "chars", .functionPtr = &Neuron::toggleDisplayCharacters}},
	{'p', {.description = "physical", .functionPtr = &Neuron::toggleDisplayPhysical}},
	{'v', {.description = "vital", .functionPtr = &Neuron::toggleDisplayVital}},
	{'a', {.description = "action", .functionPtr = &Neuron::toggleDisplayAction}},
	{'m', {.description = "measures", .functionPtr = &Neuron::toggleDisplayMeasure}},
	{'w', {.description = "want", .functionPtr = &Neuron::toggleDisplayActionResolution}},
	{'b', {.description = "bars", .functionPtr = &Neuron::toggleDisplayBars}},
	{'o', {.description = "outs", .functionPtr = &Neuron::toggleDisplayOuts}},
	{'x', {.description = "axons", .functionPtr = &Neuron::toggleDisplayAxons}},
	{'B', {.description = "bias bars", .functionPtr = &Neuron::toggleDisplayBiasBars}},
	{' ', {.description = "new", .functionPtr = &makeBrain}},
};

void printMenu()
{
	printw("| ");
	for (const auto& kv : g_menu) {
		printw("%c %s\t", kv.first, kv.second.description.c_str());
	}
	printw("\n");
}

void dealKeyPress(int ch)
{
	if (g_menu.find(ch) != g_menu.end())
		g_menu[ch].functionPtr();
}

void run()
{
	g_running = true;
	while (!g_quit)
	{
		if (g_running)
		{
			Neuron::processAll();

			clear();
			if (g_showMenu)
				printMenu();
			Neuron::printScreen();
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
	set_tabsize(12);
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
}

void destroy()
{
	endwin();
}

void makeBrain()
{
	Neuron::reset();

	Neuron::Vital("Breath", {"Empty", "Neutral", "Full"},
		0, 0, "", 0.0, EXPRESSOR_THRESHOLD);
	Neuron::Physical("Nose", {"Short", "Medium", "Long"});
  Neuron::Measure("Eyes", {"Closed", "Normal", "Wide Open"}, EXPRESSOR_THRESHOLD);
  Neuron::Measure("Humor",
		{"Crappy", "Bad", "Medium", "Ok", "Good", "Enthusiastic", "Incredible"},
		EXPRESSOR_THRESHOLD);
  Neuron::Vital("Heart",
		{"Frozen", "Slow", "Normal", "Peaced", "Accelerated", "Fast", "Hyper"},
		0, 260, "bpm", 0.8);
  Neuron::Measure("Tired", {}, EXPRESSOR_CURRENT);
	Neuron::Action("Drop");
	Neuron::Action("Clench", {"Softly", "Moderate", "Hard"});
	Neuron::Action("Sleep");

	Neuron::Bias(5);
	Neuron::Axon(100);
}


int main() {
	prepare();
	makeBrain();
	run();
	destroy();
	return 0;
}
