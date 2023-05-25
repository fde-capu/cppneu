#ifndef RANDOMS_HPP
# define RANDOMS_HPP
# include "randoms.hpp"
# include <random>

template <typename T = MEMORY_TYPE_SIZE>
T randomValue() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<typename std::make_unsigned<T>::type> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
	return static_cast<T>(dist(gen));
}

template <typename T = MEMORY_TYPE_SIZE>
T variateValue(T& value, float band = 1.0) {
	T newValue = randomValue<T>();
	value = ((float)newValue - (float)value) * band + (float)value;
	return value;
}

#endif
