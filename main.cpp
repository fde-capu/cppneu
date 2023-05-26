#include "header.hpp"

void run()
{
	while (true) {

		clear();

		Neuron::processAll();

		Neuron::printAllCharacters();
		Neuron::printAllBars();
//		Neuron::printOuts();
//		Neuron::printAllAxons();
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

std::vector<int> intVector(int min, int max)
{
	std::vector<int> myVector(max - min); //initialize a vector with 256 elements
	for (int i = 0; i <= max - min - 1; i++)
		myVector[i] = i + min; //fill the elements with values ranging from 25 to 280 (inclusive)
	return myVector;
}

int main() {
	prepare();

  Neuron::Measure("Humor", {"Bad", "Medium", "Ok", "Good", "Incredible"});
	Neuron::Oscil("Breath", {"Empty", "Neutral", "Full"});

  Neuron::Measure("Heart", {"Stoped", "Icy", "Slow", "Peaced", "Fast", "Hyper"}, 0, 220, "bpm");
  Neuron(T_MEASURE, "Tired");

	Neuron(T_ACTION, "Drop");
	Neuron(T_ACTION, "Clench");
	Neuron(T_ACTION, "Sleep");

	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);
	Neuron(T_AXON);

//	Axon();

	run();
	return 0;
}
