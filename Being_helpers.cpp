#include "Being.hpp"
#include "randoms.hpp"

Being::Being()
{
	Being::g_Axon_UID = 0;
	Being::g_Neuron_UID = 0;
}

std::string Being::getHeader()
{
	std::stringstream ss;
	ss << name << " " << count_neuron << "N " <<
		count_axon << "A " << count_bias << "B";
	return ss.str();
}

void Being::on()
{
	inCount = {};
	for (auto& pair : axon_table)
		inCount[pair.second.slotOut]++;
	bestAction = {};
}

void Being::nextId(size_t& u_id)
{
	if (u_id && neuron_table.count(u_id))
	{
		warn("Warning: overwriting Neuron " +
			std::to_string(u_id) + ".");
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

NEURON& Being::neuronByName(const std::string& name)
{
	for (auto& n : neuron_table)
		if (n.second.name == name)
			return n.second;
	return neuron_table.at(0); // Should return null.
}

void Being::readInput(NEURON& n) {
	n.feed(
		n.isBias() ?
			bias_switch ?
				randomZeroOne()
				: 0.0
		: axonOut[n.neuron_UID]
	);
}

void Being::switchBias()
{ bias_switch = !bias_switch; }
