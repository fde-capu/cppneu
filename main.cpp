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
#define ASCII_BAR_LENGTH 48
#define STEP_MS 100

template <typename T = MEMORY_TYPE_SIZE>
T randomValue() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<typename std::make_unsigned<T>::type> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    return static_cast<T>(dist(gen));
}

template <typename T = MEMORY_TYPE_SIZE>
T variateValue(T value, float band = 1.0) {
	if (!(rand() % 30))
		return std::numeric_limits<T>::max();
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

	public:
		Neuron(T* inputMemory, T* outputMemory)
			:	threshold(randomValue<T>()),
				originalThreshold(threshold), inputAddress(inputMemory), outputAddress(outputMemory) {}

		T getThreshold() const {
			return threshold;
		}

		T getOriginalThreshold() const {
			return originalThreshold;
		}

		float getThresholdDecFactor() const {
			return thresholdDecreaseFactor;
		}

		void readRandomInputValue() {
			*inputAddress = variateValue<T>(*inputAddress, 0.1);
		}

		void updateInternals() {
			T diff = threshold - originalThreshold;
			threshold -= diff * thresholdDecreaseFactor;
			thresholdDecreaseFactor *= 1.01;
//			if (threshold > originalThreshold)
//				threshold -= std::numeric_limits<T>::max() / 100;
				if (threshold < originalThreshold)
					threshold = originalThreshold;
		}

		void process() {
			updateInternals();
			if (*inputAddress >= threshold) {
				*outputAddress = 1;
				thresholdDecreaseFactor = static_cast<float>(*inputAddress - threshold) / static_cast<float>(std::numeric_limits<T>::max());
				threshold = *inputAddress;
			} else {
				*outputAddress = 0;
			}

		}
};

template <typename T>
void printAsciiBar(T inputValue, T threshold, T originalThreshold, float thresholdDecreaseFactor, int length) {
    double scaleFactor = static_cast<double>(length) / std::numeric_limits<T>::max();
    int scaledInputValue = static_cast<int>(inputValue * scaleFactor);
    int scaledThreshold = static_cast<int>(threshold * scaleFactor);
    int scaledOriginalThreshold = static_cast<int>(originalThreshold * scaleFactor);

		std::cout << "[";
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

		if (inputValue >= threshold)
			std::cout << " *";
		else
			std::cout << "  ";

		std::cout << "\t" << static_cast<T>(inputValue) << "\t" << static_cast<T>(threshold) << "\t" << static_cast<T>(originalThreshold) << "\t" << thresholdDecreaseFactor;
}

std::mutex mtx; // Mutex for synchronizing access to inputMemory
std::atomic<bool> running(true);

void neuronThread(Neuron<MEMORY_TYPE_SIZE>* neuron, MEMORY_TYPE_SIZE* inputMemory, MEMORY_TYPE_SIZE* outputMemory) {
    while (running) {
        mtx.lock();
        neuron->readRandomInputValue();
        mtx.unlock();

        printf("\r"); // Move cursor to the beginning of the line
        fflush(stdout); // Flush the output buffer to ensure the cursor is moved

        printAsciiBar(*inputMemory, neuron->getThreshold(), neuron->getOriginalThreshold(), neuron->getThresholdDecFactor(), ASCII_BAR_LENGTH); // Update to use new printAsciiBar() function
        (void)outputMemory;

        neuron->process();

        std::this_thread::sleep_for(std::chrono::milliseconds(STEP_MS));
    }
}

void biasNeuronThread(MEMORY_TYPE_SIZE* inputMemory) {
    Neuron<MEMORY_TYPE_SIZE> biasNeuron(inputMemory, nullptr);

    while (running) {
        mtx.lock();
        biasNeuron.readRandomInputValue();
        mtx.unlock();

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
    std::thread bias_neuron_thread(biasNeuronThread, &inputMemory);
    std::thread user_input_thread(userInputThread);

    neuron_thread.join();
    bias_neuron_thread.join();
    user_input_thread.join();

    return 0;
}
