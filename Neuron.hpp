#ifndef NEURON_HPP
# define NEURON_HPP
# include "defines.hpp"
# include <cstdlib>
# include <string>
# include <sstream>
# include <vector>
# include <map>
# include "randoms.hpp"
# include <ncurses.h>
# include "graphics.hpp"

typedef struct TypeNeuronConfig
{
	int type;
	std::string name;
	int expressor;
	int scaleMin;
	int scaleMax;
	std::string unit;
	std::vector<std::string> scale;
	ZERO_ONE_SIZE dump;
} t_config;

class Neuron {
	public:
		static void Physical(std::string, std::vector<std::string>, int expressor = EXPRESSOR_ORIGINAL_THRESHOLD);
		static void Measure(std::string, std::vector<std::string> = {}, int expressor = EXPRESSOR_THRESHOLD);
		static void Vital(std::string, std::vector<std::string> = {}, int = 0, int = 0, std::string = "", ZERO_ONE_SIZE dump = 0.5, int expressor = EXPRESSOR_THRESHOLD);
		static void Action(std::string, std::vector<std::string> = {});
		static void Axon(int amount = 1);
		static void Bias(int amount = 1);
		static void reset();

		MEMORY_TYPE_SIZE threshold;
		MEMORY_TYPE_SIZE originalThreshold;
		MEMORY_TYPE_SIZE inputValue;
		MEMORY_TYPE_SIZE outputValue;
		ZERO_ONE_SIZE thresholdPull;
		ZERO_ONE_SIZE thresholdStability;
		ZERO_ONE_SIZE speed;
		ZERO_ONE_SIZE force;

		size_t UID;
		int type;
		std::string name;
		int expressor;
		size_t slotIn;
		size_t slotOut;
		ZERO_ONE_SIZE multiplyer;
		int scaleMin;
		int scaleMax;
		std::string unit;
		std::vector<std::string> scale;
		ZERO_ONE_SIZE dump;
		ZERO_ONE_SIZE thresholdDecay;

		static size_t globalUID;
		static std::vector<Neuron> table;
		static std::vector<ZERO_ONE_SIZE> out;
		static std::vector<ZERO_ONE_SIZE> axonOut;
		static std::vector<std::string> actions;
		static ZERO_ONE_SIZE actionScore;
		static std::string bestAction;
		static MEMORY_TYPE_SIZE max();

		static size_t count_neuron;
		static size_t count_axon;
		static size_t count_bias;

		Neuron(const t_config& u_);
		Neuron(int type, std::string name);
		Neuron(int type, std::string name, std::vector<std::string> scale);
		Neuron(int type, std::string name, int scaleMin, int scaleMax, std::string unit, std::vector<std::string> scale);
		Neuron(int type);

		void extraProcess();
		void process();
		static void processAll();
		static void processAxons();
		void readAxons();
		void updateInternals();
		static size_t size();

		static void printScreen();
		static void printHeader();
		static void printAllCharacters();
		static void printAllBars();
		static void printAllAxons();
		static void printOuts();
		static void printFile();
		static void printAllDescriptions();
		static void printWantedActions();

		static void toggleDisplayHeader();
		static void toggleDisplayCharacters();
		static void toggleDisplayPhysical();
		static void toggleDisplayVital();
		static void toggleDisplayAction();
		static void toggleDisplayMeasure();
		static void toggleDisplayActionResolution();
		static void toggleDisplayBars();
		static void toggleDisplayOuts();
		static void toggleDisplayAxons();
		static void toggleDisplayBiasBars();

		static bool displayHeader;
		static bool displayCharacters;
		static bool displayPhysical;
		static bool displayVital;
		static bool displayAction;
		static bool displayMeasure;
		static bool displayActionResolution;
		static bool displayBars;
		static bool displayOuts;
		static bool displayAxons;
		static bool displayBiasBars;

		void printAsciiBar();
		void printCharacter();
		std::string printDescription(bool silent = false);
		size_t randomNeuronWithOutput();
		size_t randomNeuronWithInput();
		bool isNeuron();
		bool isAxon();
		bool isBias();
		bool isStatsVisible();
		bool isBarVisible();
		bool isCharacterVisible();
		bool isOutBlockVisible();
		bool hasInput();
		bool hasOutput();
};

#endif
