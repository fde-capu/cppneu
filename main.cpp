#include "header.hpp"

void makeBrain();

static bool g_quit = false;
static bool g_running = false;
static bool g_showMenu = true;
void doQuit() { g_quit = true; }
void toggleShowMenu() { g_showMenu = !g_showMenu; }
void toggleRunning() { g_running = !g_running; }

typedef void (*voidFuncPtr)(void);

struct DescriptionFunction {
    std::string description;
    voidFuncPtr functionPtr;
};

static std::map<char, DescriptionFunction> g_menu = {
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

int main() {
	prepare();
	Neuron::reset();
	makeBrain();
	run();
	destroy();
	return 0;
}

void makeBrain()
{
  Neuron::Create(T_VITAL, "Heart",
		{"Frozen", "Slow", "Normal", "Peaced", "Accelerated", "Fast", "Hyper"},
		{0, 260, "bpm"}, EXPRESSOR_THRESHOLD,	.8);
	Neuron::Create(T_VITAL, "Breath",
		{"Empty", "Neutral", "Full"});
	Neuron::Create(T_PHYSICAL, "Nose",
		{"Short", "Medium", "Long"},
		{}, EXPRESSOR_ORIGINAL_THRESHOLD, 1.0);
  Neuron::Create(T_MEASURE, "Eyes",
		{"Closed", "Normal", "Wide Open"});
  Neuron::Create(T_MEASURE, "Humor",
		{"Crappy", "Bad", "Medium", "Ok", "Good", "Enthusiastic", "Incredible"});
  Neuron::Create(T_MEASURE, "Tired",
		{}, {}, EXPRESSOR_CURRENT);
	Neuron::Create(T_ACTION, "Drop",
		{}, {}, EXPRESSOR_CURRENT);
	Neuron::Create(T_ACTION, "Clench",
		{"Softly", "Moderate", "Hard"}, {}, EXPRESSOR_CURRENT);
	Neuron::Create(T_ACTION, "Sleep",
		{}, {}, EXPRESSOR_CURRENT);
	Neuron::Bias(5);
	Neuron::Axon(100);
}
