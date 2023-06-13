#ifndef METANEURON_HPP
# define METANEURON_HPP

# include "TypesNeuron.hpp"

class MetaNeuron: public virtual TypesNeuron
{
	public:
		size_t neuron_UID;
		std::string name;
		int expressor;
		int scaleMin;
		int scaleMax;
		std::string unit;
		std::vector<std::string> scale;

	public:
		MetaNeuron(t_config);
		MetaNeuron();
		MetaNeuron(MetaNeuron const&);
		MetaNeuron& operator= (MetaNeuron const&);
		~MetaNeuron();

		virtual std::string readable() const;
		std::string getDescription();

	private:
		bool customScale() const;
};

#endif
