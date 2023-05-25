#ifndef NEURON_HPP
# define NEURON_HPP
# include "defines.hpp"
# include <cstdlib>
# include <string>
# include <vector>
# include "randoms.hpp"
# include <ncurses.h>
# include "graphics.hpp"

class Neuron {
	public:
		MEMORY_TYPE_SIZE threshold;
		MEMORY_TYPE_SIZE originalThreshold;
		MEMORY_TYPE_SIZE inputValue;
		MEMORY_TYPE_SIZE outputValue;
		ZERO_ONE_SIZE thresholdPull;
		size_t UID;
		std::string name;
		int type;
		size_t slotIn;
		size_t slotOut;
		ZERO_ONE_SIZE multiplyer;
		std::vector<std::string> scale;

		static size_t globalUID;
		static std::vector<Neuron> table;
		static std::vector<ZERO_ONE_SIZE> out;
		static std::vector<ZERO_ONE_SIZE> axonOut;
		static std::vector<std::string> actions;
		static ZERO_ONE_SIZE actionScore;
		static std::string bestAction;

		Neuron(int type, std::string name);
		Neuron(int type, std::string name, std::vector<std::string>);
		Neuron(int type);

		void process();
		static void processAll();
		static void processAxons();
		void readAxons();
		void updateInternals();
		static size_t size();
		static void printAllCharacters();
		static void printAllBars();
		static void printAllAxons();
		static void printOuts();
		static void printFile();
		void printAsciiBar();
		void printCharacter();
		size_t randomNeuron();
};

#endif
