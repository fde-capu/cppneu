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
# include "Axon.hpp"

class Being {
	public:
		static size_t g_Neuron_UID;

		std::map<size_t, NEURON> neuron_table = {};
		std::map<size_t, Axon> axon_table = {};
		std::map<size_t, zo> neuronOut = {};
		std::map<size_t, zo> axonOut = {};
		zo actionScore = 0.0;
		std::string bestAction = "";
		size_t count_neuron = 0;
		size_t count_axon = 0;
		size_t count_bias = 0;

		void addAxon();
		void addNeuron(t_config& u_);

		void process();
		void processAxons();
		void readInput(NEURON&);
		void extraFiringProcess(NEURON&);

		size_t randomNeuronWithOutput();
		size_t randomNeuronWithInput();

		virtual std::string readable() const ;
	
	public:
		bool bias_switch = true;
		void switchBias();
};

#endif
