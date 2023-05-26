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

int main() {
	prepare();

  Neuron::Measure("Humor",
		{"Crappy", "Bad", "Medium", "Ok", "Good", "Enthusiastic", "Incredible"});

	Neuron::Oscil("Breath", {"Empty", "Neutral", "Full"});

  Neuron::Measure("Heart",
		{"Slow", "Normal", "Peaced", "Accelerated", "Fast", "Hyper"},
		0, 260, "bpm");

  Neuron::Measure("Tired");
  Neuron::Measure("Eyes", {"Closed", "Normal", "Wide Open"});

	Neuron::Action("Drop");
	Neuron::Action("Clench", {"Softly", "Moderate", "Hard"});
	Neuron::Action("Sleep");
	Neuron::Bias(4);
	Neuron::Axon(50);

	run();
	return 0;
}
