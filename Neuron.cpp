#include "Neuron.hpp"
#include <iostream>

Neuron::Neuron()
{
	outputValue = 0.0;
	originalThreshold = randomZeroOne();
	debug("A" + std::to_string(originalThreshold));
	init();
}

Neuron::Neuron(zo set_threshold)
{
	originalThreshold = randomZeroOne();
	originalThreshold = set_threshold;
	init();
}

void Neuron::init()
{
	strbin = tobin(originalThreshold);

	std::stringstream ss;
	ss << "N" << originalThreshold;
	readable = ss.str();
}

zo& Neuron::fire(zo in)
{
	outputValue = in >= originalThreshold ?
		1.0 : 0.0;
	return outputValue;
}

Neuron::Neuron(Neuron const & src)
{	*this = src; }

Neuron& Neuron::operator= (Neuron const & rhs)
{
	if (this != &rhs)
	{
		this->originalThreshold = rhs.originalThreshold;
	}
	return *this;
}

Neuron::~Neuron()
{}
