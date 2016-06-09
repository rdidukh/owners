#include "TestFramework.h"

#include <string>
#include <vector>


static int bigTestsCounter = 0;
char bigTestsBuffer[sizeof(bigTests) + 15];
char * bigTestsBufferPtr = bigTestsBuffer;
static std::map<std::string, RdBigTest> & bigTests = reinterpret_cast<std::map<std::string, RdBigTest> &>((bigTestsBufferPtr+15)%16);

struct RdBigTestInitialiser
{
    RdBigTestInitialiser();
    ~RdBigTestInitialiser()
} rdBigTestInitialiser;

RdBigTestInitialiser::RdBigTestInitialiser()
{
    if(bigTestsCounter++ == 0)
        new( &bigTests ) std::map<std::string, RdBigTest>( );
}

RdBigTestInitialiser::~RdBigTestInitialiser()
{
    if(--bigTestsCounter == 0)
        (&bigTests)->~std::map<std::string, RdBigTest>();
}

void addLittleTest(const std::string & name, RdLittleTest * littleTest)
{
    getBigTest(name).addLittleTest(littleTest);
}

RdBigTest & getBigTest(const std::string & name)
{
    if(bigTests.find(name) == bigTests.end())
        bigTests.insert(make_pair(name, RdBigTest(name)));
    return bigTests.find(name)->second;
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
    for(std::map<std::string, RdBigTest>::iterator it = bigTests.begin(); it != bigTests.end(); ++it)
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
            std::cout << GREEN_COLOR << name << "::" << littleTest.name << "   OK" << NO_COLOR << '\n';
            ok++;
        }
        else
        {
            std::cout << RED_COLOR << name << "::" << littleTest.name << "   FAILED" << NO_COLOR << '\n';
            fail++;
        }
    }
    if(fail > 0)
    {
        std::cout << RED_COLOR << name << ": " << fail << " FAILED out of " << (ok+fail) << NO_COLOR << '\n';
    }
    else
    {
        std::cout << GREEN_COLOR << name << ": " << "ALL " << ok << " OK" << NO_COLOR << '\n';
    }
}
