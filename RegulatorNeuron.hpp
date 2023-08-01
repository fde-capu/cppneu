#ifndef REGULATORNEURON_HPP
# define REGULATORNEURON_HPP

# include "InteractiveNeuron.hpp"

class RegulatorNeuron: public virtual InteractiveNeuron
{
	public:
		RegulatorNeuron(t_config);
		RegulatorNeuron();
		RegulatorNeuron(RegulatorNeuron const&);
		RegulatorNeuron& operator= (RegulatorNeuron const&);
		~RegulatorNeuron();
};

#endif
