#include "MetaNeuron.hpp"

size_t MetaNeuron::g_Neuron_UID = 0;

MetaNeuron::MetaNeuron(){}

MetaNeuron::MetaNeuron(
	std::string u_name,
	int u_expressor,
	int u_scaleMin,
	int u_scaleMax,
	std::string u_unit,
	std::vector<std::string> u_scale
)
:
	neuron_UID(++g_Neuron_UID),
	name(u_name),
	expressor(u_expressor),
	scaleMin(u_scaleMin),
	scaleMax(u_scaleMax),
	unit(u_unit),
	scale(u_scale)
{
}

MetaNeuron::MetaNeuron(MetaNeuron const& src)
{	*this = src; }

MetaNeuron& MetaNeuron::operator= (MetaNeuron const& rhs)
{
	if (this != &rhs)
	{
		TypesNeuron::operator=(rhs);
		this->neuron_UID = rhs.neuron_UID;
		this->name = rhs.name;
		this->expressor = rhs.expressor;
		this->scaleMin = rhs.scaleMin;
		this->scaleMax = rhs.scaleMax;
		this->unit = rhs.unit;
		this->scale = rhs.scale;
	}
	return *this;
}

std::string MetaNeuron::readable() const
{
	return TypesNeuron::readable() + \
		std::to_string(neuron_UID) + " " + \
		name + "," + std::to_string(expressor) + "," + \
		std::to_string(scaleMin) + "," + std::to_string(scaleMax) + "," + \
		unit + "," + to_string(scale) + ";";
}

MetaNeuron::~MetaNeuron()
{}
