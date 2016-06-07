#pragma once

#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>

#ifdef WIN32
#define RED_COLOR 	""
#define GREEN_COLOR	""
#define NO_COLOR	""
#else
#define RED_COLOR 	"\033[0;31m"
#define GREEN_COLOR	"\033[0;32m"
#define NO_COLOR	"\033[0m"
#endif

template<typename U, typename V>
struct Equal
{
    Equal( const U & a, const V & b ) {}
    bool operator()(const U & a, const V & b)
    { 
        return a == b;
    }
};



template<typename U, typename V, typename Compare>
bool assert_common(const U & expected, const V & actual, const char * expStr, const char * actStr, const char * file, unsigned line, Compare comp, const char * opposite)
{
    bool res = comp(actual, expected);

    if(res)
    {
		std::cerr << file << ":" << line << std::endl;
        std::cerr << RED_COLOR << "FAIL: " << actStr << " " << opposite << " " << expStr << NO_COLOR << std::endl;
        std::cerr << actStr << ": " << std::endl;
        std::cerr << "Expected: " << expected << std::endl;
        std::cerr << "Actual: " << actual << std::endl;
        return false;
    }
    else 
    {
		// std::cout << GREEN_COLOR << "OK: " << actStr << " == " << expStr << NO_COLOR << std::endl;
    }
    return true;
}

#define ASSERT_COMMON(expected, actual, expStr, actStr, comp, opposite, detailed) \
    do {\
       bool ret = actual ##comp## expected; \
       if(!ret) {\
              std::cerr << __FILE__ << ":" << __LINE__ << std::endl; \
              std::cerr << RED_COLOR << "FAIL: " << actStr << opposite << expStr << NO_COLOR << std::endl; \
              if(detailed) { \
              std::cerr << actStr << ": " << std::endl;           \
              std::cerr << "Expected: " << expected << std::endl; \
              std::cerr << "Actual: " << actual << std::endl; \
                            }\
              exit(1); \
                       } \
        } while(0);

#define ASSERT_TRUE(x) ASSERT_COMMON(true, x, "TRUE", #x, ==, "!=", false)
#define ASSERT_FALSE(x) ASSERT_COMMON(false, x, "FALSE", #x, ==, "!=", false)

#if 0
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
#endif

#endif //TEST_FRAMEWORK_H
