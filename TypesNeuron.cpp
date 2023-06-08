#include "TypesNeuron.hpp"

TypesNeuron::TypesNeuron(zo u_damp)
:
DynamicNeuron(u_damp)
{
	debug("Types ");
}

std::string TypesNeuron::readable() const
{
	return DynamicNeuron::readable() + ",";
}
