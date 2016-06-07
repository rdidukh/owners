#include "Matrix.h"
#include "Graph.h"
#include "Algos.h"

void test()
{
	Matrix::test();
    Graph::test();

    RecursionAlgo recursionAlgo;
    BaseAlgo::test(recursionAlgo);
}
