#ifndef NEURON_HPP
# define NEURON_HPP
# include "defines.hpp"
# include <cstdlib>
# include <string>
# include <vector>
# include "randoms.hpp"
# include <ncurses.h>
# include "graphics.hpp"

typedef struct TypeNeuronConfig
{
	int type;
	std::string name;
	int scaleMin;
	int scaleMax;
	std::string unit;
	std::vector<std::string> scale;
} t_config;

class Neuron {
	public:
		static void Measure(std::string, std::vector<std::string>, int = 0, int = 0, std::string = "");
		static void Oscil(std::string, std::vector<std::string>);

		MEMORY_TYPE_SIZE threshold;
		MEMORY_TYPE_SIZE originalThreshold;
		MEMORY_TYPE_SIZE inputValue;
		MEMORY_TYPE_SIZE outputValue;
		ZERO_ONE_SIZE thresholdPull;
		ZERO_ONE_SIZE thresholdStability;
		ZERO_ONE_SIZE speed;

		size_t UID;
		int type;
		std::string name;
		size_t slotIn;
		size_t slotOut;
		ZERO_ONE_SIZE multiplyer;
		int scaleMin;
		int scaleMax;
		std::string unit;
		std::vector<std::string> scale;

		static size_t globalUID;
		static std::vector<Neuron> table;
		static std::vector<ZERO_ONE_SIZE> out;
		static std::vector<ZERO_ONE_SIZE> axonOut;
		static std::vector<std::string> actions;
		static ZERO_ONE_SIZE actionScore;
		static std::string bestAction;

		Neuron(const t_config& u_);
		Neuron(int type, std::string name);
		Neuron(int type, std::string name, std::vector<std::string> scale);
		Neuron(int type, std::string name, int scaleMin, int scaleMax, std::string unit, std::vector<std::string> scale);
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
		void printDescription();
		size_t randomNeuron();
		bool isNeuron();
		bool isAxon();
		bool isStatsVisible();
};

#endif
