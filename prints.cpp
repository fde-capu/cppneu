#include "prints.hpp"

void printScreen(Being& b)
{
	b.printHeader();
	b.printAllCharacters();
	b.printAllDescriptions();
	b.printAllBars();
	b.printOuts();
	b.printAllAxons();
	b.printWantedActions();
}
