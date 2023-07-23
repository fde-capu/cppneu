#include "Being.hpp"
#include "randoms.hpp"

size_t Being::g_Neuron_UID = 0;
size_t Being::g_Axon_UID = 0;

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

std::string Being::readable()
{
	std::stringstream ss;
		ss << "name:" << name << std::endl;
	for (auto& pair : neuron_table)
		ss << pair.second.readable() << std::endl;
	for (auto& pair : axon_table)
		ss << pair.second.readable(nameList) << std::endl;
	return ss.str();
}

void Being::save()
{
	std::string f_name(name);
	prompt("Name:", f_name);
	if (!f_name.length())
	{
		status("Save aborted.");
		return ;
	}
	std::string filename =
		std::string(SAVE_DIRECTORY)
		+ std::string("/") + f_name;
	std::ofstream fn(filename.c_str());
	if (fn.is_open())
	{
		fn << readable();
		fn.close();
		status("File saved: " + filename);
	}
	else
	{
		status("Failed to save.");
	}
}
