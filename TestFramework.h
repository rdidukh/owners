#pragma once

#include <iostream>

#define RED_COLOR 	"\033[0;31m"
#define GREEN_COLOR	"\033[0;32m"
#define NO_COLOR	"\033[0m"

template<typename U, typename V>
void assert_eq(const U & expected, const V & actual, const char * expStr, const char * actStr, const char * file, unsigned line)
{
    if(actual != expected)
    {
		std::cerr << file << ":" << line << std::endl;
        std::cerr << RED_COLOR << "FAIL: " << actStr << " != " << expStr << NO_COLOR << std::endl;
        std::cerr << actStr << ": " << std::endl;
        std::cerr << "Expected: " << expected << std::endl;
        std::cerr << "Actual: " << actual << std::endl;
        exit(1);
    }
    else 
    {
		std::cout << GREEN_COLOR << "OK: " << actStr << " == " << expStr << NO_COLOR << std::endl; \
    }
}

template<typename U>
void assert_eq_float(const U & expected, const U & actual, const U & precision, const char * expStr, const char * actStr, const char * file, unsigned line)
{
    U diff = expected - actual;
    if(diff < 0)
        diff = -diff;

    if(diff > precision)
    {
		std::cerr << file << ":" << line << std::endl;
        std::cerr << RED_COLOR << "FAIL: " << actStr << " != " << expStr << " +- " << precision << NO_COLOR << std::endl;
        std::cerr << actStr << ": " << std::endl;
        std::cerr << "Expected: " << expected << std::endl;
        std::cerr << "Actual: " << actual << std::endl;
        std::cerr << "Precision: " << precision << std::endl;
        exit(1);
    }
    else
    {
        std::cout << GREEN_COLOR << "OK: " << actStr << " == " << expStr << " +- " << precision  << NO_COLOR << std::endl; \
    }

}

#define ASSERT_NULL(x)																	\
	do {																				\
		if((x) != NULL)																	\
		{																				\
			std::cerr << __FILE__ << ":" << __LINE__ << std::endl;						\
			std::cerr << RED_COLOR << "FAIL: " #x " != NULL" << NO_COLOR << std::endl;	\
			exit(1);																	\
		} else {																		\
			std::cout << GREEN_COLOR << "OK: " #x " == NULL" << NO_COLOR << std::endl;	\
		}																				\
	} while(0);

#define ASSERT_NOTNULL(x)																\
	do {																				\
		if((x) == NULL)																	\
		{																				\
			std::cerr << __FILE__ << ":" << __LINE__ << std::endl;						\
			std::cerr << RED_COLOR << "FAIL: " #x " == NULL" << NO_COLOR << std::endl;	\
			exit(1);																	\
		} else {																		\
			std::cout << GREEN_COLOR << "OK: " #x " != NULL" << NO_COLOR << std::endl;	\
		}																				\
	} while(0);

#define ASSERT_TRUE(x)																	\
	do {																				\
		if((x) != true)																	\
		{																				\
			std::cerr << __FILE__ << ":" << __LINE__ << std::endl;						\
			std::cerr << RED_COLOR << "FAIL: " #x " != TRUE" << NO_COLOR << std::endl;	\
			exit(1);																	\
		} else {																		\
			std::cout << GREEN_COLOR << "OK: " #x " == TRUE" << NO_COLOR << std::endl;	\
		}																				\
	} while(0);

#define ASSERT_FALSE(x)																	\
	do {																				\
		if((x) != false)																\
		{																				\
			std::cerr << __FILE__ << ":" << __LINE__ << std::endl;						\
			std::cerr << RED_COLOR << "FAIL: " #x " != FALSE" << NO_COLOR << std::endl;	\
			exit(1);																	\
		} else {																		\
			std::cout << GREEN_COLOR << "OK: " #x " == FALSE" << NO_COLOR << std::endl;	\
		}																				\
	} while(0);

#define ASSERT_EQ(expected, actual) \
	do {	\
		assert_eq(expected, actual, #expected, #actual, __FILE__, __LINE__); \
	} while(0);

#define ASSERT_EQ_F(expected, actual, precision) \
	do {	\
		assert_eq_float(expected, actual, precision, #expected, #actual, __FILE__, __LINE__); \
	} while(0);