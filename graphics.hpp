#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP
# include "header.hpp"

template <typename T>
void printAsciiBar(Neuron* neuron) {
	int length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length) / std::numeric_limits<T>::max();
	int scaledInputValue = static_cast<int>(neuron->getInputValue() * scaleFactor);
	int scaledThreshold = static_cast<int>(neuron->getThreshold() * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(neuron->getOriginalThreshold() * scaleFactor);

	printw("%u [", neuron->getUID());
	for (int i = 0; i < length; i++) {
		if (i == scaledOriginalThreshold && i == scaledThreshold) {
			printw("!");
		} else if (i == scaledOriginalThreshold) {
			printw("|");
		} else if (i == scaledThreshold) {
			printw("+");
		} else if (i < scaledInputValue) {
			printw(".");
		} else {
			printw(" ");
		}
	}
	printw("]");

	if (neuron->getOutputValue())
		printw(" * ");
	else
		printw("   ");
	printw("%s", neuron->getName().c_str());
	printw("\n");
}

template <typename T>
void printOutTable()
{
		printw("\n Outputs:\t|");
		for (auto& value : Neuron::neuronOut)
		{
			if (!std::isinf(value))
				printw("*|", value);
			else
				printw(" |");
		}
		printw("\n");
		printw("\n");
}


#endif
