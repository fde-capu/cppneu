#include "TypesNeuron.hpp"

TypesNeuron::TypesNeuron(int u_type, zo u_damp)
:
DynamicNeuron(u_damp),
type(u_type)
{
	debug("Types ");
}

std::string TypesNeuron::readable() const
{
	return DynamicNeuron::readable() + \
		"y" + std::to_string(type) + \
		",";
}

bool TypesNeuron::isBeing()
{ return
				type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
		||	type == T_BIAS
;}

bool TypesNeuron::isAxon()
{ return type == T_AXON; }

bool TypesNeuron::isBias()
{ return type == T_BIAS; }

bool TypesNeuron::hasInput()
{ return
				type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
;}

bool TypesNeuron::hasOutput()
{ return isBeing(); }

