#include "Being.hpp"
#include "helpers.hpp"

int Being::displaySet = \
	DISPLAY_BAR + \
	DISPLAY_DESCRIPTION + \
	DISPLAY_AXONS + \
	DISPLAY_BIAS + \
	DISPLAY_HEADER + \
	DISPLAY_CHARS + \
	DISPLAY_WANT + \
	DISPLAY_BAR_ALL \
;

void Being::setDisplay(int bit_value)
{
	toggleBit(displaySet, bit_value);
}

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
		if (!scale.size() && !scaleMax && isStatsVisible())
		{
			scaleFactor = static_cast<double>(1.0);
			scaleFactor = static_cast<double>(getExpressor * scaleFactor);
			ss << ": " << scaleFactor;
		}
	}
	return ss.str();
}

bool Being::isStatsVisible()
{ return
				type == T_MEASURE; }

bool Being::isBarVisible()
{ return
				type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
		||	type == T_BIAS
		||	type == T_PHYSICAL
;}

bool Being::isCharacterVisible()
{	return
				type == T_VITAL
		||	type == T_MEASURE
		||	type == T_BIAS
;}

bool Being::isOutBlockVisible()
{	return
				type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
		||	type == T_BIAS
;}
