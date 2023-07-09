#ifndef HELPERS_HPP
# define HELPERS_HPP

# include "defines.hpp"
# include <bitset>
# include <sstream>
# include <cmath>
# include "header.hpp"
# include <vector>
# include <map>

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
void toggleBit(int&, int);

template <typename T>
bool exists (std::map<size_t, T>& m, size_t i) {
	return m.find(i) != m.end();
}

std::string removeZerosFromEnd(std::string float000);

# define BOLD if (g_colors) attron(A_BOLD);
# define UNBOLD if (g_colors) attroff(A_BOLD);

#endif
