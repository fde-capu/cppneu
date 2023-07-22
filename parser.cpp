#include "parser.hpp"
#include "helpers.hpp"

static size_t g_UID = 0;
size_t UID;
std::string name;
char type;
char expressor;
int scaleMin;
int scaleMax;
std::string unit;
std::vector<std::string> scale;
zo damp;
zo originalThreshold;
bool named;

void parseReset()
{
	UID = g_UID++;
	name = std::to_string(UID);
	type = 0;
	expressor = 0;
	scaleMin = g_default_set.scaleMin;
	scaleMax = g_default_set.scaleMax;
	unit = g_default_set.unit;
	scale = g_default_set.scale;
	damp = 0;
	originalThreshold = g_default_set.originalThreshold;
	named = false;
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
	if (!named) return false;
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
	if (!named)
	{
		name = n;
		named = true;
		return true;
	}
	return false;
}

// m/^{$x}[0-9]*\.?[0-9]+$/
bool uFormat(const std::string& s, char x)
{
	bool one_dot = false;
	if (s.at(0) != x) return false;
	for (size_t i = 1; i < s.length(); i++)
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
		v = readZO(s.substr(1));
}

bool looksLikeId(const std::string& s)
{
	if (!(	uFormat(s, ID_CHAR)
			||	uFormat(s, T_BIAS)
			||	uFormat(s, T_NEURON)
	)) return false;

	type = s.at(0) != ID_CHAR ? s.at(0) : type;
	type = type == T_NEURON ? 0 : type;
	size_t new_UID = readSizeT(s, 1);	
	if (!idTaken(new_UID))
		UID = new_UID;
	else
	{
		std::cerr << "Conflict id: " << s << "." << std::endl;
		return false;
	}
	return true;
}

bool looksLikeOriginalThreshold(const std::string &s)
{
	if (!uFormat(s, 'o')) return false;
	uRead(originalThreshold, s);
	return true;
}

bool looksLikeDamp(const std::string& s)
{
	if (!uFormat(s, 'd')) return false;
	uRead(damp, s);
	return true;
}

void autoGen(const std::string& l)
{
	std::string make = 
		l.at(0) == T_NEURON ? "neuron" : 
		l.at(0) == T_AXON ? "axon" :
		l.at(0) == T_BIAS ? "bias" :
		"";

	if (make == "")
	{
		std::cerr << "Warning: nothing to auto generate: " << l << std::endl;
		return ;
	}

	size_t a = readSizeT(l, 2);
	t_config set =
		make == "bias" ? g_bias_set :
		make == "axon" ? g_axon_set :
		g_default_set;
	if (make == "neuron")
		set.type = T_QUIET;
	while (a--)
	{
		g_conf.push_back(set);
	}
}

//	 /^\c{ }1\d+$/
bool looksLikeAutoGen(const std::string& s)
{
	enum phase { p_char , space , digit };
	phase c_phase = p_char;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (c_phase == p_char
			&& s.at(i) >= 'a' && s.at(i) <= 'z')
			{ c_phase = space; continue; }
		if (c_phase == space
			&& s.at(i) == ' ')
			{ c_phase = digit ; continue; }
		if (c_phase == digit
			&& s.at(i) >= '0' && s.at(i) <= '9')
			continue;
		return false;
	}
	autoGen(s);
	return true;
}

bool idTaken(const size_t& id)
{
	for (auto& c : g_conf)
		if (id == c.UID)
			return true;
	return false;
}

size_t idOrIdByName(const std::string& v)
{
	if (isAllDigits(v))
		return readSizeT(v);
	for (auto& c : g_conf)
		if (v == c.name)
			return c.UID;
	std::cerr << "Error! Name not found: '" << v << "'." << std::endl;
	return ST_MAX;
}

bool looksLikeAxon(const std::string& l)
{
	if (l.at(0) != T_AXON)
		return false;
	std::vector<std::string> spl = readSplit(l);
	std::vector<std::string> newAxon = split(spl[1], '-');
	if (newAxon.size() == 3)
	{
		t_config u_axon = g_axon_set;
		u_axon.slotIn = idOrIdByName(newAxon[0]);
		u_axon.multiplier = readZO(newAxon[1]);
		u_axon.slotOut = idOrIdByName(newAxon[2]);
		if (u_axon.slotIn == ST_MAX || u_axon.slotOut == ST_MAX)
		{
			std::cerr << "While processing '" << l << "'. Skipping." << std::endl;
			return false;
		}
		g_conf.push_back(u_axon);
		return true;
	}
	return false;
}

void parse(const std::string& l)
{
	if (looksLikeAutoGen(l))
		return ;
	if (looksLikeAxon(l))
		return ;

	parseReset();
	std::vector<std::string> spl = readSplit(l);

	for (auto& s : spl)
	{
		if (s.length() == 1)
		{
			if (
					s.at(0) == E_THRESHOLD
			||	s.at(0) == E_CURRENT
			||	s.at(0) == E_ORIGINAL
			||	s.at(0) == E_SHORT
			)
			{
				if (expressor)
					std::cerr << "Multiple expressors: " << l << std::endl;
				expressor = s.at(0);
				if (!named)
					name += std::string(expressor, 1);
			}
			
			if (
					s.at(0) == T_PHYSICAL
			||	s.at(0) == T_VITAL
			||	s.at(0) == T_ACTION
			||	s.at(0) == T_MEASURE
			||	s.at(0) == T_BIAS
			||	s.at(0) == T_QUIET
			)
			{
				if (type)
					std::cerr << "Type given more than once: " << l << std::endl;
				type = s.at(0);
				if (!named)
					name = std::string(type, 1) + name;
			}
		}

		if (s.length() > 1)
		{
			if (looksLikeName(s)) continue ; // Any string.
			if (looksLikeScale(s)) continue ; // min:max:unit
			if (looksLikeDamp(s)) continue ; // dnnn
			if (looksLikeOriginalThreshold(s)) continue ; // onnn
			if (looksLikeId(s)) continue ; // innn, bnnn, nnnn
			if (thenItsScaleName(s)) continue ; // Other strings (sequenctialy)
			std::cerr << "Error: id '" << s << "' on '" << l << "'. Not created." << std::endl;
			g_UID--;
			return ;
		}
	}

	if (type == T_BIAS)
	{
		expressor = expressor ? expressor : g_bias_set.expressor;
		type = g_bias_set.type;
	}

	g_conf.push_back({
		.UID = UID,
		.name = name,
		.type = type ? type : g_default_set.type,
		.expressor = expressor ? expressor : g_default_set.expressor,
		.scaleMin = scaleMin,
		.scaleMax = scaleMax,
		.unit = unit,
		.scale = scale,
		.damp = damp ? damp : g_default_set.damp,
		.originalThreshold = originalThreshold,
	});
}

void loadConf(const char* u_fn)
{
	std::fstream file_read = loadFile(u_fn);
	std::string line;
	while (std::getline(file_read, line))
	{
		hard_trim(line);
		if (!line.length()) continue;
		parse(line);
	}
}
