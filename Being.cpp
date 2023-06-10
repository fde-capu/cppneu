#include "Being.hpp"

void Being::addNeuron(const t_config& u_)
{
	NEURON n(u_, randomBeingWithOutput(), randomBeingWithInput());
	neuron_table.push_back(n);
	out.resize(neuron_table.size());
	axonOut.resize(neuron_table.size());
	if (n.isBeing()) count_being++;
	if (n.isAxon()) count_axon++;
	if (n.isBias()) count_bias++;
}

size_t Being::randomBeingWithOutput() {
	if (!size()) return 0;
	size_t beingI = randomValue<size_t>(0, size() - 1);
	if (!neuron_table[beingI].hasOutput())
		return randomBeingWithOutput();
	return neuron_table[beingI].neuron_UID;
}

size_t Being::randomBeingWithInput() {
	if (!size()) return 0;
	size_t beingI = randomValue<size_t>(0, size() - 1);
	if (!neuron_table[beingI].hasInput())
		return randomBeingWithInput();
	return neuron_table[beingI].neuron_UID;
}

size_t Being::size() { return neuron_table.size(); }

void Being::extraFiringProcess(NEURON& n) {
	if (!n.isBias())
	{
		if (n.force > actionScore)
		{
			actionScore = n.force;
			bestAction = n.getDescription();
			return;
		}
	}
}

void Being::readAxons(NEURON& n) {
	n.feed(
		n.isBias() ?
			randomZeroOne()
		:
			axonOut[n.neuron_UID]
	);
}

void Being::process()
{
	actionScore *= 0.99;
	if (actionScore < 0.001)
		bestAction = "-";
	for (NEURON& n : neuron_table)
	{
		readAxons(n);
		n.tick();
		out[n.neuron_UID] = n.outputValue;
		if (n.outputValue)
			extraFiringProcess(n);
	}
	processAxons();
}

void Being::processAxons()
{
	std::vector<size_t> inCount(neuron_table.size(), 0);
	for (size_t i = 0; i < neuron_table.size(); i++)
	{
		if (neuron_table[i].isAxon())
			inCount[neuron_table[i].slotOut]++;
	}

	for (zo& v : axonOut)
		v = 0.0;

	for (size_t i = 0; i < neuron_table.size(); i++)
	{
		if (neuron_table[i].isAxon())
		{
			size_t slotI = neuron_table[i].slotIn;
			size_t slotO = neuron_table[i].slotOut;
			if (!std::isinf(out[slotI]))
				axonOut[slotO] += out[slotI] * \
					neuron_table[i].threshold / inCount[slotO];
		}
	}
}

std::string Being::readable() const {
	std::string s;
	s = "{";
	for (const NEURON& n : neuron_table)
		s += n.readable();
	s += "}";
	return s;
}
