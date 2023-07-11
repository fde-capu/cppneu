#include "TypesNeuron.hpp"

TypesNeuron::TypesNeuron(int u_type)
: type(u_type)
{}

TypesNeuron::TypesNeuron(
	TypesNeuron const& src)
{ *this = src; }

TypesNeuron& TypesNeuron::operator=
	(TypesNeuron const & rhs)
{
	if (this != &rhs)
	{
		DynamicNeuron::operator=(rhs);
		this->type = rhs.type;
	}
	return *this;
}

std::string TypesNeuron::readable() const
{
	std::string readOut = "";
	if (type)
		readOut += std::string(1, type);
	readOut += " ";
	return readOut;
}

bool TypesNeuron::isNeuron()
{ return
				type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
		||	type == T_QUIET
;}

bool TypesNeuron::isBias() const
{ return type == T_BIAS; }

bool TypesNeuron::hasInput()
{ return
				type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
		||	type == T_QUIET
;}

bool TypesNeuron::hasOutput()
{ return hasInput() || isBias(); }

TypesNeuron::~TypesNeuron() {}
