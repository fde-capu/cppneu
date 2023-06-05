#include "Being.hpp"

size_t Being::count_being = 0;
size_t Being::count_axon = 0;
size_t Being::count_bias = 0;

void Being::Bias(int amount)
{
  Being({
		.type = T_BIAS,
		.name = "bias",
		.expressor = EXPRESSOR_CURRENT,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = {}
	});
	if (--amount > 0)
		Being::Bias(amount);
}

void Being::Axon(int amount)
{
  Being({
		.type = T_AXON,
		.name = "",
		.expressor = EXPRESSOR_CURRENT,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = {},
		.damp = 0.0
	});
	if (--amount > 0)
		Being::Axon(amount);
}

Being::Being(const t_config& u_)
	: DynamicNeuron(),
	type(u_.type),
	name(u_.name),
	expressor(u_.expressor),
	scaleMin(u_.scaleMin),
	scaleMax(u_.scaleMax),
	unit(u_.unit),
	scale(u_.scale)
{
	debug("C" + std::to_string(originalThreshold));

	damp = u_.damp;
	UID = Being::g_Being_UID++;
	inputDecay = INPUT_DECAY;
	inputValue = 0.0;
	if (type == T_AXON)
	{
		slotIn = randomBeingWithOutput();
		slotOut = randomBeingWithInput();
		multiplyer = randomZeroOne();
	}
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
	size_t beingI = randomValue<size_t>(0, size() - 1);
	if (!table[beingI].hasOutput())
		return randomBeingWithOutput();
	return beingI;
}

size_t Being::randomBeingWithInput() {
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
	actionScore = 0.0;
	bestAction = " *";
}

void Being::readAxons() {
	if (type == T_BIAS)
	{
		inputValue = randomZeroOne();
		return ;
	}
	if (axonOut[UID])
	{
		inputValue += axonOut[UID];
		zoRestrain(inputValue);
	}
}

void Being::process() {
	inputValue *= inputDecay; 
	readAxons();
	if (isBeing())
	{
		DynamicNeuron::fire(inputValue);
		Being::out[UID] = outputValue;
		if (inputValue >= threshold)
			extraFiringProcess();
	}
}

void Being::processAll() {
		actions.clear();
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

zo Being::max()
{ return 1.0; }

bool Being::isBeing()
{ return
				type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
		||	type == T_BIAS
;}

bool Being::isAxon()
{ return type == T_AXON; }

bool Being::isBias()
{ return type == T_BIAS; }

bool Being::hasInput()
{ return
				type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
;}

bool Being::hasOutput()
{ return isBeing(); }

size_t Being::g_Being_UID = 0;
std::vector<Being> Being::table;
std::vector<std::string> Being::actions;
zo Being::actionScore = 0.0;
std::string Being::bestAction = "";
std::vector<zo> Being::out;
std::vector<zo> Being::axonOut;
