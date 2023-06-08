#ifndef DYNAMICNEURON_HPP
# define DYNAMICNEURON_HPP

# include <iostream>
# include "defines.hpp"
# include "Neuron.hpp"
# include "header.hpp"

class DynamicNeuron: public virtual Neuron
{
	public:
		zo threshold = 0.0;
		zo damp = 0.0;

	public:
		zo force = 0.0;

	public:
		DynamicNeuron(zo);
		DynamicNeuron(DynamicNeuron const&);
		DynamicNeuron& operator= (DynamicNeuron const&);
		void feed(zo);
		void tick();
		virtual std::string readable() const;
		virtual ~DynamicNeuron();
};

#endif
