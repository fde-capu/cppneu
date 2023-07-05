#ifndef PARSER_HPP
# define PARSER_HPP

#include "defines.hpp"
#include "Being.hpp"
#include "helpers.hpp"
#include <string>

t_config g_default_set =
{
		.type = T_MEASURE,
		.name = "",
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
		.type = T_BIAS,
		.name = BIAS_NAME,
		.expressor = EXPRESSOR_CURRENT,
		.damp = DEFAULT_DAMP,
};

t_config g_axon_set =
{
		.type = T_AXON,
};

#endif
