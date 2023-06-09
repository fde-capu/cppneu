#ifndef METANEURON_HPP
# define METANEURON_HPP

# include "TypesNeuron.hpp"

class MetaNeuron: public virtual TypesNeuron
{
	public:
		MetaNeuron();
		MetaNeuron(MetaNeuron const&);
		MetaNeuron& operator= (MetaNeuron const&);
		~MetaNeuron();

		virtual std::string readable() const;
};

#endif
