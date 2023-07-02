#include "DynamicNeuron.hpp"

DynamicNeuron::DynamicNeuron(zo u_damp)
{
	damp = u_damp != -1.0 ? u_damp :
		randomZeroOne();
	threshold = originalThreshold;
	debug("SET threshold " + std::to_string(threshold));
}

bool DynamicNeuron::firing()
{ return inputValue > threshold; }

void DynamicNeuron::feed(zo in)
{
	if (firing())
		inputValue -= threshold;
	inputValue *= damp;
	inputValue += in;
	zoRestrain(inputValue);
}

void DynamicNeuron::tick()
{
	Neuron::tick();
	if (firing())
	{
		force = (inputValue - threshold);
		threshold += force * (1.0 - damp) / 10;
	}
	else
	{
		threshold -= 
			((threshold - originalThreshold)
			 * force) * (1.0 - damp);
		outputValue = 0.0;
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
	return Neuron::readable() + (damp != 0.0 ? "d" + 
		removeZerosFromEnd(floatUp(damp, PRECISION_DIGITS))
	 + " " : "");
}

DynamicNeuron::~DynamicNeuron()
{}
