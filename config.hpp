#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <assert.h>
#include <iostream>

typedef float real;


/**
 * Function for debug printing, bottom of recursion
 */
template<typename T>
void print(const T t) {
	std::cout << t << std::endl;
}

/**
 * Function for debug printing
 */
template<typename T, typename... Args>
void print(const T t, const Args... args) {
	std::cout << t << " ";
	print(args...);
}


#endif // CONFIG_HPP
