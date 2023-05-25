# include "header.hpp"

std::string Neuron::getName() const {
	return name;
}

int Neuron::getUID() const {
	return UID;
}

MEMORY_TYPE_SIZE Neuron::getOutputValue() const {
	return outputValue;
}

MEMORY_TYPE_SIZE Neuron::getInputValue() const {
	return inputValue;
}

MEMORY_TYPE_SIZE Neuron::getThreshold() const {
	return threshold;
}

MEMORY_TYPE_SIZE Neuron::getOriginalThreshold() const {
	return originalThreshold;
}

ZERO_ONE_SIZE Neuron::getThresholdDecFactor() const {
	return thresholdPull;
}

void Neuron::readAxons() {
	variateValue<MEMORY_TYPE_SIZE>(inputValue, RANDOM_VARIATION);
}

void Neuron::updateInternals() {
	if (threshold >= originalThreshold) {
		thresholdPull *= THRESHOLD_STABILITY;
	} else if (threshold < originalThreshold) {
		thresholdPull *= 1 + (1 - THRESHOLD_STABILITY);
	}
	if (thresholdPull > 1.0 && static_cast<MEMORY_TYPE_SIZE>(threshold * thresholdPull) < threshold)
	{
		threshold = std::numeric_limits<MEMORY_TYPE_SIZE>::max();
		thresholdPull = 1.0;
	}
	else
		threshold *= thresholdPull;
}

void Neuron::process() {
	updateInternals();
	readAxons();
	if (inputValue >= threshold) {
		ZERO_ONE_SIZE force = static_cast<ZERO_ONE_SIZE>(inputValue - threshold) / static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max());
		outputValue = std::numeric_limits<MEMORY_TYPE_SIZE>::max();
		threshold += (inputValue - threshold) * force;
		thresholdPull = 1 - (force * 0.1);
	} else {
		outputValue = 0;
	}
	Neuron::neuronOut[UID] = static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max()) / static_cast<ZERO_ONE_SIZE>(outputValue);
}


size_t Neuron::globalUID = 0;

std::vector<Neuron> Neuron::neuronVector;

std::vector<ZERO_ONE_SIZE> Neuron::neuronOut;
