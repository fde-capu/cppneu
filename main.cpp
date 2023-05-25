#include "header.hpp"

void run()
{
	while (true) {

		clear();

		Neuron::processAll();

		Neuron::printAllCharacters();
		Neuron::printAllBars();
		Neuron::printOuts();
		Neuron::printAllAxons();
//		Axon::printAll();

		refresh();

		std::this_thread::sleep_for(std::chrono::milliseconds(STEP_MS));
	}
}

void prepare()
{
	srand(time(NULL));
	initscr();
	set_tabsize(12);
}

int main() {
	prepare();

  Neuron(T_MEASURE, "Breath");
  Neuron(T_MEASURE, "Heart");

	Neuron(T_ACTION, "Drop");

	Neuron(T_AXON);
	Neuron(T_AXON);

//	Axon();

	run();
	return 0;
}
