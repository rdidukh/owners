#pragma once

#ifndef FILE_ALGOS_H
#define FILE_ALGOS_H

#include "Matrix.h"

class Algo
{
public:
	virtual bool calculate(const Matrix & inMtx, Matrix & outMtx) = 0;
	virtual std::string getErrorString() = 0;
};

class BaseAlgo : public Algo
{
public:
	virtual std::string getErrorString();
    static bool test(Algo & algo);
protected:
	void setErrorString(const std::string & str);
	bool preCheck(const Matrix & mtx);
private:
	std::string errStr;
};

class RecursionAlgo : public BaseAlgo
{
public:
	virtual bool calculate(const Matrix & inMtx, Matrix & outMtx);
};

#endif // !FILE_ALGOS_H