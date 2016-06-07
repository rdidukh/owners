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

struct Equal
{
    template<typename U, typename V, typename W>
    bool operator()(const U & a, const V & b, const W &)
    { 
        return a == b;
    }
};

struct NotEqual
{
	template<typename U, typename V, typename W>
	bool operator()(const U & a, const V & b, const W &)
	{
		return a != b;
	}
};

struct FloatEqual
{
	template<class U>
	bool operator()(const U & a, const U & b, const U& prec)
	{
		return std::fabs(a - b) < prec;
	}
};

template<typename U, typename V, typename Compare, typename W>
bool assert_common(const U & expected, const V & actual, const char * expStr, const char * actStr, const char * file, unsigned line, Compare comp, const W & third, const char * opposite, bool detailed)
{
    bool res = comp(actual, expected, third);

    if(!res)
    {
		std::cout << std::endl;
		std::cout << file << ":" << line << std::endl;
        std::cout << RED_COLOR << "FAIL: " << actStr << " " << opposite << " " << expStr << NO_COLOR << std::endl;
		if(detailed)
		{
			std::cout << actStr << ": " << std::endl;
			std::cout << "Expected: " << expected << std::endl;
			std::cout << "Actual: " << actual << std::endl;
		}
        return false;
    }
    else 
    {
		std::cout << GREEN_COLOR << '+' << NO_COLOR;
    }

    return true;
}

#define ASSERT_COMMON(expected, actual, expStr, actStr, comp, third, opposite, detailed) \
    do {\
		bool ret = assert_common(expected, actual, expStr, actStr, __FILE__, __LINE__, comp, third, opposite, detailed); \
		if(!ret) exit(1); \
       } while(0);

#define ASSERT_TRUE(x) ASSERT_COMMON(true, x, "TRUE", #x, Equal(), 0, "!=", false)
#define ASSERT_FALSE(x) ASSERT_COMMON(false, x, "FALSE", #x, Equal(), 0, "!=", false)
#define ASSERT_NULL(x) ASSERT_COMMON(NULL, x, "NULL", #x, Equal(), 0, "!=", false)
#define ASSERT_NOTNULL(x) ASSERT_COMMON(NULL< x, "NULL", #x, NotEqual(), 0, "==", false)
#define ASSERT_EQ(expected, actual) ASSERT_COMMON(expected, actual, #expected, #actual, Equal(), 0, "!=", true)
#define ASSERT_FLOAT_EQ(expected, actual, precision) ASSERT_COMMON(expected, actual, #expected, #actual, FloatEqual(), precision, "!=", true)


#endif //TEST_FRAMEWORK_H
