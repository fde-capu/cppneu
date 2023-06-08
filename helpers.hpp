#ifndef HELPERS_HPP
# define HELPERS_HPP

# include <bitset>
# include <sstream>
# include <cmath>
# include "header.hpp"
# include <vector>

std::string tobin(zo n);
int floatUp(zo n);
std::string zeroOut(zo n);
zo& zoRestrain(zo& n, zo min = 0.0, zo max = 1.0);
size_t readSizeT(const std::string& l, size_t i);
std::string readQuoted(const std::string& l, size_t i);
zo readZO(const std::string&l, size_t i);
std::vector<std::string> readSplit(const std::string& l);
void hard_trim(std::string& line);
zo max();

#endif
