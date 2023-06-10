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
	printw("%dN %dA %dB\n", b.count_being, b.count_axon, b.count_bias);
}

void printAllCharacters(Being& b)
{
	if (!(displaySet & DISPLAY_CHARS)) return ;
	for (auto& n : b.table)
			printCharacter(n);
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
	if (!(displaySet & DISPLAY_AXONS)) return ;
		for (auto& n : b.table)
		{
			if (n.isAxon())
			{
				printw("%d-%d>%d ",
					n.slotIn, floatUp(n.threshold), n.slotOut); 
			}
		}
		printw("\n");
}

void printOuts(Being& b)
{
	if (!(displaySet & DISPLAY_OUTS)) return;
		printw("|");
		for (auto& n : b.table)
		{
			if (isOutBlockVisible(b))
			{
				if (n.outputValue)
					printw("*|");
				else
					printw(" |");
			}
		}
		printw("\n");
}

void printCharacter(Being& b)
{
	if (!isCharacterVisible(b))
		return;
	std::string shadowGray(" -~=+*oO&#%@");
	double scaleFactor = static_cast<double>(shadowGray.length() - 1);
	int scaledInputValue = static_cast<int>(b.inputValue * scaleFactor);
	int scaledThreshold = static_cast<int>(b.threshold * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(b.originalThreshold * scaleFactor);

	if (b.outputValue)
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
	for (auto& n : b.table)
		printAsciiBar(n);
}

void printAllDescriptions(Being& b)
{
	std::string physical("");
	std::string vital("");
	std::string action("");
	std::string measure("");
	std::string tmp;

	for (auto& n : b.table)
	{
		tmp = n.getDescription() + "\n";
		switch (n.type)
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
		printw(physical.c_str());
	if (displaySet & DISPLAY_VITAL)
		printw(vital.c_str());
	if (displaySet & DISPLAY_AXONS)
		printw(action.c_str());
	if (displaySet & DISPLAY_MEASURES)
		printw(measure.c_str());
}

void printDescription(Being& n)
{
	printw(n.getDescription().c_str());
}

void printAsciiBar(Being& b)
{
	static std::string barMap("[ ,.;:!]");

	if (!isBarVisible(b)
		|| (b.isBias() && !(displaySet & DISPLAY_BIAS)))
		return ;
	size_t length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length);
	size_t scaledInputValue = static_cast<int>(b.inputValue * scaleFactor);
	size_t scaledThreshold = static_cast<int>(b.threshold * scaleFactor);
	size_t scaledOriginalThreshold = static_cast<int>(b.originalThreshold * scaleFactor);

	if (displaySet & DISPLAY_BAR)
	{
		printw("%u %c", b.neuron_UID, barMap.at(0));
		for (size_t i = 0; i < length; i++) {
			if (i == scaledOriginalThreshold && i == scaledThreshold) {
				if (b.outputValue)
					printw("%c", barMap.at(6));
				else
					printw("%c", barMap.at(4));
			} else if (i == scaledOriginalThreshold) {
				if (b.threshold == b.originalThreshold && b.outputValue)
					printw("%c", barMap.at(6));
				else
					printw("%c", barMap.at(2));
			} else if (i == scaledThreshold) {
				if (b.outputValue)
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
		printCharacter(b);
	}
	if (displaySet & DISPLAY_NUMBERS)
	{
		printw(" ");
		printNumbers(b);
	}
	if (displaySet & DISPLAY_DESCRIPTION)
	{
		printw(" ");
		printDescription(b);
	}
	printw("\n");
}

void printNumbers(Being& b)
{
	zo scaleFactor = 1.0;
	zo scaledInputValue = static_cast<zo>(b.inputValue * scaleFactor);
	zo scaledThreshold = static_cast<zo>(b.threshold * scaleFactor);
	zo scaledOriginalThreshold = static_cast<zo>(b.originalThreshold * scaleFactor);
	printw("%s %s %s",
		zeroOut(scaledInputValue).c_str(),
		zeroOut(scaledThreshold).c_str(),
		zeroOut(scaledOriginalThreshold).c_str());
}

bool isStatsVisible(Being& b)
{ return
				b.type == T_MEASURE; }

bool isBarVisible(Being& b)
{ return
				b.type == T_VITAL
		||	b.type == T_ACTION
		||	b.type == T_MEASURE
		||	b.type == T_BIAS
		||	b.type == T_PHYSICAL
;}

bool isCharacterVisible(Being& b)
{	return
				b.type == T_VITAL
		||	b.type == T_MEASURE
		||	b.type == T_BIAS
;}

bool isOutBlockVisible(Being& b)
{	return
				b.type == T_PHYSICAL
		||	b.type == T_VITAL
		||	b.type == T_ACTION
		||	b.type == T_MEASURE
		||	b.type == T_BIAS
;}

void setDisplay(int bit_value)
{
	toggleBit(displaySet, bit_value);
}
