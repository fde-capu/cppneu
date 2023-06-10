#include "Axon.hpp"

size_t Axon::g_Axon_UID = 0;

Axon::Axon(size_t slotIn, size_t slotOut)
: slotIn(slotIn), slotOut(slotOut)
{
	axon_UID = ++g_Axon_UID;
	multiplier = randomZeroOne();
}

Axon::Axon(Axon const& src)
{
	*this = src;
}

Axon& Axon::operator= (Axon const& rhs)
{
	if (this != &rhs)
	{
		this->axon_UID = rhs.axon_UID;
		this->slotIn = rhs.slotIn;
		this->slotOut = rhs.slotOut;
		this->multiplier = rhs.multiplier;
	}
	return *this;
}

Axon::~Axon()
{}
