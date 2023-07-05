#ifndef AXON_HPP
# define AXON_HPP

# include "defines.hpp"
# include "randoms.hpp"

class Axon
{
	public:
		size_t slotIn;
		size_t slotOut;
		zo multiplier;

	public:
		Axon(size_t slotIn = 0, size_t slotOut = 0,
			zo u_multiplier = -1.0);
		Axon(Axon const &);
		Axon& operator= (Axon const &);
		virtual ~Axon();
		std::string readable() const;
};

#endif
