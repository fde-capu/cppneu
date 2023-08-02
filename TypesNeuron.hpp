#ifndef TYPESNEURON_HPP
# define TYPESNEURON_HPP

# include "DynamicNeuron.hpp"

class TypesNeuron: public virtual DynamicNeuron
{
	public:
		int type;

	public:
		TypesNeuron(int type = DEFAULT_NEURON_TYPE);
		TypesNeuron(TypesNeuron const&);
		TypesNeuron& operator= (TypesNeuron const&);
		bool isNeuron() const;
		bool isBias() const;
		bool hasInput() const;
		bool hasOutput() const;
		virtual std::string readable() const;
		virtual ~TypesNeuron();
};

#endif
