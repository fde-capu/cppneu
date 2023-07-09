#ifndef TYPESNEURON_HPP
# define TYPESNEURON_HPP

# include "DynamicNeuron.hpp"
# include "defines.hpp"

class TypesNeuron: public virtual DynamicNeuron
{
	public:
		int type;

	public:
		TypesNeuron(int type = DEFAULT_NEURON_TYPE);
		TypesNeuron(TypesNeuron const&);
		TypesNeuron& operator= (TypesNeuron const&);
		bool isNeuron();
		bool isBias();
		bool hasInput();
		bool hasOutput();
		virtual std::string readable() const;
		virtual ~TypesNeuron();
};

#endif
