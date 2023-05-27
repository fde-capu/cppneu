#include "Neuron.hpp"

size_t Neuron::count_neuron = 0;
size_t Neuron::count_axon = 0;
size_t Neuron::count_bias = 0;


void Neuron::Physical(std::string name, std::vector<std::string> scale, int expressor)
{
  Neuron({
		.type = T_PHYSICAL,
		.name = name,
		.expressor = expressor,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = scale,
		.dump = 1.0
	});
}

void Neuron::Vital(std::string name, std::vector<std::string> scale,
	int scaleMin, int scaleMax, std::string unit, ZERO_ONE_SIZE dump,
	int expressor)
{
  Neuron({
		.type = T_VITAL,
		.name = name,
		.expressor = expressor,
		.scaleMin = scaleMin,
		.scaleMax = scaleMax,
		.unit = unit,
		.scale = scale,
		.dump = dump
	});
}

void Neuron::Measure(std::string name, std::vector<std::string> scale,
	int expressor)
{
  Neuron({
		.type = T_MEASURE,
		.name = name,
		.expressor = expressor,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = scale,
		.dump = 0.0
	});
}

void Neuron::Action(std::string name, std::vector<std::string> scale)
{
  Neuron({
		.type = T_ACTION,
		.name = name,
		.expressor = EXPRESSOR_CURRENT,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = scale,
		.dump = 0.0
	});
}

void Neuron::Axon(int amount)
{
  Neuron({
		.type = T_AXON,
		.name = "",
		.expressor = EXPRESSOR_CURRENT,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = {},
		.dump = 0.0
	});
	if (--amount > 0)
		Neuron::Axon(amount);
}

void Neuron::Bias(int amount)
{
  Neuron({
		.type = T_BIAS,
		.name = "bias",
		.expressor = EXPRESSOR_CURRENT,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = {}
	});
	if (--amount > 0)
		Neuron::Bias(amount);
}

Neuron::Neuron(const t_config& u_)
: type(u_.type),
	name(u_.name),
	expressor(u_.expressor),
	scaleMin(u_.scaleMin),
	scaleMax(u_.scaleMax),
	unit(u_.unit),
	scale(u_.scale),
	dump(u_.dump)
{
	UID = Neuron::globalUID++;
	originalThreshold = randomValue<MEMORY_TYPE_SIZE>();
	threshold = originalThreshold;
	thresholdDecay = THRESHOLD_DECAY;
	inputValue = 0;
	outputValue = 0;
	if (type == T_AXON)
	{
		slotIn = randomNeuronWithOutput();
		slotOut = randomNeuronWithInput();
		multiplyer = randomZeroOne();
	}
	if (isNeuron()) count_neuron++;
	if (isAxon()) count_axon++;
	if (isBias()) count_bias++;

	table.push_back(*this);
	Neuron::out.resize(table.size());
	Neuron::axonOut.resize(table.size());
}

void Neuron::reset()
{
	table.clear();
	out.clear();
	axonOut.clear();
}

size_t Neuron::randomNeuronWithOutput() {
	size_t neuronI = randomValue<size_t>(0, size() - 1);
	if (!table[neuronI].hasOutput())
		return randomNeuronWithOutput();
	return neuronI;
}

size_t Neuron::randomNeuronWithInput() {
	size_t neuronI = randomValue<size_t>(0, size() - 1);
	if (!table[neuronI].hasInput())
		return randomNeuronWithInput();
	return neuronI;
}

size_t Neuron::size() { return table.size(); }

void Neuron::readAxons() {
	MEMORY_TYPE_SIZE newInputValue;
	if (axonOut[UID])
	{
		newInputValue = axonOut[UID] * \
			static_cast<ZERO_ONE_SIZE>(max());
		if (newInputValue > inputValue)
		{
			if (inputValue + newInputValue < inputValue)
				inputValue = max();
			else
				inputValue += newInputValue;
		}
	}
}

void Neuron::updateInternals() {
	if (type == T_BIAS)
		inputValue = randomValue<MEMORY_TYPE_SIZE>();

	if (isNeuron())
	{
	}
}

void Neuron::process() {
	ZERO_ONE_SIZE force = 0.0;
	long long newThreshold = threshold;

	inputValue -= (inputValue * INPUT_DECAY); 
	readAxons();
	updateInternals();
	if (isNeuron())
	{
		if (inputValue >= threshold)
		{
			force = static_cast<ZERO_ONE_SIZE>(inputValue - threshold) /
				static_cast<ZERO_ONE_SIZE>(max());
			newThreshold += ((inputValue - threshold) * ((1.0 - dump)));
//			thresholdDecay += (force - thresholdDecay) * (1.0 - THRESHOLD_DECAY);
			thresholdDecay += force;
			outputValue = max();

			if (type == T_ACTION)
			{
				actions.push_back(name);
				if (force > actionScore)
				{
					actionScore = force;
					bestAction = name;
				}
			}
		}
		else
		{
			outputValue = 0.0;
		}
		newThreshold -= (((long long)threshold - (long long)originalThreshold) * thresholdDecay);
		thresholdDecay -= (thresholdDecay - THRESHOLD_DECAY) * thresholdDecay;
		if (thresholdDecay > 1.0) thresholdDecay = 1.0;
		if (thresholdDecay < 0.0) thresholdDecay = 0.0;
		if (newThreshold > max()) newThreshold = max();
		if (newThreshold < 0) newThreshold = 0;
		threshold = newThreshold;
		Neuron::out[UID] = static_cast<ZERO_ONE_SIZE>(max()) / static_cast<ZERO_ONE_SIZE>(outputValue);
	}
}

void Neuron::processAll() {
		actions.clear();
		actionScore = 0.0;
		for (auto& neuron : table)
			neuron.process();
		processAxons();
}

void Neuron::processAxons()
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

MEMORY_TYPE_SIZE Neuron::max()
{ return std::numeric_limits<MEMORY_TYPE_SIZE>::max(); }

bool Neuron::isNeuron()
{ return
				type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
		||	type == T_BIAS
;}

bool Neuron::isAxon()
{ return type == T_AXON; }

bool Neuron::isBias()
{ return type == T_BIAS; }

bool Neuron::isStatsVisible()
{ return
				type == T_MEASURE; }

bool Neuron::isBarVisible()
{ return
				type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
//		||	type == T_BIAS
;}

bool Neuron::isCharacterVisible()
{	return
				type == T_VITAL
		||	type == T_MEASURE
		||	type == T_BIAS
;}

bool Neuron::isOutBlockVisible()
{	return
				type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
		||	type == T_BIAS
;}

bool Neuron::hasInput()
{ return
				type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
;}

bool Neuron::hasOutput()
{ return isNeuron(); }

size_t Neuron::globalUID = 0;
std::vector<Neuron> Neuron::table;
std::vector<std::string> Neuron::actions;
ZERO_ONE_SIZE Neuron::actionScore = 0;
std::string Neuron::bestAction = "";
std::vector<ZERO_ONE_SIZE> Neuron::out;
std::vector<ZERO_ONE_SIZE> Neuron::axonOut;
