#include "parser.hpp"

bool looksLikeScale(const std::string& s, int& scaleMin, int& scaleMax, std::string& unit)
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

void ifLooksLikeDamp(const std::string& s, zo& damp)
{
	size_t dot = 0;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (s.at(i) == '.')
			dot++;
		else if (s.at(i) >= '0' && s.at(i) <= '9')
			continue;
		else
			return;
	}
	if (dot != 1) return;
	damp = readZO(s, 0);
}

void parse(const std::string& l)
{
	std::string name = g_default_set.name;
	int type = g_default_set.type;
	int expressor = g_default_set.expressor;
	int scaleMin = g_default_set.scaleMin;
	int scaleMax = g_default_set.scaleMax;
	std::string unit = g_default_set.unit;
	std::vector<std::string> scale = g_default_set.scale;
	zo damp = g_default_set.damp;

	std::string make = "";

	std::vector<std::string> spl = readSplit(l);

	for (size_t i = 0; i < spl.size(); i++)
	{
		if (spl[i].length() == 1)
		{
			if (spl[i] == "a") type = T_ACTION;
			if (spl[i] == "b") make = "bias";
			if (spl[i] == "c") expressor = EXPRESSOR_CURRENT;
			if (spl[i] == "m") type = T_MEASURE;
			if (spl[i] == "n") make = "neuron";
			if (spl[i] == "o") expressor = EXPRESSOR_ORIGINAL_THRESHOLD;
			if (spl[i] == "p") type = T_PHYSICAL;
			if (spl[i] == "s") expressor = EXPRESSOR_THRESHOLD_SHORT;
			if (spl[i] == "t") expressor = EXPRESSOR_THRESHOLD;
			if (spl[i] == "v") type = T_VITAL;
			if (spl[i] == "x") make = "axon";
		}
		if (spl[i].length() > 1)
		{
			if (!name.length())
				name = spl[i];
			else
			{
				if (!looksLikeScale(spl[i], scaleMin, scaleMax, unit))
					scale.push_back(spl[i]);
				ifLooksLikeDamp(spl[i], damp);
			}
		}
	}

	if (make == "" || make == "neuron")
	{
		g_conf.push_back({
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

	if (make == "bias")
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
