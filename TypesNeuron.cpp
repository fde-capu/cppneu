#include "TypesNeuron.hpp"

TypesNeuron::TypesNeuron(
	int u_type
)
:
type(u_type)
{}

TypesNeuron::TypesNeuron(TypesNeuron const& src)
{ *this = src; }

TypesNeuron& TypesNeuron::operator= (TypesNeuron const & rhs)
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
	readOut += DynamicNeuron::readable();
	switch (type)
	{
		case T_PHYSICAL:
			readOut += std::string(1, T_PHYSICAL_CHAR);
			break;
		case T_VITAL:
			readOut += std::string(1, T_VITAL_CHAR);
			break;
		case T_ACTION:
			readOut += std::string(1, T_ACTION_CHAR);
			break;
		case T_MEASURE:
			readOut += std::string(1, T_MEASURE_CHAR);
			break;
		case T_BIAS:
			readOut += std::string(1, T_BIAS_CHAR);
			break;
		default:
			readOut += "--type-error--";
	}
	readOut += " ";
	return readOut;
}

bool TypesNeuron::isNeuron()
{ return
			type == T_PHYSICAL
		||	type == T_VITAL
		||	type == T_ACTION
		||	type == T_MEASURE
;}

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
{ return hasInput() || isBias(); }

TypesNeuron::~TypesNeuron()
{}
