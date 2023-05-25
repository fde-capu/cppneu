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
	private:
		MEMORY_TYPE_SIZE threshold;
		MEMORY_TYPE_SIZE originalThreshold;
		MEMORY_TYPE_SIZE inputValue;
		MEMORY_TYPE_SIZE outputValue;
		ZERO_ONE_SIZE thresholdPull;
		size_t UID;
		std::string name;

	public:
		static size_t globalUID;
		static std::vector<Neuron> table;
		static std::vector<ZERO_ONE_SIZE> out;
		static std::vector<std::string> actions;
		static ZERO_ONE_SIZE actionScore;
		static std::string bestAction;

		Neuron(std::string name);
		MEMORY_TYPE_SIZE getInputValue() const;
		MEMORY_TYPE_SIZE getThreshold() const;
		MEMORY_TYPE_SIZE getOriginalThreshold() const;
		size_t getUID() const;
		MEMORY_TYPE_SIZE getOutputValue() const;
		std::string getName() const;
		void process();
		static void processAll();
		ZERO_ONE_SIZE getThresholdDecFactor() const;
		void readAxons();
		void updateInternals();
		static size_t size();
		static void printAllCharacters();
		static void printAllBars();
		static void printOuts();
		static void printFile();
		void printAsciiBar();
		void printCharacter();
};

class Axon {
	private:
		size_t UID;
		size_t slotIn;
		size_t slotOut;
		ZERO_ONE_SIZE multiplyer;

	public:
		static std::vector<Axon> table;
		static std::vector<ZERO_ONE_SIZE> out;

		Axon();
		size_t getUID() const;
		size_t getSlotIn() const;
		size_t getSlotOut() const;
		ZERO_ONE_SIZE getMultiplyer() const;
		static void printAll();
		static void processAll();
};

#endif
