#include "randoms.hpp"

ZERO_ONE_SIZE randomZeroOne()
{
	return static_cast<ZERO_ONE_SIZE>(randomValue<MEMORY_TYPE_SIZE>()) / static_cast<ZERO_ONE_SIZE>(std::numeric_limits<MEMORY_TYPE_SIZE>::max());
}

ZERO_ONE_SIZE variateZeroOne(ZERO_ONE_SIZE & value, ZERO_ONE_SIZE band)
{
	value += (randomZeroOne() - 0.5) * band;
	return value;
}
