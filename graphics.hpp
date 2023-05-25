#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP
# include "header.hpp"

template <typename T>
void printAsciiBar(Neuron<T>* neuron) {
	int length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length) / std::numeric_limits<T>::max();
	int scaledInputValue = static_cast<int>(neuron->getInputValue() * scaleFactor);
	int scaledThreshold = static_cast<int>(neuron->getThreshold() * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(neuron->getOriginalThreshold() * scaleFactor);

	printw("%u %s [", neuron->getUID(), neuron->getName().c_str());
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
		printw(" * %u",  neuron->getOutputValue());
	else
		printw("  ");
	printw("\n");
}

#endif
