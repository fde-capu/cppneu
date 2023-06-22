#include "parser.hpp"

size_t UID;
std::string name;
int type;
int expressor;
int scaleMin;
int scaleMax;
std::string unit;
std::vector<std::string> scale;
zo damp;

void parseReset()
{
	UID = 0;
	name = g_default_set.name;
	type = g_default_set.type;
	expressor = g_default_set.expressor;
	scaleMin = g_default_set.scaleMin;
	scaleMax = g_default_set.scaleMax;
	unit = g_default_set.unit;
	scale = g_default_set.scale;
	damp = g_default_set.damp;
}

bool looksLikeScale(const std::string& s)
{
	size_t div = 0;
	size_t min = 0;
	size_t max = 0;
	size_t u = 0;

	for (size_t i = 0; i < s.length(); i++)
	{
		if (s.at(i) >= '0' && s.at(i) <= '9')
		{
			if (!min && div == 0) min = i;
			if (!max && div == 1) max = i;
			continue;
		}
		else if (s.at(i) == ':') div++;
		else
		{
			if (!u && div == 2)
				u = i;
			else if (!u) return false;
		}
	}
	if (!u || !max) return false;
	scaleMin = readSizeT(s, min);
	scaleMax = readSizeT(s, max);
	unit = readQuoted(s, u);
	return true;
}

bool thenItsScaleName(const std::string& s)
{
	if (!name.length()) return false;
	scale.push_back(s);
	return true;
}

//	m/^\c\d+$/
bool isGenericUFormat(const std::string& s)
{
	size_t i = 0;
	if (s.at(i) < 'a' || s.at(i) > 'z') return false;
	while (++i < s.length() && s.at(i) >= '0' && s.at(i) <= '9');
	return i > 1 && i == s.length();
}

bool looksLikeName(const std::string& n)
{
	if (isGenericUFormat(n))
		return false;
	if (!name.length())
	{
		name = n;
		return true;
	}
	return false;
}

// m/^{$x}[0-9]*\.?[0-9]+$/
bool uFormat(const std::string& s, char x)
{
	bool one_dot = false;
	if (s.at(0) != x) return false;
	for (size_t i = 1; i < s.length() - 1; i++)
	{
		if (s.at(i) == '.')
		{
			if (one_dot)
				return false;
			else
				one_dot = true;
			continue ;
		}
		if (s.at(i) >= '0' && s.at(i) <= '9')
			continue ;
		return false;
	}
	return true;
}

template <typename T>
void uRead(T& v, const std::string& s)
{
	if (s.substr(1) == "1.0")
		v = 1.0;
	else
		v = readZO("0." + s.substr(1));
}

bool looksLikeId(const std::string& s)
{
	if (!uFormat(s, 'i')) return false;
	UID = readSizeT(s, 1);	
	return true;
}

bool looksLikeDamp(const std::string& s)
{
	if (!uFormat(s, 'd')) return false;
	uRead(damp, s);
	return true;
}

void parse(const std::string& l)
{
	parseReset();
	std::string make = "";

	std::vector<std::string> spl = readSplit(l);

	for (auto& s : spl)
	{
		if (s.length() == 1)
		{
			if (s.at(0) == T_ACTION_CHAR) type = T_ACTION;
			if (s.at(0) == T_BIAS_CHAR) make = "bias";
			if (s.at(0) == E_CURRENT_CHAR) expressor = EXPRESSOR_CURRENT;
			if (s.at(0) == T_MEASURE_CHAR) type = T_MEASURE;
			if (s.at(0) == E_ORIGINAL_CHAR) expressor = EXPRESSOR_ORIGINAL_THRESHOLD;
			if (s.at(0) == T_PHYSICAL_CHAR) type = T_PHYSICAL;
			if (s.at(0) == E_SHORT_CHAR) expressor = EXPRESSOR_THRESHOLD_SHORT;
			if (s.at(0) == E_THRESHOLD_CHAR) expressor = EXPRESSOR_THRESHOLD;
			if (s.at(0) == T_VITAL_CHAR) type = T_VITAL;
			if (s.at(0) == T_AXON_CHAR) make = "axon";
		}
		if (s.length() > 1)
		{
			if (looksLikeName(s)) continue ;
			if (looksLikeScale(s)) continue ;
			if (looksLikeDamp(s)) continue ;
			if (looksLikeId(s)) continue ;
			if (thenItsScaleName(s)) continue ;
		}
	}

	if (make == "") // default to "neuron"
	{
		g_conf.push_back({
			.UID = UID,
			.type = type,
			.name = name,
			.expressor = expressor,
			.scaleMin = scaleMin,
			.scaleMax = scaleMax,
			.unit = unit,
			.scale = scale,
			.damp = damp,
		});
	}

	if (make == BIAS_NAME)
	{
		size_t a = readSizeT(l, 2);
		while (a--)
			g_conf.push_back(g_bias_set);
	}

	if (make == "axon")
	{
		size_t a = readSizeT(l, 2);
		while (a--)
			g_conf.push_back(g_axon_set);
	}
}

void loadConf(const char* u_fn)
{
	std::string fn(u_fn);
	std::fstream file_read;
	file_read.open(u_fn, std::ios::in);
	if (!file_read)
	{
		file_read.close();
		std::cout << "Failed to load or empty string for file " << u_fn << "." << std::endl;
		return ;
	}
	std::string line;
	while (std::getline(file_read, line))
	{
		hard_trim(line);
		if (!line.length()) continue;
		parse(line);
	}
}
