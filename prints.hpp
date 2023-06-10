#ifndef PRINTS_HPP
# define PRINTS_HPP

# include "Being.hpp"

void printScreen(Being&);
void printHeader(Being&);

void printAllCharacters(Being& b);
void printAllBars(Being& b);
void printAllAxons(Being& b);
void printOuts(Being& b);
void printAllDescriptions(Being& b);
void printWantedActions(Being& b);

void printDescription(NEURON&);
void printNumbers(NEURON&);
void printCharacter(NEURON&);
void printAsciiBar(NEURON&);

bool isStatsVisible(NEURON&);
bool isBarVisible(NEURON&);
bool isCharacterVisible(NEURON&);
bool isOutBlockVisible(NEURON&);

void setDisplay(int);

#endif
