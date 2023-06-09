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

class Being: public virtual NEURON {
	public:
		static std::vector<Being> table;

		static zo actionScore;
		static std::string bestAction;
		static std::vector<zo> out;
		static std::vector<zo> axonOut;
		static size_t count_being;
		static size_t count_axon;
		static size_t count_bias;

		static void reset();
		Being(const t_config& u_);
		Being(int type);

		void extraFiringProcess();
		void process();
		static void processAll();
		static void processAxons();
		void readAxons();
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

		static void setDisplay(int);
		static void toggleDisplayHeader();
		static void toggleDisplayCharacters();
		static void toggleDisplayPhysical();
		static void toggleDisplayVital();
		static void toggleDisplayAction();
		static void toggleDisplayMeasure();
		static void toggleDisplayActionResolution();
		static void toggleDisplayBarsUp();
		static void toggleDisplayBarsDown();
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
		static int displayBars;
		static bool displayOuts;
		static bool displayAxons;
		static bool displayBiasBars;

		void printAsciiBar();
		void printCharacter();
		void printNumbers();
		std::string printDescription(bool silent = false);

		bool isStatsVisible();
		bool isBarVisible();
		bool isCharacterVisible();
		bool isOutBlockVisible();

		size_t randomBeingWithOutput();
		size_t randomBeingWithInput();

		static const std::string to_string();
		virtual std::string readable() const ;
};

#endif
