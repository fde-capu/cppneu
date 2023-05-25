#include "Neuron.hpp"

Neuron::Neuron(int type, std::string name)
	:	threshold(randomValue<MEMORY_TYPE_SIZE>()),
	originalThreshold(threshold),
	inputValue(0),
	outputValue(0),
	thresholdPull(1.0),
	UID(Neuron::globalUID++),
	name(name),
	type(type)
{
	table.push_back(*this);
	Neuron::out.resize(table.size());
	Neuron::axonOut.resize(table.size());
}

Neuron::Neuron(int type, std::string name, std::vector<std::string> scale)
	:	threshold(randomValue<MEMORY_TYPE_SIZE>()),
	originalThreshold(threshold),
	inputValue(0),
	outputValue(0),
	thresholdPull(1.0),
	UID(Neuron::globalUID++),
	name(name),
	type(type),
	scaleMin(0),
	scaleMax(0),
	scale(scale)
{
	table.push_back(*this);
	Neuron::out.resize(table.size());
	Neuron::axonOut.resize(table.size());
}

Neuron::Neuron(int type, std::string name, int scaleMin, int scaleMax, std::string unit, std::vector<std::string> scale = {})
	:	threshold(randomValue<MEMORY_TYPE_SIZE>()),
	originalThreshold(threshold),
	inputValue(0),
	outputValue(0),
	thresholdPull(1.0),
	UID(Neuron::globalUID++),
	name(name),
	type(type),
	scaleMin(scaleMin),
	scaleMax(scaleMax),
	unit(unit),
	scale(scale)
{
	table.push_back(*this);
	Neuron::out.resize(table.size());
	Neuron::axonOut.resize(table.size());
}

Neuron::Neuron(int type)
	:	threshold(type == T_AXON ? 0 : randomValue<MEMORY_TYPE_SIZE>()),
	originalThreshold(threshold),
	inputValue(0),
	outputValue(0),
	thresholdPull(1.0),
	UID(Neuron::globalUID++),
	name(type == T_AXON ? "axon" : ""),
	type(type)
{
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
	if (table[neuronI].type != T_ACTION
		&& table[neuronI].type != T_MEASURE)
		return randomNeuron();
	return neuronI;
}

size_t Neuron::size() { return table.size(); }

void Neuron::readAxons() {
	if (axonOut[UID])
		inputValue = axonOut[UID] * static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max());
}

