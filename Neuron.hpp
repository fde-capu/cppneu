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
		zo inputValue = 0.0;
		zo outputValue = 0.0;
		zo originalThreshold = 0.0;

	public:
		Neuron();
		Neuron(Neuron const&);
		Neuron& operator= (Neuron const&);
		~Neuron();
		void tick();
		std::string strbin;
		std::string readable;
	private:
		void init();
};

#endif
