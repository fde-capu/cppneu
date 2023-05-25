#include "header.hpp"

void runProcess()
{
	while (true) {

		clear();
		for (auto& neuron : neuronVector<MEMORY_TYPE_SIZE>) {
			neuron.process();
		}
		refresh();

		std::this_thread::sleep_for(std::chrono::milliseconds(STEP_MS));
	}
}


void makeNeuron(std::string name)
{
	Neuron<MEMORY_TYPE_SIZE> neuron(name);
	neuronVector<MEMORY_TYPE_SIZE>.push_back(neuron);
}

int main() {
	srand(time(NULL));
	initscr();
	cbreak();
	noecho();
 
  makeNeuron("haha");
	makeNeuron("HAHA");
	makeNeuron("KIKI");

	runProcess();
	return 0;
}
