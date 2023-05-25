#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <climits>
#include <thread>
#include <chrono>
#include <ncurses.h>

#define MEMORY_TYPE_SIZE unsigned int
#define ASCII_BAR_LENGTH 32
#define STEP_MS 100
#define RANDOM_VARIATION 0.2
#define THRESHOLD_STABILITY 0.999

static int globalUID = 0;

template <typename T = MEMORY_TYPE_SIZE>
T randomValue() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<typename std::make_unsigned<T>::type> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
	return static_cast<T>(dist(gen));
}

template <typename T = MEMORY_TYPE_SIZE>
T variateValue(T& value, float band = 1.0) {
	T newValue = randomValue<T>();
	value = ((float)newValue - (float)value) * band + (float)value;
	return value;
}

template <typename T = MEMORY_TYPE_SIZE>
class Neuron {
	private:
		T threshold;
		T originalThreshold;
		T inputValue;
		T outputValue;
		float thresholdPull;
		int UID;
		std::string name;

	public:
		Neuron(std::string name)
			:	threshold(randomValue<T>()),
				originalThreshold(threshold),
				inputValue(0),
				outputValue(0),
				thresholdPull(1.0),
				UID(globalUID++),
				name(name)
				{}

		std::string getName() const {
			return name;
		}

		int getUID() const {
			return UID;
		}

		T getOutputValue() const {
			return outputValue;
		}

		T getInputValue() const {
			return inputValue;
		}

		T getThreshold() const {
			return threshold;
		}

		T getOriginalThreshold() const {
			return originalThreshold;
		}

		float getThresholdDecFactor() const {
			return thresholdPull;
		}

		void readAxons() {
			variateValue<T>(inputValue, RANDOM_VARIATION);
		}

		void updateInternals() {
			if (threshold >= originalThreshold) {
				thresholdPull *= THRESHOLD_STABILITY;
			} else if (threshold < originalThreshold) {
				thresholdPull *= 1 + (1 - THRESHOLD_STABILITY);
			}
			if (thresholdPull > 1.0 && static_cast<T>(threshold * thresholdPull) < threshold)
			{
				threshold = std::numeric_limits<T>::max();
				thresholdPull = 1.0;
			}
			else
				threshold *= thresholdPull;
		}

		void process() {
			readAxons();
			updateInternals();
			if (inputValue >= threshold) {
				float force = static_cast<float>(inputValue - threshold) / static_cast<float>(std::numeric_limits<T>::max());
				outputValue = std::numeric_limits<T>::max();
				threshold += (inputValue - threshold) * force;
				thresholdPull = 1 - (force * 0.1);
			} else {
				outputValue = 0;
			}

			printAsciiBar(this);
		}
};

template <typename T>
void printAsciiBar(Neuron<T>* neuron) {
	int length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length) / std::numeric_limits<T>::max();
	int scaledInputValue = static_cast<int>(neuron->getInputValue() * scaleFactor);
	int scaledThreshold = static_cast<int>(neuron->getThreshold() * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(neuron->getOriginalThreshold() * scaleFactor);

	printw("%u %s [", neuron->getUID(), neuron->getName().c_str());
	for (int i = 0; i < length; i++) {
		if (i == scaledOriginalThreshold && i == scaledThreshold) {
			printw("!");
		} else if (i == scaledOriginalThreshold) {
			printw("|");
		} else if (i == scaledThreshold) {
			printw("+");
		} else if (i < scaledInputValue) {
			printw(".");
		} else {
			printw(" ");
		}
	}
	printw("]");

	if (neuron->getOutputValue())
		printw(" * %u",  neuron->getOutputValue());
	else
		printw("  ");
	printw("\n");
}

std::vector<Neuron<MEMORY_TYPE_SIZE> > neuronVector;

void runProcess()
{
	while (true) {

		clear();
		for (auto& neuron : neuronVector) {
			neuron.process();
		}
		refresh();

		std::this_thread::sleep_for(std::chrono::milliseconds(STEP_MS));
	}
}


void makeNeuron(std::string name)
{
	Neuron<MEMORY_TYPE_SIZE> neuron(name);
	neuronVector.push_back(neuron);
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
