#ifndef HEADER_HPP
# define HEADER_HPP

# define CONFIG_FILE "config.md"
# define MEMORY_TYPE_SIZE unsigned int
# define zo float
# define LEADING_ZEROS 5
# define PRECISION_DIGITS 8
# define ASCII_BAR_LENGTH 32
# define STEP_MS 100

static bool g_showDebug = true;

# define DISPLAY_SET_DEFAULT \
	DISPLAY_BAR + \
	DISPLAY_DESCRIPTION + \
	DISPLAY_AXONS + \
	DISPLAY_BIAS + \
	DISPLAY_HEADER + \
	DISPLAY_CHARS + \
	DISPLAY_WANT + \
	DISPLAY_BAR_ALL

#endif
