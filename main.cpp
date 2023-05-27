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
			Neuron::processAll();

			clear();
			Neuron::printScreen();
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

	Neuron::Physical("Nose", {"Short", "Medium", "Long"});

  Neuron::Measure("Eyes", {"Closed", "Normal", "Wide Open"}, EXPRESSOR_THRESHOLD);

  Neuron::Measure("Humor",
		{"Crappy", "Bad", "Medium", "Ok", "Good", "Enthusiastic", "Incredible"},
		EXPRESSOR_THRESHOLD);

	Neuron::Vital("Breath", {"Empty", "Neutral", "Full"},
		0, 0, "", 0.0, EXPRESSOR_THRESHOLD);

  Neuron::Vital("Heart 2",
		{"Frozen", "Slow", "Normal", "Peaced", "Accelerated", "Fast", "Hyper"},
		0, 260, "bpm", 0.4);

  Neuron::Vital("Heart",
		{"Frozen", "Slow", "Normal", "Peaced", "Accelerated", "Fast", "Hyper"},
		0, 260, "bpm", 0.4);

  Neuron::Measure("Tired", {}, EXPRESSOR_CURRENT);

	Neuron::Action("Drop");
	Neuron::Action("Clench", {"Softly", "Moderate", "Hard"});
	Neuron::Action("Sleep");

	Neuron::Axon(20);
	Neuron::Bias(3);
}


int main() {
	prepare();
	makeBrain();
	run();
	destroy();
	return 0;
}
