#ifndef DEFINES_HPP
# define DEFINES_HPP

# define LAST_NEURON_IMPLEMENTATION "MetaNeuron.hpp"
# define NEURON MetaNeuron

# include "header.hpp"
# include <string>
# include <map>
# include <ncurses.h>
# include <thread>
# include <string>
# include <fstream>
# include <vector>
# include <iostream>

# define T_PHYSICAL 1
# define T_VITAL 2
# define T_ACTION 3
# define T_MEASURE 4
# define T_BIAS 20
# define T_AXON 40

# define T_DEFAULT T_MEASURE

# define T_PHYSICAL_CHAR 'p'
# define T_VITAL_CHAR 'v'
# define T_ACTION_CHAR 'a'
# define T_MEASURE_CHAR 'm'
# define T_BIAS_CHAR 'b'
# define T_AXON_CHAR 'x'
# define T_NEURON_CHAR 'n'

# define EXPRESSOR_THRESHOLD 1
# define EXPRESSOR_CURRENT 2
# define EXPRESSOR_ORIGINAL_THRESHOLD 3
# define EXPRESSOR_THRESHOLD_SHORT 4

# define E_THRESHOLD_CHAR 't'
# define E_CURRENT_CHAR 'c'
# define E_ORIGINAL_CHAR 'o'
# define E_SHORT_CHAR 's'

# define DISPLAY_BAR_ALL (1 << 0)
# define DISPLAY_BAR (1 << 1)
# define DISPLAY_CHARACTER (1 << 2)
# define DISPLAY_NUMBERS (1 << 3)
# define DISPLAY_DESCRIPTION (1 << 4)
# define DISPLAY_OUTS (1 << 5)
# define DISPLAY_AXONS (1 << 6)
# define DISPLAY_BIAS (1 << 7)
# define DISPLAY_HEADER (1 << 8)
# define DISPLAY_CHARS (1 << 9)
# define DISPLAY_PHYSICAL (1 << 10)
# define DISPLAY_VITAL (1 << 11)
# define DISPLAY_ACTION (1 << 12)
# define DISPLAY_MEASURES (1 << 13)
# define DISPLAY_WANT (1 << 14)

typedef struct TypeBeingConfig
{
	size_t UID;
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
void switchBias();

#endif
