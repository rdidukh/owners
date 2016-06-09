#include "Algos.h"
#include "Matrix.h"
#include "TestFramework.h"
#include <sstream>

bool BaseAlgo::preCheck(const Matrix & mtx)
{
	unsigned rows = mtx.rows();

	if(rows == 0)
	{
		setErrorString("Empty matrix(rows = 0)");
		return false;
	}

	unsigned cols = mtx.cols();

	if(cols == 0)
	{
		setErrorString("Empty matrix(cols = 0)");
		return false;
	}

	for(auto & row : mtx)
	{
		if(row.size() != cols)
		{
			setErrorString("Matrix is not uniform");
			return false;
		}
	}

	for(unsigned j = 0; j < cols; j++)
	{
		double colSum = 0;
		for(unsigned i = 0; i < rows; i++)
			colSum += mtx[i][j];
		if(colSum != 0 && fabs(1.0 - colSum) > std::numeric_limits<double>::epsilon())
		{
			std::ostringstream oss;
			oss << "Sum of column " << j << " is " << colSum << std::endl;
			setErrorString(oss.str());
			return false;
		}
	}

	// TODO: check whether graph is DAG
	return true;
}

void BaseAlgo::setErrorString(const std::string & str)
{
	errStr = str;
}

std::string BaseAlgo::getErrorString()
{
	return errStr;
}

bool BaseAlgo::test(Algo & algo)
{
    std::istringstream iss(""
    "2 2     "
    "0.0 1.0 "
    "0.0 0.0 ");

    Matrix inMtx, outMtx;
    bool ret;

    iss >> inMtx;

    ret = algo.calculate(inMtx, outMtx);
#if 0
    ASSERT_TRUE(ret);
    ASSERT_TRUE(inMtx == outMtx);
#endif
    return true;
}