void Neuron::updateInternals() {
	variateValue<MEMORY_TYPE_SIZE>(inputValue, RANDOM_VARIATION);
	if (type == T_ACTION || type == T_MEASURE)
	{
		if (threshold >= originalThreshold) {
			thresholdPull *= THRESHOLD_STABILITY;
		} else if (threshold < originalThreshold) {
			thresholdPull *= 1 + (1 - THRESHOLD_STABILITY);
		}
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
	if (type == T_ACTION || type == T_MEASURE)
	{
		if (inputValue >= threshold)
		{
			ZERO_ONE_SIZE force = static_cast<ZERO_ONE_SIZE>(inputValue - threshold) / static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max());
			outputValue = std::numeric_limits<MEMORY_TYPE_SIZE>::max();
			threshold += (inputValue - threshold) * force;
			thresholdPull = 1 - (force * 0.05);
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

//	printw("inCount\t");
//	for (auto& v : inCount)
//	{
//		if (v != 0.0)
//			printw("%d\t", v);
//	}
//	printw("\n");
//	
//	printw("Neuron::out\t");
//	for (auto& v : Neuron::out)
//	{
//		if (v != 0.0)
//			printw("%f\t", v);
//	}
//	printw("\n");

	for (auto& v : axonOut)
		v = 0.0;

	for (size_t i = 0; i < table.size(); i++)
	{
		if (table[i].type == T_AXON)
		{
			size_t slotI = table[i].slotIn;
			size_t slotO = table[i].slotOut;
			// printw("\ni %u, slotI %u, slotO %u\n", i, slotI, slotO);
			// printw("%f += %f * %f / %u", axonOut[slotO], out[slotI], table[i].multiplyer, inCount[slotO]);
			if (!std::isinf(out[slotI]))
				axonOut[slotO] += out[slotI] * table[i].multiplyer / inCount[slotO];
			// printw(" = %f\n", axonOut[slotO]);
		}
	}
}

void Neuron::printAllCharacters() {
	for (auto& neuron : table)
	{
		if (neuron.type == T_ACTION || neuron.type == T_MEASURE)
			neuron.printCharacter();
	}

	printw("\n [ %s ]", bestAction.c_str());
	for (auto& action : actions)
		printw(" %s", action.c_str());
	printw("\n");
}

void Neuron::printAllBars() {
		for (auto& neuron : table)
		{
			if (neuron.type == T_ACTION || neuron.type == T_MEASURE)
				neuron.printAsciiBar();
		}
}

void Neuron::printAllAxons() {
		for (auto& neuron : table)
		{
			if (neuron.type == T_AXON)
			{
				printw("%u [ %d -(%f)-> %d ]\n", neuron.UID,
					neuron.slotIn, neuron.multiplyer,
					neuron.slotOut); 
			}
		}
}

void Neuron::printOuts() {
		printw("\nNeuron Outputs:\t|");
		for (auto& neuron : table)
		{
			if (neuron.type == T_ACTION || neuron.type == T_MEASURE)
			{
				if (!std::isinf(out[neuron.UID]))
					printw("*|", out[neuron.UID]);
				else
					printw(" |");
			}
		}
		printw("\n");
		printw("\n");
}

void Neuron::printCharacter() {
	std::string shadowGray(" -~=+*oO&#%@");
	double scaleFactor = static_cast<double>(shadowGray.length() - 1) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
	int scaledInputValue = static_cast<int>(inputValue * scaleFactor);
	int scaledThreshold = static_cast<int>(threshold * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(originalThreshold * scaleFactor);

	printw("%c", shadowGray.at(scaledInputValue));
	printw("%c", shadowGray.at(scaledThreshold));
	printw("%c", shadowGray.at(scaledOriginalThreshold));
	if (outputValue)
		printw("!");
	else
		printw(" ");
}

void Neuron::printAsciiBar() {
	size_t length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
	size_t scaledInputValue = static_cast<int>(inputValue * scaleFactor);
	size_t scaledThreshold = static_cast<int>(threshold * scaleFactor);
	size_t scaledOriginalThreshold = static_cast<int>(originalThreshold * scaleFactor);

	printw("%u [", UID);
	for (size_t i = 0; i < length; i++) {
		if (i == scaledOriginalThreshold && i == scaledThreshold) {
			printw("!");
		} else if (i == scaledOriginalThreshold) {
			printw("+");
		} else if (i == scaledThreshold) {
			printw("|");
		} else if (i < scaledInputValue) {
			printw(".");
		} else {
			printw(" ");
		}
	}
	printw("]");

	printDescription();

	printw("\n");
}

void Neuron::printDescription()
{
	double scaleFactor;
	size_t scaledInputValue;
	size_t scaledThreshold;
	size_t scaledOriginalThreshold;
	(void)scaledOriginalThreshold;
	(void)scaledInputValue;

	if (outputValue)
		printw(" * ");
	else
		printw("   ");
	printw("%s", name.c_str());
	if (type == T_MEASURE)
	{
		if (!scaleMax && scale.size())
		{
			scaleFactor = static_cast<double>(scale.size()) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
			scaledThreshold = static_cast<int>(threshold * scaleFactor);
			printw(": %s", scale[scaledThreshold].c_str());
		}
		else if (scaleMax)
		{
			scaleFactor = static_cast<double>(scaleMax - scaleMin) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
			scaledThreshold = static_cast<int>(threshold * scaleFactor) + scaleMin;
			printw(": %d %s", scaledThreshold, unit.c_str());
			if (scale.size())
			{
				scaleFactor = static_cast<double>(scale.size()) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
				scaledThreshold = static_cast<int>(threshold * scaleFactor);
				printw(": %s", scale[scaledThreshold].c_str());
			}
		}
		else
		{
			scaleFactor = static_cast<double>(1.0) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
			scaleFactor = static_cast<double>(threshold * scaleFactor);
			printw(": %f", scaleFactor);
		}
	}
}

size_t Neuron::globalUID = 0;
std::vector<Neuron> Neuron::table;
std::vector<std::string> Neuron::actions;
ZERO_ONE_SIZE Neuron::actionScore = 0;
std::string Neuron::bestAction = "";
std::vector<ZERO_ONE_SIZE> Neuron::out;
std::vector<ZERO_ONE_SIZE> Neuron::axonOut;
