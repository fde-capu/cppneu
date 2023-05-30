#include "randoms.hpp"

zo randomZeroOne()
{
	return static_cast<zo>(randomValue<MEMORY_TYPE_SIZE>()) / static_cast<zo>(std::numeric_limits<MEMORY_TYPE_SIZE>::max());
}

zo variateZeroOne(zo & value, zo band)
{
	value += (randomZeroOne() - 0.5) * band;
	return value;
}
