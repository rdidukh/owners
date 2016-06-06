#include "Matrix.h"
#include "Algos.h"

bool RecursionAlgo::calculate(const Matrix & inMtx, Matrix & outMtx)
{
	bool ret = preCheck(inMtx);

	if(!ret)
		return false;

	/*
	TODO: Implement
	*/

	outMtx = inMtx;

	return true;
}
