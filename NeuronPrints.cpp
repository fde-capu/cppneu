#include "Neuron.hpp"

void Neuron::printAllCharacters() {
	for (auto& neuron : table)
	{
		if (neuron.isNeuron())
			neuron.printCharacter();
	}

	printw("\n [ %s ]", bestAction.c_str());
	for (auto& action : actions)
		printw(" %s", action.c_str());
	printw("\n");
}

void Neuron::printAllBars() {
		for (auto& neuron : table)
		{
			if (neuron.isBarVisible())
				neuron.printAsciiBar();
		}
}

void Neuron::printAllAxons() {
		for (auto& neuron : table)
		{
			if (neuron.isAxon())
			{
				printw("%u [ %d -(%f)-> %d ]\n", neuron.UID,
					neuron.slotIn, neuron.multiplyer,
					neuron.slotOut); 
			}
		}
}

void Neuron::printOuts() {
		printw("\nNeuron Outputs:\t|");
		for (auto& neuron : table)
		{
			if (neuron.isNeuron())
			{
				if (!std::isinf(out[neuron.UID]))
					printw("*|", out[neuron.UID]);
				else
					printw(" |");
			}
		}
		printw("\n");
		printw("\n");
}

void Neuron::printCharacter() {
	std::string shadowGray(" -~=+*oO&#%@");
	double scaleFactor = static_cast<double>(shadowGray.length() - 1) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
	int scaledInputValue = static_cast<int>(inputValue * scaleFactor);
	int scaledThreshold = static_cast<int>(threshold * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(originalThreshold * scaleFactor);

	printw("%c", shadowGray.at(scaledInputValue));
	printw("%c", shadowGray.at(scaledThreshold));
	printw("%c", shadowGray.at(scaledOriginalThreshold));
	if (outputValue)
		printw("!");
	else
		printw(" ");
}

void Neuron::printAsciiBar() {
	size_t length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
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

	printw("\n");
}

void Neuron::printDescription()
{
	double scaleFactor;
	size_t scaledInputValue;
	size_t scaledThreshold;
	size_t scaledOriginalThreshold;
	(void)scaledOriginalThreshold;
	(void)scaledThreshold;

	if (outputValue)
		printw(" * ");
	else
		printw("   ");
	printw("%s", name.c_str());
	if (isNeuron())
	{
		if (scaleMax)
		{
			scaleFactor = static_cast<double>(scaleMax - scaleMin) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
			scaledInputValue = static_cast<int>(inputValue * scaleFactor) + scaleMin;
			printw(": %d %s", scaledInputValue, unit.c_str());
		}
		if (scale.size())
		{
			scaleFactor = static_cast<double>(scale.size()) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
			scaledInputValue = static_cast<int>(inputValue * scaleFactor);
			if (scaledInputValue > scale.size() - 1) scaledInputValue = scale.size() - 1;
			printw(": %s", scale[scaledInputValue].c_str());
		}
		if (!scale.size() && !scaleMax && isStatsVisible())
		{
			scaleFactor = static_cast<double>(1.0) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
			scaleFactor = static_cast<double>(inputValue * scaleFactor);
			printw(": %f", scaleFactor);
		}
	}
}
