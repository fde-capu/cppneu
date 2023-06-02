#ifndef HELPERS_HPP
# define HELPERS_HPP

# include <bitset>
# include <sstream>
# include <cmath>
# include "defines.hpp"

std::string tobin(zo n);
int floatUp(zo n);
std::string zeroOut(zo n);
zo& zoRestrain(zo& n, zo min = 0.0, zo max = 1.0);

#endif
