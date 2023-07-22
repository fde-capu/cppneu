#include "prints.hpp"
#include "helpers.hpp"
#include "header.hpp"

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

bool canDisplay(const NEURON& n)
{
	if (n.isBias() && !(displaySet & DISPLAY_BIAS))
		return false;
	if (n.type == T_QUIET && !(displaySet & DISPLAY_QUIETS))
		return false;
	return true;
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
		if (canDisplay(pair.second))
			printCharacter(pair.second);
	printw("\n");
}

void printWantedActions(Being& b)
{
	if (!(displaySet & DISPLAY_WANT)) return ;
	for (auto& n : b.bestAction)
	{
		if (n != ST_MAX)
			printw("%s\n", b.neuron_table[n].getDescription().c_str());
		else
			printw("-\n");
	}
}

void printAllAxons(Being& b)
{
	static std::string c_set(AXON_DISPLAY_SET);
	char fire_char_a;
	char fire_char_b;

	if (!(displaySet & DISPLAY_AXONS))
		return ;

	for (auto& pair : b.axon_table)
	{
		const NEURON& nIn = b.neuron_table[pair.second.slotIn];
		const NEURON& nOut = b.neuron_table[pair.second.slotOut];

		fire_char_a = nIn.fire ?
			c_set.at(2) : c_set.at(0);
		fire_char_b = nIn.fire ?
			c_set.at(3) : c_set.at(1);
		if (nIn.fire)
			BOLD
		if (nIn.name != "")
			printw("%s", nIn.name.c_str());
		else
			printw("%zu", pair.second.slotIn);
		printw("%c%s%c",
			fire_char_a,
			floatUpFire(pair.second.multiplier).c_str(),
			fire_char_b);
		if (nOut.name != "")
			printw("%s", nOut.name.c_str());
		else
			printw("%zu", pair.second.slotOut);
		printw(" ");
		if (nIn.fire)
			UNBOLD
	}
	printw("\n");
}

void printOuts(Being& b)
{
	if (!(displaySet & DISPLAY_OUTS))
		return ;
	printw("|");
	for (auto& pair : b.neuron_table)
	{
		if (!canDisplay(pair.second))
			continue ;
		if (pair.second.fire)
		{
			if (pair.second.isNeuron())
			{
				if (pair.second.isPoked())
					printw("_");
				else
					printw("*");
			}
			else if (pair.second.isBias())
				printw(".");
		}
		else
			printw(" ");
	}
	printw("|\n");
}

void printCharacter(NEURON& n)
{
	static std::string shadowGray(ASCII_CHAR_SCALE);
	if (n.fire) BOLD
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
	if (n.fire) UNBOLD
}

void printAllBars(Being& b)
{
	if (!displaySet || !(displaySet & DISPLAY_BAR_ALL)) return;

	for (auto& n : b.neuron_table)
		if (canDisplay(n.second))
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

	if (displaySet & DISPLAY_PHYSICAL)
		printw("%s", physical.c_str());
	if (displaySet & DISPLAY_VITAL)
		printw("%s", vital.c_str());
	if (displaySet & DISPLAY_ACTION)
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
	static std::string barMap(ASCII_BAR_SET);

	size_t length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length);
	size_t scaledInputValue = static_cast<int>(n.inputValue * scaleFactor);
	size_t scaledThreshold =
		static_cast<int>(n.threshold * scaleFactor - EPSILON);
	size_t scaledOriginalThreshold =
		static_cast<int>(n.originalThreshold * scaleFactor - EPSILON);

	if (displaySet & DISPLAY_BAR)
	{
		printw("%zu %c", n.neuron_UID, barMap.at(n.isBias() ? 8 : 0));
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
		printw("%c", barMap.at(n.isBias() ? 9 : 7));
	}
	if (n.fire) BOLD;
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
	if (n.fire) UNBOLD;
	printw("\n");
}

void printNumbers(NEURON& n)
{
	static bool originalInfo = false;
	if (originalInfo)
	{
		printw(">%s :%s d%s o%s",
				floatUpFire(n.inputValue).c_str(),
				floatUpFire(n.threshold).c_str(),
				floatUpFire(n.damp).c_str(),
				floatUpFire(n.originalThreshold).c_str()
			);
	}
	else
	{
		printw("%c%s:%s",
				n.isBias() ? '~' : '>',
				floatUpFire(n.inputValue).c_str(),
				floatUpFire(n.threshold).c_str()
			);
	}
}

void setDisplay(long bit_value)
{
	toggleBit(displaySet, bit_value);
}
