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
		.expressor = EXPRESSOR_CURRENT,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = {},
		.damp = 0.5,
};

t_config g_bias_set =
{
		.type = T_BIAS,
		.name = BIAS_NAME,
		.damp = -1.0,
};

t_config g_axon_set =
{
		.type = T_AXON,
};

#endif
