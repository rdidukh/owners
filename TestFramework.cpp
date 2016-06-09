#include "TestFramework.h"

#include <string>
#include <vector>
#include <cassert>

template<class T>
T * align_forward(T * addr, unsigned n)
{
	assert((n&(n - 1)) == 0 && (n != 0));
	unsigned long ul = reinterpret_cast<unsigned long>(addr);
	return reinterpret_cast<T*>((ul + n - 1) % n);
}

int pluses = 0;
static int bigTestsCounter = 0;
static RdBigTestMap * bigTests = NULL;

RdBigTestInitialiser::RdBigTestInitialiser()
{
	if(bigTestsCounter++ == 0)
	{
		pluses = 0;
		bigTests = new RdBigTestMap();
	}
}

RdBigTestInitialiser::~RdBigTestInitialiser()
{
	if(--bigTestsCounter == 0)
	{
		delete bigTests;
	}
}

void addLittleTest(const std::string & name, RdLittleTest * littleTest)
{
    getBigTest(name).addLittleTest(littleTest);
}

RdBigTest & getBigTest(const std::string & name)
{
    if(bigTests->find(name) == bigTests->end())
        bigTests->insert(make_pair(name, RdBigTest(name)));
    return bigTests->find(name)->second;
}

RdLittleTest::RdLittleTest(const std::string & className, const std::string & testName):name(testName)
{
    addLittleTest(className, this);
}

RdBigTest::RdBigTest(const std::string & className):name(className)
{
}

void RdBigTest::addLittleTest(RdLittleTest * littleTest)
{
    littleTests.push_back(littleTest);
}

void RdBigTest::runAll()
{
    for(std::map<std::string, RdBigTest>::iterator it = bigTests->begin(); it != bigTests->end(); ++it)
        it->second.run();
}

void RdBigTest::run()
{
    unsigned ok = 0, fail = 0;
    for(std::vector<RdLittleTest *>::iterator it = littleTests.begin(); it != littleTests.end(); ++it)
    {
        RdLittleTest & littleTest = *(*it);
        littleTest.ok = true;
        littleTest.run();
        if(littleTest.ok)
        {
            cout() << GREEN_COLOR << name << "::" << littleTest.name << "   OK" << NO_COLOR << '\n';
            ok++;
        }
        else
        {
            cout() << RED_COLOR << name << "::" << littleTest.name << "   FAILED" << NO_COLOR << '\n';
            fail++;
        }
    }
    if(fail > 0)
    {
        cout() << RED_COLOR << name << ": " << fail << " out of " << (ok+fail) << "FAILED" << NO_COLOR << '\n';
    }
    else
    {
        cout() << GREEN_COLOR << name << ": " << ok << " out of " << ok << " OK" << NO_COLOR << '\n';
    }
}
