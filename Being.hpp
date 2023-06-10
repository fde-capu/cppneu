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
		std::vector<zo> out;
		std::vector<zo> axonOut;

		static zo actionScore;
		static std::string bestAction;

		static size_t count_being;
		static size_t count_axon;
		static size_t count_bias;

		Being();
		void addNeuron(const t_config& u_);
		void reset();

		void process();
		void processAxons();
		void readAxons(NEURON&);
		void extraFiringProcess(NEURON&);

		size_t size();

		size_t randomBeingWithOutput();
		size_t randomBeingWithInput();

		const std::string to_string();
		virtual std::string readable() const ;
};

#endif
