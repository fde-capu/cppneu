#include "Being.hpp"

size_t Being::g_Neuron_UID = 0;

void Being::addAxon()
{
	Axon a(randomNeuronWithOutput(), randomNeuronWithInput());
	axon_table[a.axon_UID] = a;
	count_axon++;
}

void Being::addNeuron(t_config& u_)
{
	if (!u_.UID)
		u_.UID = g_Neuron_UID++;
	else
		g_Neuron_UID =
			u_.UID + 1 > g_Neuron_UID ?
			u_.UID + 1 : g_Neuron_UID;
	NEURON n(u_);
	neuron_table[n.neuron_UID] = n;
	if (n.isNeuron()) count_neuron++;
	if (n.isBias()) count_bias++;
}

size_t Being::randomNeuronWithOutput() {

	if (neuron_table.size() < 1) return 0;

	auto it = neuron_table.begin();
	std::advance(it, 
		randomValue<size_t>(0, neuron_table.size() - 1)
	);
	size_t beingI = it->first;

	if (!neuron_table.at(beingI).hasOutput())
		return randomNeuronWithOutput();
	return neuron_table.at(beingI).neuron_UID;
}

size_t Being::randomNeuronWithInput() {
	if (neuron_table.size() < 1) return 0;

	auto it = neuron_table.begin();
	std::advance(it, 
		randomValue<size_t>(0, neuron_table.size() - 1)
	);
	size_t beingI = it->first;

	if (!neuron_table.at(beingI).hasInput())
		return randomNeuronWithInput();
	return neuron_table.at(beingI).neuron_UID;
}

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

void Being::readInput(NEURON& n) {
	n.feed(
		n.isBias() ?
			bias_switch ? randomZeroOne() : 0.0
		:
			axonOut[n.neuron_UID]
	);
}

void Being::process()
{
	actionScore *= 0.99;
	if (actionScore < 0.001)
		bestAction = "-";
	for (auto & pair : neuron_table)
	{
		NEURON& n = pair.second;
		readInput(n);
		n.tick();
		neuronOut[n.neuron_UID] = n.outputValue;
		if (n.outputValue)
			extraFiringProcess(n);
	}
	processAxons();
}

void Being::processAxons()
{
	std::map<size_t, size_t> inCount;
	for (auto& pair : axon_table)
	{
		inCount[pair.second.slotOut]++;
	}

	for (auto& pair : axonOut)
		pair.second = 0.0;

	for (auto& pair : axon_table)
	{
		Axon& a = pair.second;
		axonOut[a.slotOut] += \
			neuronOut[a.slotIn] \
			/ inCount[
				neuron_table.at(a.slotOut)
					.neuron_UID] \
			* a.multiplier;
	}
}

std::string Being::readable() const {
	std::stringstream ss;
	for (auto& pair : neuron_table)
	{
		ss << pair.second.readable();
		ss << std::endl;
	}
	return ss.str();
}

void Being::switchBias()
{ bias_switch = !bias_switch; }
