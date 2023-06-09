#include "TypesNeuron.hpp"

TypesNeuron::TypesNeuron(
	int u_type, size_t u_slotIn, size_t u_slotOut
)
:
type(u_type),
slotIn(u_slotIn),
slotOut(u_slotOut)
{
}

TypesNeuron::TypesNeuron(TypesNeuron const& src)
{ *this = src; }

TypesNeuron& TypesNeuron::operator= (TypesNeuron const & rhs)
{
	if (this != &rhs)
	{
		DynamicNeuron::operator=(rhs);
		this->type = rhs.type;
		this->slotIn = rhs.slotIn;
		this->slotOut = rhs.slotOut;
	}
	return *this;
}

std::string TypesNeuron::readable() const
{
	return DynamicNeuron::readable() + \
		"y" + std::to_string(type) + \
		"," + std::to_string(slotIn) + \
		"," + std::to_string(slotOut) + \
		";";
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

TypesNeuron::~TypesNeuron()
{}
