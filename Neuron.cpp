#include "Neuron.hpp"

void Neuron::Measure(std::string name, std::vector<std::string> scale, int scaleMin, int scaleMax, std::string unit)
{
  Neuron({
		.type = T_MEASURE,
		.name = name,
		.scaleMin = scaleMin,
		.scaleMax = scaleMax,
		.unit = unit,
		.scale = scale
	});
}

void Neuron::Oscil(std::string name, std::vector<std::string> scale)
{
  Neuron({
		.type = T_OSCIL,
		.name = name,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = scale
	});
}

void Neuron::Action(std::string name, std::vector<std::string> scale)
{
  Neuron({
		.type = T_ACTION,
		.name = name,
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = scale
	});
}

void Neuron::Axon(int amount)
{
  Neuron({
		.type = T_AXON,
		.name = "",
		.scaleMin = 0,
		.scaleMax = 0,
		.unit = "",
		.scale = {}
	});
	if (--amount > 0)
		Neuron::Axon(amount);
}

void Neuron::Bias(int amount)
{
  Neuron({
		.type = T_BIAS,
		.name = "bias",
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
	scaleMin(u_.scaleMin),
	scaleMax(u_.scaleMax),
	unit(u_.unit),
	scale(u_.scale)
{
	UID = Neuron::globalUID++;
	originalThreshold = randomValue<MEMORY_TYPE_SIZE>();
	threshold = originalThreshold;
	variateValue<MEMORY_TYPE_SIZE>(threshold, 0.1);
	inputValue = 0;
	outputValue = 0;
	thresholdPull = 1.0;
	speed = SPEED;
	if (type == T_OSCIL)
		speed *= 20;
	if (type == T_AXON)
	{
		slotIn = randomNeuron();
		slotOut = randomNeuron();
		multiplyer = randomZeroOne();
	}

	table.push_back(*this);
	Neuron::out.resize(table.size());
	Neuron::axonOut.resize(table.size());
}

size_t Neuron::randomNeuron() {
	size_t neuronI = randomValue<size_t>(0, size() - 1);
	if (!table[neuronI].isNeuron())
		return randomNeuron();
	return neuronI;
}

size_t Neuron::size() { return table.size(); }

void Neuron::readAxons() {
	if (axonOut[UID])
		inputValue = axonOut[UID] * static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max());
}

void Neuron::updateInternals() {
	if (type == T_BIAS)
		variateValue<MEMORY_TYPE_SIZE>(inputValue, BIAS_VARIATION);
	variateValue<MEMORY_TYPE_SIZE>(inputValue, RANDOM_VARIATION);
	if (isNeuron())
	{
		if (threshold >= originalThreshold)
		{
			thresholdPull -= speed;
		}
		else
		{
			thresholdPull += speed;
		}

		if (thresholdPull < 0)
			thresholdPull = 0;

		if (thresholdPull > 1.0 && static_cast<MEMORY_TYPE_SIZE>(threshold * thresholdPull) < threshold)
		{
			threshold = std::numeric_limits<MEMORY_TYPE_SIZE>::max();
			thresholdPull = 1.0;
		}
		else
			threshold *= thresholdPull;
	}
}

void Neuron::process() {
	readAxons();
	updateInternals();
	if (isNeuron())
	{
		if (inputValue >= threshold)
		{
			ZERO_ONE_SIZE force = static_cast<ZERO_ONE_SIZE>(inputValue - threshold) / static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max());
			outputValue = std::numeric_limits<MEMORY_TYPE_SIZE>::max();
			threshold += (inputValue - threshold) * force;
//			thresholdPull = 1 - (force * speed);
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
		Neuron::out[UID] = static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max()) / static_cast<ZERO_ONE_SIZE>(outputValue);
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

bool Neuron::isNeuron()
{ return type != T_AXON; }

bool Neuron::isAxon()
{ return type == T_AXON; }

bool Neuron::isStatsVisible()
{ return type == T_MEASURE || type == T_OSCIL; }

bool Neuron::isBarVisible()
{ return isNeuron() && type != T_BIAS; }

size_t Neuron::globalUID = 0;
std::vector<Neuron> Neuron::table;
std::vector<std::string> Neuron::actions;
ZERO_ONE_SIZE Neuron::actionScore = 0;
std::string Neuron::bestAction = "";
std::vector<ZERO_ONE_SIZE> Neuron::out;
std::vector<ZERO_ONE_SIZE> Neuron::axonOut;
