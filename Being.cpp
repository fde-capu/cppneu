#include "Being.hpp"
#include "randoms.hpp"

void Being::addNeuron(n_config& u_)
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

void Being::addAxon(n_config& u_)
{
	if ((u_.slotIn != ST_MAX && !neuron_table.count(u_.slotIn))
	|| (u_.slotOut != ST_MAX && !neuron_table.count(u_.slotOut)))
	{
		warn("Warning: invalid slot, axon " + \
			std::to_string(u_.slotIn) + "-" +
			std::to_string(u_.multiplier) + "-" +
			std::to_string(u_.slotOut) +	\
			" ignored.");
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

void Being::poke(const std::string& nname)
{
	neuronByName(nname).poke();
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
