#ifndef TYPESNEURON_HPP
# define TYPESNEURON_HPP

# include "DynamicNeuron.hpp"

class TypesNeuron: public virtual DynamicNeuron
{
	public:
		int type;
		size_t slotIn;
		size_t slotOut;
		zo multiplyer;

	public:
		bool isBeing();
		bool isAxon();
		bool isBias();
		TypesNeuron(int, zo);
		bool hasInput();
		bool hasOutput();
		virtual std::string readable() const;
};

#endif
