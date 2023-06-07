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

void hard_trim(std::string& line)
{
	std::string out;
	char last = ' ';
	char now = 0;
	size_t i = -1;
	while (++i < line.length())
	{
		now = line.at(i);
		if (now == '#')	break ;
		if (now == '\'') now = '"';
		if (now == '\t') now = ' ';
		if (now == ';') now = ' ';
		if (last == ' ' && now == ' ') continue ;
		last = now;
		out += now;
	}
	if (out.length())
		if (out.at(out.length() - 1) == ' ')
			out = out.substr(0, out.length() - 1);
	if (out.length() < 3)
		out = "";
	line = out;
}

std::string readQuoted(const std::string& l, size_t i)
{
	char f = l.at(i) == '"' ? '"' : ' ';
	i += f == '"' ? 0 : -1;
	std::string o;
	while (++i < l.length() && l.at(i) != f)
		o += l.at(i);
	return o;
}

size_t readSizeT(const std::string& l, size_t i)
{
		return std::atoi(readQuoted(l, i).c_str());
}

zo readZO(const std::string&l, size_t i)
{
	return std::stof(readQuoted(l, i).c_str());
}

std::vector<std::string> readSplit(const std::string& l)
{
	std::vector<std::string> o = {};
	size_t s = 0;
	std::string n;

	while (s < l.length())
	{
		n = readQuoted(l, s);
		o.push_back(n);
		s += n.length() + 1;
	}
	return o;
}

