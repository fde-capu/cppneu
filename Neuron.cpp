#include "Neuron.hpp"

Neuron::Neuron(std::string name)
	:	threshold(randomValue<MEMORY_TYPE_SIZE>()),
	originalThreshold(threshold),
	inputValue(0),
	outputValue(0),
	thresholdPull(1.0),
	UID(Neuron::globalUID++),
	name(name)
{
	Neuron::table.push_back(*this);
	Neuron::out.resize(Neuron::table.size());
}

Axon::Axon()
	: UID(Neuron::globalUID++),
	slotIn(randomValue<size_t>(0, Neuron::size() - 1)),
	slotOut(randomValue<size_t>(0, Neuron::size() - 1)),
	multiplyer(randomZeroOne())
	{
		Axon::table.push_back(*this);
		Axon::out.resize(Axon::table.size());
	}

size_t Neuron::size() { return Neuron::table.size(); }

size_t Axon::getSlotIn() const { return slotIn; }
size_t Axon::getSlotOut() const { return slotOut; }
ZERO_ONE_SIZE Axon::getMultiplyer() const { return multiplyer; }

std::string Neuron::getName() const {
	return name;
}

size_t Neuron::getUID() const {
	return UID;
}

size_t Axon::getUID() const {
	return UID;
}

MEMORY_TYPE_SIZE Neuron::getOutputValue() const {
	return outputValue;
}

MEMORY_TYPE_SIZE Neuron::getInputValue() const {
	return inputValue;
}

MEMORY_TYPE_SIZE Neuron::getThreshold() const {
	return threshold;
}

MEMORY_TYPE_SIZE Neuron::getOriginalThreshold() const {
	return originalThreshold;
}

ZERO_ONE_SIZE Neuron::getThresholdDecFactor() const {
	return thresholdPull;
}

void Neuron::readAxons() {
	if (Axon::out[UID])
		inputValue = Axon::out[UID] * static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max());
	variateValue<MEMORY_TYPE_SIZE>(inputValue, RANDOM_VARIATION);
}

void Neuron::updateInternals() {
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

void Neuron::process() {
	updateInternals();
	readAxons();
	if (inputValue >= threshold) {
		ZERO_ONE_SIZE force = static_cast<ZERO_ONE_SIZE>(inputValue - threshold) / static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max());
		outputValue = std::numeric_limits<MEMORY_TYPE_SIZE>::max();
		threshold += (inputValue - threshold) * force;
		thresholdPull = 1 - (force * 0.05);
		actions.push_back(name);
		if (force > actionScore)
		{
			actionScore = force;
			bestAction = name;
		}
	} else {
		outputValue = 0.0;
	}
	Neuron::out[UID] = static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max()) / static_cast<ZERO_ONE_SIZE>(outputValue);
}

void Neuron::processAll() {
		actions.clear();
		actionScore = 0.0;
		for (auto& neuron : Neuron::table) {
			neuron.process();
		}
}

void Axon::processAll()
{
	std::vector<size_t> inCount(Axon::table.size(), 0);
	for (size_t i = 0; i < Axon::table.size(); i++)
	{
		inCount[Axon::table[i].getSlotOut()]++;
	}

//	printw("inCount\t");
//	for (auto& v : inCount)
//	{ printw("%d\t", v); }
//	printw("\n");
//	
//	printw("Neuron::out\t");
//	for (auto& v : Neuron::out)
//	{ printw("%f\t", v); }
//	printw("\n");
	
	for (auto& v : out)
		v = 0.0;

	for (size_t i = 0; i < Axon::table.size(); i++)
	{
		size_t slotI = Axon::table[i].getSlotIn();
		size_t slotO = Axon::table[i].getSlotOut();
//		printw("\ni %u, slotI %u, slotO %u\n", i, slotI, slotO);
//		printw("%f += %f * %f / %u", out[slotO], Neuron::out[slotI], Axon::table[i].getMultiplyer(), inCount[slotO]);
		if (!std::isinf(Neuron::out[slotI]))
			out[slotO] += Neuron::out[slotI] * Axon::table[i].getMultiplyer() / inCount[slotO];
//		printw(" = %f\n\n", out[slotO]);
	}

}

void Neuron::printAllCharacters() {
		for (auto& neuron : Neuron::table) {
			neuron.printCharacter();
		}
		printw("\n");
		for (auto& action : actions)
			printw(" %s ", action.c_str());
		printw("\n [ %s ]", bestAction.c_str());
		printw("\n");
}

void Neuron::printAllBars() {
		for (auto& neuron : Neuron::table) {
			neuron.printAsciiBar();
		}
}

void Neuron::printOuts() {
		printw("\nNeuron Outputs:\t|");
		for (auto& value : Neuron::out)
		{
			if (!std::isinf(value))
				printw("*|", value);
			else
				printw(" |");
		}
		printw("\n");
		printw("\n");
}

void Neuron::printCharacter() {
	std::string shadowGray(".;-=+*oO&#%@");
	double scaleFactor = static_cast<double>(shadowGray.length() - 1) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
	int scaledInputValue = static_cast<int>(getInputValue() * scaleFactor);
	int scaledThreshold = static_cast<int>(getThreshold() * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(getOriginalThreshold() * scaleFactor);

		printw("%c", shadowGray.at(scaledInputValue));
		printw("%c", shadowGray.at(scaledThreshold));
		printw("%c", shadowGray.at(scaledOriginalThreshold));
		if (getOutputValue())
			printw("!");
		else
			printw(" ");
}

void Neuron::printAsciiBar() {
	int length = ASCII_BAR_LENGTH;
	double scaleFactor = static_cast<double>(length) / std::numeric_limits<MEMORY_TYPE_SIZE>::max();
	int scaledInputValue = static_cast<int>(getInputValue() * scaleFactor);
	int scaledThreshold = static_cast<int>(getThreshold() * scaleFactor);
	int scaledOriginalThreshold = static_cast<int>(getOriginalThreshold() * scaleFactor);

	printw("%u [", getUID());
	for (int i = 0; i < length; i++) {
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

	if (getOutputValue())
		printw(" * ");
	else
		printw("   ");
	printw("%s", getName().c_str());
	printw("\n");
}

void Axon::printAll() {
	for (auto& axon: Axon::table)
	{
		printw("%u [ %d -(%f)-> %d ]\n", axon.getUID(),
			axon.getSlotIn(), axon.getMultiplyer(),
			axon.getSlotOut()); 
	}
}

size_t Neuron::globalUID = 0;
std::vector<Neuron> Neuron::table;
std::vector<std::string> Neuron::actions;
ZERO_ONE_SIZE Neuron::actionScore = 0;
std::string Neuron::bestAction = "";
std::vector<ZERO_ONE_SIZE> Neuron::out;

std::vector<ZERO_ONE_SIZE> Axon::out;
std::vector<Axon> Axon::table;
