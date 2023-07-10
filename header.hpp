#ifndef HEADER_HPP
# define HEADER_HPP
# include "defines.hpp"

# define DEFAULT_CONFIG_FILE "config.md"

# define DEFAULT_NEURON_TYPE T_MEASURE
# define DEFAULT_EXPRESSOR E_SHORT

# define LEADING_ZEROS 3
# define PRECISION_DIGITS 8
# define ASCII_BAR_LENGTH 10
# define DEFAULT_TICK_MS 100

static bool g_showDebug = false;
static bool g_colors = true;

# define DISPLAY_SET_DEFAULT \
	DISPLAY_BAR + \
	DISPLAY_DESCRIPTION + \
	DISPLAY_HEADER + \
	DISPLAY_WANT + \
	DISPLAY_BAR_ALL

#endif
