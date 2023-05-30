#include "DynamicNeuron.hpp"
#include <iostream>

zo DynamicNeuron::default_dump = 0.5;

DynamicNeuron::DynamicNeuron()
{
	threshold = originalThreshold;
	dump = default_dump;
	init();
}

DynamicNeuron::DynamicNeuron(zo set_threshold)
{
	threshold = set_threshold;
	dump = default_dump;
	init();
}

DynamicNeuron::DynamicNeuron(zo set_threshold, zo set_dump)
{
	threshold = set_threshold;
	dump = set_dump;
	init();
}

void DynamicNeuron::init()
{
	strbin = Neuron::strbin +
		tobin(dump);

	std::stringstream ss;
	ss << Neuron::readable <<
		"d" << dump;
	readable = ss.str();
}

zo DynamicNeuron::fire(zo in)
{
	zo out = Neuron::fire(in);
	target = in >= threshold ?
		in : originalThreshold;
	threshold += (target - threshold) * (1.0 - dump);
	return out;
}

DynamicNeuron::DynamicNeuron(DynamicNeuron const & src)
{	*this = src; }

DynamicNeuron & DynamicNeuron::operator= (DynamicNeuron const & rhs)
{
	if (this != &rhs)
	{
		Neuron::operator=(rhs);
		this->dump = rhs.dump;
	}
	return *this;
}

DynamicNeuron::~DynamicNeuron()
{}
