#include "Being.hpp"

size_t Being::g_Neuron_UID = 0;
size_t Being::g_Axon_UID = 0;

void Being::addAxon(t_config& u_)
{
	Axon a(
		u_.slotIn ?
			u_.slotIn : randomNeuronWithOutput(),
		u_.slotOut ?
			u_.slotOut : randomNeuronWithInput(),
		u_.multiplier ? u_.multiplier : -1.0
	);
	axon_table[g_Axon_UID++] = a;
	count_axon++;
}

void Being::addNeuron(t_config& u_)
{
	nextId(u_.UID);
	NEURON n(u_);
	neuron_table[n.neuron_UID] = n;
	if (n.isNeuron()) count_neuron++;
	if (n.isBias()) count_bias++;
}

void Being::nextId(size_t& u_id) const
{
	if (u_id && neuron_table.count(u_id))
	{
		std::cerr << "Warning: overwriting Neuron "
			<< u_id << "." << std::endl;
	}
	else
	{
		if (u_id || !g_Neuron_UID)
			return (void)g_Neuron_UID++;
		while (neuron_table.count(g_Neuron_UID))
			g_Neuron_UID++;
		u_id = g_Neuron_UID;
	}
}

size_t Being::randomNeuronWithOutput()
{
	if (count_neuron < 1)
		throw std::runtime_error("Not enough neurons.");
	auto it = neuron_table.begin();
	std::advance(it, 
		randomValue<size_t>
		(0, neuron_table.size() - 1));
	size_t beingI = it->first;
	if (!neuron_table.at(beingI).hasOutput())
		return randomNeuronWithOutput();
	return neuron_table.at(beingI).neuron_UID;
}

size_t Being::randomNeuronWithInput()
{
	if (count_neuron < 1)
		throw std::runtime_error("Not enough neurons.");
	auto it = neuron_table.begin();
	std::advance(it, 
		randomValue<size_t>
		(0, neuron_table.size() - 1));
	size_t beingI = it->first;
	if (!neuron_table.at(beingI).hasInput())
		return randomNeuronWithInput();
	return neuron_table.at(beingI).neuron_UID;
}

void Being::extraFiringProcess(NEURON& n)
{
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
			bias_switch ?
				randomZeroOne()
				: 0.0
		:
			n.neuron_UID ?
				axonOut[n.neuron_UID]
				: 0.0
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

void Being::on()
{
	for (auto& pair : axon_table)
		inCount[pair.second.slotOut]++;
}

void Being::processAxons()
{
	for (auto& pair : axonOut)
		pair.second = 0.0;
	for (auto& pair : axon_table)
	{
		Axon& a = pair.second;
		if (!neuron_table.count(a.slotOut))
			continue ;
		axonOut[a.slotOut] +=
			neuronOut[a.slotIn] \
			/ inCount[
				neuron_table.at(a.slotOut) \
					.neuron_UID
				] \
			* a.multiplier;
	}
}

std::string Being::readable() const {
	std::stringstream ss;
	for (auto& pair : neuron_table)
		ss << pair.second.readable() << std::endl;
	for (auto& pair : axon_table)
		ss << pair.second.readable() << std::endl;
	return ss.str();
}

void Being::switchBias()
{ bias_switch = !bias_switch; }
