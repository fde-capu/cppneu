#include "InteractiveNeuron.hpp" 

InteractiveNeuron::InteractiveNeuron(){};

InteractiveNeuron::InteractiveNeuron(t_config u_)
:
	Neuron(),
	DynamicNeuron(
		u_.damp
	),
	TypesNeuron(
		u_.type
	),
	MetaNeuron(u_)
{}

void InteractiveNeuron::poke()
{
	feed(1.0);
}

InteractiveNeuron::InteractiveNeuron(InteractiveNeuron const& src)
{ *this = src; }

InteractiveNeuron& InteractiveNeuron::operator= (InteractiveNeuron const& rhs)
{
	if (this != &rhs)
	{
		MetaNeuron::operator=(rhs);
	}
	return *this;
}

InteractiveNeuron::~InteractiveNeuron(){};
