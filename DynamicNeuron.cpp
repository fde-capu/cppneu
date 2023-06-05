#include "DynamicNeuron.hpp"
#include <iostream>

zo DynamicNeuron::default_damp = 0.5;

DynamicNeuron::DynamicNeuron()
: Neuron()
{
	debug("Ba" + std::to_string(originalThreshold));

	threshold = originalThreshold;
	damp = default_damp;
	thresholdDecay = THRESHOLD_DECAY;
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

void DynamicNeuron::fire(zo in)
{
	Neuron::fire(in);
	if (in >= threshold)
	{
		force = (in - threshold) * (1.0 - damp);
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
