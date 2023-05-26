#include "header.hpp"

static bool g_running = false;

void makeBrain();

void dealKeyPress(int ch)
{
	printw("Key pressed: %d\n", ch);
	if (ch == 'p')
		g_running = !g_running;
	if (ch == ' ')
		makeBrain();
}

void run()
{
	g_running = true;
	while (true)
	{
		if (g_running)
		{
			clear();
			Neuron::processAll();

			Neuron::printAllCharacters();
			Neuron::printAllBars();
			//		Neuron::printOuts();
			Neuron::printAllAxons();
			refresh();
		}

		int ch = getch();
		if (ch != ERR) {
			dealKeyPress(ch);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(STEP_MS));
	}
}

void prepare()
{
	srand(time(NULL));
	initscr();
	set_tabsize(12);
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
}

void destroy()
{
	endwin();
}

void makeBrain()
{
	Neuron::reset();

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

	Neuron::Bias(3);
	Neuron::Axon(10);
}


int main() {
	prepare();
	makeBrain();
	run();
	destroy();
	return 0;
}
