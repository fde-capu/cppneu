#include "Neuron.hpp"
#include <iostream>

Neuron::Neuron()
{
	debug("Neu ");
	originalThreshold = randomZeroOne();
}

void Neuron::tick()
{
	if (inputValue > originalThreshold)
	{
		outputValue = 1.0;
	}
	else
	{
		outputValue = 0.0;
	}
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

std::string Neuron::readable() const
{
	return "o" + std::to_string(originalThreshold) + ",";
}

Neuron::~Neuron()
{}
