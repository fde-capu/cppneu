#include "helpers.hpp"
#include <boost/algorithm/string.hpp>

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

std::string zeroDotOut(zo n)
{
	return n == 1.0 ? "1.0" :
		removeZerosFromEnd(
		floatUp(n, PRECISION_DIGITS));
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

std::string removeZerosFromEnd(std::string float000)
{
	size_t i = float000.length();
	if (!i) return float000;
	while (--i && float000.at(i) == '0') ;
	float000 = float000.substr(0, ++i);
	return float000;
}

bool isAllDigits(const std::string& s)
{
	for (size_t i = 0; i < s.length(); i++)
		if (s.at(i) < '0' || s.at(i) > '9')
			return false;
	return true;
}

std::string readQuoted(const std::string& l,
	size_t& u_i)
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

size_t readSizeT(const std::string& l,
	size_t i)
{
		return std::atoi(readQuoted(l, i).c_str());
}

zo readZO(const std::string& l, size_t i)
{
	if (l == "1.0")
		return 1.0;
	return std::stof(readQuoted(
		"0." + l, i).c_str());
}

std::vector<std::string> readSplit
	(const std::string& l)
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

std::string join(const std::vector<std::string>& vec, char spacer)
{
	std::string out = "";
	size_t i = 0;
	while (i < vec.size())
	{
		out += vec[i];
		if (++i < vec.size())
			out += std::string(1, spacer);
	}
	return out;
}

std::vector<std::string> split(const std::string &s, char delimiter)
{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter)) {
				tokens.push_back(token);
		}
		return tokens;
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

template <typename T>
size_t nextUID(std::map<size_t, T>& m, size_t& g_)
{
	while(exist(m, g_))
		g_++;
	return g_;
}

std::fstream loadFile(const char* u_fn)
{
	std::string fn(u_fn);
	std::fstream file_read;
	file_read.open(u_fn, std::ios::in);
	if (!file_read)
	{
		file_read.close();
		std::cout << "Failed to load or empty string for file " << u_fn << "." << std::endl;
	}
	return file_read;
}

void prompt(const std::string& question, std::string& var)
{
	std::string answer(var);
	int ch;
	clear();
	printw("%s %s", question.c_str(), answer.c_str());
	refresh();
	while (true)
	{
		SLEEP_REST
		ch = getch();
		if (ch == ERR)
			continue ;
		if (ch == '\n')
		{
			var = answer;
			return ;
		}
		if (ch == '\b' || ch == KEY_BACKSPACE || ch == 127)
		{
			if (!answer.length())
				continue ;
			answer.pop_back();
			clear();
			printw("%s %s", question.c_str(), answer.c_str());
			refresh();
			continue ;
		}
		if (ch >= '!' && ch <= '~')
		{
			answer.push_back(ch);
			clear();
			printw("%s %s", question.c_str(), answer.c_str());
			refresh();
			continue ;
		}
	}
}

std::string to_lower(const std::string& upper)
{
	std::string lower(upper);
	for (size_t i = 0; i < lower.size(); ++i)
		lower[i] = std::tolower(static_cast<unsigned char>(lower[i]));
	return lower;
}

void select(const std::string& header, const std::vector<std::string>& name_list, size_t& s)
{
	size_t cancel(s);
	int ch;
	std::string search = "";
	size_t i;
	size_t chosen = ST_MAX;
	bool found;
	bool search_mark = false;
	while (chosen == ST_MAX)
	{
		found = false;
		while (search.length())
		{
			i = 0;
			for (const std::string& b : name_list)
			{
				if (
							to_lower(b).find(to_lower(search)) != std::string::npos
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
		if (search_mark || search.length())
		{
			printw(" /%s_\n", search.c_str());
		}
		else
			printw("\n");

		i = 0;
		for (const std::string& b : name_list)
		{
			if (i == s)
				REVERSE
			printw("%zu\t%s\n", i, b.c_str());
			if (i == s)
				UNREVERSE
			i++;
		}
//		printw("ch>%d\n", ch);
		refresh();

		while (true)
		{
			SLEEP_REST
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
					if (ch == 'A' || ch == 'B') // up or dn
					{
						s = ch == 'A' ?
								(s == 0 ? name_list.size() - 1 : s - 1)
							:	(s == name_list.size() - 1 ? 0 : s + 1);
						search = "";
						search_mark = false;
						break ;
					}
				}
			}
			if (ch == '/' && !search.length())
			{
				search_mark = true;
				break ;
			}
			if (ch >= ' ' && ch <= '~')
			{
				search.push_back(ch);
				break ;
			}
			if (ch == '\b' || ch == KEY_BACKSPACE || ch == 127)
			{
				if (!search.length())
				{
					search_mark = false;
					break ;
				}
				search.pop_back();
				break ;
			}
			if (ch == '\n')
			{
				chosen = s;
				break ;
			}
		}

	}
	s = chosen;
}

std::string funnyName(const std::string& base)
{
	size_t p;
	std::string out = "";
	char ch;
	int fullname = randomValue<int>(2, 4);

	while (fullname--)
	{
		ch = 0;
		while (true)
		{
			if (!ch)
				do { p = randomValue<size_t>(0, base.length() - 2); }
					while (base.at(p) < 'A' || base.at(p) > 'Z');
			if (ch && randomValue<int>(0, 1))
				do { p = randomValue<size_t>(0, base.length() - 2); }
					while (base.at(p) != ch);
			p += ch && p < base.length() - 1 ? 1 : 0;
			ch = base.at(p);
			if (ch == ' ')
				break ;
			out.push_back(ch);
		}
		if (fullname)
			out.push_back(ch);
	}

	return out;
}

size_t rtou(const std::string& roman) {
	std::unordered_map<char, size_t> roman_map = {
		{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
		{'C', 100}, {'D', 500}, {'M', 1000}
	};

	size_t result = 0;
	size_t prev = 0;
	size_t count = 0;

	for (auto it = roman.rbegin(); it != roman.rend(); ++it) {
		size_t curr = roman_map[*it];
		if (curr == 0)
			return 0;
		if (curr < prev && (prev / curr) > 10)
			return 0;
		if (curr == prev)
		{
			count++;
			if (count == 4 || (count == 2 && (curr == 5 || curr == 50 || curr == 500)))
				return 0;
		} else
			count = 1;
		if (curr < prev)
			result -= curr;
		else
			result += curr;
		prev = curr;
	}
	return result;
}

std::string utor(size_t algebric)
{
	std::vector<std::pair<size_t, std::string>> roman = {
		{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
		{100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
		{10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
	};

	std::string result;
	for (auto& pair : roman) {
		while (algebric >= pair.first) {
			result += pair.second;
			algebric -= pair.first;
		}
	}
	return result;
}

void nextRomanName(std::string& name)
{
	std::vector<std::string> ns = split(name, ' ');
	size_t r = rtou(ns.back());
	if (r)
		ns.pop_back();
	ns.push_back(utor(++r));
	name = join(ns, ' ');
}
