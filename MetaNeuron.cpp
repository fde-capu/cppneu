#include "MetaNeuron.hpp"

MetaNeuron::MetaNeuron(){}

MetaNeuron::MetaNeuron(
	t_config u_
)
:
	Neuron(),
	DynamicNeuron(
		u_.damp
	),
	TypesNeuron(
		u_.type
	),
	neuron_UID(u_.UID),
	name(u_.name),
	expressor(u_.expressor),
	scaleMin(u_.scaleMin),
	scaleMax(u_.scaleMax),
	unit(u_.unit),
	scale(u_.scale)
{
	if (u_.originalThreshold != 0.0)
	{
		originalThreshold = u_.originalThreshold;
		threshold = originalThreshold;
	}
}

MetaNeuron::MetaNeuron(MetaNeuron const& src)
{ *this = src; }

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

bool MetaNeuron::customScale() const
{ return scaleMax && unit.length(); }

std::string MetaNeuron::readable() const
{
	std::string readOut = "";
	readOut += "i" + 
		std::to_string(neuron_UID) + " ";
	if (name.length())
		readOut += name + " ";
	readOut += TypesNeuron::readable();
	if (expressor)
		readOut += std::string(1, expressor) + " ";
	if (customScale())
	{
		readOut += std::to_string(scaleMin) + \
			":" + std::to_string(scaleMax) + \
			":" + unit + \
			" ";
	}
	if (scale.size())
		readOut += to_string(scale) + " ";
	return readOut;
}

std::string MetaNeuron::getDescription()
{
	double scaleFactor;
	size_t scaledExpressor;
	zo getExpressor;
	std::stringstream ss;

	getExpressor =
		expressor == E_CURRENT ? inputValue
		: expressor == E_THRESHOLD ? threshold
		: expressor == E_ORIGINAL ?
			originalThreshold
		: expressor == E_SHORT ?
			(threshold - originalThreshold)
			/ (1.0 + EPSILON - originalThreshold)
		: 0.0;
	
	if (fire)
		ss << "* ";
	else
		ss << "  ";
	if (name.length())
		ss << name;
	if (scaleMax)
	{
		scaleFactor = static_cast<double>(scaleMax - scaleMin);
		scaledExpressor = static_cast<int>(getExpressor * scaleFactor)
			+ scaleMin;
		if (name.length())
			ss << ": ";
		ss << scaledExpressor << unit.c_str();
	}
	if (scale.size())
	{
		scaleFactor = static_cast<double>(scale.size());
		scaledExpressor = static_cast<int>(getExpressor * scaleFactor);
		if (scaledExpressor > scale.size() - 1) scaledExpressor = scale.size() - 1;
		if (name.length())
			ss << ": ";
		ss << scale[scaledExpressor];
	}
	if (!scale.size() && !scaleMax)
	{
		scaleFactor = static_cast<double>(1.0);
		scaleFactor = static_cast<double>(getExpressor * scaleFactor);
		if (name.length())
			ss << ": ";
		ss << floatUpFire(scaleFactor);
	}
	return ss.str();
}

MetaNeuron::~MetaNeuron(){}
