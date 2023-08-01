#ifndef HEADER_HPP
# define HEADER_HPP

# include "extern.hpp"
# include "defines.hpp"

# define DEFAULT_NEURON_TYPE T_MEASURE

# define DEFAULT_CONFIG_FILE "config.md"
# define DEFAULT_SYS_CONFIG_FILE "sys.conf"

# define DEFAULT_EXPRESSOR E_SHORT

# define SAVE_DIRECTORY "saves"
# define PRECISION_DIGITS 8
# define ASCII_BAR_LENGTH 10
# define DEFAULT_TICK_MS 100

# define LEADING_ZEROS 3

static bool g_showDebug = false;
static int g_showStatus = 1;
static bool g_colors = true;
extern long displaySet;

void debug(const std::string& s);
void status(const std::string& s);
void warn(const std::string& s);

template <typename T>
void debug(std::string s, T any)
{ debug(s + " " + std::to_string(any)); }

#endif
