#include "header.hpp"
#include "types.hpp"
#include "Being.hpp"
#include "menu.hpp"
#include "helpers.hpp"
#include "defines.hpp"

std::vector<n_config> g_conf = {};
b_config g_bconf;
bool g_quit = false;
bool g_running = false;
size_t g_tick_ms = DEFAULT_TICK_MS;

long displaySet;
std::string baseNames;

std::vector<Being> g_being;
size_t curb = 0;

std::ostream& operator<< (std::ostream& o, n_config const& self)
{
	o << "n_config {" <<
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

			g_being[curb].process();

			clear();
			printMenu();
			printDebug();
			printStatus();
			printScreen(g_being[curb]);
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
	g_being[curb].switchBias();
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

std::string& uniqueName()
{
	if (!g_bconf.name.length())
		g_bconf.name = funnyName(baseNames);
	for (const auto& b : g_being)
	{
		if (b.name == g_bconf.name)
		{
			nextRomanName(g_bconf.name);
			warn(b.name + " already exist, renaming to " + g_bconf.name + ".");
			return uniqueName();
		}
	}
	return g_bconf.name;
}

void config()
{
	Being newBeing;
	g_being.insert(g_being.begin() + curb, newBeing);
	for (size_t i = 0; i < g_conf.size(); i++)
	{
		if (g_conf[i].type == T_AXON)
			g_being[curb].addAxon(g_conf[i]);
		else
			g_being[curb].addNeuron(g_conf[i]);
	}
	g_being[curb].name = uniqueName();
	g_being[curb].on();
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

int main()
{
	prepare();
	sysconfig(DEFAULT_SYS_CONFIG_FILE);
	loadConf(DEFAULT_CONFIG_FILE);
	config();
//	debug(g_being[curb].readable());
	run();
	destroy();
	return 0;
}

void createNewBeing() {
	loadConf(DEFAULT_CONFIG_FILE);
	config();
}

void nextBeing()
{ curb = curb + 1 == g_being.size() ? 0 : curb + 1; }

void previousBeing()
{ curb = curb == 0 ? g_being.size() - 1 : curb - 1; }

void poke()
{
	g_being[curb].poke("CustomBiasName");
}

void save() {
	g_being[curb].save();
}

void chooseBeing()
{
	std::vector<std::string> beingList = {};
	for (const Being& b : g_being)
		beingList.push_back(b.name);
	select("Select:", beingList, curb);
}

void sysSave()
{
	std::ofstream fn(DEFAULT_SYS_CONFIG_FILE);
	if (fn.is_open())
	{
		fn << "displaySet:" << displaySet << std::endl;
		fn << "baseNames:" << baseNames << std::endl;
		fn.close();
		status("System configuration saved.");
	}
	else
		status("Failed to save system configuration.");
}
