#ifndef DEFINES_HPP
# define DEFINES_HPP
# include "types.hpp"

# define LAST_NEURON_IMPLEMENTATION "MetaNeuron.hpp"
# define NEURON MetaNeuron

# include <string>
# include <map>
# include <ncurses.h>
# include <thread>
# include <string>
# include <fstream>
# include <vector>
# include <iostream>

# define T_PHYSICAL 'p'
# define T_VITAL 'v'
# define T_ACTION 'a'
# define T_MEASURE 'm'
# define T_AXON 'x'
# define T_BIAS 'b'
# define T_NEURON 'n'
# define ID_CHAR 'i'

# define E_THRESHOLD 't'
# define E_CURRENT 'c'
# define E_ORIGINAL 'o'
# define E_SHORT 's'

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

extern bool g_quit;
extern bool g_running;
extern std::vector<t_config> g_conf;
extern size_t g_tick_ms;

void printDebug();
void loadConf(const char* u_fn);
void doQuit();
void debug(std::string s);

template <typename T>
void debug(std::string s, T any)
{ debug(s + " " + std::to_string(any)); }

void switchBias();
void increment(size_t&, size_t);
void decrement(size_t&, size_t);
std::string zeroDotOut(zo n);

# define BIAS_NAME "bias"

# define EPSILON 0.00000001
# define FLOAT_MARK "$"
# define ASCII_BAR_SET "[ ,.;:!]"
# define AXON_DISPLAY_SET "--**"
# define ASCII_CHAR_SCALE " -~=+*oO&#%@"

#endif
