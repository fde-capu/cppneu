#ifndef PARSER_HPP
# define PARSER_HPP

# include "types.hpp"
# include "header.hpp"

t_config g_default_set =
{
		.name = "",
		.type = DEFAULT_NEURON_TYPE,
		.expressor = DEFAULT_EXPRESSOR,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = {},
		.damp = -1.0,
		.originalThreshold = 0.0,
};

t_config g_bias_set =
{
		.type = T_BIAS,
		.expressor = DEFAULT_EXPRESSOR,
		.damp = -1.0,
};

t_config g_axon_set =
{
		.type = T_AXON
};

bool idTaken(const size_t&);

#endif
