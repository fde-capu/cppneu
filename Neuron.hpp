#ifndef NEURON_HPP
# define NEURON_HPP

class Neuron {
	private:
		MEMORY_TYPE_SIZE threshold;
		MEMORY_TYPE_SIZE originalThreshold;
		MEMORY_TYPE_SIZE inputValue;
		MEMORY_TYPE_SIZE outputValue;
		ZERO_ONE_SIZE thresholdPull;
		size_t UID;
		std::string name;

	public:
		static size_t globalUID;
		static std::vector<Neuron> neuronVector;
		static std::vector<ZERO_ONE_SIZE> neuronOut;

		MEMORY_TYPE_SIZE getInputValue() const;
		MEMORY_TYPE_SIZE getThreshold() const;
		MEMORY_TYPE_SIZE getOriginalThreshold() const;
		int getUID() const;
		MEMORY_TYPE_SIZE getOutputValue() const;
		std::string getName() const;
		void process();
		ZERO_ONE_SIZE getThresholdDecFactor() const;
		void readAxons();
		void updateInternals();

		Neuron(std::string name)
			:	threshold(randomValue<MEMORY_TYPE_SIZE>()),
			originalThreshold(threshold),
			inputValue(0),
			outputValue(0),
			thresholdPull(1.0),
			UID(Neuron::globalUID++),
			name(name)
	{
		Neuron::neuronVector.push_back(*this);
		Neuron::neuronOut.resize(Neuron::neuronVector.size());
	}
};

#endif
