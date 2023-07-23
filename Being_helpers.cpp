#include "Being.hpp"
#include "randoms.hpp"

Being::Being()
{}

void Being::on()
{
	inCount = {};
	for (auto& pair : axon_table)
		inCount[pair.second.slotOut]++;
	bestAction = {};
	status("Being on: " + name);
}

void Being::addNeuron(t_config& u_)
{
	nextId(u_.UID);
	if (!u_.name.length())
		u_.name = "_" +
			std::to_string(u_.UID) + "_";
	NEURON n(u_);
	neuron_table[n.neuron_UID] = n;
	nameList[n.neuron_UID] = n.name;
	if (n.isNeuron())
	{
		count_neuron++;
		if (n.type != T_QUIET)
			bestAction.push_back(n.neuron_UID);
	}
	if (n.isBias()) count_bias++;
}

void Being::addAxon(t_config& u_)
{
	if ((u_.slotIn != ST_MAX && !neuron_table.count(u_.slotIn))
	|| (u_.slotOut != ST_MAX && !neuron_table.count(u_.slotOut)))
	{
		std::cerr << "Warning: invalid slot, axon " << \
		u_.slotIn << "-" << u_.multiplier << "-" << u_.slotOut <<	\
		" ignored.";
		return ;
	}
	Axon a(
		u_.slotIn != ST_MAX ?
			u_.slotIn : randomNeuronWithOutput(),
		u_.slotOut != ST_MAX ?
			u_.slotOut : randomNeuronWithInput(),
		u_.multiplier ? u_.multiplier : randomZeroOne()
	);
	bool merge = false;
	for (auto& pair : axon_table)
	{
		if (pair.second.slotIn == a.slotIn
		&&	pair.second.slotOut == a.slotOut)
		{
			size_t div = ++axonMergeCount[pair.first] + 1;
			pair.second.multiplier = \
					(pair.second.multiplier / div * (div - 1))
					+ (a.multiplier / div);
			merge = true;
			break ;
		}
	}
	if (!merge)
	{
		axon_table[g_Axon_UID++] = a;
		count_axon++;
	}
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
