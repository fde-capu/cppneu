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

		Being();
		Being(const t_config& u_);
		void addNeuron(const t_config& u_);
		Being(int type);
		void reset();

		void extraFiringProcess();
		void process();
		static void processAll();
		static void processAxons();
		void readAxons();
		static size_t size();

		static void setDisplay(int);
		static void toggleDisplayHeader();
		static void toggleDisplayCharacters();
		static void toggleDisplayPhysical();
		static void toggleDisplayVital();
		static void toggleDisplayAction();
		static void toggleDisplayMeasure();
		static void toggleDisplayActionResolution();

		static int displayBars;

		std::string getDescription();

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
