#ifndef BEING_HPP
# define BEING_HPP

# include "defines.hpp"
# include LAST_NEURON_IMPLEMENTATION
# include "Axon.hpp"
# include "helpers.hpp"

class Being {
	public:
		static size_t g_Neuron_UID;
		static size_t g_Axon_UID;

		std::map<size_t, NEURON> neuron_table = {};
		std::map<size_t, Axon> axon_table = {};
		std::map<size_t, zo> neuronOut = {};
		std::map<size_t, zo> axonOut = {};
		std::map<size_t, size_t> inCount = {};
		std::map<size_t, std::vector<zo> > fireCount = {};
		zo actionScore = 0.0;
		std::deque<size_t> bestAction;
		size_t count_neuron = 0;
		size_t count_axon = 0;
		size_t count_bias = 0;

		void addAxon(t_config& u_);
		void addNeuron(t_config& u_);

		void process();
		void balanceAxons();
		void processAxons();
		void readInput(NEURON&);
		void extraFiringProcess(NEURON&);

		void inaction();
		void ponderAction(const NEURON&);

		size_t randomNeuronWithOutput();
		size_t randomNeuronWithInput();

		virtual std::string readable();
		void nextId(size_t&) const;

		void on();
		std::map<size_t, std::string> nameList = {};
		std::map<size_t, size_t> axonMergeCount = {};
		NEURON& neuronByName(const std::string&);
		void poke(const std::string&);
	
	public:
		bool bias_switch = true;
		void switchBias();

		void save();
		std::string name;

		Being();
		virtual ~Being();
};

#endif
