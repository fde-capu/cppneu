#include "DynamicNeuron.hpp"
#include <iostream>

DynamicNeuron::DynamicNeuron(zo u_damp)
: Neuron()
{
	debug("Ba" + std::to_string(originalThreshold));
	damp = u_damp;
	threshold = originalThreshold;
	init();
}

void DynamicNeuron::init()
{
	strbin = Neuron::strbin +
		tobin(damp);

	std::stringstream ss;
	ss << Neuron::readable <<
		"d" << damp;
	readable = ss.str();
}

void DynamicNeuron::tick()
{
	Neuron::tick();
	if (inputValue >= threshold)
	{
		force = (inputValue - threshold) * (1.0 - damp);
		threshold += force;
	}
	else
	{
		threshold -= 
			((threshold - originalThreshold)
			 * force);
		outputValue = 0.0;
	}
	zoRestrain(threshold, originalThreshold, 1.0);
}

DynamicNeuron::DynamicNeuron(DynamicNeuron const & src)
{	*this = src; }

DynamicNeuron& DynamicNeuron::operator= (DynamicNeuron const & rhs)
{
	if (this != &rhs)
	{
		Neuron::operator=(rhs);
		this->damp = rhs.damp;
	}
	return *this;
}

DynamicNeuron::~DynamicNeuron()
{}
