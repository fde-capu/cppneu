#ifndef DEFINES_HPP
# define DEFINES_HPP

# include "header.hpp"
# include <string>
# include <map>
# include <ncurses.h>
# include <thread>
# include <string>
# include <fstream>
# include <vector>

# define T_PHYSICAL 1
# define T_VITAL 2
# define T_ACTION 3
# define T_MEASURE 4
# define T_BIAS 20
# define T_AXON 40

# define EXPRESSOR_THRESHOLD 1
# define EXPRESSOR_CURRENT 2
# define EXPRESSOR_ORIGINAL_THRESHOLD 3
# define EXPRESSOR_THRESHOLD_SHORT 4

# define DISPLAY_BAR 1
# define DISPLAY_CHARACTER 2
# define DISPLAY_NUMBERS 4
# define DISPLAY_DESCRIPTION 8
# define DISPLAY_ALL DISPLAY_BAR + DISPLAY_CHARACTER + DISPLAY_NUMBERS + DISPLAY_DESCRIPTION

typedef struct TypeBeingConfig
{
	int type;
	std::string name;
	int expressor;
	int scaleMin;
	int scaleMax;
	std::string unit;
	std::vector<std::string> scale;
	zo damp;
} t_config;

extern bool g_quit;
extern bool g_running;
extern std::vector<t_config> g_conf;

void printDebug();
void loadConf(const char* u_fn);
void doQuit();
void debug(std::string s);

#endif
