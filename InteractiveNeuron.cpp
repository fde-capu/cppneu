#include "InteractiveNeuron.hpp" 

InteractiveNeuron::InteractiveNeuron(){};

InteractiveNeuron::InteractiveNeuron(n_config u_)
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
	poked = true;
}

bool InteractiveNeuron::isPoked()
{
	bool old_poke = poked;
	poked = false;
	return old_poke;
}

InteractiveNeuron::InteractiveNeuron(InteractiveNeuron const& src)
{ *this = src; }

InteractiveNeuron& InteractiveNeuron::operator= (InteractiveNeuron const& rhs)
{
	if (this != &rhs)
	{
		MetaNeuron::operator=(rhs);
		this->poked = rhs.poked;
	}
	return *this;
}

InteractiveNeuron::~InteractiveNeuron(){};
