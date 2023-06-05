#include "header.hpp"
#include "Being.hpp"

void makeBrain();

static bool g_showDebug = false;
static bool g_quit = false;
static bool g_running = false;
static bool g_showMenu = true;
void doQuit() { g_quit = true; }
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
	{' ', {.description = "new", .functionPtr = &makeBrain}},
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

void run()
{
	g_running = true;
	while (!g_quit)
	{
		if (g_running)
		{
			Being::processAll();

			clear();
			if (g_showMenu)
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
	makeBrain();
	run();
	destroy();
	return 0;
}

void makeBrain()
{
  Being({
		.type = T_VITAL,
		.name = "Heart",
		.expressor = EXPRESSOR_THRESHOLD,
		.scaleMin = 0,
		.scaleMax = 260,
		.unit = "bpm",
		.scale = {"Frozen", "Slow", "Normal", "Peaced", "Accelerated", "Fast", "Hyper"},
		.damp = 0.9
	});
	Being({
		.type = T_PHYSICAL,
		.name = "Nose",
		.expressor = EXPRESSOR_ORIGINAL_THRESHOLD,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = {"Short", "Medium", "Long"},
		.damp = 1.0
	});
//	Being::Create(T_VITAL, "Breath",
//		{"Empty", "Neutral", "Full"});
//  Being::Create(T_MEASURE, "Eyes",
//		{"Closed", "Normal", "Wide Open"});
//  Being::Create(T_MEASURE, "Humor",
//		{"Crappy", "Bad", "Medium", "Ok", "Good", "Enthusiastic", "Incredible"});
//  Being::Create(T_MEASURE, "Tired",
//		{}, {}, EXPRESSOR_CURRENT);
//	Being::Create(T_ACTION, "Drop",
//		{}, {}, EXPRESSOR_CURRENT);
//	Being::Create(T_ACTION, "Clench",
//		{"Softly", "Moderate", "Hard"}, {}, EXPRESSOR_CURRENT);
//	Being::Create(T_ACTION, "Sleep",
//		{}, {}, EXPRESSOR_CURRENT);
	Being::Bias(3);
	Being::Axon(10);
}
