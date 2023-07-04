#include "DynamicNeuron.hpp"

DynamicNeuron::DynamicNeuron(zo u_damp)
{
	damp = u_damp != -1.0 ? u_damp :
		randomZeroOne();
	threshold = originalThreshold;
}

void DynamicNeuron::feed(zo in)
{
	if (fire)
		inputValue -= threshold;
	inputValue *= damp;
	inputValue += in;
	zoRestrain(inputValue);
}

void DynamicNeuron::tick()
{
	if (false) Neuron::tick(); // Ignore.
	fire = inputValue >= threshold;
	outputValue = fire ? 1.0 : 0.0;
	if (fire)
	{
		force = (inputValue - threshold);
		threshold += force * (1.0 - damp) / 10;
	}
	else
	{
		threshold -= 
			((threshold - originalThreshold)
			 * force) * (1.0 - damp);
	}
	zoRestrain(threshold, originalThreshold, 1.0);
}

DynamicNeuron::DynamicNeuron(DynamicNeuron const& src)
{ *this = src; }

DynamicNeuron& DynamicNeuron::operator= (DynamicNeuron const & rhs)
{
	if (this != &rhs)
	{
		Neuron::operator=(rhs);
		this->damp = rhs.damp;
		this->threshold = rhs.threshold;
		this->force = rhs.force;
	}
	return *this;
}

std::string DynamicNeuron::readable() const
{
	return Neuron::readable() + (
		damp != 0.0 ? 
			"d" + removeZerosFromEnd(
				floatUp(damp, PRECISION_DIGITS))
	 + " " : "");
}

DynamicNeuron::~DynamicNeuron()
{}
