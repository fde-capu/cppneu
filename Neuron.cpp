#include "Neuron.hpp"
#include <iostream>

Neuron::Neuron()
{
	originalThreshold = randomZeroOne();

	debug("::Neuron()");
	debug(std::to_string(originalThreshold));

	init();
}

Neuron::Neuron(zo set_threshold)
{
	debug("::Neuron(set_threshold)");
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

zo Neuron::fire(zo in)
{
	return in >= originalThreshold ?
		1.0 : 0.0;
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
