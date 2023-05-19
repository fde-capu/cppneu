#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <climits>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>
#include <atomic>
#include <cstdio>

#define MEMORY_TYPE_SIZE unsigned int
#define ASCII_BAR_LENGTH 16
#define STEP_MS 100
#define RANDOM_VARIATION 0.4
#define THRESHOLD_PULL 0.3

static int globalUID = 0;

template <typename T = MEMORY_TYPE_SIZE>
T randomValue() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<typename std::make_unsigned<T>::type> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
	return static_cast<T>(dist(gen));
}

template <typename T = MEMORY_TYPE_SIZE>
T variateValue(T value, float band = 1.0) {
	T newValue = randomValue<T>();
	value = ((float)newValue - (float)value) * band + (float)value;
	return value;
}

template <typename T = MEMORY_TYPE_SIZE>
class Neuron {
	private:
		T threshold;
		T originalThreshold;
		T* inputAddress;
		T* outputAddress;
		float thresholdDecreaseFactor;
		int UID;

	public:
		Neuron(T* inputMemory, T* outputMemory)
			:	threshold(randomValue<T>()),
				originalThreshold(threshold),
				inputAddress(inputMemory),
				outputAddress(outputMemory),
				UID(globalUID++) {}

		int getUID() const {
			return UID;
		}

		T getInputValue() const {
			return *inputAddress;
		}

		T getThreshold() const {
			return threshold;
		}

		T getOriginalThreshold() const {
			return originalThreshold;
		}

		float getThresholdDecFactor() const {
			return thresholdDecreaseFactor;
		}

		void readAxons() {
			*inputAddress = variateValue<T>(*inputAddress, RANDOM_VARIATION);
		}

		void updateInternals() {
			T diff = threshold - originalThreshold;
			threshold -= diff * thresholdDecreaseFactor;
			thresholdDecreaseFactor *= 1.0 + THRESHOLD_PULL;
			if (threshold < originalThreshold)
				threshold = originalThreshold;
		}

		void process() {
			readAxons();
			updateInternals();
			if (*inputAddress >= threshold) {
				*outputAddress = 1;
				thresholdDecreaseFactor = static_cast<float>(*inputAddress - threshold) / static_cast<float>(std::numeric_limits<T>::max());
				threshold = *inputAddress;
			} else {
				*outputAddress = 0;
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

	std::cout << neuron->getUID() << "  [";
	for (int i = 0; i < length; i++) {
		if (i == scaledOriginalThreshold && i == scaledThreshold) {
			std::cout << '!';
		} else if (i == scaledOriginalThreshold) {
			std::cout << '|';
		} else if (i == scaledThreshold) {
			std::cout << '+';
		} else if (i < scaledInputValue) {
			std::cout << '-';
		} else {
			std::cout << ' ';
		}
	}
	std::cout << "]";

	if (neuron->getInputValue() >= neuron->getThreshold())
		std::cout << " *";
	else
		std::cout << "  ";

	//		std::cout << "\t" << static_cast<T>(neuron->getInputValue()) << "\t" << static_cast<T>(neuron->getThreshold()) << "\t" << static_cast<T>(neuron->getOriginalThreshold()) << "\t" << neuron->getThresholdDecFactor();
	std::cout << std::endl;
}

std::atomic<bool> running(true);

void neuronThread(Neuron<MEMORY_TYPE_SIZE>* neuron, MEMORY_TYPE_SIZE* inputMemory, MEMORY_TYPE_SIZE* outputMemory) {
	while (running) {

		(void)outputMemory;
		(void)inputMemory;

		neuron->process();

		std::this_thread::sleep_for(std::chrono::milliseconds(STEP_MS));
	}
}

void userInputThread() {
	char c;
	while (running) {
		c = getchar();
		if (c == 'q' || c == 'Q') {
			running = false;
		}
	}
}

int main() {
	srand(time(NULL));

	MEMORY_TYPE_SIZE inputMemory;
	MEMORY_TYPE_SIZE outputMemory = 0;

	Neuron<MEMORY_TYPE_SIZE> neuron(&inputMemory, &outputMemory);

	std::thread neuron_thread(neuronThread, &neuron, &inputMemory, &outputMemory);
	std::thread user_input_thread(userInputThread);

	neuron_thread.join();
	user_input_thread.join();

	return 0;
}
