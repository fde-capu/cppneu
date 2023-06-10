#include "MetaNeuron.hpp"

size_t MetaNeuron::g_Neuron_UID = 0;

MetaNeuron::MetaNeuron(){}

MetaNeuron::MetaNeuron(
	t_config u_,
	size_t u_out,
	size_t u_in
)
:
	Neuron(),
	DynamicNeuron(
		u_.damp
	),
	TypesNeuron(
		u_.type,
		u_out,
		u_in
	),
	neuron_UID(++g_Neuron_UID),
	name(u_.name),
	expressor(u_.expressor),
	scaleMin(u_.scaleMin),
	scaleMax(u_.scaleMax),
	unit(u_.unit),
	scale(u_.scale)
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

std::string MetaNeuron::getDescription()
{
	double scaleFactor;
	size_t scaledExpressor;
	zo getExpressor;
	std::stringstream ss;

	getExpressor = expressor == EXPRESSOR_CURRENT ? inputValue :
								expressor == EXPRESSOR_THRESHOLD ? threshold :
								expressor == EXPRESSOR_ORIGINAL_THRESHOLD ? originalThreshold :
								expressor == EXPRESSOR_THRESHOLD_SHORT ?
									(threshold - originalThreshold) / (1.0 - originalThreshold)
								: 0.0;
	if (outputValue)
		ss << "* ";
	else
		ss << "  ";
	ss << name;
	if (isBeing())
	{
		if (scaleMax)
		{
			scaleFactor = static_cast<double>(scaleMax - scaleMin);
			scaledExpressor = static_cast<int>(getExpressor * scaleFactor) + scaleMin;
			ss << ": " << scaledExpressor << unit.c_str();
		}
		if (scale.size())
		{
			scaleFactor = static_cast<double>(scale.size());
			scaledExpressor = static_cast<int>(getExpressor * scaleFactor);
			if (scaledExpressor > scale.size() - 1) scaledExpressor = scale.size() - 1;
			ss << ": " << scale[scaledExpressor];
		}
		if (!scale.size() && !scaleMax)
		{
			scaleFactor = static_cast<double>(1.0);
			scaleFactor = static_cast<double>(getExpressor * scaleFactor);
			ss << ": " << scaleFactor;
		}
	}
	return ss.str();
}

MetaNeuron::~MetaNeuron()
{}
