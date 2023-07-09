#ifndef NEURON_HPP
# define NEURON_HPP

# include "header.hpp"
# include "randoms.hpp"
# include <sstream>
# include "helpers.hpp"

class Neuron
{
	public:
		zo originalThreshold = 0.0;

	public:
		zo inputValue = 0.0;
		zo outputValue = 0.0;
		bool fire = false;

	public:
		Neuron();
		Neuron(Neuron const&);
		Neuron& operator= (Neuron const&);
		void tick();
		virtual std::string readable() const;
		virtual ~Neuron();
};

#endif
