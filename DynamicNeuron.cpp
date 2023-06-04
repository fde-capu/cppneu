#include "DynamicNeuron.hpp"
#include <iostream>

zo DynamicNeuron::default_damp = 0.5;

DynamicNeuron::DynamicNeuron()
{
	debug("B" + std::to_string(originalThreshold));

	threshold = originalThreshold;
	damp = default_damp;
	thresholdDecay = THRESHOLD_DECAY;
	init();
}

DynamicNeuron::DynamicNeuron(zo set_threshold)
: Neuron()
{
	threshold = set_threshold;
	damp = default_damp;
	init();
}

DynamicNeuron::DynamicNeuron(zo set_threshold, zo set_damp)
: Neuron()
{
	threshold = set_threshold;
	damp = set_damp;
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

zo& DynamicNeuron::fire(zo in)
{
	zo& out = Neuron::fire(in);
	if (in >= threshold)
	{
		force = in - threshold;
		threshold += force * (1.0 - damp);
		threshold = in;
	}
	else
	{
		threshold -= 
			((threshold - originalThreshold)
			 * force);
	}
	zoRestrain(threshold, originalThreshold, 1.0);
	return out;
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
