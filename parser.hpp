#ifndef PARSER_HPP
# define PARSER_HPP

#include "defines.hpp"
#include "Being.hpp"
#include "helpers.hpp"
#include <string>

t_config g_default_set =
{
		.name = "",
		.type = DEFAULT_NEURON_TYPE,
		.expressor = DEFAULT_EXPRESSOR,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = {},
		.damp = DEFAULT_DAMP,
		.originalThreshold = 0.0,
};

t_config g_bias_set =
{
		.name = BIAS_NAME,
		.type = T_BIAS,
		.expressor = DEFAULT_EXPRESSOR,
		.damp = DEFAULT_DAMP,
};

t_config g_axon_set =
{
		.type = T_AXON
};

#endif
