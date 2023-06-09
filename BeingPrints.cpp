#include "Being.hpp"
#include "helpers.hpp"

int Being::displayBars = \
	DISPLAY_BAR + \
	DISPLAY_DESCRIPTION + \
	DISPLAY_AXONS + \
	DISPLAY_BIAS + \
	DISPLAY_HEADER + \
	DISPLAY_CHARS + \
	DISPLAY_WANT + \
	DISPLAY_BAR_ALL \
;

void Being::printHeader()
{
	if (!(displayBars & DISPLAY_HEADER)) return ;
	printw("%dN %dA %dB\n", count_being, count_axon, count_bias);
}

void Being::printAllCharacters()
{
	if (!(displayBars & DISPLAY_CHARS)) return ;
	for (auto& being : table)
			being.printCharacter();
	printw("\n");
}

void Being::printWantedActions()
{
	if (!(displayBars & DISPLAY_WANT)) return ;
	printw("%s", bestAction.c_str());
	printw("\n");
}

void Being::printAllAxons()
{
	if (!(displayBars & DISPLAY_AXONS)) return ;
		for (auto& being : table)
		{
			if (being.isAxon())
			{
				printw("%d-%d>%d ",
					being.slotIn, floatUp(being.threshold), being.slotOut); 
			}
		}
		printw("\n");
}

void Being::printOuts()
{
	if (!(displayBars & DISPLAY_OUTS)) return;
		printw("|");
		for (auto& being : table)
		{
			if (being.isOutBlockVisible())
			{
				if (being.outputValue)
					printw("*|");
				else
					printw(" |");
			}
		}
		printw("\n");
}

void Being::printCharacter()
{
	if (!isCharacterVisible())
		return;
	std::string shadowGray(" -~=+*oO&#%@");
	double scaleFactor = static_cast<double>(shadowGray.length() - 1);
	int scaledInputValue = static_cast<int>(inputValue * scaleFactor);
	int scaledThreshold = static_cast<int>(threshold * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(Neuron::originalThreshold * scaleFactor);

	if (outputValue)
		printw("!");
	else
		printw(" ");
	printw("%c", shadowGray.at(scaledInputValue));
	printw("%c", shadowGray.at(scaledThreshold));
	printw("%c", shadowGray.at(scaledOriginalThreshold));
}

void Being::printAllBars()
{
	if (!displayBars || !(displayBars & DISPLAY_BAR_ALL)) return;
	for (auto& being : table)
		being.printAsciiBar();
}

void Being::setDisplay(int bit_value)
{
	toggleBit(displayBars, bit_value);
}

void Being::printAsciiBar()
{
	static std::string barMap("[ ,.;:!]");

	if (!isBarVisible()
		|| (isBias() && !(displayBars & DISPLAY_BIAS)))
		return ;
	size_t length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length);
	size_t scaledInputValue = static_cast<int>(inputValue * scaleFactor);
	size_t scaledThreshold = static_cast<int>(threshold * scaleFactor);
	size_t scaledOriginalThreshold = static_cast<int>(originalThreshold * scaleFactor);

	if (displayBars & DISPLAY_BAR)
	{
		printw("%u %c", neuron_UID, barMap.at(0));
		for (size_t i = 0; i < length; i++) {
			if (i == scaledOriginalThreshold && i == scaledThreshold) {
				if (outputValue)
					printw("%c", barMap.at(6));
				else
					printw("%c", barMap.at(4));
			} else if (i == scaledOriginalThreshold) {
				if (threshold == originalThreshold && outputValue)
					printw("%c", barMap.at(6));
				else
					printw("%c", barMap.at(2));
			} else if (i == scaledThreshold) {
				if (outputValue)
					printw("%c", barMap.at(6));
				else
					printw("%c", barMap.at(5));
			} else if (i < scaledInputValue) {
					printw("%c", barMap.at(3));
			} else {
				printw("%c", barMap.at(1));
			}
		}
		printw("%c ", barMap.at(7));
	}
	if (displayBars & DISPLAY_CHARACTER)
	{
		printw(" ");
		printCharacter();
	}
	if (displayBars & DISPLAY_NUMBERS)
	{
		printw(" ");
		printNumbers();
	}
	if (displayBars & DISPLAY_DESCRIPTION)
	{
		printw(" ");
		printDescription();
	}
	printw("\n");
}

void Being::printNumbers()
{
	zo scaleFactor = 1.0;
	zo scaledInputValue = static_cast<zo>(inputValue * scaleFactor);
	zo scaledThreshold = static_cast<zo>(threshold * scaleFactor);
	zo scaledOriginalThreshold = static_cast<zo>(Neuron::originalThreshold * scaleFactor);
	printw("%s %s %s",
		zeroOut(scaledInputValue).c_str(),
		zeroOut(scaledThreshold).c_str(),
		zeroOut(scaledOriginalThreshold).c_str());
}

void Being::printAllDescriptions()
{
	std::string physical("");
	std::string vital("");
	std::string action("");
	std::string measure("");
	std::string tmp;

	for (auto& being : table)
	{
		tmp = being.getDescription() + "\n";
		switch (being.type)
		{
			case T_PHYSICAL: physical += tmp; break;
			case T_VITAL: vital += tmp; break;
			case T_ACTION: action += tmp; break;
			case T_MEASURE: measure += tmp; break;
		}
	}

//	if (physical.length()) physical = "physical:\t" + physical;
//	if (vital.length()) vital = "vital:\t" + vital;
//	if (action.length()) action = "action:\t" + action;
//	if (measure.length()) measure = "measure:\t" + measure;

//	if (physical.length()) physical += "\n";
//	if (vital.length()) vital += "\n";
//	if (action.length()) action += "\n";
//	if (measure.length()) measure += "\n";
	
	if (displayBars & DISPLAY_PHYSICAL)
		printw(physical.c_str());
	if (displayBars & DISPLAY_VITAL)
		printw(vital.c_str());
	if (displayBars & DISPLAY_AXONS)
		printw(action.c_str());
	if (displayBars & DISPLAY_MEASURES)
		printw(measure.c_str());
}

void Being::printDescription()
{
	printw(getDescription().c_str());
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
