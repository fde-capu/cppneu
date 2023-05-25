#include "header.hpp"

void run()
{
	while (true) {

		clear();
		for (auto& neuron : Neuron::neuronVector) {
			neuron.process();
			printAsciiBar<MEMORY_TYPE_SIZE>(&neuron);
		}
		printOutTable<MEMORY_TYPE_SIZE>();
		refresh();

		std::this_thread::sleep_for(std::chrono::milliseconds(STEP_MS));
	}
}

void prepare()
{
	srand(time(NULL));
	initscr();
}

int main() {
	prepare();

  Neuron("haha");
	Neuron("HAHA");
	Neuron("KIKI");

	run();
	return 0;
}
