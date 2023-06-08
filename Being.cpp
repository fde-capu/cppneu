#include "Being.hpp"

size_t Being::count_being = 0;
size_t Being::count_axon = 0;
size_t Being::count_bias = 0;

Being::Being(const t_config& u_)
	:
	DynamicNeuron(u_.damp),
	TypesNeuron(u_.type, randomBeingWithOutput(), 
		randomBeingWithInput(), u_.damp),
	name(u_.name),
	expressor(u_.expressor),
	scaleMin(u_.scaleMin),
	scaleMax(u_.scaleMax),
	unit(u_.unit),
	scale(u_.scale)
{
	debug("Being ");

	UID = Being::g_Being_UID++;

	if (isBeing()) count_being++;
	if (isAxon()) count_axon++;
	if (isBias()) count_bias++;

	table.push_back(*this);
	out.resize(table.size());
	axonOut.resize(table.size());
}

void Being::reset()
{
	table.clear();
	out.clear();
	axonOut.clear();
}

size_t Being::randomBeingWithOutput() {
	if (!size()) return 0;
	size_t beingI = randomValue<size_t>(0, size() - 1);
	if (!table[beingI].hasOutput())
		return randomBeingWithOutput();
	return beingI;
}

size_t Being::randomBeingWithInput() {
	if (!size()) return 0;
	size_t beingI = randomValue<size_t>(0, size() - 1);
	if (!table[beingI].hasInput())
		return randomBeingWithInput();
	return beingI;
}

size_t Being::size() { return table.size(); }

void Being::extraFiringProcess() {
	if (!isBias())
	{
		if (force > actionScore)
		{
			actionScore = force;
			bestAction = printDescription();
			return;
		}
	}
}

void Being::readAxons() {
	feed(
		type == T_BIAS ?
			randomZeroOne()
		:
			axonOut[UID]
	);
}

void Being::process()
{
	actionScore *= 0.99;
	if (actionScore < 0.001)
		bestAction = "-";
	readAxons();
	tick();
	out[UID] = outputValue;
	if (outputValue)
		extraFiringProcess();
}

void Being::processAll()
{
		for (auto& being : table)
			being.process();
		processAxons();
}

void Being::processAxons()
{
	std::vector<size_t> inCount(table.size(), 0);
	for (size_t i = 0; i < table.size(); i++)
	{
		if (table[i].type == T_AXON)
			inCount[table[i].slotOut]++;
	}

	for (auto& v : axonOut)
		v = 0.0;

	for (size_t i = 0; i < table.size(); i++)
	{
		if (table[i].type == T_AXON)
		{
			size_t slotI = table[i].slotIn;
			size_t slotO = table[i].slotOut;
			if (!std::isinf(out[slotI]))
				axonOut[slotO] += out[slotI] * table[i].multiplyer / inCount[slotO];
		}
	}
}

size_t Being::g_Being_UID = 0;
std::vector<Being> Being::table;
zo Being::actionScore = 0.0;
std::string Being::bestAction = "";
std::vector<zo> Being::out;
std::vector<zo> Being::axonOut;

const std::string Being::to_string()
{
	std::stringstream ss;
	for (auto& being : table)
	{
		ss << being.readable();
	}
	return ss.str();
}

std::string Being::readable() const {
	return "B[" + TypesNeuron::readable() + "];";
}
