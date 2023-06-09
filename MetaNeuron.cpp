#include "MetaNeuron.hpp"

MetaNeuron::MetaNeuron(
	std::string u_name,
	int u_expressor,
	int u_scaleMin,
	int u_scaleMax,
	std::string u_unit,
	std::vector<std::string> u_scale
)
:
	name(u_name),
	expressor(u_expressor),
	scaleMin(u_scaleMin),
	scaleMax(u_scaleMax),
	unit(u_unit),
	scale(u_scale)
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
