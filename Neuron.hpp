#ifndef NEURON_HPP
# define NEURON_HPP
# include <string>
# include "header.hpp"
# include "defines.hpp"
# include "randoms.hpp"

template <typename T = MEMORY_TYPE_SIZE>
class Neuron
{
	private:
		T threshold;
		T originalThreshold;
		T inputValue;
		T outputValue;
		float thresholdPull;
		int UID;
		std::string name;

	public:
		static int globalUID;
		Neuron(std::string name)
			:	threshold(randomValue<T>()),
				originalThreshold(threshold),
				inputValue(0),
				outputValue(0),
				thresholdPull(1.0),
				UID(Neuron::globalUID++),
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
			updateInternals();
			readAxons();
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
int Neuron<T>::globalUID = 0;

template <typename T>
static std::vector<Neuron<T> > neuronVector;

#endif
