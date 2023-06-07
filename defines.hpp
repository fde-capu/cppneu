#ifndef DEFINES_HPP
# define DEFINES_HPP

# include <string>
# include <map>
# include <ncurses.h>
# include <thread>
# include <string>
# include <fstream>

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

static bool g_quit = false;
static bool g_running = false;
static bool g_showMenu = true;
static bool g_showDebug = false;

void printMenu();
void printDebug();
void dealKeyPress(int ch);
void loadConf(const char* u_fn);
void doQuit();
void debug(std::string s);
void menuInit();

#endif
