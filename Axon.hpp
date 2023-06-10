#ifndef AXON_HPP
# define AXON_HPP

# include "defines.hpp"
# include "randoms.hpp"

class Axon
{
	public:
		size_t axon_UID;
		size_t slotIn;
		size_t slotOut;
	
	public:
		zo multiplier;

	public:
		Axon(size_t slotIn = 0, size_t slotOut = 0);
		Axon(Axon const &);
		Axon& operator= (Axon const &);
		virtual ~Axon();
		static size_t g_Axon_UID;
};

#endif
