#ifndef TYPESNEURON_HPP
# define TYPESNEURON_HPP

# include "DynamicNeuron.hpp"

class TypesNeuron: public virtual DynamicNeuron
{
	public:
		TypesNeuron(zo);
		virtual std::string readable() const;
};

#endif
