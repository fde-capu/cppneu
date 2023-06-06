#include "header.hpp"
#include "Being.hpp"

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
//	{' ', {.description = "new", .functionPtr = &makeBrain}},
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

void hard_trim(std::string& line)
{
	std::string out;
	char last = ' ';
	char now = 0;
	size_t i = -1;
	while (++i < line.length())
	{
		now = line.at(i);
		if (now == '#')	break ;
		if (now == '\'') now = '"';
		if (now == '\t') now = ' ';
		if (now == ';') now = ' ';
		if (last == ' ' && now == ' ') continue ;
		last = now;
		out += now;
	}
	if (out.length())
		if (out.at(out.length() - 1) == ' ')
			out = out.substr(0, out.length() - 1);
	if (out.length() < 3)
		out = "";
	line = out;
}

std::string readQuoted(const std::string& l, size_t i)
{
	char f = l.at(i) == '"' ? '"' : ' ';
	i += f == '"' ? 0 : -1;
	std::string o;
	while (++i < l.length() && l.at(i) != f)
		o += l.at(i);
	return o;
}

size_t readSizeT(const std::string& l, size_t i)
{
		return std::atoi(readQuoted(l, i).c_str());
}

zo readZO(const std::string&l, size_t i)
{
	return std::stof(readQuoted(l, i).c_str());
}

std::vector<t_config> g_conf = {};

t_config g_default_set =
{
		.type = T_MEASURE,
		.name = "",
		.expressor = EXPRESSOR_CURRENT,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = {},
		.damp = 0.5,
};

t_config g_bias_set =
{
		.type = T_BIAS,
		.name = "bias",
};

t_config g_axon_set =
{
		.type = T_AXON,
};

std::vector<std::string> readSplit(const std::string& l)
{
	std::vector<std::string> o = {};
	size_t s = 0;
	std::string n;

	while (s < l.length())
	{
		n = readQuoted(l, s);
		o.push_back(n);
		s += n.length() + 1;
	}
	return o;
}

void ifLooksLikeScale(const std::string& s, int& scaleMin, int& scaleMax, std::string& unit)
{
	size_t div = 0;
	size_t min = 0;
	size_t max = 0;
	size_t u = 0;

	for (size_t i = 0; i < s.length(); i++)
	{
		if (s.at(i) >= '0' && s.at(i) <= '9')
		{
			if (!min && div == 0) min = i;
			if (!max && div == 1) max = i;
			continue;
		}
		else if (s.at(i) == ':') div++;
		else
		{
			if (!u && div == 2)
				u = i;
			else if (!u) return;
		}
	}
	if (!u || !max) return;
	scaleMin = readSizeT(s, min);
	scaleMax = readSizeT(s, max);
	unit = readQuoted(s, u);
	return;
}

void ifLooksLikeDamp(const std::string& s, zo& damp)
{
	size_t dot = 0;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (s.at(i) == '.')
			dot++;
		else if (s.at(i) >= '0' && s.at(i) <= '9')
			continue;
		else
			return;
	}
	if (dot != 1) return;
	damp = readZO(s, 0);
}

void parse(const std::string& l)
{
	std::string name = g_default_set.name;
	int type = g_default_set.type;
	int expressor = g_default_set.expressor;
	int scaleMin = g_default_set.scaleMin;
	int scaleMax = g_default_set.scaleMax;
	std::string unit = g_default_set.unit;
	std::vector<std::string> scale = g_default_set.scale;
	zo damp = g_default_set.damp;

	std::string make = "";

	std::vector<std::string> spl = readSplit(l);

	for (size_t i = 0; i < spl.size(); i++)
	{
		if (spl[i].length() == 1)
		{
			if (spl[i] == "n") make = "neuron";
			if (spl[i] == "a") make = make != "" ? make : "axon";
			if (spl[i] == "a") type = make != "" ? T_ACTION : type;
			if (spl[i] == "b") make = "bias";
			if (spl[i] == "v") type = T_VITAL;
			if (spl[i] == "p") type = T_PHYSICAL;
			if (spl[i] == "m") type = T_MEASURE;
			if (spl[i] == "t") expressor = EXPRESSOR_THRESHOLD;
			if (spl[i] == "o") expressor = EXPRESSOR_ORIGINAL_THRESHOLD;
			if (spl[i] == "c") expressor = EXPRESSOR_CURRENT;
		}
		if (spl[i].length() > 1)
		{
			if (!name.length())
				name = spl[i];
			else
				scale.push_back(spl[i]);
			ifLooksLikeScale(spl[i], scaleMin, scaleMax, unit);
			ifLooksLikeDamp(spl[i], damp);
		}
	}

	if (make == "neuron")
	{
		g_conf.push_back({
			.type = type,
			.name = name,
			.expressor = expressor,
			.scaleMin = scaleMin,
			.scaleMax = scaleMax,
			.unit = unit,
			.scale = scale,
			.damp = damp,
		});
	}

	if (make == "bias")
	{
		size_t a = readSizeT(l, 2);
		while (a--)
			g_conf.push_back(g_bias_set);
	}

	if (make == "axon")
	{
		size_t a = readSizeT(l, 2);
		while (a--)
			g_conf.push_back(g_axon_set);
	}
}

void loadConf(const char* u_fn)
{
	std::string fn(u_fn);
	std::fstream file_read;
	file_read.open(u_fn, std::ios::in);
	if (!file_read)
	{
		file_read.close();
		std::cout << "Failed to load or empty string for file " << u_fn << "." << std::endl;
		return ;
	}
	std::string line;
	while (std::getline(file_read, line))
	{
		hard_trim(line);
		if (!line.length()) continue;
		parse(line);
	}
	for (size_t i = 0; i < g_conf.size(); i++)
		(Being(g_conf[i]));
}

int main() {
	prepare();
	Being::reset();
	loadConf("config.txt");
	run();
	destroy();
	return 0;
}
