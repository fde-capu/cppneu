#include "header.hpp"

void run()
{
	while (true) {

		clear();

		Neuron::processAll();
		Axon::processAll();

		Neuron::printAllCharacters();
		Neuron::printAllBars();
		Neuron::printOuts();
		Axon::printAll();

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

  Neuron("Hungry");
	Neuron("Eat");
	Neuron("Satisfied");
	Neuron("Thristy");
	Neuron("Drink");
	Neuron("Do nothing");

	Axon();
	Axon();
	Axon();
	Axon();
	Axon();
	Axon();
	Axon();
	Axon();
	Axon();
	Axon();

	run();
	return 0;
}
