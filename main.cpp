#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <climits>

#define MEMORY_TYPE_SIZE unsigned char
#define THRESHOLD_DECAY 0.4
#define OUTPUT_VALUE_DECAY 0.8
#define ASCII_BAR_LENGTH 32

template <typename T = MEMORY_TYPE_SIZE>
T randomValue() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    return static_cast<T>(dist(gen));
}

template <typename T = MEMORY_TYPE_SIZE>
class Neuron {
private:
    T threshold;
    T originalThreshold;
    T* inputAddress;
    T* outputAddress;
    double thresholdDecay; // New member variable for threshold decay
    double outputValueDecay; // New member variable for output value decay

public:
    Neuron(T* inputAddress, T* outputAddress, double thresholdDecay = THRESHOLD_DECAY, double outputValueDecay = OUTPUT_VALUE_DECAY)
        : inputAddress(inputAddress), outputAddress(outputAddress), thresholdDecay(thresholdDecay), outputValueDecay(outputValueDecay) {
        threshold = randomValue<T>();
        originalThreshold = threshold;
    }

    T getThreshold() const {
        return threshold;
    }

    T getOriginalThreshold() const {
        return originalThreshold;
    }

    void writeRandomInputValue() {
        *inputAddress = randomValue<T>();
    }

    void process() {
        if (*inputAddress > threshold) {
            threshold = *inputAddress;
            *outputAddress = *inputAddress;
        } else {
            *outputAddress *= outputValueDecay;
        }
        threshold = originalThreshold + ((threshold - originalThreshold) * thresholdDecay); // Updated threshold update line
        *inputAddress = 0;
    }
};

template <typename T>
void printAsciiBar(T inputValue, T threshold, T originalThreshold, int length) {
    double scaleFactor = static_cast<double>(length) / std::numeric_limits<T>::max();
    int scaledInputValue = static_cast<int>(inputValue * scaleFactor);
    int scaledThreshold = static_cast<int>(threshold * scaleFactor);
    int scaledOriginalThreshold = static_cast<int>(originalThreshold * scaleFactor);

    for (int i = 0; i < length; i++) {
        if (i == scaledThreshold) {
            std::cout << '|';
        } else if (i == scaledOriginalThreshold) {
            std::cout << '*';
        } else if (i < scaledInputValue) {
            std::cout << '=';
        } else {
            std::cout << '-';
        }
    }
    std::cout << std::endl;
}

int main() {
    srand(time(NULL));

    MEMORY_TYPE_SIZE inputMemory; // Removed the initialization
    MEMORY_TYPE_SIZE outputMemory = 0;

    Neuron<MEMORY_TYPE_SIZE> neuron(&inputMemory, &outputMemory);

    for (int i = 0; i < 3; i++) {
        neuron.writeRandomInputValue();

        std::cout << "Run " << i + 1 << std::endl;
        std::cout << "Threshold: " << static_cast<int>(neuron.getThreshold()) << std::endl;
        std::cout << "Input value: " << static_cast<int>(inputMemory) << std::endl;

        printAsciiBar(inputMemory, neuron.getThreshold(), neuron.getOriginalThreshold(), ASCII_BAR_LENGTH);

        neuron.process();

        std::cout << "Output value: " << static_cast<int>(outputMemory) << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
