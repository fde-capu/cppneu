#ifndef METANEURON_HPP
# define METANEURON_HPP

# include "TypesNeuron.hpp"

class MetaNeuron: public virtual TypesNeuron
{
	public:
		std::string name;
		int expressor;
		int scaleMin;
		int scaleMax;
		std::string unit;
		std::vector<std::string> scale;

	public:
		MetaNeuron(std::string, int, int, int, std::string, std::vector<std::string>);
		MetaNeuron(MetaNeuron const&);
		MetaNeuron& operator= (MetaNeuron const&);
		~MetaNeuron();

		virtual std::string readable() const;
};

#endif
