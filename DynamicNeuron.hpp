#ifndef DYNAMICNEURON_HPP
# define DYNAMICNEURON_HPP

# include <iostream>
# include "defines.hpp"
# include "Neuron.hpp"

class DynamicNeuron: public Neuron
{
	public:
		zo dump;

	public:
		DynamicNeuron();
		DynamicNeuron(zo);
		DynamicNeuron(zo, zo);
		DynamicNeuron(DynamicNeuron const&);
		DynamicNeuron& operator= (DynamicNeuron const&);
		~DynamicNeuron();
		zo fire(zo);
		std::string strbin;
		std::string readable;
		zo threshold;

	private:
		void init();
		static zo default_dump;
		zo target;
};

#endif
