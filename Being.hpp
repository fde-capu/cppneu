#ifndef BEING_HPP
# define BEING_HPP

# include <vector>
# include "defines.hpp"
# include <string>
# include "randoms.hpp"
# include <ncurses.h>
# include <sstream>
# include LAST_NEURON_IMPLEMENTATION
# include "header.hpp"

class Being {
	public:
		std::vector<NEURON> neuron_table = {};
		std::vector<zo> out = {};
		std::vector<zo> axonOut = {};
		zo actionScore = 0.0;
		std::string bestAction = "";
		size_t count_being = 0;
		size_t count_axon = 0;
		size_t count_bias = 0;

		void addNeuron(const t_config& u_);

		void process();
		void processAxons();
		void readAxons(NEURON&);
		void extraFiringProcess(NEURON&);

		size_t size();

		size_t randomBeingWithOutput();
		size_t randomBeingWithInput();

		virtual std::string readable() const ;
};

#endif
