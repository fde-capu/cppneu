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

# define SLEEP_REST std::this_thread::sleep_for(std::chrono::milliseconds(50));

template <typename T>
void select(const std::string& header, const std::vector<T>& gb, size_t& s)
{
	size_t cancel(s);
	int ch;
	std::string search = "";
	size_t i;
	size_t chosen = ST_MAX;
	bool found;
	while (chosen == ST_MAX)
	{
		found = false;
		while (search.length())
		{
			i = 0;
			for (const T& b : gb)
			{
				if (
							b.name.find(search) != std::string::npos
					||	std::to_string(i).find(search) != std::string::npos
				)
				{
					s = i;
					found = true;
					break ;
				}
				i++;
			}
			if (found)
				break ;
			search.pop_back();
		}

		clear();
		printw("%s", header.c_str());
		if (search.length())
			printw(" /%s_\n", search.c_str());
		else
			printw("\n");

		i = 0;
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

			if (ch == 27)
			{
				ch = getch();
				if (ch == -1)
				{
					chosen = cancel;
					break ;
				}
				if (ch == '[')
				{
					ch = getch();
					if (ch == 'A')
					{
						s = s == 0 ? gb.size() - 1 : s - 1;
						search = "";
						break ;
					}
					if (ch == 'B')
					{
						s = s == gb.size() - 1 ? 0 : s + 1;
						search = "";
						break ;
					}
				}
			}
			if (ch == '/' && !search.length())
				continue ;
			if (ch >= ' ' && ch <= '~')
			{
				search.push_back(ch);
				break ;
			}
			if (ch == '\b' || ch == KEY_BACKSPACE || ch == 127)
			{
				if (!search.length())
					continue ;
				search.pop_back();
				break ;
			}
			if (ch == '\n')
			{
				chosen = s;
				break ;
			}
			SLEEP_REST
		}

	}
	s = chosen;
}

#endif
