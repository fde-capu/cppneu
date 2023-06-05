#ifndef NEURON_HPP
# define NEURON_HPP

# include "defines.hpp"
# include "randoms.hpp"
# include <sstream>
# include "helpers.hpp"
# include "header.hpp"

class Neuron
{
	public:
		zo outputValue;
		zo originalThreshold;

	public:
		Neuron();
		Neuron(Neuron const&);
		Neuron& operator= (Neuron const&);
		~Neuron();
		void fire(zo);
		std::string strbin;
		std::string readable;
	private:
		void init();
};

#endif
