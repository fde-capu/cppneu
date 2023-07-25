#ifndef HELPERS_HPP
# define HELPERS_HPP

# include "extern.hpp"
# include "types.hpp"
# include "header.hpp"
# include "defines.hpp"
# include "randoms.hpp"

std::string tobin(zo n);
std::string floatUp(zo n, size_t digitis = LEADING_ZEROS, bool mark = false);
std::string floatUpFire(zo n);
zo& zoRestrain(zo& n, zo min = 0.0, zo max = 1.0);
size_t readSizeT(const std::string& l, size_t i = 0);
std::string readQuoted(const std::string& l, size_t&);
zo readZO(const std::string&l, size_t i = 0);
std::vector<std::string> readSplit(const std::string& l);
std::vector<std::string> split(const std::string &s, char delimiter);
void hard_trim(std::string& line);
zo max();
std::string to_string(std::vector<std::string>);

template <typename T>
void toggleBit(T& d, T b)
{ d += d & b ? -b : b; }

template <typename T>
bool exists (std::map<size_t, T>& m, size_t i) {
	return m.find(i) != m.end();
}

std::string removeZerosFromEnd(std::string float000);

# define BOLD if (g_colors) attron(A_BOLD);
# define UNBOLD if (g_colors) attroff(A_BOLD);
# define NORMAL if (g_colors) attron(A_NORMAL);
# define UNNORMAL if (g_colors) attroff(A_NORMAL);
# define STANDOUT if (g_colors) attron(A_STANDOUT);
# define UNSTANDOUT if (g_colors) attroff(A_STANDOUT);
# define UNDERLINE if (g_colors) attron(A_UNDERLINE);
# define UNUNDERLINE if (g_colors) attroff(A_UNDERLINE);
# define REVERSE if (g_colors) attron(A_REVERSE);
# define UNREVERSE if (g_colors) attroff(A_REVERSE);
# define BLINK if (g_colors) attron(A_BLINK);
# define UNBLINK if (g_colors) attroff(A_BLINK);
# define DIM if (g_colors) attron(A_DIM);
# define UNDIM if (g_colors) attroff(A_DIM);
# define PROTECT if (g_colors) attron(A_PROTECT);
# define UNPROTECT if (g_colors) attroff(A_PROTECT);
# define INVIS if (g_colors) attron(A_INVIS);
# define UNINVIS if (g_colors) attroff(A_INVIS);
# define ALTCHARSET if (g_colors) attron(A_ALTCHARSET);
# define UNALTCHARSET if (g_colors) attroff(A_ALTCHARSET);
# define CHARTEXT if (g_colors) attron(A_CHARTEXT);
# define UNCHARTEXT if (g_colors) attroff(A_CHARTEXT);

bool isAllDigits(const std::string& s);

# define UPC - 32
# define DNC + 32

std::fstream loadFile(const char* u_fn);
std::string funnyName(const std::string&);

void prompt(const std::string& question, std::string& var);

# define SLEEP_REST std::this_thread::sleep_for(std::chrono::milliseconds(10));

template <typename T>
void select(const std::string& header, const std::vector<T>& gb, size_t& s)
{
	int ch;
	size_t i;
	size_t chosen = ST_MAX;
	while (chosen == ST_MAX)
	{
		i = 0;
		clear();
		printw("%s\n", header.c_str());
		for (const T& b : gb)
		{
			if (i == s)
				REVERSE
			printw("%zu\t%s\n", i, b.name.c_str());
			if (i == s)
				UNREVERSE
			i++;
		}
		printw("ch>%d\n", ch);
		refresh();
		while (true)
		{
			ch = getch();
			if (ch == ERR)
				continue ;
			if (ch == '\n')
			{
				chosen = s;
				return ;
			}
			if (ch == 66 || ch == 'j')
			{
				s = s == gb.size() - 1 ? 0 : s + 1;
				break ;
			}
			if (ch == 65 || ch == 'k')
			{
				s = s == 0 ? gb.size() - 1 : s - 1;
				break ;
			}
			SLEEP_REST
		}
	}
}

#endif
