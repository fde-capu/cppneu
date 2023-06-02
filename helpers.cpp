#include "helpers.hpp"

std::string tobin(zo n)
{
	std::bitset<32> binarySet(static_cast<unsigned int>(n));
	std::stringstream ss;
	ss << binarySet;
	return ss.str();
}

int floatUp(zo n)
{
	return static_cast<int>(n * pow(10, LEADING_ZEROS));
}

std::string zeroOut(zo n)
{
	std::string str(std::to_string(floatUp(n)));
	if (str.length() > LEADING_ZEROS)
	{
		str = "";
		while (str.length() < LEADING_ZEROS)
			str += "*";
		return str;
	}
	while (str.length() < LEADING_ZEROS)
		str = "0" + str;
	return str;
}

zo& zoRestrain(zo& n, zo min, zo max)
{
	n = n > max ? max : n < min ? min : n;
	return n;
}
