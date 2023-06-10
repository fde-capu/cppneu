#include "Being.hpp"
#include "helpers.hpp"



std::string Being::getDescription()
{
	double scaleFactor;
	size_t scaledExpressor;
	zo getExpressor;
	std::stringstream ss;

	getExpressor = expressor == EXPRESSOR_CURRENT ? inputValue :
								expressor == EXPRESSOR_THRESHOLD ? threshold :
								expressor == EXPRESSOR_ORIGINAL_THRESHOLD ? originalThreshold :
								expressor == EXPRESSOR_THRESHOLD_SHORT ?
									(threshold - originalThreshold) / (1.0 - originalThreshold)
								: 0.0;
	if (outputValue)
		ss << "* ";
	else
		ss << "  ";
	ss << name;
	if (isBeing())
	{
		if (scaleMax)
		{
			scaleFactor = static_cast<double>(scaleMax - scaleMin);
			scaledExpressor = static_cast<int>(getExpressor * scaleFactor) + scaleMin;
			ss << ": " << scaledExpressor << unit.c_str();
		}
		if (scale.size())
		{
			scaleFactor = static_cast<double>(scale.size());
			scaledExpressor = static_cast<int>(getExpressor * scaleFactor);
			if (scaledExpressor > scale.size() - 1) scaledExpressor = scale.size() - 1;
			ss << ": " << scale[scaledExpressor];
		}
		if (!scale.size() && !scaleMax)
		{
			scaleFactor = static_cast<double>(1.0);
			scaleFactor = static_cast<double>(getExpressor * scaleFactor);
			ss << ": " << scaleFactor;
		}
	}
	return ss.str();
}
