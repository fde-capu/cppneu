#include "MetaNeuron.hpp"

MetaNeuron::MetaNeuron()
{
	debug("Meta ");
}

MetaNeuron::MetaNeuron(MetaNeuron const& src)
{	*this = src; }

MetaNeuron& MetaNeuron::operator= (MetaNeuron const& rhs)
{
	if (this != &rhs)
	{
		TypesNeuron::operator=(rhs);
	}
	return *this;
}

std::string MetaNeuron::readable() const
{
	return TypesNeuron::readable() + \
		"(meta)";
}

MetaNeuron::~MetaNeuron()
{}
