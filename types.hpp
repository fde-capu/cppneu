#ifndef TYPES_HPP
# define TYPES_HPP

# include "extern.hpp"

# define MEMORY_TYPE_SIZE unsigned int
# define zo float
# define ST_MAX std::numeric_limits<size_t>::max()

typedef struct NeuronConfig
{
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
	size_t slotIn = ST_MAX;
	size_t slotOut = ST_MAX;
	zo multiplier;
} n_config;

std::ostream& operator<< (std::ostream&, n_config const&);

#endif
