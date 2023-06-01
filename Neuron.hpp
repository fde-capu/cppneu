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
		zo originalThreshold;

	public:
		Neuron();
		Neuron(zo);
		Neuron(Neuron const&);
		Neuron& operator= (Neuron const&);
		~Neuron();
		zo fire(zo);
		std::string strbin;
		std::string readable;
	private:
		void init();
};

#endif
