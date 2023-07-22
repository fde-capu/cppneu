#include "Being.hpp"
#include "randoms.hpp"

size_t Being::g_Neuron_UID = 0;
size_t Being::g_Axon_UID = 0;

void Being::on()
{
	inCount = {};
	for (auto& pair : axon_table)
		inCount[pair.second.slotOut]++;
	bestAction = {};
	for (auto& pair : neuron_table)
	{
		if (pair.second.isNeuron() && pair.second.type != T_QUIET)
			bestAction.push_back(pair.second.neuron_UID);
		if (pair.second.name.length())
			nameList[pair.second.neuron_UID] = pair.second.name;
	}
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

void Being::addNeuron(t_config& u_)
{
	nextId(u_.UID);
	if (!u_.name.length())
		u_.name = "_" +
			std::to_string(u_.UID) + "_";
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

NEURON& Being::neuronByName(const std::string& name)
{
	for (auto& n : neuron_table)
		if (n.second.name == name)
			return n.second;
	return neuron_table.at(0); // Should return null.
}

void Being::poke(const std::string& name)
{
	neuronByName(name).poke();
}

void Being::extraFiringProcess(NEURON& n)
{
	if (!n.isBias() && !(n.type == T_QUIET))
	{
		if (n.force > actionScore)
		{
			actionScore = n.force;
			ponderAction(n);
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
		: axonOut[n.neuron_UID]
	);
}

void Being::inaction()
{
  auto it = std::find(bestAction.begin(), bestAction.end(), ST_MAX);
  if (it != bestAction.end())
    std::rotate(bestAction.begin(), it, it + 1);
	else
	{
		bestAction.push_front(ST_MAX);
		if (bestAction.size() > 10)
			bestAction.pop_back();
	}
}

void Being::ponderAction(const NEURON& n)
{
  auto it = std::find(bestAction.begin(), bestAction.end(), n.neuron_UID);
  if (it != bestAction.end())
    std::rotate(bestAction.begin(), it, it + 1);
	else
	{
		bestAction.push_front(n.neuron_UID);
		if (bestAction.size() > 10)
			bestAction.pop_back();
	}
}

void Being::process()
{
	actionScore *= 0.9;
	if (actionScore < EPSILON)
		inaction();
	for (auto & pair : neuron_table)
	{
		NEURON& n = pair.second;
		readInput(n);
		n.tick();
		neuronOut[n.neuron_UID] = n.outputValue;
		if (n.outputValue)
			extraFiringProcess(n);
	}
	balanceAxons();
	processAxons();
}

void Being::balanceAxons()
{
	for (auto& pair : axon_table)
	{
		Axon& a = pair.second;
		if (neuronOut[a.slotOut]
			&& a.charge)
		{
			zo sum = 0.0;
			size_t count;
			for (auto& v : fireCount[a.slotOut])
				sum += v;
			count = fireCount[a.slotOut].size();
			zo med = sum/count;
			a.multiplier += (med - a.multiplier) / count * 0.1;
		}
	}
}

void Being::processAxons()
{
	for (auto& pair : axonOut)
		pair.second = 0.0;
	for (auto& pair : fireCount)
		pair.second = {};
	for (auto& pair : axon_table)
	{
		Axon& a = pair.second;
		if (!neuron_table.count(a.slotOut))
			continue ;
		a.feed(neuronOut[a.slotIn]);
		axonOut[a.slotOut] += a.charge \
			/ inCount[a.slotOut];
		if (a.charge)
			fireCount[a.slotOut].push_back(a.charge);
	}
}

std::string Being::readable() {
	std::stringstream ss;
	for (auto& pair : neuron_table)
		ss << pair.second.readable() << std::endl;
	for (auto& pair : axon_table)
		ss << pair.second.readable(nameList) << std::endl;
	return ss.str();
}

void Being::switchBias()
{ bias_switch = !bias_switch; }

void Being::save(const char* u_fn)
{
	std::ofstream fn(u_fn);
	if (fn.is_open())
	{
		fn << readable();
		fn.close();
	}
}
