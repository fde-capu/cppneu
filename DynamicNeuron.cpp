#include "DynamicNeuron.hpp"

DynamicNeuron::DynamicNeuron(zo u_damp)
{
	debug("Dyn ");
	damp = u_damp;
	threshold = originalThreshold;
}

void DynamicNeuron::feed(zo in)
{
	if (inputValue > threshold)
		inputValue -= threshold;
	inputValue *= damp;
	inputValue += in;
	zoRestrain(inputValue);
}

void DynamicNeuron::tick()
{
	Neuron::tick();
	if (inputValue > threshold)
	{
		force = (inputValue - threshold);
		threshold += force * (1.0 - damp);
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

std::string DynamicNeuron::readable() const
{
	return Neuron::readable() + "d" + std::to_string(damp) + ";";
}

DynamicNeuron::~DynamicNeuron()
{}
