#ifndef DYNAMICNEURON_HPP
# define DYNAMICNEURON_HPP

# include "Neuron.hpp"
# include "header.hpp"
# include <iostream>

class DynamicNeuron: public virtual Neuron
{
	public:
		zo damp;

	public:
		zo threshold = 0.0;
		zo force = 0.0;
		bool fire = false;

	public:
		DynamicNeuron(zo u_damp = -1.0);
		DynamicNeuron(DynamicNeuron const&);
		DynamicNeuron& operator= (DynamicNeuron const&);
		void feed(zo);
		void tick();
		virtual std::string readable() const;
		virtual ~DynamicNeuron();
};

#endif
