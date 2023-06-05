#include "Neuron.hpp"
#include <iostream>

Neuron::Neuron()
{
	originalThreshold = randomZeroOne();
	debug("Aa" + std::to_string(originalThreshold));
	init();
}

void Neuron::init()
{
	strbin = tobin(originalThreshold);

	std::stringstream ss;
	ss << "N" << originalThreshold;
	readable = ss.str();
}

void Neuron::tick()
{
	outputValue = inputValue >= originalThreshold ?
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
