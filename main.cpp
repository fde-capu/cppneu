#include "header.hpp"
#include "types.hpp"
#include "Being.hpp"
#include "menu.hpp"
#include "helpers.hpp"
#include "defines.hpp"

std::vector<t_config> g_conf = {};
bool g_quit = false;
bool g_running = false;
size_t g_tick_ms = DEFAULT_TICK_MS;

long displaySet;
std::string baseNames;

std::vector<Being> g_being;

std::ostream& operator<< (std::ostream& o, t_config const& self)
{
	o << "t_config {" <<
		 " UID: " << self.UID <<
		", type: " << self.type <<
		", name: " << self.name <<
		", expressor: " << self.expressor <<
		", scaleMin: " << self.scaleMin <<
		", scaleMax: " << self.scaleMax <<
		", unit: " << self.unit <<
		", scale: " << self.scale.size() <<
		", damp: " << self.damp <<
		", originalThreshold: " << self.originalThreshold <<
		", slotIn: " << self.slotIn <<
		", slotOut: " << self.slotOut <<
		", multiplier: " << self.multiplier <<
		" }" << std::endl;
	return o;
}

void doQuit() { g_quit = true; }

void run()
{
	menuInit();
	g_running = true;
	status("Running.");
	while (!g_quit)
	{
		if (g_running)
		{

			g_being[0].process();

			clear();
			printMenu();
			printDebug();
			printStatus();
			printScreen(g_being[0]);
			refresh();
		}

		int ch = getch();
		if (ch != ERR)
				dealKeyPress(ch);

		std::this_thread::sleep_for(std::chrono::milliseconds(g_tick_ms));
	}
}

void switchBias()
{
	g_being[0].switchBias();
}

void destroy()
{
	endwin();
}

void sysconfig(std::string sys_conf)
{
	std::fstream file_read = loadFile(sys_conf.c_str());
	std::string line;
	std::vector<std::string> kv;
	while (std::getline(file_read, line))
	{
		kv = split(line, ':');
		if (kv[0] == "displaySet")
			displaySet = std::atol(kv[1].c_str());
		if (kv[0] == "baseNames")
			baseNames = kv[1];
	}
}

void config()
{
	Being newBeing;
	g_being.insert(g_being.begin(), newBeing);
	for (size_t i = 0; i < g_conf.size(); i++)
	{
		if (g_conf[i].type == T_AXON)
			g_being[0].addAxon(g_conf[i]);
		else
			g_being[0].addNeuron(g_conf[i]);
	}
	g_being[0].name = funnyName(baseNames);
	g_being[0].on();
}

void prepare()
{
	srand(time(NULL));
	initscr();

	if (g_colors)
	{
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		wbkgd(stdscr, COLOR_PAIR(1));
	}

	set_tabsize(LEADING_ZEROS + 1);
	//nocbreak();
	noecho();
	nodelay(stdscr, TRUE);
	g_conf = {};
}

int main() {
	prepare();
	sysconfig(DEFAULT_SYS_CONFIG_FILE);
	loadConf(DEFAULT_CONFIG_FILE);
	config();
//	debug(g_being[0].readable());
	run();
	destroy();
	return 0;
}

void createNewBeing() {
	config();
}

void poke() {
	g_being[0].poke("CustomBiasName");
}

void save() {
	g_being[0].save();
}

void sysSave() {
	std::ofstream fn(DEFAULT_SYS_CONFIG_FILE);
	if (fn.is_open())
	{
		fn << "displaySet:" << displaySet << std::endl;
		fn << "baseNames:" << baseNames << std::endl;
		fn.close();
	}
}
