#ifndef DYNAMICNEURON_HPP
# define DYNAMICNEURON_HPP

# include <iostream>
# include "defines.hpp"
# include "Neuron.hpp"
# include "header.hpp"

class DynamicNeuron: public virtual Neuron
{
	public:
		zo damp;
		zo force;

	public:
		DynamicNeuron();
		DynamicNeuron(zo);
		DynamicNeuron(zo, zo);
		DynamicNeuron(DynamicNeuron const&);
		DynamicNeuron& operator= (DynamicNeuron const&);
		~DynamicNeuron();
		zo& fire(zo);
		std::string strbin;
		std::string readable;
		zo threshold;

	private:
		void init();
		static zo default_damp;
		zo thresholdDecay;
};

#endif
