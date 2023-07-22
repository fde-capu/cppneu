#ifndef AXON_HPP
# define AXON_HPP

# include "extern.hpp"
# include "types.hpp"

class Axon
{
	public:
		size_t slotIn;
		size_t slotOut;
		zo multiplier;
		zo originalMultiplier;
		zo charge;

	public:
		Axon(
			size_t slotIn = ST_MAX,
			size_t slotOut = ST_MAX,
			zo u_multiplier = -1.0
		);
		Axon(Axon const &);
		Axon& operator= (Axon const &);
		virtual ~Axon();
		std::string readable(std::map<size_t, std::string>&) const;
		void feed(zo);
};

#endif
