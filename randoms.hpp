#ifndef RANDOMS_HPP
# define RANDOMS_HPP

# include <random>
# include "header.hpp"

zo randomZeroOne();
zo variateZeroOne(zo & value, zo band = 1.0);

template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
T randomValue(T min = T(), T max = std::numeric_limits<T>::max()) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<typename std::make_unsigned<T>::type> dist(min, max);
    return static_cast<T>(dist(gen));
}

template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
T randomValue(T min = T(), T max = std::numeric_limits<T>::max())
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dist(min, max);
    return static_cast<T>(dist(gen));
}

template <typename T = MEMORY_TYPE_SIZE>
T variateValue(T& value, zo band = 1.0)
{
	if (band == 0.0)
		return value;
	T valBand = (static_cast<zo>(std::numeric_limits<T>::max()) * band) / 2;
	T min = 
		value - valBand < value ?
		value - valBand : 0;
	T max =
		value + valBand > value ?
		value + valBand : std::numeric_limits<T>::max();
//	printw("preval %u, max * band %u , min %u, max %u, ", value, valBand, min, max);
	value = randomValue<T>(min, max);
//	printw("val %u\n", value);
	return value;
}

#endif
