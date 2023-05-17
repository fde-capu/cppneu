#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <climits>

#define MEMORY_TYPE_SIZE unsigned char

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
    Neuron(T* inputAddress, T* outputAddress, double thresholdDecay = 0.4, double outputValueDecay = 0.8)
        : inputAddress(inputAddress), outputAddress(outputAddress), thresholdDecay(thresholdDecay), outputValueDecay(outputValueDecay) {
        threshold = randomValue<T>();
        originalThreshold = threshold;
    }

    T getThreshold() const {
        return threshold;
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

int main() {
    srand(time(NULL));

    MEMORY_TYPE_SIZE inputMemory; // Removed the initialization
    MEMORY_TYPE_SIZE outputMemory = 0;

    Neuron<MEMORY_TYPE_SIZE> neuron(&inputMemory, &outputMemory);

    for (int i = 0; i < 3; i++) {
        neuron.writeRandomInputValue(); // Write a random value to the input memory address

        std::cout << "Run " << i + 1 << std::endl;
        std::cout << "Threshold: " << static_cast<int>(neuron.getThreshold()) << std::endl;
        std::cout << "Initial input value: " << static_cast<int>(inputMemory) << std::endl;
        std::cout << "Initial output value: " << static_cast<int>(outputMemory) << std::endl;

        neuron.process();

        std::cout << "After processing input value: " << static_cast<int>(inputMemory) << std::endl;
        std::cout << "After processing output value: " << static_cast<int>(outputMemory) << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
