#include "prints.hpp"

static int displaySet = DISPLAY_SET_DEFAULT;

void printScreen(Being& b)
{
	printHeader(b);
	printAllCharacters(b);
	printAllDescriptions(b);
	printAllBars(b);
	printOuts(b);
	printAllAxons(b);
	printWantedActions(b);
}

void printHeader(Being& b)
{
	if (!(displaySet & DISPLAY_HEADER)) return ;
	printw("%zuN %zuA %zuB\n", b.count_neuron, b.count_axon, b.count_bias);
}

void printAllCharacters(Being& b)
{
	if (!(displaySet & DISPLAY_CHARS)) return ;
	for (auto& pair : b.neuron_table)
			printCharacter(pair.second);
	printw("\n");
}

void printWantedActions(Being& b)
{
	if (!(displaySet & DISPLAY_WANT)) return ;
	printw("%s", b.bestAction.c_str());
	printw("\n");
}

void printAllAxons(Being& b)
{
	char fire_char;
	if (!(displaySet & DISPLAY_AXONS)) return ;
		for (auto& pair : b.axon_table)
		{
			fire_char = b.neuron_table[pair.second.slotIn].firing() ? '*' : '-';
			printw("%zu%c%s>%zu ",
				pair.second.slotIn,
				fire_char,
				floatUp(pair.second.multiplier).c_str(),
				pair.second.slotOut); 
		}
		printw("\n");
}

void printOuts(Being& b)
{
	if (!(displaySet & DISPLAY_OUTS)) return;
		printw("|");
		for (auto& pair : b.neuron_table)
		{
			if (isOutBlockVisible(pair.second))
			{
				if (pair.second.outputValue)
					printw("*|");
				else
					printw(" |");
			}
		}
		printw("\n");
}

void printCharacter(NEURON& n)
{
	if (!isCharacterVisible(n))
		return;
	std::string shadowGray(" -~=+*oO&#%@");
	double scaleFactor = static_cast<double>(shadowGray.length() - 1);
	int scaledInputValue = static_cast<int>(n.inputValue * scaleFactor);
	int scaledThreshold = static_cast<int>(n.threshold * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(n.originalThreshold * scaleFactor);

	if (n.outputValue)
		printw("!");
	else
		printw(" ");
	printw("%c", shadowGray.at(scaledInputValue));
	printw("%c", shadowGray.at(scaledThreshold));
	printw("%c", shadowGray.at(scaledOriginalThreshold));
}

void printAllBars(Being& b)
{
	if (!displaySet || !(displaySet & DISPLAY_BAR_ALL)) return;
	for (auto& n : b.neuron_table)
		printAsciiBar(n.second);
}

void printAllDescriptions(Being& b)
{
	std::string physical("");
	std::string vital("");
	std::string action("");
	std::string measure("");
	std::string tmp;

	for (auto& n : b.neuron_table)
	{
		tmp = n.second.getDescription() + "\n";
		switch (n.second.type)
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
	
	if (displaySet & DISPLAY_PHYSICAL)
		printw("%s", physical.c_str());
	if (displaySet & DISPLAY_VITAL)
		printw("%s", vital.c_str());
	if (displaySet & DISPLAY_AXONS)
		printw("%s", action.c_str());
	if (displaySet & DISPLAY_MEASURES)
		printw("%s", measure.c_str());
}

void printDescription(NEURON& n)
{
	printw("%s", n.getDescription().c_str());
}

void printAsciiBar(NEURON& n)
{
	static std::string barMap("[ ,.;:!]");

	if (!isBarVisible(n)
		|| (n.isBias() && !(displaySet & DISPLAY_BIAS)))
		return ;
	size_t length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length);
	size_t scaledInputValue = static_cast<int>(n.inputValue * scaleFactor);
	size_t scaledThreshold = static_cast<int>(n.threshold * scaleFactor);
	size_t scaledOriginalThreshold = static_cast<int>(n.originalThreshold * scaleFactor);

	if (displaySet & DISPLAY_BAR)
	{
		printw("%zu %c", n.neuron_UID, barMap.at(0));
		for (size_t i = 0; i < length; i++) {
			if (i == scaledOriginalThreshold && i == scaledThreshold) {
				if (n.outputValue)
					printw("%c", barMap.at(6));
				else
					printw("%c", barMap.at(4));
			} else if (i == scaledOriginalThreshold) {
				if (n.threshold == n.originalThreshold && n.outputValue)
					printw("%c", barMap.at(6));
				else
					printw("%c", barMap.at(2));
			} else if (i == scaledThreshold) {
				if (n.outputValue)
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
	if (displaySet & DISPLAY_CHARACTER)
	{
		printw(" ");
		printCharacter(n);
	}
	if (displaySet & DISPLAY_NUMBERS)
	{
		printw(" ");
		printNumbers(n);
	}
	if (displaySet & DISPLAY_DESCRIPTION)
	{
		printw(" ");
		printDescription(n);
	}
	printw("\n");
}

void printNumbers(NEURON& n)
{
	printw(">%s :%s d%s o%s",
		floatUp(n.inputValue).c_str(),
		floatUp(n.threshold).c_str(),
		floatUp(n.damp).c_str(),
		floatUp(n.originalThreshold).c_str());
}

bool isStatsVisible(NEURON& n)
{ return
				n.type == T_MEASURE; }

bool isBarVisible(NEURON& n)
{ return
			n.type == T_VITAL
		||	n.type == T_ACTION
		||	n.type == T_MEASURE
		||	n.type == T_BIAS
		||	n.type == T_PHYSICAL
;}

bool isCharacterVisible(NEURON& n)
{	return
			n.type == T_VITAL
		||	n.type == T_MEASURE
		||	n.type == T_BIAS
;}

bool isOutBlockVisible(NEURON& n)
{	return
			n.type == T_PHYSICAL
		||	n.type == T_VITAL
		||	n.type == T_ACTION
		||	n.type == T_MEASURE
		||	n.type == T_BIAS
;}

void setDisplay(int bit_value)
{
	toggleBit(displaySet, bit_value);
}
