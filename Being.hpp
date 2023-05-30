#ifndef BEING_HPP
# define BEING_HPP

# include <vector>
# include "defines.hpp"
# include <string>
# include "randoms.hpp"
# include <ncurses.h>
# include <sstream>

typedef struct TypeBeingConfig
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

class Being {
	public:
		typedef struct Scale {
			int scaleMin;
			int scaleMax;
			std::string unit;
		} t_scale;
			
		static void Physical(std::string, std::vector<std::string>, int expressor = EXPRESSOR_ORIGINAL_THRESHOLD);
		static void Measure(std::string, std::vector<std::string> = {}, int expressor = EXPRESSOR_THRESHOLD);
		static void Create(int = 0, std::string = "", std::vector<std::string> = {}, t_scale = {}, int = EXPRESSOR_THRESHOLD, ZERO_ONE_SIZE = 0.0);
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
		static std::vector<Being> table;
		static std::vector<ZERO_ONE_SIZE> out;
		static std::vector<ZERO_ONE_SIZE> axonOut;
		static std::vector<std::string> actions;
		static ZERO_ONE_SIZE actionScore;
		static std::string bestAction;
		static MEMORY_TYPE_SIZE max();

		static size_t count_being;
		static size_t count_axon;
		static size_t count_bias;

		Being(const t_config& u_);
		Being(int type, std::string name);
		Being(int type, std::string name, std::vector<std::string> scale);
		Being(int type, std::string name, int scaleMin, int scaleMax, std::string unit, std::vector<std::string> scale);
		Being(int type);

		void extraFiringProcess();
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
		size_t randomBeingWithOutput();
		size_t randomBeingWithInput();
		bool isBeing();
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
