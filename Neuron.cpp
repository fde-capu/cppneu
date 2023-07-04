#include "Neuron.hpp"

Neuron::Neuron()
{
	originalThreshold = randomZeroOne();
}

void Neuron::tick()
{
	if (inputValue >= originalThreshold)
	{
		outputValue = 1.0;
		fire = true;
	}
	else
	{
		outputValue = 0.0;
		fire = false;
	}
}

Neuron::Neuron(Neuron const & src)
{ *this = src; }

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
	return "o" + 
		(originalThreshold == 1.0 ? "1.0" :
		removeZerosFromEnd(floatUp(originalThreshold, PRECISION_DIGITS)))
		 + " ";
}

Neuron::~Neuron()
{}
