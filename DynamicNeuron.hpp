#ifndef DYNAMICNEURON_HPP
# define DYNAMICNEURON_HPP

# include "defines.hpp"
# include "Neuron.hpp"
# include "header.hpp"
# include <iostream>

# define DEFAULT_DAMP 0.0

class DynamicNeuron: public virtual Neuron
{
	public:
		zo damp = DEFAULT_DAMP;

	public:
		zo threshold = 0.0;
		zo force = 0.0;

	public:
		DynamicNeuron(zo u_damp = DEFAULT_DAMP);
		DynamicNeuron(DynamicNeuron const&);
		DynamicNeuron& operator= (DynamicNeuron const&);
		void feed(zo);
		void tick();
		virtual std::string readable() const;
		virtual ~DynamicNeuron();
};

#endif
