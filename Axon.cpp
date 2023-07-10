#include "Axon.hpp"

Axon::Axon(size_t slotIn, size_t slotOut,
	zo u_multiplier)
: slotIn(slotIn), slotOut(slotOut)
{
	multiplier = u_multiplier == -1.0 ?
		randomZeroOne() : u_multiplier;
	originalMultiplier = multiplier;
	charge = 0.0;
}

Axon::Axon(Axon const& src)
{ *this = src; }

Axon& Axon::operator= (Axon const& rhs)
{
	if (this != &rhs)
	{
		this->slotIn = rhs.slotIn;
		this->slotOut = rhs.slotOut;
		this->multiplier = rhs.multiplier;
		this->originalMultiplier = rhs.originalMultiplier;
		this->charge = rhs.charge;
	}
	return *this;
}

std::string Axon::readable(std::map<size_t, std::string>& name_map) const
{
	std::string readOut = "x " + 
		(
			name_map.count(slotIn) ?
				name_map[slotIn] :
				std::to_string(slotIn)
		)
		+ "-" + zeroDotOut(multiplier)
		+ "-" + 
		(
			name_map.count(slotOut) ?
				name_map[slotOut] :
				std::to_string(slotOut)
		);
	return readOut;
}

void Axon::feed(zo u_charge)
{
	charge = u_charge * multiplier;
}

Axon::~Axon(){}
