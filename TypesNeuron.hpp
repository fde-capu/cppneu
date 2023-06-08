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
		TypesNeuron(int, size_t, size_t, zo);
		TypesNeuron(TypesNeuron const&);
		TypesNeuron& operator= (TypesNeuron const&);
		bool isBeing();
		bool isAxon();
		bool isBias();
		bool hasInput();
		bool hasOutput();
		virtual std::string readable() const;
		virtual ~TypesNeuron();
};

#endif
