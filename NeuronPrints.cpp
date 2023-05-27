#include "Neuron.hpp"

void Neuron::printScreen()
{
	Neuron::printHeader();
	Neuron::printAllCharacters();
	Neuron::printAllDescriptions();
	Neuron::printWantedActions();
	 Neuron::printAllBars();
	//		Neuron::printOuts();
	//Neuron::printAllAxons();
}

void Neuron::printHeader()
{
	printw("%dN %dA %dB ", count_neuron, count_axon, count_bias);
}

void Neuron::printAllCharacters()
{
	for (auto& neuron : table)
			neuron.printCharacter();
	printw("\n");
}

void Neuron::printWantedActions()
{
	printw("[ %s ]", bestAction.c_str());
	for (auto& action : actions)
		printw(" %s", action.c_str());
	printw("\n");
}

void Neuron::printAllBars()
{
		for (auto& neuron : table)
				neuron.printAsciiBar();
}

void Neuron::printAllAxons()
{
		printw("|");
		for (auto& neuron : table)
		{
			if (neuron.isAxon())
			{
				printw("%d-%d>%d|",
					neuron.slotIn, static_cast<int>(neuron.multiplyer * 10),
					neuron.slotOut); 
			}
		}
		printw("\n");
}

void Neuron::printOuts()
{
		for (auto& neuron : table)
		{
			if (neuron.isOutBlockVisible())
			{
				if (!std::isinf(out[neuron.UID]))
					printw("*|", out[neuron.UID]);
				else
					printw(" |");
			}
		}
		printw("\n");
}

void Neuron::printCharacter()
{
	if (!isCharacterVisible())
		return;

	std::string shadowGray(" -~=+*oO&#%@");
	double scaleFactor = static_cast<double>(shadowGray.length() - 1) / max();
	int scaledInputValue = static_cast<int>(inputValue * scaleFactor);
	int scaledThreshold = static_cast<int>(threshold * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(originalThreshold * scaleFactor);

	if (outputValue)
		printw("!");
	else
		printw(" ");
	printw("%c", shadowGray.at(scaledInputValue));
	printw("%c", shadowGray.at(scaledThreshold));
	printw("%c", shadowGray.at(scaledOriginalThreshold));
}

void Neuron::printAsciiBar()
{
	if (!isBarVisible())
		return ;
	size_t length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length) / max();
	size_t scaledInputValue = static_cast<int>(inputValue * scaleFactor);
	size_t scaledThreshold = static_cast<int>(threshold * scaleFactor);
	size_t scaledOriginalThreshold = static_cast<int>(originalThreshold * scaleFactor);

	printw("%u [", UID);
	for (size_t i = 0; i < length; i++) {
		if (i == scaledOriginalThreshold && i == scaledThreshold) {
			printw("!");
		} else if (i == scaledOriginalThreshold) {
			printw("+");
		} else if (i == scaledThreshold) {
			printw("|");
		} else if (i < scaledInputValue) {
			printw(".");
		} else {
			printw(" ");
		}
	}
	printw("]");
	printDescription();
}

void Neuron::printAllDescriptions()
{
	std::string physical("");
	std::string vital("");
	std::string action("");
	std::string measure("");
	std::string tmp;

	for (auto& neuron : table)
	{
		tmp = neuron.printDescription(true);
		switch (neuron.type)
		{
			case T_PHYSICAL: physical += tmp; break;
			case T_VITAL: vital += tmp; break;
			case T_ACTION: action += tmp; break;
			case T_MEASURE: measure += tmp; break;
		}
	}

	if (physical.length()) physical = "physical:\t" + physical;
	if (vital.length()) vital = "vital:\t" + vital;
	if (action.length()) action = "action:\t" + action;
	if (measure.length()) measure = "measure:\t" + measure;

//	if (physical.length()) physical += "\n";
//	if (vital.length()) vital += "\n";
//	if (action.length()) action += "\n";
//	if (measure.length()) measure += "\n";
	
	printw(physical.c_str());
	printw(vital.c_str());
	printw(action.c_str());
	printw(measure.c_str());
}

std::string Neuron::printDescription(bool silent)
{
	double scaleFactor;
	size_t scaledExpressor;
	MEMORY_TYPE_SIZE getExpressor;
	std::stringstream ss;

	getExpressor = expressor == EXPRESSOR_CURRENT ? inputValue :
								expressor == EXPRESSOR_THRESHOLD ? threshold :
								originalThreshold;
	if (outputValue)
		ss << " * ";
	else
		ss << "   ";
	ss << name;
	if (isNeuron())
	{
		if (scaleMax)
		{
			scaleFactor = static_cast<double>(scaleMax - scaleMin) / max();
			scaledExpressor = static_cast<int>(getExpressor * scaleFactor) + scaleMin;
			ss << ": " << scaledExpressor << unit.c_str();
		}
		if (scale.size())
		{
			scaleFactor = static_cast<double>(scale.size()) / max();
			scaledExpressor = static_cast<int>(getExpressor * scaleFactor);
			if (scaledExpressor > scale.size() - 1) scaledExpressor = scale.size() - 1;
			ss << ": " << scale[scaledExpressor];
		}
		if (!scale.size() && !scaleMax && isStatsVisible())
		{
			scaleFactor = static_cast<double>(1.0) / max();
			scaleFactor = static_cast<double>(getExpressor * scaleFactor);
			ss << ": " << scaleFactor;
		}
		ss << "\t> " << thresholdDecay;
		ss << std::endl;
	}
	std::string outStr = (ss.str());
	if (!silent)
		printw(outStr.c_str());
	return outStr;
}
