#ifndef INTERACTIVENEURON_HPP
# define INTERACTIVENEURON_HPP

# include "MetaNeuron.hpp"

class InteractiveNeuron: public virtual MetaNeuron
{
	public:
		bool poked = false;
		void poke();

	public:
		bool isPoked();

	public:
		InteractiveNeuron(t_config);
		InteractiveNeuron();
		InteractiveNeuron(InteractiveNeuron const&);
		InteractiveNeuron& operator= (InteractiveNeuron const&);
		~InteractiveNeuron();
};

#endif
