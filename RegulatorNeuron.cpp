#include "RegulatorNeuron.hpp"

RegulatorNeuron::RegulatorNeuron(){};

RegulatorNeuron::RegulatorNeuron(t_config u_)
:
	Neuron(),
	DynamicNeuron(
		u_.damp
	),
	TypesNeuron(
		u_.type
	),
	MetaNeuron(u_),
	InteractiveNeuron(u_)
{};

RegulatorNeuron::RegulatorNeuron(RegulatorNeuron const& src)
{ *this = src; }

RegulatorNeuron& RegulatorNeuron::operator= (RegulatorNeuron const& rhs)
{
	if (this != &rhs)
	{
		InteractiveNeuron::operator=(rhs);
//		member = rhs.getMember();
	}
	return *this;
}

RegulatorNeuron::~RegulatorNeuron(){};
