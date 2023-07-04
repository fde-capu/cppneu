#include "helpers.hpp"

std::string tobin(zo n)
{
	std::bitset<32> binarySet(static_cast<unsigned int>(n));
	std::stringstream ss;
	ss << binarySet;
	return ss.str();
}

std::string floatUp(zo n, size_t digits, bool mark)
{
	if (n >= 1.0 || n < 0.0)
		return	std::to_string(n).substr
			(0, digits - 1) +
				(mark ? FLOAT_MARK : "");
	std::string fout(std::to_string(n));
	fout = fout.substr(fout.find('.') + 1);
	if (fout.length() > digits) fout = fout.substr(0, digits);
	while (fout.length() < digits)
		fout += "0";
	return fout;
}

std::string floatUpFire(zo n)
{ return floatUp(n, LEADING_ZEROS, true); }

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

std::string removeZerosFromEnd(std::string float000)
{
	size_t i = float000.length();
	if (!i) return float000;
	while (--i && float000.at(i) == '0') ;
	float000 = float000.substr(0, ++i);
	return float000;
}

std::string readQuoted(const std::string& l, size_t& u_i)
{
	size_t i(u_i);
	char f = l.at(i) == '"' ? '"' : ' ';
	i += f == '"' ? 0 : -1;
	u_i += f == '"' ? 1 : 0;

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

zo max()
{ return 1.0; }

std::string to_string (std::vector<std::string> v)
{
	std::stringstream ss;
	for (auto& vi : v)
	{
		if (vi.find(' ') != std::string::npos) ss << "\"";
		ss << vi;
		if (vi.find(' ') != std::string::npos) ss << "\"";
		ss << " ";
	}
	return ss.str();
}

void toggleBit(int& d, int b)
{
	d += d & b ? -b : b;
}

template <typename T>
size_t nextUID(std::map<size_t, T>& m, size_t& g_)
{
	while(exist(m, g_))
		g_++;
	return g_;
}
