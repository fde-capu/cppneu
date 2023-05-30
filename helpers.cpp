#include "helpers.hpp"

std::string tobin(zo n)
{
	std::bitset<32> binarySet(static_cast<unsigned int>(n));
	std::stringstream ss;
	ss << binarySet;
	return ss.str();
}

